# Guía de Estilo de Código - CourseraClone

## Información General

Esta guía establece las convenciones de codificación para el proyecto CourseraClone, basada en las mejores prácticas de Google C++ Style Guide, adaptada para nuestro equipo y priorizando nuestro idioma español para elementos de dominio específico. Se utilizará la extensión `.hpp` para los archivos de cabecera C++.

### Principios Fundamentales

- **Consistencia**: Todo el código debe seguir las mismas convenciones
- **Legibilidad**: El código debe ser fácil de leer y entender
- **Mantenibilidad**: Las convenciones deben facilitar el mantenimiento del código
- **Arquitectura Header-Only**: Optimización para compilación single-file con múltiples headers (`.hpp`)
- **Bilingüismo controlado**: Español para dominio del negocio, inglés para estructuras de datos estándar y terminos especificos de la industria.
- **Arquitectura Header-Only**: Proyecto diseñado con un solo `.cpp` principal y todas las implementaciones en headers (`.hpp`)

### Principios Adicionales de Codificación Limpia

Además de los principios fundamentales, se recomienda seguir estas pautas para mejorar la calidad del código:

- **Claridad sobre Concisión Extrema**: Si bien el código conciso es bueno, la legibilidad es primordial. Los nombres de variables, funciones y clases deben ser descriptivos y autoexplicativos.
- **Responsabilidad Única (Simplificado)**:
  - Cada función o método debe realizar una sola tarea específica y hacerla bien.
  - Cada clase debe tener una responsabilidad principal bien definida. Debemos evitar clases "todopoderosas".
- **`const` Correctness**:
  - Declara variables como `const` si su valor no cambiará después de la inicialización.
  - Marca los métodos de clase como `const` si no modifican el estado del objeto. Esto ayuda a prevenir errores y puede ser aprovechado por el compilador.
  ```cpp
  class Ejemplo {
      int _valor;
  public:
      int getValor() const { return _valor; } // Método const
      void setValor(int v) { _valor = v; }
  };
  const int MAX_INTENTOS = 3; // Variable const
  ```
- **Limitar el Alcance de las Variables**: Declara las variables en el ámbito (scope) más pequeño posible. Esto reduce la posibilidad de errores por nombres conflictivos y mejora la legibilidad.
- **Inicialización de Variables**: Siempre inicializa las variables antes de su primer uso para evitar comportamientos indefinidos.
- **Uso de `nullptr`**: Para punteros, prefiere `nullptr` (introducido en C++11) en lugar de `0` o `NULL` para mayor seguridad de tipos.
  ```cpp
  Curso* ptrCurso = nullptr;
  ```
- **Bucles Basados en Rango (Range-based for loops)**: Cuando iteres sobre colecciones (como `std::vector` o `LinkedList`), utiliza bucles basados en rango (C++11 en adelante) para un código más limpio y seguro, si la estructura de datos lo soporta directamente o mediante iteradores.
  ```cpp
  std::vector<Estudiante> estudiantes = /* ... */;
  for (const Estudiante& est : estudiantes) {
      // Procesar estudiante
  }
  ```
- **Evitar Variables Globales**: Minimiza el uso de variables globales. Si son necesarias, encapsúlalas dentro de una clase o namespace de utilidades y documenta claramente su propósito y manejo.

---

## 1. Nomenclatura de Archivos

### Archivos de Cabecera (.hpp)

```cpp
// ✅ CORRECTO - Entidades de dominio en español
Usuario.hpp
Curso.hpp
Especializacion.hpp
Estudiante.hpp

// ✅ CORRECTO - Pantallas con sufijo "Screen"
LoginScreen.hpp
RegistroScreen.hpp
DashboardEstudianteScreen.hpp
MostrarCursoScreen.hpp
ExplorarContenidoScreen.hpp

// ✅ CORRECTO - Controladores/Gestores identificables
GestionadorCursos.hpp
Controladora.hpp

// ✅ CORRECTO - Estructuras de datos en inglés (estándar industria)
LinkedList.hpp
BinarySearchTree.hpp
HashTable.hpp
PriorityQueue.hpp

// ✅ CORRECTO - Utilidades con sufijo descriptivo
FileUtils.hpp
ValidationHelper.hpp
ExtendedFunctions.hpp  // Nombre actual - mantener
```

