#ifndef STL_VECTOR_H
#define STL_VECTOR_H

#include "../internal/stl_macros.h"

#ifndef CSTL_USE_RAW
#define vector(type) __stl_t(type, vector)

#define vector_create(type) __stl_fn(type, vector, create)
#define vector_desloc(type) __stl_fn(type, vector, desloc)
#define vector_insert(type) __stl_fn(type, vector, insert)
#define vector_set(type) __stl_fn(type, vector, set)
#define vector_remove(type) __stl_fn(type, vector, remove)
#define vector_get(type) __stl_fn(type, vector, get)
#define vector_first(type) __stl_fn(type, vector, first)
#define vector_last(type) __stl_fn(type, vector, last)
#define vector_push_front(type) __stl_fn(type, vector, push_front)
#define vector_push_back(type) __stl_fn(type, vector, push_back)
#define vector_pop_front(type) __stl_fn(type, vector, pop_front)
#define vector_pop_back(type) __stl_fn(type, vector, pop_back)
#define vector_copy(type) __stl_fn(type, vector, copy)
#define vector_clone(type) __stl_fn(type, vector, clone)
#define vector_equal(type) __stl_fn(type, vector, equal)
#define vector_fill(type) __stl_fn(type, vector, fill)
#define vector_find(type) __stl_fn(type, vector, find)
#define vector_find_cmp(type) __stl_fn(type, vector, find_cmp)
#define vector_resize(type) __stl_fn(type, vector, resize)
#define vector_count(type) __stl_fn(type, vector, count)
#define vector_count_cmp(type) __stl_fn(type, vector, count_cmp)
#define vector_all(type) __stl_fn(type, vector, all)
#define vector_all_cmp(type) __stl_fn(type, vector, all_cmp)
#define vector_any(type) __stl_fn(type, vector, any)
#define vector_any_cmp(type) __stl_fn(type, vector, any_cmp)
#define vector_join(type) __stl_fn(type, vector, join)
#define vector_reverse(type) __stl_fn(type, vector, reverse)
#define vector_free(type) __stl_fn(type, vector, free)
#define vector_lenght(type) __stl_fn(type, vector, lenght)
#define vector_map(type) __stl_fn(type, vector, map)
#define vector_filter(type) __stl_fn(type, vector, filter)
#endif

#define stl_declare_vector_alias(type) \
    typedef type alias;                \
    stl_declare_vector(type);

#define stl_declare_vector_for(...) call_macro_x_for_each(stl_declare_vector, __VA_ARGS__)

