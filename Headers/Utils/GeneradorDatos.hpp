#ifndef COURSErACLONE_HEADERS_UTILS_GENERADORDATOS_HPP
#define COURSErACLONE_HEADERS_UTILS_GENERADORDATOS_HPP

// Headers estándar
#include "../Controllers/SessionManager.hpp"
#include "ContentGenerator.hpp"
#include "../Utils/ValidationUtils.hpp"

class GeneradorDatos {

public:

    inline std::vector<std::string> generarNombres();
    inline std::vector<std::string> generarNombres(int n);
    inline void generarUsuarios(int n = 2);

};

inline std::vector<std::string> GeneradorDatos::generarNombres(int n) {
    // Backtracking
    std::vector<std::string> nombres;
    std::string current = "";

    auto backtrack = [&](auto&& self, int pos) -> void {
        if (pos == n) {
            nombres.push_back(current);
            return;
        }
        for (char c = 'a'; c <= 'z'; c++) {
            current[pos] = c;
            self(self, pos + 1);
        }
        };

    backtrack(backtrack, 0);
    return nombres;
}

inline std::vector<std::string> GeneradorDatos::generarNombres() {
	return generarNombres(2);
}

inline void GeneradorDatos::generarUsuarios(int n) {
    std::vector<std::string> nombres = generarNombres(n);

    for (std::string& nombre : nombres) {
		std::string email = nombre + "@gmail.com";
		std::string password = "123456";

        int longitud = n;

        for (int i = 1; i <= 2; i++) {
            bool emailNuevo = emailRepetido(email, i);
            if (!emailNuevo) {
                TipoUsuario tipoUsuarioActual = static_cast<TipoUsuario>(i);
                int cantidadAhora = FilesManager::getInstance().cantidadUsuarios(tipoUsuarioActual);
                Usuario nuevoUsuario(cantidadAhora, tipoUsuarioActual, nombre, email, password);
                nuevoUsuario.guardar();
            }

        }
    }

}

#endif // COURSERACLONE_HEADERS_UTILS_GENERADORDATOS_HPP
