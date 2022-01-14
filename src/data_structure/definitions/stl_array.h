#ifndef STL_ARRAY_H
#define STL_ARRAY_H

#include "../internal/stl_macros.h"

#ifndef CSTL_USE_RAW
#define array(type) __stl_t(type, array)

#define array_create(type) __stl_fn(type, array, create)
#define array_desloc(type) __stl_fn(type, array, desloc)
#define array_insert(type) __stl_fn(type, array, insert)
#define array_set(type) __stl_fn(type, array, set)
#define array_remove(type) __stl_fn(type, array, remove)
#define array_get(type) __stl_fn(type, array, get)
#define array_first(type) __stl_fn(type, array, first)
#define array_copy(type) __stl_fn(type, array, copy)
#define array_clone(type) __stl_fn(type, array, clone)
#define array_equal(type) __stl_fn(type, array, equal)
#define array_fill(type) __stl_fn(type, array, fill)
#define array_find(type) __stl_fn(type, array, find)
#define array_find_cmp(type) __stl_fn(type, array, find_cmp)
#define array_resize(type) __stl_fn(type, array, resize)
#define array_count(type) __stl_fn(type, array, count)
#define array_count_cmp(type) __stl_fn(type, array, count_cmp)
#define array_all(type) __stl_fn(type, array, all)
#define array_all_cmp(type) __stl_fn(type, array, all_cmp)
#define array_join(type) __stl_fn(type, array, join)
#define array_reverse(type) __stl_fn(type, array, reverse)
#define array_free(type) __stl_fn(type, array, free)
#endif

#define stl_declare_array_alias(type, alias) \
    typedef type alias;                      \
    stl_declare_array(alias)

#define stl_declare_array(type)                                                                                             \
    typedef struct                                                                                                          \
    {                                                                                                                       \
        type *buffer;                                                                                                       \
        size_t lenght;                                                                                                      \
    } __stl_t(type, array);                                                                                                 \
                                                                                                                            \
    void __stl_fn(type, array, create)(__stl_t(type, array) * arr, size_t lenght);                                          \
    void __stl_fn(type, array, desloc)(__stl_t(type, array) * arr, size_t from, int steps);                                 \
    void __stl_fn(type, array, insert)(__stl_t(type, array) * arr, type value, size_t index);                               \
    void __stl_fn(type, array, set)(__stl_t(type, array) * arr, type value, size_t index);                                  \
    void __stl_fn(type, array, remove)(__stl_t(type, array) * arr, size_t index);                                           \
    type __stl_fn(type, array, get)(__stl_t(type, array) * arr, size_t index);                                              \
    type __stl_fn(type, array, first)(__stl_t(type, array) * arr);                                                          \
    void __stl_fn(type, array, copy)(__stl_t(type, array) * arr, type * *out, size_t start, size_t end);                    \
    void __stl_fn(type, array, clone)(__stl_t(type, array) * arr, type * *out);                                             \
    bool __stl_fn(type, array, equal)(__stl_t(type, array) * a, __stl_t(type, array) * b);                                  \
    void __stl_fn(type, array, fill)(__stl_t(type, array) * arr, type value);                                               \
    int __stl_fn(type, array, find)(__stl_t(type, array) * arr, type value);                                                \
    int __stl_fn(type, array, find_cmp)(__stl_t(type, array) * arr, type value, bool (*cmp)(type a, type b));               \
    void __stl_fn(type, array, resize)(__stl_t(type, array) * arr, size_t lenght);                                          \
    size_t __stl_fn(type, array, count)(__stl_t(type, array) * arr, type value);                                            \
    size_t __stl_fn(type, array, count_cmp)(__stl_t(type, array) * arr, type value, bool (*cmp)(type a, type b));           \
    bool __stl_fn(type, array, all)(__stl_t(type, array) * arr, type value);                                                \
    bool __stl_fn(type, array, all_cmp)(__stl_t(type, array) * arr, type value, bool (*cmp)(type a, type b));               \
    void __stl_fn(type, array, join)(__stl_t(type, array) * a, __stl_t(type, array) * b, size_t lenght_a, size_t lenght_b); \
    void __stl_fn(type, array, reverse)(__stl_t(type, array) * arr);                                                        \
    void __stl_fn(type, array, free)(__stl_t(type, array) * arr);

#endif