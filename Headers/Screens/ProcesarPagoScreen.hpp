#ifndef COURSERACLONE_SCREENS_PROCESARPAGOSCREEN_HPP
#define COURSERACLONE_SCREENS_PROCESARPAGOSCREEN_HPP

// Headers estándar
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <conio.h>
#include <limits>
#include <random>

// Headers propios
#include "../Utils/SystemUtils.hpp"
#include "../Utils/ScreenSystem.hpp"
#include "../Utils/UI_Ascii.hpp"
#include "../Utils/InputUtils.hpp"
#include "../Utils/ValidationUtils.hpp"
#include "../Types/UsuarioTypes.hpp"

/// Pantalla para procesar el pago de cursos o especializaciones
class ProcesarPagoScreen : public PantallaBase
{
private:
    // Estado de navegación
    AccionPantalla _pantallaAnterior;
    bool _primeraRenderizacion;
    
    // Estados del proceso de pago
    enum class EstadoPago {
        SELECCION_METODO = 0,
        CONFIRMACION = 1,
        PROCESANDO = 2,
        COMPLETADO = 3,
        ERROR_PAGO = 4
    };
    
    EstadoPago _estadoActual;
    int _metodoSeleccionado;
    bool _procesandoPago;
    
    // Datos del item a comprar
    struct ItemCompra {
        std::string nombre;
        std::string tipo; // "Curso" o "Especialización"
        double precio;
        std::string codigoDescuento;
        double descuentoAplicado;
        double precioFinal;
        std::string instructor;
        std::string duracion;
    };
    
    // Métodos de pago disponibles (simulados)
    struct MetodoPago {
        std::string tipo;
        std::string numero;
        std::string titular;
        std::string banco;
        bool esPrincipal;
    };
    
    ItemCompra _itemCompra;
    std::vector<MetodoPago> _metodosPago;
    std::string _numeroTransaccion;
    
    // Constantes para la interfaz
    static const int COL_ITEM_INFO = 20;
    static const int FILA_ITEM_INFO = 10;
    
    static const int COL_METODOS = 20;
    static const int FILA_METODOS = 18;
    
    static const int COL_RESUMEN = 60;
    static const int FILA_RESUMEN = 18;
    
    static const int COL_BOTONES = 30;
    static const int FILA_BOTONES = 30;
    
    // ---- MÉTODOS PRIVADOS ----
    
    /// @brief Métodos de inicialización
    inline void _limpiarEstado();
    inline void _cargarDatosEjemplo();
    inline void _cargarMetodosPagoEjemplo();
    
    /// @brief Métodos de renderizado
    inline void dibujarInterfazCompleta();
    inline void _renderizarInformacionItem();
    inline void _renderizarMetodosPago();
    inline void _renderizarResumenPago();
    inline void _renderizarConfirmacion();
    inline void _renderizarProcesando();
    inline void _renderizarCompletado();
    inline void _renderizarError();
    inline void _renderizarInstrucciones();
    
    /// @brief Métodos de procesamiento
    inline ResultadoPantalla _procesarPago();
    inline void _navegarMetodos(int direccion);
    inline void _aplicarDescuento();
    inline void _calcularPrecioFinal();
    
    /// @brief Métodos de utilidad
    inline std::string _formatearPrecio(double precio);
    inline std::string _generarNumeroTransaccion();
    inline void _simularProcesamiento();

public:
    inline ProcesarPagoScreen(AccionPantalla pantallaAnterior = AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE);
    
    inline ~ProcesarPagoScreen() = default;

    inline ResultadoPantalla ejecutar() override;
};

// --- IMPLEMENTACIONES INLINE ---

// Constructor
inline ProcesarPagoScreen::ProcesarPagoScreen(AccionPantalla pantallaAnterior) : PantallaBase(),
    _pantallaAnterior(pantallaAnterior), _primeraRenderizacion(true), 
    _estadoActual(EstadoPago::SELECCION_METODO), _metodoSeleccionado(0), _procesandoPago(false)
{
    _cargarDatosEjemplo();
    _cargarMetodosPagoEjemplo();
}

// Limpiar estado
inline void ProcesarPagoScreen::_limpiarEstado()
{
    _estadoActual = EstadoPago::SELECCION_METODO;
    _metodoSeleccionado = 0;
    _procesandoPago = false;
    _numeroTransaccion = "";
    _primeraRenderizacion = true;
}

