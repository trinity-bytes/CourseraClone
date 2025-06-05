#pragma once

#include "../Utils/Pantalla.h"
#include "../Utils/ExtendedFunctions.h"
#include "../Utils/UI_Ascii.h"
#include "../Entities/Empresa.h"
#include <string>

class PerfilOrganizacion : public PantallaBase
{
private:
    // Datos de la organización
    int idOrganizacion;
    string nombreOrganizacion;
    string correoOrganizacion;

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
        SetConsoleColor(15, 0);
        gotoXY(COL_ETIQUETA, FILA_ID);
        cout << "ID: " << idOrganizacion;

        gotoXY(COL_ETIQUETA, FILA_NOMBRE);
        cout << "ORGANIZACION: " << nombreOrganizacion;

        gotoXY(COL_ETIQUETA, FILA_CORREO);
        cout << "CORREO: " << correoOrganizacion << "@gmail.edu.com";
        SetConsoleColor(15, 0);

        // Botón de editar perfil
        gotoXY(92, 12);
        SetConsoleColor(15, 0);
        cout << " EDITAR PERFIL ";
        SetConsoleColor(15, 0);
    }

public:
    PerfilOrganizacion(int _idOrganizacion, string _nombreOrganizacion, string _correoOrganizacion)
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

            if (tecla == 13) { // Enter para editar perfil
                res.accion = AccionPantalla::IR_A_EDITAR_PERFIL;
                return res;
            }
            if (tecla == 27) { // ESC para volver
                res.accion = AccionPantalla::IR_A_DASHBOARD_ORGANIZACION;
                return res;
            }
        }
    }
};
