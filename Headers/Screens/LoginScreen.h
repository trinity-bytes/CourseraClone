#pragma once

// Librerias estándar
#include <string>

// Librerías propias
#include "../Utils/ScreenSystem.h"
#include "../Entities/Estudiante.h"
#include "../Entities/Empresa.h"
#include "../DataStructures/LinkedList.h"
#include "../Entities/Curso.h"
#include "../Entities/Especializacion.h"

// forward declarations
class Usuario;

class LoginScreen : public PantallaBase 
{
// Atributos privados
private:
    static const int ELEMENTOS_INPUT = 2;     /// Número de campos de entrada
    static const int CANT_BOTONES = 3;        /// Número de botones en la interfaz

    // Datos de entrada del usuario
    std::string _email;                       /// Email ingresado por el usuario
    std::string _password;                    /// Contraseña ingresada
    TipoUsuario _tipoUsuario;                 /// Tipo de usuario seleccionado
    
    // Estado de la interfaz
    int _campoActual;                         /// Campo actualmente seleccionado
    int _campoAnterior;                       /// Campo anteriormente seleccionado
    bool _primeraRenderizacion;               /// Bandera para primera renderización
    int _tipoUsuarioActual;                   /// 0: Estudiante, 1: Organización
    
    // Manejo de errores
    bool _error;                              /// Bandera de error
    std::string _mensajeError;                /// Mensaje de error a mostrar
    
    // Referencias a entidades
    Estudiante& _estudiante;                  /// Referencia al estudiante
    Empresa& _empresa;                        /// Referencia a la empresa
    LinkedList<Curso*>& _cursos;              /// Lista de cursos disponibles
    LinkedList<Especializacion*>& _especialidades; /// Lista de especializaciones
    
    // Configuración de interfaz
    COORD _coordsElementosUserInput[ELEMENTOS_INPUT] = { {34, 15}, {34, 20} };
    COORD _coordsBotones[CANT_BOTONES] = { {44, 25}, {62, 25}, {52, 29} };
    const std::string _elementosUserinput[ELEMENTOS_INPUT] = { " ", " " };
    const std::string _textosBotones[CANT_BOTONES] = { " Estudiante ", " Organizacion ", " Iniciar Sesión " };

// Metodos privados para manejar la interfaz y la lógica de login
private:
    /**
     * @brief Configura la visibilidad del cursor
     * @param mostrar True para mostrar el cursor, false para ocultarlo
     */
    void _configurarCursor(bool mostrar);
    
    /**
     * @brief Limpia el estado interno de la pantalla
     */
    void _limpiarEstado();

    /**
     * @brief Renderiza un campo de entrada de texto
     * @param valor Valor actual del campo
     * @param indice Índice del campo
     * @param seleccionado Estado de selección del campo
     */
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
     * @brief Dibuja el header visual del sistema
     */
    void _dibujarHeader();
    
    /**
     * @brief Dibuja el mensaje de bienvenida
     */
    void _dibujarMensajeBienvenida();
    
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
    void _configurarSesionEstudiante(int index);
    
    /**
     * @brief Configura la sesión de la empresa después del login exitoso
     * @param index Índice del usuario en la base de datos
     */
    void _configurarSesionEmpresa(int index);

    /**
     * @brief Muestra un mensaje de error en la interfaz
     * @param mensaje Mensaje de error a mostrar
     */
    void _mostrarError(const std::string& mensaje);
    
    /**
     * @brief Limpia el estado de error
     */
    void _limpiarError();

// Metodos públicos
public:
    /**
     * @brief Constructor por defecto
     */
    LoginScreen();
    
    /**
     * @brief Constructor con parámetros
     * @param estudiante Referencia al objeto estudiante
     * @param empresa Referencia al objeto empresa
     * @param cursos Lista de cursos disponibles
     * @param especialidades Lista de especializaciones disponibles
     */
    LoginScreen(Estudiante& estudiante, 
                Empresa& empresa, 
                LinkedList<Curso*>& cursos, 
                LinkedList<Especializacion*>& especialidades);

    /**
     * @brief Destructor virtual
     */
    virtual ~LoginScreen() = default;

    /**
     * @brief Ejecuta la pantalla de login
     * @return Resultado de la ejecución con la acción a realizar
     */
    ResultadoPantalla ejecutar() override;
    
    // Limpia el estado de la pantalla para una nueva sesión
    void clearState();

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
    
    /**
     * @brief Verifica si hay un error activo
     * @return True si hay error, false en caso contrario
     */
    bool hasError() const { return _error; }
    
    /**
     * @brief Obtiene el mensaje de error actual
     * @return Mensaje de error
     */
    const std::string& getMensajeError() const { return _mensajeError; }
};

// Alias para LoginScreen (COMPATIBILIDAD)
using Login = LoginScreen;

inline LoginScreen::LoginScreen() 
    : _campoActual(0)
    , _campoAnterior(-1)
    , _primeraRenderizacion(true)
    , _error(false)
    , _tipoUsuarioActual(0)
    , _estudiante(*(new Estudiante()))
    , _empresa(*(new Empresa()))
    , _cursos(*(new LinkedList<Curso*>()))
    , _especialidades(*(new LinkedList<Especializacion*>()))
{
}

inline LoginScreen::LoginScreen(Estudiante& estudiante, 
                                Empresa& empresa, 
                                LinkedList<Curso*>& cursos, 
                                LinkedList<Especializacion*>& especialidades)
    : _campoActual(0)
    , _campoAnterior(-1)
    , _primeraRenderizacion(true)
    , _error(false)
    , _tipoUsuarioActual(0)
    , _estudiante(estudiante)
    , _empresa(empresa)
    , _cursos(cursos)
    , _especialidades(especialidades)
{
}

