#ifndef STL_HASH_TABLE_H
#define STL_HASH_TABLE_H

#include "../internal/stl_macros.h"
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
#define hash_map_delete(key_type, value_type) __stl_fn_hash(key_type, value_type, hash_map, delete)
#define hash_map_clear(key_type, value_type) __stl_fn_hash(key_type, value_type, hash_map, clear)
#endif

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
        uintmax_t (*hash_fn)(char *);                                          \
        bool (*cmp_key_fn)(key_type a, key_type b);                            \
    } __stl_t_hash(key_type, value_type);

#define stl_declare_hash_table_alias(key_type, key_alias, value_type, value_alias) \
    typedef key_type key_alias;                                                    \
    typedef value_type value_alias;                                                \
    stl_declare_hash_table(key_alias, value_alias);

#define stl_declare_hash_table(key_type, value_type)                                                                                                                                                   \
    ___stl_declare_hash_table(key_type, value_type);                                                                                                                                                   \
    void __stl_fn_hash(key_type, value_type, hash_map, create)(__stl_t_hash(key_type, value_type) * hash_ptr, size_t lenght, uintmax_t(*hash_fn)(char *), bool (*cmp_key_fn)(key_type a, key_type b)); \
    void __stl_fn_hash(key_type, value_type, hash_map, add)(__stl_t_hash(key_type, value_type) * hash_ptr, key_type key, value_type value);                                                            \
    bool __stl_fn_hash(key_type, value_type, hash_map, get)(__stl_t_hash(key_type, value_type) * hash_ptr, key_type key, value_type * value);                                                          \
    bool __stl_fn_hash(key_type, value_type, hash_map, exist)(__stl_t_hash(key_type, value_type) * hash_ptr, key_type key);                                                                            \
    bool __stl_fn_hash(key_type, value_type, hash_map, remove)(__stl_t_hash(key_type, value_type) * hash_ptr, key_type key);                                                                           \
    void __stl_fn_hash(key_type, value_type, hash_map, delete)(__stl_t_hash(key_type, value_type) * hash_ptr);                                                                                         \
    void __stl_fn_hash(key_type, value_type, hash_map, clear)(__stl_t_hash(key_type, value_type) * hash_ptr);

#endif