#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "suggest.h"




static void remove_char(char *str, int index) {

  char *src;
  char garbage = str[index];
  char *dst;
  for (src = dst = str; *src != '\0'; src++) {
      *dst = *src;
      if (*dst != garbage) dst++;
  }
  *dst = '\0';
}



static void single_deletions(const char *s, bool (*is_word)(const char *), int i, struct wordlist *w){
  
  for(int a = 0; a < i - 1; a++){
    char* str = malloc(i* sizeof(char));
    strcpy(str, s);
    remove_char(str, a);
    if(is_word(str) && strcmp(str, s)){
      //printf("%s\n", str);
      wordlist_add(str, w);
      free(str);
    }else{
      free(str);
    }
  }
}

static void subs_char(char *str, int index, char x) {
  char *src;
  char *dst;
  int curpos = 0;
  for (src = dst = str; *src != '\0'; src++) {
    if(curpos == index){
      *dst = x;
      
    }
      *dst = *src;
      dst++;
      curpos++;
    
  }
  *dst = '\0';
}

static void single_subs(const char *s, bool (*is_word)(const char *), int i,struct wordlist *w){
 for(char z = 0 + 'a'; z < 26 + 'a'; z++){
  for(int a = 0; a < i - 1; a++){
    char* str = malloc(i* sizeof(char));
    strcpy(str, s);
    subs_char(str, a , z);
    if(is_word(str) && strcmp(str, s)){
      //printf("%s\n", str);
      wordlist_add(str, w);
      free(str);
    }else{
      free(str);
    }
  }
 }
}

static void ins_char(char *str, int index, char z, int len,  bool (*is_word)(const char *),struct wordlist *w) {
  char *p = malloc((len + 1) * sizeof(char));
  int x = 0;
  for(int i = 0; i < len - 1 ; i++){
    if(i == index){
      p[i] = z;
      x++;
    }
    p[x] = str[i];
    x++;
  }
  p[len - 1] = '\0';
  if(is_word(p) && strcmp(str, p)){
      //printf("%s\n", p);
      wordlist_add(p, w);
      free(p);
  }else{
      free(p);
  }
}

static void single_ins(const char *s, bool (*is_word)(const char *), int i, struct wordlist *w){
 for(char z = 0 + 'a'; z < 26 + 'a'; z++){
  for(int a = 0; a <= i; a++){
    char* str = malloc((i + 1) * sizeof(char));
    strcpy(str, s);
    ins_char(str, a , z, i + 1, is_word, w);
    free(str);
  }
 }
}

static void swap_char(char *s, int a, int len){
  if(a < len - 1){
    char dummy = s[a];
    s[a] = s[a + 1];
    s[a + 1] = dummy;
  }
}

static void adj_swap(const char *s, bool (*is_word)(const char *), int i, struct wordlist *w){
  for(int a = 0; a < i; a++){
    char* str = malloc((i + 1) * sizeof(char));
    strcpy(str, s);
    swap_char(str, a , i);
    if(is_word(str) && strcmp(str, s)){
      //printf("%s\n", str);
      wordlist_add(str, w);
      free(str);
    }else{
      free(str);
    }
  }
}
                      
struct wordlist *suggest(const char *s, bool (*is_word)(const char *)) {
  struct wordlist *w = wordlist_create();
  int len = strlen(s);
  len += 1;
  single_deletions(s, is_word, len, w);
  single_subs(s, is_word, len, w);
  single_ins(s, is_word, len, w);
  adj_swap(s, is_word, len, w);
  return w;
}


