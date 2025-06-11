#ifndef COURSERACLONE_SCREENS_REGISTROSCREEN_HPP
#define COURSERACLONE_SCREENS_REGISTROSCREEN_HPP

// Headers estándar
#include <string>

// Headers propios
#include "../Utils/ScreenSystem.hpp"
#include "../Entities/Usuario.hpp"
#include "../Utils/SystemUtils.hpp"

/// Pantalla de registro de usuarios
class RegistroScreen : public PantallaBase {
private:
    static const int ELEMENTOS_INPUT = 4;
    static const int CANT_BOTONES = 3;
    
    std::string _nombre;
    std::string _email;
    std::string _password;
    std::string _confirmarPassword;
    TipoUsuario _tipoUsuario;
    int _campoActual;
    int _campoAnterior;
    bool _error;
    std::string _mensajeError;
    bool _primeraRenderizacion;
    int _tipoUsuarioActual = 0; // 0: Estudiante, 1: Organización

    // Coordenadas para dibujar
    COORD _coordsElementosUserInput[ELEMENTOS_INPUT] = { {11, 15}, {11, 20}, {11, 25}, {63, 25} };
    COORD _coordsBotones[CANT_BOTONES] = { {68, 20}, {90, 20}, {53, 29} };
    const std::string _textosBotones[CANT_BOTONES] = { " Soy un Estudiante ", " Soy una Organizacion ", " Crear Cuenta "};
    const std::string _etiquetas[ELEMENTOS_INPUT] = { " ", " ", " ", " " };

    void mostrarCursor(bool mostrar) {
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        cursorInfo.bVisible = mostrar;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    }    
    
    void renderizarCampo(const std::string& _etiqueta, const std::string& _valor, int _indice, bool _seleccionado) {
        gotoXY(_coordsElementosUserInput[_indice].X, _coordsElementosUserInput[_indice].Y);

        if (_seleccionado) {
            setConsoleColor(15, 4, true, true);
            mostrarCursor(true);
        }
        else {
            setConsoleColor(15, 0, false, false);
            mostrarCursor(false);
        }        if (_indice == 2 || _indice == 3) // Contraseña
            std::cout << std::string(_valor.length(), '*');
        else
            std::cout << _valor;

        setConsoleColor(15, 0); // Restaurar color normal
    }    void renderizarBoton(const std::string& _texto, int _indice, bool _seleccionado) {
        gotoXY(_coordsBotones[_indice].X, _coordsBotones[_indice].Y);

        // Resaltar botones de tipo usuario basado en la selección actual o el tipo activo
        if (_indice == 0 || _indice == 1) {
            if (_seleccionado || (_indice == 0 && _tipoUsuarioActual == 0) || (_indice == 1 && _tipoUsuarioActual == 1)) {
                setConsoleColor(15, 4, true, true);
            }
            else {
                setConsoleColor(15, 13, false, true);
            }
        }
        else {
            if (_seleccionado) {
                setConsoleColor(15, 5, true, true);
            }
            else {
                setConsoleColor(15, 5, false, false);
            }
        }        //mostrarCursor(false);
        std::cout << _texto;
        setConsoleColor(15, 0);
    }

