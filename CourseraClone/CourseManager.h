#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Curso.h"
#include "Especializacion.h"

class CourseManager {
private:
    vector<unique_ptr<Curso>> cursos;
    vector<unique_ptr<Especializacion>> especializaciones;

public:
    CourseManager() = default;

    bool crearCurso(const string& titulo, const string& descripcion, int cantidadClases, const string& instructor) {
        // Verificar si ya existe un curso con el mismo título
        for (const auto& curso : cursos) {
            if (curso->getTitulo() == titulo) {
                return false;
            }
        }

        // Crear el nuevo curso
        auto nuevoCurso = make_unique<Curso>(titulo, descripcion, cantidadClases, instructor);
        cursos.push_back(move(nuevoCurso));
        return true;
    }

    bool crearEspecializacion(const string& titulo, const string& descripcion, int cantidadCursos) {
        // Verificar si ya existe una especialización con el mismo título
        for (const auto& especializacion : especializaciones) {
            if (especializacion->getTitulo() == titulo) {
                return false;
            }
        }

        // Crear la nueva especialización
        auto nuevaEspecializacion = make_unique<Especializacion>(titulo, descripcion, cantidadCursos);
        especializaciones.push_back(move(nuevaEspecializacion));
        return true;
    }

    const vector<unique_ptr<Curso>>& getCursos() const {
        return cursos;
    }

    const vector<unique_ptr<Especializacion>>& getEspecializaciones() const {
        return especializaciones;
    }
}; 