// Cargar datos de ejemplo
inline void ProcesarPagoScreen::_cargarDatosEjemplo()
{
    _itemCompra = {
        "Fundamentos de Python para Data Science",
        "Curso",
        99.0,
        "",
        0.0,
        99.0,
        "Dr. Ana Rodriguez",
        "6 semanas"
    };
    
    _calcularPrecioFinal();
}

// Cargar métodos de pago de ejemplo
inline void ProcesarPagoScreen::_cargarMetodosPagoEjemplo()
{
    _metodosPago.clear();
    
    _metodosPago.push_back({
        "Tarjeta de Credito",
        "****-****-****-1234",
        "Juan Perez",
        "Banco Continental",
        true
    });
    
    _metodosPago.push_back({
        "Tarjeta de Debito",
        "****-****-****-5678",
        "Juan Perez",
        "Interbank",
        false
    });
    
    _metodosPago.push_back({
        "Transferencia Bancaria",
        "Cuenta: ****-****-9012",
        "Juan Perez",
        "BCP",
        false
    });
    
    _metodosPago.push_back({
        "Billetera Digital",
        "juan.perez@email.com",
        "Juan Perez",
        "Yape",
        false
    });
}

// Dibujar interfaz completa
inline void ProcesarPagoScreen::dibujarInterfazCompleta()
{
    system("cls");
    UI_ProcesarPago();
    
    switch (_estadoActual) {
    case EstadoPago::SELECCION_METODO:
        _renderizarInformacionItem();
        _renderizarMetodosPago();
        _renderizarResumenPago();
        break;
    case EstadoPago::CONFIRMACION:
        _renderizarConfirmacion();
        break;
    case EstadoPago::PROCESANDO:
        _renderizarProcesando();
        break;
    case EstadoPago::COMPLETADO:
        _renderizarCompletado();
        break;
    case EstadoPago::ERROR_PAGO:
        _renderizarError();
        break;
    }
    
    _renderizarInstrucciones();
    resetColor();
}

// Renderizar información del item
inline void ProcesarPagoScreen::_renderizarInformacionItem()
{
    gotoXY(COL_ITEM_INFO, FILA_ITEM_INFO - 1);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "ITEM A COMPRAR:";
    resetColor();
    
    gotoXY(COL_ITEM_INFO, FILA_ITEM_INFO);
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << _itemCompra.tipo << ": " << _itemCompra.nombre;
    
    gotoXY(COL_ITEM_INFO, FILA_ITEM_INFO + 1);
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Instructor: " << _itemCompra.instructor;
    
    gotoXY(COL_ITEM_INFO, FILA_ITEM_INFO + 2);
    std::cout << "Duracion: " << _itemCompra.duracion;
    
    gotoXY(COL_ITEM_INFO, FILA_ITEM_INFO + 3);
    setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Precio: " << _formatearPrecio(_itemCompra.precio);
    
    resetColor();
}

// Renderizar métodos de pago
inline void ProcesarPagoScreen::_renderizarMetodosPago()
{
    gotoXY(COL_METODOS, FILA_METODOS - 1);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "SELECCIONAR METODO DE PAGO:";
    resetColor();
    
    for (size_t i = 0; i < _metodosPago.size(); ++i) {
        const auto& metodo = _metodosPago[i];
        int fila = FILA_METODOS + i;
        
        gotoXY(COL_METODOS, fila);
        if (i == _metodoSeleccionado) {
            setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
            std::cout << "> ";
        } else {
            setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
            std::cout << "  ";
        }
        
        std::cout << metodo.tipo << " - " << metodo.numero;
        
        if (metodo.esPrincipal) {
            setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
            std::cout << " (Principal)";
        }
        
        gotoXY(COL_METODOS + 2, fila + 1);
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << metodo.titular << " - " << metodo.banco;
        
        resetColor();
    }
}

// Renderizar resumen de pago
inline void ProcesarPagoScreen::_renderizarResumenPago()
{
    gotoXY(COL_RESUMEN, FILA_RESUMEN - 1);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "RESUMEN DE PAGO:";
    resetColor();
    
    gotoXY(COL_RESUMEN, FILA_RESUMEN);
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Subtotal: " << _formatearPrecio(_itemCompra.precio);
    
    if (_itemCompra.descuentoAplicado > 0) {
        gotoXY(COL_RESUMEN, FILA_RESUMEN + 1);
        setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "Descuento: -" << _formatearPrecio(_itemCompra.descuentoAplicado);
        
        gotoXY(COL_RESUMEN, FILA_RESUMEN + 2);
        std::cout << "Codigo: " << _itemCompra.codigoDescuento;
    }
    
    // Línea separadora
    gotoXY(COL_RESUMEN, FILA_RESUMEN + 3);
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "------------------------";
    
    gotoXY(COL_RESUMEN, FILA_RESUMEN + 4);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "TOTAL: " << _formatearPrecio(_itemCompra.precioFinal);
    
    resetColor();
}

