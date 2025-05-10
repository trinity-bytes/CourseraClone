#pragma once

#include "Pantalla.h"
#include "ExtendedFunctions.h"
#include "UI_Ascii.h"
#include "Usuario.h"
#include "Estudiante.h"
#include "Empresa.h"
#include <string>
#include <iostream>

using namespace std;

class EditarPerfil : public PantallaBase
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
    string nombreOriginal;
    string emailOriginal;
    string passwordOriginal;

    // Datos modificables
    string nombre;
    string email;
    string password;
    string confirmarPassword;

    // Estado actual
    int campoActual;
    int campoAnterior;
    bool primeraRenderizacion;
    bool error;
    string mensajeError;

    // Coordenadas para dibujar
    const COORD coordsCampos[TOTAL_CAMPOS] = {
        {149, 337}, // Nombre
        {340, 429}, // Email (sin @gmail.com)
        {362, 521}, // Password
        {828, 521}, // Confirmar Password
        {591, 592}  // Bot�n Guardar
    };

    // Referencias a los objetos de usuario
    std::unique_ptr<Estudiante>* estudiante;
    std::unique_ptr<Empresa>* empresa;

    void mostrarCursor(bool mostrar) {
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        cursorInfo.bVisible = mostrar;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    }

    void dibujarInterfazCompleta() {
        system("cls");
        UI_UserUpdateData();

        // Mostrar valores actuales
        renderizarCampo(CAMPO_NOMBRE, nombre, campoActual == CAMPO_NOMBRE);
        renderizarCampo(CAMPO_EMAIL, email, campoActual == CAMPO_EMAIL);
        renderizarCampo(CAMPO_PASSWORD, string(password.length(), '*'), campoActual == CAMPO_PASSWORD);
        renderizarCampo(CAMPO_CONFIRMAR_PASSWORD, string(confirmarPassword.length(), '*'), campoActual == CAMPO_CONFIRMAR_PASSWORD);
        renderizarBotonGuardar(campoActual == CAMPO_GUARDAR);

        if (error) {
            gotoXY(coordsCampos[CAMPO_GUARDAR].X - 200, coordsCampos[CAMPO_GUARDAR].Y + 40);
            SetConsoleColor(1, 4);
            cout << mensajeError;
            SetConsoleColor(15, 1);
        }
    }

    void renderizarCampo(int campo, const string& valor, bool seleccionado) {
        gotoXY(coordsCampos[campo].X, coordsCampos[campo].Y);

        // Limpiar el �rea
        if (campo == CAMPO_NOMBRE) {
            cout << string(60, ' ');
            gotoXY(coordsCampos[campo].X, coordsCampos[campo].Y);
        }

        if (seleccionado) {
            SetConsoleColor(1, 13);
            mostrarCursor(true);
        }
        else {
            SetConsoleColor(15, 1);
            mostrarCursor(false);
        }

        cout << valor;
        SetConsoleColor(15, 1);
    }

    void renderizarBotonGuardar(bool seleccionado) {
        gotoXY(coordsCampos[CAMPO_GUARDAR].X, coordsCampos[CAMPO_GUARDAR].Y);

        if (seleccionado) {
            SetConsoleColor(1, 13);
        }
        else {
            SetConsoleColor(15, 1);
        }

        cout << "GUARDAR CAMBIOS";
        SetConsoleColor(15, 1);
    }

    void actualizarSeleccion() {
        if (campoAnterior >= 0 && campoAnterior < TOTAL_CAMPOS) {
            if (campoAnterior == CAMPO_GUARDAR) {
                renderizarBotonGuardar(false);
            }
            else {
                string valor;
                switch (campoAnterior) {
                case CAMPO_NOMBRE: valor = nombre; break;
                case CAMPO_EMAIL: valor = email; break;
                case CAMPO_PASSWORD: valor = string(password.length(), '*'); break;
                case CAMPO_CONFIRMAR_PASSWORD: valor = string(confirmarPassword.length(), '*'); break;
                }
                renderizarCampo(campoAnterior, valor, false);
            }
        }

        if (campoActual >= 0 && campoActual < TOTAL_CAMPOS) {
            if (campoActual == CAMPO_GUARDAR) {
                renderizarBotonGuardar(true);
            }
            else {
                string valor;
                switch (campoActual) {
                case CAMPO_NOMBRE: valor = nombre; break;
                case CAMPO_EMAIL: valor = email; break;
                case CAMPO_PASSWORD: valor = string(password.length(), '*'); break;
                case CAMPO_CONFIRMAR_PASSWORD: valor = string(confirmarPassword.length(), '*'); break;
                }
                renderizarCampo(campoActual, valor, true);
            }
        }

        campoAnterior = campoActual;
    }

    bool validarCampos() {
        // Validar que los campos no est�n vac�os
        if (nombre.empty() || email.empty()) {
            error = true;
            mensajeError = "El nombre y el email son obligatorios";
            return false;
        }

        // Validar que las contrase�as coincidan si se est�n modificando
        if (!password.empty() && password != confirmarPassword) {
            error = true;
            mensajeError = "Las contrase�as no coinciden";
            return false;
        }

        // Validar longitud m�nima de contrase�a si se est� modificando
        if (!password.empty() && password.length() < 6) {
            error = true;
            mensajeError = "La contrase�a debe tener al menos 6 caracteres";
            return false;
        }

        // Validar que el email no est� ya en uso (excepto si es el mismo usuario)
        if (email != emailOriginal) {
            Usuario temp;
            int index = temp.buscarIndexUsuario(email, tipoUsuario);
            if (index != -1 && index != idUsuario) {
                error = true;
                mensajeError = "Este email ya est� en uso por otro usuario";
                return false;
            }
        }

        return true;
    }

    void guardarCambios() {
        Usuario usuario;

        if (tipoUsuario == TipoUsuario::ESTUDIANTE && estudiante && *estudiante) {
            (*estudiante)->setNombre(nombre);
            (*estudiante)->setUsername(email);
            if (!password.empty()) {
                (*estudiante)->setContrasena(password);
            }
            (*estudiante)->guardar();
        }
        else if (tipoUsuario == TipoUsuario::EMPRESA && empresa && *empresa) {
            (*empresa)->setNombre(nombre);
            (*empresa)->setUsername(email);
            if (!password.empty()) {
                (*empresa)->setContrasena(password);
            }
            (*empresa)->guardar();
        }
    }

