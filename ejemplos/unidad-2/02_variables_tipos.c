/*
 * 02_variables_tipos.c
 * Unidad 2.C — tipos de datos primitivos y sizeof.
 */
#include <stdio.h>
#include <stdbool.h>

int main(void) {
    char letra = 'A';
    int edad = 21;
    short pequenio = 100;
    long grande = 10000000000L;
    float precio = 19.99f;
    double pi = 3.14159265358979;
    bool aprobado = true;      // requiere <stdbool.h>

    printf("char   : valor=%c  tamanio=%zu bytes\n", letra, sizeof(letra));
    printf("int    : valor=%d  tamanio=%zu bytes\n", edad, sizeof(edad));
    printf("short  : valor=%hd tamanio=%zu bytes\n", pequenio, sizeof(pequenio));
    printf("long   : valor=%ld tamanio=%zu bytes\n", grande, sizeof(grande));
    printf("float  : valor=%f  tamanio=%zu bytes\n", precio, sizeof(precio));
    printf("double : valor=%lf tamanio=%zu bytes\n", pi, sizeof(pi));
    printf("bool   : valor=%d  tamanio=%zu bytes\n", aprobado, sizeof(aprobado));

    return 0;
}
