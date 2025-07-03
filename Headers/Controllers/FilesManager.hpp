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
#include "../Types/ComprobanteDePagoTypes.hpp"
#include "../Types/FilesTypes.hpp"
#include "../Utils/DataPaths.hpp"
#include "../DataStructures/algoritmosBusqueda.hpp"
#include "../Utils/Lambda.hpp"
#include "../DataStructures/HashTable.hpp"


class FilesManager {
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
	HashTable<std::string,RawCursoData> indiceCursos;
    HashTable<int,RawComprobanteData> indiceComprobantes;    
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
    void logInfo(const std::string& operation, const std::string& file, std::string details = "");

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
	/// @brief Carga los datos de los offsets de inscripciones con busqueda binaria
	/// @param id ID del estudiante
	/// @param offsets Vector donde se almacenarán los offsets encontrados
    FileOperationResult cargarOffsets(int id, std::vector<int>& offsets);

	/// @brief Carga los datos de inscripciones en bruto desde un archivo
	/// @param _offsets Vector de offsets de inscripciones
	/// @param is Archivo de entrada para leer los datos
    std::vector<RawInscripcionData> getInscripcionesRawData(std::vector<int> _offsets, std::ifstream& is);

    /// @brief Guarda los datos por oden de idUsuario
	FileOperationResult guardarInidiceInscripcion(int _idEstudiante, int _offset);

    /// @brief Guarda un usuario en formato binario
    /// @param bin Datos binarios del usuario
    /// @param tipo Tipo de usuario (ESTUDIANTE/EMPRESA)
    /// @param offset Posición donde se guardó (salida)
    ///  @return Resultado de la operación
    FileOperationResult guardarUsuarioBinario(const UsuarioBinario& bin, TipoUsuario tipo);

    UsuarioBinario getUsuarioBinario(int offset, TipoUsuario tipo);

    /// @brief Carga los índices de usuarios de un tipo específico
    /// @param tipo Tipo de usuario
    /// @return Vector con los índices cargados
    std::vector<UsuarioIndex> cargarIndicesUsuario(TipoUsuario tipo);

	/// @brief Busca el índice de un usuario por su email
	/// @param _email Email del usuario a buscar
	/// @param tipo Tipo de usuario (ESTUDIANTE/EMPRESA)
	int buscarIndexUsuario(std::string _email, int _tipoUsuario);

	/// @brief Elimina un índice de usuario por ID
	/// @param idUsuario ID del usuario a eliminar
	/// @param tipo Tipo de usuario
	/// @return Resultado de la operación
	FileOperationResult eliminarIndiceUsuario(std::string _email, TipoUsuario tipo);

    FileOperationResult updateUsuarioBinario(const UsuarioBinario& usuario);

    /// @brief Guarda un índice de usuario
    /// @param indice Índice a guardar
    /// @param tipo Tipo de usuario
    /// @return Resultado de la operación
    FileOperationResult guardarIndiceUsuario(UsuarioIndex& indice, TipoUsuario tipo);

    /// @brief Carga todas las inscripciones del estudiante
    /// @param id Id del estudiante
    /// @return Resultado de la operación
    FileOperationResult cargarInscripcionesPorEstudiante(int id, std::vector<RawInscripcionData>& inscripciones);

    /// @brief Guarda una inscripción en formato binario
    /// @param bin Datos de la inscripción
    /// @param offsetRegistro Posición donde se guardó (salida)
    /// @return Resultado de la operación
    FileOperationResult guardarInscripcionBinaria(const InscripcionBinaria& bin, int& offsetRegistro);

	/// @brief Devuelve la cantidad de inscripciones registradas en el sistema
    /// @return Cantidad de inscripciones
    int cantidadInscripciones();

	/// @brief Devuelve la cantidad de usuarios de un tipo específico
	/// @param _tipoUsuario Tipo de usuario a contar
	/// @return Cantidad de usuarios del tipo especificado
    int cantidadUsuarios(TipoUsuario _tipoUsuario);

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


    int contarFilasCSV(const std::string& ruta = DataPaths::Financial::DB_COMPROBANTES, bool tieneCabecera = true);

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

    /// @brief Escribe un mensaje de debug al archivo de logs
    /// @param mensaje Mensaje a escribir
    void escribirDebugLog(const std::string& mensaje);

    /// @brief Busca un curso por su nombre
    /// @param nombreCurso Nombre del curso a buscar
    /// @return Datos del curso encontrado, o estructura vacía si no se encuentra
    bool buscarCursoPorNombreHash(const std::string& nombre, RawCursoData& resultado);

    void FilesManager::cargarCursos();

    /// @brief Busca un curso por su ID en la tabla hash
    int obtenerIdCursoPorNombre(const std::string& nombreCurso);

    /// @brief carga los comprobantes y los agrega a la tabla hash
    void cargarComprobantes();

	/// @brief Busca un comprobante por su ID en la tabla hash
    bool buscarComprobantePorIdHash(int id, RawComprobanteData& resultado);

	/// @brief Obtiene el índice de cursos
    HashTable<std::string, RawCursoData>& getIndiceCursos();

};

// ========== INICIALIZACIÓN DE MIEMBROS ESTÁTICOS ==========
/// @brief Definición de la instancia única (inline para header-only)
inline std::unique_ptr<FilesManager> FilesManager::_instance = nullptr;

/// @brief Definición del flag para std::call_once
inline std::once_flag FilesManager::_onceFlag;

// ========== IMPLEMENTACIONES INLINE ==========
/// @brief Constructor privado
inline FilesManager::FilesManager() : _sistemaInicializado(false) {
    logInfo("Constructor", "FilesManager Singleton inicializado");
    inicializarSistemaArchivos();
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

inline void FilesManager::logInfo(const std::string& operation, const std::string& file, std::string details) {
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
		if (!details.empty()) {
			infoLogFile << "Detalles: " << details << std::endl;
		}
        infoLogFile.close();    }
    
	/// @brief También mostrar en consola para feedback inmediato - Comentar y descomentar para depuración
    //std::cout << "[FilesManager INFO] " << infoMessage << std::endl;
}

