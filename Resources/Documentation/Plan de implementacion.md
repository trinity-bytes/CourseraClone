# Plan de Implementación: CourseraClone - Funcionalidades Core

## Información General del Proyecto

**Duración Total:** 3 Semanas  
**Objetivo General:** Implementar todas las funcionalidades core de CourseraClone usando estructuras de datos avanzadas, enfocándose en la lógica de negocio y experiencia de usuario.

### Principios Clave

- **Aplicación Monolítica:** Una sola aplicación de consola, sin componentes de red ✅
- **Estructuras de Datos Avanzadas:** Uso extensivo de BST, HashMap, PriorityQueue, etc. ⏳
- **Funcionalidades Completas:** Sistema completo de gestión de cursos y especializaciones ⏳
- **Experiencia de Usuario Fluida:** Interfaces de consola pulidas y funcionales ⏳
- **Código Limpio:** Aplicación de guía de estilo y convenciones consistentes ⏳

### Estado Actual del Proyecto

- ✅ **Eliminación completa de lógica cliente-servidor**
- ✅ **Nueva estructura de carpetas Headers/ implementada**
- ✅ **Archivos base de estructuras de datos creados**
- ✅ **RESUELTO: Consolidación de archivos duplicados en Headers/Screens/**
- ⏳ **Implementación de estructuras de datos en progreso**
- ⏳ **Actualización de referencias en Controladora.h pendiente**
- ❌ **Funcionalidades avanzadas pendientes**

### Asignación de Responsabilidades Actualizada

- **Santi:** `BinaryHeap`, `PriorityQueue`, Landing Page, Explorar Cursos, **Consolidación Login/Registro**, Testing
- **Mauricio:** `BST`, `HashMap`, Sistema de Inscripciones, Dashboard Estudiante, **Consolidación Dashboards**
- **Jahat:** Algoritmos, `LinkedList`, auxiliares, **consolidación archivos restantes**, **actualización Controladora.h**

---

## SEMANA 1: Estructuras de Datos Core y Funcionalidades Base

### 🎯 Objetivos Principales

1. ✅ **Duplicación de archivos resuelta** - Desbloqueante completado
2. Implementar todas las estructuras de datos necesarias
3. Refactorizar [`Controladora`](CourseraClone/Controladora.h) para eliminar lógica de red ✅
4. **Actualizar referencias en Controladora.h** (nueva prioridad)
5. Completar funcionalidades básicas de navegación
6. Optimizar carga y gestión de datos

### 📋 Tareas Detalladas

#### 1. Limpieza del Código Base ✅ COMPLETADO

| Tarea                     | Responsable | Estado | Descripción                                                        |
| ------------------------- | ----------- | ------ | ------------------------------------------------------------------ |
| Eliminar archivos de red  | Jahat       | [✅]   | Remover `NetworkManagerServer.h`, `RequestHandler.h`               |
| Limpiar main.cpp          | Jahat       | [✅]   | Eliminar argumentos de línea de comandos en `CourseraCloneApp.cpp` |
| Refactorizar Controladora | Santi       | [✅]   | Eliminar atributos de red, mantener solo lógica local              |
| Actualizar proyecto VS    | Jahat       | [✅]   | Remover archivos eliminados del proyecto Visual Studio             |
| Reorganizar estructura    | Equipo      | [✅]   | Implementar nueva estructura de carpetas Headers/                  |

**✅ Archivos eliminados exitosamente:**

- ~~`CourseraClone/NetworkManagerServer.h`~~
- ~~`CourseraClone/RequestHandler.h`~~
- ~~`cliente_test.cpp`~~ (archivo de prueba del cliente)

**✅ Modificaciones completadas:**

- `CourseraClone/CourseraCloneApp.cpp`: Simplificado para aplicación monolítica
- `CourseraClone/Controladora.h`: Removidos atributos y métodos de red
- Proyecto VS actualizado con nueva estructura de carpetas
- **Nueva estructura Headers/** implementada y funcional

#### 2. Estructuras de Datos - Estado Actual

##### Santi - BinaryHeap y PriorityQueue

- **Archivos:** `BinaryHeap.h`, `PriorityQueue.h` ✅ Ya creados
- **Funcionalidades:** `insertar`, `extraerMax/Min`, `peek`, `ordenar`
- **Uso:** Landing Page (cursos populares), ordenamiento por inscripciones
- **Estado:** [✅] Archivos creados [⏳] Implementación [ ] Testing

##### Mauricio - BST y HashMap

- **Archivos:** `BinarySearchTree.h`, `HashTable.h`, `HashEntity.h` ✅ Ya creados
- **BST:** `insertar`, `buscar`, `eliminar`, recorridos in-order
- **HashMap:** `put`, `get`, `remove`, manejo de colisiones
- **Uso:** Búsquedas rápidas, índices de cursos/usuarios
- **Estado:** [✅] Archivos creados [⏳] Implementación [ ] Testing

##### Jahat - Algoritmos y Estructuras Auxiliares

- **Archivos:** `algoritmosBusqueda.h`, `algoritmosOrdenamiento.h` ✅ Ya creados
- **Adicionales:** `LinkedList.h`, `Queue.h`, `Stack.h`, `Nodo.h` ✅ Ya creados
- **Uso:** Algoritmos de búsqueda/ordenamiento, estructuras auxiliares
- **Estado:** [✅] Archivos creados [⏳] Implementación [ ] Testing

**📋 NOTA:** Los archivos de AVLTree y Graph aún no están creados y se necesitarán para funcionalidades avanzadas.

#### 3. Funcionalidades Base - Estado Actual

| Funcionalidad            | Responsable | Estructura Usada             | Archivos Disponibles                       | Estado |
| ------------------------ | ----------- | ---------------------------- | ------------------------------------------ | ------ |
| Landing Page mejorada    | Santi       | `PriorityQueue`              | `LandingPageScreen.h` ✅                   | [⏳]   |
| Explorar Cursos          | Santi       | `HashMap`, `BST`             | `ExplorarCursosYEspecialidadesScreen.h` ✅ | [⏳]   |
| Dashboard Estudiante     | Mauricio    | `LinkedList`, `HashMap`      | `DashboardEstudianteScreen.h` ✅           | [⏳]   |
| Dashboard Organización   | Mauricio    | `LinkedList`, `HashMap`      | `DashboardOrganizacionScreen.h` ✅         | [⏳]   |
| Login/Registro           | Equipo      | `HashMap`, archivos binarios | `LoginScreen.h`, `RegistroScreen.h` ✅     | [⏳]   |
| Gestión de Inscripciones | Mauricio    | `HashMap`, archivos binarios | Sistema de archivos ✅                     | [⏳]   |

**📋 NOTAS IMPORTANTES:**

- ✅ **RESUELTO: Duplicación de archivos en Headers/Screens/**
  - **Consolidación completada:** Archivos duplicados eliminados exitosamente
  - **Estructura limpia:** Solo archivos con nomenclatura correcta en Headers/Screens/
  - **Próximo paso:** Verificar y actualizar referencias en Controladora.h
- ⏳ **Migración pendiente:** Actualizar includes en el controlador principal
- **Prioridad ACTUAL:** Implementar estructuras de datos y funcionalidades core

#### 4. Consolidación de Archivos ✅ COMPLETADO

**✅ PROBLEMA RESUELTO:** Los archivos duplicados han sido consolidados exitosamente.

| Tarea                         | Responsable | Descripción                                    | Estado | Criticidad     |
| ----------------------------- | ----------- | ---------------------------------------------- | ------ | -------------- |
| Migrar Login/Registro         | Santi       | Consolidar `Login.h` → `LoginScreen.h`         | [✅]   | 🔴 ALTA        |
| Migrar Dashboards             | Mauricio    | Consolidar dashboards con sufijo "Screen"      | [✅]   | 🔴 ALTA        |
| Migrar Pantallas Restantes    | Jahat       | Aplicar convenciones a todas las pantallas     | [✅]   | 🟡 MEDIA       |
| Limpiar archivos obsoletos    | Equipo      | Eliminar versiones sin sufijo "Screen"         | [✅]   | 🟡 MEDIA       |
| **Actualizar Controladora.h** | **Equipo**  | **Corregir includes en controlador principal** | [✅]   | **🔴 CRÍTICA** |
| Testing post-consolidación    | Equipo      | Verificar que la aplicación compile y funcione | [⏳]   | 🔴 ALTA        |

**✅ Consolidación Completada:**

- Archivos duplicados eliminados exitosamente
- Estructura de Headers/Screens/ limpia y consistente
- Controladora.h con referencias correctas
- Sistema listo para continuar desarrollo

**⏳ PRÓXIMAS PRIORIDADES:**

1. **Testing de compilación** - Verificar que el proyecto compila sin errores
2. **Implementación de estructuras de datos** - BinaryHeap, PriorityQueue, BST, HashMap
3. **Funcionalidades básicas** - Navegación y interacción con datos

---

## SEMANA 2: Funcionalidades Avanzadas y Consolidación

### 🎯 Objetivos Principales

1. ✅ **Consolidación de archivos completada** - Desbloqueante resuelto
2. **Implementar funcionalidades core** de las estructuras de datos (nueva prioridad)
3. **Testing y optimización** del sistema base
4. **Sistema de recomendaciones** con Graph (si el tiempo lo permite)
5. **Optimización** de rendimiento básico

### 📋 Tareas Detalladas

#### 1. Testing y Validación (Nueva Prioridad Alta)

| Componente                | Responsable | Descripción                                      | Estado |
| ------------------------- | ----------- | ------------------------------------------------ | ------ |
| Testing de compilación    | Equipo      | Verificar que el proyecto compila sin errores    | [⏳]   |
| Testing de navegación     | Santi       | Verificar que todas las pantallas funcionan      | [⏳]   |
| Validación de includes    | Mauricio    | Confirmar que todos los includes están correctos | [⏳]   |
| Documentación actualizada | Jahat       | Actualizar documentos con nueva estructura       | [⏳]   |

#### 2. Implementación de Estructuras de Datos

| Funcionalidad              | Responsable | Estructura                           | Estado |
| -------------------------- | ----------- | ------------------------------------ | ------ |
| Completar BinaryHeap       | Santi       | `BinaryHeap.h` funcional             | [ ]    |
| Completar PriorityQueue    | Santi       | `PriorityQueue.h` funcional          | [ ]    |
| Completar BST              | Mauricio    | `BinarySearchTree.h` funcional       | [ ]    |
| Completar HashMap          | Mauricio    | `HashTable.h` + `HashEntity.h`       | [ ]    |
| Algoritmos de búsqueda     | Jahat       | `algoritmosBusqueda.h` funcional     | [ ]    |
| Algoritmos de ordenamiento | Jahat       | `algoritmosOrdenamiento.h` funcional | [ ]    |

#### 3. Sistema de Recomendaciones (Si el tiempo lo permite)

| Componente                  | Responsable | Descripción                                         | Estado |
| --------------------------- | ----------- | --------------------------------------------------- | ------ |
| Crear AVLTree.h             | Jahat       | Implementar AVL Tree con rotaciones                 | [ ]    |
| Crear Graph.h               | Jahat       | Modelar relaciones entre cursos y especializaciones | [ ]    |
| Algoritmos de Recomendación | Jahat       | BFS/DFS para encontrar cursos relacionados          | [ ]    |

---

## SEMANA 3: Pulimiento, Optimización y Documentación

### 🎯 Objetivos Principales

1. Sistema completo y robusto
2. Optimizaciones de rendimiento
3. Interfaces de usuario pulidas
4. Documentación completa

### 📋 Tareas Detalladas

#### 1. Optimizaciones y Rendimiento

| Aspecto                  | Responsable | Descripción                                                        | Estado |
| ------------------------ | ----------- | ------------------------------------------------------------------ | ------ |
| Carga eficiente de datos | Mauricio    | Optimizar [`GestionadorCursos`](CourseraClone/GestionadorCursos.h) | [ ]    |
| Búsquedas optimizadas    | Jahat       | AVL para búsquedas O(log n)                                        | [ ]    |
| Manejo de memoria        | Santi       | Optimizar PriorityQueue y BinaryHeap                               | [ ]    |

#### 2. Funcionalidades Faltantes

| Funcionalidad                  | Responsable | Descripción                                     | Estado |
| ------------------------------ | ----------- | ----------------------------------------------- | ------ |
| Sistema de Calificaciones      | Mauricio    | Gestión completa de calificaciones y notas      | [ ]    |
| Progreso de Cursos             | Santi       | Tracking del avance en cursos/especializaciones | [ ]    |
| Sistema de Certificados        | Jahat       | Generación y gestión de certificados            | [ ]    |
| Gestión de Boletas/Pagos       | Mauricio    | Sistema completo de transacciones               | [ ]    |
| Sistema de Reseñas             | Santi       | Calificación y comentarios de cursos            | [ ]    |
| Reportes y Estadísticas        | Jahat       | Dashboards con métricas detalladas              | [ ]    |
| Gestión de Archivos Multimedia | Equipo      | Manejo de recursos de cursos                    | [ ]    |
| Backup y Recuperación          | Santi       | Sistema de respaldo de datos                    | [ ]    |
| Exportar/Importar Datos        | Jahat       | Intercambio de datos con otros sistemas         | [ ]    |

#### 3. Pulimiento de UI

| Pantalla            | Responsable   | Mejoras                                | Estado |
| ------------------- | ------------- | -------------------------------------- | ------ |
| Todas las pantallas | Santi (líder) | Consistencia visual, manejo de errores | [ ]    |
| Navegación fluida   | Mauricio      | Transiciones mejoradas                 | [ ]    |
| Validaciones        | Jahat         | Input validation robusto               | [ ]    |

### 🎁 Entregable Final

Sistema CourseraClone completo con todas las funcionalidades requeridas, usando estructuras de datos avanzadas y con interfaz de usuario pulida.

---

## 📝 Historial de Actualizaciones

- **Mayo 28, 2025:** Creación inicial del plan
- **Mayo 29 - Junio 4, 2025:** Implementacion del codigo cliente/servidor
- **Junio 7, 2025:** Actualización post-eliminación de código cliente/servidor
  - ✅ Marcada como completada la limpieza de archivos de red
  - ✅ Actualizado estado de estructuras de datos (archivos creados)
  - 🆕 Agregada tarea de consolidación de archivos duplicados
  - 🔄 Reajustadas prioridades para SEMANA 2
  - 📊 Actualizado estado general del proyecto
- **Junio 7, 2025 (Tarde):** Resolución crítica de archivos duplicados
  - ✅ **COMPLETADO:** Consolidación de 13 pares de archivos duplicados en Headers/Screens/
  - ✅ **VERIFICADO:** Referencias en Controladora.h están correctas
  - 🔄 **REAJUSTE:** Prioridades actualizadas - enfoque en estructuras de datos
  - 🚀 **DESBLOQUEADO:** Desarrollo puede continuar sin restricciones

**Nota:** Este documento está en constante evolución debido a las iteraciones que hacemos en el proyecto.
