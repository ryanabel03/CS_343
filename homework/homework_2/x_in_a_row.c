#include <stdio.h>

int x_in_a_row(int array[], int size, int length_to_win) {
  int count = 1;
  int player = -1;

  if( size <= 0) {
    printf("Row must be greater than 0");
    return -1;
  }

  if(length_to_win <= 1) {
    printf("Length to win must be greater than 1.");
    return -1;
  }

  printf("Length %d to win. Array length %d.", length_to_win, size);
  int i = 1;
  while( i < size) {
    if(array[i] == array[i - 1] && array[i] != -1) {
      count++;
      player = array[i];

      if(count >= length_to_win) {
        printf(" Player %d\n.", player);
        return player;
      }
    } else {
      count = 1;
    }
    i++;
  }
  printf("Length to win was: %d and count was %d. Miss\n", length_to_win, count);
  return -1;
}
