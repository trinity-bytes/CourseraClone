// filepath: Headers/Entities/Clase.hpp
// Header que representa una clase de un curso en el sistema de cursos de CourseraClone

#ifndef COURSERACLONE_ENTITIES_CLASE_HPP
#define COURSERACLONE_ENTITIES_CLASE_HPP

// Headers del sistema
#include <string> // std::string

// Clase que representa una clase individual dentro de un curso
class Clase 
{
private:
	int _ordenClase;
    std::string _titulo;
    std::string _contenido;

public:
    Clase() :_ordenClase(-1), _titulo(""), _contenido("") {}
    
    Clase(
        const int ordenClase, const std::string& titulo, const std::string& contenido
    ) : _ordenClase(ordenClase), _titulo(_titulo), _contenido(_contenido) {}

    // Getters
	int getOrdenClase() const { return _ordenClase; }
    const std::string& getTitulo() const { return _titulo; }
    const std::string& getContenido() const { return _contenido; }
    
    // Setters
	void setOrdenClase(int _ordenClase) { this->_ordenClase = _ordenClase; }
    void setTitulo(const std::string& _titulo) { this->_titulo = _titulo; }
    void setContenido(const std::string& _contenido) { this->_contenido = _contenido; }
};

#endif // COURSERACLONE_ENTITIES_CLASE_HPP