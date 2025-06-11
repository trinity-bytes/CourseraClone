// description: Este archivo define la clase FileManager, 
//				que se encarga de gestionar archivos en el sistema usando organización por dominios.

#ifndef COURSERACLONE_PERSISTENCE_FILESMANAGER_HPP
#define COURSERACLONE_PERSISTENCE_FILESMANAGER_HPP

// Headers estándar
#include <string>    // Para uso de std::string
#include <fstream>   // Para manejo de archivos
#include <vector>    // Para uso de vector
#include <stdexcept> // Para std::runtime_error
#include <iostream>  // Para logging
#include <filesystem>// Para verificación de directorios

// Headers propios
#include "UsuarioTypes.hpp" 
#include "InscripcionTypes.hpp"
#include "../Utils/DataPaths.hpp"

// Constantes de tipos
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

// Resultados de operaciones de archivo
enum class FileOperationResult {
    SUCCESS,
    FILE_NOT_FOUND,
    PERMISSION_DENIED,
    CORRUPTION_DETECTED,
    UNKNOWN_ERROR
};

class FileManager
{
private:
    // Utilidades privadas para logging y validación
    static void logError(const std::string& operation, const std::string& file, const std::string& error);
    static void logInfo(const std::string& operation, const std::string& file);
    static bool validateFileIntegrity(const std::string& filePath, size_t expectedRecordSize);
    static bool createDirectoryIfNotExists(const std::string& path);

public:
    // Inicialización del sistema de archivos
    static bool inicializarSistemaArchivos();
    static bool verificarIntegridadTodosLosArchivos();

    // ========== DOMINIO CORE (Usuarios e Inscripciones) ==========

    // Gestión de usuarios
    static FileOperationResult guardarUsuarioBinario(
        const UsuarioBinario& bin,
        TipoUsuario tipo,
        long& offset
    );

    static std::vector<UsuarioIndex> cargarIndicesUsuario(TipoUsuario tipo);

    static FileOperationResult guardarIndiceUsuario(
        const UsuarioIndex& indice,
        TipoUsuario tipo
    );

    static UsuarioBinario cargarUsuarioPorOffset(TipoUsuario tipo, long offset);

    // Gestión de inscripciones
    static FileOperationResult guardarInscripcionBinaria(
        const InscripcionBinaria& bin,
        int& offsetRegistro
    );

    static FileOperationResult actualizarPagoInscripcion(int posicion, bool estado);

    static std::vector<InscripcionBinaria> leerDatosInscripciones();

    static FileOperationResult eliminarInscripcion(int posicion);

    // ========== DOMINIO CONTENT (Cursos y Especializaciones) ==========

    // Gestión de actividades académicas
    static RawActividadesData leerDatosActividades();

    static FileOperationResult guardarCurso(const RawCursoData& curso);

    static FileOperationResult guardarEspecializacion(const RawEspecializacionData& especializacion);

    static FileOperationResult actualizarActividad(int id, const std::string& nuevosDatos);

    // ========== DOMINIO FINANCIAL (Pagos y Comprobantes) ==========

    // Gestión de pagos
    static FileOperationResult registrarPago(
        int idUsuario,
        int idActividad,
        double monto,
        const std::string& metodoPago
    );

    static FileOperationResult generarComprobantePago(
        int idPago,
        const std::string& datosComprobante
    );

    static std::vector<std::string> obtenerHistorialPagos(int idUsuario);

    static FileOperationResult procesarReembolso(int idPago, const std::string& motivo);

    // ========== UTILIDADES GENERALES ==========

    // Backup y restauración
    static FileOperationResult crearBackupCompleto(const std::string& rutaDestino);

    static FileOperationResult restaurarDesdeBackup(const std::string& rutaBackup);

    // Mantenimiento
    static FileOperationResult compactarArchivos();

    static FileOperationResult limpiarArchivosTemporales();

    // Estadísticas del sistema
    static void mostrarEstadisticasArchivos();

    static size_t obtenerTamanoArchivo(const std::string& rutaArchivo);

private:
    // Helpers para obtener rutas según el tipo de usuario
    static std::string getDataFilePath(TipoUsuario tipo);
    static std::string getIndexFilePath(TipoUsuario tipo);
};

// ========== IMPLEMENTACIONES INLINE ==========

// Utilidades privadas
inline void FileManager::logError(const std::string& operation, const std::string& file, const std::string& error) {
    std::cerr << "[ERROR] " << operation << " en " << file << ": " << error << std::endl;
}

inline void FileManager::logInfo(const std::string& operation, const std::string& file) {
    std::cout << "[INFO] " << operation << " exitoso en " << file << std::endl;
}

