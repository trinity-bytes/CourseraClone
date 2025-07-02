#ifndef COURSERACLONE_SCREENS_GESTIONAROFERTASSCREEN_HPP
#define COURSERACLONE_SCREENS_GESTIONAROFERTASSCREEN_HPP

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

/// Pantalla para gestionar ofertas existentes de la organización
class GestionarOfertasScreen : public PantallaBase
{
private:
    // Estado de navegación
    AccionPantalla _pantallaAnterior;
    bool _primeraRenderizacion;
    
    // Navegación y filtros
    int _ofertaActual;
    int _totalOfertas;
    int _paginaActual;
    int _ofertasPorPagina;
    std::string _filtroEstado; // "TODAS", "ACTIVAS", "VENCIDAS", "INACTIVAS"
    
    // Estructura de datos para ofertas
    struct OfertaGestionada {
        int id;
        std::string nombreContenido;
        std::string tipoContenido; // "Curso" o "Especialización"
        std::string codigoPromocional;
        int descuentoPorcentaje;
        double precioOriginal;
        double precioConDescuento;
        std::string fechaCreacion;
        std::string fechaVencimiento;
        std::string estado; // "Activa", "Vencida", "Inactiva", "Pausada"
        int usosTotal;
        int usosRestantes;
        double ingresoGenerado;
    };
    
    std::vector<OfertaGestionada> _ofertas;
    std::vector<OfertaGestionada> _ofertasFiltradas;
    
    // Constantes para la interfaz
    static const int OFERTAS_POR_PAGINA = 8;
    static const int COL_LISTA = 5;
    static const int FILA_LISTA = 10;
    static const int ANCHO_ITEM = 110;
    static const int ALTO_ITEM = 3;
    
    static const int COL_FILTROS = 90;
    static const int FILA_FILTROS = 6;
    
    static const int COL_NAVEGACION = 40;
    static const int FILA_NAVEGACION = 27;
    
    // ---- MÉTODOS PRIVADOS ----
    
    /// @brief Métodos de inicialización
    inline void _limpiarEstado();
    inline void _cargarOfertasEjemplo();
    
    /// @brief Métodos de renderizado
    inline void dibujarInterfazCompleta();
    inline void _renderizarListaOfertas();
    inline void _renderizarItemOferta(const OfertaGestionada& oferta, int fila, bool seleccionado);
    inline void _renderizarFiltros();
    inline void _renderizarEstadisticas();
    inline void _renderizarNavegacion();
    inline void _renderizarInstrucciones();
    
    /// @brief Métodos de navegación
    inline void _navegarArriba();
    inline void _navegarAbajo();
    inline void _cambiarPagina(int direccion);
    inline void _cambiarFiltroEstado();
    
    /// @brief Métodos de filtrado
    inline void _aplicarFiltros();
    inline bool _cumpleFiltros(const OfertaGestionada& oferta);
    
    /// @brief Métodos de acción
    inline void _verDetallesOferta();
    inline void _editarOferta();
    inline void _cambiarEstadoOferta();
    inline void _eliminarOferta();
    inline void _duplicarOferta();
    
    /// @brief Métodos de utilidad
    inline std::string _formatearPrecio(double precio);
    inline std::string _formatearFecha(const std::string& fecha);
    inline std::string _obtenerColorEstado(const std::string& estado);
    inline bool _estaVencida(const std::string& fechaVencimiento);

public:
    inline GestionarOfertasScreen(AccionPantalla pantallaAnterior = AccionPantalla::IR_A_DASHBOARD_ORGANIZACION);
    
    inline ~GestionarOfertasScreen() = default;

    inline ResultadoPantalla ejecutar() override;
};

// --- IMPLEMENTACIONES INLINE ---

// Constructor
inline GestionarOfertasScreen::GestionarOfertasScreen(AccionPantalla pantallaAnterior) : PantallaBase(),
    _pantallaAnterior(pantallaAnterior), _primeraRenderizacion(true), 
    _ofertaActual(0), _totalOfertas(0), _paginaActual(1), _ofertasPorPagina(OFERTAS_POR_PAGINA),
    _filtroEstado("TODAS")
{
    _cargarOfertasEjemplo();
    _aplicarFiltros();
}

