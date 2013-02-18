#include <string.h>
#include <stdio.h>
#include "stack.h"

int isOperator(char letter) {
  if(letter == '*' || letter == '/' || letter == '+' || letter == '-' || letter == '^' || letter == '%') {
    return 1;
  } else {
    return 0;
  }
}

int inputPrecedence(char operand) {
  if(operand == '(') {
    return 5;
  } else if(operand == '^') {
    return 4;
  }else if(operand == '*' || operand == '/' || operand == '%') {
    return 2;
  } else {
    return 1;
  }
}

int stackPrecedence(char* operand) {
  if(strstr(operand, "(")) {
    return -1;
  } else if(strstr(operand, "^")) {
    return 3;
  }else if(strstr(operand, "*") || strstr(operand, "/") || strstr(operand, "%")) {
    return 2;
  } else {
    return 1;
  }
}

void popHigherOperators(char* str, stack *stkPtr, char operand) {
  int inPrecedence = inputPrecedence(operand);
  int stkPrecedence = stackPrecedence(stackPeek(stkPtr)) ;
  printf("Stack precedence %d for %s\n", stkPrecedence, stackPeek(stkPtr));

  while(stkPrecedence >= inPrecedence) {
    char* stackOperand = stackPop(stkPtr);
    str[strlen(str)] = *stackOperand;
    stkPrecedence = stackPrecedence(stackPop(stkPtr));
  }
}

char* infixToPostfix(char* infixStr) {
  char* expression = "(3+3) * 8";
  char str[1024];
  stack s1;
  stackInit(&s1);

  int i = 0;
  int len = strlen(expression);

  for(i = 0; i < len; i++) {
    char letter = expression[i];
    
    printf("letter? %c\n", letter);

    if(letter == ' ') {
    } else if(letter == '(') {
      stackPush(&s1, &letter); 
      //PUSH onto stack
      
    } else if(isOperator(letter)) {
      popHigherOperators(str, &s1, letter);
      stackPush(&s1, &letter);
      //DO operator things


    } else if(letter == ')') {
      //DO Right paren thing

    } else {
      //Number
      str[strlen(str)] = letter;
    }
  }

  printf("%s", str);


  return NULL;

}

int evaluatePostfix(char* postfixStr) {


}

int main() {
  infixToPostfix("blah");

  return 0;

}
