// filepath: Headers/Utils/InputUtils.hpp
// Descripcion: Utilidades para entrada de usuario y manejo de teclado

#ifndef COURSERACLONE_UTILS_INPUTUTILS_HPP
#define COURSERACLONE_UTILS_INPUTUTILS_HPP

#include <conio.h>
#include <windows.h>

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

#endif // COURSERACLONE_UTILS_INPUTUTILS_HPP
