#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h> 
#include "trie.h"

// a simple assertion-based client for the trie module

// you may want to consider making your own I/O based client

int main(void) {
  struct trie *t = trie_create();
  assert(t);
  assert(t->root == NULL);
  assert(trie_count(t) == 0);
  trie_add("a", t);
  assert(trie_lookup("a", t));  
  assert(trie_count(t) == 1);
  assert(t->root->children[0]);
  assert(t->root->children[0]->word_end);
  trie_print(t);
  char **aos = trie_to_aos(t);
  assert(aos);
  assert(!strcmp("a", aos[0]));
  free(aos[0]);
  free(aos);
  assert(!trie_lookup("b", t));
  trie_add("b", t);
  assert(t->root->children[1]);
  assert(t->root->children[1]->word_end);
  assert(trie_lookup("b", t));
  assert(trie_count(t) == 2);
  trie_remove("b", t);
  assert(t->root->children[1] == NULL);
  assert(!trie_lookup("b", t));
  assert(trie_count(t) == 1);
  trie_destroy(t); 
  /*
  struct trie *at = trie_create();
  trie_add("", at);
  trie_add("zoo", at);
  trie_add("ot", at);
  trie_add("at", at);
  trie_add("a", at);
  trie_add("ege", at);
  trie_add("egemen", at);
  trie_add("azoo", at);
  trie_add("aot", at);
  trie_add("aat", at);
  trie_add("kaa", at);
  trie_add("caege", at);
  trie_add("baegemen", at);
  char **s = trie_to_aos(at);
  assert(s);
  printf("%s\n", s[0]);
  printf("%s\n", s[1]);
  printf("%s\n", s[2]);
  printf("%s\n", s[3]);
  printf("%s\n", s[4]);
  printf("%s\n", s[5]);
  printf("%s\n", s[6]);
  printf("%s\n", s[7]);
  printf("%s\n", s[8]);
  printf("%s\n", s[9]);
  printf("%s\n", s[10]);
  printf("%s\n", s[11]);
  printf("%s\n", s[12]);
  free(s[0]);
  free(s[1]);
  free(s[2]);
  free(s[3]);
  free(s[4]);
  free(s[5]);
  free(s[6]);
  free(s[7]);
  free(s[8]);
  free(s[9]);
  free(s[10]);
  free(s[11]);
  free(s[12]);
  free(s);
  trie_print(at);
  trie_destroy(at); 
  */
}
