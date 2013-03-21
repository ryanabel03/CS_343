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

void checkRightDiagonal_returns_winner_if_there_is_one(CuTest *tc) {
  int board[3][3];
  ct_initialize(3, 3, board);

  board[0][0] = 0;
  board[1][1] = 0;
  board[2][2] = 0;

  int answer = checkRightDiagonal(3, 3, board, 3);
  CuAssertIntEquals_Msg(tc, "Player 0.", 0, answer);
}

void checkRightDiagonal_resets_count_properly_top_loop(CuTest *tc) {
  int board[5][5];
  ct_initialize(5, 5, board);

  board[1][0] = 0;
  board[2][1] = 0;
  board[3][2] = 1;
  board[4][3] = 1;

  int answer = checkRightDiagonal(5, 5, board, 3);
  CuAssertIntEquals_Msg(tc, "No Winner.", -1, answer);
}

void checkRightDiagonal_resets_count_properly(CuTest *tc) {
  int board[5][5];
  ct_initialize(5, 5, board);

  board[0][0] = 0;
  board[1][1] = 0;
  board[2][2] = 1;
  board[3][3] = 1;

  int answer = checkRightDiagonal(5, 5, board, 3);
  CuAssertIntEquals_Msg(tc, "No Winner.", -1, answer);
}

void checkRightDiagonal_returns_negative_one_if_no_winner(CuTest *tc) {
  int board[3][3];
  ct_initialize(3, 3, board);

  int answer = checkRightDiagonal(3, 3, board, 3);
  CuAssertIntEquals_Msg(tc, "No winner.", -1, answer);
}

void checkRightDiagonal_can_find_winners_above_largest_diagonal(CuTest *tc) {
  int board[4][4];
  ct_initialize(4, 4, board);

  board[1][0] = 0;
  board[2][1] = 0;
  board[3][2] = 0;

  int answer = checkRightDiagonal(4, 4, board, 3);
  CuAssertIntEquals_Msg(tc, "Player 0.", 0, answer);
}

void checkRightDiagonal_can_find_winners_below_largest_diagonal(CuTest *tc) {
  int board[4][4];
  ct_initialize(4, 4, board);

  board[0][1] = 0;
  board[1][2] = 0;
  board[2][3] = 0;

  int answer = checkRightDiagonal(4, 4, board, 3);
  CuAssertIntEquals_Msg(tc, "Player 0.", 0, answer);
}

void checkRightDiagonal_can_use_larger_boards(CuTest *tc) {
  int board[5][5];
  ct_initialize(5, 5, board);

  board[1][2] = 1;
  board[2][3] = 1;
  board[3][4] = 1;

  int answer = checkRightDiagonal(5, 5, board, 3);
  CuAssertIntEquals_Msg(tc, "Player 0.", 1, answer);
}



void checkLeftDiagonal_can_find_winners_above_largest_diagonal(CuTest *tc) {
  int board[5][5];
  ct_initialize(5, 5, board);

  board[4][2] = 1;
  board[3][3] = 1;
  board[2][4] = 1;

  int answer = checkLeftDiagonal(5, 5, board, 3);
  CuAssertIntEquals_Msg(tc, "Player 0.", 1, answer);
}

void checkLeftDiagonal_can_find_winners_above_below_largest_diagonal(CuTest *tc) {
  int board[5][5];
  ct_initialize(5, 5, board);

  board[3][0] = 1;
  board[2][1] = 1;
  board[1][2] = 1;

  int answer = checkLeftDiagonal(5, 5, board, 3);
  CuAssertIntEquals_Msg(tc, "Player 0.", 1, answer);
}

void checkLeftDiagonal_returns_winner_if_there_is_one(CuTest *tc) {
  int board[3][3];
  ct_initialize(3, 3, board);

  board[2][0] = 0;
  board[1][1] = 0;
  board[0][2] = 0;

  int answer = checkLeftDiagonal(3, 3, board, 3);
  CuAssertIntEquals_Msg(tc, "Player 0.", 0, answer);
}

void checkLeftDiagonal_returns_negative_one_if_no_winner(CuTest *tc) {
  int board[3][3];
  ct_initialize(3, 3, board);

  int answer = checkLeftDiagonal(3, 3, board, 3);
  CuAssertIntEquals_Msg(tc, "No winner.", -1, answer);

}

