#include "seqarray.h"
#include "cs136-tracing.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

struct sequence {
  int len;
  int maxlen;
  int *data;
};


struct sequence *sequence_create(void) {
  struct sequence *seq = malloc(sizeof(struct sequence));
  seq->len = 0;
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
  return seq->len;
}


int sequence_item_at(const struct sequence *seq, int pos) {
  assert(seq);
  assert(0 <= pos);
  assert(pos < seq->len);
  return seq->data[pos];
}


void sequence_insert_at(struct sequence *seq, int pos, int val) {
  assert(seq);
  assert(0 <= pos);
  assert(pos <= seq->len);
  if(seq->len == seq-> maxlen){
    seq->maxlen *= 2;
    seq->data = realloc(seq->data, seq->maxlen * sizeof(int));
  }
  for(int i = seq->len - 1; i >= pos ; i--){
    seq->data[i + 1] = seq->data[i];
  }
  seq->data[pos] = val;
  seq->len++;
  
}


int sequence_remove_at(struct sequence *seq, int pos) {
  assert(seq);
  assert(0 <= pos);
  assert(pos < seq->len);
  int retval = seq->data[pos];
  for(int i = pos + 1 ; i < seq->len ; i++){
    seq->data[i - 1] = seq->data[i];
  }
  if(seq->len == seq-> maxlen / 4){
    seq->maxlen /= 2;
    seq->data = realloc(seq->data, seq->maxlen * sizeof(int));
  }
  seq->len -= 1;
  return retval;
}


void sequence_print(const struct sequence *seq) {
  assert(seq);
 
  
  if (!seq->len) {
    printf("[empty]\n");
    return;
  }
  printf("[%d", seq->data[0]);
  for(int i = 1; i < seq->len ; i++){
    printf(",%d", seq->data[i]);
  }
  printf("]\n");
}

