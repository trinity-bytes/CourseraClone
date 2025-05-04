#pragma once
#include "Actividad.h"
#include "Instructor.h"
#include "algoritmosBusqueda.h"
#include <fstream>

struct CursoIndex {
	int idCurso;     
	int offset;   
};

class Curso : public Actividad {
private:
	string instructor;
	int cantidadModulo;

public:
	Curso(int _id, int _idEmpresa, string _titulo, string _nombreEmpresa, int _cantidadAlumnos, int _tipo, string _instructor, int _cantidadModulo, string _descripcion) : Actividad(_id, _idEmpresa, _titulo, _nombreEmpresa, _cantidadAlumnos, _tipo, _descripcion) {
		instructor = _instructor;
		cantidadModulo = _cantidadModulo;
	}

	void guardar() {
		ofstream archivo("Resources/Data/cursos_muestra.txt", ios::app);
		if (archivo.is_open()) {
			archivo << id << '\n';
			archivo << idEmpresa << '\n';
			archivo << titulo << '\n';
			archivo << descripcion << '\n';
			archivo << cantidadAlumnos << '\n';
			archivo.close();
		}
		else {
			cout << "Error al abrir el archivo." << endl;
		}

		fstream archivoOrden("Resources/Data/indices/cursos.txt", ios::binary | ios::out | ios::in);
		if (archivoOrden.is_open()) {
			archivoOrden.seekg(0, ios::end);
			int cantidad = archivoOrden.tellg() / sizeof(CursoIndex);

			auto busqueda = [&](int pos) {
				archivoOrden.seekg(pos * sizeof(int) * 2, ios::beg);
				int idEmpresaAhora;
				archivoOrden.read(reinterpret_cast<char*>(&idEmpresaAhora), sizeof(int));

				return idEmpresa >= idEmpresaAhora;
				};

			int pos = busquedaBinaria(1, cantidad, busqueda);
		}
	}
};