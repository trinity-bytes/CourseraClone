#pragma once

#include "Pantalla.h"

class Controladora; // Declaración anticipada de la clase Controladora

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

    void actualizarSeleccion() {
        // Si cambió de sección, actualizar ambas secciones implicadas
        if (seccionActual != seccionAnterior) {
            actualizarElementoMenu(seccionAnterior, false);
            actualizarElementoMenu(seccionActual, true);
        }
        // Si solo cambió el elemento dentro de la misma sección
        else if (elementoActual != elementoAnterior) {
            actualizarElementoMenu(elementoAnterior, false);
            actualizarElementoMenu(elementoActual, true);
        }

        seccionAnterior = seccionActual;
        elementoAnterior = elementoActual;
    }

    void actualizarElementoMenu(int indice, bool seleccionado) {
        if (indice < 0 || indice >= TOTAL_SECCIONES) return;

        gotoXY(coordsElementosMenu[indice].X, coordsElementosMenu[indice].Y);

        if (seleccionado) SetConsoleColor(1, 4);
        else SetConsoleColor(15, 1);

        std::cout << ELEMENTOS_MENU[indice];
        SetConsoleColor(15, 1);
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
        gotoXY(11, 15);
        std::cout << "Mis Cursos Inscritos:";
        // TODO: Mostrar lista de cursos
    }

    void dibujarCertificados() {
        gotoXY(11, 15);
        std::cout << "Mis Certificados:";
        // TODO: Mostrar lista de certificados
    }

    void dibujarBoletas() {
        gotoXY(11, 15);
        std::cout << "Mis Boletas:";
        // TODO: Mostrar lista de boletas
    }

    void dibujarPerfil() {
        gotoXY(11, 15);
        std::cout << "Mi Perfil:";
        // TODO: Mostrar información del perfil
    }

public:
    DashboardEstudiante(Controladora* ctrl) 
        : PantallaBase(ctrl),
          seccionActual(0), elementoActual(0),
          seccionAnterior(0), elementoAnterior(0) {}
    // PantallaBase(ctrl, Pantalla::DASHBOARD_ESTUDIANTE), opcional para los constructores pero no implementado depende de si sea necesario en el futuro

    void renderizar() override {
        if (primeraRenderizacion) {
            limpiarPantalla();
            dibujarInterfazCompleta();
            primeraRenderizacion = false;
        }
        else {
            actualizarSeleccion();
        }
    }

    void manejarInput(int tecla) override {
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
                        // TODO: Navegar a detalle de curso
                        break;
                    case SECCION_CERTIFICADOS:
                        // TODO: Navegar a detalle de certificado
                        break;
                    case SECCION_BOLETAS:
                        // TODO: Navegar a detalle de boleta
                        break;
                    case SECCION_PERFIL:
                        // TODO: Navegar a edición de perfil
                        break;
                }
                break;
            case VK_ESCAPE:
                controladora->cerrarSesion();
                break;
        }
    }

    Pantalla getSiguientePantalla() override {
        // Por ahora, siempre retorna la pantalla actual
        // TODO: Implementar lógica de navegación
        return pantallaActual;
    }
}; 