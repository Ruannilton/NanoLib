#include "munit.h"
#include "data_structure/cstl.h"
#include "macros.h"

typedef char *string;

stl_declare_hash_table(string, string);

hash_map(string, string) myhash;

uintmax_t hashfn(char *key)
{
    uintmax_t k = 0;
    char *c = key;
    size_t len = strlen(key);
    for (size_t i = 0; i < len; i++)
    {
        k += (int)(c[i]);
    }
    return k;
}
bool hashcmp(char *a, char *b)
{
    return strcmp(a, b) == 0;
}

static void *setup(const MunitParameter params[], void *user_data)
{
    hash_map_create(string, string)(&myhash, 16, hashfn, hashcmp);
    return 0;
}

static void clear(void *data)
{
    hash_map_delete(string, string)(&myhash);
}

TEST_FUNC(test_add)
{
    hash_map_add(string, string)(&myhash, "Ruan", "Azevedo");
    hash_map_add(string, string)(&myhash, "Vic", "França");

    bool er = hash_map_exist(string, string)(&myhash, "Ruan");
    bool ev = hash_map_exist(string, string)(&myhash, "Vic");

    munit_assert(er);
    munit_assert(ev);

    return MUNIT_OK;
}

TEST_FUNC(test_remove)
{
    hash_map_add(string, string)(&myhash, "Ruan", "Azevedo");
    hash_map_add(string, string)(&myhash, "Vic", "França");

    hash_map_remove(string, string)(&myhash, "Ruan");
    hash_map_remove(string, string)(&myhash, "Vic");

    bool et = hash_map_remove(string, string)(&myhash, "Thau");
    bool er = hash_map_exist(string, string)(&myhash, "Ruan");
    bool ev = hash_map_exist(string, string)(&myhash, "Vic");

    munit_assert(!et);
    munit_assert(!er);
    munit_assert(!ev);

    return MUNIT_OK;
}

TEST_FUNC(test_get)
{
    char *out;
    hash_map_add(string, string)(&myhash, "Ruan", "Azevedo");
    bool found = hash_map_get(string, string)(&myhash, "Ruan", &out);
    if (found)
    {
        bool eq = (strcmp(out, "Azevedo") == 0);
        munit_assert(eq);
    }
    munit_assert(found);
    return MUNIT_OK;
}

TEST_FUNC(test_clear)
{
    char *out;
    hash_map_add(string, string)(&myhash, "Ruan", "Azevedo");
    hash_map_clear(string, string)(&myhash);

    bool founded = hash_map_get(string, string)(&myhash, "Ruan", &out);

    munit_assert(!founded);
    return MUNIT_OK;
}

static MunitTest tests[] = {
    TEST("/test_add", test_add),
    TEST("/test_remove", test_remove),
    TEST("/test_get", test_get),
    TEST("/test_clear", test_clear),
};

MunitSuite hash_suite = {"/hash", tests, NULL, 1, MUNIT_SUITE_OPTION_NONE};