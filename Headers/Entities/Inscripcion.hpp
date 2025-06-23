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
#include "../Types/InscripcionTypes.hpp"
#include "../Utils/DataPaths.hpp"

// Clase que representa una inscripción de estudiante a una actividad
class Inscripcion 
{
private:
    int id;
    int idEstudiante;
    int idActividad;
	TipoActividad tipo;
    double progreso;
    bool completado;
    bool estadoPago;

public:
    inline Inscripcion();
    inline Inscripcion(int _idEstudiante, int _idActividad, int _id, TipoActividad _tipo);
    inline Inscripcion(InscripcionBinaria& _bin, int _off);
    inline Inscripcion(RawInscripcionData rawInscripcionData);

	// Getters
	inline int getId() const;
	inline int getIdEstudiante() const;
	inline int getIdActividad() const;
	inline double getProgreso() const;
	inline bool getCompletado() const;
	inline bool getEstadoPago() const;
    inline TipoActividad getTipo() const;

    inline void guardar();

    inline void actualizaPagoEnDisco(int _posicion, bool _estado);
    inline void marcarComoPagada();

    inline RawInscripcionData obtenerDatosCrudos() const;
    inline RawInscripcionElementoDash obtenerElementoDash() const;

    /*
    NOTA IMPORTANTE:
    Esta clase debe interactuar con el ContentManager, FilesManager y Usuarios para realizar las operaciones que necesita.
	No debe contener oeracione mas alla de gestionar inscripciones y su estado.
    */
};

inline Inscripcion::Inscripcion()
    : id(0), idEstudiante(0), idActividad(0),
    progreso(0.0), completado(false), estadoPago(false) {
}
inline Inscripcion::Inscripcion(int _idEstudiante, int _idActividad, int _id, TipoActividad _tipo)
    : id(_id), idEstudiante(_idEstudiante), idActividad(_idActividad), 
    progreso(0.0), completado(false), estadoPago(false), tipo(_tipo)
{

}
inline Inscripcion::Inscripcion(InscripcionBinaria& _bin, int _off)
    : id(_off), idEstudiante(_bin.idEstudiante), idActividad(_bin.idActividad),
    progreso(_bin.progreso), completado(_bin.completado),
    estadoPago(_bin.pagado), tipo(static_cast<TipoActividad>(_bin.tipoActividad))
{

}
inline Inscripcion::Inscripcion(RawInscripcionData rawInscripcionData)
    : id(rawInscripcionData.id), idEstudiante(rawInscripcionData.idEstudiante),
    idActividad(rawInscripcionData.idActividad), progreso(rawInscripcionData.progreso),
    completado(rawInscripcionData.completado), estadoPago(rawInscripcionData.pagado),
    tipo(rawInscripcionData.tipo)
{
}

// Getters
inline int Inscripcion::getId() const {
    return this->id;
}
inline int Inscripcion::getIdEstudiante() const {
	return this->idEstudiante;
}
inline int Inscripcion::getIdActividad() const {
    return this->idActividad;
}
inline double Inscripcion::getProgreso() const {
	return this->progreso;
}
inline bool Inscripcion::getCompletado() const {
    return this->completado;
}
inline bool Inscripcion::getEstadoPago() const {
    return this->estadoPago;
}
inline TipoActividad Inscripcion::getTipo() const {
    return this->tipo;
}

inline void Inscripcion::guardar() {
	FilesManager::getInstance().guardarInscripcionBinaria(InscripcionBinaria(idEstudiante, idActividad, static_cast<int>(tipo), progreso, completado, estadoPago), this->id);
    FilesManager::getInstance().guardarInidiceInscripcion(idEstudiante, this->id);
}

inline void Inscripcion::marcarComoPagada() {
	this->estadoPago = true;
	FilesManager::getInstance().actualizarPagoInscripcion(id, this->estadoPago);
}

inline RawInscripcionData Inscripcion::obtenerDatosCrudos() const {
	RawInscripcionData datos;
	datos.id = this->id;
	datos.idEstudiante = this->idEstudiante;
	datos.idActividad = this->idActividad;
	datos.progreso = this->progreso;
	datos.completado = this->completado;
	datos.pagado = this->estadoPago;
	datos.tipo = this->tipo;
	return datos;
}

inline RawInscripcionElementoDash Inscripcion::obtenerElementoDash() const {
    return RawInscripcionElementoDash{ idActividad, id, tipo };
}


#endif // COURSERACLONE_ENTITIES_INSCRIPCION_HPP