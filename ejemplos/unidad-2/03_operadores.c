/*
 * 03_operadores.c
 * Unidad 2.C — operadores aritméticos, relacionales, lógicos y bit a bit.
 */
#include <stdio.h>

int main(void) {
    int a = 7, b = 2;

    printf("--- Aritméticos ---\n");
    printf("%d + %d = %d\n", a, b, a + b);
    printf("%d - %d = %d\n", a, b, a - b);
    printf("%d * %d = %d\n", a, b, a * b);
    printf("%d / %d = %d   (division ENTERA, se trunca)\n", a, b, a / b);
    printf("%d %% %d = %d  (modulo: resto de la division)\n", a, b, a % b);

    int x = 5;
    printf("\n--- Pre/post incremento (x=5) ---\n");
    // Ojo: leer y modificar 'x' en los mismos argumentos de un printf es
    // comportamiento indefinido (el orden de evaluación de argumentos no
    // está definido). Por eso separamos cada paso en su propia sentencia.
    int valor_devuelto = x++;           // x++ devuelve el valor ANTES de incrementar
    printf("x++ devuelve %d, luego x vale %d\n", valor_devuelto, x);
    valor_devuelto = ++x;               // ++x incrementa y luego devuelve el nuevo valor
    printf("++x devuelve %d, luego x vale %d\n", valor_devuelto, x);

    printf("\n--- Relacionales y logicos ---\n");
    printf("(%d > %d) = %d\n", a, b, a > b);
    printf("(%d == %d) = %d\n", a, b, a == b);
    printf("(%d > 0 && %d > 0) = %d\n", a, b, a > 0 && b > 0);
    printf("(%d > 100 || %d > 0) = %d  (cortocircuito: no hace falta evaluar todo)\n",
           a, b, a > 100 || b > 0);

    printf("\n--- Bit a bit ---\n");
    unsigned char u1 = 5;  // 0b00000101
    unsigned char u2 = 3;  // 0b00000011
    printf("%u & %u  = %u\n", u1, u2, (unsigned)(u1 & u2));
    printf("%u | %u  = %u\n", u1, u2, (unsigned)(u1 | u2));
    printf("%u ^ %u  = %u\n", u1, u2, (unsigned)(u1 ^ u2));
    printf("%u << 1 = %u  (equivale a multiplicar por 2)\n", u1, (unsigned)(u1 << 1));
    printf("%u >> 1 = %u  (equivale a dividir por 2)\n", u1, (unsigned)(u1 >> 1));

    return 0;
}
