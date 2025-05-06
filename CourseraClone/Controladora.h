#pragma once
#include "LinkedList.h"
#include "Actividad.h"
#include "PriorityQueue.h"
#include "Especializacion.h"
#include <string>
#include "algoritmosOrdenamiento.h"
#include "UI_Menu_LandingPage.h"
#include <fstream>

class Controladora {
private:
	Usuario* usuario;
	LinkedList<Curso*> cursosTodos;
	LinkedList<Especializacion*> especializacionesTodos;
	
	vector<ElementoMenu> cursosPopularesLandingPage;
	vector<ElementoMenu> especializacionesPopularesLandingPage;
	
	vector<Actividad*> actividades;

private:
	void cargarDatosArchivo() {
		ifstream ruta("Resources/Data/actividades.txt");
		if (ruta.is_open()) {
			int id = 1, idEmpresa, tipo;
			string nombreEmpresa, titulo, descripcion;

			while (ruta.peek() != EOF) {
				ruta >> idEmpresa; ruta.ignore();
				ruta >> tipo; ruta.ignore();
				getline(ruta, nombreEmpresa);
				getline(ruta, titulo);
				getline(ruta, descripcion);

				if (tipo == 1) {
					string instructor;
					getline(ruta, instructor);
					int cantidadClases;
					ruta >> cantidadClases; ruta.ignore();
					Curso* nuevoCurso = new Curso(id, idEmpresa, titulo, nombreEmpresa, cantidadClases, instructor, descripcion);
					for (int i = 0; i < cantidadClases; i++) {
						string tituloClase, descripcionClase;
						getline(ruta, tituloClase);
						getline(ruta, descripcionClase);
						nuevoCurso->añadirClases(tituloClase, descripcionClase);
					}
					actividades.push_back(nuevoCurso);
					cursosTodos.agregarAlFinal(nuevoCurso);
				}
				else if (tipo == 2) {
					int cantidadCursos;
					ruta >> cantidadCursos; ruta.ignore();
					Especializacion* nuevaEspecializacion = new Especializacion(id, idEmpresa, nombreEmpresa, titulo, cantidadCursos, descripcion);
					for (int i = 0; i < cantidadCursos; i++) {
						int idCurso;
						ruta >> idCurso; ruta.ignore();
						nuevaEspecializacion->añadirCurso(dynamic_cast<Curso*>(actividades[idCurso]));
					}
					actividades.push_back(nuevaEspecializacion);
					especializacionesTodos.agregarAlFinal(nuevaEspecializacion);
				}
				else {
					cout << "Tipo de actividad no reconocido." << endl;
				}
			}
			id++;

		}
	}
	void cargarDatosInscripciones() {
		ifstream ruta("Resources/Data/inscripciones.dat", ios::binary);
		if (ruta.is_open()) {
			InscripcionBinaria inscripcion;
			while (ruta.read(reinterpret_cast<char*>(&inscripcion), sizeof(inscripcion))) {
				int idActividad = inscripcion.idActividad;
				actividades[idActividad - 1]->aumentarAlumno(1);
			}
			ruta.close();
		}
		else {
			cout << "Error al abrir el archivo de inscripciones." << endl;
		}
	}
	void cargarDatosLanding(int maximo) {
		cursosPopularesLandingPage = vector<ElementoMenu>(maximo);
		especializacionesPopularesLandingPage = vector<ElementoMenu>(maximo);

		PriorityQueue<Curso*> priorityCursosLandingPage(maximo);
		PriorityQueue<Especializacion*> priorityEspecializacionesLandingPage(maximo);
		auto cantidad = [](Actividad* a) {
			return a->getCantidadAlumnos();
			};
		priorityCursosLandingPage.llenarDesde<int>(cursosTodos, cantidad);
		priorityEspecializacionesLandingPage.llenarDesde<int>(especializacionesTodos, cantidad);

		vector<string> titulosCursos, descripcionesCursos, titulosEspecializaciones, descripcionesEspecializaciones;
		auto tituloActividad = [](Actividad* a) { // Retorna el dato de titulo
			return a->getTitulo();
			};
		auto descripcionActividad = [](Actividad* a) { // Retorna el dato de inscripción
			return a->getDescripcion();
			};

		// obtener datos
		titulosCursos = priorityCursosLandingPage.extraerDato<string>(tituloActividad);
		titulosEspecializaciones = priorityEspecializacionesLandingPage.extraerDato<string>(tituloActividad);
		descripcionesCursos = priorityCursosLandingPage.extraerDato<string>(descripcionActividad);
		descripcionesEspecializaciones = priorityEspecializacionesLandingPage.extraerDato<string>(descripcionActividad);

		for (int i = 0; i < maximo; i++) {
			cursosPopularesLandingPage[i].titulo = titulosCursos[i];
			cursosPopularesLandingPage[i].descripcion = descripcionesCursos[i];
			especializacionesPopularesLandingPage[i].titulo = titulosEspecializaciones[i];
			especializacionesPopularesLandingPage[i].descripcion = descripcionesEspecializaciones[i];
		}
	}


public:
	void cargarTodosDatos() {
		actividades = vector<Actividad*>();
		cursosTodos = LinkedList<Curso*>();
		especializacionesTodos = LinkedList<Especializacion*>();

		cargarDatosArchivo();
		cargarDatosInscripciones();
		cargarDatosLanding(3);
		usuario = new Usuario();
	}

	Controladora() {
		cargarTodosDatos();
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