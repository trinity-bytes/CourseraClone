#pragma once
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include "Utils.h"  // Incluimos Utils.h para usar sus constantes

using namespace std;
using namespace System;

struct Color 
{
    BYTE r;
    BYTE g;
    BYTE b;
};

// Paleta de colores COURSERA simplificada
namespace Palette 
{
    constexpr Color AZUL_PRIMARIO = { 8, 113, 240 };       // Botones principales, encabezados
    constexpr Color CREMA = { 244, 237, 221 };             // Fondo general
    constexpr Color AZUL_OSCURO = { 40, 16, 102 };         // Barra de navegación, pies de página
    constexpr Color AMARILLO_ACCENT = { 242, 208, 75 };    // Destacar elementos importantes
    constexpr Color ROSA_SECUNDARIO = { 238, 154, 128 };   // Botones secundarios, íconos
    constexpr Color BLANCO_PURO = { 255, 255, 255 };       // Texto principal
    constexpr Color VERDE_EXITO = { 80, 173, 89 };         // Indicadores de éxito, progreso
    constexpr Color GRIS_SUAVE = { 210, 210, 210 };        // Bordes, líneas divisorias
    constexpr Color AZUL_HOVER = { 20, 80, 200 };          // Efectos hover sobre botones azules
    constexpr Color ROSA_CLARO = { 255, 223, 211 };        // Fondos de alertas, tooltips
    constexpr Color GRIS_OSCURO = { 100, 100, 100 };       // Texto secundario
    constexpr Color ROJO_ERROR = { 222, 53, 57 };          // Mensajes de error, advertencias
    constexpr Color AZUL_LINK = { 120, 160, 255 };         // Enlaces interactivos
    constexpr Color VERDE_CLARO = { 220, 240, 215 };       // Fondos de éxito
    constexpr Color SOMBRA_AZUL = { 15, 45, 90 };          // Sombras, profundidad
    constexpr Color NEGRO = { 0, 0, 0 };    // Advertencias importantes
}

inline void setColorPalette(int index, Color color) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFOEX csbi;
    csbi.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);
    GetConsoleScreenBufferInfoEx(hConsole, &csbi);

    csbi.ColorTable[index] = RGB(color.r, color.g, color.b);

    SetConsoleScreenBufferInfoEx(hConsole, &csbi);
}

inline void gotoXY(int x, int y) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = x;     // Columna (horizontal)
    coord.Y = y;     // Fila (vertical)
    SetConsoleCursorPosition(hConsole, coord);
}

// Oculta el cursor parpadeante en la consola
inline void ocultarCursor() {
	Console::CursorVisible = false;
}

// Configurar la fuente y tamano de la letra
inline void CambiarFuenteConsola(const wstring& nombreFuente, COORD tamanioFuente) 
{
    HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_FONT_INFOEX cfi = { 0 };
    cfi.cbSize = sizeof(cfi);
    wcscpy_s(cfi.FaceName, nombreFuente.c_str());
    cfi.dwFontSize = tamanioFuente;
    cfi.FontWeight = FW_NORMAL;

    SetCurrentConsoleFontEx(hConsola, FALSE, &cfi);
}

/// Cambia el color de la consola
/*
// Opción normal (texto blanco sobre crema)
SetConsoleColor(1, 0);

// Opción seleccionada (texto azul intenso sobre crema claro)
SetConsoleColor(4, 0, true, true);

// Mensaje de error (texto rojo intenso sobre rosa claro)
SetConsoleColor(3, 10, true);

// Botón primario (texto blanco sobre azul con intensidad)
SetConsoleColor(1, 4, false, true);

// Texto secundario (gris oscuro sobre crema)
SetConsoleColor(7, 0);
*/
inline void SetConsoleColor(int textColor, int backgroundColor = 0, bool intenseText = false, bool intenseBackground = false) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Validar rangos de colores
    textColor &= 0xF;        // Mantener entre 0-15
    backgroundColor &= 0xF;  // Mantener entre 0-15

    // Construir atributo con control de intensidad
    WORD attributes = textColor | (backgroundColor << 4);

    if (intenseText) attributes |= FOREGROUND_INTENSITY;
    if (intenseBackground) attributes |= BACKGROUND_INTENSITY;

    SetConsoleTextAttribute(hConsole, attributes);
}

// Configurar la consola
inline void ConfigurarConsola()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	ocultarCursor();
	CambiarFuenteConsola(L"Cascadia Mono", { 0, 24 });

    // Establecer paleta de colores 
    setColorPalette(0, Palette::CREMA);            // Fondo general
    setColorPalette(1, Palette::BLANCO_PURO);      // Texto principal
    setColorPalette(2, Palette::VERDE_EXITO);      // Progreso completado
    setColorPalette(3, Palette::ROJO_ERROR);       // Tiempo restante
    setColorPalette(4, Palette::AZUL_PRIMARIO);    // Botones principales
    setColorPalette(5, Palette::ROSA_SECUNDARIO);  // Botones secundarios
    setColorPalette(6, Palette::GRIS_SUAVE);       // Bordes de tarjetas
    setColorPalette(7, Palette::GRIS_OSCURO);      // Texto secundario
    setColorPalette(8, Palette::AZUL_HOVER);       // Hover en botones
    setColorPalette(9, Palette::VERDE_CLARO);      // Fondos de notificaciones
    setColorPalette(10, Palette::ROSA_CLARO);      // Alertas suaves
    setColorPalette(11, Palette::AZUL_LINK);       // Enlaces interactivos
    setColorPalette(12, Palette::AMARILLO_ACCENT); // Estrellas de valoración
    setColorPalette(13, Palette::AZUL_OSCURO);     // Barra superior
    setColorPalette(14, Palette::SOMBRA_AZUL);     // Sombras de tarjetas
    setColorPalette(15, Palette::NEGRO);           // Texto normal o Límites de tiempo

    SetConsoleColor(15, 1);

	Console::SetWindowSize(ANCHO_CONSOLA, ALTO_CONSOLA);

	SetConsoleTitle(L"Coursera Clone | Alpha 2");
}

// =====================================================
// FUNCIONES DE COLOR
// Utilizan las constantes de color definidas en Utils.h
// =====================================================

// Establece el color del texto
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

// Restaura los colores por defecto
void resetColor() {
    setColor(Colors::NORMAL);
}

// Muestra un mensaje de error
void mostrarError(const string& mensaje) {
    setColor(Colors::ERRORES);
    cout << mensaje << endl;
    resetColor();
}

// Muestra un mensaje de éxito
void mostrarExito(const string& mensaje) {
    setColor(Colors::EXITO);
    cout << mensaje << endl;
    resetColor();
}

// =====================================================
// FUNCIONES DE ENTRADA
// =====================================================

// Limpia el buffer de entrada
void limpiarBuffer() {
    while (_kbhit()) _getch();
}

// Espera una tecla específica
bool esperarTecla(int tecla) {
    while (true) {
        if (_kbhit()) {
            int teclaPresionada = _getch();
            if (teclaPresionada == tecla) return true;
            if (teclaPresionada == 27) return false; // ESC
        }
        Sleep(16);
    }
}