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

  for (int i = 0; i < tokens->count; i++) {
    char *token = retrieve(tokens, i);
    puts(token);

    switch (*token) {
      case '{':
        break;

      case '[':
        break;

      case '"':
        break;

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
        break;

      case 't':
      case 'f':
        break;

      case 'n':
        break;
      default:
        break;
    }
  }

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
