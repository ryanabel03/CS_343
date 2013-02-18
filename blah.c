#include <stdio.h>
#include <string.h>

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

  while(stkPrecedence && stkPrecedence >= inPrecedence) {
    char* stackOperand = stackPop(stkPtr);
    str[strlen(str)] = *stackOperand;
    stkPrecedence = stackPrecedence(stackPop(stkPtr));
  }
}
int main() {
}
