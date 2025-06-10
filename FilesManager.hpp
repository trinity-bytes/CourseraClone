// filepath: Headers/Controllers/FileManager.hpp
// description: Este archivo define la clase FileManager, 
//				que se encarga de gestionar archivos en el sistema.

#ifndef HEADER_CONTROLLERS_FILEMANAGER_HPP
#define HEADER_CONTROLLERS_FILEMANAGER_HPP

// Headers estándar
#include <string>    // Para uso de std::string
#include <fstream>   // Para manejo de archivos
#include <vector>    // Para uso de vector

// Headers propios
#include "CourseManager.hpp"

class FileManager
{
private:
    // 
    const std::string RUTA_ACTIVIDADES = "Resources/Data/actividades.txt";
    const std::string RUTA_INSCRIPCIONES = "Resources/Data/inscripciones.dat";

    // constantes
    const int TIPO_CURSO = 1;
    const int TIPO_ESPECIALIZACION = 2;

public:
	FileManager();
	~FileManager();

    void cargarDatosArchivo();
    void cargarDatosInscripciones();
};

FileManager::FileManager()
{
}

FileManager::~FileManager() {}

// Carga datos de actividades desde archivo de texto
void FileManager::cargarDatosCourseManager()
{
    std::ifstream archivo(RUTA_ACTIVIDADES);

	if (!archivo.is_open()) // Verifica si el archivo se pudo abrir
    {
        throw std::runtime_error("No se pudo abrir el archivo de actividades: " + RUTA_ACTIVIDADES);
    }

    std::string nombreEmpresa, titulo, descripcion, instructor, tituloActividad, descripcionActividad;
    int cantidad = 0;
    int tipo, idEmpresa;

    while (archivo >> idEmpresa) {
        archivo.ignore();
        archivo >> tipo;
        archivo.ignore();
        getline(archivo, nombreEmpresa);
        getline(archivo, tituloActividad);
        getline(archivo, descripcionActividad);

        if (tipo == TIPO_CURSO) {
            // Procesar curso
            getline(archivo, instructor);
            int cantidadClase = 0;
            archivo >> cantidadClase;
            archivo.ignore();

            std::vector<std::string> titulos(cantidadClase), descripciones(cantidadClase);
            for (int i = 0; i < cantidadClase; i++) {
                getline(archivo, titulo);
                getline(archivo, descripcion);
                titulos[i] = titulo;
                descripciones[i] = descripcion;
            }

            if (!_gestionadorCursos->crearCurso(idEmpresa, tituloActividad, nombreEmpresa, cantidadClase, instructor, descripcionActividad, titulos, descripciones)) {
                throw runtime_error("Error al crear curso: " + tituloActividad);
            }
        }
        else if (tipo == TIPO_ESPECIALIZACION) {
            // Procesar especialización
            int cantidadCursos = 0;
            archivo >> cantidadCursos;
            archivo.ignore();

            vector<int> idsCursos(cantidadCursos);
            for (int i = 0; i < cantidadCursos; i++) {
                archivo >> idsCursos[i];
                archivo.ignore();
            }

            if (!_gestionadorCursos->crearEspecializacion(idEmpresa, nombreEmpresa, tituloActividad, cantidadCursos, descripcionActividad, idsCursos)) {
                throw runtime_error("Error al crear especialización: " + tituloActividad);
            }
        }

        cantidad++;
    }

    archivo.close();
}

// Carga datos de inscripciones desde archivo binario
void FileManager::cargarDatosInscripciones()
{
    ifstream archivo(RUTA_INSCRIPCIONES, ios::binary);
    if (!archivo.is_open()) {
        throw runtime_error("No se pudo abrir el archivo de inscripciones: " + RUTA_INSCRIPCIONES);
    }

    try {
        InscripcionBinaria inscripcion;
        while (archivo.read(reinterpret_cast<char*>(&inscripcion), sizeof(InscripcionBinaria))) {
            int idx = inscripcion.idActividad;
            int tipo = inscripcion.tipoActividad;

            if (tipo == TIPO_CURSO) {
                _gestionadorCursos->getCursos().get(idx)->aumentarAlumno(1);
            }
            else if (tipo == TIPO_ESPECIALIZACION) {
                _gestionadorCursos->getEspecializaciones().get(idx)->aumentarAlumno(1);
            }
        }

        if (!archivo.eof()) {
            throw runtime_error("Error al leer el archivo de inscripciones");
        }
    }
    catch (const exception& e) {
        archivo.close();
        throw runtime_error("Error al procesar inscripciones: " + string(e.what()));
    }

    archivo.close();
}

#endif // !HEADER_CONTROLLERS_FILEMANAGER_HPP