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
		// ToDo: Implementar la lógica para guardar el curso en un archivo del filemanger
		RawCursoData datosCurso = obtenerDatosCrudosCurso();
		auto resultado = FilesManager::getInstance().guardarCurso(datosCurso);
		if (resultado != FileOperationResult::SUCCESS) {
			std::cerr << "Error al guardar el curso: " << obtenerMensaje(resultado) << std::endl;
			return false;
		}
		std::cout << "Curso guardado correctamente." << std::endl;
        return true;
    }

	// ToDo: Implementar el método para cargar el curso desde un archivo
   
    void mostrarCurso(std::string nombreCurso) {
        RawCursoData curso;
        if (FilesManager::getInstance().buscarCursoPorNombreHash(nombreCurso, curso)) {
            std::cout << "Curso encontrado:\n";
            std::cout << "ID: " << curso.id << "\n";
            std::cout << "Título: " << curso.titulo << "\n";
            std::cout << "Descripción: " << curso.descripcion << "\n";
            std::cout << "Instructor: " << curso.instructor << "\n";
			std::cout << "Categoría: " << static_cast<int>(curso.categoria) << "\n";
			std::cout << "Cantidad de Clases: " << curso.cantidadClases << "\n";
			std::cout << "Empresa: " << curso.nombreEmpresa << " (ID: " << curso.idEmpresa << ")\n";
        }
        else {
            std::cout << "No se encontró un curso con ese nombre.\n";
        }
    }
};

#endif // COURSERACLONE_ENTITIES_CURSO_HPP