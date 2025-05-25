#pragma once

// headers propios
#include "Actividad.h"
#include "algoritmosBusqueda.h"
#include "Venta.h"

// headers de la libreria estandar
#include "fstream"
#include "iostream"

using namespace std;

struct InscripcionIndex 
{
    int idUsuario;
    int offset;

    InscripcionIndex(int _idUsuario, int _offset) : idUsuario(_idUsuario), offset(_offset) {}
    InscripcionIndex() : idUsuario(0), offset(0) {}
};

struct InscripcionBinaria 
{
    int idEstudiante;
    int idActividad;
    int tipoActividad;
    double progreso;
    bool completado;
    bool pagado;

    InscripcionBinaria(int _idUsuario, int _idActividad, int _tipoActividad, double _progreso, bool _completado, bool _pagado)
        : idEstudiante(_idUsuario), idActividad(_idActividad), tipoActividad(_tipoActividad), progreso(_progreso), completado(_completado), pagado(_pagado) {
    }
    InscripcionBinaria() : idEstudiante(0), idActividad(0), tipoActividad(0), progreso(0.0), completado(false), pagado(false) {};
};

class Inscripcion {
private:
    int id;
    int idEstudiante;
    Actividad* actividad;
    double progreso;
    bool completado;
    bool pagado;

public:
    Inscripcion() : id(0), idEstudiante(0), actividad(nullptr), progreso(0.0), completado(false), pagado(false) {}

    Inscripcion(int _idEstudiante, Actividad* _actividad)
        : idEstudiante(_idEstudiante), actividad(_actividad),
        progreso(0.0), completado(false), pagado(false)
    {
        ifstream archivo("Resources/Data/inscripciones.dat", ios::binary | ios::ate); 
        
        streamoff peso = archivo.tellg();
        id = int(peso / sizeof(InscripcionBinaria));
        archivo.close();
    }

    Inscripcion(InscripcionBinaria& bin, Actividad* act, int off)
        : idEstudiante(bin.idEstudiante),
        actividad(act),
        progreso(bin.progreso),
        completado(bin.completado),
        pagado(bin.pagado),
        id(off)
    {
    }

	

    void guardar() {
        ofstream archivo("Resources/Data/inscripciones.dat", ios:: binary | ios::app);
        int offsetRegistro = 0;
        if (archivo.is_open()) 
        {
            InscripcionBinaria nuevo(idEstudiante, actividad->getId(), 
                actividad->getTipo(), progreso, completado, pagado);

            archivo.seekp(0, ios::end);
            offsetRegistro = int((archivo.tellp() / sizeof(InscripcionBinaria)));

            archivo.write(reinterpret_cast<char*>(&nuevo), sizeof(nuevo));
            archivo.close();
        }
        
        fstream archivoOrden("Resources/Data/indices/inscripciones.dat", ios::binary | ios::in | ios::out);

        if (archivoOrden.is_open()) 
        {
            archivoOrden.seekg(0, ios::end);
            int cantidad = archivoOrden.tellg() / sizeof(InscripcionIndex);
            InscripcionIndex nuevo(idEstudiante, offsetRegistro);

            if (cantidad == 0) {
                archivoOrden.seekp(0, ios::beg);
                archivoOrden.write(reinterpret_cast<char*>(&nuevo), sizeof(InscripcionIndex));
                archivoOrden.close();
                return;
            }

            archivoOrden.seekg(0, ios::beg);
            auto busqueda = [&](int pos) {
                InscripcionIndex temp;
                archivoOrden.seekg(pos * sizeof(InscripcionIndex), ios::beg);
                archivoOrden.read(reinterpret_cast<char*>(&temp), sizeof(InscripcionIndex));

                return idEstudiante <= temp.idUsuario;
                };


            int pos = busquedaBinaria(0, cantidad - 1, busqueda);

            for (int i = cantidad - 1; i >= pos; --i) {
                InscripcionIndex temp;
                archivoOrden.seekg(i * sizeof(InscripcionIndex), ios::beg);
                archivoOrden.read(reinterpret_cast<char*>(&temp), sizeof(InscripcionIndex));
                archivoOrden.seekp((i + 1) * sizeof(InscripcionIndex), ios::beg);
                archivoOrden.write(reinterpret_cast<char*>(&temp), sizeof(InscripcionIndex));
            }

            
            archivoOrden.seekp(pos * sizeof(InscripcionIndex), ios::beg);
            archivoOrden.write(reinterpret_cast<char*>(&nuevo), sizeof(InscripcionIndex));
            
            archivoOrden.close();
        }
    }

	int getIdEstudiante() {
		return idEstudiante;
	}

    // Funcion critica
    void actualizaPagoEnDisco(int posicion, bool estado) {
        fstream archivo("Resources/Data/inscripciones.dat", ios::binary | ios::in | ios::out);
        if (!archivo) throw runtime_error("Error en el archivo");
        archivo.seekp(posicion * sizeof(InscripcionBinaria) + offsetof(InscripcionBinaria, pagado),
            ios::beg);
        archivo.write(reinterpret_cast<char*>(&estado), sizeof(estado));
    }

    bool estaPagada() const { return pagado; }

    void marcarComoPagada(LinkedList<Boleta>& boletas) { 
        if (!estaPagada()) {
            pagado = true;
            //actualizaPagoEnDisco(id, pagado);
            Venta prueba;
            prueba.pagarInscripcion(id, getIdActividad(), 20.5, boletas, idEstudiante);
        }
    }
	int getIdActividad() {
		return actividad->getId();
	}
	int getId() {
		return id;
	}
    void mostrar() {
		cout << "ID Estudiante: " << idEstudiante << endl;
		cout << "ID Actividad: " << actividad->getId() << endl;
		cout << "Progreso: " << progreso << endl;
		cout << "Completado: " << (completado ? "S�" : "No") << endl;
		cout << "Pagado: " << (pagado ? "S�" : "No") << endl;
    }
};