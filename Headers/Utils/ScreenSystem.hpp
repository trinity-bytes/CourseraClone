// filepath: Headers/Utils/ScreenSystem.hpp
// Descripcion: Sistema de gestión de pantallas y navegación

#ifndef COURSERACLONE_UTILS_SCREENSYSTEM_HPP
#define COURSERACLONE_UTILS_SCREENSYSTEM_HPP

// Headers del sistema
#include <string> // std::string

// Headers propios del proyecto
#include "../Types/ScreenTypes.hpp"  // Acciones de pantalla, Pantallas
#include "../Types/UsuarioTypes.hpp" // tipos de usuario

// Clase abstracta base para todas las pantallas del sistema
class PantallaBase 
{
protected:
    bool _esPrimeraVez = true;

	// FUNCIONES DE UTILIDAD

    inline void marcarComoVisitada() 
    { 
        _esPrimeraVez = false; 
    }

    // Helpers para crear resultados
    inline ResultadoPantalla crearResultado(AccionPantalla _accion) const 
    {
        return ResultadoPantalla(_accion);
    }

    inline ResultadoPantalla crearResultado(AccionPantalla _accion, TipoUsuario _user) const 
    {
        return ResultadoPantalla(_accion, _user);
    }

    inline ResultadoPantalla crearResultadoLogin(
        AccionPantalla _accion, 
        const std::string& _email,
        const std::string& _password, 
        TipoUsuario _tipo
    ) const {
        return ResultadoPantalla(_accion, _email, _password, _tipo);
    }

    inline ResultadoPantalla crearResultadoConCurso(AccionPantalla _accion, int _idCurso) const 
    {
        ResultadoPantalla resultado(_accion);        
        resultado.idCursoSeleccionado = _idCurso;
        return resultado;
    }
public:
    explicit inline PantallaBase() {}
    
    virtual inline ~PantallaBase() = default;
    
    // Método principal que debe implementar cada pantalla
    virtual inline ResultadoPantalla ejecutar() = 0;
    
    // Getters
    inline bool esPrimeraVez() const { return _esPrimeraVez; }
};

#endif // COURSERACLONE_UTILS_SCREENSYSTEM_HPP
