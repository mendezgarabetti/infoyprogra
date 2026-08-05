# 2.C Tipos de Datos, Operadores, Expresiones y Sentencias

> Código de ejemplo:
> [`ejemplos/unidad-2/02_variables_tipos.c`](../../ejemplos/unidad-2/02_variables_tipos.c),
> [`ejemplos/unidad-2/03_operadores.c`](../../ejemplos/unidad-2/03_operadores.c),
> [`ejemplos/unidad-2/04_conversion_tipos.c`](../../ejemplos/unidad-2/04_conversion_tipos.c)

## Tipos de datos primitivos

Un **tipo de dato** define qué valores puede tomar una variable, cuánta
memoria ocupa y qué operaciones son válidas sobre ella. C tiene un conjunto
pequeño de tipos primitivos (a diferencia de Python, donde `int` tiene
precisión arbitraria, en C cada tipo tiene un tamaño fijo en bytes):

| Tipo | Qué representa | Tamaño típico* | Rango típico (con signo) |
|---|---|---|---|
| `char` | Un carácter (o entero pequeño) | 1 byte | -128 a 127 |
| `int` | Entero | 4 bytes | -2 147 483 648 a 2 147 483 647 |
| `short` | Entero corto | 2 bytes | -32 768 a 32 767 |
| `long` | Entero largo | 8 bytes (en Linux 64 bits) | mucho más grande |
| `float` | Punto flotante (decimal) simple precisión | 4 bytes | ~7 dígitos decimales de precisión |
| `double` | Punto flotante doble precisión | 8 bytes | ~15 dígitos decimales de precisión |

\* El estándar de C **no fija** el tamaño exacto de cada tipo (salvo
`char`, que siempre es 1 byte) — depende del compilador y la arquitectura.
Los tamaños de la tabla son los típicos en un sistema Linux de 64 bits con
`gcc`, que es el entorno de este curso. Para conocer el tamaño exacto en tu
sistema, usá el operador `sizeof` (ver ejemplo de código).

Cada uno de los tipos enteros (`char`, `short`, `int`, `long`) puede
llevar el calificador `unsigned` (sin signo), que elimina los números
negativos y en cambio duplica el rango positivo: `unsigned char` va de 0 a
255 en vez de -128 a 127.

No existe un tipo `string`/`str` nativo en C como en Python: una cadena de
caracteres se representa como un arreglo de `char` (ver Unidad 3.A) — es
una de las diferencias más grandes respecto a lenguajes de alto nivel.

Tampoco existe un tipo `bool` "de fábrica" en C89; C99 en adelante lo provee
como `bool` incluyendo `<stdbool.h>` (que en realidad es un `int` con
`true`=1 y `false`=0 por debajo). Antes de C99 se usaba directamente `int`
con la convención `0 = falso, cualquier otro valor = verdadero`, convención
que **sigue vigente** en todas las expresiones condicionales de C, tengas o
no `<stdbool.h>` incluido.

## Operadores unarios y binarios

- **Unario**: opera sobre un solo operando. Ej.: `-x` (negación), `!x`
  (negación lógica), `++x` (incremento).
- **Binario**: opera sobre dos operandos. Ej.: `x + y`, `x == y`.

C tiene además un único operador **ternario** (tres operandos):
`condicion ? valor_si_verdadero : valor_si_falso`.

```c
int max = (a > b) ? a : b;   // equivalente a un if/else compacto
```

## Operadores aritméticos

| Operador | Significado | Ejemplo |
|---|---|---|
| `+` `-` `*` `/` | suma, resta, multiplicación, división | `a + b` |
| `%` | módulo (resto de la división entera) | `7 % 3` → `1` |
| `++` | incremento (pre o post) | `x++`, `++x` |
| `--` | decremento (pre o post) | `x--`, `--x` |

## ⚠️ Cuidado: división entera

```c
int a = 7, b = 2;
printf("%d\n", a / b);        // imprime 3, NO 3.5 — división entera trunca
printf("%f\n", (double)a / b); // imprime 3.500000 — casteando uno de los operandos a double
```