// Método principal de ejecución
inline ResultadoPantalla GestionarOfertasScreen::ejecutar()
{
    char tecla;
    
    do {
        if (_primeraRenderizacion) {
            dibujarInterfazCompleta();
            _primeraRenderizacion = false;
        }
        
        _renderizarListaOfertas();
        _renderizarFiltros();
        _renderizarEstadisticas();
        _renderizarNavegacion();
        _renderizarInstrucciones();
        
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
                
            case 13: // Enter - Ver detalles
                _verDetallesOferta();
                break;
                
            case 'e': case 'E': // Editar oferta
                _editarOferta();
                break;
                
            case 's': case 'S': // Cambiar estado
                _cambiarEstadoOferta();
                break;
                
            case 'd': case 'D': // Duplicar oferta
                _duplicarOferta();
                break;
                
            case 'x': case 'X': // Eliminar oferta
                _eliminarOferta();
                break;
                
            case 'f': case 'F': // Cambiar filtro estado
                _cambiarFiltroEstado();
                _aplicarFiltros();
                _primeraRenderizacion = true;
                break;
                
            case 27: // ESC
                return ResultadoPantalla(_pantallaAnterior);
        }
        
    } while (true);
    
    return ResultadoPantalla(AccionPantalla::SALIR);
}

// Limpiar estado
inline void GestionarOfertasScreen::_limpiarEstado()
{
    _ofertaActual = 0;
    _paginaActual = 1;
}

// Cargar ofertas de ejemplo
inline void GestionarOfertasScreen::_cargarOfertasEjemplo()
{
    _ofertas = {
        {1, "Introducción a Python", "Curso", "PYTHON20", 20, 89.90, 71.92, "15/06/2025", "30/07/2025", "Activa", 45, 55, 3236.40},
        {2, "Especialización Data Science", "Especialización", "DATASCI40", 40, 299.99, 179.99, "20/05/2025", "15/08/2025", "Activa", 78, 22, 14039.22},
        {3, "JavaScript Moderno", "Curso", "JS25", 25, 79.99, 59.99, "10/06/2025", "25/07/2025", "Activa", 32, 68, 1919.68},
        {4, "Machine Learning Avanzado", "Curso", "ML50", 50, 149.99, 74.99, "05/05/2025", "20/06/2025", "Vencida", 15, 0, 1124.85},
        {5, "Full Stack Development", "Especialización", "FULLSTACK30", 30, 399.99, 279.99, "12/06/2025", "30/08/2025", "Activa", 23, 77, 6439.77},
        {6, "UX/UI Design Fundamentals", "Curso", "DESIGN35", 35, 99.99, 64.99, "18/06/2025", "18/07/2025", "Pausada", 8, 92, 519.92},
        {7, "Cybersecurity Essentials", "Curso", "CYBER25", 25, 129.99, 97.49, "25/05/2025", "10/07/2025", "Activa", 29, 71, 2827.21},
        {8, "Cloud Computing AWS", "Curso", "CLOUD40", 40, 179.99, 107.99, "01/06/2025", "31/07/2025", "Activa", 19, 81, 2051.81},
        {9, "DevOps con Docker", "Especialización", "DEVOPS45", 45, 349.99, 192.49, "08/06/2025", "08/08/2025", "Activa", 12, 88, 2309.88},
        {10, "Marketing Digital", "Curso", "MARKETING20", 20, 89.99, 71.99, "02/05/2025", "15/06/2025", "Vencida", 67, 0, 4823.33}
    };
    
    _totalOfertas = _ofertas.size();
}

// Dibujar interfaz completa
inline void GestionarOfertasScreen::dibujarInterfazCompleta()
{
	system("cls");
    UI_GestionarOfertas();
}

// Renderizar lista de ofertas
inline void GestionarOfertasScreen::_renderizarListaOfertas()
{
    int inicioItem = (_paginaActual - 1) * _ofertasPorPagina;
    int finItem = (std::min)(inicioItem + _ofertasPorPagina, (int)_ofertasFiltradas.size());
    
    for (int i = inicioItem; i < finItem; i++) {
        int filaItem = FILA_LISTA + (i - inicioItem) * (ALTO_ITEM + 1);
        bool seleccionado = (i == _ofertaActual);
        _renderizarItemOferta(_ofertasFiltradas[i], filaItem, seleccionado);
    }
}

