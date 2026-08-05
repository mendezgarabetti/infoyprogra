/*
 * 08_funciones.c
 * Unidad 2.E — definición, prototipo, llamada y paso por valor.
 */
#include <stdio.h>

// Prototipos: le avisan al compilador que estas funciones existen,
// aunque su cuerpo esté definido más abajo en el archivo.
int sumar(int a, int b);
void saludar(char inicial);
void incrementar(int n);

int main(void) {
    int resultado = sumar(4, 5);
    printf("sumar(4, 5) = %d\n", resultado);

    saludar('M');

    int x = 5;
    incrementar(x);
    printf("despues de incrementar(x), x sigue valiendo %d (paso por valor: copia)\n", x);

    return 0;
}

int sumar(int a, int b) {
    return a + b;
}

void saludar(char inicial) {
    printf("Hola, %c\n", inicial);
}

void incrementar(int n) {
    n = n + 1; // modifica solo la copia local 'n', no la variable original
}
