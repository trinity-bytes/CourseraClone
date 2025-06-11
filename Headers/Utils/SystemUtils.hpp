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
constexpr int ALTO_CONSOLA = 35;

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


// PALETA DE COLORES COURSERA
namespace Palette {
    // Colores principales de la marca Coursera
    constexpr Color AZUL_PRIMARIO      = { 8, 113, 240 };    // Botones principales, encabezados
    constexpr Color AZUL_OSCURO        = { 40, 16, 102 };    // Barra de navegación, fondos importantes
    constexpr Color AMARILLO_ACCENT    = { 242, 208, 75 };   // Destacar elementos
    constexpr Color ROSA_SECUNDARIO    = { 238, 154, 128 };  // Botones secundarios
    
    // Colores de estado y feedback
    constexpr Color VERDE_EXITO        = { 80, 173, 89 };    // Éxito, progreso
    constexpr Color ROJO_ERROR         = { 222, 53, 57 };    // Errores, advertencias
    constexpr Color AZUL_LINK          = { 120, 160, 255 };  // Enlaces interactivos
    constexpr Color AZUL_HOVER         = { 20, 80, 200 };    // Efectos hover
    
    // Colores neutros y fondos
    constexpr Color BLANCO_PURO        = { 255, 255, 255 };  // Texto principal, fondos limpios
    constexpr Color GRIS_MUY_CLARO     = { 248, 248, 248 };  // Fondo general principal
    constexpr Color GRIS_CLARO         = { 230, 230, 230 };  // Fondos de secciones
    constexpr Color GRIS_SUAVE         = { 180, 180, 180 };  // Bordes, divisorias
    constexpr Color GRIS_MEDIO         = { 120, 120, 120 };  // Texto secundario
    constexpr Color GRIS_OSCURO        = { 70, 70, 70 };     // Texto menos importante
    constexpr Color NEGRO              = { 0, 0, 0 };        // Texto intenso
    
    // Colores de fondo especiales (solo para alertas/notificaciones)
    constexpr Color CREMA_SUAVE        = { 252, 248, 240 };  // Solo para notificaciones especiales
    constexpr Color VERDE_CLARO        = { 240, 248, 240 };  // Fondos de éxito
    constexpr Color SOMBRA_AZUL        = { 15, 45, 90 };     // Sombras, profundidad
}

