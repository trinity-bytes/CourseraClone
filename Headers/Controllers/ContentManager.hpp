// description: Clase para gestionar todo el contenido del sistema (cursos y especializaciones) usando la nueva arquitectura por dominios.

#ifndef COURSERACLONE_CONTROLLERS_CONTENTMANAGER_HPP
#define COURSERACLONE_CONTROLLERS_CONTENTMANAGER_HPP

// Headers estándar
#include <memory>    // Para std::unique_ptr
#include <vector>    // Para std::vector
#include <map>       // Para std::map
#include <string>    // Para std::string
#include <stdexcept> // Para excepciones
#include <iostream>  // Para logging
#include <algorithm> // Para std::find_if
#include <set>       // Para std::set en estadísticas
#include <mutex>     // Para std::once_flag

// Headers propios
#include "FilesManager.hpp"
#include "../Entities/Curso.hpp"
#include "../Entities/Especializacion.hpp"
#include "../Entities/Inscripcion.hpp"
#include "../DataStructures/LinkedList.hpp"
#include "../Utils/DataPaths.hpp"

// Enums para tipos y resultados
enum class ActividadTipo : int {
    CURSO = 1,
    ESPECIALIZACION = 2
};

enum class ContentOperationResult {
    SUCCESS,
    CONTENT_NOT_FOUND,
	COURSE_NOT_FOUND,
	SPECIALIZATION_NOT_FOUND,
    STUDENT_ALREADY_ENROLLED,
    INVALID_DATA,
    FILE_ERROR,
    SPECIALIZATION_INCOMPLETE,
    COURSE_DEPENDENCY_ERROR,
    UNKNOWN_ERROR
};

class ContentManager {
private:
    // La única instancia de la clase
    static std::unique_ptr<ContentManager> _instance;

    // El mutex para asegurar la inicialización segura en entornos multi-hilo
    static std::once_flag _onceFlag;

    int idCursoMostrar;
    int idEspecializacionMostrar;

    // Constructor privado para evitar instanciación externa
    ContentManager();

    // Estructuras de datos principales
    std::vector<std::unique_ptr<Curso>> _cursos;
    std::vector<std::unique_ptr<Especializacion>> _especializaciones;

    // Mapas para seguimiento de progreso y calificaciones
    std::map<int, std::map<int, double>> _progresoEstudiantes; // [idEstudiante][idActividad] -> progreso
    std::map<int, std::map<int, std::pair<int, std::string>>> _calificacionesActividades; // [idActividad][idEstudiante] -> (calificacion, comentario)

    // Cachés para búsquedas rápidas
    std::map<int, Curso*> _cacheIdCursos;
    std::map<int, Especializacion*> _cacheIdEspecializaciones;

    // Contadores para IDs autoincrementales
    int _nextCursoId;
    int _nextEspecializacionId;

    // Utilidades privadas
    void actualizarCaches();
    void limpiarCaches();
    void logOperation(const std::string& operation, const std::string& details);
    void logError(const std::string& operation, const std::string& error);

public:
    // Eliminar constructor de copia y operador de asignación para asegurar una única instancia
    ContentManager(const ContentManager&) = delete;
    ContentManager& operator=(const ContentManager&) = delete;

    // Método estático para obtener la única instancia de la clase
    static ContentManager& getInstance();

    // El destructor puede ser público si unique_ptr lo maneja, o privado si la gestión es más estricta.
    // En este caso, unique_ptr se encargará de la liberación.
    ~ContentManager() = default;

    // ========== INICIALIZACIÓN Y CARGA DE DATOS ==========

    /**
     * @brief Inicializa el manager cargando datos desde archivos
     * @return true si la inicialización fue exitosa
     */
    bool inicializarSistema();    
    
    /**
     * @brief Carga datos desde estructuras raw del FileManager
     * @param dataActividades Datos de cursos y especializaciones
     * @param dataInscripciones Vector de inscripciones binarias
     * @return ContentOperationResult resultado de la operación
     */
    ContentOperationResult cargarDesdeDatos(
        const RawActividadesData& dataActividades,
        const std::vector<InscripcionBinaria>& dataInscripciones
    );

    // ========== GESTIÓN DE CURSOS ==========

