#ifndef COURSERACLONE_SCREENS_REGISTROSCREEN_HPP
#define COURSERACLONE_SCREENS_REGISTROSCREEN_HPP

// Headers estándar
#include <string>
#include <vector>
#include <conio.h>  // Para _getch()

// Headers propios del proyecto
#include "../Entities/Usuario.hpp"
#include "../Types/ActividadTypes.hpp"
#include "../Types/UsuarioTypes.hpp"
#include "../Utils/ScreenSystem.hpp"
#include "../Utils/SystemUtils.hpp"
#include "../Utils/UI_Ascii.hpp"

/// Pantalla de registro de usuarios
class RegistroScreen : public PantallaBase 
{
private:
    // ---- ATRIBUTOS PRIVADOS ----
    static const int ELEMENTOS_INPUT = 4;
    static const int CANT_BOTONES = 3;
    static const int TOTAL_ELEMENTOS = ELEMENTOS_INPUT + CANT_BOTONES; // Total de elementos navegables
    
    /// @brief Variables para los elementos de entrada de datos
    std::string _nombre;
    std::string _email;
    std::string _password;
    std::string _confirmarPassword;
    TipoUsuario _tipoUsuario;

    /// @brief Variables para el manejo de la interfaz
    int _campoActual;
    int _campoAnterior;
    bool _error;
    std::string _mensajeError;
    bool _primeraRenderizacion;
    TipoUsuario _tipoUsuarioActual;

    /// @brief Coordenadas para dibujar
    COORD _coordsElementosUserInput[ELEMENTOS_INPUT] = { 
        {26, 9}, {26, 13}, {26, 17}, {26, 21} 
    };
    
    COORD _coordsBotones[CANT_BOTONES] = { 
        {54, 24}, {70, 24}, {53, 27} 
    };

    /// @brief Textos de los botones y etiquetas
    std::vector<std::string> _textosBotones = {
        " UN ESTUDIANTE ", 
        " UNA ORGANIZACION ", 
        " CREAR CUENTA "
    };
    
    const std::string _elementosUserinput[ELEMENTOS_INPUT] = { " ", " ", " ", " " };
    
    // ---- METODOS PRIVADOS ----
    /// @brief Limpia el estado interno de la pantalla
    inline void _limpiarEstado();

    /// @brief Muestra un mensaje de error en la interfaz
    /// @param mensaje Mensaje de error a mostrar
    inline void _mostrarError(const std::string& mensaje);

    /// @brief Renderiza un campo de entrada de texto
    /// @param valor Valor actual del campo
    /// @param indice Índice del campo
    /// @param seleccionado Estado de selección del campo
    inline void _renderizarCampo(const std::string& valor, int indice, bool seleccionado);

    /// @brief Renderiza un botón de la interfaz
    /// @param texto Texto del botón
    /// @param indice Índice del botón
    /// @param seleccionado Estado de selección del botón
    inline void _renderizarBoton(const std::string& texto, int indice, bool seleccionado);

    /// @brief Dibuja la interfaz completa de registro
    inline void _dibujarInterfazCompleta();

    /// @brief Actualiza la selección visual de campos y botones
    inline void _actualizarSeleccion();

    /// @brief Actualiza la renderización de todos los botones
    inline void _actualizarBotones();

    /// @brief Maneja la entrada de caracteres en los campos
    /// @param tecla Tecla presionada
    inline void _manejarEntradaTexto(int tecla);

    /// @brief Maneja la navegación con las teclas direccionales
    /// @param tecla Código de la tecla presionada
    inline void _manejarNavegacion(int tecla);

    /// @brief Maneja la acción de retroceso (Backspace)
    inline void _manejarRetroceso();

    /// @brief Valida los campos de entrada
    /// @return True si los campos son válidos, false en caso contrario
    inline bool _validarCamposLlenos();

    /// @brief Procesa el intento de registro
    /// @return Resultado del proceso de registro
    inline ResultadoPantalla _procesarRegistro();

public:
    /// @brief Constructor por defecto
    RegistroScreen();

    /// @brief Destructor virtual
    virtual ~RegistroScreen() = default;

    /// @brief Ejecuta la pantalla de registro
    /// @return Resultado de la ejecución con la acción a realizar
    ResultadoPantalla ejecutar() override;

    /// @brief Obtiene el email ingresado
    /// @return Email del usuario
    const std::string& getEmail() const { return _email; }

    /// @brief Obtiene el tipo de usuario seleccionado
    /// @return Tipo de usuario
    TipoUsuario getTipoUsuario() const { return _tipoUsuarioActual; }
};

// ---- CONSTRUCTORES INLINE ----
inline RegistroScreen::RegistroScreen() : PantallaBase(), _campoActual(0), _campoAnterior(-1),
    _error(false), _mensajeError(""), _primeraRenderizacion(true), _tipoUsuarioActual(TipoUsuario::DEFAULT) {
}

