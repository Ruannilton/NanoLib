#ifndef _STL_CORE_H
#define _STL_CORE_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define __prefix stl_
#define __base_name core

#define _____concat2(A, B) A##B
#define _____concat(A, B) _____concat2(A, B)

#define __stl_fn(type, name, fn) _____concat(_____concat(_____concat(__prefix, _____concat(_____concat(name, _), type)), _), fn)
#define __stl_t(type, name) _____concat(_____concat(_____concat(name, _), type), _t)

#define __unique(name) _____concat(name, _____concat(_____concat(_stl_core_, __LINE__), __COUNTER__))

#define stl_declare_alias(type, alias) \
    typedef type alias;                \
    stl_declare(alias)

#define stl_declare_iterator(type)                                                        \
    typedef struct                                                                        \
    {                                                                                     \
        size_t current;                                                                   \
        size_t lenght;                                                                    \
        type *buffer;                                                                     \
    } __stl_t(type, it);                                                                  \
    __stl_t(type, it) __stl_fn(type, __base_name, it_init)(type * buffer, size_t lenght); \
    const type *__stl_fn(type, __base_name, it_next)(__stl_t(type, it) * it);

#define stl_implement_iterator(type)                                                     \
    __stl_t(type, it) __stl_fn(type, __base_name, it_init)(type * buffer, size_t lenght) \
    {                                                                                    \
        return (__stl_t(type, it)){.current = 0, .lenght = lenght, .buffer = buffer};    \
    }                                                                                    \
    const type *__stl_fn(type, __base_name, it_next)(__stl_t(type, it) * it)             \
    {                                                                                    \
        if (it->current < it->lenght)                                                    \
        {                                                                                \
            type *v = &(it->buffer[it->current]);                                        \
            it->current++;                                                               \
            return v;                                                                    \
        }                                                                                \
        return NULL;                                                                     \
    }

#define foreach(type, var, it) \
    for (const type *var = NULL; (var = __stl_fn(type, __base_name, it_next)(&it)) != NULL;)

#define stl_declare(type)                                                                                                 \
    void __stl_fn(type, __base_name, create)(type * *buffer, size_t lenght);                                              \
    void __stl_fn(type, __base_name, desloc)(type * buffer, size_t lenght, size_t from, int steps);                       \
    void __stl_fn(type, __base_name, grow)(type * *buffer, size_t * lenght);                                              \
    void __stl_fn(type, __base_name, push_back)(type * buffer, type value, size_t * index);                               \
    void __stl_fn(type, __base_name, insert)(type * buffer, type value, size_t index, size_t lenght);                     \
    void __stl_fn(type, __base_name, push_front)(type * buffer, type value, size_t lenght);                               \
    void __stl_fn(type, __base_name, set)(type * buffer, type value, size_t index);                                       \
    void __stl_fn(type, __base_name, pop_front)(type * buffer, size_t lenght);                                            \
    void __stl_fn(type, __base_name, remove)(type * buffer, size_t index, size_t lenght);                                 \
    type __stl_fn(type, __base_name, get)(type * buffer, size_t index);                                                   \
    type __stl_fn(type, __base_name, first)(type * buffer);                                                               \
    void __stl_fn(type, __base_name, copy)(type * buffer, type * *out, size_t start, size_t end);                         \
    void __stl_fn(type, __base_name, clone)(type * buffer, type * *out, size_t lenght);                                   \
    bool __stl_fn(type, __base_name, equal)(type * a, type * b, size_t lenght);                                           \
    void __stl_fn(type, __base_name, fill)(type * buffer, type value, size_t lenght);                                     \
    bool __stl_fn(type, __base_name, find)(type * buffer, type value, size_t lenght);                                     \
    bool __stl_fn(type, __base_name, find_cmp)(type * buffer, type value, size_t lenght, bool (*cmp)(type a, type b));    \
    void __stl_fn(type, __base_name, resize)(type * *buffer, size_t lenght);                                              \
    size_t __stl_fn(type, __base_name, count)(type * buffer, type value, size_t lenght);                                  \
    size_t __stl_fn(type, __base_name, count_cmp)(type * buffer, type value, size_t lenght, bool (*cmp)(type a, type b)); \
    bool __stl_fn(type, __base_name, all)(type * buffer, type value, size_t lenght);                                      \
    bool __stl_fn(type, __base_name, all_cmp)(type * buffer, type value, size_t lenght, bool (*cmp)(type a, type b));     \
    void __stl_fn(type, __base_name, join)(type * *a, type * b, size_t lenght_a, size_t lenght_b);                        \
    void __stl_fn(type, __base_name, reverse)(type * buffer, size_t lenght);

