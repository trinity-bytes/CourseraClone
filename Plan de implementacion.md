# Plan de Implementación: CourseraClone - Fase Cliente-Servidor y Nuevas Funcionalidades

**Duración Total Estimada:** 3 Semanas

**Objetivo General:** Evolucionar el sistema CourseraClone para que opere bajo una arquitectura cliente-servidor, donde un único ejecutable pueda actuar como cliente o servidor. Integrar nuevas estructuras de datos y funcionalidades requeridas, incluyendo gestión avanzada de cursos, especializaciones, inscripciones, sistema de recomendaciones y filtros mejorados.

**Principios Clave:**
*   **Un Único Ejecutable:** Inicio en modo cliente o servidor vía argumento.
*   **Servidor como Cerebro:** El servidor maneja archivos, estructuras de datos complejas y lógica de negocio.
*   **Cliente Ligero:** Solicita operaciones y presenta datos.
*   **Protocolo de Red Simple y Evolutivo:** Basado en texto, expandido incrementalmente.
*   **Desarrollo Iterativo:** Funcionalidades y estructuras se integran progresivamente.

**Asignación General de Responsabilidades (Estructuras de Datos):**
*   **Santi:** `BinaryHeap`, `PriorityQueue` (mejorado).
*   **Mauricio:** `BST` (Árbol Binario de Búsqueda), `HashMap`.
*   **Jahat:** `AVLTree`, `Graph`.

---

## Semana 1: Red Mínima Indispensable + Estructuras de Datos Base

**Objetivos Principales de la Semana:**
1.  **Conectividad de Red Básica:** Cliente se conecta a servidor, PING/PONG funcional.
2.  **Modo Dual de Inicio:** Programa se inicia como cliente o servidor (`-server`, `-client <ip>`).
3.  **`Controladora` Consciente del Modo:** `Controladora` sabe en qué modo opera.
4.  **Implementación Base de Estructuras de Datos:** Clases template definidas y con pruebas unitarias básicas.

**Tareas Detalladas y Responsables:**

### 1. Networking y Arquitectura Base
    *   **Tarea:** Modificar `main.cpp` para argumentos de inicio (`-server`, `-client <ip> [puerto]`).
        *   **Responsable:** (Definir, ej: Jahat)
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Implementar `NetworkManagerServer.h/.cpp` (Winsock TCP: `iniciarServidor`, `aceptarCliente`, `recibirDatos`, `enviarDatos`).
        *   **Responsable:** Jahat
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Implementar `NetworkManagerClient.h/.cpp` (Winsock TCP: `conectarAServidor`, `enviarDatos`, `recibirDatos`, `desconectar`).
        *   **Responsable:** Mauricio
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Definir y implementar protocolo PING/PONG.
        *   **Responsable:** Santi
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Adaptar `Controladora` (atributos `isServerMode`, `netClient`, `netServerInstance`; constructor modificado).
        *   **Responsable:** Santi
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Pruebas de conexión básica y PING/PONG.
        *   **Responsable:** Todos
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

### 2. Implementación Base de Estructuras de Datos
    *   **Tarea:** Template `BinaryHeap<T>` y `PriorityQueue<T>` (usando `BinaryHeap`).
        *   **Responsable:** Santi
        *   **Funcionalidades Clave:** `insertar`, `extraerMax/Min`, `peek`.
        *   **Pruebas Unitarias:** Casos básicos, inserción múltiple, extracción.
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Template `BST<T>` (Árbol Binario de Búsqueda).
        *   **Responsable:** Mauricio
        *   **Funcionalidades Clave:** `insertar`, `buscar`, `eliminar` (opcional si es complejo para inicio), recorridos.
        *   **Pruebas Unitarias:** Casos básicos, búsqueda de existente/inexistente.
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Template `HashMap<K, V>`.
        *   **Responsable:** Mauricio
        *   **Funcionalidades Clave:** `put/insertar`, `get/buscar`, `remove/eliminar`, manejo de colisiones (ej. encadenamiento).
        *   **Pruebas Unitarias:** Inserción, búsqueda, actualización, eliminación, manejo de colisiones.
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Template `AVLTree<T>`.
        *   **Responsable:** Jahat
        *   **Funcionalidades Clave:** `insertar` (con rotaciones para balanceo), `buscar`. `eliminar` (opcional si es complejo para inicio).
        *   **Pruebas Unitarias:** Inserción simple, inserciones que requieran rotaciones (RR, LL, RL, LR), búsqueda.
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Template `Graph<TNodeData>` (ej. Lista de Adyacencia).
        *   **Responsable:** Jahat
        *   **Funcionalidades Clave:** `addNodo`, `addArista` (dirigida/no dirigida), `getNodosAdyacentes`.
        *   **Pruebas Unitarias:** Creación de nodos, adición de aristas, verificación de adyacencia.
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

