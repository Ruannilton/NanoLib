#ifndef STL_UTILS_HASHF_H
#define STL_UTILS_HASHF_H

#include <inttypes.h>

// djb2, sdbm:
// http://www.cse.yorku.ca/~oz/hash.html

#ifdef CSTL_IMPLEMENT

uintmax_t cstl_djb2_str(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c;

    return hash;
}

uintmax_t cstl_djb2_32(unsigned char *str)
{
    unsigned long hash = 5381;

    for (int32_t i = 0; i < 4; i++)
    {
        int c = *str++;
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

uintmax_t cstl_djb2_64(unsigned char *str)
{
    unsigned long hash = 5381;

    for (int32_t i = 0; i < 8; i++)
    {
        int c = *str++;
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

uintmax_t cstl_sdbm_str(unsigned char *str)
{
    unsigned long hash = 0;
    int c;

    while (c = *str++)
        hash = c + (hash << 6) + (hash << 16) - hash;

    return hash;
}

uintmax_t cstl_sdbm_32(unsigned char *str)
{
    unsigned long hash = 0;
    int c;

    for (int32_t i = 0; i < 4; i++)
    {
        int c = *str++;
        hash = c + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

uintmax_t cstl_sdbm_64(unsigned char *str)
{
    unsigned long hash = 0;

    for (int32_t i = 0; i < 8; i++)
    {
        int c = *str++;
        hash = c + (hash << 6) + (hash << 16) - hash;
    }

    return hash;
}

#else
uintmax_t cstl_djb2_str(unsigned char *str);
uintmax_t cstl_djb2_32(unsigned char *str);
uintmax_t cstl_djb2_64(unsigned char *str);
uintmax_t cstl_sdbm_str(unsigned char *str);
uintmax_t cstl_sdbm_32(unsigned char *str);
uintmax_t cstl_sdbm_64(unsigned char *str);
#endif

#endif