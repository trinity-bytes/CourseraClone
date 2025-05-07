#pragma once

// Headers propios
#include "Menu_State.h"
#include "Managers/GestionadorUsuarios.h"
#include "Managers/GestionadorCursos.h"
#include "Curso.h"
#include "Stack.h"
#include "Especializacion.h"
#include "Actividad.h"
#include "Usuario.h"

// Headers de la libreria estandar
#include <fstream>
#include <memory>
#include <vector>
#include <string>

// Los estados específicos 
#include "LandingPage_State.h"
#include "Login_State.h"
//#include "Registro_State.h"
//#include "States/DashboardEstudiante_State.h"
//#include "States/DashboardOrganizacion_State.h"
//#include "States/DashboardInstructor_State.h"

class Controladora {
private:
	unique_ptr<MenuState> estadoActual;
	unique_ptr<GestionadorUsuarios> gestionadorUsuarios;
	unique_ptr<GestionadorCursos> gestionadorCursos;
	vector<Actividad> actividades;
	Usuario* usuarioActual;
	bool ejecutando;

	void cargarDatosArchivo() {
		std::ifstream archivo("actividades.txt");
		if (!archivo.is_open()) {
			std::cerr << "Error al abrir el archivo de actividades" << std::endl;
			return;
		}

		std::string linea;
		while (getline(archivo, linea)) {
			actividades.push_back(Actividad(
				0,                  // id
				0,                  // idEmpresa
				"",                 // nombreEmpresa
				linea,             // titulo
				0,                  // cantidadAlumnos
				0,                  // tipo
				""                 // descripcion
			));
		}
		archivo.close();
	}

	void cargarDatosInscripciones() {
		ifstream archivo("inscripciones.bin", ios::binary);
		if (!archivo.is_open()) {
			cerr << "Error al abrir el archivo de inscripciones" << '\n';
			return;
		}

		InscripcionBinaria inscripcion;
		auto procesarInscripcion = [&](const InscripcionBinaria& ins) {
			int idx = ins.idActividad - 1;
			if (idx >= 0 && idx < actividades.size())
				actividades[idx].aumentarAlumno(1);
			};
	
		function<void()> leerRecursivo = [&]() { // lambda normal no permite recursividad
			InscripcionBinaria ins;
			if (archivo.read(reinterpret_cast<char*>(&ins), sizeof(ins))) {
				procesarInscripcion(ins);
				leerRecursivo();
			}

			};

		leerRecursivo();  // inicia la recursión
		archivo.close();
	}

public:
	Controladora() : usuarioActual(nullptr), ejecutando(true) {
		gestionadorUsuarios = make_unique<GestionadorUsuarios>();
		gestionadorCursos = make_unique<GestionadorCursos>();
		estadoActual = make_unique<LandingPageState>(this);
		cargarDatosArchivo();
		cargarDatosInscripciones();
	}

	~Controladora() {
		// Los smart pointers se encargan de la limpieza automáticamente
	}

	// Navegación
	void cambiarEstado(unique_ptr<MenuState> nuevoEstado) {
		estadoActual = move(nuevoEstado);
	}

	// Autenticación
	bool iniciarSesion(const string& email, const string& password) {
		//usuarioActual = gestionadorUsuarios->iniciarSesion(email, password);
		return usuarioActual != nullptr;
	}

	bool registrarUsuario(const string& nombre, const string& email, 
						 const string& password, const string& tipo) {
		//return gestionadorUsuarios->registrarUsuario(nombre, email, password, tipo);
	}

	void cerrarSesion() {
		usuarioActual = nullptr;
	}

	// Gestión de cursos
	bool crearCurso(const string& titulo, const string& descripcion) {
		//return gestionadorCursos->crearCurso(titulo, descripcion);
	}

	bool crearEspecializacion(const string& titulo, const string& descripcion) {
		//return gestionadorCursos->crearEspecializacion(titulo, descripcion);
	}

	// Listados
	vector<Curso> listarCursos() const {
		//return gestionadorCursos->listarCursos();
	}

	vector<Especializacion> listarEspecializaciones() const {
		//return gestionadorCursos->listarEspecializaciones();
	}

	vector<Actividad> listarActividades() const {
		return actividades;
	}

	// Gestión de contenido
	bool agregarContenidoACurso(int cursoId, const std::string& titulo, 
							   const std::string& descripcion) {
		//return gestionadorCursos->agregarContenidoACurso(cursoId, titulo, descripcion);
	}

	bool agregarContenidoAEspecializacion(
		int especializacionId, 
		const string& titulo, 
		const string& descripcion) 
	{
		//return gestionadorCursos->agregarContenidoAEspecializacion(especializacionId, titulo, descripcion);
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

	/*
	vector<int> getIdsCursos() const
	{
		vector<int> idsCursos;
		for (auto curso : cursosTodos) {
			idsCursos.push_back(curso->getId());
		}
		return idsCursos;
	}
	*/

	// Métodos de búsqueda
	vector<Curso*> buscarCursos(const string& criterio) 
	{
		return gestionadorCursos->buscarCursos(criterio);
	}

	vector<Especializacion*> buscarEspecializaciones(const string& criterio) 
	{
		return gestionadorCursos->buscarEspecializaciones(criterio);
	}

	/// --- Ejecución ---
	void run() 
	{
		while (ejecutando) {
			estadoActual->render();
			int tecla = _getch();
			if (tecla == 27) { // ESC
				ejecutando = false;
			} else {
				estadoActual->handleInput(tecla);
				auto siguienteEstado = estadoActual->getNextState();
				if (siguienteEstado) {
					estadoActual = move(siguienteEstado);
				}
			}
		}
	}

	// Getters
	Usuario* getUsuarioActual() const { return usuarioActual; }
	GestionadorUsuarios* getGestionadorUsuarios() const { return gestionadorUsuarios.get(); }
	GestionadorCursos* getGestionadorCursos() const { return gestionadorCursos.get(); }
};