// ---- METODOS PRIVADOS ----
inline void RegistroScreen::_limpiarEstado()
{
    _nombre.clear();
    _email.clear();
    _password.clear();
    _confirmarPassword.clear();
    _tipoUsuarioActual = TipoUsuario::DEFAULT;
    _campoActual = 0;
    _campoAnterior = -1;
    _error = false;
    _mensajeError.clear();
    _primeraRenderizacion = true;
}

inline void RegistroScreen::_mostrarError(const std::string& mensaje)
{
    gotoXY(25, 25);
    setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::ERROR_COLOR);
    std::cout << "[ERROR]: " << mensaje;
    resetColor();

    // Pausa para mostrar el error
    _getch();

    // Limpia el mensaje de error
    gotoXY(11, 11);
    for (int i = 0; i < mensaje.length() + 9; ++i)
    {
        std::cout << " ";
    }
}

inline void RegistroScreen::_renderizarCampo(const std::string& valor, int indice, bool seleccionado)
{
    gotoXY(_coordsElementosUserInput[indice].X, _coordsElementosUserInput[indice].Y);

    if (seleccionado)
    {
        setConsoleColor(ColorIndex::FONDO_PRINCIPAL, ColorIndex::BORDES_SUTILES);
        _configurarCursor(true);
    }
    else {
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        _configurarCursor(false);
    }

    // Mostrar el valor con padding para limpiar caracteres residuales
    std::string display = valor;
    display.resize(66, ' '); // Asegurar que el campo tenga tamaño fijo
    std::cout << display;

    // Posicionar cursor al final del texto real inmediatamente después de renderizar
    if (seleccionado) 
    {
        gotoXY(_coordsElementosUserInput[indice].X + valor.length(), _coordsElementosUserInput[indice].Y);
    }
    else
    {
        _configurarCursor(false);
    }

    resetColor();
}

inline void RegistroScreen::_renderizarBoton(const std::string& texto, int indice, bool seleccionado)
{
    _configurarCursor(false);  
    gotoXY(_coordsBotones[indice].X, _coordsBotones[indice].Y);  
    
    if (indice == 0 || indice == 1)
    {
        // Botones de tipo de usuario
        if (seleccionado)
        {
            setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::HOVER_ESTADO);
        }
        else if (indice == 0 && _tipoUsuarioActual == TipoUsuario::ESTUDIANTE)
        {
            setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::EXITO_COLOR);
        }
        else if (indice == 1 && _tipoUsuarioActual == TipoUsuario::EMPRESA)
        {
            setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::EXITO_COLOR);
        }
        else
        {
            setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        }
    }
    else {
        // Botón de crear cuenta
        if (seleccionado)
        {
            setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::HOVER_ESTADO);
        }
        else
        {
            setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        }
    }

    std::cout << texto;
    resetColor();
}

inline void RegistroScreen::_dibujarInterfazCompleta()
{
    system("cls");
    UI_Signup();

    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);

    // Renderizar campos de entrada
    for (int i = 0; i < ELEMENTOS_INPUT; ++i)
    {
        std::string* valor = nullptr;
        switch (i)
        {
        case 0: valor = &_nombre; break;
        case 1: valor = &_email; break;
        case 2: valor = &_password; break;
        case 3: valor = &_confirmarPassword; break;
        }
        
        if (valor != nullptr)
        {
            _renderizarCampo(*valor, i, _campoActual == i);
        }
    }

    // Renderizar botones
    for (int i = 0; i < CANT_BOTONES; ++i) {
        _renderizarBoton(_textosBotones[i], i, _campoActual == (ELEMENTOS_INPUT + i));
    }

    resetColor();
}

inline void RegistroScreen::_actualizarSeleccion()
{
    // Solo actualizar si hay cambio de selección
    if (_campoAnterior != _campoActual)
    {
        // Actualizar campo anterior
        if (_campoAnterior >= 0)
        {
            if (_campoAnterior < ELEMENTOS_INPUT)
            {
                std::string* valor = nullptr;
                switch (_campoAnterior)
                {
                case 0: valor = &_nombre; break;
                case 1: valor = &_email; break;
                case 2: valor = &_password; break;
                case 3: valor = &_confirmarPassword; break;
                }
                
                if (valor != nullptr)
                {
                    _renderizarCampo(*valor, _campoAnterior, false);
                }
            }
            else
            {
                int indiceBoton = _campoAnterior - ELEMENTOS_INPUT;
                _renderizarBoton(_textosBotones[indiceBoton], indiceBoton, false);
            }
        }

        // Actualizar campo actual
        if (_campoActual < ELEMENTOS_INPUT)
        {
            std::string* valor = nullptr;
            switch (_campoActual)
            {
            case 0: valor = &_nombre; break;
            case 1: valor = &_email; break;
            case 2: valor = &_password; break;
            case 3: valor = &_confirmarPassword; break;
            }
            
            if (valor != nullptr)
            {
                _renderizarCampo(*valor, _campoActual, true);
            }
        }
        else
        {
            int indiceBoton = _campoActual - ELEMENTOS_INPUT;
            _renderizarBoton(_textosBotones[indiceBoton], indiceBoton, true);
        }

        _campoAnterior = _campoActual;
    }
}

