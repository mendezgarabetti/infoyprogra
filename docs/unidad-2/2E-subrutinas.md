# 2.E Subrutinas (Funciones)

> Código de ejemplo:
> [`ejemplos/unidad-2/08_funciones.c`](../../ejemplos/unidad-2/08_funciones.c),
> [`ejemplos/unidad-2/09_recursion.c`](../../ejemplos/unidad-2/09_recursion.c),
> [`ejemplos/unidad-2/10_alcance_variables.c`](../../ejemplos/unidad-2/10_alcance_variables.c)

## Conceptos generales

A medida que un programa crece, escribir todo dentro de `main` se vuelve
inmanejable: código duplicado, difícil de leer, difícil de testear en
partes. Las **subrutinas** (en C, simplemente **funciones** — C no
distingue "función" de "procedimiento" como otros lenguajes; todo es una
función, que puede o no devolver un valor útil) son la herramienta para
dividir un programa en partes manejables. Cuatro ideas fundamentales de
diseño, que se aplican a funciones pero también a estructuras más grandes:

- **Cohesión**: qué tan enfocada está una función en hacer *una* cosa. Una
  función con alta cohesión (`calcular_promedio`) hace exactamente lo que
  su nombre indica, nada más. Una función con baja cohesión hace varias
  cosas no relacionadas (`procesar_datos_y_mostrar_menu`) — más difícil de
  entender, reutilizar y testear.
- **Acoplamiento**: qué tan dependiente es una función (o módulo) de los
  detalles internos de otras. Bajo acoplamiento es deseable: una función
  debería poder cambiar su implementación interna sin romper a quien la
  usa, siempre que su "contrato" (qué recibe, qué devuelve) no cambie.
- **Encapsulamiento**: ocultar los detalles internos de cómo una función
  logra su resultado, exponiendo solo lo necesario para usarla (su firma).
  Quien llama a `sqrt(x)` no necesita saber qué algoritmo usa por dentro.
- **Reutilización de código**: una vez escrita y probada una función,
  se puede llamar todas las veces que haga falta, desde distintos lugares
  del programa, sin reescribir la lógica.

## Utilidad de las funciones

- Evitan duplicar código (si hay que corregir un bug, se corrige en un
  solo lugar).
- Facilitan testear cada parte del programa por separado.
- Hacen que `main` se lea como un resumen de alto nivel de qué hace el
  programa, delegando el "cómo" a funciones con nombres descriptivos.
- Permiten trabajar en equipo dividiendo el problema en funciones
  independientes.

## Definición de la cabecera (firma) de una función

La **firma (signature)** de una función especifica su nombre, los
argumentos que recibe (con sus tipos) y el tipo del valor que retorna:

```c
tipo_de_retorno nombre_funcion(tipo_arg1 nombre_arg1, tipo_arg2 nombre_arg2) {
    // cuerpo: sentencias
    return valor; // solo si tipo_de_retorno no es void
}
```

Ejemplo concreto:

```c
int sumar(int a, int b) {
    return a + b;
}

void saludar(char inicial) {  // void: no devuelve ningún valor
    printf("Hola, %c\n", inicial);
}
```

- `int sumar(...)`: retorna un `int`.
- `void saludar(...)`: `void` como tipo de retorno significa "no devuelve
  nada" — se usa cuando la función solo produce un efecto (imprimir,
  modificar algo por puntero, ver 3.B) sin resultado que devolver.
- Una función sin argumentos se declara como `nombre(void)`, no
  `nombre()` — en C, `()` vacíos técnicamente significa "cualquier
  cantidad de argumentos, sin verificar", un resabio histórico. Usá
  siempre `(void)` explícito cuando no hay argumentos.

### Declaración (prototipo) vs. definición

Si una función se usa **antes** de donde está definida en el archivo (o
está definida en otro archivo `.c`), hace falta declarar su **prototipo**
antes de usarla — le dice al compilador "esta función existe, con esta
firma", sin dar todavía el cuerpo:

```c
int sumar(int a, int b); // prototipo (declaración): termina en ;, sin cuerpo

int main(void) {
    printf("%d\n", sumar(2, 3)); // el compilador ya sabe que sumar existe
    return 0;
}

int sumar(int a, int b) { // definición: acá sí va el cuerpo
    return a + b;
}
```

En proyectos con varios archivos, los prototipos se ponen típicamente en un
archivo de cabecera (`.h`), incluido con `#include "archivo.h"` en cada
`.c` que necesita usar esas funciones (retomando el preprocesador de 2.B).

## Llamada a una función

**Llamar** a una función es usar su nombre seguido de paréntesis con los
argumentos correspondientes. Los **argumentos** (o parámetros actuales) que
pasás en la llamada se copian en los **parámetros formales** declarados en
la firma — ver "paso por valor" más abajo, y "paso por referencia" en 3.B
con punteros.

```c
int resultado = sumar(4, 5); // 4 se copia en 'a', 5 se copia en 'b'
```

## Variables: alcance, vida y visibilidad

- **Alcance (scope)**: la región del código donde un identificador es
  válido/reconocido. En C, una variable declarada dentro de un bloque `{ }`
  solo es visible dentro de ese bloque (y los bloques anidados dentro de
  él) — se dice que tiene **alcance de bloque (local)**. Una variable
  declarada fuera de toda función tiene **alcance de archivo (global)**:
  visible desde cualquier función del archivo, desde su declaración en
  adelante.
