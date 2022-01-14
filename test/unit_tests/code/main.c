#include "munit.h"
#include <stdio.h>

extern MunitSuite core_suite;
extern MunitSuite array_suite;
extern MunitSuite vector_suite;
extern MunitSuite hash_suite;
extern MunitSuite list_suite;

int main(int argc, char *const argv[])
{
   munit_suite_main(&core_suite, NULL, argc, argv);
   printf("\n");
   munit_suite_main(&array_suite, NULL, argc, argv);
   printf("\n");
   munit_suite_main(&vector_suite, NULL, argc, argv);
   printf("\n");
   munit_suite_main(&hash_suite, NULL, argc, argv);
   printf("\n");
   munit_suite_main(&list_suite, NULL, argc, argv);
   printf("\n");
   return 0;
}