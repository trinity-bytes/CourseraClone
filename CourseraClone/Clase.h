#pragma once

class Clase
{
private:
	string titulo, contenido;
public:
	Clase() : titulo(""), contenido("") {}
	Clase(
		string _titulo, 
		string _contenido
	) : titulo(_titulo), 
		contenido(_contenido) 
	{}

	string getTitulo() const { return titulo; }
	string getContenido() const { return contenido; }
};