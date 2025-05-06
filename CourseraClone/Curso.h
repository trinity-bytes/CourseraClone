#pragma once
#include "Actividad.h"
#include "Instructor.h"
#include "algoritmosBusqueda.h"
#include <fstream>


class Curso : public Actividad {
private:
	string instructor;
	int cantidadModulo;

public:
	Curso(int _id, int _idEmpresa, string _titulo, string _nombreEmpresa, int _cantidadAlumnos, int _tipo, string _instructor, int _cantidadModulo, string _descripcion) : Actividad(_id, _idEmpresa, _titulo, _nombreEmpresa, _cantidadAlumnos, _tipo, _descripcion) {
		instructor = _instructor;
		cantidadModulo = _cantidadModulo;
	}

	void guardar() {
		ofstream archivo("Resources/Data/cursos_muestra.txt", ios::app);
		if (archivo.is_open()) {
			archivo << nombreEmpresa << '\n';
			archivo << titulo << '\n';
			archivo << descripcion << '\n';
			archivo << instructor << '\n';
			archivo << cantidadModulo << '\n';
			archivo.close();
		}
		else {
			cout << "Error al abrir el archivo." << endl;
		}
	}
	// getters
	string getTitulo() {
		return titulo;
	}
	int getCantidadModulo() {
		return cantidadModulo;
	}
	int getId() {
		return id;
	}
};