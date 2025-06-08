# Guía de Estilo de Código - CourseraClone

## Información General

Esta guía establece las convenciones de codificación para el proyecto CourseraClone, basada en las mejores prácticas de Google C++ Style Guide, adaptada para nuestro equipo y priorizando nuestro idioma español para elementos de dominio específico.

### Principios Fundamentales

- **Consistencia**: Todo el código debe seguir las mismas convenciones
- **Legibilidad**: El código debe ser fácil de leer y entender
- **Mantenibilidad**: Las convenciones deben facilitar el mantenimiento del código
- **Arquitectura Header-Only**: Optimización para compilación single-file con múltiples headers
- **Bilingüismo controlado**: Español para dominio del negocio, inglés para estructuras de datos estándar y terminos especificos de la industria.
- **Arquitectura Header-Only**: Proyecto diseñado con un solo .cpp principal y todas las implementaciones en headers (.h)

---

## 1. Nomenclatura de Archivos

### Archivos de Cabecera (.h)

```cpp
// ✅ CORRECTO - Entidades de dominio en español
Usuario.h
Curso.h
Especializacion.h
Estudiante.h

// ✅ CORRECTO - Pantallas con sufijo "Screen"
Login_Screen.h
Registro_Screen.h
DashboardEstudiante_Screen.h
MostrarCurso_Screen.h
ExplorarCursos_Screen.h

// ✅ CORRECTO - Controladores/Gestores identificables
GestionadorCursos.h
Controladora.h

// ✅ CORRECTO - Estructuras de datos en inglés (estándar industria)
LinkedList.h
BinarySearchTree.h
HashTable.h
PriorityQueue.h

// ✅ CORRECTO - Utilidades con sufijo descriptivo
FileUtils.h
ValidationHelper.h
ExtendedFunctions.h  // Nombre actual - mantener
```

### Archivos de Implementación (.cpp)

```cpp
// ✅ CORRECTO - Coincide con el archivo .h
CourseraCloneApp.cpp

// ✅ CORRECTO - Implementaciones con sufijos descriptivos
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
Usuario.h, Estudiante.h, Curso.h, Especializacion.h
Empresa.h, Inscripcion.h, Boleta.h, Venta.h
```

### Headers/Screens/ - Sufijo "Screen"

```cpp
// Antes (confuso):
Login.h, Registro.h, DashboardEstudiante.h

// Después (claro):
LoginScreen.h, RegistroScreen.h, DashboardEstudianteScreen.h
MostrarCursoScreen.h, EditarPerfilScreen.h, VerBoletasScreen.h
```

### Headers/Controllers/ - Sufijo "Manager" o "Controller"

```cpp
// Nombres que indican responsabilidad de coordinación
Controladora.h           // Controlador principal - mantener
GestionadorCursos.h      // Gestor específico - mantener
CourseManager.h          // Alternativa en inglés
UserController.h         // Estilo REST
```

### Headers/DataStructures/ - Inglés estándar

```cpp
// Nomenclatura estándar de la industria - mantener
LinkedList.h, BinarySearchTree.h, HashTable.h
PriorityQueue.h, Stack.h, Queue.h
```

### Headers/Utils/ - Sufijo "Utils", "Helper" o nombres descriptivos

```cpp
// Clases de utilidad claramente identificables
FileUtils.h              // Utilidades de archivos
ValidationHelper.h       // Ayudantes de validación
ExtendedFunctions.h      // Nombre actual - mantener por legado
UI_Ascii.h              // Nombre descriptivo específico - mantener
```

## 2.7 Guía de Migración de Nombres Existentes

Para las clases actuales que necesitan renombrarse:

### Cambios Recomendados Inmediatos:

