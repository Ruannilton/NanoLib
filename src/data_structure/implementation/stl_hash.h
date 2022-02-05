#ifndef STL_HASH_IMPL_H
#define STL_HASH_IMPL_H

#include "../internal/stl_macros.h"
#include "../internal/slt_foreach_macro.h"
#include <assert.h>

#define stl_implement_hash_table_for(...) call_macro_x_for_each(___i_stl_implement_ht_, __VA_ARGS__)

#define ___i_stl_implement_ht_(x) stl_implement_hash_table x

#define ___stl_generic_hash_cmp(key_type)                                      \
    bool _____concat(___stl_def_cmp_, key_type)(key_type a, key_type b)        \
    {                                                                          \
        return cstl_memcmp((void *)(&a), (void *)(&b), sizeof(key_type)) == 0; \
    }                                                                          \
                                                                               \
    uintmax_t _____concat(___stl_def_hash_, key_type)(char *key)               \
    {                                                                          \
        assert(key != NULL);                                                   \
        uintmax_t k = 0;                                                       \
        char *c = key;                                                         \
        for (size_t i = 0; i < sizeof(key_type); i++)                          \
        {                                                                      \
            k += (int)(c[i]);                                                  \
        }                                                                      \
        return k;                                                              \
    }

#define stl_implement_hash_table(key_type, value_type)                                                                                                                                                \
    ___stl_generic_hash_cmp(key_type);                                                                                                                                                                \
    void __stl_fn_hash(key_type, value_type, hash_map, create)(__stl_t_hash(key_type, value_type) * hash_ptr, size_t lenght, uintmax_t(*hash_fn)(char *), bool (*cmp_key_fn)(key_type a, key_type b)) \
    {                                                                                                                                                                                                 \
        assert(hash_ptr != NULL);                                                                                                                                                                     \
        assert(hash_fn != NULL);                                                                                                                                                                      \
        assert(cmp_key_fn != NULL);                                                                                                                                                                   \
        assert(lenght > 0);                                                                                                                                                                           \
        hash_ptr->len = lenght;                                                                                                                                                                       \
        hash_ptr->hash_fn = (hash_fn != 0) ? (hash_fn) : (_____concat(___stl_def_hash_, key_type));                                                                                                   \
        hash_ptr->cmp_key_fn = (cmp_key_fn != 0) ? (cmp_key_fn) : (_____concat(___stl_def_cmp_, key_type));                                                                                           \
        hash_ptr->buffer = cstl_malloc((lenght * sizeof(_____concat(__stl_bucket(key_type, value_type), _hash_arr_t))));                                                                              \
        hash_ptr->count = 0;                                                                                                                                                                          \
        for (size_t i = 0; i < lenght; i++)                                                                                                                                                           \
        {                                                                                                                                                                                             \
            hash_ptr->buffer[i].arr = 0;                                                                                                                                                              \
            hash_ptr->buffer[i].count = 0;                                                                                                                                                            \
            hash_ptr->buffer[i].len = 0;                                                                                                                                                              \
        }                                                                                                                                                                                             \
    }                                                                                                                                                                                                 \
    void __stl_fn_hash(key_type, value_type, hash_map, add)(__stl_t_hash(key_type, value_type) * hash_ptr, key_type key, value_type value)                                                            \
    {                                                                                                                                                                                                 \
        assert(hash_ptr != NULL);                                                                                                                                                                     \
        uintmax_t insert_index = hash_ptr->hash_fn((char *)(&(key))) % hash_ptr->len;                                                                                                                 \
        _____concat(__stl_bucket(key_type, value_type), _hash_arr_t) *bucket_arr = hash_ptr->buffer + insert_index;                                                                                   \
                                                                                                                                                                                                      \
        if (bucket_arr->len == 0)                                                                                                                                                                     \
        {                                                                                                                                                                                             \
            bucket_arr->len = 2;                                                                                                                                                                      \
            size_t alloc_size = sizeof(__stl_bucket(key_type, value_type)) * bucket_arr->len;                                                                                                         \
                                                                                                                                                                                                      \
            bucket_arr->arr = cstl_malloc(alloc_size);                                                                                                                                                \
        }                                                                                                                                                                                             \
        else                                                                                                                                                                                          \
        {                                                                                                                                                                                             \
            for (size_t i = 0; i < bucket_arr->count; i++)                                                                                                                                            \
            {                                                                                                                                                                                         \
                if (hash_ptr->cmp_key_fn(bucket_arr->arr[i].key, key))                                                                                                                                \
                {                                                                                                                                                                                     \
                    bucket_arr->arr[i].value = value;                                                                                                                                                 \
                    return;                                                                                                                                                                           \
                }                                                                                                                                                                                     \
            }                                                                                                                                                                                         \
        }                                                                                                                                                                                             \
        if (bucket_arr->count == bucket_arr->len)                                                                                                                                                     \
        {                                                                                                                                                                                             \
            bucket_arr->len *= 2;                                                                                                                                                                     \
            size_t relloc_size = sizeof(__stl_bucket(key_type, value_type)) * bucket_arr->len;                                                                                                        \
                                                                                                                                                                                                      \
            void *ptr = cstl_realloc(bucket_arr->arr, relloc_size);                                                                                                                                   \
            if (ptr)                                                                                                                                                                                  \
                bucket_arr->arr = ptr;                                                                                                                                                                \
        }                                                                                                                                                                                             \
                                                                                                                                                                                                      \
        bucket_arr->arr[bucket_arr->count] = (__stl_bucket(key_type, value_type)){.key = key, .value = value};                                                                                        \
        bucket_arr->count++;                                                                                                                                                                          \
        hash_ptr->count++;                                                                                                                                                                            \
    }                                                                                                                                                                                                 \
    bool __stl_fn_hash(key_type, value_type, hash_map, get)(__stl_t_hash(key_type, value_type) * hash_ptr, key_type key, value_type * value)                                                          \
    {                                                                                                                                                                                                 \
        assert(hash_ptr != NULL);                                                                                                                                                                     \
        uintmax_t get_index = hash_ptr->hash_fn((char *)(&(key))) % hash_ptr->len;                                                                                                                    \
        _____concat(__stl_bucket(key_type, value_type), _hash_arr_t) *bucket_arr = &(hash_ptr->buffer[get_index]);                                                                                    \
        if (bucket_arr->len == 0 || bucket_arr->count == 0)                                                                                                                                           \
            return false;                                                                                                                                                                             \
                                                                                                                                                                                                      \
        for (size_t i = 0; i < bucket_arr->count; i++)                                                                                                                                                \
        {                                                                                                                                                                                             \
            if (hash_ptr->cmp_key_fn(bucket_arr->arr[i].key, key))                                                                                                                                    \
            {                                                                                                                                                                                         \
                *value = bucket_arr->arr[i].value;                                                                                                                                                    \
                return true;                                                                                                                                                                          \
            }                                                                                                                                                                                         \
        }                                                                                                                                                                                             \
        return false;                                                                                                                                                                                 \
    }                                                                                                                                                                                                 \
    bool __stl_fn_hash(key_type, value_type, hash_map, exist)(__stl_t_hash(key_type, value_type) * hash_ptr, key_type key)                                                                            \
    {                                                                                                                                                                                                 \
        assert(hash_ptr != NULL);                                                                                                                                                                     \
        uintmax_t get_index = hash_ptr->hash_fn((char *)(&(key))) % hash_ptr->len;                                                                                                                    \
        _____concat(__stl_bucket(key_type, value_type), _hash_arr_t) *bucket_arr = &(hash_ptr->buffer[get_index]);                                                                                    \
        if (bucket_arr->len == 0 || bucket_arr->count == 0)                                                                                                                                           \
            return false;                                                                                                                                                                             \
        for (size_t i = 0; i < bucket_arr->count; i++)                                                                                                                                                \
        {                                                                                                                                                                                             \
            if (hash_ptr->cmp_key_fn(bucket_arr->arr[i].key, key))                                                                                                                                    \
            {                                                                                                                                                                                         \
                return true;                                                                                                                                                                          \
            }                                                                                                                                                                                         \
        }                                                                                                                                                                                             \
        return false;                                                                                                                                                                                 \
    }                                                                                                                                                                                                 \
    bool __stl_fn_hash(key_type, value_type, hash_map, remove)(__stl_t_hash(key_type, value_type) * hash_ptr, key_type key)                                                                           \
    {                                                                                                                                                                                                 \
        assert(hash_ptr != NULL);                                                                                                                                                                     \
        uintmax_t get_index = hash_ptr->hash_fn((char *)(&(key))) % hash_ptr->len;                                                                                                                    \
        _____concat(__stl_bucket(key_type, value_type), _hash_arr_t) *bucket_arr = &(hash_ptr->buffer[get_index]);                                                                                    \
        if (bucket_arr->len == 0 || bucket_arr->count == 0)                                                                                                                                           \
            return false;                                                                                                                                                                             \
        bool found = false;                                                                                                                                                                           \
        for (size_t i = 0; i < bucket_arr->count; i++)                                                                                                                                                \
        {                                                                                                                                                                                             \
            if (found)                                                                                                                                                                                \
            {                                                                                                                                                                                         \
                bucket_arr->arr[i - 1] = bucket_arr->arr[i];                                                                                                                                          \
            }                                                                                                                                                                                         \
            else if (hash_ptr->cmp_key_fn(bucket_arr->arr[i].key, key))                                                                                                                               \
            {                                                                                                                                                                                         \
                found = true;                                                                                                                                                                         \
            }                                                                                                                                                                                         \
        }                                                                                                                                                                                             \
        if (found)                                                                                                                                                                                    \
        {                                                                                                                                                                                             \
            bucket_arr->count--;                                                                                                                                                                      \
            hash_ptr->count--;                                                                                                                                                                        \
        }                                                                                                                                                                                             \
        return found;                                                                                                                                                                                 \
    }                                                                                                                                                                                                 \
    void __stl_fn_hash(key_type, value_type, hash_map, free)(__stl_t_hash(key_type, value_type) * hash_ptr)                                                                                           \
    {                                                                                                                                                                                                 \
        assert(hash_ptr != NULL);                                                                                                                                                                     \
        for (size_t i = 0; i < hash_ptr->len; i++)                                                                                                                                                    \
        {                                                                                                                                                                                             \
            cstl_free(hash_ptr->buffer[i].arr);                                                                                                                                                       \
            hash_ptr->buffer[i].arr = 0;                                                                                                                                                              \
        }                                                                                                                                                                                             \
        cstl_free(hash_ptr->buffer);                                                                                                                                                                  \
        hash_ptr->buffer = 0;                                                                                                                                                                         \
    }                                                                                                                                                                                                 \
    void __stl_fn_hash(key_type, value_type, hash_map, clear)(__stl_t_hash(key_type, value_type) * hash_ptr)                                                                                          \
    {                                                                                                                                                                                                 \
        assert(hash_ptr != NULL);                                                                                                                                                                     \
        for (size_t i = 0; i < hash_ptr->len; i++)                                                                                                                                                    \
        {                                                                                                                                                                                             \
            cstl_free(hash_ptr->buffer[i].arr);                                                                                                                                                       \
            hash_ptr->buffer[i].arr = 0;                                                                                                                                                              \
            hash_ptr->buffer[i].count = 0;                                                                                                                                                            \
            hash_ptr->buffer[i].len = 0;                                                                                                                                                              \
        }                                                                                                                                                                                             \
        hash_ptr->count = 0;                                                                                                                                                                          \
    }                                                                                                                                                                                                 \
    size_t __stl_fn_hash(key_type, value_type, hash_map, lenght)(__stl_t_hash(key_type, value_type) * hash_ptr)                                                                                       \
    {                                                                                                                                                                                                 \
        assert(hash_ptr != NULL);                                                                                                                                                                     \
        return hash_ptr->count;                                                                                                                                                                       \
    }                                                                                                                                                                                                 \
    void __stl_fn_hash(key_type, value_type, hash_map, clone)(__stl_t_hash(key_type, value_type) * source, __stl_t_hash(key_type, value_type) * *dest)                                                \
    {                                                                                                                                                                                                 \
        (*dest)->len = source->len;                                                                                                                                                                   \
        (*dest)->count = source->count;                                                                                                                                                               \
        (*dest)->hash_fn = source->hash_fn;                                                                                                                                                           \
        (*dest)->cmp_key_fn = source->cmp_key_fn;                                                                                                                                                     \
        (*dest)->buffer = cstl_malloc(((*dest)->len * sizeof(_____concat(__stl_bucket(key_type, value_type), _hash_arr_t))));                                                                         \
        for (size_t i = 0; i < (*dest)->len; i++)                                                                                                                                                     \
        {                                                                                                                                                                                             \
            (*dest)->buffer[i].count = source->buffer[i].count;                                                                                                                                       \
            (*dest)->buffer[i].len = source->buffer[i].len;                                                                                                                                           \
            cstl_memcpy((*dest)->buffer[i].arr, source->buffer[i].arr, sizeof(__stl_bucket(key_type, value_type)) * source->buffer[i].len);                                                           \
        }                                                                                                                                                                                             \
    }                                                                                                                                                                                                 \
    bool __stl_fn_hash(key_type, value_type, hash_map, equal)(__stl_t_hash(key_type, value_type) * a, __stl_t_hash(key_type, value_type) * b)                                                         \
    {                                                                                                                                                                                                 \
        if (a->len == b->len &&                                                                                                                                                                       \
            a->count == b->count &&                                                                                                                                                                   \
            a->hash_fn == b->hash_fn &&                                                                                                                                                               \
            a->cmp_key_fn == b->cmp_key_fn)                                                                                                                                                           \
        {                                                                                                                                                                                             \
            for (size_t i = 0; i < a->len; i++)                                                                                                                                                       \
            {                                                                                                                                                                                         \
                if (!(a->buffer[i].len == b->buffer[i].len &&                                                                                                                                         \
                      cstl_memcmp(a->buffer[i].arr, b->buffer[i].arr, sizeof(__stl_bucket(key_type, value_type)) * a->buffer[i].len) == 0))                                                           \
                    return false;                                                                                                                                                                     \
            }                                                                                                                                                                                         \
            return true;                                                                                                                                                                              \
        }                                                                                                                                                                                             \
        return false;                                                                                                                                                                                 \
    }                                                                                                                                                                                                 \
    size_t __stl_fn_hash(key_type, value_type, hash_map, count_values)(__stl_t_hash(key_type, value_type) * hash_ptr, value_type value)                                                               \
    {                                                                                                                                                                                                 \
        size_t count = 0;                                                                                                                                                                             \
        for (size_t i = 0; i < hash_ptr->len; i++)                                                                                                                                                    \
        {                                                                                                                                                                                             \
            for (size_t j = 0; j < hash_ptr->buffer[i].len; j++)                                                                                                                                      \
            {                                                                                                                                                                                         \
                if (hash_ptr->buffer[i].arr[j].value == value)                                                                                                                                        \
                    count++;                                                                                                                                                                          \
            }                                                                                                                                                                                         \
        }                                                                                                                                                                                             \
        return count;                                                                                                                                                                                 \
    }                                                                                                                                                                                                 \
    size_t __stl_fn_hash(key_type, value_type, hash_map, count_values_cmp)(__stl_t_hash(key_type, value_type) * hash_ptr, value_type value, bool (*cmp)(value_type a, value_type b))                  \
    {                                                                                                                                                                                                 \
        size_t count = 0;                                                                                                                                                                             \
        for (size_t i = 0; i < hash_ptr->len; i++)                                                                                                                                                    \
        {                                                                                                                                                                                             \
            for (size_t j = 0; j < hash_ptr->buffer[i].len; j++)                                                                                                                                      \
            {                                                                                                                                                                                         \
                if (cmp(hash_ptr->buffer[i].arr[j].value, value))                                                                                                                                     \
                    count++;                                                                                                                                                                          \
            }                                                                                                                                                                                         \
        }                                                                                                                                                                                             \
        return count;                                                                                                                                                                                 \
    }                                                                                                                                                                                                 \
    bool __stl_fn_hash(key_type, value_type, hash_map, all_values)(__stl_t_hash(key_type, value_type) * hash_ptr, value_type value)                                                                   \
    {                                                                                                                                                                                                 \
        for (size_t i = 0; i < hash_ptr->len; i++)                                                                                                                                                    \
        {                                                                                                                                                                                             \
            for (size_t j = 0; j < hash_ptr->buffer[i].len; j++)                                                                                                                                      \
            {                                                                                                                                                                                         \
                if (hash_ptr->buffer[i].arr[j].value != value)                                                                                                                                        \
                    return false;                                                                                                                                                                     \
            }                                                                                                                                                                                         \
        }                                                                                                                                                                                             \
        return true;                                                                                                                                                                                  \
    }                                                                                                                                                                                                 \
    bool __stl_fn_hash(key_type, value_type, hash_map, all_values_cmp)(__stl_t_hash(key_type, value_type) * hash_ptr, value_type value, bool (*cmp)(value_type a, value_type b))                      \
    {                                                                                                                                                                                                 \
        for (size_t i = 0; i < hash_ptr->len; i++)                                                                                                                                                    \
        {                                                                                                                                                                                             \
            for (size_t j = 0; j < hash_ptr->buffer[i].len; j++)                                                                                                                                      \
            {                                                                                                                                                                                         \
                if (!cmp(hash_ptr->buffer[i].arr[j].value, value))                                                                                                                                    \
                    return false;                                                                                                                                                                     \
            }                                                                                                                                                                                         \
        }                                                                                                                                                                                             \
        return true;                                                                                                                                                                                  \
    }                                                                                                                                                                                                 \
    bool __stl_fn_hash(key_type, value_type, hash_map, any_values)(__stl_t_hash(key_type, value_type) * hash_ptr, value_type value)                                                                   \
    {                                                                                                                                                                                                 \
        for (size_t i = 0; i < hash_ptr->len; i++)                                                                                                                                                    \
        {                                                                                                                                                                                             \
            for (size_t j = 0; j < hash_ptr->buffer[i].len; j++)                                                                                                                                      \
            {                                                                                                                                                                                         \
                if (hash_ptr->buffer[i].arr[j].value == value)                                                                                                                                        \
                    return true;                                                                                                                                                                      \
            }                                                                                                                                                                                         \
        }                                                                                                                                                                                             \
        return false;                                                                                                                                                                                 \
    }                                                                                                                                                                                                 \
    bool __stl_fn_hash(key_type, value_type, hash_map, any_values_cmp)(__stl_t_hash(key_type, value_type) * hash_ptr, value_type value, bool (*cmp)(value_type a, value_type b))                      \
    {                                                                                                                                                                                                 \
        for (size_t i = 0; i < hash_ptr->len; i++)                                                                                                                                                    \
        {                                                                                                                                                                                             \
            for (size_t j = 0; j < hash_ptr->buffer[i].len; j++)                                                                                                                                      \
            {                                                                                                                                                                                         \
                if (cmp(hash_ptr->buffer[i].arr[j].value, value))                                                                                                                                     \
                    return true;                                                                                                                                                                      \
            }                                                                                                                                                                                         \
        }                                                                                                                                                                                             \
        return false;                                                                                                                                                                                 \
    }

#endif