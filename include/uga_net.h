//
//
//      uganet
//      uga_net.h
//

#ifndef UGANET_NET_H_
#define UGANET_NET_H_

#define UGA_BACKLOG 16


typedef enum
{
        UGA_UDP,
        UGA_TCP
} uga_protocol ;

typedef struct
{
        int          family   ;
        uga_protocol protocol ;
        char const * port     ;
} uga_config ;


struct sockaddr_in uga_ip_to_net ( char const * remote_ip ) ;
char * uga_net_to_ip ( struct sockaddr_in const * saddr ) ;
struct addrinfo * uga_addrinfo ( char const * host, uga_config const * config ) ;

int uga_socket ( uga_config const * config ) ;
int uga_sock_from_addr ( struct addrinfo * addr ) ;

int uga_bind ( int sockfd, uga_config const * config ) ;

int uga_get_bound_sock ( uga_config const * config ) ;

int uga_tcp_connect      ( char const * remote_host, char const * remote_port                          ) ;
int uga_tcp_connect_from ( char const * remote_host, char const * remote_port, char const * local_port ) ;

int uga_listen_on_port ( uga_config const * config ) ;
int uga_accept_connection ( int sockfd, uga_config const * config, void( *handle_connection )() ) ;

int uga_start_listen ( char const * local_port, uga_config const config, void ( *handle_request )( char const * request_data ) ) ;

int uga_listen ( int sockfd, void ( *handle_request )( char const * request_data ) ) ;

char const * uga_hear_say ( char const * remote_host, char const * remote_port, char const * content, char const * content_len ) ;
char const * uga_say_hear ( char const * remote_host, char const * remote_port, char const * content, char const * content_len ) ;


#endif // UGANET_NET_H_
