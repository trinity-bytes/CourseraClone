// filepath: Headers/Entities/Clase.hpp
// Descripcion: Clase que representa una clase individual dentro de un curso

#ifndef COURSERACLONE_ENTITIES_CLASE_HPP
#define COURSERACLONE_ENTITIES_CLASE_HPP

#include <string>

// Clase que representa una clase individual dentro de un curso
class Clase {
private:
    std::string _titulo;
    std::string _contenido;

public:
    Clase() : _titulo(""), _contenido("") {}
    
    Clase(const std::string& _titulo, const std::string& _contenido) 
        : _titulo(_titulo), _contenido(_contenido) {}

    // Getters
    const std::string& getTitulo() const { return _titulo; }
    const std::string& getContenido() const { return _contenido; }
    
    // Setters
    void setTitulo(const std::string& _titulo) { this->_titulo = _titulo; }
    void setContenido(const std::string& _contenido) { this->_contenido = _contenido; }
};

#endif // COURSERACLONE_ENTITIES_CLASE_HPP