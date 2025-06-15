// filepath: Headers/Utils/ConsoleConfig.hpp
// Descripcion: Configuración de consola (fuente, cursor, paleta, etc.)

#ifndef COURSERACLONE_UTILS_CONSOLECONFIG_HPP
#define COURSERACLONE_UTILS_CONSOLECONFIG_HPP

#include <windows.h>
#include <string>
#include <clocale>
#include "ColorPalette.hpp"
#include "ConsoleTypes.hpp"

// FUNCIONES DE CONFIGURACIÓN DE CONSOLA

/// @brief Establece una paleta de color en un índice específico
inline void setPaletteColor(int index, const Color& color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFOEX csbi;
    csbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    
    if (GetConsoleScreenBufferInfoEx(hConsole, &csbi)) {
        csbi.ColorTable[index & 0xF] = RGB(color.r, color.g, color.b);
        SetConsoleScreenBufferInfoEx(hConsole, &csbi);
    }
}

/// @brief Configura toda la paleta de colores oficial de Coursera
inline void configurarPaletaColores() {
    // COLORES FUNDAMENTALES (Base de la identidad visual)
    setPaletteColor(ColorIndex::FONDO_PRINCIPAL,        Palette::GRIS_100);
    setPaletteColor(ColorIndex::TEXTO_PRIMARIO,         Palette::GRIS_900);
    setPaletteColor(ColorIndex::AZUL_MARCA,             Palette::AZUL_COURSERA);
    setPaletteColor(ColorIndex::BLANCO_PURO,            Palette::BLANCO_COURSERA);
    
    // COLORES DE INTERACCIÓN (Para mejor UX)
    setPaletteColor(ColorIndex::HOVER_ESTADO,           Palette::AZUL_HOVER);
    setPaletteColor(ColorIndex::LINK_COLOR,             Palette::AZUL_LINK);
    setPaletteColor(ColorIndex::PRESIONADO,             Palette::AZUL_PRESIONADO);
    setPaletteColor(ColorIndex::FONDO_AZUL_SUAVE,       Palette::AZUL_MUY_CLARO);
    
    // JERARQUÍA DE TEXTO (Legibilidad optimizada)
    setPaletteColor(ColorIndex::TEXTO_SECUNDARIO,       Palette::GRIS_600);
    setPaletteColor(ColorIndex::TEXTO_DESHABILITADO,    Palette::GRIS_500);
    setPaletteColor(ColorIndex::TEXTO_IMPORTANTE,       Palette::GRIS_800);
    setPaletteColor(ColorIndex::BORDES_SUTILES,         Palette::GRIS_300);
    
    // COLORES DE ESTADO (Semáforo universal)
    setPaletteColor(ColorIndex::EXITO_COLOR,            Palette::VERDE_EXITO);
    setPaletteColor(ColorIndex::ERROR_COLOR,            Palette::ROJO_ERROR);
    setPaletteColor(ColorIndex::ATENCION_COLOR,         Palette::AMARILLO_ATENCION);
    setPaletteColor(ColorIndex::INFO_COLOR,             Palette::AZUL_INFO);
}

/// @brief Configura la fuente de la consola
inline void configurarFuente(const std::wstring& nombreFuente = L"Cascadia Code Semibold", 
                             int altoFuente = 22) {
    HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX cfi = { 0 };
    cfi.cbSize = sizeof(cfi);
    wcscpy_s(cfi.FaceName, nombreFuente.c_str());
    cfi.dwFontSize.Y = altoFuente;
    cfi.FontWeight = FW_NORMAL;
    SetCurrentConsoleFontEx(hConsola, FALSE, &cfi);
}

/// @brief Oculta el cursor parpadeante
inline void ocultarCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE; // Ocultar el cursor
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

/// @brief Configuración completa de la consola
inline void configurarConsola() {
    // Configurar codificación UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Configurar locale para español
    setlocale(LC_ALL, "es_ES.UTF-8");

    // Configurar apariencia
    ocultarCursor();
    configurarFuente();
    configurarPaletaColores();

    // Establecer tamaño de ventana
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = { (SHORT)ANCHO_CONSOLA, (SHORT)ALTO_CONSOLA };
    SetConsoleScreenBufferSize(hConsole, bufferSize);    SMALL_RECT windowSize = { 0, 0, (SHORT)(ANCHO_CONSOLA - 1), (SHORT)(ALTO_CONSOLA - 1) };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    // Título de la aplicación
    SetConsoleTitle(L"Coursera Clone - Alpha 4");
}

#endif // COURSERACLONE_UTILS_CONSOLECONFIG_HPP
