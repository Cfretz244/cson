#ifndef ARRAY_H
#define ARRAY_H

/*----- Local Includes -----*/

#include "definitions.h"

/*----- Numerical Constants -----*/

#define INIT_ARRAY_LENGTH 8

/*----- Struct Declarations -----*/

// Struct essentially behaves like an ArrayList.
typedef struct array {
    void **storage;
    int size, count;
} array;

/*----- Array Functions -----*/

array *create_array();
bool insert(array *arr, int index, void *data);
bool push(array *arr, void *data);
void *retrieve(array *arr, int index);
void *clear(array *arr, int index);
void destroy_array(array *arr, void (*destruct) (void *));

#endif
