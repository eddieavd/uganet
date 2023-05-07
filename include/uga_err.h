//
//
//      uganet
//      uga_err.h
//

#ifndef UGANET_ERR_H_
#define UGANET_ERR_H_


typedef enum
{
        UGA_ERR_NONE   ,
        UGA_ERR_STDLIB ,
        UGA_ERR_GAIERR ,
        UGA_ERR_BAD_ARG,
        UGA_ERR_EOF    ,
        UGA_ERR_UNKNOWN
} err_type ;


#pragma GCC diagnostic ignored "-Wunused-variable"


static err_type uga_errno  = UGA_ERR_NONE ;
static int      uga_stderr =            0 ;
static int      uga_gaierr =            0 ;


char const * uga_strerror () ;

void uga_set_stdlib_err (             ) ;
void uga_set_gai_err    ( int gai_err ) ;

int  uga_had_errs () ;
void uga_clr_errs () ;

void uga_print_err          (                  ) ;
void uga_print_err_and_exit ( int const status ) ;

void uga_print_err_str          ( char const * msg                   ) ;
void uga_print_err_str_and_exit ( char const * msg, int const status ) ;

void uga_handle_err          (                   void ( *err_handler )( int const uga_err ) ) ;
void uga_handle_err_and_exit ( int const status, void ( *err_handler )( int const uga_err ) ) ;


#endif // UGANET_ERR_H_
