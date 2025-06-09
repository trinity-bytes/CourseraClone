// Controlador principal del sistema CourseraClone
#pragma once

// Headers de la libreria estandar
#include <memory>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <conio.h>
#include <stdexcept>

// Headers propios
#include "GestionadorCursos.h"
#include "../Entities/Actividad.h"
#include "../Entities/Estudiante.h"
#include "../Entities/Empresa.h"
#include "../Screens/LoginScreen.h"
#include "../Screens/LandingPageScreen.h"
#include "../Screens/DashboardEstudianteScreen.h"
#include "../Screens/DashboardOrganizacionScreen.h"
#include "../Screens/PerfilEstudianteScreen.h"
#include "../Screens/PerfilOrganizacionScreen.h"
#include "../Screens/EditarPerfilScreen.h"
#include "../Screens/MostrarCursoScreen.h"
#include "../Screens/MostrarEspecialidadScreen.h"
#include "../Screens/RegistroScreen.h"
#include "../Screens/ExplorarContenidoScreen.h"
#include "../Screens/VerBoletasScreen.h"
#include "../Utils/ScreenSystem.h"

// Forward declarations
class GestionadorCursos;
class Usuario;
class Curso;
class Especializacion;

using namespace std;

// Constantes del sistema
const string RUTA_ACTIVIDADES = "Resources/Data/actividades.txt";
const string RUTA_INSCRIPCIONES = "Resources/Data/inscripciones.dat";
const int TIPO_CURSO = 1;
const int TIPO_ESPECIALIZACION = 2;

// Controlador principal del sistema CourseraClone
class Controladora 
{
private:
    // Atributos privados
    unique_ptr<GestionadorCursos> _gestionadorCursos;
    vector<Actividad> _actividades;
    Estudiante* _estudiante; 
    Empresa* _empresa;
    bool _ejecutando;

    // Métodos privados de carga de datos
    void cargarDatosArchivo();
    void cargarDatosInscripciones();
    
    // Métodos privados de navegación
    unique_ptr<PantallaBase> crearPantallaLogin();
    unique_ptr<PantallaBase> crearPantallaDashboardEstudiante();
    unique_ptr<PantallaBase> crearPantallaDashboardOrganizacion();
    unique_ptr<PantallaBase> crearPantallaLandingPage();

public:
    // Constructor y destructor
    Controladora();
    ~Controladora() = default;

    // Método principal de ejecución
    void run();

    // Getters públicos
    vector<Actividad>& listarActividades() { return _actividades; }
    GestionadorCursos* getGestionadorCursos() const { return _gestionadorCursos.get(); }
};

// Constructor
Controladora::Controladora() : _ejecutando(true) 
{
    // Inicializar gestores
    _gestionadorCursos = make_unique<GestionadorCursos>();
    _estudiante = new Estudiante(0, "", "", "");
    _empresa = new Empresa(0, "", "", "");

    // Cargar datos iniciales
    cargarDatosArchivo();
    cargarDatosInscripciones();
}

// Carga datos de actividades desde archivo de texto
void Controladora::cargarDatosArchivo() 
{
    ifstream archivo(RUTA_ACTIVIDADES);
    if (!archivo.is_open()) {
        throw runtime_error("No se pudo abrir el archivo de actividades: " + RUTA_ACTIVIDADES);
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

        if (tipo == TIPO_CURSO) {
            // Procesar curso
            getline(archivo, instructor);
            int cantidadClase = 0; 
            archivo >> cantidadClase;
            archivo.ignore();
            
            vector<string> titulos(cantidadClase), descripciones(cantidadClase);
            for (int i = 0; i < cantidadClase; i++) {
                getline(archivo, titulo);
                getline(archivo, descripcion);
                titulos[i] = titulo;
                descripciones[i] = descripcion;
            }
            
            if (!_gestionadorCursos->crearCurso(idEmpresa, tituloActividad, nombreEmpresa, cantidadClase, instructor, descripcionActividad, titulos, descripciones)) {
                throw runtime_error("Error al crear curso: " + tituloActividad);
            }
        } 
        else if (tipo == TIPO_ESPECIALIZACION) {
            // Procesar especialización
            int cantidadCursos = 0;
            archivo >> cantidadCursos;
            archivo.ignore();
            
            vector<int> idsCursos(cantidadCursos);
            for (int i = 0; i < cantidadCursos; i++) {
                archivo >> idsCursos[i];
                archivo.ignore();
            }
            
            if (!_gestionadorCursos->crearEspecializacion(idEmpresa, nombreEmpresa, tituloActividad, cantidadCursos, descripcionActividad, idsCursos)) {
                throw runtime_error("Error al crear especialización: " + tituloActividad);
            }
        }
        
        cantidad++;
    }
    
    archivo.close();
}

