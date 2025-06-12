// filepath: Headers/Entities/Actividad.hpp
// Descripcion: Clase base para actividades educativas (cursos y especializaciones)

#ifndef COURSERACLONE_ENTITIES_ACTIVIDAD_HPP
#define COURSERACLONE_ENTITIES_ACTIVIDAD_HPP

// Includes del sistema
#include <string>

// Includes propios del proyecto
#include "../Persistence/ActividadTypes.hpp"

// Clase base que representa una actividad educativa
class Actividad 
{
protected:
    int _id;
    int _idEmpresa;
    std::string _nombreEmpresa;
    CategoriaActividad _categoria;
    std::string _titulo;
    std::string _descripcion;

public:
    Actividad() : _id(0), 
                  _idEmpresa(0), 
                  _nombreEmpresa(""), 
		          _categoria(CategoriaActividad::DEFAULT),
                  _titulo(""), 
                  _descripcion("")
                  
    {}

    Actividad(
        int id,
        int idEmpresa,
        const std::string& nombreEmpresa,
        CategoriaActividad categoria,
        const std::string& titulo,
        const std::string& descripcion
    ) : _id(id),
        _idEmpresa(idEmpresa),
        _nombreEmpresa(nombreEmpresa),
        _categoria(categoria),
        _titulo(titulo),
        _descripcion(descripcion)		
    {}

    virtual ~Actividad() = default;

    // Getters
    int getId() const { return _id; }
    int getIdEmpresa() const { return _idEmpresa; }
    const std::string& getNombreEmpresa() const { return _nombreEmpresa; }
    const CategoriaActividad getCategoria() const { return _categoria; }
    const std::string& getTitulo() const { return _titulo; }
    const std::string& getDescripcion() const { return _descripcion; }	

	// Setters
    void setId(int id) { _id = id; }
    void setIdEmpresa(int idEmpresa) { _idEmpresa = idEmpresa; }
    void setNombreEmpresa(const std::string& nombreEmpresa) { _nombreEmpresa = nombreEmpresa; }
    void setCategoria(const CategoriaActividad categoria) { _categoria = categoria; }
    void setTitulo(const std::string& titulo) { _titulo = titulo; }
    void setDescripcion(const std::string& descripcion) { _descripcion = descripcion; }	

	virtual RawCursoData obtenerDatosCrudos() = 0; // Método virtual puro para obtener datos crudos
};

#endif // COURSERACLONE_ENTITIES_ACTIVIDAD_HPP