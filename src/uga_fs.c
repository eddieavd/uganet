//
//
//      uganet
//      uga_fs.c
//

#include <sys/stat.h>

#include <uga_fs.h>


FILE * open_file ( char const * filename, char const * mode )
{
        FILE * fptr = fopen( filename, mode );

        if( fptr == NULL )
        {
                uga_set_stdlib_err();
                return NULL;
        }
        return fptr;
}

void close_file ( FILE * file )
{
        if( fclose( file ) != 0 )
        {
                uga_set_stdlib_err();
        }
}

int64_t get_filesize ( char const * filename )
{
        struct stat st;
        stat( filename, &st );
        printf( "stat.st_size: %ld\n", st.st_size );
        return st.st_size;
}
