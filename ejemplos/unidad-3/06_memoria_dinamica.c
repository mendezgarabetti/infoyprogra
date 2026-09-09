/*
 * 06_memoria_dinamica.c
 * Unidad 3.B — malloc/free, y modificar in-place vs. crear y devolver.
 */
#include <stdio.h>
#include <stdlib.h>

// "Crear y devolver": reserva memoria nueva y devuelve el puntero.
double *crear_vector(int n) {
    double *v = malloc(n * sizeof(double)); // ojo: sizeof del tipo correcto
    if (v == NULL) {
        fprintf(stderr, "No hay memoria disponible\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        v[i] = i * 1.5;
    }
    return v;
}

// "In-place": recibe un puntero y modifica ESA memoria, no crea otra.
void escalar(double *v, int n, double factor) {
    for (int i = 0; i < n; i++) {
        v[i] *= factor;
    }
}

void mostrar(const double *v, int n) {
    for (int i = 0; i < n; i++) {
        printf("%.2f ", v[i]);
    }
    printf("\n");
}

int main(void) {
    int n = 5;

    double *vector = crear_vector(n);
    printf("Vector original: ");
    mostrar(vector, n);

    escalar(vector, n, 2.0); // modifica "vector" en el lugar
    printf("Escalado x2:     ");
    mostrar(vector, n);

    free(vector); // quien reservo con malloc es responsable del free
    vector = NULL; // evita usarlo por error despues de liberado (dangling pointer)

    return 0;
}
