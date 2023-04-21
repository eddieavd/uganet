//
//
//      uganet
//      uga_net.h
//

#ifndef UGANET_NET_H_
#define UGANET_NET_H_


typedef enum
{
        UDP,
        TCP
} uga_protocol ;

int uga_connect      ( char const * remote_host, char const * remote_port                          ) ;
int uga_connect_from ( char const * remote_host, char const * remote_port, char const * local_port ) ;

int uga_listen ( char const * local_port, uga_protocol const protocol, void ( *handle_request )( char const * request_data ) ) ;

char const * uga_hear_say ( char const * remote_host, char const * remote_port, char const * content, char const * content_len ) ;
char const * uga_say_hear ( char const * remote_host, char const * remote_port, char const * content, char const * content_len ) ;


#endif // UGANET_NET_H_
