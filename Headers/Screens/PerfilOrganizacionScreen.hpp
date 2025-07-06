#ifndef COURSERACLONE_SCREENS_PERFILORGANIZACIONSCREEN_HPP
#define COURSERACLONE_SCREENS_PERFILORGANIZACIONSCREEN_HPP

#pragma once

// Headers estándar
#include <string>
#include <conio.h>

// Headers de consola
#include "../Utils/SystemUtils.hpp"
#include "../Utils/ScreenSystem.hpp"
#include "../Utils/UI_Ascii.hpp"
#include "../Controllers/SessionManager.hpp"

/// Pantalla para mostrar perfil de organización
class PerfilOrganizacionScreen : public PantallaBase
{
private:
    /// @brief Constantes para secciones
    static const int SECCION_BOTONES = 0;
    static const int TOTAL_SECCIONES = 1;

    /// @brief Constantes para botones
    static const int BOTON_EDITAR_PERFIL = 0;
    static const int TOTAL_BOTONES = 1;    // Datos de la organización
    int _idOrganizacion;
    std::string _nombreOrganizacion;
    std::string _correoOrganizacion;
    std::string _fechaCreacionOrganizacion;

    
    /// @brief Estado actual
    bool _primeraRenderizacion;
    bool _botonSeleccionado;

    /// @brief Elementos de botones
    std::vector<std::string> _elementosHeader = {
        " EDITAR PERFIL "
    };    /// @brief Coordenadas para botones
    COORD coordsBotones[TOTAL_BOTONES] = {
        {84, 10}  // EDITAR PERFIL
    };

    /// @brief Coordenadas para datos del perfil
    COORD coordsNombre = {36, 18};
    COORD coordsCorreo = {30, 22};
    COORD coordsFechaCreacion = {47, 26};

    /// @brief Coordenada para ID
    COORD coordID = { 30,14 };
    
    // ---- MÉTODOS PRIVADOS ----
    
    /// @brief Métodos de inicialización
    inline void _limpiarEstado();
    inline void _cargarDatosDummy();

    /// @brief Métodos de renderizado
    inline void dibujarInterfazCompleta();
    inline void renderizarDatosPerfil();
    inline void renderizarBoton(bool seleccionado);

    /// @brief Métodos de navegación
    inline ResultadoPantalla _procesarSeleccion();

public:
    inline PerfilOrganizacionScreen();

    inline ~PerfilOrganizacionScreen() = default;

    inline ResultadoPantalla ejecutar() override;
};

// --- IMPLEMENTACIONES INLINE ---

// Constructor
inline PerfilOrganizacionScreen::PerfilOrganizacionScreen() : PantallaBase(),
    _idOrganizacion(1), 
    _nombreOrganizacion("UPC - Universidad Peruana de Ciencias Aplicadas"),
    _correoOrganizacion("admin@upc.edu.pe"),
    _fechaCreacionOrganizacion("10 de Enero, 2020"),
    _primeraRenderizacion(true), _botonSeleccionado(true)
{
    _cargarDatosDummy();
}

// Limpiar estado
inline void PerfilOrganizacionScreen::_limpiarEstado()
{
    _primeraRenderizacion = true;
    _botonSeleccionado = true; // El único botón siempre está seleccionado por defecto
}

// Cargar datos de ejemplo
inline void PerfilOrganizacionScreen::_cargarDatosDummy()
{
    SessionManager& sm = SessionManager::getInstance();
    bool sesionIniciada = sm.isLoggedIn();
    if (sesionIniciada) {
        _idOrganizacion = sm.getCurrentUser().getId();
        _correoOrganizacion = sm.getCurrentUser().getUsername();
        _nombreOrganizacion = sm.getCurrentUser().getNombreCompleto();
        _fechaCreacionOrganizacion = sm.getCurrentUser().getFechaRegistro();
    }
    // Los datos ya se cargan en el constructor
    // Este método está disponible para futuras cargas desde archivos
}

// Dibujar interfaz completa
inline void PerfilOrganizacionScreen::dibujarInterfazCompleta()
{
    system("cls");
    UI_OrganizationProfile();

    renderizarDatosPerfil();
    renderizarBoton(_botonSeleccionado);

    resetColor();
}

// Renderizar datos del perfil
inline void PerfilOrganizacionScreen::renderizarDatosPerfil()
{
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    
    gotoXY(coordID.X, coordID.Y);
	std::cout << _idOrganizacion;

    // Nombre de la organización
    gotoXY(coordsNombre.X, coordsNombre.Y);
    std::cout << _nombreOrganizacion;
    
    // Correo
    gotoXY(coordsCorreo.X, coordsCorreo.Y);
    std::cout << _correoOrganizacion;
    // Fecha de creación
    gotoXY(coordsFechaCreacion.X, coordsFechaCreacion.Y);
    std::cout << _fechaCreacionOrganizacion;
    
    resetColor();
}

// Renderizar botón
inline void PerfilOrganizacionScreen::renderizarBoton(bool seleccionado)
{
    gotoXY(coordsBotones[0].X, coordsBotones[0].Y);
    
    if (seleccionado) {
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
    } else {
        setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    }
    
    std::cout << _elementosHeader[0];
    resetColor();
}

// Procesar selección
inline ResultadoPantalla PerfilOrganizacionScreen::_procesarSeleccion()
{
    ResultadoPantalla res;
    res.accion = AccionPantalla::IR_A_EDITAR_PERFIL;
    return res;
}

// Método principal de ejecución
inline ResultadoPantalla PerfilOrganizacionScreen::ejecutar()
{
    ResultadoPantalla res;
    _limpiarEstado();

    while (true) {
        if (_primeraRenderizacion) {
            dibujarInterfazCompleta();
            _primeraRenderizacion = false;
        }

        int tecla = _getch();

        switch (tecla) {
        case 27: // ESC - Regresar al dashboard
            res.accion = AccionPantalla::IR_A_DASHBOARD_ORGANIZACION;
            return res;

        case 13: // Enter - Procesar selección (ir a editar perfil)
            res = _procesarSeleccion();
            return res;

        default:
            // Ignorar otras teclas ya que solo hay un botón
            break;
        }
    }
}

#endif // COURSERACLONE_SCREENS_PERFILORGANIZACIONSCREEN_HPP
