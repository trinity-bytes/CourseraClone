// description: Este archivo define la clase FilesManager implementando el patrón Singleton, 
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
#include <memory>    // Para std::unique_ptr
#include <mutex>     // Para std::once_flag

// Headers propios
#include "..//Persistence/UsuarioTypes.hpp" 
#include "..//Persistence/InscripcionTypes.hpp"
#include "..//Persistence/ActividadTypes.hpp"
#include "../Utils/DataPaths.hpp"

// Resultados de operaciones de archivo
enum class FileOperationResult 
{
    SUCCESS,
    FILE_NOT_FOUND,
    PERMISSION_DENIED,
    CORRUPTION_DETECTED,
    UNKNOWN_ERROR
};

class FilesManager 
{
private:
    // ========== SINGLETON PATTERN ==========
    
    // La única instancia de la clase
    static std::unique_ptr<FilesManager> _instance;
    
    // Mutex para asegurar la inicialización segura en entornos multi-hilo
    static std::once_flag _onceFlag;
    
    // Constructor privado para evitar instanciación externa
    FilesManager();
    
    // Estado interno del manager
    bool _sistemaInicializado;
    std::string _ultimoError;
    
    // ========== MÉTODOS PRIVADOS ==========
    
    // Utilidades privadas para logging y validación
    void logError(const std::string& operation, const std::string& file, const std::string& error);
    void logInfo(const std::string& operation, const std::string& file);
    bool validateFileIntegrity(const std::string& filePath, size_t expectedRecordSize);
    bool createDirectoryIfNotExists(const std::string& path);
    
    // Helpers para obtener rutas según el tipo de usuario
    std::string getDataFilePath(TipoUsuario tipo);
    std::string getIndexFilePath(TipoUsuario tipo);
	std::string getDataFilePathActividades(TipoActividad tipo);
    
public:
    // ========== SINGLETON INTERFACE ==========
    
    // Eliminar constructor de copia y operador de asignación
    FilesManager(const FilesManager&) = delete;
    FilesManager& operator=(const FilesManager&) = delete;
    
    // Método estático para obtener la única instancia
    static FilesManager& getInstance();
    
    // Destructor
    ~FilesManager() = default;
    
    // ========== INICIALIZACIÓN Y ESTADO ==========
    
    /**
     * @brief Inicializa el sistema de archivos (solo se ejecuta una vez)
     * @return true si la inicialización fue exitosa
     */
    bool inicializarSistemaArchivos();
    
    /**
     * @brief Verifica si el sistema está inicializado
     * @return true si está inicializado
     */
    bool estaInicializado() const { return _sistemaInicializado; }
    
    /**
     * @brief Obtiene el último error ocurrido
     * @return Descripción del último error
     */
    std::string obtenerUltimoError() const { return _ultimoError; }
    
    /**
     * @brief Verifica la integridad de todos los archivos
     * @return true si todos los archivos están íntegros
     */
    bool verificarIntegridadTodosLosArchivos();
    
    // ========== DOMINIO CORE (Usuarios e Inscripciones) ==========
    
    /**
     * @brief Guarda un usuario en formato binario
     * @param bin Datos binarios del usuario
     * @param tipo Tipo de usuario (ESTUDIANTE/EMPRESA)
     * @param offset Posición donde se guardó (salida)
     * @return Resultado de la operación
     */
    FileOperationResult guardarUsuarioBinario(const UsuarioBinario& bin, TipoUsuario tipo, long& offset);
    
    /**
     * @brief Carga los índices de usuarios de un tipo específico
     * @param tipo Tipo de usuario
     * @return Vector con los índices cargados
     */
    std::vector<UsuarioIndex> cargarIndicesUsuario(TipoUsuario tipo);
    
    /**
     * @brief Guarda un índice de usuario
     * @param indice Índice a guardar
     * @param tipo Tipo de usuario
     * @return Resultado de la operación
     */
    FileOperationResult guardarIndiceUsuario(const UsuarioIndex& indice, TipoUsuario tipo);
    