inline bool FileManager::createDirectoryIfNotExists(const std::string& path) {
    try {
        if (!std::filesystem::exists(path)) {
            return std::filesystem::create_directories(path);
        }
        return true;
    }
    catch (const std::filesystem::filesystem_error& e) {
        logError("Crear directorio", path, e.what());
        return false;
    }
}

// Inicialización del sistema
inline bool FileManager::inicializarSistemaArchivos() {
    bool success = true;

    // Crear directorios necesarios
    success &= createDirectoryIfNotExists(DataPaths::Core::BASE);
    success &= createDirectoryIfNotExists(DataPaths::Content::BASE);
    success &= createDirectoryIfNotExists(DataPaths::Financial::BASE);
    success &= createDirectoryIfNotExists("Resources/Data/Index/");
    success &= createDirectoryIfNotExists("Resources/Data/Indices/");

    if (success) {
        logInfo("Inicialización", "Sistema de archivos");
    }
    else {
        logError("Inicialización", "Sistema de archivos", "No se pudieron crear algunos directorios");
    }

    return success;
}

// Helpers para rutas de usuario
inline std::string FileManager::getDataFilePath(TipoUsuario tipo) {
    switch (tipo) {
    case TipoUsuario::ESTUDIANTE:
        return DataPaths::Core::DB_USUARIOS; // Asumiendo que todos van al mismo archivo
    case TipoUsuario::EMPRESA:
        return DataPaths::Core::DB_USUARIOS;
    default:
        throw std::invalid_argument("Tipo de usuario no válido");
    }
}

inline std::string FileManager::getIndexFilePath(TipoUsuario tipo) {
    switch (tipo) {
    case TipoUsuario::ESTUDIANTE:
        return DataPaths::Core::INDICES_ESTUDIANTES;
    case TipoUsuario::EMPRESA:
        return DataPaths::Core::INDICES_EMPRESAS;
    default:
        throw std::invalid_argument("Tipo de usuario no válido");
    }
}

// ========== DOMINIO CORE ==========

inline FileOperationResult FileManager::guardarUsuarioBinario(
    const UsuarioBinario& bin,
    TipoUsuario tipo,
    long& offset
) {
    try {
        auto path = getDataFilePath(tipo);
        std::ofstream os(path, std::ios::binary | std::ios::app);

        if (!os.is_open()) {
            logError("Guardar usuario", path, "No se pudo abrir el archivo");
            return FileOperationResult::FILE_NOT_FOUND;
        }

        os.seekp(0, std::ios::end);
        offset = os.tellp();
        os.write(reinterpret_cast<const char*>(&bin), sizeof(bin));

        if (!os.good()) {
            logError("Guardar usuario", path, "Error al escribir datos");
            return FileOperationResult::UNKNOWN_ERROR;
        }

        logInfo("Guardar usuario", path);
        return FileOperationResult::SUCCESS;

    }
    catch (const std::exception& e) {
        logError("Guardar usuario", "Sistema", e.what());
        return FileOperationResult::UNKNOWN_ERROR;
    }
}

inline std::vector<UsuarioIndex> FileManager::cargarIndicesUsuario(TipoUsuario tipo) {
    std::vector<UsuarioIndex> indices;

    try {
        auto path = getIndexFilePath(tipo);
        std::ifstream is(path, std::ios::binary);

        if (!is.is_open()) {
            logError("Cargar índices", path, "Archivo no encontrado");
            return indices; // Retorna vector vacío
        }

        UsuarioIndex tmp;
        while (is.read(reinterpret_cast<char*>(&tmp), sizeof(tmp))) {
            indices.push_back(tmp);
        }

        logInfo("Cargar índices", path + " (" + std::to_string(indices.size()) + " registros)");

    }
    catch (const std::exception& e) {
        logError("Cargar índices", "Sistema", e.what());
    }

    return indices;
}

inline FileOperationResult FileManager::guardarInscripcionBinaria(
    const InscripcionBinaria& bin,
    int& offsetRegistro
) {
    try {
        std::ofstream os(DataPaths::Core::DB_INSCRIPCIONES, std::ios::binary | std::ios::app);

        if (!os.is_open()) {
            logError("Guardar inscripción", DataPaths::Core::DB_INSCRIPCIONES, "No se pudo abrir el archivo");
            return FileOperationResult::FILE_NOT_FOUND;
        }

        os.seekp(0, std::ios::end);
        offsetRegistro = static_cast<int>(os.tellp() / sizeof(InscripcionBinaria));
        os.write(reinterpret_cast<const char*>(&bin), sizeof(bin));

        if (!os.good()) {
            logError("Guardar inscripción", DataPaths::Core::DB_INSCRIPCIONES, "Error al escribir");
            return FileOperationResult::UNKNOWN_ERROR;
        }

        logInfo("Guardar inscripción", DataPaths::Core::DB_INSCRIPCIONES);
        return FileOperationResult::SUCCESS;

    }
    catch (const std::exception& e) {
        logError("Guardar inscripción", "Sistema", e.what());
        return FileOperationResult::UNKNOWN_ERROR;
    }
}

