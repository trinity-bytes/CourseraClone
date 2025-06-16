#ifndef COURSERACLONE_SCREENS_REGISTROSCREEN_HPP
#define COURSERACLONE_SCREENS_REGISTROSCREEN_HPP

// Headers estándar
#include <string>

// Headers propios del proyecto
#include "../Utils/ScreenSystem.hpp"
#include "../Utils/SystemUtils.hpp"
#include "../Utils/UI_Ascii.hpp"

/// Pantalla de registro de usuarios
class RegistroScreen : public PantallaBase 
{
private:
	/// @brief Enumeración para los tipos de usuario
    static const int ELEMENTOS_INPUT = 4;
    static const int CANT_BOTONES = 3;
    
	/// @brief Variables para los elementos de entrada de datos
    std::string _nombre;
    std::string _email;
    std::string _password;
    std::string _confirmarPassword;
    TipoUsuario _tipoUsuario;

	/// @brief Variables para el manejo de la interfaz
    int _campoActual;
    int _campoAnterior;
    bool _error;
    std::string _mensajeError;
    bool _primeraRenderizacion;
    TipoUsuario _tipoUsuarioActual = TipoUsuario::DEFAULT;

    /// @brief Coordenadas para dibujar
    COORD _coordsElementosUserInput[ELEMENTOS_INPUT] = { 
        {11, 15}, {11, 20}, {11, 25}, {63, 25} 
    };
    COORD _coordsBotones[CANT_BOTONES] = { 
        {68, 20}, {90, 20}, {53, 29} 
    };

	/// @brief Textos de los botones y etiquetas
    const std::string _textosBotones[CANT_BOTONES] = { 
        " UN ESTUDIANTE ", 
        " UNA ORGANIZACION ", 
        " CREAR CUENTA "};
    const std::string _etiquetas[ELEMENTOS_INPUT] = { " ", " ", " ", " " };
    
	// ---- METODOS PRIVADOS ----

    inline void renderizarCampo(const std::string& valor, int indice, bool seleccionado);
    
    inline void renderizarBoton(const std::string& texto, int indice, bool seleccionado);

    inline void dibujarInterfazCompleta();

    inline void actualizarSeleccion();

    inline void guardarUsuario();

public:
    inline RegistroScreen();

	virtual ~RegistroScreen() = default;

    inline ResultadoPantalla ejecutar() override;
};

inline RegistroScreen::RegistroScreen() 
    : PantallaBase(), _campoActual(0), _campoAnterior(0), _error(false), 
      _mensajeError(""), _primeraRenderizacion(true) 
{}



#endif // COURSERACLONE_SCREENS_REGISTROSCREEN_HPP