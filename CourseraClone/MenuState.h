#pragma once
#include "Controladora.h"

/// Estructuras de datos
struct ElementoMenu
{
    string titulo;
    string descripcion; // Usado para especialidades y cursos
};

// Estado base abstracto
class MenuState
{
protected:
    Controladora* controladora;
public:
    MenuState(Controladora* ctrl) : controladora(ctrl) {}
    virtual void handleInput(int tecla) = 0; // M�todo para manejar la entrada
    virtual void render() = 0; // M�todo para renderizar
    virtual void renderInicial() = 0; // Metodo para renderizado inicial
    virtual void renderUpdate() = 0;  // Metodo para actualizaciones
    virtual std::unique_ptr<MenuState> getNextState() = 0;
    virtual ~MenuState() = default;
};