#ifndef STL_QUEUE_IMPL_H
#define STL_QUEUE_IMPL_H

#include "../internal/stl_macros.h"
#include "../internal/slt_foreach_macro.h"
#include <assert.h>

#define stl_implement_queue_for(...) call_macro_x_for_each(stl_implement_queue, __VA_ARGS__)

#define stl_implement_queue(type)                                                                                                                              \
    void __stl_fn(type, queue, create)(__stl_t(type, queue) * arr, size_t lenght)                                                                              \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        arr->lenght = lenght;                                                                                                                                  \
        arr->count = 0;                                                                                                                                        \
        __stl_fn(type, __base_name, create)(&(arr->buffer), lenght);                                                                                           \
    }                                                                                                                                                          \
    void __stl_fn(type, queue, free)(__stl_t(type, queue) * arr)                                                                                               \
    {                                                                                                                                                          \
        assert(arr != NULL);                                                                                                                                   \
        assert(arr->buffer != NULL);                                                                                                                           \
        cstl_free(arr->buffer);                                                                                                                                \
        arr->lenght = 0;                                                                                                                                       \
        arr->buffer = 0;                                                                                                                                       \
        arr->count = 0;                                                                                                                                        \
    }                                                                                                                                                          \
    void __stl_fn(type, queue, clear)(__stl_t(type, queue) * arr)                                                                                              \
    {                                                                                                                                                          \
        arr->count = 0;                                                                                                                                        \
    }                                                                                                                                                          \
    void __stl_fn(type, queue, enqueue)(__stl_t(type, queue) * arr, type value)                                                                                \
    {                                                                                                                                                          \
        __stl_fn(type, __base_name, push_back)(arr->buffer, value, &arr->count);                                                                               \
    }                                                                                                                                                          \
    type __stl_fn(type, queue, dequeue)(__stl_t(type, queue) * arr)                                                                                            \
    {                                                                                                                                                          \
        type __v = __stl_fn(type, __base_name, first)(arr->buffer);                                                                                            \
        __stl_fn(type, __base_name, pop_front)(arr->buffer, arr->count);                                                                                       \
        arr->count--;                                                                                                                                          \
        return __v;                                                                                                                                            \
    }                                                                                                                                                          \
    type __stl_fn(type, queue, first)(__stl_t(type, queue) * arr)                                                                                              \
    {                                                                                                                                                          \
        return __stl_fn(type, __base_name, first)(arr->buffer);                                                                                                \
    }                                                                                                                                                          \
    type __stl_fn(type, queue, last)(__stl_t(type, queue) * arr)                                                                                               \
    {                                                                                                                                                          \
        return __stl_fn(type, __base_name, last)(arr->buffer, arr->count);                                                                                     \
    }                                                                                                                                                          \
    void __stl_fn(type, queue, copy)(__stl_t(type, queue) * arr, __stl_t(type, queue) * *out, size_t start, size_t end)                                        \
    {                                                                                                                                                          \
        __stl_fn(type, __base_name, copy)(arr->buffer, &((*out)->buffer), start, end);                                                                         \
        (*out)->count = (end - start) < arr->count ? (end - start) : arr->count;                                                                               \
    }                                                                                                                                                          \
    void __stl_fn(type, queue, clone)(__stl_t(type, queue) * arr, __stl_t(type, queue) * *out)                                                                 \
    {                                                                                                                                                          \
        __stl_fn(type, __base_name, clone)(arr->buffer, &((*out)->buffer), arr->lenght);                                                                       \
        (*out)->count = arr->count;                                                                                                                            \
    }                                                                                                                                                          \
    bool __stl_fn(type, queue, equal)(__stl_t(type, queue) * a, __stl_t(type, queue) * b)                                                                      \
    {                                                                                                                                                          \
        return __stl_fn(type, __base_name, equal)(a->buffer, b->buffer, a->count);                                                                             \
    }                                                                                                                                                          \
    void __stl_fn(type, queue, fill)(__stl_t(type, queue) * arr, type value)                                                                                   \
    {                                                                                                                                                          \
        __stl_fn(type, __base_name, fill)(arr->buffer, value, arr->lenght);                                                                                    \
    }                                                                                                                                                          \
    int __stl_fn(type, queue, find)(__stl_t(type, queue) * arr, type value)                                                                                    \
    {                                                                                                                                                          \
        return __stl_fn(type, __base_name, find)(arr->buffer, value, arr->count);                                                                              \
    }                                                                                                                                                          \
    int __stl_fn(type, queue, find_cmp)(__stl_t(type, queue) * arr, type value, bool (*cmp)(type a, type b))                                                   \
    {                                                                                                                                                          \
        return __stl_fn(type, __base_name, find_cmp)(arr->buffer, value, arr->count, cmp);                                                                     \
    }                                                                                                                                                          \
    void __stl_fn(type, queue, resize)(__stl_t(type, queue) * arr, size_t lenght)                                                                              \
    {                                                                                                                                                          \
        __stl_fn(type, __base_name, resize)(&(arr->buffer), lenght);                                                                                           \
        arr->lenght = lenght;                                                                                                                                  \
    }                                                                                                                                                          \
    size_t __stl_fn(type, queue, count)(__stl_t(type, queue) * arr, type value)                                                                                \
    {                                                                                                                                                          \
        return __stl_fn(type, __base_name, count)(arr->buffer, value, arr->count);                                                                             \
    }                                                                                                                                                          \
    size_t __stl_fn(type, queue, count_cmp)(__stl_t(type, queue) * arr, type value, bool (*cmp)(type a, type b))                                               \
    {                                                                                                                                                          \
        return __stl_fn(type, __base_name, count_cmp)(arr->buffer, value, arr->count, cmp);                                                                    \
    }                                                                                                                                                          \
    bool __stl_fn(type, queue, all)(__stl_t(type, queue) * arr, type value)                                                                                    \
    {                                                                                                                                                          \
        return __stl_fn(type, __base_name, all)(arr->buffer, value, arr->count);                                                                               \
    }                                                                                                                                                          \
    bool __stl_fn(type, queue, all_cmp)(__stl_t(type, queue) * arr, type value, bool (*cmp)(type a, type b))                                                   \
    {                                                                                                                                                          \
        return __stl_fn(type, __base_name, all_cmp)(arr->buffer, value, arr->count, cmp);                                                                      \
    }                                                                                                                                                          \
    bool __stl_fn(type, queue, any)(__stl_t(type, queue) * arr, type value)                                                                                    \
    {                                                                                                                                                          \
        return __stl_fn(type, __base_name, any)(arr->buffer, value, arr->count);                                                                               \
    }                                                                                                                                                          \
    bool __stl_fn(type, queue, any_cmp)(__stl_t(type, queue) * arr, type value, bool (*cmp)(type a, type b))                                                   \
    {                                                                                                                                                          \
        return __stl_fn(type, __base_name, any_cmp)(arr->buffer, value, arr->count, cmp);                                                                      \
    }                                                                                                                                                          \
    void __stl_fn(type, queue, join)(__stl_t(type, queue) * a, __stl_t(type, queue) * b)                                                                       \
    {                                                                                                                                                          \
        __stl_fn(type, __base_name, join)(&(a->buffer), b->buffer, a->count, b->count);                                                                        \
        a->count += b->count;                                                                                                                                  \
    }                                                                                                                                                          \
    void __stl_fn(type, queue, reverse)(__stl_t(type, queue) * arr)                                                                                            \
    {                                                                                                                                                          \
        __stl_fn(type, __base_name, reverse)(arr->buffer, arr->count);                                                                                         \
    }                                                                                                                                                          \
    size_t __stl_fn(type, queue, lenght)(__stl_t(type, queue) * arr)                                                                                           \
    {                                                                                                                                                          \
        return arr->lenght;                                                                                                                                    \
    }                                                                                                                                                          \
    void __stl_fn(type, queue, map)(__stl_t(type, queue) * arr, type * *out, type(*map_fn)(type value, size_t index))                                          \
    {                                                                                                                                                          \
        __stl_fn(type, __base_name, map)(arr->buffer, out, arr->count, map_fn);                                                                                \
    }                                                                                                                                                          \
    void __stl_fn(type, queue, filter)(__stl_t(type, queue) * arr, type * *out, bool (*filter_fn)(type value, size_t index, type * filtered), size_t *out_len) \
    {                                                                                                                                                          \
        __stl_fn(type, __base_name, filter)(arr->buffer, out, arr->count, filter_fn, out_len);                                                                 \
    }

#endif