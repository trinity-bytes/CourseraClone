#pragma once

#include <memory>
#include "string"

class Controladora; // Declaración anticipada de Controladora

/// Estructuras de datos
struct ElementoMenu
{
    std::string titulo;
    std::string descripcion; // Usado para especialidades y cursos
};

// Estado base abstracto
class MenuState
{
protected:
    Controladora* controladora;
public:
    MenuState(Controladora* ctrl) : controladora(ctrl) {}
    virtual void handleInput(int tecla) = 0; // Método para manejar la entrada
    virtual void render() = 0; // Método para renderizar
    virtual void renderInicial() = 0; // Metodo para renderizado inicial
    virtual void renderUpdate() = 0;  // Metodo para actualizaciones
    virtual std::unique_ptr<MenuState> getNextState() = 0;
    virtual ~MenuState() = default;
};