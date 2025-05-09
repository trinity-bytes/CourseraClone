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
#include "PantallaResultado.h"

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
	}

	void run() {
		std::unique_ptr<PantallaBase> pantallaActual = std::make_unique<LandingPage>();
		while (ejecutando) {
			ResultadoPantalla resultado = pantallaActual->ejecutar();
			switch (resultado.accion) {
				case AccionPantalla::IR_A_LOGIN:
					pantallaActual = std::make_unique<Login>();
					break;
				case AccionPantalla::IR_A_REGISTRO:
					pantallaActual = std::make_unique<Registro>();
					break;
				case AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE:
					if (iniciarSesion(resultado.email, resultado.password)) {
						pantallaActual = std::make_unique<DashboardEstudiante>();
					} else {
						pantallaActual = std::make_unique<Login>();
					}
					break;
				case AccionPantalla::IR_A_LANDING_PAGE:
					pantallaActual = std::make_unique<LandingPage>();
					break;
				case AccionPantalla::SALIR:
					ejecutando = false;
					break;
				default:
					break;
			}
		}
	}

	// Autenticación
	bool iniciarSesion(const std::string& email, const std::string& password) {
		try {
			if (gestionadorUsuarios->autenticarUsuario(email, password)) {
				usuarioActual = gestionadorUsuarios->getUsuarioActual();
				return usuarioActual != nullptr;
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
	}

	// Listados
	const std::vector<Actividad>& listarActividades() const { return actividades; }

	// Getters
	Usuario* getUsuarioActual() const { return usuarioActual; }
	GestionadorUsuarios* getGestionadorUsuarios() const { return gestionadorUsuarios.get(); }
	GestionadorCursos* getGestionadorCursos() const { return gestionadorCursos.get(); }

	LinkedList<Curso*> getCursos();
	LinkedList<Especializacion*> getEspecializaciones();
};