#pragma once

// Headers de librería estándar
#include <iostream>
#include <string>

// Headers propios
#include "../Entities/Empresa.h"
#include "../Entities/Estudiante.h"
#include "../Entities/Usuario.h"
#include "../Utils/SystemUtils.h"
#include "../Utils/ScreenSystem.h"
#include "../Utils/UI_Ascii.h"

class EditarPerfilScreen : public PantallaBase
{
private:
    // Constantes para campos de entrada
    static const int CAMPO_NOMBRE = 0;
    static const int CAMPO_EMAIL = 1;
    static const int CAMPO_PASSWORD = 2;
    static const int CAMPO_CONFIRMAR_PASSWORD = 3;
    static const int CAMPO_GUARDAR = 4;    
    static const int TOTAL_CAMPOS = 5;

    // Datos del usuario
    int idUsuario;
    TipoUsuario tipoUsuario;
    std::string nombreOriginal;
    std::string emailOriginal;
    std::string passwordOriginal;

    // Datos modificables
    std::string nombre;
    std::string email;
    std::string password;
    std::string confirmarPassword;

    // Estado actual
    int campoActual;
    int campoAnterior;
    bool primeraRenderizacion;
    bool error;
    std::string mensajeError;

    // Coordenadas para dibujar
    const COORD coordsCampos[TOTAL_CAMPOS] = {
        {11, 15}, // Nombre
        {11, 20}, // Email (sin @gmail.com)
        {11, 25}, // Password
        {63, 25}, // Confirmar Password
        {52, 29}  // Botón Guardar
    };

    void mostrarCursor(bool mostrar) {
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        cursorInfo.bVisible = mostrar;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    }

    void dibujarInterfazCompleta() {
        system("cls");
        UI_UserUpdateData();        // Mostrar valores actuales
        renderizarCampo(CAMPO_NOMBRE, nombre, campoActual == CAMPO_NOMBRE);
        renderizarCampo(CAMPO_EMAIL, email, campoActual == CAMPO_EMAIL);
        renderizarCampo(CAMPO_PASSWORD, std::string(password.length(), '*'), campoActual == CAMPO_PASSWORD);
        renderizarCampo(CAMPO_CONFIRMAR_PASSWORD, std::string(confirmarPassword.length(), '*'), campoActual == CAMPO_CONFIRMAR_PASSWORD);
        renderizarBotonGuardar(campoActual == CAMPO_GUARDAR);

        if (error) {
            gotoXY(coordsCampos[CAMPO_GUARDAR].X - 200, coordsCampos[CAMPO_GUARDAR].Y + 40);
            setConsoleColor(1, 4);
            std::cout << mensajeError;
            setConsoleColor(15, 0);
        }
    }    void renderizarCampo(int campo, const std::string& valor, bool seleccionado) {
        gotoXY(coordsCampos[campo].X, coordsCampos[campo].Y);

        // Limpiar el área
        if (campo == CAMPO_NOMBRE) {
            std::cout << std::string(60, ' ');
            gotoXY(coordsCampos[campo].X, coordsCampos[campo].Y);
        }

        if (seleccionado) {
            setConsoleColor(1, 13);
            mostrarCursor(true);
        }
        else {
            setConsoleColor(15, 0);
            mostrarCursor(false);
        }

        std::cout << valor;
        setConsoleColor(15, 0);
    }

    void renderizarBotonGuardar(bool seleccionado) {
        gotoXY(coordsCampos[CAMPO_GUARDAR].X, coordsCampos[CAMPO_GUARDAR].Y);

        if (seleccionado) {
            setConsoleColor(1, 13);
        }
        else {
            setConsoleColor(15, 0);
        }        std::cout << "GUARDAR CAMBIOS";
        setConsoleColor(15, 0);
    }

    void actualizarSeleccion() {
        if (campoAnterior >= 0 && campoAnterior < TOTAL_CAMPOS) {
            if (campoAnterior == CAMPO_GUARDAR) {
                renderizarBotonGuardar(false);
            }
            else {
                std::string valor;
                switch (campoAnterior) {
                case CAMPO_NOMBRE: valor = nombre; break;
                case CAMPO_EMAIL: valor = email; break;
                case CAMPO_PASSWORD: valor = std::string(password.length(), '*'); break;
                case CAMPO_CONFIRMAR_PASSWORD: valor = std::string(confirmarPassword.length(), '*'); break;
                }
                renderizarCampo(campoAnterior, valor, false);
            }
        }

        if (campoActual >= 0 && campoActual < TOTAL_CAMPOS) {
            if (campoActual == CAMPO_GUARDAR) {
                renderizarBotonGuardar(true);
            }
            else {
                std::string valor;
                switch (campoActual) {
                case CAMPO_NOMBRE: valor = nombre; break;
                case CAMPO_EMAIL: valor = email; break;
                case CAMPO_PASSWORD: valor = std::string(password.length(), '*'); break;
                case CAMPO_CONFIRMAR_PASSWORD: valor = std::string(confirmarPassword.length(), '*'); break;
                }
                renderizarCampo(campoActual, valor, true);
            }
        }

        campoAnterior = campoActual;
    }

