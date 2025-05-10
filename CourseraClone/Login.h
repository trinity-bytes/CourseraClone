#pragma once
#include "Pantalla.h"
#include "Usuario.h"
#include "ExtendedFunctions.h"
#include "UI_Ascii.h"
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
    int campoAnterior;
    bool primeraRenderizacion;
    bool error;
    string mensajeError;

    // Coordenadas para dibujar
    COORD coordsElementosUserInput[ELEMENTOS_INPUT] = { {67, 14}, {84, 19} };
    COORD coordsBotones[CANT_BOTONES] = { {11, 24}, {45, 24}, {79, 28} };
	const string elementosUserinput[ELEMENTOS_INPUT] = { "Email", "Contraseña" };
    const string textosBotones[CANT_BOTONES] = { "Iniciar Sesión", "Registrarse", "Volver" };

    void renderizarCampo(const string& valor, int indice, bool seleccionado) {
        gotoxy(coordsElementosUserInput[indice].X, coordsElementosUserInput[indice].Y);
        if (seleccionado) {
            setColor(Colors::SELECCION);
            cout << "> ";
        } else {
            setColor(Colors::NORMAL);
            cout << "  ";
        }
        cout << elementosUserinput[indice] << ": ";
        setColor(Colors::NORMAL);
        cout << valor;
    }

    void renderizarBoton(const string& texto, int indice, bool seleccionado) {
        gotoxy(coordsBotones[indice].X, coordsBotones[indice].Y);
        if (seleccionado) {
            setColor(Colors::SELECCION);
            cout << "> ";
        } else {
            setColor(Colors::NORMAL);
            cout << "  ";
        }
        cout << texto;
    }

    void dibujarInterfazCompleta() {
        system("cls");
        UI_Login();

        // Campos
        for (int i = 0; i < ELEMENTOS_INPUT; ++i) {
            string valor = (i == 0) ? email : string(password.length(), '*');
            renderizarCampo(valor, i, campoActual == i);
        }

        // Botones
        for (int i = 0; i < CANT_BOTONES; ++i) {
            renderizarBoton(textosBotones[i], i, campoActual == i + 2);
        }

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
    }

    void actualizarSeleccion() {
        // Actualiza el campo/botón anterior como NO seleccionado
        if (campoAnterior >= 0 && campoAnterior < ELEMENTOS_INPUT) {
            string valorAnterior = (campoAnterior == 0) ? email : string(password.length(), '*');
            renderizarCampo(valorAnterior, campoAnterior, false);
        }
        // Actualiza el campo/botón actual como seleccionado
        if (campoActual >= 0 && campoActual < ELEMENTOS_INPUT) {
            string valorActual = (campoActual == 0) ? email : string(password.length(), '*');
            renderizarCampo(valorActual, campoActual, true);
        }
        campoAnterior = campoActual;
    }

public:
    Login() : campoActual(0), campoAnterior(-1), primeraRenderizacion(true), error(false) {}

    ResultadoPantalla ejecutar() override 
    {
        while (true) 
        {
            if (primeraRenderizacion) {
                dibujarInterfazCompleta();
                primeraRenderizacion = false;
            } else {
                actualizarSeleccion();
            }

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
                            dibujarInterfazCompleta(); // Redibuja para mostrar el error
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
                            dibujarInterfazCompleta(); // Redibuja para mostrar el cambio
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
                            dibujarInterfazCompleta(); // Redibuja para mostrar el cambio
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
