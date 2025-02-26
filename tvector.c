#include "tvector.h"
#include "vector.h"

#include <stdio.h>

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

int tvector_clear(TypedVector *tvec) {
  if (!tvec) {
    fprintf(stderr, "typed_vector_clear:");
    return VEC_INPUT_ERR;
  }

  return vector_clear(&tvec->vec);
}

int tvector_push_int(TypedVector *tvec, int *new_val) {
  if (!tvec) {
    fprintf(stderr, "tvector_append: `tvec` can't be NULL.\n");
    return VEC_INPUT_ERR;
  }

  if (tvec->type != Int) {
    fprintf(
        stderr,
        "tvector_append: types of `TypedVector` and `value` do not match\n");
    return T_VEC_TYPE_ERR;
  }

  return vector_push(&tvec->vec, new_val);
}

int tvector_push_long(TypedVector *tvec, long *new_val) {
  if (!tvec) {
    fprintf(stderr, "tvector_append: `tvec` can't be NULL.\n");
    return VEC_INPUT_ERR;
  }

  if (tvec->type != Long) {
    fprintf(
        stderr,
        "tvector_append: types of `TypedVector` and `value` do not match\n");
    return T_VEC_TYPE_ERR;
  }

  return vector_push(&tvec->vec, new_val);
}

int tvector_push_size_t(TypedVector *tvec, size_t *new_val) {
  if (!tvec) {
    fprintf(stderr, "tvector_append: `tvec` can't be NULL.\n");
    return VEC_INPUT_ERR;
  }

  if (tvec->type != SizeT) {
    fprintf(
        stderr,
        "tvector_append: types of `TypedVector` and `value` do not match\n");
    return T_VEC_TYPE_ERR;
  }

  return vector_push(&tvec->vec, new_val);
}

int tvector_push_float(TypedVector *tvec, float *new_val) {
  if (!tvec) {
    fprintf(stderr, "tvector_append: `tvec` can't be NULL.\n");
    return VEC_INPUT_ERR;
  }

  if (tvec->type != Float) {
    fprintf(
        stderr,
        "tvector_append: types of `TypedVector` and `value` do not match\n");
    return T_VEC_TYPE_ERR;
  }

  return vector_push(&tvec->vec, new_val);
}

int tvector_push_double(TypedVector *tvec, double *new_val) {
  if (!tvec) {
    fprintf(stderr, "tvector_append: `tvec` can't be NULL.\n");
    return VEC_INPUT_ERR;
  }

  if (tvec->type != Double) {
    fprintf(
        stderr,
        "tvector_append: types of `TypedVector` and `value` do not match\n");
    return T_VEC_TYPE_ERR;
  }

  return vector_push(&tvec->vec, new_val);
}

int tvector_push_long_double(TypedVector *tvec,
                                           long double *new_val) {
  if (!tvec) {
    fprintf(stderr, "tvector_append: `tvec` can't be NULL.\n");
    return VEC_INPUT_ERR;
  }

  if (tvec->type != LongDouble) {
    fprintf(
        stderr,
        "tvector_append: types of `TypedVector` and `value` do not match\n");
    return T_VEC_TYPE_ERR;
  }

  return vector_push(&tvec->vec, new_val);
}

int tvector_push_string(TypedVector *tvec, char **new_val) {
  if (!tvec) {
    fprintf(stderr, "tvector_append: `tvec` can't be NULL.\n");
    return VEC_INPUT_ERR;
  }

  if (tvec->type != String) {
    fprintf(
        stderr,
        "tvector_append: types of `TypedVector` and `value` do not match\n");
    return T_VEC_TYPE_ERR;
  }

  char *new_str_val = (char *)malloc(strlen(*new_val) + 1);
  if (!new_str_val) {
    perror("tvector_append: strdup failed");
    return VEC_MEM_ERR;
  }
  strcpy(new_str_val, *new_val);

  return vector_push(&tvec->vec, &new_val);
}
