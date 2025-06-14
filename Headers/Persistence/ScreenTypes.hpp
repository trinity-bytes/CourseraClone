#ifndef COURSERACLONE_TYPES_SCREENTYPES_HPP
#define COURSERACLONE_TYPES_SCREENTYPES_HPP

#include "..//Persistence/UsuarioTypes.hpp"

/// @brief Acciones de navegación disponibles en el sistema
enum class AccionPantalla
{
    NINGUNA,
    IR_A_LOGIN,
    IR_A_REGISTRO,
    IR_A_SOBRE_NOSOTROS,
    IR_A_DASHBOARD_ESTUDIANTE,
    IR_A_DASHBOARD_ORGANIZACION,
    IR_A_LANDING_PAGE,
    IR_A_PERFIL_ESTUDIANTE,
    IR_A_PERFIL_ORGANIZACION,
    IR_A_EDITAR_PERFIL,
    IR_A_MOSTRAR_CURSO,
    IR_A_MOSTRAR_ESPECIALIZACION,
    IR_A_EXPLORAR_CURSOS_Y_ESPECIALIDADES,
    IR_A_GESTIONAR_INSCRIPCIONES,
    IR_A_VER_BOLETAS,
    SALIR
};

/// @brief Identificadores de pantallas disponibles
enum class Pantalla
{
    NONE,
    LANDING_PAGE,
    LOGIN,
    REGISTRO,
    SOBRE_NOSOTROS,
    DASHBOARD_ESTUDIANTE,
    DASHBOARD_EMPRESA,
    PERFIL_ESTUDIANTE,
    PERFIL_ORGANIZACION,
    EDITAR_PERFIL,
    MOSTRAR_ESPECIALIZACION,
    MOSTRAR_CURSO,
    CURSOS_PUBLICADOS,
    ESPECIALIDADES_PUBLICADAS,
    CURSOS_INSCRITOS,
    ESPECIALIDADES_INSCRITAS,
    DETALLE_CURSO,
    DETALLE_ESPECIALIDAD
};

/// @brief Estructura que encapsula el resultado de la ejecución de una pantalla
struct ResultadoPantalla
{
    // Compatibilidad total con código existente
    AccionPantalla accion = AccionPantalla::NINGUNA;
    std::string email = "";
    std::string password = "";
    TipoUsuario tipoUsuario = TipoUsuario::DEFAULT;
    int idCursoSeleccionado = -1;
    AccionPantalla accionAnterior = AccionPantalla::NINGUNA;

    // Nuevos campos opcionales
    int idEspecializacionSeleccionada = -1;
    int idUsuarioActual = -1;
    bool sesionActiva = false;
    bool cambioRealizado = false;

    // Constructores
    ResultadoPantalla() = default;

    explicit ResultadoPantalla(AccionPantalla _accion) : accion(_accion) {}

    explicit ResultadoPantalla(AccionPantalla _accion, TipoUsuario _tipo) : 
        accion(_accion), 
        tipoUsuario(_tipo) {}

    ResultadoPantalla(
        AccionPantalla _accion, 
        const std::string& _email,
        const std::string& _password, 
        TipoUsuario _tipo
    ) : accion(_accion), email(_email), password(_password), tipoUsuario(_tipo) {}

    // Métodos de utilidad
    inline bool tieneAccion() const { return accion != AccionPantalla::NINGUNA; }
    inline bool esAccionSalir() const { return accion == AccionPantalla::SALIR; }
    inline bool tieneSeleccionCurso() const { return idCursoSeleccionado > 0; }
    inline bool tieneSeleccionEspecializacion() const { return idEspecializacionSeleccionada > 0; }

    inline void limpiarDatosSesion()
    {
        email.clear();
        password.clear();
        idUsuarioActual = -1;
        sesionActiva = false;
    }
};

// UTILIDADES DEL SISTEMA DE PANTALLAS
namespace ScreenUtils
{
    /// @brief Convierte AccionPantalla a string para usarlo en el debugging
    inline std::string accionToString(AccionPantalla _accion)
    {
        switch (_accion)
        {
        case AccionPantalla::IR_A_LANDING_PAGE: return "IR_A_LANDING_PAGE";
        case AccionPantalla::IR_A_LOGIN: return "IR_A_LOGIN";
        case AccionPantalla::IR_A_REGISTRO: return "IR_A_REGISTRO";
        case AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE: return "IR_A_DASHBOARD_ESTUDIANTE";
        case AccionPantalla::IR_A_DASHBOARD_ORGANIZACION: return "IR_A_DASHBOARD_ORGANIZACION";
        case AccionPantalla::SALIR: return "SALIR";
        default: return "NINGUNA";
        }
    }

    /// @brief Convierte Pantalla a string para debugging
    inline std::string pantallaToString(Pantalla _pantalla)
    {
        switch (_pantalla)
        {
        case Pantalla::LANDING_PAGE: return "LANDING_PAGE";
        case Pantalla::LOGIN: return "LOGIN";
        case Pantalla::REGISTRO: return "REGISTRO";
        case Pantalla::DASHBOARD_ESTUDIANTE: return "DASHBOARD_ESTUDIANTE";
        case Pantalla::DASHBOARD_EMPRESA: return "DASHBOARD_EMPRESA";
        default: return "NONE";
        }
    }

    /// @brief Mapea AccionPantalla a Pantalla
    inline Pantalla accionAPantalla(AccionPantalla _accion) {
        switch (_accion) {
        case AccionPantalla::IR_A_LANDING_PAGE: return Pantalla::LANDING_PAGE;
        case AccionPantalla::IR_A_LOGIN: return Pantalla::LOGIN;
        case AccionPantalla::IR_A_REGISTRO: return Pantalla::REGISTRO;
        case AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE: return Pantalla::DASHBOARD_ESTUDIANTE;
        case AccionPantalla::IR_A_DASHBOARD_ORGANIZACION: return Pantalla::DASHBOARD_EMPRESA;
        case AccionPantalla::IR_A_MOSTRAR_CURSO: return Pantalla::MOSTRAR_CURSO;
        case AccionPantalla::IR_A_EXPLORAR_CURSOS_Y_ESPECIALIDADES: return Pantalla::CURSOS_PUBLICADOS;
        default: return Pantalla::NONE;
        }
    }
}

#endif // !COURSERACLONE_TYPES_SCREENTYPES_HPP
