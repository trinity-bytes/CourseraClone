#pragma once

#include <string>
using namespace std;
// =====================================================
// CONSTANTES GLOBALES DEL PROGRAMA
// Estas constantes son utilizadas en todo el programa
// y deben ser referenciadas desde aquí para mantener
// consistencia en toda la aplicación.
// =====================================================

// Dimensiones de la consola
// NOTA: Estas constantes son utilizadas por ExtendedFunctions.h
// y otras partes del programa. Si necesitas cambiar el tamaño
// de la consola, modifica estas constantes.
const int ANCHO_CONSOLA = 120;
const int ALTO_CONSOLA = 37;

// =====================================================
// ESTRUCTURAS DE DATOS COMUNES
// Estructuras utilizadas en múltiples partes del programa
// para mantener consistencia en el manejo de datos.
// =====================================================

// Estructura para elementos del menú
// Utilizada en LandingPage y otras pantallas que muestran
// elementos con título y descripción.
struct ElementoMenu {
	int id; // ID del elemento (opcional)
    string titulo;
    string descripcion;

    ElementoMenu() : titulo(""), descripcion("") {}

    ElementoMenu(const string& t, const string& d)
        : titulo(t), descripcion(d) {}
};

// =====================================================
// CONSTANTES DE COLOR
// Valores de color predefinidos para mantener consistencia
// visual en toda la aplicación.
// NOTA: Estos valores son utilizados por ExtendedFunctions.h
// para la configuración de la consola.
// =====================================================
namespace Colors {
    // Colores básicos
    const int NORMAL = 15;      // Blanco - Texto normal
    const int FONDO = 1;        // Azul oscuro - Fondo por defecto
    const int SELECCION = 4;    // Rojo - Elemento seleccionado
    const int ERRORES = 12;       // Rojo - Mensajes de error
    
    // Colores adicionales
    const int TEXTO_SECUNDARIO = 7;  // Gris oscuro
    const int EXITO = 2;             // Verde
    const int ADVERTENCIA = 14;      // Amarillo
    const int LINK = 11;             // Azul claro
} 