```cpp
// Headers/Screens/ - Agregar sufijo "Screen"
Login.h                 → LoginScreen.h
Registro.h              → RegistroScreen.h
MostrarCurso.h          → MostrarCursoScreen.h
MostrarEspecialidad.h   → MostrarEspecialidadScreen.h
EditarPerfil.h          → EditarPerfilScreen.h
VerBboletas.h           → VerBoletasScreen.h  // Corregir typo también
PerfilEstudiante.h      → PerfilEstudianteScreen.h
PerfilOrganizacion.h    → PerfilOrganizacionScreen.h
InscripcionEspecialidad.h → InscripcionEspecialidadScreen.h
```

### Mantener Sin Cambios (Ya son claros):

```cpp
// Headers/Screens/ - Actualizar a sufijo "Screen"
DashboardEstudiante.h           → DashboardEstudianteScreen.h
DashboardOrganizacion.h         → DashboardOrganizacionScreen.h
ExplorarCursosYEspecialidades.h → ExplorarCursosScreen.h (simplificar también)
LandingPage.h                   → LandingPageScreen.h
```

### Headers/Controllers/ - Ya son buenos:

```cpp
// Mantener nombres actuales (ya son descriptivos)
Controladora.h          ✅ Mantener
GestionadorCursos.h     ✅ Mantener
CourseManager.h         ✅ Mantener
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
// filepath: Headers/Entities/Usuario.h
// Descripcion: Clase base para usuarios del sistema (estudiantes y empresas)

#pragma once
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

````

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
````

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

### Estructura de Archivo .h

```cpp
// 1. Comentario de archivo
// filepath: Headers/Entities/Curso.h

// 2. Guards o #pragma once
#pragma once

// 3. Includes del sistema
#include <string>
#include <vector>
#include <iostream>

// 4. Includes del proyecto (con rutas relativas)
#include "Actividad.h"
#include "../DataStructures/LinkedList.h"

// 5. Using statements (solo en .cpp, evitar en .h)
// using namespace std; // ❌ EVITAR en headers

// 6. Constantes globales (si es necesario)
const int MAX_CLASES_POR_CURSO = 50;

// 7. Declaración de la clase
class Curso : public Actividad
{
private:
    // Atributos privados primero

public:
    // Constructores
    // Destructor
    // Métodos públicos
    // Getters y setters al final
};
```

---

## 8. Manejo de Errores

### Excepciones con Mensajes Descriptivos

```cpp
void inscribirEstudiante(int idEstudiante, int idCurso)
{
    if (idEstudiante <= 0)
    {
        throw std::invalid_argument("ID de estudiante debe ser positivo");
    }

    if (!existeCurso(idCurso))
    {
        throw std::runtime_error("El curso con ID " + std::to_string(idCurso) + " no existe");
    }

    if (estaLlenoCurso(idCurso))
    {
        throw std::runtime_error("El curso está lleno, no se pueden agregar más estudiantes");
    }
}
```

---

## 9. Convenciones Específicas del Proyecto

### Archivos de Datos

```cpp
// ✅ CORRECTO - Rutas consistentes
const string RUTA_USUARIOS_ESTUDIANTE = "Resources/Data/usuarios_estudiante.dat";
const string RUTA_USUARIOS_EMPRESA = "Resources/Data/usuarios_empresa.dat";
const string RUTA_CURSOS = "Resources/Data/cursos.txt";
```

### Estructuras de Datos Template

```cpp
// ✅ CORRECTO - Nomenclatura estándar en inglés
template<typename T>
class LinkedList
{
    // Métodos en inglés estándar
};

// ✅ CORRECTO - Uso en contexto español
LinkedList<Curso> listaCursos;
LinkedList<Estudiante> listaEstudiantes;
```

### Pantallas/UI

```cpp
// ✅ CORRECTO - Herencia consistente con sufijo "Screen"
class DashboardEstudianteScreen : public PantallaBase
{
public:
    void mostrarPantalla() override;
    PantallaBase* getSiguientePantalla() override;

private:
    void mostrarCursosInscritos();
    void mostrarRecomendaciones();
};

