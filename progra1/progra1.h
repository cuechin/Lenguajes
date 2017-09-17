#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "arreglo.h"
#ifndef PROGRA1_H
#define PROGRA1_H

/*Header de progra1.c*/


int obtener_valor(char pos_int, char* nombre_archivo, FILE *archivo);

char obtener_siguiente (char pos_int, char* nombre_archivo, FILE *archivo);

void escribir_valor(int pos_int, int valor, char* nombre_archivo, FILE *archivo);

void escribir_siguiente(int pos_int, char valor, char* nombre_archivo, FILE *archivo);

void escribir_archivo_binario(char* nombre_archivo, FILE *archivo);

void puntero_inicio(Array *a, char* nombre_archivo, FILE* archivo);

void insertar_nodo_final(int numero, Array *a, char* nombre_archivo, FILE* archivo);

void insertar_n_pos(int numero, unsigned char n_pos, Array *a, char* nombre_archivo, FILE* archivo);

void eliminar_ultimo(Array *a, char* nombre_archivo, FILE* archivo);

void eliminar_n_pos(unsigned char n_pos, Array *a, char* nombre_archivo, FILE* archivo);

#endif