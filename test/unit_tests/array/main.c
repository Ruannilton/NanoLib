#include "munit.h"
#include <stdlib.h>
#include <stdio.h>

#define CSTL_IMPLEMENT
#include "../../../src/data_structure/cstl.h"

stl_core_implement(int);
stl_declare_array(int);
stl_implement_array(int);

#define TEST(name, function)                                       \
    {                                                              \
        name, function, setup, clear, MUNIT_TEST_OPTION_NONE, NULL \
    }

#define TEST_FUNC(name) MunitResult name(const MunitParameter params[], void *user_data)

bool int_cmp(int a, int b)
{
    return a == b;
}

bool is_even(int a, int b)
{
    return a % 2 == 1;
}

bool less_than_two(int a, int b)
{
    return a < 2;
}

int mul_by_2(int value, size_t index)
{
    return value * 2;
}

bool filter_even(int value, size_t index, int *filtered)
{
    if (value % 2 == 1)
    {
        *filtered = value;
        return true;
    }
    return false;
}

TEST_FUNC(test_insert)
{
    array(int) *my_arr = user_data;
    int v1 = munit_rand_uint32();
    int v2 = munit_rand_uint32();
    int v3 = munit_rand_uint32();

    stl_array_int_insert(my_arr, v1, 0);
    stl_array_int_insert(my_arr, v2, 0);
    stl_array_int_insert(my_arr, v3, 0);

    munit_assert(my_arr->buffer[0] == v3);
    munit_assert(my_arr->buffer[1] == v2);
    munit_assert(my_arr->buffer[2] == v1);

    return MUNIT_OK;
}

TEST_FUNC(test_set)
{
    array(int) *my_arr = user_data;
    int v1 = munit_rand_uint32();
    int v2 = munit_rand_uint32();
    int v3 = munit_rand_uint32();

    stl_array_int_set(my_arr, v1, 0);
    stl_array_int_set(my_arr, v2, 1);
    stl_array_int_set(my_arr, v3, 2);

    munit_assert(my_arr->buffer[3] == 0);
    munit_assert(my_arr->buffer[2] == v3);
    munit_assert(my_arr->buffer[1] == v2);
    munit_assert(my_arr->buffer[0] == v1);

    return MUNIT_OK;
}

TEST_FUNC(test_remove)
{
    array(int) *my_arr = user_data;
    int v1 = munit_rand_uint32();
    int v2 = munit_rand_uint32();
    int v3 = munit_rand_uint32();

    stl_array_int_set(my_arr, v1, 0);
    stl_array_int_set(my_arr, v2, 1);
    stl_array_int_set(my_arr, v3, 2);

    stl_array_int_remove(my_arr, 1);

    munit_assert(my_arr->buffer[2] == 0);
    munit_assert(my_arr->buffer[1] == v3);
    munit_assert(my_arr->buffer[0] == v1);

    return MUNIT_OK;
}

TEST_FUNC(test_get)
{
    array(int) *my_arr = user_data;
    int v1 = munit_rand_uint32();
    int v2 = munit_rand_uint32();
    int v3 = munit_rand_uint32();

    stl_array_int_set(my_arr, v1, 0);
    stl_array_int_set(my_arr, v2, 1);
    stl_array_int_set(my_arr, v3, 2);

    int g1 = stl_array_int_get(my_arr, 0);
    int g2 = stl_array_int_get(my_arr, 1);
    int g3 = stl_array_int_get(my_arr, 2);

    munit_assert(g1 == v1);
    munit_assert(g2 == v2);
    munit_assert(g3 == v3);

    return MUNIT_OK;
}