inline FileOperationResult FileManager::actualizarPagoInscripcion(int posicion, bool estado) {
    try {
        std::fstream os(DataPaths::Core::DB_INSCRIPCIONES, std::ios::binary | std::ios::in | std::ios::out);

        if (!os.is_open()) {
            logError("Actualizar pago", DataPaths::Core::DB_INSCRIPCIONES, "No se pudo abrir el archivo");
            return FileOperationResult::FILE_NOT_FOUND;
        }

        os.seekp(posicion * sizeof(InscripcionBinaria) + offsetof(InscripcionBinaria, pagado), std::ios::beg);
        os.write(reinterpret_cast<const char*>(&estado), sizeof(estado));

        if (!os.good()) {
            logError("Actualizar pago", DataPaths::Core::DB_INSCRIPCIONES, "Error al actualizar");
            return FileOperationResult::UNKNOWN_ERROR;
        }

        logInfo("Actualizar pago", DataPaths::Core::DB_INSCRIPCIONES);
        return FileOperationResult::SUCCESS;

    }
    catch (const std::exception& e) {
        logError("Actualizar pago", "Sistema", e.what());
        return FileOperationResult::UNKNOWN_ERROR;
    }
}

// ========== DOMINIO CONTENT ==========

inline RawActividadesData FileManager::leerDatosActividades() {
    RawActividadesData todasLasActividades;

    try {
        std::ifstream archivo(DataPaths::Content::DB_CURSOS); // Asumiendo que actividades van a cursos

        if (!archivo.is_open()) {
            logError("Leer actividades", DataPaths::Content::DB_CURSOS, "No se pudo abrir el archivo");
            throw std::runtime_error("No se pudo abrir el archivo de actividades: " + DataPaths::Content::DB_CURSOS);
        }

        std::string nombreEmpresa, titulo, descripcion, instructor, tituloActividad, descripcionActividad;
        int tipo, idEmpresa;

        while (archivo >> idEmpresa) {
            archivo.ignore();
            archivo >> tipo;
            archivo.ignore();
            std::getline(archivo, nombreEmpresa);
            std::getline(archivo, tituloActividad);
            std::getline(archivo, descripcionActividad);

            if (tipo == TIPO_CURSO) {
                RawCursoData cursoData;
                cursoData.idEmpresa = idEmpresa;
                cursoData.nombreEmpresa = nombreEmpresa;
                cursoData.tituloActividad = tituloActividad;
                cursoData.descripcionActividad = descripcionActividad;

                std::getline(archivo, cursoData.instructor);
                archivo >> cursoData.cantidadClases;
                archivo.ignore();

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
                archivo.ignore();

                especializacionData.idsCursosInternos.resize(especializacionData.cantidadCursosEnEspecializacion);
                for (int i = 0; i < especializacionData.cantidadCursosEnEspecializacion; i++) {
                    archivo >> especializacionData.idsCursosInternos[i];
                    archivo.ignore();
                }

                todasLasActividades.especializaciones.push_back(especializacionData);
            }
        }

        archivo.close();
        logInfo("Leer actividades", DataPaths::Content::DB_CURSOS + " (" +
            std::to_string(todasLasActividades.cursos.size()) + " cursos, " +
            std::to_string(todasLasActividades.especializaciones.size()) + " especializaciones)");

    }
    catch (const std::exception& e) {
        logError("Leer actividades", "Sistema", e.what());
        throw;
    }

    return todasLasActividades;
}

// ========== DOMINIO FINANCIAL ==========

inline FileOperationResult FileManager::registrarPago(
    int idUsuario,
    int idActividad,
    double monto,
    const std::string& metodoPago
) {
    try {
        std::ofstream archivo(DataPaths::Financial::DB_PAGOS, std::ios::app);

        if (!archivo.is_open()) {
            logError("Registrar pago", DataPaths::Financial::DB_PAGOS, "No se pudo abrir el archivo");
            return FileOperationResult::FILE_NOT_FOUND;
        }

        // Formato: idUsuario|idActividad|monto|metodoPago|timestamp
        auto now = std::time(nullptr);
        archivo << idUsuario << "|" << idActividad << "|" << monto << "|"
            << metodoPago << "|" << now << std::endl;

        if (!archivo.good()) {
            logError("Registrar pago", DataPaths::Financial::DB_PAGOS, "Error al escribir");
            return FileOperationResult::UNKNOWN_ERROR;
        }

        logInfo("Registrar pago", DataPaths::Financial::DB_PAGOS);
        return FileOperationResult::SUCCESS;

    }
    catch (const std::exception& e) {
        logError("Registrar pago", "Sistema", e.what());
        return FileOperationResult::UNKNOWN_ERROR;
    }
}

