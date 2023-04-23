//
//
//      uganet
//      uga_read.h
//

#ifndef UGANET_READ_H_
#define UGANET_READ_H_

#include <stdint.h>


char * uga_read_f     ( char const * filename, int64_t const max_bytes ) ;
char * uga_read_s     ( int  const     sockid, int64_t const max_bytes ) ;
char * uga_read_all_f ( char const * filename                          ) ;
char * uga_read_all_s ( int  const     sockid                          ) ;


#define uga_read    ( src, max_bytes ) _Generic( src, char const *: uga_read_f    , int const: uga_read_s     )( src, max_bytes )
#define uga_read_all( src            ) _Generic( src, char const *: uga_read_all_f, int const: uga_read_all_s )( src            )


#endif // UGANET_READ_H_
