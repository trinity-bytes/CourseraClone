// Descripcion: Clase que representa una empresa en el sistema

#ifndef COURSERACLONE_ENTITIES_EMPRESA_HPP
#define COURSERACLONE_ENTITIES_EMPRESA_HPP

// Librerías del sistema
#include <iostream>
#include <vector>

// Librerias propias del proyecto
#include "Usuario.hpp"
#include "../Controllers/ContentManager.hpp"

// Clase que representa una empresa usuaria del sistema
class Empresa : public Usuario
{
private:
    // Atributos privados
    std::vector<int> _idsEspecializaciones;
    std::vector<int> _idsCursos;

public:
    // Constructores
    inline Empresa();
    inline Empresa(
        int id,
        TipoUsuario tipoUsuario,
        const std::string& nombreCompleto,
        const std::string& username,
        const std::string& contrasenaHash
    );

    /*
	NOTA IMPORTANTE: Usar el gestor de contenido para mnejar la 
    creacion, edicion y eliminacion de cursos y especializaciones.
	Esto permite mantener la integridad de los datos y facilita la gestion de los mismos.
	Además, el gestor de contenido se encarga de cargar los datos desde el archivo correspondiente.
    */

	// Getters
	inline const std::vector<int>& getIdsEspecializaciones() const { return _idsEspecializaciones; }
	inline const std::vector<int>& getIdsCursos() const { return _idsCursos; }

	// Setters
	inline void setIdsEspecializaciones(const std::vector<int>& _ids) { _idsEspecializaciones = _ids; }
	inline void setIdsCursos(const std::vector<int>& _ids) { _idsCursos = _ids; }

    // Métodos de gestión de datos
    inline void cargarDatos();
    inline void reset();

    // Métodos de gestión de cursos
    inline bool crearCurso(const Curso& _nuevoCurso);
    inline bool eliminarCurso(int _idCurso);

    // Métodos de gestión de especializaciones
    inline bool crearEspecializacion(const Especializacion& _nuevaEspecializacion);
    inline bool eliminarEspecializacion(int _idEspecializacion);

    // Métodos de gestión de cursos en especializaciones
    inline bool anadirCursoAEspecializacion(int _idEspecializacion, Curso& _curso);
    inline bool eliminarCursoDeEspecializacion(int _idEspecializacion, int _idCurso);

    // Métodos de consulta
    inline void mostrarProfesores() const;
    inline int obtenerCantidadCursos() const;
    inline int obtenerCantidadEspecializaciones() const;
    inline bool tieneCurso(int _idCurso) const;
    inline bool tieneEspecializacion(int _idEspecializacion) const;
};

// --- IMPLEMENTACIONES ---

inline Empresa::Empresa() : Usuario(), _idsEspecializaciones(), _idsCursos()
{
    cargarDatos();
}

inline Empresa::Empresa(
    int id,
    TipoUsuario tipoUsuario,
    const std::string& nombreCompleto,
    const std::string& username,
    const std::string& contrasena
) : Usuario(id, TipoUsuario::EMPRESA, nombreCompleto, username, contrasena), _idsEspecializaciones(), _idsCursos()
{
    cargarDatos();
}

#endif // COURSERACLONE_ENTITIES_EMPRESA_HPP
