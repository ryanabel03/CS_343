#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stack.h"
#include "if2pf.h"

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
  char* opA = stackPop(s1);
  char* opB = stackPop(s1);
  int answer = 0;

  int a = atoi(opA);
  int b = atoi(opB);

  if(strstr(operator, "*")) {
    answer = a * b;

  } else if(strstr(operator, "^")) {
    answer = pow(b, a);

  } else if(strstr(operator, "-"))  {
    answer = b - a;

  } else if(strstr(operator, "/"))  {
    answer = a / b;

  } else if(strstr(operator, "%")) {
    answer = a % b;

  } else {
    answer = a + b;
  }

  free(opA);
  free(opB);

  return answer;
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
  char* ans = malloc (sizeof(char) * 1024);

  stack s1;
  stackInit(&s1);

  char* token = strtok(infixStr, " ");

  while(token != NULL) {
    if(isLeftParen(token)) {
      stackPush(&s1, token);

    } else if(isRightParen(token)) {
      popOpsNotLeftParen(&s1, ans);

    } else if(isOperator(token)) {
      if(!stackIsEmpty(&s1)) {
        popHigherOps(&s1, token, ans);
      } else {
        stackPush(&s1, token);
      }
    } else {
      //Number
      strncat(ans, token, sizeof(token));
      strcat(ans, " ");
    }
    token = strtok(NULL, " ");
  }

  while(!stackIsEmpty(&s1)) {
    strcat(ans, stackPop(&s1));
    strcat(ans, " ");
  }

  return ans;
}


int evaluatePostfix(char* postfixStr) {
  int answer = 0;

  stack s1;
  stackInit(&s1);

  postfixStr[strlen(postfixStr) - 1] = '\0';
  char* token = strtok(postfixStr, " ");

  while(token != NULL) {
    if(isOperator(token)) {
      char* ans = malloc (sizeof(char) * 1024);
      answer = doOperation(&s1, token);
      snprintf(ans, 1024, "%d", answer);
      stackPush(&s1, ans);
    } else {
      char* ans = malloc (sizeof(char) * 1024);
      snprintf(ans, 1024, "%s", token);
      stackPush(&s1, ans);
    }
    token = strtok(NULL, " ");
  }

  char* toFreeAnswer = stackPop(&s1);
  int returnAnswer = atoi(toFreeAnswer);

  free(postfixStr);
  free(toFreeAnswer);
  return returnAnswer;
}
