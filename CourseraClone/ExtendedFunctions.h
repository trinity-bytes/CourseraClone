#pragma once
#include "iostream"
#include "windows.h" // acceder a la api de windows

using namespace std;
using namespace System;

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

	CambiarFuenteConsola(L"Cascadia Mono", { 0, 24 });

	Console::BackgroundColor = ConsoleColor::White;
	Console::ForegroundColor = ConsoleColor::Black;

	Console::SetWindowSize(120, 33);

	SetConsoleTitle(L"Coursera Clone | Alpha 1");
}