- **Vida (lifetime)**: durante cuánto tiempo de la ejecución existe la
  variable en memoria. Una variable local "nace" al entrar al bloque donde
  se declara y "muere" al salir de él (su memoria se libera automáticamente
  — es una variable **automática**, palabra clave implícita `auto`). Una
  variable global vive durante toda la ejecución del programa.
- **Visibilidad**: relacionado con alcance, pero enfatiza si el
  identificador puede verse desde otro archivo del proyecto (relevante con
  la palabra clave `static`, que restringe una variable/función global a
  ser visible solo dentro de su propio archivo `.c`).

```c
int global = 100; // alcance de archivo, vive todo el programa

void funcion(void) {
    int local = 5; // alcance de bloque (dentro de funcion), vive mientras se ejecuta funcion
    printf("%d %d\n", global, local); // ambas visibles acá
}

int main(void) {
    printf("%d\n", global); // visible
    // printf("%d\n", local); // ERROR: local no existe fuera de funcion
    funcion();
    return 0;
}
```

## ⚠️ Cuidado: variables globales

Es tentador usar variables globales para "no tener que pasar tantos
argumentos", pero eso aumenta el acoplamiento: cualquier función puede
modificarlas desde cualquier lado, lo que hace difícil rastrear de dónde
vino un valor inesperado. Preferí pasar los datos que una función necesita
como argumentos explícitos, y devolver resultados con `return` (o por
puntero, ver 3.B) — reservá las globales para constantes de configuración
(`const`) o casos puntuales bien justificados.

## Paso de argumentos: por valor (introducción)

Por default, C pasa los argumentos **por valor**: la función recibe una
**copia** del valor del argumento, no el original. Modificar el parámetro
dentro de la función no afecta a la variable original que se pasó:

```c
void incrementar(int n) {
    n = n + 1;  // modifica la COPIA local
}

int main(void) {
    int x = 5;
    incrementar(x);
    printf("%d\n", x); // imprime 5, NO 6: x no cambió
    return 0;
}
```

Para que una función pueda modificar una variable del que la llama, hace
falta pasarle su **dirección de memoria** (un puntero) — esto es "paso por
referencia" y se desarrolla en profundidad en la Unidad 3.B, que depende
directamente de entender bien el alcance y la vida de las variables vistos
acá.

## Recursión

Una función es **recursiva** cuando se llama a sí misma, directa o
indirectamente (a través de otra función que a su vez la llama). Toda
función recursiva necesita al menos:

1. **Caso base**: una condición donde la función devuelve un resultado
   directo, sin volver a llamarse — sin esto, la recursión nunca termina.
2. **Caso recursivo**: la función se llama a sí misma con un argumento que
   se acerca al caso base (más chico, más simple).

```c
int factorial(int n) {
    if (n <= 1) {       // caso base
        return 1;
    }
    return n * factorial(n - 1); // caso recursivo: se acerca al caso base
}
// factorial(4) = 4 * factorial(3) = 4 * 3 * factorial(2) = 4 * 3 * 2 * factorial(1) = 4*3*2*1 = 24
```

Cada llamada a una función (recursiva o no) reserva su propio espacio de
memoria para variables locales y parámetros en una región llamada **pila
de llamadas (call stack)** — es la misma "pila" que ves en el depurador
como *call stack* (2.D). Cada llamada recursiva agrega un nuevo "marco"
(*stack frame*) a esa pila; cuando la función retorna, su marco se
descarta.

## ⚠️ Cuidado: recursión sin caso base o mal definido

```c
int mal_factorial(int n) {
    return n * mal_factorial(n - 1); // sin caso base: nunca termina
}
```

Sin caso base (o con un caso base que nunca se alcanza, por ejemplo por un
error al acercarse a él), la función se sigue llamando indefinidamente,
agregando marcos a la pila de llamadas hasta agotar la memoria disponible
para la pila — esto produce un error de **stack overflow**, que suele
terminar el programa abruptamente. Toda función recursiva que escribas
debería poder responder, con claridad, "¿cuál es el caso base, y por qué
cada llamada recursiva se acerca a él?".

La recursión no es "más poderosa" que la iteración (`for`/`while`) — todo
lo que se puede escribir con recursión se puede reescribir iterativamente,
y viceversa. Se prefiere recursión cuando el problema es naturalmente
recursivo en su definición (recorrer un árbol, ver 3.B) porque el código
resulta más claro; se prefiere iteración cuando el rendimiento importa y la
profundidad de recursión podría ser grande, porque cada llamada recursiva
tiene el costo (en tiempo y memoria) de un marco de pila nuevo.

## Autoevaluación

1. ¿Qué diferencia hay entre la declaración (prototipo) y la definición de
   una función? ¿Cuándo hace falta declarar un prototipo antes de usar la
   función?
2. Explicá con tus palabras qué significa que C pase argumentos "por
   valor", y qué consecuencia tiene sobre si una función puede modificar
   una variable de quien la llama.
3. ¿Cuál es el alcance y la vida de una variable declarada dentro de un
   `if` que está dentro de una función?
4. En una función recursiva, ¿qué es el "caso base" y por qué es
   obligatorio para que la recursión termine?
5. Escribí (en papel o en el editor) una versión iterativa de `factorial`
   usando un `for`, y compará mentalmente qué pasa en memoria en cada
   versión (marcos de pila vs. una sola variable acumuladora).
