#ifndef COURSERACLONE_UTILS_LAMBDA_HPP
#define COURSERACLONE_UTILS_LAMBDA_HPP


#pragma once
#include <functional>
#include <fstream>
#include "../Types/InscripcionTypes.hpp"

inline std::function<bool(int)>
crearPredicadoBusqueda(std::fstream& archivo, int idUsuario) {
    return [&archivo, idUsuario](int pos) {
        InscripcionIndex tmp;
        archivo.seekg(pos * sizeof(InscripcionIndex), std::ios::beg);
        archivo.read(reinterpret_cast<char*>(&tmp), sizeof(tmp));
        return idUsuario <= tmp.idUsuario;
        };
}

#endif //  COURSERACLONE_UTILS_LAMBDA_HPP