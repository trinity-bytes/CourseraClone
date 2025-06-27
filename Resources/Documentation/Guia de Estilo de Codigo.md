# Guía de Estilo de Código - CourseraClone

**Autor**: Jahat Trinidad  
**Última actualización**: Junio 27, 2025

## Información General

He preparado esta guía para establecer nuestras convenciones de codificación en el proyecto CourseraClone. Está basada en las mejores prácticas del Google C++ Style Guide, pero la he adaptado específicamente para nuestro equipo, priorizando el español para elementos de dominio específico y optimizando para nuestra arquitectura header-only con archivos `.hpp`.

### Principios Fundamentales

- **Consistencia**: Todo nuestro código debe seguir las mismas convenciones
- **Legibilidad**: El código debe ser fácil de leer y entender por cualquier miembro del equipo
- **Mantenibilidad**: Las convenciones deben facilitar el mantenimiento del código a largo plazo
- **Arquitectura Header-Only**: Optimización para nuestra compilación single-file con múltiples headers (`.hpp`)
- **Bilingüismo controlado**: Español para dominio del negocio, inglés para estructuras de datos estándar y términos específicos de la industria
- **Inline por defecto**: Uso estándar de `inline` para optimización en arquitectura header-only
- **Documentación de dependencias**: Control estricto de headers importados con comentarios de uso específico

### Principios Adicionales de Codificación Limpia

Además de los principios fundamentales, he incluido estas pautas para mejorar la calidad de nuestro código:

- **Claridad sobre Concisión Extrema**: Aunque el código conciso es bueno, priorizo la legibilidad. Los nombres de variables, funciones y clases deben ser descriptivos y autoexplicativos.
- **Responsabilidad Única (Simplificado)**:
  - Cada función o método debe realizar una sola tarea específica y hacerla bien.
  - Cada clase debe tener una responsabilidad principal bien definida. Evitamos clases "todopoderosas".
- **`const` Correctness**:
  - Declaro variables como `const` si su valor no cambiará después de la inicialización.
  - Marco los métodos de clase como `const` si no modifican el estado del objeto. Esto ayuda a prevenir errores y puede ser aprovechado por el compilador.
  ```cpp
  class Ejemplo {
      int _valor;
  public:
      inline int getValor() const { return _valor; } // Método const e inline
      inline void setValor(int v) { _valor = v; }
  };
  const int MAX_INTENTOS = 3; // Variable const
  ```
- **Uso de `inline` por defecto**: En nuestra arquitectura header-only, uso `inline` como estándar para funciones pequeñas y métodos para evitar problemas de linkado múltiple.
- **Optimizaciones Header-Only**:
  - Uso `constexpr` para valores que pueden calcularse en tiempo de compilación
  - Implemento template specialization cuando es necesario
  - Evito definiciones globales que puedan causar ODR violations
- **Limitar el Alcance de las Variables**: Declaro las variables en el ámbito (scope) más pequeño posible. Esto reduce la posibilidad de errores por nombres conflictivos y mejora la legibilidad.
- **Inicialización de Variables**: Siempre inicializo las variables antes de su primer uso para evitar comportamientos indefinidos.
- **Uso de `nullptr`**: Para punteros, prefiero `nullptr` (introducido en C++11) en lugar de `0` o `NULL` para mayor seguridad de tipos.
  ```cpp
  Curso* ptrCurso = nullptr;
  ```
- **Bucles Basados en Rango (Range-based for loops)**: Cuando itero sobre colecciones (como `std::vector` o nuestro `LinkedList`), utilizo bucles basados en rango (C++11 en adelante) para un código más limpio y seguro, si la estructura de datos lo soporta directamente o mediante iteradores.
  ```cpp
  std::vector<Estudiante> estudiantes = /* ... */;
  for (const Estudiante& est : estudiantes) {
      // Procesar estudiante
  }
  ```
