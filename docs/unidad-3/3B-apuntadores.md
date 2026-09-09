# 3.B Apuntadores y Memoria Dinámica

> Código de ejemplo:
> [`ejemplos/unidad-3/05_punteros_basicos.c`](../../ejemplos/unidad-3/05_punteros_basicos.c),
> [`ejemplos/unidad-3/06_memoria_dinamica.c`](../../ejemplos/unidad-3/06_memoria_dinamica.c),
> [`ejemplos/unidad-3/07_matrices_dinamicas.c`](../../ejemplos/unidad-3/07_matrices_dinamicas.c)

En 3.A quedaron un par de cosas pendientes: qué es exactamente `edades[i]`
por dentro, por qué un arreglo pasado a una función "pierde" su `sizeof`, y
cómo se hace para tener un arreglo cuyo tamaño se decide en tiempo de
ejecución. Todo eso son la misma idea de fondo: **punteros**.

## ¿Qué es un puntero?

Toda variable vive en una dirección de memoria. Un **puntero** es una
variable que, en vez de guardar un dato "normal", guarda una **dirección de
memoria** — la ubicación de otra variable.

```c
int x = 5;
int *p = &x; // p guarda la direccion de x, NO el valor 5

printf("%d\n", x);   // 5           -> el valor de x
printf("%p\n", (void *)p);  // 0x7ffee...  -> la direccion donde vive x
printf("%d\n", *p);  // 5           -> "el valor que hay en la direccion p"
```

Dos operadores, inversos entre sí:

- `&variable` — "dame la **dirección** de esta variable" (de variable a dirección).
- `*puntero` — "dame el **valor** que hay en esta dirección" (de dirección a variable), operación llamada **desreferenciar**.

## Paso por valor vs. paso por referencia

Por defecto, C pasa argumentos a una función **por valor**: la función
recibe una **copia**. Modificar la copia no afecta a la variable original
del `main`.

```c
void no_duplica(int v) {
    v = v * 2; // solo cambia la copia local "v"
}
```

Para que una función modifique una variable que vive en otro lado (por
ejemplo, en `main`), hay que pasarle su **dirección**, no su valor — un
puntero:

```c
void duplicar(int *v) {
    *v = *v * 2; // "el valor en la direccion v" = el doble de si mismo
}

int main(void) {
    int x = 5;
    duplicar(&x); // &x = la direccion de x
    printf("%d\n", x); // 10: SI cambio, porque duplicar modifico esa direccion
    return 0;
}
```

## ⚠️ Cuidado: & y * son inversos

Confundir cuándo usar cada uno es el error más común al empezar con
punteros:

- Si el parámetro de la función es `int *v` (un puntero), en la llamada hay
  que pasar una dirección: `funcion(&x)`.
- Adentro de la función, para leer o escribir el valor apuntado se usa
  `*v`, no `v` (que es la dirección, no el valor).

## Arreglos y punteros

En 3.A quedó pendiente esta pregunta: ¿qué es realmente `edades[i]`? La
respuesta es que un arreglo, en la mayoría de los contextos, **decae a un
puntero a su primer elemento**. `edades[i]` es literalmente equivalente a
`*(edades + i)`: sumarle `i` a la dirección del primer elemento, y
desreferenciar.

```c
int edades[5] = {18, 20, 19, 22, 21};

printf("%d\n", edades[2]);      // 19
printf("%d\n", *(edades + 2));  // 19 (exactamente lo mismo)
```

Esto explica por qué `sizeof(arreglo) / sizeof(arreglo[0])` (visto en 3.A)
**deja de funcionar** apenas el arreglo se pasa como parámetro a una
función: adentro de la función, el parámetro ya es un puntero (4 u 8 bytes,
según la arquitectura), no el arreglo completo — `sizeof` del parámetro da
el tamaño del puntero, no el del arreglo original. Por eso las funciones
que reciben arreglos casi siempre reciben también su tamaño como parámetro
aparte (`void f(int arr[], int n)`).

