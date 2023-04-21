//
//
//      uganet
//      main.c
//

#include <stdio.h>
#include <stdlib.h>

#include <uganet.h>


int main ()
{
        char const * filename = "test.txt";

        uga_write_f( filename, "halo_buraz", 10 );

        if( uga_had_errs() )
        {
                printf( "uga::err: %s\n", uga_strerror() );
                return 1;
        }

        char * content = uga_read_all_f( filename );

        if( content == NULL )
        {
                printf( "uga::err: %s\n", uga_strerror() );
                return 1;
        }

        printf( "%s\n", content );

        free( content );


        return 0;
}
