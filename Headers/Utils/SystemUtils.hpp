// filepath: Headers/Utils/SystemUtils.hpp
// Descripcion: Utilidades del sistema - Archivo principal refactorizado

#ifndef COURSERACLONE_UTILS_SYSTEMUTILS_HPP
#define COURSERACLONE_UTILS_SYSTEMUTILS_HPP

// Headers del sistema
#include <windows.h>
#include <iostream>
#include <string>

// Headers de utilidades modularizadas
#include "ConsoleTypes.hpp"     // Estructuras y constantes comunes
#include "ColorPalette.hpp"     // Paleta de colores de Coursera
#include "ConsoleConfig.hpp"    // Configuración de consola
#include "ConsoleRenderer.hpp"  // Funciones de renderizado y UI
#include "InputUtils.hpp"       // Utilidades de entrada
#include "ValidationUtils.hpp"  // Utilidades de validación

// FUNCIONES DE CONVENIENCIA PARA COMPATIBILIDAD TOTAL
// Estas funciones actúan como "facade" y garantizan compatibilidad con código existente

/// @brief Configuración completa de la consola (función principal de inicialización)
inline void inicializarSistema() {
    configurarConsola();
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
}

/// @brief Función legacy para compatibilidad - ahora delegada a configurarConsola()
inline void setupConsola() {
    inicializarSistema();
}

#endif // COURSERACLONE_UTILS_SYSTEMUTILS_HPP