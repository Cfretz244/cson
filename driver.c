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
      hash *actor_hash = actor->data;
      cson_object_t *links = get(actor_hash, "links");
      if (cson_is_array(links)) {
        array *links_arr = links->data;
        cson_object_t *elem = retrieve(links_arr, 0);
        if (cson_is_hash(elem)) {
          hash *elem_hash = elem->data;
          cson_object_t *rel = get(elem_hash, "rel");
          if (cson_is_string(rel)) {
            char *rel_str = rel->data;
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
