#include "arraystrings.h"

int main(void) {
  struct aos *a = aos_read_words();
  print_strings(a);
  aos_destroy(a);
}
