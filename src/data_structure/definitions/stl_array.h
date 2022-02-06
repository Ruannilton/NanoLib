#ifndef STL_ARRAY_H
#define STL_ARRAY_H

#include "../internal/stl_macros.h"
#include "../internal/slt_foreach_macro.h"

#ifndef CSTL_USE_RAW
#define array(type) __stl_t(type, array)

#define array_create(type) __stl_fn(type, array, create)
#define array_desloc(type) __stl_fn(type, array, desloc)
#define array_insert(type) __stl_fn(type, array, insert)
#define array_set(type) __stl_fn(type, array, set)
#define array_remove(type) __stl_fn(type, array, remove)
#define array_get(type) __stl_fn(type, array, get)
#define array_first(type) __stl_fn(type, array, first)
#define array_last(type) __stl_fn(type, array, last)
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
#define array_any(type) __stl_fn(type, array, any)
#define array_any_cmp(type) __stl_fn(type, array, any_cmp)
#define array_join(type) __stl_fn(type, array, join)
#define array_reverse(type) __stl_fn(type, array, reverse)
#define array_free(type) __stl_fn(type, array, free)
#define array_lenght(type) __stl_fn(type, array, lenght)
#define array_map(type) __stl_fn(type, array, map)
#define array_filter(type) __stl_fn(type, array, filter)
#endif

#define stl_declare_array_alias(type, alias) \
    typedef type alias;                      \
    stl_declare_array(alias)

#define stl_declare_array_for(...) call_macro_x_for_each(stl_declare_array, __VA_ARGS__)
#define stl_declare_array(type)                                                                                        \
    typedef struct                                                                                                     \
    {                                                                                                                  \
        type *buffer;                                                                                                  \
        size_t lenght;                                                                                                 \
    } array(type);                                                                                                     \
                                                                                                                       \
    void __stl_fn(type, array, create)(__stl_t(type, array) * arr, size_t lenght);                                     \
    void __stl_fn(type, array, desloc)(__stl_t(type, array) * arr, size_t from, int steps);                            \
    void __stl_fn(type, array, insert)(__stl_t(type, array) * arr, type value, size_t index);                          \
    void __stl_fn(type, array, set)(__stl_t(type, array) * arr, type value, size_t index);                             \
    void __stl_fn(type, array, remove)(__stl_t(type, array) * arr, size_t index);                                      \
    type __stl_fn(type, array, get)(__stl_t(type, array) * arr, size_t index);                                         \
    type __stl_fn(type, array, first)(__stl_t(type, array) * arr);                                                     \
    type __stl_fn(type, array, last)(__stl_t(type, array) * arr);                                                      \
    void __stl_fn(type, array, copy)(__stl_t(type, array) * arr, type * *out, size_t start, size_t end);               \
    void __stl_fn(type, array, clone)(__stl_t(type, array) * arr, type * *out);                                        \
    bool __stl_fn(type, array, equal)(__stl_t(type, array) * a, __stl_t(type, array) * b);                             \
    void __stl_fn(type, array, fill)(__stl_t(type, array) * arr, type value);                                          \
    int __stl_fn(type, array, find)(__stl_t(type, array) * arr, type value);                                           \
    int __stl_fn(type, array, find_cmp)(__stl_t(type, array) * arr, type value, bool (*cmp)(type a, type b));          \
    void __stl_fn(type, array, resize)(__stl_t(type, array) * arr, size_t lenght);                                     \
    size_t __stl_fn(type, array, count)(__stl_t(type, array) * arr, type value);                                       \
    size_t __stl_fn(type, array, count_cmp)(__stl_t(type, array) * arr, type value, bool (*cmp)(type a, type b));      \
    bool __stl_fn(type, array, all)(__stl_t(type, array) * arr, type value);                                           \
    bool __stl_fn(type, array, all_cmp)(__stl_t(type, array) * arr, type value, bool (*cmp)(type a, type b));          \
    bool __stl_fn(type, array, any)(__stl_t(type, array) * arr, type value);                                           \
    bool __stl_fn(type, array, any_cmp)(__stl_t(type, array) * arr, type value, bool (*cmp)(type a, type b));          \
    void __stl_fn(type, array, join)(__stl_t(type, array) * a, __stl_t(type, array) * b);                              \
    void __stl_fn(type, array, reverse)(__stl_t(type, array) * arr);                                                   \
    void __stl_fn(type, array, free)(__stl_t(type, array) * arr);                                                      \
    size_t __stl_fn(type, array, lenght)(__stl_t(type, array) * arr);                                                  \
    void __stl_fn(type, array, map)(__stl_t(type, array) * arr, type * *out, type(*map_fn)(type value, size_t index)); \
    void __stl_fn(type, array, filter)(__stl_t(type, array) * arr, type * *out, bool (*filter_fn)(type value, size_t index, type * filtered), size_t *out_len);

#define array_foreach(type, p_arr, code, ...) macro_override(dummy, ##__VA_ARGS__, _4, _3, ___i___array_foreach_2, ___i___array_foreach_1, ___i___array_foreach_0)(type, p_arr, code, ##__VA_ARGS__)

#define ___i___array_foreach_0(type, p_arr, code)                             \
    {                                                                         \
        for (size_t cstl_index = 0; cstl_index < arr->lenght; cstl_index++)   \
        {                                                                     \
            type castl_value = __stl_fn(type, array, get)(p_arr, cstl_index); \
            code                                                              \
        }                                                                     \
    }

#define ___i___array_foreach_1(type, p_arr, code, i_name)                 \
    {                                                                     \
        for (size_t i_name = 0; i_name < arr->lenght; i_name++)           \
        {                                                                 \
            type castl_value = __stl_fn(type, array, get)(p_arr, i_name); \
            code                                                          \
        }                                                                 \
    }

#define ___i___array_foreach_2(type, p_arr, code, i_name, v_name)    \
    {                                                                \
        for (size_t i_name = 0; i_name < arr->lenght; i_name++)      \
        {                                                            \
            type v_name = __stl_fn(type, array, get)(p_arr, i_name); \
            code                                                     \
        }                                                            \
    }
#endif