class LoginScreen : public PantallaBase
{
public:
    void mostrarPantalla() override;
    PantallaBase* getSiguientePantalla() override;

private:
    bool validarCredenciales(const string& email, const string& password);
    void procesarLogin();
};
```

---

## 10. Herramientas y Automatización

### Comentarios TODO/FIXME

```cpp
// TODO: Implementar validación de email más robusta
// FIXME: Corregir memory leak en cargarDatos()
// HACK: Solución temporal - refactorizar después
// NOTE: Esta función es crítica para el rendimiento
// WARNING: No modificar sin revisar dependencias
```

### Versionado de Cambios

```cpp
// CHANGELOG en comentarios importantes:
// v1.0 - Implementación inicial (Jahat)
// v1.1 - Agregada validación de prerequisitos (Mauricio)
// v1.2 - Optimizada búsqueda con BST (Santi)
```

---

## 11. Checklist de Revisión de Código

Antes de hacer commit, verificar:

- [ ] Los nombres siguen las convenciones establecidas (entidades sin sufijo, pantallas con "Screen")
- [ ] Las clases están en la carpeta correcta según su responsabilidad
- [ ] Los sufijos identifican claramente el tipo de clase (Screen, Manager, Utils, Helper)
- [ ] Cada clase tiene un comentario de una línea explicando qué hace
- [ ] Solo los algoritmos complejos tienen comentarios explicativos
- [ ] No hay comentarios obvios que explican código evidente
- [ ] Las includes están organizadas correctamente
- [ ] No hay magic numbers (usar constantes)
- [ ] Los métodos no son excesivamente largos (< 50 líneas)
- [ ] Se manejan los casos de error apropiadamente
- [ ] La indentación es consistente (4 espacios)
- [ ] No hay using namespace std en headers

---

## 12. Estructura de Carpetas del Proyecto

### Nueva Organización Implementada (Enero 2025)

El proyecto ha sido reorganizado de una estructura plana a una estructura jerárquica modular:

```
CourseraClone/
├── Headers/                          # Todos los archivos .h organizados por responsabilidad
│   ├── Controllers/                  # Lógica de control y coordinación
│   │   ├── Controladora.h           # Controlador principal de la aplicación
│   │   ├── GestionadorCursos.h      # Gestión específica de cursos
│   │   └── CourseManager.h          # Manager auxiliar (si es necesario)
│   ├── DataStructures/              # Estructuras de datos implementadas
│   │   ├── LinkedList.h             # Lista enlazada genérica
│   │   ├── BinarySearchTree.h       # Árbol binario de búsqueda
│   │   ├── HashTable.h              # Tabla hash con manejo de colisiones
│   │   ├── PriorityQueue.h          # Cola de prioridad
│   │   ├── BinaryHeap.h             # Heap binario para PriorityQueue
│   │   ├── algoritmosBusqueda.h     # Algoritmos de búsqueda
│   │   ├── algoritmosOrdenamiento.h # Algoritmos de ordenamiento
│   │   └── ...                      # Otras estructuras (Nodo.h, etc.)
│   ├── Entities/                    # Clases de entidades del dominio
│   │   ├── Usuario.h                # Clase base para usuarios
│   │   ├── Estudiante.h             # Entidad estudiante
│   │   ├── Empresa.h                # Entidad empresa/organización
│   │   ├── Curso.h                  # Entidad curso
│   │   ├── Especializacion.h        # Entidad especialización
│   │   ├── Inscripcion.h            # Entidad inscripción
│   │   └── ...                      # Otras entidades
│   ├── Screens/                     # Pantallas de la aplicación
│   │   ├── Login.h                  # Pantalla de inicio de sesión
│   │   ├── LandingPage.h            # Página principal
│   │   ├── DashboardEstudiante.h    # Panel de estudiante
│   │   ├── DashboardOrganizacion.h  # Panel de organización
│   │   ├── ExplorarCursosYEspecialidades.h  # Explorador
│   │   └── ...                      # Otras pantallas
│   └── Utils/                       # Utilidades y helpers
│       ├── Pantalla.h               # Clase base para pantallas
│       ├── ExtendedFunctions.h      # Funciones de utilidad
│       ├── UI_Ascii.h               # Elementos ASCII para UI
│       └── Utils.h                  # Utilidades generales
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
#include "../Entities/Usuario.h"        // Acceder a entidades
#include "../Controllers/Controladora.h" // Acceder a controladores
#include "../Utils/Pantalla.h"          // Acceder a utilidades
#include "../DataStructures/LinkedList.h" // Acceder a estructuras

