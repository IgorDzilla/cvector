#include "tvector.h"

int main(void) {
  TypedVector type_vec;
  typed_vector_init(&type_vec, Int);

  for (int i = 0; i < 10; i++) {
    tvector_append(&type_vec, &i);
  }

  tvector_clear(&type_vec);

  return 0;
}
