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
    
    // COORDENADAS PARA EL SISTEMA DE POSICIONAMIENTO
    /// @brief Coordenadas para elementos principales
    static const short LISTA_INICIO_X = 8;
    static const short LISTA_INICIO_Y = 8;
    static const short ALTURA_COMPROBANTE = 2;
    static const short ANCHO_COMPROBANTE = 90;
    
    /// @brief Coordenadas para la información de paginación
    const COORD _coordsPaginacion = {8, 27};
    const COORD _coordsIndicadorPrevio = {60, 27};
    const COORD _coordsIndicadorSiguiente = {60, 27};
    
    /// @brief Coordenadas para los campos de cada comprobante
    struct CoordsComprobante {
        COORD numero;      // Número de comprobante
        COORD fecha;       // Fecha de emisión
        COORD actividad;   // Nombre de la actividad
        COORD monto;       // Monto pagado
        COORD estado;      // Estado del comprobante
    };
    
    // ---- MÉTODOS PRIVADOS ----
    
    /// @brief Métodos de inicialización
    inline void _limpiarEstado();
    inline void _cargarDatosEjemplo();
    
    /// @brief Métodos de renderizado
    inline void dibujarInterfazCompleta();
    inline void _renderizarListaComprobantes();
    inline void _renderizarComprobante(const ComprobanteDePago& comprobante, int indice, bool seleccionado);
    inline void _renderizarIndicadoresPaginacion();
    inline void _mostrarQRComprobante(const ComprobanteDePago& comprobante);
    inline void _actualizarSeleccion();
    
    /// @brief Métodos de navegación
    inline void _manejarNavegacion(int tecla);
    inline void _navegarArriba();
    inline void _navegarAbajo();
    
    /// @brief Métodos de procesamiento
    inline ResultadoPantalla _procesarSeleccion();
    
    /// @brief Métodos utilitarios
    inline CoordsComprobante _calcularCoordenadasComprobante(int indice);
    inline std::string _formatearMonto(double monto);

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
    _cargarDatosEjemplo();
}

// Limpiar estado
inline void VerBoletasScreen::_limpiarEstado()
{
    _comprobanteSeleccionado = 0;
    _indiceInicio = 0;
    _primeraRenderizacion = true;
}

// Cargar datos de ejemplo para pruebas
inline void VerBoletasScreen::_cargarDatosEjemplo()
{
    _comprobantes.clear();
    
    // Generar algunos comprobantes de ejemplo
    _comprobantes.push_back(ComprobanteDePago(1, 1001, 101, TipoActividad::CURSO, 99.0));
    _comprobantes.push_back(ComprobanteDePago(2, 1001, 102, TipoActividad::ESPECIALIZACION, 199.0));
    _comprobantes.push_back(ComprobanteDePago(3, 1001, 103, TipoActividad::CURSO, 149.0));
    _comprobantes.push_back(ComprobanteDePago(4, 1001, 104, TipoActividad::ESPECIALIZACION, 299.0));
    _comprobantes.push_back(ComprobanteDePago(5, 1001, 105, TipoActividad::CURSO, 79.0));
    _comprobantes.push_back(ComprobanteDePago(6, 1001, 106, TipoActividad::CURSO, 119.0));
    _comprobantes.push_back(ComprobanteDePago(7, 1001, 107, TipoActividad::ESPECIALIZACION, 249.0));
    _comprobantes.push_back(ComprobanteDePago(8, 1001, 108, TipoActividad::CURSO, 89.0));
    _comprobantes.push_back(ComprobanteDePago(8, 1001, 108, TipoActividad::CURSO, 89.0));
    _comprobantes.push_back(ComprobanteDePago(8, 1001, 108, TipoActividad::CURSO, 89.0));
}

// Dibujar interfaz completa
inline void VerBoletasScreen::dibujarInterfazCompleta()
{
    system("cls");
    UI_ComprobanteDePago();
    
    _renderizarListaComprobantes();
    _renderizarIndicadoresPaginacion();
    
    resetColor();
}

// Calcular coordenadas para un comprobante específico
inline VerBoletasScreen::CoordsComprobante VerBoletasScreen::_calcularCoordenadasComprobante(int indice)
{
    short fila = static_cast<short>(LISTA_INICIO_Y + (indice * ALTURA_COMPROBANTE));
    
    CoordsComprobante coords;
    coords.numero = {LISTA_INICIO_X, fila};
    coords.fecha = {static_cast<short>(LISTA_INICIO_X + 8), fila};
    coords.actividad = {static_cast<short>(LISTA_INICIO_X + 20), fila};
    coords.monto = {static_cast<short>(LISTA_INICIO_X + 65), fila};
    coords.estado = {static_cast<short>(LISTA_INICIO_X + 78), fila};
    
    return coords;
}

// Formatear monto con símbolo de moneda
inline std::string VerBoletasScreen::_formatearMonto(double monto)
{
    std::ostringstream oss;
    oss << "S/ " << std::fixed << std::setprecision(2) << monto;
    return oss.str();
}

