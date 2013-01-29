#include <stdio.h>
#include <limits.h>

int main() {
  char a = 'a';
  switch(a) {
  case 'a':
    printf("here");
    break;
  default:
    printf("yo");
    break;
  }    
  return 0;
}
