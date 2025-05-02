#pragma once
#include "LinkedList.h"
#include "Actividad.h"
#include "algoritmosOrdenamiento.h"
#include <fstream>

class Controladora {
private:
	//Usuario usario;
	LinkedList<Actividad> actividadesBuscadas;

public:
	LinkedList<Actividad> buscarActividades() {
		vector<int> idCursos, idEspecializacion;
		usuario.getActividadesBuscadas(idCursos, idEspecializacion);
		mergeSort(idCursos, 0, int(idCursos.size()) - 1);
		mergeSort(idEspecializacion, 0, int(idEspecializacion.size()) - 1);

		ifstream cursos("./archivos/planos/cursos.txt");
		ifstream especializaciones("./archivos/planos/especializaciones.txt");

		
	}

	void mostrarInterfaz() {

	}

	void mostrarBusqueda() {

	}
};