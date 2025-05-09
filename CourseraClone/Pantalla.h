#pragma once

// Headers propios
//#include "Controladora.h"
#include "UI_Ascii.h"
#include "ExtendedFunctions.h"
#include "Utils.h"

// Headers de librerías
#include <string>
#include <vector>
#include <memory>

// Declaracion anticipada de la clase Controladora
class Controladora;

// Enumeración de pantallas disponibles
enum class Pantalla {
    NONE,
    LANDING_PAGE,
    LOGIN,
    REGISTRO,
    DASHBOARD_ESTUDIANTE,
    DASHBOARD_EMPRESA,
    DETALLE_CURSO,
    DETALLE_ESPECIALIDAD
};

// Clase base para todas las pantallas
class PantallaBase {
protected:
    Controladora* controladora;
    Pantalla pantallaActual;
    Pantalla siguientePantalla;
    bool primeraRenderizacion;

public:
    PantallaBase(Controladora* ctrl) 
        : controladora(ctrl), pantallaActual(Pantalla::NONE), siguientePantalla(Pantalla::NONE), primeraRenderizacion(true) {}
    
    virtual ~PantallaBase() = default;

    // Métodos virtuales que deben implementar todas las pantallas
    virtual void renderizar() = 0;
    virtual void manejarInput(int tecla) = 0;

    // Método para limpiar la pantalla
    void limpiarPantalla() {
        system("cls");
    }

    // Método para actualizar el estado de primera renderización
    void setPrimeraRenderizacion(bool valor) {
        primeraRenderizacion = valor;
    }

    // Método para obtener la pantalla actual
    Pantalla getPantallaActual() const {
        return pantallaActual;
    }

    // Método para obtener la siguiente pantalla
    virtual Pantalla getSiguientePantalla()  {
        return siguientePantalla;
    }

protected:
    void cambiarPantalla(Pantalla nuevaPantalla) {
        siguientePantalla = nuevaPantalla;
    }
}; 