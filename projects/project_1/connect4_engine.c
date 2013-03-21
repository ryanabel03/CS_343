#include <stdio.h>
#include "connect4_engine.h"

#define EMPTY -1

int checkRows(int rows, int columns, int array[rows][columns], int length_to_win) {
  int i, j, player = -1;
  for(i = 0; i < rows; i++) {
    int count = 1;
    for(j = 1; j < columns; j++) {
      if(array[i][j - 1] == array[i][j] && array[i][j] != -1) {
        count++;
        player = array[i][j];
      }

      if(count == length_to_win) {
        return player;
      }
    }
  }
  return -1;
}

int placeToken(int player, int column, int num_rows, int num_columns, int board[num_rows][num_columns]) {
  int i;
  int space = 0;
  if(column >= num_columns || column < 0) {
    printf("Cannot place token in column %d, it is outside the board\n", column);
    return 0;
  }
  for(i = num_rows - 1; i >= 0; i--) {
    if(board[i][column] == -1) {
      board[i][column] = player;
      space = 1;
      break;
    }
  }

  if(!space) {
    printf("The column you tried to place a token in is full\n");
    return 0;
  }
  return 1;
}

int checkColumns(int rows, int columns, int array[rows][columns], int length_to_win) {
  int i, j, player = -1;
  for(i = 0; i < columns; i++) {
    int count = 1;
    for(j = 1; j < rows; j++) {
      if(array[j - 1][i] == array[j][i] && array[j][i] != -1) {
        count++;
        player = array[j][i];
      } else {
        count = 1;
      }

      if(count == length_to_win) {
        return player;
      }
    }
  }
  return -1;
}

int checkRightDiagonal(int rows, int columns, int array[rows][columns], int length_to_win) {
  int startRow = rows - length_to_win;
  int startColumn = columns - length_to_win;

  while(startRow >= 0) {
    int count = 1;
    int column = 0;
    int player = -1;
    int row;

    for(row = startRow; row < rows - 1; row++) {
      if(array[row][column] == array[row + 1][column + 1] && array[row][column] != -1) {
        count++;
        player = array[row][column];

        if(count == length_to_win) {
          return player;
        }
      } 
      else {
        count = 1;
      }
      column++;
    }
    startRow--;
  }

  while(startColumn >= 0) {
    int count = 1;
    int row = 0;
    int player = -1;
    int column;

    for(column = startColumn; column < columns - 1; column++) {
      if(array[row][column] == array[row + 1][column + 1] && array[row][column] != -1) {
        count++;
        player = array[row][column];

        if(count == length_to_win) {
          return player;
        }
      } else {
        count = 1;
      }
      row++;
    }
    startColumn--;
  }
  return -1;
}

int checkLeftDiagonal(int rows, int columns, int array[rows][columns], int length_to_win) {
  int startColumn = columns - length_to_win;
  int startRow = rows - length_to_win;

  while(startColumn >= 0) {
    int column;
    int row = rows - 1;
    int player = -1;
    int count = 1;

    for(column = startColumn; column < columns - 1; column++) {
      if(array[row][column] == array[row - 1][column + 1] && array[row][column] != -1) {
        count++;
        player = array[row][column];
      } 
      else {
        count = 1;
      }

      if(count == length_to_win) {
        return player;
      }
      row--;
    }
    startColumn--;
  }

  while(startRow <= rows - 1) {
    int row;
    int column = 0;
    int player = -1;
    int count = 1;

    for(row = startRow; row > 0 ; row--) {
      if(array[row][column] == array[row - 1][column + 1] && array[row][column] != -1) {
        count++;
        player = array[row][column];

        if(count == length_to_win) {
          return player;
        }
        column++;
      } 
      else {
        count = 1;
      }
    }
    startRow++;
  }
  return -1;

}
int winner(int num_rows, int num_columns, int length_to_win, int array[num_rows][num_columns]) {
  int winner = -1;

  winner = checkColumns(num_rows, num_columns, array, length_to_win);

  if(winner != -1) {
    return winner;
  }

  winner = checkRows(num_rows, num_columns, array, length_to_win);

  if(winner != -1) {
    return winner;
  }

  winner = checkLeftDiagonal(num_rows, num_columns, array, length_to_win);

  if(winner != -1) {
    return winner;
  }

  winner = checkRightDiagonal(num_rows, num_columns, array, length_to_win);

  return winner;
}

void createBoard(int num_rows, int num_cols, int array[num_rows][num_cols]) {
  int r, c;
  for (r = 0; r < num_rows; r++) {
    for (c = 0; c < num_cols; c++) {
      array[r][c] = EMPTY;
    }
  }
}

int fullBoard(int num_rows, int num_cols, int array[num_rows][num_cols]) {
  int r, c;
  for(r = 0; r < num_rows; r++) {
    for(c = 0; c < num_cols; c++) {
      if(array[r][c] == EMPTY) {
        return -1;
      }
    }
  }
  return 1;
}

void printBoard(int num_rows, int num_cols, int array[num_rows][num_cols]) {
  int r, c;
  for(r = 0; r < num_rows; r++) {
    for(c = 0; c < num_cols; c++) {
      if( c == 0) {
        if(array[r][c] == -1) {
          printf("|   |");
        } else {
          printf("| %d |", array[r][c]);
        }
      } else if(c == num_cols -1) {
        if(array[r][c] == -1) {
          printf("   |\n");
        } else {
          printf(" %d |\n", array[r][c]);
        }
      } else {
        if(array[r][c] == -1) {
          printf("   |");
        } else {
          printf(" %d |", array[r][c]);
        }
      }
    }
  }
}