    /**
     * @brief Crea un nuevo curso en el sistema
     * @param idEmpresa ID de la empresa que ofrece el curso
     * @param titulo Título del curso
     * @param nombreEmpresa Nombre de la empresa
     * @param instructor Nombre del instructor
     * @param descripcion Descripción del curso
     * @param titulosClases Vector con títulos de las clases
     * @param descripcionesClases Vector con descripciones de las clases     * @param categoria Categoría del curso (opcional)
     * @return ContentOperationResult resultado de la operación
     */
    ContentOperationResult crearCurso(
        int idEmpresa,
        const std::string& titulo,
        const std::string& nombreEmpresa,
        const std::string& instructor,
        const std::string& descripcion,
        const std::vector<std::string>& titulosClases,
        const std::vector<std::string>& descripcionesClases,
        const std::string& categoria = ""
    );

    /**
     * @brief Actualiza un curso existente
     * @param idCurso ID del curso a actualizar
     * @param nuevosDatos Nuevos datos del curso
     * @return ContentOperationResult resultado de la operación
     */
    ContentOperationResult actualizarCurso(int idCurso, const RawCursoData& nuevosDatos);

    /**
     * @brief Elimina un curso del sistema
     * @param idCurso ID del curso a eliminar
     * @return ContentOperationResult resultado de la operación
     */
    ContentOperationResult eliminarCurso(int idCurso);

    // ========== GESTIÓN DE ESPECIALIZACIONES ==========

    /**
     * @brief Crea una nueva especialización
     * @param idEmpresa ID de la empresa
     * @param nombreEmpresa Nombre de la empresa
     * @param titulo Título de la especialización
     * @param descripcion Descripción
     * @param idsCursos Vector con IDs de cursos incluidos     * @param categoria Categoría (opcional)
     * @return ContentOperationResult resultado de la operación
     */
    ContentOperationResult crearEspecializacion(
        int idEmpresa,
        const std::string& nombreEmpresa,
        const std::string& titulo,
        const std::string& descripcion,
        const std::vector<int>& idsCursos,
        const std::string& categoria = ""
    );

    /**
     * @brief Actualiza una especialización existente
     * @param idEspecializacion ID de la especialización
     * @param nuevosDatos Nuevos datos
     * @return ContentOperationResult resultado de la operación
     */
    ContentOperationResult actualizarEspecializacion(int idEspecializacion, const RawEspecializacionData& nuevosDatos);

    /**
     * @brief Elimina una especialización
     * @param idEspecializacion ID de la especialización
     * @return ContentOperationResult resultado de la operación
     */
    ContentOperationResult eliminarEspecializacion(int idEspecializacion);

    // ========== GESTIÓN DE INSCRIPCIONES ==========    
    /**
     * @brief Inscribe un estudiante a un curso
     * @param idEstudiante ID del estudiante
     * @param idCurso ID del curso
     * @return ContentOperationResult resultado de la operación
     */
    ContentOperationResult inscribirEstudianteACurso(int idEstudiante, int idCurso);

    /**
     * @brief Inscribe un estudiante a una especialización
     * @param idEstudiante ID del estudiante
     * @param idEspecializacion ID de la especialización
     * @return ContentOperationResult resultado de la operación
     */
    ContentOperationResult inscribirEstudianteAEspecializacion(int idEstudiante, int idEspecializacion);

    /**
     * @brief Desinscribe un estudiante de una actividad
     * @param idEstudiante ID del estudiante
     * @param idActividad ID de la actividad
     * @param tipoActividad Tipo de actividad
     * @return ContentOperationResult resultado de la operación
     */
    ContentOperationResult desinscribirEstudiante(int idEstudiante, int idActividad, ActividadTipo tipoActividad);

    // ========== GESTIÓN DE PROGRESO Y CALIFICACIONES ==========    
    /**
     * @brief Actualiza el progreso de un estudiante en una actividad
     * @param idEstudiante ID del estudiante
     * @param idActividad ID de la actividad
     * @param nuevoProgreso Nuevo progreso (0.0 - 100.0)
     * @return ContentOperationResult resultado de la operación
     */
    ContentOperationResult actualizarProgreso(int idEstudiante, int idActividad, double nuevoProgreso);

    /**
     * @brief Agrega una calificación a una actividad
     * @param idActividad ID de la actividad
     * @param idEstudiante ID del estudiante que califica
     * @param calificacion Calificación (1-5)
     * @param comentario Comentario opcional
     * @return ContentOperationResult resultado de la operación
     */
    ContentOperationResult agregarCalificacion(int idActividad, int idEstudiante, int calificacion, const std::string& comentario = "");

    // ========== BÚSQUEDAS Y CONSULTAS ==========

    /**
     * @brief Obtiene un curso por su ID
     * @param id ID del curso
     * @return Puntero al curso o nullptr si no existe
     */
    Curso* obtenerCurso(int id);

	RawCursoData obtenerCursoDatos(int id);

