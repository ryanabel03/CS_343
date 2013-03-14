#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

void stackInit(stack *stkPtr) {
  stkPtr->top = NULL;
}

void stackDestroy(stack *stkPtr) {
  stkNode* node = stkPtr->top;

  while(node != NULL) {
    stkNode* temp = node;
    node = node->next;
    free(temp);
  }

  free(stkPtr);
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
    stkNode* node = stkPtr->top;
    stkElement elem = node->element;
    stkPtr->top = node->next;
    free(node);
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
  if(stkPtr->top) {
    if(stkPtr->top->element == NULL) {
      return true;
    } else {
      return false;
    }
  }
  return true;
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

