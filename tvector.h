#ifndef TVECTOR_H
#define TVECTOR_H

#include "cvector.c"

typedef enum vector_std_type {
  Int = 0,
  Long = 1,
  SizeT = 2,
  Float = 3,
  Double = 4,
  LongDouble = 5,
  String = 6,
} val_t;

typedef struct typed_vector {
  val_t type;
  Vector vec;
} TypedVector;

int typed_vector_init(TypedVector *t_vec, val_t type);

int int_vector_push(TypedVector *t_vec, int new_val);
int long_vector_push(TypedVector *t_vec, long new_val);
int size_t_vector_push(TypedVector *t_vec, size_t new_val);
int float_vector_push(TypedVector *t_vec, float new_val);
int double_vector_push(TypedVector *t_vec, double new_val);
int long_double_vector_push(TypedVector *t_vec, long double new_val);
int string_vector_push(TypedVector *t_vec, char *new_val);


#endif
