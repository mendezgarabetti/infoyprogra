# Guion de orador — 1/3: Introducción a Python para Programadores de C

Texto para leer/decir en cada diapositiva de `01-fundamentos.pdf` (26
páginas). Está escrito en primera persona, tal como se diría en clase —
usalo como base y ajustalo a tu propio estilo, no hace falta leerlo textual.

---

### 1. Título

Buenas a todos. Hoy arrancamos una serie de tres clases para pasar de C a
Python. La buena noticia es que no estamos aprendiendo a programar de
nuevo: todo lo que ya saben —variables, condicionales, bucles, funciones—
sigue siendo válido. Lo que cambia es la sintaxis, y en algunos casos, cómo
se resuelven las mismas ideas con menos código. Vamos a ir viendo todo por
contraste: siempre C de un lado, Python del otro.

### 2. Índice de Contenidos

Este es el mapa de la clase de hoy: primero sintaxis fundamental, después
variables y tipos de datos, estructuras de control —los if y los bucles—,
entrada de datos por teclado, funciones y parámetros, y cerramos con un
resumen comparativo. Son seis bloques, todos cortos.

### 3. Por qué cambiamos de lenguaje ahora

Quiero que quede clara una cosa antes de empezar: esto no es un curso de
programación desde cero, ya programan. Lo que vamos a hacer es aprender la
sintaxis de Python apoyándonos en lo que ya saben de C. Esta es la primera
de tres presentaciones: hoy vemos los fundamentos —lo que necesitan para
escribir cualquier programa simple—; en la segunda vamos a ver listas,
tuplas y diccionarios, que son las estructuras de datos de Python,
equivalentes a los arreglos y `structs` de C; y en la tercera, cadenas de
texto más avanzadas, manejo de archivos y funciones más completas. Con las
tres van a tener todo lo que necesitan para resolver la Parte B del TP4.

### 4. *(automática)* Índice — Sección 1

Arrancamos por el primer bloque: sintaxis fundamental.

### 5. ¡Hola, Mundo!

Empecemos con el clásico "Hola, Mundo". Miren el lado izquierdo: en C
necesitamos incluir la librería de entrada y salida, declarar la función
`main`, usar `printf` con su cadena de formato, terminar con punto y coma,
y encima compilar antes de poder correrlo. Ahora miren Python: una sola
línea, `print`, entre paréntesis el texto, y listo, ya lo pueden correr.
Cuatro cosas para quedarse: Python es interpretado, no compila; no exige
una función `main`; no usa punto y coma —es opcional y nadie lo usa—; y los
bloques de código no se marcan con llaves, se marcan con la indentación.
Ese último punto es tan importante que le dedico la próxima diapositiva
entera.

### 6. Cuidado: la indentación es sintaxis

Esto no es un detalle de prolijidad, es sintaxis real. En C ustedes pueden
indentar como quieran, o no indentar nada, y el programa compila igual —al
compilador no le importa, solo mira las llaves. En Python la indentación
ES la forma de decir qué línea pertenece a qué bloque. Miren el ejemplo: la
primera línea después del `if`, con cuatro espacios, pertenece al `if` y se
ejecuta. La segunda, que tiene un espacio de más, Python la interpreta
como un bloque distinto y no sabe a qué pertenece — tira un error de
indentación. Mi recomendación: configuren el editor para que use siempre
espacios, nunca mezclen con tabs, eso genera estos errores todo el tiempo.

### 7. *(automática)* Índice — Sección 2

Pasamos a variables y tipos de datos.

### 8. Variables y Tipos de Datos

La diferencia principal acá es el tipado. En C ustedes tienen que declarar
el tipo antes de usar la variable —`int`, `float`, lo que sea— y ese tipo
queda fijo. En Python no declaran nada: el tipo se infiere automáticamente
según el valor que le asignan. Si le asigno diez, es un entero; si le
asigno noventa y cinco con cincuenta, es un flotante. Si en algún momento
quieren saber qué tipo tiene una variable, existe la función `type()`.

### 9. Cuidado: dinámico no es "sin tipo"

