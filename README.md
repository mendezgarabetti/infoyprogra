# Introducción a la Programación en C

Material completo de cátedra para aprender C desde cero hasta poder resolver
trabajos prácticos de desarrollo con estructuras de datos, punteros, memoria
dinámica e interacción con el sistema operativo.

Este repositorio cubre las **Unidades 2 y 3** del programa de la materia:

## Unidad 2 — Introducción a la programación

| Tema | Documento |
|---|---|
| 2.A Lenguajes y herramientas de programación | [docs/unidad-2/2A-lenguajes-y-herramientas.md](docs/unidad-2/2A-lenguajes-y-herramientas.md) |
| 2.B Introducción al lenguaje C | [docs/unidad-2/2B-introduccion-a-c.md](docs/unidad-2/2B-introduccion-a-c.md) |
| 2.C Tipos de datos, operadores, expresiones y sentencias | [docs/unidad-2/2C-tipos-operadores-expresiones.md](docs/unidad-2/2C-tipos-operadores-expresiones.md) |
| 2.D Control básico del flujo de ejecución | [docs/unidad-2/2D-control-de-flujo.md](docs/unidad-2/2D-control-de-flujo.md) |
| 2.E Subrutinas (funciones) | [docs/unidad-2/2E-subrutinas.md](docs/unidad-2/2E-subrutinas.md) |

## Unidad 3 — Estructuras de datos e interacción con el sistema operativo

| Tema | Documento |
|---|---|
| 3.A Estructuras de datos (arreglos, cadenas, structs) | [docs/unidad-3/3A-estructuras-de-datos.md](docs/unidad-3/3A-estructuras-de-datos.md) |
| 3.B Apuntadores y memoria dinámica | [docs/unidad-3/3B-apuntadores.md](docs/unidad-3/3B-apuntadores.md) |
| 3.C Interacción con el sistema operativo | [docs/unidad-3/3C-interaccion-sistema-operativo.md](docs/unidad-3/3C-interaccion-sistema-operativo.md) |

## Cómo está organizado el repositorio

```
.
├── docs/                   Material teórico, un archivo .md por tema
│   ├── unidad-2/
│   └── unidad-3/
├── ejemplos/               Código C compilable que acompaña cada tema
│   ├── unidad-2/
│   └── unidad-3/
├── bin/                    Binarios compilados (no se versiona)
└── Makefile                Compila todos los ejemplos
```

Cada documento de `docs/` tiene explicación en texto, ejemplos de código y,
al final, una sección de **autoevaluación** con preguntas para repasar antes
de encarar el trabajo práctico correspondiente. El código que aparece en los
documentos también está disponible como archivo `.c` compilable en
`ejemplos/`, referenciado al inicio de cada sección.

Antes de empezar, leé [docs/00-como-usar-este-material.md](docs/00-como-usar-este-material.md)
para saber cómo compilar y ejecutar los ejemplos.

## Orden de lectura sugerido

1. 2.A → 2.B → 2.C → 2.D → 2.E (fundamentos del lenguaje, en ese orden)
2. 3.A → 3.B (estructuras de datos y punteros — la base de casi todos los TP)
3. 3.C (interacción con el sistema operativo — más avanzado, hacia el final de la cursada)

## Convenciones usadas en este material

- Todo el código se compila con `gcc` usando los flags `-Wall -Wextra -std=c11`.
  Si tu código tira warnings con esos flags, corregilo antes de entregar el TP:
  la mayoría de los bugs típicos (variables sin inicializar, comparaciones con
  signo/sin signo, etc.) aparecen ahí.
- Los ejemplos están comentados en español y priorizan la claridad por sobre
  el estilo "profesional" — no es el código que escribirías en un proyecto
  real, es código pensado para que se entienda leyéndolo una vez.
- Cuando un tema tiene una trampa común (undefined behavior, fuga de memoria,
  etc.) hay un bloque **⚠️ Cuidado** explicándola.