inline void LoginScreen::_configurarCursor(bool mostrar) {
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = mostrar;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

inline void LoginScreen::_limpiarEstado() {
    _email.clear();
    _password.clear();
    _tipoUsuarioActual = 0;
    _campoActual = 0;
    _campoAnterior = -1;
    _limpiarError();
}

inline void LoginScreen::_limpiarError() {
    _error = false;
    _mensajeError.clear();
}

inline void LoginScreen::_mostrarError(const std::string& mensaje) {
    _error = true;
    _mensajeError = mensaje;
}

inline void LoginScreen::clearState() {
    _limpiarEstado();
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
    
    if (indice == 0 || indice == 1) {
        if (seleccionado || (indice == 0 && _tipoUsuarioActual == 0) || (indice == 1 && _tipoUsuarioActual == 1)) {
            setConsoleColor(1, 4, true, true);
        } else {
            setConsoleColor(7, 0);
        }
    } else {
        if (seleccionado) {
            setConsoleColor(1, 5, true, true);
        } else {
            setConsoleColor(5, 1, false, true);
        }
    }
    
    _configurarCursor(false);
    std::cout << texto;
    setConsoleColor(15, 0);
}

inline void LoginScreen::_dibujarHeader() {
    setConsoleColor(12, 13, true, true);
    gotoXY(42, 4);    std::cout << "▒█▀▀█ █▀▀█ █░░█ █▀▀█ █▀▀ █▀▀ █▀▀█ █▀▀█";
    gotoXY(42, 5);    std::cout << "▒█░░░ █░░█ █░░█ █▄▄▀ ▀▀█ █▀▀ █▄▄▀ █▄▄█";
    gotoXY(42, 6);    std::cout << "▒█▄▄█ ▀▀▀▀ ░▀▀▀ ▀░▀▀ ▀▀▀ ▀▀▀ ▀░▀▀ ▀░░▀";
    
    setConsoleColor(12, 13, true, true);
    gotoXY(71, 7);    std::cout << "C L O N E";
}

inline void LoginScreen::_dibujarMensajeBienvenida() {
    setConsoleColor(8, 0, true);
    gotoXY(44, 9);
    std::cout << "- QUE BUENO TENERTE DE VUELTA! -";
}

inline void LoginScreen::_dibujarInterfazCompleta() {
    setConsoleColor(15, 0);
    system("cls");
    
    UI_Login();
    
    // Dibuja el fondo del header
    for (int i = 3; i <= 7; i++) {
        gotoXY(3, i);
        setConsoleColor(1, 13, true);
        std::cout << std::string(114, ' ');
    }
    
    _dibujarHeader();
    _dibujarMensajeBienvenida();
    
    setConsoleColor(15, 0);
    
    // Renderizar campos de entrada
    for (int i = 0; i < ELEMENTOS_INPUT; ++i) {
        std::string valor = (i == 0) ? _email : std::string(_password.length(), '*');
        _renderizarCampo(valor, i, _campoActual == i);
    }
    
    // Renderizar botones
    for (int i = 0; i < CANT_BOTONES; ++i) {
        _renderizarBoton(_textosBotones[i], i, _campoActual == i + 2);
    }
    
    // Mostrar mensaje de error si existe
    if (_error) {
        gotoXY(ANCHO_CONSOLA / 2 - _mensajeError.length() / 2, 11);
        setConsoleColor(1, 3);
        std::cout << _mensajeError;
        setConsoleColor(15, 1);
    }
    
    gotoXY(34, 15);
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
        _mostrarError("Todos los campos son obligatorios");
        return false;
    }
    return true;
}

inline LoginStatus LoginScreen::_autenticarUsuario() {
    Usuario usuarioTemp;
    _tipoUsuario = (_tipoUsuarioActual == 0) ? TipoUsuario::ESTUDIANTE : TipoUsuario::EMPRESA;
    int index = usuarioTemp.buscarIndexUsuario(_email, _tipoUsuario);
    
    if (index == -1) {
        _mostrarError("Usuario no encontrado");
        return LoginStatus::USER_NOT_FOUND;
    }
    
    return usuarioTemp.login(usuarioTemp, _tipoUsuario, _password, index);
}

inline void LoginScreen::_configurarSesionEstudiante(int index) {
    Usuario usuarioTemp;
    _estudiante.reset();
    _estudiante.setId(index);
    _estudiante.setNombre(usuarioTemp.getNombreCompleto());
    _estudiante.setUsername(_email);
    _estudiante.setContrasena("");
    _estudiante.cargarInscripciones(_cursos, _especialidades);
    _estudiante.cargarDatos();
    _empresa.reset();
}

inline void LoginScreen::_configurarSesionEmpresa(int index) {
    Usuario usuarioTemp;
    _empresa.reset();
    _empresa.setId(index);
    _empresa.setNombre(usuarioTemp.getNombreCompleto());
    _empresa.setUsername(_email);
    _empresa.setContrasena("");
    _estudiante.reset();
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
            _configurarSesionEstudiante(index);
            res.accion = AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE;
        } else {
            _configurarSesionEmpresa(index);
            res.accion = AccionPantalla::IR_A_DASHBOARD_ORGANIZACION;
        }
        
        clearState();
        return res;
    } else {
        _mostrarError("Contraseña incorrecta");
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
                    _tipoUsuarioActual = 0;
                    _dibujarInterfazCompleta();
                } else if (_campoActual == 3) { // Botón Organización
                    _tipoUsuarioActual = 1;
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
        
        _limpiarError();
    }
}
