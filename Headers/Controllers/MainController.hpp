#ifndef COURSERACLONE_CONTROLLERS_MAINCONTROLLER_HPP
#define COURSERACLONE_CONTROLLERS_MAINCONTROLLER_HPP

// Headers del sistema
#include <memory>
#include <stack>

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
#include "../Controllers/SessionManager.hpp"
#include "../Utils/ScreenSystem.hpp"

class MainController
{
private:
    /// @brief Estado de la aplicación
    bool _ejecutando;
    
    /// @brief Sistema de navegación con historial
    std::stack<AccionPantalla> _historialNavegacion;
    AccionPantalla _pantallaActual;
    
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
    
    /// @brief Métodos del sistema de navegación
    inline void _procesarNavegacion(const ResultadoPantalla& resultado);
    inline void _pushHistorial(AccionPantalla accion);
    inline AccionPantalla _popHistorial();
    inline bool _esPantallaConHistorial(AccionPantalla accion);
    inline bool _esPantallaQueResetea(AccionPantalla accion);
    inline AccionPantalla _resolverPantallaAnterior();
    inline std::unique_ptr<PantallaBase> _crearPantallaConHistorial(AccionPantalla accion);

public:
    /// @brief Constructor y destructor
    inline MainController();
    inline ~MainController() = default;

    /// @brief Método principal de ejecución
    inline void run();
};

// ---- CONSTRUCTOR Y DESTRUCTOR ----
inline MainController::MainController() : _ejecutando(true), _pantallaActual(AccionPantalla::IR_A_LANDING_PAGE) {}

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

// ---- SISTEMA DE NAVEGACIÓN INTELIGENTE ----

/// @brief Procesa la navegación con historial inteligente
inline void MainController::_procesarNavegacion(const ResultadoPantalla& resultado)
{
    // Si la pantalla especifica una acción anterior, la guardamos en el historial
    if (resultado.accionAnterior != AccionPantalla::NINGUNA) {
        _pushHistorial(resultado.accionAnterior);
    } else if (_esPantallaConHistorial(resultado.accion)) {
        // Para pantallas que necesitan historial, guardamos la actual
        _pushHistorial(_pantallaActual);
    }
    
    // Actualizar la pantalla actual
    _pantallaActual = resultado.accion;
}

/// @brief Agrega una pantalla al historial si es apropiado
inline void MainController::_pushHistorial(AccionPantalla accion)
{
    // No agregar pantallas que resetean el historial o son temporales
    if (!_esPantallaQueResetea(accion) && accion != AccionPantalla::NINGUNA) {
        _historialNavegacion.push(accion);
    }
}

/// @brief Obtiene la pantalla anterior del historial
inline AccionPantalla MainController::_popHistorial()
{
    if (!_historialNavegacion.empty()) {
        AccionPantalla anterior = _historialNavegacion.top();
        _historialNavegacion.pop();
        return anterior;
    }
    
    // Si no hay historial, determinar pantalla por defecto según contexto
    return _resolverPantallaAnterior();
}

/// @brief Determina si una pantalla necesita manejo de historial
inline bool MainController::_esPantallaConHistorial(AccionPantalla accion)
{
    switch (accion) {
    case AccionPantalla::IR_A_MOSTRAR_CURSO:
    case AccionPantalla::IR_A_MOSTRAR_ESPECIALIZACION:
    case AccionPantalla::IR_A_VER_BOLETAS:
    case AccionPantalla::IR_A_EDITAR_PERFIL:
    case AccionPantalla::IR_A_VER_CERTIFICADOS:
    case AccionPantalla::IR_A_PROCESAR_PAGO:
    case AccionPantalla::IR_A_AGREGAR_METODO_PAGO:
        return true;
    default:
        return false;
    }
}

/// @brief Determina si una pantalla resetea el historial de navegación
inline bool MainController::_esPantallaQueResetea(AccionPantalla accion)
{
    switch (accion) {
    case AccionPantalla::IR_A_LOGIN:
    case AccionPantalla::IR_A_REGISTRO:
    case AccionPantalla::IR_A_LANDING_PAGE:
    case AccionPantalla::SALIR:
        return true;
    default:
        return false;
    }
}

