#ifndef COURSERACLONE_CONTROLLERS_MAINCONTROLLER_HPP
#define COURSERACLONE_CONTROLLERS_MAINCONTROLLER_HPP

// Headers del sistema
#include <memory>
#include "../Utils/GeneradorDatos.hpp"

// Headers de estructuras de datos propias
#include "../DataStructures/Stack.hpp"

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
#include "../Screens/VerCertificadosScreen.hpp"
#include "../Screens/ListarContenidoScreen.hpp"
#include "../Screens/ListarMisInscripciones.hpp"
#include "../Controllers/SessionManager.hpp"
#include "../Utils/ScreenSystem.hpp"

class MainController
{
private:
    /// @brief Estado de la aplicación
    bool _ejecutando;
    
    /// @brief Sistema de navegación con historial usando estructura propia
    Stack<AccionPantalla> _historialNavegacion;
    AccionPantalla _pantallaActual;
    
    /// @brief Configuración del historial
    static const int MAX_HISTORIAL = 20; // Evitar crecimiento infinito
    
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
    inline std::unique_ptr<PantallaBase> crearPantallaVerCertificados();
    inline std::unique_ptr<PantallaBase> crearPantallaListarContenido();
    inline std::unique_ptr<PantallaBase> crearPantallaListarMisInscripciones();
    
