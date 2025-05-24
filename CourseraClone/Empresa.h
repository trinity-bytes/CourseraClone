#pragma once
#include "Usuario.h"
#include "Curso.h"
#include "Especializacion.h"
#include <unordered_set>

class Empresa : public Usuario
{
private:
    LinkedList<Actividad> actividadesPropias;
    LinkedList<Especializacion> especializaciones;
    LinkedList<Curso> cursos;
public:
    void cargarDatos() {}

    Empresa() :
        Usuario() { }

    Empresa(int _id, string nombreCompleto, string _nickname, string _contrasena) : Usuario(_id, TipoUsuario::EMPRESA, nombreCompleto, _nickname, _contrasena) {
        cargarDatos();
    }

    void reset() {
        Usuario::reset();
        actividadesPropias.clear();
        especializaciones.clear();
        cursos.clear();
    }

    int crearCurso(Curso& nuevoCurso) {
        cursos.agregarAlFinal(nuevoCurso);
        cout << "Curso creado exitosamente." << endl;
    }

    int crearEspecializacion(Especializacion _nuevaEspecializacion) {
        especializaciones.agregarAlFinal(_nuevaEspecializacion);
    }

    void verProfesores() {
        unordered_set<string> profesores;

        // Iterar sobre la lista de cursos
        for (const auto& curso : cursos) {
            if (curso.getTitulo() != "") {
                profesores.insert(curso.getInstructor());
            }
        }

        // Mostrar los nombres de los profesores
        cout << "Profesores asociados a los cursos de la empresa:" << endl;
        for (const auto& profesor : profesores) {
            cout << "- " << profesor << endl;
        }
    }

    void eliminarCursoEspecializacion(Curso& curso) {
        if (curso.getTitulo() != "") {
            // Eliminar el curso de la especialización
            for (auto& especializacion : especializaciones) {
                if (especializacion.getTitulo() !=  "") {
                    especializacion.eliminarCurso(curso.getId());
                }
            }
            cout << "Curso eliminado exitosamente de la especialización." << endl;
        }
        else {
            cout << "Error: El curso proporcionado es nulo." << endl;
        }
    }

    void anadirCursoEspecializacion(int idEspecializacion, Curso curso) {
        // Validar que el curso no sea nulo
        if (curso.getTitulo() == "") {
            cout << "Error: El curso proporcionado es nulo." << endl;
            return;
        }

        // Buscar la especialización por su ID
        for (auto& especializacion : especializaciones) {
            if (especializacion.getTitulo() != "" && especializacion.getId() == idEspecializacion) {
                // Agregar el curso a la especialización
                especializacion.anadirCurso(curso);
                cout << "Curso añadido exitosamente a la especialización: " << especializacion.getTitulo() << endl;
                return;
            }
        }

        cout << "Error: No se encontró una especialización con el ID proporcionado." << endl;
    }
};
