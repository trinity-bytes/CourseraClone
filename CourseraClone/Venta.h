#pragma once
#include "Boleta.h"

class Venta {
private:
    int idVenta;
    int idEstudiante;
    int idActividad;
    double precio;
    bool pagado;

public:

    Venta(int _idVenta, int _idEstudiante, int _idActividad, double _precio, bool _pagado)
        : idVenta(_idVenta), idEstudiante(_idEstudiante), idActividad(_idActividad), precio(_precio), pagado(_pagado) { }

    Venta() : idVenta(0), idEstudiante(0), idActividad(0), precio(0.0), pagado(false) { }

    void pagar() {
        if (!pagado) {
            pagado = true;
            generarBoleta();
        }
    }

private:

    void generarBoleta() {
        int siguienteBoletaId = 1;
        Boleta b(siguienteBoletaId++,
            idEstudiante,
            idActividad,
            precio);
        b.guardar();
    }
};
