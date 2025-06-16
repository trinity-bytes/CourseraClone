// filepath: Headers/Controllers/MainController.hpp
/// @brief Controlador principal del sistema CourseraClone 

#ifndef COURSERACLONE_CONTROLLERS_MAINCONTROLLER_HPP
#define COURSERACLONE_CONTROLLERS_MAINCONTROLLER_HPP

// Headers del sistema
#include <memory>

// Headers propios del proyecto
#include "../Screens/LandingPageScreen.hpp"
#include "../Screens/LoginScreen.hpp"
#include "../Utils/ScreenSystem.hpp"

class MainController
{
private:
    /// @brief Estado de la aplicación
    bool _ejecutando;
    
    /// @brief Métodos privados de navegación
    std::unique_ptr<PantallaBase> crearPantallaLandingPage();
    std::unique_ptr<PantallaBase> crearPantallaLogin();

public:
    /// @brief Constructor y destructor
    inline MainController();
    inline ~MainController() = default;

    /// @brief Método principal de ejecución
    inline void run();
};

// ---- CONSTRUCTOR Y DESTRUCTOR ----
inline MainController::MainController() : _ejecutando(true) {}

// ---- FUNCIONES PRIVADAS DE NAVEGACIÓN ----
/// @brief Crea una nueva instancia de la pantalla landing page
inline std::unique_ptr<PantallaBase> MainController::crearPantallaLandingPage()
{
    return std::make_unique<LandingPageScreen>();
}

inline std::unique_ptr<PantallaBase> MainController::crearPantallaLogin()
{
    return std::make_unique<LoginScreen>();
}

// ---- FUNCIONES PÚBLICAS ----
/// Método principal de ejecución del sistema
inline void MainController::run()
{
    std::unique_ptr<PantallaBase> _pantallaActual = crearPantallaLogin();
    
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