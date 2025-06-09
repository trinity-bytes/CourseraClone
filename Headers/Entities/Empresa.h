// Descripcion: Clase que representa una empresa en el sistema

#pragma once

// Librerías estándar
#include <unordered_set>
#include <stdexcept>

// Librerias del proyecto
#include "Usuario.hpp"
#include "Curso.h"
#include "Especializacion.h"

// Clase que representa una empresa usuaria del sistema
class Empresa : public Usuario
{
private:
    // Atributos privados
    LinkedList<Actividad> _actividadesPropias;
    LinkedList<Especializacion> _especializaciones;
    LinkedList<Curso> _cursos;

    // Métodos privados de validación
    bool validarCurso(const Curso& _curso) const;
    bool validarEspecializacion(const Especializacion& _especializacion) const;

public:
    // Constructores
    Empresa();
    Empresa(int _id, const string& _nombreCompleto, const string& _nickname, const string& _contrasena);

    // Métodos de gestión de datos
    void cargarDatos();
    void reset();

    // Métodos de gestión de cursos
    bool crearCurso(const Curso& _nuevoCurso);
    bool eliminarCurso(int _idCurso);
    LinkedList<Curso>& getCursos() { return _cursos; }
    const LinkedList<Curso>& getCursos() const { return _cursos; }

    // Métodos de gestión de especializaciones
    bool crearEspecializacion(const Especializacion& _nuevaEspecializacion);
    bool eliminarEspecializacion(int _idEspecializacion);
    LinkedList<Especializacion>& getEspecializaciones() { return _especializaciones; }
    const LinkedList<Especializacion>& getEspecializaciones() const { return _especializaciones; }

    // Métodos de gestión de cursos en especializaciones
    bool anadirCursoAEspecializacion(int _idEspecializacion, Curso& _curso);
    bool eliminarCursoDeEspecializacion(int _idEspecializacion, int _idCurso);

    // Métodos de consulta
    void mostrarProfesores() const;
    int obtenerCantidadCursos() const;
    int obtenerCantidadEspecializaciones() const;
    bool tieneCurso(int _idCurso) const;
    bool tieneEspecializacion(int _idEspecializacion) const;
};

// --- IMPLEMENTACIONES ---

inline Empresa::Empresa() : Usuario()
{
    cargarDatos();
}

inline Empresa::Empresa(int _id, const string& _nombreCompleto, const string& _nickname, const string& _contrasena)
    : Usuario(_id, TipoUsuario::EMPRESA, _nombreCompleto, _nickname, _contrasena)
{
    cargarDatos();
}

inline void Empresa::cargarDatos()
{
    // TODO: Implementar carga de datos desde archivo
}

inline void Empresa::reset()
{
    Usuario::reset();
    _actividadesPropias.clear();
    _especializaciones.clear();
    _cursos.clear();
}

inline bool Empresa::validarCurso(const Curso& _curso) const
{
    return !_curso.getTitulo().empty() && _curso.getId() > 0;
}

inline bool Empresa::validarEspecializacion(const Especializacion& _especializacion) const
{
    return !_especializacion.getTitulo().empty() && _especializacion.getId() > 0;
}

inline bool Empresa::crearCurso(const Curso& _nuevoCurso)
{
    if (!validarCurso(_nuevoCurso))
    {
        throw invalid_argument("Error: El curso proporcionado no es válido.");
    }

    // Verificar que no existe un curso con el mismo ID
    if (tieneCurso(_nuevoCurso.getId()))
    {
        throw invalid_argument("Error: Ya existe un curso con ese ID.");
    }

    _cursos.agregarAlFinal(_nuevoCurso);
    return true;
}

inline bool Empresa::eliminarCurso(int _idCurso)
{
    if (_idCurso <= 0)
    {
        throw invalid_argument("Error: ID de curso inválido.");
    }

    // TODO: Implementar eliminación por ID en LinkedList
    // Por ahora retornamos false indicando que no se pudo eliminar
    return false;
}

inline bool Empresa::crearEspecializacion(const Especializacion& _nuevaEspecializacion)
{
    if (!validarEspecializacion(_nuevaEspecializacion))
    {
        throw invalid_argument("Error: La especialización proporcionada no es válida.");
    }

    // Verificar que no existe una especialización con el mismo ID
    if (tieneEspecializacion(_nuevaEspecializacion.getId()))
    {
        throw invalid_argument("Error: Ya existe una especialización con ese ID.");
    }

    _especializaciones.agregarAlFinal(_nuevaEspecializacion);
    return true;
}

inline bool Empresa::eliminarEspecializacion(int _idEspecializacion)
{
    if (_idEspecializacion <= 0)
    {
        throw invalid_argument("Error: ID de especialización inválido.");
    }

    // TODO: Implementar eliminación por ID en LinkedList
    return false;
}

inline void Empresa::mostrarProfesores() const
{
    unordered_set<string> profesores;

    // Recopilar profesores únicos de todos los cursos
    for (const auto& curso : _cursos)
    {
        if (validarCurso(curso))
        {
            string instructor = curso.getInstructor();
            if (!instructor.empty())
            {
                profesores.insert(instructor);
            }
        }
    }

    // Mostrar resultados
    if (profesores.empty())
    {
        cout << "No hay profesores registrados para esta empresa." << endl;
    }
    else
    {
        cout << "Profesores asociados a los cursos de la empresa:" << endl;
        for (const auto& profesor : profesores)
        {
            cout << "- " << profesor << endl;
        }
    }
}

inline bool Empresa::anadirCursoAEspecializacion(int _idEspecializacion, Curso& _curso)
{
    if (!validarCurso(_curso))
    {
        throw invalid_argument("Error: El curso proporcionado no es válido.");
    }

    if (_idEspecializacion <= 0)
    {
        throw invalid_argument("Error: ID de especialización inválido.");
    }

    // Buscar la especialización por ID
    for (auto& especializacion : _especializaciones)
    {
        if (validarEspecializacion(especializacion) && especializacion.getId() == _idEspecializacion)
        {
            especializacion.anadirCurso(_curso);
            return true;
        }
    }

    throw invalid_argument("Error: No se encontró una especialización con el ID proporcionado.");
}

inline bool Empresa::eliminarCursoDeEspecializacion(int _idEspecializacion, int _idCurso)
{
    if (_idEspecializacion <= 0 || _idCurso <= 0)
    {
        throw invalid_argument("Error: IDs inválidos proporcionados.");
    }

    // Buscar la especialización por ID
    for (auto& especializacion : _especializaciones)
    {
        if (validarEspecializacion(especializacion) && especializacion.getId() == _idEspecializacion)
        {
            return especializacion.eliminarCurso(_idCurso);
        }
    }

    throw invalid_argument("Error: No se encontró una especialización con el ID proporcionado.");
}

inline int Empresa::obtenerCantidadCursos() const
{
    return _cursos.getTamano();
}

inline int Empresa::obtenerCantidadEspecializaciones() const
{
    return _especializaciones.getTamano();
}

inline bool Empresa::tieneCurso(int _idCurso) const
{
    if (_idCurso <= 0) return false;

    for (const auto& curso : _cursos)
    {
        if (curso.getId() == _idCurso)
        {
            return true;
        }
    }
    return false;
}

inline bool Empresa::tieneEspecializacion(int _idEspecializacion) const
{
    if (_idEspecializacion <= 0) return false;

    for (const auto& especializacion : _especializaciones)
    {
        if (especializacion.getId() == _idEspecializacion)
        {
            return true;
        }
    }
    return false;
}
