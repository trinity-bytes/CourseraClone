// filepath: Headers/Entities/Curso.hpp
// Descripcion: Clase que representa un curso en el sistema

#ifndef COURSERACLONE_ENTITIES_CURSO_HPP
#define COURSERACLONE_ENTITIES_CURSO_HPP

// Headers de la libreria estandar
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <functional>

// Headers propios
#include "Actividad.hpp"
#include "Clase.hpp"
#include "../DataStructures/algoritmosBusqueda.hpp"

// Constantes
const std::string RUTA_ARCHIVO_CURSOS = "Resources/Data/actividades.txt";

// Clase que representa un curso en el sistema educativo
class Curso : public Actividad {
private:
    std::string _instructor;
    std::string _categoria;
    float _calificacionPromedio;
    int _totalCalificaciones;
    int _cantidadClases;

    // Colecciones
    LinkedList<Clase> _clases;

public:
    // Constructores
    Curso() :
        Actividad(0, 0, "", "", 0, 1, ""),
        _instructor(""),
        _cantidadClases(0),
        _categoria(""),
        _calificacionPromedio(0.0f),
        _totalCalificaciones(0) {
    }

    Curso(
        int _id,
        int _idEmpresa,
        const std::string& _nombreEmpresa,
        const std::string& _titulo,
        const std::string& _descripcion,
        const std::string& _instructor,
        int _cantidadClases,
        const std::string& _categoria = ""
    ) :
        Actividad(_id, _idEmpresa, _nombreEmpresa, _titulo, 0, 1, _descripcion),
        _instructor(_instructor),
        _cantidadClases(_cantidadClases),
        _categoria(_categoria),
        _calificacionPromedio(0.0f),
        _totalCalificaciones(0) {
        _clases = LinkedList<Clase>();
    }

    // Getters
    const std::string& getInstructor() const { return _instructor; }
    int getCantidadClases() const { return _cantidadClases; }
    LinkedList<Clase>& getClases() { return _clases; }
    const std::string& getCategoria() const { return _categoria; }
    float getCalificacionPromedio() const { return _calificacionPromedio; }
    int getTotalCalificaciones() const { return _totalCalificaciones; }

    // Setters
    void setCategoria(const std::string& _categoria) { this->_categoria = _categoria; }

    // Métodos para gestión de clases
    void anadirClases(const std::string& _titulo, const std::string& _descripcion) {
        Clase nuevaClase(_titulo, _descripcion);
        _clases.agregarAlFinal(nuevaClase);
        _cantidadClases++;
    }

    bool modificarClase(int _idClase, const std::string& _nuevoContenido) {
        if (_idClase < 0 || _idClase >= _clases.getTamano())
            return false;

        auto it = _clases.begin();
        std::advance(it, _idClase);
        it->setContenido(_nuevoContenido);
        return true;
    }

    bool eliminarClase(int idClase) {
        if (idClase < 0 || idClase >= clases.getTamano())
            return false;

        auto it = clases.begin();
        advance(it, idClase);
        clases.eliminar(it);
        cantidadClases--;
        return true;
    }    // Métodos para calificaciones
    void agregarCalificacion(int _calificacion) {
        if (_calificacion < 1 || _calificacion > 5)
            return;

        float sumaTotal = _calificacionPromedio * _totalCalificaciones + _calificacion;
        _totalCalificaciones++;
        _calificacionPromedio = sumaTotal / _totalCalificaciones;
    }

    // Métodos para cálculos
    int calcularProgreso(const std::vector<int>& _clasesCompletadas) const {
        if (_clasesCompletadas.empty() || _cantidadClases == 0)
            return 0;
        return (_clasesCompletadas.size() * 100) / _cantidadClases;
    }    // Métodos de visualización y serialización
    void mostrar() const {
        std::cout << "=== INFORMACIÓN DEL CURSO ===" << std::endl;
        std::cout << "Curso: " << _titulo << std::endl;
        std::cout << "Empresa: " << _nombreEmpresa << std::endl;
        std::cout << "Instructor: " << _instructor << std::endl;
        std::cout << "Cantidad de alumnos: " << _cantidadAlumnos << std::endl;
        std::cout << "Descripción: " << _descripcion << std::endl;
        std::cout << "Categoría: " << _categoria << std::endl;
        std::cout << "Calificación: " << _calificacionPromedio << " (" << _totalCalificaciones << " opiniones)" << std::endl;
        std::cout << "===========================" << std::endl;
    }

    // Método para persistencia
    bool guardar() {
        std::ofstream archivo(RUTA_ARCHIVO_CURSOS, std::ios::app);
        if (!archivo.is_open()) {
            std::cerr << "Error: No se pudo abrir el archivo " << RUTA_ARCHIVO_CURSOS << std::endl;
            return false;
        }

        // Guardar datos básicos        archivo << getIdEmpresa() << '\n'
            << getTipo() << '\n'
            << getNombreEmpresa() << '\n'
            << getTitulo() << '\n'
            << getDescripcion() << '\n'
            << _instructor << '\n';

        // Definir funciones lambda para extraer datos
        std::function<std::string(const Clase&)> conseguirTitulo = [](const Clase& _c) {
            return _c.getTitulo();
        };

        std::function<std::string(const Clase&)> conseguirDescripcion = [](const Clase& _c) {
            return _c.getContenido();
        };

        // Extraer datos de clases
        std::vector<std::string> titulos = _clases.extraerDato<std::string>(conseguirTitulo);
        std::vector<std::string> descripciones = _clases.extraerDato<std::string>(conseguirDescripcion);

        // Guardar clases
        archivo << _clases.getTamano() << '\n';
        for (std::size_t i = 0; i < _clases.getTamano(); i++) {
            archivo << titulos[i] << '\n'
                << descripciones[i] << '\n';
        }

        archivo.close();
        return true;
    }
};

#endif // COURSERACLONE_ENTITIES_CURSO_HPP