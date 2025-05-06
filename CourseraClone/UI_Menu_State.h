#pragma once
#include "ExtendedFunctions.h"
#include "UI_Ascii.h"
#include "Controladora.h"
#include "memory"

// Estado base abstracto
class MenuState 
{
public:
    virtual void handleInput(int tecla) = 0;
    virtual void render() = 0;
    virtual std::unique_ptr<MenuState> getNextState() = 0;
    virtual ~MenuState() = default;
};

// Estado de la página principal
class LandingPageState : public MenuState {
private:
    // Constantes del menú
    static const int SECCION_CABECERA = 0;
    static const int SECCION_ESPECIALIDADES = 1;
    static const int SECCION_CURSOS = 2;
    static const int TOTAL_SECCIONES = 3;

    // Estado actual
    int seccionActual;
    int elementoActual;
    int seccionAnterior;
    int elementoAnterior;

    // Datos del menú
    std::vector<ElementoMenu> especialidades;
    std::vector<ElementoMenu> cursos;

    // Coordenadas para dibujar
    COORD coordsElementosCabecera[3] = { {67, 3}, {84, 3}, {98, 3} };
    COORD coordsTituloEspecialidad[3] = { {11, 15}, {45, 15}, {79, 15} };
    COORD coordsDescEspecialidad[3] = { {11, 17}, {45, 17}, {79, 17} };
    COORD coordsTituloCurso[3] = { {11, 25}, {45, 25}, {79, 25} };
    COORD coordsDescCurso[3] = { {11, 27}, {45, 27}, {79, 27} };

    void actualizarSeleccion() {
        if (seccionActual != seccionAnterior) {
            switch (seccionAnterior) {
                case SECCION_CABECERA:
                    actualizarElementoCabecera(elementoAnterior, false);
                    break;
                case SECCION_ESPECIALIDADES:
                    actualizarElementoEspecialidad(elementoAnterior, false);
                    break;
                case SECCION_CURSOS:
                    actualizarElementoCurso(elementoAnterior, false);
                    break;
            }
        }

        switch (seccionActual) {
            case SECCION_CABECERA:
                actualizarElementoCabecera(elementoActual, true);
                break;
            case SECCION_ESPECIALIDADES:
                actualizarElementoEspecialidad(elementoActual, true);
                break;
            case SECCION_CURSOS:
                actualizarElementoCurso(elementoActual, true);
                break;
        }

        seccionAnterior = seccionActual;
        elementoAnterior = elementoActual;
    }

    void actualizarElementoCabecera(int indice, bool seleccionado) {
        if (indice < 0 || indice >= 3) return;
        gotoXY(coordsElementosCabecera[indice].X, coordsElementosCabecera[indice].Y);
        if (seleccionado) SetConsoleColor(1, 13);
        else SetConsoleColor(15, 1);
        cout << ELEMENTOS_CABECERA[indice];
        SetConsoleColor(15, 1);
    }

    void actualizarElementoEspecialidad(int indice, bool seleccionado) {
        if (indice < 0 || indice >= especialidades.size()) return;
        actualizarElementoGenerico(
            coordsTituloEspecialidad[indice],
            coordsDescEspecialidad[indice],
            especialidades[indice],
            seleccionado
        );
    }

    void actualizarElementoCurso(int indice, bool seleccionado) {
        if (indice < 0 || indice >= cursos.size()) return;
        actualizarElementoGenerico(
            coordsTituloCurso[indice],
            coordsDescCurso[indice],
            cursos[indice],
            seleccionado
        );
    }

    void actualizarElementoGenerico(const COORD& coordTitulo, const COORD& coordDesc,
        const ElementoMenu& elemento, bool seleccionado) {
        gotoXY(coordTitulo.X, coordTitulo.Y);
        if (seleccionado) SetConsoleColor(1, 13);
        else SetConsoleColor(15, 1);
        cout << elemento.titulo;
        SetConsoleColor(15, 1);

        gotoXY(coordDesc.X, coordDesc.Y);
        cout << elemento.descripcion;
    }

public:
    LandingPageState() : 
        seccionActual(SECCION_CABECERA),
        elementoActual(0),
        seccionAnterior(-1),
        elementoAnterior(-1) {
        // Cargar datos por defecto
        especialidades = {
            {"Desarrollo Web", "Frontend & Backend"},
            {"Ciencia de Datos", "Analisis y ML"},
            {"Marketing Digital", "SEO, SEM & Ads"}
        };
        cursos = {
            {"Curso C++ CLI", "Interaccion consola"},
            {"Curso Python DS", "Data science intro"},
            {"Curso React JS", "Web UI development"}
        };
    }

