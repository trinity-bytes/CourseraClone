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

	bool inscribirseACurso(Curso* curso)
	{
		if (!curso) {
			std::cerr << "Error: Curso inválido" << std::endl;
			return false;
		}

		// Crear una nueva inscripción
		Inscripcion* nuevaInscripcion = new Inscripcion(this->getId(), *curso);

		// Guardar en archivo
		nuevaInscripcion->guardar();

		// 3. Agregar a la lista del estudiante
		if (actividadNueva.getTipo() == 1) {
			cursosEs.push(nuevaInscripcion);
		}
		else {
			especializacionesEs.push(nuevaInscripcion);
		}
		// Agregar a la lista del estudiante
		inscripciones.agregarAlFinal(nuevaInscripcion);

		// También agregarlo a la pila de actividades inscritas
		actividadesInscritas.push(nuevaInscripcion);

		// Actualizar contador de alumnos del curso
		curso->aumentarAlumno(1);

		std::cout << "Inscripción completada para el curso: " << curso->getTitulo() << std::endl;
		return true;
	}

	// Método sobrecargado para inscribirse a una especialización
	int inscribirseAEspecializacion(Especializacion* especializacion) {
		if (!especializacion) {
			std::cerr << "Error: Especialización inválida" << std::endl;
			return 0;
		}

		// Crear una nueva inscripción
		Inscripcion* nuevaInscripcion = new Inscripcion(this->getId(), *especializacion);

		// Guardar en archivo
		nuevaInscripcion->guardar();

		// Agregar a la lista del estudiante
		inscripciones.agregarAlFinal(nuevaInscripcion);

		// También agregarlo a la pila de actividades inscritas
		actividadesInscritas.push(nuevaInscripcion);

		// Actualizar contador de alumnos de la especialización
		especializacion->aumentarAlumno(1);

		std::cout << "Inscripción completada para la especialización: " << especializacion->getTitulo() << std::endl;
		return 1;
	}
};
