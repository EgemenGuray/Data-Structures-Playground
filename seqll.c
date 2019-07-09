#include <stdio.h>
#include <stdlib.h>
#include "seqll.h"
#include <assert.h>

struct llnode {
  int item;
  struct llnode *next;
};

struct sequence {
  struct llnode *data;
};


struct sequence *sequence_create(void) {
  struct sequence *seq = malloc(sizeof(struct sequence));
  seq->data = NULL;
  return seq;
}


void sequence_destroy(struct sequence *seq) {
  assert(seq);
  struct llnode *curnode = seq->data;
  struct llnode *nextnode = NULL;
  while(curnode){
    nextnode = curnode->next;
    free(curnode);
    curnode = nextnode;    
  }
  free(seq);
}


int sequence_length(const struct sequence *seq) {
  assert(seq);
  int len = 0;
  struct llnode *node = seq->data;
  while(node){
    len++;
    node = node->next;
  }
  return len;
}


int sequence_item_at(const struct sequence *seq, int pos) {
  assert(seq);
  assert(0 <= pos);
  assert(pos < sequence_length(seq));
  int len = 0;
  struct llnode *node = seq->data;
  int retval = 0;
  while(node){
    if(pos == len){
      retval = node->item;
      break;
    }else{
      len++;
      node = node->next;
    }
  }
  node = NULL;
  free(node);
  return retval;
}


void sequence_insert_at(struct sequence *seq, int pos, int val) {
  assert(seq);
  assert(0 <= pos);
  assert(pos <= sequence_length(seq));
  int cur_pos = 0;
  if(seq->data == NULL || pos <= cur_pos){
    struct llnode *node = malloc(sizeof(struct llnode));
    node->item = val;
    node->next = seq->data;
    seq->data = node;
  }else{
    struct llnode *prevnode = seq->data;
    while (prevnode->next && pos - 1 > cur_pos) {
      prevnode = prevnode->next;
      cur_pos++;
    }
    struct llnode *newnode = malloc(sizeof(struct llnode));
    newnode->item = val;
    newnode->next = prevnode->next;
    prevnode->next = newnode;
  }
}


int sequence_remove_at(struct sequence *seq, int pos) {
  assert(seq);
  assert(0 <= pos);
  assert(pos < sequence_length(seq));
  int cur_pos = 0;
  int ret_val = 0;
  if(seq->data == NULL || pos < cur_pos + 1){
    struct llnode *curnode = seq->data;
    seq->data = seq->data->next;
    ret_val = curnode->item;
    free(curnode);
  }else{
    struct llnode *prevnode = seq->data;
    while (prevnode->next && pos - 1 > cur_pos) {
      prevnode = prevnode->next;
      cur_pos++;
    }
    struct llnode *curnode = prevnode->next;
    prevnode->next = curnode->next;
    ret_val = curnode->item;
    free(curnode);
  }
  return ret_val;
}


void sequence_print(const struct sequence *seq) {
  assert(seq);
  struct llnode *node = seq->data;
  if (!sequence_length(seq)) {
    printf("[empty]\n");
    return;
  }
  printf("[");
  while(node){
    printf("%d", node->item);
    node = node->next;
    if(node != NULL){
      printf(",");
    }
  }
  printf("]\n");
}

