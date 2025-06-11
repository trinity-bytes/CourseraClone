// filepath: Headers/Entities/Curso.hpp
// Clase que representa un curso en el sistema

#ifndef COURSERACLONE_ENTITIES_CURSO_HPP
#define COURSERACLONE_ENTITIES_CURSO_HPP

// Headers del sistema
#include <iostream> // Para std::cout, std::endl
#include <string>   // Para std::string

// Headers propios
#include "Actividad.hpp"                     // Clase base Actividad
#include "../Persistence/ActividadTypes.hpp" // RawCursoData

// Clase que representa un curso en el sistema educativo
class Curso : public Actividad 
{
private:
    std::string _instructor;
    std::string _categoria;
    int _cantidadClases;

	// ToDo: Implementar lista de clases relacionadas al curso
public:
    // Constructores
    Curso() : Actividad(0, 0, "", "", ""), _instructor(""), _categoria(""), _cantidadClases(0) {}

    Curso(
        int _id,
        int _idEmpresa,
        const std::string& _nombreEmpresa,
        const std::string& _titulo,
        const std::string& _descripcion,
        const std::string& _instructor,
        const std::string& _categoria = "",
        int _cantidadClases
    ) : Actividad(_id, _idEmpresa, _nombreEmpresa, _titulo, _descripcion),
        _instructor(_instructor),
        _cantidadClases(_cantidadClases),
        _categoria(_categoria) {}

    // Getters
    const std::string& getInstructor() const { return _instructor; }
    int getCantidadClases() const { return _cantidadClases; }
    const std::string& getCategoria() const { return _categoria; }

    // Setters
    void setInstructor(const std::string& _instructor) { this->_instructor = _instructor; }
	void setInstructor(const std::string& _instructor) { this->_instructor = _instructor; }
    void setCategoria(const std::string& _categoria) { this->_categoria = _categoria; }

    
	// Obtener datos crudos del curso
    RawCursoData obtenerDatosCrudos() const 
    {
        RawCursoData datos;

        datos.id = this->getId();
        datos.idEmpresa = this->getIdEmpresa();
        datos.nombreEmpresa = this->getNombreEmpresa();
        datos.titulo = this->getTitulo();
        datos.descripcion = this->getDescripcion();
        datos.instructor = this->_instructor;
        datos.categoria = this->_categoria;
        datos.cantidadClases = this->_cantidadClases;

        return datos;
	}

    // Método para persistencia
    bool guardar() 
    {
		// ToDo: Implementar la lógica para guardar el curso en un archivo
    }

	// ToDo: Implementar el método para cargar el curso desde un archivo
};

#endif // COURSERACLONE_ENTITIES_CURSO_HPP