// Renderizar confirmación
inline void ProcesarPagoScreen::_renderizarConfirmacion()
{
    gotoXY(40, 12);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "CONFIRMAR PAGO";
    
    gotoXY(20, 15);
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Item: " << _itemCompra.nombre;
    
    gotoXY(20, 16);
    std::cout << "Precio: " << _formatearPrecio(_itemCompra.precioFinal);
    
    gotoXY(20, 17);
    std::cout << "Metodo: " << _metodosPago[_metodoSeleccionado].tipo;
    
    gotoXY(20, 18);
    std::cout << "Numero: " << _metodosPago[_metodoSeleccionado].numero;
    
    gotoXY(30, 22);
    setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
    std::cout << " [ENTER] CONFIRMAR PAGO ";
    
    gotoXY(30, 24);
    setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::ERROR_COLOR);
    std::cout << " [ESC] CANCELAR ";
    
    resetColor();
}

// Renderizar procesando
inline void ProcesarPagoScreen::_renderizarProcesando()
{
    gotoXY(35, 15);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "PROCESANDO PAGO...";
    
    gotoXY(30, 18);
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Por favor espere mientras procesamos";
    
    gotoXY(35, 19);
    std::cout << "su transaccion...";
    
    gotoXY(40, 22);
    setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "[ * * * ]";
    
    resetColor();
}

// Renderizar completado
inline void ProcesarPagoScreen::_renderizarCompletado()
{
    gotoXY(35, 10);
    setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "PAGO COMPLETADO EXITOSAMENTE";
    
    gotoXY(20, 13);
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Numero de transaccion: " << _numeroTransaccion;
    
    gotoXY(20, 15);
    std::cout << "Item comprado: " << _itemCompra.nombre;
    
    gotoXY(20, 16);
    std::cout << "Precio pagado: " << _formatearPrecio(_itemCompra.precioFinal);
    
    gotoXY(20, 17);
    std::cout << "Metodo de pago: " << _metodosPago[_metodoSeleccionado].tipo;
    
    gotoXY(20, 19);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "El contenido ya esta disponible en tu dashboard!";
    
    gotoXY(20, 22);
    setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
    std::cout << " Presiona cualquier tecla para continuar ";
    
    resetColor();
}

// Renderizar error
inline void ProcesarPagoScreen::_renderizarError()
{
    gotoXY(35, 12);
    setConsoleColor(ColorIndex::ERROR_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "ERROR EN EL PAGO";
    
    gotoXY(20, 15);
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Ha ocurrido un error al procesar el pago.";
    
    gotoXY(20, 16);
    std::cout << "Por favor verifique sus datos e intente nuevamente.";
    
    gotoXY(20, 19);
    setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
    std::cout << " [ENTER] REINTENTAR ";
    
    gotoXY(20, 21);
    setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::ERROR_COLOR);
    std::cout << " [ESC] CANCELAR ";
    
    resetColor();
}

// Renderizar instrucciones
inline void ProcesarPagoScreen::_renderizarInstrucciones()
{
    if (_estadoActual == EstadoPago::SELECCION_METODO) {
        gotoXY(15, 35);
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "Navegacion: ";
        setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "[FLECHAS] ";
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "| Continuar: ";
        setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "[ENTER] ";
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "| Volver: ";
        setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "[ESC]";
        resetColor();
    }
}

// Procesar pago
inline ResultadoPantalla ProcesarPagoScreen::_procesarPago()
{
    _estadoActual = EstadoPago::PROCESANDO;
    _primeraRenderizacion = true;
    dibujarInterfazCompleta();
    
    _simularProcesamiento();
    
    // Simular éxito o fallo (90% éxito)
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10);
    
    if (dis(gen) <= 9) { // 90% éxito
        _numeroTransaccion = _generarNumeroTransaccion();
        _estadoActual = EstadoPago::COMPLETADO;
    } else { // 10% error
        _estadoActual = EstadoPago::ERROR_PAGO;
    }
    
    return ResultadoPantalla{AccionPantalla::NINGUNA};
}

