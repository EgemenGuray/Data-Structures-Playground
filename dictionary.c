#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include <cs136-tracing.h>
#include <string.h>

/////// DO NOT MODIFY DATA STRUCTURES OR PRINT CONSTANTS

struct bstnode {
  void *item;                // key
  void *value;               // additional value (augmentation)
  struct bstnode *left;
  struct bstnode *right;
  int size;                  // *** new augmentation (see notes)
};

struct dictionary {
  struct bstnode *root;
  // function pointers
  DictKeyCompare key_compare;
  FreeFunction free_key;
  FreeFunction free_val;
  PrintKeyVal print_keyval;  
};

const int PREORDER = -1;
const int INORDER = 0;
const int POSTORDER = 1;

/////////////////////////////


Dictionary dict_create(DictKeyCompare cmp_function,
                       FreeFunction free_key_function,
                       FreeFunction free_val_function,
                       PrintKeyVal print_function) {
  Dictionary d = malloc(sizeof(struct dictionary));
  d->root = NULL;
  d->key_compare = cmp_function;
  d->free_key = free_key_function;
  d->free_val = free_val_function;
  d->print_keyval = print_function;
  return d;
}



static struct bstnode *new_leaf(void *key, void *val){
  struct bstnode *leaf = malloc(sizeof(struct bstnode));
  leaf->left = NULL;
  leaf->right = NULL;
  leaf->item = key;
  leaf->value = val;
  leaf->size = 1;
  return leaf;
  
}

void dict_insert(void *key, void *val, Dictionary d) {
  assert(d);
  int increase = 0;
  struct bstnode *curnode = d->root;
  struct bstnode *prevnode = NULL;
  
  if(NULL == dict_lookup(key, d)){
    increase = 1;
  }
  
  while (curnode) {
    if (d->key_compare(curnode->item, key) == 0) {
      d->free_key(curnode->item);
      d->free_val(curnode->value);
      curnode->item = key;
      curnode->value = val;
      return;
    }
      prevnode = curnode;
    if (d->key_compare(curnode->item, key) > 0) {
      if(increase){
        curnode->size += 1;
      }
      curnode = curnode->left;
    } else {
      if(increase){
        curnode->size += 1;
      }
      curnode = curnode->right;
    }
  }
  if (prevnode == NULL) { // tree was empty
    d->root = new_leaf(key, val);
  } else if (d->key_compare(prevnode->item, key) > 0) {
    prevnode->left = new_leaf(key, val);
  } else {
    prevnode->right = new_leaf(key, val);
  }
}

static void *node_look(void *key, DictKeyCompare key_compare, struct bstnode *n){
  if(n == NULL){
    return NULL;
  }else if(key_compare(key, n->item) == 0){
    return n->value;
  }else if(key_compare(key, n->item) < 0){
    return node_look(key, key_compare, n->left);
  }else if(key_compare(key, n->item) > 0){
    return node_look(key, key_compare, n->right);
  }
  return NULL;
}


void *dict_lookup(void *key, Dictionary d) {
  return node_look(key, d->key_compare, d->root);
}

struct bstnode *remove_bstnode(void *key, struct bstnode *node, FreeFunction free_key, FreeFunction free_val, DictKeyCompare key_compare) {
  // key did not exist:
  if (node == NULL) return NULL;
    // search for the node that contains the key
  if (key_compare(key, node->item) < 0) {
    node->size -= 1;
    node->left = remove_bstnode(key, node->left, free_key, free_val, key_compare);
  } else if (key_compare(key, node->item) > 0) {
    node->size -= 1;
    node->right = remove_bstnode(key, node->right, free_key, free_val, key_compare);
  // (we have now found the key node)
  } else if (node->left == NULL) {
    struct bstnode *new_root = node->right;
    free_key(node->item);
    free_val(node->value);
    free(node);
    return new_root;
  } else if (node->right == NULL) {
    struct bstnode *new_root = node->left;
    free_key(node->item);
    free_val(node->value);
    free(node);
    return new_root;
  } else {
    // find the next largest key
    struct bstnode *next = node->right;
    while (next->left) {
      next = next->left;
    }
    // remove the old value===================================
    free_key(node->item);
    free_val(node->value);
    // replace the key/value of this node
    node->item = next->item;
    node->value = next->value;
    // remove the next largest key
    node->right = remove_bstnode(next->item, node->right, free_key, free_val, key_compare);
  }
  return node;
}
  
void dict_remove(void *key, Dictionary d) {
  assert(d);
  d->root = remove_bstnode(key, d->root, d->free_key, d->free_val, d->key_compare);
}


static void inorder_print(PrintKeyVal print_function, struct bstnode *n){
  if(n == NULL){
    return;
  }
  inorder_print(print_function, n->left);
  print_function(n->item, n->value);
  inorder_print(print_function, n->right);
}

static void preorder_print(PrintKeyVal print_function, struct bstnode *n){
  if(n == NULL){
    return;
  }
  print_function(n->item, n->value);
  preorder_print(print_function, n->left);
  preorder_print(print_function, n->right);
}

static void postorder_print(PrintKeyVal print_function, struct bstnode *n){
  if(n == NULL){
    return;
  }
  postorder_print(print_function, n->left);
  postorder_print(print_function, n->right);
  print_function(n->item, n->value);
  
}

void dict_print(int order, Dictionary d) {
  if(order == INORDER){
    inorder_print(d->print_keyval, d->root);
  }else if(order == PREORDER){
    preorder_print(d->print_keyval, d->root);
  }else{
    postorder_print(d->print_keyval, d->root);
  }
}

static void *select_node(int k, struct bstnode *n){
  assert(n);
  assert(0 <= k && k < n->size);
  int left_size = 0;
  if(n->left){
    left_size = n->left->size;
  }
  if(k < left_size){
    return select_node(k, n->left);
  }
  if(k == left_size){
    return n->item;
  }
  return select_node(k - left_size - 1, n->right);
}


void *dict_select(int k, Dictionary d) {
  assert(d);
  assert(0 <= k && k < dict_size(d));
  if(d->root == NULL){
   return NULL; 
  }else{
   return select_node(k, d->root);
  }
}


int dict_size(Dictionary d) {
  assert(d);
  return d->root->size;
}



static void node_destroy(struct bstnode *nd, FreeFunction free_key, FreeFunction free_val){
  if(nd){
    node_destroy(nd->left, free_key, free_val);
    node_destroy(nd->right, free_key, free_val);
    free_key(nd->item);
    free_val(nd->value);
    free(nd);
  }
  
}


void dict_destroy(Dictionary d) {
  assert(d);
  node_destroy(d->root, d->free_key, d->free_val);
  free(d);
}
