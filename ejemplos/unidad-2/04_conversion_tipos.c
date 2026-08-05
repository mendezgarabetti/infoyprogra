/*
 * 04_conversion_tipos.c
 * Unidad 2.C — conversiones de tipo implícitas y explícitas (casting).
 */
#include <stdio.h>

int main(void) {
    int a = 7, b = 2;

    printf("Division entera sin cast: %d / %d = %d\n", a, b, a / b);
    printf("Division con cast a double: (double)%d / %d = %f\n",
           a, b, (double)a / b);

    double d = 3.99;
    int truncado = (int)d; // casting explícito: trunca, no redondea
    printf("\n(int)3.99 = %d  (trunca, no redondea)\n", truncado);

    int grande = 300;
    signed char chico = (signed char)grande; // signed char: -128 a 127
    printf("\n(signed char)300 = %d  (overflow: se \"da la vuelta\")\n", chico);

    int entero = 5;
    double promocionado = entero; // conversión implícita, segura
    printf("\nint %d convertido implicitamente a double: %f\n", entero, promocionado);

    return 0;
}
