#include <stdlib.h>
#include <string.h>
#include "cson_obj.h"
#include "array.h"
#include "hash.h"

/*----- Value Creation Implementations -----*/

cson_object_t *create_cson_int(int value) {
  cson_object_t *new_obj = malloc(sizeof(cson_object_t));
  new_obj->data = malloc(sizeof(int));
  new_obj->type |= CSON_IS_INTEGER;
  memcpy(new_obj->data, &value, sizeof(int));
  return new_obj;
}

cson_object_t *create_cson_double(double value) {
  cson_object_t *new_obj = malloc(sizeof(cson_object_t));
  new_obj->data = malloc(sizeof(double));
  new_obj->type |= CSON_IS_DOUBLE;
  memcpy(new_obj->data, &value, sizeof(double));
  return new_obj;
}

cson_object_t *create_cson_bool(bool value) {
  cson_object_t *new_obj = malloc(sizeof(cson_object_t));
  new_obj->data = malloc(sizeof(bool));
  new_obj->type |= CSON_IS_BOOL;
  memcpy(new_obj->data, &value, sizeof(bool));
  return new_obj;
}

cson_object_t *create_cson_string(char *value) {
  cson_object_t *new_obj = malloc(sizeof(cson_object_t));
  new_obj->data = value;
  new_obj->type |= CSON_IS_STRING;
  return new_obj;
}

cson_object_t *create_cson_array(array *value) {
  cson_object_t *new_obj = malloc(sizeof(cson_object_t));
  new_obj->data = value;
  new_obj->type |= CSON_IS_ARRAY;
  return new_obj;
}

cson_object_t *create_cson_hash(hash *value) {
  cson_object_t *new_obj = malloc(sizeof(cson_object_t));
  new_obj->data = value;
  new_obj->type |= CSON_IS_OBJECT;
  return new_obj;
}

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
