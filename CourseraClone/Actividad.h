#pragma once
#include <string>

class Actividad 
{
protected:
	int id;
	int idEmpresa;
	std::string nombreEmpresa;
	std::string titulo;
	std::string descripcion;
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
		const std::string& _nombreEmpresa, 
		const std::string& _titulo, 
		int _cantidadAlumnos, 
		int _tipo, 
		const std::string& _descripcion
	) : 
		id(_id),
		idEmpresa(_idEmpresa),
		nombreEmpresa(_nombreEmpresa),
		titulo(_titulo),
		cantidadAlumnos(_cantidadAlumnos),
		tipo(_tipo),
		descripcion(_descripcion)
	{}

	virtual ~Actividad() = default;

	void aumentarAlumno(int cantidad) {
		cantidadAlumnos += cantidad;
	}

	// -- Getters --
	int getIdEmpresa() const { return idEmpresa; }
	const std::string& getNombreEmpresa() const { return nombreEmpresa; }
	int getId() const { return id; }
	int getTipo() const { return tipo; }
	int getCantidadAlumnos() const { return cantidadAlumnos; }
	const std::string& getTitulo() const { return titulo; }
	const std::string& getDescripcion() const { return descripcion; }
};