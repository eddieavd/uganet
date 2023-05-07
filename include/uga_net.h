//
//
//      uganet
//      uga_net.h
//

#ifndef UGANET_NET_H_
#define UGANET_NET_H_

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define UGA_RECV_BUFFLEN 4 * 1024


typedef enum
{
        UGA_UDP,
        UGA_TCP
} uga_protocol ;

typedef enum
{
        UGA_NO_RECV,
        UGA_NO_SEND,
        UGA_NONE
} shutdown_mode ;

typedef struct
{
        int          family   ;
        uga_protocol protocol ;
        char const * port     ;
} uga_config ;


typedef struct sockaddr         sockaddr_t         ;
typedef struct sockaddr_in      sockaddr_in_t      ;
typedef struct sockaddr_in6     sockaddr_in6_t     ;
typedef struct sockaddr_storage sockaddr_storage_t ;
typedef struct     addrinfo         addrinfo_t     ;


sockaddr_in_t   uga_ip_to_net ( char          const * remote_ip ) ;
char          * uga_net_to_ip ( sockaddr_in_t const *     saddr ) ;

addrinfo_t * uga_addrinfo ( char const * host, uga_config const * config ) ;

int uga_socket         ( uga_config const * config ) ;
int uga_sock_from_addr ( addrinfo_t const *   addr ) ;

int uga_shutdown   ( int const sockfd, shutdown_mode const mode ) ;
int uga_close_sock ( int const sockfd                           ) ;

int uga_bind ( int sockfd, uga_config const * config ) ;

int uga_get_bound_sock ( uga_config const * config ) ;

int uga_connect_to_remote ( char const * remote_host, uga_config const * config ) ;

int uga_listen_on_port ( uga_config const * config ) ;

int uga_accept_and_handle ( int sockfd, int( *handle_connection )( int const clientfd ) ) ;

int    uga_send      ( int const sockfd, char const *        data, int64_t const data_len ) ;
char * uga_recv      ( int const sockfd, int        * bytes_recvd                         ) ;
char * uga_recv_all  ( int const sockfd, int        * bytes_recvd                         ) ;
char * uga_recv_some ( int const sockfd, int        *   max_bytes                         ) ;

char * uga_hear_say ( char const * remote_host, char const * remote_port, char const * content, char const * content_len ) ;
char * uga_say_hear ( char const * remote_host, char const * remote_port, char const * content, char const * content_len ) ;

int uga_buga_send ( char const * remote_host, char const * remote_port, char const * content, char const * content_len ) ;


#endif // UGANET_NET_H_
