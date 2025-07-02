#ifndef COURSERACLONE_SCREENS_CREAROFERTASCREEN_HPP
#define COURSERACLONE_SCREENS_CREAROFERTASCREEN_HPP

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
#include "../Types/ActividadTypes.hpp"

/// Pantalla para crear nueva oferta promocional
class CrearOfertaScreen : public PantallaBase
{
private:
    // Estado de navegación
    AccionPantalla _pantallaAnterior;
    bool _primeraRenderizacion;
    
    // Datos de la oferta
    struct DatosOferta {
        int idContenido;
        std::string nombreContenido;
        std::string codigoPromocional;
        int descuentoPorcentaje;
        std::string fechaVencimiento;
        double precioOriginal;
        double precioConDescuento;
    };
    
    DatosOferta _oferta;
    
    // Constantes para la interfaz (basadas en el UI)
    static const int COL_ID_CONTENT = 20;
    static const int FILA_ID_CONTENT = 11;
    static const int COL_NOMBRE_CONTENT = 45;
    static const int FILA_NOMBRE_CONTENT = 11;
    
    static const int COL_CODIGO_PROMO = 20;
    static const int FILA_CODIGO_PROMO = 17;
    static const int COL_DESCUENTO = 50;
    static const int FILA_DESCUENTO = 17;
    static const int COL_FECHA_VENC = 80;
    static const int FILA_FECHA_VENC = 17;
    
    static const int COL_PRECIO_ORIG = 20;
    static const int FILA_PRECIO_ORIG = 22;
    static const int COL_PRECIO_DESC = 60;
    static const int FILA_PRECIO_DESC = 22;
    
    static const int COL_BOTON_CREAR = 519;
    static const int FILA_BOTON_CREAR = 26;
    
    // ---- MÉTODOS PRIVADOS ----
    
    /// @brief Métodos de inicialización
    inline void _limpiarEstado();
    
    /// @brief Métodos de renderizado
    inline void dibujarInterfazCompleta();
    inline void _renderizarFormulario();
    
    /// @brief Métodos de procesamiento
    inline ResultadoPantalla _procesarFormulario();
    inline bool _validarDatos();
    inline void _calcularPrecioConDescuento();
    
    /// @brief Métodos de entrada
    inline std::string _solicitarTexto(int col, int fila, int maxLength);
    inline int _solicitarNumero(int col, int fila, int min, int max);
    inline double _solicitarDecimal(int col, int fila, double min, double max);
    
    /// @brief Métodos de utilidad
    inline void _mostrarMensaje(const std::string& mensaje);
    inline void _mostrarExito();

public:
    inline CrearOfertaScreen(AccionPantalla pantallaAnterior = AccionPantalla::IR_A_DASHBOARD_ORGANIZACION);
    
    inline ~CrearOfertaScreen() = default;

    inline ResultadoPantalla ejecutar() override;
};

// --- IMPLEMENTACIONES INLINE ---

// Constructor
inline CrearOfertaScreen::CrearOfertaScreen(AccionPantalla pantallaAnterior) : PantallaBase(),
    _pantallaAnterior(pantallaAnterior), _primeraRenderizacion(true)
{
    _limpiarEstado();
}

// Limpiar estado
inline void CrearOfertaScreen::_limpiarEstado()
{
    _oferta = DatosOferta();
    _primeraRenderizacion = true;
}

// Dibujar interfaz completa
inline void CrearOfertaScreen::dibujarInterfazCompleta()
{
    system("cls");
    UI_CrearOferta();
    
    _renderizarFormulario();
    
    resetColor();
}

// Renderizar formulario
inline void CrearOfertaScreen::_renderizarFormulario()
{
    // El UI ya está dibujado, solo agregamos las instrucciones
    gotoXY(10, 30);
    setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Completa los campos y presiona TAB para navegar. ENTER para crear oferta. ESC para volver.";
    resetColor();
}