    void dibujarInterfazCompleta() {
        system("cls");
        UI_Signup();        for (int i = 3; i <= 7; i++) {
            gotoXY(3, i);
            setConsoleColor(1, 13, true);
            std::cout << std::string(114, ' ');
        }

        setConsoleColor(12, 13, true, true);
        gotoXY(42, 4);    std::cout << "▒█▀▀█ █▀▀█ █░░█ █▀▀█ █▀▀ █▀▀ █▀▀█ █▀▀█";
        gotoXY(42, 5);    std::cout << "▒█░░░ █░░█ █░░█ █▄▄▀ ▀▀█ █▀▀ █▄▄▀ █▄▄█";
        gotoXY(42, 6);    std::cout << "▒█▄▄█ ▀▀▀▀ ░▀▀▀ ▀░▀▀ ▀▀▀ ▀▀▀ ▀░▀▀ ▀░░▀";

        setConsoleColor(12, 13, true, true);
        gotoXY(71, 7);    std::cout << "C L O N E";
        for (int i = 0; i < ELEMENTOS_INPUT; ++i) {
            std::string valor = (i == 2) ? std::string(_password.length(), '*') : (i == 3) ? std::string(_confirmarPassword.length(), '*') : (i == 0) ? _nombre : _email;
            renderizarCampo(_etiquetas[i], (i == 0) ? _nombre : (i == 1) ? _email : (i == 2) ? _password : _confirmarPassword, i, _campoActual == i);
        }
        //renderizarTipoUsuario();
        for (int i = 0; i < CANT_BOTONES; ++i) {
            renderizarBoton(_textosBotones[i], i, _campoActual == i + ELEMENTOS_INPUT);
        }
        if (_error) {
            gotoXY(20, 23);
            setConsoleColor(1, 4);
            std::cout << _mensajeError;
            setConsoleColor(15, 1);
        }   setConsoleColor(15, 1);
        }

        setConsoleColor(15, 0);
    }    void actualizarSeleccion() {
        // Actualizar selección de botones
        for (int i = 0; i < CANT_BOTONES; ++i) {
            renderizarBoton(_textosBotones[i], i, _campoActual == i + ELEMENTOS_INPUT);
        }

        if (_campoAnterior >= 0 && _campoAnterior < ELEMENTOS_INPUT) {
            renderizarCampo(_etiquetas[_campoAnterior], (_campoAnterior == 0) ? _nombre : (_campoAnterior == 1) ? _email : (_campoAnterior == 2) ? _password : _confirmarPassword, _campoAnterior, false);
        }
        if (_campoActual >= 0 && _campoActual < ELEMENTOS_INPUT) {
            renderizarCampo(_etiquetas[_campoActual], (_campoActual == 0) ? _nombre : (_campoActual == 1) ? _email : (_campoActual == 2) ? _password : _confirmarPassword, _campoActual, true);
        }

        _campoAnterior = _campoActual;
        setConsoleColor(15, 0);
    }    bool validarCampos() {
        Usuario temp;
        if (_nombre.empty() || _email.empty() || _password.empty() || _confirmarPassword.empty()) {
            _error = true;
            _mensajeError = "Todos los campos son obligatorios";
            return false;
        }
        if (temp.buscarIndexUsuario(_email, _tipoUsuario) != -1) {
            _error = true;
            _mensajeError = "El email ya está registrado";
            return false;
        }
        if (_password != _confirmarPassword) {
            _error = true;
            _mensajeError = "Las contraseñas no coinciden";
            return false;
        }
        if (_password.length() < 6) {            _error = true;
            _mensajeError = "La contraseña debe tener al menos 6 caracteres";
            return false;
        }
        return true;
    }

    void guardarUsuario() {
        Usuario nuevo;
        nuevo.setNombre(_nombre);
        nuevo.setUsername(_email);
        nuevo.setContrasena(_password);
        nuevo.setTipoUsuario(_tipoUsuario);
        nuevo.guardar();
    }

