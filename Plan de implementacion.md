# Plan de Implementación: CourseraClone - Fase Cliente-Servidor

## Información General del Proyecto

**Duración Total:** 3 Semanas  
**Objetivo General:** Evolucionar el sistema CourseraClone hacia una arquitectura cliente-servidor con nuevas estructuras de datos y funcionalidades avanzadas, implementando un único ejecutable con capacidad de actuar como cliente o servidor.

### Principios Clave
- **Un Único Ejecutable:** Inicio en modo cliente o servidor mediante argumentos
- **Servidor como Cerebro:** Maneja archivos, estructuras de datos complejas (AVL, Grafo, HashMap, etc.) y lógica de negocio
- **Cliente Ligero:** Solicita operaciones y presenta datos
- **Protocolo de Red Simple y Evolutivo:** Basado en texto inicialmente, expandible
- **Desarrollo Iterativo:** Funcionalidades y estructuras se integran progresivamente
- **Arquitectura Modular:** Separación clara de responsabilidades (Red, Lógica de Peticiones, Lógica de Negocio)

### Asignación de Responsabilidades por Estructuras de Datos
- **Santi:** `BinaryHeap`, `PriorityQueue` (mejorado)
- **Mauricio:** `BST` (Árbol Binario de Búsqueda), `HashMap`
- **Jahat:** `AVLTree`, `Graph`

---

## SEMANA 1: Red Mínima Indispensable, Estructuras Base y Utilidades Arquitectónicas

### 🎯 Objetivos Principales
1. Establecer conectividad de red básica (PING/PONG funcional)
2. Implementar modo dual de inicio del programa (`-server`, `-client`)
3. Adaptar `Controladora` para ser consciente del modo de operación
4. Crear implementación base de todas las estructuras de datos
5. Implementar `Logger` y `ConfigManager` básicos

### 📋 Tareas Detalladas

#### 1. Networking y Arquitectura Base

| Tarea | Responsable | Estado | Descripción |
|-------|-------------|---------|-------------|
| Modificar `main.cpp` para argumentos de inicio | Jahat | [En proceso] | Flags `-server [puerto_servidor]`, `-client <ip> [puerto_servidor]`. Integrar `ConfigManager` |
| `NetworkManagerServer.h/.cpp` | Jahat | [ ] | Winsock TCP: `iniciarServidor`, `aceptarCliente`, `recibirDatos`, `enviarDatos`. Bucle de escucha básico |
| `NetworkManagerClient.h/.cpp` | Mauricio | [ ] | Winsock TCP: `conectarAServidor`, `enviarDatos`, `recibirDatos`, `desconectar` |
| `RequestHandler.h/.cpp` (Esqueleto) | Jahat | [ ] | Clase para parsear futuras peticiones y delegar. Inicialmente solo para PING |
| Protocolo PING/PONG | Santi | [ ] | Definir e implementar. `RequestHandler` lo procesa |
| Adaptar `Controladora` | Santi | [ ] | Atributos `isServerMode`, `netClient`. Carga de datos solo en modo servidor |
| `ConfigManager.h/.cpp` (Básico) | Jahat | [ ] | Cargar IP/puerto por defecto, nombres de archivos de datos |
| `Logger.h/.cpp` (Básico) | Santi | [ ] | Funciones estáticas `Logger::logInfo(msg)`, `Logger::logError(msg)`. Salida a consola |
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
| Comentarios Doxygen en estructuras | Todos | [ ] |
| Uso básico de `Logger` y `ConfigManager` | Jahat/Santi | [ ] |

### 🎁 Entregable Semana 1
Aplicación que inicia en modo cliente o servidor con comunicación PING/PONG funcional, clases base de estructuras de datos implementadas, y `Logger` y `ConfigManager` básicos integrados.

---

## SEMANA 2: Desarrollo Intensivo de Funcionalidades en el Servidor y Expansión del Protocolo

