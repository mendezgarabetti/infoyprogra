# 2.D Control Básico del Flujo de Ejecución

> Código de ejemplo:
> [`ejemplos/unidad-2/05_condicionales.c`](../../ejemplos/unidad-2/05_condicionales.c),
> [`ejemplos/unidad-2/06_switch.c`](../../ejemplos/unidad-2/06_switch.c),
> [`ejemplos/unidad-2/07_bucles.c`](../../ejemplos/unidad-2/07_bucles.c)

Por defecto, un programa en C ejecuta sus sentencias **secuencialmente**,
una tras otra, en el orden en que aparecen. Las **estructuras de control**
permiten alterar ese orden: ejecutar (o no) un bloque según una condición,
o repetir un bloque varias veces.

## Sentencias simples y bloques de sentencias

Una **sentencia simple** es una instrucción terminada en `;`. Un **bloque**
es un conjunto de sentencias agrupadas entre `{ }`, que se trata como una
unidad — en cualquier lugar donde C espera una sentencia, podés poner un
bloque.

```c
int x = 5;              // sentencia simple

{                        // bloque: agrupa varias sentencias
    int y = 10;
    printf("%d\n", y);
}
```

Una variable declarada dentro de un bloque solo existe (tiene **alcance**)
dentro de ese bloque — se retoma en detalle en 2.E.

## Estructuras condicionales

### `if` / `else` / `else if`

```c
int nota = 7;

if (nota >= 6) {
    printf("Aprobado\n");
} else {
    printf("Desaprobado\n");
}
```

Con más de dos casos, se encadena con `else if`:

```c
if (nota >= 9) {
    printf("Sobresaliente\n");
} else if (nota >= 6) {
    printf("Aprobado\n");
} else {
    printf("Desaprobado\n");
}
```

Las condiciones se evalúan en orden: apenas una es verdadera, se ejecuta
ese bloque y **se saltean** las siguientes comparaciones, aunque también
serían verdaderas.

En C, cualquier expresión entera se puede usar como condición: `0` es
falso, **cualquier otro valor** es verdadero (no solo `1`). Esto incluye
punteros: un puntero `NULL` es falso, cualquier puntero válido es verdadero
(ver 3.B).

```c
if (3) { ... }        // siempre entra (3 != 0)
if (puntero) { ... }  // entra si puntero no es NULL
```

## ⚠️ Cuidado: llaves opcionales

```c
if (nota >= 6)
    printf("Aprobado\n");
    printf("Felicitaciones\n"); // esto se ejecuta SIEMPRE, no solo si aprobó
```

Si el cuerpo de un `if` (o un bucle) es una sola sentencia, las llaves son
opcionales — pero eso significa que **solo la primera línea** pertenece al
`if`, sin importar la indentación. El código de arriba compila e imprime
"Felicitaciones" siempre, aunque la indentación sugiera lo contrario, porque
para el compilador la indentación no existe. **Recomendación de estilo para
este curso**: usá siempre llaves, aunque el cuerpo sea una sola sentencia.
Evita esta clase de bug por completo.

### Selector de caso: `switch`

Alternativa a una cadena larga de `if/else if` cuando se compara una misma
variable (de tipo entero o `char`) contra varios valores constantes:

```c
int dia = 3;

switch (dia) {
    case 1:
        printf("Lunes\n");
        break;
    case 2:
        printf("Martes\n");
        break;
    case 3:
        printf("Miercoles\n");
        break;
    default:
        printf("Otro dia\n");
        break;
}
```

- `break` corta la ejecución del `switch`. Sin `break`, la ejecución
  **continúa cayendo** (*fall-through*) al siguiente `case`, sin volver a
  evaluar su condición — esto a veces es intencional (varios casos con el
  mismo cuerpo), pero olvidarlo por descuido es un bug clásico.
- `default` se ejecuta si ningún `case` coincidió (es opcional, pero es
  buena práctica incluirlo siempre).

```c
switch (dia) {
    case 6:
    case 7:                       // fall-through intencional: mismo cuerpo para 6 y 7
        printf("Fin de semana\n");
        break;
    default:
        printf("Dia habil\n");
        break;
}
```

## ⚠️ Cuidado: olvidar el `break`

```c
switch (dia) {
    case 1:
        printf("Lunes\n");
        // falta el break: sigue ejecutando el case 2 también
    case 2:
        printf("Martes\n");
        break;
}
// con dia = 1, imprime "Lunes" Y "Martes"
```

## Estructuras de iteración (bucles)

### `while`

Evalúa la condición **antes** de cada iteración. Si es falsa desde el
principio, el cuerpo no se ejecuta ni una vez.