// ✅ CORRECTO - Desde un archivo en Headers/Entities/
#include "../DataStructures/LinkedList.h"  // Acceder a estructuras
#include "Usuario.h"                       // Archivo en la misma carpeta

// ✅ CORRECTO - Desde Source/
#include "../Headers/Controllers/Controladora.h"  // Acceder desde Source
```

### Reglas para Agregar Nuevos Archivos

1. **Nuevas Entidades**: Agregar en `Headers/Entities/` - sin sufijo
2. **Nuevas Pantallas**: Agregar en `Headers/Screens/` - con sufijo "Screen"
3. **Nuevas Estructuras de Datos**: Agregar en `Headers/DataStructures/` - inglés estándar
4. **Nuevos Controladores**: Agregar en `Headers/Controllers/` - con sufijo "Manager" o "Controller"
5. **Nuevas Utilidades**: Agregar en `Headers/Utils/` - con sufijo "Utils" o "Helper"
6. **Implementaciones .cpp**: Agregar en `Source/` - mismo nombre que el .h correspondiente

### Ejemplos de Nomenclatura por Carpeta:

```cpp
// Headers/Entities/ - Entidades de dominio
class NuevoConcepto { ... };          // NuevoConcepto.h

// Headers/Screens/ - Pantallas
class ConfiguracionScreen { ... };    // ConfiguracionScreen.h

// Headers/Controllers/ - Lógica de control
class ReportManager { ... };          // ReportManager.h

// Headers/Utils/ - Utilidades
class CsvHelper { ... };              // CsvHelper.h
```

### Configuración de Visual Studio

La configuración del proyecto está actualizada para:

- Reconocer la nueva estructura de carpetas
- Generar archivos debug en la carpeta raíz (`x64/Debug/`)
- Mantener compatibilidad con el sistema de filtros de VS

**Versión:** 1.1 (Actualizada con nueva estructura)  
**Última actualización:** 6 de enero de 2025  
**Autores:** Santi, Mauricio, Jahat

---

## 6. Arquitectura Header-Only

### 6.1 Principios de Compilación Single-File

**Optimización para main.cpp único:**

```cpp
// main.cpp - Único archivo .cpp del proyecto
#include "Headers/Controllers/Controladora.h"

int main() {
    Controladora app;
    app.ejecutar();
    return 0;
}
```

### 6.2 Gestión de Includes

**Headers deben ser auto-contenidos:**

```cpp
// ✅ CORRECTO - Header completo
#ifndef ENTITIES_CURSO_H
#define ENTITIES_CURSO_H

#include <string>
#include <vector>
#include "Instructor.h"

class Curso {
    // Implementación completa aquí
private:
    std::string titulo;
    std::vector<Instructor> instructores;

public:
    Curso(const std::string& titulo) : titulo(titulo) {}

    void agregarInstructor(const Instructor& instructor) {
        instructores.push_back(instructor);
    }

    const std::string& getTitulo() const { return titulo; }
};

#endif // ENTITIES_CURSO_H
```

**Evitar includes circulares:**

```cpp
// ✅ CORRECTO - Forward declaration cuando sea posible
#ifndef ENTITIES_ESTUDIANTE_H
#define ENTITIES_ESTUDIANTE_H

#include <string>
#include <vector>

// Forward declaration en lugar de #include "Curso.h"
class Curso;

