#ifndef COURSERACLONE_SCREENS_AGREGARMETODOPAGOSCREEN_HPP
#define COURSERACLONE_SCREENS_AGREGARMETODOPAGOSCREEN_HPP

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

/// Pantalla para agregar un nuevo método de pago
class AgregarMetodoPagoScreen : public PantallaBase
{
private:
    // Estado de navegación
    AccionPantalla _pantallaAnterior;
    bool _primeraRenderizacion;
    
    // Tipos de métodos de pago
    enum class TipoMetodoPago {
        TARJETA_CREDITO = 0,
        TARJETA_DEBITO = 1,
        TRANSFERENCIA_BANCARIA = 2,
        BILLETERA_DIGITAL = 3
    };
    
    // Datos del método de pago
    struct DatosMetodoPago {
        TipoMetodoPago tipo;
        std::string numeroTarjeta;
        std::string nombreTitular;
        std::string fechaVencimiento;
        std::string cvv;
        std::string nombreBanco;
        std::string correoElectronico;
        bool esMetodoPrincipal;
    };
    
    DatosMetodoPago _metodoPago;
    int _tipoSeleccionado;
    
    // Constantes para la interfaz
    static const int COL_TIPO = 20;
    static const int FILA_TIPO = 12;
    
    static const int COL_NUMERO_TARJETA = 20;
    static const int FILA_NUMERO_TARJETA = 17;
    static const int COL_NOMBRE_TITULAR = 60;
    static const int FILA_NOMBRE_TITULAR = 17;
    
    static const int COL_FECHA_VENC = 20;
    static const int FILA_FECHA_VENC = 22;
    static const int COL_CVV = 40;
    static const int FILA_CVV = 22;
    static const int COL_BANCO = 60;
    static const int FILA_BANCO = 22;
    
    static const int COL_EMAIL = 20;
    static const int FILA_EMAIL = 27;
    
    // ---- MÉTODOS PRIVADOS ----
    
    /// @brief Métodos de inicialización
    inline void _limpiarEstado();
    
    /// @brief Métodos de renderizado
    inline void dibujarInterfazCompleta();
    inline void _renderizarTiposMetodoPago();
    inline void _renderizarFormulario();
    inline void _renderizarInstrucciones();
    
    /// @brief Métodos de procesamiento
    inline ResultadoPantalla _procesarFormulario();
    inline bool _validarDatos();
    inline void _navegarTipos(int direccion);
    
    /// @brief Métodos de utilidad
    inline std::string _obtenerNombreTipo(TipoMetodoPago tipo);
    inline void _mostrarMensaje(const std::string& mensaje);
    inline void _mostrarExito();

public:
    inline AgregarMetodoPagoScreen(AccionPantalla pantallaAnterior = AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE);
    
    inline ~AgregarMetodoPagoScreen() = default;

    inline ResultadoPantalla ejecutar() override;
};

// --- IMPLEMENTACIONES INLINE ---

// Constructor
inline AgregarMetodoPagoScreen::AgregarMetodoPagoScreen(AccionPantalla pantallaAnterior) : PantallaBase(),
    _pantallaAnterior(pantallaAnterior), _primeraRenderizacion(true), _tipoSeleccionado(0)
{
    _limpiarEstado();
}

// Limpiar estado
inline void AgregarMetodoPagoScreen::_limpiarEstado()
{
    _metodoPago = DatosMetodoPago();
    _metodoPago.tipo = TipoMetodoPago::TARJETA_CREDITO;
    _metodoPago.esMetodoPrincipal = false;
    _tipoSeleccionado = 0;
    _primeraRenderizacion = true;
}

// Dibujar interfaz completa
inline void AgregarMetodoPagoScreen::dibujarInterfazCompleta()
{
    system("cls");
    UI_AgregarMetodoPago();
    
    _renderizarTiposMetodoPago();
    _renderizarFormulario();
    _renderizarInstrucciones();
    
    resetColor();
}

