# Guía de Paleta de Colores Coursera - CourseraClone

## 🎨 Paleta de Colores Oficial

Esta paleta está basada en la **guía oficial de branding de Coursera** disponible en: https://about.coursera.org/brand-guide/

### ✨ Principios de Diseño

1. **Consistencia**: Uso coherente de los colores oficiales de Coursera
2. **Confianza**: Paleta profesional que transmite credibilidad
3. **Accesibilidad**: Contrastes optimizados para legibilidad
4. **Familiaridad**: Experiencia visual similar a la plataforma oficial

---

## 🔵 Colores Primarios de Marca

### Azul Coursera Oficial

- **Código**: `#0056D2` (RGB: 0, 86, 210)
- **Uso**: Botones principales, CTAs, elementos de navegación
- **Variable**: `Palette::AZUL_COURSERA`
- **Índice**: `ColorIndex::AZUL_MARCA`

### Negro Coursera Oficial

- **Código**: `#000000` (RGB: 0, 0, 0)
- **Uso**: Texto principal, títulos importantes
- **Variable**: `Palette::NEGRO_COURSERA`
- **Índice**: `ColorIndex::TEXTO_PRIMARIO` (mapeado a gris 900 para mejor UX)

### Blanco Coursera Oficial

- **Código**: `#FFFFFF` (RGB: 255, 255, 255)
- **Uso**: Fondos, texto sobre fondos oscuros
- **Variable**: `Palette::BLANCO_COURSERA`
- **Índice**: `ColorIndex::BLANCO_PURO`

---

## 🔄 Estados Interactivos

### Hover (Azul más oscuro)

- **Código**: `#0046B4` (RGB: 0, 70, 180)
- **Uso**: Estados hover de botones
- **Índice**: `ColorIndex::HOVER_ESTADO`

### Presionado (Azul muy oscuro)

- **Código**: `#003796` (RGB: 0, 55, 150)
- **Uso**: Estados activos/presionados
- **Índice**: `ColorIndex::PRESIONADO`

### Enlaces

- **Código**: `#1964DC` (RGB: 25, 100, 220)
- **Uso**: Enlaces interactivos, navegación
- **Índice**: `ColorIndex::LINK_COLOR`

---

## 📊 Jerarquía de Grises

Escala profesional de grises para crear jerarquía visual clara:

| Nivel        | Color     | RGB           | Uso Principal       |
| ------------ | --------- | ------------- | ------------------- |
| **Gris 900** | `#111111` | (17,17,17)    | Títulos principales |
| **Gris 800** | `#222222` | (34,34,34)    | Texto importante    |
| **Gris 700** | `#444444` | (68,68,68)    | Texto normal        |
| **Gris 600** | `#666666` | (102,102,102) | Texto secundario    |
| **Gris 500** | `#888888` | (136,136,136) | Texto deshabilitado |
| **Gris 400** | `#AAAAAA` | (170,170,170) | Bordes principales  |
| **Gris 300** | `#CCCCCC` | (204,204,204) | Bordes sutiles      |
| **Gris 200** | `#EEEEEE` | (238,238,238) | Fondos de sección   |
| **Gris 100** | `#F8F8F8` | (248,248,248) | Fondo general       |
| **Gris 50**  | `#FCFCFC` | (252,252,252) | Fondo alternativo   |

---

## 🚦 Colores de Estado (Semáforo UX)

### ✅ Éxito

- **Color**: `#228B22` (RGB: 34, 139, 34)
- **Uso**: Confirmaciones, completados, progreso exitoso
- **Índice**: `ColorIndex::EXITO_COLOR`

### ❌ Error

- **Color**: `#DC2626` (RGB: 220, 38, 38)
- **Uso**: Errores críticos, validaciones fallidas
- **Índice**: `ColorIndex::ERROR_COLOR`

### ⚠️ Atención

- **Color**: `#F59E0B` (RGB: 245, 158, 11)
- **Uso**: Advertencias, estados pendientes
- **Índice**: `ColorIndex::ATENCION_COLOR`

### ℹ️ Información

- **Color**: `#3B82F6` (RGB: 59, 130, 246)
- **Uso**: Información neutral, ayuda
- **Índice**: `ColorIndex::INFO_COLOR`

---

## 🛠️ Guía de Uso Práctica

### Funciones Básicas de Color

```cpp
// Configurar colores básicos
setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);

// Solo cambiar color de texto
setTextColor(ColorIndex::AZUL_MARCA);

// Restaurar colores por defecto
resetColor();
```

### Funciones de Mensajes

```cpp
// Mensajes con formato automático
mostrarError("Error de validación");
mostrarExito("Operación completada");
mostrarAdvertencia("Revisar datos");
mostrarInfo("Información adicional");
```

### Funciones Avanzadas de UI

```cpp
// Títulos y subtítulos
mostrarTituloPrincipal("Bienvenido a Coursera Clone", true);
mostrarSubtitulo("Panel de Control");
mostrarTextoAyuda("Selecciona una opción del menú");

// Elementos interactivos
mostrarBoton("Iniciar Sesión", false, true); // botón con hover
mostrarEnlace("¿Olvidaste tu contraseña?", true); // enlace subrayado
mostrarBadge("Premium", ColorIndex::AZUL_MARCA);

// Contenedores y separadores
crearCajaContenido("Contenido importante");
mostrarSeparadorElegante();
mostrarProgreso(75); // barra de progreso al 75%
```

---

## 📱 Compatibilidad con Código Existente

Para mantener compatibilidad con el código anterior, se mantienen los aliases:

```cpp
namespace Colors {
    constexpr int NORMAL = ColorIndex::TEXTO_PRIMARIO;
    constexpr int FONDO = ColorIndex::FONDO_PRINCIPAL;
    constexpr int SELECCION = ColorIndex::AZUL_MARCA;
    constexpr int ERRORES = ColorIndex::ERROR_COLOR;
    constexpr int EXITO = ColorIndex::EXITO_COLOR;
    constexpr int LINK = ColorIndex::LINK_COLOR;
    // ... más aliases
}
```

---

## 🎯 Mejores Prácticas

### ✅ Recomendado

- Usar `AZUL_MARCA` para CTAs principales
- Aplicar jerarquía de grises para texto
- Utilizar colores de estado para feedback
- Mantener consistencia en toda la aplicación

### ❌ Evitar

- Mezclar colores que no están en la paleta
- Usar colores saturados para texto extenso
- Combinar demasiados colores en una vista
- Ignorar contrastes de accesibilidad

---

## 🔧 Configuración Inicial

Para activar la nueva paleta en tu aplicación:

```cpp
#include "Headers/Utils/SystemUtils.hpp"

int main() {
    // Configuración completa de consola con nueva paleta
    configurarConsola();

    // Tu código aquí...

    return 0;
}
```

---

## 📐 Especificaciones Técnicas

- **Rango de colores**: 0-15 (limitación de consola Windows)
- **Formato RGB**: Valores 0-255 por canal
- **Compatibilidad**: Windows 10+ con soporte de color extendido
- **Fuente recomendada**: Cascadia Code Semibold (22pt)

---

_Esta paleta garantiza una experiencia visual profesional y coherente con la identidad de marca de Coursera, mejorando la usabilidad y la percepción de calidad del software._
