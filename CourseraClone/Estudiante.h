#pragma once
#include "Usuario.h"
#include"LinkedList.h"
#include"Stack.h"
#include"Queue.h"
#include"Inscripcion.h"
#include "Boleta.h"
#include "Curso.h"

class Estudiante :public Usuario
{
private:
	LinkedList<Boleta*> boletas;
	Stack<Inscripcion*> cursosEs;
	Stack<Inscripcion*> especializacionesEs;
public:
	
	Estudiante(int _id, string nombreCompleto, 
		string _nickname, string _contrasena) : Usuario(_id, TipoUsuario::ESTUDIANTE, nombreCompleto,
												_nickname, _contrasena) 
	{
		cursosEs = Stack<Inscripcion*>();
		especializacionesEs = Stack<Inscripcion*>();
		boletas = LinkedList<Boleta*>();
		cargarDatos();
	}

	void cargarInscripciones() {

	}

	void cargarDatos() {
		// cargar boletas
	}

	void verBoletas() {
		//todas las boletas que el estudiante tiene
		/*
		ifstream file("boletas.txt");
		if (!file.is_open()) {
			cout << "No se pudo abrir el archivo." << endl;
			return;
		}
		
		while (file.read(reinterpret_cast<char*>(&boleta), sizeof(Boleta))) {
			boleta->mostrar();
		}
		*/
	}

	void verCursosInscritos() {
		ifstream file("inscripciones.txt");
		/*
		if (!file.is_open()) {
			cout << "No se pudo abrir el archivo." << endl;
			return;
		}
		while (file.read(reinterpret_cast<char*>(&inscripcion), sizeof(Inscripcion))) {
			if (inscripcion->getIdEstudiante() == id) {
				inscripcion->mostrar();
			}
			else {
				cout << "No tienes cursos inscritos." << endl;
			}
		}
		file.close();
		*/
	}

	bool inscribirseACurso(Curso* curso, GestionadorCursos* gestionadorCursos)
	{
		if (!curso) {
			std::cerr << "Error: Curso inválido" << std::endl;
			return false;
		}

		// Verificar si ya está inscrito
		for (int i = 0; i < this->cursosEs.getTamano(); i++) {
			Inscripcion* inscripcion = this->cursosEs.get(i);
			if (inscripcion && inscripcion->getIdActividad() == curso->getId()) {
				std::cerr << "Error: Ya estás inscrito en este curso." << std::endl;
				return false;
			}
		}

		// Usar el GestionadorCursos para la inscripción
		if (gestionadorCursos->inscribirEstudianteACurso(this->getId(), curso->getId())) {
			// Si la inscripción fue exitosa en el GestionadorCursos, actualizar localmente
			Inscripcion* nuevaInscripcion = new Inscripcion(this->getId(), *curso);
			cursosEs.push(nuevaInscripcion);
			return true;
		}

		return false;
	}

	// Método sobrecargado para inscribirse a una especialización
	bool inscribirseAEspecializacion(Especializacion* especializacion) {
		if (!especializacion) {
			std::cerr << "Error: Especialización inválida" << std::endl;
			return false;
		}

		// Verificar si ya está inscrito
		for (int i = 0; i < this->especializacionesEs.getTamano(); i++) {
			Inscripcion* inscripcion = this->especializacionesEs.get(i);
			if (inscripcion && inscripcion->getIdActividad() == especializacion->getId()) {
				std::cerr << "Error: Ya estás inscrito en esta especialización." << std::endl;
				return false;
			}
		}

		// Crear una nueva inscripción
		Inscripcion* nuevaInscripcion = new Inscripcion(this->getId(), *especializacion);

		// Guardar en archivo
		nuevaInscripcion->guardar();

		// Agregar a la pila de especializaciones inscritas
		especializacionesEs.push(nuevaInscripcion);

		// Actualizar contador de alumnos de la especialización
		especializacion->aumentarAlumno(1);

		return true;
	}
};
