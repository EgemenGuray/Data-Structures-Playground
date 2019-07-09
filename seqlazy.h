#include <stdbool.h>

// Sequence: provides an Integer Sequence ADT
// NOTE: ALL sequence parameters must be valid

// This ADT uses "lazy deletion" (see assignment)
// Where elements are not actually removed until an insert occurs

// NOTE: the interface of the lazy ADT is identical to the non-lazy ADTs,
//       only the running times are affected

// O(d) is the number of pending deletions, or O(1) if there are none


struct sequence;

// sequence_create() returns a pointer to a new (empty) sequence
// effects: allocates memory (caller must call sequence_destroy)
// time: O(1)
struct sequence *sequence_create(void);

// sequence_destroy(seq) frees all dynamically allocated memory 
// effects: the memory at seq is invalid (freed)
// time: O(1)
void sequence_destroy(struct sequence *seq);

// sequence_length(seq) returns the number of items in seq
// time: O(1)
int sequence_length(const struct sequence *seq);

// sequence_item_at(seq, pos) returns the item in seq at position pos
// requires: 0 <= pos < sequence_length(seq)
// time: O(d) [see above]
int sequence_item_at(const struct sequence *seq, int pos);

// sequence_insert_at(seq, pos, val) inserts a new item with value val
//   at position pos in seq
//   (changing the position of items at position >= pos)
// requires: 0 <= pos <=  sequence_length(seq)
// effects: seq is modified
// time: O(n)
void sequence_insert_at(struct sequence *seq, int pos, int val);

// sequence_remove_at(seq, pos) removes the item at position pos in seq
//   and returns the removed value
//   (changing the position of items > pos)
// requires: 0 <= pos <  sequence_length(seq)
// effects: seq is modified
// time: O(d) [see above]
int sequence_remove_at(struct sequence *seq, int pos);

// sequence_print(seq) prints out the items in seq
//   using the format: "[item_0,item_1,...,item_last]\n"
//   or "[empty]\n"
// effects: prints out a message
// time : O(n)
void sequence_print(const struct sequence *seq);

// sequence_lazy_print(seq) prints out the items in seq including
//   those marked as DELETED that have not yet been removed, for example:
//   "[item_0,DELETED,item_1,item_2,DELETED,item_3,...,item_last]\n"
//   or "[empty]\n"
// note: identical to sequence_print if there are no pending deletions
// effects: prints out a message
// time : O(n + d) [see above]
void sequence_lazy_print(const struct sequence *seq);
