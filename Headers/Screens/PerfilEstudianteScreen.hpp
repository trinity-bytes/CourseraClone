#ifndef COURSERACLONE_SCREENS_PERFILESTUDIANTESCREEN_HPP
#define COURSERACLONE_SCREENS_PERFILESTUDIANTESCREEN_HPP

// Headers estándar
#include <string>
#include <conio.h>

// Headers propios
#include "../Utils/SystemUtils.hpp"
#include "../Utils/ScreenSystem.hpp"
#include "../Utils/UI_Ascii.hpp"
#include "../Controllers/ContentManager.hpp"

/// Pantalla para mostrar perfil de estudiante
class PerfilEstudianteScreen : public PantallaBase
{
private:
    /// @brief Constantes para secciones
    static const int SECCION_BOTONES = 0;
    static const int TOTAL_SECCIONES = 1;

    /// @brief Constantes para botones
    static const int BOTON_CERTIFICADOS = 0;
    static const int BOTON_BOLETAS = 1;
    static const int BOTON_EDITAR = 2;
    static const int TOTAL_BOTONES = 3;    
    
    /// @brief Datos del usuario
    int _idEstudiante;
    std::string _nombreEstudiante;
    std::string _emailEstudiante;
    std::string _fechaRegistroEstudiante;

    /// @brief Estadísticas del estudiante
    int _cursosCompletados;
    int _certificadosObtenidos;
    int _horasEstudio;

    /// @brief Estado actual
    int _seccionActual;
    int _botonActual;
    int _botonAnterior;
    bool _primeraRenderizacion;

    /// @brief Elementos de botones
    std::vector<std::string> _elementosHeader = {
        " MIS CERTIFICADOS ",
        " MIS BOLETAS ",
        " EDITAR PERFIL "
    };    
    
    /// @brief Coordenadas para botones
    COORD coordsBotones[TOTAL_BOTONES] = {
        {49, 10}, // MIS CERTIFICADOS
        {69, 10}, // MIS BOLETAS  
        {84, 10}  // EDITAR PERFIL
    };

    /// @brief Coordenadas para datos del perfil
    COORD coordsNombre = {34, 18};
    COORD coordsEmail = {30, 22};
    COORD coordsFechaRegistro = {49, 26};

    /// @brief Coordenadas para estadísticas
    COORD coordsEstadisticas[3] = {
        {30, 14}, {55, 14}, {80, 14}  // Cursos, Certificados, Horas
    };
	// ---- METODOS PRIVADOS ----

    /// @brief Métodos de inicialización
    inline void _limpiarEstado();
    inline void cargarDatos();
    inline void _cargarDatosDummy();

    /// @brief Métodos de renderizado
    inline void dibujarInterfazCompleta();
    inline void renderizarDatosPerfil();
    inline void renderizarEstadisticas();
    inline void renderizarBoton(int indice, bool seleccionado);
    inline void actualizarSeleccion();

    /// @brief Métodos de navegación
    inline void _manejarNavegacion(int tecla);
    inline ResultadoPantalla _procesarSeleccion();

public:

    inline PerfilEstudianteScreen();

    inline ~PerfilEstudianteScreen() = default;

    inline ResultadoPantalla ejecutar() override;
};

// --- IMPLEMENTACIONES INLINE ---

// Constructor
inline PerfilEstudianteScreen::PerfilEstudianteScreen() : PantallaBase(),
    _idEstudiante(1), _nombreEstudiante("Juan Carlos Pérez"),
    _emailEstudiante("juan.perez@upc.edu.pe"),
    _fechaRegistroEstudiante("15 de Marzo, 2024"),
    _cursosCompletados(8), _certificadosObtenidos(5), _horasEstudio(120),
    _seccionActual(0), _botonActual(0), _botonAnterior(-1), _primeraRenderizacion(true)
{
    _cargarDatosDummy();
}



// Limpiar estado
inline void PerfilEstudianteScreen::_limpiarEstado()
{
    _seccionActual = 0;
    _botonActual = 0;
    _botonAnterior = -1;
    _primeraRenderizacion = true;
    _cargarDatosDummy();
}

// Cargar datos de ejemplo
inline void PerfilEstudianteScreen::_cargarDatosDummy()
{
    SessionManager& sm = SessionManager::getInstance();
    bool sesionIniciada = sm.isLoggedIn();
    if (sesionIniciada) {
        _idEstudiante = sm.getCurrentUser().getId();
        _emailEstudiante = sm.getCurrentUser().getUsername();
        _nombreEstudiante = sm.getCurrentUser().getNombreCompleto();
        _fechaRegistroEstudiante = sm.getCurrentUser().getFechaRegistro();
        
        // Cargar estadísticas reales desde ContentManager
        ContentManager& cm = ContentManager::getInstance();
        std::vector<InscripcionBinaria> inscripciones = cm.obtenerInscripcionesEstudiante(_idEstudiante);
        
        _cursosCompletados = 0;
        _certificadosObtenidos = 0;
        _horasEstudio = 0;
        
        for (const auto& inscripcion : inscripciones) {
            if (inscripcion.completado) {
                _cursosCompletados++;
                _certificadosObtenidos++;
                
                // Calcular horas estimadas
                if (static_cast<TipoActividad>(inscripcion.tipoActividad) == TipoActividad::CURSO) {
                    RawCursoData curso = cm.obtenerCursoDatos(inscripcion.idActividad);
                    if (curso.id != -1) {
                        _horasEstudio += curso.cantidadClases * 2; // 2 horas por clase
                    }
                } else {
                    RawEspecializacionData esp = cm.obtenerEspecializacionDatos(inscripcion.idActividad);
                    if (esp.id != -1) {
                        _horasEstudio += esp.duracionEstimada * 8; // 8 horas por semana
                    }
                }
            }
        }
        
        // Si no hay datos reales, usar valores por defecto
        if (_cursosCompletados == 0) {
            _cursosCompletados = 8;
            _certificadosObtenidos = 5;
            _horasEstudio = 120;
        }
    } else {
        // Valores por defecto si no hay sesión
        _cursosCompletados = 8;
        _certificadosObtenidos = 5;
        _horasEstudio = 120;
    }
}

