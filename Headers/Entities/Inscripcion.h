#pragma once

// headers propios
#include "Actividad.h"
#include "../Persistence/InscripcionTypes.hpp"
#include "../Persistence/FilesManager.hpp"
#include "Venta.h"

// headers de la libreria estandar
#include <iostream>

using namespace std;

class Inscripcion {
private:
    int id;
    int idEstudiante;
    Actividad* actividad;
    double progreso;
    bool completado;
    bool pagado;

public:
    Inscripcion() : id(0), idEstudiante(0), actividad(nullptr), progreso(0.0), completado(false), pagado(false) {}

    Inscripcion(int _idEstudiante, Actividad* _actividad)
        : idEstudiante(_idEstudiante), actividad(_actividad),
        progreso(0.0), completado(false), pagado(false)
    {
        // Obtener nuevo ID basado en tamaño actual del archivo
        std::ifstream archivo(RUTA_INSCRIPCIONES, ios::binary | ios::ate);
        streamoff peso = archivo.tellg();
        id = int(peso / sizeof(InscripcionBinaria));
    }

    Inscripcion(InscripcionBinaria& bin, Actividad* act, int off)
        : idEstudiante(bin.idEstudiante),
        actividad(act),
        progreso(bin.progreso),
        completado(bin.completado),
        pagado(bin.pagado),
        id(off)
    {
    }

    void guardar() {
        InscripcionBinaria nuevo(idEstudiante, actividad->getId(), actividad->getTipo(), progreso, completado, pagado);
        int offsetRegistro = 0;
        if (FileManager::guardarInscripcionBinaria(nuevo, offsetRegistro)) {
            // opcional: actualizar índices si es necesario
            id = offsetRegistro;
        }
    }

    void actualizaPagoEnDisco(int posicion, bool estado) {
        FileManager::actualizarPagoInscripcion(posicion, estado);
    }

    bool estaPagada() const { return pagado; }

    void marcarComoPagada(LinkedList<Boleta>& boletas) { 
        if (!estaPagada()) {
            pagado = true;
            FileManager::actualizarPagoInscripcion(id, pagado);
            Venta prueba;
            prueba.pagarInscripcion(id, getIdActividad(), 20.5, boletas, idEstudiante);
        }
    }

    int getIdActividad() const { return actividad->getId(); }
    int getId() const { return id; }
    int getIdEstudiante() const { return idEstudiante; }

    void mostrar() {
        cout << "ID Estudiante: " << idEstudiante << endl;
        cout << "ID Actividad: " << actividad->getId() << endl;
        cout << "Progreso: " << progreso << endl;
        cout << "Completado: " << (completado ? "Si" : "No") << endl;
        cout << "Pagado: " << (pagado ? "Si" : "No") << endl;
    }
};