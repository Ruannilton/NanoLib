#include "munit.h"
#include "data_structure/cstl.h"
#include "macros.h"

stl_declare_vector(int);

vector(int) myvec;

static void *setup(const MunitParameter params[], void *user_data)
{

    stl_vector_int_create(&myvec, INIT_LEN);

    for (int i = 0; i < myvec.lenght; i++)
        myvec.buffer[i] = 0;
    return 0;
}

static void clear(void *data)
{
    free(myvec.buffer);
}

static bool cmp_int(int a, int b)
{
    return a == b;
}

TEST_FUNC(test_insert)
{
    stl_vector_int_push_back(&myvec, 5);
    stl_vector_int_push_back(&myvec, 6);
    stl_vector_int_insert(&myvec, 9, 1);
    munit_assert_int(myvec.buffer[1], ==, 9);
    munit_assert_int(myvec.buffer[2], ==, 6);
    return MUNIT_OK;
}

TEST_FUNC(test_set)
{
    stl_vector_int_push_back(&myvec, 5);
    stl_vector_int_set(&myvec, 3, 0);
    munit_assert_int(myvec.buffer[0], ==, 3);
    return MUNIT_OK;
}

TEST_FUNC(test_copy)
{
    vector(int) cpvec;
    stl_vector_int_create(&cpvec, INIT_LEN);
    stl_vector_int_set(&myvec, 3, 5);
    stl_vector_int_copy(&myvec, &cpvec, 0, INIT_LEN);
    munit_assert_memory_equal(cpvec.count, myvec.buffer, cpvec.buffer);
    free(cpvec.buffer);
    return MUNIT_OK;
}

TEST_FUNC(test_clone)
{
    vector(int) cpvec;
    stl_vector_int_create(&cpvec, INIT_LEN);
    stl_vector_int_set(&myvec, 3, 5);
    stl_vector_int_clone(&myvec, &cpvec);
    munit_assert_memory_equal(cpvec.count, myvec.buffer, cpvec.buffer);
    free(cpvec.buffer);
    return MUNIT_OK;
}

TEST_FUNC(test_equal)
{
    vector(int) cpvec;
    stl_vector_int_create(&cpvec, INIT_LEN);
    stl_vector_int_set(&myvec, 3, 5);
    stl_vector_int_clone(&myvec, &cpvec);
    bool eq = stl_vector_int_equal(&cpvec, &myvec);
    munit_assert(eq);
    free(cpvec.buffer);
    return MUNIT_OK;
}

TEST_FUNC(test_remove)
{
    stl_vector_int_push_back(&myvec, 1);
    stl_vector_int_push_back(&myvec, 2);
    stl_vector_int_push_back(&myvec, 3);
    stl_vector_int_remove(&myvec, 1);
    munit_assert_int(myvec.buffer[1], ==, 3);
    return MUNIT_OK;
}

TEST_FUNC(test_get)
{
    stl_vector_int_push_back(&myvec, 5);
    int f = stl_vector_int_get(&myvec, 0);
    munit_assert_int(f, ==, 5);
    munit_assert_int(myvec.count, ==, 1);
    return MUNIT_OK;
}

TEST_FUNC(test_first)
{
    stl_vector_int_push_back(&myvec, 5);
    int f = stl_vector_int_first(&myvec);
    munit_assert_int(myvec.count, ==, 1);
    munit_assert_int(f, ==, 5);
    return MUNIT_OK;
}

TEST_FUNC(test_last)
{
    stl_vector_int_push_back(&myvec, 5);
    stl_vector_int_push_back(&myvec, 7);
    int f = stl_vector_int_last(&myvec);
    munit_assert_int(myvec.count, ==, 2);
    munit_assert_int(f, ==, 7);
    return MUNIT_OK;
}

TEST_FUNC(test_push_front)
{
    stl_vector_int_push_front(&myvec, 5);
    stl_vector_int_push_front(&myvec, 7);
    int f = stl_vector_int_first(&myvec);
    munit_assert_int(myvec.count, ==, 2);
    munit_assert_int(f, ==, 7);
    return MUNIT_OK;
}

TEST_FUNC(test_push_back)
{
    stl_vector_int_push_back(&myvec, 5);
    stl_vector_int_push_back(&myvec, 7);
    int f = stl_vector_int_get(&myvec, 1);
    munit_assert_int(myvec.count, ==, 2);
    munit_assert_int(f, ==, 7);
    return MUNIT_OK;
}

TEST_FUNC(test_pop_front)
{
    stl_vector_int_push_back(&myvec, 5);
    stl_vector_int_push_back(&myvec, 7);
    stl_vector_int_pop_front(&myvec);
    int f = stl_vector_int_first(&myvec);
    munit_assert_int(myvec.count, ==, 1);
    munit_assert_int(f, ==, 7);
    return MUNIT_OK;
}

