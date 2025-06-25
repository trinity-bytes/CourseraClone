#ifndef COURSERACLONE_PERSISTENCE_BOLETATYPES_HPP
#define COURSERACLONE_PERSISTENCE_BOLETATYPES_HPP

enum class MetodoDePago{
    DEFAULT = 0,
    TARJETA_CREDITO = 1,
    TARJETA_DEBITO = 2,
    BILLETERA_DIGITAL = 3
};

struct BoletaBinaria {
    int idEstudiante;
    int idActividad;
    char fecha[20];    // "dd/MM/yy HH:mm:ss\0"
    double precio;

    BoletaBinaria() : idEstudiante(0), idActividad(0), fecha(), precio(0.0) {}
};

struct BoletaIndex {
    int idEstudiante;
    int offset;

    BoletaIndex() : idEstudiante(0), offset(0) {}
    BoletaIndex(int _idEstudiante, int _offset) : idEstudiante(_idEstudiante), offset(_offset) {}
};

struct RawComprobanteData {
    int id;
    int idEstudiante;
    int idActividad; // Curso o Especialidad
    TipoActividad tipoActividad;
    std::string fechaEmision;
    std::string horaEmision;
    double montoPagado;
    MetodoDePago metodoPago;
};
#endif // !COURSERACLONE_PERSISTENCE_BOLETATYPES_HPP