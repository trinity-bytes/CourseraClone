# Modificaciones del Sistema de Logs

## Resumen de Cambios

Se han modificado las funciones de logging en el `FilesManager` para que almacenen la información en archivos de texto en lugar de solo mostrar en consola.

## Archivos Modificados

### 1. FilesManager.hpp

- **Funciones modificadas:**

  - `logError()`: Ahora escribe en `Error_Logs.txt` con timestamp
  - `logInfo()`: Ahora escribe en `Info_Logs.txt` con timestamp

- **Funciones agregadas:**

  - `limpiarLogsAntiguos(int diasAntiguedad)`: Elimina logs antiguos
  - `obtenerEstadisticasLogs()`: Retorna estadísticas detalladas de logs
  - Modificada `mostrarEstadisticasArchivos()`: Incluye información de logs

- **Headers agregados:**
  - `<chrono>`: Para manejo de timestamps
  - `<iomanip>`: Para formateo de tiempo
  - `<sstream>`: Para std::stringstream

### 2. DataPaths.hpp

- **Corrección de bug:** Rutas de logs corregidas para usar `Logs::BASE`

## Funcionalidades Implementadas

### Logging con Timestamp

```cpp
// Formato de logs:
[2025-06-14 15:30:45] [ERROR] [Operación] Mensaje de error (Archivo: ruta)
[2025-06-14 15:30:45] [INFO] [Operación] Mensaje informativo
```

### Ubicación de Archivos de Log

- **Error Logs:** `Resources/Data/Logs/Error_Logs.txt`
- **Info Logs:** `Resources/Data/Logs/Info_Logs.txt`

### Gestión de Logs

- **Creación automática:** El directorio de logs se crea durante la inicialización
- **Limpieza automática:** Función para eliminar logs antiguos (por defecto 30 días)
- **Estadísticas:** Información sobre tamaño y última modificación de logs

## Características del Sistema

### Persistencia Dual

- Los logs se escriben tanto en archivo como en consola
- Garantiza feedback inmediato y persistencia de datos

### Manejo de Errores

- Si no se puede escribir en el archivo, continúa con el logging en consola
- No interrumpe el funcionamiento del sistema por problemas de logging

### Formato Consistente

- Timestamps en formato: `YYYY-MM-DD HH:MM:SS`
- Categorización por tipo: `[ERROR]` y `[INFO]`
- Identificación de operación y archivo involucrado

## Uso Recomendado

### Limpieza Periódica

```cpp
// Limpiar logs más antiguos de 30 días
FilesManager::getInstance().limpiarLogsAntiguos(30);
```

### Obtener Estadísticas

```cpp
// Ver estadísticas completas del sistema (incluye logs)
FilesManager::getInstance().mostrarEstadisticasArchivos();

// Solo estadísticas de logs
std::string stats = FilesManager::getInstance().obtenerEstadisticasLogs();
std::cout << stats;
```

## Beneficios

1. **Auditoría:** Historial completo de operaciones del sistema
2. **Debugging:** Facilita la identificación de problemas
3. **Monitoreo:** Seguimiento del uso del sistema
4. **Mantenimiento:** Limpieza automática de logs antiguos
5. **Análisis:** Estadísticas para optimización del sistema

## Notas Técnicas

- El sistema usa `std::chrono` para timestamps precisos
- Los archivos se abren en modo append (`std::ios::app`)
- Thread-safe gracias al patrón Singleton del FilesManager
- Compatible con el sistema de dominios organizados del proyecto
