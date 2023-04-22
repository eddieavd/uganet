//
//
//      uganet
//      uga_err.c
//

#include <uga_err.h>

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