```c
int contador = 0;
while (contador < 5) {
    printf("%d\n", contador);
    contador++;
}
```

### `for`

Ideal cuando de antemano sabés cuántas veces (o bajo qué condición
numérica) se va a repetir. Tiene tres partes, separadas por `;`:
inicialización, condición, actualización.

```c
for (int i = 0; i < 5; i++) {
    printf("%d\n", i);
}
// equivale a:
int i = 0;
while (i < 5) {
    printf("%d\n", i);
    i++;
}
```

1. **Inicialización** (`int i = 0`): se ejecuta una única vez, al entrar.
2. **Condición** (`i < 5`): se evalúa antes de cada iteración; si es falsa,
   el bucle termina.
3. **Actualización** (`i++`): se ejecuta al final de cada iteración.

### `do/while`

Igual que `while`, pero evalúa la condición **después** de cada iteración
— por lo tanto, el cuerpo se ejecuta **al menos una vez**, aunque la
condición sea falsa desde el principio.

```c
int opcion;
do {
    printf("Ingrese una opcion (1-3): ");
    scanf("%d", &opcion);
} while (opcion < 1 || opcion > 3);
// útil para validar entrada del usuario: hay que pedirla al menos una vez
```

### `break` y `continue`

- `break`: corta inmediatamente el bucle (o `switch`) más interno.
- `continue`: salta directamente a la siguiente iteración (en un `for`,
  ejecuta primero la actualización), sin ejecutar el resto del cuerpo en
  esta vuelta.

```c
for (int i = 0; i < 10; i++) {
    if (i == 5) break;       // corta el bucle completo al llegar a 5
    if (i % 2 == 0) continue; // se salta los pares, sin imprimirlos
    printf("%d\n", i);       // solo imprime impares menores a 5: 1, 3
}
```

## Estructuras de control anidadas

Cualquier estructura de control puede contener otra dentro de su cuerpo,
sin límite de profundidad (aunque anidar demasiado suele ser señal de que
conviene extraer una función, ver 2.E):

```c
for (int fila = 0; fila < 3; fila++) {
    for (int columna = 0; columna < 3; columna++) {
        if (fila == columna) {
            printf("X ");
        } else {
            printf(". ");
        }
    }
    printf("\n");
}
```

`break` y `continue` solo afectan al bucle (o `switch`) **más interno** que
los contiene — no hay forma directa de "romper" dos niveles de bucle a la
vez salvo usando una variable de control adicional o (en casos justificados)
`goto`.

## Uso práctico del depurador

A partir de acá el depurador (ver 2.A) deja de ser opcional: cuando un
programa con bucles y condicionales da un resultado incorrecto, "leer el
código con la vista" suele no alcanzar. Flujo básico con el depurador de
VS Code:

1. Poner un **breakpoint** (click al margen izquierdo del editor, junto al
   número de línea) en la línea donde sospechás que algo falla.
2. Ejecutar en modo depuración (`F5` o el botón correspondiente). El
   programa corre normalmente hasta llegar a esa línea, y se **pausa**.
3. Inspeccionar el valor actual de las variables en el panel de "Variables".
4. Avanzar de a un paso:
   - **Step Over** (`F10`): ejecuta la línea actual y pasa a la siguiente,
     sin entrar en el detalle de las funciones que llama.
   - **Step Into** (`F11`): si la línea actual llama a una función, entra a
     ejecutarla paso a paso también.
   - **Step Out** (`Shift+F11`): termina de ejecutar la función actual de
     un tirón y vuelve a quien la llamó.
5. La **call stack** (traza de llamadas) muestra la cadena de funciones que
   llevó hasta el punto actual — indispensable cuando el bug está en una
   función invocada desde varios lugares distintos.

Practicá esto activamente con los bucles anidados: poné un breakpoint
dentro del bucle interno y mirá cómo cambian `fila` y `columna` en cada
paso — es la forma más rápida de entender (o depurar) un bucle anidado que
no se comporta como esperabas.

## Autoevaluación

1. ¿Qué diferencia hay entre `while` y `do/while` en cuántas veces se
   ejecuta el cuerpo como mínimo?
2. Reescribí un `for (int i = 0; i < n; i++) { ... }` como un `while`
   equivalente.
3. ¿Qué pasa si te olvidás un `break` dentro de un `case` de un `switch`?
4. Dado el código de llaves opcionales de la sección "⚠️ Cuidado" de
   arriba, ¿qué imprime si `nota` vale 4, y por qué (aunque la indentación
   sugiera otra cosa)?
5. Con `break` y `continue` dentro de un bucle `for` anidado en otro `for`,
   ¿a cuál de los dos bucles afectan?
