#ifndef COURSERACLONE_UTILS_CONTENTGENERATOR_HPP
#define COURSERACLONE_UTILS_CONTENTGENERATOR_HPP

// Headers estándar
#include <string>
#include <vector>
#include <map>
#include <random>
#include <ctime>

// Headers propios
#include "../Types/ActividadTypes.hpp"
#include "../Controllers/SessionManager.hpp"

/// @brief Generador automático de contenido educativo
class ContentGenerator
{
public:
    /// @brief Genera datos completos para un nuevo curso
    /// @param tituloUsuario Título proporcionado por el usuario (opcional)
    /// @param descripcionUsuario Descripción proporcionada por el usuario (opcional)  
    /// @param precioUsuario Precio proporcionado por el usuario (opcional)
    /// @param duracionUsuario Duración proporcionada por el usuario (opcional)
    /// @return RawCursoData con todos los datos generados
    static RawCursoData generarCurso(
        const std::string& tituloUsuario,
        const std::string& descripcionUsuario, 
        const std::string& precioUsuario,
        const std::string& duracionUsuario
    );
    
    /// @brief Genera datos completos para una nueva especialización
    /// @param tituloUsuario Título proporcionado por el usuario (opcional)
    /// @param descripcionUsuario Descripción proporcionada por el usuario (opcional)
    /// @param duracionUsuario Duración proporcionada por el usuario (opcional)
    /// @return RawEspecializacionData con todos los datos generados
    static RawEspecializacionData generarEspecializacion(
        const std::string& tituloUsuario,
        const std::string& descripcionUsuario,
        const std::string& precioUsuario,
        const std::string& duracionUsuario
    );

    /// @brief Crea cursos automáticamente para una especialización
    /// @param categoria Categoría de la especialización
    /// @param idEmpresa ID de la empresa
    /// @param nombreEmpresa Nombre de la empresa
    /// @param tituloBase Título base para los cursos
    /// @param cantidadCursos Cantidad de cursos a crear
    /// @return Vector con IDs de los cursos creados
    static std::vector<int> crearCursosParaEspecializacion(
        CategoriaActividad categoria,
        int idEmpresa,
        const std::string& nombreEmpresa,
        const std::string& tituloBase,
        int cantidadCursos
    );

private:
    // ===== UTILIDADES DE GENERACIÓN =====
    
    /// @brief Selecciona una categoría aleatoria
    static CategoriaActividad seleccionarCategoriaAleatoria();
    
    /// @brief Genera o valida el título
    static std::string generarTitulo(const std::string& tituloUsuario, CategoriaActividad categoria);
    
    /// @brief Genera o valida la descripción
    static std::string generarDescripcion(const std::string& descripcionUsuario, CategoriaActividad categoria);
    
    /// @brief Selecciona un instructor aleatorio
    static std::string generarInstructor();
    
    /// @brief Genera clases para un curso (máximo 5)
    static std::vector<std::pair<std::string, std::string>> generarClases(CategoriaActividad categoria, int cantidad = 5);
    
    /// @brief Genera o valida el precio
    static double generarPrecio(const std::string& precioUsuario);
    
    /// @brief Genera o valida la duración
    static int generarDuracion(const std::string& duracionUsuario, bool esCurso = true);
    
    /// @brief Obtiene información de la empresa de la sesión actual
    static std::pair<int, std::string> obtenerInfoEmpresa();
    
    /// @brief Obtiene un número aleatorio en un rango
    static int randomInt(int min, int max);

    // ===== DATOS ESTÁTICOS =====
    
    /// @brief Pool de instructores disponibles
    static const std::vector<std::string> INSTRUCTORES;
    
    /// @brief Títulos por categoría
    static const std::map<CategoriaActividad, std::vector<std::string>> TITULOS_POR_CATEGORIA;
    
    /// @brief Descripciones por categoría
    static const std::map<CategoriaActividad, std::vector<std::string>> DESCRIPCIONES_POR_CATEGORIA;
    
    /// @brief Tópicos de clases por categoría
    static const std::map<CategoriaActividad, std::vector<std::string>> CLASES_POR_CATEGORIA;
    
