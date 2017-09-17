/**
 *
 * Tarea Programada 1: La lista enlazada simpática... ¡Tirando a chistosa!
 * Andrés Mora Miranda
 * 201341401
 * Lenguajes de programación
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "progra1.h"


/*  - Punteros apuntan a alguna area de memoria.
    - Puntero es un numero que se refiere a un area de memoria.
    - Archivo va a ser mi area de memoria.
    - Los numeros que son los punteros se van a referir a un byte dentro del archivo donde va a estar.
    - Crear los 256 bytes del archivo desde el inicio.
    - El ultimo byte es el que tiene el puntero a inicio (sobra byte, entonces puntero a inicio).
    - Empezar con el fseek (funcion para moverme) agarro el numero del puntero lo pongo en fseek.
    - fread y fwrite leen y escriben a partir de ese indicador.
    - .2 es el byte que sobra al final que vamos a usar para el apuntador a inicio, el puntero al principio de la lista.
    - Nodo 5 bytes, concepto abstracto de un elemento de la lista, un valor y una felcha a sig.
    - Registro == nodo pero en diferente contexto.
    - Escribir directamente en el archivo el entero y el puntero.
    - calloc, con el puntero se puede ir a ese espacio de memoria sacar el numero y el puntero a sig.
    - Sacar el entero -> moverse a la posicion del archivo, copiar los 4 bytes e imprimir el entero
    - Sacar el puntero -> moverse al principio los 4 bytes del entero leo el byte del apuntador y uso ese apuntador.
    - 

    ___________________________________________________________________________________________________

    - calloc(numero de elementos, tama;o de esos elementos);
    - fwrite(void *puntero, size_t tamano, size_t cantidad, FILE *archivo); 
    // puntero a la zona de memoria de donde se obtendrán los datos a escribir, 
    el tamaño de cada registro, el número de registros a escribir 
    y un puntero a la estructura FILE del fichero al que se hará la escritura
    - int fseek(FILE *stream, long int desplazamiento, int origen);
    - long int ftell(FILE *stream); retorna el valor del indicador de posición de fichero para el stream, si se tiene éxito
*/

/*Funcion que retorna el valor del nodo actual*/

int obtener_valor(char pos_int, char* nombre_archivo, FILE *archivo) {

    int valor;

    archivo = fopen(nombre_archivo, "rb");

    fseek(archivo, pos_int, SEEK_SET);

    fread(&valor, sizeof(int), 1, archivo);

    fclose(archivo);

    return valor;

}

/*Funcion que retorna el valor de la direccion del nodo actual*/

char obtener_siguiente (char pos_int, char* nombre_archivo, FILE *archivo)
{

    int numero;

    char puntero;

    archivo = fopen(nombre_archivo, "rb");

    fseek(archivo, pos_int, SEEK_SET);

    fread(&numero, sizeof(int), 1, archivo);

    fread(&puntero, sizeof(unsigned char), 1, archivo);

    fclose(archivo);

    return puntero;

}

/*Funcion que escribe un numero en la posicion dada*/

void escribir_valor(int pos_int, int valor, char* nombre_archivo, FILE *archivo)
{

    int numero = valor;

    archivo = fopen(nombre_archivo,"rb+");

    fseek(archivo, pos_int, SEEK_SET);

    fwrite(&numero, sizeof(int), 1, archivo);

    fclose(archivo);

}

/*Funcion que escribe un puntero en la posicion dada*/

void escribir_siguiente(int pos_int, char valor, char* nombre_archivo, FILE *archivo)
{

    
    char numero = valor;

    archivo = fopen(nombre_archivo,"rb+");

    fseek(archivo, pos_int + 4, SEEK_SET);

    fwrite(&numero, sizeof(unsigned char), 1, archivo);

    fclose(archivo);

}

/*Funcion que crea el archivo y lo inicializa con 255 bytes en valores de 0, debido a calloc*/

void escribir_archivo_binario(char* nombre_archivo, FILE *archivo)
{

    archivo = fopen(nombre_archivo, "wb");

    unsigned char* buffer = calloc(256, sizeof(unsigned char));

    fwrite(buffer, sizeof(unsigned char), 256, archivo);

    fflush(archivo);

    fclose(archivo);

    free(buffer);

};

/*Funcion que apunta el puntero del byte 256 al inicio de la lista*/

void puntero_inicio(Array *a, char* nombre_archivo, FILE* archivo)
{

    archivo = fopen(nombre_archivo, "rb+");

    unsigned char ultimo_puntero = 0;

    fseek(archivo, 0, SEEK_SET);

    ultimo_puntero = ftell(archivo);

    fseek(archivo, 255, SEEK_SET);

    fwrite(&ultimo_puntero, sizeof(unsigned char), 1, archivo);

    fflush(archivo);

    fclose(archivo);
 
}

/*Funcion que escribe un nodo en la posicion final de la lista*/

