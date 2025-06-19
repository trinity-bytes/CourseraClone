// filepath: Headers/Entities/Curso.hpp
// Clase que representa un curso en el sistema

#ifndef COURSERACLONE_ENTITIES_CURSO_HPP
#define COURSERACLONE_ENTITIES_CURSO_HPP

// Headers del sistema
#include <iostream> // Para std::cout, std::endl
#include <string>   // Para std::string

// Headers propios
#include "Actividad.hpp"                     // Clase base Actividad
#include "../Types/ActividadTypes.hpp" // RawCursoData

// Clase que representa un curso en el sistema educativo
class Curso : public Actividad {
private:
    std::string _instructor;
    int _cantidadClases;
	// ToDo: Implementar lista de clases relacionadas al curso
public:
    Curso() : Actividad(0, 0, "", CategoriaActividad::DEFAULT, "", ""), _instructor(""), _cantidadClases(0) {}

    Curso(
        int id,
        int idEmpresa,
        const std::string& nombreEmpresa,
		CategoriaActividad categoria,
        const std::string& titulo,
        const std::string& descripcion,
        const std::string& instructor,
        int cantidadClases
    ) : Actividad(id, idEmpresa, nombreEmpresa, categoria, titulo, descripcion),
        _instructor(instructor),
        _cantidadClases(cantidadClases) 
    {}

    // Getters
    const std::string& getInstructor() const { return _instructor; }
    int getCantidadClases() const { return _cantidadClases; }

    // Setters
    void setInstructor(const std::string& _instructor) { this->_instructor = _instructor; }

    
	// Obtener datos crudos del curso
    RawCursoData obtenerDatosCrudosCurso() {
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
    bool guardar() override{
		// ToDo: Implementar la lógica para guardar el curso en un archivo

        return true;
    }

	// ToDo: Implementar el método para cargar el curso desde un archivo

    void mostrarCursoPorId(int id) {
        RawCursoData curso;
		if (FilesManager::getInstance().buscarCursoPorIdHash(this->getId(), curso)) {
			std::cout << "Curso ID: " << curso.id << std::endl;
			std::cout << "Empresa ID: " << curso.idEmpresa << std::endl;
			std::cout << "Nombre Empresa: " << curso.nombreEmpresa << std::endl;
			std::cout << "Título: " << curso.titulo << std::endl;
			std::cout << "Descripción: " << curso.descripcion << std::endl;
			std::cout << "Instructor: " << curso.instructor << std::endl;
			std::cout << "Categoría: " << static_cast<int>(curso.categoria) << std::endl;
			std::cout << "Cantidad de Clases: " << curso.cantidadClases << std::endl;
		}
		else {
			std::cerr << "Curso no encontrado." << std::endl;
		}
    }
};

#endif // COURSERACLONE_ENTITIES_CURSO_HPP