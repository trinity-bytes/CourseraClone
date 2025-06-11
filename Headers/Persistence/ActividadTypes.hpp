// FILEPATH: Headers/Persistence/ActividadTypes.hpp
// Define tipos de datos para las actividades en la persistencia del sistema

#ifndef COURSERACLONE_PERSISTENCE_ACTIVIDADTYPES_HPP
#define COURSERACLONE_PERSISTENCE_ACTIVIDADTYPES_HPP

// includes del sistema
#include <string>
#include <vector>

// Enum para representar los tipos de actividad
enum class TipoActividad
{
    CURSO = 1,
	ESPECIALIZACION = 2
};

// Datos crudos de un curso leídos del archivo
struct RawCursoData 
{
    // Datos generales del curso
    int id;
    int idEmpresa;
    std::string nombreEmpresa;
    std::string titulo;
    std::string descripcion;
    std::string instructor;
    std::string categoria;
    int cantidadClases;
};

// Datos crudos de una especialización leídos del archivo
struct RawEspecializacionData 
{
    int idEmpresa;
    std::string nombreEmpresa;
    std::string tituloActividad;
    std::string descripcionActividad;
    int cantidadCursosEnEspecializacion;
    std::vector<int> idsCursosInternos;
};

// Estructura para agrupar los datos crudos de todas las actividades
struct RawActividadesData 
{
    std::vector<RawCursoData> cursos;
    std::vector<RawEspecializacionData> especializaciones;
};

#endif // !COURSERACLONE_PERSISTENCE_ACTIVIDADTYPES_HPP