void insertar_nodo_final(int numero, Array *a, char* nombre_archivo, FILE* archivo)    // Se inserta un nuevo elemento al final de la lista.
{
    
    archivo = fopen(nombre_archivo, "rb+");

    unsigned char final = 255;

    unsigned char actual = 0;

    if (tamano_array(a) != 0){

        while (searchArray(a, actual)) {

        actual = actual + 5;

        }

        unsigned char pasado = a->array[tamano_array(a) -1];

        fseek(archivo, pasado + 4, SEEK_SET);

        fwrite(&actual, sizeof(unsigned char), 1, archivo);

        fseek(archivo, actual, SEEK_SET);

        fwrite(&actual, sizeof(unsigned char), 1, archivo);

        fseek(archivo, actual + 1, SEEK_SET);

        fwrite(&numero, sizeof(unsigned int), 1, archivo);
    
    }


    fseek(archivo, actual, SEEK_SET);
    
    fwrite(&numero, sizeof(unsigned int), 1, archivo);

    fwrite(&final, sizeof(unsigned char), 1, archivo);

    insertArray(a, actual);

    fflush(archivo);

    fclose(archivo);

    
};

/*Funcion que escribe un nodo en la posicion dada*/


void insertar_n_pos(int numero, unsigned char n_pos, Array *a, char* nombre_archivo, FILE* archivo)    // Se inserta en una posición específica de la lista (no del archivo).
{

    archivo = fopen(nombre_archivo, "rb+");

    unsigned char final = 255;

    unsigned char puntero_anterior;

    unsigned char nuevo_puntero;


    if (tamano_array(a) != 0 && searchArray(a, n_pos) != 1){

        escribir_valor(n_pos, numero, nombre_archivo, archivo);

        fseek(archivo, n_pos - 1, SEEK_SET);

        //ftelll = ftell(archivo);

        //printf("%d\n", n_pos - 1);

        //printf("%d\n", ftelll);

        puntero_anterior = fread(&puntero_anterior, sizeof(unsigned char), 1, archivo);

        //printf("%d\n", puntero_anterior);

        //fseek(archivo, n_pos, SEEK_SET);

        escribir_siguiente(n_pos, puntero_anterior, nombre_archivo, archivo);

        fseek(archivo, n_pos, SEEK_SET);
        nuevo_puntero = ftell(archivo);
        fseek(archivo, n_pos -1, SEEK_SET);
        fwrite(&nuevo_puntero,sizeof(unsigned char), 1, archivo);


    } else{

        exit(1);
    }


}

/*Funcion que elimina un nodo en la posicion final de la lista*/


void eliminar_ultimo(Array *a, char* nombre_archivo, FILE* archivo)   // Se elimina el último elemento de la lista
{

    archivo = fopen(nombre_archivo, "rb+");

    unsigned char act = 0;

    unsigned char pos_actual;

    unsigned char pos_int_anterior;

    unsigned char pos_puntero_anterior;

    unsigned char char_borrador = 0;

    int int_borrador = 0;


    if (tamano_array(a) == 0){

        exit(1);

    } else{

        while (act != 255){

            fread(&act, sizeof(unsigned char), 1, archivo);

        };

        pos_actual = ftell(archivo) - 1;

        pos_int_anterior = ftell(archivo) - 5;

        pos_puntero_anterior = ftell(archivo) - 6;

        if (pos_int_anterior == 0){

            fseek(archivo, pos_actual, SEEK_SET);

            fwrite(&char_borrador, sizeof(unsigned char), 1, archivo);

            fseek(archivo, pos_int_anterior, SEEK_SET);

            fwrite(&int_borrador, sizeof(int), 1, archivo);

            eliminar_pos_Array(pos_int_anterior, a);


        } else{

            fseek(archivo, pos_actual, SEEK_SET);

            fwrite(&char_borrador, sizeof(unsigned char), 1, archivo);

            fseek(archivo, pos_int_anterior, SEEK_SET);

            fwrite(&int_borrador, sizeof(int), 1, archivo);

            fseek(archivo, pos_puntero_anterior, SEEK_SET);

            fwrite(&act, sizeof(unsigned char), 1, archivo);

            eliminar_pos_Array(pos_int_anterior, a);

        }

        
    }

    fflush(archivo);

    fclose(archivo);


};

/*Funcion que escribe un nodo en la posicion dada*/


void eliminar_n_pos(unsigned char n_pos, Array *a, char* nombre_archivo, FILE* archivo)    // Se elimina el elemento en la posición indicada de la lista (no del archivo).
{

    archivo = fopen(nombre_archivo, "rb+");

    unsigned char puntero_n_pos = 0;

    if (searchArray(a,n_pos) == 1){

        puntero_n_pos = obtener_siguiente(n_pos, nombre_archivo, archivo);

        escribir_valor(n_pos, 0, nombre_archivo, archivo);

        escribir_siguiente(n_pos, 0, nombre_archivo, archivo);

        fseek(archivo, n_pos - 1, SEEK_SET);

        fwrite(&puntero_n_pos, sizeof(unsigned char), 1, archivo);

        eliminar_pos_Array(n_pos, a);

    } else {

        exit(1);

        fflush(archivo);

        fclose(archivo);
    }


};
    

int main ()
{

    FILE *archivo;

    char* nombre_archivo = "progra";

    Array a;

    initArray(&a, 256);

    escribir_archivo_binario(nombre_archivo, archivo);

    puntero_inicio(&a, nombre_archivo, archivo);

    insertar_nodo_final(1, &a, nombre_archivo, archivo);

    insertar_nodo_final(2, &a, nombre_archivo, archivo);

    insertar_nodo_final(3, &a, nombre_archivo, archivo);

    insertar_nodo_final(4, &a, nombre_archivo, archivo);

    eliminar_n_pos(10, &a, nombre_archivo, archivo);

    insertar_n_pos(5, 10, &a, nombre_archivo, archivo);

    //printf("%d\n", tamano_array(&a));

    //printArray(&a);
    
};