// Renderizar tipos de método de pago
inline void AgregarMetodoPagoScreen::_renderizarTiposMetodoPago()
{
    std::vector<std::string> tipos = {
        "Tarjeta de Credito",
        "Tarjeta de Debito", 
        "Transferencia Bancaria",
        "Billetera Digital"
    };
    
    gotoXY(COL_TIPO, FILA_TIPO - 1);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "TIPO DE METODO DE PAGO:";
    resetColor();
    
    for (size_t i = 0; i < tipos.size(); ++i) {
        gotoXY(COL_TIPO + 2, FILA_TIPO + i);
        if (i == _tipoSeleccionado) {
            setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
            std::cout << "> " << tipos[i] << " <";
        } else {
            setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
            std::cout << "  " << tipos[i];
        }
        resetColor();
    }
    
    // Actualizar el tipo seleccionado
    _metodoPago.tipo = static_cast<TipoMetodoPago>(_tipoSeleccionado);
}

// Renderizar formulario
inline void AgregarMetodoPagoScreen::_renderizarFormulario()
{
    // Campos comunes para tarjetas
    if (_metodoPago.tipo == TipoMetodoPago::TARJETA_CREDITO || 
        _metodoPago.tipo == TipoMetodoPago::TARJETA_DEBITO) {
        
        gotoXY(COL_NUMERO_TARJETA, FILA_NUMERO_TARJETA - 1);
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "Numero de Tarjeta:";
        
        gotoXY(COL_NOMBRE_TITULAR, FILA_NOMBRE_TITULAR - 1);
        std::cout << "Nombre del Titular:";
        
        gotoXY(COL_FECHA_VENC, FILA_FECHA_VENC - 1);
        std::cout << "Fecha Venc. (MM/AA):";
        
        gotoXY(COL_CVV, FILA_CVV - 1);
        std::cout << "CVV:";
        
        gotoXY(COL_BANCO, FILA_BANCO - 1);
        std::cout << "Banco Emisor:";
    }
    
    // Campo para transferencia bancaria
    if (_metodoPago.tipo == TipoMetodoPago::TRANSFERENCIA_BANCARIA) {
        gotoXY(COL_NUMERO_TARJETA, FILA_NUMERO_TARJETA - 1);
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "Numero de Cuenta:";
        
        gotoXY(COL_NOMBRE_TITULAR, FILA_NOMBRE_TITULAR - 1);
        std::cout << "Nombre del Titular:";
        
        gotoXY(COL_BANCO, FILA_BANCO - 1);
        std::cout << "Banco:";
    }
    
    // Campo para billetera digital
    if (_metodoPago.tipo == TipoMetodoPago::BILLETERA_DIGITAL) {
        gotoXY(COL_EMAIL, FILA_EMAIL - 1);
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "Correo Electronico:";
        
        gotoXY(COL_NOMBRE_TITULAR, FILA_NOMBRE_TITULAR - 1);
        std::cout << "Nombre del Usuario:";
    }
    
    resetColor();
}

