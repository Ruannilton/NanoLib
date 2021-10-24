#include "munit/munit.h"
#include "../stl_core.h"

#define TEST(name, function)                                       \
    {                                                              \
        name, function, setup, clear, MUNIT_TEST_OPTION_NONE, NULL \
    }

stl_declare(int);

#define INIT_LEN 10

static struct
{
    int *arr;
    size_t len;
} myarr = {0, INIT_LEN};

static void *setup(const MunitParameter params[], void *user_data)
{
    myarr.len = INIT_LEN;
    stl_core_int_create(&(myarr.arr), myarr.len);
    for (int i = 0; i < myarr.len; i++)
        myarr.arr[i] = 0;
    return 0;
}

static bool cmp_int(int a, int b)
{
    return a == b;
}

static void clear(void *data)
{
    free(myarr.arr);
}

static MunitResult test_grow(const MunitParameter params[], void *user_data)
{
    stl_core_int_grow(&myarr.arr, &myarr.len);
    munit_assert_int(myarr.len, ==, 15);
    return MUNIT_OK;
}

static MunitResult test_push_back(const MunitParameter params[], void *user_data)
{
    size_t index = 0;
    int cmp[myarr.len];
    for (size_t i = 0; i < myarr.len; i++)
    {
        int val = (int)munit_rand_uint32();
        stl_core_int_push_back(myarr.arr, val, &index);
        int val_acessed = myarr.arr[i];
        munit_assert_int(index, ==, i + 1);
        munit_assert_int(val, ==, val_acessed);
        cmp[i] = val;
    }
    munit_assert_memory_equal(sizeof(int) * myarr.len, cmp, myarr.arr);
    return MUNIT_OK;
}

static MunitResult test_insert(const MunitParameter params[], void *user_data)
{
    int cmp[myarr.len];
    for (size_t i = 0; i < myarr.len; i++)
    {
        int val = (int)munit_rand_uint32();
        stl_core_int_insert(myarr.arr, val, 0, myarr.len);
        int val_acessed = myarr.arr[0];
        munit_assert_int(val, ==, val_acessed);
        cmp[(myarr.len - 1) - i] = val;
    }
    munit_assert_memory_equal(sizeof(int) * myarr.len, cmp, myarr.arr);
    return MUNIT_OK;
}

static MunitResult test_push_front(const MunitParameter params[], void *user_data)
{
    int cmp[myarr.len];
    for (size_t i = 0; i < myarr.len; i++)
    {
        int val = (int)munit_rand_uint32();
        stl_core_int_push_front(myarr.arr, val, myarr.len);
        int val_acessed = myarr.arr[0];
        munit_assert_int(val, ==, val_acessed);
        cmp[(myarr.len - 1) - i] = val;
    }
    munit_assert_memory_equal(sizeof(int) * myarr.len, cmp, myarr.arr);
    return MUNIT_OK;
}

static MunitResult test_set(const MunitParameter params[], void *user_data)
{
    stl_core_int_set(myarr.arr, 2, 1);
    int val = myarr.arr[1];
    munit_assert_int(val, ==, 2);
    return MUNIT_OK;
}

static MunitResult test_pop_front(const MunitParameter params[], void *user_data)
{
    stl_core_int_push_front(myarr.arr, 0, myarr.len);
    stl_core_int_push_front(myarr.arr, 1, myarr.len);
    stl_core_int_push_front(myarr.arr, 2, myarr.len);
    stl_core_int_pop_front(myarr.arr, myarr.len);
    stl_core_int_pop_front(myarr.arr, myarr.len);
    int val = myarr.arr[0];
    munit_assert_int(val, ==, 0);
    return MUNIT_OK;
}

static MunitResult test_remove(const MunitParameter params[], void *user_data)
{
    stl_core_int_push_front(myarr.arr, 0, myarr.len);
    stl_core_int_push_front(myarr.arr, 1, myarr.len);
    stl_core_int_push_front(myarr.arr, 2, myarr.len);
    stl_core_int_remove(myarr.arr, 0, myarr.len);
    int first = myarr.arr[0];
    munit_assert_int(first, ==, 1);
    return MUNIT_OK;
}

static MunitResult test_get(const MunitParameter params[], void *user_data)
{
    stl_core_int_push_front(myarr.arr, 0, myarr.len);
    stl_core_int_push_front(myarr.arr, 1, myarr.len);
    stl_core_int_push_front(myarr.arr, 2, myarr.len);
    stl_core_int_remove(myarr.arr, 0, myarr.len);
    int first = stl_core_int_get(myarr.arr, 0);
    munit_assert_int(first, ==, 1);
    return MUNIT_OK;
}

static MunitResult test_first(const MunitParameter params[], void *user_data)
{
    stl_core_int_push_front(myarr.arr, 0, myarr.len);
    stl_core_int_push_front(myarr.arr, 1, myarr.len);
    stl_core_int_push_front(myarr.arr, 2, myarr.len);
    stl_core_int_remove(myarr.arr, 0, myarr.len);
    int first = stl_core_int_first(myarr.arr);
    munit_assert_int(first, ==, 1);
    return MUNIT_OK;
}

static MunitResult test_copy(const MunitParameter params[], void *user_data)
{
    int *buff;
    stl_core_int_push_front(myarr.arr, 0, myarr.len);
    stl_core_int_push_front(myarr.arr, 1, myarr.len);
    stl_core_int_push_front(myarr.arr, 2, myarr.len);
    stl_core_int_copy(myarr.arr, &buff, 0, 3);
    munit_assert_memory_equal(3 * sizeof(int), myarr.arr, buff);
    free(buff);
    return MUNIT_OK;
}