// Navegar métodos
inline void ProcesarPagoScreen::_navegarMetodos(int direccion)
{
    if (direccion > 0) { // Abajo
        if (_metodoSeleccionado < static_cast<int>(_metodosPago.size()) - 1) {
            _metodoSeleccionado++;
        }
    } else { // Arriba
        if (_metodoSeleccionado > 0) {
            _metodoSeleccionado--;
        }
    }
}

// Aplicar descuento
inline void ProcesarPagoScreen::_aplicarDescuento()
{
    // Simulación de descuento
    if (_itemCompra.codigoDescuento.empty()) {
        _itemCompra.codigoDescuento = "STUDENT20";
        _itemCompra.descuentoAplicado = _itemCompra.precio * 0.20;
        _calcularPrecioFinal();
    }
}

// Calcular precio final
inline void ProcesarPagoScreen::_calcularPrecioFinal()
{
    _itemCompra.precioFinal = _itemCompra.precio - _itemCompra.descuentoAplicado;
    if (_itemCompra.precioFinal < 0) {
        _itemCompra.precioFinal = 0;
    }
}

// Formatear precio
inline std::string ProcesarPagoScreen::_formatearPrecio(double precio)
{
    std::ostringstream oss;
    oss << "S/ " << std::fixed << std::setprecision(2) << precio;
    return oss.str();
}

// Generar número de transacción
inline std::string ProcesarPagoScreen::_generarNumeroTransaccion()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000, 999999);
    
    return "TXN" + std::to_string(dis(gen));
}

// Simular procesamiento
inline void ProcesarPagoScreen::_simularProcesamiento()
{
    // Simular delay de procesamiento
    for (int i = 0; i < 30; ++i) {
        Sleep(100); // 100ms * 30 = 3 segundos
        
        // Actualizar indicador de progreso
        gotoXY(40, 22);
        setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
        switch (i % 4) {
        case 0: std::cout << "[ |   ]"; break;
        case 1: std::cout << "[ /   ]"; break;
        case 2: std::cout << "[ -   ]"; break;
        case 3: std::cout << "[ \\   ]"; break;
        }
        resetColor();
    }
}

// Método principal de ejecución
inline ResultadoPantalla ProcesarPagoScreen::ejecutar()
{
    _limpiarEstado();
    
    while (true) {
        if (_primeraRenderizacion) {
            dibujarInterfazCompleta();
            _primeraRenderizacion = false;
        }
        
        int tecla = _getch();
        
        switch (_estadoActual) {
        case EstadoPago::SELECCION_METODO:
            switch (tecla) {
            case 0:
            case 224: // Teclas especiales
            {
                int segundaTecla = _getch();
                switch (segundaTecla) {
                case 72: // Flecha arriba
                    _navegarMetodos(-1);
                    _renderizarMetodosPago();
                    break;
                case 80: // Flecha abajo
                    _navegarMetodos(1);
                    _renderizarMetodosPago();
                    break;
                }
            }
            break;
            
            case 13: // Enter - Ir a confirmación
                _estadoActual = EstadoPago::CONFIRMACION;
                _primeraRenderizacion = true;
                break;
                
            case 27: // ESC - Volver
                return ResultadoPantalla{_pantallaAnterior};
            }
            break;
            
        case EstadoPago::CONFIRMACION:
            switch (tecla) {
            case 13: // Enter - Procesar pago
            {
                ResultadoPantalla res = _procesarPago();
                _primeraRenderizacion = true;
            }
            break;
            
            case 27: // ESC - Volver a selección
                _estadoActual = EstadoPago::SELECCION_METODO;
                _primeraRenderizacion = true;
                break;
            }
            break;
            
        case EstadoPago::COMPLETADO:
            // Cualquier tecla vuelve al dashboard
            return ResultadoPantalla{_pantallaAnterior};
            
        case EstadoPago::ERROR_PAGO:
            switch (tecla) {
            case 13: // Enter - Reintentar
                _estadoActual = EstadoPago::SELECCION_METODO;
                _primeraRenderizacion = true;
                break;
                
            case 27: // ESC - Cancelar
                return ResultadoPantalla{_pantallaAnterior};
            }
            break;
            
        default:
            break;
        }
    }
}

#endif // COURSERACLONE_SCREENS_PROCESARPAGOSCREEN_HPP
