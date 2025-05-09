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
	unique_ptr<GestionadorUsuarios> gestionadorUsuarios;
	unique_ptr<GestionadorCursos> gestionadorCursos;
	vector<Actividad> actividades;
	Usuario* usuarioActual;
	bool ejecutando;

	void cargarDatosArchivo() {
		ifstream archivo(".\\Resources\\Data\\actividades.txt");
		if (!archivo.is_open()) {
			throw runtime_error("No se pudo abrir el archivo de actividades"); // Nos salta error al ejecutar
		}

		string linea;
		while (getline(archivo, linea)) {
			actividades.push_back(Actividad(
				0,     // id
				0,     // idEmpresa
				"",    // nombreEmpresa
				linea, // titulo
				0,     // cantidadAlumnos
				0,     // tipo
				""     // descripcion
			));
		}
		archivo.close();
	}

	void cargarDatosInscripciones() {
		ifstream archivo(".\\Resources\\Data\\inscripciones.bin", ios::binary);
		if (!archivo.is_open()) {
			throw runtime_error("No se pudo abrir el archivo de inscripciones"); // Nos salta error al ejecutar
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
				throw runtime_error("Error al leer el archivo de inscripciones");
			}
		}
		catch (const exception& e) {
			archivo.close();
			throw runtime_error(string("Error al procesar inscripciones: ") + e.what());
		}
		
		archivo.close();
	}

public:
	Controladora() : usuarioActual(nullptr), ejecutando(true) {
		// Inicializar gestores
		gestionadorUsuarios = make_unique<GestionadorUsuarios>();
		gestionadorCursos = make_unique<GestionadorCursos>();
		
		// Cargar datos iniciales
		cargarDatosArchivo();
		cargarDatosInscripciones();
	}

	void run() {
		unique_ptr<PantallaBase> pantallaActual = make_unique<LandingPage>();
		while (ejecutando) {
			ResultadoPantalla resultado = pantallaActual->ejecutar();
			switch (resultado.accion) {
				case AccionPantalla::IR_A_LOGIN:
					pantallaActual = make_unique<Login>();
					break;
				case AccionPantalla::IR_A_REGISTRO:
					pantallaActual = make_unique<Registro>();
					break;
				case AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE:
					if (iniciarSesion(resultado.email, resultado.password)) {
						pantallaActual = make_unique<DashboardEstudiante>();
					} else {
						pantallaActual = make_unique<Login>();
					}
					break;
				case AccionPantalla::IR_A_LANDING_PAGE:
					pantallaActual = make_unique<LandingPage>();
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
	bool iniciarSesion(const string& email, const string& password) {
		try {
			if (gestionadorUsuarios->autenticarUsuario(email, password)) {
				usuarioActual = gestionadorUsuarios->getUsuarioActual();
				return usuarioActual != nullptr;
			}
			return false;
		}
		catch (const exception& e) {
			cerr << "Error durante el inicio de sesión: " << e.what() << endl;
			return false;
		}
	}

	bool registrarUsuario(const string& nombre, const string& email,
						 const string& password, const string& tipo) {
		try {
			return gestionadorUsuarios->registrarUsuario(nombre, email, password, tipo);
		}
		catch (const exception& e) {
			cerr << "Error durante el registro: " << e.what() << endl;
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
	const vector<Actividad>& listarActividades() const { return actividades; }

	// Getters
	Usuario* getUsuarioActual() const { return usuarioActual; }
	GestionadorUsuarios* getGestionadorUsuarios() const { return gestionadorUsuarios.get(); }
	GestionadorCursos* getGestionadorCursos() const { return gestionadorCursos.get(); }

	LinkedList<Curso*> getCursos();
	LinkedList<Especializacion*> getEspecializaciones();
};