## `malloc`: reservar memoria en tiempo de ejecución

Un arreglo declarado como `int v[10]` tiene tamaño **fijo en tiempo de
compilación**. Cuando el tamaño depende de un dato que solo se conoce
cuando el programa ya está corriendo (por ejemplo, un `N` que ingresa el
usuario), hace falta pedirle memoria al sistema operativo **en tiempo de
ejecución**. Para eso está `malloc` (de `<stdlib.h>`):

```c
#include <stdlib.h>

double *crear_vector(int n) {
    double *v = malloc(n * sizeof(double));
    if (v == NULL) {
        // malloc puede fallar si no hay memoria disponible
        fprintf(stderr, "No hay memoria disponible\n");
        exit(1);
    }
    return v;
}
```

`malloc(bytes)` reserva esa cantidad de bytes y devuelve un puntero al
primer byte reservado (o `NULL` si no pudo). A partir de ahí, ese puntero
se usa exactamente como un arreglo: `v[0]`, `v[1]`, etc.

## ⚠️ Cuidado: `sizeof` del tipo correcto

```c
double *v = malloc(n * sizeof(int));    // MAL: reserva de menos (int suele ser mas chico que double)
double *v = malloc(n * sizeof(double)); // BIEN
```

Es un error muy común copiar y pegar una línea de `malloc` de otro lado y
olvidarse de actualizar el `sizeof`. El resultado casi nunca es un error de
compilación — es memoria insuficiente que se corrompe silenciosamente al
usarse, un bug muy difícil de rastrear.

## `free`: siempre que se reserva, hay que liberar

Toda memoria pedida con `malloc` sigue reservada hasta que el programa
termina o hasta que se libera explícitamente con `free`:

```c
double *v = crear_vector(5);
// ... usar v ...
free(v);   // devuelve la memoria al sistema
v = NULL;  // evita usar "v" por error despues de liberado
```

No liberar memoria que ya no se usa es una **fuga de memoria (memory
leak)**: el programa va acumulando memoria reservada sin devolverla nunca,
y en un programa que corre mucho tiempo (o que reserva en un bucle) esto
puede agotar la memoria disponible.

## ⚠️ Cuidado: usar memoria después de liberada, o liberarla dos veces

- **Dangling pointer**: usar un puntero después de haberlo liberado con
  `free`. La memoria ya no es tuya; puede haber sido reasignada a otra
  cosa.
- **Double free**: llamar `free()` dos veces sobre el mismo puntero.

Ambos son errores de memoria clásicos — el programa puede "andar bien" en
una corrida y fallar (o corromper datos) en otra, dependiendo de qué haya
en esa memoria en ese momento. Poner `puntero = NULL;` justo después de
liberar ayuda: usar un puntero `NULL` por error se detecta al instante
(falla claramente), en vez de corromper memoria en silencio.

## Modificar in-place vs. crear y devolver

Hay dos formas válidas de que una función produzca un resultado sobre un
arreglo o matriz:

| Estrategia | Cuándo usarla |
|---|---|
| **In-place**: la función recibe un puntero y modifica esa memoria directamente, sin reservar nada nuevo | Cuando el enunciado pide explícitamente "sin crear otro arreglo" / "en la misma memoria" |
| **Crear y devolver**: la función reserva memoria nueva con `malloc` y devuelve el puntero | Cuando hay que generar una estructura que antes no existía (por ejemplo, el resultado de una multiplicación) |

```c
// in-place: escala el MISMO arreglo que recibio, no crea uno nuevo
void escalar(double *v, int n, double factor) {
    for (int i = 0; i < n; i++) {
        v[i] *= factor;
    }
}
```

## ⚠️ Cuidado: no mezclar las dos estrategias

