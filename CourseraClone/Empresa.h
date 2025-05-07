#pragma once
#include "Usuario.h"
#include <vector>

class Empresa: public Usuario
{
private:
	LinkedList<Actividad*> actividadesPropias;
	LinkedList<Especializacion*> especializaciones;
	LinkedList<Curso*> cursos;
public:
	void cargarDatos() { }

	Empresa(int _id, string nombreCompleto, string _nickname, string _contrasena): Usuario(id, 2, nombreCompleto, _nickname, _contrasena) {
		cargarDatos();
		this->actividadesPropias = LinkedList<Actividad*>();
	}
	
	int crearCurso(Curso *nuevoCurso){
		cursos.agregarAlFinal(nuevoCurso);
	}

	int crearEspecializacion(Especializacion *_nuevaEspecializacion) {
		especializaciones.agregarAlFinal(_nuevaEspecializacion);
	}
	void verProfesores() {

	}
	bool eliminarCUrsoEspecializacion() {

	}
	bool anadirCUrsoEspecilizacion() {

	}
};
