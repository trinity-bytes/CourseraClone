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
#include "../Screens/EditarPerfilScreen.hpp"
#include "../Screens/MostrarEspecialidadScreen.hpp"
#include "../Screens/MostrarCursoScreen.hpp"
#include "../Screens/EstadisticasEmpresaScreen.hpp"
#include "../Screens/ExplorarContenidoScreen.hpp"
#include "../Screens/VerBoletasScreen.hpp"
#include "../Screens/CrearContenidoScreen.hpp"
#include "../Screens/CrearOfertaScreen.hpp"
#include "../Screens/VerOfertasScreen.hpp"
#include "../Screens/AgregarMetodoPagoScreen.hpp"
#include "../Screens/ProcesarPagoScreen.hpp"
#include "../Screens/VerCertificadosScreen.hpp"
#include "../Screens/ListarContenidoScreen.hpp"
#include "../Screens/GestionarOfertasScreen.hpp"
#include "../Utils/ScreenSystem.hpp"

class MainController
{
private:
    /// @brief Estado de la aplicación
    bool _ejecutando;    
    
    /// @brief Métodos privados de navegación
    inline std::unique_ptr<PantallaBase> crearPantallaLandingPage();
    inline std::unique_ptr<PantallaBase> crearPantallaSobreNosotros();
    inline std::unique_ptr<PantallaBase> crearPantallaLogin();    
    inline std::unique_ptr<PantallaBase> crearPantallaRegistro();    
    inline std::unique_ptr<PantallaBase> crearPantallaDashboardEstudiante();    
    inline std::unique_ptr<PantallaBase> crearPantallaDashboardOrganizacion();    
    inline std::unique_ptr<PantallaBase> crearPantallaPerfilEstudiante();    
    inline std::unique_ptr<PantallaBase> crearPantallaPerfilOrganizacion();    
    inline std::unique_ptr<PantallaBase> crearPantallaEditarPerfil();
    inline std::unique_ptr<PantallaBase> crearPantallaMostrarEspecializacion();
    inline std::unique_ptr<PantallaBase> crearPantallaMostrarCurso();
    inline std::unique_ptr<PantallaBase> crearPantallaEstadisticasEmpresa();
    inline std::unique_ptr<PantallaBase> crearPantallaExplorarContenido();
    inline std::unique_ptr<PantallaBase> crearPantallaVerBoletas();
    inline std::unique_ptr<PantallaBase> crearPantallaCrearContenido();
    inline std::unique_ptr<PantallaBase> crearPantallaCrearOferta();
    inline std::unique_ptr<PantallaBase> crearPantallaVerOfertas();
    inline std::unique_ptr<PantallaBase> crearPantallaAgregarMetodoPago();
    inline std::unique_ptr<PantallaBase> crearPantallaProcesarPago();
    inline std::unique_ptr<PantallaBase> crearPantallaVerCertificados();
    inline std::unique_ptr<PantallaBase> crearPantallaListarContenido();
    inline std::unique_ptr<PantallaBase> crearPantallaGestionarOfertas();

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

/// @brief Crea una nueva instancia de la pantalla editar perfil
inline std::unique_ptr<PantallaBase> MainController::crearPantallaEditarPerfil()
{
    return std::make_unique<EditarPerfilScreen>();
}

/// @brief Crea una nueva instancia de la pantalla mostrar especialización
inline std::unique_ptr<PantallaBase> MainController::crearPantallaMostrarEspecializacion()
{
    return std::make_unique<MostrarEspecialidadScreen>();
}

/// @brief Crea una nueva instancia de la pantalla mostrar curso
inline std::unique_ptr<PantallaBase> MainController::crearPantallaMostrarCurso()
{
    return std::make_unique<MostrarCursoScreen>();
}

/// @brief Crea una nueva instancia de la pantalla estadísticas de empresa
inline std::unique_ptr<PantallaBase> MainController::crearPantallaEstadisticasEmpresa()
{
    return std::make_unique<EstadisticasEmpresaScreen>();
}

/// @brief Crea una nueva instancia de la pantalla explorar contenido
inline std::unique_ptr<PantallaBase> MainController::crearPantallaExplorarContenido()
{
    return std::make_unique<ExplorarContenidoScreen>();
}

/// @brief Crea una nueva instancia de la pantalla ver boletas
inline std::unique_ptr<PantallaBase> MainController::crearPantallaVerBoletas()
{
    return std::make_unique<VerBoletasScreen>();
}

/// @brief Crea una nueva instancia de la pantalla crear contenido
inline std::unique_ptr<PantallaBase> MainController::crearPantallaCrearContenido()
{
    return std::make_unique<CrearContenidoScreen>();
}

/// @brief Crea una nueva instancia de la pantalla crear oferta
inline std::unique_ptr<PantallaBase> MainController::crearPantallaCrearOferta()
{
    return std::make_unique<CrearOfertaScreen>();
}

/// @brief Crea una nueva instancia de la pantalla ver ofertas
inline std::unique_ptr<PantallaBase> MainController::crearPantallaVerOfertas()
{
    return std::make_unique<VerOfertasScreen>();
}

/// @brief Crea una nueva instancia de la pantalla agregar método de pago
inline std::unique_ptr<PantallaBase> MainController::crearPantallaAgregarMetodoPago()
{
    return std::make_unique<AgregarMetodoPagoScreen>();
}

/// @brief Crea una nueva instancia de la pantalla procesar pago
inline std::unique_ptr<PantallaBase> MainController::crearPantallaProcesarPago()
{
    return std::make_unique<ProcesarPagoScreen>();
}

/// @brief Crea una nueva instancia de la pantalla ver certificados
inline std::unique_ptr<PantallaBase> MainController::crearPantallaVerCertificados()
{
    return std::make_unique<VerCertificadosScreen>();
}

/// @brief Crea una nueva instancia de la pantalla listar contenido
inline std::unique_ptr<PantallaBase> MainController::crearPantallaListarContenido()
{
    return std::make_unique<ListarContenidoScreen>();
}

/// @brief Crea una nueva instancia de la pantalla gestionar ofertas
inline std::unique_ptr<PantallaBase> MainController::crearPantallaGestionarOfertas()
{
    return std::make_unique<GestionarOfertasScreen>();
}

// ---- FUNCIONES PÚBLICAS ----
/// Método principal de ejecución del sistema
inline void MainController::run()
{
    std::unique_ptr<PantallaBase> _pantallaActual = crearPantallaListarContenido();
    
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
        
        case AccionPantalla::IR_A_EDITAR_PERFIL:
            _pantallaActual = crearPantallaEditarPerfil();
            break;        
        
        case AccionPantalla::IR_A_MOSTRAR_ESPECIALIZACION:
            _pantallaActual = crearPantallaMostrarEspecializacion();
            break;

        case AccionPantalla::IR_A_MOSTRAR_CURSO:
            _pantallaActual = crearPantallaMostrarCurso();
            break;

        case AccionPantalla::IR_A_VER_ESTADISTICAS:
            _pantallaActual = crearPantallaEstadisticasEmpresa();
            break;

		case AccionPantalla::IR_A_SOBRE_NOSOTROS:
            _pantallaActual = crearPantallaSobreNosotros();
			break;

        case AccionPantalla::IR_A_EXPLORAR_CURSOS_Y_ESPECIALIDADES:
            _pantallaActual = crearPantallaExplorarContenido();
            break;

        case AccionPantalla::IR_A_VER_BOLETAS:
            _pantallaActual = crearPantallaVerBoletas();
            break;

        case AccionPantalla::IR_A_CREAR_CONTENIDO:
            _pantallaActual = crearPantallaCrearContenido();
            break;

        case AccionPantalla::IR_A_CREAR_OFERTA:
            _pantallaActual = crearPantallaCrearOferta();
            break;

        case AccionPantalla::IR_A_VER_OFERTAS:
            _pantallaActual = crearPantallaVerOfertas();
            break;

        case AccionPantalla::IR_A_AGREGAR_METODO_PAGO:
            _pantallaActual = crearPantallaAgregarMetodoPago();
            break;

        case AccionPantalla::IR_A_PROCESAR_PAGO:
            _pantallaActual = crearPantallaProcesarPago();
            break;

        case AccionPantalla::IR_A_VER_CERTIFICADOS:
            _pantallaActual = crearPantallaVerCertificados();
            break;

        case AccionPantalla::IR_A_LISTAR_CONTENIDO:
            _pantallaActual = crearPantallaListarContenido();
            break;

        case AccionPantalla::IR_A_GESTIONAR_OFERTAS:
            _pantallaActual = crearPantallaGestionarOfertas();
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