Si **ambos** operandos de `/` son enteros, el resultado es entero
(se trunca la parte decimal, no se redondea). Este es uno de los errores más
frecuentes al empezar: para obtener un resultado decimal, al menos uno de
los operandos tiene que ser `float`/`double` (ver conversión de tipos, más
abajo). `%` (módulo) solo está definido para tipos enteros.

Pre vs. post incremento/decremento: `x++` devuelve el valor de `x` *antes*
de incrementarlo, `++x` lo devuelve *después*. Cuando se usan como
sentencia aislada (`x++;` sola en su línea) da igual; la diferencia importa
cuando el resultado se usa en la misma expresión: `y = x++;` vs `y = ++x;`
dan valores distintos para `y`.

## Operadores relacionales y lógicos

| Operador | Significado |
|---|---|
| `==` | igualdad |
| `!=` | distinto |
| `<` `>` `<=` `>=` | comparaciones |
| `&&` | Y lógico (AND) |
| `\|\|` | O lógico (OR) |
| `!` | negación lógica (NOT) |

Todas las expresiones relacionales y lógicas producen un `int`: `1` (verdad)
o `0` (falso).

## ⚠️ Cuidado: `=` vs `==`

```c
int x = 5;
if (x = 10) {           // BUG: esto ASIGNA 10 a x, y como 10 != 0, la condición es "verdadera"
    printf("entra siempre\n");
}
```

`=` es asignación, `==` es comparación. Escribir `=` donde correspondía
`==` es un error clásico en C porque el compilador lo acepta (una
asignación es una expresión válida y tiene un valor) — solo `-Wall` te va a
avisar (`suggest parentheses around assignment used as truth value`). En
Python este error ni siquiera compila, porque `=` es una sentencia, no una
expresión — otra diferencia de diseño entre ambos lenguajes.

**Cortocircuito (short-circuit evaluation)**: en `a && b`, si `a` es falso,
`b` **no se evalúa** (el resultado ya es falso, no hace falta). En `a || b`,
si `a` es verdadero, `b` no se evalúa. Esto es una herramienta útil (y a
veces necesaria para evitar errores):

```c
if (puntero != NULL && puntero->valor > 0) { // si puntero es NULL, nunca se evalúa puntero->valor
    ...
}
```

## Operadores a nivel de bits (bitwise)

Operan sobre la representación binaria de los enteros, bit a bit. Menos
frecuentes en programación de aplicación, pero fundamentales en sistemas
embebidos, drivers, protocolos de red y optimización.

| Operador | Significado |
|---|---|
| `&` | AND bit a bit |
| `\|` | OR bit a bit |
| `^` | XOR bit a bit |
| `~` | complemento (NOT bit a bit) |
| `<<` | desplazamiento a la izquierda |
| `>>` | desplazamiento a la derecha |

```c
unsigned char a = 0b00000101; // 5
unsigned char b = 0b00000011; // 3
a & b;   // 0b00000001 → 1
a | b;   // 0b00000111 → 7
a ^ b;   // 0b00000110 → 6
a << 1;  // 0b00001010 → 10 (equivalente a multiplicar por 2)
a >> 1;  // 0b00000010 → 2 (equivalente a dividir por 2, para enteros sin signo)
```

## ⚠️ Cuidado: `&`/`|` no son `&&`/`||`

`&` y `|` operan bit a bit sobre **todo** el valor; `&&` y `\|\|` son
lógicos y solo miran si el valor es cero o no. `if (a & b)` casi nunca es lo
que querés escribir cuando la intención era `if (a && b)` — son operadores
distintos que casualmente comparten símbolo.

## Expresiones aritméticas, lógicas y generales

Una **expresión** es cualquier combinación de operandos y operadores que
produce un valor. Una **sentencia** es una instrucción completa, terminada
en `;` (puede contener una expresión, pero no toda sentencia es una
expresión — ej. `if (...) { }` es una sentencia de control, no produce un
valor).

```c
3 + 4 * 2          // expresión aritmética → 11
(a > 0) && (b < 10) // expresión lógica → 0 o 1
x = 5;             // sentencia de asignación (que además es una expresión: vale 5)
```

## Reglas de precedencia y asociatividad

