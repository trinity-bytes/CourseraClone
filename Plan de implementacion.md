# Plan de Implementaci�n: CourseraClone - Fase Cliente-Servidor y Nuevas Funcionalidades

**Duraci�n Total Estimada:** 3 Semanas

**Objetivo General:** Evolucionar el sistema CourseraClone para que opere bajo una arquitectura cliente-servidor, donde un �nico ejecutable pueda actuar como cliente o servidor. Integrar nuevas estructuras de datos y funcionalidades requeridas, incluyendo gesti�n avanzada de cursos, especializaciones, inscripciones, sistema de recomendaciones y filtros mejorados.

**Principios Clave:**
*   **Un �nico Ejecutable:** Inicio en modo cliente o servidor v�a argumento.
*   **Servidor como Cerebro:** El servidor maneja archivos, estructuras de datos complejas y l�gica de negocio.
*   **Cliente Ligero:** Solicita operaciones y presenta datos.
*   **Protocolo de Red Simple y Evolutivo:** Basado en texto, expandido incrementalmente.
*   **Desarrollo Iterativo:** Funcionalidades y estructuras se integran progresivamente.

**Asignaci�n General de Responsabilidades (Estructuras de Datos):**
*   **Santi:** `BinaryHeap`, `PriorityQueue` (mejorado).
*   **Mauricio:** `BST` (�rbol Binario de B�squeda), `HashMap`.
*   **Jahat:** `AVLTree`, `Graph`.

---

## Semana 1: Red M�nima Indispensable + Estructuras de Datos Base

**Objetivos Principales de la Semana:**
1.  **Conectividad de Red B�sica:** Cliente se conecta a servidor, PING/PONG funcional.
2.  **Modo Dual de Inicio:** Programa se inicia como cliente o servidor (`-server`, `-client <ip>`).
3.  **`Controladora` Consciente del Modo:** `Controladora` sabe en qu� modo opera.
4.  **Implementaci�n Base de Estructuras de Datos:** Clases template definidas y con pruebas unitarias b�sicas.

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
    *   **Tarea:** Pruebas de conexi�n b�sica y PING/PONG.
        *   **Responsable:** Todos
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

### 2. Implementaci�n Base de Estructuras de Datos
    *   **Tarea:** Template `BinaryHeap<T>` y `PriorityQueue<T>` (usando `BinaryHeap`).
        *   **Responsable:** Santi
        *   **Funcionalidades Clave:** `insertar`, `extraerMax/Min`, `peek`.
        *   **Pruebas Unitarias:** Casos b�sicos, inserci�n m�ltiple, extracci�n.
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Template `BST<T>` (�rbol Binario de B�squeda).
        *   **Responsable:** Mauricio
        *   **Funcionalidades Clave:** `insertar`, `buscar`, `eliminar` (opcional si es complejo para inicio), recorridos.
        *   **Pruebas Unitarias:** Casos b�sicos, b�squeda de existente/inexistente.
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Template `HashMap<K, V>`.
        *   **Responsable:** Mauricio
        *   **Funcionalidades Clave:** `put/insertar`, `get/buscar`, `remove/eliminar`, manejo de colisiones (ej. encadenamiento).
        *   **Pruebas Unitarias:** Inserci�n, b�squeda, actualizaci�n, eliminaci�n, manejo de colisiones.
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Template `AVLTree<T>`.
        *   **Responsable:** Jahat
        *   **Funcionalidades Clave:** `insertar` (con rotaciones para balanceo), `buscar`. `eliminar` (opcional si es complejo para inicio).
        *   **Pruebas Unitarias:** Inserci�n simple, inserciones que requieran rotaciones (RR, LL, RL, LR), b�squeda.
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Template `Graph<TNodeData>` (ej. Lista de Adyacencia).
        *   **Responsable:** Jahat
        *   **Funcionalidades Clave:** `addNodo`, `addArista` (dirigida/no dirigida), `getNodosAdyacentes`.
        *   **Pruebas Unitarias:** Creaci�n de nodos, adici�n de aristas, verificaci�n de adyacencia.
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

### 3. Documentaci�n
    *   **Tarea:** Iniciar documento de protocolo de red (solo PING/PONG).
        *   **Responsable:** Santi
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Documentaci�n b�sica (comentarios en c�digo) para las estructuras de datos.
        *   **Responsable:** Todos
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

**Entregable Clave Semana 1:** Un esqueleto de aplicaci�n cliente-servidor que puede comunicarse m�nimamente, y las clases base de todas las estructuras de datos listas para ser integradas.

