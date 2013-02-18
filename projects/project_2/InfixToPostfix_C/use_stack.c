#include "stack.h"

#define EMPTY -1

int main(void) {

  // technique 1 (don't forget to free the stack)
  stack *s;
  s = (stack*)malloc(sizeof(stack));
  stackInit(s);
  free(s);
  
    // technique 2
  stack s2;
  stackInit(&s2);
  // (no need to free);

  // don't do this
  stack *s3;
  stackInit(s3); // asking for a seg fault.


  // Another bad idea
  char* token = "123";
  stackPush(&s2, token);
  token[2] = '4'; // take care not to modify strings after you've 
  // pushed them onto the stack.


  return 0;
}

// Another bad idea
stack* makeStack() 
{
  stack s;
  s.top = NULL;
  // don't return references to local variables!
  return &s;
}

// This is better
stack* makeStack2()
{
  stack* s = (stack*)malloc(sizeof(stack));
  s->top = NULL;
  return s;
}
