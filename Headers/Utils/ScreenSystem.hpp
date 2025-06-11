// filepath: Headers/Utils/ScreenSystem.hpp
// Descripcion: Sistema de gestión de pantallas y navegación

#ifndef COURSERACLONE_UTILS_SCREENSYSTEM_HPP
#define COURSERACLONE_UTILS_SCREENSYSTEM_HPP

// Headers de librerías
#include <string>
#include <vector>
#include <memory>

// Headers propios
#include "../Persistence/UsuarioTypes.hpp"
#include "SystemUtils.hpp"
#include "UI_Ascii.hpp"

// Declaración anticipada de la clase Controladora
class Controladora;

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
enum class Pantalla {
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

// Estructura que encapsula el resultado de la ejecución de una pantalla
struct ResultadoPantalla {
    // Compatibilidad total con código existente
    AccionPantalla accion = AccionPantalla::NINGUNA;
    std::string email;
    std::string password;
    TipoUsuario tipoUsuario = TipoUsuario::ESTUDIANTE;
    int idCursoSeleccionado = -1;
    AccionPantalla accionAnterior = AccionPantalla::NINGUNA;
    
    // Nuevos campos opcionales
    int idEspecializacionSeleccionada = -1;
    int idUsuarioActual = -1;
    bool sesionActiva = false;
    bool cambioRealizado = false;
    
    // Constructores
    ResultadoPantalla() = default;
    
    explicit ResultadoPantalla(AccionPantalla _accion) 
        : accion(_accion) {}

    explicit ResultadoPantalla(AccionPantalla _accion, TipoUsuario _tipo)
        : accion(_accion), tipoUsuario(_tipo) {}
    
    ResultadoPantalla(AccionPantalla _accion, const std::string& _email, 
                     const std::string& _password, TipoUsuario _tipo)
        : accion(_accion), email(_email), password(_password), tipoUsuario(_tipo) {}
    
    // Métodos de utilidad
    bool tieneAccion() const { return accion != AccionPantalla::NINGUNA; }
    bool esAccionSalir() const { return accion == AccionPantalla::SALIR; }
    bool tieneSeleccionCurso() const { return idCursoSeleccionado > 0; }
    bool tieneSeleccionEspecializacion() const { return idEspecializacionSeleccionada > 0; }
    
    void limpiarDatosSesion() {
        email.clear();
        password.clear();
        idUsuarioActual = -1;
        sesionActiva = false;
    }
};

// Clase abstracta base para todas las pantallas del sistema
class PantallaBase {
protected:
    Controladora* _controladora = nullptr;
    bool _esPrimeraVez = true;
    std::string _titulo = "";
    
public:
    explicit PantallaBase(Controladora* _controladora = nullptr) 
        : _controladora(_controladora) {}
    
    virtual ~PantallaBase() = default;
    
    // Método principal que debe implementar cada pantalla
    virtual ResultadoPantalla ejecutar() = 0;
    
    // Métodos opcionales
    virtual void inicializar() {}
    virtual void limpiar() {}
    virtual bool validarAcceso() { return true; }
    
    // Getters y setters
    void setControladora(Controladora* _controladora) { this->_controladora = _controladora; }
    void setTitulo(const std::string& _titulo) { this->_titulo = _titulo; }
    const std::string& getTitulo() const { return _titulo; }
    bool esPrimeraVez() const { return _esPrimeraVez; }
    
protected:
    void marcarComoVisitada() { _esPrimeraVez = false; }
    
    // Helpers para crear resultados
    ResultadoPantalla crearResultado(AccionPantalla _accion) const {
        return ResultadoPantalla(_accion);
    }

    ResultadoPantalla crearResultado(AccionPantalla _accion, TipoUsuario _user) const {
        return ResultadoPantalla(_accion, _user);
    }
    
    ResultadoPantalla crearResultadoLogin(AccionPantalla _accion, const std::string& _email, 
                                        const std::string& _password, TipoUsuario _tipo) const {
        return ResultadoPantalla(_accion, _email, _password, _tipo);
    }
    
    ResultadoPantalla crearResultadoConCurso(AccionPantalla _accion, int _idCurso) const {
        ResultadoPantalla resultado(_accion);        resultado.idCursoSeleccionado = _idCurso;
        return resultado;
    }
};

// UTILIDADES DEL SISTEMA DE PANTALLAS
namespace ScreenUtils {
    
    // Convierte AccionPantalla a string para usarlo en el debugging
    inline std::string accionToString(AccionPantalla _accion) {
        switch (_accion) {
            case AccionPantalla::IR_A_LANDING_PAGE: return "IR_A_LANDING_PAGE";
            case AccionPantalla::IR_A_LOGIN: return "IR_A_LOGIN";
            case AccionPantalla::IR_A_REGISTRO: return "IR_A_REGISTRO";
            case AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE: return "IR_A_DASHBOARD_ESTUDIANTE";
            case AccionPantalla::IR_A_DASHBOARD_ORGANIZACION: return "IR_A_DASHBOARD_ORGANIZACION";
            case AccionPantalla::SALIR: return "SALIR";
            default: return "NINGUNA";
        }
    }
    
    // Convierte Pantalla a string para debugging
    inline std::string pantallaToString(Pantalla _pantalla) {
        switch (_pantalla) {
            case Pantalla::LANDING_PAGE: return "LANDING_PAGE";
            case Pantalla::LOGIN: return "LOGIN";
            case Pantalla::REGISTRO: return "REGISTRO";
            case Pantalla::DASHBOARD_ESTUDIANTE: return "DASHBOARD_ESTUDIANTE";
            case Pantalla::DASHBOARD_EMPRESA: return "DASHBOARD_EMPRESA";
            default: return "NONE";
        }
    }
    
    // Mapea AccionPantalla a Pantalla
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
    
    // Verifica si una acción es para estudiantes
    inline bool esAccionEstudiante(AccionPantalla _accion) {
        return _accion == AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE ||
               _accion == AccionPantalla::IR_A_PERFIL_ESTUDIANTE;
    }
    
    // Verifica si una acción es para organizaciones
    inline bool esAccionOrganizacion(AccionPantalla _accion) {
        return _accion == AccionPantalla::IR_A_DASHBOARD_ORGANIZACION ||
               _accion == AccionPantalla::IR_A_PERFIL_ORGANIZACION;
    }
}

#endif // COURSERACLONE_UTILS_SCREENSYSTEM_HPP
