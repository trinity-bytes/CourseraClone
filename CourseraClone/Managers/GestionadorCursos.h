#pragma once
#include "../Curso.h"
#include "../LinkedList.h"
#include "../Especializacion.h"
#include <fstream>
#include <string>
#include <vector>

class GestionadorCursos {
private:
    LinkedList<Curso*> cursos;
    LinkedList<Especializacion*> especializaciones;
    const string RUTA_CURSOS = "Resources/Data/cursos.txt";
    const string RUTA_ESPECIALIZACIONES = "Resources/Data/especializaciones.txt";

public:
    GestionadorCursos() {
        cargarCursos();
        cargarEspecializaciones();
    }

    ~GestionadorCursos() {
        // Liberar memoria
        for (auto curso : cursos) {
            delete curso;
        }
        for (auto especializacion : especializaciones) {
            delete especializacion;
        }
    }

    bool crearCurso(int idEmpresa, const string& titulo, const string& nombreEmpresa,
        int cantidadClases, const string& instructor, const string& descripcion) {
        Curso* nuevoCurso = new Curso(
            cursos.getSize() + 1, // ID autoincremental
            idEmpresa,
            titulo,
            nombreEmpresa,
            cantidadClases,
            instructor,
            descripcion
        );

        cursos.agregarAlFinal(nuevoCurso);
        guardarCursos();
        return true;
    }

    bool crearEspecializacion(int idEmpresa, const string& nombreEmpresa,
        const string& titulo, int cantidadCursos, const string& descripcion) {
        Especializacion* nuevaEspecializacion = new Especializacion(
            especializaciones.getSize() + 1, // ID autoincremental
            idEmpresa,
            nombreEmpresa,
            titulo,
            cantidadCursos,
            descripcion
        );

        especializaciones.agregarAlFinal(nuevaEspecializacion);
        guardarEspecializaciones();
        return true;
    }

    vector<Curso*> buscarCursos(const string& criterio) {
        vector<Curso*> resultados;
        for (auto curso : cursos) {
            if (curso->getTitulo().find(criterio) != string::npos ||
                curso->getDescripcion().find(criterio) != string::npos) {
                resultados.push_back(curso);
            }
        }
        return resultados;
    }

    vector<Especializacion*> buscarEspecializaciones(const string& criterio) {
        vector<Especializacion*> resultados;
        for (auto especializacion : especializaciones) {
            if (especializacion->getTitulo().find(criterio) != string::npos ||
                especializacion->getDescripcion().find(criterio) != string::npos) {
                resultados.push_back(especializacion);
            }
        }
        return resultados;
    }

    Curso* obtenerCurso(int id) {
        for (auto curso : cursos) {
            if (curso->getId() == id) {
                return curso;
            }
        }
        return nullptr;
    }

    Especializacion* obtenerEspecializacion(int id) {
        for (auto especializacion : especializaciones) {
            if (especializacion->getId() == id) {
                return especializacion;
            }
        }
        return nullptr;
    }

private:
    void cargarCursos() {
        ifstream archivo(RUTA_CURSOS);
        if (!archivo.is_open()) return;

        string linea;
        while (getline(archivo, linea)) {
            // Parsear línea y crear curso
            // Implementar según el formato del archivo
        }
    }

    void cargarEspecializaciones() {
        ifstream archivo(RUTA_ESPECIALIZACIONES);
        if (!archivo.is_open()) return;

        string linea;
        while (getline(archivo, linea)) {
            // Parsear línea y crear especialización
            // Implementar según el formato del archivo
        }
    }

    void guardarCursos() {
        ofstream archivo(RUTA_CURSOS);
        if (!archivo.is_open()) return;

        for (auto curso : cursos) {
            archivo << curso->toString() << endl;
        }
    }

    void guardarEspecializaciones() {
        ofstream archivo(RUTA_ESPECIALIZACIONES);
        if (!archivo.is_open()) return;

        for (auto especializacion : especializaciones) {
            archivo << especializacion->toString() << endl;
        }
    }
}; 