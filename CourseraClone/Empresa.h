#pragma once
#include "Usuario.h"

class Empresa: public Usuario
{
private:
	LinkedList<Actividad*> actividadesPropias;
public:
	void cargarDatos() { }

	Empresa(int _id, string nombreCompleto, string _nickname, string _contrasena): Usuario(id, 2, nombreCompleto, _nickname, _contrasena) {
		cargarDatos();
		this->actividadesPropias = LinkedList<Actividad*>();
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
