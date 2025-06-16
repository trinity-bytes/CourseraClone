#ifndef COURSERACLONE_SCREENS_LOGINSCREEN_HPP
#define COURSERACLONE_SCREENS_LOGINSCREEN_HPP

// Librerias estándar
#include <string>
#include <vector>
#include <conio.h>  // Para _getch()

// Librerías propias
#include "../Entities/Usuario.hpp"
#include "../Types/ActividadTypes.hpp"
#include "../Types/UsuarioTypes.hpp"
#include "../Utils/ScreenSystem.hpp"
#include "../Utils/SystemUtils.hpp"
#include "../Utils/UI_Ascii.hpp"

class LoginScreen : public PantallaBase
{
private:
    // ---- ATRIBUTOS PRIVADOS ----
    static const int ELEMENTOS_INPUT = 2;
    static const int CANT_BOTONES = 3;
    static const int TOTAL_ELEMENTOS = ELEMENTOS_INPUT + CANT_BOTONES; // Total de elementos navegables

    /// @brief Datos de entrada del usuario
    std::string _email;
    std::string _password;
    TipoUsuario _tipoUsuario;

    /// @brief Estado de la interfaz
    int _campoActual;
    int _campoAnterior;
    bool _primeraRenderizacion;
    TipoUsuario _tipoUsuarioActual;

    /// @brief Configuración de interfaz
    COORD _coordsElementosUserInput[ELEMENTOS_INPUT] = {
        {34, 13}, {34, 18}
    };

    COORD _coordsBotones[CANT_BOTONES] = {
        {44, 23}, {62, 23}, {52, 26}
    };

    const std::string _elementosUserinput[ELEMENTOS_INPUT] = { " ", " " };

    std::vector<std::string> _textosBotones = {
        " ESTUDIANTE ",
        " ORGANIZACION ",
        " INICIAR SESION "
    };

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

    /// @brief Dibuja la interfaz completa de login
    inline void _dibujarInterfazCompleta();

    /// @brief Actualiza la selección visual de campos y botones
    inline void _actualizarSeleccion();

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

    /// @brief Procesa el intento de inicio de sesión
    /// @return Resultado del proceso de autenticación
    inline ResultadoPantalla _procesarLogin();

    /// @brief Autentica al usuario con las credenciales proporcionadas
    /// @return Estado del login
    inline LoginStatus _autenticarUsuario();

    /// @brief Configura la sesión del estudiante después del login exitoso
    /// @param index Índice del usuario en la base de datos
    inline UsuarioRawData _configurarSesionUsuario(int index);

public:
    /// @brief Constructor por defecto
    LoginScreen();

    /// @brief Destructor virtual
    virtual ~LoginScreen() = default;

    /// @brief Ejecuta la pantalla de login
    /// @return Resultado de la ejecución con la acción a realizar
    ResultadoPantalla ejecutar() override;

    /// @brief Obtiene el email ingresado
    /// @return Email del usuario
    const std::string& getEmail() const { return _email; }

    /// @brief Obtiene el tipo de usuario seleccionado
    /// @return Tipo de usuario
    TipoUsuario getTipoUsuario() const { return _tipoUsuario; }
};

// ---- CONSTRUCTORES INLINE ----
inline LoginScreen::LoginScreen() : PantallaBase(), _campoActual(0), _campoAnterior(-1),
_primeraRenderizacion(true), _tipoUsuarioActual(TipoUsuario::DEFAULT) {
}

// ---- METODOS PRIVADOS ----
inline void LoginScreen::_limpiarEstado()
{
    _email.clear();
    _password.clear();
    _tipoUsuarioActual = TipoUsuario::DEFAULT;
    _campoActual = 0;
    _campoAnterior = -1;
    _primeraRenderizacion = true;
}

inline void LoginScreen::_mostrarError(const std::string& mensaje)
{
    gotoXY(34, 9);
    setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::ERROR_COLOR);
    std::cout << "[ERROR]: " << mensaje;
    resetColor();

    // Pausa para mostrar el error
    _getch();

    // Limpia el mensaje de error
    gotoXY(34, 9);
    for (int i = 0; i < mensaje.length() + 9; ++i)
    {
        std::cout << " ";
    }
}