// Carga datos de inscripciones desde archivo binario
void Controladora::cargarDatosInscripciones() 
{
    ifstream archivo(RUTA_INSCRIPCIONES, ios::binary);
    if (!archivo.is_open()) {
        throw runtime_error("No se pudo abrir el archivo de inscripciones: " + RUTA_INSCRIPCIONES);
    }

    try {
        InscripcionBinaria inscripcion;
        while (archivo.read(reinterpret_cast<char*>(&inscripcion), sizeof(InscripcionBinaria))) {
            int idx = inscripcion.idActividad;
            int tipo = inscripcion.tipoActividad;
            
            if (tipo == TIPO_CURSO) {
                _gestionadorCursos->getCursos().get(idx)->aumentarAlumno(1);
            }
            else if (tipo == TIPO_ESPECIALIZACION) {
                _gestionadorCursos->getEspecializaciones().get(idx)->aumentarAlumno(1);
            }
        }
        
        if (!archivo.eof()) {
            throw runtime_error("Error al leer el archivo de inscripciones");
        }    }
    catch (const exception& e) {
        archivo.close();
        throw runtime_error("Error al procesar inscripciones: " + string(e.what()));
    }
    
    archivo.close();
}

// Crea una nueva instancia de la pantalla de login
unique_ptr<PantallaBase> Controladora::crearPantallaLogin() 
{
    return make_unique<LoginScreen>(*_estudiante, *_empresa, _gestionadorCursos->getCursos(), _gestionadorCursos->getEspecializaciones());
}

// Crea dashboard para estudiante
unique_ptr<PantallaBase> Controladora::crearPantallaDashboardEstudiante() 
{
    if (_estudiante) {
        return make_unique<DashboardEstudianteScreen>(this, _estudiante->getId(), _estudiante->getNombreCompleto());
    }
    return crearPantallaLogin();
}

// Crea dashboard para organización
unique_ptr<PantallaBase> Controladora::crearPantallaDashboardOrganizacion() 
{
    if (_empresa) {
        return make_unique<DashboardOrganizacionScreen>(this, _empresa->getId(), _empresa->getNombreCompleto());
    }
    return crearPantallaLogin();
}

// Crea pantalla de landing page
unique_ptr<PantallaBase> Controladora::crearPantallaLandingPage() 
{
    _estudiante->reset();
    _empresa->reset();
    return make_unique<LandingPageScreen>(_gestionadorCursos->getCursos(), _gestionadorCursos->getEspecializaciones());
}