// Procesar formulario
inline ResultadoPantalla CrearOfertaScreen::_procesarFormulario()
{
    try {
        // Solicitar ID del contenido
        gotoXY(COL_ID_CONTENT, FILA_ID_CONTENT);
        setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "> ";
        resetColor();
        
        std::string idStr;
        std::getline(std::cin, idStr);
        _oferta.idContenido = std::stoi(idStr);
        
        // Solicitar nombre del contenido
        gotoXY(COL_NOMBRE_CONTENT, FILA_NOMBRE_CONTENT);
        setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "> ";
        resetColor();
        std::getline(std::cin, _oferta.nombreContenido);
        
        // Solicitar código promocional
        gotoXY(COL_CODIGO_PROMO, FILA_CODIGO_PROMO);
        setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "> ";
        resetColor();
        std::getline(std::cin, _oferta.codigoPromocional);
        
        // Solicitar descuento
        gotoXY(COL_DESCUENTO, FILA_DESCUENTO);
        setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "> ";
        resetColor();
        
        std::string descStr;
        std::getline(std::cin, descStr);
        _oferta.descuentoPorcentaje = std::stoi(descStr);
        
        // Solicitar fecha de vencimiento
        gotoXY(COL_FECHA_VENC, FILA_FECHA_VENC);
        setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "> ";
        resetColor();
        std::getline(std::cin, _oferta.fechaVencimiento);
        
        // Solicitar precio original
        gotoXY(COL_PRECIO_ORIG, FILA_PRECIO_ORIG);
        setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "> ";
        resetColor();
        
        std::string precioStr;
        std::getline(std::cin, precioStr);
        _oferta.precioOriginal = std::stod(precioStr);
        
        // Calcular precio con descuento
        _calcularPrecioConDescuento();
        
        // Mostrar precio calculado
        gotoXY(COL_PRECIO_DESC, FILA_PRECIO_DESC);
        setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
        std::cout << std::fixed << std::setprecision(2) << _oferta.precioConDescuento;
        resetColor();
        
        if (_validarDatos()) {
            _mostrarExito();
            return ResultadoPantalla{_pantallaAnterior};
        } else {
            _mostrarMensaje("Datos inválidos. Revise los campos.");
        }
        
    } catch (const std::exception& e) {
        _mostrarMensaje("Error en los datos ingresados.");
    }
    
    return ResultadoPantalla{AccionPantalla::NINGUNA};
}

// Validar datos
inline bool CrearOfertaScreen::_validarDatos()
{
    if (_oferta.idContenido <= 0) return false;
    if (_oferta.nombreContenido.empty()) return false;
    if (_oferta.codigoPromocional.empty()) return false;
    if (_oferta.descuentoPorcentaje < 1 || _oferta.descuentoPorcentaje > 100) return false;
    if (_oferta.fechaVencimiento.empty()) return false;
    if (_oferta.precioOriginal <= 0) return false;
    
    return true;
}

// Calcular precio con descuento
inline void CrearOfertaScreen::_calcularPrecioConDescuento()
{
    double descuento = (_oferta.precioOriginal * _oferta.descuentoPorcentaje) / 100.0;
    _oferta.precioConDescuento = _oferta.precioOriginal - descuento;
}

// Mostrar mensaje
inline void CrearOfertaScreen::_mostrarMensaje(const std::string& mensaje)
{
    gotoXY(10, 28);
    setConsoleColor(ColorIndex::ERROR_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << mensaje;
    resetColor();
    
    gotoXY(10, 29);
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Presiona cualquier tecla para continuar...";
    resetColor();
    
    _getch();
}

// Mostrar éxito
inline void CrearOfertaScreen::_mostrarExito()
{
    system("cls");
    
    gotoXY(40, 10);
    setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "OFERTA CREADA EXITOSAMENTE";
    
    gotoXY(20, 12);
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Código promocional: " << _oferta.codigoPromocional;
    
    gotoXY(20, 13);
    std::cout << "Contenido: " << _oferta.nombreContenido;
    
    gotoXY(20, 14);
    std::cout << "Descuento: " << _oferta.descuentoPorcentaje << "%";
    
    gotoXY(20, 15);
    std::cout << "Precio original: S/ " << std::fixed << std::setprecision(2) << _oferta.precioOriginal;
    
    gotoXY(20, 16);
    setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Precio con descuento: S/ " << std::fixed << std::setprecision(2) << _oferta.precioConDescuento;
    
    gotoXY(20, 18);
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Válido hasta: " << _oferta.fechaVencimiento;
    
    gotoXY(20, 21);
    setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
    std::cout << " Presiona cualquier tecla para volver ";
    resetColor();
    
    _getch();
}

// Método principal de ejecución
inline ResultadoPantalla CrearOfertaScreen::ejecutar()
{
    _limpiarEstado();
    
    while (true) {
        if (_primeraRenderizacion) {
            dibujarInterfazCompleta();
            _primeraRenderizacion = false;
        }
        
        int tecla = _getch();
        
        switch (tecla) {
        case 13: // Enter - Procesar formulario
        {
            ResultadoPantalla res = _procesarFormulario();
            if (res.accion != AccionPantalla::NINGUNA) {
                return res;
            }
            _primeraRenderizacion = true;
        }
        break;
        
        case 27: // ESC - Volver a pantalla anterior
        {
            ResultadoPantalla res;
            res.accion = _pantallaAnterior;
            return res;
        }
        
        default:
            // Para otras teclas, iniciar el formulario
            ResultadoPantalla res = _procesarFormulario();
            if (res.accion != AccionPantalla::NINGUNA) {
                return res;
            }
            _primeraRenderizacion = true;
            break;
        }
    }
}

#endif // COURSERACLONE_SCREENS_CREAROFERTASCREEN_HPP
