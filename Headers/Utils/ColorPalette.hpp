// filepath: Headers/Utils/ColorPalette.hpp
// Descripcion: Paleta de colores oficial de Coursera y definiciones RGB

#ifndef COURSERACLONE_UTILS_COLORPALETTE_HPP
#define COURSERACLONE_UTILS_COLORPALETTE_HPP

#include <windows.h>

// Estructura RGB para definir colores
struct Color {
    BYTE r, g, b;
    
    constexpr Color(BYTE _red, BYTE _green, BYTE _blue) 
        : r(_red), g(_green), b(_blue) {}
};

// PALETA DE COLORES COURSERA OFICIAL
// Basada en la guía oficial de branding de Coursera (https://about.coursera.org/brand-guide/)
namespace Palette {
    // COLORES PRIMARIOS DE MARCA (Oficial Coursera)
    constexpr Color AZUL_COURSERA      = { 0, 86, 210 };     // #0056D2 - Color primario oficial
    constexpr Color NEGRO_COURSERA     = { 0, 0, 0 };        // #000000 - Negro oficial
    constexpr Color BLANCO_COURSERA    = { 255, 255, 255 };  // #FFFFFF - Blanco oficial
    
    // DERIVADOS DEL AZUL PRIMARIO (Para jerarquía visual)
    constexpr Color AZUL_HOVER         = { 0, 70, 180 };     // Hover del primario (-15% luminosidad)
    constexpr Color AZUL_PRESIONADO    = { 0, 55, 150 };     // Estado presionado (-25% luminosidad)
    constexpr Color AZUL_CLARO         = { 51, 133, 229 };   // Versión más clara (+20% luminosidad)
    constexpr Color AZUL_MUY_CLARO     = { 230, 241, 255 };  // Fondo azul muy sutil
    constexpr Color AZUL_LINK          = { 25, 100, 220 };   // Enlaces interactivos
    
    // GRISES NEUTROS (Escala profesional basada en el negro oficial)
    constexpr Color GRIS_900           = { 17, 17, 17 };     // Casi negro (títulos principales)
    constexpr Color GRIS_800           = { 34, 34, 34 };     // Texto importante
    constexpr Color GRIS_700           = { 68, 68, 68 };     // Texto normal
    constexpr Color GRIS_600           = { 102, 102, 102 };  // Texto secundario
    constexpr Color GRIS_500           = { 136, 136, 136 };  // Texto deshabilitado
    constexpr Color GRIS_400           = { 170, 170, 170 };  // Bordes, divisores
    constexpr Color GRIS_300           = { 204, 204, 204 };  // Bordes sutiles
    constexpr Color GRIS_200           = { 238, 238, 238 };  // Fondos de sección
    constexpr Color GRIS_100           = { 248, 248, 248 };  // Fondo general
    constexpr Color GRIS_50            = { 252, 252, 252 };  // Fondo alternativo
    
    // COLORES DE ESTADO (Semáforo universal para UX óptima)
    constexpr Color VERDE_EXITO        = { 34, 139, 34 };    // Verde bosque - éxito, completado
    constexpr Color VERDE_CLARO        = { 240, 248, 240 };  // Fondo de éxito
    constexpr Color ROJO_ERROR         = { 220, 38, 38 };    // Rojo profesional - errores
    constexpr Color ROJO_CLARO         = { 254, 242, 242 };  // Fondo de error
    constexpr Color AMARILLO_ATENCION  = { 245, 158, 11 };   // Amber - atención, pendiente
    constexpr Color AMARILLO_CLARO     = { 255, 251, 235 };  // Fondo de atención
    
    // COLORES ESPECIALES (Para mejorar UX)
    constexpr Color AZUL_INFO          = { 59, 130, 246 };   // Información
    constexpr Color AZUL_INFO_CLARO    = { 239, 246, 255 };  // Fondo informativo
    constexpr Color VIOLETA_PREMIUM    = { 124, 58, 237 };   // Para contenido premium
    constexpr Color VIOLETA_CLARO      = { 245, 243, 255 };  // Fondo premium
}

// INDICES DE COLORES DE CONSOLA (0-15) - Optimizados para UX
namespace ColorIndex {
    // COLORES FUNDAMENTALES
    constexpr int FONDO_PRINCIPAL      = 0;   // Gris 100 - Fondo general limpio
    constexpr int TEXTO_PRIMARIO       = 1;   // Gris 900 - Texto principal legible
    constexpr int AZUL_MARCA           = 2;   // Azul Coursera oficial - CTAs principales
    constexpr int BLANCO_PURO          = 3;   // Blanco Coursera - Contraste máximo
    
    // COLORES DE INTERACCIÓN
    constexpr int HOVER_ESTADO         = 4;   // Azul hover - Estados interactivos
    constexpr int LINK_COLOR           = 5;   // Azul link - Enlaces y navegación
    constexpr int PRESIONADO           = 6;   // Azul presionado - Feedback táctil
    constexpr int FONDO_AZUL_SUAVE     = 7;   // Azul muy claro - Destacados sutiles
    
    // JERARQUÍA DE TEXTO
    constexpr int TEXTO_SECUNDARIO     = 8;   // Gris 600 - Información secundaria
    constexpr int TEXTO_DESHABILITADO  = 9;   // Gris 500 - Estados inactivos
    constexpr int TEXTO_IMPORTANTE     = 10;  // Gris 800 - Énfasis moderado
    constexpr int BORDES_SUTILES       = 11;  // Gris 300 - Divisiones suaves
    
    // COLORES DE ESTADO (Semáforo UX)
    constexpr int EXITO_COLOR          = 12;  // Verde éxito - Confirmaciones
    constexpr int ERROR_COLOR          = 13;  // Rojo error - Alertas críticas
    constexpr int ATENCION_COLOR       = 14;  // Amarillo atención - Advertencias
    constexpr int INFO_COLOR           = 15;  // Azul info - Información neutral
}

// COMPATIBILIDAD CON CÓDIGO EXISTENTE
// Aliases actualizados para mantener compatibilidad con Utils.h anterior
namespace Colors {
    constexpr int NORMAL               = ColorIndex::TEXTO_PRIMARIO;
    constexpr int FONDO                = ColorIndex::FONDO_PRINCIPAL;
    constexpr int SELECCION            = ColorIndex::AZUL_MARCA;
    constexpr int ERRORES              = ColorIndex::ERROR_COLOR;
    constexpr int TEXTO_SECUNDARIO     = ColorIndex::TEXTO_SECUNDARIO;
    constexpr int EXITO                = ColorIndex::EXITO_COLOR;
    constexpr int ADVERTENCIA          = ColorIndex::ATENCION_COLOR;
    constexpr int LINK                 = ColorIndex::LINK_COLOR;
    constexpr int HOVER                = ColorIndex::HOVER_ESTADO;
    constexpr int BLANCO               = ColorIndex::BLANCO_PURO;
    constexpr int INFO                 = ColorIndex::INFO_COLOR;
}

#endif // COURSERACLONE_UTILS_COLORPALETTE_HPP
