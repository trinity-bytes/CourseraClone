#ifndef COURSERACLONE_SCREENS_VERBOLETASSCREEN_HPP
#define COURSERACLONE_SCREENS_VERBOLETASSCREEN_HPP

// Headers estándar
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <conio.h>

// Headers propios
#include "../Utils/SystemUtils.hpp"
#include "../Utils/ScreenSystem.hpp"
#include "../Utils/UI_Ascii.hpp"
#include "../Types/UsuarioTypes.hpp"
#include "../Entities/ComprobanteDePago.hpp"

/// Pantalla para ver comprobantes de pago del estudiante
class VerBoletasScreen : public PantallaBase
{
private:
    // Estado de navegación
    AccionPantalla _pantallaAnterior;
    bool _primeraRenderizacion;
    
    // Navegación y selección
    int _comprobanteSeleccionado;
    int _indiceInicio;
    int _comprobantesPorPagina;
    
    // Datos simulados de comprobantes
    std::vector<ComprobanteDePago> _comprobantes;
    
    // Constantes para la interfaz
    static const int COL_TITULO = 45;
    static const int FILA_TITULO = 4;
    static const int COL_VOLVER = 100;
    static const int FILA_VOLVER = 4;
    
    static const int COL_LISTA_COMPROBANTES = 15;
    static const int FILA_LISTA_COMPROBANTES = 8;
    static const int ESPACIO_ENTRE_COMPROBANTES = 3;
    static const int ANCHO_COMPROBANTE = 90;
    
    // ---- MÉTODOS PRIVADOS ----
    
    /// @brief Métodos de inicialización
    inline void _limpiarEstado();
    
    /// @brief Métodos de renderizado
    inline void dibujarInterfazCompleta();
    inline void _renderizarTitulo();
    inline void _renderizarBotonVolver();
    inline void _renderizarListaComprobantes();
    inline void _renderizarIndicadoresPaginacion();
    inline void _mostrarQRComprobante(const ComprobanteDePago& comprobante);
    inline void _actualizarSeleccion();
    
    /// @brief Métodos de navegación
    inline void _manejarNavegacion(int tecla);
    inline void _navegarArriba();
    inline void _navegarAbajo();
    
    /// @brief Métodos de procesamiento
    inline ResultadoPantalla _procesarSeleccion();

public:
    inline VerBoletasScreen(AccionPantalla pantallaAnterior = AccionPantalla::IR_A_PERFIL_ESTUDIANTE);
    
    inline ~VerBoletasScreen() = default;

    inline ResultadoPantalla ejecutar() override;
};

// --- IMPLEMENTACIONES INLINE ---

// Constructor
inline VerBoletasScreen::VerBoletasScreen(AccionPantalla pantallaAnterior) : PantallaBase(),
    _pantallaAnterior(pantallaAnterior), _primeraRenderizacion(true), 
    _comprobanteSeleccionado(0), _indiceInicio(0), _comprobantesPorPagina(8)
{
}

// Limpiar estado
inline void VerBoletasScreen::_limpiarEstado()
{
    _comprobanteSeleccionado = 0;
    _indiceInicio = 0;
    _primeraRenderizacion = true;
}

// Dibujar interfaz completa
inline void VerBoletasScreen::dibujarInterfazCompleta()
{
    system("cls");
    UI_ComprobanteDePago();
    
    _renderizarTitulo();
    _renderizarBotonVolver();
    _renderizarListaComprobantes();
    _renderizarIndicadoresPaginacion();
    
    resetColor();
}

// Renderizar título
inline void VerBoletasScreen::_renderizarTitulo()
{
    gotoXY(COL_TITULO, FILA_TITULO);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "MIS COMPROBANTES DE PAGO";
    resetColor();
}

// Renderizar botón volver
inline void VerBoletasScreen::_renderizarBotonVolver()
{
    gotoXY(COL_VOLVER, FILA_VOLVER);
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "[ ESC - VOLVER ]";
    resetColor();
}

// Renderizar lista de comprobantes
inline void VerBoletasScreen::_renderizarListaComprobantes()
{
    if (_comprobantes.empty()) {
        gotoXY(COL_LISTA_COMPROBANTES, FILA_LISTA_COMPROBANTES + 2);
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "No tienes comprobantes de pago registrados.";
        resetColor();
        return;
    }
    
    int comprobantesAMostrar = (std::min)(_comprobantesPorPagina,
                                      static_cast<int>(_comprobantes.size()) - _indiceInicio);
    
    for (int i = 0; i < comprobantesAMostrar; ++i) {
        int indice = _indiceInicio + i;
        const ComprobanteDePago& comprobante = _comprobantes[indice];
        
        int fila = FILA_LISTA_COMPROBANTES + i * ESPACIO_ENTRE_COMPROBANTES;

        
        resetColor();
    }
}

