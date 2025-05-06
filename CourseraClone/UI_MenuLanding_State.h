#pragma once
// Encabezados propios
#include "ExtendedFunctions.h"
#include "UI_Ascii.h"
#include "Controladora.h"

// Encabezados de librerías
#include "memory"

// Estado base abstracto
class MenuState 
{
protected:
    Controladora* controladora;
public:
    MenuState(Controladora* ctrl) : controladora(ctrl) {}
	virtual void handleInput(int tecla) = 0; // Método para manejar la entrada
	virtual void render() = 0; // Método para renderizar
    virtual void renderInicial() = 0; // Metodo para renderizado inicial
    virtual void renderUpdate() = 0;  // Metodo para actualizaciones
    virtual std::unique_ptr<MenuState> getNextState() = 0;
    virtual ~MenuState() = default;
};

// Estado de la página principal
class LandingPageState : public MenuState 
{
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

    bool primeraRenderizacion;

    // Datos del menú
    std::vector<ElementoMenu> especialidades;
    std::vector<ElementoMenu> cursos;

    // Coordenadas para dibujar
    COORD coordsElementosCabecera[3] = { {67, 3}, {84, 3}, {98, 3} };
    COORD coordsTituloEspecialidad[3] = { {11, 15}, {45, 15}, {79, 15} };
    COORD coordsDescEspecialidad[3] = { {11, 17}, {45, 17}, {79, 17} };
    COORD coordsTituloCurso[3] = { {11, 25}, {45, 25}, {79, 25} };
    COORD coordsDescCurso[3] = { {11, 27}, {45, 27}, {79, 27} };
    
