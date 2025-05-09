#pragma once
#include "Pantalla.h"
//#include "Controladora.h"
#include "ExtendedFunctions.h"
#include <string>

class Controladora; // Declaración anticipada de la clase Controladora

class Registro : public PantallaBase {
private:
    Controladora* controladora;
    std::string nombre;
    std::string email;
    std::string password;
    std::string confirmarPassword;
    int campoActual;
    bool error;
    std::string mensajeError;

    void renderizarCampo(const std::string& etiqueta, const std::string& valor, int y, bool seleccionado) {
        gotoxy(ANCHO_CONSOLA / 2 - 20, y);
        if (seleccionado) {
            setColor(Colors::SELECCION);
            std::cout << "> ";
        } else {
            setColor(Colors::NORMAL);
            std::cout << "  ";
        }
        std::cout << etiqueta << ": ";
        setColor(Colors::NORMAL);
        std::cout << valor;
    }

    void renderizarBoton(const std::string& texto, int y, bool seleccionado) {
        gotoxy(ANCHO_CONSOLA / 2 - 10, y);
        if (seleccionado) {
            setColor(Colors::SELECCION);
            std::cout << "> ";
        } else {
            setColor(Colors::NORMAL);
            std::cout << "  ";
        }
        std::cout << texto;
    }

public:
	Registro(Controladora* controladora) : PantallaBase(controladora),
        controladora(controladora), campoActual(0), error(false) {}

    void renderizar() override {
        system("cls");
        
        // Título
        gotoxy(ANCHO_CONSOLA / 2 - 10, 2);
        setColor(Colors::NORMAL);
        std::cout << "REGISTRO DE USUARIO";

        // Campos
        renderizarCampo("Nombre", nombre, 5, campoActual == 0);
        renderizarCampo("Email", email, 7, campoActual == 1);
        renderizarCampo("Contraseña", std::string(password.length(), '*'), 9, campoActual == 2);
        renderizarCampo("Confirmar Contraseña", std::string(confirmarPassword.length(), '*'), 11, campoActual == 3);

        // Botones
        renderizarBoton("Registrarse", 14, campoActual == 4);
        renderizarBoton("Volver", 16, campoActual == 5);

        // Mensaje de error
        if (error) {
            gotoxy(ANCHO_CONSOLA / 2 - mensajeError.length() / 2, 18);
            setColor(Colors::ERRORES);
            std::cout << mensajeError;
        }

        // Instrucciones
        gotoxy(ANCHO_CONSOLA / 2 - 20, ALTO_CONSOLA - 2);
        setColor(Colors::TEXTO_SECUNDARIO);
        std::cout << "Use las flechas para navegar y Enter para seleccionar";
    }

    void manejarInput(int tecla) override {
        switch (tecla) {
            case 72: // Flecha arriba
                if (campoActual > 0) campoActual--;
                break;
            case 80: // Flecha abajo
                if (campoActual < 5) campoActual++;
                break;
            case 13: // Enter
                if (campoActual == 4) { // Registrarse
                    if (validarCampos()) {
                        if (controladora->registrarUsuario(nombre, email, password, "ESTUDIANTE")) {
                            cambiarPantalla(Pantalla::LOGIN);
                        } else {
                            error = true;
                            mensajeError = "Error al registrar usuario. Intente nuevamente.";
                        }
                    }
                } else if (campoActual == 5) { // Volver
                    cambiarPantalla(Pantalla::LANDING_PAGE);
                }
                break;
            case 8: // Backspace
                if (campoActual >= 0 && campoActual <= 3) {
                    std::string* campo = nullptr;
                    switch (campoActual) {
                        case 0: campo = &nombre; break;
                        case 1: campo = &email; break;
                        case 2: campo = &password; break;
                        case 3: campo = &confirmarPassword; break;
                    }
                    if (campo && !campo->empty()) {
                        campo->pop_back();
                    }
                }
                break;
            default:
                if (tecla >= 32 && tecla <= 126) { // Caracteres imprimibles
                    std::string* campo = nullptr;
                    switch (campoActual) {
                        case 0: campo = &nombre; break;
                        case 1: campo = &email; break;
                        case 2: campo = &password; break;
                        case 3: campo = &confirmarPassword; break;
                    }
                    if (campo) {
                        campo->push_back(static_cast<char>(tecla));
                    }
                }
                break;
        }
        error = false;
    }

private:
    bool validarCampos() {
        if (nombre.empty() || email.empty() || password.empty() || confirmarPassword.empty()) {
            error = true;
            mensajeError = "Todos los campos son obligatorios";
            return false;
        }

        if (password != confirmarPassword) {
            error = true;
            mensajeError = "Las contraseñas no coinciden";
            return false;
        }

        if (password.length() < 6) {
            error = true;
            mensajeError = "La contraseña debe tener al menos 6 caracteres";
            return false;
        }

        // Validación básica de email
        if (email.find('@') == std::string::npos || email.find('.') == std::string::npos) {
            error = true;
            mensajeError = "Email inválido";
            return false;
        }

        return true;
    }
}; 