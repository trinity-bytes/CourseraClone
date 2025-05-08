#pragma once

#include "Menu_State.h"
#include <string>

class Controladora;

/// Estado de Login
class LoginState : public MenuState
{
private:
    bool primeraRenderizacion;
    std::string username;
    std::string password;
    int campoActual; // 0: username, 1: password

public:
    explicit LoginState(Controladora* ctrl);
    void handleInput(int tecla) override;
    void render() override;
    void renderInicial() override;
    void renderUpdate() override;
    std::unique_ptr<MenuState> getNextState() override;
};