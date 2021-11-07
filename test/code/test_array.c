#include "munit.h"
#include "data_structure/stl_array.h"

#define TEST(name, function)                                       \
    {                                                              \
        name, function, setup, clear, MUNIT_TEST_OPTION_NONE, NULL \
    }

stl_declare_array(int);

#define INIT_LEN 10

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

static MunitResult test_get(const MunitParameter params[], void *user_data)
{
    for (int i = 0; i < myarr.lenght; i++)
        myarr.buffer[i] = i;

    int val = stl_array_int_get(&myarr, 1);
    munit_assert_int(1, ==, val);
    return MUNIT_OK;
}

static MunitResult test_first(const MunitParameter params[], void *user_data)
{
    for (int i = 0; i < myarr.lenght; i++)
        myarr.buffer[i] = munit_rand_uint32();

    int v0 = stl_array_int_first(&myarr);
    int i0 = myarr.buffer[0];
    munit_assert_int(v0, ==, i0);
    return MUNIT_OK;
}

static MunitResult test_copy(const MunitParameter params[], void *user_data)
{
    for (int i = 0; i < myarr.lenght; i++)
        myarr.buffer[i] = munit_rand_uint32();

    int *buff = (int *)malloc(sizeof(int) * 5);
    stl_array_int_copy(&myarr, &buff, 0, 5);
    munit_assert_memory_equal(sizeof(int) * 5, myarr.buffer, buff);
    free(buff);
    return MUNIT_OK;
}

static MunitResult test_clone(const MunitParameter params[], void *user_data)
{
    for (int i = 0; i < myarr.lenght; i++)
        myarr.buffer[i] = munit_rand_uint32();

    int *buff = (int *)malloc(sizeof(int) * myarr.lenght);
    stl_array_int_clone(&myarr, &buff);
    munit_assert_memory_equal(sizeof(int) * myarr.lenght, myarr.buffer, buff);
    free(buff);
    return MUNIT_OK;
}

static MunitResult test_equal(const MunitParameter params[], void *user_data)
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

static MunitResult test_fill(const MunitParameter params[], void *user_data)
{
    int cmp[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2};

    stl_array_int_fill(&myarr, 2);
    munit_assert_memory_equal(sizeof(int) * myarr.lenght, myarr.buffer, cmp);

    return MUNIT_OK;
}

static MunitResult test_find(const MunitParameter params[], void *user_data)
{
    for (int i = 0; i < myarr.lenght; i++)
        myarr.buffer[i] = i;
    int index = stl_array_int_find(&myarr, 2);
    munit_assert_int(index, ==, 2);
    return MUNIT_OK;
}

static const MunitTest tests[] = {
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
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

MunitSuite array_suite = {"/array", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};
