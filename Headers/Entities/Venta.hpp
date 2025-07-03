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
    static inline void pagarCurso(int idCurso, double precio, int idEstudiante);
    static inline void pagarEspecialidad();
};

inline void Venta::pagarCurso(int idCurso, double precio, int idEstudiante) {
    int nuevoID = FilesManager::getInstance().contarFilasCSV(DataPaths::Financial::DB_COMPROBANTES, false);
    ComprobanteDePago nuevoComprobante(nuevoID, idEstudiante, idCurso, TipoActividad::CURSO, precio);
    nuevoComprobante.guardar();
}

inline void Venta::pagarEspecialidad() {

}

#endif // COURSERACLONE_ENTITIES_VENTA_HPP