// Renderizar item individual de oferta
inline void GestionarOfertasScreen::_renderizarItemOferta(const OfertaGestionada& oferta, int fila, bool seleccionado)
{
    if (seleccionado) {
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::AZUL_MARCA);
    } else {
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    }
    
    // Línea 1: Código, contenido y descuento
    gotoXY(COL_LISTA, fila);
    std::cout << std::setw(3) << oferta.id << " │ ";
    std::cout << std::left << std::setw(12) << oferta.codigoPromocional;
    std::cout << " │ " << std::setw(35) << oferta.nombreContenido.substr(0, 33);
    std::cout << " │ " << std::setw(3) << oferta.descuentoPorcentaje << "%";
    std::cout << " │ " << std::setw(10) << _formatearPrecio(oferta.precioConDescuento);
    std::cout << " │ " << std::setw(8) << oferta.estado;
    
    // Línea 2: Tipo, fechas y usos
    gotoXY(COL_LISTA, fila + 1);
    std::cout << "    │ " << std::setw(12) << oferta.tipoContenido;
    std::cout << " │ Vence: " << std::setw(10) << oferta.fechaVencimiento;
    std::cout << " │ Usos: " << std::setw(3) << oferta.usosTotal;
    std::cout << " │ Ingresos: " << _formatearPrecio(oferta.ingresoGenerado);
    
    // Línea 3: Separador
    gotoXY(COL_LISTA, fila + 2);
    std::cout << std::string(ANCHO_ITEM, '─');
    
    resetColor();
}

// Renderizar filtros
inline void GestionarOfertasScreen::_renderizarFiltros()
{
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    
    gotoXY(COL_FILTROS, FILA_FILTROS);
    std::cout << "┌── FILTROS ──┐";
    
    gotoXY(COL_FILTROS, FILA_FILTROS + 1);
    std::cout << "│ Estado:     │";
    
    gotoXY(COL_FILTROS, FILA_FILTROS + 2);
    std::cout << "│ " << std::setw(11) << _filtroEstado.substr(0, 11) << " │";
    
    gotoXY(COL_FILTROS, FILA_FILTROS + 3);
    std::cout << "│             │";
    
    gotoXY(COL_FILTROS, FILA_FILTROS + 4);
    std::cout << "│ F: Cambiar  │";
    
    gotoXY(COL_FILTROS, FILA_FILTROS + 5);
    std::cout << "└─────────────┘";
    
    resetColor();
}

// Renderizar estadísticas
inline void GestionarOfertasScreen::_renderizarEstadisticas()
{
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    
    int totalActivas = 0, totalVencidas = 0, totalPausadas = 0;
    int totalUsos = 0;
    double ingresoTotal = 0.0;
    
    for (const auto& oferta : _ofertas) {
        if (oferta.estado == "Activa") totalActivas++;
        else if (oferta.estado == "Vencida") totalVencidas++;
        else if (oferta.estado == "Pausada") totalPausadas++;
        
        totalUsos += oferta.usosTotal;
        ingresoTotal += oferta.ingresoGenerado;
    }
    
    gotoXY(10, 6);
    std::cout << "Ofertas - Activas: " << totalActivas << " │ Vencidas: " << totalVencidas 
              << " │ Pausadas: " << totalPausadas << " │ Usos totales: " << totalUsos 
              << " │ Ingresos: " << _formatearPrecio(ingresoTotal);
    
    resetColor();
}

// Renderizar navegación
inline void GestionarOfertasScreen::_renderizarNavegacion()
{
    int totalPaginas = (_ofertasFiltradas.size() + _ofertasPorPagina - 1) / _ofertasPorPagina;
    if (totalPaginas == 0) totalPaginas = 1;
    
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    
    gotoXY(COL_NAVEGACION, FILA_NAVEGACION);
    std::cout << "< ANTERIOR     [" << _paginaActual << "/" << totalPaginas << "]     SIGUIENTE >";
    
    gotoXY(COL_NAVEGACION + 50, FILA_NAVEGACION);
    std::cout << "DETALLES  EDITAR  ESTADO  DUPLICAR  ELIMINAR";
    
    resetColor();
}

// Renderizar instrucciones
inline void GestionarOfertasScreen::_renderizarInstrucciones()
{
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    
    gotoXY(0, 29);
    std::cout << std::string(120, '─');
    gotoXY(5, 30);
    std::cout << "ARRIBA/ABAJO: Navegar │ IZQUIERDA/DERECHA: Página │ ENTER: Detalles │ E: Editar │ S: Estado";
    gotoXY(5, 31);
    std::cout << "D: Duplicar │ X: Eliminar │ F: Filtro estado │ ESC: Regresar";
    
    resetColor();
}

