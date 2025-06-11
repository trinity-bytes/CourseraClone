#ifndef COURSERACLONE_PERSISTENCE_BOLETATYPES_HPP
#define COURSERACLONE_PERSISTENCE_BOLETATYPES_HPP

struct BoletaBinaria 
{
    int idEstudiante;
    int idActividad;
    char fecha[20];    // "dd/MM/yy HH:mm:ss\0"
    double precio;

    BoletaBinaria() : idEstudiante(0), idActividad(0), fecha(), precio(0.0) {}
};

struct BoletaIndex 
{
    int   idEstudiante;
    int offset;

    BoletaIndex() : idEstudiante(0), offset(0) {}
    BoletaIndex(int _idEstudiante, int _offset) : idEstudiante(_idEstudiante), offset(_offset) {}
};

#endif // !COURSERACLONE_PERSISTENCE_BOLETATYPES_HPP