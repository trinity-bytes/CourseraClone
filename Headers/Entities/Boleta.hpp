// filepath: Headers/Entities/Boleta.hpp
// Descripcion: Clase que representa una boleta de pago en el sistema

#ifndef COURSERACLONE_ENTITIES_BOLETA_HPP
#define COURSERACLONE_ENTITIES_BOLETA_HPP

// Headers estandar
#include <iostream>
#include <string>
#include <ctime>
#include <fstream>

// Headers propios
#include "../DataStructures/algoritmosBusqueda.hpp"
#include "../Persistence/BoletaTypes.hpp"

// Clase que representa una boleta de pago
class Boleta {
private:
    int _id;
    int _idEstudiante;
    int _idActividad;
    int _tipoActividad;
    std::string _fecha;
    double _precio;

    std::string generarFechaActual() {
        time_t t = time(nullptr);
        tm tm = localtime(&t)[0];

        std::string fecha;

        auto agregar = [&](int _valor) {
            if (_valor < 10) fecha += '0';
            fecha += std::to_string(_valor);
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
    Boleta(int _id, int _idEstudiante, int _idActividad, const std::string& _fecha, double _precio)
        : _id(_id), _idEstudiante(_idEstudiante), _idActividad(_idActividad),
        _fecha(_fecha), _precio(_precio) {
    }

    Boleta() :
        _id(-1), _idEstudiante(-1), _idActividad(-1), _fecha(""), _precio(0) {
    }

    Boleta(int _idEstudiante, int _idActividad, double _precio, int _id)
        : _idEstudiante(_idEstudiante), _idActividad(_idActividad),
        _fecha(generarFechaActual()), _precio(_precio), _id(_id) {
    }

    void guardar() {
        // 1) Escribir boleta.dat
        std::ofstream archivo("Resources/Data/boletas.dat", std::ios::binary | std::ios::app);
        int offset = 0;
        if (archivo.is_open()) {
            archivo.seekp(0, std::ios::end);
            offset = archivo.tellp();

            BoletaBinaria boleBin;
            boleBin.idEstudiante = _idEstudiante;
            boleBin.idActividad = _idActividad;
            strncpy(boleBin.fecha, _fecha.c_str(), sizeof(boleBin.fecha) - 1);
            boleBin.fecha[sizeof(boleBin.fecha) - 1] = '\0';            boleBin.precio = _precio;
            archivo.write(reinterpret_cast<char*>(&boleBin), sizeof(boleBin));
            archivo.close();
        }

        std::fstream indiceArchivo("Resources/Data/indices/boletas.dat", std::ios::binary | std::ios::in | std::ios::out);
        if (indiceArchivo.is_open()) {
            indiceArchivo.seekg(0, std::ios::end);
            int cantidad = indiceArchivo.tellg() / sizeof(BoletaIndex);

            // predicado para busquedaBinaria
            auto pred = [&](int _pos) -> bool {
                BoletaIndex temp;
                indiceArchivo.seekg(_pos * sizeof(temp), std::ios::beg);
                indiceArchivo.read(reinterpret_cast<char*>(&temp), sizeof(temp));
                return _idEstudiante >= temp.idEstudiante;
            };

            int posIns = (cantidad > 0) ? busquedaBinaria(0, cantidad - 1, pred) : 0;

            for (int i = cantidad - 1; i >= posIns; --i) {
                BoletaIndex t;
                indiceArchivo.seekg(i * sizeof(t), std::ios::beg);
                indiceArchivo.read(reinterpret_cast<char*>(&t), sizeof(t));
                indiceArchivo.seekp((i + 1) * sizeof(t), std::ios::beg);
                indiceArchivo.write(reinterpret_cast<char*>(&t), sizeof(t));
            }
            // insertar nuevo
            BoletaIndex nuevo(_idEstudiante, offset);
            indiceArchivo.seekp(posIns * sizeof(nuevo), std::ios::beg);
            indiceArchivo.write(reinterpret_cast<char*>(&nuevo), sizeof(nuevo));
            indiceArchivo.close();
        }
    }

    void mostrar() const {
        std::cout << "Boleta ID: " << _id << std::endl;
        std::cout << "ID Estudiante: " << _idEstudiante << std::endl;
        std::cout << "ID Actividad: " << _idActividad << std::endl;
        std::cout << "Fecha: " << _fecha << std::endl;
        std::cout << "Precio: " << _precio << std::endl;
    }

    int getId() const { return _id; }
    const std::string& getFecha() const { return _fecha; }
    double getPrecio() const { return _precio; }
};

#endif // COURSERACLONE_ENTITIES_BOLETA_HPP