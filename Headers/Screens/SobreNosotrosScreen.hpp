#ifndef COURSERACLONE_SCREENS_SOBRENOSOTROSSCREEN_HPP
#define COURSERACLONE_SCREENS_SOBRENOSOTROSSCREEN_HPP

#include <iostream>
#include <vector>
#include <string>
#include <conio.h>  // Para _getch()

#include "../Utils/ScreenSystem.hpp"
#include "../Utils/UI_Ascii.hpp"
#include "../Utils/SystemUtils.hpp"

class SobreNosotrosScreen : public PantallaBase
{
private:
	// ---- ATRIBUTOS PRIVADOS ----
	static const int CANT_BOTONES = 5;

	/// @brief Estado de la interfaz
	int _campoActual;
	int _campoAnterior;
	bool _primeraRenderizacion;
	/// @brief Configuración de interfaz - Coordenadas de los botones
	COORD _coordsBotones[CANT_BOTONES] = {
		{18, 16},  // Perfil GitHub Fabrizio
		{18, 20},  // Perfil GitHub Mauricio
		{18, 24},  // Perfil GitHub Jahat
		{31, 28},  // Repositorio GitHub del proyecto
		{67, 28}   // Carpeta de documentacion en el repositorio
	};
	/// @brief Textos de los botones
	std::vector<std::string> _textosBotones = {
		" Ver perfil de GitHub ",
		" Ver perfil de GitHub ",
		" Ver perfil de GitHub ",
		" IR AL REPOSITORIO DE GITHUB ",
		" IR A LA DOCUMENTACIÓN "
	};

	/// @brief URLs correspondientes a cada botón (para futuro uso)
	std::vector<std::string> _urlsBotones = {
		"https://github.com/Santi2007939",             // GitHub Fabrizio
		"https://github.com/mau-tz",                   // GitHub Mauricio
		"https://github.com/trinity-bytes",            // GitHub Jahat
		"https://github.com/CourseraClone/proyecto",   /// @TODO URL del repositorio
		"https://github.com/CourseraClone/proyecto"    /// @TODO URL de la crpeta de documentacion del repositorio
	};

	// ---- METODOS PRIVADOS ----

	/// @brief Limpia el estado interno de la pantalla
	inline void _limpiarEstado();

	/// @brief Renderiza un botón de la interfaz
	/// @param texto Texto del botón
	/// @param indice Índice del botón
	/// @param seleccionado Estado de selección del botón
	inline void _renderizarBoton(const std::string& texto, int indice, bool seleccionado);

	/// @brief Dibuja la interfaz completa de Sobre Nosotros
	inline void _dibujarInterfazCompleta();

	/// @brief Actualiza la selección visual de botones
	inline void _actualizarSeleccion();

	/// @brief Actualiza la renderización de todos los botones
	inline void _actualizarBotones();

	/// @brief Maneja la navegación con las teclas direccionales
	/// @param tecla Código de la tecla presionada
	inline void _manejarNavegacion(int tecla);

	/// @brief Procesa la selección de un botón (abrir URL)
	/// @param indice Índice del botón seleccionado
	inline void _procesarSeleccionBoton(int indice);

public:
	inline SobreNosotrosScreen();
	inline ~SobreNosotrosScreen() = default;

	inline ResultadoPantalla ejecutar() override;

};

// ---- IMPLEMENTACIONES INLINE ----

// Constructor
inline SobreNosotrosScreen::SobreNosotrosScreen() : PantallaBase(),
	_campoActual(0), _campoAnterior(0), _primeraRenderizacion(true) {}

// Limpia el estado interno
inline void SobreNosotrosScreen::_limpiarEstado()
{
	_campoActual = 0;
	_campoAnterior = 0;
	_primeraRenderizacion = true;
}

// Renderiza un botón con estado de selección
inline void SobreNosotrosScreen::_renderizarBoton(const std::string& texto, int indice, bool seleccionado)
{
	COORD pos = _coordsBotones[indice];
	gotoXY(pos.X, pos.Y);

	if (seleccionado) {
		setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::HOVER_ESTADO);
	}
	else {
		setConsoleColor(ColorIndex::LINK_COLOR, ColorIndex::FONDO_PRINCIPAL);
	}

	std::cout << texto;
	resetColor();
}

