//
//
//      uganet client
//      client.c
//

#include <uganet.h>


int main ( int argc, char ** argv )
{
        if( argc < 3 )
        {
                printf( "usage: %s <filename> <server_port>\n", argv[ 0 ] );
                return 1;
        }

        char const * fnam = argv[ 1 ];
        char const * port = argv[ 2 ];

        uga_config config = { AF_INET, UGA_TCP, port };

        printf( "client: connecting to server...\n" );

        int sockfd = uga_connect_to_remote( "localhost", &config );
        if( uga_had_errs() )
        {
                printf( "client::err: connect_to_remote failed with error: %s\n", uga_strerror() );
                return 1;
        }
        printf( "client: connected to server!\n" );
        printf( "client: sending request...\n" );

        int sent = uga_send( sockfd, fnam, strlen( fnam ) );
        if( uga_had_errs() )
        {
                printf( "client::err: send failed with error: %s\n", uga_strerror() );
                return 1;
        }
//        uga_send( sockfd, "\n", 1 );
        uga_shutdown( sockfd, UGA_NO_SEND );
        if( uga_had_errs() )
        {
                printf( "client::err: shutdown failed with error: %s\n", uga_strerror() );
                return 1;
        }
        printf( "client: request sent!\nclient: waiting for data...\n" );

        int content_len = 0;
        char * contents = uga_recv_all( sockfd, &content_len );
        if( uga_had_errs() )
        {
                printf( "client::err: recv failed with error: %s\n", uga_strerror() );
                return 1;
        }
        printf( "client: received %d bytes!\nclient: writing to file...\n", content_len );

        uga_write( "newfile.txt", contents, content_len );
        if( uga_had_errs() )
        {
                printf( "client::err: write failed with error: %s\n", uga_strerror() );
                free( contents );
                return 1;
        }
        free( contents );
        uga_close_sock( sockfd );
        if( uga_had_errs() )
        {
                printf( "client::err: socket close failed with error: %s\n", uga_strerror() );
                return 1;
        }

        printf( "client: data written!\nclient: exiting...\n" );



        return 0;
}