    void handleInput(int tecla) override {
        if (tecla == 224) { // Tecla extendida
            tecla = _getch();
            switch (tecla) {
                case 72: // Flecha arriba
                    seccionActual--;
                    if (seccionActual < 0) seccionActual = 0;
                    elementoActual = 0;
                    actualizarSeleccion();
                    break;
                case 80: // Flecha abajo
                    seccionActual++;
                    if (seccionActual >= TOTAL_SECCIONES) 
                        seccionActual = TOTAL_SECCIONES - 1;
                    elementoActual = 0;
                    actualizarSeleccion();
                    break;
                case 75: // Flecha izquierda
                    elementoActual--;
                    if (elementoActual < 0) elementoActual = 0;
                    actualizarSeleccion();
                    break;
                case 77: // Flecha derecha
                    elementoActual++;
                    if (elementoActual >= 3) elementoActual = 2;
                    actualizarSeleccion();
                    break;
            }
        }
    }

    void render() override {
        system("cls");
        UI_LandingPage();
        dibujarInterfazCompleta();
    }

    std::unique_ptr<MenuState> getNextState() override {
        if (seccionActual == SECCION_CABECERA) {
            switch (elementoActual) {
                case 0: return std::make_unique<LoginState>();
                case 1: return std::make_unique<RegisterState>();
                case 2: return std::make_unique<AboutUsState>();
            }
        }
        return nullptr;
    }
};

// Estado de Login
class LoginState : public MenuState {
public:
    void handleInput(int tecla) override {
        // Implementar lógica de input para login
    }

    void render() override {
        UI_Login();
    }

    std::unique_ptr<MenuState> getNextState() override {
        // Retornar al estado anterior o al dashboard según el resultado del login
        return std::make_unique<LandingPageState>();
    }
};

// Estado de Registro
class RegisterState : public MenuState {
public:
    void handleInput(int tecla) override {
        // Implementar lógica de input para registro
    }

    void render() override {
        UI_Signup();
    }

    std::unique_ptr<MenuState> getNextState() override {
        // Retornar al estado anterior después del registro
        return std::make_unique<LandingPageState>();
    }
};

// Estado de About Us
class AboutUsState : public MenuState {
public:
    void handleInput(int tecla) override {
        // Implementar lógica de input para about us
    }

    void render() override {
        // Implementar UI de about us
    }

    std::unique_ptr<MenuState> getNextState() override {
        // Retornar al estado anterior
        return std::make_unique<LandingPageState>();
    }
};

// Estado del Dashboard de Estudiante
class StudentDashboardState : public MenuState {
private:
    Controladora* controladora;
    int opcionActual;

public:
    StudentDashboardState(Controladora* ctrl) : controladora(ctrl), opcionActual(0) {}

    void handleInput(int tecla) override {
        if (tecla == 224) { // Tecla extendida
            tecla = _getch();
            switch (tecla) {
                case 72: // Flecha arriba
                    opcionActual = (opcionActual - 1 + 3) % 3;
                    break;
                case 80: // Flecha abajo
                    opcionActual = (opcionActual + 1) % 3;
                    break;
            }
        }
        else if (tecla == 13) { // Enter
            // Implementar acciones según opcionActual
        }
    }

    void render() override {
        UI_StudentDashboard();
        // Actualizar la interfaz según opcionActual
    }

    std::unique_ptr<MenuState> getNextState() override {
        // Implementar lógica de transición
        return nullptr;
    }
};

// Estado del Dashboard de Organización
class OrganizationDashboardState : public MenuState {
private:
    Controladora* controladora;
    int opcionActual;

public:
    OrganizationDashboardState(Controladora* ctrl) : controladora(ctrl), opcionActual(0) {}

    void handleInput(int tecla) override {
        if (tecla == 224) { // Tecla extendida
            tecla = _getch();
            switch (tecla) {
                case 72: // Flecha arriba
                    opcionActual = (opcionActual - 1 + 3) % 3;
                    break;
                case 80: // Flecha abajo
                    opcionActual = (opcionActual + 1) % 3;
                    break;
            }
        }
        else if (tecla == 13) { // Enter
            // Implementar acciones según opcionActual
        }
    }

    void render() override {
        UI_OrganizationDashboard();
        // Actualizar la interfaz según opcionActual
    }

    std::unique_ptr<MenuState> getNextState() override {
        // Implementar lógica de transición
        return nullptr;
    }
}; 