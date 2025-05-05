#pragma once
#include "Actividad.h"
#include "Instructor.h"
#include "algoritmosBusqueda.h"
#include <fstream>

struct InscripcionIndex {
    int idUsuario;
	int tipoActividad;
    int offset;

    InscripcionIndex(int _idUsuario, int _offset, int _tipoActividad) : idUsuario(_idUsuario), offset(_offset), tipoActividad(_tipoActividad) {}
    InscripcionIndex() : idUsuario(0), offset(0), tipoActividad(0) {}
};

struct InscripcionBinaria {
    int idEstudiante;
    int idActividad;
    double progreso;
    bool completado;
    bool pagado;

    InscripcionBinaria(int _idUsuario, int _idActividad, double _progreso, bool _completado, bool _pagado)
        : idEstudiante(_idUsuario), idActividad(_idActividad), progreso(_progreso), completado(_completado), pagado(_pagado) {
    }
    InscripcionBinaria(bool _pagado) : idEstudiante(0), idActividad(0), progreso(0.0), completado(false), pagado(_pagado) {};
};

class Inscripcion {
private:
    int id;
    int idEstudiante;
    Actividad actividad;
    double progreso;
    bool completado;
    bool pagado;

public:
    /*
    Inscripcion(int _idEstudiante, )
        : idEstudiante(_idEstudiante), idActividad(_idActividad), tipoActividad(_tipo) {
    }
    */

    void guardar() {
        ofstream archivo("Resources/Data/inscripciones.dat", ios::app);
        int offsetRegistro = 0;
        if (archivo.is_open()) {
            InscripcionBinaria nuevo(idEstudiante, actividad.getId(), progreso, completado, pagado);
            archivo.seekp(0, ios::end);
            offsetRegistro = int((archivo.tellp() / sizeof(InscripcionBinaria))) + 1;

            archivo.write(reinterpret_cast<char*>(&nuevo), sizeof(nuevo));
            archivo.close();
        }

        fstream archivoOrden("Resources/Data/indices/inscripciones.dat", ios::binary | ios::in | ios::out);
        if (archivoOrden.is_open()) {
            archivoOrden.seekg(0, ios::end);
            int cantidad = archivoOrden.tellg() / sizeof(InscripcionIndex);
            auto busqueda = [&](int pos) {
                InscripcionIndex temp;
                archivoOrden.seekg(pos * sizeof(InscripcionIndex), ios::beg);
                archivoOrden.read(reinterpret_cast<char*>(&temp), sizeof(InscripcionIndex));

                return idEstudiante >= temp.idUsuario;
                };

            int pos = busquedaBinaria(0, cantidad - 1, busqueda);

            for (int i = cantidad - 1; i >= pos; --i) {
                InscripcionIndex temp;
                archivoOrden.seekg(i * sizeof(InscripcionIndex), ios::beg);
                archivoOrden.read(reinterpret_cast<char*>(&temp), sizeof(InscripcionIndex));
                archivoOrden.seekp((i + 1) * sizeof(InscripcionIndex), ios::beg);
                archivoOrden.write(reinterpret_cast<char*>(&temp), sizeof(InscripcionIndex));
            }

            InscripcionIndex nuevo(idEstudiante, offsetRegistro, actividad.getTipo());
            archivoOrden.seekp(pos * sizeof(InscripcionIndex), ios::beg);
            archivoOrden.write(reinterpret_cast<char*>(&nuevo), sizeof(InscripcionIndex));
            archivoOrden.close();
        }
    }
};