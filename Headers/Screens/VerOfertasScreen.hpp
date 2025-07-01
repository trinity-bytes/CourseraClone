#ifndef COURSERACLONE_SCREENS_VEROFERTASSCREEN_HPP
#define COURSERACLONE_SCREENS_VEROFERTASSCREEN_HPP

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
#include "../Types/ActividadTypes.hpp"

/// Pantalla para ver ofertas destacadas y promociones activas
class VerOfertasScreen : public PantallaBase
{
private:
    // Estado de navegación
    AccionPantalla _pantallaAnterior;
    bool _primeraRenderizacion;
    
    // Navegación y selección
    int _ofertaSeleccionada;
    int _filtroSeleccionado;
    enum class ModoDeFocus {
        OFERTAS_DESTACADAS = 0,
        FILTROS = 1
    };
    ModoDeFocus _modoFocus;
    
    // Datos de ofertas
    struct OfertaDestacada {
        std::string titulo;
        std::string descripcion;
        double precioAntes;
        double precioAhora;
        std::string codigo;
        int descuentoPorcentaje;
        std::string categoria;
        std::string fechaVencimiento;
    };
    
    struct PromociActiva {
        std::string curso;
        double precioAntes;
        double precioAhora;
        std::string fechaVencimiento;
    };
    
    std::vector<OfertaDestacada> _ofertasDestacadas;
    std::vector<PromociActiva> _promocionesActivas;
    
    // Constantes para la interfaz
    static const int COL_OFERTAS_DESTACADAS = 15;
    static const int FILA_OFERTAS_DESTACADAS = 8;
    static const int ANCHO_OFERTA = 30;
    static const int ALTO_OFERTA = 12;
    
    static const int COL_PROMOCIONES = 15;
    static const int FILA_PROMOCIONES = 22;
    
    static const int COL_FILTROS = 100;
    static const int FILA_FILTROS = 8;
    
    // Filtros disponibles
    enum class TipoFiltro {
        CATEGORIA_TODAS = 0,
        CATEGORIA_TECNOLOGIA = 1,
        CATEGORIA_NEGOCIOS = 2,
        CATEGORIA_DISENO = 3,
        CATEGORIA_CIENCIAS = 4,
        DESCUENTO_TODOS = 5,
        DESCUENTO_30 = 6,
        DESCUENTO_50 = 7,
        DESCUENTO_70 = 8,
        PRECIO_TODOS = 9,
        PRECIO_50 = 10,
        PRECIO_100 = 11,
        PRECIO_200 = 12
    };
    
    // ---- MÉTODOS PRIVADOS ----
    
    /// @brief Métodos de inicialización
    inline void _limpiarEstado();
    inline void _cargarOfertasEjemplo();
    
    /// @brief Métodos de renderizado
    inline void dibujarInterfazCompleta();
    inline void _renderizarOfertasDestacadas();
    inline void _renderizarPromociones();
    inline void _renderizarFiltros();
    inline void _renderizarInstrucciones();
    inline void _actualizarSeleccion();
    
    /// @brief Métodos de navegación
    inline void _manejarNavegacion(int tecla);
    inline void _navegarArriba();
    inline void _navegarAbajo();
    inline void _navegarIzquierda();
    inline void _navegarDerecha();
    
    /// @brief Métodos de procesamiento
    inline ResultadoPantalla _procesarSeleccion();
    inline void _aplicarFiltros();
    
    /// @brief Métodos de utilidad
    inline std::string _formatearPrecio(double precio);

public:
    inline VerOfertasScreen(AccionPantalla pantallaAnterior = AccionPantalla::IR_A_LANDING_PAGE);
    
    inline ~VerOfertasScreen() = default;

    inline ResultadoPantalla ejecutar() override;
};

// --- IMPLEMENTACIONES INLINE ---

// Constructor
inline VerOfertasScreen::VerOfertasScreen(AccionPantalla pantallaAnterior) : PantallaBase(),
    _pantallaAnterior(pantallaAnterior), _primeraRenderizacion(true), 
    _ofertaSeleccionada(0), _filtroSeleccionado(0), _modoFocus(ModoDeFocus::OFERTAS_DESTACADAS)
{
    _cargarOfertasEjemplo();
}

// Limpiar estado
inline void VerOfertasScreen::_limpiarEstado()
{
    _ofertaSeleccionada = 0;
    _filtroSeleccionado = 0;
    _modoFocus = ModoDeFocus::OFERTAS_DESTACADAS;
    _primeraRenderizacion = true;
}