    ElementoMenu obtenerRawCursoMenu(int id);


    RawEspecializacionData ContentManager::obtenerEspecializacionDatos(int id);
    /**
     * @brief Obtiene una especialización por su ID
     * @param id ID de la especialización
     * @return Puntero a la especialización o nullptr si no existe
     */
    Especializacion* obtenerEspecializacion(int id) const;

    /**
     * @brief Busca cursos por categoría
     * @param categoria Categoría a buscar
     * @return Vector con punteros a los cursos encontrados
     */
    std::vector<Curso*> buscarCursosPorCategoria(const std::string& categoria) const;

    /**
     * @brief Busca especializaciones por categoría
     * @param categoria Categoría a buscar
     * @return Vector con punteros a las especializaciones encontradas
     */
    std::vector<Especializacion*> buscarEspecializacionesPorCategoria(const std::string& categoria) const;

    /**
     * @brief Obtiene actividades de una empresa específica
     * @param idEmpresa ID de la empresa
     * @return Par con vectores de cursos y especializaciones
     */
    std::pair<std::vector<Curso*>, std::vector<Especializacion*>> obtenerActividadesPorEmpresa(int idEmpresa) const;

    /**
     * @brief Obtiene las inscripciones de un estudiante
     * @param idEstudiante ID del estudiante
     * @return Vector con las inscripciones
     */
    std::vector<InscripcionBinaria> obtenerInscripcionesEstudiante(int idEstudiante) const;

    // ========== ESTADÍSTICAS Y REPORTES ==========

    /**
     * @brief Obtiene estadísticas generales del sistema
     * @return Mapa con estadísticas
     */
    std::map<std::string, int> obtenerEstadisticasGenerales() const;

    /**
     * @brief Obtiene los cursos más populares
     * @param limite Número máximo de cursos a retornar
     * @return Vector con los cursos más populares
     */
    std::vector<Curso*> obtenerCursosMasPopulares(int limite = 10) const;

    /**
     * @brief Obtiene las especializaciones más populares
     * @param limite Número máximo de especializaciones a retornar
     * @return Vector con las especializaciones más populares
     */
    std::vector<Especializacion*> obtenerEspecializacionesMasPopulares(int limite = 10) const;

    // ========== PERSISTENCIA ==========    
    /**
     * @brief Guarda todos los cambios en archivos
     * @return ContentOperationResult resultado de la operación
     */
    ContentOperationResult guardarTodosCambios();

    /**
     * @brief Recarga los datos desde archivos
     * @return ContentOperationResult resultado de la operación
     */
    ContentOperationResult recargarDatos();

	//inline Especializacion* obtenerEspecializacion(int idCurso) const;

    // ========== OBTENCIÓN DE DATOS CRUDOS ==========

    /**
     * @brief Obtiene datos crudos de cursos y especializaciones para pantallas
     * @param maxCursos Máximo número de cursos a devolver (-1 para todos)
     * @param maxEspecializaciones Máximo número de especializaciones a devolver (-1 para todas)
     * @return Estructura con datos crudos de actividades
     */
    RawActividadesData obtenerDatosCrudos(int maxCursos = -1, int maxEspecializaciones = -1) const;

    std::vector<RawExploradorData> obtenerExploradorDatos() const;

    // ========== GETTERS ==========

    const std::vector<std::unique_ptr<Curso>>& getCursos() const { return _cursos; }
    const std::vector<std::unique_ptr<Especializacion>>& getEspecializaciones() const { return _especializaciones; }

    int getTotalCursos() const { return _cursos.size(); }
    int getTotalEspecializaciones() const { return _especializaciones.size(); }
	int getCursoIdMostrar() { return idCursoMostrar; }
    int getEspecializacionIdMostrar() { return idEspecializacionMostrar; }

    void setCursoIdMostrar(int _idNuevo) { idCursoMostrar = _idNuevo; }
    void setEspecializacionIdMostar(int _idNuevo) { idEspecializacionMostrar = _idNuevo; }

    double obtenerProgreso(int idEstudiante, int idActividad) const;
};

// Inicialización de los miembros estáticos en el archivo de implementación (o en este caso, el mismo header)
// Esta es la parte crucial para el enfoque header-only: la definición de los miembros estáticos.
// La palabra clave 'inline' es necesaria si se define en un header para evitar errores de enlace múltiple.
// Sin embargo, para `std::unique_ptr` y `std::once_flag`, C++17 introdujo `inline variables`,
// lo que permite su definición directamente en el header sin violar la One Definition Rule (ODR).