Ahora, cuidado con un malentendido muy común: que Python "no tiene tipos".
Eso es falso. Lo que pasa es que el mismo nombre de variable puede
referirse a un entero en un momento y a un string en otro —eso es lo
dinámico—. Pero en cualquier momento dado, esa variable SÍ tiene un tipo
bien definido, y Python lo respeta estrictamente. Miren el ejemplo: si
intento sumar el string `"Tengo"` con el entero `edad`, Python me tira un
`TypeError`, exactamente como pasaría en C si mezclaran tipos incompatibles
sin castear. La solución es la misma idea que un cast en C: convertir
explícitamente, en este caso con `str(edad)`.

### 10. *(automática)* Índice — Sección 3

Estructuras de control.

### 11. Condicionales: if / elif / else

Acá el mapeo es casi directo. El `if` de C es `if` en Python. El `else if`
se escribe todo junto, `elif`. Y el `else` queda igual. Lo que cambia: no
hace falta paréntesis alrededor de la condición, y en vez de llaves se usan
dos puntos más indentación. Importante: se ejecuta el PRIMER bloque cuya
condición dé verdadero, y ahí termina, no sigue evaluando los demás. En el
ejemplo, con `nota = 75`, no entra en el primero porque no es mayor o igual
a 90, entra en el segundo porque sí es mayor o igual a 60, imprime
"Aprobado", y no llega a evaluar el `else`.

### 12. Equivalente a Switch

Una pregunta que seguro se van a hacer: ¿y el `switch` de C? Python no
tiene `switch-case` como estructura del lenguaje. La forma de lograr
exactamente lo mismo es encadenar `if`, `elif`, `elif`... tantas veces como
casos necesiten, con un `else` al final haciendo de `default`. Miren el
ejemplo de los días de la semana: mismo resultado, misma lógica, un poco
más de líneas que un `switch`, pero nada nuevo conceptualmente.

### 13. Bucles: while

El `while` es prácticamente idéntico al de C. Se saca el paréntesis de la
condición, y ojo con un detalle: Python no tiene el operador `++` ni `--`.
Si en C escribían `i++`, en Python tienen que escribir `i += 1`.

### 14. Bucles: for

Acá sí hay un cambio de filosofía, no solo de sintaxis. El `for` de C es un
contador: ustedes arman a mano la inicialización, la condición de corte, y
el incremento. El `for` de Python no funciona así — itera sobre una
secuencia de valores, uno por uno. Entonces, ¿cómo hacemos para contar como
en C? Usamos la función `range()`. `range(5)` genera la secuencia `0, 1, 2,
3, 4`, y el `for` va tomando cada uno de esos valores. Es la forma de
simular el contador de C dentro de la lógica de iteración de Python.

### 15. range() con inicio, fin y paso

`range()` es más flexible de lo que parece: acepta inicio, fin y paso. Así
como en C pueden hacer un `for` que vaya de 10 a 1 restando de a uno, en
Python hacen `range(10, 0, -1)` y `range` genera esa cuenta regresiva. Un
detalle para recordar siempre: el valor de "fin" NUNCA se incluye en la
secuencia, exactamente como la condición de corte de un `for` en C — ahí
paramos, ese valor no se procesa.

### 16. *(automática)* Índice — Sección 4

Entrada de datos desde teclado.

### 17. Lectura de Datos: scanf vs input()

Para leer datos del usuario, en C usan `scanf`, con un especificador de
formato como `%d` o `%s`, y tienen que pasar la dirección de memoria con el
`&`. En Python usan `input()`, pero ojo: `input()` SIEMPRE devuelve un
string, sin importar qué haya tipeado el usuario. Si necesitan que sea un
número, tienen que convertir explícitamente con `int()` o `float()`. Miren
el ejemplo: piden la edad con `input()`, y directamente envuelven eso con
`int()` antes de guardarlo en la variable. Y de paso, noten el `print` con
la `f` adelante — eso es un f-string, la forma moderna de armar strings con
variables adentro, mucho más cómoda que ir concatenando con `+`.

### 18. Lectura de Múltiples Valores