**Precedencia** determina qué operador "liga más fuerte" cuando aparecen
varios en una expresión sin paréntesis. **Asociatividad** determina el orden
entre operadores de igual precedencia (de izquierda a derecha, o de derecha
a izquierda).

Orden (de mayor a menor precedencia, resumido — hay más niveles de los que
se listan acá):

1. `()` `[]` `->` `.` (llamada a función, indexado, acceso a miembro)
2. `!` `~` `++` `--` `-` (unario) `(tipo)` (cast) `*` (indirección) `&`
   (dirección) `sizeof` — unarios, asocian derecha a izquierda
3. `*` `/` `%`
4. `+` `-`
5. `<<` `>>`
6. `<` `<=` `>` `>=`
7. `==` `!=`
8. `&`
9. `^`
10. `\|`
11. `&&`
12. `\|\|`
13. `?:`  (ternario)
14. `=` `+=` `-=` ... (asignación) — asocia derecha a izquierda

```c
int r = 2 + 3 * 4;       // 14, no 20: * liga más fuerte que +
int r2 = (2 + 3) * 4;    // 20: los paréntesis fuerzan el orden
```

**Regla práctica**: no memorices la tabla completa. Cuando una expresión
mezcla más de dos o tres operadores distintos, usá paréntesis explícitos
aunque no sean estrictamente necesarios — es más legible y evita bugs por
asumir mal la precedencia (un error muy común mezclando bitwise con
relacionales, ej. `a & b == c` se interpreta como `a & (b == c)`, casi
nunca lo que se buscaba).

## Conversiones de tipo implícitas y explícitas (casting)

### Conversión implícita

El compilador convierte automáticamente entre tipos compatibles cuando
hace falta, siguiendo reglas de "promoción" — en general, del tipo "más
chico" al "más grande" para no perder información:

```c
int entero = 5;
double flotante = entero;    // conversión implícita: int → double (segura, sin pérdida)

double d = 3.99;
int i = d;                   // conversión implícita: double → int (¡pérdida! trunca a 3)
```

### Conversión explícita (casting)

Le pedís vos explícitamente al compilador que convierta un valor a otro
tipo, escribiendo el tipo destino entre paréntesis antes de la expresión:

```c
int a = 7, b = 2;
double resultado = (double)a / b;  // fuerza a que la división sea entre double y int
                                    // → la división completa se promueve a double → 3.5
```

Esto es exactamente lo que resuelve el problema de división entera que
viste más arriba: cuando casteás **uno solo** de los operandos a `double`,
el otro se promueve automáticamente y toda la expresión se evalúa en punto
flotante.

## ⚠️ Cuidado: pérdida de información en conversiones

```c
int grande = 300;
char chico = (char)grande;   // char (con signo) va de -128 a 127: overflow, resultado impredecible/truncado

float f = 1.0 / 3.0;
double d = f;                // d hereda la precisión limitada de f (float), aunque double tenga más capacidad
```

Convertir de un tipo "más grande" a uno "más chico" (`int` → `char`,
`double` → `float`, `double` → `int`) puede perder información
silenciosamente — el compilador con `-Wall` avisa en algunos casos
(`-Wconversion` los detecta más agresivamente) pero **compila igual**. Es
responsabilidad tuya asegurarte de que el valor entra en el rango del tipo
destino.

## Autoevaluación

1. ¿Por qué `5 / 2` da `2` en C, y qué hay que hacer para que dé `2.5`?
2. Explicá la diferencia entre `x++` y `++x` cuando el resultado se usa en
   la misma expresión (ej. `y = x++;` vs `y = ++x;` partiendo de `x = 5`).
3. ¿Qué imprime `if (x = 0) { printf("A"); } else { printf("B"); }`? ¿Por
   qué, y cómo se corrige si la intención era comparar `x` con `0`?
4. Dado `int a = 6, b = 3;`, ¿qué diferencia hay entre `a & b` y `a && b`?
5. ¿Qué es "cortocircuito" en `&&` y `\|\|`, y por qué es útil (o
   necesario) cuando el segundo operando puede fallar si se evalúa (ej. un
   puntero nulo)?
