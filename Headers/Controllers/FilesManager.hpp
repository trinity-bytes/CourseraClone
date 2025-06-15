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
#include <chrono>    // Para timestamps
#include <iomanip>   // Para formateo de tiempo
#include <sstream>   // Para std::stringstream

// Headers propios
#include "../Types/UsuarioTypes.hpp" 
#include "../Types/InscripcionTypes.hpp"
#include "../Types/ActividadTypes.hpp"
#include "../Types/FilesTypes.hpp"
#include "../Utils/DataPaths.hpp"

class FilesManager 
{
private:
    // ========== SINGLETON PATTERN ==========
    /// @brief La única instancia de la clase
    static std::unique_ptr<FilesManager> _instance;
    
    /// @brief Mutex para asegurar la inicialización segura en entornos multi-hilo
    static std::once_flag _onceFlag;
    
    /// @brief Estado interno del manager
    bool _sistemaInicializado;
    std::string _ultimoError;

    /// @brief Constructor privado para evitar instanciación externa
    inline FilesManager();

    // ========== MÉTODOS PRIVADOS ==========
    /// @brief Utilidades privadas para logging y validación
    bool validateFileIntegrity(const std::string& filePath, size_t expectedRecordSize);
    bool createDirectoryIfNotExists(const std::string& path);
    
    /// @brief Helpers para obtener rutas según el tipo de usuario
    std::string getDataFilePath(TipoUsuario tipo);
    std::string getIndexFilePath(TipoUsuario tipo);
	std::string getDataFilePathActividades(TipoActividad tipo);
    
public:
    // ============== MENSAJES ==============
    void logError(const std::string& operation, const std::string& file, const std::string& error);
    void logInfo(const std::string& operation, const std::string& file);

    // ========== SINGLETON INTERFACE ==========
    /// @brief Eliminar constructor de copia y operador de asignación
    FilesManager(const FilesManager&) = delete;
    FilesManager& operator=(const FilesManager&) = delete;
    
    /// @brief Método estático para obtener la única instancia
    static FilesManager& getInstance();
    
    /// @brief Destructor
    ~FilesManager() = default;
    
    // ========== INICIALIZACIÓN Y ESTADO ==========
    /// @brief Inicializa el sistema de archivos (solo se ejecuta una vez)
    /// @return true si la inicialización fue exitosa
    bool inicializarSistemaArchivos();

    /// @brief Verifica si el sistema está inicializado
    /// @return true si está inicializado
    bool estaInicializado() const { return _sistemaInicializado; }
    
    /// @brief Obtiene el último error ocurrido
    /// @return Descripción del último error
    std::string obtenerUltimoError() const { return _ultimoError; }
    
    /// @brief Verifica la integridad de todos los archivos
    /// @return true si todos los archivos están íntegros
    bool verificarIntegridadTodosLosArchivos();
    
    // ========== DOMINIO CORE (Usuarios e Inscripciones) ==========
    /// @brief Guarda un usuario en formato binario
    /// @param bin Datos binarios del usuario
    /// @param tipo Tipo de usuario (ESTUDIANTE/EMPRESA)
    /// @param offset Posición donde se guardó (salida)
    ///  @return Resultado de la operación
    FileOperationResult guardarUsuarioBinario(const UsuarioBinario& bin, TipoUsuario tipo, long& offset);

    /// @brief Carga los índices de usuarios de un tipo específico
    /// @param tipo Tipo de usuario
    /// @return Vector con los índices cargados
    std::vector<UsuarioIndex> cargarIndicesUsuario(TipoUsuario tipo);

    /// @brief Guarda un índice de usuario
    /// @param indice Índice a guardar
    /// @param tipo Tipo de usuario
    /// @return Resultado de la operación
    FileOperationResult guardarIndiceUsuario(const UsuarioIndex& indice, TipoUsuario tipo);
 
