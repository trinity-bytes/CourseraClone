# Plan de Implementación: CourseraClone - Funcionalidades Core

## Información General del Proyecto

**Duración Total:** 3 Semanas  
**Objetivo General:** Implementar todas las funcionalidades core de CourseraClone usando estructuras de datos avanzadas, enfocándose en la lógica de negocio y experiencia de usuario.

### Principios Clave

- **Aplicación Monolítica:** Una sola aplicación de consola, sin componentes de red
- **Estructuras de Datos Avanzadas:** Uso extensivo de BST, AVL, HashMap, Graph, etc.
- **Funcionalidades Completas:** Sistema completo de gestión de cursos y especializaciones
- **Experiencia de Usuario Fluida:** Interfaces de consola pulidas y funcionales
- **Sin Conectividad:** Eliminación completa de lógica cliente-servidor

### Asignación de Responsabilidades Actualizada

- **Santi:** `BinaryHeap`, `PriorityQueue`, Landing Page, Explorar Cursos
- **Mauricio:** `BST`, `HashMap`, Sistema de Inscripciones, Dashboard Estudiante
- **Jahat:** `AVLTree`, `Graph`, Sistema de Recomendaciones, Gestión de Cursos

---

## SEMANA 1: Estructuras de Datos Core y Funcionalidades Base

### 🎯 Objetivos Principales

1. Implementar todas las estructuras de datos necesarias
2. Refactorizar [`Controladora`](CourseraClone/Controladora.h) para eliminar lógica de red
3. Completar funcionalidades básicas de navegación
4. Optimizar carga y gestión de datos

### 📋 Tareas Detalladas

#### 1. Limpieza del Código Base

| Tarea                     | Responsable | Estado | Descripción                                                        |
| ------------------------- | ----------- | ------ | ------------------------------------------------------------------ |
| Eliminar archivos de red  | Jahat       | [✅]   | Remover `NetworkManagerServer.h`, `RequestHandler.h`               |
| Limpiar main.cpp          | Jahat       | [✅]   | Eliminar argumentos de línea de comandos en `CourseraCloneApp.cpp` |
| Refactorizar Controladora | Santi       | [✅]   | Eliminar atributos de red, mantener solo lógica local              |
| Actualizar proyecto VS    | Jahat       | [✅]   | Remover archivos eliminados del proyecto Visual Studio             |

**Archivos a eliminar:**

- `CourseraClone/NetworkManagerServer.h`
- `CourseraClone/RequestHandler.h`
- `cliente_test.cpp` (archivo de prueba del cliente)

**Modificaciones necesarias:**

- `CourseraClone/CourseraCloneApp.cpp`: Simplificar main(), eliminar lógica de argumentos
- `CourseraClone/Controladora.h`: Remover atributos y métodos relacionados con red
- Actualizar `CourseraClone.vcxproj` y `CourseraClone.vcxproj.filters`

#### 2. Estructuras de Datos - Prioridad Alta

##### Santi - BinaryHeap y PriorityQueue

- **Funcionalidades:** `insertar`, `extraerMax/Min`, `peek`, `ordenar`
- **Uso:** Landing Page (cursos populares), ordenamiento por inscripciones
- **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

##### Mauricio - BST y HashMap

- **BST:** `insertar`, `buscar`, `eliminar`, recorridos in-order
- **HashMap:** `put`, `get`, `remove`, manejo de colisiones
- **Uso:** Búsquedas rápidas, índices de cursos/usuarios
- **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

##### Jahat - AVLTree y Graph

- **AVLTree:** `insertar` con rotaciones, `buscar`, `eliminar`
- **Graph:** `addNodo`, `addArista`, algoritmos de búsqueda
- **Uso:** Índices balanceados, sistema de recomendaciones
- **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

#### 3. Funcionalidades Base

| Funcionalidad            | Responsable | Estructura Usada             | Estado |
| ------------------------ | ----------- | ---------------------------- | ------ |
| Landing Page mejorada    | Santi       | `PriorityQueue`              | [ ]    |
| Explorar Cursos          | Santi       | `HashMap`, `BST`             | [ ]    |
| Dashboard Estudiante     | Mauricio    | `LinkedList`, `HashMap`      | [ ]    |
| Gestión de Inscripciones | Mauricio    | `HashMap`, archivos binarios | [ ]    |

---

## SEMANA 2: Funcionalidades Avanzadas y Sistema de Recomendaciones

### 🎯 Objetivos Principales

1. Sistema de recomendaciones con Graph
2. Filtros y búsquedas avanzadas
3. Gestión completa de cursos y especializaciones
4. Optimización de rendimiento

### 📋 Tareas Detalladas

#### 1. Sistema de Recomendaciones

| Componente                  | Responsable   | Descripción                                         | Estado |
| --------------------------- | ------------- | --------------------------------------------------- | ------ |
| Graph de Cursos             | Jahat         | Modelar relaciones entre cursos y especializaciones | [ ]    |
| Algoritmos de Recomendación | Jahat         | BFS/DFS para encontrar cursos relacionados          | [ ]    |
| Integración en UI           | Jahat + Santi | Mostrar recomendaciones en pantallas relevantes     | [ ]    |

#### 2. Gestión Avanzada de Cursos

| Funcionalidad                    | Responsable | Estructura                     | Estado |
| -------------------------------- | ----------- | ------------------------------ | ------ |
| Crear/Editar Cursos              | Jahat       | `AVLTree` para validación      | [ ]    |
| Búsqueda por múltiples criterios | Mauricio    | `HashMap` + filtros            | [ ]    |
| Ordenamiento dinámico            | Santi       | `PriorityQueue` personalizable | [ ]    |

#### 3. Dashboard Organizaciones

| Componente                | Responsable | Descripción                              | Estado |
| ------------------------- | ----------- | ---------------------------------------- | ------ |
| Gestión de Cursos Propios | Jahat       | CRUD completo de cursos                  | [ ]    |
| Estadísticas              | Mauricio    | Análisis de inscripciones usando BST     | [ ]    |
| Reportes                  | Santi       | Generación de reportes con PriorityQueue | [ ]    |

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

| Funcionalidad             | Responsable | Estado |
| ------------------------- | ----------- | ------ |
| Sistema de Calificaciones | Mauricio    | [ ]    |
| Progreso de Cursos        | Santi       | [ ]    |
| Exportar/Importar Datos   | Jahat       | [ ]    |

#### 3. Pulimiento de UI

| Pantalla            | Responsable   | Mejoras                                | Estado |
| ------------------- | ------------- | -------------------------------------- | ------ |
| Todas las pantallas | Santi (líder) | Consistencia visual, manejo de errores | [ ]    |
| Navegación fluida   | Mauricio      | Transiciones mejoradas                 | [ ]    |
| Validaciones        | Jahat         | Input validation robusto               | [ ]    |

### 🎁 Entregable Final

Sistema CourseraClone completo con todas las funcionalidades requeridas, usando estructuras de datos avanzadas y con interfaz de usuario pulida.
