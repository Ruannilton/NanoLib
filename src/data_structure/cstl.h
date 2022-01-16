#ifndef __CSTL_H__
#define __CSTL_H__

#ifndef CSTL_NO_STD

#include <stdlib.h>
#include <string.h>

#define cstl_malloc malloc

#define cstl_free free

#define cstl_realloc realloc

#define cstl_memmove memmove

#define cstl_memcpy memcpy

#define cstl_memcmp memcmp

#else

#ifndef cstl_malloc
#error when CSTL_NO_STD is defined cstl_malloc need to be manually defined. ex: #define cstl_malloc my_malloc_func
#endif

#ifndef cstl_free
#error when CSTL_NO_STD is defined cstl_free need to be manually defined. ex: #define cstl_free my_free_func
#endif

#ifndef cstl_realloc
#error when CSTL_NO_STD is defined cstl_realloc need to be manually defined. ex: #define cstl_realloc my_realloc_func
#endif

#ifndef cstl_memmove
#error when CSTL_NO_STD is defined cstl_memmove need to be manually defined. ex: #define cstl_memmove my_memmmove_func
#endif

#ifndef cstl_memcpy
#error when CSTL_NO_STD is defined cstl_memcpy need to be manually defined. ex: #define cstl_memcpy my_memcpy_func
#endif

#ifndef cstl_memcmp
#error when CSTL_NO_STD is defined cstl_memcmp need to be manually defined. ex: #define cstl_memmove my_memmmove_func
#endif

#endif

#include "internal/slt_foreach_macro.h"

#include "definitions/stl_array.h"
#include "definitions/stl_vector.h"
#include "definitions/stl_hash.h"
#include "definitions/stl_linked_list.h"

#include "implementation/stl_core.h"
#include "implementation/stl_array.h"
#include "implementation/stl_vector.h"
#include "implementation/stl_hash.h"
#include "implementation/stl_linked_list.h"

#endif