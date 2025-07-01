#ifndef COURSERACLONE_PERSISTENCE_INSCRIPCIONTYPES_HPP
#define COURSERACLONE_PERSISTENCE_INSCRIPCIONTYPES_HPP

#include "ActividadTypes.hpp"

struct RawInscripcionData{
    int id;
    int idEstudiante;
    int idActividad;
    TipoActividad tipo;
    double progreso;
    bool completado;
    bool pagado;
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

    InscripcionBinaria(int _idUsuario, int _idActividad, int _tipoActividad,
                       double _progreso, bool _completado, bool _pagado)
        : idEstudiante(_idUsuario), idActividad(_idActividad),
          tipoActividad(_tipoActividad), progreso(_progreso),
          completado(_completado), pagado(_pagado) {}
    InscripcionBinaria()
        : idEstudiante(0), idActividad(0), tipoActividad(0), progreso(0.0),
          completado(false), pagado(false) {}
};

#endif // COURSERACLONE_PERSISTENCE_INSCRIPCIONTYPES_HPP
