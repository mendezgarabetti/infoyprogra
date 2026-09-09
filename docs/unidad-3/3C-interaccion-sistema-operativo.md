# 3.C Interacción con el Sistema Operativo

> Código de ejemplo:
> [`ejemplos/unidad-3/08_argumentos_linea_comandos.c`](../../ejemplos/unidad-3/08_argumentos_linea_comandos.c),
> [`ejemplos/unidad-3/09_archivos.c`](../../ejemplos/unidad-3/09_archivos.c)

Hasta ahora todo lo que un programa "conocía" del mundo exterior venía por
`scanf` (el teclado) y salía por `printf` (la pantalla). Esta unidad
agrega tres formas más de interacción con el sistema operativo: recibir
datos al momento de **ejecutar** el programa (no mientras corre), leer y
escribir **archivos** en disco, y consultar **variables de entorno**.

## Argumentos de línea de comandos

En 2.B quedó pendiente esta firma alternativa de `main`, que permite
recibir datos al ejecutar el programa, sin esperar a un `scanf`:

```c
int main(int argc, char *argv[]) {
    // argc: cantidad de argumentos (incluyendo el nombre del programa)
    // argv: arreglo de cadenas con esos argumentos
}
```

```bash
./programa hola mundo
```

Con esa llamada:

- `argc` vale `3` (el nombre del programa cuenta como uno).
- `argv[0]` es `"./programa"` (el nombre con el que se invocó).
- `argv[1]` es `"hola"`, `argv[2]` es `"mundo"`.
- `argv[argc]` es siempre `NULL` (marca el final del arreglo), pero no hace
  falta usarlo: alcanza con recorrer de `1` a `argc - 1`.

```c
for (int i = 1; i < argc; i++) { // arranca en 1: argv[0] es el nombre del programa
    printf("argv[%d] = %s\n", i, argv[i]);
}
```

## ⚠️ Cuidado: validar argc antes de acceder a argv[i]

Igual que con un arreglo común (3.A), acceder a `argv[i]` con un `i` que no
llegó a recibirse es leer memoria fuera de rango — comportamiento
indefinido, no un error que el compilador detecte. Si un programa necesita
que le pasen exactamente 2 argumentos, hay que chequear `argc` **antes** de
usar `argv[1]` o `argv[2]`:

```c
if (argc != 3) {
    fprintf(stderr, "Uso: %s <arg1> <arg2>\n", argv[0]);
    return 1;
}
```

## El código de salida de un programa

El valor que devuelve `main` (con `return`) o que se pasa a `exit()` es el
**código de salida** del programa: por convención, `0` significa "terminó
bien", y cualquier valor distinto de `0` indica algún tipo de error. No es
solo protocolo: scripts, Makefiles y otros programas usan ese valor para
decidir si algo salió bien.

```bash
./programa
echo $?    # en Linux/macOS: imprime el codigo de salida del ultimo comando
```

## Archivos: `fopen`, `fclose`, y el mismo patrón mental que `malloc`/`free`

Para trabajar con un archivo en disco, primero hay que **abrirlo** con
`fopen`, indicando el modo:

| Modo | Significa |
|---|---|
| `"r"` | Leer. El archivo debe existir. |
| `"w"` | Escribir. Crea el archivo si no existe; si existe, lo **pisa**. |
| `"a"` | Agregar (*append*). Escribe al final, sin borrar lo que había. |

```c
FILE *f = fopen("saludo.txt", "w");
if (f == NULL) {
    // el archivo no se pudo abrir (permisos, disco lleno, ruta invalida, etc.)
    fprintf(stderr, "No se pudo abrir el archivo\n");
    return 1;
}
fprintf(f, "Hola desde C\n"); // igual que printf, pero escribe en "f"
fclose(f);
```

`fopen` **puede fallar** (devuelve `NULL`) — a diferencia de `scanf` o
`printf`, que casi siempre funcionan, abrir un archivo depende de cosas
externas al programa (que exista, que haya permisos, que haya espacio en
disco). Por eso siempre se chequea el resultado antes de usar `f`.

## ⚠️ Cuidado: cada `fopen` exitoso necesita su `fclose`

Es exactamente el mismo patrón mental que `malloc`/`free` de 3.B: un
recurso que se pide explícitamente (memoria allá, un archivo abierto acá)
tiene que devolverse explícitamente. No cerrar un archivo puede dejar
datos sin escribirse de verdad en el disco (quedan en un buffer intermedio
hasta que se hace `fclose`), o agotar la cantidad de archivos que un
programa puede tener abiertos a la vez.

## Leer un archivo línea por línea

```c
char linea[100];
FILE *f = fopen("saludo.txt", "r");
while (fgets(linea, sizeof(linea), f) != NULL) {
    printf("%s", linea); // fgets conserva el '\n' de cada linea leida
}
fclose(f);
```

`fgets(destino, tamaño, archivo)` lee una línea (hasta el próximo `\n`, o
hasta completar `tamaño - 1` caracteres) y la guarda en `destino`, siempre
dejando un `'\0'` al final — nunca desborda el buffer, a diferencia de
`gets` (que por eso está deprecada y no debería usarse). Devuelve `NULL`
cuando ya no queda nada para leer, lo que la hace ideal como condición de
un `while`.

## Variables de entorno

El sistema operativo mantiene un conjunto de variables de entorno
(configuración del usuario, rutas, etc.) a las que un programa en C puede
acceder con `getenv`:

```c
#include <stdlib.h>

const char *usuario = getenv("USER"); // puede devolver NULL si no existe
if (usuario != NULL) {
    printf("Usuario: %s\n", usuario);
}
```

`getenv` devuelve un puntero a la cadena con el valor de la variable, o
`NULL` si esa variable no está definida — siempre hay que chequearlo antes
de usarla, igual que con `malloc` y `fopen`.

## Autoevaluación

1. Si se ejecuta `./programa a b c`, ¿cuánto vale `argc`? ¿Qué contiene
   `argv[0]`?
2. ¿Por qué hay que chequear `argc` antes de acceder a `argv[2]`?
3. ¿Qué significa que un programa termine con código de salida distinto de
   `0`? ¿Cómo se consulta ese valor desde la terminal en Linux/macOS?
4. ¿Qué diferencia hay entre abrir un archivo en modo `"w"` y en modo
   `"a"`?
5. ¿Por qué hay que revisar si `fopen` devolvió `NULL` antes de seguir
   usando ese archivo? Dar un ejemplo de por qué podría fallar.
6. ¿Qué tienen en común, conceptualmente, `malloc`/`free` (3.B) y
   `fopen`/`fclose` (3.C)?
