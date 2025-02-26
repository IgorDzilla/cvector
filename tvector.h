#ifndef TVECTOR_H
#define TVECTOR_H

#include "vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/*
 * Inits new `TypedVector` at given pointer `tvec` with given `type`;
 * Returns VecErrors.
 * */
int typed_vector_init(TypedVector *tvec, val_t type);

/*
 * Clears memory used by `tvec`, leaving pointer unchanged.
 * */
int tvector_clear(TypedVector *tvec);

/* Functions for tvector_push macro*/
int tvector_push_string(TypedVector *tvec, char **new_val);
int tvector_push_long_double(TypedVector *tvec, long double *new_val);
int tvector_push_double(TypedVector *tvec, double *new_val);
int tvector_push_float(TypedVector *tvec, float *new_val);
int tvector_push_size_t(TypedVector *tvec, size_t *new_val);
int tvector_push_long(TypedVector *tvec, long *new_val);
int tvector_push_int(TypedVector *tvec, int *new_val);

/* Functions for tvector_push_fw macro*/
int tvector_push_fw_string(TypedVector *tvec, char **new_val);
int tvector_push_fw_long_double(TypedVector *tvec, long double *new_val);
int tvector_push_fw_double(TypedVector *tvec, double *new_val);
int tvector_push_fw_float(TypedVector *tvec, float *new_val);
int tvector_push_fw_size_t(TypedVector *tvec, size_t *new_val);
int tvector_push_fw_long(TypedVector *tvec, long *new_val);
int tvector_push_fw_int(TypedVector *tvec, int *new_val);

/* Funtions for tvector_at*/
int tvector_at_string(TypedVector *tvec, size_t index, char **new_val);
int tvector_at_long_double(TypedVector *tvec, size_t index,
                           long double *new_val);
int tvector_at_double(TypedVector *tvec, size_t index, double *new_val);
int tvector_at_float(TypedVector *tvec, size_t index, float *new_val);
int tvector_at_size_t(TypedVector *tvec, size_t index, size_t *new_val);
int tvector_at_long(TypedVector *tvec, size_t index, long *new_val);
int tvector_at_int(TypedVector *tvec, size_t index, int *new_val);

/* Functions for tvector_insert macro */
int tvector_insert_string(TypedVector *tvec, size_t index, char **new_val);
int tvector_insert_long_double(TypedVector *tvec, size_t index,
                               long double *new_val);
int tvector_insert_double(TypedVector *tvec, size_t index, double *new_val);
int tvector_insert_float(TypedVector *tvec, size_t index, float *new_val);
int tvector_insert_size_t(TypedVector *tvec, size_t index, size_t *new_val);
int tvector_insert_long(TypedVector *tvec, size_t index, long *new_val);
int tvector_insert_int(TypedVector *tvec, size_t index, int *new_val);

/* Functions for tvector_remove macro */
int tvector_remove_string(TypedVector *tvec, char **new_val);
int tvector_remove_long_double(TypedVector *tvec, long double *new_val);
int tvector_remove_double(TypedVector *tvec, double *new_val);
int tvector_remove_float(TypedVector *tvec, float *new_val);
int tvector_remove_size_t(TypedVector *tvec, size_t *new_val);
int tvector_remove_long(TypedVector *tvec, long *new_val);
int tvector_remove_int(TypedVector *tvec, int *new_val);

inline int type_err_msg(TypedVector *tvec, void *new_val) {
  fprintf(stderr, "tvector_push (macro): unsupported data type.\n");
  return T_VEC_TYPE_ERR;
}

/*
 * Pushes a `new_value` to the end of the given `TypedVector` tvec;
 * Returns VecErrors.
 * */
#define tvector_push(tvec, new_val)                                            \
  _Generic((tvec),                                                             \
      TypedVector *: _Generic((new_val),                                       \
                   int *: tvector_push_int,                                    \
                   long *: tvector_push_long,                                  \
                   size_t *: tvector_push_size_t,                              \
                   float *: tvector_push_float,                                \
                   double *: tvector_push_double,                              \
                   long double *: tvector_push_long_double,                    \
                   char **: tvector_push_string,                               \
                   const char **: tvector_push_string,                         \
                   default: type_err_msg, ))(tvec, new_val)

#define tvector_get(tvec, index, new_val)                                      \
  _Generic((tvec),                                                             \
      TypedVector *: _Generic((new_val),                                       \
                   int *: tvector_get_int,                                     \
                   long *: tvector_get_long,                                   \
                   size_t *: tvector_get_size_t,                               \
                   float *: tvector_get_float,                                 \
                   double *: tvector_get_double,                               \
                   long double *: tvector_get_long_double,                     \
                   char **: tvector_get_string,                                \
                   default: type_err_msg))(tvec, index, new_val)

#define tvector_insert(tvec, index, new_val)                                   \
  _Generic((tvec),                                                             \
      TypedVector *: _Generic((new_val),                                       \
                   int *: tvector_insert_int,                                  \
                   long *: tvector_insert_long,                                \
                   size_t *: tvector_insert_size_t,                            \
                   float *: tvector_insert_float,                              \
                   double *: tvector_insert_double,                            \
                   long double *: tvector_insert_long_double,                  \
                   char **: tvector_insert_string,                             \
                   const char **: tvector_insert_string,                       \
                   default: type_err_msg))(tvec, index, new_val)

#define tvector_push_fw(tvec, new_val)                                         \
  _Generic((tvec),                                                             \
      TypedVector *: _Generic((new_val),                                       \
                   int *: tvector_push_fw_int,                                 \
                   long *: tvector_push_fw_long,                               \
                   size_t *: tvector_push_fw_size_t,                           \
                   float *: tvector_push_fw_float,                             \
                   double *: tvector_push_fw_double,                           \
                   long double *: tvector_push_fw_long_double,                 \
                   char **: tvector_push_fw_string,                            \
                   const char **: tvector_push_fw_string,                      \
                   default: type_err_msg))(tvec, new_val)

#define tvector_remove(tvec, new_val)                                          \
  _Generic((tvec),                                                             \
      TypedVector *: _Generic((new_val),                                       \
                   int *: tvector_remove_int,                                  \
                   long *: tvector_remove_long,                                \
                   size_t *: tvector_remove_size_t,                            \
                   float *: tvector_remove_float,                              \
                   double *: tvector_remove_double,                            \
                   long double *: tvector_remove_long_double,                  \
                   char **: tvector_remove_string,                             \
                   const char **: tvector_remove_string,                       \
                   default: type_err_msg))(tvec, new_val)

#endif
