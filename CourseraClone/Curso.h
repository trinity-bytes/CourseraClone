#pragma once
#include "Actividad.h"
#include "Clase.h"
#include "algoritmosBusqueda.h"
#include <fstream>
#include <string>
#include <vector>

class Curso : public Actividad {
private:
	string instructor;
	int cantidadClases;
	LinkedList<Clase> clases;
	string categoria;
	vector<string> requisitos;
	float calificacionPromedio;
	int totalCalificaciones;

public:

	Curso() : Actividad(0,0,"","",0,1,"") {
		instructor = "";
		cantidadClases = 0;
		clases = LinkedList<Clase>();
		categoria = "";
		calificacionPromedio = 0.0f;
		totalCalificaciones = 0;
	}

	Curso(int _id, int _idEmpresa, string _nombreEmpresa, string _titulo, string _descripcion, string _instructor, int _cantidadClases, string _categoria = "") : Actividad(_id, _idEmpresa, _nombreEmpresa, _titulo, 0, 1, _descripcion) {
		instructor = _instructor;
		cantidadClases = _cantidadClases;
		clases = LinkedList<Clase>();
		categoria = _categoria;
		calificacionPromedio = 0.0f;
		totalCalificaciones = 0;
	}

	void anadirClases(string _titulo, string _descripcion) {
		Clase nuevaClase(_titulo, _descripcion);
		clases.agregarAlFinal(nuevaClase);
		cantidadClases++;
	}

	bool modificarClase(int idClase, const string& nuevoContenido) {
		if (idClase < 0 || idClase >= clases.getTamano()) return false;
		
		auto it = clases.begin();
		for (int i = 0; i < idClase; i++) ++it;
		
		it->setDescripcion(nuevoContenido);
		return true;
	}

	bool eliminarClase(int idClase) {
		if (idClase < 0 || idClase >= clases.getTamano()) return false;
		
		auto it = clases.begin();
		for (int i = 0; i < idClase; i++) ++it;
		
		clases.eliminar(it);
		cantidadClases--;
		return true;
	}

	void setCategoria(const string& _categoria) { categoria = _categoria; }
	string getCategoria() const { return categoria; }

	void agregarRequisito(const string& requisito) {
		requisitos.push_back(requisito);
	}

	vector<string> getRequisitos() const { return requisitos; }

	void agregarCalificacion(int calificacion) {
		if (calificacion < 1 || calificacion > 5) return;
		
		calificacionPromedio = (calificacionPromedio * totalCalificaciones + calificacion) / (totalCalificaciones + 1);
		totalCalificaciones++;
	}

	float getCalificacionPromedio() const { return calificacionPromedio; }
	int getTotalCalificaciones() const { return totalCalificaciones; }

	string getInstructor() const { return instructor; }
	int getCantidadClases() const { return cantidadClases; }
	LinkedList<Clase> getClases() const { return clases; }

	int calcularProgreso(const vector<int>& clasesCompletadas) const {
		if (clasesCompletadas.empty()) return 0;
		return (clasesCompletadas.size() * 100) / cantidadClases;
	}

	bool verificarRequisitos(const vector<int>& cursosCompletados) const {
		if (requisitos.empty()) return true;
		
		return true;
	}

	void mostrar() override {
		cout << "Curso: " << titulo << "\n";
		cout << "Empresa: " << nombreEmpresa << "\n";
		cout << "Instructor: " << instructor << "\n";
		cout << "Cantidad de alumnos: " << cantidadAlumnos << "\n";
		cout << "Descripcion: " << descripcion << "\n";
		cout << "Categoría: " << categoria << "\n";
		cout << "Calificación promedio: " << calificacionPromedio << "\n";
		cout << "Total de calificaciones: " << totalCalificaciones << "\n";
	}

	string toString() const {
		stringstream ss;
		ss << idEmpresa << '\n'
		   << tipo << '\n'
		   << nombreEmpresa << '\n'
		   << titulo << '\n'
		   << descripcion << '\n'
		   << instructor << '\n'
		   << cantidadClases << '\n'
		   << categoria << '\n'
		   << calificacionPromedio << '\n'
		   << totalCalificaciones << '\n';
		
		ss << clases.getTamano() << '\n';
		for (const auto& clase : clases) {
			ss << clase.getTitulo() << '\n'
			   << clase.getDescripcion() << '\n';
		}
		
		ss << requisitos.size() << '\n';
		for (const auto& req : requisitos) {
			ss << req << '\n';
		}
		
		return ss.str();
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
};