#ifndef CSON_PARSER
#define CSON_PARSER

/*----- Local Includes -----*/

#include "cson_obj.h"

/*----- Numerical Constants -----*/

#define CSON_START_SIZE 64

/*----- Parsing Functions -----*/

cson_object_t *cson_parse_string(char *json);
cson_object_t *cson_parse_file(FILE *json_file);
cson_object_t *cson_parse_filename(char *filename);

#endif
