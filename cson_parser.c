/*----- System Includes -----*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>

/*----- Local Includes -----*/

#include "definitions.h"
#include "array.h"
#include "hash.h"
#include "cson_parser.h"

/*----- Macro Function Declarations -----*/

#define ADVANCE() token = retrieve(tokens, (*index)++)

#define HASH_ENFORCE_TOKEN(target) \
  if (*token != target) { \
    destroy_hash(data); \
    return NULL; \
  }

#define ARRAY_ENFORCE_TOKEN(target) \
  if (*token != target) { \
    destroy_array(data, free); \
    return NULL; \
  }


/*----- Internal Parsing Function Stub Declarations -----*/

array *tokenize(char *json);
cson_object_t *literal_switch(array *tokens, int *index);

cson_object_t *parse_hash(array *tokens, int *index);
cson_object_t *parse_array(array *tokens, int *index);
cson_object_t *parse_string(array *tokens, int *index);
cson_object_t *parse_bool(array *tokens, int *index);
cson_object_t *parse_double(array *tokens, int *index);
cson_object_t *parse_int(array *tokens, int *index);

/*----- Public Parsing Function Implementations -----*/

cson_object_t *cson_parse_string(char *json) {
  array *tokens = tokenize(json);
  int index = 0;
  cson_object_t *parsed = literal_switch(tokens, &index);

  return NULL;
}

cson_object_t *cson_parse_file(FILE *json_file) {
  int size = CSON_START_SIZE;
  char *json = malloc(sizeof(char) * size);
  if (json) {
    for (int i = 0; true; i++) {
      char c = getc(json_file);
      if (c == EOF) {
        json[i] = '\0';
        break;
      }
      json[i] = c;
      if (i == size - 1) {
        size *= 2;
        char *resized = realloc(json, size);
        if (!resized) return NULL;
        if (json != resized) free(json);
        json = resized;
      }
    }
    cson_object_t *result = cson_parse_string(json);
    free(json);
    return result;
  } else {
    return NULL;
  }
}

cson_object_t *cson_parse_filename(char *filename) {
  struct stat buf;
  stat(filename, &buf);

  if (S_ISREG(buf.st_mode)) {
    FILE *file = fopen(filename, "r");
    cson_object_t *result = cson_parse_file(file);
    fclose(file);
    return result;
  } else {
    return NULL;
  }
}

/*----- Internal Parsing Function Implementations -----*/

array *tokenize(char *json) {
  array *tokens = create_array();
  int length = strlen(json);

  for (int i = 0; i < length; i++) {
    char c = json[i], *tmp;
    if (isspace(c)) continue;

    if (c == '"') {
      tmp = malloc(sizeof(char) * 2);
      *tmp = c;
      *(tmp + 1) = '\0';
      push(tokens, tmp);
      i++;

      int diff;
      char prev = '\0';
      for (diff = 0; i + diff < length && (json[i + diff] != '"' || prev == '\\'); diff++) prev = json[i + diff];
      if (diff) {
        tmp = malloc(sizeof(char) * (diff + 1));
        memcpy(tmp, json + i, diff);
        *(tmp + diff + 1) = '\0';
        push(tokens, tmp);
      }

      i += diff;
      c = json[i];
      if (c != '"') {
        destroy_array(tokens, free);
        return NULL;
      }

      tmp = malloc(sizeof(char) * 2);
      *tmp = c;
      *(tmp + 1) = '\0';
      push(tokens, tmp);
    } else if (c >= '0' && c <= '9' || c == 't' || c == 'f' || c == 'n') {
      int diff;
      char start = c >= '0' && c <= '9' ? '0' : 'a', end = c >= '0' && c <= '9' ? '9' : 'z';
      for (diff = 0; diff < length && json[i + diff] >= start && json[i + diff] <= end; diff++);
      tmp = malloc(sizeof(char) * (diff + 2));
      memcpy(tmp, json + i, diff);
      *(tmp + diff + 1) = '\0';
      i += diff - 1;
      push(tokens, tmp);
    } else {
      tmp = malloc(sizeof(char) * 2);
      *tmp = c;
      *(tmp + 1) = '\0';
      push(tokens, tmp);
    }
  }

  return tokens;
}

cson_object_t *literal_switch(array *tokens, int *index) {
  char *token = retrieve(tokens, (*index)++);
  switch (*token) {
    case '{':
      return parse_hash(tokens, index);
    case '[':
      return parse_array(tokens, index);
    case '"':
      return parse_string(tokens, index);
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
      return parse_int(tokens, index);
    case 't':
    case 'f':
      return parse_bool(tokens, index);
    case 'n':
      return parse_hash(tokens, index);
    default:
      return NULL;
  }
}


cson_object_t *parse_hash(array *tokens, int *index) {
  hash *data = create_hash(free);
  cson_object_t *new_obj = create_cson_hash(data);

  for (char *token = retrieve(tokens, (*index)++); *token != '}'; token = retrieve(tokens, (*index)++)) {
    HASH_ENFORCE_TOKEN('"');
    ADVANCE();

    char *key = token;
    ADVANCE();

    HASH_ENFORCE_TOKEN('"');
    ADVANCE();
    HASH_ENFORCE_TOKEN(':');
    ADVANCE();

    put(data, key, literal_switch(tokens, index));
    HASH_ENFORCE_TOKEN(',');
  }

  return new_obj;
}

cson_object_t *parse_array(array *tokens, int *index) {
  array *data = create_array();
  cson_object_t *new_obj = create_cson_array(data);

  for (char *token = retrieve(tokens, (*index)++); *token != ']'; token = retrieve(tokens, (*index)++)) {
    push(data, literal_switch(tokens, index));
    ARRAY_ENFORCE_TOKEN(',');
  }

  return new_obj;
}

cson_object_t *parse_string(array *tokens, int *index) {
  char *str = retrieve(tokens, (*index)++);
  char *copy = malloc(sizeof(char) * (strlen(str) + 1));
  strcpy(copy, str);

  cson_object_t *new_obj = create_cson_string(copy);
  return new_obj;
}

cson_object_t *parse_bool(array *tokens, int *index) {
  bool *boolean = retrieve(tokens, (*index)++);
  cson_object_t *new_obj = create_cson_bool(*boolean);
  return new_obj;
}

cson_object_t *parse_double(array *tokens, int *index) {
  double *decimal = retrieve(tokens, (*index)++);
  cson_object_t *new_obj = create_cson_double(*decimal);
  return new_obj;
}

cson_object_t *parse_int(array *tokens, int *index) {
  int *integer = retrieve(tokens, (*index)++);
  cson_object_t *new_obj = create_cson_int(*integer);
  return new_obj;
}
