#include "arraystrings.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// DO NOT MODIFY THIS STRUCTURE
struct aos {
  int len;
  int maxlen;
  char **words;
};


void print_strings(struct aos *a) {
  for (int i = 0; i < a->len; ++i) {
    printf("%s\n", a->words[i]);
  }
}

char *readstr(int *x) {
  char c;
  if (scanf(" %c", &c) != 1) return NULL; // ignore initial WS
  int maxlen = 1;
  int len = 1;
  char *str = malloc(maxlen * sizeof(char));
  str[0] = c;
  while (1) {
    if (scanf("%c", &c) != 1) break;
    if (c == ' ' || c == '\n') break;
    if (len == maxlen) {
      maxlen *= 2;
      str = realloc(str, maxlen * sizeof(char));
    }
    ++len;
    str[len - 1] = c;
  }
  str = realloc(str, (len + 1) * sizeof(char));
  str[len] = '\0';
  if(*x < len + 1){
    *x = len + 1;
  }
  return str;
}

struct aos *aos_read_words(void) {
  int z = 1;
  struct aos *a = malloc(sizeof(struct aos));
  a->len = 0;
  a->maxlen = 1;
  a->words = malloc(a->maxlen * 10 * sizeof(char));
  while(1){
    char *x = readstr(&z);
    if(x == NULL){
      break;
    }
    if (a->len == a->maxlen) {
      a->maxlen *= 2;
      z *=2;
      a->words = realloc(a->words, z * a->maxlen * sizeof(char));
    }
   
    a->words[a->len] = x;
    a->len++;
  }

  return a;
}


void aos_destroy(struct aos *a) {
  assert(a);
  for(int i = 0; i < a->len; i++){
    free(a->words[i]);
  }
  free(a->words);
  free(a);
}