TEST_FUNC(test_first)
{
    array(int) *my_arr = user_data;
    int v1 = munit_rand_uint32();
    int v2 = munit_rand_uint32();
    int v3 = munit_rand_uint32();

    int arr[3] = {v1, v2, v3};

    stl_array_int_set(my_arr, v1, 0);
    stl_array_int_set(my_arr, v2, 1);
    stl_array_int_set(my_arr, v3, 2);

    for (size_t i = 0; i < 3; i++)
    {
        int g = stl_array_int_first(my_arr);
        munit_assert(g == arr[i]);
        stl_array_int_remove(my_arr, 0);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_last)
{
    array(int) *my_arr = user_data;
    int v1 = munit_rand_uint32();
    stl_array_int_set(my_arr, v1, my_arr->lenght - 1);
    int g1 = stl_array_int_last(my_arr);
    munit_assert(g1 == v1);
    return MUNIT_OK;
}

TEST_FUNC(test_copy)
{
    array(int) *my_arr = user_data;
    for (size_t z = 0; z < 1000; z++)
    {
        size_t start = munit_rand_uint32() % 5;
        size_t len = munit_rand_int_range(1, my_arr->lenght - start - 1);

        int *buff = malloc(sizeof(int) * len);

        for (size_t i = 0; i < my_arr->lenght; i++)
        {
            stl_array_int_set(my_arr, munit_rand_uint32(), i);
        }

        stl_array_int_copy(my_arr, &buff, start, start + len);

        for (size_t i = start, c = 0; i < start + len; i++, c++)
        {
            munit_assert(stl_array_int_get(my_arr, i) == buff[c]);
        }

        free(buff);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_clone)
{
    array(int) *my_arr = user_data;

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        stl_array_int_set(my_arr, munit_rand_uint32(), i);
    }

    int *buff = malloc(sizeof(int) * my_arr->lenght);
    stl_array_int_clone(my_arr, &buff);

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        munit_assert(stl_array_int_get(my_arr, i) == buff[i]);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_equal)
{
    array(int) other_arr = {.buffer = 0, .lenght = 0};
    array(int) *my_arr = user_data;

    stl_array_int_create(&other_arr, my_arr->lenght);

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        uint32_t v = munit_rand_uint32();
        stl_array_int_set(my_arr, v, i);
        stl_array_int_set(&other_arr, v, i);
    }

    bool eq = stl_array_int_equal(&other_arr, my_arr);
    munit_assert(eq);

    stl_array_int_free(&other_arr);
    return MUNIT_OK;
}

TEST_FUNC(test_fill)
{
    array(int) *my_arr = user_data;

    uint32_t number = munit_rand_uint32();

    stl_array_int_fill(my_arr, number);

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        munit_assert(stl_array_int_get(my_arr, i) == number);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_find)
{
    array(int) *my_arr = user_data;
    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        stl_array_int_set(my_arr, i, i);
        int pos = stl_array_int_find(my_arr, i);
        munit_assert(pos == i);
    }

    int pos = stl_array_int_find(my_arr, -342);
    munit_assert(pos == -1);

    return MUNIT_OK;
}

TEST_FUNC(test_find_cmp)
{
    array(int) *my_arr = user_data;
    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        stl_array_int_set(my_arr, i, i);
        int pos = stl_array_int_find_cmp(my_arr, i, int_cmp);
        munit_assert(pos == i);
    }

    int pos = stl_array_int_find_cmp(my_arr, -342, int_cmp);
    munit_assert(pos == -1);

    return MUNIT_OK;
}

TEST_FUNC(test_resize)
{
    array(int) *my_arr = user_data;
    size_t i = 0;
    for (; i < my_arr->lenght; i++)
    {
        stl_array_int_set(my_arr, i, i);
    }
    stl_array_int_resize(my_arr, my_arr->lenght * 2);
    for (; i < my_arr->lenght; i++)
    {
        stl_array_int_set(my_arr, i, i);
    }
    for (i = 0; i < my_arr->lenght; i++)
    {
        munit_assert(stl_array_int_get(my_arr, i) == i);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_count)
{
    array(int) *my_arr = user_data;

    size_t c = 0;
    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        c += i % 2;
        stl_array_int_set(my_arr, i % 2, i);
    }
    munit_assert(c == stl_array_int_count(my_arr, 1));
    munit_assert(0 == stl_array_int_count(my_arr, -1));
    return MUNIT_OK;
}

TEST_FUNC(test_count_cmp)
{
    array(int) *my_arr = user_data;

    size_t c = 0;
    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        c += i % 2;
        stl_array_int_set(my_arr, i % 2, i);
    }
    munit_assert(c == stl_array_int_count_cmp(my_arr, 1, int_cmp));
    munit_assert(0 == stl_array_int_count_cmp(my_arr, -1, int_cmp));
    return MUNIT_OK;
}

TEST_FUNC(test_all)
{
    array(int) *my_arr = user_data;

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        stl_array_int_set(my_arr, 1, i);
    }

    munit_assert(stl_array_int_all(my_arr, 1));
    munit_assert(stl_array_int_all(my_arr, 0) == false);
    return MUNIT_OK;
}

TEST_FUNC(test_all_cmp)
{
    array(int) *my_arr = user_data;

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        stl_array_int_set(my_arr, i % 2, i);
    }

    munit_assert(stl_array_int_all_cmp(my_arr, 0, less_than_two));
    munit_assert(stl_array_int_all_cmp(my_arr, 0, is_even) == false);
    munit_assert(stl_array_int_all_cmp(my_arr, 2, int_cmp) == false);
    return MUNIT_OK;
}