Si el enunciado pide modificar in-place, hacer `malloc` de un arreglo nuevo
adentro de la función y devolverlo **no cumple la consigna** — aunque el
resultado numérico sea correcto — y además genera una fuga de memoria si
nadie libera el arreglo original que quedó sin usar. Antes de escribir la
función, conviene preguntarse: *¿el enunciado quiere que yo modifique lo
que me pasaron, o que genere algo nuevo?*

## Matrices dinámicas

Una matriz `M x N` dinámica se representa habitualmente como un **arreglo
de punteros**: un `malloc` para el arreglo de filas, y un `malloc`
independiente por cada fila.

```c
double **crear_matriz(int filas, int columnas) {
    double **m = malloc(filas * sizeof(double *));
    for (int i = 0; i < filas; i++) {
        m[i] = malloc(columnas * sizeof(double));
    }
    return m;
}
```

Liberarla requiere el **orden inverso**: primero cada fila, después el
arreglo de punteros.

```c
void liberar_matriz(double **m, int filas) {
    for (int i = 0; i < filas; i++) {
        free(m[i]); // cada fila primero...
    }
    free(m); // ...el arreglo de punteros despues
}
```

### Producto matricial: validar antes de multiplicar

Para multiplicar A (`M x N`) por B (`N x P`), las **columnas de A** deben
coincidir con las **filas de B**. El resultado C es `M x P`.

```c
// A: filasA x colsA,  B: colsA x colsB  ->  C: filasA x colsB
if (colsA != filasB) {
    // dimensiones incompatibles: no se puede multiplicar
}
for (int i = 0; i < filasA; i++) {
    for (int j = 0; j < colsB; j++) {
        c[i][j] = 0;
        for (int k = 0; k < colsA; k++) {
            c[i][j] += a[i][k] * b[k][j];
        }
    }
}
```

La función debe **reservar `c` dinámicamente** adentro (con
`crear_matriz`) y devolver el puntero — y antes de multiplicar, chequear
que las dimensiones sean compatibles.

## ⚠️ Cuidado: transponer in-place solo es directo si la matriz es cuadrada

Transponer una matriz **cuadrada** (`N x N`) in-place es sencillo: se
recorre solo la mitad de la matriz e intercambia `m[i][j]` con `m[j][i]`.

```c
for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
        double tmp = m[i][j];
        m[i][j] = m[j][i];
        m[j][i] = tmp;
    }
}
```

Si la matriz es `M x N` con `M != N`, la transpuesta tiene forma `N x M` —
**no entra** en la memoria reservada originalmente como `M x N` (el
arreglo de punteros tiene `M` filas, no `N`). Transponer una matriz
rectangular sin reservar memoria nueva no es un ejercicio simple — en la
práctica, para una matriz rectangular hace falta reservar una matriz nueva
de `N x M` para el resultado. Es una trampa concreta que conviene detectar
leyendo el enunciado, **antes** de ponerse a programar.

## Autoevaluación

1. ¿Qué diferencia hay entre `p` y `*p`, si `p` es un puntero? ¿Y entre `x`
   y `&x`, si `x` es una variable normal?
2. ¿Por qué `void f(int x) { x = 10; }` no modifica la variable que se le
   pasó desde `main`, pero `void f(int *x) { *x = 10; }` sí?
3. ¿Por qué `sizeof(arr) / sizeof(arr[0])` no funciona para calcular la
   cantidad de elementos dentro de una función a la que `arr` se pasó como
   parámetro?
4. ¿Cuál es la diferencia entre reservar memoria con `int v[10]` y con
   `malloc(10 * sizeof(int))`? ¿Cuándo conviene cada una?
5. Si una función recibe un puntero y la consigna dice "sin reservar
   memoria adicional", ¿qué estrategia hay que usar: in-place o crear y
   devolver? ¿Por qué usar la otra no cumpliría la consigna aunque el
   resultado sea numéricamente correcto?
6. ¿Por qué transponer una matriz rectangular (no cuadrada) "en el lugar"
   es más complicado que transponer una cuadrada?
