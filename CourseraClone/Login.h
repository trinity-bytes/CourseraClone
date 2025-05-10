#pragma once
#include "Pantalla.h"
#include "Usuario.h"
#include "ExtendedFunctions.h"
#include <string>

class Login : public PantallaBase {
private:
    // Constantes del menú
    static const int ELEMENTOS_INPUT = 2;
    static const int CANT_BOTONES = 3;

    string email;
    string password;
    TipoUsuario tipoUsuario;
    int campoActual;
    bool error;
    string mensajeError;

    // Coordenadas para dibujar
    COORD coordsElementosUserInput[ELEMENTOS_INPUT] = { {67, 3}, {84, 3} };
    COORD coordsBotones[CANT_BOTONES] = { {11, 15}, {45, 15}, {79, 15} };

    void renderizarCampo(const string& etiqueta, const string& valor, int y, bool seleccionado) {
        gotoxy(ANCHO_CONSOLA / 2 - 20, y);
        if (seleccionado) {
            setColor(Colors::SELECCION);
            cout << "> ";
        } else {
            setColor(Colors::NORMAL);
            cout << "  ";
        }
        cout << etiqueta << ": ";
        setColor(Colors::NORMAL);
        cout << valor;
    }

    void renderizarBoton(const string& texto, int y, bool seleccionado) {
        gotoxy(ANCHO_CONSOLA / 2 - 10, y);
        if (seleccionado) {
            setColor(Colors::SELECCION);
            cout << "> ";
        } else {
            setColor(Colors::NORMAL);
            cout << "  ";
        }
        cout << texto;
    }

public:
    Login() : campoActual(0), error(false) {}

    ResultadoPantalla ejecutar() override 
    {
        while (true) 
        {
            system("cls");
            // Título
            gotoxy(ANCHO_CONSOLA / 2 - 10, 2);
            setColor(Colors::NORMAL);
            cout << "INICIO DE SESIÓN";

            // Campos
            renderizarCampo("Email", email, 5, campoActual == 0);
            renderizarCampo("Contraseña", string(password.length(), '*'), 7, campoActual == 1);

            // Botones
            renderizarBoton("Iniciar Sesión", 10, campoActual == 2);
            renderizarBoton("Registrarse", 12, campoActual == 3);
            renderizarBoton("Volver", 14, campoActual == 4);

            // Mensaje de error
            if (error) {
                gotoxy(ANCHO_CONSOLA / 2 - mensajeError.length() / 2, 16);
                setColor(Colors::ERRORES);
                cout << mensajeError;
            }

            // Instrucciones
            gotoxy(ANCHO_CONSOLA / 2 - 20, ALTO_CONSOLA - 2);
            setColor(Colors::TEXTO_SECUNDARIO);
            cout << "Use las flechas para navegar y Enter para seleccionar";

            int tecla = _getch();
            switch (tecla) {
                case 72: // Flecha arriba
                    if (campoActual > 0) campoActual--;
                    break;
                case 80: // Flecha abajo
                    if (campoActual < 4) campoActual++;
                    break;
                case 13: // Enter
                    if (campoActual == 2) { // Iniciar Sesión
                        if (validarCampos()) {
                            ResultadoPantalla res;
                            res.accion = AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE;
                            res.email = email;
                            res.password = password;
                            return res;
                        } else {
                            error = true;
                            mensajeError = "Credenciales inválidas. Intente nuevamente.";
                        }
                    } else if (campoActual == 3) { // Registrarse
                        ResultadoPantalla res;
                        res.accion = AccionPantalla::IR_A_REGISTRO;
                        return res;
                    } else if (campoActual == 4) { // Volver
                        ResultadoPantalla res;
                        res.accion = AccionPantalla::IR_A_LANDING_PAGE;
                        return res;
                    }
                    break;
                case 8: // Backspace
                    if (campoActual >= 0 && campoActual <= 1) {
                        string* campo = nullptr;
                        switch (campoActual) {
                            case 0: campo = &email; break;
                            case 1: campo = &password; break;
                        }
                        if (campo && !campo->empty()) {
                            campo->pop_back();
                        }
                    }
                    break;
                default:
                    if (tecla >= 32 && tecla <= 126) { // Caracteres imprimibles
                        string* campo = nullptr;
                        switch (campoActual) {
                            case 0: campo = &email; break;
                            case 1: campo = &password; break;
                        }
                        if (campo) {
                            campo->push_back(static_cast<char>(tecla));
                        }
                    }
                    break;
            }
            error = false;
        }
    }

private:
    bool validarCampos() {
        Usuario temp;
        if (email.empty() || password.empty()) {
            error = true;
            mensajeError = "Todos los campos son obligatorios";
            return false;
        }
        int index = temp.buscarIndexUsuario(email, tipoUsuario);
        if (index == -1) {
            error = true;
            mensajeError = "Usuario no encontrado";
            return false;
        }
        else {
            LoginStatus res = temp.login(temp, tipoUsuario, password, index);
            if (res == LoginStatus::SUCCESS) return true;
        }

        return false;
    }
};
