#include "munit.h"
#include "data_structure/cstl.h"
#include "macros.h"

stl_declare_linked_list(int);

linked_list(int) mylist;

static void *setup(const MunitParameter params[], void *user_data)
{
    linked_list_create(int)(&mylist, 0);
}

static void clear(void *data)
{
    linked_list_free(int)(&mylist, 0);
}

bool cmp_int(int a, int b)
{
    return a == b;
}

TEST_FUNC(test_add)
{
    linked_list_add(int)(&mylist, -5);
    int value = linked_list_get(int)(&mylist, 0);

    munit_assert_int(value, ==, -5);
    munit_assert_int(mylist.count, ==, 1);

    return MUNIT_OK;
}

TEST_FUNC(test_all)
{
    linked_list_add(int)(&mylist, 1);
    linked_list_add(int)(&mylist, 1);
    linked_list_add(int)(&mylist, 1);
    linked_list_add(int)(&mylist, 1);

    bool eq1 = linked_list_all(int)(&mylist, 1);
    bool eq2 = linked_list_all(int)(&mylist, 2);

    munit_assert(eq1);
    munit_assert(!eq2);

    return MUNIT_OK;
}

TEST_FUNC(test_all_cmp)
{
    linked_list_add(int)(&mylist, 1);
    linked_list_add(int)(&mylist, 1);
    linked_list_add(int)(&mylist, 1);
    linked_list_add(int)(&mylist, 1);

    bool eq1 = linked_list_all_cmp(int)(&mylist, 1, cmp_int);
    bool eq2 = linked_list_all_cmp(int)(&mylist, 2, cmp_int);

    munit_assert(eq1);
    munit_assert(!eq2);

    return MUNIT_OK;
}

TEST_FUNC(test_clone)
{
    linked_list(int) out;
    linked_list(int) *pout = &out;

    linked_list_add(int)(&mylist, 1);
    linked_list_add(int)(&mylist, 2);
    linked_list_add(int)(&mylist, 3);
    linked_list_add(int)(&mylist, 4);

    linked_list_clone(int)(&mylist, &pout);

    munit_assert(mylist.count == out.count);

    bool eq = linked_list_equal(int)(&mylist, pout);
    munit_assert(eq);

    linked_list_free(int)(pout, 0);
    return MUNIT_OK;
}

TEST_FUNC(test_copy)
{
    linked_list(int) out;
    linked_list(int) *pout = &out;

    linked_list_add(int)(&mylist, 1);
    linked_list_add(int)(&mylist, 2);
    linked_list_add(int)(&mylist, 3);
    linked_list_add(int)(&mylist, 4);
    linked_list_add(int)(&mylist, 5);
    linked_list_add(int)(&mylist, 6);

    linked_list_copy(int)(&mylist, &pout, 1, 5);

    for (size_t i = 1; i < mylist.count - 1; i++)
    {
        int a = linked_list_get(int)(&mylist, i);
        int b = linked_list_get(int)(&out, i - 1);
        munit_assert_int(a, ==, b);
    }

    linked_list_free(int)(pout, 0);
    return MUNIT_OK;
}

TEST_FUNC(test_count)
{
    linked_list_add(int)(&mylist, 1);
    linked_list_add(int)(&mylist, 2);
    linked_list_add(int)(&mylist, 1);
    linked_list_add(int)(&mylist, 4);
    linked_list_add(int)(&mylist, 1);
    linked_list_add(int)(&mylist, 6);

    int cc = linked_list_count(int)(&mylist, 1);

    munit_assert_int(cc, ==, 3);
    return MUNIT_OK;
}

TEST_FUNC(test_count_cmp)
{
    linked_list_add(int)(&mylist, 1);
    linked_list_add(int)(&mylist, 2);
    linked_list_add(int)(&mylist, 1);
    linked_list_add(int)(&mylist, 4);
    linked_list_add(int)(&mylist, 1);
    linked_list_add(int)(&mylist, 6);

    int cc = linked_list_count_cmp(int)(&mylist, 1, cmp_int);

    munit_assert_int(cc, ==, 3);
    return MUNIT_OK;
}

