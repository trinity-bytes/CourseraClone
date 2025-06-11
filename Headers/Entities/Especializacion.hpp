// filepath: Headers/Entities/Especializacion.hpp
// Descripcion: Clase que representa una especialización en el sistema

#ifndef COURSERACLONE_ENTITIES_ESPECIALIZACION_HPP
#define COURSERACLONE_ENTITIES_ESPECIALIZACION_HPP

#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "Actividad.hpp"
#include "Curso.hpp"
#include "../Controllers/CourseManager.hpp"
#include "../DataStructures/LinkedList.hpp"

// Clase que representa una especialización compuesta por varios cursos
class Especializacion : public Actividad {
private:
    std::vector<int> _idsCursos;
    LinkedList<Curso> _cursos;
    std::string _categoria;
    std::vector<std::string> _requisitos;
    float _calificacionPromedio;
    int _totalCalificaciones;
    int _duracionEstimada;

public:
    Especializacion() {};
    
    Especializacion(
        int _id, 
        int _idEmpresa, 
        const std::string& _nombreEmpresa, 
        const std::string& _titulo, 
        int _cantidadAlumnos, 
        const std::string& _descripcion,
        const std::string& _categoria = "", 
        int _duracionEstimada = 0
    ) : Actividad(
        _id, 
        _idEmpresa, 
        _nombreEmpresa, 
        _titulo, 
        _cantidadAlumnos, 
        2, 
        _descripcion) {
        this->_categoria = _categoria;
        this->_calificacionPromedio = 0.0;
        this->_totalCalificaciones = 0;
        this->_duracionEstimada = _duracionEstimada;
    }

    // Métodos de gestión de cursos
    void anadirCurso(Curso& _curso) {
        bool idYaExiste = false;
        for (int id : _idsCursos) {            if (id == _curso.getId()) {
                idYaExiste = true;
                break;
            }
        }
        if (!idYaExiste) {
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

	vector<int> getIdsCursosVector() const {
		return idsCursos; // Devuelve una copia del vector para proteger los datos internos
	}
    // Métodos de categoría y requisitos
    void setCategoria(const std::string& _categoria) { _categoria = _categoria; }
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
		cout << "Especialización: " << titulo << "\n";
		cout << "Empresa: " << nombreEmpresa << "\n";
		cout << "Cantidad de alumnos: " << cantidadAlumnos << "\n";
		cout << "Descripción: " << descripcion << "\n";
		cout << "Categoría: " << categoria << "\n";
		cout << "Duración estimada: " << duracionEstimada << " semanas\n";
		cout << "Calificación promedio: " << calificacionPromedio << "\n";
		cout << "Total de calificaciones: " << totalCalificaciones << "\n";
		cout << "Cursos incluidos:\n";
		for (const auto& curso : cursos) {
			cout << "- " << curso.getTitulo() << "\n";
		}
	}

	string toString() const {
		stringstream ss;
		ss << idEmpresa << '\n'
		   << tipo << '\n'
		   << nombreEmpresa << '\n'
		   << titulo << '\n'
		   << descripcion << '\n'
		   << categoria << '\n'
		   << duracionEstimada << '\n'
		   << calificacionPromedio << '\n'
		   << totalCalificaciones << '\n';
		
		// Guardar cursos
		ss << cursos.getTamano() << '\n';
		for (const auto& curso : cursos) {
			ss << curso.getId() << '\n';
		}
		
		// Guardar requisitos
		ss << requisitos.size() << '\n';
		for (const auto& req : requisitos) {
			ss << req << '\n';
		}
		
		return ss.str();
	}

	LinkedList<Curso> getIdsCursos(LinkedList<Curso> cursosDisponibles) const {
		LinkedList<Curso> cursosAsociados;

		cerr << "Buscando " << idsCursos.size() << " cursos asociados a especialización " << this->getTitulo() << endl;

		// Recorrer todos los IDs de cursos asociados a esta especialización
		for (int idCurso : idsCursos) {
			cerr << "Buscando curso con ID: " << idCurso << endl;
			bool encontrado = false;

			// Buscar este curso en la lista de cursos disponibles
			for (int i = 0; i < cursosDisponibles.getTamano(); i++) {
				Curso curso = cursosDisponibles.get(i);
				if (curso.getId() == idCurso) {
					cursosAsociados.agregarAlFinal(curso);
					encontrado = true;
					cerr << "  ✓ Encontrado curso: " << curso.getTitulo() << " (ID: " << curso.getId() << ")" << endl;
					break;  // Encontrado, no necesitamos seguir buscando
				}
			}

			if (!encontrado) {
				cerr << "  ✗ No se encontró el curso con ID " << idCurso << endl;
			}
		}

		cerr << "Total de cursos asociados encontrados: " << cursosAsociados.getTamano() << endl;
		return cursosAsociados;
	}

	// Método para agregar un ID de curso a la especialización
	void anadirCursoPorId(int idCurso) {
		// Verificar si el ID ya está en la lista para evitar duplicados        for (int id : _idsCursos) {
            if (id == _idCurso) {
                return; // El ID ya está en la lista
            }
        }
        // Añadir el ID a la lista
        _idsCursos.push_back(_idCurso);
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