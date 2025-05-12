#pragma once
#include "Pantalla.h"
#include "Usuario.h"
#include "ExtendedFunctions.h"
#include <string>

class Registro : public PantallaBase {
private:
    static const int ELEMENTOS_INPUT = 4;
    static const int CANT_BOTONES = 3;

    string nombre;
    string email;
    string password;
    string confirmarPassword;
    TipoUsuario tipoUsuario;
    int campoActual;
    int campoAnterior;
    bool error;
    string mensajeError;
    bool primeraRenderizacion;
    int tipoUsuarioActual = 0; // 0: Estudiante, 1: Organización

    // Coordenadas para dibujar
    COORD coordsElementosUserInput[ELEMENTOS_INPUT] = { {11, 15}, {11, 20}, {11, 25}, {63, 25} };
    COORD coordsBotones[CANT_BOTONES] = { {68, 20}, {90, 20}, {53, 29} };
    const string textosBotones[CANT_BOTONES] = { " Soy un Estudiante ", " Soy una Organizacion ", " Crear Cuenta "};
    const string etiquetas[ELEMENTOS_INPUT] = { " ", " ", " ", " " };

    void mostrarCursor(bool mostrar) {
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        cursorInfo.bVisible = mostrar;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    }

    void renderizarCampo(const string& etiqueta, const string& valor, int indice, bool seleccionado) {
        gotoXY(coordsElementosUserInput[indice].X, coordsElementosUserInput[indice].Y);

        if (seleccionado) {
            SetConsoleColor(15, 4, true, true); 
            mostrarCursor(true);
        }
        else {
            SetConsoleColor(15, 0, false, false); 
            mostrarCursor(false);
        }

        if (indice == 2 || indice == 3) // Contraseña
            cout << string(valor.length(), '*');
        else
            cout << valor;

		SetConsoleColor(15, 0); // Restaurar color normal
    }

    void renderizarBoton(const string& texto, int indice, bool seleccionado) {
        gotoXY(coordsBotones[indice].X, coordsBotones[indice].Y);

        // Resaltar botones de tipo usuario basado en la selección actual o el tipo activo
        if (indice == 0 || indice == 1) {
            if (seleccionado || (indice == 0 && tipoUsuarioActual == 0) || (indice == 1 && tipoUsuarioActual == 1)) {
                SetConsoleColor(15, 4, true, true);
            }
            else {
                SetConsoleColor(15, 13, false, true);
            }
        }
        else {
            if (seleccionado) {
                SetConsoleColor(15, 5, true, true);
            }
            else {
                SetConsoleColor(15, 5, false, false);
            }
        }

        //mostrarCursor(false);
        cout << texto;
        SetConsoleColor(15, 0);
    }

    void dibujarInterfazCompleta() {
        system("cls");
        UI_Signup();

        for (int i = 3; i <= 7; i++) {
            gotoXY(3, i);
            SetConsoleColor(1, 13, true);
            cout << string(114, ' ');
        }

        SetConsoleColor(12, 13, true, true);
        gotoXY(42, 4);    cout << "▒█▀▀█ █▀▀█ █░░█ █▀▀█ █▀▀ █▀▀ █▀▀█ █▀▀█";
        gotoXY(42, 5);    cout << "▒█░░░ █░░█ █░░█ █▄▄▀ ▀▀█ █▀▀ █▄▄▀ █▄▄█";
        gotoXY(42, 6);    cout << "▒█▄▄█ ▀▀▀▀ ░▀▀▀ ▀░▀▀ ▀▀▀ ▀▀▀ ▀░▀▀ ▀░░▀";

        SetConsoleColor(12, 13, true, true);
        gotoXY(71, 7);    cout << "C L O N E";

        SetConsoleColor(15, 0);

        for (int i = 0; i < ELEMENTOS_INPUT; ++i) {
            string valor = (i == 2) ? string(password.length(), '*') : (i == 3) ? string(confirmarPassword.length(), '*') : (i == 0) ? nombre : email;
            renderizarCampo(etiquetas[i], (i == 0) ? nombre : (i == 1) ? email : (i == 2) ? password : confirmarPassword, i, campoActual == i);
        }
        //renderizarTipoUsuario();
        for (int i = 0; i < CANT_BOTONES; ++i) {
            renderizarBoton(textosBotones[i], i, campoActual == i + ELEMENTOS_INPUT);
        }
        if (error) {
            gotoXY(20, 23);
            SetConsoleColor(1, 4);
            cout << mensajeError;
            SetConsoleColor(15, 1);
        }

        SetConsoleColor(15, 0);
    }

    void actualizarSeleccion() {
        // Actualizar selección de botones
        for (int i = 0; i < CANT_BOTONES; ++i) {
            renderizarBoton(textosBotones[i], i, campoActual == i + ELEMENTOS_INPUT);
        }

        if (campoAnterior >= 0 && campoAnterior < ELEMENTOS_INPUT) {
            renderizarCampo(etiquetas[campoAnterior], (campoAnterior == 0) ? nombre : (campoAnterior == 1) ? email : (campoAnterior == 2) ? password : confirmarPassword, campoAnterior, false);
        }
        if (campoActual >= 0 && campoActual < ELEMENTOS_INPUT) {
            renderizarCampo(etiquetas[campoActual], (campoActual == 0) ? nombre : (campoActual == 1) ? email : (campoActual == 2) ? password : confirmarPassword, campoActual, true);
        }

        campoAnterior = campoActual;
        SetConsoleColor(15, 0);
    }