    bool validarCampos() {
        // Validar que los campos no están vacíos
        if (nombre.empty() || email.empty()) {
            error = true;
            mensajeError = "El nombre y el email son obligatorios";
            return false;
        }

        // Validar que las contraseñas coincidan si se están modificando
        if (!password.empty() && password != confirmarPassword) {
            error = true;
            mensajeError = "Las contraseñas no coinciden";
            return false;
        }

        // Validar longitud mínima de contraseña si se está modificando
        if (!password.empty() && password.length() < 6) {
            error = true;
            mensajeError = "La contraseña debe tener al menos 6 caracteres";
            return false;
        }

        // Validar que el email no está ya en uso (excepto si es el mismo usuario)
        if (email != emailOriginal) {
            Usuario temp;
            int index = temp.buscarIndexUsuario(email, tipoUsuario);
            if (index != -1 && index != idUsuario) {
                error = true;
                mensajeError = "Este email ya está en uso por otro usuario";
                return false;
            }
        }

        return true;
    }    void guardarCambios() {
        // Acceso a través de la controladora
        if (tipoUsuario == TipoUsuario::ESTUDIANTE) {
            // Lógica para actualizar estudiante a través de la controladora
            // _controladora->actualizarEstudiante(idUsuario, nombre, email, password);
        }
        else if (tipoUsuario == TipoUsuario::EMPRESA) {
            // Lógica para actualizar empresa a través de la controladora
            // _controladora->actualizarEmpresa(idUsuario, nombre, email, password);
        }
    }

public:
    EditarPerfilScreen(Controladora* _controladora, int _idUsuario, TipoUsuario _tipoUsuario, 
        const std::string& _nombre, const std::string& _email)
        : PantallaBase(_controladora),
        idUsuario(_idUsuario),
        tipoUsuario(_tipoUsuario),
        nombreOriginal(_nombre),
        emailOriginal(_email),
        nombre(_nombre),
        email(_email),
        password(""),
        confirmarPassword(""),
        campoActual(0),
        campoAnterior(-1),
        primeraRenderizacion(true),
        error(false) {
    }    ResultadoPantalla ejecutar() override {
        while (true) {
            if (primeraRenderizacion) {
                dibujarInterfazCompleta();
                primeraRenderizacion = false;
                mostrarCursor(true);
            }
            else {
                actualizarSeleccion();
            }

            int tecla = _getch();
            switch (tecla) {
            case 72: // Flecha arriba
                if (campoActual > 0) {
                    // Navegación especial entre campos
                    if (campoActual == CAMPO_GUARDAR) {
                        campoActual = CAMPO_CONFIRMAR_PASSWORD;
                    }
                    else if (campoActual == CAMPO_PASSWORD || campoActual == CAMPO_CONFIRMAR_PASSWORD) {
                        campoActual = CAMPO_EMAIL;
                    }
                    else {
                        campoActual--;
                    }
                }
                break;

            case 80: // Flecha abajo
                if (campoActual < TOTAL_CAMPOS - 1) {
                    // Navegación especial entre campos
                    if (campoActual == CAMPO_EMAIL) {
                        campoActual = CAMPO_PASSWORD;
                    }
                    else if (campoActual == CAMPO_PASSWORD || campoActual == CAMPO_CONFIRMAR_PASSWORD) {
                        campoActual = CAMPO_GUARDAR;
                    }
                    else {
                        campoActual++;
                    }
                }
                break;

            case 75: // Flecha izquierda
                if (campoActual == CAMPO_CONFIRMAR_PASSWORD) {
                    campoActual = CAMPO_PASSWORD;
                }
                break;

            case 77: // Flecha derecha
                if (campoActual == CAMPO_PASSWORD) {
                    campoActual = CAMPO_CONFIRMAR_PASSWORD;
                }
                break;

            case 13: // Enter
                if (campoActual == CAMPO_GUARDAR) {
                    if (validarCampos()) {
                        guardarCambios();
                        // Redirigir al perfil correspondiente usando helpers del ScreenSystem
                        return crearResultado((tipoUsuario == TipoUsuario::ESTUDIANTE) ?
                            AccionPantalla::IR_A_PERFIL_ESTUDIANTE :
                            AccionPantalla::IR_A_PERFIL_ORGANIZACION);
                    }
                    else {
                        dibujarInterfazCompleta();
                    }
                }
                break;

            case 27: // ESC
                return crearResultado((tipoUsuario == TipoUsuario::ESTUDIANTE) ?
                    AccionPantalla::IR_A_PERFIL_ESTUDIANTE :
                    AccionPantalla::IR_A_PERFIL_ORGANIZACION);

            case 9: // Tab
                campoActual = (campoActual + 1) % TOTAL_CAMPOS;
                break;

            case 8: // Backspace
                if (campoActual >= 0 && campoActual < CAMPO_GUARDAR) {
                    std::string* campo = nullptr;
                    switch (campoActual) {
                    case CAMPO_NOMBRE: campo = &nombre; break;
                    case CAMPO_EMAIL: campo = &email; break;
                    case CAMPO_PASSWORD: campo = &password; break;
                    case CAMPO_CONFIRMAR_PASSWORD: campo = &confirmarPassword; break;
                    }
                    if (campo && !campo->empty()) {
                        campo->pop_back();
                        dibujarInterfazCompleta();
                    }
                }
                break;

            default:
                if (tecla >= 32 && tecla <= 126) { // Caracteres imprimibles
                    std::string* campo = nullptr;
                    switch (campoActual) {
                    case CAMPO_NOMBRE: campo = &nombre; break;
                    case CAMPO_EMAIL: campo = &email; break;
                    case CAMPO_PASSWORD: campo = &password; break;
                    case CAMPO_CONFIRMAR_PASSWORD: campo = &confirmarPassword; break;
                    }
                    if (campo) {
                        campo->push_back(static_cast<char>(tecla));
                        dibujarInterfazCompleta();
                    }
                }
                break;
            }
            error = false;
        }
    }
};
