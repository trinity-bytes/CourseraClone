#pragma once

// Headers propios
#include "Pantalla.h"
#include "Actividad.h"
#include "GestionadorUsuarios.h"
#include "GestionadorCursos.h"
#include "Usuario.h"
#include "Login.h"
#include "LandingPage.h"
#include "DashboardEstudiante.h"
#include "Registro.h"

// Forward declarations
class GestionadorUsuarios;
class GestionadorCursos;
class Usuario;
class LandingPageState;
class LoginState;
class Curso;
class Especializacion;

template<typename T>
class LinkedList;

// Headers de la libreria estandar
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <conio.h>
#include <stdexcept>

class Controladora {
private:
	std::unique_ptr<PantallaBase> pantallaActual;
	std::unique_ptr<GestionadorUsuarios> gestionadorUsuarios;
	std::unique_ptr<GestionadorCursos> gestionadorCursos;
	std::vector<Actividad> actividades;
	Usuario* usuarioActual;
	bool ejecutando;

	void cargarDatosArchivo() {
		std::ifstream archivo("actividades.txt");
		if (!archivo.is_open()) {
			throw std::runtime_error("No se pudo abrir el archivo de actividades");
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
		std::ifstream archivo("inscripciones.bin", std::ios::binary);
		if (!archivo.is_open()) {
			throw std::runtime_error("No se pudo abrir el archivo de inscripciones");
		}

		try {
			InscripcionBinaria inscripcion;
			while (archivo.read(reinterpret_cast<char*>(&inscripcion), sizeof(InscripcionBinaria))) {
				int idx = inscripcion.idActividad - 1;
				if (idx >= 0 && idx < static_cast<int>(actividades.size())) {
					actividades[idx].aumentarAlumno(1);
				}
			}
			
			if (!archivo.eof()) {
				throw std::runtime_error("Error al leer el archivo de inscripciones");
			}
		}
		catch (const std::exception& e) {
			archivo.close();
			throw std::runtime_error(std::string("Error al procesar inscripciones: ") + e.what());
		}
		
		archivo.close();
	}

public:
	Controladora() : usuarioActual(nullptr), ejecutando(true) {
		// Inicializar gestores
		gestionadorUsuarios = std::make_unique<GestionadorUsuarios>();
		gestionadorCursos = std::make_unique<GestionadorCursos>();
		
		// Cargar datos iniciales
		cargarDatosArchivo();
		cargarDatosInscripciones();
		
		// Iniciar con la pantalla de landing page
		cambiarPantalla(std::make_unique<LandingPage>(this));
	}

	~Controladora() {
		// Limpiar recursos
	}

	// Navegación
	void cambiarPantalla(std::unique_ptr<PantallaBase> nuevaPantalla) {
		pantallaActual = std::move(nuevaPantalla);
	}

	void ejecutarPantallaActual() {
		if (!pantallaActual) return;

		// Renderizar la pantalla actual
		pantallaActual->renderizar();

		// Manejar input si hay tecla presionada
		if (_kbhit()) {
			int tecla = _getch();
			pantallaActual->manejarInput(tecla);

			// Verificar si hay cambio de pantalla
			Pantalla siguientePantalla = pantallaActual->getSiguientePantalla();
			if (siguientePantalla != pantallaActual->getPantallaActual()) {
				switch (siguientePantalla) {
					case Pantalla::LOGIN:
						cambiarPantalla(std::make_unique<Login>(this));
						break;
					case Pantalla::LANDING_PAGE:
						cambiarPantalla(std::make_unique<LandingPage>(this));
						break;
					case Pantalla::DASHBOARD_ESTUDIANTE:
						cambiarPantalla(std::make_unique<DashboardEstudiante>(this));
						break;
					case Pantalla::REGISTRO:
						cambiarPantalla(std::make_unique<Registro>(this));
						break;
					default:
						break;
				}
			}
		}
	}

	// Autenticación
	bool iniciarSesion(const std::string& email, const std::string& password) {
		try {
			if (gestionadorUsuarios->autenticarUsuario(email, password)) {
				usuarioActual = gestionadorUsuarios->getUsuarioActual();
				
				if (usuarioActual) {
					if (usuarioActual->getTipoUsuario() == TipoUsuario::ESTUDIANTE) {
						cambiarPantalla(std::make_unique<DashboardEstudiante>(this));
					}
					// TODO: Implementar otros tipos de usuario
					return true;
				}
			}
			return false;
		}
		catch (const std::exception& e) {
			std::cerr << "Error durante el inicio de sesión: " << e.what() << std::endl;
			return false;
		}
	}

	bool registrarUsuario(const std::string& nombre, const std::string& email,
						 const std::string& password, const std::string& tipo) {
		try {
			return gestionadorUsuarios->registrarUsuario(nombre, email, password, tipo);
		}
		catch (const std::exception& e) {
			std::cerr << "Error durante el registro: " << e.what() << std::endl;
			return false;
		}
	}

	void cerrarSesion() {
		if (gestionadorUsuarios) {
			gestionadorUsuarios->cerrarSesion();
		}
		usuarioActual = nullptr;
		cambiarPantalla(std::make_unique<LandingPage>(this));
	}

	// Listados
	const std::vector<Actividad>& listarActividades() const { return actividades; }

	// Ejecución
	void run() {
		while (ejecutando) {
			ejecutarPantallaActual();
			Sleep(16); // Aproximadamente 60 FPS
		}
	}

	// Getters
	Usuario* getUsuarioActual() const { return usuarioActual; }
	GestionadorUsuarios* getGestionadorUsuarios() const { return gestionadorUsuarios.get(); }
	GestionadorCursos* getGestionadorCursos() const { return gestionadorCursos.get(); }

	LinkedList<Curso*> getCursos();
	LinkedList<Especializacion*> getEspecializaciones();
	
};