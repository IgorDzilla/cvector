#include "tvector.h"
#include "cvector.h"
#include <stddef.h>

const size_t type_sizes[] = {
    [Int] = sizeof(int),       [Long] = sizeof(long int),
    [SizeT] = sizeof(size_t),  [Float] = sizeof(float),
    [Double] = sizeof(double), [LongDouble] = sizeof(long double),
    [String] = sizeof(char *)};

int validate_vector_type(val_t type) {
  for (int i = Int; i <= String; i++)
    if (type == i)
      return i;

  return -1;
}

void string_destructor(void *val) { free(val); }

int typed_vector_init(TypedVector *t_vec, val_t type) {
  if (!t_vec) {
    fprintf(stderr, "typed_vector_init: `vec` can't be NULL.\n");
    return VEC_INPUT_ERR;
  }

  if (validate_vector_type(type) < 0) {
    fprintf(stderr, "typde_vector_init: uknown type `type`.\n");
    return VEC_INPUT_ERR;
  }

  void (*destructor)(void *) = NULL;
  if (type == String)
    destructor = free;

  return vector_init(&t_vec->vec, type_sizes[type], destructor);
}