### Archivos de Implementación (.cpp)

```cpp
// ✅ CORRECTO - Coincide con el archivo .hpp
CourseraCloneApp.cpp

// ✅ CORRECTO - Implementaciones con sufijos 
// Por ahora no son necesarios, son una mejora a futuro
descriptivos
LoginScreen.cpp
GestionadorCursos.cpp
FileUtils.cpp
```

---

## 2. Nomenclatura de Clases

### Formato: PascalCase con Sufijos Descriptivos

Para facilitar la identificación del tipo de clase y su responsabilidad, utilizamos sufijos descriptivos:

#### 2.1 Entidades de Dominio (Sin sufijo)

```cpp
// ✅ CORRECTO - Entidades de dominio puras
class Usuario
{
    // ...
};

class Estudiante : public Usuario
{
    // ...
};

class Curso
{
    // ...
};

class Especializacion
{
    // ...
};
```

#### 2.2 Pantallas/UI (Sufijo "Screen")

```cpp
// ✅ CORRECTO - Pantallas claramente identificables
class LoginScreen : public PantallaBase
{
    // ...
};

class RegistroScreen : public PantallaBase
{
    // ...
};

class DashboardEstudianteScreen : public PantallaBase
{
    // ...
};

class MostrarCursoScreen : public PantallaBase
{
    // ...
};

class ExplorarCursosScreen : public PantallaBase
{
    // ...
};

// ❌ INCORRECTO - No queda claro que es una pantalla
class Registro {  // ¿Es una entidad? ¿Una pantalla?
    // ...
};
```

#### 2.3 Controladores/Gestores (Sufijo "Manager" o "Controller")

```cpp
// ✅ CORRECTO - Lógica de control claramente identificable
class GestionadorCursos
{  // Nombre descriptivo actual - mantener
    // ...
};

class Controladora
{  // Controlador principal - mantener nombre actual
    // ...
};
```

#### 2.4 Estructuras de Datos (Inglés estándar)

```cpp
// ✅ CORRECTO - Nomenclatura estándar en inglés
template<typename T>
class LinkedList
{
    // ...
};

template<typename T>
class BinarySearchTree
{
    // ...
};

template<typename T>
class HashTable
{
    // ...
};
```

#### 2.5 Utilidades y Helpers (Sufijo "Utils" o "Helper")

```cpp
// ✅ CORRECTO - Clases de utilidad identificables
class FileUtils
{
    // ...
};

class ValidationHelper
{
    // ...
};

class DataHelper
{
    // ...
};

// ✅ CORRECTO - Funciones extendidas (mantener nombre actual)
class ExtendedFunctions
{
    // ...
};
```

---

## 2.6 Convenciones por Carpeta del Proyecto

Para mantener consistencia con la estructura modular, cada carpeta tiene convenciones específicas:

### Headers/Entities/ - Sin sufijo

```cpp
// Entidades de dominio puras - nombres descriptivos sin sufijos
Usuario.hpp, Estudiante.hpp, Curso.hpp, Especializacion.hpp
Empresa.hpp, Inscripcion.hpp, Boleta.hpp, Venta.hpp
```

### Headers/Screens/ - Sufijo "Screen"

```cpp
// Antes (confuso):
Login.hpp, Registro.hpp, DashboardEstudiante.hpp

// Después (claro):
LoginScreen.hpp, RegistroScreen.hpp, DashboardEstudianteScreen.hpp
MostrarCursoScreen.hpp, EditarPerfilScreen.hpp, VerBoletasScreen.hpp
```

### Headers/Controllers/ - Sufijo "Manager" o "Controller"

```cpp
// Nombres que indican responsabilidad de coordinación
Controladora.hpp           // Controlador principal - mantener
GestionadorCursos.hpp      // Gestor específico - mantener
CourseManager.hpp          // Alternativa en inglés
UserController.hpp         // Estilo REST
```

### Headers/DataStructures/ - Inglés estándar

```cpp
// Nomenclatura estándar de la industria - mantener
LinkedList.hpp, BinarySearchTree.hpp, HashTable.hpp
PriorityQueue.hpp, Stack.hpp, Queue.hpp
```

