//
//
//      uganet
//      uga_write.h
//

#ifndef UGANET_WRITE_H_
#define UGANET_WRITE_H_

#include <stdint.h>


void uga_write  ( char const * filename, char const * contents, int64_t const content_len ) ;
void uga_append ( char const * filename, char const * contents, int64_t const content_len ) ;


#endif // UGANET_WRITE_H_