---

## Semana 2: Desarrollo Intensivo de Funcionalidades en el Servidor + Protocolo para Exponerlas

**Objetivos Principales de la Semana:**
1.  **Servidor Funcional:** El servidor implementa l�gica de negocio usando las nuevas estructuras y accede a archivos.
2.  **Cliente Interactivo:** Cliente realiza operaciones b�sicas (Login, Registro, ver listas) v�a red.
3.  **Protocolo Expandido:** Para soportar las nuevas funcionalidades.

**Tareas Detalladas y Responsables:**

### 1. Login y Registro (Cliente-Servidor)
    *   **Tarea (Servidor):** `NetworkManagerServer` maneja comandos `LOGIN`, `REGISTER`. Llama a `Usuario::login_local()`, `Usuario::guardar_local()`.
        *   **Responsable:** Jahat (Networking), Mauricio (L�gica `Usuario`)
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Cliente):** Pantallas `Login`, `Registro` usan `netClient` para enviar solicitudes y procesar respuestas.
        *   **Responsable:** Santi (UI), Mauricio (L�gica `Usuario` cliente)
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Protocolo):** Definir mensajes para `LOGIN`, `REGISTER` y sus respuestas (�xito/fallo, datos de usuario).
        *   **Responsable:** Todos
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

### 2. Gesti�n de Cursos y Especializaciones (Servidor y Cliente)
    *   **Tarea (Servidor):** `GestionadorCursos` carga datos de `actividades.txt`.
        *   **Responsable:** (Definir, ej: Mauricio)
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Servidor - Landing Page):** Usar `PriorityQueue` (Santi) para obtener N cursos/especializaciones populares. Comando `GET_LANDING_DATA`.
        *   **Responsable:** Santi (L�gica `PriorityQueue`), Jahat (Networking)
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Cliente - Landing Page):** Solicita y muestra datos de `GET_LANDING_DATA`.
        *   **Responsable:** Santi
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Servidor - Acceso R�pido):** Usar `HashMap` (Mauricio) para acceso por ID a `Curso*` y `Especializacion*`.
        *   **Responsable:** Mauricio
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Servidor - Crear Curso):** Usar `AVLTree` (Jahat) para verificar duplicados por t�tulo al recibir `CREATE_COURSE`.
        *   **Responsable:** Jahat (L�gica `AVLTree` y Networking)
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Cliente - Crear Curso):** UI para enviar `CREATE_COURSE`.
        *   **Responsable:** (Definir, ej: Santi)
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Servidor - Explorar):** Comando `GET_COURSES [sort_by_enrollment=desc]` (filtros b�sicos).
        *   **Responsable:** Mauricio (L�gica de filtrado), Jahat (Networking)
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Cliente - Explorar):** `ExplorarCursosYEspecialidades` solicita y muestra listas.
        *   **Responsable:** Santi
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

### 3. Gesti�n de Inscripciones (Servidor y Cliente)
    *   **Tarea (Servidor):** Usar `HashMap` (Mauricio) para cargar y gestionar inscripciones desde `inscripciones.dat`. Comando `GET_MY_INSCRIPTIONS`.
        *   **Responsable:** Mauricio
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Cliente):** `DashboardEstudiante` solicita sus inscripciones.
        *   **Responsable:** Santi
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Servidor y Cliente):** L�gica de `Estudiante::inscribirseACurso/Especializacion` env�a comando `INSCRIBE` al servidor. Servidor actualiza archivos y estructuras.
        *   **Responsable:** Mauricio (L�gica `Estudiante`), Jahat (Networking)
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

### 4. Sistema de Recomendaciones (Base)
    *   **Tarea (Servidor):** `Graph` (Jahat) se puebla con cursos y sus relaciones con especializaciones. Comando `GET_RECOMMENDATIONS_FOR_SPECIALIZATION`.
        *   **Responsable:** Jahat
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Cliente):** `MostrarEspecialidad` solicita y muestra recomendaciones.
        *   **Responsable:** Santi
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

### 5. Documentaci�n
    *   **Tarea:** Actualizar y expandir el documento de protocolo de red con todos los nuevos comandos.
        *   **Responsable:** Todos
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

**Entregable Clave Semana 2:** Un sistema donde las funcionalidades principales (login, registro, visualizaci�n de cursos/especializaciones, creaci�n de cursos, inscripciones b�sicas, recomendaciones b�sicas) operan en el modelo cliente-servidor, con el servidor utilizando las nuevas estructuras de datos.

