// filepath: Headers/Entities/Inscripcion.hpp
// Descripcion: Clase que representa una inscripción de estudiante a una actividad

#ifndef COURSERACLONE_ENTITIES_INSCRIPCION_HPP
#define COURSERACLONE_ENTITIES_INSCRIPCION_HPP

// Headers de la libreria estandar
#include <iostream>
#include <memory> // Para std::shared_ptr

// Headers propios
#include "Actividad.hpp"
#include "Venta.hpp"
#include "../Controllers/FilesManager.hpp"
#include "../Persistence/InscripcionTypes.hpp"
#include "../Utils/DataPaths.hpp"

// Clase que representa una inscripción de estudiante a una actividad
class Inscripcion 
{
private:
    int _id;
    int _idEstudiante;
    int _idActividad;
    double _progreso;
    bool _completado;
    bool _estadoPago;

public:
    inline Inscripcion();
    inline Inscripcion(int idEstudiante, int idActividad);
    inline Inscripcion(InscripcionBinaria& _bin, Actividad* _act, int _off);

	// Getters
	inline int getId() const;
	inline int getIdEstudiante() const;
	inline int getIdActividad() const;
	inline double getProgreso() const;
	inline bool getCompletado() const;
	inline bool getEstadoPago() const;

    inline void guardar();

    inline void actualizaPagoEnDisco(int _posicion, bool _estado);
    inline void marcarComoPagada();

    inline RawInscripcionData obtenerDatosCrudos() const;

    /*
    NOTA IMPORTANTE:
    Esta clase debe interactuar con el ContentManager, FilesManager y Usuarios para realizar las operaciones que necesita.
	No debe contener oeracione mas alla de gestionar inscripciones y su estado.
    */
};

#endif // COURSERACLONE_ENTITIES_INSCRIPCION_HPP