#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "trie.h"
#include "wordlist.h"
#include <assert.h>


struct wordlist{
  struct trie *t;
  int count;
};

struct wordlist *wordlist_create(void) {
  struct wordlist *w1 = malloc(sizeof(struct wordlist));
  w1->t = trie_create();
  w1->count = 0;
  return w1;
}

bool wordlist_lookup(const char *s, const struct wordlist *wl) {
  assert(wl);
  return trie_lookup(s, wl->t);
}

void wordlist_add(const char *s, struct wordlist *wl){ 
  assert(wl);
  if(!wordlist_lookup(s, wl)){
    trie_add(s, wl->t);
    wl->count += 1;
  }
}


void wordlist_remove(const char *s, struct wordlist *wl) {
  assert(wl);
  if(wordlist_lookup(s,wl)){
    trie_remove(s,wl->t);
    wl->count -= 1;
  }
}


void wordlist_destroy(struct wordlist *wl) {
  assert(wl);
  trie_destroy(wl->t);
  free(wl);
}


void wordlist_print(const struct wordlist *wl) {
  assert(wl);
  trie_print(wl->t);
}


int wordlist_count(const struct wordlist *wl) {
  assert(wl);
  return wl->count;
}
