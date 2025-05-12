#pragma once
#include <iostream>
#include "Boleta.h"
#include "LinkedList.h"

class Venta {


public:

    bool pagarInscripcion(int idInscripcion, int idActividad, double precio, LinkedList<Boleta*>& boletas, int idEstudiante) {
        Boleta* b = new Boleta(idEstudiante, idActividad, precio);
        b->guardar();
        boletas.agregarAlFinal(b);
        return true;
    }

};
