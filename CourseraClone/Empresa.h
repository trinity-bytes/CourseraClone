#pragma once
#include "Estudiante.h"

class Empresa: public Usuario{
private:

	LinkedList<Actividad*> actividades;
	//LinkedList<Instructor> instructores;
public:
	void cargarDatos() {

	}

	Empresa(int _id, string _nickname, string _contrasena): Usuario(id, 2, _nickname, _contrasena) {
		cargarDatos();
		actividades = LinkedList<Actividad*>();
	}

	int crearCurso(){

	}
	int crearInstructor() {

	}
	int crearEspecializacion() {

	}
	void verProfesores() {

	}
	bool eliminarCUrsoEspecializacion() {

	}
	bool anadirCUrsoEspecilizacion() {

	}
};
