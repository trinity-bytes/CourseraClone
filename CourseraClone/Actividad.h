#pragma once
#include "Empresa.h"
#include <iostream>
using namespace std;

class Actividad {
protected:
	int id;
	int idEmpresa;
	string nombreEmpresa;
	string titulo;
	string descripcion;
	int cantidadAlumnos;
	int tipo;

public:
	Actividad(int _id, int _idEmpresa, string _nombreEmpresa, string _titulo, int _cantidadAlumnos, int _tipo, string _descripcion) {
		id = _id;
		idEmpresa = _idEmpresa;
		nombreEmpresa = _nombreEmpresa;
		titulo = _titulo;
		cantidadAlumnos = _cantidadAlumnos;
		tipo = _tipo;
		descripcion = _descripcion;
	}

	void aumentarAlumno(int cantidad) {
		cantidadAlumnos += cantidad;
	}

	virtual void guardar() {}

	virtual void mostrar() {}

	int getId(){
		return id;
	}

	int getTipo(){
		return tipo;
	}

	int getCantidadAlumnos() {
		return cantidadAlumnos;
	}

	string getTitulo() {
		return titulo;
	}

	string getDescripcion() {
		return descripcion;
	}
};