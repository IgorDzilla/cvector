#include "vector.h"

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

  for (int i = 0; i < 5; i++) {
    struct foo bar;
    memset(bar.buffer, 0, STRSIZE);
    sprintf(bar.buffer, "string %d", i);
    bar.a = i;
    bar.b = 3 * i;
    vector_push(&vec, &bar);
  }

  printf("INITIAL VECTOR\n");
  printf("SIZE OF VECTOR\t%zu\n", vec.length);
  for (size_t i = 0; i < vec.length; i++) {
    struct foo *bar = vector_at(&vec, i);
    printf("ELEMENT %zu\ta: %zu\tb: %zu\tstring: %s\n", i, bar->a, bar->b,
           bar->buffer);
  }

  struct foo bar = {"insert", 100, 200};
  vector_insert(&vec, vec.length, &bar);

  printf("AFTER INSERTION\n");
  printf("SIZE OF VECTOR\t%zu\n", vec.length);
  for (size_t i = 0; i < vec.length; i++) {
    struct foo *bar = vector_at(&vec, i);
    printf("ELEMENT %zu\ta: %zu\tb: %zu\tstring: %s\n", i, bar->a, bar->b,
           bar->buffer);
  }

  vector_remove(&vec, 1);

  printf("AFTER REMOVING\n");
  printf("SIZE OF VECTOR\t%zu\n", vec.length);
  for (size_t i = 0; i < vec.length; i++) {
    struct foo *bar = vector_at(&vec, i);
    printf("ELEMENT %zu\ta: %zu\tb: %zu\tstring: %s\n", i, bar->a, bar->b,
           bar->buffer);
  }

  puts(vec.data);

  return 0;
}