    /// @brief Carga un usuario por su offset en el archivo
    /// @param tipo Tipo de usuario
    /// @param offset Posición en el archivo
    /// @return Datos binarios del usuario
    UsuarioBinario cargarUsuarioPorOffset(TipoUsuario tipo, long offset);

    /// @brief Guarda una inscripción en formato binario
    /// @param bin Datos de la inscripción
    /// @param offsetRegistro Posición donde se guardó (salida)
    /// @return Resultado de la operación
    FileOperationResult guardarInscripcionBinaria(const InscripcionBinaria& bin, int& offsetRegistro);

    /// @brief Actualiza el estado de pago de una inscripción
    /// @param posicion Posición del registro en el archivo
    /// @param estado Nuevo estado de pago
    /// @return Resultado de la operación
    FileOperationResult actualizarPagoInscripcion(int posicion, bool estado);

    /// @brief Lee todas las inscripciones del sistema
    /// @return Vector con todas las inscripciones
    std::vector<InscripcionBinaria> leerDatosInscripciones();

    /// @brief Elimina una inscripción por posición
    /// @param posicion Posición del registro a eliminar
    /// @return Resultado de la operación
    FileOperationResult eliminarInscripcion(int posicion);
      // ========== DOMINIO CONTENT (Cursos y Especializaciones) ==========
    /// @brief Lee todos los cursos del sistema
    /// @param vectorCursoAnadir Vector donde se almacenarán los cursos leídos
    void leerDatoCurso(std::vector<RawCursoData>& vectorCursoAnadir);

    /// @brief Lee todas las especializaciones del sistema
    /// @param vectorEspecializacionAnadir Vector donde se almacenarán las especializaciones leídas
    void leerDatoEspecializacion(std::vector<RawEspecializacionData>& vectorEspecializacionAnadir);

    // @brief Lee todos los datos de actividades (cursos y especializaciones)
    // @return Estructura con todos los datos de actividades
    RawActividadesData leerDatosActividades();

    /// @brief Guarda un curso en el sistema
    /// @param curso Datos del curso a guardar
    /// @return Resultado de la operación
    FileOperationResult guardarCurso(const RawCursoData& curso);

    /// @brief Guarda una especialización en el sistema
    /// @param especializacion Datos de la especialización
    /// @return Resultado de la operación
    FileOperationResult guardarEspecializacion(const RawEspecializacionData& especializacion);

    /// @brief Actualiza los datos de una actividad
    /// @param id ID de la actividad
    /// @param nuevosDatos Nuevos datos en formato texto
    /// @return Resultado de la operación
    FileOperationResult actualizarActividad(int id, const std::string& nuevosDatos);
    
    /// @brief Busca un curso por su ID
    /// @param id ID del curso a buscar
    /// @return Datos del curso encontrado, o estructura vacía si no se encuentra
    RawCursoData buscarCursoPorId(int id);

    /// @brief Busca una especialización por su ID
    /// @param id ID de la especialización a buscar
    /// @return Datos de la especialización encontrada, o estructura vacía si no se encuentra
    RawEspecializacionData buscarEspecializacionPorId(int id);

    /// @brief Obtiene cursos por categoría
    /// @param categoria Categoría de los cursos a buscar
    /// @return Vector con los cursos de la categoría especificada
    std::vector<RawCursoData> obtenerCursosPorCategoria(CategoriaActividad categoria);

    /// @brief Obtiene especializaciones por categoría
    /// @param categoria Categoría de las especializaciones a buscar
    /// @return Vector con las especializaciones de la categoría especificada
    std::vector<RawEspecializacionData> obtenerEspecializacionesPorCategoria(CategoriaActividad categoria);

    /// @brief Verifica si un curso existe en el sistema
    /// @param id ID del curso a verificar
    /// @return true si el curso existe, false en caso contrario
    bool existeCurso(int id);

    /// @brief Verifica si una especialización existe en el sistema
    /// @param id ID de la especialización a verificar
    /// @return true si la especialización existe, false en caso contrario
    bool existeEspecializacion(int id);

