# 3.A Estructuras de Datos

> Código de ejemplo:
> [`ejemplos/unidad-3/01_arreglos.c`](../../ejemplos/unidad-3/01_arreglos.c),
> [`ejemplos/unidad-3/02_cadenas.c`](../../ejemplos/unidad-3/02_cadenas.c),
> [`ejemplos/unidad-3/03_arreglos_multidimensionales.c`](../../ejemplos/unidad-3/03_arreglos_multidimensionales.c),
> [`ejemplos/unidad-3/04_structs.c`](../../ejemplos/unidad-3/04_structs.c)

Hasta ahora cada variable representaba un único valor. Las **estructuras de
datos** agrupan varios valores relacionados bajo un mismo nombre, para
manejarlos como una unidad.

## Arreglos (vectores)

Un **arreglo (array)** es una colección de elementos del **mismo tipo**,
almacenados en posiciones de memoria **contiguas** (una al lado de la
otra), accesibles por un **índice** numérico que empieza en `0`.

```c
int notas[5]; // arreglo de 5 enteros, sin inicializar (contienen basura)

int edades[5] = {18, 20, 19, 22, 21}; // declaración + inicialización

edades[0] = 18; // el primer elemento tiene índice 0
edades[4] = 21; // el último elemento de un arreglo de 5 tiene índice 4, no 5
```

- El tamaño de un arreglo declarado así (`int edades[5]`) es **fijo**: se
  define en tiempo de compilación (o, si se usa una variable, al momento de
  crearlo) y no puede cambiar. Para tamaños que crecen dinámicamente hace
  falta memoria dinámica (Unidad 3.B).
- `edades[i]` accede al elemento en la posición `i`. Internamente, esto es
  aritmética de punteros (`*(edades + i)`) — la relación exacta entre
  arreglos y punteros se explica en 3.B.

## ⚠️ Cuidado: acceso fuera de rango

```c
int edades[5] = {18, 20, 19, 22, 21};
edades[5] = 99; // fuera de rango: el índice válido máximo es 4

printf("%d\n", edades[10]); // lee memoria que no le pertenece al arreglo
```

C **no verifica** en tiempo de ejecución que el índice esté dentro del
rango válido (a diferencia de Python, donde acceder fuera de rango lanza
`IndexError` inmediatamente). Leer o escribir fuera de los límites de un
arreglo es **comportamiento indefinido**: puede no fallar visiblemente,
puede corromper otra variable, puede provocar un *segmentation fault*
(3.B), y el comportamiento puede cambiar entre ejecuciones. Es una de las
categorías de bug más peligrosas de C — y una fuente histórica real de
vulnerabilidades de seguridad (buffer overflow). Siempre que recorras un
arreglo, asegurate de que el índice nunca llegue a su tamaño ni lo supere.

### Recorrer un arreglo

```c
int notas[5] = {8, 6, 10, 7, 9};
int suma = 0;
for (int i = 0; i < 5; i++) {
    suma += notas[i];
}
printf("Promedio: %.2f\n", (double)suma / 5);
```

`sizeof(notas) / sizeof(notas[0])` da la cantidad de elementos de un
arreglo **mientras siga siendo un arreglo real** (no funciona si el arreglo
"decayó" a puntero, por ejemplo al pasarlo como argumento a una función —
detalle que se retoma en 3.B).

## Cadenas de caracteres (strings)

C **no tiene un tipo `string` nativo**. Una cadena de caracteres es, por
convención, un arreglo de `char` que termina con el carácter especial `'\0'`
(byte nulo, valor `0`) marcando su fin — se lo llama **cadena
terminada en null (null-terminated string)**.

```c
char saludo[6] = {'H', 'o', 'l', 'a', '!', '\0'}; // forma explícita
char saludo2[] = "Hola!"; // forma habitual: el compilador agrega el '\0' solo
                          // saludo2 ocupa 6 bytes: 'H''o''l''a''!''\0'
```

Como no hay un tipo dedicado, C provee funciones de librería (en
`<string.h>`) para operar sobre cadenas, porque los operadores comunes no
sirven (no podés "sumar" dos arreglos con `+`):

| Función | Qué hace |
|---|---|
| `strlen(s)` | longitud de `s`, **sin contar** el `'\0'` |
| `strcpy(dest, src)` | copia `src` en `dest` |
| `strcat(dest, src)` | concatena `src` al final de `dest` |
| `strcmp(a, b)` | compara: `0` si son iguales, negativo/positivo según orden alfabético |
| `strncpy`, `strncat`, `strncmp` | versiones "seguras": reciben un tamaño máximo, evitan desbordar `dest` |

