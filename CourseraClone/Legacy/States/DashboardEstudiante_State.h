#pragma once

// Headers propios
#include "Menu_State.h"
#include "../UI_Ascii.h"
#include "../ExtendedFunctions.h"
#include "../Controladora.h"


// Headers de librerías
#include "vector"
#include "string"

class DashboardEstudianteState : public MenuState 
{
private:
    // Constantes del menú
    static const int SECCION_CURSOS_INSCRITOS = 0;
    static const int SECCION_CERTIFICADOS = 1;
    static const int SECCION_BOLETAS = 2;
    static const int SECCION_PERFIL = 3;
    static const int TOTAL_SECCIONES = 4;

    // Elementos del menú
    const vector<string> ELEMENTOS_MENU = {
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

    void actualizarSeleccion() {
        // Si cambió de sección, actualizar ambas secciones implicadas
        if (seccionActual != seccionAnterior) {
            // Desdibujar selección anterior
            actualizarElementoMenu(seccionAnterior, false);
            // Dibujar nueva selección
            actualizarElementoMenu(seccionActual, true);
        }
        // Si solo cambió el elemento dentro de la misma sección
        else if (elementoActual != elementoAnterior) {
            actualizarElementoMenu(elementoAnterior, false);
            actualizarElementoMenu(elementoActual, true);
        }

        // Actualizar valores anteriores
        seccionAnterior = seccionActual;
        elementoAnterior = elementoActual;
    }

    void actualizarElementoMenu(int indice, bool seleccionado) {
        if (indice < 0 || indice >= TOTAL_SECCIONES) return;

        gotoXY(coordsElementosMenu[indice].X, coordsElementosMenu[indice].Y);

        if (seleccionado) SetConsoleColor(1, 4); // Color de texto SELECCION
        else SetConsoleColor(15, 1); // Color por defecto

        cout << ELEMENTOS_MENU[indice];
        SetConsoleColor(15, 1); // Restablecer color por defecto
    }

    void dibujarInterfazCompleta() {
        // Dibujar cabecera
        for (int i = 0; i < TOTAL_SECCIONES; ++i) {
            actualizarElementoMenu(i, seccionActual == i);
        }

        // Dibujar contenido según la sección actual
        switch (seccionActual) {
            case SECCION_CURSOS_INSCRITOS:
                dibujarCursosInscritos();
                break;
            case SECCION_CERTIFICADOS:
                dibujarCertificados();
                break;
            case SECCION_BOLETAS:
                dibujarBoletas();
                break;
            case SECCION_PERFIL:
                dibujarPerfil();
                break;
        }
    }

    void dibujarCursosInscritos() {
        // Implementar visualización de cursos inscritos
        gotoXY(11, 15);
        cout << "Mis Cursos Inscritos:";
        // TODO: Mostrar lista de cursos
    }

    void dibujarCertificados() {
        // Implementar visualización de certificados
        gotoXY(11, 15);
        cout << "Mis Certificados:";
        // TODO: Mostrar lista de certificados
    }

    void dibujarBoletas() {
        // Implementar visualización de boletas
        gotoXY(11, 15);
        cout << "Mis Boletas:";
        // TODO: Mostrar lista de boletas
    }

    void dibujarPerfil() {
        // Implementar visualización de perfil
        gotoXY(11, 15);
        cout << "Mi Perfil:";
        // TODO: Mostrar información del perfil
    }

public:
    DashboardEstudianteState(Controladora* controladora) : MenuState(controladora) {
        seccionActual = 0;
        elementoActual = 0;
        seccionAnterior = 0;
        elementoAnterior = 0;
        primeraRenderizacion = true;
    }

    void render() override {
        if (primeraRenderizacion) {
            system("cls");
            dibujarInterfazCompleta();
            primeraRenderizacion = false;
        }
        else {
            actualizarSeleccion();
        }
    }

    void handleInput(int tecla) override {
        switch (tecla) {
            case VK_LEFT:
                if (seccionActual > 0) {
                    seccionActual--;
                    dibujarInterfazCompleta();
                }
                break;
            case VK_RIGHT:
                if (seccionActual < TOTAL_SECCIONES - 1) {
                    seccionActual++;
                    dibujarInterfazCompleta();
                }
                break;
            case VK_RETURN:
                // Manejar selección
                switch (seccionActual) {
                    case SECCION_CURSOS_INSCRITOS:
                        // Navegar a detalle de curso
                        break;
                    case SECCION_CERTIFICADOS:
                        // Navegar a detalle de certificado
                        break;
                    case SECCION_BOLETAS:
                        // Navegar a detalle de boleta
                        break;
                    case SECCION_PERFIL:
                        // Navegar a edición de perfil
                        break;
                }
                break;
            case VK_ESCAPE:
                // Volver al landing page
                controladora->cerrarSesion();
                break;
        }
    }

    unique_ptr<MenuState> getNextState() override {
        // Retornar nuevo estado si es necesario
        return nullptr;
    }
}; 