#pragma once
// Headers propios
#include "Pantalla.h"
#include "Actividad.h"
#include "GestionadorCursos.h"
#include "Estudiante.h"
#include "Empresa.h"
#include "Login.h"
#include "LandingPage.h"
#include "DashboardEstudiante.h"
#include "DashboardOrganizacion.h"
#include "Registro.h"
#include "PantallaResultado.h"

// Forward declarations
class GestionadorCursos;
class Usuario;
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
	unique_ptr<GestionadorCursos> gestionadorCursos;
	vector<Actividad> actividades;
	unique_ptr<Estudiante> estudiante; 
	unique_ptr<Empresa> empresa;
	bool ejecutando;

	void cargarDatosArchivo() {
		ifstream archivo(".\\Resources\\Data\\actividades.txt");
		if (!archivo.is_open()) {
			throw runtime_error("No se pudo abrir el archivo de actividades"); // Nos salta error al ejecutar
		}

		string nombreEmpresa, titulo, descripcion, instructor, tituloActividad, descripcionActividad;
		int cantidad = 0;
		int tipo, idEmpresa;
		while (archivo >> idEmpresa) {
			archivo.ignore();
			archivo >> tipo;
			archivo.ignore();
			getline(archivo, nombreEmpresa);
			getline(archivo, tituloActividad);
			getline(archivo, descripcionActividad);

			if (tipo == 1) {
				getline(archivo, instructor);
				int cantidadClase = 0; archivo >> cantidadClase;
				archivo.ignore();
				//throw runtime_error(tituloActividad);
				vector<string> titulos(cantidadClase), descripciones(cantidadClase);
				for (int i = 0; i < cantidadClase; i++) {
					getline(archivo, titulo);
					getline(archivo, descripcion);
					titulos[i] = titulo;
					descripciones[i] = descripcion;
				}
				if (!gestionadorCursos->crearCurso(idEmpresa, tituloActividad, nombreEmpresa, cantidadClase, instructor, descripcionActividad, titulos, descripciones)) {
					throw runtime_error("Falla carga");
				} //else throw runtime_error("Logrado");

			}else{
				int cantidadCursos = 0;
				archivo >> cantidadCursos;
				archivo.ignore();
				vector<int> idsCursos(cantidadCursos);
				for (int i = 0; i < cantidadCursos; i++) {
					archivo >> idsCursos[i];
					archivo.ignore();
				}
				getline(archivo, descripcion);
				if (!gestionadorCursos->crearEspecializacion(idEmpresa, nombreEmpresa, tituloActividad, cantidadCursos, descripcionActividad, idsCursos)) {
					throw runtime_error("Carga Fallida en especializacion");
				}
			}
			cantidad++;
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
	Controladora() : ejecutando(true) {
		// Inicializar gestores
		//gestionadorUsuarios = make_unique<GestionadorUsuarios>()
		estudiante = nullptr;
		empresa = nullptr;
		gestionadorCursos = make_unique<GestionadorCursos>();
		
		// Cargar datos iniciales
		cargarDatosArchivo();
		cargarDatosInscripciones();
	}

	void run() 
	{
		unique_ptr<PantallaBase> pantallaActual = make_unique<LandingPage>(gestionadorCursos->getCursos(), gestionadorCursos->getEspecializaciones());
		while (ejecutando) 
		{
			ResultadoPantalla resultado = pantallaActual->ejecutar();
			// if (resultado.accion == AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE) throw runtime_error(estudiante->getNombreCompleto());

			switch (resultado.accion) 
			{
				case AccionPantalla::IR_A_LOGIN:
					pantallaActual = make_unique<Login>(estudiante, empresa);
					break;
				case AccionPantalla::IR_A_REGISTRO:
					pantallaActual = make_unique<Registro>();
					break;
				case AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE:
					// El Login ya validó las credenciales, simplemente establecemos el usuario
					//establecerUsuarioActual(resultado.email, resultado.tipoUsuario);
					if (estudiante) {
						pantallaActual = make_unique<DashboardEstudiante>();
					}
					else {
						// En caso de error, volvemos a la pantalla de login
						pantallaActual = make_unique<Login>();
					}
					break;
				case AccionPantalla::IR_A_DASHBOARD_ORGANIZACION:
					if (empresa) {
						pantallaActual = make_unique<DashboardOrganizacion>(empresa->getId(), empresa->getNombreCompleto());
					}
					else {
						// En caso de error, volvemos a la pantalla de login
						pantallaActual = make_unique<Login>(estudiante, empresa);
					}
					break;
				case AccionPantalla::IR_A_LANDING_PAGE:
					pantallaActual = make_unique<LandingPage>();
					break;
				case AccionPantalla::SALIR:
					ejecutando = false;
					system("cls");
					cout << "Gracias por usar CourseraClone. Hasta luego!" << endl;
					break;
				default:
					break;
			}
		}
	}

	/*
	bool establecerUsuarioActual(const string& email, TipoUsuario tipo) {
		try {
			// Creamos un objeto Usuario temporal
			Usuario temp;
			// Buscamos el usuario por su email
			int index = temp.buscarIndexUsuario(email, tipo);

			if (index != -1) {
				// Cargar los datos completos del usuario
				const string indexPath = (tipo == TipoUsuario::EMPRESA) ?
					EMPRESA_INDEX_FILE : ESTUDIANTE_INDEX_FILE;

				ifstream indexFile(indexPath, ios::in | ios::binary);
				if (!indexFile.is_open()) return false;

				indexFile.seekg(index * sizeof(UsuarioIndex), ios::beg);
				UsuarioIndex encontrado;
				indexFile.read(reinterpret_cast<char*>(&encontrado), sizeof(encontrado));
				indexFile.close();

				// Abrir el archivo de datos y cargar el usuario
				const string dataPath = (tipo == TipoUsuario::EMPRESA) ?
					EMPRESA_DATA_FILE : ESTUDIANTE_DATA_FILE;

				ifstream dataFile(dataPath, ios::in | ios::binary);
				if (!dataFile.is_open()) return false;

				dataFile.seekg(encontrado.offset, ios::beg);
				UsuarioBinario binRec;
				dataFile.read(reinterpret_cast<char*>(&binRec), sizeof(binRec));
				dataFile.close();

				// Crear el usuario actual
				string nombre(binRec.nombreCompleto, strnlen(binRec.nombreCompleto, MAX_FIELD_LEN));
				string usuario(binRec.nombreDeUsuario, strnlen(binRec.nombreDeUsuario, MAX_FIELD_LEN));
				string hash(binRec.contrasenaHash, strnlen(binRec.contrasenaHash, MAX_FIELD_LEN));

				usuarioActual = make_unique<Usuario>(encontrado.offset, tipo, nombre, usuario, hash);
				return true;
			}
			return false;
		}
		catch (const exception& e) {
			cerr << "Error al establecer usuario: " << e.what() << endl;
			return false;
		}
	}
	*/

	/*
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
	*/
	
	/*
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
	*/
	
	/*
	void cerrarSesion() {
		if (gestionadorUsuarios) {
			gestionadorUsuarios->cerrarSesion();
		}
		usuarioActual = nullptr;
	}
	*/
	

	// Listados
	const vector<Actividad>& listarActividades() const { return actividades; }

	// Getters
	//Usuario* getUsuarioActual() const { return usuarioActual; }
	//GestionadorUsuarios* getGestionadorUsuarios() const { return gestionadorUsuarios.get(); }
	//GestionadorCursos* getGestionadorCursos() const { return gestionadorCursos.get(); }

	//LinkedList<Curso*> getCursos();
	//LinkedList<Especializacion*> getEspecializaciones();
};