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
#include "memory"  // Para std::unique_ptr
#include "stack"   // Para std::stack

class Controladora 
{
private:
	Usuario* usuarioActual;
	unique_ptr<MenuState> estadoActual;
	stack<unique_ptr<MenuState>> historialEstados;

	// Gestores
	unique_ptr<GestionadorUsuarios> gestionadorUsuarios;
	unique_ptr<GestionadorCursos> gestionadorCursos;

	// Colecciones de actividades
	LinkedList<Curso*> cursosTodos;
	LinkedList<Especializacion*> especializacionesTodos;
	vector<Actividad*> actividades;
	
	vector<ElementoMenu> cursosPopularesLandingPage;
	vector<ElementoMenu> especializacionesPopularesLandingPage;
	
	bool running;

private:
	void cargarDatosArchivo() 
	{
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
	


public:
	void cargarTodosDatos() 
	{
		actividades = vector<Actividad*>();
		cursosTodos = LinkedList<Curso*>();
		especializacionesTodos = LinkedList<Especializacion*>();

		cargarDatosArchivo();
		cargarDatosInscripciones();
		usuarioActual = new Usuario();
	}

	Controladora() : usuarioActual(nullptr), running(true) 
	{
		cargarTodosDatos();
		estadoActual = make_unique<LandingPageState>(this);
		gestionadorUsuarios = make_unique<GestionadorUsuarios>();
		gestionadorCursos = make_unique<GestionadorCursos>();
	}

	~Controladora() 
	{
		if (usuarioActual) delete usuarioActual;
	}

	/// Métodos de navegación
	void navegarA(unique_ptr<MenuState> nuevoEstado) 
	{
		historialEstados.push(move(estadoActual));
		estadoActual = move(nuevoEstado);
	}

	void volverAtras() 
	{
		if (!historialEstados.empty())
		{
			estadoActual = move(historialEstados.top());
			historialEstados.pop();
		}
	}

	void irAInicio() 
	{
		while (!historialEstados.empty())
		{
			historialEstados.pop();
		}
		estadoActual = make_unique<LandingPageState>(this);
	}

	/// Métodos de autenticación
	bool iniciarSesion(const string& username, const string& password) 
	{
		// Intentar login como estudiante primero
		Usuario usuarioTemp;
		LoginStatus status = Usuario::login(usuarioTemp, TipoUsuario::ESTUDIANTE, username, password);
		
		// Si no es estudiante, intentar como empresa
		if (status == LoginStatus::USER_NOT_FOUND) {
			status = Usuario::login(usuarioTemp, TipoUsuario::EMPRESA, username, password);
		}

		if (status == LoginStatus::SUCCESS) {
			usuarioActual = new Usuario(usuarioTemp);
			
			// Navegar al dashboard correspondiente
			if (usuarioActual->getTipoUsuario() == TipoUsuario::ESTUDIANTE) { 
				navegarA(make_unique<DashboardEstudianteState>(this));
			}
			else if (usuarioActual->getTipoUsuario() == TipoUsuario::EMPRESA) { 
				navegarA(make_unique<DashboardOrganizacionState>(this));
			}
			
			return true;
		}
		return false;
	}

	void cerrarSesion() 
	{
		if (usuarioActual) 
		{
			delete usuarioActual;
			usuarioActual = nullptr;
		}
		irAInicio();
	}

	bool registrarUsuario(int tipoUsuario, const int& id, 
		const string& nombre, const string& username, 
		const string& password)
	{
		return gestionadorUsuarios->registrarUsuario(tipoUsuario, id, nombre, username, password);
	}

	/// Métodos para cursos y especializaciones
	bool crearCurso(const string& titulo, const string& descripcion, 
		int cantidadClases, const string& instructor) 
	{
		if (!usuarioActual || usuarioActual->getTipoUsuario() != TipoUsuario::EMPRESA)
		{
			return false;
		}

		return gestionadorCursos->crearCurso(
			usuarioActual->getId(),
			titulo,
			usuarioActual->getUsername(),
			cantidadClases,
			instructor,
			descripcion
		);
	}

	bool crearEspecializacion(
		const string& titulo, 
		const string& descripcion, 
		int cantidadCursos, 
		const vector<int>& idsCursos) 
	{
		if (!usuarioActual || usuarioActual->getTipoUsuario() != TipoUsuario::EMPRESA)
		{
			return false;
		}

		vector<int> idsCursosCopy = idsCursos;
		return gestionadorCursos->crearEspecializacion(
			usuarioActual->getId(),
			usuarioActual->getUsername(),
			titulo,
			cantidadCursos,
			descripcion,
			idsCursosCopy
		);
	}

	// Métodos de búsqueda
	vector<Curso*> buscarCursos(const string& criterio) 
	{
		return gestionadorCursos->buscarCursos(criterio);
	}

	vector<Especializacion*> buscarEspecializaciones(const string& criterio) 
	{
		return gestionadorCursos->buscarEspecializaciones(criterio);
	}

	// Getters
	Usuario* getUsuarioActual() const { return usuarioActual; }
	MenuState* getEstadoActual() const { return estadoActual.get(); }
	TipoUsuario getTipoUsuarioActual() const { return usuarioActual->getTipoUsuario(); }

	// Métodos de inscripción
	bool inscribirseACurso(int idCurso) {
		if (!usuarioActual || usuarioActual->getTipoUsuario() != TipoUsuario::ESTUDIANTE) {
			return false;
		}
		return gestionadorCursos->inscribirEstudianteACurso(usuarioActual->getId(), idCurso);
	}

	bool inscribirseAEspecializacion(int idEspecializacion) {
		if (!usuarioActual || usuarioActual->getTipoUsuario() != TipoUsuario::ESTUDIANTE) {
			return false;
		}
		return gestionadorCursos->inscribirEstudianteAEspecializacion(usuarioActual->getId(), idEspecializacion);
	}

	// Métodos de progreso
	bool actualizarProgresoCurso(int idCurso, int progreso) {
		if (!usuarioActual || usuarioActual->getTipoUsuario() != TipoUsuario::ESTUDIANTE) {
			return false;
		}
		return gestionadorCursos->actualizarProgresoCurso(usuarioActual->getId(), idCurso, progreso);
	}

	// Métodos de calificación
	bool calificarCurso(int idCurso, int calificacion, const string& comentario) {
		if (!usuarioActual || usuarioActual->getTipoUsuario() != TipoUsuario::ESTUDIANTE) {
			return false;
		}
		return gestionadorCursos->agregarCalificacionCurso(usuarioActual->getId(), idCurso, calificacion, comentario);
	}

	// Métodos de listado
	vector<Curso*> listarCursosPorCategoria(const string& categoria) {
		return gestionadorCursos->listarCursosPorCategoria(categoria);
	}

	vector<Especializacion*> listarEspecializacionesPorCategoria(const string& categoria) {
		return gestionadorCursos->listarEspecializacionesPorCategoria(categoria);
	}

	// Métodos de gestión de contenido
	bool agregarContenidoCurso(int idCurso, const string& titulo, const string& contenido) {
		if (!usuarioActual || usuarioActual->getTipoUsuario() != TipoUsuario::EMPRESA) {
			return false;
		}
		return gestionadorCursos->agregarContenidoCurso(idCurso, titulo, contenido);
	}

	bool modificarContenidoCurso(int idCurso, int idContenido, const string& nuevoContenido) {
		if (!usuarioActual || usuarioActual->getTipoUsuario() != TipoUsuario::EMPRESA) {
			return false;
		}
		return gestionadorCursos->modificarContenidoCurso(idCurso, idContenido, nuevoContenido);
	}

	// Método de renderizado
	void run() 
	{
		while (running && estadoActual) 
		{
			estadoActual->render();
			int tecla = _getch();

			if (tecla == 0 || tecla == 224) tecla = _getch();

			estadoActual->handleInput(tecla);
			unique_ptr<MenuState> nextState = estadoActual->getNextState();

			if (nextState) {
				navegarA(move(nextState));
			}
		}
	}
};