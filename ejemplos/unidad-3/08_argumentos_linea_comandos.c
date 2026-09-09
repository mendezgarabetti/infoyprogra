/*
 * 08_argumentos_linea_comandos.c
 * Unidad 3.C — int main(int argc, char *argv[]) y codigo de salida.
 *
 * Probar:
 *   ./08_argumentos_linea_comandos
 *   ./08_argumentos_linea_comandos hola mundo
 *   echo $?      (en Linux/macOS, despues de correrlo: ve el codigo de salida)
 */
#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Nombre del programa (argv[0]): %s\n", argv[0]);
    printf("Cantidad de argumentos recibidos (sin contar argv[0]): %d\n", argc - 1);

    if (argc < 2) {
        printf("No se paso ningun argumento extra.\n");
        return 0; // codigo de salida 0: "todo bien"
    }

    for (int i = 1; i < argc; i++) { // arranca en 1: argv[0] es el nombre del programa
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    return 0;
}