TEST_FUNC(test_pop_back)
{
    stl_vector_int_push_back(&myvec, 5);
    stl_vector_int_push_back(&myvec, 7);
    stl_vector_int_push_back(&myvec, 3);
    stl_vector_int_push_back(&myvec, 12);
    stl_vector_int_pop_back(&myvec);
    int f = stl_vector_int_get(&myvec, myvec.count - 1);
    munit_assert_int(myvec.count, ==, 3);
    munit_assert_int(f, ==, 3);
    return MUNIT_OK;
}

TEST_FUNC(test_fill)
{
    int cmp[INIT_LEN] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    stl_vector_int_fill(&myvec, 1);
    munit_assert_memory_equal(INIT_LEN, cmp, myvec.buffer);
    return MUNIT_OK;
}

TEST_FUNC(test_find)
{
    stl_vector_int_push_back(&myvec, 5);
    stl_vector_int_push_back(&myvec, 7);
    stl_vector_int_push_back(&myvec, 3);
    stl_vector_int_push_back(&myvec, 12);
    int idx = stl_vector_int_find(&myvec, 3);
    munit_assert_int(idx, ==, 2);
    return MUNIT_OK;
}

TEST_FUNC(test_find_cmp)
{
    stl_vector_int_push_back(&myvec, 5);
    stl_vector_int_push_back(&myvec, 7);
    stl_vector_int_push_back(&myvec, 3);
    stl_vector_int_push_back(&myvec, 12);
    int idx = stl_vector_int_find_cmp(&myvec, 3, cmp_int);
    munit_assert_int(idx, ==, 2);
    return MUNIT_OK;
}

TEST_FUNC(test_resize)
{
    stl_vector_int_resize(&myvec, INIT_LEN * 2);
    munit_assert_int(myvec.lenght, =, INIT_LEN * 2);
    return MUNIT_OK;
}

TEST_FUNC(test_count)
{
    int eeven = 0;
    for (int i = 0; i < INIT_LEN; i++)
    {
        stl_vector_int_push_back(&myvec, i % 2);
        eeven += i % 2;
    }
    int c = stl_vector_int_count(&myvec, 1);
    munit_assert_int(eeven, =, c);
    return MUNIT_OK;
}

TEST_FUNC(test_count_cmp)
{
    int eeven = 0;
    for (int i = 0; i < INIT_LEN; i++)
    {
        stl_vector_int_push_back(&myvec, i % 2);
        eeven += i % 2;
    }
    int c = stl_vector_int_count_cmp(&myvec, 1, cmp_int);
    munit_assert_int(eeven, =, c);
    return MUNIT_OK;
}

TEST_FUNC(test_all)
{
    bool a = stl_vector_int_all(&myvec, 0);
    stl_vector_int_push_back(&myvec, 1);
    bool b = stl_vector_int_all(&myvec, 0);

    munit_assert(a);
    munit_assert(b == false);
    return MUNIT_OK;
}

TEST_FUNC(test_all_cmp)
{
    bool a = stl_vector_int_all(&myvec, 0);
    stl_vector_int_push_back(&myvec, 1);
    bool b = stl_vector_int_all(&myvec, 0);

    munit_assert(a);
    munit_assert(b == false);
    return MUNIT_OK;
}

TEST_FUNC(test_join)
{
    vector(int) jarr;
    int cmp_arr[INIT_LEN * 2];
    stl_vector_int_create(&jarr, INIT_LEN);
    for (size_t i = 0; i < INIT_LEN; i++)
    {
        stl_vector_int_push_back(&myvec, i);
        stl_vector_int_push_back(&jarr, i);
        cmp_arr[i] = i;
        cmp_arr[i + INIT_LEN] = i;
    }

    stl_vector_int_join(&myvec, &jarr, myvec.lenght, jarr.lenght);
    munit_assert_memory_equal(INIT_LEN * 2, myvec.buffer, cmp_arr);
    return MUNIT_OK;
}

TEST_FUNC(test_reverse)
{
    int cmp_arr[INIT_LEN];
    for (size_t i = 0; i < INIT_LEN; i++)
    {
        stl_vector_int_set(&myvec, i, i);
        cmp_arr[INIT_LEN - (i + 1)] = i;
    }
}

static MunitTest tests[] = {
    TEST("/test_insert", test_insert),
    TEST("/test_set", test_set),
    TEST("/test_remove", test_remove),
    TEST("/test_get", test_get),
    TEST("/test_first", test_first),
    TEST("/test_last", test_last),
    TEST("/test_push_front", test_push_front),
    TEST("/test_push_back", test_push_back),
    TEST("/test_pop_front", test_pop_front),
    TEST("/test_pop_back", test_pop_back),
    TEST("/test_copy", test_copy),
    TEST("/test_clone", test_clone),
    TEST("/test_equal", test_equal),
    TEST("/test_fill", test_fill),
    TEST("/test_find", test_find),
    TEST("/test_find_cmp", test_find_cmp),
    TEST("/test_count", test_count),
    TEST("/test_count_cmp", test_count_cmp),
    TEST("/test_all", test_all),
    TEST("/test_all_cmp", test_all_cmp),
    TEST("/test_join", test_join),
    TEST("/test_reverse", test_reverse),
};

MunitSuite vector_suite = {"/vector", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};