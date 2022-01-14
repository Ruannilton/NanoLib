#ifndef STL_VALIDATIONS_H
#define STL_VALIDATIONS_H
#include <stdlib.h>

enum STL_RET_CODES
{
    STL_OK = 0,
    STL_OUT_BOUNDS = -1,
    STL_NULL_POINTER = -2,
    STL_NULL_VALUE = -3
};

typedef enum STL_RET_CODES stl_return_code_e;

#ifdef STL_VALIDATION_ON

#ifndef __FUNCTION_NAME__
#ifdef __GNUC__
#define __FUNCTION_NAME__ __func__
#else
#define __FUNCTION_NAME__ __FUNCTION__
#endif
#endif

void cstl_set_vallidation_callback(void (*callback)(stl_return_code_e code, unsigned int line, const char *function_name));
void cstl_vallidation(stl_return_code_e code, unsigned int line, const char *function_name);

#define STL_VAL_BOUNDS(val, min, max)                                      \
    {                                                                      \
        if ((val) < (min) || (val) > (max))                                \
        {                                                                  \
            cstl_vallidation(STL_OUT_BOUNDS, __LINE__, __FUNCTION_NAME__); \
        }                                                                  \
    }

#define STL_VAL_NOT_NULL(pointer)                                            \
    {                                                                        \
        if ((pointer) == NULL)                                               \
        {                                                                    \
            cstl_vallidation(STL_NULL_POINTER, __LINE__, __FUNCTION_NAME__); \
        }                                                                    \
    }

#define STL_VAL_NOT_ZERO(value)                                            \
    {                                                                      \
        if ((value) == 0)                                                  \
        {                                                                  \
            cstl_vallidation(STL_NULL_VALUE, __LINE__, __FUNCTION_NAME__); \
        }                                                                  \
    }
#else

#define STL_VAL_BOUNDS(val, min, max)

#define STL_VAL_NOT_NULL(pointer)

#define STL_VAL_NOT_ZERO(value)

#endif

#endif