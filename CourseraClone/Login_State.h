#pragma once
#include "Controladora.h"
#include "UI_Ascii.h"
#include "Menu_State.h"
#include "ExtendedFunctions.h"
#include "LandingPage_State.h"

/// Estado de Login
class LoginState : public MenuState
{
private:
    bool primeraRenderizacion;
    string username;
    string password;
    int campoActual; // 0: username, 1: password

public:
    // Constructor por defecto
    LoginState(Controladora* ctrl) : MenuState(ctrl),
        primeraRenderizacion(true), campoActual(0) {
    }

    void handleInput(int tecla) override
    {
        if (tecla == 13) { // Enter
            if (campoActual == 0) {
                campoActual = 1;
            }
            else {
                // Intentar login
            }
        }
        else if (tecla == 8) { // Backspace
            if (campoActual == 0 && !username.empty()) {
                username.pop_back();
            }
            else if (campoActual == 1 && !password.empty()) {
                password.pop_back();
            }
        }
        else if (tecla >= 32 && tecla <= 126) { // Caracteres imprimibles
            if (campoActual == 0) {
                username += (char)tecla;
            }
            else {
                password += (char)tecla;
            }
        }
        renderUpdate();
    }

    void render() override {
        if (primeraRenderizacion) {
            renderInicial();
            primeraRenderizacion = false;
        }
        else {
            renderUpdate();
        }
    }

    void renderInicial() override
    {
        system("cls");
        UI_Login();
    }

    void renderUpdate() override
    {
        // Actualizar solo los campos de entrada
        gotoXY(67, 15);
        cout << string(30, ' '); // Limpiar �rea
        gotoXY(67, 15);
        cout << username;

        gotoXY(67, 20);
        cout << string(30, ' '); // Limpiar �rea
        gotoXY(67, 20);
        cout << string(password.length(), '*');
    }

    std::unique_ptr<MenuState> getNextState() override
    {
        // Retornar al estado anterior o al dashboard seg�n el resultado del login
        return std::make_unique<LandingPageState>(controladora);
    }
};