// Renderizar indicadores de paginación
inline void VerBoletasScreen::_renderizarIndicadoresPaginacion()
{
    // Información de página actual
    gotoXY(COL_LISTA_COMPROBANTES, FILA_LISTA_COMPROBANTES + _comprobantesPorPagina * ESPACIO_ENTRE_COMPROBANTES + 1);
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    
    int paginaActual = (_indiceInicio / _comprobantesPorPagina) + 1;
    int totalPaginas = ((_comprobantes.size() - 1) / _comprobantesPorPagina) + 1;
    
    std::cout << "Página " << paginaActual << " de " << totalPaginas 
              << " | Total: " << _comprobantes.size() << " comprobantes";
    
    // Instrucciones de uso
    gotoXY(COL_LISTA_COMPROBANTES, FILA_LISTA_COMPROBANTES + _comprobantesPorPagina * ESPACIO_ENTRE_COMPROBANTES + 3);
    setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "ENTER - Ver código QR | ↑↓ - Navegar | ESC - Volver";
    
    // Indicadores de navegación
    if (_indiceInicio > 0) {
        gotoXY(COL_LISTA_COMPROBANTES, FILA_LISTA_COMPROBANTES - 1);
        setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "↑ Flecha ARRIBA para ver anteriores";
    }
    
    if (_indiceInicio + _comprobantesPorPagina < _comprobantes.size()) {
        gotoXY(COL_LISTA_COMPROBANTES, FILA_LISTA_COMPROBANTES + _comprobantesPorPagina * ESPACIO_ENTRE_COMPROBANTES + 5);
        setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "↓ Flecha ABAJO para ver siguientes";
    }
    
    resetColor();
}

// Mostrar QR para el comprobante
inline void VerBoletasScreen::_mostrarQRComprobante(const ComprobanteDePago& comprobante)
{
    system("cls");
    
    // Título de la pantalla del QR
    gotoXY(35, 3);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "COMPROBANTE DE PAGO - CÓDIGO QR";
    
    // QR ASCII simulado (representación visual simple)
    gotoXY(35, 11);
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "████████████████████████████████";
    gotoXY(35, 12);
    std::cout << "██                            ██";
    gotoXY(35, 13);
    std::cout << "██  ████  ██████  ████  ████  ██";
    gotoXY(35, 14);
    std::cout << "██  ████  ██████  ████  ████  ██";
    gotoXY(35, 15);
    std::cout << "██        ██████        ████  ██";
    gotoXY(35, 16);
    std::cout << "██  ████        ██████  ████  ██";
    gotoXY(35, 17);
    std::cout << "██  ████  ██████  ████  ████  ██";
    gotoXY(35, 18);
    std::cout << "██        ██████        ████  ██";
    gotoXY(35, 19);
    std::cout << "██  ████  ██████  ████  ████  ██";
    gotoXY(35, 20);
    std::cout << "██                            ██";
    gotoXY(35, 21);
    std::cout << "████████████████████████████████";
    
    resetColor();
    
    // Esperar a que el usuario presione una tecla
    _getch();
}

// Actualizar selección
inline void VerBoletasScreen::_actualizarSeleccion()
{
    _renderizarListaComprobantes();
    _renderizarIndicadoresPaginacion();
}

// Manejar navegación
inline void VerBoletasScreen::_manejarNavegacion(int tecla)
{
    switch (tecla) {
    case 72: // Flecha arriba
        _navegarArriba();
        break;
    case 80: // Flecha abajo
        _navegarAbajo();
        break;
    }
}

// Navegar hacia arriba
inline void VerBoletasScreen::_navegarArriba()
{
    if (_comprobanteSeleccionado > 0) {
        _comprobanteSeleccionado--;
    } else if (_indiceInicio > 0) {
        _indiceInicio--;
        _comprobanteSeleccionado = 0;
    }
}

// Navegar hacia abajo
inline void VerBoletasScreen::_navegarAbajo()
{
    int comprobantesEnPagina = (std::min)(_comprobantesPorPagina,
                                       static_cast<int>(_comprobantes.size()) - _indiceInicio);
    
    if (_comprobanteSeleccionado < comprobantesEnPagina - 1) {
        _comprobanteSeleccionado++;
    } else if (_indiceInicio + _comprobantesPorPagina < _comprobantes.size()) {
        _indiceInicio++;
        _comprobanteSeleccionado = 0;
    }
}

// Procesar selección
inline ResultadoPantalla VerBoletasScreen::_procesarSeleccion()
{
    ResultadoPantalla res;
    
    if (!_comprobantes.empty() && _indiceInicio + _comprobanteSeleccionado < _comprobantes.size()) {
        // Obtener el comprobante seleccionado
        const ComprobanteDePago& comprobanteSeleccionado = _comprobantes[_indiceInicio + _comprobanteSeleccionado];
        
        // Mostrar el QR del comprobante
        _mostrarQRComprobante(comprobanteSeleccionado);
        
        // Después de mostrar el QR, redibujar la interfaz completa
        _primeraRenderizacion = true;
    }
    
    return res;
}

// Método principal de ejecución
inline ResultadoPantalla VerBoletasScreen::ejecutar()
{
    _limpiarEstado();
    
    while (true) {
        if (_primeraRenderizacion) {
            dibujarInterfazCompleta();
            _primeraRenderizacion = false;
        } else {
            _actualizarSeleccion();
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
        
        case 72: // Flecha arriba (por si acaso)
        case 80: // Flecha abajo (por si acaso)
            _manejarNavegacion(tecla);
            break;
            
        case 13: // Enter - Ver detalles del comprobante
        {
            ResultadoPantalla res = _procesarSeleccion();
            if (res.accion != AccionPantalla::NINGUNA) {
                return res;
            }
        }
        break;
        
        case 27: // ESC - Volver a pantalla anterior
        {
            ResultadoPantalla res;
            res.accion = _pantallaAnterior;
            return res;
        }
        
        default:
            // Ignorar otras teclas
            break;
        }
    }
}

#endif // COURSERACLONE_SCREENS_VERBOLETASSCREEN_HPP
