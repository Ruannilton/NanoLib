#ifndef STL_LINKED_LIST_IMPL_H
#define STL_LINKED_LIST_IMPL_H

#include "../definitions/stl_linked_list.h"

#define stl_implement_linked_list_alias(type, alias) \
    typedef type alias;                              \
    stl_implement_linked_list(alias);

#define stl_implement_linked_list(type)                                                                                                      \
    stl_declare_linked_list(type);                                                                                                           \
    void __stl_fn(type, linked_list, create)(__stl_t(type, linked_list) * arr, size_t lenght)                                                \
    {                                                                                                                                        \
        STL_VAL_NOT_NULL(arr);                                                                                                               \
        arr->count = 0;                                                                                                                      \
        arr->first = 0;                                                                                                                      \
        arr->last = 0;                                                                                                                       \
        if (lenght > 0)                                                                                                                      \
        {                                                                                                                                    \
            arr->first = cstl_malloc(sizeof(__stl_t(type, linked_list_node_t)));                                                             \
            __stl_t(type, linked_list_node_t) *current = arr->first;                                                                         \
            arr->last = arr->first;                                                                                                          \
            for (size_t i = 1; i < lenght; i++)                                                                                              \
            {                                                                                                                                \
                __stl_t(type, linked_list_node_t) *tmp = cstl_malloc(sizeof(__stl_t(type, linked_list_node_t)));                             \
                current->pnext = tmp;                                                                                                        \
                current = tmp;                                                                                                               \
                arr->last = tmp;                                                                                                             \
                arr->count++;                                                                                                                \
            }                                                                                                                                \
        }                                                                                                                                    \
    }                                                                                                                                        \
    void __stl_fn(type, linked_list, insert)(__stl_t(type, linked_list) * arr, type value, size_t index)                                     \
    {                                                                                                                                        \
        STL_VAL_NOT_NULL(arr);                                                                                                               \
        if (index == 0)                                                                                                                      \
        {                                                                                                                                    \
            __stl_t(type, linked_list_node_t) *new_node = cstl_malloc(sizeof(__stl_t(type, linked_list_node_t)));                            \
            new_node->value = value;                                                                                                         \
            new_node->pnext = arr->first;                                                                                                    \
            arr->first = new_node;                                                                                                           \
            arr->count++;                                                                                                                    \
        }                                                                                                                                    \
        else                                                                                                                                 \
        {                                                                                                                                    \
            STL_VAL_NOT_NULL(arr->first);                                                                                                    \
            __stl_t(type, linked_list_node_t) *aux = arr->first;                                                                             \
            for (size_t i = 0; i < index - 1; i++)                                                                                           \
            {                                                                                                                                \
                aux = aux->pnext;                                                                                                            \
            }                                                                                                                                \
            __stl_t(type, linked_list_node_t) *new_node = cstl_malloc(sizeof(__stl_t(type, linked_list_node_t)));                            \
            new_node->value = value;                                                                                                         \
            new_node->pnext = aux->pnext;                                                                                                    \
            aux->pnext = new_node;                                                                                                           \
            if (aux == arr->last)                                                                                                            \
                arr->last = new_node;                                                                                                        \
            arr->count++;                                                                                                                    \
        }                                                                                                                                    \
    }                                                                                                                                        \
    void __stl_fn(type, linked_list, set)(__stl_t(type, linked_list) * arr, type value, size_t index)                                        \
    {                                                                                                                                        \
        /*STL_VAL_NOT_NULL(arr);*/                                                                                                           \
        /*STL_VAL_NOT_NULL(arr->first);*/                                                                                                    \
        __stl_t(type, linked_list_node_t) *aux = arr->first;                                                                                 \
        for (size_t i = 0; i < index; i++)                                                                                                   \
        {                                                                                                                                    \
            aux = aux->pnext;                                                                                                                \
        }                                                                                                                                    \
        aux->value = value;                                                                                                                  \
    }                                                                                                                                        \
    void __stl_fn(type, linked_list, add)(__stl_t(type, linked_list) * arr, type value)                                                      \
    {                                                                                                                                        \
        STL_VAL_NOT_NULL(arr);                                                                                                               \
        __stl_t(type, linked_list_node_t) *new_node = cstl_malloc(sizeof(__stl_t(type, linked_list_node_t)));                                \
        new_node->value = value;                                                                                                             \
        new_node->pnext = 0;                                                                                                                 \
        if (arr->count == 0)                                                                                                                 \
        {                                                                                                                                    \
            arr->last = new_node;                                                                                                            \
            arr->first = arr->last;                                                                                                          \
        }                                                                                                                                    \
        else                                                                                                                                 \
        {                                                                                                                                    \
            arr->last->pnext = new_node;                                                                                                     \
            arr->last = new_node;                                                                                                            \
        }                                                                                                                                    \
        arr->count++;                                                                                                                        \
    }                                                                                                                                        \
    type __stl_fn(type, linked_list, remove)(__stl_t(type, linked_list) * arr, size_t index)                                                 \
    {                                                                                                                                        \
        /*STL_VAL_NOT_NULL(arr);*/                                                                                                           \
        __stl_t(type, linked_list_node_t) *rem = arr->first, *last = 0;                                                                      \
        for (size_t i = 0; i < index; i++)                                                                                                   \
        {                                                                                                                                    \
            if (rem->pnext == NULL)                                                                                                          \
                break;                                                                                                                       \
            last = rem;                                                                                                                      \
            rem = rem->pnext;                                                                                                                \
        }                                                                                                                                    \
                                                                                                                                             \
        if (rem == arr->last)                                                                                                                \
        {                                                                                                                                    \
            arr->last = last;                                                                                                                \
            arr->last->pnext = 0;                                                                                                            \
        }                                                                                                                                    \
        else if (rem == arr->first)                                                                                                          \
        {                                                                                                                                    \
            arr->first = arr->first->pnext;                                                                                                  \
        }                                                                                                                                    \
        else                                                                                                                                 \
            last->pnext = rem->pnext;                                                                                                        \
        type v = rem->value;                                                                                                                 \
        cstl_free(rem);                                                                                                                      \
        arr->count--;                                                                                                                        \
        return v;                                                                                                                            \
    }                                                                                                                                        \
    type __stl_fn(type, linked_list, get)(__stl_t(type, linked_list) * arr, size_t index)                                                    \
    {                                                                                                                                        \
        STL_VAL_NOT_NULL(arr);                                                                                                               \
        STL_VAL_NOT_NULL(arr->first);                                                                                                        \
        __stl_t(type, linked_list_node_t) *current = arr->first;                                                                             \
        for (size_t i = 0; i < index; i++)                                                                                                   \
        {                                                                                                                                    \
            current = current->pnext;                                                                                                        \
        }                                                                                                                                    \
        return current->value;                                                                                                               \
    }                                                                                                                                        \
    type __stl_fn(type, linked_list, first)(__stl_t(type, linked_list) * arr)                                                                \
    {                                                                                                                                        \
        STL_VAL_NOT_NULL(arr);                                                                                                               \
        STL_VAL_NOT_NULL(arr->first);                                                                                                        \
        return arr->first->value;                                                                                                            \
    }                                                                                                                                        \
    void __stl_fn(type, linked_list, copy)(__stl_t(type, linked_list) * arr, __stl_t(type, linked_list) * *out, size_t start, size_t end)    \
    {                                                                                                                                        \
        STL_VAL_NOT_NULL(arr);                                                                                                               \
        STL_VAL_NOT_NULL(arr->first);                                                                                                        \
        STL_VAL_NOT_NULL(out);                                                                                                               \
        __stl_t(type, linked_list_node_t) *current = arr->first;                                                                             \
        for (size_t i = 0; i < start; i++)                                                                                                   \
        {                                                                                                                                    \
            current = current->pnext;                                                                                                        \
        }                                                                                                                                    \
        __stl_t(type, linked_list_node_t) *new_node = cstl_malloc(sizeof(__stl_t(type, linked_list_node_t)));                                \
        new_node->pnext = 0;                                                                                                                 \
        new_node->value = current->value;                                                                                                    \
        current = current->pnext;                                                                                                            \
                                                                                                                                             \
        (*out)->first = new_node;                                                                                                            \
        (*out)->count = 1;                                                                                                                   \
        __stl_t(type, linked_list_node_t) *currento = (*out)->first;                                                                         \
                                                                                                                                             \
        for (size_t i = start + 1; i < end; i++)                                                                                             \
        {                                                                                                                                    \
            new_node = cstl_malloc(sizeof(__stl_t(type, linked_list_node_t)));                                                               \
            new_node->pnext = 0;                                                                                                             \
            new_node->value = current->value;                                                                                                \
                                                                                                                                             \
            currento->pnext = new_node;                                                                                                      \
                                                                                                                                             \
            current = current->pnext;                                                                                                        \
            currento = currento->pnext;                                                                                                      \
            (*out)->count++;                                                                                                                 \
        }                                                                                                                                    \
    }                                                                                                                                        \
    void __stl_fn(type, linked_list, clone)(__stl_t(type, linked_list) * arr, __stl_t(type, linked_list) * *out)                             \
    {                                                                                                                                        \
        /*STL_VAL_NOT_NULL(arr);*/                                                                                                           \
        /*STL_VAL_NOT_NULL(arr->first);*/                                                                                                    \
        /*STL_VAL_NOT_NULL(out); */                                                                                                          \
        __stl_t(type, linked_list_node_t) *current = arr->first;                                                                             \
                                                                                                                                             \
        __stl_t(type, linked_list_node_t) *new_node = cstl_malloc(sizeof(__stl_t(type, linked_list_node_t)));                                \
        new_node->pnext = 0;                                                                                                                 \
        new_node->value = current->value;                                                                                                    \
        current = current->pnext;                                                                                                            \
                                                                                                                                             \
        (*out)->first = new_node;                                                                                                            \
        (*out)->count = 1;                                                                                                                   \
        __stl_t(type, linked_list_node_t) *currento = (*out)->first;                                                                         \
                                                                                                                                             \
        for (size_t i = 1; i < arr->count; i++)                                                                                              \
        {                                                                                                                                    \
            new_node = cstl_malloc(sizeof(__stl_t(type, linked_list_node_t)));                                                               \
            new_node->pnext = 0;                                                                                                             \
            new_node->value = current->value;                                                                                                \
                                                                                                                                             \
            currento->pnext = new_node;                                                                                                      \
                                                                                                                                             \
            current = current->pnext;                                                                                                        \
            currento = currento->pnext;                                                                                                      \
            (*out)->count++;                                                                                                                 \
        }                                                                                                                                    \
    }                                                                                                                                        \
    bool __stl_fn(type, linked_list, equal)(__stl_t(type, linked_list) * a, __stl_t(type, linked_list) * b)                                  \
    {                                                                                                                                        \
        STL_VAL_NOT_NULL(a);                                                                                                                 \
        STL_VAL_NOT_NULL(b);                                                                                                                 \
        if (a->count != b->count)                                                                                                            \
            return false;                                                                                                                    \
        __stl_t(type, linked_list_node_t) *currenta = a->first;                                                                              \
        __stl_t(type, linked_list_node_t) *currentb = b->first;                                                                              \
        for (size_t i = 0; i < a->count; i++)                                                                                                \
        {                                                                                                                                    \
            if (currenta->value != currentb->value)                                                                                          \
                return false;                                                                                                                \
            currenta = currenta->pnext;                                                                                                      \
            currentb = currentb->pnext;                                                                                                      \
        }                                                                                                                                    \
        return true;                                                                                                                         \
    }                                                                                                                                        \
    void __stl_fn(type, linked_list, fill)(__stl_t(type, linked_list) * arr, type value)                                                     \
    {                                                                                                                                        \
        STL_VAL_NOT_NULL(arr);                                                                                                               \
        STL_VAL_NOT_NULL(arr->first);                                                                                                        \
        __stl_t(type, linked_list_node_t) *current = arr->first;                                                                             \
        for (size_t i = 0; i < arr->count; i++)                                                                                              \
        {                                                                                                                                    \
            current->value = value;                                                                                                          \
            current = current->pnext;                                                                                                        \
        }                                                                                                                                    \
    }                                                                                                                                        \
    int __stl_fn(type, linked_list, find)(__stl_t(type, linked_list) * arr, type value)                                                      \
    {                                                                                                                                        \
        STL_VAL_NOT_NULL(arr);                                                                                                               \
        STL_VAL_NOT_NULL(arr->first);                                                                                                        \
        __stl_t(type, linked_list_node_t) *current = arr->first;                                                                             \
        for (size_t i = 0; i < arr->count; i++)                                                                                              \
        {                                                                                                                                    \
            if (current->value == value)                                                                                                     \
            {                                                                                                                                \
                return i;                                                                                                                    \
            }                                                                                                                                \
            current = current->pnext;                                                                                                        \
        }                                                                                                                                    \
        return -1;                                                                                                                           \
    }                                                                                                                                        \
    int __stl_fn(type, linked_list, find_cmp)(__stl_t(type, linked_list) * arr, type value, bool (*cmp)(type a, type b))                     \
    {                                                                                                                                        \
        STL_VAL_NOT_NULL(arr);                                                                                                               \
        STL_VAL_NOT_NULL(arr->first);                                                                                                        \
        STL_VAL_NOT_NULL(cmp);                                                                                                               \
        __stl_t(type, linked_list_node_t) *current = arr->first;                                                                             \
        for (size_t i = 0; i < arr->count; i++)                                                                                              \
        {                                                                                                                                    \
            if (cmp(current->value, value))                                                                                                  \
            {                                                                                                                                \
                return i;                                                                                                                    \
            }                                                                                                                                \
            current = current->pnext;                                                                                                        \
        }                                                                                                                                    \
        return -1;                                                                                                                           \
    }                                                                                                                                        \
    size_t __stl_fn(type, linked_list, count)(__stl_t(type, linked_list) * arr, type value)                                                  \
    {                                                                                                                                        \
        STL_VAL_NOT_NULL(arr);                                                                                                               \
        STL_VAL_NOT_NULL(arr->first);                                                                                                        \
        size_t c = 0;                                                                                                                        \
        __stl_t(type, linked_list_node_t) *current = arr->first;                                                                             \
        for (size_t i = 0; i < arr->count; i++)                                                                                              \
        {                                                                                                                                    \
            if (current->value == value)                                                                                                     \
            {                                                                                                                                \
                c++;                                                                                                                         \
            }                                                                                                                                \
            current = current->pnext;                                                                                                        \
        }                                                                                                                                    \
        return c;                                                                                                                            \
    }                                                                                                                                        \
    size_t __stl_fn(type, linked_list, count_cmp)(__stl_t(type, linked_list) * arr, type value, bool (*cmp)(type a, type b))                 \
    {                                                                                                                                        \
        STL_VAL_NOT_NULL(arr);                                                                                                               \
        STL_VAL_NOT_NULL(arr->first);                                                                                                        \
        STL_VAL_NOT_NULL(cmp);                                                                                                               \
        size_t c = 0;                                                                                                                        \
        __stl_t(type, linked_list_node_t) *current = arr->first;                                                                             \
        for (size_t i = 0; i < arr->count; i++)                                                                                              \
        {                                                                                                                                    \
            if (cmp(current->value, value))                                                                                                  \
            {                                                                                                                                \
                c++;                                                                                                                         \
            }                                                                                                                                \
            current = current->pnext;                                                                                                        \
        }                                                                                                                                    \
        return c;                                                                                                                            \
    }                                                                                                                                        \
    bool __stl_fn(type, linked_list, all)(__stl_t(type, linked_list) * arr, type value)                                                      \
    {                                                                                                                                        \
        STL_VAL_NOT_NULL(arr);                                                                                                               \
        STL_VAL_NOT_NULL(arr->first);                                                                                                        \
        __stl_t(type, linked_list_node_t) *current = arr->first;                                                                             \
        for (size_t i = 0; i < arr->count; i++)                                                                                              \
        {                                                                                                                                    \
            if (current->value != value)                                                                                                     \
            {                                                                                                                                \
                return false;                                                                                                                \
            }                                                                                                                                \
            current = current->pnext;                                                                                                        \
        }                                                                                                                                    \
        return true;                                                                                                                         \
    }                                                                                                                                        \
    bool __stl_fn(type, linked_list, all_cmp)(__stl_t(type, linked_list) * arr, type value, bool (*cmp)(type a, type b))                     \
    {                                                                                                                                        \
        STL_VAL_NOT_NULL(arr);                                                                                                               \
        STL_VAL_NOT_NULL(arr->first);                                                                                                        \
        STL_VAL_NOT_NULL(cmp);                                                                                                               \
        __stl_t(type, linked_list_node_t) *current = arr->first;                                                                             \
        for (size_t i = 0; i < arr->count; i++)                                                                                              \
        {                                                                                                                                    \
            if (!cmp(current->value, value))                                                                                                 \
            {                                                                                                                                \
                return false;                                                                                                                \
            }                                                                                                                                \
            current = current->pnext;                                                                                                        \
        }                                                                                                                                    \
        return true;                                                                                                                         \
    }                                                                                                                                        \
    void __stl_fn(type, linked_list, join)(__stl_t(type, linked_list) * a, __stl_t(type, linked_list) * b, size_t lenght_a, size_t lenght_b) \
    {                                                                                                                                        \
        STL_VAL_NOT_NULL(a);                                                                                                                 \
        STL_VAL_NOT_NULL(b);                                                                                                                 \
        STL_VAL_NOT_ZERO(a->count);                                                                                                          \
        STL_VAL_NOT_ZERO(b->count);                                                                                                          \
        __stl_t(type, linked_list_node_t) *current = a->first;                                                                               \
        while (current->pnext != NULL)                                                                                                       \
        {                                                                                                                                    \
            current = current->pnext;                                                                                                        \
        }                                                                                                                                    \
        current->pnext = b->first;                                                                                                           \
        a->last = b->last;                                                                                                                   \
        a->count += b->count;                                                                                                                \
        b->first = 0;                                                                                                                        \
        b->count = 0;                                                                                                                        \
        b->last = 0;                                                                                                                         \
    }                                                                                                                                        \
    void __stl_fn(type, linked_list, reverse)(__stl_t(type, linked_list) * arr)                                                              \
    {                                                                                                                                        \
        STL_VAL_NOT_NULL(arr);                                                                                                               \
        STL_VAL_NOT_NULL(arr->first);                                                                                                        \
        __stl_t(type, linked_list_node_t) **buff = cstl_malloc(sizeof(__stl_t(type, linked_list_node_t) *) * arr->count);                    \
        __stl_t(type, linked_list_node_t) *current = arr->first;                                                                             \
        for (size_t i = 0; i < arr->count; i++)                                                                                              \
        {                                                                                                                                    \
            buff[i] = current;                                                                                                               \
            current = current->pnext;                                                                                                        \
        }                                                                                                                                    \
        for (size_t i = arr->count - 1; i > 0; i--)                                                                                          \
        {                                                                                                                                    \
            buff[i]->pnext = buff[i - 1];                                                                                                    \
        }                                                                                                                                    \
        buff[0]->pnext = 0;                                                                                                                  \
        arr->first = buff[arr->count - 1];                                                                                                   \
                                                                                                                                             \
        cstl_free(buff);                                                                                                                     \
    }                                                                                                                                        \
    void __stl_fn(type, linked_list, free)(__stl_t(type, linked_list) * arr, void (*custom_free)(type a))                                    \
    {                                                                                                                                        \
        STL_VAL_NOT_NULL(arr);                                                                                                               \
        STL_VAL_NOT_NULL(arr->first);                                                                                                        \
        __stl_t(type, linked_list_node_t) *current = arr->first;                                                                             \
        if (custom_free)                                                                                                                     \
        {                                                                                                                                    \
            for (size_t i = 0; i < arr->count; i++)                                                                                          \
            {                                                                                                                                \
                __stl_t(type, linked_list_node_t) *tmp = current;                                                                            \
                current = current->pnext;                                                                                                    \
                custom_free(tmp->value);                                                                                                     \
                cstl_free(tmp);                                                                                                              \
            }                                                                                                                                \
        }                                                                                                                                    \
        else                                                                                                                                 \
        {                                                                                                                                    \
            for (size_t i = 0; i < arr->count; i++)                                                                                          \
            {                                                                                                                                \
                __stl_t(type, linked_list_node_t) *tmp = current;                                                                            \
                current = current->pnext;                                                                                                    \
                cstl_free(tmp);                                                                                                              \
            }                                                                                                                                \
        }                                                                                                                                    \
    }

#endif