    /**
     * @brief Carga un usuario por su offset en el archivo
     * @param tipo Tipo de usuario
     * @param offset Posición en el archivo
     * @return Datos binarios del usuario
     */
    UsuarioBinario cargarUsuarioPorOffset(TipoUsuario tipo, long offset);
    
    /**
     * @brief Guarda una inscripción en formato binario
     * @param bin Datos de la inscripción
     * @param offsetRegistro Posición donde se guardó (salida)
     * @return Resultado de la operación
     */
    FileOperationResult guardarInscripcionBinaria(const InscripcionBinaria& bin, int& offsetRegistro);
    
    /**
     * @brief Actualiza el estado de pago de una inscripción
     * @param posicion Posición del registro en el archivo
     * @param estado Nuevo estado de pago
     * @return Resultado de la operación
     */
    FileOperationResult actualizarPagoInscripcion(int posicion, bool estado);
    
    /**
     * @brief Lee todas las inscripciones del sistema
     * @return Vector con todas las inscripciones
     */
    std::vector<InscripcionBinaria> leerDatosInscripciones();
    
    /**
     * @brief Elimina una inscripción por posición
     * @param posicion Posición del registro a eliminar
     * @return Resultado de la operación
     */
    FileOperationResult eliminarInscripcion(int posicion);
    
    // ========== DOMINIO CONTENT (Cursos y Especializaciones) ==========
    /*
    * 
    */
    inline void FilesManager::leerDatoCurso(std::vector<RawCursoData>& vectorCursoAnadir);

    /*
    */
    RawEspecializacionData FilesManager::leerDatoEspecializacion();

    /**
     * @brief Lee todos los datos de actividades (cursos y especializaciones)
     * @return Estructura con todos los datos de actividades
     */
    RawActividadesData leerDatosActividades();
    
    /**
     * @brief Guarda un curso en el sistema
     * @param curso Datos del curso a guardar
     * @return Resultado de la operación
     */
    FileOperationResult guardarCurso(const RawCursoData& curso);
    
    /**
     * @brief Guarda una especialización en el sistema
     * @param especializacion Datos de la especialización
     * @return Resultado de la operación
     */
    FileOperationResult guardarEspecializacion(const RawEspecializacionData& especializacion);
    
    /**
     * @brief Actualiza los datos de una actividad
     * @param id ID de la actividad
     * @param nuevosDatos Nuevos datos en formato texto
     * @return Resultado de la operación
     */
    FileOperationResult actualizarActividad(int id, const std::string& nuevosDatos);
    
    // ========== DOMINIO FINANCIAL (Pagos y Comprobantes) ==========
    
    /**
     * @brief Registra un pago en el sistema
     * @param idUsuario ID del usuario
     * @param idActividad ID de la actividad
     * @param monto Monto del pago
     * @param metodoPago Método de pago utilizado
     * @return Resultado de la operación
     */
    FileOperationResult registrarPago(int idUsuario, int idActividad, double monto, const std::string& metodoPago);
    
    /**
     * @brief Genera un comprobante de pago
     * @param idPago ID del pago
     * @param datosComprobante Datos del comprobante
     * @return Resultado de la operación
     */
    FileOperationResult generarComprobantePago(int idPago, const std::string& datosComprobante);
    
    /**
     * @brief Obtiene el historial de pagos de un usuario
     * @param idUsuario ID del usuario
     * @return Vector con el historial de pagos
     */
    std::vector<std::string> obtenerHistorialPagos(int idUsuario);
    
    /**
     * @brief Procesa un reembolso
     * @param idPago ID del pago a reembolsar
     * @param motivo Motivo del reembolso
     * @return Resultado de la operación
     */
    FileOperationResult procesarReembolso(int idPago, const std::string& motivo);
    
    // ========== UTILIDADES GENERALES ==========
    
    /**
     * @brief Crea un backup completo del sistema
     * @param rutaDestino Ruta donde crear el backup
     * @return Resultado de la operación
     */
    FileOperationResult crearBackupCompleto(const std::string& rutaDestino);
    
