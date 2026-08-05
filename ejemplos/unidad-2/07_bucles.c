/*
 * 07_bucles.c
 * Unidad 2.D — while, for, do/while, break, continue, y bucles anidados.
 */
#include <stdio.h>

int main(void) {
    printf("--- while ---\n");
    int contador = 0;
    while (contador < 5) {
        printf("%d ", contador);
        contador++;
    }
    printf("\n");

    printf("--- for ---\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", i);
    }
    printf("\n");

    printf("--- do/while (se ejecuta al menos una vez) ---\n");
    int x = 100;
    do {
        printf("x vale %d (aunque la condicion ya era falsa)\n", x);
    } while (x < 10);

    printf("--- break y continue ---\n");
    for (int i = 0; i < 10; i++) {
        if (i == 5) break;        // corta el bucle al llegar a 5
        if (i % 2 == 0) continue; // se salta los pares
        printf("%d ", i);         // solo imprime: 1 3
    }
    printf("\n");

    printf("--- bucles anidados: tablero 3x3 ---\n");
    for (int fila = 0; fila < 3; fila++) {
        for (int columna = 0; columna < 3; columna++) {
            if (fila == columna) {
                printf("X ");
            } else {
                printf(". ");
            }
        }
        printf("\n");
    }

    return 0;
}
