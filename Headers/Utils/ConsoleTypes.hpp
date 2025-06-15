// filepath: Headers/Utils/ConsoleTypes.hpp
// Descripcion: Estructuras y tipos comunes para el sistema de consola

#ifndef COURSERACLONE_UTILS_CONSOLETYPES_HPP
#define COURSERACLONE_UTILS_CONSOLETYPES_HPP

#include <string>

// CONSTANTES GLOBALES DEL PROGRAMA

// Dimensiones de la consola
constexpr int ANCHO_CONSOLA = 120;
constexpr int ALTO_CONSOLA = 33;

// Constantes de archivos y datos
constexpr int MAX_ESTUDIANTES_POR_CURSO = 100;
constexpr char SEPARADOR_CSV = ',';

// ESTRUCTURAS DE DATOS COMUNES

/// @brief Estructura para coordenadas en la consola
struct Posicion {
    int x, y;
    
    constexpr Posicion(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    
    Posicion operator+(const Posicion& other) const {
        return Posicion(x + other.x, y + other.y);
    }
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

#endif // COURSERACLONE_UTILS_CONSOLETYPES_HPP
