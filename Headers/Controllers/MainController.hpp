// filepath: Headers/Controllers/Controladora.hpp
// description: Heder de la clase Controladora que maneja la lógica del sistema CourseraClone

#ifndef COURSERACLONE_CONTROLLER_CONTROLADORA_HPP
#define COURSERACLONE_CONTROLLER_CONTROLADORA_HPP

// Headers estandar
#include <iostream>  // Para uso de std::cout y std::endl
#include <memory>    // Para uso de unique_ptr
#include <vector>    // Para uso de vector
#include <string>    // Para uso de std::string
#include <fstream>   // Para manejo de archivos
#include <conio.h>   // Para uso de _getch()
#include <stdexcept> // Para manejo de excepciones

// Headers propios
#include "CourseManager.hpp"
//#include "../Entities/Actividad.h"
//#include "../Entities/Estudiante.h"
//#include "../Entities/Empresa.h"
#include "../Screens/LandingPageScreen.hpp"
//#include "../Screens/LoginScreen.h"
//#include "../Screens/DashboardEstudianteScreen.h"
//#include "../Screens/DashboardOrganizacionScreen.h"
//#include "../Screens/PerfilEstudianteScreen.h"
//#include "../Screens/PerfilOrganizacionScreen.h"
//#include "../Screens/EditarPerfilScreen.h"
//#include "../Screens/MostrarCursoScreen.h"
//#include "../Screens/MostrarEspecialidadScreen.h"
//#include "../Screens/RegistroScreen.h"
//#include "../Screens/ExplorarContenidoScreen.h"
//#include "../Screens/VerBoletasScreen.h"
#include "../Utils/ScreenSystem.hpp"

// Forward declarations
//class Usuario;
//class Curso;
//class Especializacion;

// Controlador principal del sistema CourseraClone
class MainController
{
private:
    // Atributos privados
    unique_ptr<CourseManager> _courseManager;
    //std::vector<Actividad> _actividades;
    //Estudiante* _estudiante; 
    //Empresa* _empresa;
    bool _ejecutando;
    
    // Métodos privados de navegación
    //unique_ptr<PantallaBase> crearPantallaLogin();
    //unique_ptr<PantallaBase> crearPantallaDashboardEstudiante();
    //unique_ptr<PantallaBase> crearPantallaDashboardOrganizacion();
    unique_ptr<PantallaBase> crearPantallaLandingPage();

public:
    // Constructor y destructor
    MainController();
    ~MainController() = default;

    // Método principal de ejecución
    void run();

    // Getters públicos
    //vector<Actividad>& listarActividades() { return _actividades; }
    //GestionadorCursos* getGestionadorCursos() const { return _gestionadorCursos.get(); }
};

// Constructor
MainController::MainController() : _ejecutando(true)
{
    // Inicializar gestores
    _courseManager = make_unique<CourseManager>();
    //_estudiante = new Estudiante(0, "", "", "");
    //_empresa = new Empresa(0, "", "", "");
}

//// Crea una nueva instancia de la pantalla de login
//unique_ptr<PantallaBase> Controladora::crearPantallaLogin() 
//{
//    return make_unique<LoginScreen>(*_estudiante, *_empresa, _gestionadorCursos->getCursos(), _gestionadorCursos->getEspecializaciones());
//}

// Crea dashboard para estudiante
//unique_ptr<PantallaBase> Controladora::crearPantallaDashboardEstudiante() 
//{
//    if (_estudiante) {
//        return make_unique<DashboardEstudianteScreen>(this, _estudiante->getId(), _estudiante->getNombreCompleto());
//    }
//    return crearPantallaLogin();
//}

// Crea dashboard para organización
//unique_ptr<PantallaBase> Controladora::crearPantallaDashboardOrganizacion() 
//{
//    if (_empresa) {
//        return make_unique<DashboardOrganizacionScreen>(this, _empresa->getId(), _empresa->getNombreCompleto());
//    }
//    return crearPantallaLogin();
//}

// Crea pantalla de landing page
unique_ptr<PantallaBase> MainController::crearPantallaLandingPage()
{
    //_estudiante->reset();
    //_empresa->reset();
    return make_unique<LandingPageScreen>(_courseManager->getCursos(), _courseManager->getEspecializaciones());
}

// Método principal de ejecución del sistema
void MainController::run()
{
    unique_ptr<PantallaBase> pantallaActual = crearPantallaLandingPage();
    
    while (_ejecutando) {
        ResultadoPantalla resultado = pantallaActual->ejecutar();

        switch (resultado.accion) {
            /*case AccionPantalla::IR_A_LOGIN:
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
                break;*/
                
            case AccionPantalla::IR_A_LANDING_PAGE:
                pantallaActual = crearPantallaLandingPage();
                break;
                
            case AccionPantalla::SALIR:
                _ejecutando = false;
                system("cls");
                cout << "Gracias por usar CourseraClone. Hasta luego!" << endl;
                break;
                
            /*case AccionPantalla::IR_A_PERFIL_ESTUDIANTE:
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

                pantallaActual = make_unique<ExplorarContenidoScreen>(
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
                break;*/   

            default:
                break;
        }
    }
}

#endif // COURSERACLONE_CONTROLLER_CONTROLADORA_HPP