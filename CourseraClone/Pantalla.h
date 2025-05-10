#pragma once

// Headers propios
#include "PantallaResultado.h"
#include "UI_Ascii.h"
#include "ExtendedFunctions.h"
#include "Utils.h"

// Headers de librerías
#include <string>
#include <vector>
#include <memory>

// Declaracion anticipada de la clase Controladora
class Controladora;

// Enumeración de pantallas disponibles
enum class Pantalla {
    NONE,
    LANDING_PAGE,
    LOGIN,
    REGISTRO,
    SOBRE_NOSOTROS,
    DASHBOARD_ESTUDIANTE,
    DASHBOARD_EMPRESA,
	PERFIL_ESTUDIANTE,
	PERFIL_EMPRESA,
	ACTUALIZAR_PERFIL,
	CURSOS_PUBLICADOS,
	ESPECIALIDADES_PUBLICADAS,
	CURSOS_INSCRITOS,
	ESPECIALIDADES_INSCRITAS,
    DETALLE_CURSO,
    DETALLE_ESPECIALIDAD
};

// Clase base para todas las pantallas
class PantallaBase {
public:
    virtual ~PantallaBase() = default;
    virtual ResultadoPantalla ejecutar() = 0;
}; 