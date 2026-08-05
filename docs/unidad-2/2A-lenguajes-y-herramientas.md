# 2.A Introducción a los Lenguajes y Herramientas de Programación

## ¿Qué es un lenguaje de programación?

Un **lenguaje de programación** es un sistema de notación formal que permite
describir, de manera precisa y no ambigua, una secuencia de instrucciones
que una computadora puede ejecutar. La palabra clave es *formal*: a
diferencia del español o el inglés, un lenguaje de programación tiene una
gramática exacta (su **sintaxis**) y un significado exacto para cada
construcción válida de esa gramática (su **semántica**). Si escribís algo
que no respeta la sintaxis, el traductor del lenguaje (compilador o
intérprete) lo rechaza; si lo respeta, el significado no depende de quién lo
lea, siempre es el mismo.

Esto es lo que distingue "programar" de "escribir instrucciones en
español para una persona": una persona puede inferir intención a partir de
contexto ambiguo, una computadora no.

## Niveles de abstracción

Todo programa termina ejecutándose como una secuencia de instrucciones en
**lenguaje de máquina**: números binarios que el procesador interpreta
directamente (por ejemplo, "sumar el contenido de dos registros"). Escribir
directamente en binario es posible pero impracticable para programas de
cierta complejidad, así que existen capas de abstracción intermedias:

| Nivel | Ejemplo | Cercanía al hardware |
|---|---|---|
| Lenguaje de máquina | `10110000 01100001` | Total — es lo único que la CPU ejecuta |
| Lenguaje ensamblador (assembly) | `MOV AL, 61h` | Una instrucción ≈ una instrucción de máquina, con nombres mnemotécnicos |
| Lenguaje de **bajo nivel** | C | Da control fino sobre memoria y hardware, pero con sintaxis legible |
| Lenguaje de **alto nivel** | Python, Java | Abstrae memoria, tipos, gestión de recursos — prioriza productividad |

**C se ubica en un punto particular de esta escala**: es de alto nivel en el
sentido de que se lee como texto estructurado (no como binario ni
mnemotécnicos), pero se lo considera "de bajo nivel" respecto a lenguajes
como Python porque expone conceptos que en otros lenguajes están ocultos —
direcciones de memoria, el tamaño exacto en bytes de cada tipo de dato,
gestión manual de memoria. Por eso a C se lo suele llamar un lenguaje de
**nivel medio**: da el control de un lenguaje de bajo nivel con la
legibilidad sintáctica de uno de alto nivel.

Esta es precisamente la razón pedagógica de empezar el curso por C: te
obliga a entender qué está pasando "por debajo" (memoria, tipos, punteros),
conocimiento que en Python vas a poder aprovechar aunque el lenguaje te lo
oculte.

## Paradigmas de programación

Un **paradigma de programación** es una forma de conceptualizar y
estructurar la solución a un problema. No es una propiedad del lenguaje en
sí, sino un estilo que el lenguaje favorece o permite. Los principales:

- **Imperativo / procedural**: el programa es una secuencia de instrucciones
  que modifican el estado de la máquina paso a paso, organizadas en
  procedimientos (funciones) que se llaman entre sí. **C es el ejemplo
  clásico de lenguaje procedural.**
- **Orientado a objetos**: el programa se organiza en torno a "objetos" que
  combinan datos y comportamiento (Java, C++, Python también lo soporta).
- **Funcional**: el programa se expresa como composición de funciones
  matemáticas puras, evitando estado mutable (Haskell; Python y C tienen
  soporte parcial mediante funciones de primer orden en el caso de C con
  punteros a función).
- **Declarativo**: se describe *qué* se quiere obtener, no *cómo* obtenerlo
  (SQL, HTML no es un lenguaje de programación pero es declarativo).

Muchos lenguajes modernos son **multiparadigma** (Python, por ejemplo,
soporta procedural, orientado a objetos y parcialmente funcional). C es
mayormente procedural puro — no tiene clases ni objetos nativos, y eso es
intencional: fue diseñado en los años 70 para escribir sistemas operativos,
donde el control explícito del flujo y la memoria importa más que la
abstracción.

## Lenguajes de propósito general vs. de propósito particular

- **Propósito general**: diseñados para resolver cualquier tipo de
  problema computable — C, Python, Java, JavaScript.
- **Propósito particular (de dominio específico, DSL)**: diseñados para un
  dominio acotado — SQL (consultas a bases de datos), HTML/CSS (estructura
  y estilo de documentos), regex (patrones de texto), Makefile (reglas de
  compilación, que vas a usar en este mismo curso).

