#pragma once
#include "MenuState.h"
#include "../UI_Ascii.h"
#include "../ExtendedFunctions.h"
#include <vector>
#include <string>

class CrearEspecializacionState : public MenuState {
private:
    // Constantes del formulario
    static const int CAMPO_TITULO = 0;
    static const int CAMPO_DESCRIPCION = 1;
    static const int CAMPO_CANTIDAD_CURSOS = 2;
    static const int CAMPO_GUARDAR = 3;
    static const int TOTAL_CAMPOS = 4;

    // Coordenadas para dibujar
    const COORD COORD_TITULO = {11, 15};
    const COORD COORD_DESCRIPCION = {11, 18};
    const COORD COORD_CANTIDAD_CURSOS = {11, 21};
    const COORD COORD_GUARDAR = {11, 24};

    // Estado del formulario
    int campoActual;
    int campoAnterior;
    bool primeraRenderizacion;
    bool editando;

    // Datos de la especialización
    string titulo;
    string descripcion;
    string cantidadCursos;
    string error;

    void actualizarSeleccion() {
        if (campoActual != campoAnterior) {
            // Desdibujar selección anterior
            actualizarCampo(campoAnterior, false);
            // Dibujar nueva selección
            actualizarCampo(campoActual, true);
            campoAnterior = campoActual;
        }
    }

    void actualizarCampo(int campo, bool seleccionado) {
        COORD coord;
        string etiqueta;
        string valor;

        switch (campo) {
            case CAMPO_TITULO:
                coord = COORD_TITULO;
                etiqueta = "Título: ";
                valor = titulo;
                break;
            case CAMPO_DESCRIPCION:
                coord = COORD_DESCRIPCION;
                etiqueta = "Descripción: ";
                valor = descripcion;
                break;
            case CAMPO_CANTIDAD_CURSOS:
                coord = COORD_CANTIDAD_CURSOS;
                etiqueta = "Cantidad de Cursos: ";
                valor = cantidadCursos;
                break;
            case CAMPO_GUARDAR:
                coord = COORD_GUARDAR;
                etiqueta = "[Guardar Especialización]";
                valor = "";
                break;
        }

        gotoXY(coord.X, coord.Y);
        if (seleccionado) SetConsoleColor(1, 4);
        else SetConsoleColor(15, 1);

        cout << etiqueta;
        if (!valor.empty()) cout << valor;
        SetConsoleColor(15, 1);
    }

    void dibujarInterfazCompleta() {
        system("cls");
        gotoXY(11, 12);
        cout << "Crear Nueva Especialización";
        gotoXY(11, 13);
        cout << "------------------------";

        // Dibujar todos los campos
        for (int i = 0; i < TOTAL_CAMPOS; i++) {
            actualizarCampo(i, i == campoActual);
        }

        // Mostrar error si existe
        if (!error.empty()) {
            gotoXY(11, 26);
            SetConsoleColor(4, 1);
            cout << "Error: " << error;
            SetConsoleColor(15, 1);
        }
    }

    bool validarFormulario() {
        if (titulo.empty()) {
            error = "El título es requerido";
            return false;
        }
        if (descripcion.empty()) {
            error = "La descripción es requerida";
            return false;
        }
        try {
            int cantidad = stoi(cantidadCursos);
            if (cantidad <= 0) {
                error = "La cantidad de cursos debe ser mayor a 0";
                return false;
            }
        }
        catch (...) {
            error = "La cantidad de cursos debe ser un número válido";
            return false;
        }
        return true;
    }

    void guardarEspecializacion() {
        if (!validarFormulario()) {
            dibujarInterfazCompleta();
            return;
        }

        if (controladora->crearEspecializacion(
            titulo,
            descripcion,
            stoi(cantidadCursos)
        )) {
            // Volver al dashboard
            controladora->volverAtras();
        }
        else {
            error = "Error al crear la especialización";
            dibujarInterfazCompleta();
        }
    }

public:
    CrearEspecializacionState(Controladora* controladora) : MenuState(controladora) {
        campoActual = 0;
        campoAnterior = 0;
        primeraRenderizacion = true;
        editando = false;
        error = "";
    }

    void render() override {
        if (primeraRenderizacion) {
            dibujarInterfazCompleta();
            primeraRenderizacion = false;
        }
        else {
            actualizarSeleccion();
        }
    }

    void handleInput(int tecla) override {
        if (editando) {
            switch (tecla) {
                case VK_RETURN:
                    editando = false;
                    break;
                case VK_BACK:
                    switch (campoActual) {
                        case CAMPO_TITULO:
                            if (!titulo.empty()) titulo.pop_back();
                            break;
                        case CAMPO_DESCRIPCION:
                            if (!descripcion.empty()) descripcion.pop_back();
                            break;
                        case CAMPO_CANTIDAD_CURSOS:
                            if (!cantidadCursos.empty()) cantidadCursos.pop_back();
                            break;
                    }
                    dibujarInterfazCompleta();
                    break;
                default:
                    if (tecla >= 32 && tecla <= 126) { // Caracteres imprimibles
                        char c = static_cast<char>(tecla);
                        switch (campoActual) {
                            case CAMPO_TITULO:
                                if (titulo.length() < 50) titulo += c;
                                break;
                            case CAMPO_DESCRIPCION:
                                if (descripcion.length() < 200) descripcion += c;
                                break;
                            case CAMPO_CANTIDAD_CURSOS:
                                if (cantidadCursos.length() < 2 && isdigit(c)) 
                                    cantidadCursos += c;
                                break;
                        }
                        dibujarInterfazCompleta();
                    }
                    break;
            }
        }
        else {
            switch (tecla) {
                case VK_UP:
                    if (campoActual > 0) {
                        campoActual--;
                        dibujarInterfazCompleta();
                    }
                    break;
                case VK_DOWN:
                    if (campoActual < TOTAL_CAMPOS - 1) {
                        campoActual++;
                        dibujarInterfazCompleta();
                    }
                    break;
                case VK_RETURN:
                    if (campoActual == CAMPO_GUARDAR) {
                        guardarEspecializacion();
                    }
                    else {
                        editando = true;
                    }
                    break;
                case VK_ESCAPE:
                    controladora->volverAtras();
                    break;
            }
        }
    }

    unique_ptr<MenuState> getNextState() override {
        return nullptr;
    }
}; 