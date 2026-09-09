/*
 * 05_punteros_basicos.c
 * Unidad 3.B — paso por valor vs. paso por referencia con & y *.
 */
#include <stdio.h>

void no_duplica(int v) {
    v = v * 2; // solo cambia la copia local
}

void duplicar(int *v) {
    *v = *v * 2; // *v = "el valor en la direccion v"
}

int main(void) {
    int x = 5;

    no_duplica(x);
    printf("Despues de no_duplica: x = %d (no cambio)\n", x);

    duplicar(&x); // &x = "la direccion de x"
    printf("Despues de duplicar:   x = %d (SI cambio)\n", x);

    return 0;
}