C y Python son ambos de propósito general, pero cada uno con un nicho donde
se usa predominantemente: C en sistemas operativos, drivers, sistemas
embebidos y software donde el rendimiento y el control de memoria son
críticos; Python en scripting, ciencia de datos, backend web, automatización
— donde la velocidad de desarrollo importa más que exprimir el hardware.

## Interpretación vs. Compilación

Esta es una de las distinciones más importantes del curso porque explica
por qué C y Python "se sienten" tan distintos al usarlos.

- **Compilación**: un programa (el **compilador**) traduce todo el código
  fuente a lenguaje de máquina *antes* de ejecutarlo, generando un archivo
  ejecutable independiente. La traducción ocurre una sola vez; después, el
  ejecutable corre directamente sobre el hardware sin necesidad del
  compilador. **C es un lenguaje compilado.**
- **Interpretación**: un programa (el **intérprete**) lee el código fuente y
  lo ejecuta línea por línea (o instrucción por instrucción) en el momento,
  sin generar un ejecutable independiente previo. El intérprete tiene que
  estar presente cada vez que se ejecuta el programa. **Python es
  interpretado** (más precisamente, como se explica abajo, es un híbrido).

| | Compilado (C) | Interpretado (Python) |
|---|---|---|
| Cuándo se detectan errores de sintaxis | Antes de ejecutar (falla la compilación) | Recién al llegar a esa línea en ejecución |
| Velocidad de ejecución | Alta — ya es código máquina | Menor — hay trabajo de traducción en cada ejecución |
| Portabilidad del resultado | El ejecutable es específico de una plataforma (SO + arquitectura) | El código fuente corre en cualquier máquina con el intérprete instalado |
| Ciclo de desarrollo | Escribir → compilar → ejecutar (más lento por iteración) | Escribir → ejecutar (más rápido por iteración) |

