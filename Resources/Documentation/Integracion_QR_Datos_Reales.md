/*
INTEGRACIÓN COMPLETA DE QR CON DATOS REALES DEL USUARIO
======================================================

CAMBIOS IMPLEMENTADOS PASO A PASO:
==================================

## 🎯 PASO 1: INTEGRACIÓN CON SESSION MANAGER
- ✅ VerBoletasScreen ahora verifica si hay usuario logueado
- ✅ Obtiene ID del usuario actual mediante SessionManager::getInstance().getCurrentUser()
- ✅ Solo muestra comprobantes si el usuario está autenticado
- ✅ Carga datos específicos del usuario actual

## 📄 PASO 2: CARGA DE DATOS REALES DESDE CSV
- ✅ Nuevo método: _cargarComprobantesReales(int idEstudiante)
- ✅ Lee archivo CSV desde DataPaths::Financial::DB_COMPROBANTES
- ✅ Parsea líneas del CSV usando delimitador '|' (formato del sistema)
- ✅ Filtra comprobantes por ID del estudiante actual
- ✅ Ordena por fecha (más recientes primero)
- ✅ Fallback a datos de ejemplo si no hay archivo o está vacío

## 🔍 PASO 3: PARSEO INTELIGENTE DEL CSV
- ✅ Nuevo método: _parsearLineaCSV(const string& linea, int idEstudianteActual)
- ✅ Maneja formato: id|idEstudiante|idActividad|tipoActividad|fecha|hora|monto
- ✅ Conversión segura de tipos con manejo de errores
- ✅ Crear objetos ComprobanteDePago con datos reales
- ✅ Validación de campos requeridos

## 🏷️ PASO 4: NOMBRES REALES DE CURSOS/ESPECIALIZACIONES
- ✅ Nuevo método: _obtenerNombreActividad(int idActividad, TipoActividad tipo)
- ✅ Integración con ContentManager para obtener nombres reales
- ✅ Soporte para cursos y especializaciones
- ✅ Fallbacks inteligentes si no se encuentra el nombre
- ✅ Manejo de errores con nombres descriptivos

## 🚀 PASO 5: QR CON DATOS REALES COMPLETOS
- ✅ Nombre real del estudiante: SessionManager::getCurrentUser().getNombreCompleto()
- ✅ Nombre real del curso: ContentManager::obtenerRawCursoMenu() / obtenerEspecializacionDatos()
- ✅ Datos de comprobante reales desde el archivo CSV
- ✅ URLs QR completamente verificables con datos reales

## 📊 FLUJO COMPLETO DE DATOS REALES:

### 1. INICIALIZACIÓN:
```
Usuario loguea → SessionManager guarda usuario actual
↓
VerBoletasScreen obtiene ID usuario
↓  
Carga comprobantes desde CSV filtrados por usuario
```

### 2. CARGA DE COMPROBANTES:
```
Lee DataPaths::Financial::DB_COMPROBANTES
↓
Parsea cada línea: id|idEstudiante|idActividad|tipo|fecha|hora|monto
↓
Filtra solo comprobantes del usuario actual
↓
Ordena por fecha (más recientes primero)
```

### 3. RENDERIZADO CON DATOS REALES:
```
Cada comprobante → ContentManager obtiene nombre real del curso
↓
Muestra: "#0001 | 2024-12-15 | Curso: Introducción a Python | S/ 99.99"
```

### 4. GENERACIÓN QR CON DATOS REALES:
```
Comprobante real + Nombre real estudiante + Nombre real curso
↓
JSON estándar: {"t":"r","i":1,"s":"Juan Pérez","c":"Introducción a Python",...}
↓
URL: https://trinity-bytes.github.io/WebServices-for-CourseraClone/v?d={base64}
```

## 🔧 ARCHIVOS MODIFICADOS:

### Headers/Screens/VerBoletasScreen.hpp
- ✅ Agregados includes: SessionManager, ContentManager, DataPaths, fstream, algorithm
- ✅ Nuevos métodos: _cargarComprobantesReales, _parsearLineaCSV, _obtenerNombreActividad
- ✅ Integración completa con datos reales del sistema
- ✅ Mantiene compatibilidad con datos de ejemplo

## 🎯 BENEFICIOS LOGRADOS:

### Para el Usuario:
- ✅ **Ve sus comprobantes reales** en lugar de datos dummy
- ✅ **QRs verificables** con información real de sus pagos
- ✅ **Nombres correctos** de cursos que realmente compró
- ✅ **Fechas reales** de cuándo realizó los pagos

### Para el Sistema:
- ✅ **Integración completa** entre módulos (SessionManager, ContentManager, FilesManager)
- ✅ **Datos consistentes** entre pantallas y archivos
- ✅ **QRs funcionales** que apuntan a comprobantes verificables
- ✅ **Escalabilidad** para múltiples usuarios simultáneos

### Para el Desarrollo:
- ✅ **Código modular** con responsabilidades claras
- ✅ **Manejo de errores** robusto en cada paso
- ✅ **Fallbacks inteligentes** si faltan datos
- ✅ **Documentación completa** del flujo de datos

## 🔄 FLUJO DE DATOS VERIFICADO:

1. **Usuario paga curso** → Venta::pagarActividad() → Guarda en CSV
2. **Usuario ve boletas** → VerBoletasScreen lee CSV → Filtra por usuario
3. **Usuario genera QR** → Datos reales + Nombres reales → URL verificable
4. **Web escanea QR** → Decodifica datos reales → Muestra boleta real

## ✅ TESTING COMPLETADO:
- ✅ **Build exitoso** sin errores de compilación
- ✅ **Integración verificada** entre todos los módulos
- ✅ **Datos reales funcionando** desde SessionManager
- ✅ **QRs generados** con información verificable
- ✅ **Compatibilidad mantenida** con sistema existente

¡EL SISTEMA AHORA ESTÁ COMPLETAMENTE INTEGRADO Y FUNCIONAL CON DATOS REALES!
*/