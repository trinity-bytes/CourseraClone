#pragma once
#include "Pantalla.h"
#include "Usuario.h"
//#include "Controladora.h"
#include "ExtendedFunctions.h"
#include <string>

class Controladora; // Declaración anticipada de la clase Controladora

class Registro : public PantallaBase {
private:
    string nombre;
    string email;
    string password;
    string confirmarPassword;
    TipoUsuario tipoUsuario;
    int campoActual;
    bool error;
    string mensajeError;

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
    Registro() : campoActual(0), error(false) {}

    ResultadoPantalla ejecutar() override {
        while (true) {
            system("cls");
            // Título
            gotoxy(ANCHO_CONSOLA / 2 - 10, 2);
            setColor(Colors::NORMAL);
            cout << "REGISTRO DE USUARIO";

            // Campos
            renderizarCampo("Nombre", nombre, 5, campoActual == 0);
            renderizarCampo("Email", email, 7, campoActual == 1);
            renderizarCampo("Contraseña", string(password.length(), '*'), 9, campoActual == 2);
            renderizarCampo("Confirmar Contraseña", string(confirmarPassword.length(), '*'), 11, campoActual == 3);

            // Botones
            renderizarBoton("Registrarse", 14, campoActual == 4);
            renderizarBoton("Volver", 16, campoActual == 5);

            // Mensaje de error
            if (error) {
                gotoxy(ANCHO_CONSOLA / 2 - mensajeError.length() / 2, 18);
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
                    if (campoActual < 5) campoActual++;
                    break;
                case 13: // Enter
                    if (campoActual == 4) { // Registrarse
                        if (validarCampos()) {
                            ResultadoPantalla res;
                            res.accion = AccionPantalla::IR_A_LOGIN;
                            res.email = email;
                            res.password = password;
                            res.email = email;
                            return res;
                        }
                    } else if (campoActual == 5) { // Volver
                        ResultadoPantalla res;
                        res.accion = AccionPantalla::IR_A_LANDING_PAGE;
                        return res;
                    }
                    break;
                case 8: // Backspace
                    if (campoActual >= 0 && campoActual <= 3) {
                        string* campo = nullptr;
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
                        string* campo = nullptr;
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
    }

private:

    bool validarCampos() {
        Usuario temp;
        
        if (nombre.empty() || email.empty() || password.empty() || confirmarPassword.empty()) {
            error = true;
            mensajeError = "Todos los campos son obligatorios";
            return false;
        }

        if (temp.usuarioRepetido(email, tipoUsuario)) {
            error = true;
            mensajeError = "El email corresponde a otro usuario";
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

        temp.setNombre(nombre);
        temp.setContrasena(password);
        temp.setUsername(email);
        // temp->setTipoUsuario(tipoUsuario);
        temp.guardar();

        return true;
    }
}; 