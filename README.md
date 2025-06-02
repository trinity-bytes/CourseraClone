# CourseraClone C++

**Versi�n:** 1.0.0 (Cliente-Servidor)
**Autores:** Santi, Mauricio, Jahat
**Curso:** Algoritmos y Estructura de Datos
**Instituci�n:** UPC

## Descripci�n del Proyecto

CourseraClone es una aplicaci�n de consola en C++ que simula una plataforma de gesti�n de cursos en l�nea. Este proyecto implementa funcionalidades clave como la gesti�n de usuarios (estudiantes y organizaciones), creaci�n y exploraci�n de cursos y especializaciones, sistema de inscripciones, y un motor de recomendaciones.

La versi�n actual opera bajo una arquitectura cliente-servidor, donde una instancia del programa act�a como servidor (manejando la l�gica de negocio y la persistencia de datos) y m�ltiples instancias pueden actuar como clientes, interactuando con el sistema a trav�s de la red.

El proyecto hace un uso extensivo de diversas estructuras de datos implementadas como templates gen�ricos para asegurar eficiencia y modularidad.

## Caracter�sticas Principales

*   **Gesti�n de Usuarios:**
    *   Registro e inicio de sesi�n para Estudiantes y Empresas (Organizaciones).
    *   Perfiles de usuario.
*   **Gesti�n de Contenido Educativo:**
    *   Creaci�n de Cursos con clases y descripciones.
    *   Creaci�n de Especializaciones que agrupan cursos.
    *   Verificaci�n de duplicados de cursos al momento de la creaci�n (usando �rbol AVL).
*   **Sistema de Inscripciones:**
    *   Los estudiantes pueden inscribirse a cursos y especializaciones.
    *   Acceso r�pido a datos de inscripci�n (usando HashMap en el servidor).
*   **Exploraci�n y B�squeda:**
    *   Landing Page con cursos y especializaciones populares (usando PriorityQueue en el servidor).
    *   Explorador de cursos y especializaciones con filtros (ej. por cantidad de inscritos, ordenables en el servidor).
*   **Sistema de Recomendaciones:**
    *   Recomendaciones de cursos basadas en especializaciones y potencialmente otros criterios (usando Grafo en el servidor).
*   **Arquitectura Cliente-Servidor:**
    *   Un �nico ejecutable que puede operar en modo cliente o servidor.
    *   Comunicaci�n v�a sockets TCP/IP.
    *   El servidor centraliza la l�gica de negocio y el acceso a archivos de datos.
*   **Estructuras de Datos Implementadas:**
    *   `BinaryHeap<T>`
    *   `PriorityQueue<T>` (basada en BinaryHeap)
    *   `BST<T>` (�rbol Binario de B�squeda)
    *   `HashMap<K, V>`
    *   `AVLTree<T>`
    *   `Graph<TNodeData>`

## Estructura del Proyecto

*(Esta secci�n puede detallar brevemente la organizaci�n de las carpetas y archivos principales, si lo consideran �til. Por ejemplo:)*
*   `CourseraClone/`: Directorio ra�z del proyecto.
    *   `*.h`, `*.cpp`: Archivos fuente principales (Controladora, Pantallas, Clases de Entidad, Estructuras de Datos, etc.).
    *   `Resources/Data/`: Contiene los archivos de datos (`.dat`, `.txt`).
    *   `main.cpp`: Punto de entrada de la aplicaci�n.
    *   `Network/`: (Si deciden agrupar as� las clases de red) `NetworkManagerClient.h/.cpp`, `NetworkManagerServer.h/.cpp`.
    *   `DataStructures/`: (Si deciden agrupar as� las estructuras) `BinaryHeap.h`, `Graph.h`, etc.

## Compilaci�n y Ejecuci�n

### Prerrequisitos
*   Compilador C++17 (ej. MSVC incluido en Visual Studio 2022).
*   Sistema Operativo Windows (debido al uso de `conio.h`, `windows.h` para funciones de consola y Winsock).

### Compilaci�n
El proyecto est� configurado para compilarse con Visual Studio 2022.
1.  Abrir el archivo de soluci�n `CourseraClone.sln` con Visual Studio.
2.  Seleccionar la configuraci�n de compilaci�n (ej. Debug o Release).
3.  Construir la soluci�n (Build > Build Solution o F7).

### Ejecuci�n

El programa puede ejecutarse en modo servidor o cliente.

**Modo Servidor:**
Abre una terminal o S�mbolo del sistema, navega al directorio donde se encuentra el ejecutable (ej. `CourseraClone/x64/Debug/`) y ejecuta: