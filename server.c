//
//
//      uganet server
//      server.c
//

#include <uganet.h>


int handle_connection ( int clientfd ) ;

int main ( int argc, char ** argv )
{
        if( argc < 2 )
        {
                printf( "usage: %s <port>\n", argv[ 0 ] );
                return 1;
        }

        uga_config config = { AF_INET, UGA_TCP, argv[ 1 ] };

        printf( "server: starting listen on port %s\n", config.port );

        int sockfd = uga_listen_on_port( &config );

        printf( "server: waiting for connections...\n" );

        int err = uga_accept_and_handle( sockfd, handle_connection );
        if( uga_had_errs() )
        {
                printf( "server::err: accept and handle failed with error: %s\n", uga_strerror() );
                return 1;
        }
        printf( "server: connection handled! finishing...\n" );

        uga_close_sock( sockfd );


        return 0;
}

int handle_connection ( int clientfd )
{
        printf( "server::handler: receiving request...\n" );
        int req_len = 0;
        char * request = uga_recv_all( clientfd, &req_len );

        if( uga_had_errs() )
        {
                printf( "server::handler::err: recv failed with error: %s\n", uga_strerror() );
                return -1;
        }
        if( req_len == 0 )
        {
                printf( "server::handler: client closed connection!\n" );
                free( request );
                return 0;
        }
        printf( "server::handler: reading file %s\n", request );
        char * contents = uga_read_file( request );
        if( uga_had_errs() )
        {
                printf( "server::handler::err: read failed with error: %s\n", uga_strerror() );
                free( request );
                return -1;
        }
        printf( "server::handler: sending file...\n" );
        uga_send( clientfd, contents, strlen( contents ) );
        if( uga_had_errs() )
        {
                printf( "server::handler::err: send failed with error: %s\n", uga_strerror() );
                free( request );
                free( contents );
                return -1;
        }
        printf( "server::handler: data sent! closing connection...\n" );
        free( request );
        free( contents );
        uga_close_sock( clientfd );
        return 0;
}
