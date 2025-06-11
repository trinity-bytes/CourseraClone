// filepath: Headers/Entities/Venta.hpp
// Descripcion: Clase utilitaria para manejo de ventas y pagos

#ifndef COURSERACLONE_ENTITIES_VENTA_HPP
#define COURSERACLONE_ENTITIES_VENTA_HPP

#include "Boleta.hpp"
#include "../DataStructures/LinkedList.hpp"

// Clase utilitaria para procesamiento de ventas
class Venta {
public:
    static inline bool pagarInscripcion(
        int _idInscripcion, 
        int _idActividad, 
        double _precio, 
        LinkedList<Boleta>& _boletas, 
        int _idEstudiante
    ) {
        Boleta b(_idEstudiante, _idActividad, _precio, _idInscripcion);
        b.guardar();
        _boletas.agregarAlFinal(b);
        return true;
    }
};

#endif // COURSERACLONE_ENTITIES_VENTA_HPP
