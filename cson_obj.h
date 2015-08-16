#ifndef CSON_OBJ
#define CSON_OBJ

/*----- Bitmasks -----*/

#define CSON_IS_INTEGER 0x01
#define CSON_IS_DOUBLE  0x02
#define CSON_IS_BOOL    0x04
#define CSON_IS_STRING  0x08
#define CSON_IS_ARRAY   0x10
#define CSON_IS_OBJECT  0x20

/*----- Struct Declarations -----*/

typedef struct {
  unsigned char type;
  void *data;
} cson_object_t;

/*----- Intermediate Retrieval Functions -----*/

cson_object_t *cson_get_element(cson_object_t *obj, int index);
cson_object_t *cson_get_key(cson_object_t *obj, char *key);

/*----- Value Retrieval Functions -----*/

int *cson_get_int(cson_object_t *obj);
double *cson_get_double(cson_object_t *obj);
bool *cson_get_bool(cson_object_t *obj);
char *cson_get_string(cson_object_t *obj);

/*----- Introspection Functions -----*/

bool cson_is_int(cson_object_t *obj);
bool cson_is_double(cson_object_t *obj);
bool cson_is_bool(cson_object_t *obj);
bool cson_is_string(cson_object_t *obj);
bool cson_is_array(cson_object_t *obj);
bool cson_is_hash(cson_object_t *obj);

#endif
