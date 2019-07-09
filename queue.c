#include "dequeue.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// DO NOT MODIFY THIS STRUCTURE
struct queue {
  struct dequeue *deq;
};

// queue_create() creates a new empty queue
// effects: allocates memory (client must call queue_destroy)
struct queue *queue_create(void) {
  struct queue *q = malloc(sizeof(struct queue));
  q->deq = dequeue_create();
  return q;
}

// queue_is_empty(q) determines if queue q is empty
bool queue_is_empty(const struct queue *q) {
 assert(q);
 return dequeue_is_empty(q->deq);
}

// queue_front(q) returns the front item in queue q
// requires: queue is not empty
int queue_front(const struct queue *q) {
  assert(q);
  return dequeue_front(q->deq);
}

// queue_remove_front(q) returns and removes the front item from queue q
// requires: queue is not empty
// effects: modifies q
int queue_remove_front(struct queue *q) {
  assert(q);
  return dequeue_remove_front(q->deq);
}

// queue_add_back(item, q) adds item to the back of queue q
// effects: modifies q
void queue_add_back(int item, struct queue *q) {
  assert(q);
  return dequeue_add_back(item, q->deq);
}

// queue_destroy(q) frees all memory for q
// effects: q is no longer valid
void queue_destroy(struct queue *q) {
  assert(q);
  dequeue_destroy(q->deq);
  free(q);
}