void checkLeftDiagonal_properly_resets_count_top_loop(CuTest *tc) {
  int board[5][5];
  ct_initialize(5, 5, board);

  board[4][1] = 0;
  board[3][2] = 0;
  board[2][3] = 1;
  board[1][4] = 1;

  int answer = checkLeftDiagonal(5, 5, board, 3);
  CuAssertIntEquals_Msg(tc, "No winner.", -1, answer);

}

//TODO: FINISH
void checkLeftDiagonal_properly_resets_count_bottom_loop(CuTest *tc) {
  int board[5][5];
  ct_initialize(5, 5, board);

  board[3][0] = 0;
  board[2][1] = 0;
  board[1][2] = 1;
  board[0][3] = 1;

  printBoard(5, 5, board);

  int answer = checkLeftDiagonal(5, 5, board, 3);
  CuAssertIntEquals_Msg(tc, "No winner.", -1, answer);
}

void checkRows_returns_winner_if_exists(CuTest *tc) {
  int board[4][4];
  ct_initialize(4, 4, board);
  board[3][0] = 1;
  board[3][1] = 1;
  board[3][2] = 1;
  board[3][3] = 1;

  int answer = checkRows(4, 4, board, 4);
  CuAssertIntEquals_Msg(tc, "Player 1.", 1, answer);
}

void checkRows_returns_negative_one_if_no_winner(CuTest *tc) {
  int board[4][4];
  ct_initialize(4, 4, board);
  board[3][0] = 1;
  board[3][1] = -1;
  board[3][2] = 1;
  board[3][3] = 1;

  int answer = checkRows(4, 4, board, 4);
  CuAssertIntEquals_Msg(tc, "No winner", -1, answer);
}



void checkColumns_returns_winner_if_one_exists(CuTest *tc) {
  int board[4][4];
  ct_initialize(4, 4, board);

  board[0][1] = 1;
  board[1][1] = 1;
  board[2][1] = 1;
  board[3][1] = 1;

  int answer = checkColumns(4, 4, board,  4);
  CuAssertIntEquals_Msg(tc, "Player 1.", 1, answer);


}

void checkColumns_returns_negative_one_if_no_winner(CuTest *tc) {
  int board[4][4];
  ct_initialize(4, 4, board);

  board[0][1] = 1;
  board[1][1] = 1;
  board[2][1] = 0;
  board[3][1] = 1;

  int answer = winner(4, 4, 4, board);
  CuAssertIntEquals_Msg(tc, "No one wins", -1, answer);
}

void checkColumns_does_not_recognize_negative_one_as_winner(CuTest *tc) {
  int board[4][4];
  ct_initialize(4, 4, board);

  board[0][1] = -1;
  board[1][1] = -1;
  board[2][1] = -1;
  board[3][1] = -1;

  int answer = winner(4, 4, 4, board);
  CuAssertIntEquals_Msg(tc, "No one wins", -1, answer);
}

void checkColumns_properly_resets_count(CuTest *tc) {
  int board[5][5];
  ct_initialize(5, 5, board);

  board[0][1] = 1;
  board[1][1] = 1;
  board[2][1] = 0;
  board[3][1] = 1;
  board[4][1] = 1;

  int answer = winner(5, 5, 3, board);
  CuAssertIntEquals_Msg(tc, "No one wins", -1, answer);
}


void fullBoard_notices_a_full_board(CuTest *tc) {
  int board[3][3];
  ct_initialize(3, 3, board);

  board[0][0] = 0;
  board[0][1] = 0;
  board[0][2] = 0;
  board[1][0] = 0;
  board[1][1] = 0;
  board[1][2] = 0;
  board[2][0] = 0;
  board[2][1] = 0;
  board[2][2] = 0;

  int answer = fullBoard(3, 3, board);
  CuAssertIntEquals_Msg(tc, "Full board", 1, answer);
}

