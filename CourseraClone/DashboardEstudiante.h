#pragma once

#include "Pantalla.h"
#include "ExtendedFunctions.h"
#include <vector>
#include <string>

class DashboardEstudiante : public PantallaBase {
private:
    // Constantes del menú
    static const int SECCION_CURSOS_INSCRITOS = 0;
    static const int SECCION_CERTIFICADOS = 1;
    static const int SECCION_BOLETAS = 2;
    static const int SECCION_PERFIL = 3;
    static const int TOTAL_SECCIONES = 4;

    // Elementos del menú
    const std::vector<std::string> ELEMENTOS_MENU = {
        " Mis Cursos ",
        " Certificados ",
        " Boletas ",
        " Mi Perfil "
    };

    // Coordenadas para dibujar
    COORD coordsElementosMenu[TOTAL_SECCIONES] = {
        {67, 3},  // Cursos
        {84, 3},  // Certificados
        {98, 3},  // Boletas
        {112, 3}  // Perfil
    };

    // Estado actual
    int seccionActual;
    int elementoActual;
    int seccionAnterior;
    int elementoAnterior;
    bool primeraRenderizacion;

    void actualizarElementoMenu(int indice, bool seleccionado) {
        if (indice < 0 || indice >= TOTAL_SECCIONES) return;
        gotoXY(coordsElementosMenu[indice].X, coordsElementosMenu[indice].Y);
        if (seleccionado) setColor(Colors::SELECCION);
        else setColor(Colors::NORMAL);
        std::cout << ELEMENTOS_MENU[indice];
        setColor(Colors::NORMAL);
    }

    void dibujarInterfazCompleta() {
        for (int i = 0; i < TOTAL_SECCIONES; ++i) {
            actualizarElementoMenu(i, seccionActual == i);
        }
        // Aquí puedes dibujar el contenido de la sección seleccionada
    }

    void actualizarSeleccion() {
        // Aquí puedes actualizar la selección visual si lo deseas
    }

public:
    DashboardEstudiante() : seccionActual(0), elementoActual(0), seccionAnterior(0), elementoAnterior(0), primeraRenderizacion(true) {}

    ResultadoPantalla ejecutar() override {
        while (true) {
            if (primeraRenderizacion) {
                system("cls");
                dibujarInterfazCompleta();
                primeraRenderizacion = false;
            } else {
                actualizarSeleccion();
            }

            int tecla = _getch();
            switch (tecla) {
                case 224: // Tecla extendida
                    tecla = _getch();
                    switch (tecla) {
                        case 75: // Flecha izquierda
                            if (seccionActual > 0) seccionActual--;
                            break;
                        case 77: // Flecha derecha
                            if (seccionActual < TOTAL_SECCIONES - 1) seccionActual++;
                            break;
                    }
                    break;
                case 27: // ESC
                {
                    ResultadoPantalla res;
                    res.accion = AccionPantalla::IR_A_LANDING_PAGE;
                    return res;
                }
            }
        }
    }
}; 