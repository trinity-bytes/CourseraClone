#pragma once
#include "Actividad.h"
#include "Curso.h"
#include <vector>
#include "LinkedList.h"

class Especializacion : public Actividad {
private:
	LinkedList<Curso*> cursos;

public:
	Especializacion(int _id, int _idEmpresa, string _nombreEmpresa, string _titulo, int _cantidadAlumnos, string _descripcion)
		: Actividad(_id, _idEmpresa, _nombreEmpresa, _titulo, _cantidadAlumnos, 2, _descripcion) {
		cursos = LinkedList<Curso*>();
	}

	void guardar() {
		ofstream archivo("Resources/Data/actividades.txt", ios::app);
		if (archivo.is_open()) {
			archivo << idEmpresa << '\n';
			archivo << tipo << '\n';
			archivo << nombreEmpresa << '\n';
			archivo << titulo << '\n';
			archivo << descripcion << '\n';
			archivo << int(cursos.getTamano()) << '\n';

			auto conseguirIDs = [](Curso* c) {
				return c->getId();
				};

			vector<int> ids = cursos.extraerDato<int>(conseguirIDs);

			for (int i = 0; i < int(cursos.getTamano()); i++) {
				if (i != 0) archivo << " ";
				archivo << ids[i];
			}
			archivo << '\n';

			archivo.close();
		}
		else {
			cout << "Error al abrir el archivo." << endl;
		}
	}

	void añadirCurso(Curso* _curso) {
		cursos.agregarAlFinal(_curso);
	}
};