#include "vector.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int vector_init(Vector *vec, size_t val_size, void (*elem_destructor)(void *)) {
  if (!vec) {
    fprintf(stderr, "vector_init: `vec` can't be NULL\n");
    return VEC_INPUT_ERR;
  }

  if (val_size == 0) {
    fprintf(stderr, "vector_init: `val_size` can't be 0\n");
    return VEC_MEM_ERR;
  }

  vec->val_size = val_size;
  vec->length = 0;
  vec->data = NULL;
  vec->destructor = elem_destructor;

  return VEC_SUCCESS;
}

int vector_push(Vector *vec, void *new_val) {
  if (!vec) {
    fprintf(stderr, "vector_push: `vec` can't be NULL\n");
    return VEC_INPUT_ERR;
  }

  char *data_upd =
      (char *)realloc(vec->data, vec->val_size * (vec->length + 1));
  if (!data_upd) {
    perror("vector_push: memory reallocation failed\n");
    return VEC_MEM_ERR;
  }

  vec->data = data_upd;
  // copy the new data to vector, if it is not-NULL
  if (new_val) {
    memcpy(vec->data + vec->val_size * (vec->length), new_val, vec->val_size);
  } else {
    memset(vec->data + vec->val_size * (vec->length), 0, vec->val_size);
  }
  vec->length++;

  return VEC_SUCCESS;
}

int vector_push_fw(Vector *vec, void *new_val) {
  if (!vec) {
    fprintf(stderr, "vector_push_fw: `vec` can't be NULL\n");
    return VEC_INPUT_ERR;
  }

  return vector_insert(vec, 0, new_val);
}

int vector_insert(Vector *vec, size_t index, void *new_val) {
  if (!vec) {
    fprintf(stderr, "vector_insert: `vec` can't be NULL\n");
    return VEC_INPUT_ERR;
  }

  if (index > vec->length) {
    fprintf(stderr, "vector_insert: `index` is out of range\n");
    return VEC_RANGE_ERR;
  }

  char *data_upd =
      (char *)realloc(vec->data, (vec->length + 1) * (vec->val_size));
  if (!data_upd) {
    perror("vector_insert: memory reallocation failed");
    return VEC_MEM_ERR;
  }

  vec->data = data_upd;
  // shift elements
  memmove(vec->data + (index + 1) * vec->val_size,
          vec->data + index * vec->val_size,
          vec->val_size * (vec->length - index));
  if (new_val) {
    memcpy(vec->data + index * vec->val_size, new_val, vec->val_size);
  } else {
    memset(vec->data + index * vec->val_size, 0, vec->val_size);
  }
  vec->length++;

  return VEC_SUCCESS;
}

int vector_get(Vector *vec, size_t index, void *value) {
  if (index >= vec->length) {
    fprintf(stderr, "vector_get: `index` out of boundaries\n");
    return VEC_RANGE_ERR;
  }

  value = (void *)(vec->data + index * vec->val_size);
  return VEC_SUCCESS;
}

int vector_clear(Vector *vec) {
  if (!vec) {
    fprintf(stderr, "vector_clear: `vec` can't be NULL.\n");
    return VEC_INPUT_ERR;
  }

  if (vec->destructor) {
    for (size_t i = 0; i < vec->length; i++)
      free(vector_at(vec, i));
  }

  free(vec->data);
  vec->length = 0;

  return VEC_SUCCESS;
}

int vector_remove(Vector *vec, size_t index) {
  if (!vec) {
    fprintf(stderr, "vector_remove: `vec` can't be NULL.\n");
    return VEC_INPUT_ERR;
  }

  if (index >= vec->length) {
    fprintf(stderr, "vector_remove: `index` is out of range.\n");
    return VEC_RANGE_ERR;
  }

  if (vec->destructor) {
    vec->destructor(vec->data + vec->val_size * index);
  }

  if (index != vec->length - 1) {
    memmove(vec->data + vec->val_size * index,
            vec->data + vec->val_size * (index + 1),
            vec->val_size * (vec->length - index - 1));
  }

  if (vec->length == 1) {
    vec->data = NULL;
    vec->length = 0;
    return VEC_SUCCESS;
  }

  char *data_upd =
      (char *)realloc(vec->data, (vec->length - 1) * vec->val_size);
  if (!data_upd) {
    perror("vector_remove: memory reallocation failed");
    return VEC_MEM_ERR;
  }

  vec->data = data_upd;
  vec->length--;

  return VEC_SUCCESS;
}
