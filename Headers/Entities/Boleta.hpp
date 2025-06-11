#ifndef COURSERACLONE_ENTITIES_BOLETA_HPP
#define COURSERACLONE_ENTITIES_BOLETA_HPP

// Headers estandar
#include <iostream> // std::cout, std::endl
#include <string>   // std::string
#include <ctime>    // time_t, tm, localtime
#include <fstream>  // std::ofstream, std::fstream

// Headers propios
#include "../DataStructures/algoritmosBusqueda.hpp"
#include "../Persistence/BoletaTypes.hpp"

class Boleta {
private:
    int id;
    int idEstudiante;
    int idActividad;
    int tipoActividad;
    std::string fecha;
    double precio;

    std::string generarFechaActual() {
        time_t t = time(nullptr);
        tm tm = localtime(&t)[0];

        std::string fecha;

        auto agregar = [&](int valor) {
            if (valor < 10) fecha += '0';
            fecha += std::to_string(valor);
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
    Boleta(int _id, int est, int act, std::string _fecha, double _precio)
        : id(_id), idEstudiante(est), idActividad(act),
        fecha(_fecha), precio(_precio) {
    }

    Boleta() :
        id(-1), idEstudiante(-1), idActividad(-1), fecha(""), precio(0) {
    }

    Boleta(int est, int act, double _precio, int _id)
        : idEstudiante(est), idActividad(act),
        fecha(generarFechaActual()), precio(_precio), id(_id) {

    }

    void guardar() {
        // 1) Escribir boleta.dat
        std::ofstream archivo("Resources/Data/boletas.dat", std::ios::binary | std::ios::app);
        int offset = 0;
        if (archivo.is_open()) {
            archivo.seekp(0, std::ios::end);
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

        std::fstream indiceArchivo("Resources/Data/indices/boletas.dat", std::ios::binary | std::ios::in | std::ios::out);
        if (indiceArchivo.is_open()) {
            indiceArchivo.seekg(0, std::ios::end);
            int cantidad = indiceArchivo.tellg() / sizeof(BoletaIndex);

            // predicado para busquedaBinaria
            auto pred = [&](int pos)->bool {
                BoletaIndex temp;
                indiceArchivo.seekg(pos * sizeof(temp), std::ios::beg);
                indiceArchivo.read(reinterpret_cast<char*>(&temp), sizeof(temp));
                return idEstudiante >= temp.idEstudiante;
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
            BoletaIndex nuevo(idEstudiante, offset);
            indiceArchivo.seekp(posIns * sizeof(nuevo), std::ios::beg);
            indiceArchivo.write(reinterpret_cast<char*>(&nuevo), sizeof(nuevo));
            indiceArchivo.close();
        }

    }
    void mostrar() 
    {
        std::cout << "Boleta ID: " << id << std::endl;
        std::cout << "ID Estudiante: " << idEstudiante << std::endl;
        std::cout << "ID Actividad: " << idActividad << std::endl;
        std::cout << "Fecha: " << fecha << std::endl;
        std::cout << "Precio: " << precio << std::endl;
    }

    int getId() { return id; }
    std::string getFecha() { return fecha; }
    double getPrecio() { return precio; }
};

#endif // !COURSERACLONE_ENTITIES_BOLETA_HPP