// Método principal de ejecución del sistema
void Controladora::run() 
{
    unique_ptr<PantallaBase> pantallaActual = crearPantallaLandingPage();
    
    while (_ejecutando) {
        ResultadoPantalla resultado = pantallaActual->ejecutar();

        switch (resultado.accion) {
            case AccionPantalla::IR_A_LOGIN:
                pantallaActual = crearPantallaLogin();
                break;
                
            case AccionPantalla::IR_A_REGISTRO:
                pantallaActual = make_unique<RegistroScreen>();
                break;
                
            case AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE:
                pantallaActual = crearPantallaDashboardEstudiante();
                break;
                
            case AccionPantalla::IR_A_DASHBOARD_ORGANIZACION:
                pantallaActual = crearPantallaDashboardOrganizacion();
                break;
                
            case AccionPantalla::IR_A_LANDING_PAGE:
                pantallaActual = crearPantallaLandingPage();
                break;
                
            case AccionPantalla::SALIR:
                _ejecutando = false;
                system("cls");
                cout << "Gracias por usar CourseraClone. Hasta luego!" << endl;
                break;
                
            case AccionPantalla::IR_A_PERFIL_ESTUDIANTE:
                if (_estudiante) {
                    pantallaActual = make_unique<PerfilEstudianteScreen>(
                        _estudiante->getId(),
                        _estudiante->getNombreCompleto(),
                        _estudiante->getUsername()
                    );
                } else {
                    pantallaActual = crearPantallaLogin();
                }
                break;
                
            case AccionPantalla::IR_A_PERFIL_ORGANIZACION:
                if (_empresa) {
                    pantallaActual = make_unique<PerfilOrganizacionScreen>(
                        _empresa->getId(),
                        _empresa->getNombreCompleto(),
                        _empresa->getUsername()
                    );
                } else {
                    pantallaActual = crearPantallaLogin();
                }
                break;
                
            case AccionPantalla::IR_A_EDITAR_PERFIL:
                if (_estudiante) {
                    pantallaActual = make_unique<EditarPerfilScreen>(
                        this,
                        _estudiante->getId(),
                        TipoUsuario::ESTUDIANTE,
                        _estudiante->getNombreCompleto(),
                        _estudiante->getUsername()
                    );
                } else if (_empresa) {
                    pantallaActual = make_unique<EditarPerfilScreen>(
                        this,
                        _empresa->getId(),
                        TipoUsuario::EMPRESA,
                        _empresa->getNombreCompleto(),
                        _empresa->getUsername()
                    );
                } else {
                    pantallaActual = crearPantallaLogin();
                }
                break;
                
            case AccionPantalla::IR_A_MOSTRAR_CURSO:
            {
                int idCurso = resultado.idCursoSeleccionado;
                Curso* cursoSeleccionado = _gestionadorCursos->obtenerCurso(idCurso);

                pantallaActual = make_unique<MostrarCursoScreen>(
                    idCurso,
                    *_gestionadorCursos.get(),
                    *_estudiante,
                    cursoSeleccionado,
                    resultado.accionAnterior,
                    resultado.tipoUsuario
                );
                break;
            }
            
            case AccionPantalla::IR_A_MOSTRAR_ESPECIALIZACION:
            {
                Especializacion* especializacion = _gestionadorCursos->obtenerEspecializacion(resultado.idCursoSeleccionado);

                pantallaActual = make_unique<MostrarEspecialidadScreen>(
                    resultado.idCursoSeleccionado,
                    *_gestionadorCursos.get(),
                    especializacion,
                    resultado.accionAnterior,
                    resultado.tipoUsuario,
                    *_estudiante
                );
                break;
            }
            
            case AccionPantalla::IR_A_EXPLORAR_CURSOS_Y_ESPECIALIDADES:
            {
                TipoUsuario tipoUsuario = TipoUsuario::NINGUNO;
                int idUsuario = 0;
                string nombreUsuario = "";

                if (_estudiante != nullptr) {
                    tipoUsuario = TipoUsuario::ESTUDIANTE;
                    idUsuario = _estudiante->getId();
                    nombreUsuario = _estudiante->getNombreCompleto();
                } else if (_empresa != nullptr) {
                    tipoUsuario = TipoUsuario::EMPRESA;
                    idUsuario = _empresa->getId();
                    nombreUsuario = _empresa->getNombreCompleto();
                } else if (resultado.tipoUsuario != TipoUsuario::NINGUNO) {
                    tipoUsuario = resultado.tipoUsuario;
                }

                pantallaActual = make_unique<ExplorarCursosYEspecialidadesScreen>(
                    this,
                    tipoUsuario,
                    idUsuario,
                    nombreUsuario
                );
                break;
            }
            
            case AccionPantalla::IR_A_VER_BOLETAS:
                if (_estudiante) {
                    pantallaActual = make_unique<VerBoletasScreen>(*_estudiante);
                } else {
                    pantallaActual = crearPantallaLogin();
                }
                break;
                
            default:
                break;
        }
    }
}