    /**
     * @brief Restaura el sistema desde un backup
     * @param rutaBackup Ruta del backup a restaurar
     * @return Resultado de la operación
     */
    FileOperationResult restaurarDesdeBackup(const std::string& rutaBackup);
    
    /**
     * @brief Compacta los archivos del sistema
     * @return Resultado de la operación
     */
    FileOperationResult compactarArchivos();
    
    /**
     * @brief Limpia archivos temporales
     * @return Resultado de la operación
     */
    FileOperationResult limpiarArchivosTemporales();
    
    /**
     * @brief Muestra estadísticas de los archivos del sistema
     */
    void mostrarEstadisticasArchivos();
    
    /**
     * @brief Obtiene el tamaño de un archivo
     * @param rutaArchivo Ruta del archivo
     * @return Tamaño en bytes
     */
    size_t obtenerTamanoArchivo(const std::string& rutaArchivo);
    
    /**
     * @brief Reinicia el sistema de archivos (para testing)
     * @return true si el reinicio fue exitoso
     */
    bool reiniciarSistema();
};

// ========== INICIALIZACIÓN DE MIEMBROS ESTÁTICOS ==========

// Definición de la instancia única (inline para header-only)
inline std::unique_ptr<FilesManager> FilesManager::_instance = nullptr;

// Definición del flag para std::call_once
inline std::once_flag FilesManager::_onceFlag;

// ========== IMPLEMENTACIONES INLINE ==========

// Constructor privado
inline FilesManager::FilesManager() : _sistemaInicializado(false) {
    logInfo("Constructor", "FilesManager Singleton inicializado");
}

// Método getInstance del Singleton
inline FilesManager& FilesManager::getInstance() {
    std::call_once(_onceFlag, []() {
        _instance.reset(new FilesManager());
    });
    return *_instance;
}

// Utilidades privadas
inline void FilesManager::logError(const std::string& operation, const std::string& file, const std::string& error) {
    _ultimoError = "[" + operation + "] " + error + " (Archivo: " + file + ")";
    std::cerr << "[FilesManager ERROR] " << _ultimoError << std::endl;
}

inline void FilesManager::logInfo(const std::string& operation, const std::string& file) {
    std::cout << "[FilesManager INFO] " << operation << " exitoso";
    if (!file.empty()) {
        std::cout << " en " << file;
    }
    std::cout << std::endl;
}

inline bool FilesManager::createDirectoryIfNotExists(const std::string& path) {
    try {
        if (!std::filesystem::exists(path)) {
            bool created = std::filesystem::create_directories(path);
            if (created) {
                logInfo("Crear directorio", path);
            }
            return created;
        }
        return true;
    } catch (const std::filesystem::filesystem_error& e) {
        logError("Crear directorio", path, e.what());
        return false;
    }
}

// Inicialización del sistema
inline bool FilesManager::inicializarSistemaArchivos() {
    if (_sistemaInicializado) {
        logInfo("Inicialización", "Sistema ya inicializado");
        return true;
    }
    
    bool success = true;
    
    // Crear directorios necesarios
    success &= createDirectoryIfNotExists(DataPaths::Core::BASE);
    success &= createDirectoryIfNotExists(DataPaths::Content::BASE);
    success &= createDirectoryIfNotExists(DataPaths::Financial::BASE);
    success &= createDirectoryIfNotExists("Resources/Data/Index/");
    success &= createDirectoryIfNotExists("Resources/Data/Indices/");
    
    if (success) {
        _sistemaInicializado = true;
        logInfo("Inicialización completa", "Sistema de archivos");
    } else {
        logError("Inicialización", "Sistema de archivos", "No se pudieron crear algunos directorios");
    }
    
    return success;
}

inline bool FilesManager::reiniciarSistema() {
    _sistemaInicializado = false;
    _ultimoError.clear();
    logInfo("Reinicio", "Sistema reiniciado");
    return inicializarSistemaArchivos();
}

