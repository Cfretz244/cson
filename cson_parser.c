#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include "definitions.h"
#include "array.h"
#include "cson_parser.h"

/*----- Internal Parsing Function Stub Declarations -----*/

array *tokenize(char *json);

cson_object_t *parse_object(char *json);
cson_object_t *parse_array(char *json);
cson_object_t *parse_string(char *json);
cson_object_t *parse_bool(char *json);
cson_object_t *parse_double(char *json);
cson_object_t *parse_int(char *json);

/*----- Public Parsing Function Implementations -----*/

cson_object_t *cson_parse_string(char *json) {
  array *tokens = tokenize(json);

  return NULL;
}

cson_object_t *cson_parse_file(FILE *json_file) {
  int size = CSON_START_SIZE;
  char *json = malloc(sizeof(char) * size);
  if (json) {
    for (int i = 0; true; i++) {
      char c = getchar();
      if (c == EOF) {
        json[i] = '\0';
        break;
      }
      json[i] = c;
      if (i == size - 1) {
        size *= 2;
        char *resized = realloc(json, size);
        if (!resized) return NULL;
        free(json);
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

array *tokenize(char *json) {
  array *tokens = create_array();
  int length = strlen(json);

  for (int i = 0; i < length; i++) {
    char c = json[i];
    if (isspace(c)) continue;

    if (c == '"') {
      char *tmp = malloc(sizeof(char) * 2);
      *tmp = c;
      *(tmp + 1) = '\0';
      push(tokens, tmp);

      int diff;
      for (diff = 1; i + diff < length && json[i + diff] != '"'; diff++);
      if (diff > 1) {
        tmp = malloc(sizeof(char) * diff);
        memcpy(tmp, json + i, diff - 1);
        *(tmp + diff) = '\0';
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
    } else {
      char *tmp = malloc(sizeof(char) * 2);
      *tmp = c;
      *(tmp + 1) = '\0';
      push(tokens, tmp);
    }
  }
}
