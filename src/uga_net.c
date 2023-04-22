//
//
//      uganet
//      uga_net.c
//

#include <uga_err.h>
#include <uga_net.h>

#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>



struct sockaddr_in uga_ip_to_net ( char const * remote_ip )
{
        struct sockaddr_in saddr;

        int err = inet_pton( AF_INET, remote_ip, &( saddr.sin_addr ) );
        if( err != 1 )
        {
                uga_set_stdlib_err();
        }
        return saddr;
}

char * uga_net_to_ip ( struct sockaddr_in const * saddr )
{
        char * ip = ( char * ) malloc( sizeof( char ) * INET_ADDRSTRLEN );

        char const * err = inet_ntop( AF_INET, &( saddr->sin_addr ), ip, INET_ADDRSTRLEN );

        if( err == NULL )
        {
                uga_set_stdlib_err();
                return NULL;
        }
        return ip;
}

struct addrinfo * uga_addrinfo ( char const * host, uga_config const * config )
{
        int status ;

        struct addrinfo hints ;
        struct addrinfo * res ;

        memset( &hints, 0, sizeof( hints ) );

        hints.ai_family   = config->family;
        hints.ai_flags    = AI_PASSIVE;
        hints.ai_socktype = config->protocol == UGA_UDP ? SOCK_DGRAM : SOCK_STREAM ;

        if( ( status = getaddrinfo( host, config->port, &hints, &res ) ) != 0 )
        {
                uga_set_gai_err( status );
                return NULL;
        }
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
        return sockfd;
}

int uga_sock_from_addr ( struct addrinfo * addr )
{
        int sockfd = socket( addr->ai_family, addr->ai_socktype, addr->ai_protocol );

        if( sockfd == -1 )
        {
                uga_set_stdlib_err();
        }
        return sockfd;
}

int uga_bind ( int sockfd, uga_config const * config )
{
        int err;
        struct sockaddr_in local_addr;

        local_addr.sin_family      = config->family;
        local_addr.sin_port        = htons( atoi( config->port ) );
        local_addr.sin_addr.s_addr = INADDR_ANY;

        err = bind( sockfd, ( struct sockaddr * ) &local_addr, sizeof( local_addr ) );
        if( err != 0 )
        {
                uga_set_stdlib_err();
                return -1;
        }
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
        return 0;
}

int uga_accept_connection ( int sockfd, uga_config const * config, void( *handle_connection )() )
{

}

int uga_tcp_connect ( char const * remote_host, char const * remote_port )
{
        int sockfd;
        int    err;

        struct sockaddr_in remote_addr;
        struct addrinfo hints, *res;

        memset( &hints, 0, sizeof( hints ) );

        hints.ai_family =      AF_INET ;
        hints.ai_flags |= AI_CANONNAME ;

        if( ( err = getaddrinfo( remote_host, NULL, &hints, &res ) ) )
        {
                uga_set_gai_err( err );
                return -1;
        }
        if( ( sockfd = socket( AF_INET, SOCK_STREAM, 0 ) ) == -1 )
        {
                uga_set_stdlib_err();
                return -1;
        }

        remote_addr.sin_family = AF_INET;
        remote_addr.sin_port   = htons( atoi( remote_port ) );
        remote_addr.sin_addr   = ( ( struct sockaddr_in * ) res->ai_addr )->sin_addr;

        memset( remote_addr.sin_zero, '\0', sizeof( remote_addr.sin_zero ) );

        if( connect( sockfd, ( struct sockaddr * ) &remote_addr, sizeof( remote_addr ) ) == -1 )
        {
                uga_set_stdlib_err();
                return -1;
        }
        return sockfd;
}

int uga_start_listen ( char const * local_port, uga_config const config, void ( *handle_request )( char const * request_data ) )
{
        ( void ) config ;
        ( void ) handle_request ;

        int fd;

        struct sockaddr_in local_addr;

        if( ( fd = socket( AF_INET, SOCK_STREAM, 0 ) ) == -1 )
        {
                uga_set_stdlib_err();
                return -1;
        }
        local_addr.sin_family = AF_INET;
        local_addr.sin_port   = htons( atoi( local_port ) );
        local_addr.sin_addr.s_addr = INADDR_ANY;

        memset( local_addr.sin_zero, '\0', sizeof( local_addr.sin_zero ) );

        if( bind( fd, ( struct sockaddr * ) &local_addr, sizeof( local_addr ) ) == -1 )
        {
                uga_set_stdlib_err();
                return -1;
        }
        if( listen( fd, UGA_BACKLOG ) == -1 )
        {
                uga_set_stdlib_err();
                return -1;
        }
        return fd;
}
