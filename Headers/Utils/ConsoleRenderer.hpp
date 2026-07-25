// filepath: Headers/Utils/ConsoleRenderer.hpp
// Descripcion: Funciones avanzadas de renderizado y UI con paleta Coursera

#ifndef COURSERACLONE_UTILS_CONSOLERENDERER_HPP
#define COURSERACLONE_UTILS_CONSOLERENDERER_HPP

#include <iostream>
#include <string>
#include <windows.h>
#include "ColorPalette.hpp"
#include "ConsoleTypes.hpp"
#include "ConsoleVT.hpp"
#include "ConsoleConfig.hpp"

// FUNCIONES DE MANIPULACIÓN DE COLORES

// Color vigente. Con VT no existe un "atributo actual" que se pueda consultar,
// así que la app lleva su propio estado para poder cambiar solo el texto.
inline int _indiceTextoActual = ColorIndex::TEXTO_PRIMARIO;
inline int _indiceFondoActual = ColorIndex::FONDO_PRINCIPAL;

/// @brief Establece colores de texto y fondo
/// @note Los flags de intensidad quedan por compatibilidad con las llamadas
///       existentes: con color RGB de 24 bits el matiz ya viene resuelto en la
///       paleta, no hace falta el bit de brillo de conhost.
inline void setConsoleColor(int textColor, int backgroundColor = ColorIndex::FONDO_PRINCIPAL,
                            bool intenseText = false, bool intenseBackground = false) {
    (void)intenseText;
    (void)intenseBackground;

    _indiceTextoActual = textColor & 0xF;
    _indiceFondoActual = backgroundColor & 0xF;

    VT::aplicarColores(colorDeIndice(_indiceTextoActual), colorDeIndice(_indiceFondoActual));
}

/// @brief Establece solo el color del texto manteniendo el fondo actual
inline void setTextColor(int color, bool intense = false) {
    (void)intense;

    _indiceTextoActual = color & 0xF;
    VT::aplicarColorTexto(colorDeIndice(_indiceTextoActual));
}

/// @brief Restaura colores por defecto (texto primario sobre fondo principal)
inline void resetColor() {
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
}

/// @brief Limpia la pantalla pintándola con el fondo de la aplicación
/// @note Reemplaza al viejo cls por proceso externo y, sobre todo,
///       el borrado usa el fondo vigente en vez del negro del terminal.
inline void limpiarPantalla() {
    esperarTamanoMinimo();
    resetColor();
    VT::limpiarPantallaCompleta();
}

// FUNCIONES DE POSICIONAMIENTO

/// @brief Mueve el cursor a una posición específica
inline void gotoXY(int x, int y) {
    VT::moverCursor(x, y);
}

/// @brief Mueve el cursor usando estructura Posicion
inline void gotoXY(const Posicion& pos) {
    gotoXY(pos.x, pos.y);
}

/// @brief Obtiene la posición actual del cursor
inline Posicion getCursorPosition() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        return Posicion(csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y);
    }
    return Posicion(0, 0);
}

// FUNCIONES DE SALIDA FORMATEADA

/// @brief Muestra un mensaje de error con formato profesional
inline void mostrarError(const std::string& mensaje, bool nuevaLinea = true) {
    setTextColor(ColorIndex::ERROR_COLOR, true);
    std::cout << "[ERROR] " << mensaje;
    if (nuevaLinea) std::cout << std::endl;
    resetColor();
}

/// @brief Muestra un mensaje de éxito con formato profesional
inline void mostrarExito(const std::string& mensaje, bool nuevaLinea = true) {
    setTextColor(ColorIndex::EXITO_COLOR, true);
    std::cout << "[EXITO] " << mensaje;
    if (nuevaLinea) std::cout << std::endl;
    resetColor();
}

/// @brief Muestra un mensaje de atención/advertencia con formato profesional
inline void mostrarAdvertencia(const std::string& mensaje, bool nuevaLinea = true) {
    setTextColor(ColorIndex::ATENCION_COLOR, true);
    std::cout << "[ATENCION] " << mensaje;
    if (nuevaLinea) std::cout << std::endl;
    resetColor();
}

/// @brief Muestra un mensaje informativo con formato profesional
inline void mostrarInfo(const std::string& mensaje, bool nuevaLinea = true) {
    setTextColor(ColorIndex::INFO_COLOR);
    std::cout << "[INFO] " << mensaje;
    if (nuevaLinea) std::cout << std::endl;
    resetColor();
}

/// @brief Imprime texto centrado en una línea
inline void imprimirCentrado(const std::string& texto, int ancho = ANCHO_CONSOLA) {
    int espacios = (ancho - static_cast<int>(texto.length())) / 2;
    if (espacios > 0) {
        std::cout << std::string(espacios, ' ');
    }
    std::cout << texto;
}

