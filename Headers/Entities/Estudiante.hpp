// filepath: Headers/Entities/Estudiante.hpp
// Clase que representa a un estudiante en el sistema

#ifndef COURSERACLONE_ENTITIES_ESTUDIANTE_HPP
#define COURSERACLONE_ENTITIES_ESTUDIANTE_HPP

// Includes del sistema
#include <iostream>  // Para manejo de errores y mensajes
#include <vector>    // Para manejo de vectores dinámicos
#include <string>    // Para manejo de cadenas de texto

// Includes del proyecto
#include "Usuario.hpp"
#include "ComprobanteDePago.hpp"
#include "../DataStructures/LinkedList.hpp"
#include "../DataStructures/Stack.hpp"
#include "Inscripcion.hpp"
#include "Curso.hpp"
#include "Especializacion.hpp"

/// @brief Clase que representa a un estudiante en el sistema de cursos
/// @details Hereda de Usuario y maneja inscripciones a cursos y especializaciones, así como boletas de pago.
class Estudiante : public Usuario
{
private:
public:
    // Constructor por defecto
    inline Estudiante();

    inline Estudiante(int offset) :
		Usuario(offset, TipoUsuario::ESTUDIANTE) {
	}
    // Constructor con parámetros
    inline Estudiante(
        int _id,
        const std::string& _nombreCompleto,
        const std::string& _nickname,
        const std::string& _contrasena
    );


};

#endif // COURSERACLONE_ENTITIES_ESTUDIANTE_HPP