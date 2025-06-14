// filepath: Headers/Entities/Boleta.hpp
// Descripcion: Clase que representa una boleta de pago en el sistema

#ifndef COURSERACLONE_ENTITIES_BOLETA_HPP
#define COURSERACLONE_ENTITIES_BOLETA_HPP

// Headers estandar
#include <iostream> // std::cout, std::endl
#include <string>   // std::string
#include <ctime>    // time_t, tm, localtime
#include <fstream>  // std::ofstream, std::fstream

// Headers propios
#include "../Types/ComprobanteDePagoTypes.hpp"
#include "../Types/ActividadTypes.hpp"

// Clase que representa una boleta de pago
class ComprobanteDePago
{
private:
    int _id;
    int _idEstudiante;
	int _idActividad; // Curso o Especialidad
    TipoActividad _tipoActividad;
    std::string _fechaEmision; 
	std::string _horaEmision;
    double _montoPagado;
	MetodoDePago _metodoPago;

	// ---- Funciones privadas ----
    std::string obtenerFechaActual();
    std::string obtenerHoraActual();
public:
    ComprobanteDePago();
    ComprobanteDePago(
        int id, 
        int idEstudiante, 
        int idActividad, 
        TipoActividad tipoActividad, 
        const std::string& fecha, 
        const std::string& hora, 
        double montoPagado, 
        MetodoDePago metodoPago
    );

    void guardar();
    RawComprobanteData obtenerDatosCrudosComprobante();
};

ComprobanteDePago::ComprobanteDePago() : 
    _id(0),              
    _idEstudiante(0), 
    _idActividad(0), 
    _tipoActividad(TipoActividad::DEFAULT), 
    _fechaEmision(0), 
    _horaEmision(0), 
    _montoPagado(0.0), 
    _metodoPago(MetodoDePago::DEFAULT) 
{}

ComprobanteDePago::ComprobanteDePago(
    int id, 
    int idEstudiante, 
    int idActividad, 
    TipoActividad tipoActividad, 
    const std::string& fecha, 
    const std::string& hora, 
    double montoPagado, 
    MetodoDePago metodoPago
) : _id(id), 
    _idEstudiante(idEstudiante), 
    _idActividad(idActividad), 
    _tipoActividad(tipoActividad), 
    _fechaEmision(fecha), 
    _horaEmision(hora), 
    _montoPagado(montoPagado), 
    _metodoPago(metodoPago) 
{}

// ---- Funciones privadas ----
std::string ComprobanteDePago::obtenerFechaActual()
{
    time_t t = time(nullptr);
    tm tm = localtime(&t)[0];
    std::string fecha;
    auto agregar = [&](int _valor) {
        if (_valor < 10) fecha += '0';
        fecha += std::to_string(_valor);
        };

    agregar(tm.tm_year + 1900); // Años desde 1900
    fecha += '-';
    agregar(tm.tm_mon + 1); // Meses desde 0
    fecha += '-';
    agregar(tm.tm_mday);
    return fecha;
}

std::string ComprobanteDePago::obtenerHoraActual()
{
    time_t t = time(nullptr);
    tm tm = localtime(&t)[0];
    std::string hora;
    auto agregar = [&](int _valor) {
        if (_valor < 10) hora += '0';
        hora += std::to_string(_valor);
        };
    agregar(tm.tm_hour);
    hora += ':';
    agregar(tm.tm_min);
    hora += ':';
    agregar(tm.tm_sec);
    return hora;
}

// ---- Funciones publicas ----
inline void ComprobanteDePago::guardar()
{
	// ToDo: Implementar la logica para guardar el comprobante de pago en un archivo
}

inline RawComprobanteData ComprobanteDePago::obtenerDatosCrudosComprobante()
{
    RawComprobanteData data;

    data.id = _id;
    data.idEstudiante = _idEstudiante;
    data.idActividad = _idActividad;
    data.tipoActividad = _tipoActividad;
    data.fechaEmision = _fechaEmision.empty() ? obtenerFechaActual() : _fechaEmision;
    data.horaEmision = _horaEmision.empty() ? obtenerHoraActual() : _horaEmision;
    data.montoPagado = _montoPagado;
    data.metodoPago = _metodoPago;

    return data;
}
#endif // COURSERACLONE_ENTITIES_BOLETA_HPP