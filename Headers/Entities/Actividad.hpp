// filepath: Headers/Entities/Actividad.hpp
// Descripcion: Clase base para actividades educativas (cursos y especializaciones)

#ifndef COURSERACLONE_ENTITIES_ACTIVIDAD_HPP
#define COURSERACLONE_ENTITIES_ACTIVIDAD_HPP

// Includes del sistema
#include <string>

// Clase base que representa una actividad educativa
class Actividad {
protected:
    int _id;
    int _idEmpresa;
    std::string _nombreEmpresa;
    std::string _titulo;
    std::string _descripcion;
    int _cantidadAlumnos;
    int _tipo;

public:
    Actividad() :
        _id(0),
        _idEmpresa(0),
        _nombreEmpresa(""),
        _titulo(""),
        _descripcion(""),
        _cantidadAlumnos(0),
        _tipo(0) {}

    Actividad(
        int id,
        int idEmpresa,
        const std::string& nombreEmpresa,
        const std::string& titulo,
        int cantidadAlumnos,
        int tipo,
        const std::string& descripcion
    ) :
        _id(id),
        _idEmpresa(idEmpresa),
        _nombreEmpresa(nombreEmpresa),
        _titulo(titulo),
        _cantidadAlumnos(cantidadAlumnos),
        _tipo(tipo),
        _descripcion(descripcion) {}

    virtual ~Actividad() = default;

    void aumentarAlumno(int _cantidad) {
        _cantidadAlumnos += _cantidad;
    }

    // Getters
    int getIdEmpresa() const { return _idEmpresa; }
    const std::string& getNombreEmpresa() const { return _nombreEmpresa; }
    int getId() const { return _id; }
    int getTipo() const { return _tipo; }
    int getCantidadAlumnos() const { return _cantidadAlumnos; }
    const std::string& getTitulo() const { return _titulo; }
    const std::string& getDescripcion() const { return _descripcion; }
};

#endif // COURSERACLONE_ENTITIES_ACTIVIDAD_HPP