// void buffer_where(uintptr_t buffer, size_t lenght, size_t data_size, bool (*condition)(void *data, size_t data_size), void (*action)(void *data, size_t data_size));

// void buffer_map(uintptr_t buffer, uintptr_t *out, size_t lenght, size_t data_size, void (*action)(void *data, size_t data_size));

// void buffer_foreach(uintptr_t buffer, size_t lenght, size_t data_size, void (*action)(const void *data, size_t data_size));

// void buffer_zip(uintptr_t a, uintptr_t b, uintptr_t *out, size_t lenght, size_t data_size_a, size_t data_size_b, size_t *data_size_out);
#define stl_declare_alias(type, alias) \
    typedef type alias;                \
    stl_declare(alias)

#define stl_implement(type)                                                                                              \
    stl_declare(type);                                                                                                   \
    void __stl_fn(type, __base_name, create)(type * *buffer, size_t lenght)                                              \
    {                                                                                                                    \
        *buffer = malloc(sizeof(type) * lenght);                                                                         \
    }                                                                                                                    \
    void __stl_fn(type, __base_name, desloc)(type * buffer, size_t lenght, size_t from, int steps)                       \
    {                                                                                                                    \
        if (steps > 0)                                                                                                   \
        {                                                                                                                \
            size_t mv_size = ((lenght - from) - steps) * sizeof(type);                                                   \
            size_t index_to = from + steps;                                                                              \
            if (mv_size > 0 && index_to < lenght)                                                                        \
            {                                                                                                            \
                void *pfrom = (void *)(&buffer[from]);                                                                   \
                void *pto = (void *)(&buffer[index_to]);                                                                 \
                memmove(pto, pfrom, mv_size);                                                                            \
            }                                                                                                            \
        }                                                                                                                \
        else                                                                                                             \
        {                                                                                                                \
            uint64_t mv_size = (from + steps) * sizeof(type);                                                            \
            if (mv_size > 0)                                                                                             \
            {                                                                                                            \
                void *pfrom = (void *)(buffer[steps * -1]);                                                              \
                void *pto = (void *)(buffer);                                                                            \
                memmove(pto, pfrom, mv_size);                                                                            \
            }                                                                                                            \
        }                                                                                                                \
    }                                                                                                                    \
    void __stl_fn(type, __base_name, grow)(type * *buffer, size_t * lenght)                                              \
    {                                                                                                                    \
        size_t new_len = (*lenght) * 1.5f;                                                                               \
        void *new_ptr = realloc(*buffer, new_len * sizeof(type));                                                        \
        if (new_ptr)                                                                                                     \
        {                                                                                                                \
            *buffer = new_ptr;                                                                                           \
            *lenght = new_len;                                                                                           \
        }                                                                                                                \
    }                                                                                                                    \
    void __stl_fn(type, __base_name, push_back)(type * buffer, type value, size_t * index)                               \
    {                                                                                                                    \
        buffer[(*index)] = value;                                                                                        \
        *index = (*index) + 1;                                                                                           \
    }                                                                                                                    \
    void __stl_fn(type, __base_name, insert)(type * buffer, type value, size_t index, size_t lenght)                     \
    {                                                                                                                    \
        __stl_fn(type, __base_name, desloc)(buffer, lenght, index, 1);                                                   \
        buffer[index] = value;                                                                                           \
    }                                                                                                                    \
    void __stl_fn(type, __base_name, push_front)(type * buffer, type value, size_t lenght)                               \
    {                                                                                                                    \
        __stl_fn(type, __base_name, insert)(buffer, value, 0, lenght);                                                   \
    }                                                                                                                    \
    void __stl_fn(type, __base_name, set)(type * buffer, type value, size_t index)                                       \
    {                                                                                                                    \
        buffer[index] = value;                                                                                           \
    }                                                                                                                    \
    void __stl_fn(type, __base_name, pop_front)(type * buffer, size_t lenght)                                            \
    {                                                                                                                    \
        __stl_fn(type, __base_name, desloc)(buffer, lenght, -1, -1);                                                     \
    }                                                                                                                    \
    void __stl_fn(type, __base_name, remove)(type * buffer, size_t index, size_t lenght)                                 \
    {                                                                                                                    \
        if (index != lenght - 1)                                                                                         \
        {                                                                                                                \
            size_t mv_size = ((lenght - 1) - index) * sizeof(type);                                                      \
            void *pfrom = (void *)(&buffer[index + 1]);                                                                  \
            void *pto = (void *)(&buffer[index]);                                                                        \
            memmove(pto, pfrom, mv_size);                                                                                \
        }                                                                                                                \
    }                                                                                                                    \
    type __stl_fn(type, __base_name, get)(type * buffer, size_t index)                                                   \
    {                                                                                                                    \
        return buffer[index];                                                                                            \
    }                                                                                                                    \
    type __stl_fn(type, __base_name, first)(type * buffer)                                                               \
    {                                                                                                                    \
        return buffer[0];                                                                                                \
    }                                                                                                                    \
    void __stl_fn(type, __base_name, copy)(type * buffer, type * *out, size_t start, size_t end)                         \
    {                                                                                                                    \
        size_t len = end - start;                                                                                        \
        *out = (type *)malloc(len * sizeof(type));                                                                       \
        memcpy(*out, &buffer[start], len);                                                                               \
    }                                                                                                                    \
    void __stl_fn(type, __base_name, clone)(type * buffer, type * *out, size_t lenght)                                   \
    {                                                                                                                    \
        *out = (type *)malloc(lenght * sizeof(type));                                                                    \
        memcpy(*out, buffer, lenght * sizeof(type));                                                                     \
    }                                                                                                                    \
    bool __stl_fn(type, __base_name, equal)(type * a, type * b, size_t lenght)                                           \
    {                                                                                                                    \
        return memcmp(a, b, lenght * sizeof(type)) == 0;                                                                 \
    }                                                                                                                    \
    void __stl_fn(type, __base_name, fill)(type * buffer, type value, size_t lenght)                                     \
    {                                                                                                                    \
        for (size_t i = 0; i < lenght; i++)                                                                              \
        {                                                                                                                \
            buffer[i] = value;                                                                                           \
        }                                                                                                                \
    }                                                                                                                    \
    bool __stl_fn(type, __base_name, find)(type * buffer, type value, size_t lenght)                                     \
    {                                                                                                                    \
        for (uint64_t i = 0; i < lenght; i++)                                                                            \
        {                                                                                                                \
            if (buffer[i] == value)                                                                                      \
                return i;                                                                                                \
        }                                                                                                                \
    }                                                                                                                    \
    bool __stl_fn(type, __base_name, find_cmp)(type * buffer, type value, size_t lenght, bool (*cmp)(type a, type b))    \
    {                                                                                                                    \
        for (uint64_t i = 0; i < lenght; i++)                                                                            \
        {                                                                                                                \
            if ((*cmp)(buffer[i], value) == 0)                                                                           \
                return i;                                                                                                \
        }                                                                                                                \
    }                                                                                                                    \
    void __stl_fn(type, __base_name, resize)(type * *buffer, size_t lenght)                                              \
    {                                                                                                                    \
        void *new_ptr = realloc(*buffer, lenght * sizeof(type));                                                         \
        if (new_ptr)                                                                                                     \
            *buffer = new_ptr;                                                                                           \
    }                                                                                                                    \
    size_t __stl_fn(type, __base_name, count)(type * buffer, type value, size_t lenght)                                  \
    {                                                                                                                    \
        size_t count = 0;                                                                                                \
        for (size_t i = 0; i < lenght; i++)                                                                              \
        {                                                                                                                \
            if (memcmp((void *)&buffer[i], (void *)(&value), sizeof(value)) == 0)                                        \
            {                                                                                                            \
                count++;                                                                                                 \
            }                                                                                                            \
        }                                                                                                                \
        return count;                                                                                                    \
    }                                                                                                                    \
    size_t __stl_fn(type, __base_name, count_cmp)(type * buffer, type value, size_t lenght, bool (*cmp)(type a, type b)) \
    {                                                                                                                    \
        size_t count = 0;                                                                                                \
        for (size_t i = 0; i < lenght; i++)                                                                              \
        {                                                                                                                \
            if ((*cmp)(buffer[i], value) == true)                                                                        \
            {                                                                                                            \
                count++;                                                                                                 \
            }                                                                                                            \
        }                                                                                                                \
        return count;                                                                                                    \
    }                                                                                                                    \
    bool __stl_fn(type, __base_name, all)(type * buffer, type value, size_t lenght)                                      \
    {                                                                                                                    \
        for (uint64_t i = 0; i < lenght; i++)                                                                            \
        {                                                                                                                \
            if (!memcmp((void *)&buffer[i], (void *)(&value), sizeof(type)) == 0)                                        \
            {                                                                                                            \
                return false;                                                                                            \
            }                                                                                                            \
        }                                                                                                                \
        return true;                                                                                                     \
    }                                                                                                                    \
    bool __stl_fn(type, __base_name, all_cmp)(type * buffer, type value, size_t lenght, bool (*cmp)(type a, type b))     \
    {                                                                                                                    \
        for (uint64_t i = 0; i < lenght; i++)                                                                            \
        {                                                                                                                \
            if (!(*cmp)(buffer[i], value) == 0)                                                                          \
            {                                                                                                            \
                return false;                                                                                            \
            }                                                                                                            \
        }                                                                                                                \
        return true;                                                                                                     \
    }                                                                                                                    \
    void __stl_fn(type, __base_name, join)(type * *a, type * b, size_t lenght_a, size_t lenght_b)                        \
    {                                                                                                                    \
        size_t new_size = sizeof(type) * (lenght_a + lenght_b);                                                          \
        void *new_ptr = realloc(*a, new_size);                                                                           \
        if (new_ptr)                                                                                                     \
        {                                                                                                                \
            *a = new_ptr;                                                                                                \
            memcpy((void *)((uintptr_t)(*a) + (sizeof(type) * lenght_a)), b, (lenght_b * sizeof(type)));                 \
        }                                                                                                                \
    }                                                                                                                    \
    void __stl_fn(type, __base_name, reverse)(type * buffer, size_t lenght)                                              \
    {                                                                                                                    \
        size_t start = 0;                                                                                                \
        size_t end = lenght - 1;                                                                                         \
                                                                                                                         \
        while (start < end)                                                                                              \
        {                                                                                                                \
            type tmp = buffer[start];                                                                                    \
            buffer[start] = buffer[end];                                                                                 \
            buffer[end] = tmp;                                                                                           \
            start++;                                                                                                     \
            end--;                                                                                                       \
        }                                                                                                                \
    }
#endif