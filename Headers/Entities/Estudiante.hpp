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

/// @brief Clase que representa a un estudiante en el sistema de cursos
/// @details Hereda de Usuario y maneja inscripciones a cursos y especializaciones, así como boletas de pago.
class Estudiante : public Usuario
{
private:
    LinkedList<ComprobanteDePago> _boletas;
    Stack<Inscripcion> _cursosInscritos;
    Stack<Inscripcion> _especializacionesInscritas;

    // Cargar inscripciones de cursos en la pila
    void cargarInscripcionesCursos(const std::vector<int>& _offsetsCursos, LinkedList<Curso*>& _cursos);

    // Cargar inscripciones de especializaciones en la pila
    void cargarInscripcionesEspecializaciones(const std::vector<int>& _offsetsEspecializaciones, LinkedList<Especializacion*>& _listaEspecializaciones);

    // Verificar si ya está inscrito en un curso específico
    bool verificarInscripcionCurso(int _idCurso) const;

    // Verificar si ya está inscrito en una especialización específica
    bool verificarInscripcionEspecializacion(int _idEspecializacion) const;
public:
    // Constructor por defecto
    inline Estudiante();

    // Constructor con parámetros
    inline Estudiante(
        int _id,
        const std::string& _nombreCompleto,
        const std::string& _nickname,
        const std::string& _contrasena
    );

    /*
	NOTA IMPORTANTE: Para la inscripcion de cursos y especializaciones, se debe tener en cuenta que
    debemos usar la clase Inscripion que es la que se encarrgara de trabajar con la clase 
    Gestion de contenido para realizar las operaciones necesarias
	Para trabajar con archivos esta la clase FilesManager que se encargara de manejar los archivos
    */

    inline void reset();

    // Leer inscripción desde archivo binario en posición específica
    inline InscripcionBinaria leerInscripcionEn(int _posicion, const std::string& _rutaBinario);

	// Verificar si ya está inscrito en un curso
    inline std::vector<int> obtenerOffsetsInscripciones() const;

    // Cargar inscripciones usando algoritmos de ordenamiento
    inline void cargarInscripciones(LinkedList<Curso*>& _cursos, LinkedList<Especializacion*>& _listaEspecializaciones);

    void cargarDatos();

    // Getters
    inline const LinkedList<ComprobanteDePago>& getBoletas() const;
    inline const Stack<Inscripcion>& getInscripcionesCursos() const;
    inline const Stack<Inscripcion>& getInscripcionesEspecializaciones() const;

    // Métodos de visualización
    void verBoletas() const;
    void verCursosInscritos() const;

    // Métodos de inscripción
    bool inscribirseACurso(Curso* _curso);
    bool inscribirseAEspecializacion(Especializacion* _especializacion);
};

#endif // COURSERACLONE_ENTITIES_ESTUDIANTE_HPP