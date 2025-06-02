# CourseraClone C++

**Versión:** 1.0.0 (Cliente-Servidor)
**Autores:** Santi, Mauricio, Jahat
**Curso:** Algoritmos y Estructura de Datos
**Institución:** UPC

## Descripción del Proyecto

CourseraClone es una aplicación de consola en C++ que simula una plataforma de gestión de cursos en línea. Este proyecto implementa funcionalidades clave como la gestión de usuarios (estudiantes y organizaciones), creación y exploración de cursos y especializaciones, sistema de inscripciones, y un motor de recomendaciones.

La versión actual opera bajo una arquitectura cliente-servidor, donde una instancia del programa actúa como servidor (manejando la lógica de negocio y la persistencia de datos) y múltiples instancias pueden actuar como clientes, interactuando con el sistema a través de la red.

El proyecto hace un uso extensivo de diversas estructuras de datos implementadas como templates genéricos para asegurar eficiencia y modularidad.

## Características Principales

*   **Gestión de Usuarios:**
    *   Registro e inicio de sesión para Estudiantes y Empresas (Organizaciones).
    *   Perfiles de usuario.
*   **Gestión de Contenido Educativo:**
    *   Creación de Cursos con clases y descripciones.
    *   Creación de Especializaciones que agrupan cursos.
    *   Verificación de duplicados de cursos al momento de la creación (usando Árbol AVL).
*   **Sistema de Inscripciones:**
    *   Los estudiantes pueden inscribirse a cursos y especializaciones.
    *   Acceso rápido a datos de inscripción (usando HashMap en el servidor).
*   **Exploración y Búsqueda:**
    *   Landing Page con cursos y especializaciones populares (usando PriorityQueue en el servidor).
    *   Explorador de cursos y especializaciones con filtros (ej. por cantidad de inscritos, ordenables en el servidor).
*   **Sistema de Recomendaciones:**
    *   Recomendaciones de cursos basadas en especializaciones y potencialmente otros criterios (usando Grafo en el servidor).
*   **Arquitectura Cliente-Servidor:**
    *   Un único ejecutable que puede operar en modo cliente o servidor.
    *   Comunicación vía sockets TCP/IP.
    *   El servidor centraliza la lógica de negocio y el acceso a archivos de datos.
*   **Estructuras de Datos Implementadas:**
    *   `BinaryHeap<T>`
    *   `PriorityQueue<T>` (basada en BinaryHeap)
    *   `BST<T>` (Árbol Binario de Búsqueda)
    *   `HashMap<K, V>`
    *   `AVLTree<T>`
    *   `Graph<TNodeData>`

## Estructura del Proyecto

*(Esta sección puede detallar brevemente la organización de las carpetas y archivos principales, si lo consideran útil. Por ejemplo:)*
*   `CourseraClone/`: Directorio raíz del proyecto.
    *   `*.h`, `*.cpp`: Archivos fuente principales (Controladora, Pantallas, Clases de Entidad, Estructuras de Datos, etc.).
    *   `Resources/Data/`: Contiene los archivos de datos (`.dat`, `.txt`).
    *   `main.cpp`: Punto de entrada de la aplicación.
    *   `Network/`: (Si deciden agrupar así las clases de red) `NetworkManagerClient.h/.cpp`, `NetworkManagerServer.h/.cpp`.
    *   `DataStructures/`: (Si deciden agrupar así las estructuras) `BinaryHeap.h`, `Graph.h`, etc.

## Compilación y Ejecución

### Prerrequisitos
*   Compilador C++17 (ej. MSVC incluido en Visual Studio 2022).
*   Sistema Operativo Windows (debido al uso de `conio.h`, `windows.h` para funciones de consola y Winsock).

### Compilación
El proyecto está configurado para compilarse con Visual Studio 2022.
1.  Abrir el archivo de solución `CourseraClone.sln` con Visual Studio.
2.  Seleccionar la configuración de compilación (ej. Debug o Release).
3.  Construir la solución (Build > Build Solution o F7).

### Ejecución

El programa puede ejecutarse en modo servidor o cliente.

**Modo Servidor:**
Abre una terminal o Símbolo del sistema, navega al directorio donde se encuentra el ejecutable (ej. `CourseraClone/x64/Debug/`) y ejecuta: