#include <stdio.h>
#include <assert.h>
#include "seqll.h"

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
  //sequence_print(q);
  sequence_remove_at(q, 0);
  //sequence_print(q);
  sequence_remove_at(q, 0);
  //sequence_print(q);
  sequence_remove_at(q, 0);
  //sequence_print(q);
  sequence_remove_at(q, 0);
  //sequence_print(q);
  sequence_remove_at(q, 1);
  assert(sequence_length(q) == 8);
  //sequence_print(q);
  sequence_remove_at(q, 2);
  sequence_remove_at(q, 6);
  sequence_remove_at(q, 0);
  sequence_remove_at(q, 0);
  sequence_remove_at(q, 0);
  sequence_remove_at(q, 0);
  
  sequence_remove_at(q, 0);
  sequence_remove_at(q, 0);
  sequence_insert_at(q, 0, 5);
  //sequence_print(q);
  sequence_destroy(q);
  
  // ============ MORE TESTS ============
  struct sequence *aq = sequence_create();
  assert(sequence_length(aq) == 0);
  sequence_insert_at(aq, 0, 0);
  sequence_insert_at(aq, 1, 1);
  sequence_insert_at(aq, 2, 2);
  sequence_insert_at(aq, 3, 3);
  sequence_insert_at(aq, 4, 4);
  sequence_insert_at(aq, 5, 5);
  //sequence_print(aq);
  sequence_insert_at(aq, 0, 0);
  sequence_insert_at(aq, 1, 1);
  sequence_insert_at(aq, 2, 2);
  sequence_insert_at(aq, 3, 3);
  sequence_insert_at(aq, 4, 4);
  sequence_insert_at(aq, 5, 5);
  sequence_insert_at(aq, 12, 1927);
  
  //sequence_print(aq);
  assert(sequence_item_at(aq, 0) == 0);
  assert(sequence_item_at(aq, 1) == 1);
  assert(sequence_item_at(aq, 2) == 2);
  assert(sequence_item_at(aq, 3) == 3);
  assert(sequence_item_at(aq, 4) == 4);
  assert(sequence_item_at(aq, 5) == 5);
  assert(sequence_item_at(aq, 6) == 0);
  assert(sequence_item_at(aq, 7) == 1);
  assert(sequence_item_at(aq, 8) == 2);
  assert(sequence_item_at(aq, 9) == 3);
  assert(sequence_item_at(aq, 10) == 4);
  assert(sequence_item_at(aq, 11) == 5);
  assert(sequence_item_at(aq, 12) == 1927);
  sequence_remove_at(aq, 12);
  assert(sequence_item_at(aq, 0) == 0);
  assert(sequence_item_at(aq, 1) == 1);
  assert(sequence_item_at(aq, 2) == 2);
  assert(sequence_item_at(aq, 3) == 3);
  assert(sequence_item_at(aq, 4) == 4);
  assert(sequence_item_at(aq, 5) == 5);
  assert(sequence_item_at(aq, 6) == 0);
  assert(sequence_item_at(aq, 7) == 1);
  assert(sequence_item_at(aq, 8) == 2);
  assert(sequence_item_at(aq, 9) == 3);
  assert(sequence_item_at(aq, 10) == 4);
  assert(sequence_item_at(aq, 11) == 5);
  sequence_remove_at(aq, 6);
  assert(sequence_item_at(aq, 0) == 0);
  assert(sequence_item_at(aq, 1) == 1);
  assert(sequence_item_at(aq, 2) == 2);
  assert(sequence_item_at(aq, 3) == 3);
  assert(sequence_item_at(aq, 4) == 4);
  assert(sequence_item_at(aq, 5) == 5);
  assert(sequence_item_at(aq, 6) == 1);
  assert(sequence_item_at(aq, 7) == 2);
  assert(sequence_item_at(aq, 8) == 3);
  assert(sequence_item_at(aq, 9) == 4);
  assert(sequence_item_at(aq, 10) == 5);
  sequence_destroy(aq);
}