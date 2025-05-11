#pragma once
#include "Actividad.h"
#include "Curso.h"
#include "GestionadorCursos.h"
#include <vector>
#include "LinkedList.h"
#include <string>
#include <sstream>

class Especializacion : public Actividad {
private:
	std::vector<int> idsCursos;
	LinkedList<Curso*> cursos;
	string categoria;
	vector<string> requisitos;
	float calificacionPromedio;
	int totalCalificaciones;
	int duracionEstimada; // en semanas

public:
	Especializacion() {};
	Especializacion(
		int _id, 
		int _idEmpresa, 
		string _nombreEmpresa, 
		string _titulo, 
		int _cantidadAlumnos, 
		string _descripcion,
		string _categoria = "", 
		int _duracionEstimada = 0
	) : Actividad(
		_id, 
		_idEmpresa, 
		_nombreEmpresa, 
		_titulo, 
		_cantidadAlumnos, 
		2, 
		_descripcion) 
	{
		this->cursos = LinkedList<Curso*>();
		this->categoria = _categoria;
		this->calificacionPromedio = 0.0;
		this->totalCalificaciones = 0;
		this->duracionEstimada = _duracionEstimada;
	}

	// Métodos de gestión de cursos
	void anadirCurso(Curso* _curso) {
		cursos.agregarAlFinal(_curso);
	}

	bool eliminarCurso(int idCurso) {
		if (idCurso < 0 || idCurso >= cursos.getTamano()) return false;
		
		auto it = cursos.begin();
		for (int i = 0; i < idCurso; i++) ++it;
		
		cursos.eliminar(it);
		return true;
	}

	// Métodos de categoría y requisitos
	void setCategoria(const string& _categoria) { categoria = _categoria; }
	string getCategoria() const { return categoria; }

	void agregarRequisito(const string& requisito) {
		requisitos.push_back(requisito);
	}

	vector<string> getRequisitos() const { return requisitos; }

	// Métodos de calificación
	void agregarCalificacion(int calificacion) {
		if (calificacion < 1 || calificacion > 5) return;
		
		calificacionPromedio = (calificacionPromedio * totalCalificaciones + calificacion) / (totalCalificaciones + 1);
		totalCalificaciones++;
	}

	float getCalificacionPromedio() const { return calificacionPromedio; }
	int getTotalCalificaciones() const { return totalCalificaciones; }

	// Métodos de duración
	void setDuracionEstimada(int semanas) { duracionEstimada = semanas; }
	int getDuracionEstimada() const { return duracionEstimada; }

	// Getters
	LinkedList<Curso*> getCursos() const { return cursos; }
	int getCantidadCursos() const { return cursos.getTamano(); }

	// Método para calcular el progreso de un estudiante
	int calcularProgreso(const vector<int>& cursosCompletados) const {
		if (cursosCompletados.empty()) return 0;
		return (cursosCompletados.size() * 100) / cursos.getTamano();
	}

	// Método para verificar si un estudiante puede acceder a la especialización
	bool verificarRequisitos(const vector<int>& cursosCompletados) const {
		if (requisitos.empty()) return true;
		
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
			cout << "- " << curso->getTitulo() << "\n";
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
			ss << curso->getId() << '\n';
		}
		
		// Guardar requisitos
		ss << requisitos.size() << '\n';
		for (const auto& req : requisitos) {
			ss << req << '\n';
		}
		
		return ss.str();
	}

	LinkedList<Curso*> getIdsCursos(LinkedList<Curso*> cursoLista) const {
		LinkedList<Curso*> cursosAsociados;

		// Iterar sobre cada ID de curso almacenado en la especialización
		for (int idCurso : idsCursos) {
			Curso* curso = cursoLista.get(idCurso);
			if (curso != nullptr) {
				// Si el curso existe, agregarlo a la lista
				cursosAsociados.agregarAlFinal(curso);
			}
			else {
				// Mensaje de depuración para indicar que no se encontró el curso
				std::cerr << "Error: No se encontró el curso con ID " << idCurso << std::endl;
			}
		}

		return cursosAsociados;
	}

	// Método para agregar un ID de curso a la especialización
	void anadirCursoPorId(int idCurso) {
		idsCursos.push_back(idCurso);
	}

	// Método para eliminar un ID de curso de la especialización
	bool eliminarCursoPorId(int idCurso) {
		auto it = std::find(idsCursos.begin(), idsCursos.end(), idCurso);
		if (it != idsCursos.end()) {
			idsCursos.erase(it);
			return true;
		}
		return false;
	}

	void guardar() {
		ofstream archivo("Resources/Data/actividades.txt", ios::app);
		if (archivo.is_open()) {
			archivo << toString();
			archivo.close();
		}
		else {
			cout << "Error al abrir el archivo." << endl;
		}
	}
};