class Estudiante {
private:
    std::vector<Curso*> cursosInscritos; // Punteros para forward declaration

public:
    void inscribirseEnCurso(Curso* curso);
    const std::vector<Curso*>& getCursos() const;
};

#endif // ENTITIES_ESTUDIANTE_H
```

### 6.3 Orden de Includes

**Jerarquía estricta para evitar conflictos:**

```cpp
// 1. Headers estándar de C++
#include <iostream>
#include <string>
#include <vector>

// 2. Headers de terceros (si los hubiera)
// #include <third_party_lib.h>

// 3. Headers del proyecto - Controllers primero
#include "Headers/Controllers/Controladora.h"

// 4. Headers del proyecto - por categoría
#include "Headers/DataStructures/BinaryHeap.h"
#include "Headers/Entities/Usuario.h"
#include "Headers/Screens/LoginScreen.h"
#include "Headers/Utils/Validadores.h"
```

### 6.4 Protección de Headers

**Guards obligatorios y consistentes:**

```cpp
// Patrón: CARPETA_ARCHIVO_H
#ifndef CONTROLLERS_CONTROLADORA_H
#define CONTROLLERS_CONTROLADORA_H

// Contenido del header...

#endif // CONTROLLERS_CONTROLADORA_H
```

**Mapping de carpetas a prefijos:**

- `Controllers/` → `CONTROLLERS_`
- `DataStructures/` → `DATASTRUCTURES_`
- `Entities/` → `ENTITIES_`
- `Screens/` → `SCREENS_`
- `Utils/` → `UTILS_`

### 6.5 Implementación Inline

**Métodos simples inline en header:**

```cpp
class Usuario {
private:
    std::string _nombre;
    int _edad;

public:
    // ✅ Inline para getters simples
    const std::string& getNombre() const { return _nombre; }
    int getEdad() const { return _edad; }

    // ✅ Inline para setters con validación simple
    void setEdad(int nuevaEdad) {
        if (nuevaEdad >= 0) _edad = nuevaEdad;
    }

    // ✅ Métodos complejos también inline (arquitectura header-only)
    void actualizarPerfil(const std::string& nuevoNombre, int nuevaEdad) {
        if (!nuevoNombre.empty() && nuevaEdad >= 0) {
            _nombre = nuevoNombre;
            _edad = nuevaEdad;
            std::cout << "Perfil actualizado exitosamente\n";
        } else {
            std::cout << "Error: Datos inválidos\n";
        }
    }
};
```

### 6.6 Manejo de Templates

**Templates siempre en headers:**

```cpp
#ifndef DATASTRUCTURES_BINARYHEAP_H
#define DATASTRUCTURES_BINARYHEAP_H

#include <vector>
#include <functional>

template<typename T, typename Compare = std::less<T>>
class BinaryHeap {
private:
    std::vector<T> _heap;
    Compare _comp;

    void heapifyUp(int index) {
        if (index > 0) {
            int parent = (index - 1) / 2;
            if (_comp(_heap[parent], _heap[index])) {
                std::swap(_heap[parent], _heap[index]);
                heapifyUp(parent);
            }
        }
    }

public:
    BinaryHeap(const Compare& c = Compare()) : _comp(c) {}

    void insert(const T& value) {
        _heap.push_back(value);
        heapifyUp(_heap.size() - 1);
    }

    bool empty() const { return _heap.empty(); }
    size_t size() const { return _heap.size(); }
};

#endif // DATASTRUCTURES_BINARYHEAP_H
```

### 6.7 Organización de Código en Headers

**Estructura estándar para cada header:**

```cpp
#ifndef CARPETA_ARCHIVO_H
#define CARPETA_ARCHIVO_H

// 1. Includes necesarios
#include <iostream>
#include "OtrosHeaders.h"

// 2. Forward declarations
class ClaseRelacionada;

// 3. Constantes y tipos
const int MAX_ELEMENTOS = 100;
using TipoId = unsigned int;

