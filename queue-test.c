#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void) {
  struct queue *q = queue_create();
  queue_add_back(27, q);
  assert(queue_front(q) == 27);
  assert(queue_remove_front(q) == 27);
  assert(queue_is_empty(q));
  // ======== more test ==========
  queue_add_back(1, q);
  queue_add_back(2, q);
  queue_add_back(3, q);
  queue_add_back(4, q);
  assert(queue_front(q) == 1);
  assert(queue_remove_front(q) == 1);
  assert(queue_remove_front(q) == 2);
  queue_destroy(q);
  
  
}