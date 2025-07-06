#pragma once

#ifndef COURSERACLONE_SCREENS_LISTARMIS_INSCRIPCIONES_HPP
#define COURSERACLONE_SCREENS_LISTARMIS_INSCRIPCIONES_HPP

// Headers estándar
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <conio.h>
#include <limits>

// Headers propios
#include "../Utils/SystemUtils.hpp"
#include "../Utils/ScreenSystem.hpp"
#include "../Utils/UI_Ascii.hpp"
#include "../Utils/InputUtils.hpp"
#include "../Utils/ValidationUtils.hpp"
#include "../Types/UsuarioTypes.hpp"
#include "../Types/InscripcionTypes.hpp"
#include "../Controllers/ContentManager.hpp"
#include "../Controllers/SessionManager.hpp"

/// Pantalla para listar las inscripciones del estudiante actual
class ListarMisInscripcionesScreen : public PantallaBase
{
private:
    // Estado de navegación
    AccionPantalla _pantallaAnterior;
    bool _primeraRenderizacion;
    
    // Navegación
    int _inscripcionActual;
    int _totalInscripciones;
    int _paginaActual;
    int _inscripcionesPorPagina;
   
    std::vector<InscripcionContenido> _inscripciones;
    
    // Constantes para la interfaz
    static const int INSCRIPCIONES_POR_PAGINA = 8;
    static const int ANCHO_ITEM = 110;
    static const int ALTO_ITEM = 1;
    
    // COORDENADAS DE POSICIONAMIENTO
    /// @brief Coordenadas base para el listado
    static const int COL_LISTA_BASE = 8;
    static const int FILA_LISTA_BASE = 10;
    
    /// @brief Coordenadas para cada campo de la inscripción
    COORD _coordsID = {COL_LISTA_BASE, 0}; // Y será calculado dinámicamente
    COORD _coordsNombre = {COL_LISTA_BASE + 4, 0};
    COORD _coordsTipo = {COL_LISTA_BASE + 45, 0};
    COORD _coordsCompletado = {COL_LISTA_BASE + 63, 0};
    COORD _coordsPagado = {COL_LISTA_BASE + 82, 0};
    
    /// @brief Coordenadas para elementos de navegación
    COORD _coordsNavegacion = {40, 28};

    // ---- MÉTODOS PRIVADOS ----
    
    /// @brief Métodos de inicialización
    inline void _limpiarEstado();
    inline void _cargarInscripcionesEstudiante();
    inline void _cargarInscripcionesEjemplo(); // Mantener como fallback
    
    /// @brief Métodos de renderizado
    inline void dibujarInterfazCompleta();
    inline void _renderizarListaInscripciones();
    inline void _renderizarItemInscripcion(const InscripcionContenido& inscripcion, int fila, bool seleccionado);
    inline void _renderizarCampo(const COORD& coordBase, int fila, const std::string& texto, int ancho, bool alinearDerecha = false);
    inline void _limpiarAreaItems();
    inline void _renderizarNavegacion();
    
    /// @brief Métodos de navegación
    inline void _navegarArriba();
    inline void _navegarAbajo();
    inline void _cambiarPagina(int direccion);
    
    /// @brief Métodos de utilidad
    inline std::string _formatearEstado(bool estado);
    
public:
    inline ListarMisInscripcionesScreen(AccionPantalla pantallaAnterior = AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE);
    
    inline ~ListarMisInscripcionesScreen() = default;

    inline ResultadoPantalla ejecutar() override;
};

// --- IMPLEMENTACIONES INLINE ---

// Constructor
inline ListarMisInscripcionesScreen::ListarMisInscripcionesScreen(AccionPantalla pantallaAnterior) : PantallaBase(),
    _pantallaAnterior(pantallaAnterior), _primeraRenderizacion(true), 
    _inscripcionActual(0), _totalInscripciones(0), _paginaActual(1), _inscripcionesPorPagina(INSCRIPCIONES_POR_PAGINA)
{
    _cargarInscripcionesEstudiante();
}

