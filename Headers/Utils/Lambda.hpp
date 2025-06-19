#ifndef COURSERACLONE_UTILS_LAMBDA_HPP
#define COURSERACLONE_UTILS_LAMBDA_HPP


#pragma once
#include <functional>
#include <fstream>
#include "../Types/InscripcionTypes.hpp"
#include "../Types/UsuarioTypes.hpp"

inline std::function<bool(int)>
crearPredicadoBusqueda(std::fstream& archivo, int idUsuario) {
    return [&archivo, idUsuario](int pos) {
        InscripcionIndex tmp;
        archivo.seekg(pos * sizeof(InscripcionIndex), std::ios::beg);
        archivo.read(reinterpret_cast<char*>(&tmp), sizeof(tmp));
        return idUsuario <= tmp.idUsuario;
        };
}

inline std::function<bool(int)>
crearPredicadoBusquedaUsuario(std::ifstream& archivo, std::string username) {
    return [&archivo, username](int pos) {
        UsuarioIndex tmp;
		archivo.seekg(pos * sizeof(UsuarioIndex), std::ios::beg);
		archivo.read(reinterpret_cast<char*>(&tmp), sizeof(tmp));
        return std::strncmp(username.c_str(), tmp.nombreDeUsuario, MAX_FIELD_LEN) <= 0;
        };
}

inline std::function<bool(int)>
crearPredicadoBusquedaUsuarioLecEsc(std::fstream& archivo, std::string username) {
    return [&archivo, username](int pos) {
        UsuarioIndex tmp;
        archivo.seekg(pos * sizeof(UsuarioIndex), std::ios::beg);
        archivo.read(reinterpret_cast<char*>(&tmp), sizeof(tmp));
        return std::strncmp(username.c_str(), tmp.nombreDeUsuario, MAX_FIELD_LEN) <= 0;
        };
}

#endif //  COURSERACLONE_UTILS_LAMBDA_HPP