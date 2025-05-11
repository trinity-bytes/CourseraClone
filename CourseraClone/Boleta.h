#pragma once

#include <string>
#include <ctime>
#include <fstream>
#include "algoritmosBusqueda.h"
using namespace std;

struct BoletaBinaria {
    int    idEstudiante;
    int    idActividad;
    char   fecha[20];    // "dd/MM/yy HH:mm:ss\0"
    double precio;

    BoletaBinaria() : idEstudiante(0), idActividad(0), fecha(), precio(0.0) {}
};

struct BoletaIndex {
    int   idEstudiante;
    int offset;

    BoletaIndex() : idEstudiante(0), offset(0) {}
    BoletaIndex(int _idEstudiante, int _offset) : idEstudiante(_idEstudiante), offset(_offset) {}
};

class Boleta {
private:
    int id;
    int idEstudiante;
    int idActividad;
    string fecha;
    double precio;

    string generarFechaActual() {
        time_t t = time(nullptr);
        tm tm = localtime(&t)[0];

        string fecha;

        auto agregar = [&](int valor) {
            if (valor < 10) fecha += '0';
            fecha += to_string(valor);
            };

        agregar(tm.tm_mday);
        fecha += '/';
        agregar(tm.tm_mon + 1);
        fecha += '/';
        agregar(tm.tm_year % 100);
        fecha += ' ';
        agregar(tm.tm_hour);
        fecha += ':';
        agregar(tm.tm_min);
        fecha += ':';
        agregar(tm.tm_sec);

        return fecha;
    }

public:
    Boleta(int _id, int est, int act, string _fecha, double _precio)
        : id(_id), idEstudiante(est), idActividad(act),
        fecha(_fecha), precio(_precio) {}

    Boleta(int est, int act, double _precio)
        : idEstudiante(est), idActividad(act),
        fecha(generarFechaActual()), precio(_precio) {
        
        ifstream archivo("Resources/Data/boletas.dat", ios::binary);
        if (archivo.is_open()) {
            id = int(archivo.tellg() / sizeof(BoletaBinaria));
            archivo.close();
        }
        else {
            id = 1;
        }

    }

    void guardar() {
        // 1) Escribir boleta.dat
        ofstream archivo("Resources/Data/boletas.dat", ios::binary | ios::app);
        int offset = 0;
        if (archivo.is_open()) {
            archivo.seekp(0, ios::end);
            offset = archivo.tellp();

            BoletaBinaria boleBin;
            boleBin.idEstudiante = idEstudiante;
            boleBin.idActividad = idActividad;
            strncpy(boleBin.fecha, fecha.c_str(), sizeof(boleBin.fecha) - 1);
            boleBin.fecha[sizeof(boleBin.fecha) - 1] = '\0';
            boleBin.precio = precio;
            archivo.write(reinterpret_cast<char*>(&boleBin), sizeof(boleBin));
            archivo.close();
        }
        
        fstream indiceArchivo("Resources/Data/indices/boletas.dat", ios::binary | ios::in | ios::out);
        if (indiceArchivo.is_open()) {
            indiceArchivo.seekg(0, ios::end);
            int cantidad = indiceArchivo.tellg() / sizeof(BoletaIndex);

            // predicado para busquedaBinaria
            auto pred = [&](int pos)->bool {
                BoletaIndex temp;
                indiceArchivo.seekg(pos * sizeof(temp), ios::beg);
                indiceArchivo.read(reinterpret_cast<char*>(&temp), sizeof(temp));
                return idEstudiante >= temp.idEstudiante;
                };

            int posIns = (cantidad > 0) ? busquedaBinaria(0, cantidad - 1, pred) : 0;

            for (int i = cantidad - 1; i >= posIns; --i) {
                BoletaIndex t;
                indiceArchivo.seekg(i * sizeof(t), ios::beg);
                indiceArchivo.read(reinterpret_cast<char*>(&t), sizeof(t));
                indiceArchivo.seekp((i + 1) * sizeof(t), ios::beg);
                indiceArchivo.write(reinterpret_cast<char*>(&t), sizeof(t));
            }
            // insertar nuevo
            BoletaIndex nuevo(idEstudiante, offset);
            indiceArchivo.seekp(posIns * sizeof(nuevo), ios::beg);
            indiceArchivo.write(reinterpret_cast<char*>(&nuevo), sizeof(nuevo));
            indiceArchivo.close();
        }
        
    }
};
