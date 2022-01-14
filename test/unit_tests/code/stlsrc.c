#define CSTL_IMPLEMENT
#include "data_structure/cstl.h"

stl_core_implement(int);
stl_implement_vector(int);
stl_implement_array(int);
stl_implement_linked_list(int);

typedef char *string;

stl_implement_hash_table(string, string);