- **Evitar Variables Globales**: Minimizo el uso de variables globales. Si son necesarias, las encapsulo dentro de una clase o namespace de utilidades y documento claramente su propósito y manejo.

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
CourseManager.hpp
MainController.hpp

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
    // ✅ CORRECTO - Verbos claros y descriptivos con inline
    inline bool inscribirEstudiante(int idEstudiante, int idCurso);
    inline void mostrarCursosDisponibles();
    Curso* buscarCursoPorId(int id); // Funciones complejas sin inline
    vector<Curso> filtrarCursosPorCategoria(const string& categoria);
    bool validarPrerequisitos(int idEstudiante, int idCurso);

    // Getters y Setters - siempre inline
    inline int getId() const { return _id; }
    inline void setId(int _nuevoId) { _id = _nuevoId; }

    inline string getTitulo() const { return _titulo; }
    inline void setTitulo(const string& _nuevoTitulo) { _titulo = _nuevoTitulo; }
};
```

### Funciones de Estructuras de Datos (inglés estándar)

```cpp
template<typename T>
class LinkedList
{
public:
    inline void push_back(const T& elemento);
    inline void push_front(const T& elemento);
    inline T& front();
    inline T& back();
    inline bool empty() const;
    inline size_t size() const;
    void clear(); // Operación compleja sin inline
};
```

---

## 5. Sistema de Comentarios Evolucionado

He evolucionado nuestro sistema de comentarios para ser más eficiente y mantener mejor control de dependencias:

### 5.1 Comentarios de Archivo (Header de archivo)

```cpp
// filepath: Headers/Entities/Usuario.hpp
// description: Clase base para usuarios del sistema, maneja autenticación y datos comunes

#ifndef COURSERACLONE_ENTITIES_USUARIO_HPP
#define COURSERACLONE_ENTITIES_USUARIO_HPP

// Control de dependencias - comentar funciones específicas utilizadas
#include <string>    // string, c_str(), length()
#include <vector>    // vector, push_back(), size()
#include <iostream>  // cout, cin (solo si se usa en este header)
#include <fstream>   // ifstream, ofstream (para operaciones de archivo)

// ...resto del código...
#endif
```

**¿Por qué comentamos las funciones específicas?**

- Nos ayuda a mantener control sobre qué headers realmente necesitamos
- Facilita la limpieza de includes no utilizados
- Mejora los tiempos de compilación al identificar dependencias innecesarias

### 5.2 Comentarios con Anotaciones @ (Doxygen-style)

Usamos anotaciones @ para mejorar la legibilidad y aprovechar el coloreado de nuestra extensión:

```cpp
/**
 * @brief Gestor principal de cursos en el sistema
 * @todo Implementar cache para búsquedas frecuentes
 */
class GestionadorCursos
{
private:
    LinkedList<Curso> _listaCursos;

public:
    /**
     * @brief Busca un curso por ID usando búsqueda binaria
     * @param id Identificador único del curso
     * @return Puntero al curso encontrado o nullptr si no existe
     * @note La lista debe estar ordenada previamente por ID
     */
    Curso* buscarCursoPorId(int id);

    /**
     * @brief Valida que el estudiante cumpla los prerequisitos
     * @param idEstudiante ID del estudiante a validar
     * @param idCurso ID del curso objetivo
     * @return true si cumple los prerequisitos, false en caso contrario
     * @warning Este método es crítico para la integridad del sistema
     */
    bool validarPrerequisitos(int idEstudiante, int idCurso);

    // Getters simples no necesitan documentación @
    inline int getId() const { return _id; }
    inline void setId(int _nuevoId) { _id = _nuevoId; }
};
```

### 5.3 Guía de Cuándo Usar Cada Tipo de Comentario

#### Usar @brief cuando:

- La función/clase tiene lógica compleja
- No es obvio qué hace por el nombre
- Es parte de la API pública principal

#### Usar @param y @return cuando:

- Los parámetros no son auto-explicativos
- El valor de retorno requiere explicación
- Hay múltiples parámetros con significados específicos

#### Usar @todo cuando:

- Hay funcionalidad pendiente de implementar
- Se requieren mejoras de rendimiento
- Hay refactoring planificado

#### Usar @note cuando:

- Hay precondiciones importantes
- Existen efectos secundarios no obvios
- Se requiere contexto adicional

#### Usar @warning cuando:

- La función es crítica para seguridad/integridad
- Hay riesgos de mal uso
- Existen limitaciones importantes

#### NO usar comentarios @ cuando:

- Es un getter/setter simple
- El nombre de la función es completamente descriptivo
- Es código trivial

### 5.4 Comentarios en Línea (Explicar el "por qué", no el "qué")

```cpp
void procesarInscripcion(int idEstudiante, int idCurso)
{
    // Verificar existencia antes de proceder - evita estados inconsistentes
    if (!existeEstudiante(idEstudiante))
    {
        throw std::runtime_error("Estudiante no encontrado");
    }

    // Los prerequisitos son obligatorios por política académica
    if (!validarPrerequisitos(idEstudiante, idCurso))
    {
        return;
    }

    registrarInscripcion(idEstudiante, idCurso);
}
```

### 5.5 Comentarios de Control de Desarrollo

```cpp
// @todo Implementar validación de cupos máximos
// @fixme Corregir duplicación de inscripciones en BD
// @hack Solución temporal para el demo - refactorizar en v2.0
// @performance Este método es crítico - optimizar si supera 1000 elementos
```

### 5.6 Cuándo NO comentar (Evitar ruido)

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

### 5.7 Plantilla de Header Completa

```cpp
// filepath: Headers/Entities/MiClase.hpp
// description: Descripción concisa de qué hace este header y para qué sirve