inline void FilesManager::escribirDebugLog(const std::string& mensaje) {
    // Escribir en el archivo de logs de información (se puede usar para debug)
    std::ofstream debugLogFile(DataPaths::Logs::INFO_LOGS, std::ios::app);
    if (debugLogFile.is_open()) {
        // Obtener timestamp actual
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        auto tm = *std::localtime(&time_t);
        
        debugLogFile << "[" << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << "] "
                     << "[DEBUG] " << mensaje << std::endl;
        debugLogFile.close();
    }
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
inline FileOperationResult FilesManager::cargarOffsets(int id, std::vector<int>& offsets) {
    offsets.clear();

    auto path = DataPaths::Core::INDICES_INSCRIPCIONES;
    std::fstream archivoOrden(path, std::ios::binary | std::ios::in | std::ios::ate);

    archivoOrden.seekg(0, std::ios::end);
    int cantidad = static_cast<int>(archivoOrden.tellg() / sizeof(InscripcionIndex));

    if (cantidad == 0) {
        logInfo("Leer inscripciones", path + " (No hay registros)");
        archivoOrden.close();
        return FileOperationResult::SUCCESS;
    }

    auto busqueda = crearPredicadoBusqueda(archivoOrden, id);
    int pos = busquedaBinaria(0, cantidad - 1, busqueda);

    if (pos < 0 || pos >= cantidad) {
        logInfo("Cargar inscripciones", "No se encontraron inscripciones para el ID: " + std::to_string(id));
        return FileOperationResult::SUCCESS;
    }
	logInfo("Cargar inscripciones", "Primer ID encontrado en: " + std::to_string(pos));

    int contador = 0;
    for (int i = pos; i < cantidad; i++) {
        contador++;
        InscripcionIndex tmpIndex;
        archivoOrden.seekg(i * sizeof(InscripcionIndex), std::ios::beg);
        archivoOrden.read(reinterpret_cast<char*>(&tmpIndex), sizeof(InscripcionIndex));
        if (tmpIndex.idUsuario == id) {
            offsets.push_back(tmpIndex.offset);
            logInfo("Cargar inscripciones", "Inscripcion encontrada: id " + std::to_string(tmpIndex.offset));
        }
    }
    

    logInfo("Cargar inscripciones", "Se han cargado " + std::to_string(cantidad) + " offsets de inscripciones");
    archivoOrden.close();

    return FileOperationResult::SUCCESS;
}

inline std::vector<RawInscripcionData> FilesManager::getInscripcionesRawData(std::vector<int> _offsets, std::ifstream& is) {
	std::vector<RawInscripcionData> inscripciones;

    for (int& offset : _offsets) {
        InscripcionBinaria inscripcion;
		RawInscripcionData rawInscripcion;

        is.seekg(offset * sizeof(InscripcionBinaria), std::ios::beg);
        is.read(reinterpret_cast<char*>(&inscripcion), sizeof(inscripcion));
        rawInscripcion.id = offset;
		rawInscripcion.completado = inscripcion.completado;
		rawInscripcion.idActividad = inscripcion.idActividad;
		rawInscripcion.idEstudiante = inscripcion.idEstudiante;
        rawInscripcion.tipo = static_cast<TipoActividad>(inscripcion.tipoActividad);
		rawInscripcion.progreso = inscripcion.progreso;
		rawInscripcion.pagado = inscripcion.pagado;
		
		inscripciones.push_back(rawInscripcion);
        logInfo("Cargar inscripciones", "Inscripción cargada: id " + std::to_string(inscripcion.idActividad));
    }

    return inscripciones;
}

inline FileOperationResult FilesManager::cargarInscripcionesPorEstudiante(int id, std::vector<RawInscripcionData>& inscripciones) {
    /*
    if (!_sistemaInicializado) {
        logError("Cargar inscripciones", "Sistema", "Sistema no inicializado");
        return FileOperationResult::UNKNOWN_ERROR;
    }
    */

    try {
        std::ifstream is(DataPaths::Core::DB_INSCRIPCIONES, std::ios::binary);

        if (!is.is_open()) {
            logError("Cargar inscripciones", DataPaths::Core::DB_INSCRIPCIONES, "Archivo no encontrado");
            return FileOperationResult::FILE_NOT_FOUND;
        }

		std::vector<int> offsets;

		FileOperationResult resultadoOffsets = cargarOffsets(id, offsets);
        if (resultadoOffsets == FileOperationResult::SUCCESS) {

            inscripciones.clear();
			inscripciones = getInscripcionesRawData(offsets, is);
			is.close();
			logInfo("Cargar inscripciones", "Se han cargado " + std::to_string(inscripciones.size()) + " inscripciones para el ID: " + std::to_string(id));
		}
        else {
			logError("Cargar inscripciones", "Sistema", "Error al cargar offsets");
            return FileOperationResult::UNKNOWN_ERROR;
        }

		
        return FileOperationResult::SUCCESS;

    }
    catch (const std::exception& e) {
        logError("Cargar inscripciones", "Sistema", e.what());
        return FileOperationResult::UNKNOWN_ERROR;
    }
}

inline UsuarioBinario FilesManager::getUsuarioBinario(int offset, TipoUsuario tipo) {
    try {
        auto path = getDataFilePath(tipo);
        std::ifstream is(path, std::ios::binary | std::ios::in);
        UsuarioBinario tmp;
        is.seekg(offset * sizeof(UsuarioBinario), std::ios::beg);
        is.read(reinterpret_cast<char*> (&tmp), sizeof(UsuarioBinario));
		logInfo("Cargar Usuario por index", path + " (Offset: " + std::to_string(offset) + ")");
		return tmp;

    }
    catch (const std::exception& e) {
        logError("Cargar Usuario por index", "Sistema", e.what());
        return UsuarioBinario();
    }
}

inline FileOperationResult FilesManager::guardarUsuarioBinario(const UsuarioBinario& bin,TipoUsuario tipo) {
    /*
    if (!_sistemaInicializado) {
        logError("Guardar usuario", "Sistema", "Sistema no inicializado");
        return FileOperationResult::UNKNOWN_ERROR;
    }
    */
    
    try {
        auto path = getDataFilePath(tipo);
        std::ofstream os(path, std::ios::binary | std::ios::app);
        
        if (!os.is_open()) {
            logError("Guardar usuario", path, "No se pudo abrir el archivo");
            return FileOperationResult::FILE_NOT_FOUND;
        }
        
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

inline FileOperationResult FilesManager::guardarInidiceInscripcion(int _idEstudiante, int _offset) {
    auto path = DataPaths::Core::INDICES_INSCRIPCIONES;
    std::fstream archivoOrden(path, std::ios::binary | std::ios::in | std::ios::out);
	if (!archivoOrden.is_open()) {
		logError("Guardar índice de inscripciones", path, "No se pudo abrir el archivo");
		return FileOperationResult::FILE_NOT_FOUND;
	}
	try {
		archivoOrden.seekg(0, std::ios::end);
		int cantidad = static_cast<int>(archivoOrden.tellg() / sizeof(InscripcionIndex));

        InscripcionIndex nuevoIndice(_idEstudiante, _offset);
        if (cantidad == 0) {
			archivoOrden.seekp(0, std::ios::beg); // Si es el primer registro, ir al inicio
			archivoOrden.write(reinterpret_cast<char*>(&nuevoIndice), sizeof(InscripcionIndex));
            archivoOrden.close();
			logInfo("Guardar índice de inscripciones", path + " (1 registro)");
			return FileOperationResult::SUCCESS;
        }

		archivoOrden.seekg(0, std::ios::beg);
        auto busqueda = crearPredicadoBusqueda(archivoOrden, _idEstudiante);

        int pos = busquedaBinaria(0, cantidad - 1, busqueda);
        for (int i = cantidad - 1; i >= pos; i--) {
			InscripcionIndex tmp;
			archivoOrden.seekg(i * sizeof(InscripcionIndex), std::ios::beg);
			archivoOrden.read(reinterpret_cast<char*>(&tmp), sizeof(InscripcionIndex));
			archivoOrden.seekp((i + 1) * sizeof(InscripcionIndex), std::ios::beg);
			archivoOrden.write(reinterpret_cast<char*>(&tmp), sizeof(InscripcionIndex));
        }
        
		archivoOrden.seekp(pos * sizeof(InscripcionIndex), std::ios::beg);
		archivoOrden.write(reinterpret_cast<char*>(&nuevoIndice), sizeof(InscripcionIndex));
        archivoOrden.close();

        logInfo("Guardar índice de inscripciones", path + " (Busqueda binaria)");
        return FileOperationResult::SUCCESS;
		

    } catch (const std::exception& e) {
        logError("Guardar índice de inscripciones", "Sistema", e.what());
        return FileOperationResult::UNKNOWN_ERROR;
    }
}

inline std::vector<UsuarioIndex> FilesManager::cargarIndicesUsuario(TipoUsuario tipo) {
    std::vector<UsuarioIndex> indices;
    /*
    if (!_sistemaInicializado) {
        logError("Cargar índices", "Sistema", "Sistema no inicializado");
        return indices;
    }
    */
    
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

inline int FilesManager::buscarIndexUsuario(std::string _email, int _tipoUsuario) {
    TipoUsuario tipoUsuario = static_cast<TipoUsuario>(_tipoUsuario);

	if (!_sistemaInicializado) {
		logError("Buscar índice de usuario", "Sistema", "Sistema no inicializado");
		return -1; // Indica error
	}
	
	std::string indexPath = getIndexFilePath(tipoUsuario);
	std::ifstream is(indexPath, std::ios::in | std::ios::binary);
	if (!is.is_open()) {
		logError("Buscar índice de usuario", indexPath, "No se pudo abrir el archivo");
		return -1; // Indica error
	}

    is.seekg(0, std::ios::end);
    int cantidad = static_cast<int>(is.tellg() / sizeof(UsuarioIndex));
    if (cantidad == 0) {
		logInfo("Buscar índice de usuario", indexPath + " (No hay registros)");
		is.close();
		return -1; // No encontrado
    }

	auto busqueda = crearPredicadoBusquedaUsuario(is, _email);
	int pos = busquedaBinaria(0, cantidad - 1, busqueda);

    // Verificar la coincidencia exacta
    if (pos < cantidad) {
        UsuarioIndex encontrado;
        is.seekg(pos * sizeof(UsuarioIndex), std::ios::beg);
        is.read(reinterpret_cast<char*>(&encontrado), sizeof(encontrado));
        if (std::strncmp(encontrado.nombreDeUsuario, _email.c_str(), MAX_FIELD_LEN) == 0) {
			logInfo("Buscar índice de usuario", "Usuario encontrado: " + _email + " en posición " + std::to_string(pos));
			is.close();
            return encontrado.offset;
        }
    }
	logInfo("Buscar índice de usuario", "Usuario no encontrado: " + _email);
	is.close();
    return -1;
}

inline FileOperationResult FilesManager::eliminarIndiceUsuario(std::string _email, TipoUsuario tipo) {
    if (!_sistemaInicializado) {
        logError("Buscar índice de usuario", "Sistema", "Sistema no inicializado");
        return FileOperationResult::FILE_NOT_FOUND; // Indica error
    }
    try {
		int idUsuario = buscarIndexUsuario(_email, static_cast<int>(tipo));
		auto path = getIndexFilePath(tipo);
		std::fstream archivoOrden(path, std::ios::binary | std::ios::in | std::ios::out);
		archivoOrden.seekg(0, std::ios::end);
		int cantidad = static_cast<int>(archivoOrden.tellg() / sizeof(UsuarioIndex));
        for (int i = idUsuario; i < cantidad - 1; i++) {
			UsuarioIndex tmp;
			archivoOrden.seekg((i + 1) * sizeof(UsuarioIndex), std::ios::beg);
			archivoOrden.read(reinterpret_cast<char*>(&tmp), sizeof(UsuarioIndex));
			archivoOrden.seekp(i * sizeof(UsuarioIndex), std::ios::beg);
			archivoOrden.write(reinterpret_cast<char*>(&tmp), sizeof(UsuarioIndex));
        }
        archivoOrden.close();
        try {
			/// Truncar el archivo para eliminar el último registro. Utilizamos 'uinmax_t'
            std::filesystem::resize_file(path, static_cast<std::uintmax_t>((cantidad - 1) * sizeof(UsuarioIndex)));
			logInfo("Eliminar índice de usuario", "Archivo truncado a " + std::to_string((cantidad - 1) * sizeof(UsuarioIndex)) + " bytes");
        }
        catch (const std::exception& e) {
            logError("Eliminar índice de usuario", path, "Error al truncar archivo: " + std::string(e.what()));
            return FileOperationResult::UNKNOWN_ERROR;
        }

        logInfo("Eliminar indice usuario", "Indice eliminado en la posicion " + std::to_string(idUsuario));
		return FileOperationResult::SUCCESS;
    }
	catch (const std::exception& e) {
		logError("Eliminar índice de usuario", "Sistema", e.what());
		return FileOperationResult::UNKNOWN_ERROR;
	}
}

inline FileOperationResult FilesManager::updateUsuarioBinario(const UsuarioBinario& usuario) {
    if (!_sistemaInicializado) {
        logError("Buscar índice de usuario", "Sistema", "Sistema no inicializado");
        return FileOperationResult::FILE_NOT_FOUND; // Indica error
    }
    try {
		auto path = getDataFilePath(usuario.tipoUsuario);
		std::fstream archivo(path, std::ios::binary | std::ios::in | std::ios::out);
        if (!archivo.is_open()) {
            logError("Actualizar usuario binario", path, "No se pudo abrir el archivo");
            return FileOperationResult::FILE_NOT_FOUND;
        }
        
		int id = usuario.id;
        archivo.seekg((id) * sizeof(UsuarioBinario), std::ios::beg);
		if (archivo.eof()) {
			logError("Actualizar usuario binario", path, "Posición fuera de rango");
			archivo.close();
			return FileOperationResult::FILE_NOT_FOUND;
		}
		archivo.write(reinterpret_cast<const char*>(&usuario), sizeof(UsuarioBinario));

		if (!archivo.good()) {
			logError("Actualizar usuario binario", path, "Error al escribir datos");
			archivo.close();
			return FileOperationResult::UNKNOWN_ERROR;
		}

		archivo.close();
		logInfo("Actualizar usuario binario", path + " (ID: " + std::to_string(usuario.id) + ")");
		return FileOperationResult::SUCCESS;
		

    }
	catch (const std::exception& e) {
		logError("Actualizar usuario binario", "Sistema", e.what());
		return FileOperationResult::UNKNOWN_ERROR;
	}
}

inline FileOperationResult FilesManager::guardarIndiceUsuario(UsuarioIndex& indice, TipoUsuario tipo) {
	auto path = getIndexFilePath(tipo);
    std::fstream archivoOrden(path, std::ios::binary | std::ios::in | std::ios::out);

    if (!archivoOrden.is_open()) {
		logError("Guardar índice de usuario", path, "No se pudo abrir el archivo");
		return FileOperationResult::FILE_NOT_FOUND;
	}
    try {
        archivoOrden.seekg(0, std::ios::end);
        int cantidad = static_cast<int>(archivoOrden.tellg() / sizeof(UsuarioIndex));

		

        if (cantidad == 0) {
            archivoOrden.seekp(0, std::ios::beg); // Si es el primer registro, ir al inicio
            archivoOrden.write(reinterpret_cast<char*>(&indice), sizeof(UsuarioIndex));
            archivoOrden.close();
            logInfo("Guardar índice de usuarios", path + " (1 registro)");
            return FileOperationResult::SUCCESS;
        }

        archivoOrden.seekg(0, std::ios::beg);
        auto busqueda = crearPredicadoBusquedaUsuarioLecEsc(archivoOrden, std::string(indice.nombreDeUsuario));
        int pos = busquedaBinaria(0, cantidad - 1, busqueda);

        for (int i = cantidad - 1; i >= pos; i--) {
            UsuarioIndex tmp;
            archivoOrden.seekg(i * sizeof(UsuarioIndex), std::ios::beg);
            archivoOrden.read(reinterpret_cast<char*>(&tmp), sizeof(UsuarioIndex));
            archivoOrden.seekp((i + 1) * sizeof(UsuarioIndex), std::ios::beg);
            archivoOrden.write(reinterpret_cast<char*>(&tmp), sizeof(UsuarioIndex));
        }

        archivoOrden.seekp(pos * sizeof(UsuarioIndex), std::ios::beg);
        archivoOrden.write(reinterpret_cast<char*>(&indice), sizeof(UsuarioIndex));
        archivoOrden.close();

        logInfo("Guardar índice de usuarios", path + " (Busqueda binaria)");
        return FileOperationResult::SUCCESS;


    }
    catch (const std::exception& e) {
        logError("Guardar índice de usuarios", "Sistema", e.what());
        return FileOperationResult::UNKNOWN_ERROR;
    }
}

inline FileOperationResult FilesManager::guardarInscripcionBinaria(const InscripcionBinaria& bin,int& offsetRegistro) {
    
    if (!_sistemaInicializado) {
        logError("Guardar inscripción", "Sistema", "Sistema no inicializado");
        return FileOperationResult::UNKNOWN_ERROR;
    }
    
    
    try {
        auto path = DataPaths::Core::DB_INSCRIPCIONES;
        std::fstream os(path, std::ios::binary | std::ios::in | std::ios::out);
        
        if (!os.is_open()) {
            logError("Guardar inscripción", DataPaths::Core::DB_INSCRIPCIONES, "No se pudo abrir el archivo");
            return FileOperationResult::FILE_NOT_FOUND;
        }

        os.seekg((offsetRegistro) * sizeof(InscripcionBinaria), std::ios::beg);
        if (os.eof()) {
            logError("Actualizar usuario binario", path, "Posición fuera de rango");
            os.close();
            return FileOperationResult::FILE_NOT_FOUND;
        }
        os.write(reinterpret_cast<const char*>(&bin), sizeof(InscripcionBinaria));
  
        
        if (!os.good()) {
            logError("Guardar inscripción", DataPaths::Core::DB_INSCRIPCIONES, "Error al escribir datos");
            return FileOperationResult::UNKNOWN_ERROR;
        }
        
        logInfo("Guardar inscripción " + std::to_string(offsetRegistro), DataPaths::Core::DB_INSCRIPCIONES);
        os.close();
        return FileOperationResult::SUCCESS;
        
    } catch (const std::exception& e) {
        logError("Guardar inscripción", "Sistema", e.what());
        return FileOperationResult::UNKNOWN_ERROR;
    }
}

inline int FilesManager::cantidadInscripciones() {
    /*
    if (!_sistemaInicializado) {
        logError("Cantidad de inscripciones", "Sistema", "Sistema no inicializado");
        return -1; // Indica error
    }
    */
    std::ifstream archivo(DataPaths::Core::DB_INSCRIPCIONES, std::ios::binary);
    if (!archivo.is_open()) {
        logError("Cantidad de inscripciones", DataPaths::Core::DB_INSCRIPCIONES, "No se pudo abrir el archivo");
        return -1; // Indica error
    }
    archivo.seekg(0, std::ios::end);
    int cantidad = static_cast<int>(archivo.tellg() / sizeof(InscripcionBinaria));
    archivo.close();
    logInfo("Cantidad de inscripciones", DataPaths::Core::DB_INSCRIPCIONES + " (" + std::to_string(cantidad) + " registros)");
    return cantidad;
}

inline int FilesManager::cantidadUsuarios(TipoUsuario _tipoUsuario) {
	auto path = getDataFilePath(_tipoUsuario);
    std::ifstream archivo(path, std::ios::binary);
	if (!archivo.is_open()) {
		logError("Cantidad de usuarios", path, "No se pudo abrir el archivo");
		return -1; // Indica error
	}
	archivo.seekg(0, std::ios::end);
	int cantidad = static_cast<int>(archivo.tellg() / sizeof(UsuarioBinario));
	archivo.close();
	logInfo("Cantidad de usuarios", path + " (" + std::to_string(cantidad) + " registros)");
	return cantidad;
}

// ========== DOMINIO CONTENT ==========

inline void FilesManager::leerDatoCurso(std::vector<RawCursoData>& vectorCursoAnadir) {
    if (!_sistemaInicializado) {
        logError("Leer cursos", "Sistema", "Sistema no inicializado");
        return;
    }

    const std::string path = DataPaths::Content::DB_CURSOS;
    std::ifstream archivo(path);

    if (!archivo.is_open()) {
        logError("Leer cursos", path, "No se pudo abrir el archivo");
        return;
    }

    logInfo("Iniciando lectura", "Cursos");
    escribirDebugLog("Iniciando lectura de cursos desde: " + path + " con delimitador \'%%%\'");

    std::string linea;
    RawCursoData cursoData;
    int cursosLeidos = 0;
    int lineCount = 0;
    bool leyendoClases = false;
    int clasesPorLeer = 0;
    int clasesLeidasActual = 0;
    bool enCurso = false; // Para rastrear si estamos procesando un curso

    while (std::getline(archivo, linea)) {
        lineCount++;
        
        // Skip empty lines
        if (linea.empty()) {
            continue;
        }

        // Check for course delimiter
        if (linea == "%%%") {
            // If we have a valid course, add it to the vector
            if (enCurso && cursoData.id != -1 && !cursoData.titulo.empty() && cursoData.idEmpresa != -1) {
                // Verify all classes were read correctly
                if (clasesLeidasActual == clasesPorLeer) {
                    vectorCursoAnadir.push_back(cursoData);
                    escribirDebugLog("Curso ID: " + std::to_string(cursoData.id) + " agregado correctamente");
                    cursosLeidos++;
                } else {
                    escribirDebugLog("Curso ID: " + std::to_string(cursoData.id) + " descartado - clases incompletas (" + 
                        std::to_string(clasesLeidasActual) + "/" + std::to_string(clasesPorLeer) + ")");
                }
            } else if (enCurso) {
                escribirDebugLog("Curso ID: " + std::to_string(cursoData.id) + " descartado - datos incompletos");
            }
            
            // Reset for next course
            cursoData = RawCursoData();
            leyendoClases = false;
            clasesPorLeer = 0;
            clasesLeidasActual = 0;
            enCurso = false;
            
            if (archivo.eof()) break;
            
            escribirDebugLog("Leyendo curso #" + std::to_string(cursosLeidos + 1));
            continue;
        }

        // Start of a new course
        if (!enCurso) {
            try {
                // Read course ID (first line of course data)
                cursoData.id = std::stoi(linea);
                enCurso = true;
                escribirDebugLog("Leyendo curso ID: " + std::to_string(cursoData.id));

                // Read company ID (next line)
                if (!std::getline(archivo, linea)) {
                    escribirDebugLog("Error: EOF inesperado después de ID del curso");
                    break;
                }
                cursoData.idEmpresa = std::stoi(linea);

                // Read company name (next line)
                if (!std::getline(archivo, cursoData.nombreEmpresa)) {
                    escribirDebugLog("Error: EOF inesperado después de ID de empresa");
                    break;
                }

                // Read course title (next line)
                if (!std::getline(archivo, cursoData.titulo)) {
                    escribirDebugLog("Error: EOF inesperado después de nombre de empresa");
                    break;
                }

                // Read course description (next line)
                if (!std::getline(archivo, cursoData.descripcion)) {
                    escribirDebugLog("Error: EOF inesperado después de título del curso");
                    break;
                }

                // Read category (next line)
                if (!std::getline(archivo, linea)) {
                    escribirDebugLog("Error: EOF inesperado después de descripción del curso");
                    break;
                }

                try {
                    // Remove any whitespace from the category string
                    linea.erase(std::remove_if(linea.begin(), linea.end(), ::isspace), linea.end());
                    cursoData.categoria = RawActividadData::stringToCategoria(linea);
                    escribirDebugLog("Categoría leída: " + linea);
                }
                catch (const std::exception& e) {
                    escribirDebugLog("Advertencia: Categoría no válida '" + linea + "'. Usando valor por defecto. Error: " + e.what());
                    cursoData.categoria = CategoriaActividad::OTROS;
                }

                // Read instructor (next line)
                if (!std::getline(archivo, cursoData.instructor)) {
                    escribirDebugLog("Error: EOF inesperado después de categoría");
                    break;
                }

                // Read number of classes (next line)
                if (!std::getline(archivo, linea)) {
                    escribirDebugLog("Error: EOF inesperado después de instructor");
                    break;
                }

                try {
                    clasesPorLeer = std::stoi(linea);
                    cursoData.cantidadClases = clasesPorLeer;
                    escribirDebugLog("Cantidad de clases: " + std::to_string(clasesPorLeer));

                    if (clasesPorLeer > 0) {
                        leyendoClases = true;
                        clasesLeidasActual = 0;
                 
                    }
                    else {
                        escribirDebugLog("Advertencia: El curso no tiene clases definidas");
                    }
                }
                catch (const std::invalid_argument& e) {
                    escribirDebugLog("Error: Número de clases no válido: " + linea);
                    enCurso = false;
                    continue;
                }
                catch (const std::out_of_range& e) {
                    escribirDebugLog("Error: Número de clases fuera de rango: " + linea);
                    enCurso = false;
                    continue;
                }
            }
            catch (const std::exception& e) {
                escribirDebugLog("Error inesperado al leer datos del curso: " + std::string(e.what()));
                enCurso = false;
                continue;
            }
        } else if (leyendoClases && clasesLeidasActual < clasesPorLeer) // Reading class data if we're in the middle of reading classes 
            {
                std::string tituloClase = linea;
                std::string descripcionClase;
                
                // Read class description (next line)
                if (!std::getline(archivo, descripcionClase)) {
                    escribirDebugLog("Error: EOF inesperado después del título de la clase #" + 
                                  std::to_string(clasesLeidasActual + 1) + " del curso ID: " + std::to_string(cursoData.id));
                    enCurso = false;
                    continue;
                }
                
                // Add class data to the course
                cursoData.descripcionClases.push_back({ tituloClase, descripcionClase });

                clasesLeidasActual++;
                
                escribirDebugLog("  Clase #" + std::to_string(clasesLeidasActual) + 
                              "/" + std::to_string(clasesPorLeer) + 
                              ": " + tituloClase);
                
                // If we've read all expected classes, mark as done
                if (clasesLeidasActual >= clasesPorLeer) {
                    leyendoClases = false;
                    escribirDebugLog("Todas las clases leídas para el curso ID: " + std::to_string(cursoData.id));
                }
        } else if (leyendoClases) {
            // This block should not be reached if we're properly handling class data above
            escribirDebugLog("Error: Estado inesperado - leyendoClases es true pero no se esperaba aquí");
            leyendoClases = false;
        }
    }
    // Handle the last course if the file doesn't end with %%%
    if (enCurso && cursoData.id != -1 && !cursoData.titulo.empty() && cursoData.idEmpresa != -1) {
        // Verify all required classes were read
        if (clasesLeidasActual == clasesPorLeer) {
            // Check if the course is already in the list
            bool yaExiste = false;
            for (const auto& curso : vectorCursoAnadir) {
                if (curso.id == cursoData.id) {
                    yaExiste = true;
                    break;
                }
            }
            
            if (!yaExiste) {
                vectorCursoAnadir.push_back(cursoData);
                escribirDebugLog("Último curso (ID: " + std::to_string(cursoData.id) + ") agregado correctamente");
                cursosLeidos++;
            } else {
                escribirDebugLog("Advertencia: Curso duplicado ID: " + std::to_string(cursoData.id) + ". Ignorando.");
            }
        } else {
            escribirDebugLog("Advertencia: Último curso (ID: " + std::to_string(cursoData.id) + ") no agregado - clases incompletas (" + 
                std::to_string(clasesLeidasActual) + "/" + std::to_string(clasesPorLeer) + ")");
        }
    } else if (enCurso) {
        escribirDebugLog("Advertencia: Último curso (ID: " + std::to_string(cursoData.id) + ") no agregado - datos incompletos");
    }

    // Log final statistics
    std::string mensajeFinal = "Lectura de cursos completada. ";
    mensajeFinal += "Cursos leídos: " + std::to_string(cursosLeidos) + ". ";
    mensajeFinal += "Total en memoria: " + std::to_string(vectorCursoAnadir.size());
    
    logInfo("Leer cursos", path + " (" + std::to_string(cursosLeidos) + " registros)");
    escribirDebugLog(mensajeFinal);
    
    // Log the first few courses for verification
    int cursosAMostrar = (std::min)(3, static_cast<int>(vectorCursoAnadir.size()));
    for (int i = 0; i < cursosAMostrar; i++) {
        escribirDebugLog("  Curso #" + std::to_string(i+1) + ": ID=" + std::to_string(vectorCursoAnadir[i].id) + 
                        ", Título='" + vectorCursoAnadir[i].titulo + "'" +
                        ", Categoría='" + std::to_string(static_cast<int>(vectorCursoAnadir[i].categoria)) + "'" +
                        ", Clases='" + std::to_string(vectorCursoAnadir[i].cantidadClases) + "'");
    }
    
    if (vectorCursoAnadir.empty()) {
        escribirDebugLog("ADVERTENCIA: No se encontraron cursos válidos en el archivo");
    }
}


inline void FilesManager::leerDatoEspecializacion(std::vector<RawEspecializacionData>& vectorEspecializacionAnadir) {
    std::string filePath = DataPaths::Content::DB_ESPECIALIZACIONES;
    std::ifstream file(filePath);

    if (!file.is_open()) {
        logError("Leer especializaciones", filePath, "No se pudo abrir el archivo.");
        return;
    }

    escribirDebugLog("Iniciando lectura de especializaciones desde: " + filePath + " con delimitador '%%%'");

    std::string linea;
    std::string delimitador = "%%%";
    int especializacionCount = 0;

    while (true) {
        RawEspecializacionData especializacion; 
        especializacion.id = -1; // Initialize fields to default/invalid state
        especializacion.idEmpresa = -1;
        especializacion.cantidadCursos = 0; // Explicitly initialize to 0
        especializacion.duracionEstimada = 0;
        // std::string and std::vector are default-initialized correctly (empty)

        if (!std::getline(file, linea)) break; 
        if (linea.empty() && file.eof()) break; 
        try {
            especializacion.id = std::stoi(linea);
        } catch (const std::exception& e) {
            logError("Leer especializaciones", filePath, "Error al convertir idEspecializacion: '" + linea + "'. Error: " + e.what());
            while(std::getline(file, linea) && linea != delimitador) {}
            if (!file) break;
            continue;
        }
        escribirDebugLog("Record #" + std::to_string(especializacionCount + 1) + ": Parsed idEspecializacion: " + std::to_string(especializacion.id));

        if (!std::getline(file, linea)) { logError("Leer especializaciones", filePath, "EOF inesperado después de idEspecializacion para ID: " + std::to_string(especializacion.id)); break; }
        try {
            especializacion.idEmpresa = std::stoi(linea);
        } catch (const std::exception& e) {
            logError("Leer especializaciones", filePath, "Error al convertir idEmpresa: '" + linea + "' para Esp ID: " + std::to_string(especializacion.id) + ". Error: " + e.what());
            while(std::getline(file, linea) && linea != delimitador) {}
            if (!file) break;
            continue;
        }

        if (!std::getline(file, linea)) { logError("Leer especializaciones", filePath, "EOF inesperado antes de nombreEmpresa para Esp ID: " + std::to_string(especializacion.id)); break; }
        especializacion.nombreEmpresa = linea;

        std::string categoriaStr;
        if (!std::getline(file, linea)) { logError("Leer especializaciones", filePath, "EOF inesperado antes de categoriaStr para Esp ID: " + std::to_string(especializacion.id)); break; }
        categoriaStr = linea;
        try {
            especializacion.categoria = RawActividadData::stringToCategoria(categoriaStr);
        } catch (const std::runtime_error& e) {
            logError("Leer especializaciones", filePath, "Error al convertir categoria: '" + categoriaStr + "' para Esp ID: " + std::to_string(especializacion.id) + ". Error: " + e.what());
            especializacion.categoria = CategoriaActividad::DEFAULT; // Default o manejo de error
        }
        
        if (!std::getline(file, linea)) { logError("Leer especializaciones", filePath, "EOF inesperado antes de titulo para Esp ID: " + std::to_string(especializacion.id)); break; }
        especializacion.titulo = linea;
        escribirDebugLog("Esp ID " + std::to_string(especializacion.id) + " - Titulo leido: '" + especializacion.titulo + "'");

        if (!std::getline(file, linea)) { logError("Leer especializaciones", filePath, "EOF inesperado antes de descripcion para Esp ID: " + std::to_string(especializacion.id)); break; }
        especializacion.descripcion = linea;
        escribirDebugLog("Esp ID " + std::to_string(especializacion.id) + " - Descripcion leida: '" + especializacion.descripcion + "'");

        if (!std::getline(file, linea)) { 
            logError("Leer especializaciones", filePath, "EOF inesperado antes de numCursos para Esp ID: " + std::to_string(especializacion.id));
            break; 
        }
        escribirDebugLog("Esp ID " + std::to_string(especializacion.id) + " - Linea para numCursos: '" + linea + "'");
        try {
            especializacion.cantidadCursos = std::stoi(linea);
        } catch (const std::invalid_argument& ia) {
            logError("Leer especializaciones", filePath, "Error (invalid_argument) al convertir numCursos a entero para Esp ID: " + std::to_string(especializacion.id) + ". Línea: '" + linea + "'. Error: " + ia.what());
            while(std::getline(file, linea) && linea != delimitador) {}
            if (!file) break;
            continue;
        } catch (const std::out_of_range& oor) {
            logError("Leer especializaciones", filePath, "Error (out_of_range) al convertir numCursos para Esp ID: " + std::to_string(especializacion.id) + ". Línea: '" + linea + "'. Error: " + oor.what());
            while(std::getline(file, linea) && linea != delimitador) {}
            if (!file) break;
            continue;
        }
        escribirDebugLog("Esp ID " + std::to_string(especializacion.id) + " - numCursos parseado: " + std::to_string(especializacion.cantidadCursos));

        std::string idsCursosLinea;
        if (!std::getline(file, idsCursosLinea)) { 
            logError("Leer especializaciones", filePath, "EOF inesperado antes de idsCursos para Esp ID: " + std::to_string(especializacion.id));
            break; 
        }
        escribirDebugLog("Esp ID " + std::to_string(especializacion.id) + " - Linea para idsCursos: '" + idsCursosLinea + "'");
        
        std::stringstream ss(idsCursosLinea);
        std::string idCursoStr;
        int idCursoVal; // Renamed to avoid conflict with a potential global
        especializacion.idsCursos.clear(); 
        while (std::getline(ss, idCursoStr, ',')) {
            escribirDebugLog("Esp ID " + std::to_string(especializacion.id) + " - Procesando token idCurso: '" + idCursoStr + "'");
            try {
                idCursoVal = std::stoi(idCursoStr);
                especializacion.idsCursos.push_back(idCursoVal);
            } catch (const std::invalid_argument& ia) {
                logError("Leer especializaciones", filePath, "Error (invalid_argument) al convertir ID de curso a entero: '" + idCursoStr + "' para Esp ID: " + std::to_string(especializacion.id) + ". Error: " + ia.what());
            } catch (const std::out_of_range& oor) {
                logError("Leer especializaciones", filePath, "Error (out_of_range) al convertir ID de curso: '" + idCursoStr + "' para Esp ID: " + std::to_string(especializacion.id) + ". Error: " + oor.what());
            }
        }
        escribirDebugLog("Esp ID " + std::to_string(especializacion.id) + " - idsCursos parseados count: " + std::to_string(especializacion.idsCursos.size()));

        escribirDebugLog("Esp ID " + std::to_string(especializacion.id) + " - ANTES DE CHECK: numCursos = " + std::to_string(especializacion.cantidadCursos) + ", idsCursos.size() = " + std::to_string(especializacion.idsCursos.size()));
        if (especializacion.idsCursos.size() != static_cast<size_t>(especializacion.cantidadCursos)) {
            logError("Leer especializaciones", filePath, 
                     "Inconsistencia en IDs de cursos para especialización ID: " + std::to_string(especializacion.id) +
                     ". Esperados: " + std::to_string(especializacion.cantidadCursos) +
                     ", Encontrados: " + std::to_string(especializacion.idsCursos.size()) +
                     ". Linea IDs: '" + idsCursosLinea + "'");
            while(std::getline(file, linea) && linea != delimitador) {} 
            if (!file && linea != delimitador) break; // If EOF and no delimiter found
            if (linea != delimitador && std::getline(file, linea) && linea != delimitador) { // check next line if current wasn't delimiter
                 // If still not delimiter after consuming one more line, or EOF
                 if (!file) break;
            }
            if (!file && linea != delimitador) break; // Check again if EOF reached before finding delimiter
            if (linea != delimitador) { // If after all attempts, delimiter is not found (and not EOF)
                 logError("Leer especializaciones", filePath, "Consumido hasta non-delimiter '" + linea + "' para Esp ID " + std::to_string(especializacion.id) + ", pero no '%%%' o EOF.");
                 // break; // Decide if this is fatal for the whole file reading
            }
            continue; 
        }

        if (!std::getline(file, linea)) { 
            logError("Leer especializaciones", filePath, "EOF inesperado antes de duracionEstimada para Esp ID: " + std::to_string(especializacion.id));
            break; 
        }
        try {
            especializacion.duracionEstimada = std::stoi(linea);
        } catch (const std::exception& e) {
            logError("Leer especializaciones", filePath, "Error al convertir duracionEstimada: '" + linea + "' para Esp ID: " + std::to_string(especializacion.id) + ". Error: " + e.what());
            while(std::getline(file, linea) && linea != delimitador) {}
            if (!file) break;
            continue;
        }

        if (!std::getline(file, linea) || linea != delimitador) {
            if (file.eof() && (linea.empty() || linea != delimitador) && especializacionCount == 0 && vectorEspecializacionAnadir.empty() && especializacion.id != -1) {
                 // Special case: if it's the first record, and we parsed something, but then EOF instead of '%%%'

                 // This might be a valid single record file without a trailing delimiter.
                 // However, our format expects '%%%'

                 logError("Leer especializaciones", filePath, "Archivo parece tener un solo registro sin delimitador '%%%' final, o formato incorrecto. Ultima linea: '" + linea + "' para Esp ID: " + std::to_string(especializacion.id));
            } else if (linea != delimitador) {
                logError("Leer especializaciones", filePath, "Delimitador '%%%' no encontrado después de especialización ID: " + std::to_string(especializacion.id) + ". Encontrado: '" + linea + "'");
            } else { // !file case
                 logError("Leer especializaciones", filePath, "EOF inesperado buscando delimitador para especialización ID: " + std::to_string(especializacion.id));
            }
            break; 
        }
        
        escribirDebugLog("Delimitador '%%%' encontrado para especialización ID: " + std::to_string(especializacion.id));
        vectorEspecializacionAnadir.push_back(especializacion);
        especializacionCount++;
        escribirDebugLog("Especialización agregada. Total especializaciones leídas: " + std::to_string(especializacionCount));
        if(file.peek() != EOF) { // Check if there's more to read before logging "Leyendo siguiente"
            escribirDebugLog("Leyendo especialización #" + std::to_string(especializacionCount + 1));
        }
    }

    logInfo("Leer especializaciones", filePath + " (" + std::to_string(especializacionCount) + " registros)");
    escribirDebugLog("Lectura de especializaciones completada. Total: " + std::to_string(especializacionCount));
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

inline FileOperationResult FilesManager::guardarCurso(const RawCursoData& curso) {
	try {
		std::ofstream archivo(DataPaths::Content::DB_CURSOS, std::ios::app);

		if (!archivo.is_open()) {
			logError("Guardar curso", DataPaths::Content::DB_CURSOS, "No se pudo abrir el archivo");
			return FileOperationResult::FILE_NOT_FOUND;
		}

		// Formato: id|idEmpresa|nombreEmpresa|titulo|descripcion|categoria|instructor|cantidadClases
		archivo << curso.id << "\n"
			<< curso.idEmpresa << "\n"
			<< curso.nombreEmpresa << "\n"
			<< curso.titulo << "\n"
			<< curso.descripcion << "\n"
			<< RawActividadData::categoriaToString(curso.categoria) << "\n"
			<< curso.instructor << "\n"
			<< curso.cantidadClases << "\n";

		for (int i = 0; i < static_cast<int>(curso.descripcionClases.size()); i++) {
			archivo << curso.descripcionClases[i].first << "\n" 
                << curso.descripcionClases[i].second << "\n";
		}

		archivo << "%%%\n"; // Delimitador de fin de curso

		if (!archivo.good()) {
			logError("Guardar curso", DataPaths::Content::DB_CURSOS, "Error al escribir");
			return FileOperationResult::UNKNOWN_ERROR;
		}

		logInfo("Guardar curso", DataPaths::Content::DB_CURSOS);
		return FileOperationResult::SUCCESS;

	}
	catch (const std::exception& e) {
		logError("Guardar curso", "Sistema", e.what());
		return FileOperationResult::UNKNOWN_ERROR;
	}
}

inline FileOperationResult FilesManager::guardarEspecializacion(const RawEspecializacionData& especializacion) {
	try {
		std::ofstream archivo(DataPaths::Content::DB_ESPECIALIZACIONES, std::ios::app);

		if (!archivo.is_open()) {
			logError("Guardar especialización", DataPaths::Content::DB_ESPECIALIZACIONES, "No se pudo abrir el archivo");
			return FileOperationResult::FILE_NOT_FOUND;
		}

		// Formato: id|idEmpresa|nombreEmpresa|categoria|titulo|descripcion|cantidadCursos|idsCursos|duracionEstimada
		archivo << especializacion.id << "\n"
			<< especializacion.idEmpresa << "\n"
			<< especializacion.nombreEmpresa << "\n"
			<< RawActividadData::categoriaToString(especializacion.categoria) << "\n"
			<< especializacion.titulo << "\n"
			<< especializacion.descripcion << "\n"
			<< especializacion.cantidadCursos << "\n";

		// Guardar IDs de cursos separados por comas
		for (size_t i = 0; i < especializacion.idsCursos.size(); i++) {
			archivo << especializacion.idsCursos[i];
			if (i < especializacion.idsCursos.size() - 1) {
				archivo << ",";
			}
		}
		archivo << "\n";

		archivo << especializacion.duracionEstimada << "\n";
		archivo << "%%%\n"; // Delimitador de fin de especialización

		if (!archivo.good()) {
			logError("Guardar especialización", DataPaths::Content::DB_ESPECIALIZACIONES, "Error al escribir");
			return FileOperationResult::UNKNOWN_ERROR;
		}

		logInfo("Guardar especialización", DataPaths::Content::DB_ESPECIALIZACIONES, "Especialización ID: " + std::to_string(especializacion.id));
		return FileOperationResult::SUCCESS;

	}
	catch (const std::exception& e) {
		logError("Guardar especialización", "Sistema", e.what());
		return FileOperationResult::UNKNOWN_ERROR;
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

inline FileOperationResult FilesManager::registrarPago(int idUsuario,int idActividad,
    double monto,const std::string& metodoPago) {
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

inline int FilesManager::contarFilasCSV(const std::string& ruta , bool tieneCabecera) {
    std::ifstream file(ruta);
    if (!file.is_open()) {
        logError("contarFilasCSV", ruta, "No se pudo abrir el archivo");
        return 0;
    }

    int lineas = 0;
    std::string linea;
    while (std::getline(file, linea)) {
        if (!linea.empty())
            lineas++;
    }
    // Si hay cabecera, la restamos
    return (tieneCabecera && lineas > 0) ? lineas - 1 : lineas;
}

inline FileOperationResult FilesManager::generarComprobantePago(int idPago,const std::string& datosComprobante) {
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

// ========= BUSQUEDAS RAPIDAS CON HASH =========
inline void FilesManager::cargarCursos() {
    indiceCursos.clear(); // Limpia el hash table antes de cargar

    std::vector<RawCursoData> cursos;
    leerDatoCurso(cursos); // Lee todos los cursos del archivo

    for (const auto& curso : cursos) {
        indiceCursos.insert(curso.titulo, curso); // Agrega cada curso al hash table usando el ID como clave
    }

    logInfo("Cargar cursos", "Se cargaron " + std::to_string(cursos.size()) + " cursos al hash table");
}

inline bool FilesManager::buscarCursoPorNombreHash(const std::string& nombre, RawCursoData& resultado) {
	if (indiceCursos.find(nombre, resultado)) {
		logInfo("Buscar curso por nombre", "Curso encontrado: " + nombre);
		return true;
	}
	else {
		logInfo("Buscar curso por nombre", "Curso no encontrado: " + nombre);
		return false;
	}
}

inline int FilesManager::obtenerIdCursoPorNombre(const std::string& nombreCurso) {
    std::vector<RawCursoData> cursos;
    leerDatoCurso(cursos);
    for (const auto& curso : cursos) {
        if (curso.titulo == nombreCurso) {
            return curso.id;
        }
    }
    return -1; // No encontrado
}

inline void FilesManager::cargarComprobantes() {
    indiceComprobantes.clear();

    const std::string path = DataPaths::Financial::DB_COMPROBANTES;
    std::ifstream archivo(path);

    if (!archivo.is_open()) {
        logError("Cargar comprobantes", path, "No se pudo abrir el archivo");
        return;
    }

    std::string linea;
    int lineNumber = 0;
    while (std::getline(archivo, linea)) {
        lineNumber++;
        if (linea.empty()) continue;

        std::stringstream ss(linea);
        std::string campo;
        RawComprobanteData comprobante;

        try {
            // id
            if (!std::getline(ss, campo, '|')) throw std::runtime_error("Campo id faltante");
            comprobante.id = std::stoi(campo);

            // idEstudiante
            if (!std::getline(ss, campo, '|')) throw std::runtime_error("Campo idEstudiante faltante");
            comprobante.idEstudiante = std::stoi(campo);

            // idActividad
            if (!std::getline(ss, campo, '|')) throw std::runtime_error("Campo idActividad faltante");
            comprobante.idActividad = std::stoi(campo);

            // tipoActividad
            if (!std::getline(ss, campo, '|')) throw std::runtime_error("Campo tipoActividad faltante");
            comprobante.tipoActividad = static_cast<TipoActividad>(std::stoi(campo));

            // fechaEmision
            if (!std::getline(ss, comprobante.fechaEmision, '|')) throw std::runtime_error("Campo fechaEmision faltante");

            // horaEmision
            if (!std::getline(ss, comprobante.horaEmision, '|')) throw std::runtime_error("Campo horaEmision faltante");

            // montoPagado
            if (!std::getline(ss, campo, '|')) throw std::runtime_error("Campo montoPagado faltante");
            comprobante.montoPagado = std::stod(campo);


            // Insertar en la tabla hash
            indiceComprobantes.insert(comprobante.id, comprobante);
        }
        catch (const std::exception& e) {
            logError("Cargar comprobantes", path, "Error en línea " + std::to_string(lineNumber) + ": " + e.what());
            continue; // Salta a la siguiente línea
        }
    }

    archivo.close();
    logInfo("Cargar comprobantes", path + " (Total: " + std::to_string(indiceComprobantes.size()) + " comprobantes indexados)");
}


inline bool FilesManager::buscarComprobantePorIdHash(int id, RawComprobanteData& resultado) {
    return indiceComprobantes.find(id, resultado);
}

inline HashTable<std::string, RawCursoData>& FilesManager::getIndiceCursos() {
	return indiceCursos;
}

#endif // COURSERACLONE_PERSISTENCE_FILESMANAGER_HPP