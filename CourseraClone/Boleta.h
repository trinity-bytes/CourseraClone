#pragma once
#include <iostream>
using namespace std;

class Boleta {
private:
	int id;
	string nombreEstudiante;
	string nombreActividad;
	string fecha;
	double precio;

public:
	Boleta(int _id, string _nombreEstudiante, string _nombreActividad, string _fecha, double _precio) {
		id = _id;
		nombreEstudiante = _nombreEstudiante;
		nombreActividad = _nombreActividad;
		fecha = _fecha;
		precio = _precio;
	}

	// Getters
	int getId() {
		return id;
	}
	string getNombreEstudiante() {
		return nombreEstudiante;
	}
	string getNombreActividad() {
		return nombreActividad;
	}

	void mostrar() {
		cout << "Boleta ID: " << id << endl;
		cout << "Nombre Estudiante: " << nombreEstudiante << endl;
		cout << "Nombre Actividad: " << nombreActividad << endl;
		cout << "Fecha: " << fecha << endl;
		cout << "Precio: $" << precio << endl;
	}
};

/*
// Boleta.h
#include <Date.h>
#include "BoletaPersistencia.h"
class Boleta {
private:
    int    id;
    int    idEstudiante;
    int    idActividad;
    Date   fecha;
    double precio;
public:
    // Nuevo constructor
    Boleta(int _id, int est, int act, const Date& _fecha, double _precio)
        : id(_id), idEstudiante(est), idActividad(act),
        fecha(_fecha), precio(_precio) {
    }

    void guardar() {
        // 1) Escribir registro principal
        std::ofstream out("Resources/Data/boletas.dat",
            std::ios::binary | std::ios::app);
        if (!out.is_open()) throw std::runtime_error("No puedo abrir boletas.dat");
        out.seekp(0, std::ios::end);
        long offset = out.tellp();

        BoletaBinaria bin{ id, idEstudiante, idActividad, fecha, precio };
        out.write(reinterpret_cast<char*>(&bin), sizeof(bin));
        out.close();

        // 2) Insertar en índice
        const char* idxPath = "Resources/Data/indices/boletas.dat";
        std::fstream idx(idxPath, std::ios::binary | std::ios::in | std::ios::out);
        if (!idx.is_open()) {
            // si no existe, crearlo
            std::ofstream create(idxPath, std::ios::binary);
            create.close();
            idx.open(idxPath, std::ios::binary | std::ios::in | std::ios::out);
        }
        idx.seekg(0, std::ios::end);
        int count = idx.tellg() / sizeof(BoletaIndex);

        // búsqueda para mantener orden por idEstudiante
        auto pred = [&](int pos)->bool {
            BoletaIndex temp;
            idx.seekg(pos * sizeof(BoletaIndex), std::ios::beg);
            idx.read(reinterpret_cast<char*>(&temp), sizeof(temp));
            return idEstudiante >= temp.idEstudiante;
            };
        // Supongamos busquedaBinaria disponible (lower_bound)
        int posIns = (count > 0
            ? busquedaBinaria(0, count - 1, pred)
            : 0);
        // mover registros hacia atrás
        for (int i = count - 1; i >= posIns; --i) {
            BoletaIndex t;
            idx.seekg(i * sizeof(BoletaIndex), std::ios::beg);
            idx.read(reinterpret_cast<char*>(&t), sizeof(t));
            idx.seekp((i + 1) * sizeof(BoletaIndex), std::ios::beg);
            idx.write(reinterpret_cast<char*>(&t), sizeof(t));
        }
        // escribir nuevo índice
        BoletaIndex nuevo{ idEstudiante, offset };
        idx.seekp(posIns * sizeof(BoletaIndex), std::ios::beg);
        idx.write(reinterpret_cast<char*>(&nuevo), sizeof(nuevo));
        idx.close();
    }
};
*/