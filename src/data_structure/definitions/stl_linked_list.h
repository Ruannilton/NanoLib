#ifndef STL_LINKED_LIST_H
#define STL_LINKED_LIST_H

#include "../internal/stl_macros.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdbool.h"

#ifndef CSTL_USE_RAW
#define linked_list(type) __stl_t(type, linked_list)

#define linked_list_create(type) __stl_fn(type, linked_list, create)
#define linked_list_insert(type) __stl_fn(type, linked_list, insert)
#define linked_list_set(type) __stl_fn(type, linked_list, set)
#define linked_list_add(type) __stl_fn(type, linked_list, add)
#define linked_list_remove(type) __stl_fn(type, linked_list, remove)
#define linked_list_get(type) __stl_fn(type, linked_list, get)
#define linked_list_first(type) __stl_fn(type, linked_list, first)
#define linked_list_copy(type) __stl_fn(type, linked_list, copy)
#define linked_list_clone(type) __stl_fn(type, linked_list, clone)
#define linked_list_equal(type) __stl_fn(type, linked_list, equal)
#define linked_list_fill(type) __stl_fn(type, linked_list, fill)
#define linked_list_find(type) __stl_fn(type, linked_list, find)
#define linked_list_find_cmp(type) __stl_fn(type, linked_list, find_cmp)
#define linked_list_count(type) __stl_fn(type, linked_list, count)
#define linked_list_count_cmp(type) __stl_fn(type, linked_list, count_cmp)
#define linked_list_all(type) __stl_fn(type, linked_list, all)
#define linked_list_all_cmp(type) __stl_fn(type, linked_list, all_cmp)
#define linked_list_join(type) __stl_fn(type, linked_list, join)
#define linked_list_reverse(type) __stl_fn(type, linked_list, reverse)
#define linked_list_free(type) __stl_fn(type, linked_list, free)
#define linked_list_lenght(type) __stl_fn(type, linked_list, lenght)
#define linked_list_any(type) __stl_fn(type, linked_list, any)
#define linked_list_any_cmp(type) __stl_fn(type, linked_list, any_cmp)
#define linked_list_last(type) __stl_fn(type, linked_list, last)
#define linked_list_map(type) __stl_fn(type, linked_list, map)
#define linked_list_filter(type) __stl_fn(type, linked_list, filter)
#endif

#define stl_declare_linked_list_alias(type, alias) \
    typedef type alias;                            \
    stl_declare_linked_list(type);

#define stl_declare_linked_list_for(...) call_macro_x_for_each(stl_declare_linked_list, __VA_ARGS__)

