#ifndef STL_QUEUE_H
#define STL_QUEUE_H

#include "../internal/stl_macros.h"
#include "../internal/slt_foreach_macro.h"

#ifndef CSTL_USE_RAW
#define queue(type) __stl_t(type, queue)

#define queue(type) __stl_t(type, queue)
#define queue_create(type) __stl_fn(type, queue, create)
#define queue_free(type) __stl_fn(type, queue, free)
#define queue_clear(type) __stl_fn(type, queue, clear)
#define queue_enqueue(type) __stl_fn(type, queue, enqueue)
#define queue_dequeue(type) __stl_fn(type, queue, dequeue)
#define queue_first(type) __stl_fn(type, queue, first)
#define queue_last(type) __stl_fn(type, queue, last)
#define queue_clone(type) __stl_fn(type, queue, clone)
#define queue_equal(type) __stl_fn(type, queue, equal)
#define queue_copy(type) __stl_fn(type, queue, copy)
#define queue_find(type) __stl_fn(type, queue, find)
#define queue_find_cmp(type) __stl_fn(type, queue, find_cmp)
#define queue_fill(type) __stl_fn(type, queue, fill)
#define queue_count(type) __stl_fn(type, queue, count)
#define queue_count_cmp(type) __stl_fn(type, queue, count_cmp)
#define queue_all(type) __stl_fn(type, queue, all)
#define queue_all_cmp(type) __stl_fn(type, queue, all_cmp)
#define queue_any(type) __stl_fn(type, queue, any)
#define queue_any_cmp(type) __stl_fn(type, queue, any_cmp)
#define queue_join(type) __stl_fn(type, queue, join)
#define queue_reverse(type) __stl_fn(type, queue, reverse)
#define queue_resize(type) __stl_fn(type, queue, resize)
#define queue_lenght(type) __stl_fn(type, queue, lenght)
#define queue_map(type) __stl_fn(type, queue, map)
#define queue_filter(type) __stl_fn(type, queue, filter)

#endif

#define stl_declare_queue_alias(type, alias) \
    typedef type alias;                      \
    stl_declare_queue(alias)

#define stl_declare_queue_for(...) call_macro_x_for_each(stl_declare_queue, __VA_ARGS__)
#define stl_declare_queue(type)                                                                                          \
    typedef struct                                                                                                       \
    {                                                                                                                    \
        type *buffer;                                                                                                    \
        size_t lenght;                                                                                                   \
        size_t count;                                                                                                    \
    } queue(type);                                                                                                       \
    void __stl_fn(type, queue, create)(__stl_t(type, queue) * arr, size_t lenght);                                       \
    void __stl_fn(type, queue, free)(__stl_t(type, queue) * arr);                                                        \
    void __stl_fn(type, queue, clear)(__stl_t(type, queue) * arr);                                                       \
    void __stl_fn(type, queue, enqueue)(__stl_t(type, queue) * arr, type value);                                         \
    type __stl_fn(type, queue, denqueue)(__stl_t(type, queue) * arr);                                                    \
    type __stl_fn(type, queue, first)(__stl_t(type, queue) * arr);                                                       \
    type __stl_fn(type, queue, last)(__stl_t(type, queue) * arr);                                                        \
    void __stl_fn(type, queue, copy)(__stl_t(type, queue) * arr, __stl_t(type, queue) * *out, size_t start, size_t end); \
    void __stl_fn(type, queue, clone)(__stl_t(type, queue) * arr, __stl_t(type, queue) * *out);                          \
    bool __stl_fn(type, queue, equal)(__stl_t(type, queue) * a, __stl_t(type, queue) * b);                               \
    void __stl_fn(type, queue, fill)(__stl_t(type, queue) * arr, type value);                                            \
    int __stl_fn(type, queue, find)(__stl_t(type, queue) * arr, type value);                                             \
    int __stl_fn(type, queue, find_cmp)(__stl_t(type, queue) * arr, type value, bool (*cmp)(type a, type b));            \
    void __stl_fn(type, queue, resize)(__stl_t(type, queue) * arr, size_t lenght);                                       \
    size_t __stl_fn(type, queue, count)(__stl_t(type, queue) * arr, type value);                                         \
    size_t __stl_fn(type, queue, count_cmp)(__stl_t(type, queue) * arr, type value, bool (*cmp)(type a, type b));        \
    bool __stl_fn(type, queue, all)(__stl_t(type, queue) * arr, type value);                                             \
    bool __stl_fn(type, queue, all_cmp)(__stl_t(type, queue) * arr, type value, bool (*cmp)(type a, type b));            \
    bool __stl_fn(type, queue, any)(__stl_t(type, queue) * arr, type value);                                             \
    bool __stl_fn(type, queue, any_cmp)(__stl_t(type, queue) * arr, type value, bool (*cmp)(type a, type b));            \
    void __stl_fn(type, queue, join)(__stl_t(type, queue) * a, __stl_t(type, queue) * b);                                \
    void __stl_fn(type, queue, reverse)(__stl_t(type, queue) * arr);                                                     \
    size_t __stl_fn(type, queue, lenght)(__stl_t(type, queue) * arr);                                                    \
    void __stl_fn(type, queue, map)(__stl_t(type, queue) * vec, type * *out, type(*map_fn)(type value, size_t index));   \
    void __stl_fn(type, queue, filter)(__stl_t(type, queue) * vec, type * *out, bool (*filter_fn)(type value, size_t index, type * filtered), size_t *out_len);

#endif