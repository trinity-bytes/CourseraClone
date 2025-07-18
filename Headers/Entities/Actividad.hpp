// filepath: Headers/Entities/Actividad.hpp
// Descripcion: Clase base para actividades educativas (cursos y especializaciones)

#ifndef COURSERACLONE_ENTITIES_ACTIVIDAD_HPP
#define COURSERACLONE_ENTITIES_ACTIVIDAD_HPP

// Includes del sistema
#include <string>

// Includes propios del proyecto
#include "../Types/ActividadTypes.hpp"



// Clase base que representa una actividad educativa
class Actividad
{
protected:
    int _id;
    int _idEmpresa;
    std::string _nombreEmpresa;
    CategoriaActividad _categoria;
    TipoActividad _tipo;
    std::string _titulo;
    std::string _descripcion;
    int _cantidadAlumnos;
    int _cantidadCompletados;
    double _montoRecaudado;
    double _progresoTotal;
    double _precio;

public:
    Actividad() : _id(0),
        _idEmpresa(0),
        _nombreEmpresa(""),
        _categoria(CategoriaActividad::DEFAULT),
        _tipo(TipoActividad::DEFAULT),
        _titulo(""),
        _descripcion(""),
        _cantidadAlumnos(0),
        _cantidadCompletados(0),
        _montoRecaudado(0),
        _progresoTotal(0.0)
    {
    }

    Actividad(
        int id,
        int idEmpresa,
        const std::string& nombreEmpresa,
        CategoriaActividad categoria,
        const std::string& titulo,
        const std::string& descripcion,
        TipoActividad tipo,
		double precio = 0.0
    ) : _id(id),
        _idEmpresa(idEmpresa),
        _nombreEmpresa(nombreEmpresa),
        _categoria(categoria),
        _titulo(titulo),
        _descripcion(descripcion),
        _tipo(tipo),
        _cantidadAlumnos(0),
        _cantidadCompletados(0),
        _montoRecaudado(0),
        _progresoTotal(0.0),
		_precio(precio)
    {
    }

    virtual ~Actividad() = default;

    // Metodo para elemento menu
    ElementoMenu obtenerDatosCrudosMenu() {
        return ElementoMenu(_id, _titulo, _descripcion);
    }

    RawExploradorData obtenerDatosCrudosExplorador() const {
        return RawExploradorData{ _tipo, _id, _titulo, _categoria };
    }

    RawLandingData obtenerDatosLanding() {
        return RawLandingData{ _id, _tipo, _cantidadAlumnos };
    }

    // Getters
    int getId() const { return _id; }
    int getIdEmpresa() const { return _idEmpresa; }
    const std::string& getNombreEmpresa() const { return _nombreEmpresa; }
    const CategoriaActividad getCategoria() const { return _categoria; }
    const std::string& getTitulo() const { return _titulo; }
    const std::string& getDescripcion() const { return _descripcion; }
    const int getCantidad() const { return _cantidadAlumnos; }
    const TipoActividad getTipo() const { return _tipo; } 
    const double getMontoRecaudado() const { return _montoRecaudado; }
    const double getPrecio() const { return _precio; }
    double getProgresoTotal() {
        calcularProgreso();
        return _progresoTotal;
    }

    // Setters
    void setId(int id) { _id = id; }
    void setIdEmpresa(int idEmpresa) { _idEmpresa = idEmpresa; }
    void setNombreEmpresa(const std::string& nombreEmpresa) { _nombreEmpresa = nombreEmpresa; }
    void setCategoria(const CategoriaActividad categoria) { _categoria = categoria; }
    void setTitulo(const std::string& titulo) { _titulo = titulo; }
    void setDescripcion(const std::string& descripcion) { _descripcion = descripcion; }
    void setTipo(const TipoActividad tipo) { _tipo = tipo; }
    void aumentarAlumno() { _cantidadAlumnos++; }
    void aumentarAlumnoCompletado() { _cantidadCompletados++; }
    void aumentarMonto(double nuevoIngreso) { _montoRecaudado += nuevoIngreso; }
    void calcularProgreso() {
        double alumnoTotalDouble = static_cast<double> (_cantidadAlumnos);
        if (_cantidadAlumnos == 0) {
            _progresoTotal = 0.0;
            return;
        }
        double alumnoCompletoDouble = static_cast<double> (_cantidadCompletados);
        _progresoTotal = (_cantidadCompletados * 100) / alumnoTotalDouble;
    }


    virtual bool guardar() = 0; // M�todo virtual puro para guardar la actividad
};

#endif // COURSERACLONE_ENTITIES_ACTIVIDAD_HPP