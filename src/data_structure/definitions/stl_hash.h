#ifndef STL_HASH_TABLE_H
#define STL_HASH_TABLE_H

#include "../internal/stl_macros.h"
#include "../internal/slt_foreach_macro.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"

#define __stl_bucket(key_type, value_type) _____concat(__prefix, _____concat(_____concat(key_type, _____concat(_, value_type)), _bucket))

#define __stl_bucket_arr(key_type, value_type) _____concat(__stl_bucket(key_type, value_type), _arr)

#define __stl_t_hash(key, value) __stl_t(_____concat(_____concat(key, _), value), hash)

#define __stl_fn_hash(ktype, vtype, name, fn) _____concat(_____concat(_____concat(__prefix, _____concat(_____concat(_____concat(_____concat(name, _), ktype), _), vtype)), _), fn)

#ifndef CSTL_USE_RAW
#define hash_map(key_type, value_type) __stl_t_hash(key_type, value_type)

#define hash_map_create(key_type, value_type) __stl_fn_hash(key_type, value_type, hash_map, create)
#define hash_map_add(key_type, value_type) __stl_fn_hash(key_type, value_type, hash_map, add)
#define hash_map_remove(key_type, value_type) __stl_fn_hash(key_type, value_type, hash_map, remove)
#define hash_map_get(key_type, value_type) __stl_fn_hash(key_type, value_type, hash_map, get)
#define hash_map_exist(key_type, value_type) __stl_fn_hash(key_type, value_type, hash_map, exist)
#define hash_map_free(key_type, value_type) __stl_fn_hash(key_type, value_type, hash_map, free)
#define hash_map_clear(key_type, value_type) __stl_fn_hash(key_type, value_type, hash_map, clear)
#define hash_map_lenght(key_type, value_type) __stl_fn_hash(key_type, value_type, hash_map, lenght)
#define hash_map_clone(key_type, value_type) __stl_fn_hash(key_type, value_type, hash_map, clone)
#define hash_map_equal(key_type, value_type) __stl_fn_hash(key_type, value_type, hash_map, equal)
#define hash_map_count_values(key_type, value_type) __stl_fn_hash(key_type, value_type, hash_map, count_values)
#define hash_map_count_values_cmp(key_type, value_type) __stl_fn_hash(key_type, value_type, hash_map, count_values_cmp)
#define hash_map_all_values(key_type, value_type) __stl_fn_hash(key_type, value_type, hash_map, all_values)
#define hash_map_all_values_cmp(key_type, value_type) __stl_fn_hash(key_type, value_type, hash_map, all_values_cmp)
#define hash_map_any_values(key_type, value_type) __stl_fn_hash(key_type, value_type, hash_map, any_values)
#define hash_map_any_values_cmp(key_type, value_type) __stl_fn_hash(key_type, value_type, hash_map, any_values_cmp)
#endif

#define stl_declare_hash_table_for(...) call_macro_x_for_each(___i_stl_declare_ht_, __VA_ARGS__)

#define __stl_declare_hash_array(data) \
    typedef struct                     \
    {                                  \
        data *arr;                     \
        size_t len;                    \
        size_t count;                  \
    } _____concat(data, _hash_arr_t);

#define ___stl_declare_hash_table(key_type, value_type)                        \
    typedef struct                                                             \
    {                                                                          \
        key_type key;                                                          \
        value_type value;                                                      \
    } __stl_bucket(key_type, value_type);                                      \
                                                                               \
    __stl_declare_hash_array(__stl_bucket(key_type, value_type));              \
                                                                               \
    typedef struct                                                             \
    {                                                                          \
        _____concat(__stl_bucket(key_type, value_type), _hash_arr_t) * buffer; \
        size_t len;                                                            \
        size_t count;                                                          \
        uintmax_t (*hash_fn)(char *);                                          \
        bool (*cmp_key_fn)(key_type a, key_type b);                            \
    } __stl_t_hash(key_type, value_type);

#define stl_declare_hash_table_alias(key_type, key_alias, value_type, value_alias) \
    typedef key_type key_alias;                                                    \
    typedef value_type value_alias;                                                \
    stl_declare_hash_table(key_alias, value_alias);

#define ___i_stl_declare_ht_(x) stl_declare_hash_table x

