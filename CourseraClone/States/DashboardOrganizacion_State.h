#pragma once
#include "Menu_State.h"
#include "../UI_Ascii.h"
#include "../ExtendedFunctions.h"
#include "../Controladora.h"
//#include "CrearEspecializacionState.h"
#include <vector>
#include <string>

class DashboardOrganizacionState : public MenuState {
private:
    static const int OPCION_CREAR_CURSO = 0;
    static const int OPCION_CREAR_ESPECIALIZACION = 1;
    static const int OPCION_CERRAR_SESION = 2;
    static const int TOTAL_OPCIONES = 3;

    int opcionActual;
    int opcionAnterior;
    bool primeraRenderizacion;
    Controladora* controladora;
    void actualizarSeleccion() {
        if (opcionActual != opcionAnterior) {
            // Desdibujar selección anterior
            actualizarOpcion(opcionAnterior, false);
            // Dibujar nueva selección
            actualizarOpcion(opcionActual, true);
            opcionAnterior = opcionActual;
        }
    }

    void actualizarOpcion(int opcion, bool seleccionado) {
        COORD coord = {11, 15 + opcion};
        gotoXY(coord.X, coord.Y);
        if (seleccionado) SetConsoleColor(1, 4);
        else SetConsoleColor(15, 1);

        switch (opcion) {
            case OPCION_CREAR_CURSO:
                cout << "[Crear Nuevo Curso]";
                break;
            case OPCION_CREAR_ESPECIALIZACION:
                cout << "[Crear Nueva Especialización]";
                break;
            case OPCION_CERRAR_SESION:
                cout << "[Cerrar Sesión]";
                break;
        }
        SetConsoleColor(15, 1);
    }

    void dibujarInterfazCompleta() {
        system("cls");
        gotoXY(11, 12);
        cout << "Dashboard de Organización";
        gotoXY(11, 13);
        cout << "----------------------";

        // Dibujar todas las opciones
        for (int i = 0; i < TOTAL_OPCIONES; i++) {
            actualizarOpcion(i, i == opcionActual);
        }
    }

public:
    DashboardOrganizacionState(Controladora* controladora) : MenuState(controladora) {
        opcionActual = 0;
        opcionAnterior = 0;
        primeraRenderizacion = true;
        controladora = new Controladora();
    }

    void render() override {
        if (primeraRenderizacion) {
            dibujarInterfazCompleta();
            primeraRenderizacion = false;
        }
        else {
            actualizarSeleccion();
        }
    }

    void handleInput(int tecla) override {
        switch (tecla) {
            case VK_UP:
                if (opcionActual > 0) {
                    opcionActual--;
                    dibujarInterfazCompleta();
                }
                break;
            case VK_DOWN:
                if (opcionActual < TOTAL_OPCIONES - 1) {
                    opcionActual++;
                    dibujarInterfazCompleta();
                }
                break;
            case VK_RETURN:
                switch (opcionActual) {
                    case OPCION_CREAR_CURSO:
                        //nextState = make_unique<CrearCursoState>(controladora);
                        break;
                    case OPCION_CREAR_ESPECIALIZACION:
                        //nextState = make_unique<CrearEspecializacionState>(controladora);
                        break;
                    case OPCION_CERRAR_SESION:
                        controladora->cerrarSesion();
                        break;
                }
                break;
        }
    }

    unique_ptr<MenuState> getNextState() override {
        return move(nextState);
    }

private:
    unique_ptr<MenuState> nextState;
}; 