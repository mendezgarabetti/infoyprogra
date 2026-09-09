/*
 * 09_archivos.c
 * Unidad 3.C — escribir y leer un archivo de texto, y consultar una
 * variable de entorno con getenv().
 */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *nombre_archivo = "saludo.txt";

    // Escribir
    FILE *f = fopen(nombre_archivo, "w"); // "w": crea el archivo (o lo pisa si ya existia)
    if (f == NULL) {
        fprintf(stderr, "No se pudo crear %s\n", nombre_archivo);
        return 1;
    }
    fprintf(f, "Hola desde C\n");
    fprintf(f, "Segunda linea\n");
    fclose(f); // cada fopen exitoso necesita su fclose

    // Leer linea por linea
    f = fopen(nombre_archivo, "r"); // "r": el archivo debe existir
    if (f == NULL) {
        fprintf(stderr, "No se pudo abrir %s para lectura\n", nombre_archivo);
        return 1;
    }

    char linea[100];
    printf("Contenido de %s:\n", nombre_archivo);
    while (fgets(linea, sizeof(linea), f) != NULL) {
        printf("  > %s", linea); // fgets conserva el '\n' del archivo
    }
    fclose(f);

    // Variable de entorno (puede no existir: getenv devuelve NULL)
    const char *usuario = getenv("USER");
    if (usuario != NULL) {
        printf("Variable de entorno USER: %s\n", usuario);
    } else {
        printf("La variable de entorno USER no esta definida en este sistema.\n");
    }

    return 0;
}
