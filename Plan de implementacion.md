# Plan de Implementación: CourseraClone - Fase Cliente-Servidor

## Información General del Proyecto

**Duración Total:** 3 Semanas  
**Objetivo General:** Evolucionar el sistema CourseraClone hacia una arquitectura cliente-servidor con nuevas estructuras de datos y funcionalidades avanzadas.

### Principios Clave
- **Un Único Ejecutable:** Inicio en modo cliente o servidor mediante argumentos
- **Servidor como Cerebro:** Maneja archivos, estructuras de datos complejas y lógica de negocio
- **Cliente Ligero:** Solicita operaciones y presenta datos
- **Protocolo de Red Simple y Evolutivo:** Basado en texto, expandible incrementalmente
- **Desarrollo Iterativo:** Funcionalidades se integran progresivamente

### Asignación de Responsabilidades por Estructuras de Datos
- **Santi:** `BinaryHeap`, `PriorityQueue` (mejorado)
- **Mauricio:** `BST` (Árbol Binario de Búsqueda), `HashMap`
- **Jahat:** `AVLTree`, `Graph`

---

## SEMANA 1: Fundamentos de Red y Estructuras Base

### 🎯 Objetivos Principales
1. Establecer conectividad de red básica (PING/PONG funcional)
2. Implementar modo dual de inicio del programa
3. Adaptar `Controladora` para ser consciente del modo de operación
4. Crear implementación base de todas las estructuras de datos

### 📋 Tareas Detalladas

#### 1. Networking y Arquitectura Base

| Tarea | Responsable | Estado | Descripción |
|-------|-------------|---------|-------------|
| Modificar `main.cpp` para argumentos de inicio | Jahat | [ ] | Implementar flags `-server`, `-client <ip> [puerto]` |
| `NetworkManagerServer.h/.cpp` | Jahat | [ ] | Winsock TCP: `iniciarServidor`, `aceptarCliente`, `recibirDatos`, `enviarDatos` |
| `NetworkManagerClient.h/.cpp` | Mauricio | [ ] | Winsock TCP: `conectarAServidor`, `enviarDatos`, `recibirDatos`, `desconectar` |
| Protocolo PING/PONG | Santi | [ ] | Definir e implementar protocolo básico de comunicación |
| Adaptar `Controladora` | Santi | [ ] | Agregar atributos `isServerMode`, `netClient`, `netServerInstance` |
| Pruebas de conexión básica | Todos | [ ] | Verificar funcionamiento PING/PONG |

#### 2. Implementación de Estructuras de Datos

##### Santi - BinaryHeap y PriorityQueue
- **Funcionalidades:** `insertar`, `extraerMax/Min`, `peek`
- **Pruebas:** Casos básicos, inserción múltiple, extracción
- **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

##### Mauricio - BST y HashMap
**BST (Árbol Binario de Búsqueda):**
- **Funcionalidades:** `insertar`, `buscar`, `eliminar` (opcional), recorridos
- **Pruebas:** Casos básicos, búsqueda existente/inexistente
- **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

**HashMap:**
- **Funcionalidades:** `put/insertar`, `get/buscar`, `remove/eliminar`, manejo de colisiones
- **Pruebas:** Inserción, búsqueda, actualización, eliminación, colisiones
- **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

##### Jahat - AVLTree y Graph
**AVLTree:**
- **Funcionalidades:** `insertar` (con rotaciones), `buscar`, `eliminar` (opcional)
- **Pruebas:** Inserción simple, rotaciones (RR, LL, RL, LR), búsqueda
- **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

**Graph (Lista de Adyacencia):**
- **Funcionalidades:** `addNodo`, `addArista`, `getNodosAdyacentes`
- **Pruebas:** Creación de nodos, adición de aristas, verificación de adyacencia
- **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

#### 3. Documentación Inicial

| Tarea | Responsable | Estado |
|-------|-------------|---------|
| Documento de protocolo de red (PING/PONG) | Santi | [ ] |
| Comentarios en código de estructuras | Todos | [ ] |

### 🎁 Entregable Semana 1
Esqueleto de aplicación cliente-servidor con comunicación básica y clases base de estructuras de datos implementadas.

---

## SEMANA 2: Desarrollo de Funcionalidades Core

### 🎯 Objetivos Principales
1. Servidor funcional con lógica de negocio usando nuevas estructuras
2. Cliente interactivo para operaciones básicas (Login, Registro, listas)
3. Protocolo expandido para soportar nuevas funcionalidades

### 📋 Tareas Detalladas

#### 1. Sistema de Autenticación

##### Login y Registro (Cliente-Servidor)
| Componente | Responsable | Tarea | Estado |
|------------|-------------|-------|---------|
| Servidor | Jahat + Mauricio | `NetworkManagerServer` maneja `LOGIN`, `REGISTER` | [ ] |
| Cliente | Santi + Mauricio | Pantallas usan `netClient` para solicitudes | [ ] |
| Protocolo | Todos | Definir mensajes y respuestas de autenticación | [ ] |

#### 2. Gestión de Cursos y Especializaciones

##### Servidor
| Funcionalidad | Responsable | Estructura Usada | Estado |
|---------------|-------------|------------------|---------|
| Cargar datos de `actividades.txt` | Mauricio | - | [ ] |
| Landing Page (cursos populares) | Santi + Jahat | `PriorityQueue` | [ ] |
| Acceso rápido por ID | Mauricio | `HashMap` | [ ] |
| Verificar duplicados en creación | Jahat | `AVLTree` | [ ] |
| Explorar con filtros básicos | Mauricio + Jahat | Múltiples | [ ] |