### 3. Documentación
    *   **Tarea:** Iniciar documento de protocolo de red (solo PING/PONG).
        *   **Responsable:** Santi
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Documentación básica (comentarios en código) para las estructuras de datos.
        *   **Responsable:** Todos
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

**Entregable Clave Semana 1:** Un esqueleto de aplicación cliente-servidor que puede comunicarse mínimamente, y las clases base de todas las estructuras de datos listas para ser integradas.

---

## Semana 2: Desarrollo Intensivo de Funcionalidades en el Servidor + Protocolo para Exponerlas

**Objetivos Principales de la Semana:**
1.  **Servidor Funcional:** El servidor implementa lógica de negocio usando las nuevas estructuras y accede a archivos.
2.  **Cliente Interactivo:** Cliente realiza operaciones básicas (Login, Registro, ver listas) vía red.
3.  **Protocolo Expandido:** Para soportar las nuevas funcionalidades.

**Tareas Detalladas y Responsables:**

### 1. Login y Registro (Cliente-Servidor)
    *   **Tarea (Servidor):** `NetworkManagerServer` maneja comandos `LOGIN`, `REGISTER`. Llama a `Usuario::login_local()`, `Usuario::guardar_local()`.
        *   **Responsable:** Jahat (Networking), Mauricio (Lógica `Usuario`)
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Cliente):** Pantallas `Login`, `Registro` usan `netClient` para enviar solicitudes y procesar respuestas.
        *   **Responsable:** Santi (UI), Mauricio (Lógica `Usuario` cliente)
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Protocolo):** Definir mensajes para `LOGIN`, `REGISTER` y sus respuestas (éxito/fallo, datos de usuario).
        *   **Responsable:** Todos
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

### 2. Gestión de Cursos y Especializaciones (Servidor y Cliente)
    *   **Tarea (Servidor):** `GestionadorCursos` carga datos de `actividades.txt`.
        *   **Responsable:** (Definir, ej: Mauricio)
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Servidor - Landing Page):** Usar `PriorityQueue` (Santi) para obtener N cursos/especializaciones populares. Comando `GET_LANDING_DATA`.
        *   **Responsable:** Santi (Lógica `PriorityQueue`), Jahat (Networking)
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Cliente - Landing Page):** Solicita y muestra datos de `GET_LANDING_DATA`.
        *   **Responsable:** Santi
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Servidor - Acceso Rápido):** Usar `HashMap` (Mauricio) para acceso por ID a `Curso*` y `Especializacion*`.
        *   **Responsable:** Mauricio
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Servidor - Crear Curso):** Usar `AVLTree` (Jahat) para verificar duplicados por título al recibir `CREATE_COURSE`.
        *   **Responsable:** Jahat (Lógica `AVLTree` y Networking)
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Cliente - Crear Curso):** UI para enviar `CREATE_COURSE`.
        *   **Responsable:** (Definir, ej: Santi)
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Servidor - Explorar):** Comando `GET_COURSES [sort_by_enrollment=desc]` (filtros básicos).
        *   **Responsable:** Mauricio (Lógica de filtrado), Jahat (Networking)
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Cliente - Explorar):** `ExplorarCursosYEspecialidades` solicita y muestra listas.
        *   **Responsable:** Santi
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

### 3. Gestión de Inscripciones (Servidor y Cliente)
    *   **Tarea (Servidor):** Usar `HashMap` (Mauricio) para cargar y gestionar inscripciones desde `inscripciones.dat`. Comando `GET_MY_INSCRIPTIONS`.
        *   **Responsable:** Mauricio
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Cliente):** `DashboardEstudiante` solicita sus inscripciones.
        *   **Responsable:** Santi
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Servidor y Cliente):** Lógica de `Estudiante::inscribirseACurso/Especializacion` envía comando `INSCRIBE` al servidor. Servidor actualiza archivos y estructuras.
        *   **Responsable:** Mauricio (Lógica `Estudiante`), Jahat (Networking)
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

### 4. Sistema de Recomendaciones (Base)
    *   **Tarea (Servidor):** `Graph` (Jahat) se puebla con cursos y sus relaciones con especializaciones. Comando `GET_RECOMMENDATIONS_FOR_SPECIALIZATION`.
        *   **Responsable:** Jahat
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Cliente):** `MostrarEspecialidad` solicita y muestra recomendaciones.
        *   **Responsable:** Santi
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

