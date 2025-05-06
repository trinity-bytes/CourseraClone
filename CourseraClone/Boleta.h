#pragma once
#include <iostream>
using namespace std;

class Boleta {
private:
	int id;
	string nombreEstudiante;
	string apellidoEstudiante;
	string nombreActividad;
	string fecha;
	double precio;

public:
	Boleta(int _id, string _nombreEstudiante, string _nombreActividad, string _apellidoEstudiante, string _fecha, double _precio) {
		id = _id;
		nombreEstudiante = _nombreEstudiante;
		nombreActividad = _nombreActividad;
		apellidoEstudiante = _apellidoEstudiante;
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
	string getApellidoEstudiante() {
		return apellidoEstudiante;
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