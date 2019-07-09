#include <stdio.h>
#include <assert.h>
#include "seqarray.h"
#include "cs136-tracing.h"

int main(void) {
  struct sequence *seq = sequence_create();
  assert(sequence_length(seq) == 0);
  sequence_insert_at(seq, 0, 27);
  assert(sequence_item_at(seq, 0) == 27);
  assert(sequence_length(seq) == 1);
  sequence_destroy(seq);
  // =========== MORE TEST ============
  struct sequence *q = sequence_create();
  assert(sequence_length(q) == 0);
  sequence_insert_at(q, 0, 27);
  assert(sequence_item_at(q, 0) == 27);
  assert(sequence_length(q) == 1);
  sequence_insert_at(q, 0, 17);
  assert(sequence_item_at(q, 0) == 17);
  sequence_insert_at(q, 0, 1);
  sequence_insert_at(q, 1, 2);
  sequence_insert_at(q, 2, 3);
  sequence_insert_at(q, 3, 4);
  sequence_insert_at(q, 4, 5);
  sequence_insert_at(q, 0, 1);
  sequence_insert_at(q, 1, 2);
  sequence_insert_at(q, 2, 3);
  sequence_insert_at(q, 3, 4);
  sequence_insert_at(q, 4, 5);
  sequence_insert_at(q, 4, 5);
  sequence_remove_at(q, 0);
  sequence_remove_at(q, 0);
  sequence_remove_at(q, 0);
  sequence_remove_at(q, 0);
  sequence_remove_at(q, 2);
  sequence_remove_at(q, 1);
  sequence_remove_at(q, 1);
  //sequence_print(q);
  sequence_remove_at(q, 5);
  assert(sequence_item_at(q, 0) == 5);
  assert(sequence_item_at(q, 1) == 3);
  //sequence_insert_at(q, 1, 5);
  //sequence_print(q);
  assert(sequence_length(q) == 5);
  sequence_insert_at(q, 1, 5);
  //sequence_print(q);
  sequence_insert_at(q, 6, 5);
  sequence_insert_at(q, 6, 1);
  sequence_insert_at(q, 6, 1);
  sequence_remove_at(q, 0);
  sequence_remove_at(q, 0);
  sequence_remove_at(q, 0);
  sequence_remove_at(q, 0);
  sequence_remove_at(q, 0);
  sequence_remove_at(q, 0);
  sequence_remove_at(q, 0);
  sequence_remove_at(q, 0);
  sequence_remove_at(q, 0);
  sequence_insert_at(q, 0, 5);
  //sequence_print(q);
  sequence_destroy(q);
}