// Helpers para rutas de usuario
inline std::string FilesManager::getDataFilePath(TipoUsuario tipo) {
    switch (tipo) {
        case TipoUsuario::ESTUDIANTE:
            return DataPaths::Core::DB_USUARIOS;
        case TipoUsuario::EMPRESA:
            return DataPaths::Core::DB_USUARIOS;
        default:
            throw std::invalid_argument("Tipo de usuario no válido");
    }
}

inline std::string FilesManager::getIndexFilePath(TipoUsuario tipo) {
    switch (tipo) {
        case TipoUsuario::ESTUDIANTE:
            return DataPaths::Core::INDICES_ESTUDIANTES;
        case TipoUsuario::EMPRESA:
            return DataPaths::Core::INDICES_EMPRESAS;
        default:
            throw std::invalid_argument("Tipo de usuario no válido");
    }
}

std::string getDataFilePathActividades(TipoActividad tipo) {
    switch (tipo) {
    case TipoActividad::CURSO:
        return DataPaths::Content::DB_CURSOS;
    case TipoActividad::ESPECIALIZACION:
        return DataPaths::Content::DB_ESPECIALIZACIONES;
    default:
        throw std::invalid_argument("Tipo de actividad no válido");
    }
}
// ========== DOMINIO CORE ==========

inline FileOperationResult FilesManager::guardarUsuarioBinario(
    const UsuarioBinario& bin,
    TipoUsuario tipo,
    long& offset
) {
    if (!_sistemaInicializado) {
        logError("Guardar usuario", "Sistema", "Sistema no inicializado");
        return FileOperationResult::UNKNOWN_ERROR;
    }
    
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
        
    } catch (const std::exception& e) {
        logError("Guardar usuario", "Sistema", e.what());
        return FileOperationResult::UNKNOWN_ERROR;
    }
}

inline std::vector<UsuarioIndex> FilesManager::cargarIndicesUsuario(TipoUsuario tipo) {
    std::vector<UsuarioIndex> indices;
    
    if (!_sistemaInicializado) {
        logError("Cargar índices", "Sistema", "Sistema no inicializado");
        return indices;
    }
    
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
        
    } catch (const std::exception& e) {
        logError("Cargar índices", "Sistema", e.what());
    }
    
    return indices;
}

inline FileOperationResult FilesManager::guardarInscripcionBinaria(
    const InscripcionBinaria& bin,
    int& offsetRegistro
) {
    if (!_sistemaInicializado) {
        logError("Guardar inscripción", "Sistema", "Sistema no inicializado");
        return FileOperationResult::UNKNOWN_ERROR;
    }
    
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
        
    } catch (const std::exception& e) {
        logError("Guardar inscripción", "Sistema", e.what());
        return FileOperationResult::UNKNOWN_ERROR;
    }
}

inline FileOperationResult FilesManager::actualizarPagoInscripcion(int posicion, bool estado) {
    if (!_sistemaInicializado) {
        logError("Actualizar pago", "Sistema", "Sistema no inicializado");
        return FileOperationResult::UNKNOWN_ERROR;
    }
    
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
        
    } catch (const std::exception& e) {
        logError("Actualizar pago", "Sistema", e.what());
        return FileOperationResult::UNKNOWN_ERROR;
    }
}

// ========== DOMINIO CONTENT ==========

inline void FilesManager::leerDatoCurso(std::vector<RawCursoData>& vectorCursoAnadir) {
	auto path = getDataFilePathActividades(TipoActividad::CURSO);
    std::ifstream is(path, std::ios::in);

    int id, idEmpresa, cantidadClases, categoriaNumero;
    std::string nombreEmpresa, titulo, descripcion, instructor;
	CategoriaActividad categoria;

    while (is >> id) {
        // Leer Datos
        std::cin >> idEmpresa >> nombreEmpresa >> titulo >> descripcion;
		std::cin >> categoriaNumero; // Leer como entero y convertir a enum
        std::cin >> instructor;
        std::cin >> cantidadClases;

        // Asignar valores
		RawCursoData cursoData;
		cursoData.id = id;
		cursoData.idEmpresa = idEmpresa;
		cursoData.nombreEmpresa = nombreEmpresa;
		cursoData.titulo = titulo;
		cursoData.descripcion = descripcion;
		cursoData.instructor = instructor;
		cursoData.categoria = static_cast<CategoriaActividad>(categoriaNumero);

        // Anadimos al vector
		vectorCursoAnadir.push_back(cursoData);
    }
}