static MunitResult test_clone(const MunitParameter params[], void *user_data)
{
    int *buff;
    stl_core_int_push_front(myarr.arr, 0, myarr.len);
    stl_core_int_push_front(myarr.arr, 1, myarr.len);
    stl_core_int_push_front(myarr.arr, 2, myarr.len);
    stl_core_int_clone(myarr.arr, &buff, myarr.len);
    munit_assert_memory_equal(myarr.len * sizeof(int), myarr.arr, buff);
    free(buff);
    return MUNIT_OK;
}

static MunitResult test_equal(const MunitParameter params[], void *user_data)
{
    int *buff;
    stl_core_int_push_front(myarr.arr, 0, myarr.len);
    stl_core_int_push_front(myarr.arr, 1, myarr.len);
    stl_core_int_push_front(myarr.arr, 2, myarr.len);
    stl_core_int_clone(myarr.arr, &buff, myarr.len);
    munit_assert_memory_equal(myarr.len * sizeof(int), myarr.arr, buff);
    free(buff);
    return MUNIT_OK;
}

static MunitResult test_fill(const MunitParameter params[], void *user_data)
{
    int b[INIT_LEN] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    stl_core_int_fill(myarr.arr, 1, myarr.len);
    munit_assert_memory_equal(myarr.len * sizeof(int), myarr.arr, b);
    return MUNIT_OK;
}

static MunitResult test_find(const MunitParameter params[], void *user_data)
{
    for (int i = 0; i < myarr.len; i++)
        myarr.arr[i] = i;
    int index = stl_core_int_find(myarr.arr, 5, myarr.len);
    munit_assert_int(index, ==, 5);
    return MUNIT_OK;
}

static MunitResult test_find_cmp(const MunitParameter params[], void *user_data)
{
    for (int i = 0; i < myarr.len; i++)
        myarr.arr[i] = i;
    int index = stl_core_int_find_cmp(myarr.arr, 5, myarr.len, cmp_int);
    munit_assert_int(index, ==, 5);
    return MUNIT_OK;
}

static MunitResult test_resize(const MunitParameter params[], void *user_data)
{
    stl_core_int_resize(&myarr.arr, 15);
    for (size_t i = 0; i < 15; i++)
    {
        stl_core_int_set(myarr.arr, i, i);
    }
    return MUNIT_OK;
}

static MunitResult test_count(const MunitParameter params[], void *user_data)
{
    int c = 0;
    for (size_t i = 0; i < myarr.len; i++)
    {
        int n = munit_rand_int_range(0, 3);
        if (n == 2)
            c++;
        stl_core_int_set(myarr.arr, n, i);
    }
    int cc = stl_core_int_count(myarr.arr, 2, myarr.len);
    munit_assert_int(c, ==, cc);
    return MUNIT_OK;
}

static MunitResult test_count_cmp(const MunitParameter params[], void *user_data)
{
    int c = 0;
    for (size_t i = 0; i < myarr.len; i++)
    {
        int n = munit_rand_int_range(0, 3);
        if (n == 2)
            c++;
        stl_core_int_set(myarr.arr, n, i);
    }
    int cc = stl_core_int_count_cmp(myarr.arr, 2, myarr.len, cmp_int);
    munit_assert_int(c, ==, cc);
    return MUNIT_OK;
}

static MunitResult test_all(const MunitParameter params[], void *user_data)
{
    bool res = stl_core_int_all(myarr.arr, 0, myarr.len);
    munit_assert(res);
    stl_core_int_set(myarr.arr, 1, 3);
    res = stl_core_int_all(myarr.arr, 0, myarr.len);
    munit_assert(!res);
    return MUNIT_OK;
}

static MunitResult test_all_cmp(const MunitParameter params[], void *user_data)
{
    bool res = stl_core_int_all_cmp(myarr.arr, 0, myarr.len, cmp_int);
    munit_assert(res);
    stl_core_int_set(myarr.arr, 1, 3);
    res = stl_core_int_all_cmp(myarr.arr, 0, myarr.len, cmp_int);
    munit_assert(!res);
    return MUNIT_OK;
}

static MunitResult test_join(const MunitParameter params[], void *user_data)
{
    int cmp[INIT_LEN * INIT_LEN] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (size_t i = 0; i < myarr.len; i++)
    {
        stl_core_int_set(myarr.arr, i, i);
    }
    stl_core_int_join(&myarr.arr, myarr.arr, myarr.len, myarr.len);
    munit_assert_memory_equal(INIT_LEN * 2 * sizeof(int), myarr.arr, cmp);
    return MUNIT_OK;
}

static MunitResult test_reverse(const MunitParameter params[], void *user_data)
{
    int cmp[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    for (size_t i = 0; i < myarr.len; i++)
    {
        stl_core_int_set(myarr.arr, i, i);
    }
    stl_core_int_reverse(myarr.arr, myarr.len);
    munit_assert_memory_equal(INIT_LEN * sizeof(int), myarr.arr, cmp);
    return MUNIT_OK;
}

static const MunitTest tests[] = {
    TEST("/grow", test_grow),
    TEST("/push-back", test_push_back),
    TEST("/insert", test_insert),
    TEST("/push-front", test_push_front),
    TEST("/remove", test_remove),
    TEST("/pop-front", test_pop_front),
    TEST("/set", test_set),
    TEST("/get", test_get),
    TEST("/first", test_first),
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
    TEST("/join", test_join),
    TEST("/all_reverse", test_reverse),
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

MunitSuite core_suite = {"/core", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};