# CourseraClone C++

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)
![Visual Studio](https://img.shields.io/badge/IDE-Visual%20Studio%202022-purple.svg)
![License](https://img.shields.io/badge/License-Academic-green.svg)

</div>

**Versión:** 1.0.0 (Arquitectura Modular)  
**Autores:** Fabrizio Santi, Mauricio Teran, Jahat Trinidad  
**Curso:** Algoritmos y Estructura de Datos  
**Institución:** Universidad Peruana de Ciencias Aplicadas (UPC)

## 📋 Descripción del Proyecto

CourseraClone es una aplicación de consola desarrollada en C++ que simula una plataforma completa de gestión de cursos en línea. Este proyecto académico implementa un sistema robusto que incluye gestión de usuarios, creación y exploración de contenido educativo, sistema de inscripciones, y motor de recomendaciones.

### 🎯 Objetivos del Proyecto

- Implementar estructuras de datos avanzadas desde cero
- Aplicar patrones de diseño y principios SOLID
- Desarrollar una arquitectura modular y escalable
- Optimizar el rendimiento mediante estructuras de datos eficientes

## ✨ Características Principales

### 👥 Gestión de Usuarios

- **Registro e inicio de sesión** para Estudiantes y Organizaciones
- **Perfiles personalizables** con información detallada
- **Sistema de autenticación** robusto y seguro
- **Gestión de sesiones** con persistencia de datos

### 📚 Gestión de Contenido Educativo

- **Creación de Cursos** con clases, descripciones y metadata
- **Especializaciones** que agrupan cursos relacionados
- **Verificación de duplicados** usando Árbol AVL optimizado
- **Sistema de categorías** y etiquetado inteligente

### 🎓 Sistema de Inscripciones

- **Inscripciones automáticas** a cursos y especializaciones
- **Acceso rápido** a datos de inscripción (HashMap)
- **Historial completo** de actividades del estudiante
- **Sistema de boletas** y certificaciones

### 🔍 Exploración y Búsqueda

- **Landing Page** con contenido popular (PriorityQueue)
- **Motor de búsqueda** con filtros avanzados
- **Ordenamiento dinámico** por relevancia, popularidad, etc.
- **Recomendaciones personalizadas** basadas en comportamiento

### 🏗️ Arquitectura del Sistema

- **Patrón MVC** para separación de responsabilidades
- **Sistema de pantallas** modular y reutilizable
- **Controlador centralizado** para gestión de flujo
- **Persistencia de datos** optimizada

## 🛠️ Estructuras de Datos Implementadas

| Estructura         | Uso Principal           | Complejidad    |
| ------------------ | ----------------------- | -------------- |
| `BinaryHeap<T>`    | Sistema de prioridades  | O(log n)       |
| `PriorityQueue<T>` | Contenido popular       | O(log n)       |
| `AVLTree<T>`       | Verificación duplicados | O(log n)       |
| `HashMap<K,V>`     | Acceso rápido a datos   | O(1) promedio  |
| `BST<T>`           | Búsquedas ordenadas     | O(log n)       |
| `LinkedList<T>`    | Colecciones dinámicas   | O(1) inserción |
| `Graph<T>`         | Sistema recomendaciones | O(V + E)       |

## 📁 Estructura del Proyecto

```
CourseraClone/
├── 📄 CourseraClone.sln              # Solución de Visual Studio
├── 📄 README.md                       # Este archivo
├── 📁 Headers/                        # Archivos de cabecera
│   ├── 📁 Controllers/               # Controladores del sistema
│   │   ├── Controladora.h           # Controlador principal
│   │   └── GestionadorCursos.h      # Gestión de cursos
│   ├── 📁 DataStructures/           # Estructuras de datos custom
│   │   ├── BinaryHeap.h            # Heap binario
│   │   ├── HashMap.h               # Tabla hash
│   │   ├── AVLTree.h              # Árbol AVL
│   │   └── ...                     # Otras estructuras
│   ├── 📁 Entities/                # Modelos de datos
│   │   ├── Usuario.h              # Clase base usuario
│   │   ├── Estudiante.h           # Estudiante
│   │   ├── Empresa.h              # Organización
│   │   ├── Curso.h                # Curso
│   │   └── ...                    # Otras entidades
│   ├── 📁 Screens/                # Pantallas del sistema
│   │   ├── LoginScreen.h          # Pantalla login
│   │   ├── DashboardEstudianteScreen.h
│   │   └── ...                    # Otras pantallas
│   └── 📁 Utils/                  # Utilidades del sistema
│       ├── ScreenSystem.h         # Sistema de pantallas
│       ├── UI_Ascii.h            # Interfaz ASCII
│       └── SystemUtils.h         # Utilidades generales
├── 📁 Source/                    # Código fuente
│   └── CourseraCloneApp.cpp     # Punto de entrada
└── 📁 Resources/                # Recursos del proyecto
    ├── 📁 Data/                 # Archivos de datos
    │   ├── usuarios_estudiante.dat
    │   ├── cursos_muestra.txt
    │   └── ...
    ├── 📁 Backup/              # Respaldos
    └── 📁 Documentation/       # Documentación
        ├── Guia de Estilo de Codigo.md
        └── Plan de implementacion.md
```

## 🚀 Instalación y Configuración

### 📋 Prerrequisitos

- **Visual Studio 2022** o superior
- **Compilador MSVC** con soporte C++17
- **Windows 10/11** (requerido para `conio.h` y APIs de Windows)
- **Mínimo 4GB RAM** para compilación óptima

### ⚙️ Compilación

1. **Clonar el repositorio:**

   ```bash
   git clone [URL_DEL_REPOSITORIO]
   cd CourseraClone
   ```

2. **Abrir en Visual Studio:**

   ```bash
   start CourseraClone.sln
   ```

3. **Configurar el proyecto:**

   - Seleccionar configuración `Debug` o `Release`
   - Verificar que la plataforma sea `x64`
   - Asegurar que el SDK de Windows esté instalado

4. **Compilar:**
   - Usar `Ctrl + Shift + B` o
   - Menú: `Build > Build Solution`

### ▶️ Ejecución

```bash
# Navegar al directorio de salida
cd x64/Debug/

# Ejecutar la aplicación
./CourseraClone.exe
```

## 🎮 Guía de Uso

### 🏠 Pantalla Principal

Al iniciar la aplicación, verás la **Landing Page** con:

- Cursos y especializaciones populares
- Opciones de login y registro
- Información del sistema

### 👤 Para Estudiantes

1. **Registro:** Crear cuenta con datos académicos
2. **Explorar:** Buscar cursos y especializaciones
3. **Inscribirse:** Unirse a contenido de interés
4. **Dashboard:** Ver progreso y historial
5. **Perfil:** Gestionar información personal

### 🏢 Para Organizaciones

1. **Registro:** Crear cuenta empresarial
2. **Publicar:** Crear cursos y especializaciones
3. **Gestionar:** Administrar contenido publicado
4. **Analytics:** Ver estadísticas de inscripciones
5. **Perfil:** Mantener información actualizada

## 🔧 Arquitectura Técnica

### 🎯 Patrones de Diseño Implementados

- **MVC (Model-View-Controller):** Separación clara de responsabilidades
- **Screen System:** Navegación modular entre pantallas
- **Template Specialization:** Estructuras de datos genéricas
- **RAII:** Gestión automática de recursos

### 📊 Optimizaciones de Rendimiento

- **Lazy Loading:** Carga de datos bajo demanda
- **Caching Inteligente:** Reducción de accesos a disco
- **Memory Pool:** Gestión eficiente de memoria
- **Algoritmos Optimizados:** Búsquedas y ordenamientos eficientes

### 🛡️ Manejo de Errores

- **Exception Safety:** Código robusto ante errores
- **Input Validation:** Validación exhaustiva de datos
- **Graceful Degradation:** Funcionamiento ante fallas parciales
- **Error Logging:** Registro detallado de errores

## 📈 Métricas del Proyecto

- **Líneas de código:** ~15,000+ LOC
- **Archivos fuente:** 50+ archivos
- **Estructuras de datos:** 8 implementaciones custom
- **Pantallas:** 12 interfaces diferentes
- **Entidades:** 10+ modelos de dominio

## 🤝 Contribuciones

Este es un proyecto académico desarrollado por estudiantes de UPC. Las contribuciones están limitadas a los miembros del equipo de desarrollo.

### 👨‍💻 Equipo de Desarrollo

- **Santi:** Arquitectura del sistema y estructuras de datos
- **Mauricio:** Interfaz de usuario y sistema de pantallas
- **Jahat:** Lógica de negocio y persistencia de datos

## 📝 Licencia

Este proyecto es desarrollado con fines académicos para el curso de Algoritmos y Estructura de Datos de la Universidad Peruana de Ciencias Aplicadas (UPC).

## 🔗 Enlaces Útiles

- [Documentación del Código](Resources/Documentation/)
- [Guía de Estilo](Resources/Documentation/Guia%20de%20Estilo%20de%20Codigo.md)
- [Plan de Implementación](Resources/Documentation/Plan%20de%20implementacion.md)

---

<div align="center">

**Desarrollado con ❤️ por estudiantes de UPC**

</div>