inline FileOperationResult FileManager::generarComprobantePago(
    int idPago,
    const std::string& datosComprobante
) {
    try {
        std::ofstream archivo(DataPaths::Financial::DB_COMPROBANTES, std::ios::app);

        if (!archivo.is_open()) {
            logError("Generar comprobante", DataPaths::Financial::DB_COMPROBANTES, "No se pudo abrir el archivo");
            return FileOperationResult::FILE_NOT_FOUND;
        }

        archivo << datosComprobante << std::endl;

        if (!archivo.good()) {
            logError("Generar comprobante", DataPaths::Financial::DB_COMPROBANTES, "Error al escribir");
            return FileOperationResult::UNKNOWN_ERROR;
        }

        logInfo("Generar comprobante", DataPaths::Financial::DB_COMPROBANTES);
        return FileOperationResult::SUCCESS;

    }
    catch (const std::exception& e) {
        logError("Generar comprobante", "Sistema", e.what());
        return FileOperationResult::UNKNOWN_ERROR;
    }
}

// ========== INSCRIPCIONES ==========

inline std::vector<InscripcionBinaria> FileManager::leerDatosInscripciones() {
    std::vector<InscripcionBinaria> listaInscripciones;

    try {
        std::ifstream archivo(DataPaths::Core::DB_INSCRIPCIONES, std::ios::binary);

        if (!archivo.is_open()) {
            logError("Leer inscripciones", DataPaths::Core::DB_INSCRIPCIONES, "No se pudo abrir el archivo");
            throw std::runtime_error("No se pudo abrir el archivo de inscripciones: " + DataPaths::Core::DB_INSCRIPCIONES);
        }

        InscripcionBinaria inscripcion;
        while (archivo.read(reinterpret_cast<char*>(&inscripcion), sizeof(InscripcionBinaria))) {
            listaInscripciones.push_back(inscripcion);
        }

        if (archivo.bad()) {
            throw std::runtime_error("Error crítico de IO al leer el archivo de inscripciones.");
        }
        else if (!archivo.eof() && archivo.fail()) {
            throw std::runtime_error("Error al leer el archivo de inscripciones: posible formato incorrecto.");
        }

        archivo.close();
        logInfo("Leer inscripciones", DataPaths::Core::DB_INSCRIPCIONES + " (" +
            std::to_string(listaInscripciones.size()) + " registros)");

    }
    catch (const std::ios_base::failure& e) {
        logError("Leer inscripciones", DataPaths::Core::DB_INSCRIPCIONES, e.what());
        throw std::runtime_error("Excepción de IO al procesar inscripciones: " + std::string(e.what()));
    }

    return listaInscripciones;
}

// ========== UTILIDADES ==========

inline void FileManager::mostrarEstadisticasArchivos() {
    std::cout << "\n========== ESTADÍSTICAS DEL SISTEMA DE ARCHIVOS ==========\n";

    // Core domain
    std::cout << "DOMINIO CORE:\n";
    std::cout << "  Usuarios: " << obtenerTamanoArchivo(DataPaths::Core::DB_USUARIOS) << " bytes\n";
    std::cout << "  Inscripciones: " << obtenerTamanoArchivo(DataPaths::Core::DB_INSCRIPCIONES) << " bytes\n";

    // Content domain  
    std::cout << "DOMINIO CONTENT:\n";
    std::cout << "  Cursos: " << obtenerTamanoArchivo(DataPaths::Content::DB_CURSOS) << " bytes\n";
    std::cout << "  Especializaciones: " << obtenerTamanoArchivo(DataPaths::Content::DB_ESPECIALIZACIONES) << " bytes\n";

    // Financial domain
    std::cout << "DOMINIO FINANCIAL:\n";
    std::cout << "  Pagos: " << obtenerTamanoArchivo(DataPaths::Financial::DB_PAGOS) << " bytes\n";
    std::cout << "  Comprobantes: " << obtenerTamanoArchivo(DataPaths::Financial::DB_COMPROBANTES) << " bytes\n";

    std::cout << "=========================================================\n\n";
}

inline size_t FileManager::obtenerTamanoArchivo(const std::string& rutaArchivo) {
    try {
        if (std::filesystem::exists(rutaArchivo)) {
            return std::filesystem::file_size(rutaArchivo);
        }
        return 0;
    }
    catch (const std::filesystem::filesystem_error&) {
        return 0;
    }
}

#endif // COURSERACLONE_PERSISTENCE_FILESMANAGER_HPP