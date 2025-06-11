// filepath: Headers/Controllers/CourseManager.hpp
// description: Clase para gestionar cursos y especializaciones de CourseraClone.

#ifndef COURSERACLONE_CONTROLLERS_COURSEMANAGER_HPP
#define COURSERACLONE_CONTROLLERS_COURSEMANAGER_HPP

// Headers estandar
#include <fstream>   // Para manejo de archivos
#include <string>    // Para manejo de cadenas
#include <vector>    // Para manejo de vectores
#include <map>       // Para manejo de mapas
#include <stdexcept> // Para manejo de excepciones
#include <memory>    // Para std::unique_ptr

// Headers propios
#include "../Entities/Curso.hpp"
#include "../Entities/Especializacion.hpp"
#include "../Entities/Inscripcion.hpp"
#include "../DataStructures/LinkedList.hpp"
#include "../Persistence/FilesManager.hpp" // Para RawActividadesData e InscripcionBinaria

// Enum class para tipos de actividad
enum class ActividadTipo : int {
    CURSO = 1,
    ESPECIALIZACION = 2
};

class CourseManager {
private:

    LinkedList<std::unique_ptr<Curso>> _cursos;
    LinkedList<std::unique_ptr<Especializacion>> _especializaciones;

    const std::string RUTA_INSCRIPCIONES = "Resources/Data/inscripciones.dat";
    const std::string RUTA_PROGRESO = "Resources/Data/progreso.dat";
    const std::string RUTA_CALIFICACIONES = "Resources/Data/calificaciones.txt";

    std::map<int, std::map<int, int>> _progresoEstudiantes;
    std::map<int, std::map<int, std::pair<int, std::string>>> _calificacionesCursos;

public:
    CourseManager() = default;

    // No necesitamos un destructor ~CourseManager() manual.
    // std::unique_ptr se encargará de liberar la memoria de los cursos y especializaciones.    
    void inicializarDesdeDatos(
        const RawActividadesData& _dataActividades,
        const std::vector<InscripcionBinaria>& _dataInscripciones
    ) {
        // Cargar Cursos
        for (const auto& _cursoData : _dataActividades.cursos) 
        {
            crearCurso(
                _cursoData.idEmpresa,
                _cursoData.tituloActividad,
                _cursoData.nombreEmpresa,
                _cursoData.cantidadClases,
                _cursoData.instructor,
                _cursoData.descripcionActividad,
                _cursoData.titulosClases,
                _cursoData.descripcionesClases
            );
        }

        // Cargar Especializaciones
        for (const auto& _espData : _dataActividades.especializaciones) 
        {
            crearEspecializacion(
                _espData.idEmpresa,
                _espData.nombreEmpresa,
                _espData.tituloActividad,
                _espData.cantidadCursosEnEspecializacion,
                _espData.descripcionActividad,
                _espData.idsCursosInternos
            );
        }        // Procesar Inscripciones para actualizar contadores
        for (const auto& _inscripcion : _dataInscripciones) 
        {
            if (_inscripcion.tipoActividad == static_cast<int>(ActividadTipo::CURSO)) 
            {
                Curso* curso = obtenerCurso(_inscripcion.idActividad);
                if (curso) {
                    curso->aumentarAlumno(1);
                }
            }
            else if (_inscripcion.tipoActividad == static_cast<int>(ActividadTipo::ESPECIALIZACION)) 
            {
                Especializacion* especializacion = obtenerEspecializacion(_inscripcion.idActividad);
                if (especializacion) {
                    especializacion->aumentarAlumno(1);
                }
            }
        }
    }

    bool crearCurso(
        int _idEmpresa,
        const std::string& _titulo,
        const std::string& _nombreEmpresa,
        int _cantidadClases,
        const std::string& _instructor,
        const std::string& _descripcion,
        const std::vector<std::string>& _titulosClases,
        const std::vector<std::string>& _descripcionesClases
    ) {
        auto nuevoCurso = std::make_unique<Curso>(
            _cursos.getTamano() + 1, // Asumiendo ID autoincremental
            _idEmpresa,
            _nombreEmpresa,
            _titulo,
            _descripcion,
            _instructor,
            0 // Alumnos iniciales
        );

        for (int i = 0; i < _cantidadClases; ++i) 
        {
            if (i < _titulosClases.size() && i < _descripcionesClases.size()) 
            {
                nuevoCurso->anadirClases(_titulosClases[i], _descripcionesClases[i]);
            }
            else {
                // Hay que considerar loggear una advertencia. Por ahora, salimos.
                break;
            }
        }

        _cursos.agregarAlFinal(std::move(nuevoCurso)); // std::move transfiere la propiedad al linked list
        return true;
    }

    bool crearEspecializacion(
        int _idEmpresa,
        const std::string& _nombreEmpresa,
        const std::string& _titulo,
        int _cantidadCursos,
        const std::string& _descripcion,
        const std::vector<int>& _idsCursos
    ) {
        auto nuevaEspecializacion = std::make_unique<Especializacion>(
            _especializaciones.getTamano() + 1, // ID Autoincremental
            _idEmpresa,
            _nombreEmpresa,
            _titulo,
            0, // Alumnos iniciales
            _descripcion
        );

        if (_idsCursos.size() != _cantidadCursos) {
            // Loggear advertencia o manejar error de datos inconsistentes
        }

        for (int idCurso : _idsCursos) {
            nuevaEspecializacion->anadirCursoPorId(idCurso);
        }

        _especializaciones.agregarAlFinal(std::move(nuevaEspecializacion));
        return true;
    }

    bool inscribirEstudianteACurso(int _idEstudiante, int _idCurso) {
        Curso* curso = obtenerCurso(_idCurso);
        if (!curso) return false;

        InscripcionBinaria inscripcion;
        inscripcion.idEstudiante = _idEstudiante;
        inscripcion.idActividad = _idCurso;
        inscripcion.tipoActividad = static_cast<int>(ActividadTipo::CURSO);

        std::ofstream archivo(RUTA_INSCRIPCIONES, std::ios::binary | std::ios::app);
        if (!archivo.is_open()) return false;

        archivo.write(reinterpret_cast<const char*>(&inscripcion), sizeof(inscripcion));
        curso->aumentarAlumno(1);
        return true;
    }

    // Getters que devuelven referencias const para proteger la encapsulación y son métodos const.
    const LinkedList<std::unique_ptr<Curso>>& getCursos() const { return _cursos; }
    const LinkedList<std::unique_ptr<Especializacion>>& getEspecializaciones() const { return _especializaciones; }

    // Métodos de búsqueda marcados como const. Devuelven punteros crudos no propietarios.
    Curso* obtenerCurso(int _id) const 
    {
        auto busquedaId = [](const std::unique_ptr<Curso>& c) { return c->getId(); };
        //int pos = _cursos.buscarPorClave(_id, busquedaId);
        //return (pos != -1) ? _cursos.get(pos).get() : nullptr;
    }

    Especializacion* obtenerEspecializacion(int _id) const 
    {
        auto busquedaId = [](const std::unique_ptr<Especializacion>& e) { return e->getId(); };
        //int pos = _especializaciones.buscarPorClave(_id, busquedaId);
        //return (pos != -1) ? _especializaciones.get(pos).get() : nullptr;
    }
};

#endif // !COURSERACLONE_CONTROLLERS_COURSEMANAGER_HPP