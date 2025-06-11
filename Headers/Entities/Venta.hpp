#pragma once
#include "Boleta.hpp"
#include "../DataStructures/LinkedList.h"

class Venta 
{
public:
    static inline bool pagarInscripcion(
        int idInscripcion, 
        int idActividad, 
        double precio, 
        LinkedList<Boleta>& boletas, 
        int idEstudiante
    ) {
        Boleta b(idEstudiante, idActividad, precio, idInscripcion);
        b.guardar();
        boletas.agregarAlFinal(b);
        return true;
    }
};
