#ifndef COURSERACLONE_PERSISTENCE_INSCRIPCIONTYPES_HPP
#define COURSERACLONE_PERSISTENCE_INSCRIPCIONTYPES_HPP

#include "ActividadTypes.hpp"
static constexpr int MAX_DATE_LEN_INS = 11;

struct RawInscripcionData{
    int id;
    int idEstudiante;
    int idActividad;
    TipoActividad tipo;
    double progreso;
    bool completado;
    bool pagado;
    std::string fechaInicio;
    std::string fechaFinal;
};

struct RawInscripcionElementoDash {
    int idActividad;
    int idInscripcion;
    TipoActividad tipo;
};

struct ElementoInscripcion {
    int idActividad = -1; // ID de la actividad (curso o especialización)
    int idInscripcion = -1;
    std::string titulo; // Título de la actividad
    std::string descripcion; // Descripción de la actividad
    bool activo = true; // Indica si el elemento está activo
    TipoActividad tipo;

    ElementoInscripcion() = default;

    ElementoInscripcion(const std::string& _titulo, const std::string& _descripcion, int _idActividad = -1, int _idInscripcion = -1, TipoActividad _tipo = TipoActividad::DEFAULT)
        : titulo(_titulo), descripcion(_descripcion), idActividad(_idActividad), idInscripcion(_idInscripcion), tipo(_tipo) {
    }
};

struct InscripcionContenido {
    int idActividad;
    std::string nombre;
    bool completado;
    bool pagado;
    bool esEspecializacion;

    InscripcionContenido() = default;

	InscripcionContenido(const std::string& _nombre, int _idActividad = -1, bool _completado = false, bool _pagado = false, bool _esEspecializacion = false)
		: nombre(_nombre), idActividad(_idActividad), completado(_completado), pagado(_pagado), esEspecializacion(_esEspecializacion) {
	}

    bool operator<(const InscripcionContenido& otro) const{
        if (idActividad != otro.idActividad)
            return idActividad < otro.idActividad;
        return nombre < otro.nombre;
    }
};

// Estructura para índice de inscripciones en disco (.dat)
struct InscripcionIndex {
    int idUsuario;
    int offset;

    InscripcionIndex(int _idUsuario, int _offset)
        : idUsuario(_idUsuario), offset(_offset) {}
    InscripcionIndex() : idUsuario(0), offset(0) {}
};

// Estructura para inscripciones (registro principal) en disco
struct InscripcionBinaria {
    int id;
    int idEstudiante;
    int idActividad;
    int tipoActividad;
    double progreso;
    bool completado;
    bool pagado;
    char fechaInicio[MAX_DATE_LEN_INS];
    char fechaFinal[MAX_DATE_LEN_INS];

    InscripcionBinaria(int _idUsuario, int _idActividad, int _tipoActividad,
        double _progreso, bool _completado, bool _pagado,
        const std::string& _fechaInicio, const std::string& _fechaFinal)
        : idEstudiante(_idUsuario), idActividad(_idActividad),
        tipoActividad(_tipoActividad), progreso(_progreso),
        completado(_completado), pagado(_pagado)
    {
        std::strncpy(fechaInicio, _fechaInicio.c_str(), MAX_DATE_LEN_INS - 1);
        std::strncpy(fechaFinal, _fechaFinal.c_str(), MAX_DATE_LEN_INS - 1);
        fechaInicio[MAX_DATE_LEN_INS - 1] = '\0';
        fechaFinal[MAX_DATE_LEN_INS - 1] = '\0';
    }

    InscripcionBinaria()
        : idEstudiante(0), idActividad(0), tipoActividad(0), progreso(0.0),
          completado(false), pagado(false) {
        std::memset(fechaInicio, 0, MAX_DATE_LEN_INS);
        std::memset(fechaFinal, 0, MAX_DATE_LEN_INS);
    }
};

#endif // COURSERACLONE_PERSISTENCE_INSCRIPCIONTYPES_HPP
