// filepath: Headers/Entities/Venta.hpp
// Descripcion: Clase utilitaria para manejo de ventas y pagos

#ifndef COURSERACLONE_ENTITIES_VENTA_HPP
#define COURSERACLONE_ENTITIES_VENTA_HPP

#include "ComprobanteDePago.hpp"
#include "../Controllers/FilesManager.hpp"

// Clase utilitaria para procesamiento de ventas
class Venta 
{
public:
    static inline int generarId();
    static inline void pagarActividad(int idCurso, double precio, int idEstudiante, TipoActividad tipo);


};

inline int Venta::generarId() {
    return FilesManager::getInstance().contarFilasCSV(DataPaths::Financial::DB_COMPROBANTES, true);
}

inline void Venta::pagarActividad(int idCurso, double precio, int idEstudiante, TipoActividad tipo) {
    int nuevoID = generarId();
    ComprobanteDePago nuevoComprobante(nuevoID, idEstudiante, idCurso, tipo, precio);
    nuevoComprobante.guardar();
}
#endif // COURSERACLONE_ENTITIES_VENTA_HPP