##### Cliente
| Pantalla | Responsable | Comando Servidor | Estado |
|----------|-------------|------------------|---------|
| Landing Page | Santi | `GET_LANDING_DATA` | [ ] |
| Crear Curso | Santi | `CREATE_COURSE` | [ ] |
| Explorar | Santi | `GET_COURSES` | [ ] |

#### 3. Sistema de Inscripciones

| Componente | Responsable | Descripción | Estado |
|------------|-------------|-------------|---------|
| Servidor | Mauricio | `HashMap` para gestionar `inscripciones.dat` | [ ] |
| Cliente Dashboard | Santi | `DashboardEstudiante` solicita inscripciones | [ ] |
| Lógica Inscripción | Mauricio + Jahat | `Estudiante::inscribirseA*` + comando `INSCRIBE` | [ ] |

#### 4. Sistema de Recomendaciones (Base)

| Componente | Responsable | Descripción | Estado |
|------------|-------------|-------------|---------|
| Servidor | Jahat | `Graph` con cursos y especializaciones | [ ] |
| Cliente | Santi | `MostrarEspecialidad` muestra recomendaciones | [ ] |

#### 5. Actualización de Documentación

| Tarea | Responsable | Estado |
|-------|-------------|---------|
| Expandir documento de protocolo | Todos | [ ] |

### 🎁 Entregable Semana 2
Sistema cliente-servidor con funcionalidades principales operativas: autenticación, visualización, creación, inscripciones básicas y recomendaciones básicas.

---

## SEMANA 3: Completar Sistema y Pruebas Exhaustivas

### 🎯 Objetivos Principales
1. Sistema completo y robusto con todas las funcionalidades
2. Recomendaciones y filtros avanzados implementados
3. Pruebas integrales del sistema completo
4. Documentación final completa

### 📋 Tareas Detalladas

#### 1. Funcionalidades Avanzadas del Servidor

| Funcionalidad | Responsable | Descripción | Estado |
|---------------|-------------|-------------|---------|
| Recomendaciones sofisticadas | Jahat | Expandir `Graph` con algoritmos de búsqueda | [ ] |
| Filtros avanzados | Mauricio | Múltiples criterios para exploración | [ ] |

#### 2. UI Cliente Completa

| Aspecto | Responsable | Descripción | Estado |
|---------|-------------|-------------|---------|
| Todas las pantallas | Santi (líder) + Mauricio + Jahat | Interacción fluida con servidor | [ ] |
| Estados de carga y errores | Santi | Manejo adecuado de respuestas del servidor | [ ] |

#### 3. Integridad y Validaciones

| Aspecto | Responsable | Descripción | Estado |
|---------|-------------|-------------|---------|
| IDs únicos y validaciones | Todos | Revisar integridad en sus módulos | [ ] |
| Manejo de errores robusto | Todos | Errores de red y lógicos | [ ] |

#### 4. Pruebas Exhaustivas

| Tipo de Prueba | Responsable | Descripción | Estado |
|----------------|-------------|-------------|---------|
| Pruebas unitarias | Cada miembro | Para su código específico | [ ] |
| Pruebas de integración | Equipos de 2 | Cliente-servidor por funcionalidad | [ ] |
| Pruebas con múltiples clientes | Todos | Simulados o reales | [ ] |
| Casos borde y errores | Todos | Escenarios extremos | [ ] |

#### 5. Documentación Final

| Documento | Responsable | Descripción | Estado |
|-----------|-------------|-------------|---------|
| Estructuras de datos | Cada miembro | Comentarios Doxygen para sus estructuras | [ ] |
| Protocolo cliente-servidor | Santi o Jahat | Documento completo del protocolo | [ ] |
| README.md | Mauricio | Instrucciones de compilación y ejecución | [ ] |
| Arquitectura del sistema | Jahat | Descripción y diagrama de clases | [ ] |

### 🎁 Entregable Semana 3
Sistema cliente-servidor robusto, funcional y bien documentado que cumple todos los requisitos del proyecto.

---

## 📊 Metodología de Seguimiento

### Reuniones Diarias (Stand-ups)
- **Formato:** Cortas y enfocadas
- **Contenido:** Progreso, próximos pasos, bloqueos
- **Duración:** 15-20 minutos máximo

### Control de Versiones (Git)
- **Commits:** Frecuentes y descriptivos
- **Ramas:** Por funcionalidad o semana
- **Merges:** Cuidadosos con revisión de código

### Actualización del Plan
- **Frecuencia:** Cada 1-2 días
- **Contenido:** Estado de tareas, notas, problemas encontrados
- **Responsabilidad:** Compartida entre todos

### Flexibilidad
- Preparados para reasignar tareas según impedimentos
- Ajustar prioridades según necesidades del proyecto
- Comunicación constante para resolver bloqueos

---

## ✅ Leyenda de Estados
- [ ] **Pendiente:** Tarea no iniciada
- [ ] **En Progreso:** Tarea en desarrollo
- [ ] **Completado:** Tarea finalizada y verificada

---

*Documento actualizado para seguimiento del proyecto CourseraClone - Fase Cliente-Servidor*