#include "munit.h"
#include <stdio.h>

extern MunitSuite core_suite;
extern MunitSuite array_suite;

int main(int argc, char *const argv[])
{
   munit_suite_main(&core_suite, NULL, argc, argv);
   printf("\n");
   munit_suite_main(&array_suite, NULL, argc, argv);

   return 0;
}