#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

void stackInit(stack *stkPtr) {
  stkPtr->top = NULL;
}

void stackDestroy(stack *stkPtr) {
  stack s1 = *stkPtr;
  if(s1.top) {
    while(s1.top->next) {
      s1.top = s1.top->next;
      free(s1.top->next);
    }
    free(s1.top);
  } else {
    free(&s1);
  }
}

void stackPush(stack* stkPtr, stkElement element) {
  stkNode *node;

  node = malloc(sizeof(struct stkNode));

  node->element = element;
  node->next = stkPtr->top;
  stkPtr->top = node;
}

stkElement stackPop(stack* stkPtr) {
  if(stkPtr->top) {
    stkElement elem = stkPtr->top->element;
    stkPtr->top = stkPtr->top->next;
    return elem;
  }
  return NULL;
}

stkElement stackPeek(stack* stkPtr) {
  if(stkPtr->top) {
    return stkPtr->top->element;
  }
  return NULL;
}

bool stackIsEmpty(stack* stkPtr) {
  if(stkPtr->top->element == NULL) {
    return 1;
  } else {
    return 0;
  }
}

int stackLength(stack* stkPtr) {
  int count = 0;
  stkNode* next = stkPtr->top;
  while(next) {
    count++;
    next = next->next;
  }
  return count;
}

