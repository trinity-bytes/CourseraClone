#pragma once
#include <string>

enum class AccionPantalla {
    NINGUNA,
    IR_A_LOGIN,
    IR_A_REGISTRO,
    IR_A_SOBRE_NOSOTROS,
    IR_A_DASHBOARD_ESTUDIANTE,
    IR_A_LANDING_PAGE,
    SALIR
};

struct ResultadoPantalla {
    AccionPantalla accion = AccionPantalla::NINGUNA;
    std::string email;
    std::string password;
    // Puedes agregar más campos según lo que necesites transferir
}; 