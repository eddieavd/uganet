//
//
//      uganet
//      uga_fs.h
//

#ifndef UGANET_FS_H_
#define UGANET_FS_H_

#include <stdio.h>
#include <stdint.h>


FILE * uga_open_file  ( char const * filename, char const * mode ) ;
void   uga_close_file ( FILE       * file                        ) ;

int64_t uga_get_filesize ( char const * filename ) ;


#endif // UGANET_FS_H_
