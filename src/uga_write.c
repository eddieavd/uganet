//
//
//      uganet
//      uga_write.c
//

#include <uga_err.h>
#include <uga_fs.h>
#include <uga_write.h>


#pragma GCC diagnostic ignored "-Wunused-parameter"


void _uga_fwrite ( FILE * fptr, char const * contents, int64_t const content_len ) ;

void uga_write ( char const * filename, char const * contents, int64_t const content_len )
{
        FILE * file = uga_open_file( filename, "w+" );

        if( uga_had_errs() ) return;

        _uga_fwrite( file, contents, content_len );

        uga_close_file( file );
}

void uga_append ( char const * filename, char const * contents, int64_t const content_len )
{
        FILE * file = uga_open_file( filename, "a+" );

        if( uga_had_errs() ) return;

        _uga_fwrite( file, contents, content_len );

        uga_close_file( file );
}

void _uga_fwrite ( FILE * fptr, char const * contents, int64_t const content_len )
{
        int64_t wrote = fwrite( contents, sizeof( char ), content_len, fptr );

        if( wrote == -1 || wrote != content_len ) uga_set_stdlib_err();
}
