#include <stdio.h>

int checkRows(int size, int sector[], int length_to_win, int isHorizontal) {
  int i = 1;
  int count = 1;
  int player = -1;

  while( i < size) {
    if(sector[i] == sector[i - 1] && sector[i] != -1) {
      count++;
      player = sector[i];

      if(count >= length_to_win) {
        printf(" Player %d.\n", player);
        return player;
      }
    } else {
      count = 1;
    }
    i++;
  }
  printf("No winner");
  return -1;
}
int place_token(int player, int column, int num_rows, int num_columns, int board[num_rows][num_columns]) {
  int i;
  int space = 0;
  for(i = 0; i < num_rows; i++) {
    if(board[i][column] == -1) {
      board[i][column] = player;
      space = 1;
      break;
    }
  }

  if(!space) {
    printf("The column you tried to place a token in is full");
    return 0;
  } 
  return 1;
}

int checkColumns(int rows, int columns, int array[rows][columns], int length_to_win) {
  int i, j, player = -1;
  for(i = 1; i < rows; i++) {
    int count = 1;
    for(j = 1; j < columns; j++) {
      if(array[i - 1][j - 1] == array[i][j] && array[i][j] != -1) {
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

int winner(int num_rows, int num_columns, int length_to_win, int array[num_rows][num_columns]) {
  int winner = -1;

  winner = checkColumns(num_rows, num_columns, array[num_rows][num_columns], length_to_win);

  return winner;
}
