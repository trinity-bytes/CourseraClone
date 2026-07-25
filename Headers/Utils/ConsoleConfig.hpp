// filepath: Headers/Utils/ConsoleConfig.hpp
// Descripcion: Configuración e inicialización del terminal (modo VT, tamaño, ciclo de vida)

#ifndef COURSERACLONE_UTILS_CONSOLECONFIG_HPP
#define COURSERACLONE_UTILS_CONSOLECONFIG_HPP

#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <clocale>
#include <iostream>
#include <string>

#include "ColorPalette.hpp"
#include "ConsoleTypes.hpp"
#include "ConsoleVT.hpp"

// TAMAÑO DE LA VENTANA

/// @brief Bloquea hasta que el terminal tenga el tamaño mínimo que la UI necesita.
///
/// Windows Terminal no permite que la aplicación redimensione su ventana, así que
/// en vez de forzarlo se le pide cooperativamente y, si no alcanza, se le avisa al
/// usuario y se espera. Devuelve true si hubo que mostrar el aviso.
inline bool esperarTamanoMinimo(int anchoMinimo = ANCHO_CONSOLA, int altoMinimo = ALTO_CONSOLA)
{
    int ancho = 0;
    int alto = 0;
    bool avisoMostrado = false;

    while (VT::obtenerTamano(ancho, alto) && (ancho < anchoMinimo || alto < altoMinimo))
    {
        VT::aplicarColores(colorDeIndice(ColorIndex::TEXTO_PRIMARIO),
                           colorDeIndice(ColorIndex::FONDO_PRINCIPAL));
        VT::limpiarPantallaCompleta();

        VT::moverCursor(0, 0);
        std::cout << "La ventana del terminal es demasiado chica.";
        VT::moverCursor(0, 2);
        std::cout << "Necesito " << anchoMinimo << " x " << altoMinimo
                  << "  ->  ahora tenes " << ancho << " x " << alto << "   ";
        VT::moverCursor(0, 4);
        VT::aplicarColorTexto(colorDeIndice(ColorIndex::TEXTO_SECUNDARIO));
        std::cout << "Agranda la ventana (o baja el tamano de fuente con Ctrl + rueda).";

        avisoMostrado = true;
        Sleep(120);
    }

    return avisoMostrado;
}

// CICLO DE VIDA DEL TERMINAL

/// @brief Configuración completa del terminal al arrancar la aplicación
inline void configurarConsola()
{
    // Salida en UTF-8: el arte ASCII usa bloques y bordes Unicode
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_ALL, "es_ES.UTF-8");

    // Sin buffer: las secuencias VT y el texto comparten el mismo flujo, y el
    // orden entre ambos tiene que respetarse siempre.
    setvbuf(stdout, nullptr, _IONBF, 0);

    VT::habilitarModoVT();
    VT::entrarPantallaAlternativa();
    std::atexit(VT::restaurarTerminal);

    VT::mostrarCursor(false);
    SetConsoleTitleW(L"Coursera Clone - Beta 2");

    // Intento cooperativo de tamaño; si el terminal lo ignora, entra el aviso
    VT::solicitarTamano(ANCHO_CONSOLA, ALTO_CONSOLA);
    Sleep(60);
    esperarTamanoMinimo();

    VT::aplicarColores(colorDeIndice(ColorIndex::TEXTO_PRIMARIO),
                       colorDeIndice(ColorIndex::FONDO_PRINCIPAL));
    VT::limpiarPantallaCompleta();
}

/// @brief Oculta el cursor parpadeante
inline void ocultarCursor()
{
    VT::mostrarCursor(false);
}

#endif // COURSERACLONE_UTILS_CONSOLECONFIG_HPP
