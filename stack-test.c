#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void) {
  struct stack *s = stack_create();
  stack_push(27, s);
  assert(stack_top(s) == 27);
  assert(stack_pop(s) == 27);
  assert(stack_is_empty(s));
  stack_push(1, s);
  assert(stack_top(s) == 1);
  stack_push(2, s);
  assert(stack_top(s) == 2);
  stack_push(3, s);
  assert(stack_top(s) == 3);
  stack_push(4, s);
  assert(stack_top(s) == 4);
  assert(stack_pop(s) == 4);
  assert(stack_pop(s) == 3);
  assert(stack_pop(s) == 2);
  assert(stack_pop(s) == 1);
  stack_destroy(s);
  struct stack *as = stack_create();
  stack_destroy(as);
}