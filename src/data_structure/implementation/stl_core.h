#ifndef STL_CORE_IMPL_H
#define STL_CORE_IMPL_H

#include "../internal/stl_macros.h"
#include "../internal/slt_foreach_macro.h"
#include <assert.h>

#define stl_implement_core_for(...) call_macro_x_for_each(stl_core_implement, __VA_ARGS__)

#define stl_core_declare(type)                                                                                                 \
    void __stl_fn(type, __base_name, create)(type * *buffer, size_t lenght);                                                   \
    void __stl_fn(type, __base_name, desloc)(type * buffer, size_t lenght, size_t from, int steps);                            \
    void __stl_fn(type, __base_name, grow)(type * *buffer, size_t * lenght);                                                   \
    void __stl_fn(type, __base_name, push_back)(type * buffer, type value, size_t * index);                                    \
    void __stl_fn(type, __base_name, insert)(type * buffer, type value, size_t index, size_t lenght);                          \
    void __stl_fn(type, __base_name, push_front)(type * buffer, type value, size_t lenght);                                    \
    void __stl_fn(type, __base_name, set)(type * buffer, type value, size_t index);                                            \
    void __stl_fn(type, __base_name, pop_front)(type * buffer, size_t lenght);                                                 \
    void __stl_fn(type, __base_name, remove)(type * buffer, size_t index, size_t lenght);                                      \
    type __stl_fn(type, __base_name, get)(type * buffer, size_t index);                                                        \
    type __stl_fn(type, __base_name, first)(type * buffer);                                                                    \
    type __stl_fn(type, __base_name, last)(type * buffer, size_t len);                                                         \
    void __stl_fn(type, __base_name, copy)(type * buffer, type * *out, size_t start, size_t end);                              \
    void __stl_fn(type, __base_name, clone)(type * buffer, type * *out, size_t lenght);                                        \
    bool __stl_fn(type, __base_name, equal)(type * a, type * b, size_t lenght);                                                \
    void __stl_fn(type, __base_name, fill)(type * buffer, type value, size_t lenght);                                          \
    int __stl_fn(type, __base_name, find)(type * buffer, type value, size_t lenght);                                           \
    int __stl_fn(type, __base_name, find_cmp)(type * buffer, type value, size_t lenght, bool (*cmp)(type a, type b));          \
    void __stl_fn(type, __base_name, resize)(type * *buffer, size_t lenght);                                                   \
    size_t __stl_fn(type, __base_name, count)(type * buffer, type value, size_t lenght);                                       \
    size_t __stl_fn(type, __base_name, count_cmp)(type * buffer, type value, size_t lenght, bool (*cmp)(type a, type b));      \
    bool __stl_fn(type, __base_name, all)(type * buffer, type value, size_t lenght);                                           \
    bool __stl_fn(type, __base_name, all_cmp)(type * buffer, type value, size_t lenght, bool (*cmp)(type a, type b));          \
    bool __stl_fn(type, __base_name, any)(type * buffer, type value, size_t lenght);                                           \
    bool __stl_fn(type, __base_name, any_cmp)(type * buffer, type value, size_t lenght, bool (*cmp)(type a, type b));          \
    void __stl_fn(type, __base_name, join)(type * *a, type * b, size_t lenght_a, size_t lenght_b);                             \
    void __stl_fn(type, __base_name, reverse)(type * buffer, size_t lenght);                                                   \
    void __stl_fn(type, __base_name, map)(type * buffer, type * *out, size_t lenght, type(*map_fn)(type value, size_t index)); \
    void __stl_fn(type, __base_name, filter)(type * buffer, type * *out, size_t lenght, bool (*filter_fn)(type value, size_t index, type * filtered), size_t *out_len);

