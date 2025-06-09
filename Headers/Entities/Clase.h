#pragma once

class Clase
{
private:
	std::string titulo, contenido;
public:
	Clase() : titulo(""), contenido("") {}
	Clase(
		std::string _titulo,
		std::string _contenido
	) : titulo(_titulo), 
		contenido(_contenido) 
	{}

	// getters
	std::string getTitulo() const { return titulo; }
	std::string getContenido() const { return contenido; }
	// setters
	void setTitulo(const std::string& _titulo) { titulo = _titulo; }
	void setContenido(const std::string& _contenido) { contenido = _contenido; }
};