¿Qué pasa si necesito leer dos valores en una sola línea, como cuando en C
hacían `scanf` con dos `%d` seguidos? En Python, leo la línea completa como
un string con `input()`, la separo en pedazos con el método `.split()`
—que por defecto separa por espacios—, y desempaqueto el resultado
directamente en dos variables, `a` y `b`. Después convierto cada una a
entero. Este patrón —leer, separar, desempaquetar, convertir— lo van a usar
todo el tiempo en el TP4, por ejemplo para leer una coordenada de la
batalla naval.

### 19. *(automática)* Índice — Sección 5

Funciones y parámetros.

### 20. Definición de Funciones

Para definir una función en Python se usa la palabra clave `def`. A
diferencia de C, no declaran el tipo de retorno, ni el tipo de los
parámetros — nada de eso. Solo el nombre de la función y el nombre de los
parámetros. El cuerpo, indentado como cualquier bloque. Miren el ejemplo:
la función `sumar` en C y en Python hacen exactamente lo mismo, con la
sintaxis reducida a lo esencial en Python.

### 21. Paso de Parámetros: Mutabilidad

Esta es la diapositiva más importante de hoy, así que les pido que le
presten atención especial. En C, cuando pasan un parámetro a una función,
se pasa una COPIA — si quieren que la función modifique el valor original,
tienen que pasar un puntero. En Python la historia es distinta: lo que se
pasa es una referencia al objeto. Pero acá hay un matiz clave: si el objeto
es inmutable —un número, un string— se va a COMPORTAR como si fuera paso
por valor, porque no se puede modificar en el lugar. Si el objeto es
mutable —una lista, un diccionario— se va a comportar como paso por
referencia, porque sí se puede modificar en el lugar. Se los muestro en
código en la próxima diapositiva, con un ejemplo donde, contra lo que uno
esperaría, el resultado final es exactamente el mismo en C y en Python.

### 22. Paso de Parámetros: mismo resultado en los dos lenguajes

Miren los dos códigos en paralelo. En los dos casos pasamos dos cosas: un
número suelto, y un arreglo o lista. Dentro de la función reasignamos el
número —y en ningún caso eso afecta a la variable de afuera—, ¿por qué?
Porque reasignar es simplemente hacer que el nombre local apunte a otra
cosa, no toca el original. Pero cuando modificamos la posición cero del
arreglo o de la lista, en los dos casos SÍ se ve reflejado afuera. La
explicación de fondo, y esto es lo interesante: en C, un arreglo pasado
como parámetro YA es un puntero — lo que se copia por valor es la
dirección de memoria, no el contenido. Reasignar esa variable local no
mueve el arreglo original, pero escribir en esa dirección sí lo modifica.
En Python pasa exactamente lo mismo con el concepto de referencia a
objeto. Es la misma lógica, dos sintaxis distintas.

### 23. *(automática)* Índice — Sección 6

Cerramos con un resumen.

### 24. Tabla Comparativa Rápida

Repaso relámpago de todo lo que vimos hoy en una sola tabla: tipado
estático contra dinámico, compilado contra interpretado, sintaxis verbosa
con llaves y punto y coma contra sintaxis basada en indentación, manejo
manual de memoria con `malloc` y `free` contra recolector de basura
automático, punteros explícitos contra prácticamente inexistentes en
Python, y el `for` basado en contador contra el `for` basado en iteración.
Si tienen dudas de algo de esto, este es el momento, antes de pasar al
cierre.

### 25. Lo que sigue

Con todo lo visto hoy ya pueden traducir a Python cualquier programa de C
que use variables, condicionales, bucles y funciones simples — que es
exactamente lo que necesitan para los ejercicios 5 y 6 del TP4, el parking
inteligente y la batalla naval, al menos en su lógica básica. Pero para
modelar los datos de esos ejercicios —los tres pisos del parking, el
tablero de la batalla naval, el inventario de la librería— vamos a
necesitar algo más que variables sueltas. Eso es exactamente el tema de la
próxima clase: listas, tuplas y diccionarios, el equivalente en Python de
los arreglos y los `structs` de C.

### 26. Cierre

Bueno, con esto cerramos la primera parte. Abrimos a preguntas, y después
pasamos a la práctica en Colab para que empiecen a escribir código
ustedes.
