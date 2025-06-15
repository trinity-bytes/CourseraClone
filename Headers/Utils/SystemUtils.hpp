// filepath: Headers/Utils/SystemUtils.hpp
// Descripcion: Utilidades del sistema y constantes globales

#ifndef COURSERACLONE_UTILS_SYSTEMUTILS_HPP
#define COURSERACLONE_UTILS_SYSTEMUTILS_HPP

// Headers del sistema
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>

// CONSTANTES GLOBALES DEL PROGRAMA

// Dimensiones de la consola
constexpr int ANCHO_CONSOLA = 120;
constexpr int ALTO_CONSOLA = 33;

// Constantes de archivos y datos
constexpr int MAX_ESTUDIANTES_POR_CURSO = 100;
constexpr char SEPARADOR_CSV = ',';
const std::string RUTA_DATOS_USUARIOS = "Resources/Data/";
const std::string RUTA_BACKUP = "Resources/Backup/";

// ESTRUCTURAS DE DATOS COMUNES
// Estructura RGB para definir colores
struct Color {
    BYTE r, g, b;
    
    constexpr Color(BYTE _red, BYTE _green, BYTE _blue) 
        : r(_red), g(_green), b(_blue) {}
};

// Estructura para elementos de menú reutilizable
struct ElementoMenu {
    int id = -1;
    std::string titulo;
    std::string descripcion;
    bool activo = true;

    ElementoMenu() = default;
    
    ElementoMenu(const std::string& _titulo, const std::string& _descripcion, int _id = -1)
        : titulo(_titulo), descripcion(_descripcion), id(_id) {}
        
    ElementoMenu(int _id, const std::string& _titulo, const std::string& _descripcion)
        : id(_id), titulo(_titulo), descripcion(_descripcion) {}
};

/// @brief Estructura para coordenadas en la consola
struct Posicion {
    int x, y;
    
    constexpr Posicion(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    
    Posicion operator+(const Posicion& other) const {
        return Posicion(x + other.x, y + other.y);
    }
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
    // La clase System::Console es parte de .NET/CLI, no C++ estándar.
    // Para C++ nativo y WinAPI, se debe usar la siguiente aproximación:
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE; // Ocultar el cursor
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

// FUNCIONES DE MANIPULACIÓN DE COLORES

/// @brief Establece colores de texto y fondo con control de intensidad
inline void setConsoleColor(int textColor, int backgroundColor = ColorIndex::FONDO_PRINCIPAL, 
                            bool intenseText = false, bool intenseBackground = false) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    // Validar rangos (0-15)
    textColor &= 0xF;
    backgroundColor &= 0xF;
    
    WORD attributes = textColor | (backgroundColor << 4);
    
    if (intenseText) attributes |= FOREGROUND_INTENSITY;
    if (intenseBackground) attributes |= BACKGROUND_INTENSITY;
    
    SetConsoleTextAttribute(hConsole, attributes);
}

/// @brief Establece solo el color del texto manteniendo el fondo actual
inline void setTextColor(int color, bool intense = false) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    
    WORD attributes = (csbi.wAttributes & 0xF0) | (color & 0xF);
    if (intense) attributes |= FOREGROUND_INTENSITY;
    
    SetConsoleTextAttribute(hConsole, attributes);
}

/// @brief Restaura colores por defecto (texto primario sobre fondo principal)
inline void resetColor() {
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
}

// FUNCIONES DE POSICIONAMIENTO

/// @brief Mueve el cursor a una posición específica
inline void gotoXY(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(hConsole, coord);
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

// UTILIDADES DE VALIDACIÓN

/// @brief Verifica si una cadena es un número válido
inline bool esNumeroValido(const std::string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

/// @brief Verifica si un email tiene formato básico válido
inline bool esEmailValido(const std::string& email) {
    size_t at = email.find('@');
    size_t dot = email.find('.', at);
    return at != std::string::npos && dot != std::string::npos && 
           at > 0 && dot > at + 1 && dot < email.length() - 1;
}

/// @brief Limita una cadena a un tamaño máximo
inline std::string limitarTexto(const std::string& texto, size_t maxLength, 
                               const std::string& sufijo = "...") {
    if (texto.length() <= maxLength) return texto;
    return texto.substr(0, maxLength - sufijo.length()) + sufijo;
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

// ------
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
    // La clase System::Console es parte de .NET/CLI, no C++ estándar.
    // Para C++ nativo y WinAPI, se debe usar la siguiente aproximación:
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = { (SHORT)ANCHO_CONSOLA, (SHORT)ALTO_CONSOLA };
    SetConsoleScreenBufferSize(hConsole, bufferSize);

    SMALL_RECT windowSize = { 0, 0, (SHORT)(ANCHO_CONSOLA - 1), (SHORT)(ALTO_CONSOLA - 1) };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);    // Configurar color inicial (texto primario sobre fondo principal)
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);

    // Título de la aplicación
    SetConsoleTitle(L"Coursera Clone - Alpha 4");
}

#endif // COURSERACLONE_UTILS_SYSTEMUTILS_HPP