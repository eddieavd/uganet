//
//
//      uganet
//      uga_write.h
//

#ifndef UGANET_WRITE_H_
#define UGANET_WRITE_H_

#include <stdint.h>


void uga_write_f   ( char const * filename, char const * contents, int64_t const content_len ) ;
void uga_write_s   ( int  const     sockid, char const * contents, int64_t const content_len ) ;
void uga_write_all ( int  const     sockid, char const * contents, int64_t const content_len ) ;

void uga_append ( char const * filename, char const * contents, int64_t const content_len ) ;

void uga_send     ( char const * remote_host, char const * remote_port, char const * contents, int64_t const content_len ) ;
void uga_send_all ( char const * remote_host, char const * remote_port, char const * contents, int64_t const content_len ) ;


#define uga_write( dest, contents, content_len ) _Generic( dest, char const *: uga_write_f, int const: uga_write_s )( dest, contents, content_len )


#endif // UGANET_WRITE_H_
