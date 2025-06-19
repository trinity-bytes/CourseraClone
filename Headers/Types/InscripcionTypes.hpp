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
