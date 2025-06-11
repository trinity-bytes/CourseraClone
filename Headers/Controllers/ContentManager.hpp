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

    // Constructor privado para evitar instanciación externa
    ContentManager();

    // Estructuras de datos principales
    LinkedList<std::unique_ptr<Curso>> _cursos;
    LinkedList<std::unique_ptr<Especializacion>> _especializaciones;

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
    void logOperation(const std::string& operation, const std::string& details = "");
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
    bool inicializarSistema();    /**
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
    Curso* obtenerCurso(int id) const;

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

    // ========== GETTERS ==========

    const LinkedList<std::unique_ptr<Curso>>& getCursos() const { return _cursos; }
    const LinkedList<std::unique_ptr<Especializacion>>& getEspecializaciones() const { return _especializaciones; }

    int getTotalCursos() const { return _cursos.getTamano(); }
    int getTotalEspecializaciones() const { return _especializaciones.getTamano(); }

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

inline ContentManager::ContentManager()
    : _nextCursoId(1), _nextEspecializacionId(1) {
    logOperation("Constructor", "ContentManager inicializado (Singleton)");
}

inline ContentManager& ContentManager::getInstance() {
    // std::call_once asegura que la inicialización se realice una sola vez, incluso en entornos multi-hilo
    std::call_once(_onceFlag, []() {
        _instance.reset(new ContentManager());
        });
    return *_instance;
}

inline void ContentManager::logOperation(const std::string& operation, const std::string& details) {
    std::cout << "[ContentManager INFO] " << operation;
    if (!details.empty()) {
        std::cout << ": " << details;
    }
    std::cout << std::endl;
}

inline void ContentManager::logError(const std::string& operation, const std::string& error) {
    std::cerr << "[ContentManager ERROR] " << operation << ": " << error << std::endl;
}

inline bool ContentManager::inicializarSistema() {
    try {
        // Inicializar sistema de archivos
        FilesManager& fileManager = FilesManager::getInstance();
        if (!fileManager.inicializarSistemaArchivos()) {
            logError("Inicialización", "No se pudo inicializar el sistema de archivos");
            return false;
        }

        // Cargar datos existentes
        auto actividades = fileManager.leerDatosActividades();
        auto inscripciones = fileManager.leerDatosInscripciones();

        auto resultado = cargarDesdeDatos(actividades, inscripciones);

        if (resultado == ContentOperationResult::SUCCESS) {
            logOperation("Inicialización completa",
                "Cargados " + std::to_string(_cursos.getTamano()) + " cursos y " +
                std::to_string(_especializaciones.getTamano()) + " especializaciones");
            return true;
        }

        return false;

    }
    catch (const std::exception& e) {
        logError("Inicialización", e.what());
        return false;
    }
}

inline ContentOperationResult ContentManager::cargarDesdeDatos(
    const RawActividadesData& dataActividades,
    const std::vector<InscripcionBinaria>& dataInscripciones
) {
    try {
        // Limpiar datos existentes
        limpiarCaches();
        _cursos.clear();
        _especializaciones.clear();

        // Cargar cursos
        for (const auto& cursoData : dataActividades.cursos) {
            auto nuevoCurso = std::make_unique<Curso>(
                _nextCursoId++,
                cursoData.idEmpresa,
                cursoData.nombreEmpresa,
                cursoData.tituloActividad,
                cursoData.descripcionActividad,
                cursoData.instructor,
                cursoData.cantidadClases
            );

            // Agregar clases al curso
            for (size_t i = 0; i < cursoData.titulosClases.size() && i < cursoData.descripcionesClases.size(); ++i) {
                nuevoCurso->anadirClases(cursoData.titulosClases[i], cursoData.descripcionesClases[i]);
            }

            _cursos.agregarAlFinal(std::move(nuevoCurso));
        }

        // Cargar especializaciones
        for (const auto& espData : dataActividades.especializaciones) {
            auto nuevaEspecializacion = std::make_unique<Especializacion>(
                _nextEspecializacionId++,
                espData.idEmpresa,
                espData.nombreEmpresa,
                espData.tituloActividad,
                0, // Alumnos iniciales
                espData.descripcionActividad
            );

            // Agregar IDs de cursos
            for (int idCurso : espData.idsCursosInternos) {
                nuevaEspecializacion->anadirCursoPorId(idCurso);
            }

            _especializaciones.agregarAlFinal(std::move(nuevaEspecializacion));
        }

        // Procesar inscripciones para actualizar contadores
        for (const auto& inscripcion : dataInscripciones) {
            if (inscripcion.tipoActividad == static_cast<int>(ActividadTipo::CURSO)) {
                if (auto curso = obtenerCurso(inscripcion.idActividad)) {
                    curso->aumentarAlumno(1);
                }
            }
            else if (inscripcion.tipoActividad == static_cast<int>(ActividadTipo::ESPECIALIZACION)) {
                if (auto especializacion = obtenerEspecializacion(inscripcion.idActividad)) {
                    especializacion->aumentarAlumno(1);
                }
            }

            // Actualizar progreso si existe
            if (inscripcion.progreso > 0.0) {
                _progresoEstudiantes[inscripcion.idEstudiante][inscripcion.idActividad] = inscripcion.progreso;
            }
        }

        // Actualizar cachés
        actualizarCaches();

        logOperation("Carga de datos",
            "Cargados " + std::to_string(_cursos.getTamano()) + " cursos y " +
            std::to_string(_especializaciones.getTamano()) + " especializaciones");

        return ContentOperationResult::SUCCESS;

    }
    catch (const std::exception& e) {
        logError("Carga de datos", e.what());
        return ContentOperationResult::UNKNOWN_ERROR;
    }
}

inline void ContentManager::actualizarCaches() {
    _cacheIdCursos.clear();
    _cacheIdEspecializaciones.clear();

    // Actualizar cache de cursos
    for (auto it = _cursos.begin(); it != _cursos.end(); ++it) {
        _cacheIdCursos[(*it)->getId()] = it->get();
    }

    // Actualizar cache de especializaciones
    for (auto it = _especializaciones.begin(); it != _especializaciones.end(); ++it) {
        _cacheIdEspecializaciones[(*it)->getId()] = it->get();
    }
}

inline void ContentManager::limpiarCaches() {
    _cacheIdCursos.clear();
    _cacheIdEspecializaciones.clear();
    _progresoEstudiantes.clear();
    _calificacionesActividades.clear();
}

inline Curso* ContentManager::obtenerCurso(int id) const {
    auto it = _cacheIdCursos.find(id);
    return (it != _cacheIdCursos.end()) ? it->second : nullptr;
}

inline Especializacion* ContentManager::obtenerEspecializacion(int id) const {
    auto it = _cacheIdEspecializaciones.find(id);
    return (it != _cacheIdEspecializaciones.end()) ? it->second : nullptr;
}

inline ContentOperationResult ContentManager::crearCurso(
    int idEmpresa,
    const std::string& titulo,
    const std::string& nombreEmpresa,
    const std::string& instructor,
    const std::string& descripcion,
    const std::vector<std::string>& titulosClases,
    const std::vector<std::string>& descripcionesClases,
    const std::string& categoria
) {
    try {
        auto nuevoCurso = std::make_unique<Curso>(
            _nextCursoId++,
            idEmpresa,
            nombreEmpresa,
            titulo,
            descripcion,
            instructor,
            static_cast<int>(titulosClases.size())
        );

        if (!categoria.empty()) {
            nuevoCurso->setCategoria(categoria);
        }

        // Agregar clases
        size_t minSize = std::min(titulosClases.size(), descripcionesClases.size());
        for (size_t i = 0; i < minSize; ++i) {
            nuevoCurso->anadirClases(titulosClases[i], descripcionesClases[i]);
        }

        // Guardar curso en archivo
        RawCursoData cursoData;
        cursoData.idEmpresa = idEmpresa;
        cursoData.nombreEmpresa = nombreEmpresa;
        cursoData.tituloActividad = titulo;
        cursoData.descripcionActividad = descripcion;
        cursoData.instructor = instructor;
        cursoData.cantidadClases = static_cast<int>(titulosClases.size());
        cursoData.titulosClases = titulosClases;
        cursoData.descripcionesClases = descripcionesClases;

        auto resultado = FilesManager::getInstance().guardarCurso(cursoData);
        if (resultado != FileOperationResult::SUCCESS) {
            logError("Crear curso", "Error al guardar en archivo");
            return ContentOperationResult::FILE_ERROR;
        }

        // Agregar a la estructura de datos y cache
        int cursoId = nuevoCurso->getId();
        Curso* ptrCurso = nuevoCurso.get();
        _cursos.agregarAlFinal(std::move(nuevoCurso));
        _cacheIdCursos[cursoId] = ptrCurso;

        logOperation("Crear curso", "Curso '" + titulo + "' creado con ID " + std::to_string(cursoId));
        return ContentOperationResult::SUCCESS;

    }
    catch (const std::exception& e) {
        logError("Crear curso", e.what());
        return ContentOperationResult::UNKNOWN_ERROR;
    }
}

inline ContentOperationResult ContentManager::inscribirEstudianteACurso(int idEstudiante, int idCurso) {
    try {
        // Verificar que el curso existe
        Curso* curso = obtenerCurso(idCurso);
        if (!curso) {
            logError("Inscribir estudiante", "Curso no encontrado: " + std::to_string(idCurso));
            return ContentOperationResult::COURSE_NOT_FOUND;
        }

        // Crear inscripción binaria
        InscripcionBinaria inscripcion(
            idEstudiante,
            idCurso,
            static_cast<int>(ActividadTipo::CURSO),
            0.0,  // Progreso inicial
            false, // No completado
            false  // No pagado
        );

        // Guardar en archivo
        int offsetRegistro;
        auto resultado = FilesManager::getInstance().guardarInscripcionBinaria(inscripcion, offsetRegistro);
        if (resultado != FileOperationResult::SUCCESS) {
            logError("Inscribir estudiante", "Error al guardar inscripción");
            return ContentOperationResult::FILE_ERROR;
        }

        // Actualizar contador de alumnos
        curso->aumentarAlumno(1);

        // Inicializar progreso
        _progresoEstudiantes[idEstudiante][idCurso] = 0.0;

        logOperation("Inscribir estudiante",
            "Estudiante " + std::to_string(idEstudiante) + " inscrito en curso " + std::to_string(idCurso));

        return ContentOperationResult::SUCCESS;

    }
    catch (const std::exception& e) {
        logError("Inscribir estudiante", e.what());
        return ContentOperationResult::UNKNOWN_ERROR;
    }
}

inline std::map<std::string, int> ContentManager::obtenerEstadisticasGenerales() const {
    std::map<std::string, int> estadisticas;

    estadisticas["total_cursos"] = _cursos.getTamano();
    estadisticas["total_especializaciones"] = _especializaciones.getTamano();

    // Contar total de estudiantes únicos
    std::set<int> estudiantesUnicos;
    for (const auto& progreso : _progresoEstudiantes) {
        estudiantesUnicos.insert(progreso.first);
    }
    estadisticas["estudiantes_activos"] = static_cast<int>(estudiantesUnicos.size());

    // Contar inscripciones totales
    int totalInscripciones = 0;
    for (const auto& estudiante : _progresoEstudiantes) {
        totalInscripciones += static_cast<int>(estudiante.second.size());
    }
    estadisticas["total_inscripciones"] = totalInscripciones;

    return estadisticas;
}

inline double ContentManager::obtenerProgreso(int idEstudiante, int idActividad) const {
    auto itEstudiante = _progresoEstudiantes.find(idEstudiante);
    if (itEstudiante != _progresoEstudiantes.end()) {
        auto itActividad = itEstudiante->second.find(idActividad);
        if (itActividad != itEstudiante->second.end()) {
            return itActividad->second;
        }
    }
    return 0.0;
}

// Implementación de las nuevas funciones de persistencia y operaciones de búsqueda

inline ContentOperationResult ContentManager::actualizarCurso(int idCurso, const RawCursoData& nuevosDatos) {
    try {
        Curso* curso = obtenerCurso(idCurso);
        if (!curso) {
            logError("Actualizar curso", "Curso no encontrado: " + std::to_string(idCurso));
            return ContentOperationResult::COURSE_NOT_FOUND;
        }

        // Actualizar los datos del curso en memoria
        curso->setNombreEmpresa(nuevosDatos.nombreEmpresa);
        curso->setTitulo(nuevosDatos.tituloActividad);
        curso->setDescripcion(nuevosDatos.descripcionActividad);
        curso->setInstructor(nuevosDatos.instructor);
        curso->setCantidadClases(nuevosDatos.cantidadClases);
        // Aquí podrías agregar lógica para actualizar clases si fuera necesario,
        // pero RawCursoData no incluye una forma directa de modificar clases existentes por ID.
        // Si las clases se manejan como una lista simple, podrías reemplazarlas o actualizarlas.
        // Por simplicidad, asumimos que se actualizan los metadatos principales.

        // Convertir el objeto Curso a RawCursoData para guardar
        RawCursoData dataToSave;
        dataToSave.idCurso = curso->getId();
        dataToSave.idEmpresa = curso->getIdEmpresa();
        dataToSave.nombreEmpresa = curso->getNombreEmpresa();
        dataToSave.tituloActividad = curso->getTitulo();
        dataToSave.descripcionActividad = curso->getDescripcion();
        dataToSave.instructor = curso->getInstructor();
        dataToSave.cantidadClases = curso->getCantidadClases();
        // Las clases deben ser obtenidas del curso actualizado si quieres persistirlas
        // Esto requeriría un método en Curso para obtener sus clases en formato Raw
        // Por ahora, asumimos que no se guardan directamente los títulos/descripciones de clases aquí.
        // Si las clases son parte integral, necesitarías modificar RawCursoData para incluirlas adecuadamente,
        // o manejar la actualización de clases por separado.

        if (FilesManager::getInstance().actualizarCurso(dataToSave) != FileOperationResult::SUCCESS) {
            logError("Actualizar curso", "Error al guardar en archivo");
            return ContentOperationResult::FILE_ERROR;
        }

        logOperation("Actualizar curso", "Curso con ID " + std::to_string(idCurso) + " actualizado.");
        return ContentOperationResult::SUCCESS;
    }
    catch (const std::exception& e) {
        logError("Actualizar curso", e.what());
        return ContentOperationResult::UNKNOWN_ERROR;
    }
}

inline ContentOperationResult ContentManager::eliminarCurso(int idCurso) {
    try {
        auto it = _cursos.buscar([idCurso](const std::unique_ptr<Curso>& curso) {
            return curso->getId() == idCurso;
            });

        if (!it.esValido()) { // LinkedList::buscar devuelve un iterador no válido si no lo encuentra
            logError("Eliminar curso", "Curso no encontrado: " + std::to_string(idCurso));
            return ContentOperationResult::COURSE_NOT_FOUND;
        }

        // Eliminar del archivo de persistencia
        if (FilesManager::getInstance().eliminarCurso(idCurso) != FileOperationResult::SUCCESS) {
            logError("Eliminar curso", "Error al eliminar de archivo");
            return ContentOperationResult::FILE_ERROR;
        }

        // Eliminar de la lista en memoria
        _cursos.eliminar(it);

        // Eliminar de la caché
        _cacheIdCursos.erase(idCurso);

        // Eliminar inscripciones y progreso relacionados con este curso
        // Esto requeriría iterar sobre todas las inscripciones y eliminarlas
        // tanto de FileManager como de _progresoEstudiantes.
        // Para simplificar, solo se elimina de memoria y caché.
        // Una implementación robusta necesitaría una función en FileManager para limpiar inscripciones.
        for (auto& entry : _progresoEstudiantes) {
            entry.second.erase(idCurso);
        }
        for (auto& entry : _calificacionesActividades) {
            if (entry.first == idCurso) {
                _calificacionesActividades.erase(entry.first);
                break;
            }
        }


        logOperation("Eliminar curso", "Curso con ID " + std::to_string(idCurso) + " eliminado.");
        return ContentOperationResult::SUCCESS;
    }
    catch (const std::exception& e) {
        logError("Eliminar curso", e.what());
        return ContentOperationResult::UNKNOWN_ERROR;
    }
}

inline ContentOperationResult ContentManager::crearEspecializacion(
    int idEmpresa,
    const std::string& nombreEmpresa,
    const std::string& titulo,
    const std::string& descripcion,
    const std::vector<int>& idsCursos,
    const std::string& categoria
) {
    try {
        auto nuevaEspecializacion = std::make_unique<Especializacion>(
            _nextEspecializacionId++,
            idEmpresa,
            nombreEmpresa,
            titulo,
            0, // Alumnos iniciales
            descripcion
        );

        if (!categoria.empty()) {
            nuevaEspecializacion->setCategoria(categoria);
        }

        for (int idCurso : idsCursos) {
            if (!obtenerCurso(idCurso)) {
                logError("Crear especialización", "Curso con ID " + std::to_string(idCurso) + " no encontrado para la especialización.");
                return ContentOperationResult::INVALID_DATA; // No podemos crear una especialización con cursos inexistentes
            }
            nuevaEspecializacion->anadirCursoPorId(idCurso);
        }

        // Guardar especialización en archivo
        RawEspecializacionData espData;
        espData.idEmpresa = idEmpresa;
        espData.nombreEmpresa = nombreEmpresa;
        espData.tituloActividad = titulo;
        espData.descripcionActividad = descripcion;
        espData.idsCursosInternos = idsCursos;

        if (FilesManager::getInstance().guardarEspecializacion(espData) != FileOperationResult::SUCCESS) {
            logError("Crear especialización", "Error al guardar en archivo");
            return ContentOperationResult::FILE_ERROR;
        }

        int especializacionId = nuevaEspecializacion->getId();
        Especializacion* ptrEspecializacion = nuevaEspecializacion.get();
        _especializaciones.agregarAlFinal(std::move(nuevaEspecializacion));
        _cacheIdEspecializaciones[especializacionId] = ptrEspecializacion;

        logOperation("Crear especialización", "Especialización '" + titulo + "' creada con ID " + std::to_string(especializacionId));
        return ContentOperationResult::SUCCESS;
    }
    catch (const std::exception& e) {
        logError("Crear especialización", e.what());
        return ContentOperationResult::UNKNOWN_ERROR;
    }
}

inline ContentOperationResult ContentManager::actualizarEspecializacion(int idEspecializacion, const RawEspecializacionData& nuevosDatos) {
    try {
        Especializacion* especializacion = obtenerEspecializacion(idEspecializacion);
        if (!especializacion) {
            logError("Actualizar especialización", "Especialización no encontrada: " + std::to_string(idEspecializacion));
            return ContentOperationResult::COURSE_NOT_FOUND;
        }

        // Actualizar los datos de la especialización en memoria
        especializacion->setNombreEmpresa(nuevosDatos.nombreEmpresa);
        especializacion->setTitulo(nuevosDatos.tituloActividad);
        especializacion->setDescripcion(nuevosDatos.descripcionActividad);
        // Actualizar cursos internos, esto podría ser complejo si se debe mantener la coherencia
        // con los IDs antiguos y nuevos. Asumimos que se reemplazan.
        especializacion->limpiarCursos();
        for (int idCurso : nuevosDatos.idsCursosInternos) {
            if (!obtenerCurso(idCurso)) {
                logError("Actualizar especialización", "Curso con ID " + std::to_string(idCurso) + " no encontrado para la especialización.");
                return ContentOperationResult::INVALID_DATA;
            }
            especializacion->anadirCursoPorId(idCurso);
        }


        // Convertir a RawEspecializacionData para guardar
        RawEspecializacionData dataToSave;
        dataToSave.idEspecializacion = especializacion->getId();
        dataToSave.idEmpresa = especializacion->getIdEmpresa();
        dataToSave.nombreEmpresa = especializacion->getNombreEmpresa();
        dataToSave.tituloActividad = especializacion->getTitulo();
        dataToSave.descripcionActividad = especializacion->getDescripcion();
        dataToSave.idsCursosInternos = especializacion->getIdsCursos(); // Asegúrate de que Especializacion tenga este getter

        if (FilesManager::getInstance().actualizarEspecializacion(dataToSave) != FileOperationResult::SUCCESS) {
            logError("Actualizar especialización", "Error al guardar en archivo");
            return ContentOperationResult::FILE_ERROR;
        }

        logOperation("Actualizar especialización", "Especialización con ID " + std::to_string(idEspecializacion) + " actualizada.");
        return ContentOperationResult::SUCCESS;
    }
    catch (const std::exception& e) {
        logError("Actualizar especialización", e.what());
        return ContentOperationResult::UNKNOWN_ERROR;
    }
}

inline ContentOperationResult ContentManager::eliminarEspecializacion(int idEspecializacion) {
    try {
        auto it = _especializaciones.buscar([idEspecializacion](const std::unique_ptr<Especializacion>& especializacion) {
            return especializacion->getId() == idEspecializacion;
            });

        if (!it.esValido()) {
            logError("Eliminar especialización", "Especialización no encontrada: " + std::to_string(idEspecializacion));
            return ContentOperationResult::COURSE_NOT_FOUND;
        }

        // Eliminar del archivo de persistencia
        if (FilesManager::getInstance().eliminarEspecializacion(idEspecializacion) != FileOperationResult::SUCCESS) {
            logError("Eliminar especialización", "Error al eliminar de archivo");
            return ContentOperationResult::FILE_ERROR;
        }

        // Eliminar de la lista en memoria
        _especializaciones.eliminar(it);

        // Eliminar de la caché
        _cacheIdEspecializaciones.erase(idEspecializacion);

        // Limpiar progreso y calificaciones relacionadas
        for (auto& entry : _progresoEstudiantes) {
            entry.second.erase(idEspecializacion);
        }
        for (auto& entry : _calificacionesActividades) {
            if (entry.first == idEspecializacion) {
                _calificacionesActividades.erase(entry.first);
                break;
            }
        }

        logOperation("Eliminar especialización", "Especialización con ID " + std::to_string(idEspecializacion) + " eliminada.");
        return ContentOperationResult::SUCCESS;
    }
    catch (const std::exception& e) {
        logError("Eliminar especialización", e.what());
        return ContentOperationResult::UNKNOWN_ERROR;
    }
}

inline ContentOperationResult ContentManager::inscribirEstudianteAEspecializacion(int idEstudiante, int idEspecializacion) {
    try {
        Especializacion* especializacion = obtenerEspecializacion(idEspecializacion);
        if (!especializacion) {
            logError("Inscribir estudiante", "Especialización no encontrada: " + std::to_string(idEspecializacion));
            return ContentOperationResult::COURSE_NOT_FOUND;
        }

        // Crear inscripción binaria
        InscripcionBinaria inscripcion(
            idEstudiante,
            idEspecializacion,
            static_cast<int>(ActividadTipo::ESPECIALIZACION),
            0.0,  // Progreso inicial
            false, // No completado
            false  // No pagado
        );

        // Guardar en archivo
        int offsetRegistro;
        auto resultado = FilesManager::getInstance().guardarInscripcionBinaria(inscripcion, offsetRegistro);
        if (resultado != FileOperationResult::SUCCESS) {
            logError("Inscribir estudiante", "Error al guardar inscripción");
            return ContentOperationResult::FILE_ERROR;
        }

        // Actualizar contador de alumnos
        especializacion->aumentarAlumno(1);

        // Inicializar progreso
        _progresoEstudiantes[idEstudiante][idEspecializacion] = 0.0;

        logOperation("Inscribir estudiante",
            "Estudiante " + std::to_string(idEstudiante) + " inscrito en especialización " + std::to_string(idEspecializacion));

        return ContentOperationResult::SUCCESS;
    }
    catch (const std::exception& e) {
        logError("Inscribir estudiante", e.what());
        return ContentOperationResult::UNKNOWN_ERROR;
    }
}

inline ContentOperationResult ContentManager::desinscribirEstudiante(int idEstudiante, int idActividad, ActividadTipo tipoActividad) {
    try {
        // Asumimos que FileManager tiene una función para eliminar inscripciones por ID.
        // Si no la tiene, se debería implementar una que pueda buscar y eliminar.
        // Por ahora, solo se elimina de las estructuras en memoria.

        // Eliminar de _progresoEstudiantes
        auto itEstudiante = _progresoEstudiantes.find(idEstudiante);
        if (itEstudiante != _progresoEstudiantes.end()) {
            itEstudiante->second.erase(idActividad);
            if (itEstudiante->second.empty()) {
                _progresoEstudiantes.erase(itEstudiante);
            }
        }

        // Decrementar contador de alumnos en Curso/Especializacion
        if (tipoActividad == ActividadTipo::CURSO) {
            if (auto curso = obtenerCurso(idActividad)) {
                curso->disminuirAlumno(1);
            }
        }
        else if (tipoActividad == ActividadTipo::ESPECIALIZACION) {
            if (auto especializacion = obtenerEspecializacion(idActividad)) {
                especializacion->disminuirAlumno(1);
            }
        }

        // Si se mantiene la persistencia, se necesita eliminar la inscripción del archivo
        // Esto implicaría una función en FileManager que elimine una inscripción específica
        // o que reescriba el archivo de inscripciones.

        logOperation("Desinscribir estudiante",
            "Estudiante " + std::to_string(idEstudiante) + " desinscrito de actividad " + std::to_string(idActividad));

        return ContentOperationResult::SUCCESS;
    }
    catch (const std::exception& e) {
        logError("Desinscribir estudiante", e.what());
        return ContentOperationResult::UNKNOWN_ERROR;
    }
}


inline ContentOperationResult ContentManager::actualizarProgreso(int idEstudiante, int idActividad, double nuevoProgreso) {
    if (nuevoProgreso < 0.0 || nuevoProgreso > 100.0) {
        logError("Actualizar progreso", "Progreso inválido: " + std::to_string(nuevoProgreso));
        return ContentOperationResult::INVALID_DATA;
    }

    auto itEstudiante = _progresoEstudiantes.find(idEstudiante);
    if (itEstudiante != _progresoEstudiantes.end()) {
        auto itActividad = itEstudiante->second.find(idActividad);
        if (itActividad != itEstudiante->second.end()) {
            itActividad->second = nuevoProgreso;

            // Actualizar en archivo de persistencia si es necesario
            // Esto requeriría leer todas las inscripciones, encontrar la correcta y reescribirla,
            // o que FileManager tenga una función para actualizar una inscripción específica por ID y Estudiante ID.
            // Para mantener la consistencia, idealmente se debería actualizar el archivo aquí.

            logOperation("Actualizar progreso",
                "Progreso de estudiante " + std::to_string(idEstudiante) + " en actividad " +
                std::to_string(idActividad) + " a " + std::to_string(nuevoProgreso) + "%");
            return ContentOperationResult::SUCCESS;
        }
    }

    logError("Actualizar progreso", "Inscripción no encontrada para actualizar progreso.");
    return ContentOperationResult::COURSE_NOT_FOUND; // O un código más específico si la inscripción no existe
}

inline ContentOperationResult ContentManager::agregarCalificacion(int idActividad, int idEstudiante, int calificacion, const std::string& comentario) {
    if (calificacion < 1 || calificacion > 5) {
        logError("Agregar calificación", "Calificación inválida: " + std::to_string(calificacion));
        return ContentOperationResult::INVALID_DATA;
    }

    // Aquí almacenaríamos la calificación. La estructura _calificacionesActividades
    // tiene [idActividad][idEstudiante] -> (calificacion, comentario)
    _calificacionesActividades[idActividad][idEstudiante] = std::make_pair(calificacion, comentario);

    // Persistir calificación (si se desea)
    // Esto implicaría una estructura de datos para calificaciones en FileManager
    // y una función para guardarlas.

    logOperation("Agregar calificación",
        "Calificación de " + std::to_string(calificacion) + " agregada por estudiante " +
        std::to_string(idEstudiante) + " a actividad " + std::to_string(idActividad));

    return ContentOperationResult::SUCCESS;
}


inline std::vector<Curso*> ContentManager::buscarCursosPorCategoria(const std::string& categoria) const {
    std::vector<Curso*> resultados;
    for (auto it = _cursos.begin(); it != _cursos.end(); ++it) {
        if ((*it)->getCategoria() == categoria) {
            resultados.push_back(it->get());
        }
    }
    return resultados;
}

inline std::vector<Especializacion*> ContentManager::buscarEspecializacionesPorCategoria(const std::string& categoria) const {
    std::vector<Especializacion*> resultados;
    for (auto it = _especializaciones.begin(); it != _especializaciones.end(); ++it) {
        if ((*it)->getCategoria() == categoria) {
            resultados.push_back(it->get());
        }
    }
    return resultados;
}

inline std::pair<std::vector<Curso*>, std::vector<Especializacion*>> ContentManager::obtenerActividadesPorEmpresa(int idEmpresa) const {
    std::vector<Curso*> cursosEmpresa;
    std::vector<Especializacion*> especializacionesEmpresa;

    for (auto it = _cursos.begin(); it != _cursos.end(); ++it) {
        if ((*it)->getIdEmpresa() == idEmpresa) {
            cursosEmpresa.push_back(it->get());
        }
    }

    for (auto it = _especializaciones.begin(); it != _especializaciones.end(); ++it) {
        if ((*it)->getIdEmpresa() == idEmpresa) {
            especializacionesEmpresa.push_back(it->get());
        }
    }
    return { cursosEmpresa, especializacionesEmpresa };
}

inline std::vector<InscripcionBinaria> ContentManager::obtenerInscripcionesEstudiante(int idEstudiante) const {
    std::vector<InscripcionBinaria> inscripciones;
    // Esto requiere leer las inscripciones de FileManager, ya que _progresoEstudiantes
    // solo guarda progreso, no la estructura completa de InscripcionBinaria.
    // O si se carga InscripcionBinaria en otra estructura de datos en memoria.

    // Asumiendo que FilesManager::getInstance().leerDatosInscripciones() devuelve todas las inscripciones,
    // se tendría que filtrar aquí, o FileManager podría ofrecer una búsqueda específica.

    auto allInscripciones = FilesManager::getInstance().leerDatosInscripciones();
    for (const auto& insc : allInscripciones) {
        if (insc.idEstudiante == idEstudiante) {
            inscripciones.push_back(insc);
        }
    }
    return inscripciones;
}

inline std::vector<Curso*> ContentManager::obtenerCursosMasPopulares(int limite) const {
    // Para determinar popularidad, se podría usar el número de alumnos inscritos.
    std::vector<Curso*> todosLosCursos;
    for (auto it = _cursos.begin(); it != _cursos.end(); ++it) {
        todosLosCursos.push_back(it->get());
    }

    std::sort(todosLosCursos.begin(), todosLosCursos.end(), [](Curso* a, Curso* b) {
        return a->getNumAlumnos() > b->getNumAlumnos();
        });

    if (todosLosCursos.size() > limite) {
        todosLosCursos.resize(limite);
    }
    return todosLosCursos;
}

inline std::vector<Especializacion*> ContentManager::obtenerEspecializacionesMasPopulares(int limite) const {
    // Para determinar popularidad, se podría usar el número de alumnos inscritos.
    std::vector<Especializacion*> todasLasEspecializaciones;
    for (auto it = _especializaciones.begin(); it != _especializaciones.end(); ++it) {
        todasLasEspecializaciones.push_back(it->get());
    }

    std::sort(todasLasEspecializaciones.begin(), todasLasEspecializaciones.end(), [](Especializacion* a, Especializacion* b) {
        return a->getNumAlumnos() > b->getNumAlumnos();
        });

    if (todasLasEspecializaciones.size() > limite) {
        todasLasEspecializaciones.resize(limite);
    }
    return todasLasEspecializaciones;
}

inline ContentOperationResult ContentManager::guardarTodosCambios() {
    try {
        // 1. Recolectar todos los RawCursoData
        std::vector<RawCursoData> cursosRaw;
        for (auto it = _cursos.begin(); it != _cursos.end(); ++it) {
            const auto& cursoPtr = *it;
            RawCursoData data;
            data.idCurso = cursoPtr->getId();
            data.idEmpresa = cursoPtr->getIdEmpresa();
            data.nombreEmpresa = cursoPtr->getNombreEmpresa();
            data.tituloActividad = cursoPtr->getTitulo();
            data.descripcionActividad = cursoPtr->getDescripcion();
            data.instructor = cursoPtr->getInstructor();
            data.cantidadClases = cursoPtr->getCantidadClases();
            // Necesitas una forma de obtener los títulos y descripciones de las clases del objeto Curso
            // Por ejemplo, `cursoPtr->getTitulosClases()` y `cursoPtr->getDescripcionesClases()`
            // Asumiendo que existen, se añadirían aquí:
            // data.titulosClases = cursoPtr->getTitulosClases();
            // data.descripcionesClases = cursoPtr->getDescripcionesClases();
            cursosRaw.push_back(data);
        }

        // 2. Recolectar todas las RawEspecializacionData
        std::vector<RawEspecializacionData> especializacionesRaw;
        for (auto it = _especializaciones.begin(); it != _especializaciones.end(); ++it) {
            const auto& espPtr = *it;
            RawEspecializacionData data;
            data.idEspecializacion = espPtr->getId();
            data.idEmpresa = espPtr->getIdEmpresa();
            data.nombreEmpresa = espPtr->getNombreEmpresa();
            data.tituloActividad = espPtr->getTitulo();
            data.descripcionActividad = espPtr->getDescripcion();
            data.idsCursosInternos = espPtr->getIdsCursos(); // Asumiendo que Especializacion tiene este getter
            especializacionesRaw.push_back(data);
        }

        // 3. Crear RawActividadesData y guardar
        RawActividadesData allActividades;
        allActividades.cursos = cursosRaw;
        allActividades.especializaciones = especializacionesRaw;

        if (FilesManager::getInstance().guardarDatosActividades(allActividades) != FileOperationResult::SUCCESS) {
            logError("Guardar cambios", "Error al guardar actividades.");
            return ContentOperationResult::FILE_ERROR;
        }

        // 4. Recolectar todas las InscripcionBinaria desde _progresoEstudiantes
        // Esto asume que _progresoEstudiantes es la fuente de verdad para las inscripciones
        // y que puedes derivar InscripcionBinaria completa de ella (incluyendo tipo de actividad).
        // Si no, necesitarías una estructura de datos más completa para las inscripciones en memoria.
        std::vector<InscripcionBinaria> inscripcionesBinarias;
        // Esta parte es compleja porque _progresoEstudiantes no guarda el tipo de actividad.
        // Necesitarías un mapa que guarde el tipo de actividad para cada idActividad.
        // O recorrer _cursos y _especializaciones para inferir el tipo.
        // Por simplicidad, se necesitaría una estructura de datos que mantenga las InscripcionBinaria en memoria
        // de forma completa después de la carga inicial. O bien, el FileManager tendría la lógica para
        // sobreescribir las inscripciones basándose en los datos actuales.

        // Una solución más robusta sería mantener una `LinkedList<InscripcionBinaria>`
        // o `std::map<int, std::map<int, InscripcionBinaria>> _inscripciones;`
        // Para este ejemplo, omitimos la reconstrucción completa de inscripciones desde _progresoEstudiantes
        // porque el tipo de actividad no está directamente disponible allí.
        // Deberías ajustar esto a cómo las inscripciones se manejan en tu sistema.
        // Aquí un placeholder:
        // auto currentInscripciones = obtenerTodasLasInscripcionesInternamente();
        // if (FilesManager::getInstance().guardarDatosInscripciones(currentInscripciones) != FileOperationResult::SUCCESS) {
        //     logError("Guardar cambios", "Error al guardar inscripciones.");
        //     return ContentOperationResult::FILE_ERROR;
        // }

        logOperation("Guardar cambios", "Todos los datos guardados exitosamente.");
        return ContentOperationResult::SUCCESS;
    }
    catch (const std::exception& e) {
        logError("Guardar cambios", e.what());
        return ContentOperationResult::UNKNOWN_ERROR;
    }
}


inline ContentOperationResult ContentManager::recargarDatos() {
    logOperation("Recargar datos", "Iniciando recarga de datos del sistema.");
    limpiarCaches(); // Limpiar cachés y estructuras de datos actuales

    // Los contadores de ID deben ser reseteados o recalculados de los datos cargados.
    // Para un sistema con persistencia, lo ideal es que los IDs se generen a partir del
    // máximo ID existente en los datos cargados para evitar colisiones.
    // Por simplicidad, se resetean aquí. En un entorno de producción, necesitarías
    // leer los IDs máximos de los archivos.
    _nextCursoId = 1;
    _nextEspecializacionId = 1;

    return inicializarSistema() ? ContentOperationResult::SUCCESS : ContentOperationResult::UNKNOWN_ERROR;
}

#endif // COURSERACLONE_CONTROLLERS_COURSEMANAGER_HPP
