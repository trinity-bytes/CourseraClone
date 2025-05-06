#pragma once
#include "Actividad.h"
#include "Clase.h"
#include "algoritmosBusqueda.h"
#include <fstream>

class Curso : public Actividad {
private:
	string instructor;
	int cantidadClases;
	LinkedList<Clase> clases;

public:

	Curso() : Actividad(0,0,"","",0,1,"") {
		instructor = "";
		clases = LinkedList<Clase>();
	}

	Curso(int _id, int _idEmpresa, string _nombreEmpresa, string _titulo, string _descripcion, string _instructor, int _cantidadClases) : Actividad(_id, _idEmpresa, _nombreEmpresa, _titulo, 0, 1, _descripcion) {
		instructor = _instructor;
		cantidadClases = _cantidadClases;
		clases = LinkedList<Clase>();
	}

	void anadirClases(string _titulo, string _descripcion) {
		Clase nuevaClase(_titulo, _descripcion);
		clases.agregarAlFinal(nuevaClase);
	}

	void guardar() {
		ofstream archivo("Resources/Data/actividades.txt", ios::app);
		if (archivo.is_open()) {
			archivo << getIdEmpresa() << '\n';
			archivo << getTipo() << '\n';
			archivo << getNombreEmpresa() << '\n';
			archivo << titulo << '\n';   
			archivo << getDescripcion() << '\n';     
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
				cout << titulos[i] << '\n';
				cout << descripciones[i] << '\n';
			}
			archivo.close();
		}
		else {
			cout << "Error al abrir el archivo." << endl;
		}
	}
	// getters

	// Sobrescribir método virtual de Actividad
	void mostrar() {
		cout << "Curso: " << titulo << "\n";
		cout << "Empresa: " << nombreEmpresa << "\n";
		cout << "Instructor: " << instructor << "\n";
		cout << "Cantidad de alumnos: " << cantidadAlumnos << "\n";
		cout << "Descripcion: " << descripcion << "\n";
	}

	LinkedList<Clase> getClases() {
		return clases;
	}

};