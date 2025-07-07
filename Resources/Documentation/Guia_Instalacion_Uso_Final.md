# Guía de Instalación y Uso - CourseraClone

**Fecha:** 7 de julio de 2025  
**Versión:** 2.0.0 (Versión Final)  
**Estado:** ✅ PROYECTO COMPLETADO

---

## 📋 Prerrequisitos del Sistema

### 🖥️ Requisitos Mínimos

- **Sistema Operativo:** Windows 10 o superior
- **Compilador:** Visual Studio 2022 con MSVC
- **Estándar C++:** C++17 o superior
- **RAM:** Mínimo 4GB (recomendado 8GB)
- **Espacio en disco:** 500MB libres
- **Resolución:** 1920x1080 recomendado para mejor visualización

### 📦 Software Necesario

1. **Visual Studio 2022** (Community, Professional, o Enterprise)

   - Instalar workload "Desktop development with C++"
   - Incluir Windows SDK más reciente
   - Asegurar que MSVC esté instalado

2. **Git** (opcional, para clonar el repositorio)

---

## 🚀 Instalación Paso a Paso

### 1. Obtener el Código Fuente

#### Opción A: Clonar desde repositorio

```bash
git clone [URL_DEL_REPOSITORIO]
cd CourseraClone
```

#### Opción B: Descargar ZIP

1. Descargar el archivo ZIP del proyecto
2. Extraer en la ubicación deseada
3. Navegar a la carpeta del proyecto

### 2. Configurar el Proyecto

1. **Abrir Visual Studio 2022**
2. **File → Open → Project/Solution**
3. Seleccionar `CourseraClone.sln`
4. Esperar a que Visual Studio cargue el proyecto

### 3. Configurar la Compilación

1. **Seleccionar configuración:**

   - Para desarrollo: `Debug | x64`
   - Para producción: `Release | x64`

2. **Verificar propiedades del proyecto:**
   - Clic derecho en el proyecto → Properties
   - **Configuration Properties → C/C++ → Language**
   - **C++ Language Standard:** ISO C++17 Standard
   - **Configuration Properties → Linker → System**
   - **SubSystem:** Console

### 4. Compilar el Proyecto

```bash
# Método 1: Desde Visual Studio
Build → Build Solution (Ctrl+Shift+B)

# Método 2: Desde línea de comandos
msbuild CourseraClone.sln /p:Configuration=Release /p:Platform=x64
```

### 5. Verificar la Compilación

- Verificar que no haya errores en la ventana de Output
- El ejecutable debe generarse en: `x64/Debug/CourseraClone.exe` o `x64/Release/CourseraClone.exe`

---

## ▶️ Ejecución de la Aplicación

### 🎮 Desde Visual Studio

1. **Establecer como proyecto de inicio:** Clic derecho → Set as StartUp Project
2. **Ejecutar:** F5 (con debugging) o Ctrl+F5 (sin debugging)

### 🖥️ Desde Línea de Comandos

```bash
# Navegar al directorio de salida
cd x64/Debug/
# o
cd x64/Release/

# Ejecutar la aplicación
CourseraClone.exe
```

### 🗂️ Desde Windows Explorer

1. Navegar a `x64/Debug/` o `x64/Release/`
2. Hacer doble clic en `CourseraClone.exe`

---

## 🎯 Primeros Pasos en la Aplicación

### 🏠 Pantalla Principal

Al iniciar la aplicación, verás:

1. **Arte ASCII del logo CourseraClone**
2. **Cursos populares** (cargados desde PriorityQueue)
3. **Menú principal** con opciones:
   - `1` - Iniciar Sesión
   - `2` - Registrarse
   - `3` - Explorar Contenido (como invitado)
   - `4` - Sobre Nosotros
   - `0` - Salir

### 👤 Registro de Usuario

#### Para Estudiantes:

1. Seleccionar `2` - Registrarse
2. Seleccionar `1` - Estudiante
3. Completar el formulario:
   - Nombre completo
   - Email (con validación)
   - Contraseña segura
   - Teléfono (opcional)
   - Fecha de nacimiento
   - Carrera/Especialidad

#### Para Organizaciones:

1. Seleccionar `2` - Registrarse
2. Seleccionar `2` - Organización
3. Completar el formulario:
   - Nombre de la organización
   - Email corporativo
   - Contraseña segura
   - RUC (con validación)
   - Teléfono corporativo
   - Dirección

### 🔐 Inicio de Sesión

1. Seleccionar `1` - Iniciar Sesión
2. Ingresar email y contraseña
3. El sistema te dirigirá al dashboard correspondiente

---

## 🎮 Funcionalidades Principales

### 📊 Dashboard de Estudiante

**Opciones disponibles:**

- `1` - Explorar Cursos
- `2` - Mis Inscripciones
- `3` - Mi Perfil
- `4` - Mis Certificados
- `5` - Ver Boletas
- `6` - Actividades Recientes
- `0` - Cerrar Sesión

### 🏢 Dashboard de Organización

**Opciones disponibles:**

- `1` - Crear Contenido
- `2` - Gestionar Contenido
- `3` - Ver Estadísticas
- `4` - Mi Perfil
- `5` - Reportes Financieros
- `6` - Actividades Recientes
- `0` - Cerrar Sesión

### 🔍 Explorar Contenido

**Funcionalidades del motor de búsqueda:**

- Búsqueda por texto libre
- Filtros por categoría
- Filtros por organización
- Ordenamiento por:
  - Popularidad
  - Fecha de publicación
  - Precio (menor a mayor)
  - Alfabético

### 💳 Sistema de Inscripciones