// INDICES DE COLORES DE CONSOLA (0-15)
namespace ColorIndex {
    // Mapeo de colores a índices de consola para fácil referencia
    constexpr int FONDO_GENERAL        = 0;   // Gris muy claro (reemplaza crema)
    constexpr int TEXTO_PRINCIPAL      = 1;   // Negro (mejor contraste)
    constexpr int EXITO                = 2;   // Verde éxito
    constexpr int ERROR_COLOR          = 3;   // Rojo error
    constexpr int BOTON_PRIMARIO       = 4;   // Azul primario
    constexpr int BOTON_SECUNDARIO     = 5;   // Rosa secundario
    constexpr int BORDES               = 6;   // Gris suave
    constexpr int TEXTO_SECUNDARIO     = 7;   // Gris medio
    constexpr int HOVER                = 8;   // Azul hover
    constexpr int FONDO_SECCION        = 9;   // Gris claro (para secciones)
    constexpr int FONDO_ALERTA         = 10;  // Crema suave (solo alertas)
    constexpr int ENLACES              = 11;  // Azul link
    constexpr int ACENTO               = 12;  // Amarillo accent
    constexpr int NAVEGACION           = 13;  // Azul oscuro
    constexpr int SOMBRAS              = 14;  // Sombra azul
    constexpr int TEXTO_INTENSO        = 15;  // Blanco puro (para fondos oscuros)
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

/// @brief Configura toda la paleta de colores de Coursera
inline void configurarPaletaColores() {
    setPaletteColor(ColorIndex::FONDO_GENERAL,      Palette::GRIS_MUY_CLARO);
    setPaletteColor(ColorIndex::TEXTO_PRINCIPAL,    Palette::NEGRO);
    setPaletteColor(ColorIndex::EXITO,              Palette::VERDE_EXITO);
    setPaletteColor(ColorIndex::ERROR_COLOR,              Palette::ROJO_ERROR);
    setPaletteColor(ColorIndex::BOTON_PRIMARIO,     Palette::AZUL_PRIMARIO);
    setPaletteColor(ColorIndex::BOTON_SECUNDARIO,   Palette::ROSA_SECUNDARIO);
    setPaletteColor(ColorIndex::BORDES,             Palette::GRIS_SUAVE);
    setPaletteColor(ColorIndex::TEXTO_SECUNDARIO,   Palette::GRIS_MEDIO);
    setPaletteColor(ColorIndex::HOVER,              Palette::AZUL_HOVER);
    setPaletteColor(ColorIndex::FONDO_SECCION,      Palette::GRIS_CLARO);
    setPaletteColor(ColorIndex::FONDO_ALERTA,       Palette::CREMA_SUAVE);
    setPaletteColor(ColorIndex::ENLACES,            Palette::AZUL_LINK);
    setPaletteColor(ColorIndex::ACENTO,             Palette::AMARILLO_ACCENT);
    setPaletteColor(ColorIndex::NAVEGACION,         Palette::AZUL_OSCURO);
    setPaletteColor(ColorIndex::SOMBRAS,            Palette::SOMBRA_AZUL);
    setPaletteColor(ColorIndex::TEXTO_INTENSO,      Palette::BLANCO_PURO);
}

/// @brief Configura la fuente de la consola
inline void configurarFuente(const std::wstring& nombreFuente = L"Cascadia Mono", 
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
inline void setConsoleColor(int textColor, int backgroundColor = ColorIndex::FONDO_GENERAL, 
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

/// @brief Restaura colores por defecto
inline void resetColor() {
    setConsoleColor(ColorIndex::TEXTO_PRINCIPAL, ColorIndex::FONDO_GENERAL);
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

/// @brief Muestra un mensaje de error con formato
inline void mostrarError(const std::string& mensaje, bool nuevaLinea = true) {
    setTextColor(ColorIndex::ERROR_COLOR, true);
    std::cout << "[ERROR] " << mensaje;
    if (nuevaLinea) std::cout << std::endl;
    resetColor();
}

/// @brief Muestra un mensaje de éxito con formato
inline void mostrarExito(const std::string& mensaje, bool nuevaLinea = true) {
    setTextColor(ColorIndex::EXITO, true);
    std::cout << "[EXITO] " << mensaje;
    if (nuevaLinea) std::cout << std::endl;
    resetColor();
}

/// @brief Muestra un mensaje de advertencia con formato
inline void mostrarAdvertencia(const std::string& mensaje, bool nuevaLinea = true) {
    setTextColor(ColorIndex::ACENTO, true);
    std::cout << "[AVISO] " << mensaje;
    if (nuevaLinea) std::cout << std::endl;
    resetColor();
}

/// @brief Muestra un mensaje informativo con formato
inline void mostrarInfo(const std::string& mensaje, bool nuevaLinea = true) {
    setTextColor(ColorIndex::ENLACES);
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

/// @brief Imprime una línea divisoria
inline void imprimirLinea(char caracter = '-', int longitud = ANCHO_CONSOLA, 
                          int color = ColorIndex::BORDES) {
    setTextColor(color);
    std::cout << std::string(longitud, caracter) << std::endl;
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
// Aliases para mantener compatibilidad con Utils.h anterior
namespace Colors {
    constexpr int NORMAL = ColorIndex::TEXTO_PRINCIPAL;
    constexpr int FONDO = ColorIndex::FONDO_GENERAL;
    constexpr int SELECCION = ColorIndex::BOTON_PRIMARIO;
    constexpr int ERRORES = ColorIndex::ERROR_COLOR;
    constexpr int TEXTO_SECUNDARIO = ColorIndex::TEXTO_SECUNDARIO;
    constexpr int EXITO = ColorIndex::EXITO;
    constexpr int ADVERTENCIA = ColorIndex::ACENTO;
    constexpr int LINK = ColorIndex::ENLACES;
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
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    // Configurar color inicial (texto principal sobre fondo general)
    setConsoleColor(ColorIndex::TEXTO_PRINCIPAL, ColorIndex::FONDO_GENERAL);

    // Título de la aplicación
    SetConsoleTitle(L"Coursera Clone | Alpha 2.1");
}

#endif // COURSERACLONE_UTILS_SYSTEMUTILS_HPP