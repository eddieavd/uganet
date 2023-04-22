//
//
//      uganet
//      main.c
//

#include <stdio.h>
#include <stdlib.h>

#include <uganet.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>



int main ( int argc, char ** argv )
{
        ( void ) argc ;
        ( void ) argv ;

        uga_config config = { AF_INET, UGA_UDP } ;

        struct addrinfo * addr = uga_addrinfo( NULL, "8080", config );

        if( uga_had_errs() )
        {
                printf( "err: %s\n", uga_strerror() );
                return 1;
        }
        int sockfd = uga_sock_from_addr( addr );

        if( uga_had_errs() )
        {
                printf( "err: %s\n", uga_strerror() );
                return 1;
        }
        uga_bind( sockfd, "8080" );

        if( uga_had_errs() )
        {
                printf( "err: %s\n", uga_strerror() );
                return 1;
        }


        freeaddrinfo( addr );


        return 0;
}