// Navegación arriba
inline void GestionarOfertasScreen::_navegarArriba()
{
    if (_ofertaActual > 0) {
        _ofertaActual--;
        
        int paginaItem = _ofertaActual / _ofertasPorPagina + 1;
        if (paginaItem != _paginaActual) {
            _paginaActual = paginaItem;
        }
    }
}

// Navegación abajo
inline void GestionarOfertasScreen::_navegarAbajo()
{
    if (_ofertaActual < (int)_ofertasFiltradas.size() - 1) {
        _ofertaActual++;
        
        int paginaItem = _ofertaActual / _ofertasPorPagina + 1;
        if (paginaItem != _paginaActual) {
            _paginaActual = paginaItem;
        }
    }
}

// Cambiar página
inline void GestionarOfertasScreen::_cambiarPagina(int direccion)
{
    int totalPaginas = (_ofertasFiltradas.size() + _ofertasPorPagina - 1) / _ofertasPorPagina;
    if (totalPaginas == 0) totalPaginas = 1;
    
    int nuevaPagina = _paginaActual + direccion;
    if (nuevaPagina >= 1 && nuevaPagina <= totalPaginas) {
        _paginaActual = nuevaPagina;
        _ofertaActual = (_paginaActual - 1) * _ofertasPorPagina;
        
        if (_ofertaActual >= (int)_ofertasFiltradas.size()) {
            _ofertaActual = (std::max)(0, (int)_ofertasFiltradas.size() - 1);
        }
    }
}

// Cambiar filtro estado
inline void GestionarOfertasScreen::_cambiarFiltroEstado()
{
    if (_filtroEstado == "TODAS") {
        _filtroEstado = "ACTIVAS";
    } else if (_filtroEstado == "ACTIVAS") {
        _filtroEstado = "VENCIDAS";
    } else if (_filtroEstado == "VENCIDAS") {
        _filtroEstado = "PAUSADAS";
    } else {
        _filtroEstado = "TODAS";
    }
    
    _ofertaActual = 0;
    _paginaActual = 1;
}

// Aplicar filtros
inline void GestionarOfertasScreen::_aplicarFiltros()
{
    _ofertasFiltradas.clear();
    
    for (const auto& oferta : _ofertas) {
        if (_cumpleFiltros(oferta)) {
            _ofertasFiltradas.push_back(oferta);
        }
    }
    
    if (_ofertaActual >= (int)_ofertasFiltradas.size()) {
        _ofertaActual = (std::max)(0, (int)_ofertasFiltradas.size() - 1);
    }
}

// Verificar si cumple filtros
inline bool GestionarOfertasScreen::_cumpleFiltros(const OfertaGestionada& oferta)
{
    if (_filtroEstado != "TODAS") {
        if (_filtroEstado == "ACTIVAS" && oferta.estado != "Activa") return false;
        if (_filtroEstado == "VENCIDAS" && oferta.estado != "Vencida") return false;
        if (_filtroEstado == "PAUSADAS" && oferta.estado != "Pausada") return false;
    }
    
    return true;
}

// Ver detalles de la oferta
inline void GestionarOfertasScreen::_verDetallesOferta()
{
    if (_ofertasFiltradas.empty()) return;
    
    const auto& oferta = _ofertasFiltradas[_ofertaActual];
    
	system("cls");
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    
    gotoXY(40, 5);
    std::cout << "DETALLES DE LA OFERTA";
    
    gotoXY(10, 8);
    std::cout << "ID: " << oferta.id << " │ Código: " << oferta.codigoPromocional;
    
    gotoXY(10, 10);
    std::cout << "Contenido: " << oferta.nombreContenido << " (" << oferta.tipoContenido << ")";
    
    gotoXY(10, 12);
    std::cout << "Descuento: " << oferta.descuentoPorcentaje << "% │ Estado: " << oferta.estado;
    
    gotoXY(10, 14);
    std::cout << "Precio original: " << _formatearPrecio(oferta.precioOriginal);
    std::cout << " │ Precio con descuento: " << _formatearPrecio(oferta.precioConDescuento);
    
    gotoXY(10, 16);
    std::cout << "Fecha de creación: " << oferta.fechaCreacion;
    
    gotoXY(10, 18);
    std::cout << "Fecha de vencimiento: " << oferta.fechaVencimiento;
    
    gotoXY(10, 20);
    std::cout << "Usos totales: " << oferta.usosTotal << " │ Usos restantes: " << oferta.usosRestantes;
    
    gotoXY(10, 22);
    std::cout << "Ingresos generados: " << _formatearPrecio(oferta.ingresoGenerado);
    
    gotoXY(40, 26);
    std::cout << "Presiona cualquier tecla para continuar...";
    
    resetColor();
    _getch();
    _primeraRenderizacion = true;
}

