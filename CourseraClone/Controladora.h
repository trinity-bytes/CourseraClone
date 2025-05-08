#pragma once

// Headers propios
#include "Menu_State.h"
#include "Actividad.h"

// Forward declarations
class GestionadorUsuarios;
class GestionadorCursos;
class Usuario;
class LandingPageState;
class LoginState;

// Headers de la libreria estandar
#include <memory>
#include <vector>
#include <string>

class Controladora {
private:
	std::unique_ptr<MenuState> estadoActual;
	std::unique_ptr<GestionadorUsuarios> gestionadorUsuarios;
	std::unique_ptr<GestionadorCursos> gestionadorCursos;
	std::vector<Actividad> actividades;
	Usuario* usuarioActual;
	bool ejecutando;

	void cargarDatosArchivo();
	void cargarDatosInscripciones();

public:
	Controladora();
	~Controladora();

	// Navegación
	void cambiarEstado(std::unique_ptr<MenuState> nuevoEstado);

	// Autenticación
	bool iniciarSesion(const std::string& email, const std::string& password);
	bool registrarUsuario(const std::string& nombre, const std::string& email, 
						 const std::string& password, const std::string& tipo);
	void cerrarSesion();

	// Listados
	const std::vector<Actividad>& listarActividades() const { return actividades; }

	// Ejecución
	void run();

	// Getters
	Usuario* getUsuarioActual() const { return usuarioActual; }
	GestionadorUsuarios* getGestionadorUsuarios() const { return gestionadorUsuarios.get(); }
	GestionadorCursos* getGestionadorCursos() const { return gestionadorCursos.get(); }
};