#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
#ifndef ARREGLO_H
#define ARREGLO_H

/*Header de arreglo.c*/


typedef struct {

  unsigned char* array;

  size_t used;

  size_t size;

  size_t used_without_255;

} Array;

void initArray(Array *a, size_t initialSize);

void insertArray(Array *a, char element) ;

int searchArray(Array *a, char element);

void eliminar_pos_Array(char pos, Array *a);

void freeArray(Array *a);

void printArray(Array *a);

int tamano_array(Array *a);

#endif

