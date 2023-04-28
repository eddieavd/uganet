//
//
//      uganet
//      uga_read.h
//

#ifndef UGANET_READ_H_
#define UGANET_READ_H_

#include <stdint.h>


char * uga_read_some ( char const * filename, int64_t const max_bytes ) ;
char * uga_read_file ( char const * filename                          ) ;


#endif // UGANET_READ_H_