#ifndef COURSERACLONE_ENTITIES_MICLASE_HPP
#define COURSERACLONE_ENTITIES_MICLASE_HPP

// Librerías estándar - documentar funciones específicas utilizadas
#include <string>    // string, c_str(), length()
#include <vector>    // vector, push_back(), size(), clear()
#include <memory>    // unique_ptr, make_unique()

// Headers del proyecto
#include "../DataStructures/LinkedList.hpp"
#include "Usuario.hpp"

/**
 * @brief Descripción breve de la clase (solo si no es evidente)
 * @todo Tareas pendientes si las hay
 */
class MiClase
{
private:
    // Atributos privados

public:
    // Constructores y destructor

    /**
     * @brief Solo comentar métodos complejos
     * @param parametro Solo si no es obvio
     * @return Solo si requiere explicación
     */
    ReturnType metodoComplejo(TipoParametro parametro);

    // Métodos simples sin comentarios @
    inline int getId() const { return _id; }
};

#endif // COURSERACLONE_ENTITIES_MICLASE_HPP
```

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

## 7. Organización de Archivos y Optimizaciones Header-Only

### Estructura de Archivo .hpp Optimizada

```cpp
// filepath: Headers/Entities/Curso.hpp
// description: Entidad curso con sus clases y actividades, incluye validaciones de prerequisitos

#ifndef COURSERACLONE_ENTITIES_CURSO_HPP
#define COURSERACLONE_ENTITIES_CURSO_HPP

// Librerías estándar - documentar funciones específicas utilizadas
#include <string>    // string, c_str(), length(), find()
#include <vector>    // vector, push_back(), size(), clear(), begin(), end()
#include <iostream>  // cout, cin, getline() (solo si se usa I/O en este header)
#include <memory>    // unique_ptr, make_unique(), shared_ptr

// Headers del proyecto (con rutas relativas)
#include "Actividad.hpp"
#include "../DataStructures/LinkedList.hpp"
#include "../Utils/ValidationHelper.hpp"

// Using statements (solo en .cpp, evitar en .hpp)
// using namespace std; // ❌ EVITAR en archivos .hpp

// Constantes globales con constexpr para optimización
constexpr int MAX_CLASES_POR_CURSO = 50;
constexpr double CALIFICACION_MINIMA = 0.0;
constexpr double CALIFICACION_MAXIMA = 5.0;

/**
 * @brief Entidad que representa un curso en el sistema
 * @todo Implementar sistema de rating por estudiantes
 */
class Curso
{
private:
    // Atributos privados primero
    int _id;
    std::string _titulo;
    LinkedList<Actividad> _actividades;

public:
    // Constructores
    Curso() = default;
    explicit Curso(int id, const std::string& titulo);

    // Destructor
    ~Curso() = default;

    // Métodos públicos (complejos sin inline)
    bool agregarActividad(const Actividad& actividad);
    bool validarPrerequisitos(const std::vector<int>& cursosCompletados) const;

    // Getters y setters inline al final
    inline int getId() const { return _id; }
    inline void setId(int id) { _id = id; }
    inline const std::string& getTitulo() const { return _titulo; }
    inline void setTitulo(const std::string& titulo) { _titulo = titulo; }
};

// Implementaciones inline (para arquitectura header-only)
inline Curso::Curso(int id, const std::string& titulo)
    : _id(id), _titulo(titulo) {}

