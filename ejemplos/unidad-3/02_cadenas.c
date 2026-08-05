/*
 * 02_cadenas.c
 * Unidad 3.A — cadenas de caracteres y funciones de <string.h>.
 */
#include <stdio.h>
#include <string.h>

int main(void) {
    char nombre[20] = "Ana";
    printf("nombre = \"%s\", longitud = %zu\n", nombre, strlen(nombre));

    char completo[40];
    strcpy(completo, nombre);
    strcat(completo, " Garcia");
    printf("completo = \"%s\"\n", completo);

    char a[] = "hola";
    char b[] = "hola";

    printf("(a == b)          -> %d  (compara DIRECCIONES, casi siempre falso)\n", a == b);
    printf("(strcmp(a,b)==0)  -> %d  (compara CONTENIDO, correcto)\n", strcmp(a, b) == 0);

    return 0;
}
