#pragma once

// Headers de librerías
#include <string>
#include <vector>
#include <memory>

// Headers propios
#include "../Entities/Usuario.h"
#include "SystemUtils.h"
#include "UI_Ascii.h"

using std::string;
using std::vector;
using std::unique_ptr;

// Declaración anticipada de la clase Controladora
class Controladora;

//=============================================================================
// SISTEMA UNIFICADO DE PANTALLAS - COURSERA CLONE
//=============================================================================

/// @brief Acciones de navegación disponibles en el sistema
enum class AccionPantalla {
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

/// @brief Estructura que encapsula el resultado de la ejecución de una pantalla
struct ResultadoPantalla {
    // Compatibilidad total con código existente
    AccionPantalla accion = AccionPantalla::NINGUNA;
    string email;
    string password;
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
    
    ResultadoPantalla(AccionPantalla _accion, const string& _email, 
                     const string& _password, TipoUsuario _tipo)
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

/// @brief Clase abstracta base para todas las pantallas del sistema
class PantallaBase {
protected:
    Controladora* _controladora = nullptr;
    bool _esPrimeraVez = true;
    string _titulo = "";
    
public:
    explicit PantallaBase(Controladora* controladora = nullptr) 
        : _controladora(controladora) {}
    
    virtual ~PantallaBase() = default;
    
    // Método principal que debe implementar cada pantalla
    virtual ResultadoPantalla ejecutar() = 0;
    
    // Métodos opcionales
    virtual void inicializar() {}
    virtual void limpiar() {}
    virtual bool validarAcceso() { return true; }
    
    // Getters y setters
    void setControladora(Controladora* controladora) { _controladora = controladora; }
    void setTitulo(const string& titulo) { _titulo = titulo; }
    const string& getTitulo() const { return _titulo; }
    bool esPrimeraVez() const { return _esPrimeraVez; }
    
protected:
    void marcarComoVisitada() { _esPrimeraVez = false; }
    
    // Helpers para crear resultados
    ResultadoPantalla crearResultado(AccionPantalla accion) const {
        return ResultadoPantalla(accion);
    }
    
    ResultadoPantalla crearResultadoLogin(AccionPantalla accion, const string& email, 
                                        const string& password, TipoUsuario tipo) const {
        return ResultadoPantalla(accion, email, password, tipo);
    }
    
    ResultadoPantalla crearResultadoConCurso(AccionPantalla accion, int idCurso) const {
        ResultadoPantalla resultado(accion);
        resultado.idCursoSeleccionado = idCurso;
        return resultado;
    }
};

//=============================================================================
// UTILIDADES DEL SISTEMA DE PANTALLAS
//=============================================================================

namespace ScreenUtils {
    
    /// @brief Convierte AccionPantalla a string para debugging
    inline string accionToString(AccionPantalla accion) {
        switch (accion) {
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
    inline string pantallaToString(Pantalla pantalla) {
        switch (pantalla) {
            case Pantalla::LANDING_PAGE: return "LANDING_PAGE";
            case Pantalla::LOGIN: return "LOGIN";
            case Pantalla::REGISTRO: return "REGISTRO";
            case Pantalla::DASHBOARD_ESTUDIANTE: return "DASHBOARD_ESTUDIANTE";
            case Pantalla::DASHBOARD_EMPRESA: return "DASHBOARD_EMPRESA";
            default: return "NONE";
        }
    }
    
    /// @brief Mapea AccionPantalla a Pantalla
    inline Pantalla accionAPantalla(AccionPantalla accion) {
        switch (accion) {
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
    
    /// @brief Verifica si una acción es para estudiantes
    inline bool esAccionEstudiante(AccionPantalla accion) {
        return accion == AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE ||
               accion == AccionPantalla::IR_A_PERFIL_ESTUDIANTE;
    }
    
    /// @brief Verifica si una acción es para organizaciones
    inline bool esAccionOrganizacion(AccionPantalla accion) {
        return accion == AccionPantalla::IR_A_DASHBOARD_ORGANIZACION ||
               accion == AccionPantalla::IR_A_PERFIL_ORGANIZACION;
    }
}
