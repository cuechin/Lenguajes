#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
#include "arreglo.h"

/*Funcion que inicializa el arreglo*/


void initArray(Array *a, size_t initialSize) 
{

  a->array = (char *)malloc(initialSize * sizeof(unsigned char));

  a->used = 0;

  a->size = initialSize;

  a->used_without_255 = 0;
}

/*Funcion que inserta un valor en el arreglo*/


void insertArray(Array *a, char element) 
{
  
  if (a->used == a->size) {

    a->size *= 2;

    a->array = (char *)realloc(a->array, a->size * sizeof(unsigned char));
  }
  a->array[a->used++] = element;
}

/*Funcion que se dedidca a buscar un elemento del arreglo*/


int searchArray(Array *a, char element)
{

  for (int i = 0; i <= a->used; i++){

    if (a->array[i] == element){

      return 1;

    } 

  }

  return 0;

}

/*Funcion que borra todo el arreglo*/


void freeArray(Array *a)
{

  free(a->array);

  a->array = NULL;

  a->used = a->size = 0;

}

/*Funcion que devuelve el tama;o del arreglo en int*/


int tamano_array(Array *a)
{

  char cnt = 0;
  int i = 0;
  int len;
  size_t usedd = a->used;

  for (i; i <= a->used; i++){

    if ( a->array[i] == 254 ){

      cnt++;
    }
  }

  len = usedd - cnt;

  return len;

}

/*Funcion que elimina una posicion especifica del arreglo*/


void eliminar_pos_Array(char pos, Array *a)

{

  int i = 0;
  int bandera;

  //printf("%lu\n", a->used);

  while ( i <= tamano_array(a)){

    if( pos == a->array[i]){

      /*bandera = a->array[i];
      a->array[i] = a->array[a->used - 1];
      a->array[a->used - 1] = bandera;

      a->used--;*/

      a->array[i] = 254; 

      //a->size--;

    } else{

      ;

    }

    i++;

  }

}

/*Funcion que imprime el arreglo*/


void printArray(Array *a){

  for (int i = 0; i <= tamano_array(a); i++){

    printf("Posiciones ocupadas: %3d\n", a->array[i]);

  }
}