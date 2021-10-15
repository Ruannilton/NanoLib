#include "..\stl_array.h"
#include <stdio.h>

stl_implement(int);
stl_implement_array(int);

int main()
{
    array(int) arr;
    stl_array_int_create(&arr);
    printf("%d\n", arr.lenght);
    return 0;
}
