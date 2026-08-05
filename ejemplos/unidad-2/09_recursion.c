/*
 * 09_recursion.c
 * Unidad 2.E — recursión: factorial y Fibonacci, con caso base explícito.
 */
#include <stdio.h>

int factorial(int n) {
    if (n <= 1) {               // caso base
        return 1;
    }
    return n * factorial(n - 1); // caso recursivo, se acerca al caso base
}

int fibonacci(int n) {
    if (n == 0) return 0;        // caso base 1
    if (n == 1) return 1;        // caso base 2
    return fibonacci(n - 1) + fibonacci(n - 2); // caso recursivo
}

int main(void) {
    for (int i = 0; i <= 6; i++) {
        printf("factorial(%d) = %d\n", i, factorial(i));
    }

    printf("\n");
    for (int i = 0; i <= 10; i++) {
        printf("fibonacci(%d) = %d\n", i, fibonacci(i));
    }

    return 0;
}