    /// @brief Categorías disponibles para selección aleatoria
    static const std::vector<CategoriaActividad> CATEGORIAS_DISPONIBLES;
};

// ===== DATOS ESTÁTICOS (DEFINICIONES) =====

// Pool de instructores
const std::vector<std::string> ContentGenerator::INSTRUCTORES = {
    "Dr. Mario García", "Ing. Ana López", "Prof. Carlos Mendoza", "Dra. Elena Vásquez",
    "Ing. Pedro Ramírez", "Prof. Lucia Santos", "Dr. Roberto Silva", "Ing. Sofia Torres",
    "Prof. Daniel Herrera", "Dra. Carmen Flores", "Ing. Miguel Ángel Castro", "Prof. Valeria Ruiz",
    "Dr. Fernando Morales", "Ing. Alejandra Díaz", "Prof. Gabriel Romero", "Dra. Isabella Cruz",
    "Ing. Diego Martínez", "Prof. Camila Jiménez", "Dr. Andrés Guerrero", "Ing. Natalia Vargas"
};

// Categorías disponibles
const std::vector<CategoriaActividad> ContentGenerator::CATEGORIAS_DISPONIBLES = {
    CategoriaActividad::PROGRAMACION,
    CategoriaActividad::DESARROLLO_WEB,
    CategoriaActividad::CIENCIA_DE_DATOS,
    CategoriaActividad::INTELIGENCIA_ARTIFICIAL,
    CategoriaActividad::DISENO,
    CategoriaActividad::MARKETING_DIGITAL,
    CategoriaActividad::NEGOCIOS
};

// Títulos por categoría
const std::map<CategoriaActividad, std::vector<std::string>> ContentGenerator::TITULOS_POR_CATEGORIA = {
    {CategoriaActividad::PROGRAMACION, {
        "Fundamentos de Python", "Java para Principiantes", "C++ Avanzado", 
        "Algoritmos y Estructuras de Datos", "Introducción a la Programación"
    }},
    {CategoriaActividad::DESARROLLO_WEB, {
        "HTML y CSS Básico", "JavaScript Moderno", "React para Principiantes",
        "Desarrollo Backend con Node.js", "Full Stack Web Development"
    }},
    {CategoriaActividad::CIENCIA_DE_DATOS, {
        "Análisis de Datos con Python", "Machine Learning Básico", "Estadística Aplicada",
        "Data Science Fundamentals", "Big Data Analytics"
    }},
    {CategoriaActividad::INTELIGENCIA_ARTIFICIAL, {
        "Introducción a la IA", "Deep Learning con TensorFlow", "Computer Vision",
        "Procesamiento de Lenguaje Natural", "AI para Negocios"
    }},
    {CategoriaActividad::DISENO, {
        "Diseño Gráfico Digital", "UX/UI Design", "Adobe Creative Suite",
        "Diseño Web Responsive", "Branding y Identidad Visual"
    }},
    {CategoriaActividad::MARKETING_DIGITAL, {
        "Marketing en Redes Sociales", "SEO y SEM", "Google Analytics",
        "Email Marketing", "Marketing de Contenidos"
    }},
    {CategoriaActividad::NEGOCIOS, {
        "Gestión de Proyectos", "Finanzas Empresariales", "Liderazgo y Gestión",
        "Emprendimiento Digital", "Estrategia Empresarial"
    }}
};

