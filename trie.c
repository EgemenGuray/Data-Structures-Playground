#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "trie.h"
#include <assert.h>


struct trie *trie_create(void) {
  struct trie *a = malloc(sizeof(struct trie));
  a->root = NULL;
  return a;
}

struct trienode *generate_node(void){
  // allocate memory
  struct trienode *new_node = malloc(sizeof(struct trienode));
  // if allocated
  if(new_node){
    // set false word end as default
    new_node->word_end = false;
    // NULLize array as default
    for(int i = 0; i < 26; i++)
       new_node->children[i] = NULL;
    }
  return new_node;
}

void trie_add(const char *s, struct trie *t) {
  assert(t);
  // if t->root is NULL add the first node
  if(t->root == NULL){
    t->root = generate_node();
  }
  
  // initial node
  struct trienode *current_node = t->root;
  
  int i = 0;
  while(s[i]){
    // find index
    int index = s[i] - 'a';
    // if no node
    if(!current_node->children[index]){
      current_node->children[index] = generate_node();
    }
    current_node = current_node->children[index];
    i++;
  }
  
  // mark last node as leaf
  current_node->word_end = true;

}

static bool is_free_node(struct trienode *tn){
  for(int i = 0; i < 26; i++){
    if(tn->children[i]){
      return false;
    }
  }
  return true;
}

static bool remove_helper(struct trienode *tn, const char *s, int lev, int len){
  if(tn){
    // base case
    if(lev == len){
      if(tn->word_end){
        tn->word_end = false;
        // If empty, node to be deleted
        if(is_free_node(tn)){
          return true;
        }
        return false;
      }
    }else{
      int index = s[lev] - 'a';
      if(remove_helper(tn->children[index], s, lev+1, len)){
        // last node marked, delete it
        free(tn->children[index]);
        tn->children[index] = NULL;
        // recursively climb up, and delete eligible nodes
        return(!tn->word_end && is_free_node(tn));
      }
    }
  }
  return false;
}

void trie_remove(const char *s, struct trie *t) {
  assert(t);
  int len = strlen(s);
  if(len > 0){
    remove_helper(t->root, s, 0, len);
  }
}


bool trie_lookup(const char *s, const struct trie *t) {
  assert(s);
  assert(t);
  // if t->root is NULL word DNE
  if(t->root == NULL){
    return false;
  }
  
  // set up initial node
  struct trienode *current_node = t->root;
  
  int i = 0;
  while(s[i]){
    // find index
    int index = s[i] - 'a';
    if(!current_node->children[index]){
      // if index null word DNE
      return false;
    }
    // if not null get the next node
    current_node = current_node->children[index];
    i++;
  }
  // if the next node after 
  if(current_node->word_end == true){
    return true;
  }else{
    return false;
  }
}

static void node_destroy(struct trienode *tn){
  if(tn == NULL){
    free(tn);
  }else{
    for(int i = 0; i < 26; i++){
      if(tn->children[i] != NULL){
        node_destroy(tn->children[i]);
      }
    }
    free(tn);
  }
  
}


void trie_destroy(struct trie *t){
  node_destroy(t->root);
  free(t);
}

char *my_strdup(const char *src, int maxlen, int len) {
  
  char *dup = malloc(maxlen * sizeof(char));
  for(int i = 0; i < len; i++){
    dup[i] = src[i];
  }
  return dup;
}

static void node_char_print(struct trienode *tn, int len, char *a, int maxlen){
  if(tn == NULL){
    return;
  }else{
    if(tn->word_end){
      if(len == maxlen){
        
        maxlen *= 2;
        
        a = realloc(a, (maxlen + 1) * sizeof(char) );
      }
      
      a[len] = '\0';
      printf("%s", a);
      printf("\n");
    }
    for(int i = 0; i < 26; i++){
      if(tn->children[i] != NULL){
        if(len == maxlen){
          maxlen *= 2;
          a = realloc(a, (maxlen + 1) * sizeof(char));
        }
        a[len] = 'a' + i;
        len++;
        node_char_print(tn->children[i], len, my_strdup(a, maxlen, len), maxlen);
        len--;
      }
       
    }
    free(a);
  }
}

void trie_print(const struct trie *t) {
  char *a = malloc(1 * sizeof(char));
  node_char_print(t->root, 0, a, 1);
}

static void node_char_array(struct trienode *tn, int len, char *a, int maxlen, char **ar, int *alen, int *amaxlen, int *amaxdepth){
  if(tn == NULL){
    free(a);
    return;
  }else{
    if(tn->word_end){
      if(len == maxlen){
        maxlen *= 2;
        if(*amaxdepth < maxlen){
          *amaxdepth = maxlen;
        }
        a = realloc(a, (maxlen + 1) * sizeof(char) );
      }
      a[len] = '\0';
      char *b = malloc((maxlen + 1) * sizeof(char));
      for(int i = 0; i <= len; i++){
        b[i] = a[i];
      }
      if(*alen == *amaxlen){
        *amaxlen *= 2;
        ar = realloc(ar, (*amaxlen + 1) * *amaxdepth * sizeof(char));
      }
      ar[*alen] = b;
      *alen += 1;
    }
    for(int i = 0; i < 26; i++){
      if(len == maxlen){
        maxlen *= 2;
        if(*amaxdepth < maxlen){
          *amaxdepth = maxlen;
        }
        a = realloc(a, (maxlen + 1) * sizeof(char));
      }
      a[len] = 'a' + i;
      len++;
      char *c = malloc((maxlen + 1) * sizeof(char));
      for(int j = 0; j < len; j++){
        c[j] = a[j];
      }
      node_char_array(tn->children[i], len, c, maxlen, ar, alen, amaxlen, amaxdepth);
      len--;
      
    }
    free(a);
    
  }
}

char **trie_to_aos(const struct trie *t) {
  int len = 0;
  int maxlen = 520;
  int maxdepth = 1280;
  char *a = malloc(1 * sizeof(char));
  char **ar = malloc(maxlen * maxdepth * sizeof(char));
  node_char_array(t->root, 0, a, 1, ar, &len , &maxlen, &maxdepth);
  return ar;
}

static void node_end_count(struct trienode *tn, int *total){
  if(tn == NULL){
    *total += 0;
  }else{
    if(tn->word_end){
      *total += 1;
    }
    for(int i = 0; i < 26; i++){
      if(tn->children[i] != NULL){
        node_end_count(tn->children[i], total);
      }
    }
  }
}
int trie_count(const struct trie *t) {
  int total = 0;
  node_end_count(t->root, &total);
  return total;
}