// Editar oferta
inline void GestionarOfertasScreen::_editarOferta()
{
    if (_ofertasFiltradas.empty()) return;
    
	system("cls");
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    
    gotoXY(45, 10);
    std::cout << "EDITAR OFERTA";
    
    gotoXY(30, 15);
    std::cout << "Esta funcionalidad será implementada próximamente.";
    
    gotoXY(40, 20);
    std::cout << "Presiona cualquier tecla para continuar...";
    
    resetColor();
    _getch();
    _primeraRenderizacion = true;
}

// Cambiar estado de la oferta
inline void GestionarOfertasScreen::_cambiarEstadoOferta()
{
    if (_ofertasFiltradas.empty()) return;
    
    auto& oferta = _ofertasFiltradas[_ofertaActual];
    
    for (auto& original : _ofertas) {
        if (original.id == oferta.id) {
            if (original.estado == "Activa") {
                original.estado = "Pausada";
            } else if (original.estado == "Pausada") {
                original.estado = "Activa";
            }
            
            oferta.estado = original.estado;
            break;
        }
    }
    
    _aplicarFiltros();
}

// Duplicar oferta
inline void GestionarOfertasScreen::_duplicarOferta()
{
    if (_ofertasFiltradas.empty()) return;
    
	system("cls");
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    
    gotoXY(45, 10);
    std::cout << "DUPLICAR OFERTA";
    
    gotoXY(30, 15);
    std::cout << "Esta funcionalidad será implementada próximamente.";
    
    gotoXY(40, 20);
    std::cout << "Presiona cualquier tecla para continuar...";
    
    resetColor();
    _getch();
    _primeraRenderizacion = true;
}

// Eliminar oferta
inline void GestionarOfertasScreen::_eliminarOferta()
{
    if (_ofertasFiltradas.empty()) return;
    
	system("cls");
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    
    gotoXY(40, 10);
    std::cout << "CONFIRMAR ELIMINACIÓN";
    
    gotoXY(25, 15);
    std::cout << "¿Está seguro de que desea eliminar esta oferta?";
    
    gotoXY(30, 17);
    std::cout << "Esta acción no se puede deshacer.";
    
    gotoXY(35, 20);
    std::cout << "S - Confirmar │ N - Cancelar";
    
    resetColor();
    
    char confirmacion = _getch();
    if (confirmacion == 's' || confirmacion == 'S') {
        // Eliminar de la lista principal
        int idAEliminar = _ofertasFiltradas[_ofertaActual].id;
        _ofertas.erase(
            std::remove_if(_ofertas.begin(), _ofertas.end(),
                [idAEliminar](const OfertaGestionada& o) { return o.id == idAEliminar; }),
            _ofertas.end()
        );
        
        _aplicarFiltros();
        if (_ofertaActual >= (int)_ofertasFiltradas.size() && _ofertaActual > 0) {
            _ofertaActual--;
        }
    }
    
    _primeraRenderizacion = true;
}

// Formatear precio
inline std::string GestionarOfertasScreen::_formatearPrecio(double precio)
{
    std::ostringstream oss;
    oss << "S/ " << std::fixed << std::setprecision(2) << precio;
    return oss.str();
}

// Formatear fecha
inline std::string GestionarOfertasScreen::_formatearFecha(const std::string& fecha)
{
    return fecha; // Por ahora devolver tal como está
}

// Obtener color del estado
inline std::string GestionarOfertasScreen::_obtenerColorEstado(const std::string& estado)
{
    if (estado == "Activa") return "VERDE";
    if (estado == "Vencida") return "ROJO";
    if (estado == "Pausada") return "AMARILLO";
    return "GRIS";
}

// Verificar si está vencida
inline bool GestionarOfertasScreen::_estaVencida(const std::string& fechaVencimiento)
{
    // Implementación básica - en producción se compararía con la fecha actual
    return false;
}

#endif // COURSERACLONE_SCREENS_GESTIONAROFERTASSCREEN_HPP
