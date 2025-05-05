#pragma once
#include "Estudiante.h"

class Empresa: public Usuario{
private:

	LinkedList<Actividad> actividades;
	//LinkedList<Instructor> instructores;
public:
	void cargarDatos() {

	}

	Empresa(): Usuario(id, 2, nickName, contrasena) {
		cargarDatos();
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
