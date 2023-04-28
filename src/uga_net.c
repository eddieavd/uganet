//
//
//      uganet
//      uga_net.c
//

#include <uga_err.h>
#include <uga_net.h>

#include <stdio.h>

#define UGA_BACKLOG 16


sockaddr_in_t uga_ip_to_net ( char const * remote_ip )
{
        sockaddr_in_t saddr;

        int err = inet_pton( AF_INET, remote_ip, &( saddr.sin_addr ) );
        if( err != 1 )
        {
                uga_set_stdlib_err();
        }
        uga_clr_errs();
        return saddr;
}

char * uga_net_to_ip ( sockaddr_in_t const * saddr )
{
        char * ip = ( char * ) malloc( sizeof( char ) * INET_ADDRSTRLEN );

        char const * err = inet_ntop( AF_INET, &( saddr->sin_addr ), ip, INET_ADDRSTRLEN );

        if( err == NULL )
        {
                uga_set_stdlib_err();
                return NULL;
        }
        uga_clr_errs();
        return ip;
}

addrinfo_t * uga_addrinfo ( char const * host, uga_config const * config )
{
        int status ;

        addrinfo_t hints ;
        addrinfo_t * res ;

        memset( &hints, 0, sizeof( hints ) );

        hints.ai_family   = config->family;
        hints.ai_flags    = AI_PASSIVE;
        hints.ai_socktype = config->protocol == UGA_UDP ? SOCK_DGRAM : SOCK_STREAM ;

        if( ( status = getaddrinfo( host, config->port, &hints, &res ) ) != 0 )
        {
                uga_set_gai_err( status );
                return NULL;
        }
        uga_clr_errs();
        return res;
}

int uga_socket ( uga_config const * config )
{
        int sockfd;
        if( config->protocol == UGA_UDP )
        {
                sockfd = socket( config->family, SOCK_DGRAM, IPPROTO_IP );
        }
        else if( config->protocol == UGA_TCP )
        {
                sockfd = socket( config->family, SOCK_STREAM, IPPROTO_IP );
        }
        else
        {
                uga_errno = UGA_ERR_BAD_ARG;
                return -1;
        }
        if( sockfd == -1 )
        {
                uga_set_stdlib_err();
        }
        uga_clr_errs();
        return sockfd;
}

int uga_sock_from_addr ( addrinfo_t const * addr )
{
        int sockfd = socket( addr->ai_family, addr->ai_socktype, addr->ai_protocol );

        if( sockfd == -1 )
        {
                uga_set_stdlib_err();
        }
        uga_clr_errs();
        return sockfd;
}

int uga_shutdown ( int const sockfd, shutdown_mode const mode )
{
        int err = shutdown( sockfd, mode );
        if( err == -1 )
        {
                uga_set_stdlib_err();
                return -1;
        }
        uga_clr_errs();
        return 0;
}

int uga_close_sock ( int const sockfd )
{
        int err = close( sockfd );
        if( err == -1 )
        {
                uga_set_stdlib_err();
                return -1;
        }
        uga_clr_errs();
        return 0;
}

int uga_bind ( int sockfd, uga_config const * config )
{
        int err;
        sockaddr_in_t local_addr;

        local_addr.sin_family      = config->family;
        local_addr.sin_port        = htons( atoi( config->port ) );
        local_addr.sin_addr.s_addr = INADDR_ANY;

        err = bind( sockfd, ( sockaddr_t * ) &local_addr, sizeof( local_addr ) );
        if( err != 0 )
        {
                uga_set_stdlib_err();
                return -1;
        }
        uga_clr_errs();
        return 0;
}

int uga_get_bound_sock ( uga_config const * config )
{
        int sockfd;

        sockfd = uga_socket( config );

        uga_bind( sockfd, config );

        if( uga_had_errs() )
        {
                return -1;
        }
        uga_clr_errs();
        return sockfd;
}

int uga_connect_to_remote ( char const * remote_host, uga_config const * config )
{
        addrinfo_t * remote_addr = uga_addrinfo( remote_host, config );

        int sockfd = uga_sock_from_addr( remote_addr );

        int err = connect( sockfd, remote_addr->ai_addr, remote_addr->ai_addrlen );
        if( err == -1 )
        {
                uga_set_stdlib_err();
                return -1;
        }
        freeaddrinfo( remote_addr );
        return sockfd;
}

int uga_listen_on_port ( uga_config const * config )
{
        int sockfd = uga_get_bound_sock( config );

        if( uga_had_errs() )
        {
                return -1;
        }

        int err = listen( sockfd, UGA_BACKLOG );

        if( err != 0 )
        {
                uga_set_stdlib_err();
                return -1;
        }
        uga_clr_errs();
        return sockfd;
}

int uga_accept_and_handle ( int sockfd, int( *handle_connection )( int const clientfd ) )
{
        sockaddr_storage_t addr_str ;
        socklen_t          addr_len = sizeof( addr_str ) ;

        int clientfd = accept( sockfd, ( sockaddr_t * ) &addr_str, &addr_len );
        if( clientfd == -1 )
        {
                uga_set_stdlib_err();
                return -1;
        }
        uga_clr_errs();

        return handle_connection( clientfd );
}

int uga_send ( int sockfd, char const * data, int64_t const data_len )
{
        int64_t bsent = send( sockfd, data, data_len, 0 );
        if( bsent == -1 )
        {
                uga_set_stdlib_err();
                return -1;
        }
        if( bsent < data_len )
        {
                return uga_send( sockfd, data + bsent, data_len - bsent );
        }
        uga_clr_errs();

        return 0;
}

char * uga_recv ( int sockfd, int * bytes_recvd )
{
        char * buff = ( char * ) calloc( UGA_RECV_BUFFLEN, sizeof( char ) );
        if( !buff )
        {
                uga_set_stdlib_err();
                return NULL;
        }
        int recvd = recv( sockfd, buff, UGA_RECV_BUFFLEN, MSG_WAITALL );
        if( recvd == -1 )
        {
                uga_set_stdlib_err();
                free( buff );
                return NULL;
        }
        if( recvd == 0 )
        {
                free( buff );
        }
        *bytes_recvd = recvd;
        return buff;
}

char * uga_recv_all ( int sockfd, int * bytes_recvd )
{
        int recvd       = 0;
        int total_recvd = 0;
        int buff_size   = UGA_RECV_BUFFLEN;

        char * buff = ( char * ) calloc( UGA_RECV_BUFFLEN, sizeof( char ) );
        if( !buff )
        {
                uga_set_stdlib_err();
                return NULL;
        }
        printf( "uga::recv_all: allocated buffer.\n" );
        while( !uga_had_errs() )
        {
                printf( "uga::recv_all: calling recv...\n" );
                char * tmp = uga_recv( sockfd, &recvd );
                if( recvd == 0 || uga_had_errs() )
                {
                        printf( "uga::recv_all: recvd %d bytes, uga_errno is %d\n", recvd, uga_errno );
                        break;
                }
                if( buff_size < total_recvd + recvd )
                {
                        buff = ( char * ) realloc( buff, sizeof( char ) * total_recvd + recvd + UGA_RECV_BUFFLEN );
                        printf( "uga::recv_all: reallocated buffer.\n" );
                }
                printf( "uga::recv_all: received %d bytes!\n", recvd );
                memcpy( buff + total_recvd, tmp, recvd );
                total_recvd += recvd;
                free( tmp );
        }
        printf( "uga::recv_all: received %d bytes in total.\n", total_recvd );
        *bytes_recvd = total_recvd;
        return buff;
}
