### 5. Documentación
    *   **Tarea:** Actualizar y expandir el documento de protocolo de red con todos los nuevos comandos.
        *   **Responsable:** Todos
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

**Entregable Clave Semana 2:** Un sistema donde las funcionalidades principales (login, registro, visualización de cursos/especializaciones, creación de cursos, inscripciones básicas, recomendaciones básicas) operan en el modelo cliente-servidor, con el servidor utilizando las nuevas estructuras de datos.

---

## Semana 3: Funcionalidades Completas, Recomendaciones Avanzadas, UI Cliente Robusta y Pruebas Exhaustivas

**Objetivos Principales de la Semana:**
1.  **Sistema Completo y Robusto:** Todas las funcionalidades requeridas operan de forma estable.
2.  **Recomendaciones y Filtros Avanzados:** Implementados y funcionales.
3.  **Pruebas Integrales:** Sistema probado exhaustivamente.
4.  **Documentación Final.**

**Tareas Detalladas y Responsables:**

### 1. Funcionalidades Avanzadas del Servidor
    *   **Tarea (Servidor - Recomendaciones):** Expandir `Graph` (Jahat) para recomendaciones más sofisticadas (cursos comunes entre especializaciones, etc.). Implementar algoritmos de búsqueda en grafos. Nuevos comandos `GET_ADVANCED_RECOMMENDATIONS`.
        *   **Responsable:** Jahat
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Servidor - Filtros):** Implementar filtros avanzados (múltiples criterios) para `ExplorarCursosYEspecialidades` (Mauricio).
        *   **Responsable:** Mauricio
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

### 2. UI Cliente y Flujos Completos
    *   **Tarea:** Asegurar que todas las pantallas (`MostrarCurso`, `DashboardEstudiante`, `DashboardOrganizacion`, `PerfilEstudiante`, `EditarPerfil`, etc.) interactúen fluidamente con el servidor para todas sus funcionalidades (incluyendo las avanzadas).
        *   **Responsable:** Santi (Lidera UI), con apoyo de Mauricio y Jahat para la lógica de datos específica.
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Manejo adecuado de estados de carga, mensajes de error/éxito del servidor en toda la UI.
        *   **Responsable:** Santi
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

### 3. Integridad, Validaciones y Manejo de Errores
    *   **Tarea (Servidor):** Asegurar IDs únicos para todas las entidades. Validar datos de entrada del cliente.
        *   **Responsable:** Todos (revisar sus módulos)
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Servidor y Cliente):** Implementar manejo robusto de errores de red y lógicos.
        *   **Responsable:** Todos
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

### 4. Pruebas Exhaustivas
    *   **Tarea:** Pruebas de unidad para toda la lógica nueva/modificada.
        *   **Responsable:** Cada miembro para su código.
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Pruebas de integración para cada funcionalidad cliente-servidor.
        *   **Responsable:** Equipos de 2 (ej. quien hizo el cliente de una feature + quien hizo el servidor).
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Pruebas con múltiples clientes (simulados o reales).
        *   **Responsable:** Todos
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Pruebas de casos borde y escenarios de error.
        *   **Responsable:** Todos
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

### 5. Documentación Final
    *   **Tarea:** Finalizar documentación de estructuras de datos (comentarios Doxygen, etc.).
        *   **Responsable:** Cada miembro para sus estructuras.
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Completar y pulir el documento de protocolo cliente-servidor.
        *   **Responsable:** (Definir, ej: Santi o Jahat)
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Crear `README.md` con instrucciones de compilación, ejecución (cliente/servidor), y descripción general.
        *   **Responsable:** (Definir, ej: Mauricio)
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Breve descripción de la arquitectura del sistema y diagrama de clases actualizado (conceptual).
        *   **Responsable:** (Definir, ej: Jahat)
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

**Entregable Clave Semana 3:** Un sistema cliente-servidor robusto, funcional y bien documentado que cumple con todos los requisitos del proyecto.

---

**Consideraciones Adicionales para el Seguimiento:**
*   **Reuniones Diarias (Stand-ups):** Cortas, para reportar progreso, próximos pasos y bloqueos.
*   **Control de Versiones (Git):** Commits frecuentes y descriptivos. Ramas por funcionalidad o semana. Merges cuidadosos.
*   **Actualización de este Documento:** Al final de cada día o cada dos días, actualizar el estado de las tareas. Añadir notas o problemas encontrados.
*   **Flexibilidad:** Estar preparados para reasignar tareas o ajustar prioridades si surgen impedimentos mayores.

Este formato Markdown debería ser fácil de mantener y les dará una visión clara del progreso. ¡Mucho éxito!