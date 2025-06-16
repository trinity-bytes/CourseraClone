#ifndef COURSERACLONE_SCREENS_LOGINSCREEN_HPP
#define COURSERACLONE_SCREENS_LOGINSCREEN_HPP

// Librerias estándar
#include <string>
#include <vector>

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
        {34, 15}, {34, 20} 
    };

    COORD _coordsBotones[CANT_BOTONES] = { {44, 23}, {62, 23}, {52, 26} };

    const std::string _elementosUserinput[ELEMENTOS_INPUT] = { " ", " " };

    std::vector<std::string> _textosBotones = { 
        " ESTUDIANTE ", 
        " ORGANIZACION ", 
        " INICIAR SESION " 
    };

	// ---- METODOS PRIVADOS ----

    /// @brief Configura la visibilidad del cursor
    /// @param mostrar True para mostrar el cursor, false para ocultarlo
    void _configurarCursor(bool mostrar);

    /// @brief Limpia el estado interno de la pantalla
    void _limpiarEstado();

    /// @brief Renderiza un campo de entrada de texto
    /// @param valor Valor actual del campo
    /// @param indice Índice del campo
    /// @param seleccionado Estado de selección del campo
    void _renderizarCampo(const std::string& valor, int indice, bool seleccionado);
    
    /**
     * @brief Renderiza un botón de la interfaz
     * @param texto Texto del botón
     * @param indice Índice del botón
     * @param seleccionado Estado de selección del botón
     */
    void _renderizarBoton(const std::string& texto, int indice, bool seleccionado);
    
    /**
     * @brief Dibuja la interfaz completa de login
     */
    void _dibujarInterfazCompleta();
    
    /**
     * @brief Actualiza la selección visual de campos y botones
     */
    void _actualizarSeleccion();

    /**
     * @brief Maneja la entrada de caracteres en los campos
     * @param tecla Tecla presionada
     */
    void _manejarEntradaTexto(int tecla);
    
    /**
     * @brief Maneja la navegación con las teclas direccionales
     * @param tecla Código de la tecla presionada
     */
    void _manejarNavegacion(int tecla);
    
    /**
     * @brief Maneja la acción de retroceso (Backspace)
     */
    void _manejarRetroceso();

    /**
     * @brief Valida los campos de entrada
     * @return True si los campos son válidos, false en caso contrario
     */
    bool _validarCampos();
    
    /**
     * @brief Procesa el intento de inicio de sesión
     * @return Resultado del proceso de autenticación
     */
    ResultadoPantalla _procesarLogin();
    
    /**
     * @brief Autentica al usuario con las credenciales proporcionadas
     * @return Estado del login
     */
    LoginStatus _autenticarUsuario();
    
    /**
     * @brief Configura la sesión del estudiante después del login exitoso
     * @param index Índice del usuario en la base de datos
     */
    UsuarioRawData _configurarSesionUsuario(int index);

public:
    /// @brief Constructor por defecto
    LoginScreen();

    /// @brief Destructor virtual
    virtual ~LoginScreen() = default;

    /**
     * @brief Ejecuta la pantalla de login
     * @return Resultado de la ejecución con la acción a realizar
     */
    ResultadoPantalla ejecutar() override;

    /**
     * @brief Obtiene el email ingresado
     * @return Email del usuario
     */
    const std::string& getEmail() const { return _email; }
    
    /**
     * @brief Obtiene el tipo de usuario seleccionado
     * @return Tipo de usuario
     */
    TipoUsuario getTipoUsuario() const { return _tipoUsuario; }

};

// ---- CONSTUCTORES INLINE ----
inline LoginScreen::LoginScreen() : PantallaBase() {}

