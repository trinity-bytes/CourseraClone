#pragma once

#include "../Utils/Pantalla.h"
#include "../Utils/ExtendedFunctions.h"
#include "../Utils/UI_Ascii.h"
#include "../Entities/Estudiante.h"
#include <string>

class PerfilEstudiante : public PantallaBase
{
private:
    // Constantes para secciones
    static const int SECCION_BOTONES = 0;
    static const int TOTAL_SECCIONES = 1;

    // Constantes para botones
    static const int BOTON_CERTIFICADOS = 0;
    static const int BOTON_BOLETAS = 1;
    static const int BOTON_EDITAR = 2;
    static const int TOTAL_BOTONES = 3;

    // Datos del usuario
    int idEstudiante;
    string nombreEstudiante;
    string emailEstudiante;

    // Estado actual
    int seccionActual;
    int botonActual;
    bool primeraRenderizacion;

    // Coordenadas para botones
    COORD coordsBotones[TOTAL_BOTONES] = {
        {58, 12}, // MIS CERTIFICADOS
        {78, 12}, // MIS BOLETAS
        {93, 12}  // EDITAR PERFIL
    };

    void dibujarInterfazCompleta() {
        system("cls");
        UI_UserProfile();

        // Mostrar datos del perfil
        SetConsoleColor(15, 0);
        gotoXY(26, 16);
        cout << idEstudiante;

        gotoXY(34, 20);
        cout << nombreEstudiante;

        gotoXY(30, 24);
        cout << emailEstudiante;
        SetConsoleColor(15, 0);

        // Renderizar botones
        for (int i = 0; i < TOTAL_BOTONES; i++) {
            renderizarBoton(i, i == botonActual && seccionActual == SECCION_BOTONES);
        }
    }

    void renderizarBoton(int indice, bool seleccionado) {
        gotoXY(coordsBotones[indice].X, coordsBotones[indice].Y);

        if (seleccionado) {
            SetConsoleColor(1, 13); // Color para selección
        }
        else {
            SetConsoleColor(15, 0); // Color normal
        }

        switch (indice) {
        case BOTON_CERTIFICADOS:
            cout << "MIS CERTIFICADOS";
            break;
        case BOTON_BOLETAS:
            cout << "MIS BOLETAS";
            break;
        case BOTON_EDITAR:
            cout << "EDITAR PERFIL";
            break;
        }

        SetConsoleColor(15, 0); // Restaurar color
    }

    void actualizarSeleccion() {
        for (int i = 0; i < TOTAL_BOTONES; i++) {
            renderizarBoton(i, i == botonActual && seccionActual == SECCION_BOTONES);
        }
    }

public:
    PerfilEstudiante(int _idEstudiante, string _nombreEstudiante, string _emailEstudiante)
        : idEstudiante(_idEstudiante),
        nombreEstudiante(_nombreEstudiante),
        emailEstudiante(_emailEstudiante),
        seccionActual(SECCION_BOTONES),
        botonActual(0),
        primeraRenderizacion(true) {
    }

    ResultadoPantalla ejecutar() override {
        ResultadoPantalla res;

        if (primeraRenderizacion) {
            dibujarInterfazCompleta();
            primeraRenderizacion = false;
        }

        while (true) {
            // Manejar entrada del usuario
            int tecla = _getch();

            switch (tecla) {
            case 224: // Tecla extendida
                tecla = _getch();
                switch (tecla) {
                case 75: // Flecha izquierda
                    if (botonActual > 0) {
                        botonActual--;
                        actualizarSeleccion();
                    }
                    break;
                case 77: // Flecha derecha
                    if (botonActual < TOTAL_BOTONES - 1) {
                        botonActual++;
                        actualizarSeleccion();
                    }
                    break;
                }
                break;

            case 13: // Enter
                if (seccionActual == SECCION_BOTONES) {
                    switch (botonActual) {
                    case BOTON_CERTIFICADOS:
                        // Para una futura implementación
                        break;
                    case BOTON_BOLETAS:
                        // Ir a la pantalla de Ver Boletas
                        res.accion = AccionPantalla::IR_A_VER_BOLETAS;
                        return res;
                    case BOTON_EDITAR:
                        // Ir a la pantalla de editar perfil
                        res.accion = AccionPantalla::IR_A_EDITAR_PERFIL;
                        return res;
                    }
                }
                break;

            case 27: // ESC - Volver al dashboard
                res.accion = AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE;
                return res;
            }
        }

        return res;
    }
};