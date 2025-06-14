// FILEPATH: Headers/Persistence/ActividadTypes.hpp
// Define tipos de datos para las actividades en la persistencia del sistema

#ifndef COURSERACLONE_TYPES_ACTIVIDADTYPES_HPP
#define COURSERACLONE_TYPES_ACTIVIDADTYPES_HPP

// includes del sistema
#include <string>
#include <vector>

// Enum para representar los tipos de actividad
enum class TipoActividad
{
	DEFAULT, // Tipo por defecto, no se usa en la pr�ctica
    CURSO,
	ESPECIALIZACION
};

// Datos crudos de un curso le�dos del archivo
struct RawCursoData 
{
    // Datos generales del curso
    int id;
    int idEmpresa;
    std::string nombreEmpresa;
    std::string titulo;
    std::string descripcion;
    std::string instructor;
    CategoriaActividad categoria;
    int cantidadClases;
};

// Datos crudos de una especializaci�n le�dos del archivo
struct RawEspecializacionData 
{
    int id;
    int idEmpresa;
    const std::string nombreEmpresa;
    CategoriaActividad categoria;
    const std::string titulo;
    const std::string descripcion;
    const std::vector<int> idsCursos;
    int duracionEstimada;
};

// Estructura para agrupar los datos crudos de todas las actividades
struct RawActividadesData 
{
    std::vector<RawCursoData> cursos;
    std::vector<RawEspecializacionData> especializaciones;
};

// Enumeraci�n para las categor�as de actividades
enum class CategoriaActividad
{
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
    DISE�O,
    DISE�O_GRAFICO,
    DISE�O_INDUSTRIAL,
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

#endif // !COURSERACLONE_TYPES_ACTIVIDADTYPES_HPP