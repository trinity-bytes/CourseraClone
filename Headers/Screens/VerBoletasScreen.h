#pragma once

// Headers estándar
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

// Headers de consola
#include "../Entities/Boleta.h"
#include "../Entities/Estudiante.h"
#include "../Utils/SystemUtils.h"
#include "../Utils/ScreenSystem.h"
#include "../Utils/UI_Ascii.h"

// Screen to display student payment receipts/invoices
class VerBoletasScreen : public PantallaBase
{
private:
    Estudiante& _estudiante;
    std::vector<Boleta> _boletas;
    int _boletaSeleccionada;
    int _indiceInicio;
    int _boletasPorPagina;
    bool _primeraRenderizacion;
    AccionPantalla _pantallaAnterior;

    // Constantes para la interfaz
    const int COL_TITULO = 50;
    const int FILA_TITULO = 3;
    const int COL_VOLVER = 110;
    const int FILA_VOLVER = 3;

    const int COL_LISTA_BOLETAS = 10;
    const int FILA_LISTA_BOLETAS = 8;
    const int ESPACIO_ENTRE_BOLETAS = 2;
    const int ANCHO_BOLETA = 100;    void dibujarInterfazCompleta() {
        system("cls");
        // Supongamos que tenemos una función UI para esta pantalla
        // UI_VerBoletas();

        // Dibujar título
        gotoXY(COL_TITULO, FILA_TITULO);
        setConsoleColor(15, 1);
        std::cout << "MIS COMPROBANTES DE PAGO";

        // Dibujar botón volver
        gotoXY(COL_VOLVER, FILA_VOLVER);
        setConsoleColor(15, 1);
        std::cout << " VOLVER ";

        // Mostrar las boletas
        dibujarBoletas();
    }    void dibujarBoletas() {
        // Limpiar área de boletas
        for (int i = 0; i < _boletasPorPagina * ESPACIO_ENTRE_BOLETAS; i++) {
            gotoXY(COL_LISTA_BOLETAS, FILA_LISTA_BOLETAS + i);
            std::cout << std::string(ANCHO_BOLETA, ' ');
        }

        if (_boletas.empty()) {
            gotoXY(COL_LISTA_BOLETAS, FILA_LISTA_BOLETAS);
            setConsoleColor(15, 1);
            std::cout << "No tienes comprobantes de pago.";
            return;
        }

        int boletasAMostrar = (std::min)(_boletasPorPagina, static_cast<int>(_boletas.size()) - _indiceInicio);

        for (int i = 0; i < boletasAMostrar; i++) {
            int indice = _indiceInicio + i;
            Boleta boleta = _boletas[indice];

            int y = FILA_LISTA_BOLETAS + i * ESPACIO_ENTRE_BOLETAS;

            // Destacar la boleta seleccionada
            if (i == _boletaSeleccionada) {
                setConsoleColor(1, 13); // Color para selección
            }
            else {
                setConsoleColor(15, 1); // Color normal
            }

            // Mostrar información de la boleta
            gotoXY(COL_LISTA_BOLETAS, y);
            std::cout << "ID: " << boleta.getId()
                << " | Fecha: " << boleta.getFecha()
                << " | Precio: $" << std::fixed << std::setprecision(2) << boleta.getPrecio();
        }

        // Indicadores de paginación
        if (_indiceInicio > 0) {
            gotoXY(COL_LISTA_BOLETAS, FILA_LISTA_BOLETAS - 2);
            setConsoleColor(15, 1);
            std::cout << "Más arriba (Flecha ARRIBA)";
        }

        if (_indiceInicio + _boletasPorPagina < _boletas.size()) {
            gotoXY(COL_LISTA_BOLETAS, FILA_LISTA_BOLETAS + boletasAMostrar * ESPACIO_ENTRE_BOLETAS + 1);
            setConsoleColor(15, 1);
            std::cout << "Más abajo (Flecha ABAJO)";
        }

        setConsoleColor(15, 1); // Restaurar color normal
    }

public:
    VerBoletasScreen(Estudiante& _estudiante, AccionPantalla _pantallaAnterior = AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE)
        : PantallaBase(),
        _estudiante(_estudiante),
        _boletaSeleccionada(0),
        _indiceInicio(0),
        _boletasPorPagina(10),
        _primeraRenderizacion(true),
        _pantallaAnterior(_pantallaAnterior)
    {
        // Cargar boletas desde el estudiante
        // Problema
        LinkedList<Boleta>& boletasLista = _estudiante.getBoletas();

        // Convertir la lista enlazada a un vector para facilitar el manejo
        for (int i = 1; i <= boletasLista.getTamano(); i++) {
            _boletas.push_back(boletasLista.get(i));
        }
        /*
        if (estudiante != NULL) {
            
        }
        */
    }    
    
    ~VerBoletasScreen() = default;

    ResultadoPantalla ejecutar() override {
        ResultadoPantalla resultado;

        if (_primeraRenderizacion) {
            dibujarInterfazCompleta();
            _primeraRenderizacion = false;
        }

        while (true) {
            int tecla = _getch();

            switch (tecla) {
            case 224: // Tecla extendida
                tecla = _getch();

                switch (tecla) {
                case 72: // Flecha arriba
                    if (_boletaSeleccionada > 0) {
                        _boletaSeleccionada--;
                        dibujarBoletas();
                    }
                    else if (_indiceInicio > 0) {
                        _indiceInicio--;
                        dibujarBoletas();
                    }
                    break;

                case 80: // Flecha abajo
                    if (_boletaSeleccionada < (std::min)(_boletasPorPagina - 1, static_cast<int>(_boletas.size()) - _indiceInicio - 1)) {
                        _boletaSeleccionada++;
                        dibujarBoletas();
                    }
                    else if (_indiceInicio + _boletasPorPagina < _boletas.size()) {
                        _indiceInicio++;
                        dibujarBoletas();
                    }
                    break;
                }
                break;

            case 13: // Enter - Ver detalles de la boleta
                if (!_boletas.empty() && _indiceInicio + _boletaSeleccionada < _boletas.size()) {
                    // Implementar lógica para mostrar detalles (podría ser una nueva pantalla)
                    // Por ahora simplemente volvemos
                    resultado.accion = _pantallaAnterior;
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
