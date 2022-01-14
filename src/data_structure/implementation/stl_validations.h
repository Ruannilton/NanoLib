#ifndef STL_IMPLEMENT_VALIDATIONS_H
#define STL_IMPLEMENT_VALIDATIONS_H

#include "../internal/stl_validations.h"

void (*__i_cstl_vallidation_callback)(stl_return_code_e code, unsigned int line, const char *function_name) = NULL;

void cstl_set_vallidation_callback(void (*callback)(stl_return_code_e code, unsigned int line, const char *function_name))
{
    __i_cstl_vallidation_callback = callback;
}

void cstl_vallidation(stl_return_code_e code, unsigned int line, const char *function_name)
{
    if (__i_cstl_vallidation_callback != NULL)
    {
        __i_cstl_vallidation_callback(code, line, function_name);
    }
}

#endif