1. **Seleccionar curso o especialización**
2. **Ver detalles completos**
3. **Procesar pago:**
   - Seleccionar método de pago
   - Confirmar transacción
   - Generar comprobante automáticamente
4. **Inscripción automática**
5. **Acceso inmediato al contenido**

### 📜 Certificados con QR

**Generación automática:**

- Al completar un curso
- Certificado único con código QR
- Validación de autenticidad
- Datos del estudiante y curso
- Timestamp de finalización

---

## 🛠️ Gestión de Datos

### 📁 Estructura de Archivos

```
Resources/
├── Data/
│   ├── Content/      # Cursos y especializaciones
│   ├── Core/         # Usuarios y datos centrales
│   ├── Financial/    # Transacciones y comprobantes
│   ├── Index/        # Índices de búsqueda
│   └── Logs/         # Logs del sistema
└── Backup/           # Respaldos automáticos
```

### 🔄 Backup Automático

- El sistema crea respaldos automáticamente
- Frecuencia: Al iniciar y cerrar la aplicación
- Ubicación: `Resources/Backup/`
- Formato: Archivos JSON con timestamp

### 📊 Logs del Sistema

- Todas las operaciones se registran en `Resources/Data/Logs/`
- Incluye: Logins, inscripciones, creación de contenido, errores
- Formato: Texto plano con timestamps

---

## 🔧 Resolución de Problemas

### ❌ Errores Comunes

#### Error: "No se puede abrir el archivo"

**Solución:**

1. Verificar que las carpetas `Resources/Data/` existen
2. Ejecutar la aplicación como administrador
3. Verificar permisos de escritura en la carpeta

#### Error: "Fallo en la compilación"

**Solución:**

1. Verificar que tienes Visual Studio 2022 con MSVC
2. Limpiar solución: Build → Clean Solution
3. Recompilar: Build → Rebuild Solution

#### Error: "Pantalla en blanco o caracteres extraños"

**Solución:**

1. Verificar que la consola de Windows está configurada en UTF-8
2. Ejecutar: `chcp 65001` en cmd antes de ejecutar
3. Usar Windows Terminal para mejor compatibilidad

### 🐛 Debugging

1. **Compilar en modo Debug:**

   ```bash
   Configuration: Debug | x64
   ```

2. **Ejecutar con debugging:**

   ```bash
   F5 en Visual Studio
   ```

3. **Verificar logs:**
   ```bash
   # Revisar archivos en:
   Resources/Data/Logs/
   ```

---

## 📈 Casos de Uso Ejemplos

### 🎓 Caso de Uso: Estudiante Completo

1. **Registro como estudiante**
2. **Explorar cursos de "Programación"**
3. **Inscribirse en "Curso de C++"**
4. **Completar el curso**
5. **Descargar certificado con QR**
6. **Verificar certificado**

### 🏢 Caso de Uso: Organización Completa

1. **Registro como organización**
2. **Crear especialización "Desarrollo Full-Stack"**
3. **Agregar 3 cursos a la especialización**
4. **Publicar contenido**
5. **Monitorear inscripciones**
6. **Generar reporte financiero**

### 🔍 Caso de Uso: Búsqueda Avanzada

1. **Acceder como invitado**
2. **Buscar "Python" en el motor de búsqueda**
3. **Aplicar filtro por categoría "Programación"**
4. **Ordenar por popularidad**
5. **Ver detalles de curso seleccionado**

---

## 🧪 Datos de Prueba

### 📊 Usuarios Predefinidos

**Estudiante de prueba:**

- Email: `estudiante@test.com`
- Contraseña: `123456`

**Organización de prueba:**

- Email: `org@test.com`
- Contraseña: `123456`

### 📚 Contenido Preinstalado

- **5 cursos** de diferentes categorías
- **2 especializaciones** completas
- **Datos de inscripciones** de ejemplo
- **Certificados** de muestra

### 🔄 Resetear Datos

Para resetear todos los datos:

1. Eliminar la carpeta `Resources/Data/`
2. Ejecutar la aplicación
3. El sistema regenerará datos iniciales

---

## 📞 Soporte y Contacto

### 👨‍💻 Equipo de Desarrollo

- **Fabrizio Santi** - Arquitectura y Estructuras de Datos
- **Mauricio Teran** - Interfaces y Sistema de Búsqueda
- **Jahat Trinidad** - Algoritmos y Utilidades

### 📧 Contacto Académico

**Universidad Peruana de Ciencias Aplicadas (UPC)**  
**Curso:** Algoritmos y Estructura de Datos  
**Semestre:** 2025-1

---

## 📚 Recursos Adicionales

### 📖 Documentación

- [README.md](../../README.md) - Información general del proyecto
- [Entendiendo el proyecto.md](Entendiendo%20el%20proyecto.md) - Arquitectura técnica
- [Guia de Estilo de Codigo.md](Guia%20de%20Estilo%20de%20Codigo.md) - Estándares de código

### 🎨 Recursos de Diseño

- [Paleta de Colores Coursera.md](Paleta%20de%20Colores%20Coursera.md) - Colores del sistema
- [UI_Ascii.hpp](../../Headers/Utils/UI_Ascii.hpp) - Arte ASCII

### 🔧 Herramientas de Desarrollo

- **Visual Studio 2022** - IDE principal
- **Git** - Control de versiones
- **Windows Terminal** - Terminal mejorado

---

<div align="center">

## ✅ PROYECTO COMPLETADO EXITOSAMENTE

**CourseraClone v2.0.0**

_Desarrollado por estudiantes de UPC_  
_Julio 2025_

</div>
