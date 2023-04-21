//
//
//      uganet
//      uga_err.h
//

#ifndef UGANET_ERR_H_
#define UGANET_ERR_H_


typedef enum
{
        UGA_ERR_NONE  ,
        UGA_ERR_STDLIB,
        UGA_ERR_GAIERR,
        UGA_ERR_UNKNOWN
} err_type ;


#pragma GCC diagnostic ignored "-Wunused-variable"


static err_type uga_errno  = UGA_ERR_NONE ;
static int      uga_stderr =            0 ;
static int      uga_gaierr =            0 ;


char const * uga_strerror () ;

void uga_set_stdlib_err (             ) ;
void uga_set_gai_err    ( int gai_err ) ;

int uga_had_errs () ;


#endif // UGANET_ERR_H_
