#ifndef __TRLS_BASE_H__
#define __TRLS_BASE_H__


#include <stdint.h>
#include <stddef.h>


#ifndef NULL
    #define NULL ((void *)0)
#endif


typedef intptr_t  trls_int_t;
typedef uintptr_t trls_uint_t;


//trls sys boolean value definition
enum trls_flag_enum
{
    TRLS_FALSE,
    TRLS_TRUE
};
typedef enum trls_flag_enum trls_flag_e;


//trls sys result value definition
enum trls_res_enum
{
    TRLS_OK,
    TRLS_FAILED,
    TRLS_ERROR
};
typedef enum trls_res_enum trls_res_e;


#endif
