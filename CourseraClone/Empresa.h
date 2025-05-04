#pragma once
#include "Estudiante.h"

class Empresa: public Usuario{
private:
	string razonSocial;
	//LinkedList<Actividad> actividades;
	//LinkedList<Instructor> instructores;
public:
	Empresa(string _razonSocial): Usuario(id, tipoUsuario, nickName, contrasena) {
		razonSocial = _razonSocial;
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
