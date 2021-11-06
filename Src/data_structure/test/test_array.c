#include "munit/munit.h"
#include "../stl_array.h"

#define TEST(name, function)                                       \
    {                                                              \
        name, function, setup, clear, MUNIT_TEST_OPTION_NONE, NULL \
    }

stl_declare_array(int);

#define INIT_LEN 10

array(int) myarr;

static void *setup(const MunitParameter params[], void *user_data)
{

    stl_array_int_create(&myarr);

    for (int i = 0; i < myarr.lenght; i++)
        myarr.buffer[i] = 0;
    return 0;
}

static void clear(void *data)
{
    free(myarr.buffer);
}

static MunitResult test_insert(const MunitParameter params[], void *user_data)
{
    int v = munit_rand_uint32();
    stl_array_int_insert(&myarr, v, 0);
    munit_assert_int(myarr.buffer[0], ==, v);
    return MUNIT_OK;
}

static MunitResult test_set(const MunitParameter params[], void *user_data)
{
    int v = munit_rand_uint32();
    stl_array_int_set(&myarr, v, 3);
    munit_assert_int(myarr.buffer[3], ==, v);
    return MUNIT_OK;
}

static MunitResult test_remove(const MunitParameter params[], void *user_data)
{
    int cmp[] = {0, 1, 2, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < myarr.lenght; i++)
    {
        stl_array_int_set(&myarr, i, i);
        myarr.lenght++;
    }
    stl_array_int_remove(&myarr, 3);
    munit_assert_memory_equal(myarr.lenght * sizeof(int), myarr.buffer, cmp);
    return MUNIT_OK;
}

static const MunitTest tests[] = {
    TEST("/insert", test_insert),
    TEST("/set", test_set),
    TEST("/remove", test_remove),
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

MunitSuite array_suite = {"/array", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};
