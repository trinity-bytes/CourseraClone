#pragma once

#include "Pantalla.h"
#include "ExtendedFunctions.h"
#include "UI_Ascii.h"
#include "Empresa.h"
#include <string>

class PerfilOrganizacion : public PantallaBase
{
private:
    // Datos de la organización
    int idOrganizacion;
    std::string nombreOrganizacion;
    std::string correoOrganizacion;

    // Estado actual
    bool primeraRenderizacion;

    // Coordenadas para dibujar
    const int COL_ETIQUETA = 22;
    const int FILA_ID = 15;
    const int FILA_NOMBRE = 19;
    const int FILA_CORREO = 23;

    void dibujarInterfazCompleta() {
        system("cls");
        // Dibujar marco y título
        UI_OrganizationProfile();

        // Datos de la organización
        gotoXY(COL_ETIQUETA, FILA_ID);
        std::cout << "ID: " << idOrganizacion;

        gotoXY(COL_ETIQUETA, FILA_NOMBRE);
        std::cout << "ORGANIZACION: " << nombreOrganizacion;

        gotoXY(COL_ETIQUETA, FILA_CORREO);
        std::cout << "CORREO: " << correoOrganizacion << "@gmail.edu.com";
    }

public:
    PerfilOrganizacion(int _idOrganizacion, std::string _nombreOrganizacion, std::string _correoOrganizacion)
        : idOrganizacion(_idOrganizacion),
        nombreOrganizacion(_nombreOrganizacion),
        correoOrganizacion(_correoOrganizacion),
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
                res.accion = AccionPantalla::IR_A_DASHBOARD_ORGANIZACION;
                return res;
            }
        }
    }
};
