#include <stdlib.h>
#include "minheap.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

// LCHILD(x) returns the left child index of x
static int left_child(int x){
   return 2 * x + 1;
}

// RCHILD(x) returns the right child index of x
static int right_child(int x){
   return 2 * x + 2;
}

// PARENT(x) returns the parent index of x
static int parent(int x){
   return (x - 1) / 2;
}

// swap(n1, n2) swaps the n1 and n2
// effects: mutates n1 and n2
static void swap(int *n1, int *n2) {
  int temp = *n1 ;
  *n1 = *n2 ;
  *n2 = temp ;
}

// minheap_create() creates a new empty minheap
// effects: allocates memory (client must call minheap_destroy)
struct minheap *minheap_create(void) {
  struct minheap *h = malloc(sizeof(struct minheap));
  h->len = 0;
  h->maxlen = 1;
  h->data = NULL;
  return h;
}

// minheap_is_empty(h) determines if heap h is empty
// time: O(1)
bool minheap_is_empty(const struct minheap *h) {
  assert(h);
  if(h->data == NULL){
    return true;
  }else{
    return false;
  }
  
}

// minheap_insert(i, h) adds i to heap h
// effects: h is modified
// time:    O(logn), n is the size of the heap
void minheap_insert(int i, struct minheap *h) {
  assert(h);
  if(h->len == h->maxlen || h->len == 0){
    h->maxlen = h->maxlen * 2 + 1;
    h->data = realloc(h->data,  h->maxlen * sizeof(int)) ;
  }
  h->len++;
  int x = h->len - 1;
  h->data[x] = i;
  while(x != 0 && h->data[parent(x)] > h->data[x]){
     swap(&h->data[x], &h->data[parent(x)]);
     x = parent(x);
  }
}

// minheap_top(h) returns the top of the heap
// requires: h is not empty
// time:     O(1)
int minheap_top(const struct minheap *h) {
  assert(h);
  assert(h->data);
  return h->data[0];
}

// heapify(i, h) orders the heap according to the rules
// requires: h is not empty
// effects:  h is modified
// time:     O(logn), n is the size of the heap
static void heapify(int i, struct minheap *h){
  assert(h);
  
  int l = left_child(i);
  int r = right_child(i);
  int smallest = i;
  if(l < h->len && h->data[l] < h->data[i]){
    smallest = l;
  }
  if(r < h->len && h->data[r] < h->data[smallest]){
    smallest = r;
  }
  if(smallest != i){
    swap(&h->data[i], &h->data[smallest]);
    heapify(smallest, h);
  }
}

// minheap_remove(h) removes and returns the top of the heap
// requires: h is not empty
// effects:  h is modified
// time:     O(logn), n is the size of the heap
int minheap_remove(struct minheap *h) {
  assert(h);
  assert(h->len > 0);
  // if only one element
  if(h->len == 1){
    h->len--;
    return h->data[0];
  }

  // get the root
  int root = h->data[0];
  // put the maximum to root
  h->data[0] = h->data[h->len-1];
  // reduce the elements
  h->len--;
  // reorder
  heapify(0, h);
  // return root removed
  return root;
}

// minheap_destroy(h) frees all memory for h
// effects: h is no longer valid
// time:    O(1)
void minheap_destroy(struct minheap *h) {
  assert(h);
  // kill your child
  free(h->data);
  // before you kill yourself
  free(h);
}

// heap_helper(a, len, i) sorts a based on comparision
// requires: a is a valid array
// effects:  modifies a
// time:     O(logn)
static void heap_helper(int a[], int len, int i) {
  assert(a);
  assert(len >= 0);
  // set root largest
  int largest = i;  
  // left = 2*i + 1
  int l = 2*i + 1;  
  // right = 2*i + 2
  int r = 2*i + 2; 
  
  if(l < len && a[l] > a[largest]){
    //If left child is larger than the root
    largest = l;
  }
  
  if(r < len && a[r] > a[largest]){
    //If right child is larger than the current largest 
    largest = r;
  }
  // If largest isnt the root
  if(largest != i){
    // swap the largest with the root
    swap(&a[i], &a[largest]);
    // do for all recursively
    heap_helper(a, len, largest);
  }
}

// heapsort(a, len) sorts a in ascending order
// requires: a is a valid array, len > 0
// effects:  modifies a
// time:     O(nlogn)
void heapsort(int a[], int len) {
  assert(a);
  assert(len > 0);
  // heap builder
  for(int i = len / 2 - 1; i >= 0; i--){
    heap_helper(a, len, i);
  }
  // extract elements
  for(int i= len-1; i>=0; i--){
    // Move root to the end
    swap(&a[0], &a[i]);
    // do for all
    heap_helper(a, i, 0);
  }
}
