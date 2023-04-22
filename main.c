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

        uga_config config = { AF_INET, UGA_UDP, "8080" } ;

        struct addrinfo * addr = uga_addrinfo( NULL, &config );
        uga_handle_err_and_exit( 1 );

        int sockfd = uga_sock_from_addr( addr );
        uga_handle_err_and_exit( 1 );

        uga_bind( sockfd, &config );
        uga_handle_err_and_exit( 1 );


        freeaddrinfo( addr );


        return 0;
}
