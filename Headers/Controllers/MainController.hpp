// filepath: Headers/Controllers/MainController.hpp
// Descripcion: Controlador principal del sistema CourseraClone 

#ifndef COURSERACLONE_CONTROLLERS_MAINCONTROLLER_HPP
#define COURSERACLONE_CONTROLLERS_MAINCONTROLLER_HPP

// Headers del sistema
#include <iostream>
#include <memory>
#include <string>

// Headers propios
#include "../Screens/LandingPageScreen.hpp"
#include "../Utils/ScreenSystem.hpp"

/// Controlador principal del sistema CourseraClone
class MainController
{
private:
    // Estado de la aplicación
    bool _ejecutando;
    
    // Métodos privados de navegación
    std::unique_ptr<PantallaBase> crearPantallaLandingPage();

public:
    // Constructor y destructor
    inline MainController();
    inline ~MainController() = default;

    // Método principal de ejecución
    inline void run();
};

/// Constructor por defecto
inline MainController::MainController() : _ejecutando(true) {}

// FUNCIONES PRIVADAS DE NAVEGACIÓN
/// Crea una nueva instancia de la pantalla landing page
inline std::unique_ptr<PantallaBase> MainController::crearPantallaLandingPage()
{
    return std::make_unique<LandingPageScreen>();
}

// ---- FUNCIONES PÚBLICAS ----
/// Método principal de ejecución del sistema
inline void MainController::run()
{
    std::unique_ptr<PantallaBase> _pantallaActual = crearPantallaLandingPage();
    
    do
    {
        ResultadoPantalla _resultado = _pantallaActual->ejecutar();

        switch (_resultado.accion)
        {
        case AccionPantalla::IR_A_LANDING_PAGE:
            _pantallaActual = crearPantallaLandingPage();
            break;

        case AccionPantalla::SALIR:
            _ejecutando = false;
            system("cls");
            break;
        default:
            // Para acciones no implementadas aún, volver a landing page
            _pantallaActual = crearPantallaLandingPage();
            break;
        }
    } while (_ejecutando);
}

#endif // COURSERACLONE_CONTROLLERS_MAINCONTROLLER_HPP