#pragma once
// Headers propios
#include "LinkedList.h"
#include "Actividad.h"
#include "PriorityQueue.h"
#include "Especializacion.h"
#include "Inscripcion.h"
#include "Usuario.h"
#include "Estudiante.h"
#include "Empresa.h"
#include "MenuState.h"
#include "LandingPage_State.h"
#include "Login_State.h"
#include "States/DashboardEstudianteState.h"
#include "States/DashboardOrganizacionState.h"
#include "States/CrearCursoState.h"
#include "States/CrearEspecializacionState.h"
#include "Managers/GestionadorUsuarios.h"
#include "Managers/GestionadorCursos.h"

// librerias
#include "fstream"
#include "memory" // Para std::unique_ptr
#include "stack" // Para std::stack

class Controladora 
{
private:
	Usuario* usuarioActual;
	unique_ptr<MenuState> estadoActual;
	stack<unique_ptr<MenuState>> historialEstados;

	// Gestores
	GestionadorUsuarios gestionadorUsuarios;
	GestionadorCursos gestionadorCursos;

	//Usuario* usuario;
	LinkedList<Curso*> cursosTodos;
	LinkedList<Especializacion*> especializacionesTodos;
	
	//vector<ElementoMenu> cursosPopularesLandingPage;
	//vector<ElementoMenu> especializacionesPopularesLandingPage;
	
	vector<Actividad*> actividades;

	stack<unique_ptr<MenuState>> estados;
	unique_ptr<GestionadorUsuarios> userManager;
	unique_ptr<GestionadorCursos> courseManager;
	bool running;

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
						nuevoCurso->anadirClases(tituloClase, descripcionClase);
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
						nuevaEspecializacion->anadirCurso(dynamic_cast<Curso*>(actividades[idCurso]));
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
		auto descripcionActividad = [](Actividad* a) { // Retorna el dato de inscripción
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

		cargarDatosArchivo();
		cargarDatosInscripciones();
		cargarDatosLanding(0);
		//usuario = new Usuario();
	}

	Controladora() : usuarioActual(nullptr), running(true) {
		cargarTodosDatos();
		estadoActual = make_unique<LandingPageState>(this);
		userManager = make_unique<GestionadorUsuarios>();
		courseManager = make_unique<GestionadorCursos>();
		estados.push(make_unique<LoginState>(this));
	}

	~Controladora() {
		if (usuarioActual) {
			delete usuarioActual;
		}
	}

	// Métodos de navegación
	void navegarA(unique_ptr<MenuState> nuevoEstado) {
		historialEstados.push(move(estadoActual));
		estadoActual = move(nuevoEstado);
	}

	void volverAtras() {
		if (!historialEstados.empty()) {
			estadoActual = move(historialEstados.top());
			historialEstados.pop();
		}
	}

	void irAInicio() {
		while (!historialEstados.empty()) {
			historialEstados.pop();
		}
		estadoActual = make_unique<LandingPageState>(this);
	}

	// Métodos de autenticación
	bool iniciarSesion(const string& username, const string& password) {
		if (gestionadorUsuarios.autenticarUsuario(username, password)) {
			usuarioActual = gestionadorUsuarios.obtenerUsuario(username);
			
			// Navegar al dashboard correspondiente
			if (usuarioActual->getTipoUsuario() == 1) { // Estudiante
				navegarA(make_unique<DashboardEstudianteState>(this));
			}
			else if (usuarioActual->getTipoUsuario() == 2) { // Organización
				navegarA(make_unique<DashboardOrganizacionState>(this));
			}
			
			return true;
		}
		return false;
	}

	void cerrarSesion() {
		if (usuarioActual) {
			delete usuarioActual;
			usuarioActual = nullptr;
		}
		irAInicio();
	}

	bool registrarUsuario(int tipoUsuario, const string& nombre, const string& apellido,
		const string& username, const string& password) {
		return gestionadorUsuarios.registrarUsuario(tipoUsuario, nombre, apellido, username, password);
	}

	// Métodos de cursos
	bool crearCurso(const string& titulo, const string& descripcion, int cantidadClases,
		const string& instructor) {
		if (!usuarioActual || usuarioActual->getTipoUsuario() != 2) { // 2 = Empresa
			return false;
		}

		return gestionadorCursos.crearCurso(
			usuarioActual->getId(),
			titulo,
			usuarioActual->getNickname(),
			cantidadClases,
			instructor,
			descripcion
		);
	}

	vector<Curso*> buscarCursos(const string& criterio) {
		return gestionadorCursos.buscarCursos(criterio);
	}

	vector<Especializacion*> buscarEspecializaciones(const string& criterio) {
		return gestionadorCursos.buscarEspecializaciones(criterio);
	}

	// Getters
	Usuario* getUsuarioActual() const { return usuarioActual; }
	MenuState* getEstadoActual() const { return estadoActual.get(); }

	LinkedList<Actividad> buscarActividades() {
		vector<int> idCursos, idEspecializacion;
		/*
		//usuario.getActividadesBuscadas(idCursos, idEspecializacion);
		mergeSort(idCursos, 0, int(idCursos.size()) - 1);
		mergeSort(idEspecializacion, 0, int(idEspecializacion.size()) - 1);

		ifstream cursos("./archivos/planos/cursos.txt");
		ifstream especializaciones("./archivos/planos/especializaciones.txt");

		*/
	}

	void mostrarInterfaz() {

	}

	void mostrarBusqueda() {

	}

	void run() {
		while (running && !estados.empty()) {
			estados.top()->render();
			int tecla = _getch();
			if (tecla == 0 || tecla == 224) {
				tecla = _getch();
			}
			estados.top()->handleInput(tecla);
			unique_ptr<MenuState> nextState = estados.top()->getNextState();
			if (nextState) {
				estados.push(move(nextState));
			}
		}
	}

	bool login(const string& username, const string& password) {
		return userManager->autenticarUsuario(username, password);
	}

	bool registrarUsuario(const string& username, const string& password, const string& tipo) {
		return userManager->registrarUsuario(username, password, tipo);
	}

	string getTipoUsuario() const {
		return userManager->getTipoUsuario();
	}

	bool crearEspecializacion(const string& titulo, const string& descripcion, int cantidadCursos) {
		return courseManager->crearEspecializacion(titulo, descripcion, cantidadCursos);
	}

	void cerrarSesion() {
		userManager->cerrarSesion();
		while (!estados.empty()) {
			estados.pop();
		}
		estados.push(make_unique<LoginState>(this));
	}
};