// Definición de la instancia única
inline std::unique_ptr<ContentManager> ContentManager::_instance = nullptr;

// Definición de la flag para std::call_once
inline std::once_flag ContentManager::_onceFlag;

// ========== IMPLEMENTACIONES INLINE ==========

inline bool ContentManager::inicializarSistema() 
{
	FilesManager* fileManager = &FilesManager::getInstance();

	RawActividadesData dataActividades = fileManager->leerDatosActividades();
	std::vector<InscripcionBinaria> dataInscripciones = fileManager->leerDatosInscripciones();

	// Para debugging: mostrar cantidad de datos cargados
	int cantidad = dataActividades.cursos.size() + dataActividades.especializaciones.size();
    // throw std::runtime_error(std::to_string(cantidad));
    
    ContentOperationResult result = cargarDesdeDatos(dataActividades, dataInscripciones);

	if (result != ContentOperationResult::SUCCESS) {
		logError("Inicialización", "Error al cargar datos: " + std::to_string(static_cast<int>(result)));
        return false;
	}
	logOperation("Inicialización", "ContentManager completada con éxito");
    
	return true;
}

inline ContentManager::ContentManager()
    : _nextCursoId(1), _nextEspecializacionId(1), idCursoMostrar(-1), idEspecializacionMostrar(-1) {

    logOperation("Constructor", "ContentManager inicializado (Singleton)");
    inicializarSistema();
    
}

inline ContentManager& ContentManager::getInstance() {
    // std::call_once asegura que la inicialización se realice una sola vez, incluso en entornos multi-hilo
    std::call_once(_onceFlag, []() {
        _instance.reset(new ContentManager());
        });

    return *_instance;
}

inline RawActividadesData ContentManager::obtenerDatosCrudos(int maxCursos, int maxEspecializaciones) const {
    RawActividadesData datos;
    
    // Obtener cursos
    int cursoCount = 0;
    for (auto it = _cursos.begin(); it != _cursos.end() && (maxCursos == -1 || cursoCount < maxCursos); ++it) {
        if (*it != nullptr) {
            datos.cursos.push_back((*it)->obtenerDatosCrudosCurso());
            cursoCount++;
        }
    }
    
    // Obtener especializaciones
    int especializacionCount = 0;
    for (auto it = _especializaciones.begin(); it != _especializaciones.end() && (maxEspecializaciones == -1 || especializacionCount < maxEspecializaciones); ++it) {
        if (*it != nullptr) {
            datos.especializaciones.push_back((*it)->obtenerDatosCrudosEspecialidad());
            especializacionCount++;
        }
    }
    
    return datos;
}

inline std::vector<RawExploradorData> ContentManager::obtenerExploradorDatos() const {
	std::vector<RawExploradorData> datosExplorador;
	// Recorrer cursos
	for (const auto& curso : _cursos) {
		if (curso) {
			datosExplorador.push_back(curso->obtenerDatosCrudosExplorador());
		}
	}
	// Recorrer especializaciones
	for (const auto& especializacion : _especializaciones) {
		if (especializacion) {
			datosExplorador.push_back(especializacion->obtenerDatosCrudosExplorador());
		}
	}
	return datosExplorador;
}


inline Curso* ContentManager::obtenerCurso(int id) {
	if (id < 0 || id >= _nextCursoId) {
		logError("obtenerCurso", "ID de curso inválido: " + std::to_string(id));
		return nullptr; // ID inválido
	}
    return _cursos[id].get();
}

inline RawCursoData ContentManager::obtenerCursoDatos(int id) {
	return _cursos[id]->obtenerDatosCrudosCurso();
}

inline ElementoMenu ContentManager::obtenerRawCursoMenu(int id) {
	return _cursos[id]->obtenerDatosCrudosMenu();
}

inline RawEspecializacionData ContentManager::obtenerEspecializacionDatos(int id) {
	return _especializaciones[id]->obtenerDatosCrudosEspecialidad();
}

inline ContentOperationResult ContentManager::inscribirEstudianteACurso(int idEstudiante, int idCurso) {
    Curso* curso = obtenerCurso(idCurso);
    if (!curso) {
        logError("InscribirEstudianteACurso", "Curso no encontrado: " + std::to_string(idCurso));
        return ContentOperationResult::COURSE_NOT_FOUND;
    }


    /*
    // Verificar si el estudiante ya está inscrito
    if (std::find_if(_cursos.begin(), _cursos.end(), [idEstudiante, idCurso](const std::unique_ptr<Curso>& c) {
        return c->estaInscrito(idEstudiante);
        }) != _cursos.end()) {
        logError("InscribirEstudianteACurso", "Estudiante ya inscrito en el curso: " + std::to_string(idCurso));
        return ContentOperationResult::STUDENT_ALREADY_ENROLLED;
    }

    // Inscribir al estudiante
    curso->inscribirEstudiante(idEstudiante);

    logOperation("InscribirEstudianteACurso", "Estudiante " + std::to_string(idEstudiante) +
        " inscrito en curso " + std::to_string(idCurso));

    return ContentOperationResult::SUCCESS;
    */
}

