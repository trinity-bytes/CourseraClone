# Guía de Estilo de Código - CourseraClone

## Información General

Esta guía establece las convenciones de codificación para el proyecto CourseraClone, basada en las mejores prácticas de Google C++ Style Guide, adaptada para nuestro equipo y priorizando nuestro idioma español para elementos de dominio específico.

### Principios Fundamentales

- **Consistencia**: Todo el código debe seguir las mismas convenciones
- **Legibilidad**: El código debe ser fácil de leer y entender
- **Mantenibilidad**: Las convenciones deben facilitar el mantenimiento del código
- **Bilingüismo controlado**: Español para dominio del negocio, inglés para estructuras de datos estándar y terminos especificos de la industria.

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
LoginScreen.h
RegistroScreen.h
DashboardEstudianteScreen.h
MostrarCursoScreen.h
ExplorarCursosScreen.h

// ✅ CORRECTO - Controladores/Gestores identificables
GestionadorCursos.h
Controladora.h
CourseManager.h

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

Esta guía debe ser usada como contexto en todo momento durante la implementacion de nuevo codigo.
