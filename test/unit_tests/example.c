#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

typedef char *string;
typedef struct
{
    int key;
    int value;
} stl_int_int_bucket;
typedef struct
{
    stl_int_int_bucket *arr;
    size_t len;
    size_t count;
} stl_int_int_bucket_hash_arr_t;
;
typedef struct
{
    stl_int_int_bucket_hash_arr_t *buffer;
    size_t len;
    size_t count;
    uintmax_t (*hash_fn)(char *);
    bool (*cmp_key_fn)(int a, int b);
} hash_int_int_t;
;
void stl_hash_map_int_int_create(hash_int_int_t *hash_ptr, size_t lenght, uintmax_t (*hash_fn)(char *), bool (*cmp_key_fn)(int a, int b));
void stl_hash_map_int_int_add(hash_int_int_t *hash_ptr, int key, int value);
bool stl_hash_map_int_int_get(hash_int_int_t *hash_ptr, int key, int *value);
bool stl_hash_map_int_int_exist(hash_int_int_t *hash_ptr, int key);
bool stl_hash_map_int_int_remove(hash_int_int_t *hash_ptr, int key);
void stl_hash_map_int_int_free(hash_int_int_t *hash_ptr);
void stl_hash_map_int_int_clear(hash_int_int_t *hash_ptr);
void stl_hash_map_int_int_clone(hash_int_int_t *source, hash_int_int_t **dest);
bool stl_hash_map_int_int_equal(hash_int_int_t *a, hash_int_int_t *b);
size_t stl_hash_map_int_int_lenght(hash_int_int_t *hash_ptr);
size_t stl_hash_map_int_int_count_values(hash_int_int_t *hash_ptr, int value);
size_t stl_hash_map_int_int_count_values_cmp(hash_int_int_t *hash_ptr, int value, bool (*cmp)(int a, int b));
bool stl_hash_map_int_int_all_values(hash_int_int_t *hash_ptr, int value);
bool stl_hash_map_int_int_all_values_cmp(hash_int_int_t *hash_ptr, int value, bool (*cmp)(int a, int b));
bool stl_hash_map_int_int_any_values(hash_int_int_t *hash_ptr, int value);
bool stl_hash_map_int_int_any_values_cmp(hash_int_int_t *hash_ptr, int value, bool (*cmp)(int a, int b));

bool ___stl_def_cmp_int(int a, int b) { return cstl_memcmp((void *)(&a), (void *)(&b), sizeof(int)) == 0; }

