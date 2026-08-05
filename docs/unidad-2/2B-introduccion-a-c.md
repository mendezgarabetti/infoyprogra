# 2.B Lenguajes compilados fuertemente tipados: Introducción al lenguaje C

> Código de ejemplo: [`ejemplos/unidad-2/01_hola_mundo.c`](../../ejemplos/unidad-2/01_hola_mundo.c)

## Características principales de C

C fue diseñado en 1972 por Dennis Ritchie en los Bell Labs, originalmente
para reescribir el sistema operativo Unix. Esa historia explica casi todas
sus características:

- **Bajo nivel de abstracción con sintaxis de alto nivel**: da acceso
  directo a memoria (punteros) y control fino sobre el tamaño y
  representación de los datos, algo que necesitás para escribir un sistema
  operativo, pero se escribe como texto estructurado, no assembly.
- **Compilado**: genera ejecutables nativos (ver 2.A).
- **Tipado estático**: cada variable tiene un tipo fijo, verificado en
  tiempo de compilación.
- **Procedural**: se organiza en funciones, sin clases ni objetos nativos.
- **Sin gestión automática de memoria**: no tiene *garbage collector*. Vos
  sos responsable de pedir y liberar memoria dinámica explícitamente (ver
  3.B). Esto da control y rendimiento, a costa de responsabilidad: los
  errores de memoria son la fuente de bugs más típica de C.
- **Portable a nivel de código fuente**: el mismo código C compila (con
  ajustes menores) en cualquier arquitectura con un compilador C — por eso
  Unix, y después Linux, se pudieron portar a tantas plataformas distintas.
- **Estándar del lenguaje**: C no es "una cosa" fija, es una especificación
  que evolucionó: C89/C90, C99, C11, C17, C23. Este curso usa **C11**
  (`-std=c11`), un estándar moderno y ampliamente soportado.

Casi todo lo que usás a diario está escrito en C o en un lenguaje que
depende de un runtime escrito en C: el kernel de Linux, el intérprete de
Python (CPython está escrito en C), buena parte de las bases de datos,
drivers, sistemas embebidos (autos, electrodomésticos, microcontroladores).

## Estructura general de un programa en C

Todo programa en C ejecutable necesita, como mínimo, una función `main`:
es el punto de entrada — lo primero que se ejecuta cuando corrés el
programa.

```c
#include <stdio.h>          // 1. directivas de preprocesador

int main(void) {             // 2. función principal (punto de entrada)
    printf("Hola, mundo\n"); // 3. cuerpo: sentencias
    return 0;                // 4. valor de retorno al sistema operativo
}
```

Desglosado:

1. **`#include <stdio.h>`**: le pide al preprocesador que incluya la
   librería estándar de entrada/salida, necesaria para usar `printf`.
2. **`int main(void)`**: declara la función `main`. `int` es el tipo que
   retorna (un entero); `void` entre paréntesis significa que no recibe
   argumentos (hay otra forma con argumentos, `int main(int argc, char
   *argv[])`, que se ve más adelante en el curso para leer argumentos de
   línea de comandos).
3. El cuerpo de la función va entre llaves `{ }`. Cada sentencia termina
   con `;`.
4. **`return 0;`**: `main` le devuelve un entero al sistema operativo. Por
   convención, `0` significa "el programa terminó sin errores"; cualquier
   otro valor indica algún tipo de error (esto lo podés verificar en la
   terminal con `echo $?` después de ejecutar el programa).

## Componentes del lenguaje

### Sintaxis básica

- Cada sentencia termina en `;`.
- Los bloques de código van entre `{ }`.
- Los comentarios son `// comentario de una línea` o `/* comentario de
  varias líneas */`.
- C distingue mayúsculas de minúsculas (`case-sensitive`): `total` y
  `Total` son identificadores distintos.
- El espacio en blanco (espacios, tabs, saltos de línea) es en general
  irrelevante para el compilador — importa para vos, para que el código sea
  legible.

### Identificadores (variables y funciones)

Un **identificador** es el nombre que le das a una variable, función,
tipo, etc. Reglas:

- Puede contener letras, dígitos y guion bajo (`_`).
- No puede empezar con un dígito.
- Es sensible a mayúsculas/minúsculas.
- No puede coincidir con una palabra reservada del lenguaje (`int`, `if`,
  `while`, `return`, etc.).

```c
int edad;        // válido
int _contador;   // válido
int total_1;     // válido
int 1total;      // INVÁLIDO: empieza con dígito
int int;         // INVÁLIDO: palabra reservada
```

Convención de estilo usada en este curso: `snake_case` para variables y
funciones (`cantidad_items`, `calcular_promedio`), nombres descriptivos
antes que cortos (`indice` mejor que `i` salvo en bucles muy locales).

### Constantes

Un valor que no cambia durante la ejecución. Dos formas principales de
declararlas:

```c
#define PI 3.14159        // constante de preprocesador (sustitución textual, ver más abajo)
const double PI2 = 3.14159; // constante de tipo double, verificada por el compilador
```

