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
#include "PerfilEstudiante.h"
#include "PerfilOrganizacion.h"
#include "EditarPerfil.h"
#include "MostrarCurso.h"
#include "MostrarEspecialidad.h"
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

			} else {
				int cantidadCursos = 0;
				archivo >> cantidadCursos;
				archivo.ignore();
				vector<int> idsCursos(cantidadCursos);
				for (int i = 0; i < cantidadCursos; i++) {
					archivo >> idsCursos[i];
					archivo.ignore();
				}
				if (!gestionadorCursos->crearEspecializacion(idEmpresa, nombreEmpresa, tituloActividad, cantidadCursos, descripcionActividad, idsCursos)) {
					throw runtime_error("Carga Fallida en especializacion");
				}
				// else throw runtime_error(tituloActividad);
			}
			cantidad++;
		}
		//throw runtime_error(to_string(cantidad));
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
						pantallaActual = make_unique<DashboardEstudiante>(
							estudiante->getId(),
							estudiante->getNombreCompleto()
						);
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
				case AccionPantalla::IR_A_PERFIL_ESTUDIANTE:
				    if (estudiante) {
				        pantallaActual = make_unique<PerfilEstudiante>(
				            estudiante->getId(),
				            estudiante->getNombreCompleto(),
				            estudiante->getUsername()
				        );
				    }
				    else {
				        // Si no hay estudiante, redirigir al login
				        pantallaActual = make_unique<Login>(estudiante, empresa);
				    }
				    break;
				case AccionPantalla::IR_A_PERFIL_ORGANIZACION:
				    if (empresa) {
				        pantallaActual = make_unique<PerfilOrganizacion>(
				            empresa->getId(),
				            empresa->getNombreCompleto(),
				            empresa->getUsername()
				        );
				    }
				    else {
				        // Si no hay empresa, redirigir al login
				        pantallaActual = make_unique<Login>(estudiante, empresa);
				    }
				    break;
				case AccionPantalla::IR_A_EDITAR_PERFIL:
				    if (estudiante) {
				        pantallaActual = make_unique<EditarPerfil>(
				            estudiante->getId(),
				            TipoUsuario::ESTUDIANTE,
				            estudiante->getNombreCompleto(),
				            estudiante->getUsername(),
				            &estudiante,
				            nullptr
				        );
				    }
				    else if (empresa) {
				        pantallaActual = make_unique<EditarPerfil>(
				            empresa->getId(),
				            TipoUsuario::EMPRESA,
				            empresa->getNombreCompleto(),
				            empresa->getUsername(),
				            nullptr,
				            &empresa
				        );
				    }
				    else {
				        // Si no hay usuario, redirigir al login
				        pantallaActual = make_unique<Login>(estudiante, empresa);
				    }
				    break;
				case AccionPantalla::IR_A_MOSTRAR_CURSO:
				{
					// Obtener el ID del curso desde el resultado
					int idCurso = resultado.idCursoSeleccionado; // Asumiendo que añadimos este campo a ResultadoPantalla

					// Intentar obtener el curso del GestionadorCursos
					Curso* cursoSeleccionado = gestionadorCursos->obtenerCursoPorId(idCurso);

					if (cursoSeleccionado) {
						pantallaActual = make_unique<MostrarCurso>(idCurso, cursoSeleccionado, resultado.accionAnterior);
					}
					else {
						// Si no se encuentra el curso, volver a la pantalla anterior
						pantallaActual = make_unique<LandingPage>(gestionadorCursos->getCursos(), gestionadorCursos->getEspecializaciones());
					}
					break;
				}
				case AccionPantalla::IR_A_MOSTRAR_ESPECIALIZACION:
				{
					// Obtener el ID de la especialización desde el resultado
					int idEspecializacion = resultado.idCursoSeleccionado; // Reutilizamos este campo para IDs de especialización

					// Intentar obtener la especialización del GestionadorCursos
					Especializacion* especializacionSeleccionada = gestionadorCursos->obtenerEspecializacionPorId(idEspecializacion);

					if (especializacionSeleccionada) {
						pantallaActual = make_unique<MostrarEspecialidad>(idEspecializacion, especializacionSeleccionada, resultado.accionAnterior);
					}
					else {
						// Si no se encuentra la especialización, volver a la pantalla anterior
						pantallaActual = make_unique<LandingPage>(gestionadorCursos->getCursos(), gestionadorCursos->getEspecializaciones());
					}
					break;
				}
				default:
					break;
			}
		}
	}

	// Listados
	const vector<Actividad>& listarActividades() const { return actividades; }

	// Getters
	//Usuario* getUsuarioActual() const { return usuarioActual; }
	//GestionadorUsuarios* getGestionadorUsuarios() const { return gestionadorUsuarios.get(); }
	//GestionadorCursos* getGestionadorCursos() const { return gestionadorCursos.get(); }

	//LinkedList<Curso*> getCursos();
	//LinkedList<Especializacion*> getEspecializaciones();
};