inline bool Curso::agregarActividad(const Actividad& actividad)
{
    if (_actividades.size() >= MAX_CLASES_POR_CURSO) {
        return false;
    }
    _actividades.push_back(actividad);
    return true;
}

#endif // COURSERACLONE_ENTITIES_CURSO_HPP
```

### 7.1 Optimizaciones Específicas para Header-Only

**Recursos de aprendizaje**:

- Documentación oficial de C++: https://en.cppreference.com/w/cpp/language/inline
- Effective Modern C++ by Scott Meyers (Capítulos sobre constexpr y inline)
- https://isocpp.org/wiki/faq/inline-functions

#### Uso de `constexpr` para Optimización

```cpp
// ✅ CORRECTO - Valores calculables en tiempo de compilación
constexpr int BUFFER_SIZE = 1024;
constexpr double PI = 3.14159265359;
constexpr int calcularHash(const char* str)
{
    // Función constexpr para hashing simple
    int hash = 0;
    while (*str) {
        hash = hash * 31 + *str++;
    }
    return hash;
}

// Uso en tiempo de compilación
constexpr int CURSO_HASH = calcularHash("Curso");
```

#### Template Specialization para Casos Específicos

```cpp
// Template genérico
template<typename T>
class Comparador
{
public:
    static inline bool esIgual(const T& a, const T& b) {
        return a == b;
    }
};

// Especialización para strings (optimización específica)
template<>
class Comparador<std::string>
{
public:
    static inline bool esIgual(const std::string& a, const std::string& b) {
        return a.length() == b.length() && a == b; // Optimización: verificar length primero
    }
};
```

#### Evitar ODR (One Definition Rule) Violations

```cpp
// ❌ INCORRECTO - Puede causar ODR violation
int contadorGlobal = 0; // Definición global en header

// ✅ CORRECTO - Variable global segura
inline int& getContadorGlobal() {
    static int contador = 0;
    return contador;
}

// ✅ CORRECTO - Constante global
constexpr int MAX_USUARIOS = 1000;
```

---

## 8. Control de Dependencias entre Headers

### 8.1 Documentación de Funciones Utilizadas

He implementado un sistema estricto para documentar qué funciones específicas usamos de cada header:

```cpp
// ✅ CORRECTO - Control de dependencias específicas
#include <string>    // string, c_str(), length(), find(), substr()
#include <vector>    // vector, push_back(), size(), clear(), begin(), end()
#include <iostream>  // cout, cin, getline()
#include <fstream>   // ifstream, ofstream, open(), close()
#include <algorithm> // sort(), find(), binary_search()
#include <memory>    // unique_ptr, make_unique(), shared_ptr

// Headers del proyecto
#include "../DataStructures/LinkedList.hpp"  // LinkedList<T>, push_back(), size()
#include "Usuario.hpp"                       // clase Usuario, getId(), getNombre()
```

### 8.2 Beneficios del Control de Dependencias

1. **Tiempo de Compilación**: Identifica headers innecesarios fácilmente
2. **Mantenimiento**: Facilita la limpieza de código legacy
3. **Documentación**: Los nuevos miembros entienden qué se usa de cada library
4. **Refactoring**: Simplifica el proceso de cambiar dependencias

### 8.3 Proceso de Limpieza de Headers

```cpp
// Antes de cada commit, verificar:
// 1. ¿Realmente uso todas las funciones documentadas?
```

---

## 11. Checklist de Revisión de Código Actualizado

Antes de hacer commit, he establecido que debemos verificar:

**Nomenclatura y Estructura:**

- [ ] Los nombres siguen nuestras convenciones (entidades sin sufijo, pantallas con "Screen")
- [ ] Las clases están en la carpeta correcta según su responsabilidad
- [ ] Los sufijos identifican claramente el tipo de clase (Screen, Manager, Utils, Helper)
- [ ] Cada archivo `.hpp` tiene guardianes de cabecera según nuestra convención

**Sistema de Comentarios Evolucionado:**

- [ ] Header del archivo incluye filepath y descripción del propósito
- [ ] Cada librería estándar incluida tiene comentario con funciones específicas utilizadas
- [ ] Solo los métodos complejos tienen comentarios @ (brief, todo, etc.)
- [ ] No hay comentarios obvios que explican código evidente
- [ ] Los getters/setters simples NO tienen comentarios @

**Optimizaciones Header-Only:**

- [ ] Funciones pequeñas y getters/setters usan `inline`
- [ ] Se usa `constexpr` para valores calculables en tiempo de compilación
- [ ] No hay definiciones globales que puedan causar ODR violations
- [ ] Las implementaciones inline están al final del header

**Control de Dependencias:**

- [ ] Todos los `#include` tienen comentarios documentando funciones utilizadas
- [ ] Se prefieren forward declarations cuando es posible
- [ ] No hay headers incluidos sin usar

