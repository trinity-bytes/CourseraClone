#pragma once

#include "Menu_State.h"
#include "UI_Ascii.h"
#include "ExtendedFunctions.h"
#include <string>
#include <memory>
#include <conio.h> // Add this include for _getch()


// Forward declarations
class Controladora;
class LandingPageState;

/// Estado de Login
class LoginState : public MenuState
{
private:
    // Constantes del formulario
    static const int CAMPO_EMAIL = 0;
    static const int CAMPO_PASSWORD = 1;
    static const int CAMPO_LOGIN = 2;
    static const int CAMPO_VOLVER = 3;
    static const int TOTAL_CAMPOS = 4;

    // Coordenadas para dibujar
    const COORD COORD_EMAIL = {11, 15};
    const COORD COORD_PASSWORD = {11, 18};
    const COORD COORD_LOGIN = {11, 21};
    const COORD COORD_VOLVER = {11, 24};

    // Estado del formulario
    int campoActual;
    int campoAnterior;
    bool primeraRenderizacion;
    bool editando;

    // Datos del login
    std::string email;
    std::string password;
    std::string error;

    void actualizarSeleccion() {
        if (campoActual != campoAnterior) {
            // Desdibujar selección anterior
            actualizarCampo(campoAnterior, false);
            // Dibujar nueva selección
            actualizarCampo(campoActual, true);
            campoAnterior = campoActual;
        }
    }

    void actualizarCampo(int campo, bool seleccionado) {
        COORD coord;
        std::string texto;
        bool esEditable = false;

        switch (campo) {
            case CAMPO_EMAIL:
                coord = COORD_EMAIL;
                texto = "Email: " + (editando && campoActual == CAMPO_EMAIL ? email + "_" : email);
                esEditable = true;
                break;
            case CAMPO_PASSWORD:
                coord = COORD_PASSWORD;
                texto = "Contraseña: " + (editando && campoActual == CAMPO_PASSWORD ? std::string(password.length(), '*') + "_" : std::string(password.length(), '*'));
                esEditable = true;
                break;
            case CAMPO_LOGIN:
                coord = COORD_LOGIN;
                texto = "[Iniciar Sesión]";
                break;
            case CAMPO_VOLVER:
                coord = COORD_VOLVER;
                texto = "[Volver]";
                break;
        }

        gotoXY(coord.X, coord.Y);
        if (seleccionado) {
            SetConsoleColor(1, 4); // Fondo azul, texto blanco
        } else {
            SetConsoleColor(15, 1); // Fondo negro, texto blanco
        }
        std::cout << texto;
        SetConsoleColor(15, 1); // Restaurar colores
    }

    void dibujarInterfazCompleta() {
        system("cls");
        UI_Login();

        // Dibujar todos los campos
        for (int i = 0; i < TOTAL_CAMPOS; i++) {
            actualizarCampo(i, i == campoActual);
        }

        // Dibujar mensaje de error si existe
        if (!error.empty()) {
            gotoXY(11, 26);
            SetConsoleColor(12, 1); // Rojo
            std::cout << "Error: " << error;
            SetConsoleColor(15, 1);
        }
    }

    bool validarFormulario() {
        if (email.empty()) {
            error = "El email es requerido";
            return false;
        }
        if (password.empty()) {
            error = "La contraseña es requerida";
            return false;
        }
        return true;
    }

    void intentarLogin() {
        if (!validarFormulario()) {
            dibujarInterfazCompleta();
            return;
        }

        if (controladora->iniciarSesion(email, password)) {
            // Login exitoso, el controlador manejará el cambio de estado
            error = "";
        } else {
            error = "Credenciales inválidas";
            dibujarInterfazCompleta();
        }
    }

public:
    explicit LoginState(Controladora* ctrl) : MenuState(ctrl) {
        campoActual = 0;
        campoAnterior = 0;
        primeraRenderizacion = true;
        editando = false;
        error = "";
    }

    void handleInput(int tecla) override {
        if (editando) {
            if (tecla == 13) { // Enter
                editando = false;
                dibujarInterfazCompleta();
            } else if (tecla == 8) { // Backspace
                if (campoActual == CAMPO_EMAIL && !email.empty()) {
                    email.pop_back();
                } else if (campoActual == CAMPO_PASSWORD && !password.empty()) {
                    password.pop_back();
                }
                dibujarInterfazCompleta();
            } else if (tecla >= 32 && tecla <= 126) { // Caracteres imprimibles
                if (campoActual == CAMPO_EMAIL) {
                    email += static_cast<char>(tecla);
                } else if (campoActual == CAMPO_PASSWORD) {
                    password += static_cast<char>(tecla);
                }
                dibujarInterfazCompleta();
            }
            return;
        }

        switch (tecla) {
            case 224: // Tecla extendida
                tecla = _getch();
                switch (tecla) {
                    case 72: // Flecha arriba
                        if (campoActual > 0) campoActual--;
                        break;
                    case 80: // Flecha abajo
                        if (campoActual < TOTAL_CAMPOS - 1) campoActual++;
                        break;
                }
                actualizarSeleccion();
                break;
            case 13: // Enter
                if (campoActual == CAMPO_EMAIL || campoActual == CAMPO_PASSWORD) {
                    editando = true;
                    dibujarInterfazCompleta();
                } else if (campoActual == CAMPO_LOGIN) {
                    intentarLogin();
                } else if (campoActual == CAMPO_VOLVER) {
                    // Volver al landing page
                    controladora->cambiarEstado(std::make_unique<LandingPageState>(controladora));
                }
                break;
            case 27: // ESC
                controladora->cambiarEstado(std::make_unique<LandingPageState>(controladora));
                break;
        }
    }

    void render() override {
        if (primeraRenderizacion) {
            dibujarInterfazCompleta();
            primeraRenderizacion = false;
        } else {
            actualizarSeleccion();
        }
    }

    void renderInicial() override {
        dibujarInterfazCompleta();
    }

    void renderUpdate() override {
        actualizarSeleccion();
    }

    std::unique_ptr<MenuState> getNextState() override {
        // El controlador manejará el cambio de estado después del login exitoso
        return nullptr;
    }
};