inline void LoginScreen::_renderizarCampo(const std::string& valor, int indice, bool seleccionado)
{
    gotoXY(_coordsElementosUserInput[indice].X, _coordsElementosUserInput[indice].Y);

    if (seleccionado)
    {
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::BORDES_SUTILES);
        _configurarCursor(true);
    }
    else {
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        _configurarCursor(false);
    }

    // Mostrar el valor con padding para limpiar caracteres residuales
    std::string display = valor;
    display.resize(52, ' '); // Asegurar que el campo tenga tamaño fijo
    std::cout << display;

    // Posicionar cursor al final del texto real
    if (seleccionado) 
    {
        gotoXY(_coordsElementosUserInput[indice].X + valor.length(), _coordsElementosUserInput[indice].Y);
    }

    resetColor();
}

inline void LoginScreen::_renderizarBoton(const std::string& texto, int indice, bool seleccionado)
{
    gotoXY(_coordsBotones[indice].X, _coordsBotones[indice].Y);
    _configurarCursor(false);

    if (indice == 0 || indice == 1)
    {
        // Botones de tipo de usuario
        if (_tipoUsuarioActual == TipoUsuario::DEFAULT)
        {
            setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        }
        else if ((_tipoUsuarioActual == TipoUsuario::ESTUDIANTE && indice == 0) ||
                 (_tipoUsuarioActual == TipoUsuario::EMPRESA && indice == 1))
        {
            setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::TEXTO_IMPORTANTE);
        }
        else {
            setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        }
    }
    else {
        // Botón de iniciar sesión
        if (seleccionado) {
            setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::HOVER_ESTADO);
        }
        else {
            setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        }
    }

    std::cout << texto;
    resetColor();
}

inline void LoginScreen::_dibujarInterfazCompleta()
{
    system("cls");
    UI_Login();

    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);

    /// @brief Renderizar campos de entrada
    for (int i = 0; i < ELEMENTOS_INPUT; ++i)
    {
        std::string valor = (i == 0) ? _email : std::string(_password.length(), '*');
        _renderizarCampo(valor, i, _campoActual == i);
    }

    // Renderizar botones
    for (int i = 0; i < CANT_BOTONES; ++i) {
        _renderizarBoton(_textosBotones[i], i, _campoActual == i + ELEMENTOS_INPUT);
    }

    resetColor();
}

inline void LoginScreen::_actualizarSeleccion()
{
    // Solo actualizar si hay cambio de selección
    if (_campoAnterior != _campoActual)
    {
        // Actualizar campos de entrada
        for (int i = 0; i < ELEMENTOS_INPUT; ++i)
        {
            std::string valor = (i == 0) ? _email : std::string(_password.length(), '*');
            _renderizarCampo(valor, i, _campoActual == i);
        }

        // Actualizar botones
        for (int i = 0; i < CANT_BOTONES; ++i)
        {
            _renderizarBoton(_textosBotones[i], i, _campoActual == i + ELEMENTOS_INPUT);
        }

        _campoAnterior = _campoActual;
    }
}

inline void LoginScreen::_manejarNavegacion(int tecla)
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

inline void LoginScreen::_manejarEntradaTexto(int tecla)
{
    // Solo procesar entrada de texto si estamos en un campo de entrada
    if (_campoActual < ELEMENTOS_INPUT && tecla >= 32 && tecla <= 126)
    {
        std::string* campo = (_campoActual == 0) ? &_email : &_password;

        if (campo->length() < 50) // Limitar longitud
        {
            campo->push_back(static_cast<char>(tecla));

            // Actualizar solo el campo actual
            std::string valor = (_campoActual == 0) ? _email : std::string(_password.length(), '*');
            _renderizarCampo(valor, _campoActual, true);
        }
    }
}

inline void LoginScreen::_manejarRetroceso()
{
    if (_campoActual < ELEMENTOS_INPUT)
    {
        std::string* campo = (_campoActual == 0) ? &_email : &_password;

        if (!campo->empty())
        {
            campo->pop_back();

            // Actualizar solo el campo actual
            std::string valor = (_campoActual == 0) ? _email : std::string(_password.length(), '*');
            _renderizarCampo(valor, _campoActual, true);
        }
    }
}

