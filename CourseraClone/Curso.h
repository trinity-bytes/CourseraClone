#pragma once
#include "Actividad.h"
#include "Instructor.h"

class Curso : public Actividad {
private:
	string instructor;
	int cantidadModulo;

public:
	Curso(int _id, int _idEmpresa, string _titulo, string _nombreEmpresa, int _cantidadAlumnos, int _tipo, string _instructor) : Actividad(_id, _idEmpresa, _titulo, _nombreEmpresa, _cantidadAlumnos, _tipo, _instructor) {
		instructor = _instructor;
	}

	void mostrar() override {
		cout << "Curso ID: " << id << endl;
		cout << "ID Empresa: " << idEmpresa << endl;
		cout << "Titulo: " << titulo << endl;
		cout << "Cantidad Alumnos: " << cantidadAlumnos << endl;
		cout << "Tipo: " << tipo << endl;
	}
};