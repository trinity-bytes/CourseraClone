#pragma once

// Headers estándar
#include <string>

// Headers de consola
#include "../Entities/Estudiante.h"
#include "../Utils/ExtendedFunctions.h"
#include "../Utils/ScreenSystem.h"
#include "../Utils/UI_Ascii.h"

// Screen to display student profile information and navigation options
class PerfilEstudianteScreen : public PantallaBase
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
    int _idEstudiante;
    std::string _nombreEstudiante;
    std::string _emailEstudiante;

    // Estado actual
    int _seccionActual;
    int _botonActual;
    bool _primeraRenderizacion;

    // Coordenadas para botones
    COORD coordsBotones[TOTAL_BOTONES] = {
        {58, 12}, // MIS CERTIFICADOS
        {78, 12}, // MIS BOLETAS
        {93, 12}  // EDITAR PERFIL
    };

    void dibujarInterfazCompleta() {
        system("cls");
        UI_UserProfile();        // Mostrar datos del perfil
        SetConsoleColor(15, 0);
        gotoXY(26, 16);
        std::cout << _idEstudiante;

        gotoXY(34, 20);
        std::cout << _nombreEstudiante;

        gotoXY(30, 24);
        std::cout << _emailEstudiante;
        SetConsoleColor(15, 0);        // Renderizar botones
        for (int i = 0; i < TOTAL_BOTONES; i++) {
            renderizarBoton(i, i == _botonActual && _seccionActual == SECCION_BOTONES);
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
            std::cout << "MIS CERTIFICADOS";
            break;
        case BOTON_BOLETAS:
            std::cout << "MIS BOLETAS";
            break;
        case BOTON_EDITAR:
            std::cout << "EDITAR PERFIL";
            break;
        }

        SetConsoleColor(15, 0); // Restaurar color
    }

    void actualizarSeleccion() {
        for (int i = 0; i < TOTAL_BOTONES; i++) {
            renderizarBoton(i, i == _botonActual && _seccionActual == SECCION_BOTONES);
        }
    }

public:
    PerfilEstudianteScreen(int _idEstudiante, std::string _nombreEstudiante, std::string _emailEstudiante)
        : PantallaBase(),
        _idEstudiante(_idEstudiante),
        _nombreEstudiante(_nombreEstudiante),
        _emailEstudiante(_emailEstudiante),
        _seccionActual(SECCION_BOTONES),
        _botonActual(0),
        _primeraRenderizacion(true) {
    }    ~PerfilEstudianteScreen() = default;

    ResultadoPantalla ejecutar() override {
        ResultadoPantalla res;

        if (_primeraRenderizacion) {
            dibujarInterfazCompleta();
            _primeraRenderizacion = false;
        }

        while (true) {
            // Manejar entrada del usuario
            int tecla = _getch();

            switch (tecla) {
            case 224: // Tecla extendida
                tecla = _getch();
                switch (tecla) {
                case 75: // Flecha izquierda
                    if (_botonActual > 0) {
                        _botonActual--;
                        actualizarSeleccion();
                    }
                    break;
                case 77: // Flecha derecha
                    if (_botonActual < TOTAL_BOTONES - 1) {
                        _botonActual++;
                        actualizarSeleccion();
                    }
                    break;
                }
                break;

            case 13: // Enter
                if (_seccionActual == SECCION_BOTONES) {
                    switch (_botonActual) {
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