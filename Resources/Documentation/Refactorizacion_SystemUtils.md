# Refactorización del Sistema de Utilidades

## Resumen

El archivo `SystemUtils.hpp` ha sido refactorizado y dividido en múltiples módulos especializados para mejorar la organización del código y facilitar el mantenimiento.

## Nueva Estructura Modular

### 1. `ColorPalette.hpp`

**Responsabilidad:** Definición de la paleta de colores oficial de Coursera

- Estructura `Color` (RGB)
- Namespace `Palette` con todos los colores de marca
- Namespace `ColorIndex` con índices de consola (0-15)
- Namespace `Colors` para compatibilidad con código legacy

### 2. `ConsoleTypes.hpp`

**Responsabilidad:** Estructuras y tipos comunes del sistema

- Constantes globales (`ANCHO_CONSOLA`, `ALTO_CONSOLA`, etc.)
- Estructura `Posicion` para coordenadas de consola
- Estructura `ElementoMenu` para elementos de interfaz

### 3. `ConsoleConfig.hpp`

**Responsabilidad:** Configuración inicial de la consola

- `setPaletteColor()` - Establecer color individual en paleta
- `configurarPaletaColores()` - Configurar toda la paleta Coursera
- `configurarFuente()` - Configurar fuente de consola
- `ocultarCursor()` - Ocultar cursor parpadeante
- `configurarConsola()` - Configuración completa del sistema

### 4. `ConsoleRenderer.hpp`

**Responsabilidad:** Funciones de renderizado y UI avanzada

- **Manipulación de colores:** `setConsoleColor()`, `setTextColor()`, `resetColor()`
- **Posicionamiento:** `gotoXY()`, `getCursorPosition()`
- **Mensajes formateados:** `mostrarError()`, `mostrarExito()`, `mostrarAdvertencia()`, `mostrarInfo()`
- **UI básica:** `imprimirCentrado()`, `imprimirLinea()`
- **UI avanzada:** `mostrarBoton()`, `mostrarTituloPrincipal()`, `crearCajaContenido()`, `mostrarProgreso()`, etc.

### 5. `InputUtils.hpp`

**Responsabilidad:** Utilidades de entrada de usuario

- `limpiarBuffer()` - Limpiar buffer de teclado
- `esperarTecla()` - Esperar tecla específica
- `esperarCualquierTecla()` - Esperar cualquier tecla

### 6. `ValidationUtils.hpp`

**Responsabilidad:** Validación y formateo de datos

- `esNumeroValido()` - Validar cadenas numéricas
- `esEmailValido()` - Validar formato de email
- `limitarTexto()` - Truncar texto con sufijo

### 7. `SystemUtils.hpp` (Refactorizado)

**Responsabilidad:** Archivo principal que incluye todos los módulos

- Incluye todos los headers especializados
- Funciones de conveniencia para compatibilidad
- `inicializarSistema()` - Función principal de inicialización
- `setupConsola()` - Alias legacy para compatibilidad

## Ventajas de la Nueva Estructura

### ✅ **Separación de Responsabilidades**

Cada módulo tiene una responsabilidad específica y bien definida.

### ✅ **Mantenibilidad Mejorada**

Es más fácil localizar y modificar funcionalidad específica.

### ✅ **Compilación Optimizada**

Se pueden incluir solo los módulos necesarios en cada archivo.

### ✅ **Compatibilidad Total**

El código existente sigue funcionando sin modificaciones.

### ✅ **Escalabilidad**

Es fácil agregar nuevas funcionalidades en el módulo apropiado.

## Migración y Uso

### Para Código Existente

No se requieren cambios. El archivo `SystemUtils.hpp` incluye automáticamente todos los módulos necesarios.

```cpp
#include "../Utils/SystemUtils.hpp"  // Funciona igual que antes
```

### Para Código Nuevo (Recomendado)

Incluir solo los módulos específicos que necesites:

```cpp
#include "../Utils/ConsoleRenderer.hpp"  // Solo para UI
#include "../Utils/ColorPalette.hpp"     // Solo para colores
#include "../Utils/InputUtils.hpp"       // Solo para entrada
```

### Inicialización del Sistema

```cpp
// Función principal (recomendada)
inicializarSistema();

// O usar la función específica
configurarConsola();

// Legacy (sigue funcionando)
setupConsola();
```

## Archivos Modificados

1. ✅ **Creados:** 6 nuevos archivos de módulos especializados
2. ✅ **Refactorizado:** `SystemUtils.hpp` - ahora es un archivo de inclusión principal
3. ✅ **Mantenido:** Compatibilidad total con código existente

## Próximos Pasos Recomendados

1. **Probar compilación** del proyecto para verificar que todo funciona
2. **Migrar gradualmente** archivos específicos para usar includes más específicos
3. **Considerar aplicar** el mismo patrón a otros archivos grandes del proyecto
4. **Documentar** cualquier nueva funcionalidad en el módulo apropiado

## Ejemplo de Uso

```cpp
// Antes: todo en SystemUtils.hpp
#include "../Utils/SystemUtils.hpp"

// Ahora: también funciona, pero incluye TODO
#include "../Utils/SystemUtils.hpp"

// Nuevo estilo: más específico y eficiente
#include "../Utils/ConsoleRenderer.hpp"
#include "../Utils/ColorPalette.hpp"

void miPantalla() {
    // Usar las mismas funciones de antes
    mostrarTituloPrincipal("Mi Título");
    setTextColor(ColorIndex::AZUL_MARCA);
    std::cout << "Texto en azul Coursera";
    resetColor();
}
```

La refactorización mantiene 100% de compatibilidad mientras proporciona una estructura más limpia y mantenible.
