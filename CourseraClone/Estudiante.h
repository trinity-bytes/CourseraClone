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

	/*
	bool inscribirseACurso(Curso* curso, GestionadorCursos* gestionadorCursos)
	{
		if (!curso) {
			std::cerr << "Error: Curso inv�lido" << std::endl;
			return false;
		}

		// Verificar si ya est� inscrito
		for (int i = 0; i < this->cursosEs.getTamano(); i++) {
			Inscripcion* inscripcion = this->cursosEs.get(i);
			if (inscripcion && inscripcion->getIdActividad() == curso->getId()) {
				std::cerr << "Error: Ya est�s inscrito en este curso." << std::endl;
				return false;
			}
		}

		// Usar el GestionadorCursos para la inscripci�n
		if (gestionadorCursos->inscribirEstudianteACurso(this->getId(), curso->getId())) {
			// Si la inscripci�n fue exitosa en el GestionadorCursos, actualizar localmente
			Inscripcion* nuevaInscripcion = new Inscripcion(this->getId(), *curso);
			cursosEs.push(nuevaInscripcion);
			return true;
		}

		return false;
	}
	*/
	bool Estudiante::inscribirseACurso(Curso* curso) {
		if (!curso) {
			std::cerr << "Error: Curso inv�lido" << std::endl;
			return false;
		}

		// Verificar si ya est� inscrito al curso
		for (int i = 0; i < cursosEs.getTamano(); i++) {
			Inscripcion* inscripcionExistente = cursosEs.get(i);
			if (inscripcionExistente && inscripcionExistente->getIdActividad() == curso->getId()) {
				std::cerr << "Error: Ya est�s inscrito en este curso" << std::endl;
				return false;
			}
		}

		// Crear una nueva inscripci�n
		Inscripcion* nuevaInscripcion = new Inscripcion(this->getId(), *curso);

		// Guardar en archivo
		nuevaInscripcion->guardar();

		// Agregar a la pila de cursos inscritos
		cursosEs.push(nuevaInscripcion);

		// Actualizar contador de alumnos del curso
		curso->aumentarAlumno(1);
		return true;
	}

	// M�todo sobrecargado para inscribirse a una especializaci�n
	bool inscribirseAEspecializacion(Especializacion* especializacion) {
		if (!especializacion) {
			std::cerr << "Error: Especializaci�n inv�lida" << std::endl;
			return false;
		}

		// Verificar si ya est� inscrito a la especializaci�n
		for (int i = 0; i < especializacionesEs.getTamano(); i++) {
			Inscripcion* inscripcionExistente = especializacionesEs.get(i);
			if (inscripcionExistente && inscripcionExistente->getIdActividad() == especializacion->getId()) {
				std::cerr << "Error: Ya est�s inscrito en esta especializaci�n" << std::endl;
				return false;
			}
		}

		// Crear una nueva inscripci�n
		Inscripcion* nuevaInscripcion = new Inscripcion(this->getId(), *especializacion);

		// Guardar en archivo
		nuevaInscripcion->guardar();

		// Agregar a la pila de especializaciones inscritas
		especializacionesEs.push(nuevaInscripcion);

		// Actualizar contador de alumnos de la especializaci�n
		especializacion->aumentarAlumno(1);
		return true;
	}
};
