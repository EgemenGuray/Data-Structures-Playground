#include "seqlazy.h"
#include "cs136-tracing.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <limits.h>

static const int DELETED = INT_MIN;

struct sequence {
  int len;
  int maxlen;
  int pending;
  int *data;
};


struct sequence *sequence_create(void) {
  struct sequence *seq = malloc(sizeof(struct sequence));
  seq->len = 0;
  seq->pending = 0;
  seq->maxlen = 1;
  seq->data = malloc(sizeof(int));
  return seq;
}


void sequence_destroy(struct sequence *seq) {
  assert(seq);
  free(seq->data);
  free(seq);
}


int sequence_length(const struct sequence *seq) {
  assert(seq);
  return seq->len - seq->pending;
}


int sequence_item_at(const struct sequence *seq, int pos) {
  assert(seq);
  assert(0 <= pos);
  assert(pos < seq->len - seq->pending);
  int x = 0;
  int i = 0;
  while(true){
    if(x == pos && seq->data[i] != DELETED){
      break;
    }
    if(seq->data[i] != DELETED){
      x++;
    }
    i++;
    
  }
  return seq->data[i];
}


void sequence_insert_at(struct sequence *seq, int pos, int val) {
  // error check
  assert(seq);
  assert(0 <= pos);
  assert(pos  <= seq->len - seq->pending);
  
  // if needed remove
  if(seq->pending > 0){
    // dummy array
    int *a = malloc(seq->maxlen * sizeof(int));
    int x = 0;
    for(int i = 0; i < seq->len; i++){
      if(seq->data[i] != DELETED){
        // add if not deleted
        a[x] = seq->data[i];
        x++;
      }
      
    }
    // new length
    seq->len = x;
    // fill all
    for(int i = 0; i < seq->len; i++){
      seq->data[i] = a[i];
    }
    // free dummy array
    free(a);
    seq->pending = 0;
  }
  
  // resize if needed
  if(seq->len == seq-> maxlen){
    seq->maxlen *= 2;
    seq->data = realloc(seq->data, seq->maxlen * sizeof(int));
  }
  // shift
  for(int i = seq->len - 1; i >= pos ; i--){
    seq->data[i + 1] = seq->data[i];
  }
  // add
  seq->data[pos] = val;
  seq->len++;
  // if neccecessery resize
  if(seq->len == seq-> maxlen / 4){
    seq->maxlen /= 2;
    seq->data = realloc(seq->data, seq->maxlen * sizeof(int));
  }
  
  
}


int sequence_remove_at(struct sequence *seq, int pos) {
  assert(seq);
  assert(0 <= pos);
  assert(pos < seq->len - seq->pending);
  int x = 0;
  int i = 0;
  while(true){
    if(x == pos && seq->data[i] != DELETED){
      break;
    }
    if(seq->data[i] != DELETED){
      x++;
    }
    i++;
    
  }
  int retval = seq->data[i];
  seq->data[i] = DELETED;
  seq->pending++;
  return retval;
}


void sequence_print(const struct sequence *seq) {
  assert(seq);
  if (!seq->len || seq->len == seq->pending) {
    printf("[empty]\n");
    return;
  }
  int x = 0;
  while(true){
    if(seq->data[x] != DELETED){
      printf("[%d", seq->data[x]);
      break;
    }
    x++;
  }
  for(int i = x + 1; i < seq->len ; i++){
    if(seq->data[i] != DELETED){
      printf(",%d", seq->data[i]);
    }
  }
  printf("]\n");
}



void sequence_lazy_print(const struct sequence *seq) {
  assert(seq);
  if (!seq->len) {
    printf("[empty]\n");
    return;
  }
  if(seq->data[0] != DELETED){
    printf("[%d", seq->data[0]);
  }else{
    printf("[DELETED");
  }
  for(int i = 1; i < seq->len ; i++){
    if(seq->data[i] != DELETED){
      printf(",%d", seq->data[i]);
    }else{
      printf(",DELETED");
    }
  }
  printf("]\n");
}
