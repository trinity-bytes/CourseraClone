#pragma once
#include "LinkedList.h"
#include "Actividad.h"
#include "algoritmosOrdenamiento.h"
#include <fstream>

class Controladora {
private:
	//Usuario usario;
	LinkedList<Actividad> actividadesBuscadas;
	// vector con iteradores a las actividades
	// vector con iteradores a las especializaciones
	vector<Actividad*> actividades;

public:

	void cargarDatos() {
		
	}

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