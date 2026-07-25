// filepath: Headers/Utils/InputUtils.hpp
// Descripcion: Utilidades para entrada de usuario y manejo de teclado

#ifndef COURSERACLONE_UTILS_INPUTUTILS_HPP
#define COURSERACLONE_UTILS_INPUTUTILS_HPP

#include <conio.h>
#include <windows.h>
#include <iostream>

// FUNCIONES DE ENTRADA DE USUARIO

/// @brief Limpia el buffer del teclado
inline void limpiarBuffer() {
    while (_kbhit()) _getch();
}

/// @brief Espera que se presione una tecla específica
inline bool esperarTecla(int teclaEsperada, int teclaEscape = 27) {
    limpiarBuffer();
    while (true) {
        if (_kbhit()) {
            int tecla = _getch();
            if (tecla == teclaEsperada) return true;
            if (tecla == teclaEscape) return false;
        }
        Sleep(16); // ~60 FPS
    }
}

/// @brief Espera cualquier tecla
inline int esperarCualquierTecla() {
    limpiarBuffer();
    return _getch();
}

/// @brief Pausa hasta que el usuario presione una tecla
/// @note Reemplaza al viejo pause por proceso externo: no lanza cmd.exe ni escribe su propio
///       mensaje en la pantalla alternativa del terminal.
inline void pausar(const char* mensaje = "Presiona cualquier tecla para continuar...") {
    if (mensaje != nullptr) std::cout << mensaje;
    esperarCualquierTecla();
}

#endif // COURSERACLONE_UTILS_INPUTUTILS_HPP
