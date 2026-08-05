# Cómo usar este material

## Compilar y ejecutar un ejemplo

Todos los ejemplos están en `ejemplos/unidad-2/` y `ejemplos/unidad-3/` como
archivos `.c` sueltos. Para compilar uno a mano:

```bash
gcc -Wall -Wextra -std=c11 -o bin/nombre ejemplos/unidad-2/nombre.c
./bin/nombre
```

O, más simple, usá el `Makefile` del repositorio para compilar **todos** los
ejemplos de una vez:

```bash
make        # compila todo a bin/
make clean  # borra los binarios compilados
```

Esto te va a dejar un ejecutable en `bin/` por cada `.c`, con el mismo
nombre (sin la extensión).

## ¿Por qué `-Wall -Wextra`?

Porque C te deja hacer cosas peligrosas sin avisarte por default. Con estos
flags el compilador te marca usos sospechosos (variables no inicializadas,
comparaciones raras, funciones sin prototipo, etc.) que de otra forma
compilan "silenciosamente" y fallan en tiempo de ejecución, a veces solo en
la computadora del docente y no en la tuya. Acostumbrate a compilar siempre
así, incluidos los TP.

## Entorno de trabajo

Vas a necesitar `gcc` (o `clang`) y `make` instalados. Si estás en:

- **Linux**: ya los tenés o se instalan con `sudo apt install build-essential`.
- **macOS**: instalá las Xcode Command Line Tools (`xcode-select --install`).
- **Windows**: usá WSL (Windows Subsystem for Linux) con Ubuntu y seguí las
  instrucciones de Linux adentro. Evitá compilar C nativamente en Windows
  para este curso — el comportamiento de algunas funciones difiere y no vas
  a poder comparar resultados con el resto de la clase.

Como IDE se recomienda **Visual Studio Code** con las extensiones
`C/C++` (de Microsoft) y `Code Runner` o la config de `launch.json` para
poder usar el depurador (breakpoints, inspección de variables, ejecución
paso a paso) — vas a necesitarlo desde la Unidad 2.D en adelante.

> La cátedra puede optar por un entorno en la nube (sin instalación local)
> para las primeras entregas. Si es así, te vamos a avisar por el canal
> oficial del curso. El código y los ejemplos de este repositorio funcionan
> igual en cualquiera de los dos casos.

## Cómo leer cada documento de `docs/`

Cada archivo sigue la misma estructura:

1. **Explicación conceptual** — la idea antes que la sintaxis.
2. **Sintaxis y ejemplos mínimos** — fragmentos cortos para fijar la idea.
3. **Ejemplo completo** — un programa compilable en `ejemplos/`, referenciado
   con su ruta.
4. **⚠️ Cuidado** — errores típicos y comportamiento indefinido a evitar.
5. **Autoevaluación** — preguntas para chequear que entendiste antes de
   avanzar al siguiente tema o encarar el TP.

No hace falta memorizar sintaxis: lo que se evalúa en los TP y en los
exámenes es que entiendas **qué hace** cada construcción y **por qué**, para
poder aplicarla a un problema nuevo.
