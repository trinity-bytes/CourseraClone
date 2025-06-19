// filepath: Headers/Utils/ValidationUtils.hpp
// Descripcion: Utilidades de validación y formateo de datos

#ifndef COURSERACLONE_UTILS_VALIDATIONUTILS_HPP
#define COURSERACLONE_UTILS_VALIDATIONUTILS_HPP

#include <string>
#include <cctype>
#include "../Controllers/FilesManager.hpp"

// UTILIDADES DE VALIDACIÓN

/// @brief Verifica si una cadena es un número válido
inline bool esNumeroValido(const std::string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isdigit(c)) return false;
    }
    return true;
}

/// @brief Verifica si un email tiene formato básico válido
inline bool esEmailValido(const std::string& email) {
    size_t at = email.find('@');
    size_t dot = email.find('.', at);
    return at != std::string::npos && dot != std::string::npos && 
           at > 0 && dot > at + 1 && dot < email.length() - 1;
}

/// @brief Limita una cadena a un tamaño máximo
inline std::string limitarTexto(const std::string& texto, size_t maxLength, 
                               const std::string& sufijo = "...") {
    if (texto.length() <= maxLength) return texto;
    return texto.substr(0, maxLength - sufijo.length()) + sufijo;
}

inline bool emailRepetido(std::string _email, int tipo) {
	for (char& c : _email) {
		c = std::tolower(c);
	}

	int pos = FilesManager::getInstance().buscarIndexUsuario(_email, tipo);
    if (pos == -1) return false;
    return true;
}

#endif // COURSERACLONE_UTILS_VALIDATIONUTILS_HPP
