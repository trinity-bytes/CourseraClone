// Descripcion: Clase que representa una empresa en el sistema

#ifndef COURSERACLONE_ENTITIES_EMPRESA_HPP
#define COURSERACLONE_ENTITIES_EMPRESA_HPP

// Librerías del sistema
#include <iostream>
#include <vector>

// Librerias propias del proyecto
#include "Usuario.hpp"
#include "../Controllers/ContentManager.hpp"

// Clase que representa una empresa usuaria del sistema
class Empresa : public Usuario
{
private:

public:
    // Constructores
    inline Empresa();

    inline Empresa(int offset) :
		Usuario(offset, TipoUsuario::EMPRESA) { }

    inline Empresa(
        int id,
        TipoUsuario tipoUsuario,
        const std::string& nombreCompleto,
        const std::string& username,
        const std::string& contrasenaHash
    );

    

};


#endif // COURSERACLONE_ENTITIES_EMPRESA_HPP
