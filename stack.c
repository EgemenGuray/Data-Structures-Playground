#include "dequeue.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// DO NOT MODIFY THIS STRUCTURE
struct stack {
  struct dequeue *deq;
};

// stack_create() creates a new empty stack
// effects: allocates memory (client must call stack_destroy)
struct stack *stack_create(void) {
  struct stack *s = malloc(sizeof(struct stack));
  s->deq = dequeue_create();
  return s;
}

// stack_is_empty(s) determines if stack s is empty
bool stack_is_empty(const struct stack *s) {
  assert(s);
  return dequeue_is_empty(s->deq);
}

// stack_top(s) returns the top item in stack s
// requires: stack is not empty
int stack_top(const struct stack *s) {
  assert(s);
  return dequeue_front(s->deq);
}

// stack_pop(s) returns and pops (removes) the top item in stack s
// requires: stack is not empty
int stack_pop(struct stack *s) {
  assert(s);
  return dequeue_remove_front(s->deq);
}

// requires: stack is not empty
void stack_push(int item, struct stack *s) {
  assert(s);
  return dequeue_add_front(item, s->deq);
}

// stack_destroy(s) frees all memory for s
// effects: s is no longer valid
void stack_destroy(struct stack *s) {
  dequeue_destroy(s->deq);
  free(s);
}