/// @brief Resuelve una pantalla anterior por defecto cuando no hay historial
inline AccionPantalla MainController::_resolverPantallaAnterior()
{
    // Determinar pantalla por defecto basada en si hay sesión activa
    if (SessionManager::getInstance().isLoggedIn()) {
        TipoUsuario tipo = SessionManager::getInstance().getCurrentUser().getTipoUsuario();
        if (tipo == TipoUsuario::ESTUDIANTE) {
            return AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE;
        } else if (tipo == TipoUsuario::EMPRESA) {
            return AccionPantalla::IR_A_DASHBOARD_ORGANIZACION;
        }
    }
    
    return AccionPantalla::IR_A_LANDING_PAGE;
}

/// @brief Crea una pantalla pasando el historial como contexto
inline std::unique_ptr<PantallaBase> MainController::_crearPantallaConHistorial(AccionPantalla accion)
{
    AccionPantalla pantallaAnterior = _popHistorial();
    
    switch (accion) {
    case AccionPantalla::IR_A_MOSTRAR_ESPECIALIZACION:
    {
        // Obtener ID y tipo de usuario desde ContentManager y SessionManager
        int idEspecializacion = 1; // Valor por defecto
        TipoUsuario tipoUsuario = TipoUsuario::DEFAULT;
        
        if (SessionManager::getInstance().isLoggedIn()) {
            tipoUsuario = SessionManager::getInstance().getCurrentUser().getTipoUsuario();
        }
        
        return std::make_unique<MostrarEspecialidadScreen>(idEspecializacion, tipoUsuario, pantallaAnterior);
    }
    
    case AccionPantalla::IR_A_MOSTRAR_CURSO:
    {
        // Similar para MostrarCursoScreen cuando tengamos el constructor actualizado
        int idCurso = 1; // Valor por defecto
        TipoUsuario tipoUsuario = TipoUsuario::DEFAULT;
        
        if (SessionManager::getInstance().isLoggedIn()) {
            tipoUsuario = SessionManager::getInstance().getCurrentUser().getTipoUsuario();
        }
        
        return std::make_unique<MostrarCursoScreen>(idCurso, tipoUsuario, pantallaAnterior);
    }
    
    case AccionPantalla::IR_A_LISTAR_CONTENIDO:
        return std::make_unique<ListarContenidoScreen>(pantallaAnterior);
        
    case AccionPantalla::IR_A_CREAR_CONTENIDO:
        return std::make_unique<CrearContenidoScreen>(pantallaAnterior);
        
    case AccionPantalla::IR_A_GESTIONAR_OFERTAS:
        return std::make_unique<GestionarOfertasScreen>(pantallaAnterior);
        
    default:
        // Para pantallas que no necesitan historial, usar factory method normal
        switch (accion) {
        case AccionPantalla::IR_A_MOSTRAR_ESPECIALIZACION:
            return crearPantallaMostrarEspecializacion();
        case AccionPantalla::IR_A_MOSTRAR_CURSO:
            return crearPantallaMostrarCurso();
        default:
            return crearPantallaLandingPage();
        }
    }
}

