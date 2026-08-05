/*
 * 01_arreglos.c
 * Unidad 3.A — arreglos (vectores): declaración, recorrido, suma/promedio.
 */
#include <stdio.h>

int main(void) {
    int notas[5] = {8, 6, 10, 7, 9};

    printf("Notas: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", notas[i]);
    }
    printf("\n");

    int suma = 0;
    for (int i = 0; i < 5; i++) {
        suma += notas[i];
    }
    double promedio = (double)suma / 5;
    printf("Promedio: %.2f\n", promedio);

    // tamanio del arreglo mientras sigue siendo un arreglo (no un puntero)
    int cantidad = sizeof(notas) / sizeof(notas[0]);
    printf("Cantidad de elementos: %d\n", cantidad);

    return 0;
}