// Renderizar instrucciones
inline void AgregarMetodoPagoScreen::_renderizarInstrucciones()
{
    gotoXY(15, 35);
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Navegacion: ";
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "[FLECHAS ARRIBA/ABAJO] ";
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

// Procesar formulario
inline ResultadoPantalla AgregarMetodoPagoScreen::_procesarFormulario()
{
    try {
        // Solicitar datos según el tipo seleccionado
        if (_metodoPago.tipo == TipoMetodoPago::TARJETA_CREDITO || 
            _metodoPago.tipo == TipoMetodoPago::TARJETA_DEBITO) {
            
            // Número de tarjeta
            gotoXY(COL_NUMERO_TARJETA, FILA_NUMERO_TARJETA);
            setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
            std::cout << "> ";
            resetColor();
            std::getline(std::cin, _metodoPago.numeroTarjeta);
            
            // Nombre del titular
            gotoXY(COL_NOMBRE_TITULAR, FILA_NOMBRE_TITULAR);
            setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
            std::cout << "> ";
            resetColor();
            std::getline(std::cin, _metodoPago.nombreTitular);
            
            // Fecha de vencimiento
            gotoXY(COL_FECHA_VENC, FILA_FECHA_VENC);
            setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
            std::cout << "> ";
            resetColor();
            std::getline(std::cin, _metodoPago.fechaVencimiento);
            
            // CVV
            gotoXY(COL_CVV, FILA_CVV);
            setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
            std::cout << "> ";
            resetColor();
            std::getline(std::cin, _metodoPago.cvv);
            
            // Banco
            gotoXY(COL_BANCO, FILA_BANCO);
            setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
            std::cout << "> ";
            resetColor();
            std::getline(std::cin, _metodoPago.nombreBanco);
        }
        else if (_metodoPago.tipo == TipoMetodoPago::TRANSFERENCIA_BANCARIA) {
            // Número de cuenta
            gotoXY(COL_NUMERO_TARJETA, FILA_NUMERO_TARJETA);
            setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
            std::cout << "> ";
            resetColor();
            std::getline(std::cin, _metodoPago.numeroTarjeta);
            
            // Nombre del titular
            gotoXY(COL_NOMBRE_TITULAR, FILA_NOMBRE_TITULAR);
            setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
            std::cout << "> ";
            resetColor();
            std::getline(std::cin, _metodoPago.nombreTitular);
            
            // Banco
            gotoXY(COL_BANCO, FILA_BANCO);
            setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
            std::cout << "> ";
            resetColor();
            std::getline(std::cin, _metodoPago.nombreBanco);
        }
        else if (_metodoPago.tipo == TipoMetodoPago::BILLETERA_DIGITAL) {
            // Correo electrónico
            gotoXY(COL_EMAIL, FILA_EMAIL);
            setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
            std::cout << "> ";
            resetColor();
            std::getline(std::cin, _metodoPago.correoElectronico);
            
            // Nombre del usuario
            gotoXY(COL_NOMBRE_TITULAR, FILA_NOMBRE_TITULAR);
            setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
            std::cout << "> ";
            resetColor();
            std::getline(std::cin, _metodoPago.nombreTitular);
        }
        
        if (_validarDatos()) {
            _mostrarExito();
            return ResultadoPantalla{_pantallaAnterior};
        } else {
            _mostrarMensaje("Datos invalidos. Revise los campos.");
        }
        
    } catch (const std::exception& e) {
        _mostrarMensaje("Error en los datos ingresados.");
    }
    
    return ResultadoPantalla{AccionPantalla::NINGUNA};
}

// Validar datos
inline bool AgregarMetodoPagoScreen::_validarDatos()
{
    if (_metodoPago.nombreTitular.empty()) return false;
    
    if (_metodoPago.tipo == TipoMetodoPago::TARJETA_CREDITO || 
        _metodoPago.tipo == TipoMetodoPago::TARJETA_DEBITO) {
        if (_metodoPago.numeroTarjeta.length() < 13 || _metodoPago.numeroTarjeta.length() > 19) return false;
        if (_metodoPago.fechaVencimiento.length() != 5) return false; // MM/AA
        if (_metodoPago.cvv.length() < 3 || _metodoPago.cvv.length() > 4) return false;
        if (_metodoPago.nombreBanco.empty()) return false;
    }
    else if (_metodoPago.tipo == TipoMetodoPago::TRANSFERENCIA_BANCARIA) {
        if (_metodoPago.numeroTarjeta.empty()) return false; // Número de cuenta
        if (_metodoPago.nombreBanco.empty()) return false;
    }
    else if (_metodoPago.tipo == TipoMetodoPago::BILLETERA_DIGITAL) {
        if (_metodoPago.correoElectronico.empty()) return false;
        if (_metodoPago.correoElectronico.find('@') == std::string::npos) return false;
    }
    
    return true;
}

// Navegar tipos
inline void AgregarMetodoPagoScreen::_navegarTipos(int direccion)
{
    if (direccion > 0) { // Abajo
        if (_tipoSeleccionado < 3) {
            _tipoSeleccionado++;
        }
    } else { // Arriba
        if (_tipoSeleccionado > 0) {
            _tipoSeleccionado--;
        }
    }
}

// Obtener nombre del tipo
inline std::string AgregarMetodoPagoScreen::_obtenerNombreTipo(TipoMetodoPago tipo)
{
    switch (tipo) {
        case TipoMetodoPago::TARJETA_CREDITO: return "Tarjeta de Credito";
        case TipoMetodoPago::TARJETA_DEBITO: return "Tarjeta de Debito";
        case TipoMetodoPago::TRANSFERENCIA_BANCARIA: return "Transferencia Bancaria";
        case TipoMetodoPago::BILLETERA_DIGITAL: return "Billetera Digital";
        default: return "Desconocido";
    }
}

// Mostrar mensaje
inline void AgregarMetodoPagoScreen::_mostrarMensaje(const std::string& mensaje)
{
    gotoXY(10, 32);
    setConsoleColor(ColorIndex::ERROR_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << mensaje;
    resetColor();
    
    gotoXY(10, 33);
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Presiona cualquier tecla para continuar...";
    resetColor();
    
    _getch();
}

// Mostrar éxito
inline void AgregarMetodoPagoScreen::_mostrarExito()
{
    system("cls");
    
    gotoXY(35, 10);
    setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "METODO DE PAGO AGREGADO EXITOSAMENTE";
    
    gotoXY(20, 12);
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Tipo: " << _obtenerNombreTipo(_metodoPago.tipo);
    
    gotoXY(20, 13);
    std::cout << "Titular: " << _metodoPago.nombreTitular;
    
    if (_metodoPago.tipo == TipoMetodoPago::TARJETA_CREDITO || 
        _metodoPago.tipo == TipoMetodoPago::TARJETA_DEBITO) {
        gotoXY(20, 14);
        std::cout << "Tarjeta: ****-****-****-" << _metodoPago.numeroTarjeta.substr(_metodoPago.numeroTarjeta.length() - 4);
        
        gotoXY(20, 15);
        std::cout << "Banco: " << _metodoPago.nombreBanco;
    }
    else if (_metodoPago.tipo == TipoMetodoPago::BILLETERA_DIGITAL) {
        gotoXY(20, 14);
        std::cout << "Email: " << _metodoPago.correoElectronico;
    }
    
    gotoXY(20, 18);
    setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
    std::cout << " Presiona cualquier tecla para volver ";
    resetColor();
    
    _getch();
}

// Método principal de ejecución
inline ResultadoPantalla AgregarMetodoPagoScreen::ejecutar()
{
    _limpiarEstado();
    
    while (true) {
        if (_primeraRenderizacion) {
            dibujarInterfazCompleta();
            _primeraRenderizacion = false;
        } else {
            _renderizarTiposMetodoPago();
            _renderizarFormulario();
            _renderizarInstrucciones();
        }
        
        int tecla = _getch();
        
        switch (tecla) {
        case 0:
        case 224: // Teclas especiales
        {
            int segundaTecla = _getch();
            switch (segundaTecla) {
            case 72: // Flecha arriba
                _navegarTipos(-1);
                break;
            case 80: // Flecha abajo
                _navegarTipos(1);
                break;
            }
        }
        break;
        
        case 72: // Flecha arriba (por si acaso)
            _navegarTipos(-1);
            break;
            
        case 80: // Flecha abajo (por si acaso)
            _navegarTipos(1);
            break;
            
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
            // Ignorar otras teclas
            break;
        }
    }
}

#endif // COURSERACLONE_SCREENS_AGREGARMETODOPAGOSCREEN_HPP