#define stl_declare_vector(type)                                                                                           \
    typedef struct                                                                                                         \
    {                                                                                                                      \
        type *buffer;                                                                                                      \
        size_t lenght;                                                                                                     \
        size_t count;                                                                                                      \
    } __stl_t(type, vector);                                                                                               \
                                                                                                                           \
    void __stl_fn(type, vector, create)(__stl_t(type, vector) * arr, size_t lenght);                                       \
    void __stl_fn(type, vector, desloc)(__stl_t(type, vector) * arr, size_t from, int steps);                              \
    void __stl_fn(type, vector, insert)(__stl_t(type, vector) * arr, type value, size_t index);                            \
    void __stl_fn(type, vector, set)(__stl_t(type, vector) * arr, type value, size_t index);                               \
    void __stl_fn(type, vector, remove)(__stl_t(type, vector) * arr, size_t index);                                        \
    type __stl_fn(type, vector, get)(__stl_t(type, vector) * arr, size_t index);                                           \
    type __stl_fn(type, vector, first)(__stl_t(type, vector) * arr);                                                       \
    type __stl_fn(type, vector, last)(__stl_t(type, vector) * arr);                                                        \
    void __stl_fn(type, vector, push_front)(__stl_t(type, vector) * arr, type value);                                      \
    void __stl_fn(type, vector, push_back)(__stl_t(type, vector) * arr, type value);                                       \
    void __stl_fn(type, vector, pop_front)(__stl_t(type, vector) * arr);                                                   \
    void __stl_fn(type, vector, pop_back)(__stl_t(type, vector) * arr);                                                    \
    void __stl_fn(type, vector, copy)(__stl_t(type, vector) * arr, __stl_t(type, vector) * out, size_t start, size_t end); \
    void __stl_fn(type, vector, clone)(__stl_t(type, vector) * arr, __stl_t(type, vector) * out);                          \
    bool __stl_fn(type, vector, equal)(__stl_t(type, vector) * a, __stl_t(type, vector) * b);                              \
    void __stl_fn(type, vector, fill)(__stl_t(type, vector) * arr, type value);                                            \
    int __stl_fn(type, vector, find)(__stl_t(type, vector) * arr, type value);                                             \
    int __stl_fn(type, vector, find_cmp)(__stl_t(type, vector) * arr, type value, bool (*cmp)(type a, type b));            \
    void __stl_fn(type, vector, resize)(__stl_t(type, vector) * arr, size_t lenght);                                       \
    size_t __stl_fn(type, vector, count)(__stl_t(type, vector) * arr, type value);                                         \
    size_t __stl_fn(type, vector, count_cmp)(__stl_t(type, vector) * arr, type value, bool (*cmp)(type a, type b));        \
    bool __stl_fn(type, vector, all)(__stl_t(type, vector) * arr, type value);                                             \
    bool __stl_fn(type, vector, all_cmp)(__stl_t(type, vector) * arr, type value, bool (*cmp)(type a, type b));            \
    bool __stl_fn(type, vector, any)(__stl_t(type, vector) * arr, type value);                                             \
    bool __stl_fn(type, vector, any_cmp)(__stl_t(type, vector) * arr, type value, bool (*cmp)(type a, type b));            \
    void __stl_fn(type, vector, join)(__stl_t(type, vector) * a, __stl_t(type, vector) * b);                               \
    void __stl_fn(type, vector, reverse)(__stl_t(type, vector) * arr);                                                     \
    void __stl_fn(type, vector, free)(__stl_t(type, vector) * arr);                                                        \
    size_t __stl_fn(type, vector, lenght)(__stl_t(type, vector) * arr);                                                    \
    void __stl_fn(type, vector, map)(__stl_t(type, vector) * vec, type * *out, type(*map_fn)(type value, size_t index));   \
    void __stl_fn(type, vector, filter)(__stl_t(type, vector) * vec, type * *out, bool (*filter_fn)(type value, size_t index, type * filtered), size_t *out_len);

#define vector_foreach(type, p_vec, code, ...) macro_override(dummy, ##__VA_ARGS__, _4, _3, ___i___vector_foreach_2, ___i___vector_foreach_1, ___i___vector_foreach_0)(type, p_vec, code, ##__VA_ARGS__)

#define ___i___vector_foreach_0(type, p_vec, code)                            \
    {                                                                         \
        for (size_t cstl_index = 0; cstl_index < p_vec->count; cstl_index++)  \
        {                                                                     \
            type cstl_value = __stl_fn(type, vector, get)(p_vec, cstl_index); \
            code                                                              \
        }                                                                     \
    }

#define ___i___vector_foreach_1(type, p_vec, code, i_name)                \
    {                                                                     \
        for (size_t i_name = 0; i_name < p_vec->count; i_name++)          \
        {                                                                 \
            type cstl_value = __stl_fn(type, vector, get)(p_vec, i_name); \
            code                                                          \
        }                                                                 \
    }

#define ___i___vector_foreach_2(type, p_vec, code, i_name, v_name)    \
    {                                                                 \
        for (size_t i_name = 0; i_name < p_vec->count; i_name++)      \
        {                                                             \
            type v_name = __stl_fn(type, vector, get)(p_vec, i_name); \
            code                                                      \
        }                                                             \
    }

#endif