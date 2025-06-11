// description: Este archivo define la clase FileManager, 
//				que se encarga de gestionar archivos en el sistema.

#ifndef COURSERACLONE_PERSISTENCE_FILESMANAGER_HPP
#define COURSERACLONE_PERSISTENCE_FILESMANAGER_HPP

// Headers estandar
#include <string>    // Para uso de std::string
#include <fstream>   // Para manejo de archivos
#include <vector>    // Para uso de vector
#include <stdexcept> // Para std::runtime_error

// Headers propios
#include "UsuarioTypes.hpp" 
#include "InscripcionTypes.hpp"

// Rutas de archivos
const std::string RUTA_ACTIVIDADES = "Resources/Data/actividades.txt";
const std::string RUTA_INSCRIPCIONES = "Resources/Data/inscripciones.dat";

// Puntero al CourseManager
const int TIPO_CURSO = 1;
const int TIPO_ESPECIALIZACION = 2;

// Datos crudos de un curso leídos del archivo
struct RawCursoData 
{
	// Datos generales del curso
    int idEmpresa;
    std::string nombreEmpresa;
    std::string tituloActividad;
    std::string descripcionActividad;
    std::string instructor;
    int cantidadClases;
    std::vector<std::string> titulosClases;
    std::vector<std::string> descripcionesClases;
};

// Datos crudos de una especialización leídos del archivo
struct RawEspecializacionData {
    int idEmpresa;
    std::string nombreEmpresa;
    std::string tituloActividad;
    std::string descripcionActividad;
    int cantidadCursosEnEspecializacion;
    std::vector<int> idsCursosInternos;
};

// Estructura para agrupar los datos crudos de todas las actividades
struct RawActividadesData 
{
    std::vector<RawCursoData> cursos;
    std::vector<RawEspecializacionData> especializaciones;
};

namespace FileManager
{
    inline bool guardarUsuarioBinario(
        const UsuarioBinario& bin,
        TipoUsuario tipo,
        long& offset
    ) {
        auto path = getDataFilePath(tipo);
        std::ofstream os(path, std::ios::binary | std::ios::app);
        if (!os) return false;
        os.seekp(0, std::ios::end);
        offset = os.tellp();
        os.write(reinterpret_cast<const char*>(&bin), sizeof(bin));
        return os.good();
    }

    inline std::vector<UsuarioIndex> cargarIndicesUsuario(TipoUsuario tipo) 
    {
        std::vector<UsuarioIndex> v;
        std::ifstream is(getIndexFilePath(tipo), std::ios::binary);
        UsuarioIndex tmp;
        while (is.read(reinterpret_cast<char*>(&tmp), sizeof(tmp)))
            v.push_back(tmp);
        return v;
    }

    inline bool guardarInscripcionBinaria(
        const InscripcionBinaria& bin,
        int& offsetRegistro
    ) {
        std::ofstream os(RUTA_INSCRIPCIONES, std::ios::binary | std::ios::app);
        if (!os.is_open()) return false;
        os.seekp(0, std::ios::end);
        offsetRegistro = static_cast<int>(os.tellp() / sizeof(InscripcionBinaria));
        os.write(reinterpret_cast<const char*>(&bin), sizeof(bin));
        return os.good();
    }

    inline bool actualizarPagoInscripcion(int posicion, bool estado) {
        std::fstream os(RUTA_INSCRIPCIONES, std::ios::binary | std::ios::in | std::ios::out);
        if (!os.is_open()) return false;
        os.seekp(posicion * sizeof(InscripcionBinaria) + offsetof(InscripcionBinaria, pagado), ios::beg);
        os.write(reinterpret_cast<const char*>(&estado), sizeof(estado));
        return os.good();
    }

    // Lee datos de actividades (cursos y especializaciones) desde archivo de texto
    RawActividadesData leerDatosActividades();
    // Lee datos de inscripciones desde archivo binario
    std::vector<InscripcionBinaria> leerDatosInscripciones();
}