#define stl_core_implement(type)                                                                                                                                       \
    void __stl_fn(type, __base_name, create)(type * *buffer, size_t lenght)                                                                                            \
    {                                                                                                                                                                  \
        assert(buffer != NULL);                                                                                                                                        \
        assert(lenght > 0);                                                                                                                                            \
        *buffer = cstl_malloc(sizeof(type) * lenght);                                                                                                                  \
    }                                                                                                                                                                  \
    void __stl_fn(type, __base_name, desloc)(type * buffer, size_t lenght, size_t from, int steps)                                                                     \
    {                                                                                                                                                                  \
        assert(buffer != NULL);                                                                                                                                        \
        assert(lenght > 0);                                                                                                                                            \
        assert(from + steps >= 0);                                                                                                                                     \
        check_buffer_overflow_acess(buffer, (sizeof(type) * (from + steps)));                                                                                          \
        if (steps > 0)                                                                                                                                                 \
        {                                                                                                                                                              \
            size_t mv_size = ((lenght - from) - steps) * sizeof(type);                                                                                                 \
            size_t index_to = from + steps;                                                                                                                            \
            if (mv_size > 0 && index_to < lenght)                                                                                                                      \
            {                                                                                                                                                          \
                void *pfrom = (void *)(&buffer[from]);                                                                                                                 \
                void *pto = (void *)(&buffer[index_to]);                                                                                                               \
                cstl_memmove(pto, pfrom, mv_size);                                                                                                                     \
            }                                                                                                                                                          \
        }                                                                                                                                                              \
        else                                                                                                                                                           \
        {                                                                                                                                                              \
            uint64_t new_index = from + steps;                                                                                                                         \
            uint64_t mv_size = (lenght - new_index) * sizeof(type);                                                                                                    \
            if (mv_size > 0)                                                                                                                                           \
            {                                                                                                                                                          \
                void *pfrom = (void *)(&buffer[from]);                                                                                                                 \
                void *pto = (void *)(&buffer[new_index]);                                                                                                              \
                cstl_memmove(pto, pfrom, mv_size);                                                                                                                     \
            }                                                                                                                                                          \
        }                                                                                                                                                              \
    }                                                                                                                                                                  \
    void __stl_fn(type, __base_name, grow)(type * *buffer, size_t * lenght)                                                                                            \
    {                                                                                                                                                                  \
        assert(buffer != NULL);                                                                                                                                        \
        assert(lenght > 0);                                                                                                                                            \
        size_t new_len = (*lenght) * 1.5f;                                                                                                                             \
        void *new_ptr = cstl_realloc(*buffer, new_len * sizeof(type));                                                                                                 \
        if (new_ptr)                                                                                                                                                   \
        {                                                                                                                                                              \
            *buffer = new_ptr;                                                                                                                                         \
            *lenght = new_len;                                                                                                                                         \
        }                                                                                                                                                              \
    }                                                                                                                                                                  \
    void __stl_fn(type, __base_name, push_back)(type * buffer, type value, size_t * index)                                                                             \
    {                                                                                                                                                                  \
        assert(index != NULL);                                                                                                                                         \
        assert(buffer != NULL);                                                                                                                                        \
        check_buffer_overflow_acess(buffer, (sizeof(type) * (*index)));                                                                                                \
        buffer[(*index)] = value;                                                                                                                                      \
        *index = (*index) + 1;                                                                                                                                         \
    }                                                                                                                                                                  \
    void __stl_fn(type, __base_name, insert)(type * buffer, type value, size_t index, size_t lenght)                                                                   \
    {                                                                                                                                                                  \
        assert(buffer != NULL);                                                                                                                                        \
        assert(lenght > 0);                                                                                                                                            \
        assert(index < lenght);                                                                                                                                        \
        check_buffer_overflow_acess(buffer, (sizeof(type) * index));                                                                                                   \
        __stl_fn(type, __base_name, desloc)(buffer, lenght, index, 1);                                                                                                 \
        buffer[index] = value;                                                                                                                                         \
    }                                                                                                                                                                  \
    void __stl_fn(type, __base_name, push_front)(type * buffer, type value, size_t lenght)                                                                             \
    {                                                                                                                                                                  \
        assert(buffer != NULL);                                                                                                                                        \
        assert(lenght > 0);                                                                                                                                            \
        __stl_fn(type, __base_name, insert)(buffer, value, 0, lenght);                                                                                                 \
    }                                                                                                                                                                  \
    void __stl_fn(type, __base_name, set)(type * buffer, type value, size_t index)                                                                                     \
    {                                                                                                                                                                  \
        assert(buffer != NULL);                                                                                                                                        \
        check_buffer_overflow_acess(buffer, (sizeof(type) * index));                                                                                                   \
        buffer[index] = value;                                                                                                                                         \
    }                                                                                                                                                                  \
    void __stl_fn(type, __base_name, pop_front)(type * buffer, size_t lenght)                                                                                          \
    {                                                                                                                                                                  \
        assert(buffer != NULL);                                                                                                                                        \
        assert(lenght > 0);                                                                                                                                            \
        __stl_fn(type, __base_name, desloc)(buffer, lenght, 1, -1);                                                                                                    \
    }                                                                                                                                                                  \
    void __stl_fn(type, __base_name, remove)(type * buffer, size_t index, size_t lenght)                                                                               \
    {                                                                                                                                                                  \
        assert(buffer != NULL);                                                                                                                                        \
        assert(lenght > 0);                                                                                                                                            \
        assert(index < lenght);                                                                                                                                        \
        check_buffer_overflow_acess(buffer, (sizeof(type) * index));                                                                                                   \
        if (index != lenght - 1)                                                                                                                                       \
        {                                                                                                                                                              \
            size_t mv_size = ((lenght - 1) - index) * sizeof(type);                                                                                                    \
            void *pfrom = (void *)(&buffer[index + 1]);                                                                                                                \
            void *pto = (void *)(&buffer[index]);                                                                                                                      \
            cstl_memmove(pto, pfrom, mv_size);                                                                                                                         \
        }                                                                                                                                                              \
    }                                                                                                                                                                  \
    type __stl_fn(type, __base_name, get)(type * buffer, size_t index)                                                                                                 \
    {                                                                                                                                                                  \
        assert(buffer != NULL);                                                                                                                                        \
        check_buffer_overflow_acess(buffer, (sizeof(type) * index));                                                                                                   \
        return buffer[index];                                                                                                                                          \
    }                                                                                                                                                                  \
    type __stl_fn(type, __base_name, first)(type * buffer)                                                                                                             \
    {                                                                                                                                                                  \
        assert(buffer != NULL);                                                                                                                                        \
        return buffer[0];                                                                                                                                              \
    }                                                                                                                                                                  \
    type __stl_fn(type, __base_name, last)(type * buffer, size_t len)                                                                                                  \
    {                                                                                                                                                                  \
        assert(buffer != NULL);                                                                                                                                        \
        assert(len > 0);                                                                                                                                               \
        check_buffer_overflow_acess(buffer, (sizeof(type) * (len - 1)));                                                                                               \
        return buffer[len - 1];                                                                                                                                        \
    }                                                                                                                                                                  \
    void __stl_fn(type, __base_name, copy)(type * buffer, type * *out, size_t start, size_t end)                                                                       \
    {                                                                                                                                                                  \
        assert(buffer != NULL);                                                                                                                                        \
        assert(out != NULL);                                                                                                                                           \
        assert(*out != NULL);                                                                                                                                          \
        assert(end > 0);                                                                                                                                               \
        size_t len = end - start;                                                                                                                                      \
        check_buffer_overflow_size(*out, len * sizeof(type));                                                                                                          \
        cstl_memcpy(*out, &buffer[start], len * sizeof(type));                                                                                                         \
    }                                                                                                                                                                  \
    void __stl_fn(type, __base_name, clone)(type * buffer, type * *out, size_t lenght)                                                                                 \
    {                                                                                                                                                                  \
        assert(buffer != NULL);                                                                                                                                        \
        assert(out != NULL);                                                                                                                                           \
        assert(*out != NULL);                                                                                                                                          \
        assert(lenght > 0);                                                                                                                                            \
        check_buffer_overflow_size(*out, lenght * sizeof(type));                                                                                                       \
        cstl_memcpy(*out, buffer, lenght * sizeof(type));                                                                                                              \
    }                                                                                                                                                                  \
    bool __stl_fn(type, __base_name, equal)(type * a, type * b, size_t lenght)                                                                                         \
    {                                                                                                                                                                  \
        assert(a != NULL);                                                                                                                                             \
        assert(b != NULL);                                                                                                                                             \
        assert(lenght > 0);                                                                                                                                            \
        check_buffer_overflow_size(a, lenght * sizeof(type));                                                                                                          \
        check_buffer_overflow_size(b, lenght * sizeof(type));                                                                                                          \
        return cstl_memcmp(a, b, lenght * sizeof(type)) == 0;                                                                                                          \
    }                                                                                                                                                                  \
    void __stl_fn(type, __base_name, fill)(type * buffer, type value, size_t lenght)                                                                                   \
    {                                                                                                                                                                  \
        assert(buffer != NULL);                                                                                                                                        \
        assert(lenght > 0);                                                                                                                                            \
        check_buffer_overflow_size(buffer, lenght * sizeof(type));                                                                                                     \
        for (size_t i = 0; i < lenght; i++)                                                                                                                            \
        {                                                                                                                                                              \
            check_buffer_overflow_acess(buffer, i * sizeof(type));                                                                                                     \
            buffer[i] = value;                                                                                                                                         \
        }                                                                                                                                                              \
    }                                                                                                                                                                  \
    int __stl_fn(type, __base_name, find)(type * buffer, type value, size_t lenght)                                                                                    \
    {                                                                                                                                                                  \
        assert(buffer != NULL);                                                                                                                                        \
        assert(lenght > 0);                                                                                                                                            \
        check_buffer_overflow_size(buffer, lenght * sizeof(type));                                                                                                     \
        for (uint64_t i = 0; i < lenght; i++)                                                                                                                          \
        {                                                                                                                                                              \
            check_buffer_overflow_acess(buffer, i * sizeof(type));                                                                                                     \
            if (buffer[i] == value)                                                                                                                                    \
                return i;                                                                                                                                              \
        }                                                                                                                                                              \
        return -1;                                                                                                                                                     \
    }                                                                                                                                                                  \
    int __stl_fn(type, __base_name, find_cmp)(type * buffer, type value, size_t lenght, bool (*cmp)(type a, type b))                                                   \
    {                                                                                                                                                                  \
        assert(buffer != NULL);                                                                                                                                        \
        assert(cmp != NULL);                                                                                                                                           \
        assert(lenght > 0);                                                                                                                                            \
        check_buffer_overflow_size(buffer, lenght * sizeof(type));                                                                                                     \
        for (uint64_t i = 0; i < lenght; i++)                                                                                                                          \
        {                                                                                                                                                              \
            check_buffer_overflow_acess(buffer, i * sizeof(type));                                                                                                     \
            if ((*cmp)(buffer[i], value) == true)                                                                                                                      \
                return i;                                                                                                                                              \
        }                                                                                                                                                              \
        return -1;                                                                                                                                                     \
    }                                                                                                                                                                  \
    void __stl_fn(type, __base_name, resize)(type * *buffer, size_t lenght)                                                                                            \
    {                                                                                                                                                                  \
        assert(buffer != NULL);                                                                                                                                        \
        assert(*buffer != NULL);                                                                                                                                       \
        assert(lenght > 0);                                                                                                                                            \
        void *new_ptr = cstl_realloc(*buffer, lenght * sizeof(type));                                                                                                  \
        if (new_ptr)                                                                                                                                                   \
            *buffer = new_ptr;                                                                                                                                         \
    }                                                                                                                                                                  \
    size_t __stl_fn(type, __base_name, count)(type * buffer, type value, size_t lenght)                                                                                \
    {                                                                                                                                                                  \
        assert(buffer != NULL);                                                                                                                                        \
        assert(lenght > 0);                                                                                                                                            \
        size_t count = 0;                                                                                                                                              \
        check_buffer_overflow_size(buffer, lenght * sizeof(type));                                                                                                     \
        for (size_t i = 0; i < lenght; i++)                                                                                                                            \
        {                                                                                                                                                              \
            check_buffer_overflow_acess(buffer, i * sizeof(type));                                                                                                     \
            if (cstl_memcmp((void *)&buffer[i], (void *)(&value), sizeof(value)) == 0)                                                                                 \
            {                                                                                                                                                          \
                count++;                                                                                                                                               \
            }                                                                                                                                                          \
        }                                                                                                                                                              \
        return count;                                                                                                                                                  \
    }                                                                                                                                                                  \
    size_t __stl_fn(type, __base_name, count_cmp)(type * buffer, type value, size_t lenght, bool (*cmp)(type a, type b))                                               \
    {                                                                                                                                                                  \
        assert(buffer != NULL);                                                                                                                                        \
        assert(cmp != NULL);                                                                                                                                           \
        assert(lenght > 0);                                                                                                                                            \
        size_t count = 0;                                                                                                                                              \
        check_buffer_overflow_size(buffer, lenght * sizeof(type));                                                                                                     \
        for (size_t i = 0; i < lenght; i++)                                                                                                                            \
        {                                                                                                                                                              \
            check_buffer_overflow_acess(buffer, i * sizeof(type));                                                                                                     \
            if ((*cmp)(buffer[i], value) == true)                                                                                                                      \
            {                                                                                                                                                          \
                count++;                                                                                                                                               \
            }                                                                                                                                                          \
        }                                                                                                                                                              \
        return count;                                                                                                                                                  \
    }                                                                                                                                                                  \
    bool __stl_fn(type, __base_name, all)(type * buffer, type value, size_t lenght)                                                                                    \
    {                                                                                                                                                                  \
        assert(buffer != NULL);                                                                                                                                        \
        assert(lenght > 0);                                                                                                                                            \
        check_buffer_overflow_size(buffer, lenght * sizeof(type));                                                                                                     \
        for (uint64_t i = 0; i < lenght; i++)                                                                                                                          \
        {                                                                                                                                                              \
            check_buffer_overflow_acess(buffer, i * sizeof(type));                                                                                                     \
            if (!cstl_memcmp((void *)&buffer[i], (void *)(&value), sizeof(type)) == 0)                                                                                 \
            {                                                                                                                                                          \
                return false;                                                                                                                                          \
            }                                                                                                                                                          \
        }                                                                                                                                                              \
        return true;                                                                                                                                                   \
    }                                                                                                                                                                  \
    bool __stl_fn(type, __base_name, any)(type * buffer, type value, size_t lenght)                                                                                    \
    {                                                                                                                                                                  \
        assert(buffer != NULL);                                                                                                                                        \
        assert(lenght > 0);                                                                                                                                            \
        check_buffer_overflow_size(buffer, lenght * sizeof(type));                                                                                                     \
        for (uint64_t i = 0; i < lenght; i++)                                                                                                                          \
        {                                                                                                                                                              \
            check_buffer_overflow_acess(buffer, i * sizeof(type));                                                                                                     \
            if (cstl_memcmp((void *)&buffer[i], (void *)(&value), sizeof(type)) == 0)                                                                                  \
            {                                                                                                                                                          \
                return true;                                                                                                                                           \
            }                                                                                                                                                          \
        }                                                                                                                                                              \
        return false;                                                                                                                                                  \
    }                                                                                                                                                                  \
    bool __stl_fn(type, __base_name, all_cmp)(type * buffer, type value, size_t lenght, bool (*cmp)(type a, type b))                                                   \
    {                                                                                                                                                                  \
        assert(buffer != NULL);                                                                                                                                        \
        assert(cmp != NULL);                                                                                                                                           \
        assert(lenght > 0);                                                                                                                                            \
        check_buffer_overflow_size(buffer, lenght * sizeof(type));                                                                                                     \
        for (uint64_t i = 0; i < lenght; i++)                                                                                                                          \
        {                                                                                                                                                              \
            check_buffer_overflow_acess(buffer, i * sizeof(type));                                                                                                     \
            if ((*cmp)(buffer[i], value) != true)                                                                                                                      \
            {                                                                                                                                                          \
                return false;                                                                                                                                          \
            }                                                                                                                                                          \
        }                                                                                                                                                              \
        return true;                                                                                                                                                   \
    }                                                                                                                                                                  \
    bool __stl_fn(type, __base_name, any_cmp)(type * buffer, type value, size_t lenght, bool (*cmp)(type a, type b))                                                   \
    {                                                                                                                                                                  \
        assert(buffer != NULL);                                                                                                                                        \
        assert(cmp != NULL);                                                                                                                                           \
        assert(lenght > 0);                                                                                                                                            \
        check_buffer_overflow_size(buffer, lenght * sizeof(type));                                                                                                     \
        for (uint64_t i = 0; i < lenght; i++)                                                                                                                          \
        {                                                                                                                                                              \
            check_buffer_overflow_acess(buffer, i * sizeof(type));                                                                                                     \
            if ((*cmp)(buffer[i], value) == true)                                                                                                                      \
            {                                                                                                                                                          \
                return true;                                                                                                                                           \
            }                                                                                                                                                          \
        }                                                                                                                                                              \
        return false;                                                                                                                                                  \
    }                                                                                                                                                                  \
    void __stl_fn(type, __base_name, join)(type * *a, type * b, size_t lenght_a, size_t lenght_b)                                                                      \
    {                                                                                                                                                                  \
        assert(a != NULL);                                                                                                                                             \
        assert(*a != NULL);                                                                                                                                            \
        assert(b != NULL);                                                                                                                                             \
        assert(lenght_a > 0);                                                                                                                                          \
        assert(lenght_b > 0);                                                                                                                                          \
        check_buffer_overflow_size(*a, lenght_a * sizeof(type));                                                                                                       \
        check_buffer_overflow_size(b, lenght_b * sizeof(type));                                                                                                        \
        size_t new_size = sizeof(type) * (lenght_a + lenght_b);                                                                                                        \
        void *new_ptr = cstl_realloc(*a, new_size);                                                                                                                    \
        if (new_ptr)                                                                                                                                                   \
        {                                                                                                                                                              \
            *a = new_ptr;                                                                                                                                              \
            cstl_memcpy((void *)((uintptr_t)(*a) + (sizeof(type) * lenght_a)), b, (lenght_b * sizeof(type)));                                                          \
        }                                                                                                                                                              \
    }                                                                                                                                                                  \
    void __stl_fn(type, __base_name, reverse)(type * buffer, size_t lenght)                                                                                            \
    {                                                                                                                                                                  \
        assert(buffer != NULL);                                                                                                                                        \
        assert(lenght > 0);                                                                                                                                            \
        check_buffer_overflow_size(buffer, lenght * sizeof(type));                                                                                                     \
        size_t start = 0;                                                                                                                                              \
        size_t end = lenght - 1;                                                                                                                                       \
        while (start < end)                                                                                                                                            \
        {                                                                                                                                                              \
            check_buffer_overflow_acess(buffer, start * sizeof(type));                                                                                                 \
            check_buffer_overflow_acess(buffer, end * sizeof(type));                                                                                                   \
            type tmp = buffer[start];                                                                                                                                  \
            buffer[start] = buffer[end];                                                                                                                               \
            buffer[end] = tmp;                                                                                                                                         \
            start++;                                                                                                                                                   \
            end--;                                                                                                                                                     \
        }                                                                                                                                                              \
    }                                                                                                                                                                  \
    void __stl_fn(type, __base_name, map)(type * buffer, type * *out, size_t lenght, type(*map_fn)(type value, size_t index))                                          \
    {                                                                                                                                                                  \
        assert(buffer != NULL);                                                                                                                                        \
        assert(out != NULL);                                                                                                                                           \
        assert(map_fn != NULL);                                                                                                                                        \
        assert(lenght > 0);                                                                                                                                            \
        check_buffer_overflow_size(buffer, lenght * sizeof(type));                                                                                                     \
        *out = cstl_malloc(lenght * sizeof(type));                                                                                                                     \
        for (size_t i = 0; i < lenght; i++)                                                                                                                            \
        {                                                                                                                                                              \
            check_buffer_overflow_acess(*out, i * sizeof(type));                                                                                                       \
            check_buffer_overflow_acess(buffer, i * sizeof(type));                                                                                                     \
            (*out)[i] = map_fn(buffer[i], i);                                                                                                                          \
        }                                                                                                                                                              \
    }                                                                                                                                                                  \
    void __stl_fn(type, __base_name, filter)(type * buffer, type * *out, size_t lenght, bool (*filter_fn)(type value, size_t index, type * filtered), size_t *out_len) \
    {                                                                                                                                                                  \
        assert(buffer != NULL);                                                                                                                                        \
        assert(out != NULL);                                                                                                                                           \
        assert(filter_fn != NULL);                                                                                                                                     \
        assert(out_len != NULL);                                                                                                                                       \
        assert(lenght > 0);                                                                                                                                            \
        check_buffer_overflow_size(buffer, lenght * sizeof(type));                                                                                                     \
        *out = cstl_malloc((*out_len == 0 ? lenght / 2 : lenght) * sizeof(type));                                                                                      \
        size_t count = 0;                                                                                                                                              \
        type filtered;                                                                                                                                                 \
        for (size_t i = 0; i < lenght; i++)                                                                                                                            \
        {                                                                                                                                                              \
            check_buffer_overflow_acess(buffer, i * sizeof(type));                                                                                                     \
            if (filter_fn(buffer[i], i, &filtered))                                                                                                                    \
            {                                                                                                                                                          \
                if (count + 1 > lenght)                                                                                                                                \
                {                                                                                                                                                      \
                    *out = cstl_realloc(*out, sizeof(type) * lenght);                                                                                                  \
                }                                                                                                                                                      \
                check_buffer_overflow_acess(buffer, (count + 1) * sizeof(type));                                                                                       \
                (*out)[count++] = filtered;                                                                                                                            \
            }                                                                                                                                                          \
        }                                                                                                                                                              \
        *out = cstl_realloc(*out, sizeof(type) * count);                                                                                                               \
        *out_len = count;                                                                                                                                              \
    }

#endif