inline void RegistroScreen::_actualizarBotones()
{
    for (int i = 0; i < CANT_BOTONES; ++i)
    {
        _renderizarBoton(_textosBotones[i], i, _campoActual == (ELEMENTOS_INPUT + i));
    }
}

inline void RegistroScreen::_manejarNavegacion(int tecla)
{
    switch (tecla) {
    case 72: // Flecha arriba
        _campoActual = (_campoActual > 0) ? _campoActual - 1 : TOTAL_ELEMENTOS - 1;
        break;
    case 80: // Flecha abajo
        _campoActual = (_campoActual < TOTAL_ELEMENTOS - 1) ? _campoActual + 1 : 0;
        break;
    }
}

inline void RegistroScreen::_manejarEntradaTexto(int tecla)
{
    // Solo procesar entrada de texto si estamos en un campo de entrada
    if (_campoActual < ELEMENTOS_INPUT && tecla >= 32 && tecla <= 126)
    {
        std::string* campoActivo = nullptr;
        switch (_campoActual)
        {
        case 0: campoActivo = &_nombre; break;
        case 1: campoActivo = &_email; break;
        case 2: campoActivo = &_password; break;
        case 3: campoActivo = &_confirmarPassword; break;
        }

        if (campoActivo != nullptr && campoActivo->length() < 51)
        {
            *campoActivo += static_cast<char>(tecla);
            _renderizarCampo(*campoActivo, _campoActual, true);
        }
    }
}

inline void RegistroScreen::_manejarRetroceso()
{
    if (_campoActual < ELEMENTOS_INPUT)
    {
        std::string* campoActivo = nullptr;
        switch (_campoActual)
        {
        case 0: campoActivo = &_nombre; break;
        case 1: campoActivo = &_email; break;
        case 2: campoActivo = &_password; break;
        case 3: campoActivo = &_confirmarPassword; break;
        }

        if (campoActivo != nullptr && !campoActivo->empty())
        {
            campoActivo->pop_back();
            _renderizarCampo(*campoActivo, _campoActual, true);
        }
    }
}

inline bool RegistroScreen::_validarCamposLlenos()
{
    if (_nombre.empty() || _email.empty() || _password.empty() || _confirmarPassword.empty())
    {
        _mostrarError("Todos los campos son obligatorios");
        return false;
    }
    if (_tipoUsuarioActual == TipoUsuario::DEFAULT)
    {
        _mostrarError("Debe seleccionar un tipo de usuario");
        return false;
    }
    if (_password != _confirmarPassword)
    {
        _mostrarError("Las contrasenyas no coinciden");
        return false;
    }
    return true;
}

inline ResultadoPantalla RegistroScreen::_procesarRegistro()
{
    if (!_validarCamposLlenos())
    {
        return ResultadoPantalla(AccionPantalla::NINGUNA);
    }

    /// @TODO: Aquí iría la lógica de guardado del usuario
    // Por ahora, simulamos éxito y regresamos al login
    
    gotoXY(11, 11);
    setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::EXITO_COLOR);
    std::cout << "[EXITO]: Usuario registrado correctamente.";
    resetColor();
    _getch();

    return ResultadoPantalla(AccionPantalla::IR_A_LOGIN);
}

inline ResultadoPantalla RegistroScreen::ejecutar()
{
    _limpiarEstado();
    
    if (_primeraRenderizacion)
    {
        _dibujarInterfazCompleta();
        _primeraRenderizacion = false;
    }

    while (true)
    {
        _actualizarSeleccion();

        int tecla = _getch();

        // Verificar si es una tecla especial (códigos extendidos)
        if (tecla == 224 || tecla == 0)
        {
            int codigoExtendido = _getch();
            _manejarNavegacion(codigoExtendido);
        }
        else
        {
            switch (tecla)
            {
            case 13: // Enter
                if (_campoActual >= ELEMENTOS_INPUT)
                {
                    int indiceBoton = _campoActual - ELEMENTOS_INPUT;
                    if (indiceBoton == 0) // UN ESTUDIANTE
                    {
                        _tipoUsuarioActual = TipoUsuario::ESTUDIANTE;
                        _actualizarBotones();
                    }
                    else if (indiceBoton == 1) // UNA ORGANIZACION
                    {
                        _tipoUsuarioActual = TipoUsuario::EMPRESA;
                        _actualizarBotones();
                    }
                    else if (indiceBoton == 2) // CREAR CUENTA
                    {
                        return _procesarRegistro();
                    }
                }
                break;

            case 8: // Backspace
                _manejarRetroceso();
                break;

            case 27: // ESC - Regresar al login
                return ResultadoPantalla(AccionPantalla::IR_A_LOGIN);

            default:
                _manejarEntradaTexto(tecla);
                break;
            }
        }
    }
}



#endif // COURSERACLONE_SCREENS_REGISTROSCREEN_HPP