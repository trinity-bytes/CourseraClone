#pragma once
#include "Actividad.h"
#include "Curso.h"
#include <vector>
#include "LinkedList.h"

class Especializacion : public Actividad {
private:
	LinkedList<Curso*> cursos;

public:
	void guardar() {
		ofstream archivo("Resources/Data/actividades.txt", ios::app);
		if (archivo.is_open()) {
			archivo << id << '\n';
			archivo << idEmpresa << '\n';
			archivo << nombreEmpresa << '\n';
			archivo << titulo << '\n';
			archivo << descripcion << '\n';
			archivo << tipo << '\n';
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
};