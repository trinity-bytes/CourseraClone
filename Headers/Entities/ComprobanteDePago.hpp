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
#include "../Controllers/FilesManager.hpp"
#include "../Utils/DateTime.hpp"

// Clase que representa una boleta de pago
class ComprobanteDePago{
private:
    int _id;
    int _idEstudiante;
	int _idActividad; // Curso o Especialidad
    TipoActividad _tipoActividad;
    std::string _fechaEmision; 
	std::string _horaEmision;
    double _montoPagado;

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
        double montoPagado
    );

    void guardar();
    RawComprobanteData obtenerDatosCrudosComprobante();
    
    // Método para establecer fecha personalizada (útil para datos de ejemplo)
    inline void establecerFechaEmision(const std::string& fecha) {
        _fechaEmision = fecha;
    }

    bool operator<(ComprobanteDePago& otro);
};

ComprobanteDePago::ComprobanteDePago() : 
    _id(0),              
    _idEstudiante(0), 
    _idActividad(0), 
    _tipoActividad(TipoActividad::DEFAULT), 
    _montoPagado(0.0)
{}

ComprobanteDePago::ComprobanteDePago(
    int id,
    int idEstudiante,
    int idActividad,
    TipoActividad tipoActividad,
    double montoPagado
    ) : _id(id),
    _idEstudiante(idEstudiante),
    _idActividad(idActividad),
    _tipoActividad(tipoActividad), 
    _fechaEmision(obtenerFechaActual()), 
    _horaEmision(obtenerHoraActual()), 
    _montoPagado(montoPagado)
{}

// Permiter ordenar en caso de error automatico
bool ComprobanteDePago::operator<( ComprobanteDePago& otro) {
    RawComprobanteData da = this->obtenerDatosCrudosComprobante();
    auto db = otro.obtenerDatosCrudosComprobante();
    return da.fechaEmision < db.fechaEmision;
}

// ---- Funciones privadas ----
std::string ComprobanteDePago::obtenerFechaActual(){
    return DateTime::now().toIsoDateString();
}

std::string ComprobanteDePago::obtenerHoraActual(){
    return DateTime::now().toTimeString();
}

// ---- Funciones publicas ----
inline void ComprobanteDePago::guardar(){
	// ToDo: Implementar la logica para guardar el comprobante de pago en un archivo
    RawComprobanteData datosCrudos = obtenerDatosCrudosComprobante();

    // Convert RawComprobanteData to a string format suitable for FilesManager::generarComprobantePago  
    std::stringstream ss;
    ss << datosCrudos.id << "|"
        << datosCrudos.idEstudiante << "|"
        << datosCrudos.idActividad << "|"
        << static_cast<int>(datosCrudos.tipoActividad) << "|"
        << datosCrudos.fechaEmision << "|"
        << datosCrudos.horaEmision << "|"
        << datosCrudos.montoPagado << "|";

    std::string datosComprobante = ss.str();
    auto resultado = FilesManager::getInstance().generarComprobantePago(_id, datosComprobante);
    if (resultado == FileOperationResult::SUCCESS) {
        std::cout << "Comprobante guardado correctamente." << std::endl;
    }
    else {
        std::cerr << "Error al guardar el comprobante: " << obtenerMensaje(resultado) << std::endl;
    }

}

inline RawComprobanteData ComprobanteDePago::obtenerDatosCrudosComprobante(){
    RawComprobanteData data;

    data.id = _id;
    data.idEstudiante = _idEstudiante;
    data.idActividad = _idActividad;
    data.tipoActividad = _tipoActividad;
    data.fechaEmision = _fechaEmision.empty() ? obtenerFechaActual() : _fechaEmision;
    data.horaEmision = _horaEmision.empty() ? obtenerHoraActual() : _horaEmision;
    data.montoPagado = _montoPagado;

    return data;
}

#endif // COURSERACLONE_ENTITIES_BOLETA_HPP