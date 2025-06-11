// filepath: Headers/Entities/Estudiante.hpp
// Clase que representa a un estudiante en el sistema

#ifndef COURSERACLONE_ENTITIES_ESTUDIANTE_HPP
#define COURSERACLONE_ENTITIES_ESTUDIANTE_HPP

// Includes del sistema
#include <fstream>   // Para manejo de archivos
#include <iostream>  // Para manejo de errores y mensajes
#include <vector>    // Para manejo de vectores dinámicos
#include <string>    // Para manejo de cadenas de texto
#include <stdexcept> // Para manejo de excepciones

// Includes del proyecto
#include "Usuario.hpp"
#include "Boleta.hpp"
#include "Inscripcion.hpp"
#include "Especializacion.h"
#include "Venta.hpp"
#include "../DataStructures/LinkedList.h"
#include "../DataStructures/Stack.h"
#include "../DataStructures/algoritmosOrdenamiento.h"
#include "../Persistence/InscripcionTypes.hpp"
#include "../Persistence/BoletaTypes.hpp"

// Constantes para rutas de archivos
const std::string RUTA_BOLETAS = "Resources/Data/boletas.dat";
const std::string RUTA_INSCRIPCIONES = "Resources/Data/inscripciones.dat";
const std::string RUTA_INDICE_INSCRIPCIONES = "Resources/Data/indices/inscripciones.dat";

/// @brief Clase que representa a un estudiante en el sistema de cursos
/// @details Hereda de Usuario y maneja inscripciones a cursos y especializaciones, así como boletas de pago.
class Estudiante : public Usuario
{
private:
    LinkedList<Boleta> _boletas;
    Stack<Inscripcion> _cursosInscritos;
    Stack<Inscripcion> _especializacionesInscritas;

public:
    // Constructor por defecto
    Estudiante() : Usuario() {}

    // Constructor con parámetros
    Estudiante(
        int _id, 
        const std::string& _nombreCompleto,
        const std::string& _nickname, 
        const std::string& _contrasena
    ) : Usuario(_id, TipoUsuario::ESTUDIANTE, _nombreCompleto, _nickname, _contrasena)
    {
        cargarDatos();
    }

    void reset()
    {
        Usuario::reset();
        _boletas.clear();        
        _cursosInscritos.clear();
        _especializacionesInscritas.clear();
    }

    // Leer inscripción desde archivo binario en posición específica
    InscripcionBinaria leerInscripcionEn(int _posicion, const std::string& _rutaBinario) const
    {
        std::ifstream archivo(_rutaBinario, std::ios::binary | std::ios::in);
        if (!archivo.is_open())
        {
            throw std::runtime_error("No se pudo abrir binario inscripciones");
        }
        
        archivo.seekg(_posicion * sizeof(InscripcionBinaria), std::ios::beg);
        InscripcionBinaria registro;
        archivo.read(reinterpret_cast<char*>(&registro), sizeof(registro));        return registro;
    }

    std::vector<int> obtenerOffsetsInscripciones() const
    {
        std::ifstream archivoIndice(RUTA_INDICE_INSCRIPCIONES, std::ios::binary);
        if (!archivoIndice.is_open())
        {
            throw std::runtime_error("No se pudo abrir el índice de inscripciones");
        }

        archivoIndice.seekg(0, std::ios::end);
        const int cantidad = static_cast<int>(archivoIndice.tellg() / sizeof(InscripcionIndex));
        if (cantidad <= 0) return {};
        archivoIndice.seekg(0, std::ios::beg);

        // Predicado para búsqueda binaria
        auto predicadoBusqueda = [&](int _posicion) -> bool
        {
            InscripcionIndex temporal;
            archivoIndice.seekg(_posicion * sizeof(temporal), std::ios::beg);
            archivoIndice.read(reinterpret_cast<char*>(&temporal), sizeof(temporal));
            archivoIndice.clear();
            return temporal.idUsuario >= this->getId();
        };

        int inicio = busquedaBinaria(0, cantidad - 1, predicadoBusqueda);
        std::vector<int> offsets;
        offsets.reserve(cantidad - inicio);

        for (int i = inicio; i < cantidad; ++i)
        {
            InscripcionIndex temporal;
            archivoIndice.seekg(i * sizeof(temporal), std::ios::beg);
            archivoIndice.read(reinterpret_cast<char*>(&temporal), sizeof(temporal));
            if (temporal.idUsuario != this->getId()) break;
            offsets.push_back(temporal.offset);
        }        return offsets;
    }

    // Cargar inscripciones usando algoritmos de ordenamiento
    void cargarInscripciones(
        LinkedList<Curso*>& _cursos,
        LinkedList<Especializacion*>& _listaEspecializaciones
    )
    {
        const std::vector<int> offsets = obtenerOffsetsInscripciones();
        if (offsets.empty()) return;

        std::vector<int> offsetsCursos;
        std::vector<int> offsetsEspecializaciones;

        // Separar offsets por tipo de actividad
        for (int offset : offsets)
        {
            const InscripcionBinaria registro = leerInscripcionEn(offset, RUTA_INSCRIPCIONES);
            if (registro.tipoActividad == 1)
            {
                offsetsCursos.push_back(offset);
            }
            else
            {
                offsetsEspecializaciones.push_back(offset);
            }
        }

        // Ordenar usando algoritmos diferentes para demostrar su uso
        if (offsetsCursos.size() > 1)
        {
            mergeSort(offsetsCursos, 0, int(offsetsCursos.size()) - 1);
        }
        if (offsetsEspecializaciones.size() > 1)        {
            shellSort(offsetsEspecializaciones);
        }

        cargarInscripcionesCursos(offsetsCursos, _cursos);
        cargarInscripcionesEspecializaciones(offsetsEspecializaciones, _listaEspecializaciones);
    }

private:
    // Cargar inscripciones de cursos en la pila
    void cargarInscripcionesCursos(const std::vector<int>& _offsetsCursos, LinkedList<Curso*>& _cursos)
    {
        for (int offset : _offsetsCursos)
        {
            const InscripcionBinaria registro = leerInscripcionEn(offset, RUTA_INSCRIPCIONES);
            const int posicion = _cursos.buscarPorClave(registro.idActividad, [](Curso* curso) { return curso->getId(); });
            if (posicion == -1)
            {
                throw std::runtime_error("Inscripción de curso no encontrada");
            }
            Curso* actividad = _cursos.get(posicion);
            _cursosInscritos.push(Inscripcion(registro, actividad, offset));
        }
    }

