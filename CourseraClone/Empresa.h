#pragma once
#include "Estudiante.h"

class Empresa: public Usuario{
private:
	//LinkedList<Actividad> actividades;
	//LinkedList<Instructor> instructores;
public:
	Empresa(): Usuario(id, tipoUsuario, nickName, contrasena) {
		
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