// Dibuja la interfaz completa
inline void SobreNosotrosScreen::_dibujarInterfazCompleta()
{
	system("cls");
	UI_AboutUs();

	// Renderizar todos los botones
	for (int i = 0; i < CANT_BOTONES; ++i) {
		_renderizarBoton(_textosBotones[i], i, _campoActual == i);
	}

	resetColor();
}

// Actualiza solo la selección de botones (sin redibujar todo)
inline void SobreNosotrosScreen::_actualizarSeleccion()
{
	// Solo actualizar si hay cambio de selección
	if (_campoAnterior != _campoActual)
	{
		// Actualizar botón anterior (deseleccionar)
		if (_campoAnterior >= 0 && _campoAnterior < CANT_BOTONES) {
			_renderizarBoton(_textosBotones[_campoAnterior], _campoAnterior, false);
		}

		// Actualizar botón actual (seleccionar)
		if (_campoActual >= 0 && _campoActual < CANT_BOTONES) {
			_renderizarBoton(_textosBotones[_campoActual], _campoActual, true);
		}

		_campoAnterior = _campoActual;
	}
}

// Actualiza todos los botones
inline void SobreNosotrosScreen::_actualizarBotones()
{
	for (int i = 0; i < CANT_BOTONES; ++i)
	{
		_renderizarBoton(_textosBotones[i], i, _campoActual == i);
	}
}

// Maneja la navegación vertical
inline void SobreNosotrosScreen::_manejarNavegacion(int tecla)
{
	switch (tecla) {
	case 72: // Flecha arriba
		_campoActual = (_campoActual > 0) ? _campoActual - 1 : CANT_BOTONES - 1;
		break;
	case 80: // Flecha abajo
		_campoActual = (_campoActual < CANT_BOTONES - 1) ? _campoActual + 1 : 0;
		break;
	}
}

// Procesa la selección de un botón (abre URL en navegador)
inline void SobreNosotrosScreen::_procesarSeleccionBoton(int indice)
{
	if (indice >= 0 && indice < CANT_BOTONES) {
		// Mostrar mensaje temporal de que se abrirá el enlace
		gotoXY(30, 25);
		setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
		std::cout << "Abriendo enlace en el navegador...";
		resetColor();

		// Comando para abrir URL en el navegador predeterminado de Windows
		std::string comando = "start " + _urlsBotones[indice];
		system(comando.c_str());

		// Pequeña pausa para mostrar el mensaje
		Sleep(1000);

		// Limpiar el mensaje
		gotoXY(30, 25);
		std::cout << "                                     ";
	}
}

// Método principal de ejecución
inline ResultadoPantalla SobreNosotrosScreen::ejecutar()
{
	ResultadoPantalla res;

	// Inicializar estado
	_limpiarEstado();

	// Bucle principal de la pantalla
	while (true)
	{
		if (_primeraRenderizacion)
		{
			_dibujarInterfazCompleta();
			_primeraRenderizacion = false;
		}
		else {
			_actualizarSeleccion();
		}

		int tecla = _getch();

		switch (tecla) {
		case 0:    // Teclas especiales - leer segundo byte
		case 224:  // Teclas especiales en algunos sistemas
		{
			int segundaTecla = _getch();
			_manejarNavegacion(segundaTecla);
		}
		break;

		case 72: // Flecha arriba (por si acaso)
		case 80: // Flecha abajo (por si acaso)
			_manejarNavegacion(tecla);
			break;

		case 27: // ESC - Regresar a Landing Page
			res.accion = AccionPantalla::IR_A_LANDING_PAGE;
			return res;

		case 13: // Enter - Procesar selección
			_procesarSeleccionBoton(_campoActual);
			break;

		default:
			// Ignorar otras teclas
			break;
		}
	}
}

#endif // !COURSERACLONE_SCREENS_SOBRENOSOTROSSCREEN_HPP