public:
    RegistroScreen() : _campoActual(0), _campoAnterior(-1), _error(false), _primeraRenderizacion(true), _tipoUsuario(TipoUsuario::ESTUDIANTE) {}

    ResultadoPantalla ejecutar() override 
    {
        ResultadoPantalla res;        while (true) 
        {
            if (_primeraRenderizacion) 
            {
                dibujarInterfazCompleta();
				mostrarCursor(true);
                _primeraRenderizacion = false;
                gotoXY(11, 15);
            } else {
                actualizarSeleccion();
            }

            int tecla = _getch();
            switch (tecla) 
            {
                case 72: // Flecha arriba
                    //if (_campoActual > 0) _campoActual--;

                    if (_campoActual == 2) { // Si estamos en el campo de contraseña
                        _campoActual = ELEMENTOS_INPUT + 1; // Ir al botón de Organización
                    }
                    else if (_campoActual == 3) { // Si estamos en confirmar contraseña
                        _campoActual = 2; // Ir a contraseña
                    }
                    else if (_campoActual == ELEMENTOS_INPUT + 2) { // Si estamos en Crear Cuenta
                        _campoActual = 3; // Ir a confirmar contraseña
                    }
                    else if (_campoActual == ELEMENTOS_INPUT) { // Si estamos en botón Estudiante
                        _campoActual = 1; // Ir al campo de email
                    }
                    else if (_campoActual == ELEMENTOS_INPUT + 1) { // Si estamos en botón Organización
                        _campoActual = ELEMENTOS_INPUT; // Ir al campo de esrudiante                    }
                    else if (_campoActual > 0) { // Para el resto de casos
                        _campoActual--;
                    }
                    break;
                case 80: // Flecha abajo
                    //if (_campoActual < ELEMENTOS_INPUT + CANT_BOTONES - 1) _campoActual++;

                    if (_campoActual == 1) { // Si estamos en el campo de email
                        _campoActual = ELEMENTOS_INPUT; // Ir al botón de Estudiante
                    }
                    else if (_campoActual == ELEMENTOS_INPUT) { // Si estamos en estudiante
                        _campoActual = ELEMENTOS_INPUT + 1; // Ir a confirmar organizacion
                    }
                    else if (_campoActual == ELEMENTOS_INPUT + 1) { // Si estamos en organizacion
                        _campoActual = 2; // Ir al campo de contraseña
                    }
                    else if (_campoActual == 2) { // Si estamos en contraseña
                        _campoActual = 3; // Ir a confirmar contraseña
                    }
                    else if (_campoActual == 3) { // Si estamos en confirmar contraseña
                        _campoActual = ELEMENTOS_INPUT + 2; // Ir a Crear Cuenta
                    }
                    else if (_campoActual < ELEMENTOS_INPUT - 1) { // Para el resto de casos antes de email
                        _campoActual++;
                    }
                    break;
                case 27: // ESC
                    res.accion = AccionPantalla::IR_A_LANDING_PAGE;
                    return res;
                    break;
                case 13: // Enter
                    if (_campoActual == ELEMENTOS_INPUT) {
                        _tipoUsuarioActual = 0;
                        _tipoUsuario = TipoUsuario::ESTUDIANTE;
                    }
                    else if (_campoActual == ELEMENTOS_INPUT + 1) { // Si estamos en organizacion
                        _tipoUsuarioActual = 1; 
                        _tipoUsuario = TipoUsuario::EMPRESA;
                    }
                    else if (_campoActual == ELEMENTOS_INPUT + 2) { // Registrar
                        _tipoUsuario = (_tipoUsuarioActual == 0) ? TipoUsuario::ESTUDIANTE : TipoUsuario::EMPRESA;
                        if (validarCampos()) {
                            guardarUsuario();
                            //ResultadoPantalla res;
                            res.accion = AccionPantalla::IR_A_LOGIN;
                            return res;
                        }
                        else {
                            dibujarInterfazCompleta();
                            continue;
                        }
                    }
                    break;                case 8: // Backspace
                    if (_campoActual >= 0 && _campoActual < ELEMENTOS_INPUT) 
                    {
                        std::string* campo = nullptr;
                        switch (_campoActual) {
                            case 0: campo = &_nombre; break;
                            case 1: campo = &_email; break;
                            case 2: campo = &_password; break;
                            case 3: campo = &_confirmarPassword; break;
                        }
                        if (campo && !campo->empty()) 
                        {
                            campo->pop_back();
                            dibujarInterfazCompleta();
                        }
                    }
                    break;
                default:
                    if (tecla >= 32 && tecla <= 126) 
                    {
                        std::string* campo = nullptr;
                        switch (_campoActual) {
                            case 0: campo = &_nombre; break;
                            case 1: campo = &_email; break;
                            case 2: campo = &_password; break;
                            case 3: campo = &_confirmarPassword; break;
                        }
                        if (campo) {
                            campo->push_back(static_cast<char>(tecla));
                            dibujarInterfazCompleta();
                        }
                    }
                    break;
            }
            _error = false;
        }
    }
};

#endif // COURSERACLONE_SCREENS_REGISTROSCREEN_HPP