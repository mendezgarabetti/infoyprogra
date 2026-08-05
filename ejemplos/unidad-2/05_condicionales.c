/*
 * 05_condicionales.c
 * Unidad 2.D — if / else / else if.
 */
#include <stdio.h>

int main(void) {
    int nota = 7;

    if (nota >= 9) {
        printf("Sobresaliente\n");
    } else if (nota >= 6) {
        printf("Aprobado\n");
    } else {
        printf("Desaprobado\n");
    }

    // C trata cualquier entero distinto de 0 como "verdadero"
    int bandera = -5;
    if (bandera) {
        printf("bandera (%d) se evalua como verdadero\n", bandera);
    }

    return 0;
}
