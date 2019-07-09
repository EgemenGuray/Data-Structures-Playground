#include <stdlib.h>
#include <stdio.h>

struct aos;

// print_strings(a) prints the strings stored in a, one per line
// effects: prints words to output
void print_strings(struct aos *a);

// aos_read_words() creates an array of strings structure
// effects: reads words from input,
//          allocates memory (client must call aos_destroy)
// time: amortized O(nm) where 
//    n is the number of words read from input
//    m is the length of the longest string read
struct aos *aos_read_words(void);

// aos_destroy(a) frees all memory of a
// requires: a must be from a previous malloc
// effects: the memory at a is invalid
void aos_destroy(struct aos *a);