    bool validarCampos() {
        Usuario temp;
        if (nombre.empty() || email.empty() || password.empty() || confirmarPassword.empty()) {
            error = true;
            mensajeError = "Todos los campos son obligatorios";
            return false;
        }
        if (temp.buscarIndexUsuario(email, tipoUsuario) != -1) {
            error = true;
            mensajeError = "El email ya está registrado";
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
        return true;
    }

    void guardarUsuario() {
        Usuario nuevo;
        nuevo.setNombre(nombre);
        nuevo.setUsername(email);
        nuevo.setContrasena(password);
        nuevo.setTipoUsuario(tipoUsuario);
        nuevo.guardar();
    }

public:
    Registro() : campoActual(0), campoAnterior(-1), error(false), primeraRenderizacion(true), tipoUsuario(TipoUsuario::ESTUDIANTE) {}

    ResultadoPantalla ejecutar() override 
    {
        ResultadoPantalla res;
        while (true) 
        {
            if (primeraRenderizacion) 
            {
                dibujarInterfazCompleta();
				mostrarCursor(true);
                primeraRenderizacion = false;
                gotoXY(11, 15);
            } else {
                actualizarSeleccion();
            }

            int tecla = _getch();
            switch (tecla) 
            {
                case 72: // Flecha arriba
                    //if (campoActual > 0) campoActual--;

                    if (campoActual == 2) { // Si estamos en el campo de contraseña
                        campoActual = ELEMENTOS_INPUT + 1; // Ir al botón de Organización
                    }
                    else if (campoActual == 3) { // Si estamos en confirmar contraseña
                        campoActual = 2; // Ir a contraseña
                    }
                    else if (campoActual == ELEMENTOS_INPUT + 2) { // Si estamos en Crear Cuenta
                        campoActual = 3; // Ir a confirmar contraseña
                    }
                    else if (campoActual == ELEMENTOS_INPUT) { // Si estamos en botón Estudiante
                        campoActual = 1; // Ir al campo de email
                    }
                    else if (campoActual == ELEMENTOS_INPUT + 1) { // Si estamos en botón Organización
                        campoActual = ELEMENTOS_INPUT; // Ir al campo de esrudiante
                    }
                    else if (campoActual > 0) { // Para el resto de casos
                        campoActual--;
                    }
                    break;
                case 80: // Flecha abajo
                    //if (campoActual < ELEMENTOS_INPUT + CANT_BOTONES - 1) campoActual++;

                    if (campoActual == 1) { // Si estamos en el campo de email
                        campoActual = ELEMENTOS_INPUT; // Ir al botón de Estudiante
                    }
                    else if (campoActual == ELEMENTOS_INPUT) { // Si estamos en estudiante
                        campoActual = ELEMENTOS_INPUT + 1; // Ir a confirmar organizacion
                    }
                    else if (campoActual == ELEMENTOS_INPUT + 1) { // Si estamos en organizacion
                        campoActual = 2; // Ir al campo de contraseña
                    }
                    else if (campoActual == 2) { // Si estamos en contraseña
                        campoActual = 3; // Ir a confirmar contraseña
                    }
                    else if (campoActual == 3) { // Si estamos en confirmar contraseña
                        campoActual = ELEMENTOS_INPUT + 2; // Ir a Crear Cuenta
                    }
                    else if (campoActual < ELEMENTOS_INPUT - 1) { // Para el resto de casos antes de email
                        campoActual++;
                    }
                    break;
                case 27: // ESC
                    res.accion = AccionPantalla::IR_A_LANDING_PAGE;
                    return res;
                    break;
                case 13: // Enter
                    if (campoActual == ELEMENTOS_INPUT) {
                        tipoUsuarioActual = 0;
                        tipoUsuario = TipoUsuario::ESTUDIANTE;
                    }
                    else if (campoActual == ELEMENTOS_INPUT + 1) { // Si estamos en organizacion
                        tipoUsuarioActual = 1; 
                        tipoUsuario = TipoUsuario::EMPRESA;
                    }
                    else if (campoActual == ELEMENTOS_INPUT + 2) { // Registrar
                        tipoUsuario = (tipoUsuarioActual == 0) ? TipoUsuario::ESTUDIANTE : TipoUsuario::EMPRESA;
                        if (validarCampos()) {
                            guardarUsuario();
                            //ResultadoPantalla res;
                            res.accion = AccionPantalla::IR_A_LOGIN;
                            return res;
                        }
                        else {
                            dibujarInterfazCompleta();
                            continue;
                        }
                    }
                    break;
                case 8: // Backspace
                    if (campoActual >= 0 && campoActual < ELEMENTOS_INPUT) 
                    {
                        string* campo = nullptr;
                        switch (campoActual) {
                            case 0: campo = &nombre; break;
                            case 1: campo = &email; break;
                            case 2: campo = &password; break;
                            case 3: campo = &confirmarPassword; break;
                        }
                        if (campo && !campo->empty()) 
                        {
                            campo->pop_back();
                            dibujarInterfazCompleta();
                        }
                    }
                    break;
                default:
                    if (tecla >= 32 && tecla <= 126) 
                    {
                        string* campo = nullptr;
                        switch (campoActual) {
                            case 0: campo = &nombre; break;
                            case 1: campo = &email; break;
                            case 2: campo = &password; break;
                            case 3: campo = &confirmarPassword; break;
                        }
                        if (campo) {
                            campo->push_back(static_cast<char>(tecla));
                            dibujarInterfazCompleta();
                        }
                    }
                    break;
            }
            error = false;
        }
    }
}; 