inline RawEspecializacionData  FilesManager::leerDatoEspecializacion() {


    return RawEspecializacionData();
}

inline RawActividadesData FilesManager::leerDatosActividades() {
	// Todo: Implementar la lectura de actividades (cursos y especializaciones)
    std::vector<RawCursoData> cursoAnadir;
    std::vector<RawEspecializacionData> especializacionAnadir;

    try {



        return{ cursoAnadir, especializacionAnadir };

    } catch (const std::exception& e) {
        logError("Error: ", "Actividades", e.what());
        return RawActividadesData();
    }

}

// ========== DOMINIO FINANCIAL ==========

inline FileOperationResult FilesManager::registrarPago(
    int idUsuario,
    int idActividad,
    double monto,
    const std::string& metodoPago
) {
    if (!_sistemaInicializado) {
        logError("Registrar pago", "Sistema", "Sistema no inicializado");
        return FileOperationResult::UNKNOWN_ERROR;
    }
    
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
        
    } catch (const std::exception& e) {
        logError("Registrar pago", "Sistema", e.what());
        return FileOperationResult::UNKNOWN_ERROR;
    }
}

inline FileOperationResult FilesManager::generarComprobantePago(
    int idPago,
    const std::string& datosComprobante
) {
    if (!_sistemaInicializado) {
        logError("Generar comprobante", "Sistema", "Sistema no inicializado");
        return FileOperationResult::UNKNOWN_ERROR;
    }
    
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
        
    } catch (const std::exception& e) {
        logError("Generar comprobante", "Sistema", e.what());
        return FileOperationResult::UNKNOWN_ERROR;
    }
}

// ========== INSCRIPCIONES ==========

inline std::vector<InscripcionBinaria> FilesManager::leerDatosInscripciones() {
    std::vector<InscripcionBinaria> listaInscripciones;
    
    if (!_sistemaInicializado) {
        logError("Leer inscripciones", "Sistema", "Sistema no inicializado");
        return listaInscripciones;
    }
    
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
        
    } catch (const std::ios_base::failure& e) {
        logError("Leer inscripciones", DataPaths::Core::DB_INSCRIPCIONES, e.what());
        throw std::runtime_error("Excepción de IO al procesar inscripciones: " + std::string(e.what()));
    }
    
    return listaInscripciones;
}

// ========== UTILIDADES ==========

inline void FilesManager::mostrarEstadisticasArchivos() {
    if (!_sistemaInicializado) {
        std::cout << "[FilesManager] Sistema no inicializado. No se pueden mostrar estadísticas.\n";
        return;
    }
    
    std::cout << "\n========== ESTADÍSTICAS DEL SISTEMA DE ARCHIVOS (Singleton) ==========\n";
    
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
    
    std::cout << "Estado del sistema: " << (_sistemaInicializado ? "Inicializado" : "No inicializado") << "\n";
    std::cout << "Último error: " << (_ultimoError.empty() ? "Ninguno" : _ultimoError) << "\n";
    std::cout << "================================================================\n\n";
}

inline size_t FilesManager::obtenerTamanoArchivo(const std::string& rutaArchivo) {
    try {
        if (std::filesystem::exists(rutaArchivo)) {
            return std::filesystem::file_size(rutaArchivo);
        }
        return 0;
    } catch (const std::filesystem::filesystem_error&) {
        return 0;
    }
}

#endif // COURSERACLONE_PERSISTENCE_FILESMANAGER_HPP