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

	// getters
	string getTitulo() const { return titulo; }
	string getContenido() const { return contenido; }
	// setters
	void setTitulo(const string& _titulo) { titulo = _titulo; }
	void setContenido(const string& _contenido) { contenido = _contenido; }
};