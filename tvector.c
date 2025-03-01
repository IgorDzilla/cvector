#include "tvector.h"
#include "vector.h"

#include <stdio.h>
#include <string.h>

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

// tvector_push functions: BEGIN
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

int tvector_push_long_double(TypedVector *tvec, long double *new_val) {
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

  char *val = (char *)malloc(strlen(*new_val) + 1);
  if (!val) {
    perror("tvector_append: strdup failed");
    return VEC_MEM_ERR;
  }
  strcpy(val, *new_val);

  return vector_push(&tvec->vec, val);
}
// tvector_push functions: END

// tvector_push_fw functions: BEGIN
int tvector_push_fw_int(TypedVector *tvec, int *new_val) {
  if (!tvec) {
    fprintf(stderr, "tvector_push_fw: `tvec` can't be NULL.\n");
    return VEC_INPUT_ERR;
  }

  if (tvec->type != Int) {
    fprintf(
        stderr,
        "tvector_append: types of `TypedVector` and `value` do not match\n");
    return T_VEC_TYPE_ERR;
  }

  return vector_push_fw(&tvec->vec, new_val);
}

int tvector_push_fw_long(TypedVector *tvec, long *new_val) {
  if (!tvec) {
    fprintf(stderr, "tvector_push_fw: `tvec` can't be NULL.\n");
    return VEC_INPUT_ERR;
  }

  if (tvec->type != Long) {
    fprintf(
        stderr,
        "tvector_append: types of `TypedVector` and `value` do not match\n");
    return T_VEC_TYPE_ERR;
  }

  return vector_push_fw(&tvec->vec, new_val);
}

int tvector_push_fw_size_t(TypedVector *tvec, size_t *new_val) {
  if (!tvec) {
    fprintf(stderr, "tvector_push_fw: `tvec` can't be NULL.\n");
    return VEC_INPUT_ERR;
  }

  if (tvec->type != SizeT) {
    fprintf(stderr, "tvector_push_fw: types of `TypedVector` and `new_value` "
                    "do not match.\n");
    return T_VEC_TYPE_ERR;
  }

  return vector_push_fw(&tvec->vec, new_val);
}

int tvector_push_fw_float(TypedVector *tvec, float *new_val) {
  if (!tvec) {
    fprintf(stderr, "tvector_push_fw: `tvec` can't be NULL.\n");
    return VEC_INPUT_ERR;
  }

  if (tvec->type != Float) {
    fprintf(stderr, "tvector_push_fw: types of `TypedVector` and `new_value` "
                    "do not match.\n");
    return T_VEC_TYPE_ERR;
  }

  return vector_push_fw(&tvec->vec, new_val);
}

int tvector_push_fw_double(TypedVector *tvec, double *new_val) {
  if (!tvec) {
    fprintf(stderr, "tvector_push_fw: `tvec` can't be NULL.\n");
    return VEC_INPUT_ERR;
  }

  if (tvec->type != Double) {
    fprintf(stderr, "tvector_push_fw : types of `TypedVector` and `new_value` "
                    "do not match.\n");
    return T_VEC_TYPE_ERR;
  }

  return vector_push_fw(&tvec->vec, new_val);
}

int tvector_push_fw_long_double(TypedVector *tvec, long double *new_val) {
  if (!tvec) {
    fprintf(stderr, "tvector_push_fwtvector_push_fw => long double: `tvec` can't be NULL.\n");
    return VEC_INPUT_ERR;
  }

  if (tvec->type != LongDouble) {
    fprintf(stderr, "tvector_push_fw => long double: types of `TypedVector` and `new_value` "
                    "do not match.\n");
    return T_VEC_TYPE_ERR;
  }

  return vector_push_fw(&tvec->vec, new_val);
}

int tvector_push_fw_string(TypedVector *tvec, char **new_val) {
  if (!tvec) {
    fprintf(stderr, "tvector_push_fw => string: `tvec` can't be NULL.\n");
    return VEC_INPUT_ERR;
  }

  if (tvec->type != String) {
    fprintf(stderr, "tvector_push_fw => string: types of `TypedVector` and `new_value` "
                    "do not match.\n");
    return T_VEC_TYPE_ERR;
  }

  char *val = (char *)malloc(strlen(*new_val) + 1);
  if (!val) {
    perror("tvector_push => string: string: memory allocation failed.");
    return VEC_MEM_ERR;
  }
  strcpy(val, *new_val);

  return vector_push_fw(&tvec->vec, val);
}
// TVECTOR_PUSH_FW FUNCTIONS: END

// TVECTOR_GET FUNCTIONS: BEGIN
int tvector_get_int(TypedVector *tvec, size_t index, int *val) {
  if (tvec->type != Int) {
    fprintf(
        stderr,
        "tvector_get => int: types of `TypedVector` and `val` do not match.\n");
    return T_VEC_TYPE_ERR;
  }

  return vector_get(&tvec->vec, index, val);
}

int tvector_get_long(TypedVector *tvec, size_t index, long *val) {
  if (tvec->type != Long) {
    fprintf(
        stderr,
        "tvector_get => long: types of `TypedVector` and `val` do not match.\n");
    return T_VEC_TYPE_ERR;
  }

  return vector_get(&tvec->vec, index, val);
}

int tvector_get_size_t(TypedVector *tvec, size_t index, size_t *val) {
  if (tvec->type != SizeT) {
    fprintf(
        stderr,
        "tvector_get => size_t: types of `TypedVector` and `val` do not match.\n");
    return T_VEC_TYPE_ERR;
  }

  return vector_get(&tvec->vec, index, val);
}

int tvector_get_float(TypedVector *tvec, size_t index, float *val) {
  if (tvec->type != Float) {
    fprintf(
        stderr,
        "tvector_get => float: types of `TypedVector` and `val` do not match.\n");
    return T_VEC_TYPE_ERR;
  }

  return vector_get(&tvec->vec, index, val);
}

int tvector_get_double(TypedVector *tvec, size_t index, double *val) {
  if (tvec->type != Double) {
    fprintf(
        stderr,
        "tvector_get => double: types of `TypedVector` and `val` do not match.\n");
    return T_VEC_TYPE_ERR;
  }

  return vector_get(&tvec->vec, index, val);
}

int tvector_get_long_double(TypedVector *tvec, size_t index, long double *val) {
  if (tvec->type != LongDouble) {
    fprintf(
        stderr,
        "tvector_get => long double: types of `TypedVector` and `val` do not match.\n");
    return T_VEC_TYPE_ERR;
  }

  return vector_get(&tvec->vec, index, val);
}

int tvector_get_string(TypedVector *tvec, size_t index, char **val) {
  if (tvec->type != String) {
    fprintf(
        stderr,
        "tvector_get_int => string: types of `TypedVector` and `val` do not match.\n");
    return T_VEC_TYPE_ERR;
  }

  return vector_get(&tvec->vec, index, val);
}
// TVECTOR_GET FUNCTIONS: END