### 🎯 Objetivos Principales
1. Servidor implementa lógica de negocio usando las estructuras de datos y accede a archivos
2. Cliente realiza operaciones básicas (Login, Registro, ver listas) interactuando con el servidor
3. Protocolo de red expandido y formalizado
4. Integración de validación de entradas básicas en el servidor

### 📋 Tareas Detalladas

#### 1. Sistema de Autenticación

##### Login y Registro (Cliente-Servidor)
| Componente | Responsable | Tarea | Estado |
|------------|-------------|-------|---------|
| Servidor | Jahat + Mauricio | `RequestHandler` maneja `LOGIN`, `REGISTER`. Usar `Logger`, `InputValidation` | [ ] |
| Cliente | Santi + Mauricio | Pantallas usan `netClient` para solicitudes. Procesar respuestas | [ ] |
| Protocolo | Todos | Definir mensajes, respuestas (éxito/error), formato de datos de usuario | [ ] |

#### 2. Gestión de Cursos y Especializaciones

##### Servidor
| Funcionalidad | Responsable | Estructura Usada | Descripción | Estado |
|---------------|-------------|------------------|-------------|---------|
| Cargar datos de `actividades.txt` | Mauricio | `HashMap` | `GestionadorCursos` (servidor) carga todo en memoria | [ ] |
| Landing Page (cursos populares) | Santi + Jahat | `PriorityQueue` | Comando `GET_LANDING_DATA`. Servidor selecciona N más populares | [ ] |
| Acceso rápido por ID | Mauricio | `HashMap` | Para `GestionadorCursos` (servidor) | [ ] |
| Verificar duplicados en creación | Jahat | `AVLTree` (títulos) | Comando `CREATE_COURSE`. Servidor valida y guarda | [ ] |
| Explorar con filtros básicos | Mauricio + Jahat | `HashMap`, `std::sort` | Comando `GET_COURSES [sort_by_enrollment=desc]`. Servidor filtra/ordena | [ ] |

##### Cliente
| Pantalla | Responsable | Comando Servidor | Estado |
|----------|-------------|------------------|---------|
| Landing Page | Santi | `GET_LANDING_DATA` | [ ] |
| Crear Curso | Santi | `CREATE_COURSE` | [ ] |
| Explorar | Santi | `GET_COURSES`, `GET_SPECS` | [ ] |

#### 3. Sistema de Inscripciones

| Componente | Responsable | Descripción | Estado |
|------------|-------------|-------------|---------|
| Servidor | Mauricio | `HashMap` para gestionar `inscripciones.dat`. Maneja comando `INSCRIBE` | [ ] |
| Cliente Dashboard | Santi | `DashboardEstudiante` solicita `GET_MY_INSCRIPTIONS` | [ ] |
| Lógica Inscripción | Mauricio + Jahat | `Estudiante::inscribirseA*` envía comando `INSCRIBE` | [ ] |

#### 4. Sistema de Recomendaciones (Base)

| Componente | Responsable | Descripción | Estado |
|------------|-------------|-------------|---------|
| Servidor | Jahat | `Graph` con cursos y especializaciones. Comando `GET_RECOMMENDATIONS_FOR_SPEC <id_esp>` | [ ] |
| Cliente | Santi | `MostrarEspecialidad` muestra recomendaciones | [ ] |

#### 5. Mejoras Arquitectónicas y Documentación

| Tarea | Responsable | Descripción | Estado |
|-------|-------------|-------------|---------|
| `InputValidation.h/.cpp` (Básico) | Jahat | Funciones para validar IDs, emails, strings no vacíos. Usar en `RequestHandler` | [ ] |
| Definición de Serialización/DTOs (Conceptual) | Todos | Acordar cómo se envían objetos complejos (Curso, Usuario) | [ ] |
| Expandir documento de protocolo | Todos | Incluir nuevos comandos, parámetros, formatos de respuesta | [ ] |
| Uso de `Logger` en capa de red y servidor | Todos | Implementar logs en puntos críticos | [ ] |

### 🎁 Entregable Semana 2
Sistema cliente-servidor con autenticación, visualización, creación, inscripciones básicas y recomendaciones básicas operativas, utilizando las estructuras de datos implementadas.