// Lee datos de actividades (cursos y especializaciones) desde archivo de texto
inline RawActividadesData FileManager::leerDatosActividades()
{
    RawActividadesData todasLasActividades;
    std::ifstream archivo(RUTA_ACTIVIDADES);

    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo de actividades: " + RUTA_ACTIVIDADES);
    }

    std::string nombreEmpresa, titulo, descripcion, instructor, tituloActividad, descripcionActividad;
    int tipo, idEmpresa;

    while (archivo >> idEmpresa)
    {
        archivo.ignore(); // Consume el newline después de leer idEmpresa
        archivo >> tipo;
        archivo.ignore(); // Consume el newline después de leer tipo
        std::getline(archivo, nombreEmpresa);
        std::getline(archivo, tituloActividad);
        std::getline(archivo, descripcionActividad);

        if (tipo == TIPO_CURSO)
        {
            RawCursoData cursoData;
            cursoData.idEmpresa = idEmpresa;
            cursoData.nombreEmpresa = nombreEmpresa;
            cursoData.tituloActividad = tituloActividad;
            cursoData.descripcionActividad = descripcionActividad;

            std::getline(archivo, cursoData.instructor);
            archivo >> cursoData.cantidadClases;
            archivo.ignore(); // Consume el newline después de leer cantidadClases

            cursoData.titulosClases.resize(cursoData.cantidadClases);
            cursoData.descripcionesClases.resize(cursoData.cantidadClases);
            for (int i = 0; i < cursoData.cantidadClases; i++) {
                std::getline(archivo, cursoData.titulosClases[i]);
                std::getline(archivo, cursoData.descripcionesClases[i]);
            }
            todasLasActividades.cursos.push_back(cursoData);
        }
        else if (tipo == TIPO_ESPECIALIZACION) {
            RawEspecializacionData especializacionData;
            especializacionData.idEmpresa = idEmpresa;
            especializacionData.nombreEmpresa = nombreEmpresa;
            especializacionData.tituloActividad = tituloActividad;
            especializacionData.descripcionActividad = descripcionActividad;

            archivo >> especializacionData.cantidadCursosEnEspecializacion;
            archivo.ignore(); // Consume el newline

            especializacionData.idsCursosInternos.resize(especializacionData.cantidadCursosEnEspecializacion);
            for (int i = 0; i < especializacionData.cantidadCursosEnEspecializacion; i++) {
                archivo >> especializacionData.idsCursosInternos[i];
                archivo.ignore(); // Consume el newline después de cada idCurso
            }
            todasLasActividades.especializaciones.push_back(especializacionData);
        }
    }

    archivo.close();
    return todasLasActividades;
}

// Lee datos de inscripciones desde archivo binario
inline std::vector<InscripcionBinaria> FileManager::leerDatosInscripciones()
{
    std::vector<InscripcionBinaria> listaInscripciones;
    std::ifstream archivo(RUTA_INSCRIPCIONES, std::ios::binary);
    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo de inscripciones: " + RUTA_INSCRIPCIONES);
    }

    try {
        InscripcionBinaria inscripcion;
        while (archivo.read(reinterpret_cast<char*>(&inscripcion), sizeof(InscripcionBinaria))) {
            listaInscripciones.push_back(inscripcion);
        }

        if (archivo.bad()) {
            throw std::runtime_error("Error crítico de IO al leer el archivo de inscripciones.");
        }
        else if (!archivo.eof() && archivo.fail()) {
            // Falló por una razón que no es EOF (ej. error de formato)
            throw std::runtime_error("Error al leer el archivo de inscripciones: posible formato incorrecto.");
        }
        // Si es solo EOF, la lectura terminó normalmente.
    }
    catch (const std::ios_base::failure& e) {
        // Captura excepciones de IO si están habilitadas en el stream
        archivo.close();
        throw std::runtime_error("Excepción de IO al procesar inscripciones: " + std::string(e.what()));
    }

    if (archivo.is_open()) { // Asegurarse de cerrar si no hubo excepción que ya lo hizo.
        archivo.close();
    }    return listaInscripciones;
}

#endif // COURSERACLONE_PERSISTENCE_FILESMANAGER_HPP