#ifndef STL_ARRAY_IMPL_H
#define STL_ARRAY_IMPL_H

#include "stl_core.h"
#include <assert.h>

#define stl_implement_array_for(...) call_macro_x_for_each(stl_implement_array, __VA_ARGS__)

#define stl_implement_array(type)                                                                                                                              \
    void __stl_fn(type, array, create)(__stl_t(type, array) * arr, size_t lenght)                                                                              \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        arr->lenght = lenght;                                                                                                                                  \
        __stl_fn(type, __base_name, create)(&(arr->buffer), lenght);                                                                                           \
    }                                                                                                                                                          \
    void __stl_fn(type, array, desloc)(__stl_t(type, array) * arr, size_t from, int steps)                                                                     \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        __stl_fn(type, __base_name, desloc)(arr->buffer, arr->lenght, from, steps);                                                                            \
    }                                                                                                                                                          \
    void __stl_fn(type, array, insert)(__stl_t(type, array) * arr, type value, size_t index)                                                                   \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        __stl_fn(type, __base_name, insert)(arr->buffer, value, index, arr->lenght);                                                                           \
    }                                                                                                                                                          \
    void __stl_fn(type, array, set)(__stl_t(type, array) * arr, type value, size_t index)                                                                      \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        __stl_fn(type, __base_name, set)(arr->buffer, value, index);                                                                                           \
    }                                                                                                                                                          \
    void __stl_fn(type, array, remove)(__stl_t(type, array) * arr, size_t index)                                                                               \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        __stl_fn(type, __base_name, remove)(arr->buffer, index, arr->lenght);                                                                                  \
    }                                                                                                                                                          \
    type __stl_fn(type, array, get)(__stl_t(type, array) * arr, size_t index)                                                                                  \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        return __stl_fn(type, __base_name, get)(arr->buffer, index);                                                                                           \
    }                                                                                                                                                          \
    type __stl_fn(type, array, first)(__stl_t(type, array) * arr)                                                                                              \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        return __stl_fn(type, __base_name, first)(arr->buffer);                                                                                                \
    }                                                                                                                                                          \
    type __stl_fn(type, array, last)(__stl_t(type, array) * arr)                                                                                               \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        return __stl_fn(type, __base_name, last)(arr->buffer, arr->lenght);                                                                                    \
    }                                                                                                                                                          \
    void __stl_fn(type, array, copy)(__stl_t(type, array) * arr, type * *out, size_t start, size_t end)                                                        \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        __stl_fn(type, __base_name, copy)(arr->buffer, out, start, end);                                                                                       \
    }                                                                                                                                                          \
    void __stl_fn(type, array, clone)(__stl_t(type, array) * arr, type * *out)                                                                                 \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        __stl_fn(type, __base_name, clone)(arr->buffer, out, arr->lenght);                                                                                     \
    }                                                                                                                                                          \
    bool __stl_fn(type, array, equal)(__stl_t(type, array) * a, __stl_t(type, array) * b)                                                                      \
    {                                                                                                                                                          \
        assert(a != NULL);                                                                                                                                     \
        assert(b != NULL);                                                                                                                                     \
        __stl_fn(type, __base_name, equal)(a->buffer, b->buffer, a->lenght);                                                                                   \
    }                                                                                                                                                          \
    void __stl_fn(type, array, fill)(__stl_t(type, array) * arr, type value)                                                                                   \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        __stl_fn(type, __base_name, fill)(arr->buffer, value, arr->lenght);                                                                                    \
    }                                                                                                                                                          \
    int __stl_fn(type, array, find)(__stl_t(type, array) * arr, type value)                                                                                    \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        return __stl_fn(type, __base_name, find)(arr->buffer, value, arr->lenght);                                                                             \
    }                                                                                                                                                          \
    int __stl_fn(type, array, find_cmp)(__stl_t(type, array) * arr, type value, bool (*cmp)(type a, type b))                                                   \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        return __stl_fn(type, __base_name, find_cmp)(arr->buffer, value, arr->lenght, cmp);                                                                    \
    }                                                                                                                                                          \
    void __stl_fn(type, array, resize)(__stl_t(type, array) * arr, size_t lenght)                                                                              \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        __stl_fn(type, __base_name, resize)(&(arr->buffer), lenght);                                                                                           \
        arr->lenght = lenght;                                                                                                                                  \
    }                                                                                                                                                          \
    size_t __stl_fn(type, array, count)(__stl_t(type, array) * arr, type value)                                                                                \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        return __stl_fn(type, __base_name, count)(arr->buffer, value, arr->lenght);                                                                            \
    }                                                                                                                                                          \
    size_t __stl_fn(type, array, count_cmp)(__stl_t(type, array) * arr, type value, bool (*cmp)(type a, type b))                                               \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        return __stl_fn(type, __base_name, count_cmp)(arr->buffer, value, arr->lenght, cmp);                                                                   \
    }                                                                                                                                                          \
    bool __stl_fn(type, array, all)(__stl_t(type, array) * arr, type value)                                                                                    \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        return __stl_fn(type, __base_name, all)(arr->buffer, value, arr->lenght);                                                                              \
    }                                                                                                                                                          \
    bool __stl_fn(type, array, any)(__stl_t(type, array) * arr, type value)                                                                                    \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        return __stl_fn(type, __base_name, any)(arr->buffer, value, arr->lenght);                                                                              \
    }                                                                                                                                                          \
    bool __stl_fn(type, array, all_cmp)(__stl_t(type, array) * arr, type value, bool (*cmp)(type a, type b))                                                   \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        return __stl_fn(type, __base_name, all_cmp)(arr->buffer, value, arr->lenght, cmp);                                                                     \
    }                                                                                                                                                          \
    bool __stl_fn(type, array, any_cmp)(__stl_t(type, array) * arr, type value, bool (*cmp)(type a, type b))                                                   \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        return __stl_fn(type, __base_name, any_cmp)(arr->buffer, value, arr->lenght, cmp);                                                                     \
    }                                                                                                                                                          \
    void __stl_fn(type, array, join)(__stl_t(type, array) * a, __stl_t(type, array) * b)                                                                       \
    {                                                                                                                                                          \
        assert(a != NULL);                                                                                                                                     \
        assert(b != NULL);                                                                                                                                     \
        __stl_fn(type, __base_name, join)(&(a->buffer), b->buffer, a->lenght, b->lenght);                                                                      \
    }                                                                                                                                                          \
    void __stl_fn(type, array, reverse)(__stl_t(type, array) * arr)                                                                                            \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        __stl_fn(type, __base_name, reverse)(arr->buffer, arr->lenght);                                                                                        \
    }                                                                                                                                                          \
    void __stl_fn(type, array, free)(__stl_t(type, array) * arr)                                                                                               \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        assert(arr->buffer != NULL);                                                                                                                           \
        cstl_free(arr->buffer);                                                                                                                                \
        arr->lenght = 0;                                                                                                                                       \
        arr->buffer = 0;                                                                                                                                       \
    }                                                                                                                                                          \
    size_t __stl_fn(type, array, lenght)(__stl_t(type, array) * arr)                                                                                           \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        return arr->lenght;                                                                                                                                    \
    }                                                                                                                                                          \
    void __stl_fn(type, array, map)(__stl_t(type, array) * arr, type * *out, type(*map_fn)(type value, size_t index))                                          \
    {                                                                                                                                                          \
        __stl_fn(type, __base_name, map)(arr->buffer, out, arr->lenght, map_fn);                                                                               \
    }                                                                                                                                                          \
    void __stl_fn(type, array, filter)(__stl_t(type, array) * arr, type * *out, bool (*filter_fn)(type value, size_t index, type * filtered), size_t *out_len) \
    {                                                                                                                                                          \
        __stl_fn(type, __base_name, filter)(arr->buffer, out, arr->lenght, filter_fn, out_len);                                                                \
    }

#endif