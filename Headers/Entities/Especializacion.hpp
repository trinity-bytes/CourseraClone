// filepath: Headers/Entities/Especializacion.hpp
// Header para la clase Especializacion que representa una especialización compuesta por varios cursos

#ifndef COURSERACLONE_ENTITIES_ESPECIALIZACION_HPP
#define COURSERACLONE_ENTITIES_ESPECIALIZACION_HPP

// Includes del sistema y de la STL
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>

// Includes propios del proyecto
#include "Actividad.hpp"
#include "Curso.hpp"
#include "../Controllers/ContentManager.hpp"

// Clase que representa una especialización compuesta por varios cursos
class Especializacion : public Actividad 
{
private:
    std::vector<int> _idsCursos;
    CategoriaActividad _categoria;
	int _duracionEstimada; // Duración estimada en semanas

public:
    Especializacion(
        int id, 
        int idEmpresa, 
        const std::string& nombreEmpresa, 
        const std::string& titulo, 
        int cantidadAlumnos, 
        const std::string& descripcion,
        const std::string& categoria = "", 
        int duracionEstimada = 0
    ) : Actividad(
        id, 
        idEmpresa, 
        nombreEmpresa, 
        titulo, 
        cantidadAlumnos, 
        2, 
        descripcion
    ) {
        this->_categoria = categoria;
        this->_calificacionPromedio = 0.0;
        this->_totalCalificaciones = 0;
        this->_duracionEstimada = duracionEstimada;
    }

    // Métodos de gestión de cursos
    void agregarCurso(Curso& _curso) 
    {
        bool idYaExiste = false;
        for (int id : _idsCursos) 
        {            
            if (id == _curso.getId()) 
            {
                idYaExiste = true;
                break;
            }
        }
        if (!idYaExiste) 
        {
            _idsCursos.push_back(_curso.getId());
        }

        _cursos.agregarAlFinal(_curso);
    }

    bool eliminarCurso(int _idCurso) {
        if (_idCurso < 0 || _idCurso >= _cursos.getTamano()) return false;
        
        auto it = _cursos.begin();
        for (int i = 0; i < _idCurso; i++) ++it;
        
        _cursos.eliminar(it);
        return true;
    }

    std::vector<int> getIdsCursosVector() const {
		return _idsCursos; // Devuelve una copia del vector para proteger los datos internos
	}
    // Métodos de categoría y requisitos
    void setCategoria(const std::string& categoria) { _categoria = categoria; }
    const std::string& getCategoria() const { return _categoria; }

    void agregarRequisito(const std::string& _requisito) {
        _requisitos.push_back(_requisito);
    }

    const std::vector<std::string>& getRequisitos() const { return _requisitos; }

    // Métodos de calificación
    void agregarCalificacion(int _calificacion) {
        if (_calificacion < 1 || _calificacion > 5) return;
        
        _calificacionPromedio = (_calificacionPromedio * _totalCalificaciones + _calificacion) / (_totalCalificaciones + 1);
        _totalCalificaciones++;
    }

    float getCalificacionPromedio() const { return _calificacionPromedio; }
    int getTotalCalificaciones() const { return _totalCalificaciones; }

    // Métodos de duración
    void setDuracionEstimada(int _semanas) { _duracionEstimada = _semanas; }
    int getDuracionEstimada() const { return _duracionEstimada; }

    // Getters
    const LinkedList<Curso>& getCursos() const { return _cursos; }
    int getCantidadCursos() const { return _cursos.getTamano(); }

    // Método para calcular el progreso de un estudiante
    int calcularProgreso(const std::vector<int>& _cursosCompletados) const {
        if (_cursosCompletados.empty()) return 0;
        return (_cursosCompletados.size() * 100) / _cursos.getTamano();
    }

    // Método para verificar si un estudiante puede acceder a la especialización
    bool verificarRequisitos(const std::vector<int>& _cursosCompletados) const {
        if (_requisitos.empty()) return true;
		
		// Implementar lógica de verificación de requisitos
		// Por ahora retornamos true
		return true;
	}

