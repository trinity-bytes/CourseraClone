#pragma once
#include "../Curso.h"
#include "../LinkedList.h"
#include "../Especializacion.h"
#include "../Inscripcion.h"
#include <fstream>
#include <string>
#include <vector>
#include <map> // Para el mapa de progreso y calificaciones

class GestionadorCursos {
private:
    LinkedList<Curso*> cursos;
    LinkedList<Especializacion*> especializaciones;

    vector<int> idsCursos; // Ya no referencia

    const string RUTA_CURSOS = "Resources/Data/cursos.txt";
    const string RUTA_ESPECIALIZACIONES = "Resources/Data/especializaciones.txt";
    const string RUTA_INSCRIPCIONES = "Resources/Data/inscripciones.dat";
    const string RUTA_PROGRESO = "Resources/Data/progreso.dat";
    const string RUTA_CALIFICACIONES = "Resources/Data/calificaciones.txt";

    // Mapa de progreso: <idEstudiante, <idCurso, progreso>>
    map<int, map<int, int>> progresoEstudiantes;
    // Mapa de calificaciones: <idCurso, <idEstudiante, <calificacion, comentario>>>
    map<int, map<int, pair<int, string>>> calificacionesCursos;

public:
    GestionadorCursos() {
        cargarCursos();
        cargarEspecializaciones();
    }


    GestionadorCursos(vector<int>& _idsCursos) : idsCursos(_idsCursos)
    {
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

    bool crearCurso(
        int idEmpresa, 
        const string& titulo, 
        const string& nombreEmpresa,
        int cantidadClases, 
        const string& instructor, 
        const string& descripcion) 
    {
        Curso* nuevoCurso = new Curso(
            cursos.getTamano() + 1, // ID autoincremental
            idEmpresa,
            nombreEmpresa,
            titulo,
			descripcion,
			instructor,
            cantidadClases
        );

        cursos.agregarAlFinal(nuevoCurso);
        guardarCursos();
        return true;
    }

    bool crearEspecializacion(
        int idEmpresa, 
        const string& nombreEmpresa,
        const string& titulo, 
        int cantidadCursos, 
        const string& descripcion,
        vector<int>& idsCursos)
    {
        Especializacion* nuevaEspecializacion = new Especializacion(
            especializaciones.getTamano() + 1, // ID autoincremental
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

    // Métodos de inscripción
    bool inscribirEstudianteACurso(int idEstudiante, int idCurso) {
        Curso* curso = obtenerCurso(idCurso);
        if (!curso) return false;

        // Crear inscripción
        InscripcionBinaria inscripcion;
        inscripcion.idEstudiante = idEstudiante;
        inscripcion.idActividad = idCurso;
        //inscripcion.fecha = time(nullptr);

        // Guardar inscripción
        ofstream archivo(RUTA_INSCRIPCIONES, ios::binary | ios::app);
        if (!archivo.is_open()) return false;

        archivo.write(reinterpret_cast<char*>(&inscripcion), sizeof(inscripcion));
        archivo.close();

        // Actualizar contador de estudiantes
        curso->aumentarAlumno(1);
        return true;
    }

    bool inscribirEstudianteAEspecializacion(int idEstudiante, int idEspecializacion) {
        Especializacion* especializacion = obtenerEspecializacion(idEspecializacion);
        if (!especializacion) return false;

        // Crear inscripción
        InscripcionBinaria inscripcion;
        inscripcion.idEstudiante = idEstudiante;
        inscripcion.idActividad = idEspecializacion;
        //inscripcion.fecha = time(nullptr);

        // Guardar inscripción
        ofstream archivo(RUTA_INSCRIPCIONES, ios::binary | ios::app);
        if (!archivo.is_open()) return false;

        archivo.write(reinterpret_cast<char*>(&inscripcion), sizeof(inscripcion));
        archivo.close();

        // Actualizar contador de estudiantes
        especializacion->aumentarAlumno(1);
        return true;
    }

    // Métodos de progreso
    bool actualizarProgresoCurso(int idEstudiante, int idCurso, int progreso) {
        if (progreso < 0 || progreso > 100) return false;

        progresoEstudiantes[idEstudiante][idCurso] = progreso;
        
        // Guardar progreso
        ofstream archivo(RUTA_PROGRESO, ios::binary | ios::app);
        if (!archivo.is_open()) return false;

        archivo.write(reinterpret_cast<char*>(&idEstudiante), sizeof(idEstudiante));
        archivo.write(reinterpret_cast<char*>(&idCurso), sizeof(idCurso));
        archivo.write(reinterpret_cast<char*>(&progreso), sizeof(progreso));
        archivo.close();

        return true;
    }

    int obtenerProgresoCurso(int idEstudiante, int idCurso) {
        auto itEstudiante = progresoEstudiantes.find(idEstudiante);
        if (itEstudiante == progresoEstudiantes.end()) return 0;

        auto itCurso = itEstudiante->second.find(idCurso);
        if (itCurso == itEstudiante->second.end()) return 0;

        return itCurso->second;
    }

    // Métodos de calificación
    bool agregarCalificacionCurso(int idEstudiante, int idCurso, int calificacion, const string& comentario) {
        if (calificacion < 1 || calificacion > 5) return false;

        calificacionesCursos[idCurso][idEstudiante] = make_pair(calificacion, comentario);
        
        // Guardar calificación
        ofstream archivo(RUTA_CALIFICACIONES, ios::app);
        if (!archivo.is_open()) return false;

        archivo << idCurso << "," << idEstudiante << "," << calificacion << "," << comentario << endl;
        archivo.close();

        return true;
    }

    pair<int, string> obtenerCalificacionCurso(int idEstudiante, int idCurso) {
        auto itCurso = calificacionesCursos.find(idCurso);
        if (itCurso == calificacionesCursos.end()) return make_pair(0, "");

        auto itEstudiante = itCurso->second.find(idEstudiante);
        if (itEstudiante == itCurso->second.end()) return make_pair(0, "");

        return itEstudiante->second;
    }

    // Métodos de listado
    vector<Curso*> listarCursosPorCategoria(const string& categoria) {
        vector<Curso*> resultados;
        for (auto curso : cursos) {
            if (curso->getCategoria() == categoria) {
                resultados.push_back(curso);
            }
        }
        return resultados;
    }

    vector<Especializacion*> listarEspecializacionesPorCategoria(const string& categoria) {
        vector<Especializacion*> resultados;
        for (auto especializacion : especializaciones) {
            if (especializacion->getCategoria() == categoria) {
                resultados.push_back(especializacion);
            }
        }
        return resultados;
    }

    // Métodos de gestión de contenido
    bool agregarContenidoCurso(int idCurso, const string& titulo, const string& contenido) {
        Curso* curso = obtenerCurso(idCurso);
        if (!curso) return false;

        curso->anadirClases(titulo, contenido);
        guardarCursos();
        return true;
    }

    bool modificarContenidoCurso(int idCurso, int idContenido, const string& nuevoContenido) {
        Curso* curso = obtenerCurso(idCurso);
        if (!curso) return false;

        if (curso->modificarClase(idContenido, nuevoContenido)) {
            guardarCursos();
            return true;
        }
        return false;
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