/*
 * 07_matrices_dinamicas.c
 * Unidad 3.B — matrices dinamicas (doble puntero), producto validado,
 * y transposicion in-place (solo directa si la matriz es cuadrada).
 */
#include <stdio.h>
#include <stdlib.h>

double **crear_matriz(int filas, int columnas) {
    double **m = malloc(filas * sizeof(double *));
    for (int i = 0; i < filas; i++) {
        m[i] = malloc(columnas * sizeof(double));
        for (int j = 0; j < columnas; j++) {
            m[i][j] = i * columnas + j; // valores de ejemplo, no aleatorios
        }
    }
    return m;
}

void liberar_matriz(double **m, int filas) {
    for (int i = 0; i < filas; i++) {
        free(m[i]); // primero cada fila...
    }
    free(m); // ...despues el arreglo de punteros
}

void mostrar_matriz(double **m, int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            printf("%5.1f ", m[i][j]);
        }
        printf("\n");
    }
}

// A: filasA x colsA,  B: colsA x colsB  ->  C: filasA x colsB
double **producto_matricial(double **a, int filasA, int colsA,
                             double **b, int filasB, int colsB) {
    if (colsA != filasB) {
        fprintf(stderr, "Dimensiones incompatibles: A es %dx%d, B es %dx%d\n",
                filasA, colsA, filasB, colsB);
        exit(1);
    }
    double **c = crear_matriz(filasA, colsB);
    for (int i = 0; i < filasA; i++) {
        for (int j = 0; j < colsB; j++) {
            c[i][j] = 0;
            for (int k = 0; k < colsA; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}

// Solo valido si "m" es cuadrada (n x n): intercambia m[i][j] con m[j][i].
void transponer_cuadrada_in_place(double **m, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double tmp = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = tmp;
        }
    }
}

int main(void) {
    double **a = crear_matriz(2, 3); // 2x3
    double **b = crear_matriz(3, 2); // 3x2

    printf("Matriz A (2x3):\n");
    mostrar_matriz(a, 2, 3);
    printf("Matriz B (3x2):\n");
    mostrar_matriz(b, 3, 2);

    double **c = producto_matricial(a, 2, 3, b, 3, 2); // resultado: 2x2
    printf("Producto A x B (2x2):\n");
    mostrar_matriz(c, 2, 2);

    transponer_cuadrada_in_place(c, 2); // C es cuadrada (2x2): esto SI es directo
    printf("C transpuesta in-place (2x2):\n");
    mostrar_matriz(c, 2, 2);

    liberar_matriz(a, 2);
    liberar_matriz(b, 3);
    liberar_matriz(c, 2);

    return 0;
}
