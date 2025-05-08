#include "Login_State.h"
#include "Controladora.h"
#include "ExtendedFunctions.h"
#include "UI_Ascii.h"
#include <iostream>

LoginState::LoginState(Controladora* ctrl) : MenuState(ctrl),
    primeraRenderizacion(true), campoActual(0) { }

void LoginState::handleInput(int tecla) {
    if (tecla == 13) { // Enter
        if (campoActual == 0) {
            campoActual = 1;
        }
        else {
            // Intentar login
            if (controladora->iniciarSesion(username, password)) {
                // Login exitoso
            }
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

void LoginState::render() {
    if (primeraRenderizacion) {
        renderInicial();
        primeraRenderizacion = false;
    }
    else {
        renderUpdate();
    }
}

void LoginState::renderInicial() {
    system("cls");
    UI_Login();
}

void LoginState::renderUpdate() {
    // Actualizar solo los campos de entrada
    gotoXY(67, 15);
    std::cout << std::string(30, ' '); // Limpiar área
    gotoXY(67, 15);
    std::cout << username;

    gotoXY(67, 20);
    std::cout << std::string(30, ' '); // Limpiar área
    gotoXY(67, 20);
    std::cout << std::string(password.length(), '*');
}

std::unique_ptr<MenuState> LoginState::getNextState() {
    // Retornar al estado anterior o al dashboard según el resultado del login
    return nullptr;
} 