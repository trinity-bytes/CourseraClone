#pragma once
#include <string>
#include "Usuario.h"

enum class AccionPantalla {
    NINGUNA,
    IR_A_LOGIN,
    IR_A_REGISTRO,
    IR_A_SOBRE_NOSOTROS,
    IR_A_DASHBOARD_ESTUDIANTE,
    IR_A_DASHBOARD_ORGANIZACION,
    IR_A_LANDING_PAGE,
	IR_A_PERFIL_ESTUDIANTE,
	IR_A_PERFIL_ORGANIZACION,
	IR_A_EDITAR_PERFIL,
	IR_A_MOSTRAR_CURSO,
    IR_A_MOSTRAR_ESPECIALIZACION,
	IR_A_EXPLORAR_CURSOS_Y_ESPECIALIDADES,
	IR_A_GESTIONAR_INSCRIPCIONES,
    IR_A_VER_BOLETAS,
    SALIR
};

struct ResultadoPantalla {
    AccionPantalla accion = AccionPantalla::NINGUNA;
    string email;
    string password;
    TipoUsuario tipoUsuario;
    int idCursoSeleccionado;
	AccionPantalla accionAnterior;
}; 