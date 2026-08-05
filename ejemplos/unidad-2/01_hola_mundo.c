/*
 * 01_hola_mundo.c
 * Unidad 2.B — estructura mínima de un programa en C.
 *
 * Compilar y ejecutar:
 *   gcc -Wall -Wextra -std=c11 -o bin/01_hola_mundo ejemplos/unidad-2/01_hola_mundo.c
 *   ./bin/01_hola_mundo
 */
#include <stdio.h>

#define SALUDO "Hola, mundo"   // macro de preprocesador: sustitución de texto

int main(void) {
    printf("%s\n", SALUDO);

    int anio_curso = 2026;      // declaración + inicialización
    printf("Bienvenidos al curso de C, %d\n", anio_curso);

    return 0;                   // 0 = el programa terminó sin errores
}