// ---- METODOS PRIVADOS ----
inline void LoginScreen::_configurarCursor(bool mostrar) {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = mostrar;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

inline void LoginScreen::_limpiarEstado() {
    _email.clear();
    _password.clear();
    _tipoUsuarioActual = TipoUsuario::DEFAULT;
    _campoActual = 0;
    _campoAnterior = -1;
}

inline void LoginScreen::_renderizarCampo(const std::string& valor, int indice, bool seleccionado) {
    gotoXY(_coordsElementosUserInput[indice].X, _coordsElementosUserInput[indice].Y);
    
    if (seleccionado) {
        setConsoleColor(15, 4, true, true);
        _configurarCursor(true);
    } else {
        setConsoleColor(15, 0);
        _configurarCursor(false);
    }
    
    setConsoleColor(15, 1);
    std::cout << valor;
}

inline void LoginScreen::_renderizarBoton(const std::string& texto, int indice, bool seleccionado) {
    gotoXY(_coordsBotones[indice].X, _coordsBotones[indice].Y);
    
    if (indice == 0 || indice == 1) 
    {
        if (seleccionado || (indice == 0 && _tipoUsuarioActual == TipoUsuario::ESTUDIANTE) || (indice == 1 && _tipoUsuarioActual == TipoUsuario::EMPRESA)) {
            setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        } else {
            setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        }
    } else {
        if (seleccionado) {
            setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::HOVER_ESTADO);
        } else {
            setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        }
    }
    
    _configurarCursor(false);
    std::cout << texto;
	resetColor();
}

inline void LoginScreen::_dibujarInterfazCompleta() 
{
    system("cls");
    UI_Login();

    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    
    // Renderizar campos de entrada
    for (int i = 0; i < ELEMENTOS_INPUT; ++i) {
        std::string valor = (i == 0) ? _email : std::string(_password.length(), '*');
        _renderizarCampo(valor, i, _campoActual == i);
    }
    
    // Renderizar botones
    for (int i = 0; i < CANT_BOTONES; ++i) {
        _renderizarBoton(_textosBotones[i], i, _campoActual == i + 2);
    }
    
	gotoXY(34, 13); /// @brief Posicionar cursor en el primer campo
}

inline void LoginScreen::_actualizarSeleccion() {
    // Actualiza el campo anterior como NO seleccionado
    if (_campoAnterior >= 0 && _campoAnterior < ELEMENTOS_INPUT) {
        std::string valorAnterior = (_campoAnterior == 0) ? _email : std::string(_password.length(), '*');
        _renderizarCampo(valorAnterior, _campoAnterior, false);
    }
    
    // Actualiza el campo actual como seleccionado
    if (_campoActual >= 0 && _campoActual < ELEMENTOS_INPUT) {
        std::string valorActual = (_campoActual == 0) ? _email : std::string(_password.length(), '*');
        _renderizarCampo(valorActual, _campoActual, true);
    }
    
    // Actualiza selección de botones
    if (_campoAnterior >= 2 || _campoActual >= 2) {
        for (int i = 0; i < CANT_BOTONES; ++i) {
            _renderizarBoton(_textosBotones[i], i, _campoActual == i + 2);
        }
    }
    
    _campoAnterior = _campoActual;
}

inline void LoginScreen::_manejarNavegacion(int tecla) {
    switch (tecla) {
        case 72: // Flecha arriba
            if (_campoActual > 0) _campoActual--;
            break;
        case 80: // Flecha abajo
            if (_campoActual < 4) _campoActual++;
            break;
    }
}

inline void LoginScreen::_manejarEntradaTexto(int tecla) {
    if (tecla >= 32 && tecla <= 126) { // Caracteres imprimibles
        std::string* campo = nullptr;
        switch (_campoActual) {
            case 0: campo = &_email; break;
            case 1: campo = &_password; break;
        }
        if (campo) {
            campo->push_back(static_cast<char>(tecla));
            _dibujarInterfazCompleta();
        }
    }
}

