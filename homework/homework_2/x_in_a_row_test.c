#include <stdio.h>
#include "CuTest.h"

#define EMPTY -1

/*
  We do not test inputs that require "0-in-a-row" to win.  
  That simply doesn't make sense and there is no point in
  picking an arbitrary return value.  That would just make 
  unnecessary extra work for the students unrelated to
  learning C.
*/

/* "normal" match */

void ex_length10_full_hit(CuTest *tc) {
   int array[] = {1, 2, 1, 2, 1, 1, 1, 1, 2, 1};
   int observed = x_in_a_row(array, 10, 4);
   CuAssertIntEquals_Msg(tc, "Length 4 to win.  Array length 10.  Player 1", 1, observed);
}

void ex_length10_full_miss(CuTest *tc) {
 int array[] = {1, 2, 1, 2, 1, 2, 2, 1, 2, 1};
   int observed = x_in_a_row(array, 10, 4);
   CuAssertIntEquals_Msg(tc, "Length 4 to win.  Array length 10.  Miss", -1, observed);
}

void ex_length10_partial_miss(CuTest *tc) {
  int array[] = {1, 2, 1, EMPTY, EMPTY, 2, 2, EMPTY, EMPTY, 1};
   int observed = x_in_a_row(array, 10, 4);
   CuAssertIntEquals_Msg(tc, "Length 4 to win.  Array length 10.  Miss", -1, observed);
}

void it_ignores_four_empty_spaces(CuTest *tc) {
  int array[] = {1, 2, 1, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 1};
   int observed = x_in_a_row(array, 10, 4);
   CuAssertIntEquals_Msg(tc, "Length 4 to win.  Array length 10.  Miss", -1, observed);

}

void it_requires_a_win_length_greater_than_one(CuTest *tc) {
  int array[] = {1, 2, 1, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 1};
   int observed = x_in_a_row(array, 10, 1);
   CuAssertIntEquals_Msg(tc, "Length to win must be greater than 1.", -1, observed);
}

void it_requires_rows_greater_than_zero(CuTest *tc) {
  int array[] = {1, 2, 1, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, 1};
   int observed = x_in_a_row(array, 0, 3);
   CuAssertIntEquals_Msg(tc, "Row must be greater than 0", -1, observed);
}


void ex_length_zero_array_always_false(CuTest *tc) {
   int array[] = {};
   int observed;
   observed = x_in_a_row(array,EMPTY, 2);
   CuAssertIntEquals_Msg(tc, "Length 2 to win, array length 0", -1, observed);

   observed = x_in_a_row(array,EMPTY, 10);
   CuAssertIntEquals_Msg(tc, "Length 10 to win, array length 0", -1, observed);
}


/* CuTest setup */

CuSuite* x_in_a_row_example_suite() {
   CuSuite* suite = CuSuiteNew();

   SUITE_ADD_TEST(suite, ex_length10_full_hit);
   SUITE_ADD_TEST(suite, ex_length10_full_miss);
   SUITE_ADD_TEST(suite, ex_length10_partial_miss);
   SUITE_ADD_TEST(suite, ex_length_zero_array_always_false);
   SUITE_ADD_TEST(suite, it_ignores_four_empty_spaces);
   SUITE_ADD_TEST(suite, it_requires_a_win_length_greater_than_one);
   SUITE_ADD_TEST(suite, it_requires_rows_greater_than_zero);
   return suite;
}

int main(void) {
  CuString *output = CuStringNew();
  CuSuite* suite = CuSuiteNew();
  
  CuSuiteAddSuite(suite, x_in_a_row_example_suite());
  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s\n", output->buffer);
  return 0;
}