    void actualizarSeleccion() 
    {
        // Si cambió de sección, actualizar ambas secciones implicadas (anterior y actual)
        if (seccionActual != seccionAnterior) 
        {
            // Desdibujar la selección anterior (sección anterior)
            switch (seccionAnterior) 
            {
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

        // Dibujar la nueva selección (sección actual)
        switch (seccionActual) 
        {
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

    void actualizarElementoCabecera(int indice, bool seleccionado) 
    {
        if (indice < 0 || indice >= 3) return;
        gotoXY(coordsElementosCabecera[indice].X, coordsElementosCabecera[indice].Y);

        if (seleccionado) SetConsoleColor(1, 13); // Color de texto SELECCION
        else SetConsoleColor(15, 1); // Color por defecto

        cout << ELEMENTOS_CABECERA[indice];
        SetConsoleColor(15, 1); // Restablecer color por defecto
    }

    void actualizarElementoEspecialidad(int indice, bool seleccionado) 
    {
        if (indice < 0 || indice >= especialidades.size()) return;

        // Actualizar contenido usando función genérica
        actualizarElementoGenerico(
            coordsTituloEspecialidad[indice],
            coordsDescEspecialidad[indice],
            especialidades[indice],
            seleccionado
        );
    }

    void actualizarElementoCurso(int indice, bool seleccionado) 
    {
        if (indice < 0 || indice >= cursos.size()) return;

        // Actualizar contenido usando función genérica
        actualizarElementoGenerico(
            coordsTituloCurso[indice],
            coordsDescCurso[indice],
            cursos[indice],
            seleccionado
        );
    }

    void actualizarElementoGenerico(const COORD& coordTitulo, 
        const COORD& coordDesc, const ElementoMenu& elemento, 
        bool seleccionado) 
    {
        gotoXY(coordTitulo.X, coordTitulo.Y);

        if (seleccionado) SetConsoleColor(1, 13); // Color de SELECCIONADO
		else SetConsoleColor(15, 1); // Color por defecto

        cout << elemento.titulo;
		SetConsoleColor(15, 1); // Restablecer color por defecto

        gotoXY(coordDesc.X, coordDesc.Y);
        cout << elemento.descripcion;
    }

public:
    LandingPageState(Controladora* ctrl) : MenuState(ctrl),
        seccionActual(0), elementoActual(0), seccionAnterior(0),
        elementoAnterior(0), primeraRenderizacion(true)
    {
        // Inicializar vectores de elementos
        especialidades = {
            {"Ingeniería", "Cursos de ingeniería y tecnología"},
            {"Negocios", "Cursos de administración y negocios"},
            {"Diseño", "Cursos de diseño y creatividad"}
        };
        cursos = {
            {"Programación C++", "Aprende C++ desde cero"},
            {"Marketing Digital", "Estrategias de marketing moderno"},
            {"UI/UX Design", "Diseño de interfaces de usuario"}
        };
    }
    
	~LandingPageState() {}

    void handleInput(int tecla) override 
    {
        if (tecla == 224) // Tecla extendida
        { 
            tecla = _getch();
            switch (tecla) 
            {
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

    void render() override 
    {
		if (primeraRenderizacion) // Renderizar por primera vez
        {
            renderInicial(); 
            primeraRenderizacion = false;
        } 
        else // Renderizar solo actualizaciones
        {
            renderUpdate();
        }
    }

    void renderInicial() override 
    {
        system("cls");
        UI_LandingPage();
        dibujarInterfazCompleta();
    }

    void renderUpdate() override 
    {
        actualizarSeleccion();  // Solo actualizar los elementos que cambiaron
    }

	std::unique_ptr<MenuState> getNextState() override // Retornar al siguiente estado
    {
        if (seccionActual == SECCION_CABECERA)
        {
            switch (elementoActual) 
            {
                case 0: return std::make_unique<LoginState>(controladora);
                case 1: return std::make_unique<RegisterState>(controladora);
                case 2: return std::make_unique<AboutUsState>(controladora);
            }
        }
        return nullptr;
    }
};

// Estado de Login
class LoginState : public MenuState 
{
private:
    bool primeraRenderizacion;
    string username;
    string password;
    int campoActual; // 0: username, 1: password

public:
    LoginState(Controladora* ctrl) : MenuState(ctrl), primeraRenderizacion(true), campoActual(0) {}

    void handleInput(int tecla) override 
    {
        if (tecla == 13) { // Enter
            if (campoActual == 0) {
                campoActual = 1;
            } else {
                // Intentar login
            }
        } else if (tecla == 8) { // Backspace
            if (campoActual == 0 && !username.empty()) {
                username.pop_back();
            } else if (campoActual == 1 && !password.empty()) {
                password.pop_back();
            }
        } else if (tecla >= 32 && tecla <= 126) { // Caracteres imprimibles
            if (campoActual == 0) {
                username += (char)tecla;
            } else {
                password += (char)tecla;
            }
        }
        renderUpdate();
    }

    void render() override {
        if (primeraRenderizacion) {
            renderInicial();
            primeraRenderizacion = false;
        } else {
            renderUpdate();
        }
    }

    void renderInicial() override {
        system("cls");
        UI_Login();
    }

    void renderUpdate() override {
        // Actualizar solo los campos de entrada
        gotoXY(67, 15);
        cout << string(30, ' '); // Limpiar área
        gotoXY(67, 15);
        cout << username;

        gotoXY(67, 20);
        cout << string(30, ' '); // Limpiar área
        gotoXY(67, 20);
        cout << string(password.length(), '*');
    }

    std::unique_ptr<MenuState> getNextState() override {
        // Retornar al estado anterior o al dashboard según el resultado del login
        return std::make_unique<LandingPageState>(controladora);
    }
};

// Estado de Registro
class RegisterState : public MenuState {
private:
    bool primeraRenderizacion;
    string nombre;
    string apellido;
    string email;
    string password;
    string confirmPassword;
    int campoActual; // 0: nombre, 1: apellido, 2: email, 3: password, 4: confirmPassword

public:
    RegisterState(Controladora* ctrl) : MenuState(ctrl), primeraRenderizacion(true), campoActual(0) {}

    void handleInput(int tecla) override {
        if (tecla == 13) { // Enter
            campoActual = (campoActual + 1) % 5;
        } else if (tecla == 8) { // Backspace
            switch (campoActual) {
                case 0: if (!nombre.empty()) nombre.pop_back(); break;
                case 1: if (!apellido.empty()) apellido.pop_back(); break;
                case 2: if (!email.empty()) email.pop_back(); break;
                case 3: if (!password.empty()) password.pop_back(); break;
                case 4: if (!confirmPassword.empty()) confirmPassword.pop_back(); break;
            }
        } else if (tecla >= 32 && tecla <= 126) { // Caracteres imprimibles
            switch (campoActual) {
                case 0: nombre += (char)tecla; break;
                case 1: apellido += (char)tecla; break;
                case 2: email += (char)tecla; break;
                case 3: password += (char)tecla; break;
                case 4: confirmPassword += (char)tecla; break;
            }
        }
        renderUpdate();
    }

    void render() override {
        if (primeraRenderizacion) {
            renderInicial();
            primeraRenderizacion = false;
        } else {
            renderUpdate();
        }
    }

    void renderInicial() override {
        system("cls");
        UI_Signup();
    }

    void renderUpdate() override {
        // Actualizar solo los campos que cambiaron
        gotoXY(67, 15);
        cout << string(30, ' '); // Limpiar área
        gotoXY(67, 15);
        cout << nombre;

        gotoXY(67, 18);
        cout << string(30, ' '); // Limpiar área
        gotoXY(67, 18);
        cout << apellido;

        gotoXY(67, 21);
        cout << string(30, ' '); // Limpiar área
        gotoXY(67, 21);
        cout << email;

        gotoXY(67, 24);
        cout << string(30, ' '); // Limpiar área
        gotoXY(67, 24);
        cout << string(password.length(), '*');

        gotoXY(67, 27);
        cout << string(30, ' '); // Limpiar área
        gotoXY(67, 27);
        cout << string(confirmPassword.length(), '*');
    }

    std::unique_ptr<MenuState> getNextState() override {
        // Retornar al estado anterior después del registro
        return std::make_unique<LandingPageState>(controladora);
    }
};

// Estado de About Us
class AboutUsState : public MenuState {
public:
    AboutUsState(Controladora* ctrl) : MenuState(ctrl) {}

    void handleInput(int tecla) override {
        // Implementar lógica de input para about us
    }

    void render() override {
        // Implementar UI de about us
    }

    std::unique_ptr<MenuState> getNextState() override {
        // Retornar al estado anterior
        return std::make_unique<LandingPageState>(controladora);
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