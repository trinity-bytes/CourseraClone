# CourseraClone C++

<div align="center">

![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)
![Visual Studio](https://img.shields.io/badge/IDE-Visual%20Studio%202022-purple.svg)
![License](https://img.shields.io/badge/License-Academic-green.svg)

</div>

**Versión:** 2.0.0 (Versión Final - Desarrollo Completado)  
**Autores:** Fabrizio Santi, Mauricio Teran, Jahat Trinidad  
**Curso:** Algoritmos y Estructura de Datos  
**Institución:** Universidad Peruana de Ciencias Aplicadas (UPC)  
**Fecha de Finalización:** Julio 2025

## 📋 Descripción del Proyecto

CourseraClone es una aplicación de consola desarrollada en C++ que simula una plataforma completa de gestión de cursos en línea. Este proyecto académico implementa un sistema robusto que incluye gestión de usuarios, creación y exploración de contenido educativo, sistema de inscripciones, procesamiento de pagos, y generación de certificados con códigos QR.

### 🎯 Objetivos del Proyecto

- ✅ Implementar estructuras de datos avanzadas desde cero (AVL, HashMap, PriorityQueue, BST, LinkedList)
- ✅ Aplicar patrones de diseño modernos y principios SOLID
- ✅ Desarrollar una arquitectura modular, escalable y mantenible
- ✅ Optimizar el rendimiento mediante algoritmos eficientes
- ✅ Crear una experiencia de usuario fluida en consola
- ✅ Implementar sistema completo de autenticación y autorización
- ✅ Integrar sistema de códigos QR para certificados
- ✅ Desarrollar sistema de reportes y estadísticas

### 🆕 Funcionalidades Implementadas (Versión Final)

- **🏗️ Arquitectura completa:** Sistema modular con separación clara de responsabilidades
- **📁 Organización optimizada:** Estructura `Headers/` con subdirectorios especializados
- **🎮 Sistema de controladores:** `MainController`, `ContentManager`, `InscripcionesController`, `SessionManager`, `FilesManager`
- **📊 Gestión avanzada de datos:** Persistencia optimizada con índices y backup automático
- **🎨 Sistema de tipos completo:** Enumeraciones y tipos específicos para mayor claridad
- **💾 Gestión robusta de archivos:** Estructura de datos organizada por categorías
- **🔐 Sistema de autenticación:** Login seguro con gestión de sesiones
- **📊 Dashboard interactivo:** Interfaces personalizadas para estudiantes y organizaciones
- **🔍 Motor de búsqueda avanzado:** Algoritmos optimizados con filtros múltiples
- **📜 Sistema de certificados:** Generación automática con códigos QR únicos
- **💰 Procesamiento de pagos:** Sistema completo de ventas y comprobantes
- **📈 Estadísticas en tiempo real:** Reportes detallados para organizaciones

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

### 🎓 Sistema de Inscripciones y Pagos

- **Inscripciones automáticas** a cursos y especializaciones
- **Acceso rápido** a datos de inscripción (HashTable optimizada)
- **Historial completo** de actividades del estudiante
- **Sistema de comprobantes** y certificaciones
- **Procesamiento de ventas** con registro detallado
- **Gestión de boletas** integrada al sistema

### 🔍 Exploración y Búsqueda Avanzada

- **Landing Page** con contenido popular (PriorityQueue)
- **Motor de búsqueda** con algoritmos de ordenamiento personalizados
- **Filtros dinámicos** por categoría, organización, y popularidad
- **Recomendaciones personalizadas** basadas en comportamiento
- **Algoritmos de búsqueda** optimizados para diferentes criterios
- **Búsqueda por texto** con coincidencias parciales
- **Ordenamiento múltiple** por fecha, popularidad, precio, y calificación

### 📜 Sistema de Certificados con QR

- **Generación automática** de certificados al completar cursos
- **Códigos QR únicos** para verificación de autenticidad
- **Integración con datos reales** del estudiante y curso
- **Validación avanzada** con timestamps y hashes de seguridad
- **Exportación optimizada** con formato estándar
- **Sistema de verificación** mediante lectura de QR

### 💰 Sistema Financiero Completo

- **Procesamiento de pagos** con validación de métodos
- **Generación de comprobantes** con datos fiscales
- **Historial de transacciones** completo
- **Reportes financieros** para organizaciones
- **Gestión de descuentos** y promociones
- **Análisis de ventas** con métricas detalladas

### 🏗️ Arquitectura del Sistema

- **Patrón MVC mejorado** con controladores especializados
- **Sistema de pantallas** modular y extensible
- **Controlador principal** (`MainController`) para gestión de flujo
- **Gestores especializados** (`ContentManager`, `FilesManager`)
- **Persistencia de datos** optimizada por categorías
- **Sistema de tipos** robusto con enumeraciones específicas

## 🛠️ Estructuras de Datos Implementadas

| Estructura               | Uso Principal               | Complejidad    | Estado          | Implementación   |
| ------------------------ | --------------------------- | -------------- | --------------- | ---------------- |
| `ArbolAVL<T>`            | Verificación duplicados     | O(log n)       | ✅ Completo     | Autobalanceado   |
| `BinaryHeap<T>`          | Sistema de prioridades      | O(log n)       | ✅ Completo     | Min/Max Heap     |
| `PriorityQueue<T>`       | Contenido popular           | O(log n)       | ✅ Completo     | Basado en Heap   |
| `HashTable<K,V>`         | Acceso rápido a datos       | O(1) promedio  | ✅ Completo     | Chaining         |
| `BinarySearchTree<T>`    | Búsquedas ordenadas         | O(log n)       | ✅ Completo     | In-order         |
| `LinkedList<T>`          | Colecciones dinámicas       | O(1) inserción | ✅ Completo     | Doubly-linked    |
| `Queue<T>`               | Procesamiento en orden      | O(1)           | ✅ Completo     | FIFO             |
| `Stack<T>`               | Historial y navegación      | O(1)           | ✅ Completo     | LIFO             |
| `Grafo<T>`               | Relaciones entre entidades  | O(V + E)       | ✅ Completo     | Lista adyacencia |
| **Algoritmos Avanzados** | **Búsqueda y Ordenamiento** | **Variable**   | **✅ Completo** | **Optimizados**  |

### 🧮 Algoritmos Implementados

- **Algoritmos de Búsqueda:** Binaria, secuencial, por texto, y búsquedas especializadas
- **Algoritmos de Ordenamiento:** QuickSort, MergeSort, HeapSort, BubbleSort optimizados
- **Algoritmos de Hash:** Funciones hash personalizadas para diferentes tipos de datos
- **Algoritmos de Balanceo:** Rotaciones AVL y rebalanceo automático
- **Algoritmos de Grafos:** BFS, DFS para relaciones entre entidades
- **Algoritmos de Validación:** Validación de emails, teléfonos, datos fiscales
- **Algoritmos de Encriptación:** Hashing seguro para contraseñas y QR codes

## 📁 Estructura del Proyecto

```
CourseraClone/
├── 📄 CourseraClone.sln              # Solución de Visual Studio
├── 📄 CourseraClone.vcxproj          # Proyecto de Visual Studio
├── 📄 README.md                       # Este archivo
├── 📁 Headers/                        # Archivos de cabecera organizados
│   ├── 📁 Controllers/               # Controladores del sistema
│   │   ├── MainController.hpp       # Controlador principal de la app
│   │   ├── ContentManager.hpp       # Gestión de contenido educativo
│   │   ├── FilesManager.hpp         # Gestión de archivos y persistencia
│   │   ├── InscripcionesController.hpp # Controlador de inscripciones
│   │   ├── SessionManager.hpp       # Gestión de sesiones y autenticación
│   │   └── ActividadesController.hpp # Controlador de actividades
│   ├── 📁 DataStructures/           # Estructuras de datos implementadas
│   │   ├── ArbolAVL.hpp            # Árbol AVL balanceado
│   │   ├── BinaryHeap.hpp          # Heap binario min/max
│   │   ├── HashTable.hpp           # Tabla hash optimizada
│   │   ├── BinarySearchTree.hpp    # Árbol binario de búsqueda
│   │   ├── LinkedList.hpp          # Lista enlazada genérica
│   │   ├── PriorityQueue.hpp       # Cola de prioridad
│   │   ├── Queue.hpp               # Cola FIFO
│   │   ├── Stack.hpp               # Pila LIFO
│   │   ├── Grafo.hpp               # Grafo con lista de adyacencia
│   │   ├── algoritmosBusqueda.hpp  # Algoritmos de búsqueda
│   │   ├── algoritmosOrdenamiento.hpp # Algoritmos de ordenamiento
│   │   └── ...                     # Nodos y entidades auxiliares
│   ├── 📁 Entities/                # Modelos de datos del dominio
│   │   ├── Usuario.hpp             # Clase base usuario
│   │   ├── Estudiante.hpp          # Modelo estudiante
│   │   ├── Empresa.hpp             # Modelo organización
│   │   ├── Curso.hpp               # Modelo curso
│   │   ├── Especializacion.hpp     # Modelo especialización
│   │   ├── Inscripcion.hpp         # Modelo inscripción
│   │   ├── Actividad.hpp           # Modelo actividad
│   │   ├── ComprobanteDePago.hpp   # Modelo comprobante
│   │   ├── Certificado.hpp         # Modelo certificado
│   │   ├── Venta.hpp               # Modelo venta
│   │   ├── Estadistica.hpp         # Modelo estadísticas
│   │   └── Clase.hpp               # Modelo clase/lección
│   ├── 📁 Screens/                 # Pantallas del sistema
│   │   ├── LandingPageScreen.hpp   # Pantalla principal
│   │   ├── LoginScreen.hpp         # Pantalla de login
│   │   ├── RegistroScreen.hpp      # Pantalla de registro
│   │   ├── DashboardEstudianteScreen.hpp    # Dashboard estudiante
│   │   ├── DashboardOrganizacionScreen.hpp # Dashboard organización
│   │   ├── ExplorarContenidoScreen.hpp     # Explorar cursos
│   │   ├── MostrarCursoScreen.hpp          # Detalles del curso
│   │   ├── MostrarEspecialidadScreen.hpp   # Detalles especialización
│   │   ├── PerfilEstudianteScreen.hpp      # Perfil estudiante
│   │   ├── PerfilOrganizacionScreen.hpp    # Perfil organización
│   │   ├── EditarPerfilScreen.hpp          # Edición de perfil
│   │   ├── CrearContenidoScreen.hpp        # Crear cursos/especializaciones
│   │   ├── ListarContenidoScreen.hpp       # Listar contenido propio
│   │   ├── ListarMisInscripciones.hpp      # Mis inscripciones
│   │   ├── EstadisticasEmpresaScreen.hpp   # Estadísticas empresa
│   │   ├── VerCertificadosScreen.hpp       # Ver certificados
│   │   ├── VerBoletasScreen.hpp            # Visualizar boletas
│   │   └── SobreNosotrosScreen.hpp         # Información del sistema
│   ├── 📁 Types/                   # Tipos y enumeraciones
│   │   ├── UsuarioTypes.hpp        # Tipos de usuario
│   │   ├── ScreenTypes.hpp         # Tipos de pantalla
│   │   ├── InscripcionTypes.hpp    # Tipos de inscripción
│   │   ├── ActividadTypes.hpp      # Tipos de actividad
│   │   ├── FilesTypes.hpp          # Tipos de archivos
│   │   └── ComprobanteDePagoTypes.hpp # Tipos de comprobante
│   └── 📁 Utils/                   # Utilidades del sistema
│       ├── ScreenSystem.hpp        # Sistema de navegación
│       ├── ConsoleRenderer.hpp     # Renderizado de consola
│       ├── ConsoleConfig.hpp       # Configuración de consola
│       ├── ColorPalette.hpp        # Paleta de colores
│       ├── UI_Ascii.hpp           # Arte ASCII
│       ├── SystemUtils.hpp        # Utilidades del sistema
│       ├── InputUtils.hpp         # Utilidades de entrada
│       ├── ValidationUtils.hpp    # Validación de datos
│       ├── DataPaths.hpp          # Rutas de archivos
│       ├── DateTime.hpp           # Manejo de fechas
│       ├── ContentGenerator.hpp   # Generador de contenido
│       ├── GeneradorDatos.hpp     # Generador de datos de prueba
│       ├── Lambda.hpp             # Funciones lambda auxiliares
│       └── 📁 QR/                 # Utilidades para códigos QR
│           ├── QRGenerator.hpp    # Generador de QR
│           ├── QRValidator.hpp    # Validador de QR
│           └── QRUtils.hpp        # Utilidades QR
├── 📁 Source/                     # Código fuente principal
│   └── CourseraCloneApp.cpp       # Punto de entrada de la aplicación
├── 📁 Resources/                  # Recursos del proyecto
│   ├── 📁 Data/                   # Archivos de datos organizados
│   │   ├── 📁 Content/           # Datos de contenido educativo
│   │   ├── 📁 Core/              # Datos centrales del sistema
│   │   ├── 📁 Financial/         # Datos financieros y ventas
│   │   ├── 📁 Index/             # Índices para búsquedas
│   │   ├── 📁 Logs/              # Archivos de registro
│   │   └── 📁 Backup/            # Copias de seguridad automáticas
│   ├── 📁 Backup/                # Respaldos automáticos
│   └── 📁 Documentation/         # Documentación del proyecto
│       ├── Guia de Estilo de Codigo.md
│       ├── Plan de implementacion.md
│       ├── Entendiendo el proyecto.md
│       ├── Implementacion_QR_Certificados.md
│       ├── Logs_Sistema_Modificaciones.md
│       └── ...                   # Otros documentos técnicos
└── 📁 x64/                       # Archivos compilados
    └── 📁 Debug/                 # Versión de debug
        └── CourseraClone.exe     # Ejecutable principal
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

- Cursos y especializaciones populares (ordenados por PriorityQueue)
- Opciones de login y registro con validación avanzada
- Información del sistema y estadísticas en tiempo real
- Navegación intuitiva con sistema de colores Coursera

### 👤 Para Estudiantes

1. **Registro:** Crear cuenta con validación de datos académicos
2. **Explorar:** Buscar cursos con filtros avanzados y algoritmos de ordenamiento
3. **Inscribirse:** Sistema automatizado con verificación de duplicados (AVL)
4. **Dashboard:** Interfaz personalizada con progreso y recomendaciones
5. **Perfil:** Gestión completa de información personal
6. **Actividades:** Tracking detallado de todas las acciones realizadas

### 🏢 Para Organizaciones

1. **Registro:** Crear cuenta empresarial con validación
2. **Publicar:** Crear cursos y especializaciones con sistema AVL
3. **Gestionar:** Administrar contenido con `ContentManager`
4. **Analytics:** Ver estadísticas de inscripciones y ventas
5. **Perfil:** Mantener información actualizada
6. **Finanzas:** Acceder a reportes de ventas y comprobantes

## 🔧 Arquitectura Técnica

### 🎯 Patrones de Diseño Implementados

- **MVC Especializado:** Controladores específicos por dominio
- **Screen System Avanzado:** Navegación fluida con estados persistentes
- **Template Specialization:** Estructuras de datos genéricas y tipo-seguras
- **RAII:** Gestión automática de recursos y memoria
- **Strategy Pattern:** Algoritmos intercambiables de búsqueda y ordenamiento
- **Factory Pattern:** Creación dinámica de pantallas y entidades

### 📊 Optimizaciones de Rendimiento

- **Lazy Loading:** Carga de datos bajo demanda con caching inteligente
- **Memory Pool:** Gestión eficiente de memoria para estructuras grandes
- **Algoritmos Optimizados:** Búsquedas O(log n) y ordenamientos eficientes
- **File Buffering:** Acceso optimizado a archivos de datos
- **Hash Table Tuning:** Funciones hash optimizadas por tipo de dato
- **AVL Tree Balancing:** Rebalanceo automático para mantener eficiencia

### 🛡️ Manejo de Errores y Validación

- **Exception Safety:** Código robusto con manejo de excepciones completo
- **Input Validation:** Validación exhaustiva con `ValidationUtils`
- **Type Safety:** Sistema de tipos estricto con enumeraciones
- **Data Integrity:** Verificación de integridad en persistencia
- **Error Logging:** Sistema de logs detallado en `Resources/Data/Logs/`
- **Graceful Recovery:** Recuperación automática ante errores no críticos

### 🚀 Nuevas Funcionalidades Técnicas (v2.0)

#### 🗂️ Sistema de Gestión de Archivos Avanzado

- **Organización por categorías:** Datos separados en Content, Core, Financial
- **Índices automáticos:** Sistema de indexación para búsquedas rápidas
- **Backup automático:** Respaldos periódicos en `Resources/Backup/`
- **Logging completo:** Registro detallado de todas las operaciones

#### 🎯 Sistema de Tipos Robusto

- **Enumeraciones específicas:** Tipos seguros para cada dominio
- **Validación en tiempo de compilación:** Detección temprana de errores
- **Interfaces claramente definidas:** Contratos explícitos entre módulos

#### 🔍 Algoritmos de Búsqueda y Ordenamiento Optimizados

- **Búsqueda binaria:** Para datos ordenados con O(log n)
- **QuickSort optimizado:** Con pivote inteligente y fallback a HeapSort
- **MergeSort estable:** Para mantener orden relativo de elementos iguales
- **Algoritmos híbridos:** Selección automática según tamaño de datos

#### 🏗️ Arquitectura de Controladores Especializados

- **MainController:** Gestión global de la aplicación y navegación
- **ContentManager:** Especializado en gestión de contenido educativo
- **InscripcionesController:** Manejo específico de inscripciones y actividades
- **FilesManager:** Abstracción completa del sistema de archivos

## 📈 Métricas del Proyecto (Versión Final)

- **Líneas de código:** ~27,000+ LOC (proyecto completado)
- **Archivos fuente:** 74+ archivos organizados por dominio
- **Estructuras de datos:** 12+ implementaciones desde cero
- **Pantallas funcionales:** 15 interfaces completas
- **Entidades del dominio:** 12+ modelos de datos
- **Controladores:** 6 controladores especializados
- **Algoritmos implementados:** 20+ algoritmos de búsqueda y ordenamiento
- **Tipos definidos:** 6+ enumeraciones y tipos específicos
- **Utilidades:** 15+ módulos de utilidades
- **Sistema QR:** 5 módulos para generación y validación
- **Cobertura de funcionalidades:** 100% de los casos de uso implementados
- **Tiempo de desarrollo:** 3 meses de desarrollo intensivo

### 📊 Distribución de Código por Módulo

| Módulo         | Archivos | LOC Aprox. | Complejidad | Completado  |
| -------------- | -------- | ---------- | ----------- | ----------- |
| DataStructures | 15       | 8,000      | Alta        | ✅ 100%     |
| Screens        | 15       | 6,500      | Media       | ✅ 100%     |
| Entities       | 12       | 3,500      | Media       | ✅ 100%     |
| Controllers    | 6        | 4,000      | Alta        | ✅ 100%     |
| Utils          | 15       | 3,000      | Media       | ✅ 100%     |
| Types          | 6        | 800        | Baja        | ✅ 100%     |
| QR System      | 5        | 1,200      | Media       | ✅ 100%     |
| **Total**      | **74**   | **27,000** | **-**       | **✅ 100%** |

## 🤝 Contribuciones

Este es un proyecto académico desarrollado por estudiantes de UPC. Las contribuciones están limitadas a los miembros del equipo de desarrollo.

### 👨‍💻 Equipo de Desarrollo

- **Fabrizio Santi:** Arquitectura del sistema, estructuras de datos avanzadas (AVL, Heap, PriorityQueue), sistema de pantallas principales, motor de búsqueda
- **Mauricio Teran:** Sistema de búsquedas, HashTable, BST, interfaces de usuario, sistema de inscripciones, dashboard de organizaciones
- **Jahat Trinidad:** Algoritmos de ordenamiento y búsqueda, LinkedList, persistencia de datos, validaciones y utilidades, sistema de códigos QR, gestión de archivos

### 🏆 Logros del Proyecto

- ✅ **Implementación completa** de todas las funcionalidades planificadas
- ✅ **Arquitectura robusta** con patrones de diseño profesionales
- ✅ **Performance optimizada** con estructuras de datos eficientes
- ✅ **Sistema QR innovador** para certificados únicos
- ✅ **Experiencia de usuario excepcional** en entorno de consola
- ✅ **Documentación completa** para mantenimiento futuro
- ✅ **Código limpio y mantenible** siguiendo mejores prácticas

## 📝 Licencia

Este proyecto es desarrollado con fines académicos para el curso de Algoritmos y Estructura de Datos de la Universidad Peruana de Ciencias Aplicadas (UPC).

## 🔗 Enlaces Útiles

- [Documentación del Código](Resources/Documentation/)
- [Guía de Estilo](Resources/Documentation/Guia%20de%20Estilo%20de%20Codigo.md)
- [Plan de Implementación](Resources/Documentation/Plan%20de%20implementacion.md)
- [Logs del Sistema](Resources/Documentation/Logs_Sistema_Modificaciones.md)
- [Entendiendo el Proyecto](Resources/Documentation/Entendiendo%20el%20proyecto.md)

- [Implementación QR Certificados](Resources/Documentation/Implementacion_QR_Certificados.md)
- [Ejemplo Práctico QR](Resources/Documentation/Ejemplo_Practico_QR.md)
- [Integración QR con Datos](Resources/Documentation/Integracion_QR_Datos_Reales.md)
- [Optimizaciones QR](Resources/Documentation/Optimizaciones_QR.md)

### 🎨 Recursos Adicionales

- [Paleta de Colores](Resources/Documentation/Paleta%20de%20Colores%20Coursera.md)
- [Formato JSON Estándar](Resources/Documentation/Formato_JSON_Estandar.md)
- [Datos de Prueba](Resources/Data/)
- [Archivos de Backup](Resources/Backup/)
- [Logs del Sistema](Resources/Data/Logs/)

---

<div align="center">

**Desarrollado con ❤️ por estudiantes de UPC**  
_Proyecto académico completado - Algoritmos y Estructura de Datos_  
_Universidad Peruana de Ciencias Aplicadas_

**Versión Final completada:** Julio 2025  
**Estado del proyecto:** ✅ TERMINADO - Todas las funcionalidades implementadas

</div>
