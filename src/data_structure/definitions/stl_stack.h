#ifndef STL_STACK_H
#define STL_STACK_H

#include "../internal/stl_macros.h"
#include "../internal/slt_foreach_macro.h"

#ifndef CSTL_USE_RAW
#define stack(type) __stl_t(type, stack)
#define stack_create(type) __stl_fn(type, stack, create)
#define stack_free(type) __stl_fn(type, stack, free)
#define stack_clear(type) __stl_fn(type, stack, clear)
#define stack_push(type) __stl_fn(type, stack, push)
#define stack_pop(type) __stl_fn(type, stack, pop)
#define stack_top(type) __stl_fn(type, stack, top)
#define stack_clone(type) __stl_fn(type, stack, clone)
#define stack_equal(type) __stl_fn(type, stack, equal)
#define stack_copy(type) __stl_fn(type, stack, copy)
#define stack_find(type) __stl_fn(type, stack, find)
#define stack_find_cmp(type) __stl_fn(type, stack, find_cmp)
#define stack_fill(type) __stl_fn(type, stack, fill)
#define stack_count(type) __stl_fn(type, stack, count)
#define stack_count_cmp(type) __stl_fn(type, stack, count_cmp)
#define stack_all(type) __stl_fn(type, stack, all)
#define stack_all_cmp(type) __stl_fn(type, stack, all_cmp)
#define stack_any(type) __stl_fn(type, stack, any)
#define stack_any_cmp(type) __stl_fn(type, stack, any_cmp)
#define stack_join(type) __stl_fn(type, stack, join)
#define stack_reverse(type) __stl_fn(type, stack, reverse)
#define stack_resize(type) __stl_fn(type, stack, resize)
#define stack_lenght(type) __stl_fn(type, stack, lenght)
#define stack_map(type) __stl_fn(type, stack, map)
#define stack_filter(type) __stl_fn(type, stack, filter)

#endif

#define stl_declare_stack_alias(type, alias) \
    typedef type alias;                      \
    stl_declare_stack(alias)

#define stl_declare_stack_for(...) call_macro_x_for_each(stl_declare_stack, __VA_ARGS__)
#define stl_declare_stack(type)                                                                                          \
    typedef struct                                                                                                       \
    {                                                                                                                    \
        type *buffer;                                                                                                    \
        size_t lenght;                                                                                                   \
        size_t count;                                                                                                    \
    } stack(type);                                                                                                       \
    void __stl_fn(type, stack, create)(__stl_t(type, stack) * arr, size_t lenght);                                       \
    void __stl_fn(type, stack, free)(__stl_t(type, stack) * arr);                                                        \
    void __stl_fn(type, stack, clear)(__stl_t(type, stack) * arr);                                                       \
    void __stl_fn(type, stack, push)(__stl_t(type, stack) * arr, type value);                                            \
    type __stl_fn(type, stack, pop)(__stl_t(type, stack) * arr);                                                         \
    type __stl_fn(type, stack, top)(__stl_t(type, stack) * arr);                                                         \
    void __stl_fn(type, stack, copy)(__stl_t(type, stack) * arr, __stl_t(type, stack) * *out, size_t start, size_t end); \
    void __stl_fn(type, stack, clone)(__stl_t(type, stack) * arr, __stl_t(type, stack) * *out);                          \
    bool __stl_fn(type, stack, equal)(__stl_t(type, stack) * a, __stl_t(type, stack) * b);                               \
    void __stl_fn(type, stack, fill)(__stl_t(type, stack) * arr, type value);                                            \
    int __stl_fn(type, stack, find)(__stl_t(type, stack) * arr, type value);                                             \
    int __stl_fn(type, stack, find_cmp)(__stl_t(type, stack) * arr, type value, bool (*cmp)(type a, type b));            \
    void __stl_fn(type, stack, resize)(__stl_t(type, stack) * arr, size_t lenght);                                       \
    size_t __stl_fn(type, stack, count)(__stl_t(type, stack) * arr, type value);                                         \
    size_t __stl_fn(type, stack, count_cmp)(__stl_t(type, stack) * arr, type value, bool (*cmp)(type a, type b));        \
    bool __stl_fn(type, stack, all)(__stl_t(type, stack) * arr, type value);                                             \
    bool __stl_fn(type, stack, all_cmp)(__stl_t(type, stack) * arr, type value, bool (*cmp)(type a, type b));            \
    bool __stl_fn(type, stack, any)(__stl_t(type, stack) * arr, type value);                                             \
    bool __stl_fn(type, stack, any_cmp)(__stl_t(type, stack) * arr, type value, bool (*cmp)(type a, type b));            \
    void __stl_fn(type, stack, join)(__stl_t(type, stack) * a, __stl_t(type, stack) * b);                                \
    void __stl_fn(type, stack, reverse)(__stl_t(type, stack) * arr);                                                     \
    size_t __stl_fn(type, stack, lenght)(__stl_t(type, stack) * arr);                                                    \
    void __stl_fn(type, stack, map)(__stl_t(type, stack) * vec, type * *out, type(*map_fn)(type value, size_t index));   \
    void __stl_fn(type, stack, filter)(__stl_t(type, stack) * vec, type * *out, bool (*filter_fn)(type value, size_t index, type * filtered), size_t *out_len);
#endif