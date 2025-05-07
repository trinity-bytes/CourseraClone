#pragma once

// Headers propios
#include "Menu_State.h"
#include "LandingPage_State.h"
#include "Login_State.h"
//#include "Registro_State.h"
#include "States/DashboardEstudiante_State.h"
#include "States/DashboardOrganizacion_State.h"
//#include "States/DashboardInstructor_State.h"
#include "Managers/GestionadorUsuarios.h"
#include "Managers/GestionadorCursos.h"
#include "Curso.h"
#include "Especializacion.h"
#include "Actividad.h"
#include "Usuario.h"

// Headers de la libreria estandar
#include <fstream>
#include <memory>
#include <stack>
#include <vector>
#include <string>


class Controladora {
private:
	std::unique_ptr<MenuState> estadoActual;
	std::unique_ptr<GestionadorUsuarios> gestionadorUsuarios;
	std::unique_ptr<GestionadorCursos> gestionadorCursos;
	std::vector<Actividad> actividades;
	Usuario* usuarioActual;
	bool ejecutando;

	void cargarDatosArchivo() {
		std::ifstream archivo("actividades.txt");
		if (!archivo.is_open()) {
			std::cerr << "Error al abrir el archivo de actividades" << std::endl;
			return;
		}

		std::string linea;
		while (std::getline(archivo, linea)) {
			Actividad actividad;
			actividad.titulo = linea;
			actividades.push_back(actividad);
		}
		archivo.close();
	}

	void cargarDatosInscripciones() {
		std::ifstream archivo("inscripciones.bin", std::ios::binary);
		if (!archivo.is_open()) {
			std::cerr << "Error al abrir el archivo de inscripciones" << std::endl;
			return;
		}

		InscripcionBinaria inscripcion;
		while (archivo.read(reinterpret_cast<char*>(&inscripcion), sizeof(InscripcionBinaria))) {
			// Procesar inscripción
		}
		archivo.close();
	}

public:
	Controladora() : usuarioActual(nullptr), ejecutando(true) {
		gestionadorUsuarios = std::make_unique<GestionadorUsuarios>();
		gestionadorCursos = std::make_unique<GestionadorCursos>();
		estadoActual = std::make_unique<LandingPage_State>(this);
		cargarDatosArchivo();
		cargarDatosInscripciones();
	}

	~Controladora() {
		// Los smart pointers se encargan de la limpieza automáticamente
	}

	// Navegación
	void cambiarEstado(std::unique_ptr<MenuState> nuevoEstado) {
		estadoActual = std::move(nuevoEstado);
	}

	// Autenticación
	bool iniciarSesion(const std::string& email, const std::string& password) {
		usuarioActual = gestionadorUsuarios->iniciarSesion(email, password);
		return usuarioActual != nullptr;
	}

	bool registrarUsuario(const std::string& nombre, const std::string& email, 
						 const std::string& password, const std::string& tipo) {
		return gestionadorUsuarios->registrarUsuario(nombre, email, password, tipo);
	}

	void cerrarSesion() {
		usuarioActual = nullptr;
	}

	// Gestión de cursos
	bool crearCurso(const std::string& titulo, const std::string& descripcion) {
		return gestionadorCursos->crearCurso(titulo, descripcion);
	}

	bool crearEspecializacion(const std::string& titulo, const std::string& descripcion) {
		return gestionadorCursos->crearEspecializacion(titulo, descripcion);
	}

	// Listados
	std::vector<Curso> listarCursos() const {
		return gestionadorCursos->listarCursos();
	}

	std::vector<Especializacion> listarEspecializaciones() const {
		return gestionadorCursos->listarEspecializaciones();
	}

	std::vector<Actividad> listarActividades() const {
		return actividades;
	}

	// Gestión de contenido
	bool agregarContenidoACurso(int cursoId, const std::string& titulo, 
							   const std::string& descripcion) {
		return gestionadorCursos->agregarContenidoACurso(cursoId, titulo, descripcion);
	}

	bool agregarContenidoAEspecializacion(int especializacionId, 
										const std::string& titulo, 
										const std::string& descripcion) {
		return gestionadorCursos->agregarContenidoAEspecializacion(
			especializacionId, titulo, descripcion);
	}

	// Ejecución
	void run() {
		while (ejecutando) {
			estadoActual->render();
			int tecla = getch();
			if (tecla == 27) { // ESC
				ejecutando = false;
			} else {
				estadoActual->handleInput(tecla);
				auto siguienteEstado = estadoActual->getNextState();
				if (siguienteEstado) {
					estadoActual = std::move(siguienteEstado);
				}
			}
		}
	}

	// Getters
	Usuario* getUsuarioActual() const { return usuarioActual; }
	GestionadorUsuarios* getGestionadorUsuarios() const { return gestionadorUsuarios.get(); }
	GestionadorCursos* getGestionadorCursos() const { return gestionadorCursos.get(); }
};