### Headers/Utils/ - Sufijo "Utils", "Helper" o nombres descriptivos

```cpp
// Clases de utilidad claramente identificables
FileUtils.hpp              // Utilidades de archivos
ValidationHelper.hpp       // Ayudantes de validación
ExtendedFunctions.hpp      // Nombre actual - mantener por legado
UI_Ascii.hpp              // Nombre descriptivo específico - mantener
```

## 2.7 Guía de Migración de Nombres Existentes

Para las clases actuales que necesitan renombrarse:

### Cambios Recomendados Inmediatos:

```cpp
// Headers/Screens/ - Agregar sufijo "Screen"
Login.hpp                 → LoginScreen.hpp
Registro.hpp              → RegistroScreen.hpp
MostrarCurso.hpp          → MostrarCursoScreen.hpp
MostrarEspecialidad.hpp   → MostrarEspecialidadScreen.hpp
EditarPerfil.hpp          → EditarPerfilScreen.hpp
VerBboletas.hpp           → VerBoletasScreen.hpp  // Corregir typo también
PerfilEstudiante.hpp      → PerfilEstudianteScreen.hpp
PerfilOrganizacion.hpp    → PerfilOrganizacionScreen.hpp
InscripcionEspecialidad.hpp → InscripcionEspecialidadScreen.hpp
```

### Mantener Sin Cambios (Ya son claros):

```cpp
// Headers/Screens/ - Actualizar a sufijo "Screen"
DashboardEstudiante.hpp           → DashboardEstudianteScreen.hpp
DashboardOrganizacion.hpp         → DashboardOrganizacionScreen.hpp
ExplorarCursosYEspecialidades.hpp → ExplorarContenidoScreen.hpp (simplificar también)
LandingPage.hpp                   → LandingPageScreen.hpp
```

### Headers/Controllers/ - Ya son buenos:

```cpp
// Mantener nombres actuales (ya son descriptivos)
Controladora.hpp          ✅ Mantener
GestionadorCursos.hpp     ✅ Mantener
CourseManager.hpp         ✅ Mantener
```

---

## 3. Nomenclatura de Variables

### Variables Miembro (atributos)

- **Privadas**: Prefijo `_` + camelCase
- **Públicas**: camelCase directo (evitar cuando sea posible)

```cpp
class Curso
{
private:
    int _id;
    string _titulo;
    string _descripcion;
    vector<string> _prerequisitos;
    float _calificacionPromedio;
    bool _estaActivo;

public:
    int duracionSemanas;  // Solo si es realmente necesario público
};
```

### Variables Locales y Parámetros

- **Formato**: camelCase
- **Parámetros**: Prefijo `_` para distinguir de miembros

```cpp
void inscribirEstudiante(int _idEstudiante, int _idCurso)
{
    string nombreCompleto = obtenerNombreEstudiante(_idEstudiante);
    bool inscripcionExitosa = false;

    for (int i = 0; i < listaCursos.size(); i++)
    {
        // ...
    }
}
```

### Constantes

- **Formato**: MAYÚSCULAS con guiones bajos
- **Ubicación**: En archivos Utils.h o al inicio de la clase

```cpp
// En Utils.h
const int MAX_ESTUDIANTES_POR_CURSO = 100;
const string RUTA_DATOS_USUARIOS = "Resources/Data/";
const char SEPARADOR_CSV = ',';

// En clase
class Usuario
{
private:
    static const int LONGITUD_NOMBRE = 50;
    static const int LONGITUD_EMAIL = 100;
};
```

---

## 4. Nomenclatura de Funciones/Métodos

### Formato: camelCase con verbos descriptivos

```cpp
class GestionadorCursos
{
public:
    // ✅ CORRECTO - Verbos claros y descriptivos
    bool inscribirEstudiante(int idEstudiante, int idCurso);
    void mostrarCursosDisponibles();
    Curso* buscarCursoPorId(int id);
    vector<Curso> filtrarCursosPorCategoria(const string& categoria);
    bool validarPrerequisitos(int idEstudiante, int idCurso);

    // Getters y Setters
    int getId() const { return _id; }
    void setId(int _nuevoId) { _id = _nuevoId; }

    string getTitulo() const { return _titulo; }
    void setTitulo(const string& _nuevoTitulo) { _titulo = _nuevoTitulo; }
};
```

### Funciones de Estructuras de Datos (inglés estándar)

```cpp
template<typename T>
class LinkedList
{
public:
    void push_back(const T& elemento);
    void push_front(const T& elemento);
    T& front();
    T& back();
    bool empty() const;
    size_t size() const;
    void clear();
};
```

---

## 5. Comentarios (Sistema Simplificado)

Para un proyecto académico, mantenemos un sistema de comentarios simple pero efectivo:

### 5.1 Comentarios de Archivo (Mínimos necesarios)

```cpp
// filepath: Headers/Entities/Usuario.hpp
// Descripcion: Clase base para usuarios del sistema (estudiantes y empresas)

#pragma once // Considerar reemplazar con guardianes de cabecera estándar (ver Sección 13.4)
```

### 5.2 Comentarios de Clase (Una línea descriptiva)

```cpp
// Clase que representa un usuario en el sistema
class Usuario
{
    // ...
};

// Pantalla principal del estudiante
class DashboardEstudianteScreen : public PantallaBase
{
    // ...
};

// Lista enlazada genérica para cualquier tipo de dato
template<typename T>
class LinkedList
{
    // ...
};
```

### 5.3 Comentarios de Método (Solo cuando sea necesario)

```cpp
class GestionadorCursos
{
public:
    // Busca un curso por ID usando búsqueda binaria
    Curso* buscarCursoPorId(int id);

    // Métodos simples no necesitan comentario
    int getId() const { return _id; }
    void setId(int _nuevoId) { _id = _nuevoId; }

    // Solo comentar algoritmos complejos
    void ordenarCursosPorPopularidad()
    {
        // Implementa algoritmo de ordenamiento quicksort
        // por calificación promedio descendente
        quickSort(listaCursos, 0, listaCursos.size() - 1);
    }
};
```

### 5.4 Comentarios en Línea (Explicar el "por qué", no el "qué")

```cpp
void procesarInscripcion(int idEstudiante, int idCurso)
{
    // Verificar que el estudiante existe
    if (!existeEstudiante(idEstudiante))
    {
        throw std::runtime_error("Estudiante no encontrado");
    }

    // Los prerequisitos son obligatorios para inscribirse
    if (!validarPrerequisitos(idEstudiante, idCurso))
    {
        return;
    }

    registrarInscripcion(idEstudiante, idCurso);
}
```

### 5.5 Comentarios Especiales para Desarrollo

```cpp
// TODO: Implementar validación de cupos
// FIXME: Corregir duplicación de inscripciones
// HACK: Solución temporal - refactorizar después
// NOTE: Este método es crítico para rendimiento
```

### 5.6 Cuándo NO comentar

```cpp
// ❌ INCORRECTO - Comentarios obvios
int suma = a + b; // Suma a y b

// ❌ INCORRECTO - Explicar código evidente
if (edad >= 18) // Si la edad es mayor o igual a 18
{
    esAdulto = true; // Establecer esAdulto como verdadero
}

// ✅ CORRECTO - Sin comentarios innecesarios
int suma = a + b;
if (edad >= 18)
{
    esAdulto = true;
}
```

### 5.7 Reglas Simples para Comentarios

1. **Una línea por clase**: Explica qué hace la clase
2. **Comenta algoritmos complejos**: Solo si no es obvio qué hace
3. **Explica el "por qué"**: No describas el código, explica la razón
4. **Usa TODO/FIXME**: Para marcar trabajo pendiente
5. **No comentes lo obvio**: El código debe ser auto-explicativo

---

## 6. Formato y Espaciado

### Indentación

- **Usar 4 espacios** (no tabs)
- **Máximo 80-100 caracteres por línea**

### Llaves

```cpp
// ✅ CORRECTO - Estilo K&R modificado
class Usuario
{
public:
    void metodoEjemplo()
    {
        if (condicion)
        {
            // código
        } else
        {
            // código alternativo
        }

        for (int i = 0; i < limite; i++)
        {
            // iteración
        }
    }
};
```

### Espacios