// 4. Clase principal
class MiClase {
private:
    // 4.1 Atributos privados (prefijo _)

public:
    // 4.2 Constructores y destructor

    // 4.3 Métodos públicos principales

    // 4.4 Getters y setters (inline simples)

    // 4.5 Métodos de utilidad (inline si son simples)
};

// 5. Implementaciones inline complejas (fuera de la clase)
inline void MiClase::metodoComplejo() {
    // Implementación detallada aquí
}

#endif // CARPETA_ARCHIVO_H
```

### 6.8 Optimizaciones de Compilación

**Minimizar dependencias innecesarias:**

```cpp
// ❌ EVITAR - Include innecesario
#include "Headers/Entities/Curso.h" // Solo para usar Curso*

// ✅ CORRECTO - Forward declaration
class Curso; // Suficiente para punteros y referencias
```

**Uso inteligente de const y referencias:**

```cpp
// ✅ Evita copias innecesarias
void procesarCursos(const std::vector<Curso>& cursos) {
    for (const auto& curso : cursos) {
        // Procesar sin copiar
    }
}
```

### 6.9 Debugging en Arquitectura Header-Only

**Macros de debug condicionales:**

```cpp
#ifdef DEBUG_MODE
    #define DEBUG_PRINT(x) std::cout << "[DEBUG] " << x << std::endl
#else
    #define DEBUG_PRINT(x)
#endif

// Uso en headers
void metodoImportante() {
    DEBUG_PRINT("Ejecutando método importante");
    // Lógica del método...
}
```

### 6.10 Convenciones de Naming para Headers

**Archivos y guards consistentes:**

```
Headers/
├── Controllers/
│   └── Controladora.h          → CONTROLLERS_CONTROLADORA_H
├── DataStructures/
│   ├── BinaryHeap.h           → DATASTRUCTURES_BINARYHEAP_H
│   └── HashMap.h              → DATASTRUCTURES_HASHMAP_H
├── Entities/
│   ├── Usuario.h              → ENTITIES_USUARIO_H
│   └── Curso.h                → ENTITIES_CURSO_H
├── Screens/
│   ├── LoginScreen.h          → SCREENS_LOGINSCREEN_H
│   └── DashboardScreen.h      → SCREENS_DASHBOARDSCREEN_H
└── Utils/
    └── Validadores.h          → UTILS_VALIDADORES_H
```

### 6.11 Gestión de Estado Global

**Evitar variables globales, usar singletons o pasar referencias:**

```cpp
// ❌ EVITAR - Variables globales en headers
extern int globalCounter; // Problemático en header-only

// ✅ CORRECTO - Singleton pattern
class ConfigManager {
private:
    static ConfigManager* _instance;
    int _configValue;

    ConfigManager() : _configValue(0) {}

public:
    static ConfigManager& getInstance() {
        if (!_instance) {
            _instance = new ConfigManager();
        }
        return *_instance;
    }

    int getConfigValue() const { return _configValue; }
    void setConfigValue(int value) { _configValue = value; }
};

// ✅ MEJOR - Pasar referencias explícitamente
void funcionQueNecesitaConfig(const ConfigManager& config) {
    int valor = config.getConfigValue();
    // Usar valor...
}
```

### 6.12 Validación de Arquitectura

**Checklist para cada header:**

- [ ] Header guard correcto (`CARPETA_ARCHIVO_H`)
- [ ] Includes mínimos necesarios
- [ ] Forward declarations donde sea posible
- [ ] Implementación completa inline
- [ ] Atributos privados con prefijo `_`
- [ ] Métodos const donde corresponda
- [ ] Sin variables globales
- [ ] Documentación de métodos complejos

**Herramientas de validación:**

```cpp
// Verificar que header compila solo
// Crear archivo test_header.cpp temporal:
#include "Headers/MiClase.h"
int main() { return 0; }

// Si compila sin errores, el header es auto-contenido
```

---

Esta guía debe ser usada como contexto en todo momento durante la implementacion de nuevo codigo.