// Dibujar interfaz completa
inline void PerfilEstudianteScreen::dibujarInterfazCompleta()
{
    system("cls");
    UI_UserProfile();

    renderizarDatosPerfil();
    renderizarEstadisticas();
    
    // Renderizar todos los botones
    for (int i = 0; i < TOTAL_BOTONES; ++i) {
        renderizarBoton(i, _botonActual == i);
    }

    resetColor();
}

// Renderizar datos del perfil
inline void PerfilEstudianteScreen::renderizarDatosPerfil()
{
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    
    // Nombre
    gotoXY(coordsNombre.X, coordsNombre.Y);
    std::cout << _nombreEstudiante;
    
    // Email
    gotoXY(coordsEmail.X, coordsEmail.Y);
    std::cout << _emailEstudiante;
    
    // Fecha de registro
    gotoXY(coordsFechaRegistro.X, coordsFechaRegistro.Y);
    std::cout << _fechaRegistroEstudiante;
    
    resetColor();
}

// Renderizar estadísticas
inline void PerfilEstudianteScreen::renderizarEstadisticas()
{
    setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
    
    // Cursos completados
    gotoXY(coordsEstadisticas[0].X, coordsEstadisticas[0].Y);
    std::cout << _cursosCompletados;
    
    // Certificados obtenidos
    gotoXY(coordsEstadisticas[1].X, coordsEstadisticas[1].Y);
    std::cout << _certificadosObtenidos;
    
    // Horas de estudio
    gotoXY(coordsEstadisticas[2].X, coordsEstadisticas[2].Y);
    std::cout << _horasEstudio;
    
    resetColor();
}

// Renderizar botón
inline void PerfilEstudianteScreen::renderizarBoton(int indice, bool seleccionado)
{
    if (indice < 0 || indice >= TOTAL_BOTONES) return;
    
    gotoXY(coordsBotones[indice].X, coordsBotones[indice].Y);
    
    if (seleccionado) {
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::HOVER_ESTADO);
    } else {
        setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    }
    
    std::cout << _elementosHeader[indice];
    resetColor();
}

// Actualizar selección
inline void PerfilEstudianteScreen::actualizarSeleccion()
{
    if (_botonAnterior != _botonActual) {
        // Actualizar botón anterior
        if (_botonAnterior >= 0) {
            renderizarBoton(_botonAnterior, false);
        }
        
        // Actualizar botón actual
        renderizarBoton(_botonActual, true);
        
        _botonAnterior = _botonActual;
    }
}

// Manejar navegación
inline void PerfilEstudianteScreen::_manejarNavegacion(int tecla)
{
    switch (tecla) {
    case 75: // Flecha izquierda
        if (_botonActual > 0) {
            _botonActual--;
        } else {
            _botonActual = TOTAL_BOTONES - 1; // Ciclar al final
        }
        break;
    case 77: // Flecha derecha
        if (_botonActual < TOTAL_BOTONES - 1) {
            _botonActual++;
        } else {
            _botonActual = 0; // Ciclar al inicio
        }
        break;
    }
}

// Procesar selección
inline ResultadoPantalla PerfilEstudianteScreen::_procesarSeleccion()
{
    ResultadoPantalla res;
    
    switch (_botonActual) {
    case BOTON_CERTIFICADOS:
        // Ir a pantalla de certificados con historial
        res.accion = AccionPantalla::IR_A_VER_CERTIFICADOS;
        res.accionAnterior = AccionPantalla::IR_A_PERFIL_ESTUDIANTE;
        break;
    case BOTON_BOLETAS:
        // Ir a pantalla de boletas
        res.accion = AccionPantalla::IR_A_VER_BOLETAS;
        break;
    case BOTON_EDITAR:
        // Ir a pantalla de editar perfil
        res.accion = AccionPantalla::IR_A_EDITAR_PERFIL;
        break;
    default:
        res.accion = AccionPantalla::NINGUNA;
        break;
    }
    
    return res;
}

// Método principal de ejecución
inline ResultadoPantalla PerfilEstudianteScreen::ejecutar()
{
    ResultadoPantalla res;
    _limpiarEstado();

    while (true) {
        if (_primeraRenderizacion) {
            dibujarInterfazCompleta();
            _primeraRenderizacion = false;
        } else {
            actualizarSeleccion();
        }

        int tecla = _getch();

        switch (tecla) {
        case 0:
        case 224: // Teclas especiales
        {
            int segundaTecla = _getch();
            _manejarNavegacion(segundaTecla);
        }
        break;

        case 75: // Flecha izquierda (por si acaso)
        case 77: // Flecha derecha (por si acaso)
            _manejarNavegacion(tecla);
            break;

        case 27: // ESC - Regresar al dashboard
            res.accion = AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE;
            return res;

        case 13: // Enter - Procesar selección
            res = _procesarSeleccion();
            if (res.accion != AccionPantalla::NINGUNA) {
                return res;
            }
            break;

        default:
            // Ignorar otras teclas
            break;
        }
    }
}

#endif // COURSERACLONE_SCREENS_PERFILESTUDIANTESCREEN_HPP