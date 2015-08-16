#include <stdlib.h>
#include "cson_obj.h"
#include "array.h"
#include "hash.h"

/*----- Intermediate Retrieval Implementations -----*/

cson_object_t *cson_get_element(cson_object_t *obj, int index) {
  return obj->type & CSON_IS_ARRAY ? retrieve(obj->data, index) : NULL;
}

cson_object_t *cson_get_key(cson_object_t *obj, char *key) {
  return obj->type & CSON_IS_OBJECT ? get(obj->data, key) : NULL;
}

/*----- Value Retrieval Implementations -----*/

int *cson_get_int(cson_object_t *obj) {
  return obj->type & CSON_IS_INTEGER ? obj->data : NULL;
}

double *cson_get_double(cson_object_t *obj) {
  return obj->type & CSON_IS_DOUBLE ? obj->data : NULL;
}

bool *cson_get_bool(cson_object_t *obj) {
  return obj->type & CSON_IS_BOOL ? obj->data : NULL;
}

char *cson_get_string(cson_object_t *obj) {
  return obj->type & CSON_IS_STRING ? obj->data : NULL;
}

/*----- Introspection Implementations -----*/

bool cson_is_int(cson_object_t *obj) {
  return obj->type & CSON_IS_INTEGER ? true : false;
}

bool cson_is_double(cson_object_t *obj) {
  return obj->type & CSON_IS_DOUBLE ? true : false;
}

bool cson_is_bool(cson_object_t *obj) {
  return obj->type & CSON_IS_BOOL ? true : false;
}

bool cson_is_string(cson_object_t *obj) {
  return obj->type & CSON_IS_STRING ? true : false;
}

bool cson_is_array(cson_object_t *obj) {
  return obj->type & CSON_IS_ARRAY ? true : false;
}

bool cson_is_hash(cson_object_t *obj) {
  return obj->type & CSON_IS_OBJECT ? true : false;
}