    // ========== DOMINIO FINANCIAL (Pagos y Comprobantes) ==========
    /// @brief Registra un pago en el sistema
    /// @param idUsuario ID del usuario
    /// @param idActividad ID de la actividad
    /// @param monto Monto del pago
    /// @param metodoPago Método de pago utilizado
    /// @return Resultado de la operación
    FileOperationResult registrarPago(int idUsuario, int idActividad, double monto, const std::string& metodoPago);

    /// @brief Genera un comprobante de pago
    /// @param idPago ID del pago
    /// @param datosComprobante Datos del comprobante
    /// @return Resultado de la operación
    FileOperationResult generarComprobantePago(int idPago, const std::string& datosComprobante);

    /// @brief Obtiene el historial de pagos de un usuario
    /// @param idUsuario ID del usuario
    /// @return Vector con el historial de pagos
    std::vector<std::string> obtenerHistorialPagos(int idUsuario);

    /// @brief Procesa un reembolso
    /// @param idPago ID del pago a reembolsar
    /// @param motivo Motivo del reembolso
    /// @return Resultado de la operación
    FileOperationResult procesarReembolso(int idPago, const std::string& motivo);
    
    // ========== UTILIDADES GENERALES ==========
    /// @brief Crea un backup completo del sistema
    /// @param rutaDestino Ruta donde crear el backup
    /// @return Resultado de la operación
    FileOperationResult crearBackupCompleto(const std::string& rutaDestino);

    /// @brief Restaura el sistema desde un backup
    /// @param rutaBackup Ruta del backup a restaurar
    // @return Resultado de la operación
    FileOperationResult restaurarDesdeBackup(const std::string& rutaBackup);

    /// @brief Compacta los archivos del sistema
    /// @return Resultado de la operación
    FileOperationResult compactarArchivos();

    /// @brief Limpia archivos temporales
    /// @return Resultado de la operación
    FileOperationResult limpiarArchivosTemporales();    /// @brief Limpia logs antiguos según criterios de tamaño
    /// @param diasAntiguedad Parámetro mantenido por compatibilidad (actualmente no usado)
    /// @return Resultado de la operación
    /// @note Limpia archivos de log que excedan 10MB de tamaño
    FileOperationResult limpiarLogsAntiguos(int diasAntiguedad = 30);

    /// @brief Obtiene estadísticas de los archivos de logs
    /// @return Información sobre tamaño y cantidad de logs
    std::string obtenerEstadisticasLogs();

    /// @brief Muestra estadísticas de los archivos del sistema
    void mostrarEstadisticasArchivos();

    /// @brief Obtiene el tamaño de un archivo
    /// @param rutaArchivo Ruta del archivo
    /// @return Tamaño en bytes
    size_t obtenerTamanoArchivo(const std::string& rutaArchivo);

    /// @brief Reinicia el sistema de archivos (para testing)
    /// @return true si el reinicio fue exitoso
    bool reiniciarSistema();
};

// ========== INICIALIZACIÓN DE MIEMBROS ESTÁTICOS ==========
/// @brief Definición de la instancia única (inline para header-only)
inline std::unique_ptr<FilesManager> FilesManager::_instance = nullptr;

/// @brief Definición del flag para std::call_once
inline std::once_flag FilesManager::_onceFlag;

// ========== IMPLEMENTACIONES INLINE ==========
/// @brief Constructor privado
inline FilesManager::FilesManager() : _sistemaInicializado(false) 
{
    logInfo("Constructor", "FilesManager Singleton inicializado");
}

// Método getInstance del Singleton
inline FilesManager& FilesManager::getInstance() 
{
    std::call_once(_onceFlag, []() {
        _instance.reset(new FilesManager());
    });
    return *_instance;
}