TEST_FUNC(test_any)
{
    array(int) *my_arr = user_data;

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        stl_array_int_set(my_arr, i % 2, i);
    }

    munit_assert(stl_array_int_any(my_arr, 0));
    munit_assert(stl_array_int_any(my_arr, 1));
    munit_assert(stl_array_int_any(my_arr, 2) == false);
    return MUNIT_OK;
}

TEST_FUNC(test_any_cmp)
{
    array(int) *my_arr = user_data;

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        stl_array_int_set(my_arr, i % 2, i);
    }

    munit_assert(stl_array_int_any_cmp(my_arr, 0, less_than_two));
    munit_assert(stl_array_int_any_cmp(my_arr, 0, is_even));
    munit_assert(stl_array_int_any_cmp(my_arr, 2, int_cmp) == false);
    return MUNIT_OK;
}

TEST_FUNC(test_join)
{
    array(int) other_arr = {.buffer = 0, .lenght = 0};
    array(int) *my_arr = user_data;

    stl_array_int_create(&other_arr, my_arr->lenght);

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        uint32_t v = munit_rand_uint32();
        stl_array_int_set(my_arr, v, i);
        stl_array_int_set(&other_arr, v, i);
    }

    size_t i_len = my_arr->lenght;
    stl_array_int_join(my_arr, &other_arr);

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        munit_assert(stl_array_int_get(my_arr, i) == stl_array_int_get(my_arr, i + i_len));
    }

    stl_array_int_free(&other_arr);
    return MUNIT_OK;
}

TEST_FUNC(test_reverse)
{
    array(int) *my_arr = user_data;

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        stl_array_int_set(my_arr, i, i);
    }

    stl_array_int_reverse(my_arr);

    for (size_t i = 0, v = my_arr->lenght - 1; i < my_arr->lenght; i++, v--)
    {
        munit_assert(stl_array_int_get(my_arr, i) == v);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_lenght)
{
    array(int) *my_arr = user_data;

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        stl_array_int_set(my_arr, i, i);
    }

    for (size_t i = 0; i < 5; i++)
    {
        size_t n_size = munit_rand_int_range(5, 15);
        stl_array_int_resize(my_arr, n_size);
        munit_assert(stl_array_int_lenght(my_arr) == n_size);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_map)
{
    array(int) *my_arr = user_data;
    int *out;

    stl_array_int_map(my_arr, &out, mul_by_2);

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        munit_assert(stl_array_int_get(my_arr, i) * 2 == out[i]);
    }

    free(out);
    return MUNIT_OK;
}

TEST_FUNC(test_filter)
{
    array(int) *my_arr = user_data;
    int *out;
    size_t vec_len;

    for (size_t i = 0; i < my_arr->lenght; i++)
    {
        stl_array_int_set(my_arr, i, i);
    }

    stl_array_int_filter(my_arr, &out, filter_even, &vec_len);
    munit_assert(vec_len == 5);
    for (size_t i = 0; i < vec_len; i++)
    {
        munit_assert(out[i] == 1 + (i * 2));
    }

    free(out);
    return MUNIT_OK;
}

static void *setup(const MunitParameter params[], void *user_data)
{
    array(int) *my_arr = (array(int) *)malloc(sizeof(array(int)));
    stl_array_int_create(my_arr, 10);

    for (int i = 0; i < my_arr->lenght; i++)
        my_arr->buffer[i] = 0;
    return my_arr;
}

static void clear(void *data)
{
    array(int) *arr = (array(int) *)data;
    free(arr->buffer);
    free(arr);
}

int main(int argc, char *const argv[])
{
    MunitTest tests[] = {
        TEST("/insert", test_insert),
        TEST("/set", test_set),
        TEST("/remove", test_remove),
        TEST("/get", test_get),
        TEST("/first", test_first),
        TEST("/last", test_last),
        TEST("/copy", test_copy),
        TEST("/clone", test_clone),
        TEST("/equal", test_equal),
        TEST("/fill", test_fill),
        TEST("/find", test_find),
        TEST("/find_cmp", test_find_cmp),
        TEST("/resize", test_resize),
        TEST("/count", test_count),
        TEST("/count_cmp", test_count_cmp),
        TEST("/all", test_all),
        TEST("/all_cmp", test_all_cmp),
        TEST("/any", test_any),
        TEST("/any_cmp", test_any_cmp),
        TEST("/join", test_join),
        TEST("/reverse", test_reverse),
        TEST("/lenght", test_lenght),
        TEST("/map", test_map),
        TEST("/filter", test_filter),
        {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};
    MunitSuite suite = {"/array", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};
    munit_suite_main(&suite, NULL, argc, argv);
    return 0;
}