    /// @brief Métodos del sistema de navegación mejorados
    inline void _procesarNavegacion(const ResultadoPantalla& resultado);
    inline void _pushHistorial(AccionPantalla accion);
    inline AccionPantalla _popHistorial();
    inline bool _esPantallaConHistorial(AccionPantalla accion);
    inline bool _esPantallaQueResetea(AccionPantalla accion);
    inline bool _evitarBucleHistorial(AccionPantalla accion);
    inline AccionPantalla _resolverPantallaAnterior();
    inline std::unique_ptr<PantallaBase> _crearPantallaConHistorial(AccionPantalla accion);
    inline void _limpiarHistorialCompleto();
    inline void _limitarTamañoHistorial();

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

/// @brief Crea una nueva instancia de la pantalla ver certificados
inline std::unique_ptr<PantallaBase> MainController::crearPantallaVerCertificados()
{
    // Usar el sistema de historial para determinar la pantalla anterior
    AccionPantalla pantallaAnterior = _resolverPantallaAnterior();
    return std::make_unique<VerCertificadosScreen>(pantallaAnterior);
}

/// @brief Crea una nueva instancia de la pantalla listar contenido
inline std::unique_ptr<PantallaBase> MainController::crearPantallaListarContenido()
{
    return std::make_unique<ListarContenidoScreen>();
}

/// @brief Crea una nueva instancia de la pantalla listar mis inscripciones
inline std::unique_ptr<PantallaBase> MainController::crearPantallaListarMisInscripciones()
{
    return std::make_unique<ListarMisInscripcionesScreen>();
}

// ---- SISTEMA DE NAVEGACIÓN INTELIGENTE CON STACK PERSONALIZADO ----

/// @brief Procesa la navegación con historial inteligente y prevención de bucles
inline void MainController::_procesarNavegacion(const ResultadoPantalla& resultado)
{
    // Si la pantalla especifica una acción anterior, la guardamos en el historial
    if (resultado.accionAnterior != AccionPantalla::NINGUNA) {
        _pushHistorial(resultado.accionAnterior);
    } else if (_esPantallaConHistorial(resultado.accion)) {
        // Para pantallas que necesitan historial, guardamos la actual solo si no crea bucle
        if (!_evitarBucleHistorial(_pantallaActual)) {
            _pushHistorial(_pantallaActual);
        }
    }
    
    // Actualizar la pantalla actual
    _pantallaActual = resultado.accion;
}

/// @brief Agrega una pantalla al historial si es apropiado, usando Stack personalizado
inline void MainController::_pushHistorial(AccionPantalla accion)
{
    // No agregar pantallas que resetean el historial o son temporales
    if (!_esPantallaQueResetea(accion) && accion != AccionPantalla::NINGUNA) {
        _historialNavegacion.push(accion);
        _limitarTamañoHistorial();
    }
}

/// @brief Obtiene la pantalla anterior del historial usando Stack personalizado
inline AccionPantalla MainController::_popHistorial()
{
    if (!_historialNavegacion.estaVacio()) {
        AccionPantalla anterior = _historialNavegacion.top();
        _historialNavegacion.pop();
        return anterior;
    }
    
    // Si no hay historial, determinar pantalla por defecto según contexto
    return _resolverPantallaAnterior();
}

/// @brief Determina si una pantalla necesita manejo de historial - EXPANDIDO
inline bool MainController::_esPantallaConHistorial(AccionPantalla accion)
{
    switch (accion) {
    case AccionPantalla::IR_A_MOSTRAR_CURSO:
    case AccionPantalla::IR_A_MOSTRAR_ESPECIALIZACION:
    case AccionPantalla::IR_A_VER_BOLETAS:
    case AccionPantalla::IR_A_EDITAR_PERFIL:
    case AccionPantalla::IR_A_VER_CERTIFICADOS:
    case AccionPantalla::IR_A_LISTAR_CONTENIDO:
    case AccionPantalla::IR_A_CREAR_CONTENIDO:
    case AccionPantalla::IR_A_LISTAR_MIS_INSCRIPCIONES:
    case AccionPantalla::IR_A_EXPLORAR_CURSOS_Y_ESPECIALIDADES:
    case AccionPantalla::IR_A_VER_ESTADISTICAS:
    case AccionPantalla::IR_A_SOBRE_NOSOTROS:
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

/// @brief Evita bucles detectando si la acción ya está en el historial reciente
inline bool MainController::_evitarBucleHistorial(AccionPantalla accion)
{
    // Si el historial está vacío, no hay riesgo de bucle
    if (_historialNavegacion.estaVacio()) {
        return false;
    }
    
    // Verificar si la acción es igual a la última en el historial
    AccionPantalla ultimaAccion = _historialNavegacion.top();
    if (ultimaAccion == accion) {
        return true; // Evitar bucle inmediato
    }
    
    // Para pantallas de contenido específico, verificar bucles más profundos
    if (accion == AccionPantalla::IR_A_MOSTRAR_CURSO || 
        accion == AccionPantalla::IR_A_MOSTRAR_ESPECIALIZACION) {
        
        // Verificar las últimas 3 entradas del historial para detectar patrones
        int contadorVerificaciones = 0;
        const int maxVerificaciones = 3;
        
        for (int i = 0; i < _historialNavegacion.getTamano() && contadorVerificaciones < maxVerificaciones; ++i) {
            AccionPantalla accionHistorial = _historialNavegacion.get(i);
            if (accionHistorial == accion) {
                return true; // Detectado patrón de bucle
            }
            contadorVerificaciones++;
        }
    }
    
    return false;
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

/// @brief Limpia completamente el historial de navegación
inline void MainController::_limpiarHistorialCompleto()
{
    _historialNavegacion.clear();
}

/// @brief Limita el tamaño del historial para evitar crecimiento infinito
inline void MainController::_limitarTamañoHistorial()
{
    while (_historialNavegacion.getTamano() > MAX_HISTORIAL) {
        // Remover el elemento más antiguo (fondo de la pila)
        // Usamos el método eliminarPosicion para remover desde el fondo
        _historialNavegacion.eliminarPosicion(_historialNavegacion.getTamano());
    }
}

/// @brief Crea una pantalla pasando el historial como contexto con prevención de bucles
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
        // Obtener ID y tipo de usuario para MostrarCursoScreen
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
        
    case AccionPantalla::IR_A_LISTAR_MIS_INSCRIPCIONES:
        return std::make_unique<ListarMisInscripcionesScreen>(pantallaAnterior);
        
    case AccionPantalla::IR_A_VER_CERTIFICADOS:
        return std::make_unique<VerCertificadosScreen>(pantallaAnterior);
        
    case AccionPantalla::IR_A_EXPLORAR_CURSOS_Y_ESPECIALIDADES:
        return std::make_unique<ExplorarContenidoScreen>(pantallaAnterior);
        
    case AccionPantalla::IR_A_VER_ESTADISTICAS:
        return std::make_unique<EstadisticasEmpresaScreen>(pantallaAnterior);
        
    case AccionPantalla::IR_A_SOBRE_NOSOTROS:
        return std::make_unique<SobreNosotrosScreen>(pantallaAnterior);
        
    case AccionPantalla::IR_A_VER_BOLETAS:
        return std::make_unique<VerBoletasScreen>(pantallaAnterior);
        
    case AccionPantalla::IR_A_EDITAR_PERFIL:
        return std::make_unique<EditarPerfilScreen>(pantallaAnterior);
        
    default:
        // Para pantallas que no necesitan historial específico, usar resolución inteligente
        AccionPantalla pantallaFallback = _resolverPantallaAnterior();
        switch (accion) {
        case AccionPantalla::IR_A_MOSTRAR_ESPECIALIZACION:
            return std::make_unique<MostrarEspecialidadScreen>(1, TipoUsuario::DEFAULT, pantallaFallback);
        case AccionPantalla::IR_A_MOSTRAR_CURSO:
            return std::make_unique<MostrarCursoScreen>(1, TipoUsuario::DEFAULT, pantallaFallback);
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
            _limpiarHistorialCompleto();
            _pantallaActualPtr = crearPantallaLandingPage();
            break;

        case AccionPantalla::IR_A_LOGIN:
            // Limpiar historial en login
            _limpiarHistorialCompleto();
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
            _pantallaActualPtr = _crearPantallaConHistorial(_resultado.accion);
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
            _pantallaActualPtr = _crearPantallaConHistorial(_resultado.accion);
            break;

		case AccionPantalla::IR_A_SOBRE_NOSOTROS:
            _pantallaActualPtr = _crearPantallaConHistorial(_resultado.accion);
			break;

        case AccionPantalla::IR_A_EXPLORAR_CURSOS_Y_ESPECIALIDADES:
            _pantallaActualPtr = _crearPantallaConHistorial(_resultado.accion);
            break;

        case AccionPantalla::IR_A_VER_BOLETAS:
            _pantallaActualPtr = _crearPantallaConHistorial(_resultado.accion);
            break;

        case AccionPantalla::IR_A_CREAR_CONTENIDO:
            _pantallaActualPtr = _crearPantallaConHistorial(_resultado.accion);
            break;

        case AccionPantalla::IR_A_VER_CERTIFICADOS:
            _pantallaActualPtr = _crearPantallaConHistorial(_resultado.accion);
            break;

        case AccionPantalla::IR_A_LISTAR_CONTENIDO:
            _pantallaActualPtr = _crearPantallaConHistorial(_resultado.accion);
            break;

        case AccionPantalla::IR_A_LISTAR_MIS_INSCRIPCIONES:
            _pantallaActualPtr = _crearPantallaConHistorial(_resultado.accion);
            break;

        case AccionPantalla::VOLVER_ANTERIOR:
            // ✅ NUEVO CASO: Manejar navegación hacia atrás usando el historial
            {
                AccionPantalla pantallaAnterior = _popHistorial();
                
                // Crear la pantalla anterior usando el sistema de historial
                switch (pantallaAnterior) {
                case AccionPantalla::IR_A_LANDING_PAGE:
                    _pantallaActualPtr = crearPantallaLandingPage();
                    break;
                case AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE:
                    _pantallaActualPtr = crearPantallaDashboardEstudiante();
                    break;
                case AccionPantalla::IR_A_DASHBOARD_ORGANIZACION:
                    _pantallaActualPtr = crearPantallaDashboardOrganizacion();
                    break;
                case AccionPantalla::IR_A_MOSTRAR_ESPECIALIZACION:
                    _pantallaActualPtr = _crearPantallaConHistorial(pantallaAnterior);
                    break;
                case AccionPantalla::IR_A_MOSTRAR_CURSO:
                    _pantallaActualPtr = _crearPantallaConHistorial(pantallaAnterior);
                    break;
                case AccionPantalla::IR_A_EXPLORAR_CURSOS_Y_ESPECIALIDADES:
                    _pantallaActualPtr = _crearPantallaConHistorial(pantallaAnterior);
                    break;
                case AccionPantalla::IR_A_LISTAR_CONTENIDO:
                    _pantallaActualPtr = _crearPantallaConHistorial(pantallaAnterior);
                    break;
                case AccionPantalla::IR_A_LISTAR_MIS_INSCRIPCIONES:
                    _pantallaActualPtr = _crearPantallaConHistorial(pantallaAnterior);
                    break;
                case AccionPantalla::IR_A_VER_CERTIFICADOS:
                    _pantallaActualPtr = _crearPantallaConHistorial(pantallaAnterior);
                    break;
                case AccionPantalla::IR_A_VER_ESTADISTICAS:
                    _pantallaActualPtr = _crearPantallaConHistorial(pantallaAnterior);
                    break;
                case AccionPantalla::IR_A_SOBRE_NOSOTROS:
                    _pantallaActualPtr = _crearPantallaConHistorial(pantallaAnterior);
                    break;
                case AccionPantalla::IR_A_VER_BOLETAS:
                    _pantallaActualPtr = _crearPantallaConHistorial(pantallaAnterior);
                    break;
                case AccionPantalla::IR_A_CREAR_CONTENIDO:
                    _pantallaActualPtr = _crearPantallaConHistorial(pantallaAnterior);
                    break;
                case AccionPantalla::IR_A_EDITAR_PERFIL:
                    _pantallaActualPtr = _crearPantallaConHistorial(pantallaAnterior);
                    break;
                default:
                    // Si no hay historial válido, ir a pantalla por defecto
                    _pantallaActualPtr = crearPantallaLandingPage();
                    break;
                }
                
                // Actualizar pantalla actual para el historial
                _pantallaActual = pantallaAnterior;
            }
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