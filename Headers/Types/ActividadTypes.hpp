// FILEPATH: Headers/Persistence/ActividadTypes.hpp
// Define tipos de datos para las actividades en la persistencia del sistema

#ifndef COURSERACLONE_TYPES_ACTIVIDADTYPES_HPP
#define COURSERACLONE_TYPES_ACTIVIDADTYPES_HPP

// includes del sistema
#include <string>
#include <vector>

// Enumeraci�n para las categor�as de actividades
enum class CategoriaActividad : int{
    DEFAULT, // Categor�a por defecto, no se usa en la pr�ctica

    // Tecnolog�a & Desarrollo
    PROGRAMACION,
    DESARROLLO_WEB,
    DESARROLLO_MOVIL,
    DESARROLLO_JUEGOS,
    SISTEMAS_EMBEBIDOS,
    DEVOPS,
    CLOUD_COMPUTING,
    REDES,
    BASES_DE_DATOS,
    SEGURIDAD_INFORMATICA,
    INTELIGENCIA_ARTIFICIAL,
    CIENCIA_DE_DATOS,
    BLOCKCHAIN,
    IOT,
    REALIDAD_VIRTUAL,
    ROBOTICA,
    UX_UI,

    // Dise�o & Creatividad
    DISENO,
    DISENO_GRAFICO,
    DISENO_INDUSTRIAL,
    ARTE_DIGITAL,
    FOTOGRAFIA,
    VIDEO_ANIMACION,
    MUSICA_SONIDO,
    ESCRITURA_CREATIVA,

    // Negocios & Gesti�n
    NEGOCIOS,
    MARKETING_DIGITAL,
    FINANZAS,
    EMPRENDIMIENTO,
    GESTION_PROYECTOS,
    RECURSOS_HUMANOS,
    CONSULTORIA,
    ECOMMERCE,
    ANALISIS_NEGOCIOS,

    // Ciencias & Educaci�n
    INVESTIGACION,
    BIOTECNOLOGIA,
    INGENIERIA,
    MATEMATICAS,
    FISICA,
    EDUCACION,
    IDIOMAS,
    PSICOLOGIA,

    // Categor�a general
    OTROS
};

// Enum para representar los tipos de actividad
enum class TipoActividad{
	DEFAULT, // Tipo por defecto, no se usa en la pr�ctica
    CURSO,
	ESPECIALIZACION
};

// Forward declaration for FilesManager to use escribirDebugLog
class FilesManager; 

