#pragma once
// Headers propios
#include "LinkedList.h"
#include "Actividad.h"
#include "PriorityQueue.h"
#include "Especializacion.h"
#include "UI_Menu_LandingPage.h"
#include "Inscripcion.h"
<<<<<<< HEAD
#include <fstream>
#include "Usuario.h"
#include "Estudiante.h"
#include "Empresa.h"
#include "UI_MenuLanding_State.h"

class Controladora {
private:
	Usuario* usuarioActual;
=======

// librerias
#include "fstream"

class Controladora {
private:
	//Usuario* usuario;
>>>>>>> 1d73e309e3d2cc093cf45025a0c7f932947e2c37
	LinkedList<Curso*> cursosTodos;
	LinkedList<Especializacion*> especializacionesTodos;
	
	//vector<ElementoMenu> cursosPopularesLandingPage;
	//vector<ElementoMenu> especializacionesPopularesLandingPage;
	
	PriorityQueue<Actividad*> actividadesLandingPage;
	vector<Actividad*> actividades;

private:
	void cargarDatosArchivo() {


		ifstream ruta("Resources/Data/actividades.txt");
		if (ruta.is_open()) {
			int id = 0, idEmpresa, tipo;
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
					Curso* nuevoCurso = new Curso(id, idEmpresa, nombreEmpresa, titulo, descripcion, instructor, cantidadClases);
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
						int idCurso = 0;
						ruta >> idCurso; ruta.ignore();
						nuevaEspecializacion->añadirCurso(dynamic_cast<Curso*>(actividades[idCurso]));
					}
					actividades.push_back(nuevaEspecializacion);
					especializacionesTodos.agregarAlFinal(nuevaEspecializacion);
				}
				else {
					cout << "Tipo de actividad no reconocido." << endl;
				}
				id++;
			}
		
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
		//cursosPopularesLandingPage = vector<ElementoMenu>(maximo);
		//especializacionesPopularesLandingPage = vector<ElementoMenu>(maximo);

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
		auto descripcionActividad = [](Actividad* a) { // Retorna el dato de inscripci�n
			return a->getDescripcion();
			};

		// obtener datos
		titulosCursos = priorityCursosLandingPage.extraerDato<string>(tituloActividad);
		titulosEspecializaciones = priorityEspecializacionesLandingPage.extraerDato<string>(tituloActividad);
		descripcionesCursos = priorityCursosLandingPage.extraerDato<string>(descripcionActividad);
		descripcionesEspecializaciones = priorityEspecializacionesLandingPage.extraerDato<string>(descripcionActividad);

		for (int i = 0; i < maximo; i++) {
			//cursosPopularesLandingPage[i].titulo = titulosCursos[i];
			//cursosPopularesLandingPage[i].descripcion = descripcionesCursos[i];
			//especializacionesPopularesLandingPage[i].titulo = titulosEspecializaciones[i];
			//especializacionesPopularesLandingPage[i].descripcion = descripcionesEspecializaciones[i];
		}
	}


public:
	void cargarTodosDatos() {
		actividades = vector<Actividad*>();
		cursosTodos = LinkedList<Curso*>();
		especializacionesTodos = LinkedList<Especializacion*>();
	Controladora() : actividadesLandingPage(3) {
		usuarioActual = nullptr;
		vector<Actividad*> actividades;
		LinkedList<Curso*> cursosTodos;
		LinkedList<Especializacion*> especializacionesTodos;

		cargarDatosArchivo();
		cargarDatosInscripciones();
		cargarDatosLanding(0);
		//usuario = new Usuario();
	}

	Controladora() {
		cargarTodosDatos();
	}

	~Controladora() 
	{
		if (usuarioActual) {
			delete usuarioActual;
		}
	}

	bool iniciarSesion() {
		Usuario temp;
		if (Usuario::login("Resources/Data/usuarios.dat", temp)) {
			switch (temp.getTipoUsuario()) {
				case 1: // Estudiante
					usuarioActual = new Estudiante(temp.getNombre(), temp.getApellido());
					break;
				case 2: // Organizaci�n
					usuarioActual = new Empresa();
					break;
				default:
					cout << "Tipo de usuario no v�lido" << endl;
					return false;
			}
			return true;
		}
		return false;
	}

	bool registrarUsuario(int tipoUsuario, const string& nombre, const string& apellido, 
		const string& username, const string& password) {
		Usuario* nuevoUsuario;
		if (tipoUsuario == 1) {
			nuevoUsuario = new Estudiante(nombre, apellido);
		} else if (tipoUsuario == 2) {
			nuevoUsuario = new Empresa();
		} else {
			return false;
		}

		return Usuario::registrar("Resources/Data/usuarios.dat", *nuevoUsuario);
	}

	unique_ptr<MenuState> getNextStateAfterLogin() {
		if (!usuarioActual) return make_unique<LandingPageState>();

		switch (usuarioActual->getTipoUsuario()) {
			case 1: // Estudiante
				return make_unique<StudentDashboardState>(this);
			case 2: // Organización
				return make_unique<OrganizationDashboardState>(this);
			default:
				return make_unique<LandingPageState>();
		}
	}

	LinkedList<Actividad> buscarActividades() {
		vector<int> idCursos, idEspecializacion;
		usuario.getActividadesBuscadas(idCursos, idEspecializacion);
		mergeSort(idCursos, 0, int(idCursos.size()) - 1);
		mergeSort(idEspecializacion, 0, int(idEspecializacion.size()) - 1);

		ifstream cursos("./archivos/planos/cursos.txt");
		ifstream especializaciones("./archivos/planos/especializaciones.txt");

		*/
	}

	void mostrarDashboard() 
	{

	}

	void mostrarBusqueda() {

	}
};