---

## Semana 3: Funcionalidades Completas, Recomendaciones Avanzadas, UI Cliente Robusta y Pruebas Exhaustivas

**Objetivos Principales de la Semana:**
1.  **Sistema Completo y Robusto:** Todas las funcionalidades requeridas operan de forma estable.
2.  **Recomendaciones y Filtros Avanzados:** Implementados y funcionales.
3.  **Pruebas Integrales:** Sistema probado exhaustivamente.
4.  **Documentaci�n Final.**

**Tareas Detalladas y Responsables:**

### 1. Funcionalidades Avanzadas del Servidor
    *   **Tarea (Servidor - Recomendaciones):** Expandir `Graph` (Jahat) para recomendaciones m�s sofisticadas (cursos comunes entre especializaciones, etc.). Implementar algoritmos de b�squeda en grafos. Nuevos comandos `GET_ADVANCED_RECOMMENDATIONS`.
        *   **Responsable:** Jahat
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Servidor - Filtros):** Implementar filtros avanzados (m�ltiples criterios) para `ExplorarCursosYEspecialidades` (Mauricio).
        *   **Responsable:** Mauricio
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

### 2. UI Cliente y Flujos Completos
    *   **Tarea:** Asegurar que todas las pantallas (`MostrarCurso`, `DashboardEstudiante`, `DashboardOrganizacion`, `PerfilEstudiante`, `EditarPerfil`, etc.) interact�en fluidamente con el servidor para todas sus funcionalidades (incluyendo las avanzadas).
        *   **Responsable:** Santi (Lidera UI), con apoyo de Mauricio y Jahat para la l�gica de datos espec�fica.
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Manejo adecuado de estados de carga, mensajes de error/�xito del servidor en toda la UI.
        *   **Responsable:** Santi
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

### 3. Integridad, Validaciones y Manejo de Errores
    *   **Tarea (Servidor):** Asegurar IDs �nicos para todas las entidades. Validar datos de entrada del cliente.
        *   **Responsable:** Todos (revisar sus m�dulos)
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea (Servidor y Cliente):** Implementar manejo robusto de errores de red y l�gicos.
        *   **Responsable:** Todos
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

### 4. Pruebas Exhaustivas
    *   **Tarea:** Pruebas de unidad para toda la l�gica nueva/modificada.
        *   **Responsable:** Cada miembro para su c�digo.
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Pruebas de integraci�n para cada funcionalidad cliente-servidor.
        *   **Responsable:** Equipos de 2 (ej. quien hizo el cliente de una feature + quien hizo el servidor).
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Pruebas con m�ltiples clientes (simulados o reales).
        *   **Responsable:** Todos
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Pruebas de casos borde y escenarios de error.
        *   **Responsable:** Todos
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

### 5. Documentaci�n Final
    *   **Tarea:** Finalizar documentaci�n de estructuras de datos (comentarios Doxygen, etc.).
        *   **Responsable:** Cada miembro para sus estructuras.
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Completar y pulir el documento de protocolo cliente-servidor.
        *   **Responsable:** (Definir, ej: Santi o Jahat)
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Crear `README.md` con instrucciones de compilaci�n, ejecuci�n (cliente/servidor), y descripci�n general.
        *   **Responsable:** (Definir, ej: Mauricio)
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado
    *   **Tarea:** Breve descripci�n de la arquitectura del sistema y diagrama de clases actualizado (conceptual).
        *   **Responsable:** (Definir, ej: Jahat)
        *   **Estado:** [ ] Pendiente [ ] En Progreso [ ] Completado

**Entregable Clave Semana 3:** Un sistema cliente-servidor robusto, funcional y bien documentado que cumple con todos los requisitos del proyecto.

---

**Consideraciones Adicionales para el Seguimiento:**
*   **Reuniones Diarias (Stand-ups):** Cortas, para reportar progreso, pr�ximos pasos y bloqueos.
*   **Control de Versiones (Git):** Commits frecuentes y descriptivos. Ramas por funcionalidad o semana. Merges cuidadosos.
*   **Actualizaci�n de este Documento:** Al final de cada d�a o cada dos d�as, actualizar el estado de las tareas. A�adir notas o problemas encontrados.
*   **Flexibilidad:** Estar preparados para reasignar tareas o ajustar prioridades si surgen impedimentos mayores.

Este formato Markdown deber�a ser f�cil de mantener y les dar� una visi�n clara del progreso. �Mucho �xito!