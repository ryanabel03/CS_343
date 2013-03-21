#include "connect4_engine.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  char line[256];
  int rows;
  int length_to_win;

  if(argc == 3) {
    rows = atoi(argv[1]);
    length_to_win = atoi(argv[2]);
  }else if(argc == 2) {
    rows = atoi(argv[1]);
  } else {
    rows = 8;
    length_to_win = 4;
  }

  int board[rows][rows];

  printf("Creating Board size %d x %d with length to win %d...\n\n", rows, rows, length_to_win);

  createBoard(rows, rows, board);

  int counter = 2;
  while(1) {
    printBoard(rows, rows, board);
    int column;
    int isWinner = -1;
    int isFull = -1;
    int isPlaced = 0;
    printf("Player %d's turn.\n", counter % 2);
    printf("Enter a column to place a token in: ");

    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d", &column);

    isPlaced = placeToken(counter % 2, column, rows, rows, board);

    isWinner = winner(rows, rows, length_to_win, board);

    isFull = fullBoard(rows, rows, board);

    if(isWinner != -1) {
      printf("\n");
      printBoard(rows, rows, board);
      printf("Player %d Wins!", isWinner);
      exit(1);
    }

    if(isFull != -1) {
      printf("\n");
      printBoard(rows, rows, board);
      printf("Board is full, Stalemate!");
      exit(1);
    }

    if(isPlaced) {
      counter++;
    }
  }

}
