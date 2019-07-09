#include <stdio.h>
#include "deqll.h"

// check_result(result) returns false if result is 1
//   otherwise true
// effects: prints a message
bool check_result(int result) {
  if (result != 1) {
    printf("Something went wrong, bad input!\n");
    return true;
  }
  return false;
}

int main(void) {
  char c;
  int n;
  struct dequeue *deq;
  
  deq = dequeue_create();
  while(1) {
    if (check_result(scanf(" %c", &c))) break;
  
    // You should add more cases here for I/O testing
    if (c == 'a') {
      if (check_result(scanf(" %c", &c))) break;
      if (check_result(scanf("%d", &n))) break;
      if (c == 'b') {
        dequeue_add_back(n, deq);
      } else if (c == 'f') {
        dequeue_add_front(n, deq);
      } else {
        printf("Invalid parameter for ADD operation.\n");
        continue;
      }
    } else if (c == 'r'){
      if (check_result(scanf(" %c", &c))) break;
      if (c == 'b') {
        int x = 0;
        x = dequeue_remove_back(deq);
        printf("Element deleted %d.\n", x);
      } else if (c == 'f') {
        int x = 0;
        x = dequeue_remove_front(deq);
        printf("Element deleted %d.\n", x);
      } else {
        printf("Invalid parameter for ADD operation.\n");
        continue;
      }
    } else if (c == 'f') {
      printf("Front element %d.\n", dequeue_front(deq));
    } else if (c == 'b') {
      printf("Back element %d.\n", dequeue_back(deq));
    } else if (c == 'p') {
      dequeue_print(deq);
    } else if (c == 'q') {
      break;
    } else {
      printf("Invalid operation request.\n");
      continue;
    }
  }
  dequeue_destroy(deq);
}
    