// Descripciones por categoría  
const std::map<CategoriaActividad, std::vector<std::string>> ContentGenerator::DESCRIPCIONES_POR_CATEGORIA = {
    {CategoriaActividad::PROGRAMACION, {
        "Aprende las bases de la programación con ejercicios prácticos",
        "Domina los conceptos fundamentales del desarrollo de software",
        "Curso completo de programación desde cero hasta nivel avanzado"
    }},
    {CategoriaActividad::DESARROLLO_WEB, {
        "Crea sitios web modernos y responsivos",
        "Aprende las tecnologías web más demandadas del mercado",
        "Conviértete en desarrollador web full-stack"
    }},
    {CategoriaActividad::CIENCIA_DE_DATOS, {
        "Analiza datos y extrae insights valiosos para tu empresa",
        "Aprende machine learning y estadística aplicada",
        "Domina las herramientas de análisis de datos más populares"
    }},
    {CategoriaActividad::INTELIGENCIA_ARTIFICIAL, {
        "Introducción práctica al mundo de la inteligencia artificial",
        "Desarrolla soluciones inteligentes con IA",
        "Aplica algoritmos de machine learning en proyectos reales"
    }},
    {CategoriaActividad::DISENO, {
        "Crea diseños impactantes y profesionales",
        "Aprende los principios del diseño visual y UX",
        "Domina las herramientas de diseño más utilizadas"
    }},
    {CategoriaActividad::MARKETING_DIGITAL, {
        "Potencia tu presencia digital y aumenta tus ventas",
        "Aprende las estrategias de marketing más efectivas",
        "Domina las plataformas digitales para hacer crecer tu negocio"
    }},
    {CategoriaActividad::NEGOCIOS, {
        "Desarrolla habilidades empresariales y de liderazgo",
        "Aprende a gestionar proyectos y equipos eficientemente",
        "Construye y hace crecer tu empresa con estrategias probadas"
    }}
};

// Tópicos de clases por categoría
const std::map<CategoriaActividad, std::vector<std::string>> ContentGenerator::CLASES_POR_CATEGORIA = {
    {CategoriaActividad::PROGRAMACION, {
        "Variables y tipos de datos|Aprende los conceptos básicos de variables",
        "Estructuras de control|Domina if, while y for loops",
        "Funciones y métodos|Organiza tu código con funciones",
        "Programación orientada a objetos|Clases, objetos y herencia",
        "Manejo de errores|Debugging y manejo de excepciones"
    }},
    {CategoriaActividad::DESARROLLO_WEB, {
        "HTML básico y semántico|Estructura tu contenido web",
        "CSS y diseño responsivo|Estiliza y adapta tu sitio",
        "JavaScript fundamentals|Interactividad en el navegador", 
        "Frameworks modernos|React, Vue o Angular",
        "Deploy y hosting|Publica tu sitio web"
    }},
    {CategoriaActividad::CIENCIA_DE_DATOS, {
        "Pandas y manipulación de datos|Limpia y transforma datos",
        "Visualización con matplotlib|Crea gráficos informativos",
        "Estadística descriptiva|Analiza y resume datos",
        "Machine Learning básico|Algoritmos de clasificación",
        "Proyectos prácticos|Aplica lo aprendido"
    }},
    {CategoriaActividad::INTELIGENCIA_ARTIFICIAL, {
        "Introducción a la IA|Conceptos y aplicaciones",
        "Algoritmos de ML|Regresión y clasificación",
        "Redes neuronales|Deep learning básico",
        "Computer Vision|Procesamiento de imágenes",
        "Proyecto final|Implementa tu propia IA"
    }},
    {CategoriaActividad::DISENO, {
        "Principios de diseño|Teoría del color y composición",
        "Herramientas digitales|Photoshop, Illustrator, Figma",
        "Diseño de interfaces|UX/UI principles",
        "Branding y logotipos|Identidad visual",
        "Portfolio profesional|Presenta tu trabajo"
    }},
    {CategoriaActividad::MARKETING_DIGITAL, {
        "Estrategia digital|Planifica tu presencia online",
        "Redes sociales|Facebook, Instagram, LinkedIn",
        "SEO básico|Optimización en buscadores",
        "Google Ads|Publicidad pagada efectiva",
        "Analítica web|Mide y optimiza resultados"
    }},
    {CategoriaActividad::NEGOCIOS, {
        "Planificación estratégica|Define objetivos y metas",
        "Gestión de equipos|Liderazgo efectivo",
        "Finanzas básicas|Presupuestos y análisis",
        "Marketing y ventas|Atrae y retén clientes",
        "Escalabilidad|Haz crecer tu negocio"
    }}
};

// ===== IMPLEMENTACIONES =====

