/*
 * 04_structs.c
 * Unidad 3.A — structs, typedef, y arreglo de structs.
 */
#include <stdio.h>
#include <string.h>

typedef struct {
    char nombre[50];
    int edad;
    double promedio;
} Estudiante;

void mostrar_estudiante(Estudiante e) { // se pasa por valor: se copia todo el struct
    printf("%-10s edad=%d promedio=%.1f\n", e.nombre, e.edad, e.promedio);
}

int main(void) {
    Estudiante alumno;
    strcpy(alumno.nombre, "Ana");
    alumno.edad = 20;
    alumno.promedio = 8.5;
    mostrar_estudiante(alumno);

    Estudiante curso[3] = {
        {"Ana",   20, 8.5},
        {"Luis",  22, 7.0},
        {"Maria", 19, 9.2}
    };

    printf("\nCurso completo:\n");
    for (int i = 0; i < 3; i++) {
        mostrar_estudiante(curso[i]);
    }

    return 0;
}
