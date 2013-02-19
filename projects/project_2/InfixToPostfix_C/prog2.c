#include <stdio.h>
#include <string.h>
#include "if2pf.h"

int main(int argc, char* argv[]) {
  int option;

  printf("(1) Convert Infix to Postfix Expression\n");
  printf("(2) Evaluate Postfix Expression\n");
  printf("(3) Quit\n");

  while(1) {
    char line [1024];

    printf("Enter selection (1, 2, 3): ");
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d", &option);

    if(option == 1) {
      printf("Enter Infix Expression: ");
      fgets(line, sizeof(line), stdin);
      line[strlen(line) - 1] ='\0';

      char* post = infixToPostfix(line); 
      printf("Postfix: %s\n", post);

      int answer = evaluatePostfix(post);
      printf("Value: %d\n", answer);

    }else if(option == 2) {
      printf("Enter Postfix Expression: ");
      fgets(line, sizeof(line), stdin);
      line[strlen(line) - 1] ='\0';

      int answer = evaluatePostfix(line);
      printf("Value: %d\n", answer);

    }else if(option == 3) {
      printf("Quitting...\n");
      break;

    }else {
      printf("Please enter a valid option.\n");
    }

  }
  return 0;
}