inline RawCursoData ContentGenerator::generarCurso(
    const std::string& tituloUsuario,
    const std::string& descripcionUsuario, 
    const std::string& precioUsuario,
    const std::string& duracionUsuario)
{
    // Seleccionar categoría aleatoria
    CategoriaActividad categoria = seleccionarCategoriaAleatoria();
    
    // Obtener información de la empresa
    auto [idEmpresa, nombreEmpresa] = obtenerInfoEmpresa();
    
    // Generar datos
    std::string titulo = generarTitulo(tituloUsuario, categoria);
    std::string descripcion = generarDescripcion(descripcionUsuario, categoria);
    std::string instructor = generarInstructor();
    double precio = generarPrecio(precioUsuario);
    int duracion = generarDuracion(duracionUsuario, true);
    
    // Generar clases (máximo 5)
    auto clases = generarClases(categoria, 5);
    
    // Crear estructura de datos
    RawCursoData datos;
    datos.id = 0; // Se asignará automáticamente
    datos.idEmpresa = idEmpresa;
    datos.nombreEmpresa = nombreEmpresa;
    datos.categoria = categoria;
    datos.titulo = titulo;
    datos.descripcion = descripcion;
    datos.instructor = instructor;
    datos.precio = precio;
    datos.cantidadClases = static_cast<int>(clases.size());
    datos.duracionEstimada = duracion * 60; // Convertir horas a minutos
    
    // Asignar directamente las clases como pares (título, descripción)
    datos.descripcionClases = clases;
    
    return datos;
}

inline RawEspecializacionData ContentGenerator::generarEspecializacion(
    const std::string& tituloUsuario,
    const std::string& descripcionUsuario,
    const std::string& precioUsuario,
    const std::string& duracionUsuario)
{
    // Seleccionar categoría aleatoria
    CategoriaActividad categoria = seleccionarCategoriaAleatoria();
    
    // Obtener información de la empresa
    auto [idEmpresa, nombreEmpresa] = obtenerInfoEmpresa();
    
    // Generar datos básicos
    std::string titulo = generarTitulo(tituloUsuario, categoria);
    std::string descripcion = generarDescripcion(descripcionUsuario, categoria);
    int duracion = generarDuracion(duracionUsuario, false);
    
    // Generar cursos para la especialización (1 a 4 cursos)
    int cantidadCursos = randomInt(1, 4);
    
    // Crear cursos usando el método auxiliar
    std::vector<int> idsCursos = crearCursosParaEspecializacion(
        categoria, idEmpresa, nombreEmpresa, titulo, cantidadCursos
    );
    
	double precio = generarPrecio(precioUsuario) + 40;

    // Crear estructura de datos
    RawEspecializacionData datos;
    datos.id = 0; // Se asignará automáticamente
    datos.idEmpresa = idEmpresa;
    datos.nombreEmpresa = nombreEmpresa;
    datos.categoria = categoria;
    datos.titulo = titulo;
	datos.precio = precio;
    datos.descripcion = descripcion;
    datos.cantidadCursos = cantidadCursos;
    datos.idsCursos = idsCursos;
    datos.duracionEstimada = duracion;
    
    return datos;
}

inline CategoriaActividad ContentGenerator::seleccionarCategoriaAleatoria()
{
    return CATEGORIAS_DISPONIBLES[randomInt(0, CATEGORIAS_DISPONIBLES.size() - 1)];
}

inline std::string ContentGenerator::generarTitulo(const std::string& tituloUsuario, CategoriaActividad categoria)
{
    if (!tituloUsuario.empty()) {
        return tituloUsuario;
    }
    
    const auto& titulos = TITULOS_POR_CATEGORIA.at(categoria);
    return titulos[randomInt(0, titulos.size() - 1)];
}

inline std::string ContentGenerator::generarDescripcion(const std::string& descripcionUsuario, CategoriaActividad categoria)
{
    if (!descripcionUsuario.empty()) {
        return descripcionUsuario;
    }
    
    const auto& descripciones = DESCRIPCIONES_POR_CATEGORIA.at(categoria);
    return descripciones[randomInt(0, descripciones.size() - 1)];
}

inline std::string ContentGenerator::generarInstructor()
{
    return INSTRUCTORES[randomInt(0, INSTRUCTORES.size() - 1)];
}