// ========== CARGA DE DATOS ==========

inline ContentOperationResult ContentManager::cargarDesdeDatos(
    const RawActividadesData& dataActividades,
    const std::vector<InscripcionBinaria>& dataInscripciones
) {
    try {
        // Limpiar datos existentes
        _cursos.clear();
        _especializaciones.clear();
        limpiarCaches();
        
        // Cargar cursos desde datos crudos
        for (const auto& cursoData : dataActividades.cursos) {
            auto curso = std::make_unique<Curso>(
                cursoData.id,
                cursoData.idEmpresa,
                cursoData.nombreEmpresa,
                cursoData.categoria,
                cursoData.titulo,
                cursoData.descripcion,
                cursoData.instructor,
                cursoData.cantidadClases,
                cursoData.descripcionClases
            );
            
            _cursos.push_back(std::move(curso));
            
            // Actualizar contador de IDs
            if (cursoData.id >= _nextCursoId) {
                _nextCursoId = cursoData.id + 1;
            }
        }
        
        // Cargar especializaciones desde datos crudos
        for (const auto& espData : dataActividades.especializaciones) {
            auto especializacion = std::make_unique<Especializacion>(
                espData.id,
                espData.idEmpresa,
                espData.nombreEmpresa,
                espData.categoria,
                espData.titulo,
                espData.descripcion,
                espData.idsCursos,
                espData.duracionEstimada
            );
            
            _especializaciones.push_back(std::move(especializacion));
            
            // Actualizar contador de IDs
            if (espData.id >= _nextEspecializacionId) {
                _nextEspecializacionId = espData.id + 1;
            }
        }
        
        // Actualizar caches para búsquedas rápidas
        actualizarCaches();
        
        logOperation("CargarDesdeDatos", 
            "Cargados " + std::to_string(dataActividades.cursos.size()) + " cursos y " + 
            std::to_string(dataActividades.especializaciones.size()) + " especializaciones");
        
        return ContentOperationResult::SUCCESS;
        
    } catch (const std::exception& e) {
        logError("CargarDesdeDatos", e.what());
        return ContentOperationResult::UNKNOWN_ERROR;
    }
}

// ========== MÉTODOS PRIVADOS - LOGGING ==========
inline void ContentManager::logError(const std::string& operation, const std::string& error) {
    // Implementación simple para logging de errores
    FilesManager& fileManager = FilesManager::getInstance();
    fileManager.logError(operation, "ContentManager", error);
    //#ifdef _DEBUG


    //std::cerr << "[ContentManager ERROR] " << operation << " - " << error << std::endl;
    //#endif
}


inline void ContentManager::logOperation(const std::string& operation, const std::string& details) {
    // Implementación simple para logging de operaciones
    // En un proyecto más complejo esto iría a un archivo de log
	FilesManager& fileManager = FilesManager::getInstance();
	fileManager.logInfo(operation, "ContentManager");

    /*
    #ifdef _DEBUG
    std::cout << "[ContentManager] " << operation;
    if (!details.empty()) {
        std::cout << " - " << details;
    }
    std::cout << std::endl;
    #endif
    */
}



// ========== MÉTODOS PRIVADOS - GESTIÓN DE CACHE ==========

inline void ContentManager::actualizarCaches() {
    // Limpiar caches existentes
	ContentManager::limpiarCaches();
    
    // Actualizar cache de cursos
    for (auto it = _cursos.begin(); it != _cursos.end(); ++it) {
        if (*it != nullptr) {
            _cacheIdCursos[(*it)->getId()] = (*it).get();
        }
    }
    
    // Actualizar cache de especializaciones
    for (auto it = _especializaciones.begin(); it != _especializaciones.end(); ++it) {
        if (*it != nullptr) {
            _cacheIdEspecializaciones[(*it)->getId()] = (*it).get();
        }
    }
}

inline void ContentManager::limpiarCaches() {
    _cacheIdCursos.clear();
    _cacheIdEspecializaciones.clear();
}

// ========== UTILIDADES ==========

#endif // COURSERACLONE_CONTROLLERS_COURSEMANAGER_HPP
