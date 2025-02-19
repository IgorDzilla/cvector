#include "cvector.h"

#include <stdio.h>
#include <string.h>

#define STRSIZE 32

struct foo {
  char buffer[STRSIZE];
  size_t a, b;
};

int main(void) {
  Vector vec;
  vector_init(&vec, sizeof(struct foo), NULL);

  for (int i = 10; i < 16; i++) {
    struct foo *bar = (struct foo *)malloc(sizeof(struct foo));
    memset(bar->buffer, 0, STRSIZE);
    sprintf(bar->buffer, "string %d", i);
    bar->a = 2 * i;
    bar->b = 3 * i;
    vector_push(&vec, bar);
    free(bar);
  }

  struct foo bar = {"insert", 100, 200};
  vector_insert(&vec, 3, &bar);

  printf("SIZE OF VECTOR\t%zu\n", vec.length);
  for (size_t i = 0; i < vec.length; i++) {
    struct foo *bar = vector_at(&vec, i);
    printf("ELEMENT %zu\ta: %zu\tb: %zu\tstring: %s\n", i, bar->a, bar->b,
           bar->buffer);
  }

  puts(vec.data);


  return 0;
}