La diferencia entre ambas se retoma más abajo (preprocesador) y en 2.C: la
de `#define` es un simple *reemplazo de texto* antes de compilar; la de
`const` es una variable real, con tipo, que el compilador impide reasignar.
En general se prefiere `const` cuando el valor tiene un tipo claro, porque
el compilador puede verificar tipos y el depurador puede inspeccionar su
valor — con `#define` eso no es posible porque para cuando el compilador ve
el código, `PI` ya no existe como símbolo, fue reemplazado por el texto
`3.14159`.

### Operadores (introducción)

Un **operador** es un símbolo que representa una operación sobre uno o más
valores (**operandos**). Ejemplos: `+`, `-`, `*`, `/`, `=`, `==`, `&&`. Se
desarrollan en profundidad en 2.C — acá alcanza con reconocer que existen y
que `=` (asignación) es distinto de `==` (comparación de igualdad), una de
las confusiones más comunes al empezar.

### Declaración de variables

**Declarar** una variable es decirle al compilador "existe una variable con
este nombre y este tipo, reservale espacio en memoria":

```c
int edad;              // declaración: reserva espacio, valor inicial indeterminado
int anio = 2026;        // declaración + inicialización en la misma línea
double promedio = 8.5;
char inicial = 'M';
```

## ⚠️ Cuidado: variables sin inicializar

```c
int contador;
printf("%d\n", contador); // comportamiento indefinido: puede imprimir cualquier cosa
```

A diferencia de Python (donde no podés *usar* una variable sin haberla
asignado antes — te tira `NameError`), en C declarar una variable **no** le
asigna automáticamente un valor. El espacio de memoria reservado contiene lo
que haya quedado ahí de antes (basura). Usar una variable sin inicializar es
**comportamiento indefinido**: puede "funcionar" en tu máquina y fallar en
la del profesor. Compilar con `-Wall` ayuda: `gcc` suele avisar
`'contador' is used uninitialized`.

## El preprocesador

El **preprocesador** es un paso previo a la compilación en sí (ver 2.A):
procesa las líneas que empiezan con `#` y produce el código C "real" que
después ve el compilador. Es, conceptualmente, un sistema de sustitución de
texto — no entiende C, solo reemplaza patrones.

### Directiva `#include`

Incluye el contenido de otro archivo en el punto donde aparece la
directiva — literalmente "pega" el archivo ahí.

```c
#include <stdio.h>   // busca en las carpetas estándar del sistema/compilador
#include "mis_funciones.h" // busca primero en el directorio del proyecto
```

- `< >` para librerías del sistema/estándar.
- `" "` para tus propios archivos de cabecera (`.h`), típicamente en el
  mismo proyecto.

### Directiva `#define`

Define una **macro**: un identificador que el preprocesador sustituye por
un texto, en todo el archivo, antes de compilar.

```c
#define PI 3.14159
#define MAX_ESTUDIANTES 100

// también puede tener "parámetros" (macro función):
#define CUADRADO(x) ((x) * (x))

int main(void) {
    double area = PI * CUADRADO(5); // el preprocesador reemplaza esto por:
                                     // double area = 3.14159 * ((5) * (5));
    return 0;
}
```

## ⚠️ Cuidado: las macros son sustitución de texto, no funciones

```c
#define CUADRADO(x) x * x

int resultado = CUADRADO(2 + 3); // se expande a:  2 + 3 * 2 + 3  =  11, ¡no 25!
```

Por eso siempre se envuelven el macro completo y cada parámetro entre
paréntesis: `#define CUADRADO(x) ((x) * (x))`. Aun así, las macros pueden
evaluar una expresión más de una vez si el argumento tiene efectos
secundarios (por ejemplo, `CUADRADO(i++)` incrementa `i` dos veces). Por
esto, en C moderno se prefiere `const` para constantes simples y funciones
reales (ver 2.E) en vez de macros función, salvo casos puntuales.

### Otras directivas

- `#ifdef`, `#ifndef`, `#endif`: compilación condicional — incluir o
  excluir bloques de código según si una macro está definida. Uso típico:
  **guardas de inclusión** en archivos de cabecera, para evitar incluir el
  mismo `.h` dos veces:

  ```c
  #ifndef MI_ARCHIVO_H
  #define MI_ARCHIVO_H

  // contenido del archivo .h

  #endif
  ```
- `#undef`: elimina la definición de una macro.
- `#pragma`: instrucciones específicas del compilador (fuera del estándar
  estricto, ej. `#pragma once` como alternativa moderna a la guarda de
  inclusión de arriba, soportada por casi todos los compiladores actuales).

## Autoevaluación

1. ¿Qué hace concretamente `#include <stdio.h>` y en qué etapa del proceso
   de compilación ocurre (repasá 2.A)?
2. ¿Por qué `#define CUADRADO(x) x * x` es peligroso, y cómo se corrige?
3. ¿Cuál es la diferencia entre declarar una variable (`int x;`) y
   declararla e inicializarla (`int x = 0;`)? ¿Qué riesgo corrés si usás la
   variable antes de asignarle un valor?
4. ¿Qué significa el valor de retorno de `main`, y qué representa un
   `return 0;` frente a un `return 1;`?