#define stl_declare_linked_list(type)                                                                                                                                     \
    typedef struct __stl_t(type, linked_list_node)                                                                                                                        \
    {                                                                                                                                                                     \
        struct __stl_t(type, linked_list_node) * pnext;                                                                                                                   \
        type value;                                                                                                                                                       \
    }                                                                                                                                                                     \
    __stl_t(type, linked_list_node_t);                                                                                                                                    \
    typedef struct                                                                                                                                                        \
    {                                                                                                                                                                     \
        __stl_t(type, linked_list_node_t) * first;                                                                                                                        \
        __stl_t(type, linked_list_node_t) * last;                                                                                                                         \
        size_t count;                                                                                                                                                     \
    } __stl_t(type, linked_list);                                                                                                                                         \
                                                                                                                                                                          \
    void __stl_fn(type, linked_list, create)(__stl_t(type, linked_list) * arr);                                                                                           \
    void __stl_fn(type, linked_list, insert)(__stl_t(type, linked_list) * arr, type value, size_t index);                                                                 \
    void __stl_fn(type, linked_list, set)(__stl_t(type, linked_list) * arr, type value, size_t index);                                                                    \
    void __stl_fn(type, linked_list, add)(__stl_t(type, linked_list) * arr, type value);                                                                                  \
    type __stl_fn(type, linked_list, remove)(__stl_t(type, linked_list) * arr, size_t index);                                                                             \
    type __stl_fn(type, linked_list, get)(__stl_t(type, linked_list) * arr, size_t index);                                                                                \
    type __stl_fn(type, linked_list, first)(__stl_t(type, linked_list) * arr);                                                                                            \
    void __stl_fn(type, linked_list, copy)(__stl_t(type, linked_list) * arr, __stl_t(type, linked_list) * *out, size_t start, size_t end);                                \
    void __stl_fn(type, linked_list, clone)(__stl_t(type, linked_list) * arr, __stl_t(type, linked_list) * *out);                                                         \
    bool __stl_fn(type, linked_list, equal)(__stl_t(type, linked_list) * a, __stl_t(type, linked_list) * b);                                                              \
    void __stl_fn(type, linked_list, fill)(__stl_t(type, linked_list) * arr, type value);                                                                                 \
    int __stl_fn(type, linked_list, find)(__stl_t(type, linked_list) * arr, type value);                                                                                  \
    int __stl_fn(type, linked_list, find_cmp)(__stl_t(type, linked_list) * arr, type value, bool (*cmp)(type a, type b));                                                 \
    size_t __stl_fn(type, linked_list, count)(__stl_t(type, linked_list) * arr, type value);                                                                              \
    size_t __stl_fn(type, linked_list, count_cmp)(__stl_t(type, linked_list) * arr, type value, bool (*cmp)(type a, type b));                                             \
    bool __stl_fn(type, linked_list, all)(__stl_t(type, linked_list) * arr, type value);                                                                                  \
    bool __stl_fn(type, linked_list, all_cmp)(__stl_t(type, linked_list) * arr, type value, bool (*cmp)(type a, type b));                                                 \
    void __stl_fn(type, linked_list, join)(__stl_t(type, linked_list) * a, __stl_t(type, linked_list) * b);                                                               \
    void __stl_fn(type, linked_list, reverse)(__stl_t(type, linked_list) * arr);                                                                                          \
    void __stl_fn(type, linked_list, free)(__stl_t(type, linked_list) * arr, void (*custom_free)(type a));                                                                \
    size_t __stl_fn(type, linked_list, lenght)(__stl_t(type, linked_list) * arr);                                                                                         \
    bool __stl_fn(type, linked_list, any)(__stl_t(type, linked_list) * arr, type value);                                                                                  \
    bool __stl_fn(type, linked_list, any_cmp)(__stl_t(type, linked_list) * arr, type value, bool (*cmp)(type a, type b));                                                 \
    void __stl_fn(type, linked_list, map)(__stl_t(type, linked_list) * arr, __stl_t(type, linked_list) * *out, type(*map)(type value, size_t index));                     \
    void __stl_fn(type, linked_list, filter)(__stl_t(type, linked_list) * arr, __stl_t(type, linked_list) * *out, type(*filter)(type value, size_t index, int8_t * add)); \
    type __stl_fn(type, linked_list, last)(__stl_t(type, linked_list) * arr);

#define linked_list_foreach(type, p_list, code, ...) macro_override(dummy, ##__VA_ARGS__, _4, _3, ___i___linked_list_foreach_2, ___i___linked_list_foreach_1, ___i___linked_list_foreach_0)(type, p_list, code, ##__VA_ARGS__)

#define ___i___linked_list_foreach_0(type, p_list, code)                           \
    {                                                                              \
        __stl_t(type, linked_list_node_t) *___c_i_cstl_loop_pnext = p_list->first; \
        for (size_t cstl_index = 0; cstl_index < p_list->count; cstl_index++)      \
        {                                                                          \
            type cstl_value = ___c_i_cstl_loop_pnext->value;                       \
            code;                                                                  \
            ___c_i_cstl_loop_pnext = ___c_i_cstl_loop_pnext->pnext;                \
        }                                                                          \
    }

#define ___i___linked_list_foreach_1(type, p_list, code, i_name)                   \
    {                                                                              \
        __stl_t(type, linked_list_node_t) *___c_i_cstl_loop_pnext = p_list->first; \
        for (size_t i_name = 0; i_name < p_list->count; i_name++)                  \
        {                                                                          \
            type cstl_value = ___c_i_cstl_loop_pnext->value;                       \
            code;                                                                  \
            ___c_i_cstl_loop_pnext = ___c_i_cstl_loop_pnext->pnext;                \
        }                                                                          \
    }

#define ___i___linked_list_foreach_2(type, p_list, code, i_name, v_name)           \
    {                                                                              \
        __stl_t(type, linked_list_node_t) *___c_i_cstl_loop_pnext = p_list->first; \
        for (size_t i_name = 0; i_name < p_list->count; i_name++)                  \
        {                                                                          \
            type v_name = ___c_i_cstl_loop_pnext->value;                           \
            code;                                                                  \
            ___c_i_cstl_loop_pnext = ___c_i_cstl_loop_pnext->pnext;                \
        }                                                                          \
    }
#endif