// ---- FUNCIONES PÚBLICAS ----
/// Método principal de ejecución del sistema
inline void MainController::run()
{
    std::unique_ptr<PantallaBase> _pantallaActualPtr = crearPantallaLandingPage();
    
    do
    {
        ResultadoPantalla _resultado = _pantallaActualPtr->ejecutar();

        // Procesar navegación con historial
        _procesarNavegacion(_resultado);

        switch (_resultado.accion)
        {
        case AccionPantalla::IR_A_LANDING_PAGE:
            // Limpiar historial en landing page
            while (!_historialNavegacion.empty()) {
                _historialNavegacion.pop();
            }
            _pantallaActualPtr = crearPantallaLandingPage();
            break;

        case AccionPantalla::IR_A_LOGIN:
            // Limpiar historial en login
            while (!_historialNavegacion.empty()) {
                _historialNavegacion.pop();
            }
            _pantallaActualPtr = crearPantallaLogin();
			break;        
        
        case AccionPantalla::IR_A_REGISTRO:
            _pantallaActualPtr = crearPantallaRegistro();
			break;        
        
        case AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE:
            _pantallaActualPtr = crearPantallaDashboardEstudiante();
            break;        
        
        case AccionPantalla::IR_A_DASHBOARD_ORGANIZACION:
            _pantallaActualPtr = crearPantallaDashboardOrganizacion();
            break;        
        
        case AccionPantalla::IR_A_PERFIL_ESTUDIANTE:
            _pantallaActualPtr = crearPantallaPerfilEstudiante();
            break;        
        
        case AccionPantalla::IR_A_PERFIL_ORGANIZACION:
            _pantallaActualPtr = crearPantallaPerfilOrganizacion();
            break;        
        
        case AccionPantalla::IR_A_EDITAR_PERFIL:
            _pantallaActualPtr = crearPantallaEditarPerfil();
            break;        
        
        case AccionPantalla::IR_A_MOSTRAR_ESPECIALIZACION:
            // Usar sistema de historial para estas pantallas críticas
            _pantallaActualPtr = _crearPantallaConHistorial(_resultado.accion);
            break;

        case AccionPantalla::IR_A_MOSTRAR_CURSO:
            // Usar sistema de historial para estas pantallas críticas
            _pantallaActualPtr = _crearPantallaConHistorial(_resultado.accion);
            break;

        case AccionPantalla::IR_A_VER_ESTADISTICAS:
            _pantallaActualPtr = crearPantallaEstadisticasEmpresa();
            break;

		case AccionPantalla::IR_A_SOBRE_NOSOTROS:
            _pantallaActualPtr = crearPantallaSobreNosotros();
			break;

        case AccionPantalla::IR_A_EXPLORAR_CURSOS_Y_ESPECIALIDADES:
            _pantallaActualPtr = crearPantallaExplorarContenido();
            break;

        case AccionPantalla::IR_A_VER_BOLETAS:
            _pantallaActualPtr = crearPantallaVerBoletas();
            break;

        case AccionPantalla::IR_A_CREAR_CONTENIDO:
            _pantallaActualPtr = _crearPantallaConHistorial(_resultado.accion);
            break;

        case AccionPantalla::IR_A_CREAR_OFERTA:
            _pantallaActualPtr = crearPantallaCrearOferta();
            break;

        case AccionPantalla::IR_A_VER_OFERTAS:
            _pantallaActualPtr = crearPantallaVerOfertas();
            break;

        case AccionPantalla::IR_A_AGREGAR_METODO_PAGO:
            _pantallaActualPtr = crearPantallaAgregarMetodoPago();
            break;

        case AccionPantalla::IR_A_PROCESAR_PAGO:
            _pantallaActualPtr = crearPantallaProcesarPago();
            break;

        case AccionPantalla::IR_A_VER_CERTIFICADOS:
            _pantallaActualPtr = crearPantallaVerCertificados();
            break;

        case AccionPantalla::IR_A_LISTAR_CONTENIDO:
            _pantallaActualPtr = _crearPantallaConHistorial(_resultado.accion);
            break;

        case AccionPantalla::IR_A_GESTIONAR_OFERTAS:
            _pantallaActualPtr = _crearPantallaConHistorial(_resultado.accion);
            break;

        case AccionPantalla::SALIR:
            _ejecutando = false;
            system("cls");
            break;
        default:
            /// @brief Para acciones no implementadas aún, se regresa a landing page
            _pantallaActualPtr = crearPantallaLandingPage();
            break;
        }
    } while (_ejecutando);
}

#endif // COURSERACLONE_CONTROLLERS_MAINCONTROLLER_HPP