//
//
//      uganet
//      uga_fs.h
//

#ifndef UGANET_FS_H_
#define UGANET_FS_H_

#include <stdio.h>
#include <stdint.h>

#include <uga_err.h>


FILE *  open_file ( char const * filename, char const * mode ) ;
void   close_file ( FILE       * file                        ) ;

int64_t get_filesize ( char const * filename ) ;


#endif // UGANET_FS_H_
