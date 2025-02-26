#ifndef CVECTOR_H
#define CVECTOR_H

#include <stdlib.h>

typedef enum VecErrors {
  VEC_SUCCESS = 0,
  VEC_INPUT_ERR = -1,
  VEC_MEM_ERR = -2,
  VEC_RANGE_ERR = -3,
  T_VEC_TYPE_ERR = -4,
} VecErrors;

typedef struct c_vector Vector;

typedef struct c_vector {
  size_t length;
  size_t val_size;
  char *data;
  void (*destructor)(void *);
} Vector;

/*
 * Inits a new `Vector` at a given pointer with given `val_size` and
 * `destructor`.
 * `val_size` - size of value stored in vector.
 * `destructor` - function to free memory used by individual element.
 * */
int vector_init(Vector *vec, size_t val_size, void (*destructor)(void *));

/*
 * Clears memory used by `vec`, but leaves the preferences of vector
 * */
int vector_clear(Vector *vec);

int vector_push(Vector *vec, void *new_val);

int vector_insert(Vector *vec, size_t index, void *new_val);

int vector_push_fw(Vector *vec, void *new_val);

int vector_remove(Vector *vec, size_t index);

void *vector_at(Vector *vec, size_t index);

#endif // !CVECTOR_H
