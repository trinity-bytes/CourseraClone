#pragma once

#include "Pantalla.h"
#include "ExtendedFunctions.h"
#include "UI_Ascii.h"
#include "Estudiante.h"
#include "Boleta.h"
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

class VerBoletas : public PantallaBase
{
private:
    Estudiante& estudiante;
    vector<Boleta> boletas;
    int boletaSeleccionada;
    int indiceInicio;
    int boletasPorPagina;
    bool primeraRenderizacion;
    AccionPantalla pantallaAnterior;

    // Constantes para la interfaz
    const int COL_TITULO = 50;
    const int FILA_TITULO = 3;
    const int COL_VOLVER = 110;
    const int FILA_VOLVER = 3;

    const int COL_LISTA_BOLETAS = 10;
    const int FILA_LISTA_BOLETAS = 8;
    const int ESPACIO_ENTRE_BOLETAS = 2;
    const int ANCHO_BOLETA = 100;

    void dibujarInterfazCompleta() {
        system("cls");
        // Supongamos que tenemos una función UI para esta pantalla
        // UI_VerBoletas();

        // Dibujar título
        gotoXY(COL_TITULO, FILA_TITULO);
        SetConsoleColor(15, 1);
        cout << "MIS COMPROBANTES DE PAGO";

        // Dibujar botón volver
        gotoXY(COL_VOLVER, FILA_VOLVER);
        SetConsoleColor(15, 1);
        cout << " VOLVER ";

        // Mostrar las boletas
        dibujarBoletas();
    }

    void dibujarBoletas() {
        // Limpiar área de boletas
        for (int i = 0; i < boletasPorPagina * ESPACIO_ENTRE_BOLETAS; i++) {
            gotoXY(COL_LISTA_BOLETAS, FILA_LISTA_BOLETAS + i);
            cout << string(ANCHO_BOLETA, ' ');
        }

        if (boletas.empty()) {
            gotoXY(COL_LISTA_BOLETAS, FILA_LISTA_BOLETAS);
            SetConsoleColor(15, 1);
            cout << "No tienes comprobantes de pago.";
            return;
        }

        int boletasAMostrar = min(boletasPorPagina, static_cast<int>(boletas.size()) - indiceInicio);

        for (int i = 0; i < boletasAMostrar; i++) {
            int indice = indiceInicio + i;
            Boleta boleta = boletas[indice];

            int y = FILA_LISTA_BOLETAS + i * ESPACIO_ENTRE_BOLETAS;

            // Destacar la boleta seleccionada
            if (i == boletaSeleccionada) {
                SetConsoleColor(1, 13); // Color para selección
            }
            else {
                SetConsoleColor(15, 1); // Color normal
            }

            // Mostrar información de la boleta
            gotoXY(COL_LISTA_BOLETAS, y);
            cout << "ID: " << boleta.getId()
                << " | Fecha: " << boleta.getFecha()
                << " | Precio: $" << fixed << setprecision(2) << boleta.getPrecio();
        }

        // Indicadores de paginación
        if (indiceInicio > 0) {
            gotoXY(COL_LISTA_BOLETAS, FILA_LISTA_BOLETAS - 2);
            SetConsoleColor(15, 1);
            cout << "Más arriba (Flecha ARRIBA)";
        }

        if (indiceInicio + boletasPorPagina < boletas.size()) {
            gotoXY(COL_LISTA_BOLETAS, FILA_LISTA_BOLETAS + boletasAMostrar * ESPACIO_ENTRE_BOLETAS + 1);
            SetConsoleColor(15, 1);
            cout << "Más abajo (Flecha ABAJO)";
        }

        SetConsoleColor(15, 1); // Restaurar color normal
    }

public:
    VerBoletas(Estudiante& _estudiante, AccionPantalla _pantallaAnterior = AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE)
        : estudiante(_estudiante),
        boletaSeleccionada(0),
        indiceInicio(0),
        boletasPorPagina(10),
        primeraRenderizacion(true),
        pantallaAnterior(_pantallaAnterior)
    {
        // Cargar boletas desde el estudiante
        // Problema
        LinkedList<Boleta>& boletasLista = estudiante.getBoletas();

        // Convertir la lista enlazada a un vector para facilitar el manejo
        for (int i = 1; i <= boletasLista.getTamano(); i++) {
            boletas.push_back(boletasLista.get(i));
        }
        /*
        if (estudiante != NULL) {
            
        }
        */
    }

    ResultadoPantalla ejecutar() override {
        ResultadoPantalla resultado;

        if (primeraRenderizacion) {
            dibujarInterfazCompleta();
            primeraRenderizacion = false;
        }

        while (true) {
            int tecla = _getch();

            switch (tecla) {
            case 224: // Tecla extendida
                tecla = _getch();

                switch (tecla) {
                case 72: // Flecha arriba
                    if (boletaSeleccionada > 0) {
                        boletaSeleccionada--;
                        dibujarBoletas();
                    }
                    else if (indiceInicio > 0) {
                        indiceInicio--;
                        dibujarBoletas();
                    }
                    break;

                case 80: // Flecha abajo
                    if (boletaSeleccionada < min(boletasPorPagina - 1, static_cast<int>(boletas.size()) - indiceInicio - 1)) {
                        boletaSeleccionada++;
                        dibujarBoletas();
                    }
                    else if (indiceInicio + boletasPorPagina < boletas.size()) {
                        indiceInicio++;
                        dibujarBoletas();
                    }
                    break;
                }
                break;

            case 13: // Enter - Ver detalles de la boleta
                if (!boletas.empty() && indiceInicio + boletaSeleccionada < boletas.size()) {
                    // Implementar lógica para mostrar detalles (podría ser una nueva pantalla)
                    // Por ahora simplemente volvemos
                    resultado.accion = pantallaAnterior;
                    return resultado;
                }
                break;

            case 27: // ESC - Volver
                resultado.accion = AccionPantalla::IR_A_PERFIL_ESTUDIANTE; // En vez de IR_A_DASHBOARD_ESTUDIANTE
                return resultado;
            }
        }

        return resultado;
    }
};
