#ifndef STL_VECTOR_IMPL_H
#define STL_VECTOR_IMPL_H

#include "stl_core.h"
#include <assert.h>
#define stl_implement_vector_for(...) call_macro_x_for_each(stl_implement_vector, __VA_ARGS__)

#define __internal_vec_inc(vec, type, inc)                                            \
    {                                                                                 \
        if (vec->count + inc >= vec->lenght)                                          \
        {                                                                             \
            void *nptr = cstl_realloc(vec->buffer, (vec->lenght * 2) * sizeof(type)); \
            if (nptr != NULL)                                                         \
            {                                                                         \
                vec->buffer = nptr;                                                   \
                vec->lenght *= 2;                                                     \
                vec->count += inc;                                                    \
            }                                                                         \
        }                                                                             \
        else                                                                          \
        {                                                                             \
            vec->count += inc;                                                        \
        }                                                                             \
    }

#define __internal_vec_dec(vec, dec) \
    {                                \
        vec->count -= dec;           \
    }

#define stl_implement_vector(type)                                                                                                                               \
    void __stl_fn(type, vector, create)(__stl_t(type, vector) * vec, size_t lenght)                                                                              \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        assert(lenght > 0);                                                                                                                                      \
        vec->lenght = lenght;                                                                                                                                    \
        vec->count = 0;                                                                                                                                          \
        __stl_fn(type, __base_name, create)(&(vec->buffer), lenght);                                                                                             \
    }                                                                                                                                                            \
    void __stl_fn(type, vector, desloc)(__stl_t(type, vector) * vec, size_t from, int steps)                                                                     \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        __internal_vec_inc(vec, type, steps);                                                                                                                    \
        __stl_fn(type, __base_name, desloc)(vec->buffer, vec->lenght, from, steps);                                                                              \
    }                                                                                                                                                            \
    void __stl_fn(type, vector, insert)(__stl_t(type, vector) * vec, type value, size_t index)                                                                   \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        assert(index <= vec->lenght);                                                                                                                            \
        __internal_vec_inc(vec, type, 1);                                                                                                                        \
        __stl_fn(type, __base_name, insert)(vec->buffer, value, index, vec->lenght);                                                                             \
    }                                                                                                                                                            \
    void __stl_fn(type, vector, set)(__stl_t(type, vector) * vec, type value, size_t index)                                                                      \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        assert(index < vec->lenght);                                                                                                                             \
        __stl_fn(type, __base_name, set)(vec->buffer, value, index);                                                                                             \
    }                                                                                                                                                            \
    void __stl_fn(type, vector, remove)(__stl_t(type, vector) * vec, size_t index)                                                                               \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        assert(index < vec->lenght);                                                                                                                             \
        __stl_fn(type, __base_name, remove)(vec->buffer, index, vec->count);                                                                                     \
        __internal_vec_dec(vec, 1);                                                                                                                              \
    }                                                                                                                                                            \
    type __stl_fn(type, vector, get)(__stl_t(type, vector) * vec, size_t index)                                                                                  \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        assert(index < vec->lenght);                                                                                                                             \
        return __stl_fn(type, __base_name, get)(vec->buffer, index);                                                                                             \
    }                                                                                                                                                            \
    type __stl_fn(type, vector, first)(__stl_t(type, vector) * vec)                                                                                              \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        return __stl_fn(type, __base_name, first)(vec->buffer);                                                                                                  \
    }                                                                                                                                                            \
    type __stl_fn(type, vector, last)(__stl_t(type, vector) * vec)                                                                                               \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        return __stl_fn(type, __base_name, last)(vec->buffer, vec->count);                                                                                       \
    }                                                                                                                                                            \
    void __stl_fn(type, vector, push_front)(__stl_t(type, vector) * vec, type value)                                                                             \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        __internal_vec_inc(vec, type, 1);                                                                                                                        \
        __stl_fn(type, __base_name, push_front)(vec->buffer, value, vec->count);                                                                                 \
    }                                                                                                                                                            \
    void __stl_fn(type, vector, push_back)(__stl_t(type, vector) * vec, type value)                                                                              \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        __stl_fn(type, __base_name, push_back)(vec->buffer, value, &(vec->count));                                                                               \
        __internal_vec_inc(vec, type, 0);                                                                                                                        \
    }                                                                                                                                                            \
    void __stl_fn(type, vector, pop_front)(__stl_t(type, vector) * vec)                                                                                          \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        __stl_fn(type, __base_name, pop_front)(vec->buffer, vec->count);                                                                                         \
        __internal_vec_dec(vec, 1);                                                                                                                              \
    }                                                                                                                                                            \
    void __stl_fn(type, vector, pop_back)(__stl_t(type, vector) * vec)                                                                                           \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        __stl_fn(type, __base_name, remove)(vec->buffer, vec->count - 1, vec->count);                                                                            \
        __internal_vec_dec(vec, 1);                                                                                                                              \
    }                                                                                                                                                            \
    void __stl_fn(type, vector, copy)(__stl_t(type, vector) * vec, __stl_t(type, vector) * out, size_t start, size_t end)                                        \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        assert(out != NULL);                                                                                                                                     \
        __stl_fn(type, __base_name, copy)(vec->buffer, &(out->buffer), start, end);                                                                              \
        out->count = (end - start) < vec->count ? (end - start) : vec->count;                                                                                    \
    }                                                                                                                                                            \
    void __stl_fn(type, vector, clone)(__stl_t(type, vector) * vec, __stl_t(type, vector) * out)                                                                 \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        assert(out != NULL);                                                                                                                                     \
        __stl_fn(type, __base_name, clone)(vec->buffer, &(out->buffer), vec->lenght);                                                                            \
        out->count = vec->count;                                                                                                                                 \
    }                                                                                                                                                            \
    bool __stl_fn(type, vector, equal)(__stl_t(type, vector) * a, __stl_t(type, vector) * b)                                                                     \
    {                                                                                                                                                            \
        assert(a != NULL);                                                                                                                                       \
        assert(b != NULL);                                                                                                                                       \
        return __stl_fn(type, __base_name, equal)(a->buffer, b->buffer, a->count);                                                                               \
    }                                                                                                                                                            \
    void __stl_fn(type, vector, fill)(__stl_t(type, vector) * vec, type value)                                                                                   \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        __stl_fn(type, __base_name, fill)(vec->buffer, value, vec->lenght);                                                                                      \
    }                                                                                                                                                            \
    int __stl_fn(type, vector, find)(__stl_t(type, vector) * vec, type value)                                                                                    \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        return __stl_fn(type, __base_name, find)(vec->buffer, value, vec->count);                                                                                \
    }                                                                                                                                                            \
    int __stl_fn(type, vector, find_cmp)(__stl_t(type, vector) * vec, type value, bool (*cmp)(type a, type b))                                                   \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        assert(cmp != NULL);                                                                                                                                     \
        return __stl_fn(type, __base_name, find_cmp)(vec->buffer, value, vec->count, cmp);                                                                       \
    }                                                                                                                                                            \
    void __stl_fn(type, vector, resize)(__stl_t(type, vector) * vec, size_t lenght)                                                                              \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        assert(lenght > 0);                                                                                                                                      \
        __stl_fn(type, __base_name, resize)(&(vec->buffer), lenght);                                                                                             \
        vec->lenght = lenght;                                                                                                                                    \
    }                                                                                                                                                            \
    size_t __stl_fn(type, vector, count)(__stl_t(type, vector) * vec, type value)                                                                                \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        return __stl_fn(type, __base_name, count)(vec->buffer, value, vec->count);                                                                               \
    }                                                                                                                                                            \
    size_t __stl_fn(type, vector, count_cmp)(__stl_t(type, vector) * vec, type value, bool (*cmp)(type a, type b))                                               \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        assert(cmp != NULL);                                                                                                                                     \
        return __stl_fn(type, __base_name, count_cmp)(vec->buffer, value, vec->count, cmp);                                                                      \
    }                                                                                                                                                            \
    bool __stl_fn(type, vector, all)(__stl_t(type, vector) * vec, type value)                                                                                    \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        return __stl_fn(type, __base_name, all)(vec->buffer, value, vec->count);                                                                                 \
    }                                                                                                                                                            \
    bool __stl_fn(type, vector, any)(__stl_t(type, vector) * vec, type value)                                                                                    \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        return __stl_fn(type, __base_name, any)(vec->buffer, value, vec->count);                                                                                 \
    }                                                                                                                                                            \
    bool __stl_fn(type, vector, all_cmp)(__stl_t(type, vector) * vec, type value, bool (*cmp)(type a, type b))                                                   \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        assert(cmp != NULL);                                                                                                                                     \
        return __stl_fn(type, __base_name, all_cmp)(vec->buffer, value, vec->count, cmp);                                                                        \
    }                                                                                                                                                            \
    bool __stl_fn(type, vector, any_cmp)(__stl_t(type, vector) * vec, type value, bool (*cmp)(type a, type b))                                                   \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        assert(cmp != NULL);                                                                                                                                     \
        return __stl_fn(type, __base_name, any_cmp)(vec->buffer, value, vec->count, cmp);                                                                        \
    }                                                                                                                                                            \
    void __stl_fn(type, vector, join)(__stl_t(type, vector) * a, __stl_t(type, vector) * b)                                                                      \
    {                                                                                                                                                            \
        assert(a != NULL);                                                                                                                                       \
        assert(b != NULL);                                                                                                                                       \
        __stl_fn(type, __base_name, join)(&(a->buffer), b->buffer, a->count, b->count);                                                                          \
        a->count += b->count;                                                                                                                                    \
    }                                                                                                                                                            \
    void __stl_fn(type, vector, reverse)(__stl_t(type, vector) * vec)                                                                                            \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        __stl_fn(type, __base_name, reverse)(vec->buffer, vec->count);                                                                                           \
    }                                                                                                                                                            \
    void __stl_fn(type, vector, free)(__stl_t(type, vector) * vec)                                                                                               \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        cstl_free(vec->buffer);                                                                                                                                  \
        vec->count = 0;                                                                                                                                          \
        vec->lenght = 0;                                                                                                                                         \
        vec->buffer = 0;                                                                                                                                         \
    }                                                                                                                                                            \
    size_t __stl_fn(type, vector, lenght)(__stl_t(type, vector) * vec)                                                                                           \
    {                                                                                                                                                            \
        assert(vec != NULL);                                                                                                                                     \
        return vec->lenght;                                                                                                                                      \
    }                                                                                                                                                            \
    void __stl_fn(type, vector, map)(__stl_t(type, vector) * vec, type * *out, type(*map_fn)(type value, size_t index))                                          \
    {                                                                                                                                                            \
        __stl_fn(type, __base_name, map)(vec->buffer, out, vec->count, map_fn);                                                                                  \
    }                                                                                                                                                            \
    void __stl_fn(type, vector, filter)(__stl_t(type, vector) * vec, type * *out, bool (*filter_fn)(type value, size_t index, type * filtered), size_t *out_len) \
    {                                                                                                                                                            \
        __stl_fn(type, __base_name, filter)(vec->buffer, out, vec->count, filter_fn, out_len);                                                                   \
    }

#endif