    // Cargar inscripciones de especializaciones en la pila
    void cargarInscripcionesEspecializaciones(const std::vector<int>& _offsetsEspecializaciones, LinkedList<Especializacion*>& _listaEspecializaciones)
    {
        for (int offset : _offsetsEspecializaciones)
        {
            const InscripcionBinaria registro = leerInscripcionEn(offset, RUTA_INSCRIPCIONES);
            const int posicion = _listaEspecializaciones.buscarPorClave(registro.idActividad, [](Especializacion* especializacion) { return especializacion->getId(); });
            if (posicion == -1)
            {
                throw std::runtime_error("Inscripción de especialización no encontrada");
            }
            Especializacion* actividad = _listaEspecializaciones.get(posicion);
            _especializacionesInscritas.push(Inscripcion(registro, actividad, offset));
        }    }

public:
    void cargarDatos()
    {
        std::ifstream archivo(RUTA_BOLETAS, std::ios::binary);
        if (!archivo.is_open())
        {
            std::cerr << "No se pudo abrir el archivo de boletas" << std::endl;
            return;
        }

        BoletaBinaria boletaBinaria;
        int indice = 0;
        while (archivo.read(reinterpret_cast<char*>(&boletaBinaria), sizeof(boletaBinaria)))
        {
            if (boletaBinaria.idEstudiante == this->getId())
            {
                _boletas.agregarAlFinal(Boleta(
                    indice++, boletaBinaria.idEstudiante,
                    boletaBinaria.idActividad, boletaBinaria.fecha,
                    boletaBinaria.precio));
            }        }
    }

    // Getters
    const LinkedList<Boleta>& getBoletas() const { return _boletas; }
    const Stack<Inscripcion>& getInscripcionesCursos() const { return _cursosInscritos; }
    const Stack<Inscripcion>& getInscripcionesEspecializaciones() const { return _especializacionesInscritas; }

    // Métodos de visualización
    void verBoletas() const
    {
        for (int i = 0; i < _boletas.getTamano(); ++i)
        {
            const Boleta& boleta = _boletas.get(i);
            boleta.mostrar();
        }
    }

    void verCursosInscritos() const
    {
        for (int i = 0; i < _cursosInscritos.getTamano(); ++i)
        {
            const Inscripcion& inscripcion = _cursosInscritos.get(i);
            inscripcion.mostrar();        }
    }

    // Métodos de inscripción
    bool inscribirseACurso(Curso* _curso)
    {
        if (!_curso)
        {
            std::cerr << "Error: Curso inválido" << std::endl;
            return false;
        }

        if (yaEstaInscritoEnCurso(_curso->getId()))
        {
            std::cerr << "Error: Ya estás inscrito en este curso" << std::endl;
            return false;
        }

        Inscripcion nuevaInscripcion(this->getId(), _curso);
        nuevaInscripcion.guardar();
        nuevaInscripcion.marcarComoPagada(_boletas);
        _cursosInscritos.push(nuevaInscripcion);
        _curso->aumentarAlumno(1);
        return true;
    }

    bool inscribirseAEspecializacion(Especializacion* _especializacion)
    {
        if (!_especializacion)
        {
            std::cerr << "Error: Especialización inválida" << std::endl;
            return false;
        }

        if (yaEstaInscritoEnEspecializacion(_especializacion->getId()))
        {
            std::cerr << "Error: Ya estás inscrito en esta especialización" << std::endl;
            return false;
        }

        Inscripcion nuevaInscripcion(this->getId(), _especializacion);
        nuevaInscripcion.guardar();
        nuevaInscripcion.marcarComoPagada(_boletas);
        _especializacionesInscritas.push(nuevaInscripcion);
        _especializacion->aumentarAlumno(1);
        return true;
    }

private:
    // Verificar si ya está inscrito en un curso específico
    bool yaEstaInscritoEnCurso(int _idCurso) const
    {
        for (int i = 0; i < _cursosInscritos.getTamano(); ++i)
        {
            if (_cursosInscritos.get(i).getIdActividad() == _idCurso)
            {
                return true;
            }
        }
        return false;
    }

    // Verificar si ya está inscrito en una especialización específica
    bool yaEstaInscritoEnEspecializacion(int _idEspecializacion) const
    {
        for (int i = 0; i < _especializacionesInscritas.getTamano(); ++i)
        {
            if (_especializacionesInscritas.get(i).getIdActividad() == _idEspecializacion)
            {
                return true;
            }
        }
        return false;
    }
};

#endif // COURSERACLONE_ENTITIES_ESTUDIANTE_HPP