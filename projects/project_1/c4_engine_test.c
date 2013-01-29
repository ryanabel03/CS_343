#include <stdio.h>
#include "connect4_engine.h"
#include "CuTest.h"

#define EMPTY -1
#define NO_WINNER_YET -1

void ct_initialize(int num_rows, int num_cols, int array[num_rows][num_cols]) {
  int r, c;
  for (r = 0; r < num_rows; r++) {
    for (c = 0; c < num_cols; c++) {
      array[r][c] = EMPTY;
    }
  }
}

void checkRows_returns_winner_if_exists(CuTest *tc) {
  int board[4][4];
  int array[4] = {0, 0, 0, 0};
  ct_initialize(4, 4, board);

  int answer = checkRows(4, array, 4);
  CuAssertIntEquals_Msg(tc, "Player 0.", 0, answer);
}

void checkRows_returns_negative_one_if_no_winner(CuTest *tc) {
  int board[4][4];
  int array[4] = {0, 0, 1, 0};
  ct_initialize(4, 4, board);

  int answer = checkRows(4, array, 4);
  CuAssertIntEquals_Msg(tc, "No winner", -1, answer);
}

void winner_returns_horizontal_winner(CuTest *tc) {
  int board[4][4];
  ct_initialize(4, 4, board);

  board[0][0] = 1;
  board[1][0] = 1;
  board[2][0] = 1;
  board[3][0] = 1;

  int answer = winner(4, 4, 4, board); 
  CuAssertIntEquals_Msg(tc, "Player 1.", 1, answer);


}

void checkColumns_returns_winner_if_one_exists(CuTest *tc) {
  int board[4][4];
  ct_initialize(4, 4, board);

  board[1][0] = 1;
  board[1][1] = 1;
  board[1][2] = 1;
  board[1][3] = 1;

  int answer = winner(4, 4, 4, board); 
  CuAssertIntEquals_Msg(tc, "Player 1.", 1, answer);


}

/*******************************************************************************************
 *
 * Test winner function
 *
 * Note: This is just a sample of how you can test your own winner
 * function.  You may need to modify this code depending on how your
 * organized your array.  I will not be testing your winner function
 * directly.
 *
 * Note:  Be sure to add tests for different directions, quadrants, and board sizes.
 *
 ******************************************************************************************/
void winner_horizontal_r0(CuTest *tc) {

  int num_rows = 7;
  int num_columns = 7;
  int array[num_rows][num_columns];
  int answer;
  ct_initialize(num_rows, num_columns, array);

  array[0][0] = 0;
  array[0][1] = 0;
  array[0][2] = 0;
  array[0][3] = 0;

  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "0s in bottom row", 0, answer);
}

/*******************************************************************************************
 *
 * Test place_token function
 *
 * Note: This is just a sample of how you can test your own
 * place_token function.  You may need to modify this code depending
 * on how your organized your array.  I will not be testing your
 * place_token function directly.
 *
 * Note:  Be sure to add tests for different directions, quadrants, and board sizes.
 *
 ******************************************************************************************/

void place_token_c1(CuTest *tc) {

  int num_rows = 7;
  int num_columns = 7;
  int array[num_rows][num_columns];
  ct_initialize(num_rows, num_columns, array);

  place_token(1, 3, num_rows, num_columns, array);

  // make sure there is a 1 at the bottom of column 3 and a -1 everywhere else
  CuAssertIntEquals_Msg(tc, "Drop 1 into empty column 3", 1, array[0][3]);
  int r, c;
  for (r = 0; r < num_rows; r++) {
    for (c = 0; c < num_columns; c++) {
      if (r != (0) || c != 3) {
	CuAssertIntEquals_Msg(tc, "Should be empty", EMPTY, array[r][c]);
      }
    }
  }
}

void place_token_recognizes_already_placed_tokens(CuTest *tc) {
  int num_rows = 3;
  int num_columns = 3;
  int array[num_rows][num_columns];
  ct_initialize(num_rows, num_columns, array);

  place_token(0, 2, num_rows, num_columns, array);
  place_token(1, 2, num_rows, num_columns, array);

  CuAssertIntEquals_Msg(tc, "Drop 1 into empty column 3", 0, array[0][2]);
  CuAssertIntEquals_Msg(tc, "Drop 1 into empty column 3", 1, array[1][2]);

}


/*******************************************************************************************
 *
 * Test overall game play
 *
 * These tests below demonstrate how I will be testing your game.
 * These tests below should run wihtout modification.  If they don't
 * then something in your design conflicts with the tests and we need
 * to figure out what it is.  Make sure you find any such conflicts
 * and work with me to resole them well before the assignment due
 * date.
 *
 * Because they test the interaction between several methods, these
 * tests below are not technically "unit" tests.  If your tests for
 * your connect4_engine functions are thorough, you need not add many
 * tests to this section.
 *
 ******************************************************************************************/

