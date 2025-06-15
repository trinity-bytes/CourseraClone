// filepath: Headers/Entities/Especializacion.hpp
// Header para la clase Especializacion que representa una especialización compuesta por varios cursos

#ifndef COURSERACLONE_ENTITIES_ESPECIALIZACION_HPP
#define COURSERACLONE_ENTITIES_ESPECIALIZACION_HPP

// Includes del sistema y de la STL
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>

// Includes propios del proyecto
#include "Actividad.hpp"
#include "../Types/ActividadTypes.hpp"

// Clase que representa una especialización compuesta por varios cursos
class Especializacion : public Actividad 
{
private:
    std::vector<int> _idsCursos;
	int _duracionEstimada; // Duración estimada en semanas

public:
    Especializacion() : Actividad(0, 0, "", CategoriaActividad::DEFAULT, "", ""), 
		_idsCursos(),
        _duracionEstimada(0)
    {}

    Especializacion(
        int id,
        int idEmpresa,
        const std::string& nombreEmpresa,
        CategoriaActividad categoria,
        const std::string& titulo,
        const std::string& descripcion,
		const std::vector<int>& idsCursos,
        int duracionEstimada
    ) : Actividad(id, idEmpresa, nombreEmpresa, categoria, titulo, descripcion), 
        _idsCursos(idsCursos), 
        _duracionEstimada(duracionEstimada) 
    {}

    // Getters
	std::vector<int> getIdsCursos() const { return _idsCursos; }
    int getDuracionEstimada() const { return _duracionEstimada; }

	// Setters
    void setIdsCursos(const std::vector<int>& idsCursos) { _idsCursos = idsCursos; }
	void setDuracionEstimada(int duracionEstimada) { _duracionEstimada = duracionEstimada; }
	// Sobrescribir método virtual de Actividad
	RawEspecializacionData obtenerDatosCrudosEspecialidad() 
    {
        RawEspecializacionData datos;
        
        datos.id = this->getId();
        datos.idEmpresa = this->getIdEmpresa();
        datos.nombreEmpresa = this->getNombreEmpresa();
        datos.categoria = this->getCategoria();
        datos.titulo = this->getTitulo();
        datos.descripcion = this->getDescripcion();
        datos.idsCursos = this->_idsCursos;
        datos.duracionEstimada = this->_duracionEstimada;
        
        return datos;
	}

    bool guardar() override
    {
		// ToDo: Implementar lógica para guardar la especialización en un archivo
        return true;
    }
};

#endif // COURSERACLONE_ENTITIES_ESPECIALIZACION_HPP