/*
 * 10_alcance_variables.c
 * Unidad 2.E — alcance (scope), vida y visibilidad de variables.
 */
#include <stdio.h>

int contador_global = 100; // alcance de archivo, vive durante todo el programa

void funcion_a(void) {
    int local_a = 1; // alcance de bloque: solo existe dentro de funcion_a
    printf("dentro de funcion_a: local_a=%d, contador_global=%d\n",
           local_a, contador_global);
    contador_global++; // las funciones pueden modificar globales (con cuidado, ver texto)
}

void funcion_b(void) {
    // printf("%d", local_a); // ERROR si se descomenta: local_a no existe acá
    for (int i = 0; i < 3; i++) {
        int local_b = i * 10; // alcance: solo dentro de este bloque del for
        printf("dentro del for de funcion_b: i=%d, local_b=%d\n", i, local_b);
    }
    // printf("%d", i); // ERROR si se descomenta: i no existe fuera del for
}

int main(void) {
    printf("contador_global antes: %d\n", contador_global);
    funcion_a();
    funcion_a();
    printf("contador_global despues de 2 llamadas: %d\n", contador_global);

    funcion_b();

    return 0;
}