// Cargar ofertas de ejemplo
inline void VerOfertasScreen::_cargarOfertasEjemplo()
{
    _ofertasDestacadas.clear();
    _promocionesActivas.clear();
    
    // Ofertas destacadas (como en la imagen)
    _ofertasDestacadas.push_back({
        "MEGA OFERTA ESTUDIANTES",
        "50% OFF en todos los cursos\nSolo por tiempo limitado!",
        150.0, 75.0, "STUDENT50", 50, "TODAS", "30/06/2025"
    });
    
    _ofertasDestacadas.push_back({
        "PACK DESARROLLADOR WEB",
        "3 cursos + certificacion\nHTML, CSS, JavaScript",
        300.0, 199.0, "WEBDEV2025", 33, "TECNOLOGIA", "15/07/2025"
    });
    
    _ofertasDestacadas.push_back({
        "ESPECIALIZACION DATA",
        "Machine Learning + Python\n4 especialidades por S/99",
        250.0, 99.0, "DATAAI99", 60, "CIENCIAS", "25/06/2025"
    });
    
    // Promociones activas (lista de la imagen)
    _promocionesActivas.push_back({"Python Basico", 80.0, 49.0, "30/06/2025"});
    _promocionesActivas.push_back({"Especializacion Marketing Digital", 200.0, 149.0, "15/07/2025"});
    _promocionesActivas.push_back({"Pack Diseno UX/UI Completo", 180.0, 120.0, "25/06/2025"});
    _promocionesActivas.push_back({"Analisis de Datos con R", 120.0, 89.0, "28/06/2025"});
    _promocionesActivas.push_back({"Especializacion Ciberseguridad", 250.0, 175.0, "10/07/2025"});
    _promocionesActivas.push_back({"Fundamentos de IA", 90.0, 59.0, "05/07/2025"});
}

// Dibujar interfaz completa
inline void VerOfertasScreen::dibujarInterfazCompleta()
{
    system("cls");
    UI_Ofertas();
    
    _renderizarOfertasDestacadas();
    _renderizarPromociones();
    _renderizarFiltros();
    _renderizarInstrucciones();
    
    resetColor();
}

