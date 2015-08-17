#include <stdio.h>
#include <stdlib.h>
#include "cson_parser.h"

int main(void) {
  cson_object_t *json = cson_parse_filename("test.json");
  if (cson_is_hash(json)) {
    hash *hsh = json->data;
    cson_object_t *id = get(hsh, "id");
    if (cson_is_string(id)) {
      char *id_str = id->data;
      puts(id_str);
    } else {
      puts("Wrong");
    }
    cson_object_t *actor = get(hsh, "actor");
    if (cson_is_hash(actor)) {
      cson_object_t *links = cson_get_key(actor, "links");
      if (cson_is_array(links)) {
        cson_object_t *elem = cson_get_element(links, 0);
        if (cson_is_hash(elem)) {
          cson_object_t *rel = cson_get_key(elem, "rel");
          if (cson_is_string(rel)) {
            char *rel_str = cson_get_string(rel);
            puts(rel_str);
          } else {
            puts("Wrong");
          }
        } else {
          puts("Wrong");
        }
      } else {
        puts("Wrong");
      }
    } else {
      puts("Wrong");
    }
  } else {
    puts("Wrong");
  }
  puts("Hello world!");
}