---

## SEMANA 3: Funcionalidades Completas, UI Cliente Robusta y Pruebas Exhaustivas

### 🎯 Objetivos Principales
1. Sistema completo y robusto con todas las funcionalidades
2. Recomendaciones y filtros avanzados implementados
3. Pruebas integrales del sistema completo
4. Documentación final completa

### 📋 Tareas Detalladas

#### 1. Funcionalidades Avanzadas del Servidor

| Funcionalidad | Responsable | Descripción | Estado |
|---------------|-------------|-------------|---------|
| Recomendaciones sofisticadas | Jahat | Expandir `Graph` con algoritmos de búsqueda. Nuevos comandos `GET_ADV_RECS` | [ ] |
| Filtros avanzados | Mauricio | Múltiples criterios para exploración. Lógica compleja de filtrado/ordenamiento | [ ] |

#### 2. UI Cliente Completa

| Aspecto | Responsable | Descripción | Estado |
|---------|-------------|-------------|---------|
| Todas las pantallas | Santi (líder) + Mauricio + Jahat | Interacción fluida con servidor en toda la UI | [ ] |
| Estados de carga y errores | Santi | Manejo adecuado de respuestas del servidor con feedback visual | [ ] |

#### 3. Integridad y Validaciones

| Aspecto | Responsable | Descripción | Estado |
|---------|-------------|-------------|---------|
| IDs únicos y validaciones | Todos | Revisar integridad en servidor con generación robusta de IDs | [ ] |
| Manejo de errores robusto | Todos | Mejorar manejo de excepciones y errores de red | [ ] |

#### 4. Pruebas Exhaustivas

| Tipo de Prueba | Responsable | Descripción | Estado |
|----------------|-------------|-------------|---------|
| Pruebas unitarias | Cada miembro | Para estructuras y lógica específica | [ ] |
| Pruebas de integración | Equipos de 2 | Cliente-servidor por funcionalidad | [ ] |
| Pruebas con múltiples clientes | Todos | Simular conexiones concurrentes | [ ] |
| Casos borde y errores | Todos | Entradas inválidas, desconexiones simuladas | [ ] |

#### 5. Documentación Final

| Documento | Responsable | Descripción | Estado |
|-----------|-------------|-------------|---------|
| Estructuras de datos | Cada miembro | Comentarios Doxygen finales | [ ] |
| Protocolo cliente-servidor | Santi o Jahat | Documento completo del protocolo | [ ] |
| README.md | Mauricio | Instrucciones de compilación, configuración y ejecución | [ ] |
| Arquitectura del sistema | Jahat | Descripción y diagrama de clases actualizado | [ ] |

### 🎁 Entregable Semana 3
Sistema cliente-servidor robusto, funcional y bien documentado que cumple todos los requisitos del proyecto.

---

## 📊 Metodología de Seguimiento

### Reuniones Diarias (Stand-ups)
- **Formato:** Cortas y enfocadas (10 minutos máximo)
- **Contenido:** Progreso, próximos pasos, bloqueos
- **Duración:** 10-15 minutos

### Control de Versiones (Git)
- **Commits:** Frecuentes y descriptivos
- **Ramas:** Por funcionalidad (`feature/login`, `feature/recommendations`)
- **Merges:** Con revisión de código y pruebas

### Actualización del Plan
- **Frecuencia:** Cada 1-2 días
- **Contenido:** Estado de tareas, problemas encontrados
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

## 🚀 Consideraciones Arquitectónicas Adicionales (Futuras Mejoras)

- **Command Factory:** Para gestionar comandos si la cantidad crece significativamente
- **Repository Pattern:** Para desacoplar lógica de negocio del acceso a datos
- **Thread Pool:** Para manejo eficiente de múltiples clientes
- **Dependency Injection:** Para gestión avanzada de dependencias
- **Metrics y Performance Monitoring:** Para identificar cuellos de botella

*Documento actualizado para seguimiento del proyecto CourseraClone - Fase Cliente-Servidor*