En la práctica esta línea es más difusa de lo que parece: Python en
realidad compila el código fuente a un formato intermedio llamado
**bytecode** (los archivos `.pyc`), que después es interpretado por la
máquina virtual de Python (CPython). Java hace algo parecido: compila a
*bytecode* de la JVM, que luego se interpreta (o se compila "justo a
tiempo", JIT, a código máquina real). Es decir, "compilado" e "interpretado"
son puntos de un espectro, no una dicotomía estricta — pero para este curso
alcanza con la distinción simple: **C genera un ejecutable nativo antes de
correr, Python no.**

## Lenguajes fuerte y débilmente tipados

El **tipo** de un dato determina qué valores puede tomar y qué operaciones
son válidas sobre él (sumar dos enteros tiene sentido, sumar un entero con
una cadena de texto, no siempre). El **tipado** de un lenguaje describe qué
tan estrictamente controla esto:

- **Fuertemente tipado**: el lenguaje no permite operar entre tipos
  incompatibles sin una conversión explícita, y esa conversión suele estar
  sujeta a reglas claras. Errores de tipo se detectan (en C, en tiempo de
  compilación para la mayoría de los casos).
- **Débilmente tipado**: el lenguaje realiza conversiones implícitas de
  forma más permisiva, a veces con resultados sorprendentes.

Esto es independiente de otro eje: **tipado estático vs. dinámico**.

- **Estático**: el tipo de cada variable se determina y verifica en tiempo
  de compilación, y no cambia. **C es de tipado estático**: declarás
  `int x;` y `x` va a ser un entero durante toda su vida.
- **Dinámico**: el tipo se determina en tiempo de ejecución y puede cambiar.
  **Python es de tipado dinámico**: `x = 5` después `x = "hola"` es válido,
  la variable simplemente pasa a referenciar un objeto de otro tipo.

C combina tipado **estático y relativamente fuerte** (aunque con más
conversiones implícitas "peligrosas" entre tipos numéricos de las que un
purista consideraría deseable — lo vas a ver en 2.C con las conversiones de
tipo). Python combina tipado **dinámico y fuerte** (no vas a poder sumar
`"5" + 5` sin una conversión explícita, a diferencia de JavaScript).

## El proceso de compilación, enlazado y ejecución

Cuando compilás un programa en C con un comando como `gcc programa.c -o
programa`, en realidad ocurren varias etapas encadenadas, aunque `gcc` las
oculte detrás de un solo comando:

```
programa.c  →  [preprocesador]  →  [compilador]  →  [ensamblador]  →  programa.o  →  [enlazador (linker)]  →  programa
(programa       (expande #include,    (traduce C a      (traduce a          (programa      (une con librerías,       (programa
 fuente)         #define, etc.)        assembly)         binario)            objeto)         resuelve símbolos)         ejecutable)
```

1. **Preprocesamiento**: el preprocesador procesa las directivas que
   empiezan con `#` (`#include`, `#define`, etc.), literalmente
   copiando/pegando y sustituyendo texto **antes** de que el compilador vea
   una sola línea de C real. Se ve en detalle en 2.B.
2. **Compilación**: el compilador traduce el código C (ya preprocesado) a
   código ensamblador (assembly) equivalente, y verifica errores de sintaxis
   y de tipos.
3. **Ensamblado**: el ensamblador traduce el assembly a **código objeto**
   (binario, pero todavía no ejecutable) — un archivo `.o`. Este archivo
   contiene el código máquina de *ese* archivo fuente, pero tiene
   "huecos" donde se referencian funciones o variables definidas en otros
   archivos (por ejemplo, `printf`, que vive en la librería estándar).
4. **Enlazado (linking)**: el **enlazador (linker)** toma uno o más
   archivos objeto (`.o`) y los combina con las librerías necesarias
   (por ejemplo, la librería estándar de C, `libc`, que contiene la
   implementación real de `printf`), resolviendo todas las referencias
   pendientes y produciendo el **programa ejecutable** final.

Esto explica por qué un proyecto en C con varios archivos `.c` se compila
en dos pasos conceptuales: primero cada `.c` se convierte en su `.o`
(compilación independiente, en paralelo si querés), y después el linker los
junta a todos en un único ejecutable. Un error de "undefined reference" al
compilar significa específicamente que **falló el enlazado**: el compilador
entendió tu código, pero el linker no encontró en ningún lado la
implementación de algo que usaste (típicamente, olvidarte de compilar o
linkear un archivo `.c`, o de un `-lm` para usar funciones de `math.h`).

## Entornos Integrados de Desarrollo (IDE)

Un **IDE** (Integrated Development Environment) agrupa en una sola
aplicación las herramientas que un programador usa constantemente: editor de
texto, compilador/intérprete integrado, depurador y gestión de proyecto.
Alternativa a usar un editor de texto plano + terminal por separado.

IDEs/editores más usados hoy:

- **Visual Studio Code (VS Code)**: editor extensible, liviano, gratuito.
  No es un IDE "puro" de fábrica, pero con extensiones (C/C++, Python,
  debugger) se comporta como uno. Es el que vamos a usar en este curso.
- **CLion / Visual Studio (IDE completo de Microsoft)**: IDEs completos
  para C/C++, más pesados, con más funcionalidad "de fábrica".
- **PyCharm**: IDE especializado en Python.
- **Entornos en la nube** (GitHub Codespaces, Replit, etc.): el IDE corre en
  un servidor remoto, accedido desde el navegador — no requieren instalar
  nada localmente.

Funcionalidades básicas que vas a usar todo el curso:

- **Resaltado de sintaxis (syntax highlighting)**: colorea el código según
  su rol gramatical (palabras clave, tipos, strings, comentarios), ayuda a
  detectar errores a simple vista y a leer más rápido.
- **Navegación de código**: "ir a la definición" de una función o variable,
  buscar todos los usos de un símbolo, autocompletado.
- **Depuración (debugging)**: ejecutar el programa paso a paso (una
  instrucción a la vez), poner **breakpoints** (puntos donde la ejecución se
  detiene), inspeccionar el valor de las variables en ese momento, y ver la
  **traza de llamadas (call stack)** — qué función llamó a qué función para
  llegar hasta donde estás. Es la herramienta más importante para encontrar
  errores lógicos (cuando el programa compila y corre, pero da un resultado
  incorrecto). La vamos a usar en profundidad a partir de la Unidad 2.D.

## ⚠️ Cuidado

- "Compilado" no significa "sin errores en tiempo de ejecución". El
  compilador solo detecta errores de sintaxis y de tipos; errores lógicos
  (dividir por cero, acceder fuera de un arreglo, usar una variable sin
  inicializar) pueden compilar perfectamente y fallar — o peor, dar un
  resultado incorrecto sin fallar — recién al ejecutar.
- No confundir *lenguaje* con *implementación*. "C" es una especificación
  (un estándar, como C11 o C17); `gcc` y `clang` son dos compiladores
  distintos que implementan esa especificación. Pueden diferir en detalles
  no cubiertos por el estándar.

## Autoevaluación

1. ¿Por qué se dice que C es un lenguaje de "nivel medio"?
2. Dado un error de compilación que dice `undefined reference to 'foo'`,
   ¿en qué etapa del proceso (preprocesamiento, compilación, ensamblado,
   enlazado) ocurrió, y qué tipo de problema sugiere?
3. Explicá con tus palabras la diferencia entre tipado estático/dinámico y
   fuerte/débil, y ubicá a C y Python en esos dos ejes.
4. ¿Qué ventaja de iteración (ciclo de desarrollo) tiene un lenguaje
   interpretado sobre uno compilado, y qué ventaja de rendimiento tiene el
   compilado a cambio?
