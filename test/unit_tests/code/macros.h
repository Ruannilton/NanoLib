#ifndef __TEST_MACROS_H__
#define __TEST_MACROS_H__

#define TEST(name, function)                                       \
    {                                                              \
        name, function, setup, clear, MUNIT_TEST_OPTION_NONE, NULL \
    }

#define TEST_FUNC(name) static MunitResult name(const MunitParameter params[], void *user_data)

#define INIT_LEN 10

#endif