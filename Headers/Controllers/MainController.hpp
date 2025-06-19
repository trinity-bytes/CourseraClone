// filepath: Headers/Controllers/MainController.hpp
/// @brief Controlador principal del sistema CourseraClone 

#ifndef COURSERACLONE_CONTROLLERS_MAINCONTROLLER_HPP
#define COURSERACLONE_CONTROLLERS_MAINCONTROLLER_HPP

// Headers del sistema
#include <memory>

// Headers propios del proyecto
#include "../Screens/LandingPageScreen.hpp"
#include "../Screens/SobreNosotrosScreen.hpp"
#include "../Screens/LoginScreen.hpp"
#include "../Screens/RegistroScreen.hpp"
#include "../Screens/DashboardEstudianteScreen.hpp"
#include "../Screens/DashboardOrganizacionScreen.hpp"
#include "../Screens/PerfilEstudianteScreen.hpp"
#include "../Screens/PerfilOrganizacionScreen.hpp"
#include "../Screens/ExplorarContenidoScreen.hpp"
#include "../Utils/ScreenSystem.hpp"

class MainController
{
private:
    /// @brief Estado de la aplicación
    bool _ejecutando;    
    
    /// @brief Métodos privados de navegación
    std::unique_ptr<PantallaBase> crearPantallaLandingPage();
    std::unique_ptr<PantallaBase> crearPantallaSobreNosotros();
    std::unique_ptr<PantallaBase> crearPantallaLogin();    
    std::unique_ptr<PantallaBase> crearPantallaRegistro();    
    std::unique_ptr<PantallaBase> crearPantallaDashboardEstudiante();    
    std::unique_ptr<PantallaBase> crearPantallaDashboardOrganizacion();
    std::unique_ptr<PantallaBase> crearPantallaPerfilEstudiante();
    std::unique_ptr<PantallaBase> crearPantallaPerfilOrganizacion();
    std::unique_ptr<PantallaBase> crearPantallaExplorarContenido();

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

/// @brief Crea una nueva instancia de la pantalla Sobre Nosotros
inline std::unique_ptr<PantallaBase> MainController::crearPantallaSobreNosotros()
{
    return std::make_unique<SobreNosotrosScreen>();
}

/// @brief Crea una nueva instancia de la pantalla de login
inline std::unique_ptr<PantallaBase> MainController::crearPantallaLogin()
{
    return std::make_unique<LoginScreen>();
}

/// @brief Crea una nueva instancia de la pantalla de registro
inline std::unique_ptr<PantallaBase> MainController::crearPantallaRegistro()
{
    return std::make_unique<RegistroScreen>();
}

/// @brief Crea una nueva instancia del dashboard de estudiante
inline std::unique_ptr<PantallaBase> MainController::crearPantallaDashboardEstudiante()
{
    return std::make_unique<DashboardEstudianteScreen>();
}

/// @brief Crea una nueva instancia del dashboard de organización
inline std::unique_ptr<PantallaBase> MainController::crearPantallaDashboardOrganizacion()
{
    return std::make_unique<DashboardOrganizacionScreen>();
}

/// @brief Crea una nueva instancia del perfil de estudiante
inline std::unique_ptr<PantallaBase> MainController::crearPantallaPerfilEstudiante()
{
    return std::make_unique<PerfilEstudianteScreen>();
}

/// @brief Crea una nueva instancia del perfil de organización
inline std::unique_ptr<PantallaBase> MainController::crearPantallaPerfilOrganizacion()
{
    return std::make_unique<PerfilOrganizacionScreen>();
}

/// @brief Crea una nueva instancia de la pantalla explorar contenido
inline std::unique_ptr<PantallaBase> MainController::crearPantallaExplorarContenido()
{
    return std::make_unique<ExplorarContenidoScreen>();
}

// ---- FUNCIONES PÚBLICAS ----
/// Método principal de ejecución del sistema
inline void MainController::run()
{
    std::unique_ptr<PantallaBase> _pantallaActual = crearPantallaPerfilOrganizacion();
    
    do
    {
        ResultadoPantalla _resultado = _pantallaActual->ejecutar();

        switch (_resultado.accion)
        {
        case AccionPantalla::IR_A_LANDING_PAGE:
            _pantallaActual = crearPantallaLandingPage();
            break;

        case AccionPantalla::IR_A_LOGIN:
            _pantallaActual = crearPantallaLogin();
			break;        
        
        case AccionPantalla::IR_A_REGISTRO:
            _pantallaActual = crearPantallaRegistro();
			break;        
        
        case AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE:
            _pantallaActual = crearPantallaDashboardEstudiante();
            break;        
        
        case AccionPantalla::IR_A_DASHBOARD_ORGANIZACION:
            _pantallaActual = crearPantallaDashboardOrganizacion();
            break;        
        
        case AccionPantalla::IR_A_PERFIL_ESTUDIANTE:
            _pantallaActual = crearPantallaPerfilEstudiante();
            break;

        case AccionPantalla::IR_A_PERFIL_ORGANIZACION:
            _pantallaActual = crearPantallaPerfilOrganizacion();
            break;

		case AccionPantalla::IR_A_SOBRE_NOSOTROS:
            _pantallaActual = crearPantallaSobreNosotros();
			break;

        case AccionPantalla::IR_A_EXPLORAR_CURSOS_Y_ESPECIALIDADES:
            _pantallaActual = crearPantallaExplorarContenido();
            break;

        case AccionPantalla::SALIR:
            _ejecutando = false;
            system("cls");
            break;
        default:
            /// @brief Para acciones no implementadas aún, se regresa a landing page
            _pantallaActual = crearPantallaLandingPage();
            break;
        }
    } while (_ejecutando);
}

#endif // COURSERACLONE_CONTROLLERS_MAINCONTROLLER_HPP