// Método principal de ejecución
inline ResultadoPantalla ListarMisInscripcionesScreen::ejecutar()
{
    char tecla;
    
    do {
        if (_primeraRenderizacion) {
            dibujarInterfazCompleta();
            _primeraRenderizacion = false;
        }

        _renderizarListaInscripciones();
        _renderizarNavegacion();
        
        tecla = _getch();
        
        switch (tecla) {
            case 72: // Flecha arriba
                _navegarArriba();
                break;
                
            case 80: // Flecha abajo
                _navegarAbajo();
                break;
                
            case 75: // Flecha izquierda
                _cambiarPagina(-1);
                break;
                
            case 77: // Flecha derecha
                _cambiarPagina(1);
                break;
                
            case 13: // Enter - Navegar al curso/especialización seleccionado
                {
                    if (_inscripcionActual >= 0 && _inscripcionActual < _inscripciones.size()) {
                        const auto& inscripcionSeleccionada = _inscripciones[_inscripcionActual];
                        
                        if (inscripcionSeleccionada.esEspecializacion) {
                            // Navegar a MostrarEspecializacion
                            ContentManager::getInstance().setEspecializacionIdMostar(inscripcionSeleccionada.idActividad);
                            ResultadoPantalla resultado(AccionPantalla::IR_A_MOSTRAR_ESPECIALIZACION);
                            resultado.idEspecializacionSeleccionada = inscripcionSeleccionada.idActividad;
                            resultado.accionAnterior = AccionPantalla::IR_A_LISTAR_MIS_INSCRIPCIONES;
                            return resultado;
                        } else {
                            // Navegar a MostrarCurso
                            ContentManager::getInstance().setCursoIdMostrar(inscripcionSeleccionada.idActividad);
                            ResultadoPantalla resultado(AccionPantalla::IR_A_MOSTRAR_CURSO);
                            resultado.idCursoSeleccionado = inscripcionSeleccionada.idActividad;
                            resultado.accionAnterior = AccionPantalla::IR_A_LISTAR_MIS_INSCRIPCIONES;
                            return resultado;
                        }
                    }
                }
                break;
                
            case 27: // ESC
                return ResultadoPantalla(_pantallaAnterior);
        }
        
    } while (true);
    
    return ResultadoPantalla(AccionPantalla::SALIR);
}

// Limpiar estado
inline void ListarMisInscripcionesScreen::_limpiarEstado()
{
    _inscripcionActual = 0;
    _paginaActual = 1;
}

// Cargar inscripciones de ejemplo
inline void ListarMisInscripcionesScreen::_cargarInscripcionesEjemplo()
{
    _inscripciones = {
        {"Introducción a Python", 1, true, true, false},
        {"JavaScript Moderno", 3, false, true, false},
        {"Data Science", 2, true, true, true},
        {"Machine Learning Avanzado", 4, false, false, false},
        {"UX/UI Design", 6, true, true, false},
        {"Full Stack Developer", 5, false, true, true},
        {"Cybersecurity Essentials", 7, true, false, false},
        {"Cloud Computing AWS", 8, false, true, false}
    };
    
    _totalInscripciones = _inscripciones.size();
}

// Cargar inscripciones del estudiante actual
inline void ListarMisInscripcionesScreen::_cargarInscripcionesEstudiante()
{
    _inscripciones.clear();
    
    // Verificar si hay sesión activa
    if (!SessionManager::getInstance().isLoggedIn()) {
        _cargarInscripcionesEjemplo();
        return;
    }
    
    try {
        // Obtener el usuario actual (debe ser un estudiante)
        Usuario& usuarioActual = SessionManager::getInstance().getCurrentUser();
        
        if (usuarioActual.getTipoUsuario() != TipoUsuario::ESTUDIANTE) {
            _cargarInscripcionesEjemplo();
            return;
        }
        
        // Obtener el controlador de inscripciones del estudiante
        auto& inscripcionesController = SessionManager::getInstance().getInscripcionesController();
        
        // Cargar inscripciones del estudiante usando la función getInscripcionesContenido
        _inscripciones = inscripcionesController.getInscripcionesContenido();
        
        if (_inscripciones.empty()) {
            _cargarInscripcionesEjemplo();
        } else {
            _totalInscripciones = _inscripciones.size();
        }
        
    } catch (...) {
        // En caso de cualquier error, usar datos de ejemplo
        _cargarInscripcionesEjemplo();
    }
}

// Dibujar interfaz completa
inline void ListarMisInscripcionesScreen::dibujarInterfazCompleta()
{
    system("cls");
    UI_ListarMisInscripciones();
}

// Renderizar lista de inscripciones
inline void ListarMisInscripcionesScreen::_renderizarListaInscripciones()
{
    int inicioItem = (_paginaActual - 1) * _inscripcionesPorPagina;
    int finItem = (std::min)(inicioItem + _inscripcionesPorPagina, (int)_inscripciones.size());
    
    for (int i = inicioItem; i < finItem; i++) {
        int fila = FILA_LISTA_BASE + (i - inicioItem) * 2;
        bool seleccionado = (i == _inscripcionActual);
        _renderizarItemInscripcion(_inscripciones[i], fila, seleccionado);
    }
}