#define stl_declare_hash_table(key_type, value_type)                                                                                                                                                   \
    ___stl_declare_hash_table(key_type, value_type);                                                                                                                                                   \
    void __stl_fn_hash(key_type, value_type, hash_map, create)(__stl_t_hash(key_type, value_type) * hash_ptr, size_t lenght, uintmax_t(*hash_fn)(char *), bool (*cmp_key_fn)(key_type a, key_type b)); \
    void __stl_fn_hash(key_type, value_type, hash_map, add)(__stl_t_hash(key_type, value_type) * hash_ptr, key_type key, value_type value);                                                            \
    bool __stl_fn_hash(key_type, value_type, hash_map, get)(__stl_t_hash(key_type, value_type) * hash_ptr, key_type key, value_type * value);                                                          \
    bool __stl_fn_hash(key_type, value_type, hash_map, exist)(__stl_t_hash(key_type, value_type) * hash_ptr, key_type key);                                                                            \
    bool __stl_fn_hash(key_type, value_type, hash_map, remove)(__stl_t_hash(key_type, value_type) * hash_ptr, key_type key);                                                                           \
    void __stl_fn_hash(key_type, value_type, hash_map, free)(__stl_t_hash(key_type, value_type) * hash_ptr);                                                                                           \
    void __stl_fn_hash(key_type, value_type, hash_map, clear)(__stl_t_hash(key_type, value_type) * hash_ptr);                                                                                          \
    void __stl_fn_hash(key_type, value_type, hash_map, clone)(__stl_t_hash(key_type, value_type) * source, __stl_t_hash(key_type, value_type) * *dest);                                                \
    bool __stl_fn_hash(key_type, value_type, hash_map, equal)(__stl_t_hash(key_type, value_type) * a, __stl_t_hash(key_type, value_type) * b);                                                         \
    size_t __stl_fn_hash(key_type, value_type, hash_map, lenght)(__stl_t_hash(key_type, value_type) * hash_ptr);                                                                                       \
    size_t __stl_fn_hash(key_type, value_type, hash_map, count_values)(__stl_t_hash(key_type, value_type) * hash_ptr, value_type value);                                                               \
    size_t __stl_fn_hash(key_type, value_type, hash_map, count_values_cmp)(__stl_t_hash(key_type, value_type) * hash_ptr, value_type value, bool (*cmp)(value_type a, value_type b));                  \
    bool __stl_fn_hash(key_type, value_type, hash_map, all_values)(__stl_t_hash(key_type, value_type) * hash_ptr, value_type value);                                                                   \
    bool __stl_fn_hash(key_type, value_type, hash_map, all_values_cmp)(__stl_t_hash(key_type, value_type) * hash_ptr, value_type value, bool (*cmp)(value_type a, value_type b));                      \
    bool __stl_fn_hash(key_type, value_type, hash_map, any_values)(__stl_t_hash(key_type, value_type) * hash_ptr, value_type value);                                                                   \
    bool __stl_fn_hash(key_type, value_type, hash_map, any_values_cmp)(__stl_t_hash(key_type, value_type) * hash_ptr, value_type value, bool (*cmp)(value_type a, value_type b));

#define ___i___hash_map_foreach_0(key_type, value_type, p_hash, code)   \
    {                                                                   \
        for (size_t i = 0; i < p_hash->len; i++)                        \
        {                                                               \
            for (size_t k = 0; k < p_hash->buffer[i].count; k++)        \
            {                                                           \
                key_type cstl_key = p_hash->buffer[i].arr[k].key;       \
                value_type cstl_value = p_hash->buffer[i].arr[k].value; \
                code;                                                   \
            }                                                           \
        }                                                               \
    }

#define ___i___hash_map_foreach_1(key_type, value_type, p_hash, code, key_name) \
    {                                                                           \
        for (size_t i = 0; i < p_hash->len; i++)                                \
        {                                                                       \
            for (size_t k = 0; k < p_hash->buffer[i].count; k++)                \
            {                                                                   \
                key_type key_name = p_hash->buffer[i].arr[k].key;               \
                value_type cstl_value = p_hash->buffer[i].arr[k].value;         \
                code;                                                           \
            }                                                                   \
        }                                                                       \
    }

#define ___i___hash_map_foreach_2(key_type, value_type, p_hash, code, key_name, value_name) \
    {                                                                                       \
        for (size_t i = 0; i < p_hash->len; i++)                                            \
        {                                                                                   \
            for (size_t k = 0; k < p_hash->buffer[i].count; k++)                            \
            {                                                                               \
                key_type key_name = p_hash->buffer[i].arr[k].key;                           \
                value_type value_name = p_hash->buffer[i].arr[k].value;                     \
                code;                                                                       \
            }                                                                               \
        }                                                                                   \
    }
#endif