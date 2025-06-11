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
    MainController();
    ~MainController() = default;

    // Método principal de ejecución
    void run();
};

/// Constructor por defecto
MainController::MainController() : _ejecutando(true)
{
    // Inicialización básica
    std::cout << "Inicializando CourseraClone..." << std::endl;
}

/// Crea una nueva instancia de la pantalla landing page
std::unique_ptr<PantallaBase> MainController::crearPantallaLandingPage()
{
    return std::make_unique<LandingPageScreen>();
}

/// Método principal de ejecución del sistema
void MainController::run()
{
    std::unique_ptr<PantallaBase> _pantallaActual = crearPantallaLandingPage();
    
    while (_ejecutando) 
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
                std::cout << "Gracias por usar CourseraClone. Hasta luego!" << std::endl;
                break;
                
            default:
                // Para acciones no implementadas aún, volver a landing page
                _pantallaActual = crearPantallaLandingPage();
                break;
        }
    }
}

#endif // COURSERACLONE_CONTROLLERS_MAINCONTROLLER_HPP