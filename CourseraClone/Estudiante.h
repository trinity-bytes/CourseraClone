#pragma once
#include "Usuario.h"

class Estudiante :public Usuario{
private:
	string nombre, apellido;
	// LinkedList<Inscripcion> inscripciones;
	// Stack<Inscripcion> actividadesInscritas;
	// Queue<Inscripcion> actividadesRecientesCompletadas;
public:
	Estudiante(string _nombre, string _apellido): Usuario(id, tipoUsuario,nickName, contrasena){
		nombre = _nombre;
		apellido = _apellido;
	}
	void verBoletas() {

	}

	void verCursosInscritos() {

	}
	int IncribirseAcurso() {

	}

};