// Renderizar ofertas destacadas
inline void VerOfertasScreen::_renderizarOfertasDestacadas()
{
    for (size_t i = 0; i < _ofertasDestacadas.size() && i < 3; ++i) {
        const auto& oferta = _ofertasDestacadas[i];
        int col = COL_OFERTAS_DESTACADAS + (i * 32);
        int fila = FILA_OFERTAS_DESTACADAS;
        
        // Destacar si está seleccionada y estamos en modo ofertas
        if (i == _ofertaSeleccionada && _modoFocus == ModoDeFocus::OFERTAS_DESTACADAS) {
            setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
        } else {
            setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        }
        
        // Título de la oferta
        gotoXY(col + 2, fila + 1);
        std::cout << oferta.titulo;
        
        // Descripción (máximo 2 líneas)
        gotoXY(col + 2, fila + 3);
        std::string desc1 = oferta.descripcion.substr(0, 28);
        std::cout << desc1;
        
        if (oferta.descripcion.length() > 28) {
            gotoXY(col + 2, fila + 4);
            std::string desc2 = oferta.descripcion.substr(28, 28);
            std::cout << desc2;
        }
        
        // Precios
        gotoXY(col + 2, fila + 6);
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "Antes: " << _formatearPrecio(oferta.precioAntes);
        
        gotoXY(col + 15, fila + 6);
        setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "Ahora: " << _formatearPrecio(oferta.precioAhora);
        
        // Descuento
        gotoXY(col + 2, fila + 7);
        setConsoleColor(ColorIndex::ERROR_COLOR, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "-" << oferta.descuentoPorcentaje << "% OFF";
        
        // Código promocional
        gotoXY(col + 2, fila + 9);
        setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "Codigo: " << oferta.codigo;
        
        resetColor();
    }
}

// Renderizar promociones
inline void VerOfertasScreen::_renderizarPromociones()
{
    gotoXY(COL_PROMOCIONES, FILA_PROMOCIONES - 1);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "LISTA DE PROMOCIONES ACTIVAS";
    resetColor();
    
    for (size_t i = 0; i < _promocionesActivas.size(); ++i) {
        const auto& promo = _promocionesActivas[i];
        int fila = FILA_PROMOCIONES + 1 + i;
        
        gotoXY(COL_PROMOCIONES, fila);
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << promo.curso;
        
        gotoXY(COL_PROMOCIONES + 35, fila);
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << _formatearPrecio(promo.precioAntes) << " -> ";
        
        setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
        std::cout << _formatearPrecio(promo.precioAhora);
        
        gotoXY(COL_PROMOCIONES + 55, fila);
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "Valido hasta: " << promo.fechaVencimiento;
        
        resetColor();
    }
}

// Renderizar filtros
inline void VerOfertasScreen::_renderizarFiltros()
{
    gotoXY(COL_FILTROS, FILA_FILTROS - 1);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "FILTRAR OFERTAS";
    resetColor();
    
    std::vector<std::string> categorias = {"TODAS", "TECNOLOGIA", "NEGOCIOS", "DISENO", "CIENCIAS"};
    std::vector<std::string> descuentos = {"TODOS", ">30%", ">50%", ">70%"};
    std::vector<std::string> precios = {"TODOS", "<S/50", "<S/100", "<S/200"};
    
    // Categorías
    gotoXY(COL_FILTROS, FILA_FILTROS + 1);
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Categoria:";
    
    for (size_t i = 0; i < categorias.size(); ++i) {
        gotoXY(COL_FILTROS + 2, FILA_FILTROS + 2 + i);
        if (_modoFocus == ModoDeFocus::FILTROS && _filtroSeleccionado == i) {
            setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
        } else {
            setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        }
        std::cout << "- " << categorias[i];
        resetColor();
    }
    
    // Descuentos
    gotoXY(COL_FILTROS, FILA_FILTROS + 8);
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Descuento:";
    
    for (size_t i = 0; i < descuentos.size(); ++i) {
        gotoXY(COL_FILTROS + 2, FILA_FILTROS + 9 + i);
        if (_modoFocus == ModoDeFocus::FILTROS && _filtroSeleccionado == (i + 5)) {
            setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
        } else {
            setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        }
        std::cout << "- " << descuentos[i];
        resetColor();
    }
    
    // Precios
    gotoXY(COL_FILTROS, FILA_FILTROS + 14);
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Precio:";
    
    for (size_t i = 0; i < precios.size(); ++i) {
        gotoXY(COL_FILTROS + 2, FILA_FILTROS + 15 + i);
        if (_modoFocus == ModoDeFocus::FILTROS && _filtroSeleccionado == (i + 9)) {
            setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
        } else {
            setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        }
        std::cout << "- " << precios[i];
        resetColor();
    }
}

// Renderizar instrucciones
inline void VerOfertasScreen::_renderizarInstrucciones()
{
    // Instrucciones en la parte inferior
    gotoXY(15, 38);
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Navegacion: ";
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "[FLECHAS] ";
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "| Seleccionar: ";
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "[ENTER] ";
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "| Alternar vista: ";
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "[TAB] ";
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "| Volver: ";
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "[ESC]";
    resetColor();
}

// Actualizar selección
inline void VerOfertasScreen::_actualizarSeleccion()
{
    _renderizarOfertasDestacadas();
    _renderizarFiltros();
    _renderizarInstrucciones();
}

// Manejar navegación
inline void VerOfertasScreen::_manejarNavegacion(int tecla)
{
    switch (tecla) {
    case 72: // Flecha arriba
        _navegarArriba();
        break;
    case 80: // Flecha abajo
        _navegarAbajo();
        break;
    case 75: // Flecha izquierda
        _navegarIzquierda();
        break;
    case 77: // Flecha derecha
        _navegarDerecha();
        break;
    }
}

// Navegar hacia arriba
inline void VerOfertasScreen::_navegarArriba()
{
    if (_modoFocus == ModoDeFocus::FILTROS) {
        if (_filtroSeleccionado > 0) {
            _filtroSeleccionado--;
        }
    }
    // En modo ofertas destacadas no se puede navegar verticalmente
}

// Navegar hacia abajo
inline void VerOfertasScreen::_navegarAbajo()
{
    if (_modoFocus == ModoDeFocus::FILTROS) {
        if (_filtroSeleccionado < 12) { // Total de filtros (5 categorías + 4 descuentos + 4 precios - 1)
            _filtroSeleccionado++;
        }
    }
    // En modo ofertas destacadas no se puede navegar verticalmente
}

// Navegar hacia la izquierda
inline void VerOfertasScreen::_navegarIzquierda()
{
    if (_modoFocus == ModoDeFocus::OFERTAS_DESTACADAS) {
        if (_ofertaSeleccionada > 0) {
            _ofertaSeleccionada--;
        }
    }
    // En modo filtros no se puede navegar horizontalmente
}

// Navegar hacia la derecha
inline void VerOfertasScreen::_navegarDerecha()
{
    if (_modoFocus == ModoDeFocus::OFERTAS_DESTACADAS) {
        if (_ofertaSeleccionada < static_cast<int>(_ofertasDestacadas.size()) - 1 && _ofertaSeleccionada < 2) {
            _ofertaSeleccionada++;
        }
    }
    // En modo filtros no se puede navegar horizontalmente
}

// Procesar selección
inline ResultadoPantalla VerOfertasScreen::_procesarSeleccion()
{
    // Mostrar detalles de la oferta seleccionada
    const auto& oferta = _ofertasDestacadas[_ofertaSeleccionada];
    
    system("cls");
    gotoXY(30, 10);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "DETALLES DE LA OFERTA";
    
    gotoXY(20, 12);
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Titulo: " << oferta.titulo;
    
    gotoXY(20, 13);
    std::cout << "Descripcion: " << oferta.descripcion;
    
    gotoXY(20, 14);
    std::cout << "Precio original: " << _formatearPrecio(oferta.precioAntes);
    
    gotoXY(20, 15);
    setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Precio con descuento: " << _formatearPrecio(oferta.precioAhora);
    
    gotoXY(20, 16);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Codigo promocional: " << oferta.codigo;
    
    gotoXY(20, 17);
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Valido hasta: " << oferta.fechaVencimiento;
    
    gotoXY(20, 20);
    setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
    std::cout << " Presiona cualquier tecla para volver ";
    resetColor();
    
    _getch();
    _primeraRenderizacion = true;
    
    return ResultadoPantalla{AccionPantalla::NINGUNA};
}

// Aplicar filtros
inline void VerOfertasScreen::_aplicarFiltros()
{
    // Implementación básica de filtros
    // En una implementación completa, esto filtrarían las ofertas según los criterios seleccionados
    std::string filtroAplicado = "";
    
    if (_filtroSeleccionado >= 0 && _filtroSeleccionado <= 4) {
        std::vector<std::string> categorias = {"TODAS", "TECNOLOGIA", "NEGOCIOS", "DISENO", "CIENCIAS"};
        filtroAplicado = "Categoria: " + categorias[_filtroSeleccionado];
    }
    else if (_filtroSeleccionado >= 5 && _filtroSeleccionado <= 8) {
        std::vector<std::string> descuentos = {"TODOS", ">30%", ">50%", ">70%"};
        filtroAplicado = "Descuento: " + descuentos[_filtroSeleccionado - 5];
    }
    else if (_filtroSeleccionado >= 9 && _filtroSeleccionado <= 12) {
        std::vector<std::string> precios = {"TODOS", "<S/50", "<S/100", "<S/200"};
        filtroAplicado = "Precio: " + precios[_filtroSeleccionado - 9];
    }
    
    // Mostrar confirmación de filtro aplicado
    gotoXY(COL_FILTROS, FILA_FILTROS + 20);
    setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Filtro aplicado: " << filtroAplicado;
    resetColor();
}

// Formatear precio
inline std::string VerOfertasScreen::_formatearPrecio(double precio)
{
    std::ostringstream oss;
    oss << "S/" << std::fixed << std::setprecision(0) << precio;
    return oss.str();
}

// Método principal de ejecución
inline ResultadoPantalla VerOfertasScreen::ejecutar()
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
        case 75: // Flecha izquierda (por si acaso)
        case 77: // Flecha derecha (por si acaso)
            _manejarNavegacion(tecla);
            break;
            
        case 9: // TAB - Alternar entre ofertas y filtros
            if (_modoFocus == ModoDeFocus::OFERTAS_DESTACADAS) {
                _modoFocus = ModoDeFocus::FILTROS;
                _ofertaSeleccionada = 0;
            } else {
                _modoFocus = ModoDeFocus::OFERTAS_DESTACADAS;
                _filtroSeleccionado = 0;
            }
            break;
            
        case 13: // Enter
        {
            if (_modoFocus == ModoDeFocus::OFERTAS_DESTACADAS) {
                // Ver detalles de la oferta
                ResultadoPantalla res = _procesarSeleccion();
                if (res.accion != AccionPantalla::NINGUNA) {
                    return res;
                }
            } else {
                // Aplicar filtro seleccionado
                _aplicarFiltros();
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

#endif // COURSERACLONE_SCREENS_VEROFERTASSCREEN_HPP