/// @brief Imprime una línea divisoria con estilo Coursera
inline void imprimirLinea(char caracter = '-', int longitud = ANCHO_CONSOLA, 
                          int color = ColorIndex::BORDES_SUTILES) {
    setTextColor(color);
    std::cout << std::string(longitud, caracter) << std::endl;
    resetColor();
}

// FUNCIONES AVANZADAS DE UI CON PALETA COURSERA

/// @brief Muestra un botón estilizado con los colores oficiales de Coursera
inline void mostrarBoton(const std::string& texto, bool esSeleccionado = false, bool esHover = false) {
    if (esSeleccionado || esHover) {
        setConsoleColor(ColorIndex::BLANCO_PURO, esHover ? ColorIndex::HOVER_ESTADO : ColorIndex::AZUL_MARCA);
    } else {
        setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    }
    std::cout << "[ " << texto << " ]";
    resetColor();
}

/// @brief Muestra un título principal con estilo Coursera
inline void mostrarTituloPrincipal(const std::string& titulo, bool centrado = true) {
    setTextColor(ColorIndex::AZUL_MARCA, true);
    if (centrado) {
        imprimirCentrado(titulo);
    } else {
        std::cout << titulo;
    }
    resetColor();
    std::cout << std::endl;
}

/// @brief Muestra un subtítulo con jerarquía visual clara
inline void mostrarSubtitulo(const std::string& subtitulo, bool centrado = false) {
    setTextColor(ColorIndex::TEXTO_IMPORTANTE);
    if (centrado) {
        imprimirCentrado(subtitulo);
    } else {
        std::cout << subtitulo;
    }
    resetColor();
    std::cout << std::endl;
}

/// @brief Muestra texto de ayuda o descripción
inline void mostrarTextoAyuda(const std::string& ayuda, bool centrado = false) {
    setTextColor(ColorIndex::TEXTO_SECUNDARIO);
    if (centrado) {
        imprimirCentrado(ayuda);
    } else {
        std::cout << ayuda;
    }
    resetColor();
    std::cout << std::endl;
}

/// @brief Muestra un enlace interactivo
inline void mostrarEnlace(const std::string& texto, bool subrayado = false) {
    setTextColor(ColorIndex::LINK_COLOR);
    if (subrayado) {
        std::cout << "\033[4m" << texto << "\033[0m"; // ANSI underline
    } else {
        std::cout << texto;
    }
    resetColor();
}

/// @brief Crea una caja de contenido con bordes sutiles
inline void crearCajaContenido(const std::string& contenido, int ancho = 60) {
    setTextColor(ColorIndex::BORDES_SUTILES);
    std::cout << "+" << std::string(ancho - 2, '-') << "+" << std::endl;
    
    resetColor();
    std::cout << "|";
    setTextColor(ColorIndex::TEXTO_PRIMARIO);
    
    int espaciosPadding = (ancho - 2 - static_cast<int>(contenido.length())) / 2;
    if (espaciosPadding > 0) {
        std::cout << std::string(espaciosPadding, ' ');
    }
    std::cout << contenido;
    if (espaciosPadding > 0) {
        std::cout << std::string(espaciosPadding, ' ');
    }
    
    resetColor();
    setTextColor(ColorIndex::BORDES_SUTILES);
    std::cout << "|" << std::endl;
    std::cout << "+" << std::string(ancho - 2, '-') << "+" << std::endl;
    resetColor();
}

/// @brief Muestra un indicador de progreso simple
inline void mostrarProgreso(int porcentaje, int ancho = 30) {
    setTextColor(ColorIndex::TEXTO_SECUNDARIO);
    std::cout << "[";
    
    int completado = (porcentaje * ancho) / 100;
    
    setTextColor(ColorIndex::AZUL_MARCA);
    for (int i = 0; i < completado; ++i) {
        std::cout << "█";
    }
    
    setTextColor(ColorIndex::BORDES_SUTILES);
    for (int i = completado; i < ancho; ++i) {
        std::cout << "░";
    }
    
    setTextColor(ColorIndex::TEXTO_SECUNDARIO);
    std::cout << "] " << porcentaje << "%";
    resetColor();
}

/// @brief Muestra un badge o etiqueta con color específico
inline void mostrarBadge(const std::string& texto, int colorFondo = ColorIndex::AZUL_MARCA) {
    setConsoleColor(ColorIndex::BLANCO_PURO, colorFondo);
    std::cout << " " << texto << " ";
    resetColor();
}

/// @brief Crea un separador visual elegante
inline void mostrarSeparadorElegante(int longitud = ANCHO_CONSOLA) {
    setTextColor(ColorIndex::BORDES_SUTILES);
    for (int i = 0; i < longitud; ++i) {
        std::cout << (i % 3 == 0 ? "═" : "─");
    }
    std::cout << std::endl;
    resetColor();
}

/// @brief Configura la visibilidad del cursor en la consola
inline void _configurarCursor(bool mostrar)
{
    VT::mostrarCursor(mostrar);
}

#endif // COURSERACLONE_UTILS_CONSOLERENDERER_HPP
