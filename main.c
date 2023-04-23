//
//
//      uganet
//      main.c
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

#include <uganet.h>


int accept_connection ( int const clientfd )
{
        printf( "handler: got connection from clientfd %d\n", clientfd );

        int bytes = 0;
        char * data = uga_recv( clientfd, &bytes );

        if( bytes > 0 )
        {
                printf( "handler: received data: %s\n", data );
        }
        free( data );

        uga_close_sock( clientfd );
        if( uga_had_errs() )
        {
                printf( "handler: failed closing client socket with error: %s\n", uga_strerror() );
                return -1;
        }
        return 0;
}

int main ( int argc, char ** argv )
{
        ( void ) argc ;
        ( void ) argv ;

        int server_pid = fork();
        if( server_pid == 0 )
        {
                printf( "server starting...\n" );

                printf( "server calling listen_on_port...\n" );

                uga_config config = { AF_INET, UGA_TCP, "8080" };

                int sockfd = uga_listen_on_port( &config );

                if( uga_had_errs() )
                {
                        printf( "server::err: listen on port failed with error: %s\n", uga_strerror() );
                        return -1;
                }
                printf( "server: listen on port successful!\n" );

//                for( int i = 0; i < 10; ++i )
                {
                        printf( "server: calling accept_and_handle...\n" );
                        uga_accept_and_handle( sockfd, accept_connection );
                        if( uga_had_errs() )
                        {
                                printf( "server::err: accept and handle failed with error: %s\n", uga_strerror() );
                                return -1;
                        }
                        printf( "server: accept and handle successful!\n" );
                }
                printf( "server: closing socket...\n" );
                uga_close_sock( sockfd );
                if( uga_had_errs() )
                {
                        printf( "server::err: failed closing socket with error: %s\n", uga_strerror() );
                        return -1;
                }
                printf( "server: quitting...\n" );
                return 0;
        }
        int client_pid = fork();
        if( client_pid == 0 )
        {
                printf( "client starting...\n" );

                sleep( 2 );

                uga_config config = { AF_INET, UGA_TCP, "8080" };

//                for( int i = 0; i < 10; ++i )
                {
                        sleep( 1 );

                        printf( "client: calling connect_to_remote...\n" );
                        int sockfd = uga_connect_to_remote( "localhost", &config );
                        if( uga_had_errs() )
                        {
                                printf( "client::err: connect to remote failed with error: %s\n", uga_strerror() );
                                return -1;
                        }
                        printf( "client: connect to remote successful!\n" );
                        printf( "client: sending message...\n" );
                        int sent = uga_send( sockfd, "hello\n", 6 );
                        if( uga_had_errs() )
                        {
                                printf( "client::err: send failed with error: %s\n", uga_strerror() );
                                return -1;
                        }
                        printf( "client: send successful!\n" );
                        printf( "client: closing connection...\n" );
                        uga_close_sock( sockfd );
                }
                return 0;
        }

        waitpid( server_pid, NULL, 0 );
        waitpid( client_pid, NULL, 0 );




        return 0;
}
