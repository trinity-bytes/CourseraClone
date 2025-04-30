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
	int cantidadAlumnos;
	int tipo;

public:
	Actividad(int _id, int _idEmpresa, string _nombreEmpresa, string _titulo, int _cantidadAlumnos, int _tipo) {
		id = _id;
		idEmpresa = _idEmpresa;
		nombreEmpresa = _nombreEmpresa;
		titulo = _titulo;
		cantidadAlumnos = _cantidadAlumnos;
		tipo = _tipo;
	}

	virtual void mostrar() {}
};