public:
    EditarPerfil(int _idUsuario, TipoUsuario _tipoUsuario, std::string _nombre, std::string _email,
        std::unique_ptr<Estudiante>* _estudiante = nullptr, std::unique_ptr<Empresa>* _empresa = nullptr)
        : idUsuario(_idUsuario),
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
        error(false),
        estudiante(_estudiante),
        empresa(_empresa) {
    }

    ResultadoPantalla ejecutar() override {
        ResultadoPantalla res;

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
                    // Navegaci�n especial entre campos
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
                    // Navegaci�n especial entre campos
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
                        // Redirigir al perfil correspondiente
                        res.accion = (tipoUsuario == TipoUsuario::ESTUDIANTE) ?
                            AccionPantalla::IR_A_PERFIL_ESTUDIANTE :
                            AccionPantalla::IR_A_PERFIL_ORGANIZACION;
                        return res;
                    }
                    else {
                        dibujarInterfazCompleta();
                    }
                }
                break;

            case 27: // ESC
                res.accion = (tipoUsuario == TipoUsuario::ESTUDIANTE) ?
                    AccionPantalla::IR_A_PERFIL_ESTUDIANTE :
                    AccionPantalla::IR_A_PERFIL_ORGANIZACION;
                return res;

            case 9: // Tab
                campoActual = (campoActual + 1) % TOTAL_CAMPOS;
                break;

            case 8: // Backspace
                if (campoActual >= 0 && campoActual < CAMPO_GUARDAR) {
                    string* campo = nullptr;
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
                    string* campo = nullptr;
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
