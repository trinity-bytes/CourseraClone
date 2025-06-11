// filepath: Headers/Entities/Inscripcion.hpp
// Descripcion: Clase que representa una inscripción de estudiante a una actividad

#ifndef COURSERACLONE_ENTITIES_INSCRIPCION_HPP
#define COURSERACLONE_ENTITIES_INSCRIPCION_HPP

// Headers de la libreria estandar
#include <iostream>
#include <fstream>

// Headers propios
#include "Actividad.hpp"
#include "Venta.hpp"
#include "../Persistence/InscripcionTypes.hpp"
#include "../Persistence/FilesManager.hpp"

// Clase que representa una inscripción de estudiante a una actividad
class Inscripcion {
private:
    int _id;
    int _idEstudiante;
    Actividad* _actividad;
    double _progreso;
    bool _completado;
    bool _pagado;

public:
    Inscripcion() : _id(0), _idEstudiante(0), _actividad(nullptr), _progreso(0.0), _completado(false), _pagado(false) {}

    Inscripcion(int _idEstudiante, Actividad* _actividad)
        : _idEstudiante(_idEstudiante), _actividad(_actividad),
        _progreso(0.0), _completado(false), _pagado(false) {
        // Obtener nuevo ID basado en tamaño actual del archivo
        std::ifstream archivo(RUTA_INSCRIPCIONES, std::ios::binary | std::ios::ate);
        std::streamoff peso = archivo.tellg();
        _id = int(peso / sizeof(InscripcionBinaria));
    }

    Inscripcion(InscripcionBinaria& _bin, Actividad* _act, int _off)
        : _idEstudiante(_bin.idEstudiante),
        _actividad(_act),
        _progreso(_bin.progreso),
        _completado(_bin.completado),
        _pagado(_bin.pagado),
        _id(_off) {
    }

    void guardar() {
        InscripcionBinaria nuevo(_idEstudiante, _actividad->getId(), _actividad->getTipo(), _progreso, _completado, _pagado);
        int offsetRegistro = 0;
        if (FileManager::guardarInscripcionBinaria(nuevo, offsetRegistro)) {
            _id = offsetRegistro;
        }
    }    void actualizaPagoEnDisco(int _posicion, bool _estado) {
        FileManager::actualizarPagoInscripcion(_posicion, _estado);
    }

    bool estaPagada() const { return _pagado; }

    void marcarComoPagada(LinkedList<Boleta>& _boletas) {
        if (!estaPagada()) {
            _pagado = true;
            FileManager::actualizarPagoInscripcion(_id, _pagado);
            Venta prueba;
            prueba.pagarInscripcion(_id, getIdActividad(), 20.5, _boletas, _idEstudiante);
        }
    }

    int getIdActividad() const { return _actividad->getId(); }
    int getId() const { return _id; }
    int getIdEstudiante() const { return _idEstudiante; }

    void mostrar() const {
        std::cout << "ID Estudiante: " << _idEstudiante << std::endl;
        std::cout << "ID Actividad: " << _actividad->getId() << std::endl;
        std::cout << "Progreso: " << _progreso << std::endl;
        std::cout << "Completado: " << (_completado ? "Si" : "No") << std::endl;
        std::cout << "Pagado: " << (_pagado ? "Si" : "No") << std::endl;
    }
};

#endif // COURSERACLONE_ENTITIES_INSCRIPCION_HPP

#endif // !COURSERACLONE_ENTITIES_INSCRIPCION_HPP