inline bool LoginScreen::_validarCamposLlenos()
{
    if (_email.empty() || _password.empty())
    {
        _mostrarError("Todos los campos son obligatorios");
        return false;
    }
    if (_tipoUsuarioActual == TipoUsuario::DEFAULT)
    {
        _mostrarError("Debe seleccionar un tipo de usuario");
        return false;
    }
    return true;
}

inline LoginStatus LoginScreen::_autenticarUsuario()
{
    /// @todo Implementar la lógica de autenticación del usuario
    return LoginStatus::SUCCESS; // Dato por defecto, debe ser implementado
}

inline UsuarioRawData LoginScreen::_configurarSesionUsuario(int index)
{
    Usuario usuarioTemp;
    UsuarioRawData usuarioData;
    /// @todo implementar la asignacion de datos del usuario para la sesión
    return usuarioData;
}

inline ResultadoPantalla LoginScreen::_procesarLogin()
{
    ResultadoPantalla res;

    if (!_validarCamposLlenos())
    {
        res.accion = AccionPantalla::NINGUNA;
        return res;
    }

    LoginStatus status = _autenticarUsuario();

    switch (status)
    {
    case LoginStatus::SUCCESS:
        _tipoUsuario = _tipoUsuarioActual;
        res.accion = (_tipoUsuarioActual == TipoUsuario::ESTUDIANTE) ?
            AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE :
            AccionPantalla::IR_A_DASHBOARD_ORGANIZACION;
        break;
    case LoginStatus::WRONG_PASSWORD:
        _mostrarError("Credenciales incorrectas");
        res.accion = AccionPantalla::NINGUNA;
        break;
    case LoginStatus::USER_NOT_FOUND:
        _mostrarError("Usuario no encontrado");
        res.accion = AccionPantalla::NINGUNA;
        break;
    default:
        _mostrarError("Error desconocido");
        res.accion = AccionPantalla::NINGUNA;
        break;
    }

    return res;
}

inline ResultadoPantalla LoginScreen::ejecutar()
{
    ResultadoPantalla res;

    // Inicializar estado
    _limpiarEstado();

    while (true)
    {
        if (_primeraRenderizacion)
        {
            _dibujarInterfazCompleta();
            _primeraRenderizacion = false;
        }
        else {
            _actualizarSeleccion();
        }

        int tecla = _getch();

        // Debug: Mostrar código de tecla (opcional, quitar en producción)
        // gotoXY(1, 1); std::cout << "Tecla: " << tecla << "   ";

        switch (tecla) {
        case 0:  // Teclas especiales - leer segundo byte
        case 224: // Teclas especiales en algunos sistemas
        {
            int segundaTecla = _getch();
            _manejarNavegacion(segundaTecla);
        }
        break;

        case 72: // Flecha arriba (por si acaso)
        case 80: // Flecha abajo (por si acaso)
            _manejarNavegacion(tecla);
            break;

        case 27: // ESC
            res.accion = AccionPantalla::IR_A_LANDING_PAGE;
            return res;

        case 13: // Enter
            if (_campoActual == ELEMENTOS_INPUT)
            { // Botón Estudiante
                _tipoUsuarioActual = TipoUsuario::ESTUDIANTE;
                _actualizarSeleccion();
            }
            else if (_campoActual == ELEMENTOS_INPUT + 1)
            { // Botón Organización
                _tipoUsuarioActual = TipoUsuario::EMPRESA;
                _actualizarSeleccion();
            }
            else if (_campoActual == ELEMENTOS_INPUT + 2)
            { // Iniciar Sesión
                ResultadoPantalla loginRes = _procesarLogin();
                if (loginRes.accion != AccionPantalla::NINGUNA)
                {
                    return loginRes;
                }
                // Si el login falla, redibujar la interfaz
                _dibujarInterfazCompleta();
            }
            break;

        case 8: // Backspace
            _manejarRetroceso();
            break;

        case 9: // Tab - navegación alternativa
            _campoActual = (_campoActual < TOTAL_ELEMENTOS - 1) ? _campoActual + 1 : 0;
            break;

        default:
            _manejarEntradaTexto(tecla);
            break;
        }
    }
}

#endif // COURSERACLONE_SCREENS_LOGINSCREEN_HPP