	// Sobrescribir método virtual de Actividad
	void mostrar() {
        std::cout << "Especialización: " << _titulo << "\n";
        std::cout << "Empresa: " << _nombreEmpresa << "\n";
        std::cout << "Cantidad de alumnos: " << _cantidadAlumnos << "\n";
        std::cout << "Descripción: " << _descripcion << "\n";
        std::cout << "Categoría: " << _categoria << "\n";
        std::cout << "Duración estimada: " << _duracionEstimada << " semanas\n";
        std::cout << "Calificación promedio: " << _calificacionPromedio << "\n";
        std::cout << "Total de calificaciones: " << _totalCalificaciones << "\n";
        std::cout << "Cursos incluidos:\n";
		for (const auto& curso : _cursos) {
            std::cout << "- " << curso.getTitulo() << "\n";
		}
	}

    std::string toString() const {
        std::stringstream ss;
		ss << _idEmpresa << '\n'
		   << _tipo << '\n'
		   << _nombreEmpresa << '\n'
		   << _titulo << '\n'
		   << _descripcion << '\n'
		   << _categoria << '\n'
		   << _duracionEstimada << '\n'
		   << _calificacionPromedio << '\n'
		   << _totalCalificaciones << '\n';
		
		// Guardar cursos
		ss << _cursos.getTamano() << '\n';
		for (const auto& curso : _cursos) {
			ss << curso.getId() << '\n';
		}
		
		// Guardar requisitos
		ss << _requisitos.size() << '\n';
		for (const auto& req : _requisitos) {
			ss << req << '\n';
		}
		
		return ss.str();
	}

	LinkedList<Curso> getIdsCursos(LinkedList<Curso> cursosDisponibles) const {
		LinkedList<Curso> cursosAsociados;

        std::cerr << "Buscando " << _idsCursos.size() << " cursos asociados a especialización " << this->getTitulo() << std::endl;

		// Recorrer todos los IDs de cursos asociados a esta especialización
		for (int idCurso : _idsCursos) {
            std::cerr << "Buscando curso con ID: " << idCurso << std::endl;
			bool encontrado = false;

			// Buscar este curso en la lista de cursos disponibles
			for (int i = 0; i < cursosDisponibles.getTamano(); i++) {
				Curso curso = cursosDisponibles.get(i);
				if (curso.getId() == idCurso) {
					cursosAsociados.agregarAlFinal(curso);
					encontrado = true;
                    std::cerr << "  ✓ Encontrado curso: " << curso.getTitulo() << " (ID: " << curso.getId() << ")" << std::endl;
					break;  // Encontrado, no necesitamos seguir buscando
				}
			}

			if (!encontrado) {
                std::cerr << "  ✗ No se encontró el curso con ID " << idCurso << std::endl;
			}
		}

        std::cerr << "Total de cursos asociados encontrados: " << cursosAsociados.getTamano() << std::endl;
		return cursosAsociados;
	}

	// Método para agregar un ID de curso a la especialización
	void anadirCursoPorId(int idCurso) {
		// Verificar si el ID ya está en la lista para evitar duplicados        
        for (int id : _idsCursos) {
            if (id == idCurso) {
                return; // El ID ya está en la lista
            }
        }
        // Añadir el ID a la lista
        _idsCursos.push_back(idCurso);
    }

    // Método para eliminar un ID de curso de la especialización
    bool eliminarCursoPorId(int _idCurso) {
        auto it = std::find(_idsCursos.begin(), _idsCursos.end(), _idCurso);
        if (it != _idsCursos.end()) {
            _idsCursos.erase(it);
            return true;
        }
        return false;
    }

    void guardar() {
        std::ofstream archivo("Resources/Data/actividades.txt", std::ios::app);
        if (archivo.is_open()) {
            archivo << toString();
            archivo.close();
        }
        else {
            std::cout << "Error al abrir el archivo." << std::endl;
        }
    }
};

#endif // COURSERACLONE_ENTITIES_ESPECIALIZACION_HPP