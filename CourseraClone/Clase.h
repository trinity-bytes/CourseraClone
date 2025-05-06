#pragma once
#include <iostream>
using namespace std;


class Clase {
private:
	string titulo;
	string actividad;

public:
	Clase() : titulo(""), actividad("") {}
	Clase(string _titulo, string _actividad) : titulo(_titulo), actividad(_actividad) {}

	string getTitulo() const {
		return titulo;
	}
	string getDescripcion() const {
		return actividad;
	}
};