#include "munit.h"
#include "data_structure/cstl.h"
#include "macros.h"

stl_declare_array(int);

array(int) myarr;

static void *setup(const MunitParameter params[], void *user_data)
{
    stl_array_int_create(&myarr, INIT_LEN);

    for (int i = 0; i < myarr.lenght; i++)
        myarr.buffer[i] = 0;
    return 0;
}

static void clear(void *data)
{
    free(myarr.buffer);
}

static bool cmp_int(int a, int b)
{
    return a == b;
}

TEST_FUNC(test_insert)
{
    int v = munit_rand_uint32();
    stl_array_int_insert(&myarr, v, 0);
    munit_assert_int(myarr.buffer[0], ==, v);
    return MUNIT_OK;
}

TEST_FUNC(test_set)
{
    int v = munit_rand_uint32();
    stl_array_int_set(&myarr, v, 3);
    munit_assert_int(myarr.buffer[3], ==, v);
    return MUNIT_OK;
}

TEST_FUNC(test_remove)
{
    int cmp[] = {0, 1, 3, 4, 5, 6, 7, 8, 9};
    int count = 0;
    for (int i = 0; i < myarr.lenght; i++)
    {
        stl_array_int_set(&myarr, i, count);
        count++;
    }
    stl_array_int_remove(&myarr, 2);
    count--;
    munit_assert_memory_equal(count * sizeof(int), myarr.buffer, cmp);
    return MUNIT_OK;
}

TEST_FUNC(test_get)
{
    for (int i = 0; i < myarr.lenght; i++)
        myarr.buffer[i] = i;

    int val = stl_array_int_get(&myarr, 1);
    munit_assert_int(1, ==, val);
    return MUNIT_OK;
}

TEST_FUNC(test_first)
{
    for (int i = 0; i < myarr.lenght; i++)
        myarr.buffer[i] = munit_rand_uint32();

    int v0 = stl_array_int_first(&myarr);
    int i0 = myarr.buffer[0];
    munit_assert_int(v0, ==, i0);
    return MUNIT_OK;
}

TEST_FUNC(test_copy)
{
    for (int i = 0; i < myarr.lenght; i++)
        myarr.buffer[i] = munit_rand_uint32();

    int *buff = (int *)malloc(sizeof(int) * myarr.lenght);
    stl_array_int_copy(&myarr, &buff, 0, myarr.lenght);
    munit_assert_memory_equal(sizeof(int) * myarr.lenght, myarr.buffer, buff);
    free(buff);
    return MUNIT_OK;
}

TEST_FUNC(test_clone)
{
    for (int i = 0; i < myarr.lenght; i++)
        myarr.buffer[i] = munit_rand_uint32();

    int *buff = (int *)malloc(sizeof(int) * myarr.lenght);
    stl_array_int_clone(&myarr, &buff);
    munit_assert_memory_equal(sizeof(int) * myarr.lenght, myarr.buffer, buff);
    free(buff);
    return MUNIT_OK;
}

TEST_FUNC(test_equal)
{
    int cmp[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    array(int) ma;
    ma.buffer = cmp;
    ma.lenght = myarr.lenght;

    for (int i = 0; i < myarr.lenght; i++)
        myarr.buffer[i] = i;
    bool eq = stl_array_int_equal(&myarr, &ma);
    munit_assert(eq);
    return MUNIT_OK;
}

TEST_FUNC(test_fill)
{
    int cmp[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2};

    stl_array_int_fill(&myarr, 2);
    munit_assert_memory_equal(sizeof(int) * myarr.lenght, myarr.buffer, cmp);

    return MUNIT_OK;
}

TEST_FUNC(test_find)
{
    for (int i = 0; i < myarr.lenght; i++)
        myarr.buffer[i] = i;
    int index = stl_array_int_find(&myarr, 2);
    munit_assert_int(index, ==, 2);
    return MUNIT_OK;
}

TEST_FUNC(test_find_cmp)
{
    for (int i = 0; i < myarr.lenght; i++)
        myarr.buffer[i] = i;
    int index = stl_array_int_find_cmp(&myarr, 2, cmp_int);
    munit_assert_int(index, ==, 2);
    return MUNIT_OK;
}

TEST_FUNC(test_resize)
{
    stl_array_int_resize(&myarr, INIT_LEN * 2);
    munit_assert_int(myarr.lenght, =, INIT_LEN * 2);
    return MUNIT_OK;
}

TEST_FUNC(test_count)
{
    int eeven = 0;
    for (int i = 0; i < myarr.lenght; i++)
    {
        myarr.buffer[i] = i % 2;
        eeven += i % 2;
    }
    int c = stl_array_int_count(&myarr, 1);
    munit_assert_int(eeven, =, c);
    return MUNIT_OK;
}

TEST_FUNC(test_count_cmp)
{
    int eeven = 0;
    for (int i = 0; i < myarr.lenght; i++)
    {
        myarr.buffer[i] = i % 2;
        eeven += i % 2;
    }
    int c = stl_array_int_count_cmp(&myarr, 1, cmp_int);
    munit_assert_int(eeven, =, c);
    return MUNIT_OK;
}

TEST_FUNC(test_all)
{
    bool a = stl_array_int_all(&myarr, 0);
    stl_array_int_set(&myarr, 1, 2);
    bool b = stl_array_int_all(&myarr, 0);

    munit_assert(a);
    munit_assert(b == false);
    return MUNIT_OK;
}

TEST_FUNC(test_all_cmp)
{
    bool a = stl_array_int_all(&myarr, 0);
    stl_array_int_set(&myarr, 1, 2);
    bool b = stl_array_int_all(&myarr, 0);

    munit_assert(a);
    munit_assert(b == false);
    return MUNIT_OK;
}

TEST_FUNC(test_join)
{
    array_int_t jarr;
    int cmp_arr[INIT_LEN * 2];
    stl_array_int_create(&jarr, INIT_LEN);
    for (size_t i = 0; i < INIT_LEN; i++)
    {
        stl_array_int_set(&jarr, i, i);
        stl_array_int_set(&myarr, i, i);
        cmp_arr[i] = i;
        cmp_arr[i + INIT_LEN] = i;
    }

    stl_array_int_join(&myarr, &jarr, myarr.lenght, jarr.lenght);
    munit_assert_memory_equal(INIT_LEN * 2, myarr.buffer, cmp_arr);
    return MUNIT_OK;
}

TEST_FUNC(test_reverse)
{
    int cmp_arr[INIT_LEN];
    for (size_t i = 0; i < INIT_LEN; i++)
    {
        stl_array_int_set(&myarr, i, i);
        cmp_arr[INIT_LEN - (i + 1)] = i;
    }
}

static MunitTest tests[] = {
    TEST("/insert", test_insert),
    TEST("/set", test_set),
    TEST("/remove", test_remove),
    TEST("/get", test_get),
    TEST("/first", test_first),
    TEST("/copy", test_copy),
    TEST("/clone", test_clone),
    TEST("/equal", test_equal),
    TEST("/fill", test_fill),
    TEST("/find", test_find),
    TEST("/test_find_cmp", test_find_cmp),
    TEST("/test_resize", test_resize),
    TEST("/test_count", test_count),
    TEST("/test_all", test_all),
    TEST("/test_all_cmp", test_all_cmp),
    TEST("/test_join", test_join),
    TEST("/test_reverse", test_reverse),
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

MunitSuite array_suite = {"/array", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};
