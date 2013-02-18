#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"

int checkToken(char* token, char* item) {
  if(strstr(token, item)) {
    return 1;
  } else {
    return 0;
  }
}

int isLeftParen(char* token) {
  return checkToken(token, "(");
}

int isRightParen(char* token) {
  return checkToken(token, ")");
}

int isOperator(char* token) {
  if(checkToken(token, "*") ||checkToken(token, "/") || 
     checkToken(token, "+") || checkToken(token, "-") || 
     checkToken(token, "%") || checkToken(token, "%") || checkToken(token, "^")) {
    return 1;
  } else {
    return 0;
  }
}

int inputPrecedence(char* operator) {
  if(strstr(operator, "(")) {
    return 5;

  } else if(strstr(operator, "^")) {
    return 4;

  } else if(strstr(operator, "*") || strstr(operator, "/") || strstr(operator, "%")) {
    return 2;

  } else {
    return 1;

  }
}

int stackPrecedence(char* operator) {
  if(strstr(operator, "(")) {
    return -1;

  } else if(strstr(operator, "^")) {
    return 3;

  } else if(strstr(operator, "*") || strstr(operator, "/") || strstr(operator, "%")) {
    return 2;

  } else {
    return 1;

  }
}

void popHigherOps(stack* s1, char* token, char* expression) {
  int inPrec = inputPrecedence(token);
  char* stkOp = stackPeek(s1);
  int stkPrec = stackPrecedence(stkOp);
  printf("Stack(%s): %d Input(%s): %d\n", stkOp, stkPrec, token, inPrec);

  while(stkPrec >= inPrec) {
    char* op = stackPop(s1);
    strcat(expression, op);
    strcat(expression, " ");
    if(!stackIsEmpty(s1)) {
      stkPrec = stackPrecedence(op);
    } else {
      break;
    }
  }

  stackPush(s1, token);
}

int doOperation(stack* s1, char* operator) {
  int a = atoi(stackPop(s1));
  int b = atoi(stackPop(s1));
  printf("wtf is operator? %s\n", operator);

  if(strstr(operator, "*")) {
    printf("evaluating %d * %d\n", a, b);
    return a * b;

  } else if(strstr(operator, "^")) {
    printf("evaluating %d ^ %d\n", b, a);
    int answer = pow(b, a);
    printf("wtf is answer %d\n", answer);
    return answer;

  } else if(strstr(operator, "-"))  {
    printf("evaluating %d - %d\n", a, b);
    return b - a;

  } else if(strstr(operator, "/"))  {
    printf("evaluating %d / %d\n", a, b);
    return a / b;

  } else if(strstr(operator, "%")) {
    printf("evaluating %d % %d\n", a, b);
    return a % b;

  } else {
    printf("evaluating %d + %d\n", a, b);
    return a + b;
  }
}

void popOpsNotLeftParen(stack* s1, char* expression) {
  char* token = stackPop(s1);

  while(!strstr(token, "(")) {
    strcat(expression, token);
    strcat(expression, " ");
    token = stackPop(s1);
  }
}

char* infixToPostfix(char* infixStr) {
  char expression[1024];

  stack s1;
  stackInit(&s1);

  char* token = strtok(infixStr, " ");

  while(token != NULL) {
    if(isLeftParen(token)) {
      stackPush(&s1, token);

    } else if(isRightParen(token)) {
      popOpsNotLeftParen(&s1, expression);

    } else if(isOperator(token)) {
      if(!stackIsEmpty(&s1)) {
        popHigherOps(&s1, token, expression);
      } else {
        stackPush(&s1, token);
      }
    } else {
      //Number
      strcat(expression, token);
      strcat(expression, " ");
    }
    token = strtok(NULL, " ");
  }

  while(!stackIsEmpty(&s1)) {
    strcat(expression, stackPop(&s1));
    strcat(expression, " ");
  }

  printf("%s\n", expression);

  return expression;
}


int evaluatePostfix(char* postfixStr) {
  int answer = 0;
  char tostring[1024];

  stack s1;
  stackInit(&s1);

  char* token = strtok(postfixStr, " ");

  while(token != NULL) {
    if(isOperator(token)) {
      answer = doOperation(&s1, token);
      printf("Answer is %d\n", answer);
      sprintf(tostring, "%d", answer);
      stackPush(&s1, tostring);
    } else {
      stackPush(&s1, token);
    }


    token = strtok(NULL, " ");
  }
  return atoi(stackPop(&s1));
}

int main() {
  char blah[] = "( 3 + 3 ) * 8";
  char arr[] = "3 4 2 5 ^ - * 6 +";
  int wtf = evaluatePostfix(arr);
  printf("%d", wtf);

  return 0;

}
