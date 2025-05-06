#pragma once
#include "Actividad.h"
#include "Instructor.h"
#include "Clase.h"
#include "algoritmosBusqueda.h"
#include <fstream>

class Curso : public Actividad {
private:
	string instructor;
	LinkedList<Clase> clases;

public:
	Curso(int _id, int _idEmpresa, string _titulo, string _nombreEmpresa, int _cantidadAlumnos, string _instructor, string _descripcion) : Actividad(_id, _idEmpresa, _nombreEmpresa, _titulo, 0, 1, _descripcion) {
		instructor = _instructor;
		clases = LinkedList<Clase>();
	}

	void añadirClases(string _titulo, string _descripcion) {
		Clase nuevaClase(_titulo, _descripcion);
		clases.agregarAlFinal(nuevaClase);
	}

	void guardar() override {
		ofstream archivo("Resources/Data/actividades.txt", ios::app);
		if (archivo.is_open()) {
			archivo << idEmpresa << '\n';
			archivo << Actividad::tipo << '\n';
			archivo << Actividad::nombreEmpresa << '\n';
			archivo << titulo << '\n';
			archivo << descripcion << '\n';
			archivo << instructor << '\n';

			auto conseguirTitulo = [](const Clase& c) {
				return c.getTitulo();
				};
			auto conseguirDescripcion = [](const Clase& c) {
				return c.getDescripcion();
				};

			vector<string> titulos = clases.extraerDato<string>(conseguirTitulo);
			vector<string> descripciones = clases.extraerDato<string>(conseguirDescripcion);

			archivo << clases.getTamano() << '\n';
			for (int i = 0; i < int(clases.getTamano()); i++) {
				cout << titulo[i] << '\n';
				cout << descripciones[i] << '\n';
			}
			archivo.close();
		}
		else {
			cout << "Error al abrir el archivo." << endl;
		}
	}
	// getters
	string getTitulo() {
		return titulo;
	}

	LinkedList<Clase> getClases() {
		return clases;
	}

	int getId() {
		return id;
	}
};