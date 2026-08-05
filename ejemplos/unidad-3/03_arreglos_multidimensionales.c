/*
 * 03_arreglos_multidimensionales.c
 * Unidad 3.A — matrices (arreglos de 2 dimensiones).
 */
#include <stdio.h>

int main(void) {
    int tablero[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    printf("Matriz completa:\n");
    for (int fila = 0; fila < 3; fila++) {
        for (int columna = 0; columna < 3; columna++) {
            printf("%d ", tablero[fila][columna]);
        }
        printf("\n");
    }

    // suma de la diagonal principal
    int suma_diagonal = 0;
    for (int i = 0; i < 3; i++) {
        suma_diagonal += tablero[i][i];
    }
    printf("Suma de la diagonal principal: %d\n", suma_diagonal);

    return 0;
}