TEST_FUNC(test_insert)
{
    linked_list_add(int)(&mylist, 1);
    linked_list_add(int)(&mylist, 2);
    linked_list_add(int)(&mylist, 3);

    linked_list_insert(int)(&mylist, 0, 0);

    int v = linked_list_first(int)(&mylist);

    munit_assert_int(v, ==, 0);
    return MUNIT_OK;
}

TEST_FUNC(test_set)
{
    linked_list_add(int)(&mylist, 1);
    linked_list_add(int)(&mylist, 2);
    linked_list_add(int)(&mylist, 3);

    linked_list_set(int)(&mylist, -1, 1);

    int v = linked_list_get(int)(&mylist, 1);

    munit_assert_int(v, ==, -1);
    return MUNIT_OK;
}

TEST_FUNC(test_remove)
{
    linked_list_add(int)(&mylist, 1);
    linked_list_add(int)(&mylist, 2);
    linked_list_add(int)(&mylist, 3);
    linked_list_add(int)(&mylist, 4);

    for (size_t i = 0; i < 3; i++)
    {
        int r = linked_list_remove(int)(&mylist, 0);

        int v = linked_list_get(int)(&mylist, 0);

        munit_assert_int(r, ==, i + 1);
        munit_assert_int(v, ==, r + 1);
    }

    return MUNIT_OK;
}

TEST_FUNC(test_join)
{
    linked_list(int) a, b, ab;
    linked_list_create(int)(&a, 0);
    linked_list_create(int)(&b, 0);
    linked_list_create(int)(&ab, 0);

    linked_list_add(int)(&a, 1);
    linked_list_add(int)(&a, 2);
    linked_list_add(int)(&a, 3);

    linked_list_add(int)(&b, 4);
    linked_list_add(int)(&b, 5);
    linked_list_add(int)(&b, 6);

    linked_list_add(int)(&ab, 1);
    linked_list_add(int)(&ab, 2);
    linked_list_add(int)(&ab, 3);
    linked_list_add(int)(&ab, 4);
    linked_list_add(int)(&ab, 5);
    linked_list_add(int)(&ab, 6);

    linked_list_join(int)(&a, &b, 3, 3);
    bool eq = linked_list_equal(int)(&a, &ab);

    linked_list_free(int)(&a, 0);
    linked_list_free(int)(&b, 0);
    linked_list_free(int)(&ab, 0);

    munit_assert(eq);
    return MUNIT_OK;
}

TEST_FUNC(test_reverse)
{
    linked_list(int) a, b;
    linked_list_create(int)(&a, 0);
    linked_list_create(int)(&b, 0);

    linked_list_add(int)(&a, 1);
    linked_list_add(int)(&a, 2);
    linked_list_add(int)(&a, 3);

    linked_list_add(int)(&b, 3);
    linked_list_add(int)(&b, 2);
    linked_list_add(int)(&b, 1);

    linked_list_reverse(int)(&a);
    bool eq = linked_list_equal(int)(&a, &b);

    linked_list_free(int)(&a, 0);
    linked_list_free(int)(&b, 0);

    munit_assert(eq);

    return MUNIT_OK;
}

static MunitTest tests[] = {
    TEST("/add", test_add),
    TEST("/all", test_all),
    TEST("/all_cmp", test_all_cmp),
    TEST("/clone", test_clone),
    TEST("/copy", test_copy),
    TEST("/count", test_count),
    TEST("/count_cmp", test_count_cmp),
    TEST("/remove", test_remove),
    TEST("/insert", test_insert),
    TEST("/set", test_set),
    TEST("/join", test_join),
    TEST("/reverse", test_reverse),
};

MunitSuite list_suite = {"/linked_list", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};