uintmax_t ___stl_def_hash_int(char *key)
{

    uintmax_t k = 0;
    char *c = key;
    for (size_t i = 0; i < sizeof(int); i++)
    {
        k += (int)(c[i]);
    }
    return k;
};
void stl_hash_map_int_int_create(hash_int_int_t *hash_ptr, size_t lenght, uintmax_t (*hash_fn)(char *), bool (*cmp_key_fn)(int a, int b))
{

    hash_ptr->len = lenght;
    hash_ptr->hash_fn = (hash_fn != 0) ? (hash_fn) : (___stl_def_hash_int);
    hash_ptr->cmp_key_fn = (cmp_key_fn != 0) ? (cmp_key_fn) : (___stl_def_cmp_int);
    hash_ptr->buffer = cstl_malloc((lenght * sizeof(stl_int_int_bucket_hash_arr_t)));
    hash_ptr->count = 0;
    for (size_t i = 0; i < lenght; i++)
    {
        hash_ptr->buffer[i].arr = 0;
        hash_ptr->buffer[i].count = 0;
        hash_ptr->buffer[i].len = 0;
    }
}
void stl_hash_map_int_int_add(hash_int_int_t *hash_ptr, int key, int value)
{

    uintmax_t insert_index = hash_ptr->hash_fn((char *)(&(key))) % hash_ptr->len;
    stl_int_int_bucket_hash_arr_t *bucket_arr = hash_ptr->buffer + insert_index;
    if (bucket_arr->len == 0)
    {
        bucket_arr->len = 2;
        size_t alloc_size = sizeof(stl_int_int_bucket) * bucket_arr->len;
        bucket_arr->arr = cstl_malloc(alloc_size);
    }
    else
    {
        for (size_t i = 0; i < bucket_arr->count; i++)
        {
            if (hash_ptr->cmp_key_fn(bucket_arr->arr[i].key, key))
            {
                bucket_arr->arr[i].value = value;
                return;
            }
        }
    }
    if (bucket_arr->count == bucket_arr->len)
    {
        bucket_arr->len *= 2;
        size_t relloc_size = sizeof(stl_int_int_bucket) * bucket_arr->len;
        void *ptr = cstl_realloc(bucket_arr->arr, relloc_size);
        if (ptr)
            bucket_arr->arr = ptr;
    }
    bucket_arr->arr[bucket_arr->count] = (stl_int_int_bucket){.key = key, .value = value};
    bucket_arr->count++;
    hash_ptr->count++;
}
bool stl_hash_map_int_int_get(hash_int_int_t *hash_ptr, int key, int *value)
{

    uintmax_t get_index = hash_ptr->hash_fn((char *)(&(key))) % hash_ptr->len;
    stl_int_int_bucket_hash_arr_t *bucket_arr = &(hash_ptr->buffer[get_index]);
    if (bucket_arr->len == 0 || bucket_arr->count == 0)
        return false;
    for (size_t i = 0; i < bucket_arr->count; i++)
    {
        if (hash_ptr->cmp_key_fn(bucket_arr->arr[i].key, key))
        {
            *value = bucket_arr->arr[i].value;
            return true;
        }
    }
    return false;
}
bool stl_hash_map_int_int_exist(hash_int_int_t *hash_ptr, int key)
{

    uintmax_t get_index = hash_ptr->hash_fn((char *)(&(key))) % hash_ptr->len;
    stl_int_int_bucket_hash_arr_t *bucket_arr = &(hash_ptr->buffer[get_index]);
    if (bucket_arr->len == 0 || bucket_arr->count == 0)
        return false;
    for (size_t i = 0; i < bucket_arr->count; i++)
    {
        if (hash_ptr->cmp_key_fn(bucket_arr->arr[i].key, key))
        {
            return true;
        }
    }
    return false;
}
bool stl_hash_map_int_int_remove(hash_int_int_t *hash_ptr, int key)
{

    uintmax_t get_index = hash_ptr->hash_fn((char *)(&(key))) % hash_ptr->len;
    stl_int_int_bucket_hash_arr_t *bucket_arr = &(hash_ptr->buffer[get_index]);
    if (bucket_arr->len == 0 || bucket_arr->count == 0)
        return false;
    bool found = false;
    for (size_t i = 0; i < bucket_arr->count; i++)
    {
        if (found)
        {
            bucket_arr->arr[i - 1] = bucket_arr->arr[i];
        }
        else if (hash_ptr->cmp_key_fn(bucket_arr->arr[i].key, key))
        {
            found = true;
        }
    }
    if (found)
    {
        bucket_arr->count--;
        hash_ptr->count--;
    }
    return found;
}
void stl_hash_map_int_int_free(hash_int_int_t *hash_ptr)
{

    for (size_t i = 0; i < hash_ptr->len; i++)
    {
        cstl_free(hash_ptr->buffer[i].arr);
        hash_ptr->buffer[i].arr = 0;
    }
    cstl_free(hash_ptr->buffer);
    hash_ptr->buffer = 0;
}
void stl_hash_map_int_int_clear(hash_int_int_t *hash_ptr)
{

    for (size_t i = 0; i < hash_ptr->len; i++)
    {
        cstl_free(hash_ptr->buffer[i].arr);
        hash_ptr->buffer[i].arr = 0;
        hash_ptr->buffer[i].count = 0;
        hash_ptr->buffer[i].len = 0;
    }
    hash_ptr->count = 0;
}
size_t stl_hash_map_int_int_lenght(hash_int_int_t *hash_ptr)
{

    return hash_ptr->count;
}
void stl_hash_map_int_int_clone(hash_int_int_t *source, hash_int_int_t **dest)
{
    (*dest)->len = source->len;
    (*dest)->count = source->count;
    (*dest)->hash_fn = source->hash_fn;
    (*dest)->cmp_key_fn = source->cmp_key_fn;
    (*dest)->buffer = cstl_malloc(((*dest)->len * sizeof(stl_int_int_bucket_hash_arr_t)));
    for (size_t i = 0; i < (*dest)->len; i++)
    {
        (*dest)->buffer[i].count = source->buffer[i].count;
        (*dest)->buffer[i].len = source->buffer[i].len;
        (*dest)->buffer[i].arr = cstl_malloc(sizeof(stl_int_int_bucket) * source->buffer[i].len);
        cstl_memcpy((*dest)->buffer[i].arr, source->buffer[i].arr, sizeof(stl_int_int_bucket) * source->buffer[i].len);
    }
}
bool stl_hash_map_int_int_equal(hash_int_int_t *a, hash_int_int_t *b)
{
    if (a->len == b->len && a->count == b->count && a->hash_fn == b->hash_fn && a->cmp_key_fn == b->cmp_key_fn)
    {
        for (size_t i = 0; i < a->len; i++)
        {
            if (!(a->buffer[i].len == b->buffer[i].len && cstl_memcmp(a->buffer[i].arr, b->buffer[i].arr, sizeof(stl_int_int_bucket) * a->buffer[i].len) == 0))
                return false;
        }
        return true;
    }
    return false;
}
size_t stl_hash_map_int_int_count_values(hash_int_int_t *hash_ptr, int value)
{
    size_t count = 0;
    for (size_t i = 0; i < hash_ptr->len; i++)
    {
        for (size_t j = 0; j < hash_ptr->buffer[i].len; j++)
        {
            if (hash_ptr->buffer[i].arr[j].value == value)
                count++;
        }
    }
    return count;
}
size_t stl_hash_map_int_int_count_values_cmp(hash_int_int_t *hash_ptr, int value, bool (*cmp)(int a, int b))
{
    size_t count = 0;
    for (size_t i = 0; i < hash_ptr->len; i++)
    {
        for (size_t j = 0; j < hash_ptr->buffer[i].len; j++)
        {
            if (cmp(hash_ptr->buffer[i].arr[j].value, value))
                count++;
        }
    }
    return count;
}
bool stl_hash_map_int_int_all_values(hash_int_int_t *hash_ptr, int value)
{
    for (size_t i = 0; i < hash_ptr->len; i++)
    {
        for (size_t j = 0; j < hash_ptr->buffer[i].len; j++)
        {
            if (hash_ptr->buffer[i].arr[j].value != value)
                return false;
        }
    }
    return true;
}
bool stl_hash_map_int_int_all_values_cmp(hash_int_int_t *hash_ptr, int value, bool (*cmp)(int a, int b))
{
    for (size_t i = 0; i < hash_ptr->len; i++)
    {
        for (size_t j = 0; j < hash_ptr->buffer[i].len; j++)
        {
            if (!cmp(hash_ptr->buffer[i].arr[j].value, value))
                return false;
        }
    }
    return true;
}
bool stl_hash_map_int_int_any_values(hash_int_int_t *hash_ptr, int value)
{
    for (size_t i = 0; i < hash_ptr->len; i++)
    {
        for (size_t j = 0; j < hash_ptr->buffer[i].len; j++)
        {
            if (hash_ptr->buffer[i].arr[j].value == value)
                return true;
        }
    }
    return false;
}
bool stl_hash_map_int_int_any_values_cmp(hash_int_int_t *hash_ptr, int value, bool (*cmp)(int a, int b))
{
    for (size_t i = 0; i < hash_ptr->len; i++)
    {
        for (size_t j = 0; j < hash_ptr->buffer[i].len; j++)
        {
            if (cmp(hash_ptr->buffer[i].arr[j].value, value))
                return true;
        }
    }
    return false;
};

int main()
{
    return 0;
}
