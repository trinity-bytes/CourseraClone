#pragma once
#include "iostream"
#include "windows.h" // acceder a la api de windows

using namespace std;
using namespace System;

/// Constantes
const int ANCHO_CONSOLA = 120;
const int ALTO_CONSOLA = 35;

void gotoXY(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord;
    coord.X = x;     // Columna (horizontal)
    coord.Y = y;     // Fila (vertical)
    SetConsoleCursorPosition(hConsole, coord);
}

// Oculta el cursor parpadeante en la consola
void ocultarCursor() {
	Console::CursorVisible = false;
}

// Configurar la fuente y tamano de la letra
void CambiarFuenteConsola(const wstring& nombreFuente, COORD tamanioFuente) {
    HANDLE hConsola = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_FONT_INFOEX cfi = { 0 };
    cfi.cbSize = sizeof(cfi);
    wcscpy_s(cfi.FaceName, nombreFuente.c_str());
    cfi.dwFontSize = tamanioFuente;
    cfi.FontWeight = FW_NORMAL;

    SetCurrentConsoleFontEx(hConsola, FALSE, &cfi);
}

// Configurar la consola
void ConfigurarConsola()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	ocultarCursor();
	CambiarFuenteConsola(L"Cascadia Mono", { 0, 24 });

	Console::BackgroundColor = ConsoleColor::White;
	Console::ForegroundColor = ConsoleColor::Black;

	Console::SetWindowSize(ANCHO_CONSOLA, ALTO_CONSOLA);

	SetConsoleTitle(L"Coursera Clone | Alpha 1");
}