// Utilidades privadas
inline void FilesManager::logError(const std::string& operation, const std::string& file, const std::string& error) {
    _ultimoError = "[" + operation + "] " + error + " (Archivo: " + file + ")";
    
    // Escribir en el archivo de logs de error
    std::ofstream errorLogFile(DataPaths::Logs::ERROR_LOGS, std::ios::app);
    if (errorLogFile.is_open()) {
        // Obtener timestamp actual
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        auto tm = *std::localtime(&time_t);
        
        errorLogFile << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "] "
                     << "[ERROR] [" << operation << "] " 
                     << error << " (Archivo: " << file << ")" << std::endl;
        errorLogFile.close();
    }
    
    // También mostrar en consola para feedback inmediato
    std::cerr << "[FilesManager ERROR] " << _ultimoError << std::endl;
}

inline void FilesManager::logInfo(const std::string& operation, const std::string& file) {
    std::string infoMessage = operation + " exitoso";
    if (!file.empty()) {
        infoMessage += " en " + file;
    }
    
    // Escribir en el archivo de logs de información
    std::ofstream infoLogFile(DataPaths::Logs::INFO_LOGS, std::ios::app);
    if (infoLogFile.is_open()) {
        // Obtener timestamp actual
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        auto tm = *std::localtime(&time_t);
        
        infoLogFile << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "] "
                    << "[INFO] [" << operation << "] " 
                    << infoMessage << std::endl;
        infoLogFile.close();
    }
    
    // También mostrar en consola para feedback inmediato
    std::cout << "[FilesManager INFO] " << infoMessage << std::endl;
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
    success &= createDirectoryIfNotExists(DataPaths::Logs::BASE);
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

inline std::string FilesManager::getDataFilePathActividades(TipoActividad tipo) {
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
    if (!_sistemaInicializado) {
        logError("Leer cursos", "Sistema", "Sistema no inicializado");
        return;
    }

    auto path = getDataFilePathActividades(TipoActividad::CURSO);
    std::ifstream archivo(path, std::ios::in);

    if (!archivo.is_open()) {
        logError("Leer cursos", path, "No se pudo abrir el archivo");
        return;
    }

    try {
        std::string linea;
        
        while (std::getline(archivo, linea) && !linea.empty()) {
            RawCursoData cursoData;
            
            // Leer ID del curso
            cursoData.id = std::stoi(linea);
            
            // Leer ID de la empresa
            if (!std::getline(archivo, linea)) break;
            cursoData.idEmpresa = std::stoi(linea);
            
            // Leer nombre de la empresa
            if (!std::getline(archivo, linea)) break;
            cursoData.nombreEmpresa = linea;
            
            // Leer título del curso
            if (!std::getline(archivo, linea)) break;
            cursoData.titulo = linea;
            
            // Leer descripción del curso
            if (!std::getline(archivo, linea)) break;
            cursoData.descripcion = linea;
            
            // Leer categoría (como número)
            if (!std::getline(archivo, linea)) break;
            int categoriaNumero = std::stoi(linea);
            cursoData.categoria = static_cast<CategoriaActividad>(categoriaNumero);
            
            // Leer instructor
            if (!std::getline(archivo, linea)) break;
            cursoData.instructor = linea;
            
            // Leer cantidad de clases
            if (!std::getline(archivo, linea)) break;
            cursoData.cantidadClases = std::stoi(linea);
            
            // Saltar las líneas de descripción de clases
            for (int i = 0; i < cursoData.cantidadClases; ++i) {
                if (!std::getline(archivo, linea)) break;
                std::string tituloClase = linea;
				if (!std::getline(archivo, linea)) break;
				std::string descripcionClase = linea;
				cursoData.descripcionClases.push_back({ tituloClase, descripcionClase });
            }
            
            // Agregar el curso al vector
            vectorCursoAnadir.push_back(cursoData);
        }
        
        archivo.close();
        logInfo("Leer cursos", path + " (" + std::to_string(vectorCursoAnadir.size()) + " registros)");
        
    } catch (const std::exception& e) {
        logError("Leer cursos", path, "Error al procesar archivo: " + std::string(e.what()));
        archivo.close();
    }
}

inline void FilesManager::leerDatoEspecializacion(std::vector<RawEspecializacionData>& vectorEspecializacionAnadir) {
    if (!_sistemaInicializado) {
        logError("Leer especializaciones", "Sistema", "Sistema no inicializado");
        return;
    }

    auto path = getDataFilePathActividades(TipoActividad::ESPECIALIZACION);
    std::ifstream archivo(path, std::ios::in);

    if (!archivo.is_open()) {
        logError("Leer especializaciones", path, "No se pudo abrir el archivo");
        return;
    }

    try {
        std::string linea;
        
        while (std::getline(archivo, linea) && !linea.empty()) {
            RawEspecializacionData especializacionData;
            
            // Leer ID de la especialización
            especializacionData.id = std::stoi(linea);
            
            // Leer ID de la empresa
            if (!std::getline(archivo, linea)) break;
            especializacionData.idEmpresa = std::stoi(linea);
            
            // Leer nombre de la empresa
            if (!std::getline(archivo, linea)) break;
            especializacionData.nombreEmpresa = linea;
            
            // Leer título de la especialización
            if (!std::getline(archivo, linea)) break;
            especializacionData.titulo = linea;
            
            // Leer descripción de la especialización
            if (!std::getline(archivo, linea)) break;
            especializacionData.descripcion = linea;
            
            // Leer categoría (como número)
            if (!std::getline(archivo, linea)) break;
            int categoriaNumero = std::stoi(linea);
            especializacionData.categoria = static_cast<CategoriaActividad>(categoriaNumero);
            
            // Leer cantidad de cursos
            if (!std::getline(archivo, linea)) break;
            int cantidadCursos = std::stoi(linea);
            
            // Leer IDs de los cursos
            especializacionData.idsCursos.clear();
            for (int i = 0; i < cantidadCursos; ++i) {
                if (!std::getline(archivo, linea)) break;
                int idCurso = std::stoi(linea);
                especializacionData.idsCursos.push_back(idCurso);
            }
            
            // Leer duración estimada
            if (!std::getline(archivo, linea)) break;
            especializacionData.duracionEstimada = std::stoi(linea);
            
            // Agregar la especialización al vector
            vectorEspecializacionAnadir.push_back(especializacionData);
        }
        
        archivo.close();
        logInfo("Leer especializaciones", path + " (" + std::to_string(vectorEspecializacionAnadir.size()) + " registros)");
        
    } catch (const std::exception& e) {
        logError("Leer especializaciones", path, "Error al procesar archivo: " + std::string(e.what()));
        archivo.close();
    }
}

inline RawActividadesData FilesManager::leerDatosActividades() {
    if (!_sistemaInicializado) {
        logError("Leer actividades", "Sistema", "Sistema no inicializado");
        return RawActividadesData();
    }

    RawActividadesData actividades;
    bool exitoCursos = false;
    bool exitoEspecializaciones = false;

    try {
        // Leer cursos
        logInfo("Iniciando lectura", "Cursos");
        leerDatoCurso(actividades.cursos);
        exitoCursos = true;
        logInfo("Lectura completada", "Cursos - " + std::to_string(actividades.cursos.size()) + " registros");

        // Leer especializaciones
        logInfo("Iniciando lectura", "Especializaciones");
        leerDatoEspecializacion(actividades.especializaciones);
        exitoEspecializaciones = true;
        logInfo("Lectura completada", "Especializaciones - " + std::to_string(actividades.especializaciones.size()) + " registros");

        // Log de resumen
        logInfo("Lectura de actividades completada", 
                "Total: " + std::to_string(actividades.cursos.size()) + " cursos, " + 
                std::to_string(actividades.especializaciones.size()) + " especializaciones");

        return actividades;

    } catch (const std::exception& e) {
        std::string errorMsg = "Error al leer actividades: " + std::string(e.what());
        logError("Leer actividades", "Sistema", errorMsg);
        
        // Si hubo error parcial, retornar lo que se pudo leer
        if (exitoCursos || exitoEspecializaciones) {
            logInfo("Recuperación parcial", 
                    "Se pudieron leer " + std::to_string(actividades.cursos.size()) + " cursos y " + 
                    std::to_string(actividades.especializaciones.size()) + " especializaciones");
        }
        
        return actividades;
    }
}

// ========== MÉTODOS ADICIONALES DE CONTENIDO ==========

inline RawCursoData FilesManager::buscarCursoPorId(int id) {
    std::vector<RawCursoData> cursos;
    leerDatoCurso(cursos);
    
    for (const auto& curso : cursos) {
        if (curso.id == id) {
            logInfo("Buscar curso", "Curso encontrado ID: " + std::to_string(id));
            return curso;
        }
    }
    
    logInfo("Buscar curso", "Curso no encontrado ID: " + std::to_string(id));
    return RawCursoData(); // Retorna estructura vacía si no se encuentra
}

inline RawEspecializacionData FilesManager::buscarEspecializacionPorId(int id) {
    std::vector<RawEspecializacionData> especializaciones;
    leerDatoEspecializacion(especializaciones);
    
    for (const auto& especializacion : especializaciones) {
        if (especializacion.id == id) {
            logInfo("Buscar especialización", "Especialización encontrada ID: " + std::to_string(id));
            return especializacion;
        }
    }
    
    logInfo("Buscar especialización", "Especialización no encontrada ID: " + std::to_string(id));
    return RawEspecializacionData(); // Retorna estructura vacía si no se encuentra
}

inline std::vector<RawCursoData> FilesManager::obtenerCursosPorCategoria(CategoriaActividad categoria) {
    std::vector<RawCursoData> todosCursos;
    std::vector<RawCursoData> cursosCategoria;
    
    leerDatoCurso(todosCursos);
    
    for (const auto& curso : todosCursos) {
        if (curso.categoria == categoria) {
            cursosCategoria.push_back(curso);
        }
    }
    
    logInfo("Filtrar cursos por categoría", 
            "Encontrados " + std::to_string(cursosCategoria.size()) + " cursos en categoría " + std::to_string(static_cast<int>(categoria)));
    
    return cursosCategoria;
}

inline std::vector<RawEspecializacionData> FilesManager::obtenerEspecializacionesPorCategoria(CategoriaActividad categoria) {
    std::vector<RawEspecializacionData> todasEspecializaciones;
    std::vector<RawEspecializacionData> especializacionesCategoria;
    
    leerDatoEspecializacion(todasEspecializaciones);
    
    for (const auto& especializacion : todasEspecializaciones) {
        if (especializacion.categoria == categoria) {
            especializacionesCategoria.push_back(especializacion);
        }
    }
    
    logInfo("Filtrar especializaciones por categoría", 
            "Encontradas " + std::to_string(especializacionesCategoria.size()) + " especializaciones en categoría " + std::to_string(static_cast<int>(categoria)));
    
    return especializacionesCategoria;
}

inline bool FilesManager::existeCurso(int id) {
    std::vector<RawCursoData> cursos;
    leerDatoCurso(cursos);
    
    for (const auto& curso : cursos) {
        if (curso.id == id) {
            return true;
        }
    }
    
    return false;
}

inline bool FilesManager::existeEspecializacion(int id) {
    std::vector<RawEspecializacionData> especializaciones;
    leerDatoEspecializacion(especializaciones);
    
    for (const auto& especializacion : especializaciones) {
        if (especializacion.id == id) {
            return true;
        }
    }
    
    return false;
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
    
    // Logs domain
    std::cout << "DOMINIO LOGS:\n";
    std::cout << "  Error Logs: " << obtenerTamanoArchivo(DataPaths::Logs::ERROR_LOGS) << " bytes\n";
    std::cout << "  Info Logs: " << obtenerTamanoArchivo(DataPaths::Logs::INFO_LOGS) << " bytes\n";
    
    std::cout << "Estado del sistema: " << (_sistemaInicializado ? "Inicializado" : "No inicializado") << "\n";
    std::cout << "Último error: " << (_ultimoError.empty() ? "Ninguno" : _ultimoError) << "\n";
    std::cout << "================================================================\n";
    
    // Mostrar estadísticas detalladas de logs
    std::cout << obtenerEstadisticasLogs() << "\n";
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

// ========== FUNCIONES DE MANEJO DE LOGS ==========

inline FileOperationResult FilesManager::limpiarLogsAntiguos(int diasAntiguedad) {
    try {
        // Usar un enfoque más simple basado en el tamaño del archivo
        // Si el archivo es muy grande (>10MB), eliminarlo
        const size_t TAMANO_MAXIMO = 10 * 1024 * 1024; // 10MB
        
        // Limpiar logs de error
        if (std::filesystem::exists(DataPaths::Logs::ERROR_LOGS)) {
            auto tamano = std::filesystem::file_size(DataPaths::Logs::ERROR_LOGS);
            if (tamano > TAMANO_MAXIMO) {
                std::filesystem::remove(DataPaths::Logs::ERROR_LOGS);
                logInfo("Limpieza logs", "Archivo de logs de error eliminado por tamaño excesivo");
            }
        }
        
        // Limpiar logs de información
        if (std::filesystem::exists(DataPaths::Logs::INFO_LOGS)) {
            auto tamano = std::filesystem::file_size(DataPaths::Logs::INFO_LOGS);
            if (tamano > TAMANO_MAXIMO) {
                std::filesystem::remove(DataPaths::Logs::INFO_LOGS);
                logInfo("Limpieza logs", "Archivo de logs de información eliminado por tamaño excesivo");
            }
        }
        
        return FileOperationResult::SUCCESS;
        
    } catch (const std::exception& e) {
        logError("Limpieza logs", "Sistema", e.what());
        return FileOperationResult::UNKNOWN_ERROR;
    }
}

inline std::string FilesManager::obtenerEstadisticasLogs() {
    std::stringstream stats;
    
    stats << "\n========== ESTADÍSTICAS DE LOGS ==========\n";
    
    // Estadísticas del archivo de logs de error
    if (std::filesystem::exists(DataPaths::Logs::ERROR_LOGS)) {
        auto tamano = obtenerTamanoArchivo(DataPaths::Logs::ERROR_LOGS);
        
        stats << "Logs de Error:\n";
        stats << "  Archivo: " << DataPaths::Logs::ERROR_LOGS << "\n";
        stats << "  Tamaño: " << tamano << " bytes\n";
        
        // Mostrar información básica sin timestamp problemático
        if (tamano > 0) {
            stats << "  Estado: Archivo activo con datos\n";
        } else {
            stats << "  Estado: Archivo vacío\n";
        }
    } else {
        stats << "Logs de Error: Archivo no existe\n";
    }
    
    // Estadísticas del archivo de logs de información
    if (std::filesystem::exists(DataPaths::Logs::INFO_LOGS)) {
        auto tamano = obtenerTamanoArchivo(DataPaths::Logs::INFO_LOGS);
        
        stats << "Logs de Información:\n";
        stats << "  Archivo: " << DataPaths::Logs::INFO_LOGS << "\n";
        stats << "  Tamaño: " << tamano << " bytes\n";
        
        // Mostrar información básica sin timestamp problemático
        if (tamano > 0) {
            stats << "  Estado: Archivo activo con datos\n";
        } else {
            stats << "  Estado: Archivo vacío\n";
        }
    } else {
        stats << "Logs de Información: Archivo no existe\n";
    }
    
    stats << "==========================================\n";
    
    return stats.str();
}

#endif // COURSERACLONE_PERSISTENCE_FILESMANAGER_HPP