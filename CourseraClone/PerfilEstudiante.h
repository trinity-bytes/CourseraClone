#pragma once

#include "Pantalla.h"
#include "ExtendedFunctions.h"
#include "UI_Ascii.h"
#include "Estudiante.h"
#include <string>

class PerfilEstudiante : public PantallaBase
{
private:
    // Datos del estudiante
    int idEstudiante;
    std::string nombreEstudiante;
    std::string correoEstudiante;

    // Estado actual
    bool primeraRenderizacion;

    // Coordenadas para dibujar
    const int COL_ETIQUETA = 22;
    const int FILA_ID = 16; 
    const int FILA_NOMBRE = 20;
    const int FILA_CORREO = 24;

    void dibujarInterfazCompleta() {
        system("cls");
        // Dibujar marco y título
        UI_UserProfile();

        // Datos del estudiante
        gotoXY(COL_ETIQUETA, FILA_ID);
        std::cout << "ID: " << idEstudiante;

        gotoXY(COL_ETIQUETA, FILA_NOMBRE);
        std::cout << "NOMBRE: " << nombreEstudiante;

        gotoXY(COL_ETIQUETA, FILA_CORREO);
        std::cout << "CORREO: " << correoEstudiante << "@gmail.com";
    }

public:
    PerfilEstudiante(int _idEstudiante, std::string _nombreEstudiante, std::string _correoEstudiante)
        : idEstudiante(_idEstudiante),
        nombreEstudiante(_nombreEstudiante),
        correoEstudiante(_correoEstudiante),
        primeraRenderizacion(true) {
    }

    ResultadoPantalla ejecutar() override {
        if (primeraRenderizacion) {
            dibujarInterfazCompleta();
            primeraRenderizacion = false;
        }

        ResultadoPantalla res;

        while (true) {
            int tecla = _getch();

            if (tecla == 27) { // ESC para volver
                res.accion = AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE;
                return res;
            }
        }
    }
};