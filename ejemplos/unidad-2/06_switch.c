/*
 * 06_switch.c
 * Unidad 2.D — selector de caso (switch), incluyendo fall-through intencional.
 */
#include <stdio.h>

int main(void) {
    for (int dia = 1; dia <= 7; dia++) {
        printf("dia %d: ", dia);
        switch (dia) {
            case 1:
                printf("Lunes\n");
                break;
            case 2:
                printf("Martes\n");
                break;
            case 3:
                printf("Miercoles\n");
                break;
            case 4:
                printf("Jueves\n");
                break;
            case 5:
                printf("Viernes\n");
                break;
            case 6:
            case 7: // fall-through intencional: mismo cuerpo para sabado y domingo
                printf("Fin de semana\n");
                break;
            default:
                printf("Dia invalido\n");
                break;
        }
    }
    return 0;
}