**Estándar de Código:**

- [ ] No hay magic numbers (usar constantes)
- [ ] Los métodos no son excesivamente largos (< 50 líneas)
- [ ] Se manejan los casos de error apropiadamente
- [ ] La indentación es consistente (4 espacios)
- [ ] No hay `using namespace std;` en archivos `.hpp`
- [ ] Se usa `const` correctness apropiadamente

---

## 12. Recursos de Aprendizaje para Optimizaciones Header-Only

### 12.1 Documentación Oficial y Referencias

**C++ Core Guidelines:**

- https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines
- Secciones específicas sobre `inline`, `constexpr` y header organization

**cppreference.com:**

- https://en.cppreference.com/w/cpp/language/inline (funciones inline)
- https://en.cppreference.com/w/cpp/language/constexpr (constexpr)
- https://en.cppreference.com/w/cpp/language/template_specialization (template specialization)

### 12.2 Libros Recomendados

**Effective Modern C++ by Scott Meyers:**

- Item 15: Use constexpr whenever possible
- Item 30: Familiarize yourself with perfect forwarding failure cases
- Capítulos sobre template metaprogramming

**C++ Templates: The Complete Guide (2nd Edition):**

- Capítulos sobre template specialization
- Optimizaciones para compilación

### 12.3 Artículos Específicos sobre Header-Only Libraries

**Microsoft C++ Documentation:**

- https://docs.microsoft.com/en-us/cpp/cpp/inline-functions-cpp
- https://docs.microsoft.com/en-us/cpp/cpp/constexpr-cpp

**LLVM Coding Standards (para ODR best practices):**

- https://llvm.org/docs/CodingStandards.html#include-style

### 12.4 Herramientas para Análisis de Headers

**Include What You Use (IWYU):**

- https://include-what-you-use.org/
- Herramienta para detectar headers innecesarios

**Clang Static Analyzer:**

- Para detectar posibles ODR violations
- Análisis de dependencias circulares

---

## 13. Referencias y Recursos Adicionales

### 13.1 Guías de Estilo Base

- **Google C++ Style Guide**: https://google.github.io/styleguide/cppguide.html#Header_Files
- **C++ Core Guidelines**: https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines
- **cppreference.com**: https://en.cppreference.com/

### 13.2 Arquitectura Header-Only

- **Effective Modern C++** by Scott Meyers - Items sobre inline y constexpr
- **LLVM Coding Standards**: https://llvm.org/docs/CodingStandards.html#include-style
- **Microsoft C++ Inline Functions**: https://docs.microsoft.com/en-us/cpp/cpp/inline-functions-cpp

### 13.3 Documentación con Doxygen

- **Doxygen Manual**: https://www.doxygen.nl/manual/docblocks.html
- **Doxygen Special Commands**: https://www.doxygen.nl/manual/commands.html
- Nuestra extensión VS Code colorea automáticamente los @ commands para mejor legibilidad

### 13.4 Optimización y Performance

- **C++ Templates: The Complete Guide** (2nd Edition) - Template specialization
- **Include What You Use (IWYU)**: https://include-what-you-use.org/
- **Clang Static Analyzer**: Para detectar ODR violations

### 13.5 Herramientas de Desarrollo

- **cppreference offline**: Para consulta rápida sin internet
- **Compiler Explorer**: https://godbolt.org/ para verificar optimizaciones inline
- **Quick Bench**: https://quick-bench.com/ para micro-benchmarking

---

**Notas finales:**

Esta guía representa la evolución de nuestro estilo de código basado en nuestra experiencia práctica como equipo. He incluido todas las optimizaciones que hemos descubierto son efectivas para nuestra arquitectura header-only.

Recuerden que la consistencia es más importante que la perfección individual.

**Última actualización**: Junio 27, 2025  
**Próxima revisión programada**: Julio 2025