```cpp
// ✅ CORRECTO - Espacios alrededor de operadores
int resultado = (a + b) * c;
bool esValido = (edad >= 18) && (email.length() > 0);

// ✅ CORRECTO - Espacios después de comas
void metodo(int param1, string param2, bool param3);

// ✅ CORRECTO - Sin espacios en paréntesis vacíos
void metodoSinParametros();
```

---

## 7. Organización de Archivos

### Estructura de Archivo .hpp

```cpp
// 1. Comentario de archivo
// filepath: Headers/Entities/Curso.hpp

// 2. Guards o #pragma once
// Se recomienda usar guardianes de cabecera estándar. Ver Sección 13.4 para la convención.
#ifndef COURSERACLONE_ENTITIES_CURSO_HPP // Ejemplo de guardián
#define COURSERACLONE_ENTITIES_CURSO_HPP

// 3. Includes del sistema
#include <string>
#include <vector>
#include <iostream>

// 4. Includes del proyecto (con rutas relativas)
#include "Actividad.hpp"
#include "../DataStructures/LinkedList.hpp"

// 5. Using statements (solo en .cpp, evitar en .hpp)
// using namespace std; // ❌ EVITAR en archivos .hpp

// 6. Constantes globales (si es necesario)
const int MAX_CLASES_POR_CURSO = 50;

// 7. Declaración de la clase
class Curso // : public Actividad (Asumiendo que Actividad.hpp define Actividad)
{
private:
    // Atributos privados primero

public:
    // Constructores
    // Destructor
    // Métodos públicos
    // Getters y setters al final
};

#endif // COURSERACLONE_ENTITIES_CURSO_HPP // Fin del guardián
```

---

## 11. Checklist de Revisión de Código

Antes de hacer commit, verificar:

- [ ] Los nombres siguen las convenciones establecidas (entidades sin sufijo, pantallas con "Screen")
- [ ] Las clases están en la carpeta correcta según su responsabilidad
- [ ] Los sufijos identifican claramente el tipo de clase (Screen, Manager, Utils, Helper)
- [ ] Cada archivo `.hpp` tiene guardianes de cabecera según la convención definida en la Sección 13.4. <!-- NUEVO CHECK -->
- [ ] Cada clase tiene un comentario de una línea explicando qué hace
- [ ] Solo los algoritmos complejos tienen comentarios explicativos
- [ ] No hay comentarios obvios que explican código evidente
- [ ] Las includes están organizadas correctamente
- [ ] No hay magic numbers (usar constantes)
- [ ] Los métodos no son excesivamente largos (< 50 líneas)
- [ ] Se manejan los casos de error apropiadamente
- [ ] La indentación es consistente (4 espacios)
- [ ] No hay `using namespace std;` en archivos `.hpp`

---

## 12. Estructura de Carpetas del Proyecto

### Nueva Organización Implementada (Mayo 2025)

El proyecto ha sido reorganizado de una estructura plana a una estructura jerárquica modular:

```
CourseraClone/
├── Headers/                          # Todos los archivos .hpp organizados por responsabilidad
│   ├── Controllers/                  # Lógica de control y coordinación
│   │   ├── Controladora.hpp           # Controlador principal de la aplicación
│   │   ├── GestionadorCursos.hpp      # Gestión específica de cursos
│   │   └── CourseManager.hpp          # Manager auxiliar (si es necesario)
│   ├── DataStructures/              # Estructuras de datos implementadas
│   │   ├── LinkedList.hpp             # Lista enlazada genérica
│   │   ├── BinarySearchTree.hpp       # Árbol binario de búsqueda
│   │   ├── HashTable.hpp              # Tabla hash con manejo de colisiones
│   │   ├── PriorityQueue.hpp          # Cola de prioridad
│   │   ├── BinaryHeap.hpp             # Heap binario para PriorityQueue
│   │   ├── algoritmosBusqueda.hpp     # Algoritmos de búsqueda
│   │   ├── algoritmosOrdenamiento.hpp # Algoritmos de ordenamiento
│   │   └── ...                      # Otras estructuras (Nodo.hpp, etc.)
│   ├── Entities/                    # Clases de entidades del dominio
│   │   ├── Usuario.hpp                # Clase base para usuarios
│   │   ├── Estudiante.hpp             # Entidad estudiante
│   │   ├── Empresa.hpp                # Entidad empresa/organización
│   │   ├── Curso.hpp                  # Entidad curso
│   │   ├── Especializacion.hpp        # Entidad especialización
│   │   ├── Inscripcion.hpp            # Entidad inscripción
│   │   └── ...                      # Otras entidades
│   ├── Screens/                     # Pantallas de la aplicación
│   │   ├── Login.hpp                  # Pantalla de inicio de sesión
│   │   ├── LandingPage.hpp            # Página principal
│   │   ├── DashboardEstudiante.hpp    # Panel de estudiante
│   │   ├── DashboardOrganizacion.hpp  # Panel de organización
│   │   ├── ExplorarCursosYEspecialidades.hpp  # Explorador
│   │   └── ...                      # Otras pantallas
│   └── Utils/                       # Utilidades y helpers
│       ├── Pantalla.hpp               # Clase base para pantallas
│       ├── ExtendedFunctions.hpp      # Funciones de utilidad
│       ├── UI_Ascii.hpp               # Elementos ASCII para UI
│       └── Utils.hpp                  # Utilidades generales
├── Source/                          # Archivos .cpp de implementación
│   └── CourseraCloneApp.cpp         # Archivo principal de la aplicación
├── Resources/                       # Recursos del proyecto
│   ├── Data/                        # Archivos de datos
│   │   ├── cursos.txt               # Datos de cursos
│   │   ├── usuarios_estudiante.dat  # Datos binarios de estudiantes
│   │   └── ...                      # Otros archivos de datos
│   └── Documentation/               # Documentación del proyecto
│       ├── Guia de Estilo de Codigo.md  # Este archivo
│       └── Plan de implementacion.md    # Plan de desarrollo
└── x64/Debug/                       # Archivos compilados (generados en raíz)
    └── CourseraClone.exe            # Ejecutable compilado
```

### Beneficios de la Nueva Estructura

1. **Separación de Responsabilidades**: Cada carpeta tiene un propósito específico
2. **Escalabilidad**: Fácil agregar nuevas funcionalidades sin saturar la raíz
3. **Mantenibilidad**: Los desarrolladores pueden localizar rápidamente los archivos
4. **Estándar de la Industria**: Estructura similar a proyectos profesionales

### Convenciones para Rutas de Inclusión

```cpp
// ✅ CORRECTO - Desde un archivo en Headers/Screens/
#include "../Entities/Usuario.hpp"        // Acceder a entidades
#include "../Controllers/Controladora.hpp" // Acceder a controladores
#include "../Utils/Pantalla.hpp"          // Acceder a utilidades
#include "../DataStructures/LinkedList.hpp" // Acceder a estructuras

// ✅ CORRECTO - Desde un archivo en Headers/Entities/
#include "../DataStructures/LinkedList.hpp"  // Acceder a estructuras
#include "Usuario.hpp"                       // Archivo en la misma carpeta

// ✅ CORRECTO - Desde Source/
#include "../Headers/Controllers/Controladora.hpp"  // Acceder desde Source
```

### Reglas para Agregar Nuevos Archivos

1.  **Nuevas Entidades**: Agregar en `Headers/Entities/` - sin sufijo (ej. `MiEntidad.hpp`)
2.  **Nuevas Pantallas**: Agregar en `Headers/Screens/` - con sufijo "Screen" (ej. `MiPantallaScreen.hpp`)
3.  **Nuevas Estructuras de Datos**: Agregar en `Headers/DataStructures/` - inglés estándar (ej. `MyDataStructure.hpp`)
4.  **Nuevos Controladores**: Agregar en `Headers/Controllers/` - con sufijo "Manager" o "Controller" (ej. `MiGestorManager.hpp`)
5.  **Nuevas Utilidades**: Agregar en `Headers/Utils/` - con sufijo "Utils" o "Helper" (ej. `MiUtilidadHelper.hpp`)
6.  **Implementaciones .cpp**: Agregar en `Source/` - mismo nombre que el `.hpp` correspondiente

### Ejemplos de Nomenclatura por Carpeta:

```cpp
// Headers/Entities/ - Entidades de dominio
class NuevoConcepto { /* ... */ };          // NuevoConcepto.hpp

// Headers/Screens/ - Pantallas
class ConfiguracionScreen { /* ... */ };    // ConfiguracionScreen.hpp
```