inline void LoginScreen::_manejarRetroceso() {
    if (_campoActual >= 0 && _campoActual <= 1) {
        std::string* campo = nullptr;
        switch (_campoActual) {
            case 0: campo = &_email; break;
            case 1: campo = &_password; break;
        }
        if (campo && !campo->empty()) {
            campo->pop_back();
            _dibujarInterfazCompleta();
        }
    }
}

inline bool LoginScreen::_validarCampos() {
    if (_email.empty() || _password.empty()) {
        //_mostrarError("Todos los campos son obligatorios");
        return false;
    }
    return true;
}

inline LoginStatus LoginScreen::_autenticarUsuario() {
    Usuario usuarioTemp;
    
    if (_tipoUsuarioActual == TipoUsuario::DEFAULT) {
		/// @todo implementar la selección de tipo de usuario
        
	}

    int index = usuarioTemp.buscarIndexUsuario(_email, _tipoUsuario);
    
    if (index == -1) {
        //_mostrarError("Usuario no encontrado");
        return LoginStatus::USER_NOT_FOUND;
    }
    
    return usuarioTemp.login(usuarioTemp, _tipoUsuario, _password, index);
}

inline UsuarioRawData LoginScreen::_configurarSesionUsuario(int index) {
    Usuario usuarioTemp;
	UsuarioRawData usuarioData;

	/// @todo implementar la asignacion de datos del usuario para la sesión

    return usuarioData;
}

inline ResultadoPantalla LoginScreen::_procesarLogin() {
    ResultadoPantalla res;
    
    if (!_validarCampos()) {
        _dibujarInterfazCompleta();
        return res;
    }
    
    LoginStatus status = _autenticarUsuario();
    
    if (status == LoginStatus::SUCCESS) {
        res.email = _email;
        res.password = _password;
        res.tipoUsuario = _tipoUsuario;
        
        Usuario usuarioTemp;
        int index = usuarioTemp.buscarIndexUsuario(_email, _tipoUsuario);
        
        if (_tipoUsuario == TipoUsuario::ESTUDIANTE) {
            //_configurarSesionUsuario(index);
            res.accion = AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE;
        } else {
            //_configurarSesionUsuario(index);
            res.accion = AccionPantalla::IR_A_DASHBOARD_ORGANIZACION;
        }
        
        _limpiarEstado();
        return res;
    } else {
        //_mostrarError("Contraseña incorrecta");
        _dibujarInterfazCompleta();
        return res;
    }
}

inline ResultadoPantalla LoginScreen::ejecutar() {
    ResultadoPantalla res;
    
    while (true) {
        if (_primeraRenderizacion) {
            _dibujarInterfazCompleta();
            _configurarCursor(true);
            _primeraRenderizacion = false;
        } else {
            _actualizarSeleccion();
        }
        
        int tecla = _getch();
        
        switch (tecla) {
            case 72: // Flecha arriba
            case 80: // Flecha abajo
                _manejarNavegacion(tecla);
                break;
                
            case 27: // ESC
                res.accion = AccionPantalla::IR_A_LANDING_PAGE;
                return res;
                
            case 13: // Enter
                if (_campoActual == 2) { // Botón Estudiante
                    _tipoUsuarioActual = TipoUsuario::ESTUDIANTE;
                    _dibujarInterfazCompleta();
                } else if (_campoActual == 3) { // Botón Organización
                    _tipoUsuarioActual = TipoUsuario::EMPRESA;
                    _dibujarInterfazCompleta();
                } else if (_campoActual == 4) { // Iniciar Sesión
                    ResultadoPantalla loginRes = _procesarLogin();
                    if (loginRes.accion != AccionPantalla::NINGUNA) {
                        return loginRes;
                    }
                }
                break;
                
            case 8: // Backspace
                _manejarRetroceso();
                break;
                
            default:
        _manejarEntradaTexto(tecla);
                break;
        }
        
        //_limpiarError();
    }
};

#endif // COURSERACLONE_SCREENS_LOGINSCREEN_HPP
