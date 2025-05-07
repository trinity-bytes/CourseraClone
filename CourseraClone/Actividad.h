#pragma once
#include <iostream>
using namespace std;

class Actividad 
{
protected:
	int id;
	int idEmpresa;
	string nombreEmpresa;
	string titulo;
	string descripcion;
	int cantidadAlumnos;
	int tipo;

public:
	Actividad() : id(0), idEmpresa(0), nombreEmpresa(""), titulo(""), descripcion(""), cantidadAlumnos(0), tipo(0) {}
	Actividad(int _id, int _idEmpresa, string _nombreEmpresa, string _titulo, int _cantidadAlumnos, int _tipo, string _descripcion) {
		id = _id;
		idEmpresa = _idEmpresa;
		nombreEmpresa = _nombreEmpresa;
		titulo = _titulo;
		cantidadAlumnos = _cantidadAlumnos;
		tipo = _tipo;
		descripcion = _descripcion;
	}

	// Add a virtual destructor to make the class polymorphic
	virtual ~Actividad() {}

	void aumentarAlumno(int cantidad) {
		cantidadAlumnos += cantidad;
	}

	int getIdEmpresa() const {
		return idEmpresa;
	}

	string getNombreEmpresa() const {
		return nombreEmpresa;
	}

	int getId() const {
		return id;
	}

	int getTipo() const {
		return tipo;
	}

	int getCantidadAlumnos() const {
		return cantidadAlumnos;
	}

	string getTitulo() const {
		return titulo;
	}

	string getDescripcion() const {
		return descripcion;
	}
};