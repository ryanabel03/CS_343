#ifndef CONNECT4_ENGINE_H
#define CONNECT4_ENGINE_H

int placeToken(int player, int column, int num_rows, int num_columns, int board[num_rows][num_columns]);
int winner(int num_rows, int num_columns, int length_to_win, int array[num_rows][num_columns]);
void createBoard(int num_rows, int num_cols, int array[num_rows][num_cols]); 
int checkLeftDiagonal(int rows, int columns, int array[rows][columns], int length_to_win);
int checkRightDiagonal(int rows, int columns, int array[rows][columns], int length_to_win);
int checkColumns(int rows, int columns, int array[rows][columns], int length_to_win);
int checkRows(int rows, int columns, int array[rows][columns], int length_to_win);
int fullBoard(int num_rows, int num_cols, int array[num_rows][num_cols]);
void printBoard(int num_rows, int num_cols, int array[num_rows][num_cols]);

#endif

