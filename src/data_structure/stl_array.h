#ifndef STL_ARRAY_H
#define STL_ARRAY_H
#include "stl_core.h"

#define array(type) __stl_t(type, array)
#define ARRAY_INITIAL_LEN 4
#define stl_declare_array(type)                                                                           \
    typedef struct                                                                                        \
    {                                                                                                     \
        type *buffer;                                                                                     \
        size_t lenght;                                                                                    \
    } __stl_t(type, array);                                                                               \
    stl_declare(type);                                                                                    \
                                                                                                          \
    void __stl_fn(type, array, create)(array(type) * arr, size_t lenght);                                 \
    void __stl_fn(type, array, desloc)(array(type) * arr, size_t from, int steps);                        \
    void __stl_fn(type, array, insert)(array(type) * arr, type value, size_t index);                      \
    void __stl_fn(type, array, set)(array(type) * arr, type value, size_t index);                         \
    void __stl_fn(type, array, remove)(array(type) * arr, size_t index);                                  \
    type __stl_fn(type, array, get)(array(type) * arr, size_t index);                                     \
    type __stl_fn(type, array, first)(array(type) * arr);                                                 \
    void __stl_fn(type, array, copy)(array(type) * arr, type * *out, size_t start, size_t end);           \
    void __stl_fn(type, array, clone)(array(type) * arr, type * *out);                                    \
    bool __stl_fn(type, array, equal)(array(type) * a, array(type) * b);                                  \
    void __stl_fn(type, array, fill)(array(type) * arr, type value);                                      \
    int __stl_fn(type, array, find)(array(type) * arr, type value);                                       \
    int __stl_fn(type, array, find_cmp)(array(type) * arr, type value, bool (*cmp)(type a, type b));      \
    void __stl_fn(type, array, resize)(array(type) * arr, size_t lenght);                                 \
    size_t __stl_fn(type, array, count)(array(type) * arr, type value);                                   \
    size_t __stl_fn(type, array, count_cmp)(array(type) * arr, type value, bool (*cmp)(type a, type b));  \
    bool __stl_fn(type, array, all)(array(type) * arr, type value);                                       \
    bool __stl_fn(type, array, all_cmp)(array(type) * arr, type value, bool (*cmp)(type a, type b));      \
    void __stl_fn(type, array, join)(array(type) * a, array(type) * b, size_t lenght_a, size_t lenght_b); \
    void __stl_fn(type, array, reverse)(array(type) * arr);

#define stl_implement_array(type)                                                                        \
    stl_declare_array(type);                                                                             \
    void __stl_fn(type, array, create)(array(type) * arr, size_t lenght)                                 \
    {                                                                                                    \
        arr->lenght = lenght;                                                                            \
        __stl_fn(type, __base_name, create)(&(arr->buffer), lenght);                                     \
    }                                                                                                    \
    void __stl_fn(type, array, desloc)(array(type) * arr, size_t from, int steps)                        \
    {                                                                                                    \
        __stl_fn(type, __base_name, desloc)(arr->buffer, arr->lenght, from, steps);                      \
    }                                                                                                    \
    void __stl_fn(type, array, insert)(array(type) * arr, type value, size_t index)                      \
    {                                                                                                    \
        __stl_fn(type, __base_name, insert)(arr->buffer, value, index, arr->lenght);                     \
    }                                                                                                    \
    void __stl_fn(type, array, set)(array(type) * arr, type value, size_t index)                         \
    {                                                                                                    \
        __stl_fn(type, __base_name, set)(arr->buffer, value, index);                                     \
    }                                                                                                    \
    void __stl_fn(type, array, remove)(array(type) * arr, size_t index)                                  \
    {                                                                                                    \
        __stl_fn(type, __base_name, remove)(arr->buffer, index, arr->lenght);                            \
    }                                                                                                    \
    type __stl_fn(type, array, get)(array(type) * arr, size_t index)                                     \
    {                                                                                                    \
        return __stl_fn(type, __base_name, get)(arr->buffer, index);                                     \
    }                                                                                                    \
    type __stl_fn(type, array, first)(array(type) * arr)                                                 \
    {                                                                                                    \
        return __stl_fn(type, __base_name, first)(arr->buffer);                                          \
    }                                                                                                    \
    void __stl_fn(type, array, copy)(array(type) * arr, type * *out, size_t start, size_t end)           \
    {                                                                                                    \
        __stl_fn(type, __base_name, copy)(arr->buffer, &(arr->buffer), start, end);                      \
    }                                                                                                    \
    void __stl_fn(type, array, clone)(array(type) * arr, type * *out)                                    \
    {                                                                                                    \
        __stl_fn(type, __base_name, clone)(arr->buffer, &(arr->buffer), arr->lenght);                    \
    }                                                                                                    \
    bool __stl_fn(type, array, equal)(array(type) * a, array(type) * b)                                  \
    {                                                                                                    \
        __stl_fn(type, __base_name, equal)(a->buffer, b->buffer, a->lenght);                             \
    }                                                                                                    \
    void __stl_fn(type, array, fill)(array(type) * arr, type value)                                      \
    {                                                                                                    \
        __stl_fn(type, __base_name, fill)(arr->buffer, value, arr->lenght);                              \
    }                                                                                                    \
    int __stl_fn(type, array, find)(array(type) * arr, type value)                                       \
    {                                                                                                    \
        return __stl_fn(type, __base_name, find)(arr->buffer, value, arr->lenght);                       \
    }                                                                                                    \
    int __stl_fn(type, array, find_cmp)(array(type) * arr, type value, bool (*cmp)(type a, type b))      \
    {                                                                                                    \
        return __stl_fn(type, __base_name, find_cmp)(arr->buffer, value, arr->lenght, cmp);              \
    }                                                                                                    \
    void __stl_fn(type, array, resize)(array(type) * arr, size_t lenght)                                 \
    {                                                                                                    \
        __stl_fn(type, __base_name, resize)(&(arr->buffer), lenght);                                     \
        arr->lenght = lenght;                                                                            \
    }                                                                                                    \
    size_t __stl_fn(type, array, count)(array(type) * arr, type value)                                   \
    {                                                                                                    \
        return __stl_fn(type, __base_name, count)(arr->buffer, value, arr->lenght);                      \
    }                                                                                                    \
    size_t __stl_fn(type, array, count_cmp)(array(type) * arr, type value, bool (*cmp)(type a, type b))  \
    {                                                                                                    \
        return __stl_fn(type, __base_name, count_cmp)(arr->buffer, value, arr->lenght, cmp);             \
    }                                                                                                    \
    bool __stl_fn(type, array, all)(array(type) * arr, type value)                                       \
    {                                                                                                    \
        return __stl_fn(type, __base_name, all)(arr->buffer, value, arr->lenght);                        \
    }                                                                                                    \
    bool __stl_fn(type, array, all_cmp)(array(type) * arr, type value, bool (*cmp)(type a, type b))      \
    {                                                                                                    \
        return __stl_fn(type, __base_name, all_cmp)(arr->buffer, value, arr->lenght, cmp);               \
    }                                                                                                    \
    void __stl_fn(type, array, join)(array(type) * a, array(type) * b, size_t lenght_a, size_t lenght_b) \
    {                                                                                                    \
        __stl_fn(type, __base_name, join)(&(a->buffer), b->buffer, a->lenght, b->lenght);                \
    }                                                                                                    \
    void __stl_fn(type, array, reverse)(array(type) * arr)                                               \
    {                                                                                                    \
        __stl_fn(type, __base_name, reverse)(arr->buffer, arr->lenght);                                  \
    }
#endif