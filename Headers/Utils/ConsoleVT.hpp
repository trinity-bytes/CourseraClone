// filepath: Headers/Utils/ConsoleVT.hpp
// Descripcion: Capa de secuencias VT (Virtual Terminal) para Windows Terminal

#ifndef COURSERACLONE_UTILS_CONSOLEVT_HPP
#define COURSERACLONE_UTILS_CONSOLEVT_HPP

#include <windows.h>
#include <cstdio>
#include <iostream>
#include <string>

#include "ColorPalette.hpp"

// Windows SDK antiguos no siempre definen el flag de VT.
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

/// @brief Primitivas de terminal basadas en secuencias de escape ANSI/VT.
///
/// Windows Terminal ignora las APIs legacy de consola (remapeo de paleta,
/// cambio de fuente, redimension de ventana desde la app). Las secuencias VT
/// son el contrato que si respeta, y ademas funcionan en conhost moderno.
namespace VT
{
    // ESTADO DE LA TERMINAL

    /// @brief Indica si la app entro a la pantalla alternativa.
    inline bool _enPantallaAlternativa = false;

    // CONFIGURACION DEL MODO DE CONSOLA

    /// @brief Activa el procesamiento de secuencias VT en el handle de salida
    inline bool habilitarModoVT()
    {
        HANDLE salida = GetStdHandle(STD_OUTPUT_HANDLE);
        if (salida == INVALID_HANDLE_VALUE) return false;

        DWORD modo = 0;
        if (!GetConsoleMode(salida, &modo)) return false;

        modo |= ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        return SetConsoleMode(salida, modo) != 0;
    }

    // COLOR (24 bits reales, sin depender de la paleta del terminal)

    /// @brief Aplica color de texto y de fondo como RGB verdadero
    inline void aplicarColores(const Color& texto, const Color& fondo)
    {
        char secuencia[64];
        std::snprintf(secuencia, sizeof(secuencia),
                      "\x1b[38;2;%u;%u;%um\x1b[48;2;%u;%u;%um",
                      static_cast<unsigned>(texto.r),
                      static_cast<unsigned>(texto.g),
                      static_cast<unsigned>(texto.b),
                      static_cast<unsigned>(fondo.r),
                      static_cast<unsigned>(fondo.g),
                      static_cast<unsigned>(fondo.b));
        std::cout << secuencia;
    }

    /// @brief Aplica solo el color de texto, conservando el fondo vigente
    inline void aplicarColorTexto(const Color& texto)
    {
        char secuencia[32];
        std::snprintf(secuencia, sizeof(secuencia), "\x1b[38;2;%u;%u;%um",
                      static_cast<unsigned>(texto.r),
                      static_cast<unsigned>(texto.g),
                      static_cast<unsigned>(texto.b));
        std::cout << secuencia;
    }

    /// @brief Devuelve la terminal a sus atributos por defecto
    inline void restablecerAtributos()
    {
        std::cout << "\x1b[0m";
    }

    // CURSOR

    /// @brief Mueve el cursor a una posicion absoluta (origen 0,0)
    inline void moverCursor(int x, int y)
    {
        char secuencia[32];
        std::snprintf(secuencia, sizeof(secuencia), "\x1b[%d;%dH", y + 1, x + 1);
        std::cout << secuencia;
    }

    /// @brief Muestra u oculta el cursor
    inline void mostrarCursor(bool visible)
    {
        std::cout << (visible ? "\x1b[?25h" : "\x1b[?25l");
    }

    // PANTALLA

    /// @brief Borra toda la pantalla con el fondo vigente y sube el cursor al origen
    inline void limpiarPantallaCompleta()
    {
        std::cout << "\x1b[2J\x1b[H";
    }

    /// @brief Entra a la pantalla alternativa (no ensucia el historial del terminal)
    inline void entrarPantallaAlternativa()
    {
        if (_enPantallaAlternativa) return;
        std::cout << "\x1b[?1049h";
        _enPantallaAlternativa = true;
    }

    /// @brief Vuelve a la pantalla principal del terminal
    inline void salirPantallaAlternativa()
    {
        if (!_enPantallaAlternativa) return;
        std::cout << "\x1b[?1049l";
        _enPantallaAlternativa = false;
    }

    // TAMANO DE LA VENTANA

    /// @brief Lee el tamano visible actual de la ventana del terminal
    inline bool obtenerTamano(int& ancho, int& alto)
    {
        CONSOLE_SCREEN_BUFFER_INFO info;
        if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info)) return false;

        ancho = info.srWindow.Right - info.srWindow.Left + 1;
        alto = info.srWindow.Bottom - info.srWindow.Top + 1;
        return true;
    }

    /// @brief Pide al terminal un tamano concreto (XTWINOPS).
    ///        Es un intento cooperativo: si el terminal lo ignora, no pasa nada.
    inline void solicitarTamano(int ancho, int alto)
    {
        char secuencia[32];
        std::snprintf(secuencia, sizeof(secuencia), "\x1b[8;%d;%dt", alto, ancho);
        std::cout << secuencia;
    }

    // CICLO DE VIDA

    /// @brief Deja el terminal como estaba antes de arrancar la app
    inline void restaurarTerminal()
    {
        mostrarCursor(true);
        restablecerAtributos();
        salirPantallaAlternativa();
        std::cout.flush();
    }
}

#endif // COURSERACLONE_UTILS_CONSOLEVT_HPP
