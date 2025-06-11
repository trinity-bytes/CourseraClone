#ifndef COURSERACLONE_SCREENS_PERFILORGANIZACIONSCREEN_HPP
#define COURSERACLONE_SCREENS_PERFILORGANIZACIONSCREEN_HPP

#pragma once

// Headers estándar
#include <string>

// Headers de consola
#include "../Entities/Empresa.h"
#include "../Utils/SystemUtils.h"
#include "../Utils/ScreenSystem.h"
#include "../Utils/UI_Ascii.h"

/// Pantalla para mostrar perfil de organización
class PerfilOrganizacionScreen : public PantallaBase
{
private:
    // Datos de la organización
    int _idOrganizacion;
    std::string _nombreOrganizacion;
    std::string _correoOrganizacion;

    // Estado actual
    bool _primeraRenderizacion;

    // Coordenadas para dibujar
    const int COL_ETIQUETA = 22;
    const int FILA_ID = 15;
    const int FILA_NOMBRE = 19;
    const int FILA_CORREO = 23;    void dibujarInterfazCompleta() {
        system("cls");
        // Dibujar marco y título
        UI_OrganizationProfile();

        // Datos de la organización
        setConsoleColor(15, 0);
        gotoXY(COL_ETIQUETA, FILA_ID);
        std::cout << "ID: " << _idOrganizacion;

        gotoXY(COL_ETIQUETA, FILA_NOMBRE);
        std::cout << "ORGANIZACION: " << _nombreOrganizacion;

        gotoXY(COL_ETIQUETA, FILA_CORREO);
        std::cout << "CORREO: " << _correoOrganizacion << "@gmail.edu.com";
        setConsoleColor(15, 0);

        // Botón de editar perfil
        gotoXY(92, 12);
        setConsoleColor(15, 0);
        std::cout << " EDITAR PERFIL ";
        setConsoleColor(15, 0);
    }

public:
    PerfilOrganizacionScreen(int _idOrganizacion, std::string _nombreOrganizacion, std::string _correoOrganizacion)
        : PantallaBase(),
        _idOrganizacion(_idOrganizacion),
        _nombreOrganizacion(_nombreOrganizacion),
        _correoOrganizacion(_correoOrganizacion),
        _primeraRenderizacion(true) {
    }

    ~PerfilOrganizacionScreen() = default;

    ResultadoPantalla ejecutar() override {
        if (_primeraRenderizacion) {
            dibujarInterfazCompleta();
            _primeraRenderizacion = false;
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

#endif // COURSERACLONE_SCREENS_PERFILORGANIZACIONSCREEN_HPP