// Renderizar lista de comprobantes usando coordenadas
inline void VerBoletasScreen::_renderizarListaComprobantes()
{
    if (_comprobantes.empty()) {
        gotoXY(LISTA_INICIO_X, LISTA_INICIO_Y + 2);
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "No tienes comprobantes de pago registrados.";
        resetColor();
        return;
    }
    
    int comprobantesAMostrar = (std::min)(_comprobantesPorPagina,
                                      static_cast<int>(_comprobantes.size()) - _indiceInicio);
    
    for (int i = 0; i < comprobantesAMostrar; ++i) {
        int indiceGlobal = _indiceInicio + i;
        const ComprobanteDePago& comprobante = _comprobantes[indiceGlobal];
        bool seleccionado = (_comprobanteSeleccionado == i);
        
        _renderizarComprobante(comprobante, i, seleccionado);
    }
}

// Renderizar un comprobante individual con coordenadas precisas
inline void VerBoletasScreen::_renderizarComprobante(const ComprobanteDePago& comprobante, int indice, bool seleccionado)
{
    CoordsComprobante coords = _calcularCoordenadasComprobante(indice);
    
    // Obtener datos del comprobante usando el método público
    RawComprobanteData datos = const_cast<ComprobanteDePago&>(comprobante).obtenerDatosCrudosComprobante();
    
    // Configurar colores según selección
    if (seleccionado) {
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
    } else {
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    }
    
    // Limpiar línea completa
    gotoXY(LISTA_INICIO_X, coords.numero.Y);
    std::cout << std::string(ANCHO_COMPROBANTE, ' ');
    
    // Renderizar campos del comprobante
    // Número de comprobante
    gotoXY(coords.numero.X, coords.numero.Y);
    std::cout << "#" << std::setfill('0') << std::setw(4) << datos.id;
    
    // Fecha de emisión
    gotoXY(coords.fecha.X, coords.fecha.Y);
    std::cout << datos.fechaEmision;
    
    // Tipo y nombre de actividad (simulado)
    gotoXY(coords.actividad.X, coords.actividad.Y);
    std::string tipoActividad = (datos.tipoActividad == TipoActividad::CURSO) ? "Curso" : "Especialización";
    std::cout << tipoActividad << " #" << datos.idActividad;
    
    // Monto pagado
    gotoXY(coords.monto.X, coords.monto.Y);
    std::cout << _formatearMonto(datos.montoPagado);
    
    // Estado (siempre "Pagado" para comprobantes existentes)
    gotoXY(coords.estado.X, coords.estado.Y);
    setConsoleColor(ColorIndex::EXITO_COLOR, seleccionado ? ColorIndex::AZUL_MARCA : ColorIndex::FONDO_PRINCIPAL);
    std::cout << "PAGADO";
    
    resetColor();
}

// Renderizar indicadores de paginación usando coordenadas
inline void VerBoletasScreen::_renderizarIndicadoresPaginacion()
{
    if (_comprobantes.empty()) return;
    
    // Información de página actual
    gotoXY(_coordsPaginacion.X, _coordsPaginacion.Y);
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    
    int paginaActual = (_indiceInicio / _comprobantesPorPagina) + 1;
    int totalPaginas = ((_comprobantes.size() - 1) / _comprobantesPorPagina) + 1;
    
    std::cout << "Página " << paginaActual << " de " << totalPaginas 
              << " | Total: " << _comprobantes.size() << " comprobantes";
    
    // Indicadores de navegación
    if (_indiceInicio > 0) {
        gotoXY(_coordsIndicadorPrevio.X, _coordsIndicadorPrevio.Y);
        setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "↑ Flecha ARRIBA para ver anteriores ";
    }
    
    if (_indiceInicio + _comprobantesPorPagina < _comprobantes.size()) {
        gotoXY(_coordsIndicadorSiguiente.X, _coordsIndicadorSiguiente.Y);
        setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "↓ Flecha ABAJO para ver siguientes  ";
    }
    
    resetColor();
}

// Mostrar QR para el comprobante usando coordenadas
inline void VerBoletasScreen::_mostrarQRComprobante(const ComprobanteDePago& comprobante)
{
    system("cls");
    
    // Obtener datos del comprobante usando el método público
    RawComprobanteData datos = const_cast<ComprobanteDePago&>(comprobante).obtenerDatosCrudosComprobante();
    
    // Coordenadas para el QR
    const COORD coordsTituloQR = {35, 3};
    const COORD coordsQR = {35, 11};
    const COORD coordsInfoComprobante = {20, 23};
    
    // Título de la pantalla del QR
    gotoXY(coordsTituloQR.X, coordsTituloQR.Y);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "COMPROBANTE DE PAGO - CÓDIGO QR";
    
    // QR ASCII simulado (representación visual simple)
    for (int i = 0; i < 11; ++i) {
        gotoXY(coordsQR.X, coordsQR.Y + i);
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        switch (i) {
            case 0:
            case 10:
                std::cout << "████████████████████████████████";
                break;
            case 1:
            case 9:
                std::cout << "██                            ██";
                break;
            default:
                std::cout << "██  ████  ██████  ████  ████  ██";
                break;
        }
    }
    
    // Información del comprobante
    gotoXY(coordsInfoComprobante.X, coordsInfoComprobante.Y);
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Comprobante #" << std::setfill('0') << std::setw(4) << datos.id;
    
    gotoXY(coordsInfoComprobante.X, coordsInfoComprobante.Y + 1);
    std::cout << "Fecha: " << datos.fechaEmision;
    
    gotoXY(coordsInfoComprobante.X, coordsInfoComprobante.Y + 2);
    std::cout << "Monto: " << _formatearMonto(datos.montoPagado);
    
    gotoXY(coordsInfoComprobante.X, coordsInfoComprobante.Y + 4);
    setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Presiona cualquier tecla para volver...";
    
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
