#pragma once
#include "string"

using namespace std;

class Actividad {
protected:
	int id;
	int idEmpresa;
	string nombreEmpresa;
	string titulo;
	string descripcion;
	int cantidadAlumnos;
	int tipo;

public:
	Actividad() : 
		id(0), 
		idEmpresa(0), 
		nombreEmpresa(""), 
		titulo(""), 
		descripcion(""), 
		cantidadAlumnos(0), 
		tipo(0) 
	{}

	Actividad(
		int _id, 
		int _idEmpresa, 
		string _nombreEmpresa, 
		string _titulo, 
		int _cantidadAlumnos, 
		int _tipo, 
		string _descripcion
	) {
		this->id = _id;
		this->idEmpresa = _idEmpresa;
		this->nombreEmpresa = _nombreEmpresa;
		this->titulo = _titulo;
		this->cantidadAlumnos = _cantidadAlumnos;
		this->tipo = _tipo;
		this->descripcion = _descripcion;
	}

	virtual ~Actividad() {}

	void aumentarAlumno(int cantidad) {
		cantidadAlumnos += cantidad;
	}

	// -- Getters --
	int getIdEmpresa() const { return idEmpresa; }
	string getNombreEmpresa() const { return nombreEmpresa; }
	int getId() const { return id; }
	int getTipo() const { return tipo; }
	int getCantidadAlumnos() const { return cantidadAlumnos; }
	string getTitulo() const { return titulo; }
	string getDescripcion() const { return descripcion; }
};