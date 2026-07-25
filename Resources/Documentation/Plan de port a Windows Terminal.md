# Port a Windows Terminal

Rama: `port-windows-terminal`

## Por qué el programa solo servía en el `cmd` viejo

La UI dependía de cuatro APIs de conhost que **Windows Terminal ignora por completo**:

| API legacy | Para qué se usaba | Qué pasa en Windows Terminal |
| --- | --- | --- |
| `SetConsoleScreenBufferInfoEx` (ColorTable) | Remapear los 16 índices de color a la paleta Coursera | Se ignora: los índices caen en el esquema del terminal |
| `SetCurrentConsoleFontEx` | Fijar Cascadia 22pt / Consolas 6pt para el QR | Se ignora: la fuente la manda el perfil del terminal |
| `SetConsoleScreenBufferSize` + `SetConsoleWindowInfo` | Forzar la ventana a 120x33 (y 300x120 para el QR) | Se ignora: la app no redimensiona la ventana |
| `SetConsoleTextAttribute` | Pintar cada celda | Funciona, pero con los colores del terminal, no con los nuestros |

El resultado en Windows Terminal era una UI con colores arbitrarios y layout desbordado.

## Estrategia

Reemplazar las APIs legacy por **secuencias VT (ANSI)**, que Windows Terminal sí respeta.
La clave del port es que el color y el posicionamiento ya estaban centralizados en
`ConsoleRenderer.hpp`: 469 llamadas de color y 382 de `gotoXY` en 20 pantallas se
migraron sin tocar ni una pantalla, solo cambiando la implementación por dentro.

## Fases

### Fase 1 — Proyecto nativo ✅

- `CourseraClone.vcxproj`: fuera `CLRSupport`, `TargetFrameworkVersion` y `Keyword=ManagedCProj`.
- El código no tenía ni una línea de C++/CLI: el `/clr` era peso muerto que además
  ataba el ejecutable a .NET Framework 4.7.2.
- Toolset v145 y C++17 sin cambios. Compila en Release x64.

### Fase 2 — Capa VT ✅

- **Nuevo** `Headers/Utils/ConsoleVT.hpp`: primitivas de terminal (modo VT, color RGB
  de 24 bits, cursor, pantalla alternativa, tamaño de ventana, restauración).
- `ColorPalette.hpp`: nueva tabla `PALETA_CONSOLA[16]` + `colorDeIndice()`. Los índices
  de `ColorIndex` ya no son ranuras del terminal, se resuelven a RGB real.
- `ConsoleRenderer.hpp`: `setConsoleColor` / `setTextColor` / `gotoXY` / `_configurarCursor`
  ahora emiten secuencias VT. Se agregó `limpiarPantalla()`.
- `ConsoleConfig.hpp`: `configurarConsola()` habilita VT, entra a la pantalla alternativa
  (`ESC[?1049h`), registra el `atexit` de restauración, pide el tamaño 120x33 de forma
  cooperativa (`ESC[8;33;120t`) y, si el terminal no coopera, espera con un aviso
  (`esperarTamanoMinimo()`).
- `system("cls")` (20 sitios) → `limpiarPantalla()`. `system("pause")` (3 sitios) → `pausar()`.
- `system("start <url>")` → `ShellExecuteA` (sin ventana de `cmd` parpadeando).
- `stdout` sin buffer: las secuencias VT y el texto comparten flujo y el orden importa.

**Detalles que valen la pena recordar:**

- El fondo claro ya no se pinta por remapeo del índice 0: se pinta borrando la pantalla
  con el fondo VT vigente. Por eso `limpiarPantalla()` hace `resetColor()` antes del `ESC[2J`.
- Los flags `intenseText` / `intenseBackground` quedaron sin efecto a propósito. Con la
  paleta legacy, el bit de intensidad saltaba a **otro índice** de la tabla (índice | 8),
  o sea que pintaba un color distinto al buscado. Con RGB de 24 bits el matiz ya viene
  resuelto en la paleta.
- `limpiarPantalla()` revalida el tamaño mínimo, así que si el usuario achica la ventana
  a mitad de sesión el aviso aparece en la siguiente pantalla.

### Fase 3 — Pantallas de QR ✅

`VerBoletasScreen` y `VerCertificadosScreen` mostraban el QR achicando la fuente a 6pt y
agrandando la ventana a 300x120, con un layout que ponía texto en `x=150` e `y=110`.

**El problema real, medido:** el payload es una URL autocontenida (todos los datos van en
base64 adentro de la URL, porque la web es estática en GitHub Pages y no consulta nada).
Para ~226 caracteres, el QR pide:

| Corrección | Módulos | Con borde, a 2 chars por módulo | Con medio bloque |
| --- | --- | --- | --- |
| ALTA (30%) | 81 | 170 x 85 | 85 x 43 |
| MEDIA-ALTA (25%) | 69 | 146 x 73 | 73 x 37 |
| MEDIA (15%) | 61 | 130 x 65 | 65 x 33 |
| BAJA (7%) | 53 | 114 x 57 | **57 x 29** ✅ |

**La solución — medio bloque.** Una celda de terminal mide aproximadamente el doble de
alto que de ancho. El carácter `▀` pinta la mitad superior con el color de texto y la
inferior con el de fondo, así que **una celda carga dos módulos verticales**: el QR usa
la mitad de filas y encima los módulos quedan cuadrados, que es lo que un lector necesita.

**Corrección adaptativa.** `QRCodeGenerator::generarAjustado(texto, columnas, filas)`
prueba los niveles de corrección de mayor a menor y se queda con el primero que entra en
el espacio disponible. Manda la terminal, no una constante: un payload corto (un
certificado, por ejemplo) recibe corrección ALTA automáticamente; uno largo baja a BAJA.
Si ni el nivel más bajo entra, la pantalla lo dice en vez de dibujar basura.

Se dibuja negro puro sobre blanco puro (`TEXTO_PRIMARIO` sobre `BLANCO_PURO`), no sobre el
gris del fondo: el contraste es lo que decide si un lector agarra el código.

**Verificación:** se reconstruyó la matriz de módulos desde el arte dibujado y se comparó
módulo a módulo contra `QrCode::getModule()`. Coinciden todos, con los tres patrones de
esquina en su lugar y la zona silenciosa completa.

Las dos pantallas se rediseñaron para 120x33: QR a la izquierda (58x29), panel de datos a
la derecha (x=63), título arriba y pie abajo. Se borraron `_configurarConsolaParaQR()` y
`_restaurarConsolaNormal()` de ambas clases.

### Fase 4 — Limpieza interna 🔲

Detectado durante el port, pendiente de decidir:

- 11 archivos fuente están en Windows-1252 y no en UTF-8 (warnings C4828). Uno de ellos,
  `Headers/Types/FilesTypes.hpp`, tiene bytes inválidos **dentro de un literal de cadena**
  (warning C4876), no solo en comentarios.
- Warnings C4715 (`not all control paths return a value`) en `Stack`, `LinkedList`.
- Warnings C4996 (`strncpy`, `localtime`) en `UsuarioTypes`, `InscripcionTypes`, `FilesManager`.
- El layout está anclado arriba a la izquierda. Si el terminal es más grande que 120x33,
  la UI queda pegada a una esquina en vez de centrada.
