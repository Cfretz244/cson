#include <stdio.h>
#include <stdlib.h>
#include "cson_parser.h"

int main(void) {
  cson_object_t *json = cson_parse_filename("test.json");
  puts("Hello world!");
}