```c
#include <string.h>

char nombre[20] = "Ana";
printf("%zu\n", strlen(nombre));  // 3 (no cuenta el '\0')

char completo[40];
strcpy(completo, nombre);
strcat(completo, " Garcia");
printf("%s\n", completo); // "Ana Garcia"

if (strcmp(nombre, "Ana") == 0) { // strcmp, NO == : == compara direcciones, no contenido
    printf("son iguales\n");
}
```

## ⚠️ Cuidado: `==` no compara el contenido de cadenas

```c
char a[] = "hola";
char b[] = "hola";
if (a == b) { ... }       // BUG: compara direcciones de memoria, casi siempre falso
if (strcmp(a, b) == 0) { ... } // correcto: compara el CONTENIDO
```

`a` y `b` son arreglos (que "decaen" a punteros, ver 3.B); `a == b`
compara si apuntan a la **misma dirección de memoria**, no si tienen el
mismo contenido. Aunque ambas cadenas digan "hola", están en posiciones de
memoria distintas, así que `a == b` da falso. Para comparar contenido de
cadenas, siempre `strcmp`.

## ⚠️ Cuidado: `strcpy`/`strcat` y desbordamiento de buffer

```c
char destino[5];
strcpy(destino, "esto es mas largo que 5"); // escribe MAS ALLA del arreglo: comportamiento indefinido
```

`strcpy` y `strcat` **no verifican** que `dest` tenga espacio suficiente —
es responsabilidad de quien programa garantizarlo de antemano. Cuando el
tamaño de `dest` no está 100% garantizado, usá las variantes con límite
(`strncpy`, `snprintf`) que reciben explícitamente cuántos bytes como
máximo escribir.

## Arreglos multidimensionales

Un arreglo puede tener más de una dimensión — el caso típico es una matriz
(tabla de filas y columnas):

```c
int matriz[3][4]; // 3 filas, 4 columnas

int tablero[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
};

for (int fila = 0; fila < 2; fila++) {
    for (int columna = 0; columna < 3; columna++) {
        printf("%d ", tablero[fila][columna]);
    }
    printf("\n");
}
```

En memoria, un arreglo multidimensional en C se almacena de forma
contigua, en **orden por filas (row-major order)**: primero todos los
elementos de la fila 0, después todos los de la fila 1, etc. Esto importa
para el rendimiento al recorrerlo (recorrer por filas es más eficiente que
por columnas, por localidad de memoria) y para entender cómo se relaciona
con punteros (3.B).

## Tipos definidos por el usuario: `struct`

Mientras un arreglo agrupa elementos del **mismo** tipo, una **estructura
(`struct`)** agrupa campos de **tipos potencialmente distintos** bajo un
solo nombre — es la herramienta para modelar una entidad con varios
atributos (un estudiante, un punto, una fecha).

```c
struct Estudiante {
    char nombre[50];
    int edad;
    double promedio;
};

int main(void) {
    struct Estudiante alumno; // declara una variable de tipo struct Estudiante
    strcpy(alumno.nombre, "Ana");
    alumno.edad = 20;
    alumno.promedio = 8.5;

    printf("%s tiene %d anios y promedio %.1f\n",
           alumno.nombre, alumno.edad, alumno.promedio);

    return 0;
}
```

- Se accede a cada campo con el operador `.` (punto): `alumno.edad`.
- `typedef` permite darle un alias más corto al tipo, para no tener que
  escribir `struct Estudiante` cada vez:

  ```c
  typedef struct {
      char nombre[50];
      int edad;
      double promedio;
  } Estudiante; // ahora "Estudiante" es el nombre del tipo directamente

  Estudiante alumno; // en vez de "struct Estudiante alumno;"
  ```

- Un `struct` puede contener arreglos, otros `struct`, y (fundamental para
  estructuras dinámicas en 3.B) punteros a su propio tipo.
- Un arreglo de structs es la forma habitual de modelar una colección de
  entidades del mismo tipo (ej. `Estudiante curso[100];` — un curso de 100
  alumnos), y es exactamente el tipo de estructura que vas a usar en los
  primeros TP de la materia.

## Autoevaluación

1. ¿Por qué `edades[5]` es un error si `edades` se declaró como
   `int edades[5]`? ¿Qué índices son válidos?
2. ¿Qué carácter marca el final de una cadena en C, y qué función usarías
   para obtener su longitud (sin contar ese carácter)?
3. ¿Por qué `if (cadena1 == cadena2)` casi nunca es lo que se quiere para
   comparar el contenido de dos cadenas? ¿Qué se usa en su lugar?
4. ¿Cuál es la diferencia conceptual entre un arreglo y un `struct` en
   términos de qué tipos de datos pueden agrupar?
5. Dado un `struct Punto { int x; int y; };`, escribí cómo declararías una
   variable de ese tipo y le asignarías `x = 3, y = 4`.
