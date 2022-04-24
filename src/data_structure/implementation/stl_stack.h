#ifndef STL_STACK_IMPL_H
#define STL_STACK_IMPL_H

#include "../internal/stl_macros.h"
#include "../internal/slt_foreach_macro.h"
#include <assert.h>

#define stl_implement_stack_for(...) call_macro_x_for_each(stl_implement_stack, __VA_ARGS__)

#define stl_implement_stack(type)                                                                                                                              \
    void __stl_fn(type, stack, create)(__stl_t(type, stack) * arr, size_t lenght)                                                                              \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        arr->lenght = lenght;                                                                                                                                  \
        arr->count = 0;                                                                                                                                        \
        __stl_fn(type, __base_name, create)(&(arr->buffer), lenght);                                                                                           \
    }                                                                                                                                                          \
    void __stl_fn(type, stack, free)(__stl_t(type, stack) * arr)                                                                                               \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        assert(arr->buffer != NULL);                                                                                                                           \
        cstl_free(arr->buffer);                                                                                                                                \
        arr->lenght = 0;                                                                                                                                       \
        arr->buffer = 0;                                                                                                                                       \
        arr->count = 0;                                                                                                                                        \
    }                                                                                                                                                          \
    void __stl_fn(type, stack, clear)(__stl_t(type, stack) * arr)                                                                                              \
    {                                                                                                                                                          \
        arr->count = 0;                                                                                                                                        \
    }                                                                                                                                                          \
    void __stl_fn(type, stack, push)(__stl_t(type, stack) * arr, type value)                                                                                   \
    {                                                                                                                                                          \
        __stl_fn(type, __base_name, push_back)(arr->buffer, value, &arr->count);                                                                               \
    }                                                                                                                                                          \
    type __stl_fn(type, stack, pop)(__stl_t(type, stack) * arr)                                                                                                \
    {                                                                                                                                                          \
        return __stl_fn(type, __base_name, get)(arr->buffer, --arr->count);                                                                                    \
    }                                                                                                                                                          \
    type __stl_fn(type, stack, top)(__stl_t(type, stack) * arr)                                                                                                \
    {                                                                                                                                                          \
        return __stl_fn(type, __base_name, get)(arr->buffer, arr->count - 1);                                                                                  \
    }                                                                                                                                                          \
    void __stl_fn(type, stack, copy)(__stl_t(type, stack) * arr, __stl_t(type, stack) * *out, size_t start, size_t end)                                        \
    {                                                                                                                                                          \
        __stl_fn(type, __base_name, copy)(arr->buffer, &((*out)->buffer), start, end);                                                                         \
        (*out)->count = (end - start) < arr->count ? (end - start) : arr->count;                                                                               \
    }                                                                                                                                                          \
    void __stl_fn(type, stack, clone)(__stl_t(type, stack) * arr, __stl_t(type, stack) * *out)                                                                 \
    {                                                                                                                                                          \
        __stl_fn(type, __base_name, clone)(arr->buffer, &((*out)->buffer), arr->lenght);                                                                       \
        (*out)->count = arr->count;                                                                                                                            \
    }                                                                                                                                                          \
    bool __stl_fn(type, stack, equal)(__stl_t(type, stack) * a, __stl_t(type, stack) * b)                                                                      \
    {                                                                                                                                                          \
        return __stl_fn(type, __base_name, equal)(a->buffer, b->buffer, a->count);                                                                             \
    }                                                                                                                                                          \
    void __stl_fn(type, stack, fill)(__stl_t(type, stack) * arr, type value)                                                                                   \
    {                                                                                                                                                          \
        __stl_fn(type, __base_name, fill)(arr->buffer, value, arr->lenght);                                                                                    \
    }                                                                                                                                                          \
    int __stl_fn(type, stack, find)(__stl_t(type, stack) * arr, type value)                                                                                    \
    {                                                                                                                                                          \
        return __stl_fn(type, __base_name, find)(arr->buffer, value, arr->count);                                                                              \
    }                                                                                                                                                          \
    int __stl_fn(type, stack, find_cmp)(__stl_t(type, stack) * arr, type value, bool (*cmp)(type a, type b))                                                   \
    {                                                                                                                                                          \
        return __stl_fn(type, __base_name, find_cmp)(arr->buffer, value, arr->count, cmp);                                                                     \
    }                                                                                                                                                          \
    void __stl_fn(type, stack, resize)(__stl_t(type, stack) * arr, size_t lenght)                                                                              \
    {                                                                                                                                                          \
        __stl_fn(type, __base_name, resize)(&(arr->buffer), lenght);                                                                                           \
        arr->lenght = lenght;                                                                                                                                  \
    }                                                                                                                                                          \
    size_t __stl_fn(type, stack, count)(__stl_t(type, stack) * arr, type value)                                                                                \
    {                                                                                                                                                          \
        return __stl_fn(type, __base_name, count)(arr->buffer, value, arr->count);                                                                             \
    }                                                                                                                                                          \
    size_t __stl_fn(type, stack, count_cmp)(__stl_t(type, stack) * arr, type value, bool (*cmp)(type a, type b))                                               \
    {                                                                                                                                                          \
        return __stl_fn(type, __base_name, count_cmp)(arr->buffer, value, arr->count, cmp);                                                                    \
    }                                                                                                                                                          \
    bool __stl_fn(type, stack, all)(__stl_t(type, stack) * arr, type value)                                                                                    \
    {                                                                                                                                                          \
        return __stl_fn(type, __base_name, all)(arr->buffer, value, arr->count);                                                                               \
    }                                                                                                                                                          \
    bool __stl_fn(type, stack, all_cmp)(__stl_t(type, stack) * arr, type value, bool (*cmp)(type a, type b))                                                   \
    {                                                                                                                                                          \
        return __stl_fn(type, __base_name, all_cmp)(arr->buffer, value, arr->count, cmp);                                                                      \
    }                                                                                                                                                          \
    bool __stl_fn(type, stack, any)(__stl_t(type, stack) * arr, type value)                                                                                    \
    {                                                                                                                                                          \
        return __stl_fn(type, __base_name, any)(arr->buffer, value, arr->count);                                                                               \
    }                                                                                                                                                          \
    bool __stl_fn(type, stack, any_cmp)(__stl_t(type, stack) * arr, type value, bool (*cmp)(type a, type b))                                                   \
    {                                                                                                                                                          \
        return __stl_fn(type, __base_name, any_cmp)(arr->buffer, value, arr->count, cmp);                                                                      \
    }                                                                                                                                                          \
    void __stl_fn(type, stack, join)(__stl_t(type, stack) * a, __stl_t(type, stack) * b)                                                                       \
    {                                                                                                                                                          \
        __stl_fn(type, __base_name, join)(&(a->buffer), b->buffer, a->count, b->count);                                                                        \
        a->count += b->count;                                                                                                                                  \
    }                                                                                                                                                          \
    void __stl_fn(type, stack, reverse)(__stl_t(type, stack) * arr)                                                                                            \
    {                                                                                                                                                          \
        __stl_fn(type, __base_name, reverse)(arr->buffer, arr->count);                                                                                         \
    }                                                                                                                                                          \
    size_t __stl_fn(type, stack, lenght)(__stl_t(type, stack) * arr)                                                                                           \
    {                                                                                                                                                          \
        return arr->lenght;                                                                                                                                    \
    }                                                                                                                                                          \
    void __stl_fn(type, stack, map)(__stl_t(type, stack) * arr, type * *out, type(*map_fn)(type value, size_t index))                                          \
    {                                                                                                                                                          \
        __stl_fn(type, __base_name, map)(arr->buffer, out, arr->count, map_fn);                                                                                \
    }                                                                                                                                                          \
    void __stl_fn(type, stack, filter)(__stl_t(type, stack) * arr, type * *out, bool (*filter_fn)(type value, size_t index, type * filtered), size_t *out_len) \
    {                                                                                                                                                          \
        __stl_fn(type, __base_name, filter)(arr->buffer, out, arr->count, filter_fn, out_len);                                                                 \
    }

#endif