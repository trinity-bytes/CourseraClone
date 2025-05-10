#pragma once

// headers propios
#include "Actividad.h"
#include "Clase.h"
#include "LinkedList.h"
#include "algoritmosBusqueda.h"

// headers de la libreria estandar
#include "iostream"    // Para manejo de entrada/salida
#include "fstream"     // Para manejo de archivos
#include "string"      // Para manejo de cadenas
#include "vector"      // Para manejo de vectores
#include "sstream"     // Para manejo de cadenas
#include "functional"  // Para uso de funciones lambda

using namespace std;

class Curso : public Actividad 
{
private:
    // Atributos principales
    string instructor;
    string categoria;
    float calificacionPromedio;
    int totalCalificaciones;
    int cantidadClases;

    // Colecciones
    LinkedList<Clase> clases;
    vector<string> requisitos;

    // Ruta del archivo para persistencia
    const string RUTA_ARCHIVO = "Resources/Data/actividades.txt";

public:
    // Constructores
    Curso() :
        Actividad(0, 0, "", "", 0, 1, ""),
        instructor(""),
        cantidadClases(0),
        categoria(""),
        calificacionPromedio(0.0f),
        totalCalificaciones(0) {
    }

    Curso(
        int _id,
        int _idEmpresa,
        const string& _nombreEmpresa,
        const string& _titulo,
        const string& _descripcion,
        const string& _instructor,
        int _cantidadClases,
        const string& _categoria = ""
    ) :
        Actividad(_id, _idEmpresa, _nombreEmpresa, _titulo, 0, 1, _descripcion),
        instructor(_instructor),
        cantidadClases(_cantidadClases),
        categoria(_categoria),
        calificacionPromedio(0.0f),
        totalCalificaciones(0) {
    }

    // Getters
    string getInstructor() const { return instructor; }
    int getCantidadClases() const { return cantidadClases; }
    LinkedList<Clase> getClases() const { return clases; }
    string getCategoria() const { return categoria; }
    vector<string> getRequisitos() const { return requisitos; }
    float getCalificacionPromedio() const { return calificacionPromedio; }
    int getTotalCalificaciones() const { return totalCalificaciones; }

    // Setters
    void setCategoria(const string& _categoria) { categoria = _categoria; }

    // Métodos para gestión de clases
    void anadirClases(const string& _titulo, const string& _descripcion) {
        Clase nuevaClase(_titulo, _descripcion);
        clases.agregarAlFinal(nuevaClase);
        cantidadClases++;
    }

    bool modificarClase(int idClase, const string& nuevoContenido) {
        if (idClase < 0 || idClase >= clases.getTamano())
            return false;

        auto it = clases.begin();
        advance(it, idClase);
        it->setContenido(nuevoContenido);
        return true;
    }

    bool eliminarClase(int idClase) {
        if (idClase < 0 || idClase >= clases.getTamano())
            return false;

        auto it = clases.begin();
        advance(it, idClase);
        clases.eliminar(it);
        cantidadClases--;
        return true;
    }

    // Métodos para requisitos
    void agregarRequisito(const string& requisito) {
        requisitos.push_back(requisito);
    }

    // Métodos para calificaciones
    void agregarCalificacion(int calificacion) {
        if (calificacion < 1 || calificacion > 5)
            return;

        float sumaTotal = calificacionPromedio * totalCalificaciones + calificacion;
        totalCalificaciones++;
        calificacionPromedio = sumaTotal / totalCalificaciones;
    }

    // Métodos para cálculos
    int calcularProgreso(const vector<int>& clasesCompletadas) const {
        if (clasesCompletadas.empty() || cantidadClases == 0)
            return 0;
        return (clasesCompletadas.size() * 100) / cantidadClases;
    }

    bool verificarRequisitos(const vector<int>& cursosCompletados) const {
        // NOTA: Este método está incompleto en el código original
        return requisitos.empty() || true;
    }

    // Métodos de visualización y serialización
    void mostrar() const {
        cout << "=== INFORMACIÓN DEL CURSO ===" << endl;
        cout << "Curso: " << titulo << endl;
        cout << "Empresa: " << nombreEmpresa << endl;
        cout << "Instructor: " << instructor << endl;
        cout << "Cantidad de alumnos: " << cantidadAlumnos << endl;
        cout << "Descripción: " << descripcion << endl;
        cout << "Categoría: " << categoria << endl;
        cout << "Calificación: " << calificacionPromedio << " (" << totalCalificaciones << " opiniones)" << endl;
        cout << "===========================" << endl;
    }

    string toString() const {
        stringstream ss;

        // Datos básicos
        ss << idEmpresa << '\n'
            << tipo << '\n'
            << nombreEmpresa << '\n'
            << titulo << '\n'
            << descripcion << '\n'
            << instructor << '\n'
            << cantidadClases << '\n'
            << categoria << '\n'
            << calificacionPromedio << '\n'
            << totalCalificaciones << '\n';

        // Serialización de clases
        ss << clases.getTamano() << '\n';
        for (const auto& clase : clases) {
            ss << clase.getTitulo() << '\n'
                << clase.getContenido() << '\n';
        }

        // Serialización de requisitos
        ss << requisitos.size() << '\n';
        for (const auto& req : requisitos) {
            ss << req << '\n';
        }

        return ss.str();
    }

    // Método para persistencia
    bool guardar() {
        ofstream archivo(RUTA_ARCHIVO, ios::app);
        if (!archivo.is_open()) {
            cerr << "Error: No se pudo abrir el archivo " << RUTA_ARCHIVO << endl;
            return false;
        }

        // Guardar datos básicos
        archivo << getIdEmpresa() << '\n'
            << getTipo() << '\n'
            << getNombreEmpresa() << '\n'
            << titulo << '\n'
            << getDescripcion() << '\n'
            << instructor << '\n';

        // Definir funciones lambda para extraer datos
        function<string(const Clase&)> conseguirTitulo = [](const Clase& c) {
            return c.getTitulo();
            };

        function<string(const Clase&)> conseguirDescripcion = [](const Clase& c) {
            return c.getContenido();
            };

        // Extraer datos de clases
        vector<string> titulos = clases.extraerDato<string>(conseguirTitulo);
        vector<string> descripciones = clases.extraerDato<string>(conseguirDescripcion);

        // Guardar clases
        archivo << clases.getTamano() << '\n';
        for (size_t i = 0; i < clases.getTamano(); i++) {
            archivo << titulos[i] << '\n'
                << descripciones[i] << '\n';
        }

        archivo.close();
        return true;
    }
};