void horizontal_row0(CuTest* tc) 
{
  int num_rows = 7;
  int num_columns = 7;
  int array[num_rows][num_columns];
  int answer;
  ct_initialize(num_rows, num_columns, array);

  place_token(0, 0, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Single 0 in column 0", NO_WINNER_YET, answer);

  place_token(0, 1, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "0s in columns {0,1}", NO_WINNER_YET, answer);


  place_token(0, 2, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "0s in columns {0,1, 2}", NO_WINNER_YET, answer);


  place_token(0, 3, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "4 in a row, horizontal", 0, answer);
}


void vertical_column1(CuTest* tc) 
{
  int num_rows = 7;
  int num_columns = 7;
  int array[num_rows][num_columns];
  int answer;
  ct_initialize(num_rows, num_columns, array);

  place_token(0, 1, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Single 0 in column 1", NO_WINNER_YET, answer);

  place_token(0, 1, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Two 0s in column 1", NO_WINNER_YET, answer);


  place_token(0, 1, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Three 0s in column 1", NO_WINNER_YET, answer);


  place_token(0, 1, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "4 in a row, vertical", 0, answer);
}

void forward_diagonal(CuTest* tc) 
{
 /*
    . . . . . . .
    . . . . . . .
    . . . . . . .
    . . . 0 . . .
    . . . 1 0 . .
    . . . 0 0 0 .
    1 . . 1 1 1 0
  */ 

  int num_rows = 7;
  int num_columns = 7;
  int array[num_rows][num_columns];
  int answer;
  ct_initialize(num_rows, num_columns, array);

  /* column 6*/
  place_token(0, 6, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 1", NO_WINNER_YET, answer);

  /* column 5*/
  place_token(1, 5, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 2", NO_WINNER_YET, answer);

  place_token(0, 5, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 3", NO_WINNER_YET, answer);


  /* column 4*/
  place_token(1, 4, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 4", NO_WINNER_YET, answer);

  place_token(0, 4, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 5", NO_WINNER_YET, answer);

  place_token(1, 1, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 6", NO_WINNER_YET, answer);

  place_token(0, 4, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 7", NO_WINNER_YET, answer);

 /* column 3 */
  place_token(1, 3, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 8", NO_WINNER_YET, answer);

  place_token(0, 3, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 9", NO_WINNER_YET, answer);

  place_token(1, 3, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 10", NO_WINNER_YET, answer);

  place_token(0, 3, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 11 -- Winner!", 0, answer);
}


void backward_diagonal(CuTest* tc) 
{
 /*
    . . . . . . .
    . . . . . . .
    . . . . . . .
    . . . 0 . . .
    . . 0 1 . . .
    . 0 0 0 . . .
    0 1 1 1 . 1 .
  */ 

  int num_rows = 7;
  int num_columns = 7;
  int array[num_rows][num_columns];
  int answer;
  ct_initialize(num_rows, num_columns, array);

  /* column 0*/
  place_token(0, 0, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 1", NO_WINNER_YET, answer);

  /* column 1*/
  place_token(1, 1, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 2", NO_WINNER_YET, answer);

  place_token(0, 1, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 3", NO_WINNER_YET, answer);


  /* column 2*/
  place_token(1, 2, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 4", NO_WINNER_YET, answer);

  place_token(0, 2, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 5", NO_WINNER_YET, answer);

  place_token(1, 5, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 6", NO_WINNER_YET, answer);

  place_token(0, 2, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 7", NO_WINNER_YET, answer);

 /* column 3 */
  place_token(1, 3, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 8", NO_WINNER_YET, answer);

  place_token(0, 3, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 9", NO_WINNER_YET, answer);

  place_token(1, 3, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 10", NO_WINNER_YET, answer);

  place_token(0, 3, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 11 -- Winner!", 0, answer);
}



/*  setup */

CuSuite* c4_engine_suite() {
   CuSuite* suite = CuSuiteNew();
   SUITE_ADD_TEST(suite, checkRows_returns_winner_if_exists);
   SUITE_ADD_TEST(suite, checkRows_returns_negative_one_if_no_winner);

   /* SUITE_ADD_TEST(suite, winner_horizontal_r0); */
   SUITE_ADD_TEST(suite, place_token_c1);
   SUITE_ADD_TEST(suite, place_token_recognizes_already_placed_tokens);
   SUITE_ADD_TEST(suite, winner_returns_horizontal_winner);
   SUITE_ADD_TEST(suite, checkColumns_returns_winner_if_one_exists);

   /* SUITE_ADD_TEST(suite, horizontal_row0); */
   /* SUITE_ADD_TEST(suite, vertical_column1); */
   /* SUITE_ADD_TEST(suite, forward_diagonal); */
   /* SUITE_ADD_TEST(suite, backward_diagonal); */
   return suite;
}


void RunC4Tests(void) {
   CuString *output = CuStringNew();
   CuSuite* suite = CuSuiteNew();

   CuSuiteAddSuite(suite, c4_engine_suite());
   CuSuiteRun(suite);
   CuSuiteSummary(suite, output);
   CuSuiteDetails(suite, output);
   printf("%s\n", output->buffer);
}

int main(void) {
   RunC4Tests();
   return 0;
}