// Limpiar área de items mostrados
inline void ListarMisInscripcionesScreen::_limpiarAreaItems()
{
    // Limpiar solo las filas donde se muestran los items (sin tocar encabezados)
    for (int i = 0; i < INSCRIPCIONES_POR_PAGINA; i++) {
        int fila = FILA_LISTA_BASE + i * 2;
        gotoXY(COL_LISTA_BASE, fila);
        
        // Limpiar solo el área donde se escriben los datos (ancho específico)
        std::cout << std::string(ANCHO_ITEM, ' ');
    }
}

// Renderizar item individual de inscripción
inline void ListarMisInscripcionesScreen::_renderizarItemInscripcion(const InscripcionContenido& inscripcion, int fila, bool seleccionado)
{
    // Configurar colores según selección
    if (seleccionado) {
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
    } else {
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    }
    
    // Renderizar cada campo en sus coordenadas específicas
    _renderizarCampo(_coordsID, fila, std::to_string(inscripcion.idActividad), 3, true); // Right-aligned
    _renderizarCampo(_coordsNombre, fila, inscripcion.nombre, 38, false);
    
    std::string tipo = inscripcion.esEspecializacion ? "Especializacion" : "Curso";
    _renderizarCampo(_coordsTipo, fila, tipo, 17, false);
    
    _renderizarCampo(_coordsCompletado, fila, _formatearEstado(inscripcion.completado), 16, true);
    _renderizarCampo(_coordsPagado, fila, _formatearEstado(inscripcion.pagado), 10, true);
    
    resetColor();
}

// Renderizar un campo individual en coordenadas específicas
inline void ListarMisInscripcionesScreen::_renderizarCampo(const COORD& coordBase, int fila, const std::string& texto, int ancho, bool alinearDerecha)
{
    gotoXY(coordBase.X, fila);
    
    // Limpiar el área específica del campo antes de escribir
    std::cout << std::string(ancho, ' ');
    gotoXY(coordBase.X, fila);
    
    std::string textoFormateado = texto.length() > ancho ? texto.substr(0, ancho - 3) + "..." : texto;
    
    if (alinearDerecha) {
        std::cout << std::setw(ancho) << std::right << textoFormateado;
    } else {
        std::cout << std::setw(ancho) << std::left << textoFormateado;
    }
}

// Renderizar navegación
inline void ListarMisInscripcionesScreen::_renderizarNavegacion()
{
    int totalPaginas = (_inscripciones.size() + _inscripcionesPorPagina - 1) / _inscripcionesPorPagina;
    if (totalPaginas == 0) totalPaginas = 1;
    
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    
    gotoXY(_coordsNavegacion.X, _coordsNavegacion.Y);
    std::cout << "< ANTERIOR     [" << _paginaActual << "/" << totalPaginas << "]     SIGUIENTE >";
    
    resetColor();
}

// Navegación arriba
inline void ListarMisInscripcionesScreen::_navegarArriba()
{
    if (_inscripcionActual > 0) {
        _inscripcionActual--;
        
        // Cambiar página si es necesario
        int paginaItem = _inscripcionActual / _inscripcionesPorPagina + 1;
        if (paginaItem != _paginaActual) {
            // Limpiar área de items antes de cambiar de página
            _limpiarAreaItems();
            _paginaActual = paginaItem;
        }
    }
}

// Navegación abajo
inline void ListarMisInscripcionesScreen::_navegarAbajo()
{
    if (_inscripcionActual < (int)_inscripciones.size() - 1) {
        _inscripcionActual++;
        
        // Cambiar página si es necesario
        int paginaItem = _inscripcionActual / _inscripcionesPorPagina + 1;
        if (paginaItem != _paginaActual) {
            // Limpiar área de items antes de cambiar de página
            _limpiarAreaItems();
            _paginaActual = paginaItem;
        }
    }
}

// Cambiar página
inline void ListarMisInscripcionesScreen::_cambiarPagina(int direccion)
{
    int totalPaginas = (_inscripciones.size() + _inscripcionesPorPagina - 1) / _inscripcionesPorPagina;
    if (totalPaginas == 0) totalPaginas = 1;
    
    int nuevaPagina = _paginaActual + direccion;
    if (nuevaPagina >= 1 && nuevaPagina <= totalPaginas) {
        // Limpiar área de items antes de cambiar de página
        _limpiarAreaItems();
        
        _paginaActual = nuevaPagina;
        _inscripcionActual = (_paginaActual - 1) * _inscripcionesPorPagina;
        
        // Asegurar que el índice está dentro del rango
        if (_inscripcionActual >= (int)_inscripciones.size()) {
            _inscripcionActual = (std::max)(0, (int)_inscripciones.size() - 1);
        }
    }
}

// Formatear estado booleano
inline std::string ListarMisInscripcionesScreen::_formatearEstado(bool estado)
{
    return estado ? "Si" : "No";
}

#endif // COURSERACLONE_SCREENS_LISTARMIS_INSCRIPCIONES_HPP
