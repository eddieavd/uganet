//
//
//      uganet
//      uga_read.c
//

#include <stdlib.h>

#include <uga_err.h>
#include <uga_fs.h>
#include <uga_read.h>


char * uga_read_f ( char const * filename, int64_t const max_bytes )
{
        FILE * file = uga_open_file( filename, "r" );

        if( uga_had_errs() ) return NULL;

        int64_t fsize = uga_get_filesize( filename );

        int64_t to_read = fsize < max_bytes ? fsize : max_bytes ;
        char *  buffer  = ( char * ) malloc( sizeof( char ) * ( to_read + 1 ) );

        if( !buffer )
        {
                uga_set_stdlib_err();
                return NULL;
        }
        int64_t read_b = fread( buffer, sizeof( char ), to_read, file );

        if( read_b != to_read )
        {
                uga_set_stdlib_err();
                free( buffer );
                return NULL;
        }
        uga_close_file( file );
        buffer[ to_read ] = '\0';

        return buffer;
}

char * uga_read_all_f ( char const * filename )
{
        int64_t fsize = uga_get_filesize( filename );

        return uga_read_f( filename, fsize );
}

char * uga_read_s ( int const sockid, int64_t const max_bytes )
{
        ( void )    sockid ;
        ( void ) max_bytes ;

        return NULL;
}

char * uga_read_all_s ( int const sockid )
{
        return uga_read_s( sockid, 0 );
}

char * uga_recv ( char const * remote_host, char const * remote_port )
{
        ( void ) remote_host ;
        ( void ) remote_port ;

        return NULL;
}

char * uga_recv_all ( char const * remote_host, char const * remote_port )
{
        ( void ) remote_host ;
        ( void ) remote_port ;

        return NULL;
}