inline std::vector<std::pair<std::string, std::string>> ContentGenerator::generarClases(CategoriaActividad categoria, int cantidad)
{
    std::vector<std::pair<std::string, std::string>> clases;
    const auto& clasesDisponibles = CLASES_POR_CATEGORIA.at(categoria);
    
    // Limitar a máximo 5 clases
    int numClases = (std::min)(cantidad, (std::min)(5, static_cast<int>(clasesDisponibles.size())));
    
    for (int i = 0; i < numClases; i++) {
        std::string claseCompleta = clasesDisponibles[i];
        
        // Separar título y descripción por el delimitador '|'
        size_t separador = claseCompleta.find('|');
        if (separador != std::string::npos) {
            std::string titulo = claseCompleta.substr(0, separador);
            std::string descripcion = claseCompleta.substr(separador + 1);
            clases.push_back({titulo, descripcion});
        }
    }
    
    return clases;
}

inline double ContentGenerator::generarPrecio(const std::string& precioUsuario)
{
    if (!precioUsuario.empty()) {
        try {
            return std::stod(precioUsuario);
        } catch (...) {
            // Si no se puede convertir, generar precio aleatorio
        }
    }
    
    // Generar precio entre 50 y 500 soles
    return static_cast<double>(randomInt(20, 40));
}

inline int ContentGenerator::generarDuracion(const std::string& duracionUsuario, bool esCurso)
{
    if (!duracionUsuario.empty()) {
        try {
            return std::stoi(duracionUsuario);
        } catch (...) {
            // Si no se puede convertir, generar duración aleatoria
        }
    }
    
    if (esCurso) {
        // Cursos: 10-50 horas
        return randomInt(10, 50);
    } else {
        // Especializaciones: 8-24 semanas
        return randomInt(8, 24);
    }
}

inline std::pair<int, std::string> ContentGenerator::obtenerInfoEmpresa()
{
    // Intentar obtener de SessionManager
    try {
        if (SessionManager::getInstance().isLoggedIn()) {
            Usuario& currentUser = SessionManager::getInstance().getCurrentUser();
            int userId = currentUser.getId();
            std::string userName = currentUser.getNombreCompleto();
            
            // Para organizaciones, usamos el ID del usuario como ID de empresa
            // y el nombre completo como nombre de la empresa
            return {userId, userName};
        }
    } catch (...) {
        // Fallback si hay error
    }
    
    // Datos por defecto
    return {1, "Tech Education Corp"};
}

inline int ContentGenerator::randomInt(int min, int max)
{
    srand(time(NULL));
    return rand() % (max - min + 1) + min;
}

inline std::vector<int> ContentGenerator::crearCursosParaEspecializacion(
    CategoriaActividad categoria,
    int idEmpresa,
    const std::string& nombreEmpresa,
    const std::string& tituloBase,
    int cantidadCursos)
{
    std::vector<int> idsCursos;
    
    // Usar IDs secuenciales para cursos de especialización
    static int siguienteIdCursoEsp = 10000;
    
    for (int i = 0; i < cantidadCursos; i++) {
        // Generar datos para el curso
        std::string tituloCurso = tituloBase + " - Módulo " + std::to_string(i + 1);
        std::string instructor = generarInstructor();
        std::string descripcionCurso = generarDescripcion("", categoria);
        
        // Generar clases específicas para el módulo
        auto clases = generarClases(categoria, 3 + (i % 3)); // Entre 3-5 clases por módulo
        
        // Crear datos del curso
        RawCursoData cursoDatos;
        cursoDatos.id = siguienteIdCursoEsp++;
        cursoDatos.idEmpresa = idEmpresa;
        cursoDatos.nombreEmpresa = nombreEmpresa;
        cursoDatos.categoria = categoria;
        cursoDatos.titulo = tituloCurso;
        cursoDatos.descripcion = descripcionCurso;
        cursoDatos.instructor = instructor;
        cursoDatos.cantidadClases = static_cast<int>(clases.size());
        cursoDatos.duracionEstimada = randomInt(8, 15) * 60; // 8-15 horas en minutos
        cursoDatos.descripcionClases = clases;
        
        // Guardar el ID del curso
        idsCursos.push_back(cursoDatos.id);
    }
    
    return idsCursos;
}

#endif // COURSERACLONE_UTILS_CONTENTGENERATOR_HPP
