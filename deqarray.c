#include "deqarray.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// DO NOT MODIFY THIS STRUCTURE
struct dequeue {
  int front;
  int back;
  int len;
  int maxlen;
  int *queue;
};

// dequeue_create() creates a new empty queue
// effects: allocates memory (client must call dequeue_destroy)
struct dequeue *dequeue_create(void) {
  // allocates size
  struct dequeue *q = malloc(sizeof(struct dequeue));
  q->len = 0;
  q->front = -1; // currently no item
  q->back = -1; // currently no item
  q->maxlen = 1; // size one
  // resize
  q->queue = malloc(q->maxlen * sizeof(struct dequeue));
  return q;
}

// dequeue_is_empty(q) determines if double ended queue q is empty
// time: O(1)
bool dequeue_is_empty(const struct dequeue *q) {
  // error check
  assert(q);
  // end of error check
  if(q->back == -1){
    return true; 
  }else{
    return false;
  }
}

// dequeue_front(q) returns the front item in the double ended queue q
// requires: double ended queue is not empty
// time: O(1)
int dequeue_front(const struct dequeue *q) {
  // error check
  assert(q);
  assert(!dequeue_is_empty(q));
  // end of error check
  return  q->queue[q->front];
}

// dequeue_back(q) returns the back item in the double ended queue q
// requires: double ended queue is not empty
// time: O(1)
int dequeue_back(const struct dequeue *q) {
  // error check
  assert(q);
  assert(!dequeue_is_empty(q));
  // end of error check
  return  q->queue[q->back];
}

// dequeue_remove_front(q) returns and removes the front item from q
// requires: double ended queue is not empty
// effects: modifies q
// time: amortized O(1)
int dequeue_remove_front(struct dequeue *q) {
  // error check
  assert(q);
  assert(!dequeue_is_empty(q));
  // end of error check
  int x = q->queue[q->front]; // return value
  if(q->front < q-> back){ // if not the last item
    q->front += 1;
    q->len -= 1;
    if(q->len * 5 < q->maxlen){
     
      int a[q->len];
      int x = 0;
      for(int i = q->front; i <= q->back; i++){
        a[x] = q->queue[i];
        x++;
      }
      x = q->len;
      q->maxlen = q->len * 3;
      q->queue = realloc(q->queue, q->maxlen * sizeof(int));
      for(int i = 0; i < q->len; i++){
        q->queue[x] = a[i];
        x++;
      }
      q->front = q->len;
      q->back = q->len * 2 - 1;
    }
    
    return x;
  }else{ // if the last item
    q->front = -1;
    q->back = -1;
    q->len = 0;
    q->maxlen = 1;
    q->queue = realloc(q->queue, q->maxlen * sizeof(int));
    return x;
  }
  
}

// dequeue_remove_back(q) returns and removes the back item from q
// requires: double ended queue is not empty
// effects: modifies q
// time: amortized O(1)
int dequeue_remove_back(struct dequeue *q) {
  // error check
  assert(q);
  assert(!dequeue_is_empty(q));
  // end of error check
  int x = q->queue[q->back];
  if(q->front < q-> back){ // if not the last item
    q->back -= 1;
    q->len -= 1;
    if(q->len * 5 < q->maxlen ){
      int a[q->len];
      int x = 0;
      for(int i = q->front; i <= q->back; i++){
        a[x] = q->queue[i];
        x++;
      }
      x = q->len;
      q->maxlen = q->len * 3;
      q->queue = realloc(q->queue, q->maxlen * sizeof(int));
      for(int i = 0; i < q->len; i++){
        q->queue[x] = a[i];
        x++;
      }
      q->front = q->len;
      q->back = q->len * 2 - 1;
    }
    return x;
  }else{ // if the last item
    q->front = -1;
    q->back = -1;
    q->len = 0;
    q->maxlen = 1;
    q->queue = realloc(q->queue, q->maxlen * sizeof(int));
    return x;
  }
}

// dequeue_add_front(item, q) adds item to the front of q
// effects: modifies q
// time: amortized O(1)
void dequeue_add_front(int item, struct dequeue *q) {
  // error check
  assert(q);
  // end of error check
  if(dequeue_is_empty(q)){ // initilize and add
    q->back = 0;
    q->front = 0;
  }else if(q->front == 0){ // if already initialized

      q->maxlen = q-> len * 3;
      q->queue = realloc(q->queue, q->maxlen * sizeof(int));
      // get the elements
      int a[q->len];
      for(int i = 0; i < q->len; i++){
        a[i] = q->queue[i];
      }
      // fill them into middle
      int x = q->len;
      for(int i = 0; i < q->len; i++){
        q->queue[x] = a[i];
        x++;  
      }
      q->back = q->len * 2 - 1;
      q->front = q->len - 1;
  }else{
    // if front is empty set to add to front
    q->front = q->front - 1;
  }
  // add to front
  q->queue[q->front] = item;
  q->len += 1;
}

// dequeue_add_back(item, q) adds item to the back of queue q
// effects: modifies q
// time: amortized O(1)
void dequeue_add_back(int item, struct dequeue *q){
  // error check
  assert(q);
  // end of error check
  
  // if full resize
  if(q->back + 1 == q->maxlen){
      // get elements
      int a[q->len];
      int z = 0;
      for(int i = q->front; i <= q->back; i++){
        a[z] = q->queue[i];
        z++;
      }
      q->maxlen = q-> len * 3;
      q->queue = realloc(q->queue, q->maxlen * sizeof(int));
      // place them into middle
      int x = q->len;
      q->front = x;
      int y = 0;
      for(int i = 0; i < q->len; i++){
        q->queue[x] = a[i];
        y = x;
        x++;  
      }
      q->back = y;   
  }
  // if dq is initially empty
  if(dequeue_is_empty(q)){
    q->back = 0;
    q->front = 0;
  // if rear is at last position of queue
  }else{
    q->back = q->back + 1;
  }
  // add the new item
  q->queue[q->back] = item;
  q->len += 1;
}

// dequeue_destroy(q) frees all memory for q
// requires: q must be from a previous malloc
// effects: q is no longer valid
void dequeue_destroy(struct dequeue *q) {
  // error check
  assert(q);
  // end of error check
  // free elements
  free(q->queue);
  // free queue
  free(q);
}


// DO NOT MODIFY THIS FUNCTION
// dequeue_print(q) prints the contents of q
// effects: prints to output
void dequeue_print(const struct dequeue *q) {
  printf("Dequeue: [%d...%d], %d of %d\n", q->front, q->back, q->len, q->maxlen);
  if (!q->len) {
    printf("[empty]\n");
    return;
  }
  printf("[%d", q->queue[q->front]);
  for (int i = q->front + 1; i <= q->back; ++i) {
    printf(", %d", q->queue[i]);
  }
  printf("]\n");
  
}