struct RawActividadData{
    // Ahora es un método estático y completo
    static CategoriaActividad stringToCategoria(const std::string& categoriaStr){
        if (categoriaStr == "PROGRAMACION") return CategoriaActividad::PROGRAMACION;
        if (categoriaStr == "DESARROLLO_WEB") return CategoriaActividad::DESARROLLO_WEB;
        if (categoriaStr == "DESARROLLO_MOVIL") return CategoriaActividad::DESARROLLO_MOVIL;
        if (categoriaStr == "DESARROLLO_JUEGOS") return CategoriaActividad::DESARROLLO_JUEGOS;
        if (categoriaStr == "SISTEMAS_EMBEBIDOS") return CategoriaActividad::SISTEMAS_EMBEBIDOS;
        if (categoriaStr == "DEVOPS") return CategoriaActividad::DEVOPS;
        if (categoriaStr == "CLOUD_COMPUTING") return CategoriaActividad::CLOUD_COMPUTING;
        if (categoriaStr == "REDES") return CategoriaActividad::REDES;
        if (categoriaStr == "BASES_DE_DATOS") return CategoriaActividad::BASES_DE_DATOS;
        if (categoriaStr == "SEGURIDAD_INFORMATICA") return CategoriaActividad::SEGURIDAD_INFORMATICA;
        if (categoriaStr == "INTELIGENCIA_ARTIFICIAL") return CategoriaActividad::INTELIGENCIA_ARTIFICIAL;
        if (categoriaStr == "CIENCIA_DE_DATOS") return CategoriaActividad::CIENCIA_DE_DATOS;
        if (categoriaStr == "BLOCKCHAIN") return CategoriaActividad::BLOCKCHAIN;
        if (categoriaStr == "IOT") return CategoriaActividad::IOT;
        if (categoriaStr == "REALIDAD_VIRTUAL") return CategoriaActividad::REALIDAD_VIRTUAL;
        if (categoriaStr == "ROBOTICA") return CategoriaActividad::ROBOTICA;
        if (categoriaStr == "UX_UI") return CategoriaActividad::UX_UI;
        if (categoriaStr == "DISENO") return CategoriaActividad::DISENO;
        if (categoriaStr == "DISENO_GRAFICO") return CategoriaActividad::DISENO_GRAFICO;
        if (categoriaStr == "DISENO_INDUSTRIAL") return CategoriaActividad::DISENO_INDUSTRIAL;
        if (categoriaStr == "ARTE_DIGITAL") return CategoriaActividad::ARTE_DIGITAL;
        if (categoriaStr == "FOTOGRAFIA") return CategoriaActividad::FOTOGRAFIA;
        if (categoriaStr == "VIDEO_ANIMACION") return CategoriaActividad::VIDEO_ANIMACION;
        if (categoriaStr == "MUSICA_SONIDO") return CategoriaActividad::MUSICA_SONIDO;
        if (categoriaStr == "ESCRITURA_CREATIVA") return CategoriaActividad::ESCRITURA_CREATIVA;
        if (categoriaStr == "NEGOCIOS") return CategoriaActividad::NEGOCIOS;
        if (categoriaStr == "MARKETING_DIGITAL") return CategoriaActividad::MARKETING_DIGITAL;
        if (categoriaStr == "FINANZAS") return CategoriaActividad::FINANZAS;
        if (categoriaStr == "EMPRENDIMIENTO") return CategoriaActividad::EMPRENDIMIENTO;
        if (categoriaStr == "GESTION_PROYECTOS") return CategoriaActividad::GESTION_PROYECTOS;
        if (categoriaStr == "RECURSOS_HUMANOS") return CategoriaActividad::RECURSOS_HUMANOS;
        if (categoriaStr == "CONSULTORIA") return CategoriaActividad::CONSULTORIA;
        if (categoriaStr == "ECOMMERCE") return CategoriaActividad::ECOMMERCE;
        if (categoriaStr == "ANALISIS_NEGOCIOS") return CategoriaActividad::ANALISIS_NEGOCIOS;
        if (categoriaStr == "INVESTIGACION") return CategoriaActividad::INVESTIGACION;
        if (categoriaStr == "BIOTECNOLOGIA") return CategoriaActividad::BIOTECNOLOGIA;
        if (categoriaStr == "INGENIERIA") return CategoriaActividad::INGENIERIA;
        if (categoriaStr == "MATEMATICAS") return CategoriaActividad::MATEMATICAS;
        if (categoriaStr == "FISICA") return CategoriaActividad::FISICA;
        if (categoriaStr == "EDUCACION") return CategoriaActividad::EDUCACION;
        if (categoriaStr == "IDIOMAS") return CategoriaActividad::IDIOMAS;
        if (categoriaStr == "PSICOLOGIA") return CategoriaActividad::PSICOLOGIA;
        if (categoriaStr == "OTROS") return CategoriaActividad::OTROS;

        // Log an unknown category before returning OTROS
        // Need to include FilesManager.hpp or provide a logging mechanism if used here directly
        // For now, let's assume FilesManager::getInstance().escribirDebugLog() is accessible
        // Or, even better, avoid direct dependency here. The caller can log if needed.
        // For simplicity, we won't log directly from here to avoid include complexities.
        // Consider logging in FilesManager after this call if the category is OTROS and original string wasn't "OTROS"
        return CategoriaActividad::OTROS; // Default for unknown strings
    }
};

// Datos crudos de un curso le�dos del archivo
struct RawCursoData {
    // Datos generales del curso
    int id;
    int idEmpresa;
    std::string nombreEmpresa;
    std::string titulo;
    std::string descripcion;
    std::string instructor;
    CategoriaActividad categoria;
	std::vector<std::pair<std::string, std::string>> descripcionClases;
    int cantidadClases;
	std::vector<std::string> titulosClases;
	std::vector<std::string> descripcionesClases;
	int duracionEstimada; // Duraci�n en minutos
};

// Datos crudos de una especializaci�n le�dos del archivo
struct RawEspecializacionData {
    int id;
    int idEmpresa;
    std::string nombreEmpresa;
    CategoriaActividad categoria;
    std::string titulo;
    std::string descripcion;
    int cantidadCursos;
    std::vector<int> idsCursos;
    int duracionEstimada;
};

// Estructura para agrupar los datos crudos de todas las actividades
struct RawActividadesData {
    std::vector<RawCursoData> cursos;
    std::vector<RawEspecializacionData> especializaciones;
};



#endif // !COURSERACLONE_TYPES_ACTIVIDADTYPES_HPP