void fullBoard_notices_an_empty_board(CuTest *tc) {
  int board[3][3];
  ct_initialize(3, 3, board);

  board[0][1] = 0;
  board[0][2] = 0;
  board[1][0] = 0;
  board[1][1] = 0;
  board[1][2] = 0;
  board[2][0] = 0;
  board[2][1] = 0;
  board[2][2] = 0;

  int answer = fullBoard(3, 3, board);
  CuAssertIntEquals_Msg(tc, "Full board", -1, answer);
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
void winner_returns_horizontal_winner(CuTest *tc) {
  int board[4][4];
  ct_initialize(4, 4, board);

  board[1][0] = 1;
  board[1][1] = 1;
  board[1][2] = 1;
  board[1][3] = 1;

  int answer = winner(4, 4, 4, board);
  CuAssertIntEquals_Msg(tc, "Player 1.", 1, answer);
}


void winner_returns_vertical_winner(CuTest *tc) {
  int board[4][4];
  ct_initialize(4, 4, board);

  board[0][2] = 1;
  board[1][2] = 1;
  board[2][2] = 1;
  board[3][2] = 1;

  int answer = winner(4, 4, 4, board);
  CuAssertIntEquals_Msg(tc, "Player 1.", 1, answer);
}

void winner_returns_right_diagonal_winner(CuTest *tc) {
  int board[5][5];
  ct_initialize(5, 5, board);

  board[0][0] = 1;
  board[1][1] = 1;
  board[2][2] = 1;
  board[3][3] = 1;

  int answer = winner(5, 5, 4, board);
  CuAssertIntEquals_Msg(tc, "Player 1.", 1, answer);

}

void winner_returns_left_diagonal_winner(CuTest *tc) {
  int board[3][3];
  ct_initialize(3, 3, board);

  board[2][0] = 1;
  board[1][1] = 1;
  board[0][2] = 1;

  int answer = winner(3, 3, 3, board);
  CuAssertIntEquals_Msg(tc, "Player 1.", 1, answer);

}

void winner_fixes_kurmas_failure(CuTest *tc) {
  int board[8][8];
  ct_initialize(8, 8, board);

  board[7][1] = 0;
  board[6][1] = 1;
  board[5][1] = 0;
  board[4][1] = 1;

  board[7][2] = 1;
  board[6][2] = 0;
  board[5][2] = 1;
  board[4][2] = 0;

  board[7][3] = 0;
  board[6][3] = 1;
  board[5][3] = 0;
  board[4][3] = 1;

  board[7][4] = 1;

  int answer = winner(8, 8, 4, board);
  CuAssertIntEquals_Msg(tc, "Player 1.", 1, answer);

}


/*******************************************************************************************
 *
 * Test placeToken function
 *
 * Note: This is just a sample of how you can test your own
 * placeToken function.  You may need to modify this code depending
 * on how your organized your array.  I will not be testing your
 * placeToken function directly.
 *
 * Note:  Be sure to add tests for different directions, quadrants, and board sizes.
 *
 ******************************************************************************************/

void placeToken_c1(CuTest *tc) {

  int num_rows = 7;
  int num_columns = 7;
  int array[num_rows][num_columns];
  ct_initialize(num_rows, num_columns, array);

  placeToken(1, 3, num_rows, num_columns, array);

  // make sure there is a 1 at the bottom of column 3 and a -1 everywhere else
  CuAssertIntEquals_Msg(tc, "Drop 1 into empty column 3", 1, array[num_rows - 1][3]);
  int r, c;
  for (r = 0; r < num_rows; r++) {
    for (c = 0; c < num_columns; c++) {
      if (r != (num_rows - 1) || c != 3) {
	CuAssertIntEquals_Msg(tc, "Should be empty", EMPTY, array[r][c]);
      }
    }
  }
}

void placeToken_recognizes_already_placed_tokens(CuTest *tc) {
  int num_rows = 3;
  int num_columns = 3;
  int array[num_rows][num_columns];
  ct_initialize(num_rows, num_columns, array);

  placeToken(0, 2, num_rows, num_columns, array);
  placeToken(1, 2, num_rows, num_columns, array);

  CuAssertIntEquals_Msg(tc, "Drop 1 into empty column 3", 0, array[num_rows - 1][2]);
  CuAssertIntEquals_Msg(tc, "Drop 1 into empty column 3", 1, array[num_rows - 2][2]);

}

void placeToken_must_be_in_board(CuTest *tc) {
  int num_rows = 3;
  int num_columns = 3;
  int array[num_rows][num_columns];
  ct_initialize(num_rows, num_columns, array);

  placeToken(0, 3, num_rows, num_columns, array);
  placeToken(0, -1, num_rows, num_columns, array);

  CuAssertIntEquals_Msg(tc, "Must drop into board.", -1, array[num_rows - 1][0]);
  CuAssertIntEquals_Msg(tc, "Must drop into board.", -1, array[num_rows - 1][2]);


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

  placeToken(0, 0, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Single 0 in column 0", NO_WINNER_YET, answer);

  placeToken(0, 1, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "0s in columns {0,1}", NO_WINNER_YET, answer);


  placeToken(0, 2, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "0s in columns {0,1, 2}", NO_WINNER_YET, answer);


  placeToken(0, 3, num_rows, num_columns, array);
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

  placeToken(0, 1, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Single 0 in column 1", NO_WINNER_YET, answer);

  placeToken(0, 1, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Two 0s in column 1", NO_WINNER_YET, answer);


  placeToken(0, 1, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Three 0s in column 1", NO_WINNER_YET, answer);


  placeToken(0, 1, num_rows, num_columns, array);
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
  placeToken(0, 6, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 1", NO_WINNER_YET, answer);

  /* column 5*/
  placeToken(1, 5, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 2", NO_WINNER_YET, answer);

  placeToken(0, 5, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 3", NO_WINNER_YET, answer);


  /* column 4*/
  placeToken(1, 4, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 4", NO_WINNER_YET, answer);

  placeToken(0, 4, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 5", NO_WINNER_YET, answer);

  placeToken(1, 1, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 6", NO_WINNER_YET, answer);

  placeToken(0, 4, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 7", NO_WINNER_YET, answer);

 /* column 3 */
  placeToken(1, 3, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 8", NO_WINNER_YET, answer);

  placeToken(0, 3, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 9", NO_WINNER_YET, answer);

  placeToken(1, 3, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 10", NO_WINNER_YET, answer);

  placeToken(0, 3, num_rows, num_columns, array);
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
  placeToken(0, 0, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 1", NO_WINNER_YET, answer);

  /* column 1*/
  placeToken(1, 1, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 2", NO_WINNER_YET, answer);

  placeToken(0, 1, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 3", NO_WINNER_YET, answer);


  /* column 2*/
  placeToken(1, 2, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 4", NO_WINNER_YET, answer);

  placeToken(0, 2, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 5", NO_WINNER_YET, answer);

  placeToken(1, 5, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 6", NO_WINNER_YET, answer);

  placeToken(0, 2, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 7", NO_WINNER_YET, answer);

 /* column 3 */
  placeToken(1, 3, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 8", NO_WINNER_YET, answer);

  placeToken(0, 3, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 9", NO_WINNER_YET, answer);

  placeToken(1, 3, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 10", NO_WINNER_YET, answer);

  placeToken(0, 3, num_rows, num_columns, array);
  answer = winner(num_rows, num_columns, 4, array);
  CuAssertIntEquals_Msg(tc, "Step 11 -- Winner!", 0, answer);
}

void kurmas_test(CuTest *tc) {
  int num_rows = 8;
  int num_columns = 8;
  int array[num_rows][num_columns];
  int answer;
  ct_initialize(num_rows, num_columns, array);

  placeToken(0, 1, num_rows, num_columns, array);
  placeToken(1, 1, num_rows, num_columns, array);
  placeToken(0, 1, num_rows, num_columns, array);
  placeToken(1, 1, num_rows, num_columns, array);

  placeToken(1, 2, num_rows, num_columns, array);
  placeToken(0, 2, num_rows, num_columns, array);
  placeToken(1, 2, num_rows, num_columns, array);
  placeToken(0, 2, num_rows, num_columns, array);

  placeToken(0, 3, num_rows, num_columns, array);
  placeToken(1, 3, num_rows, num_columns, array);
  placeToken(0, 3, num_rows, num_columns, array);
  placeToken(1, 3, num_rows, num_columns, array);

  placeToken(1, 4, num_rows, num_columns, array);

  answer = winner(num_rows, num_columns, 4, array);

  CuAssertIntEquals_Msg(tc, "Player 1", 1, answer);
}

void kurmas_test_2(CuTest *tc) {
  int num_rows = 7;
  int num_columns = 7;
  int array[num_rows][num_columns];
  int answer;
  ct_initialize(num_rows, num_columns, array);

  placeToken(1, 0, num_rows, num_columns, array);
  placeToken(0, 0, num_rows, num_columns, array);
  placeToken(0, 0, num_rows, num_columns, array);
  placeToken(0, 0, num_rows, num_columns, array);

  placeToken(0, 1, num_rows, num_columns, array);
  placeToken(1, 1, num_rows, num_columns, array);
  placeToken(1, 1, num_rows, num_columns, array);
  placeToken(1, 1, num_rows, num_columns, array);
  placeToken(0, 1, num_rows, num_columns, array);

  placeToken(1, 2, num_rows, num_columns, array);
  placeToken(0, 2, num_rows, num_columns, array);
  placeToken(0, 2, num_rows, num_columns, array);
  placeToken(0, 2, num_rows, num_columns, array);
  placeToken(1, 2, num_rows, num_columns, array);
  placeToken(0, 2, num_rows, num_columns, array);

  placeToken(0, 3, num_rows, num_columns, array);
  placeToken(1, 3, num_rows, num_columns, array);
  placeToken(1, 3, num_rows, num_columns, array);
  placeToken(1, 3, num_rows, num_columns, array);
  placeToken(0, 3, num_rows, num_columns, array);
  placeToken(1, 3, num_rows, num_columns, array);
  placeToken(0, 3, num_rows, num_columns, array);

  placeToken(0, 6, num_rows, num_columns, array);

  answer = winner(num_rows, num_columns, 5, array);

  CuAssertIntEquals_Msg(tc, "Player 1", -1, answer);
}

/*  setup */

CuSuite* c4_engine_suite() {
   CuSuite* suite = CuSuiteNew();

   SUITE_ADD_TEST(suite, placeToken_must_be_in_board);
   SUITE_ADD_TEST(suite, placeToken_c1);
   SUITE_ADD_TEST(suite, placeToken_recognizes_already_placed_tokens);
   SUITE_ADD_TEST(suite, winner_returns_horizontal_winner);
   SUITE_ADD_TEST(suite, winner_returns_vertical_winner);
   SUITE_ADD_TEST(suite, winner_returns_left_diagonal_winner);
   SUITE_ADD_TEST(suite, winner_returns_right_diagonal_winner);
   SUITE_ADD_TEST(suite, winner_fixes_kurmas_failure);

   SUITE_ADD_TEST(suite, checkLeftDiagonal_can_find_winners_above_largest_diagonal);
   SUITE_ADD_TEST(suite, checkLeftDiagonal_can_find_winners_above_below_largest_diagonal);
   SUITE_ADD_TEST(suite, checkLeftDiagonal_returns_winner_if_there_is_one);
   SUITE_ADD_TEST(suite, checkLeftDiagonal_returns_negative_one_if_no_winner);
   SUITE_ADD_TEST(suite, checkLeftDiagonal_properly_resets_count_top_loop);
   SUITE_ADD_TEST(suite, checkLeftDiagonal_properly_resets_count_bottom_loop);

   SUITE_ADD_TEST(suite, checkRows_returns_winner_if_exists);
   SUITE_ADD_TEST(suite, checkRows_returns_negative_one_if_no_winner);

   SUITE_ADD_TEST(suite, checkColumns_returns_winner_if_one_exists);
   SUITE_ADD_TEST(suite, checkColumns_returns_negative_one_if_no_winner);
   SUITE_ADD_TEST(suite, checkColumns_returns_negative_one_if_no_winner);
   SUITE_ADD_TEST(suite, checkColumns_does_not_recognize_negative_one_as_winner);
   SUITE_ADD_TEST(suite, checkColumns_properly_resets_count);

   SUITE_ADD_TEST(suite, checkRightDiagonal_returns_winner_if_there_is_one);
   SUITE_ADD_TEST(suite, checkRightDiagonal_can_find_winners_above_largest_diagonal);
   SUITE_ADD_TEST(suite, checkRightDiagonal_can_find_winners_below_largest_diagonal);
   SUITE_ADD_TEST(suite, checkRightDiagonal_can_use_larger_boards);
   SUITE_ADD_TEST(suite, checkRightDiagonal_returns_negative_one_if_no_winner);
   SUITE_ADD_TEST(suite, checkRightDiagonal_resets_count_properly);
   SUITE_ADD_TEST(suite, checkRightDiagonal_resets_count_properly_top_loop);

   SUITE_ADD_TEST(suite, fullBoard_notices_a_full_board);
   SUITE_ADD_TEST(suite, fullBoard_notices_an_empty_board);

   SUITE_ADD_TEST(suite, horizontal_row0);
   SUITE_ADD_TEST(suite, vertical_column1);
   SUITE_ADD_TEST(suite, forward_diagonal);
   SUITE_ADD_TEST(suite, backward_diagonal);
   SUITE_ADD_TEST(suite, kurmas_test);
   SUITE_ADD_TEST(suite, kurmas_test_2);
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
