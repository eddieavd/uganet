//
//
//      uganet
//      uga_err.c
//

#include <uga_err.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <netdb.h>


char const * uga_strerror ()
{
        switch( uga_errno )
        {
                case UGA_ERR_NONE:
                        return "success";
                case UGA_ERR_STDLIB:
                        return strerror( uga_stderr );
                case UGA_ERR_GAIERR:
                        return gai_strerror( uga_gaierr );
                case UGA_ERR_BAD_ARG:
                        return "bad args";
                case UGA_ERR_EOF:
                        return "end of file";
                case UGA_ERR_UNKNOWN:
                        return "unknown error";
                default:
                        return "generic error";
        }
        uga_errno = UGA_ERR_NONE;
}

void uga_set_stdlib_err ()
{
        uga_stderr =          errno ;
        uga_errno  = UGA_ERR_STDLIB ;
}
void uga_set_gai_err ( int gai_err )
{
        uga_gaierr =        gai_err ;
        uga_errno  = UGA_ERR_GAIERR ;
}

int uga_had_errs ()
{
        return uga_errno != UGA_ERR_NONE;
}
void uga_clr_errs ()
{
        uga_stderr =            0 ;
        uga_gaierr =            0 ;
        uga_errno  = UGA_ERR_NONE ;
}

void uga_print_err ()
{
        if( uga_errno != UGA_ERR_NONE )
        {
                fprintf( stderr, "uga::err: %s\n", uga_strerror() );
        }
}
void uga_print_err_and_exit ( int const status )
{
        if( uga_errno != UGA_ERR_NONE )
        {
                fprintf( stderr, "uga::err: %s\n", uga_strerror() );
                exit( status );
        }
}

void uga_print_err_str ( char const * msg )
{
        if( uga_errno != UGA_ERR_NONE )
        {
                fprintf( stderr, "uga::err: %s : %s\n", msg, uga_strerror() );
        }
}

void uga_print_err_str_and_exit ( char const * msg, int const status )
{
        if( uga_errno != UGA_ERR_NONE )
        {
                fprintf( stderr, "uga::err: %s : %s\n", msg, uga_strerror() );
                exit( status );
        }
}

void uga_handle_err ( void ( *err_handler )( int const uga_err ) )
{
        if( uga_errno != UGA_ERR_NONE )
        {
                err_handler( uga_errno );
        }
}
void uga_handle_err_and_exit ( int const status, void ( *err_handler )( int const uga_err ) )
{
        if( uga_errno != UGA_ERR_NONE )
        {
                err_handler( uga_errno );
                exit( status );
        }
}
