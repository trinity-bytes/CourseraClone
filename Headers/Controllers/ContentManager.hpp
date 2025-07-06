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
#include "../DataStructures/PriorityQueue.hpp"

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
    LinkedList<Curso> _cursos;
    LinkedList<Especializacion> _especializaciones;

    // Mapas para seguimiento de progreso y calificaciones
    std::map<int, std::map<int, double>> _progresoEstudiantes; // [idEstudiante][idActividad] -> progreso
    std::map<int, std::map<int, std::pair<int, std::string>>> _calificacionesActividades; // [idActividad][idEstudiante] -> (calificacion, comentario)

    // Contadores para IDs autoincrementales
    int _nextCursoId;
    int _nextEspecializacionId;

    // Utilidades privadas

    void logOperation(const std::string& operation, const std::string& details);
    void logError(const std::string& operation, const std::string& error);

public:
    // Eliminar constructor de copia y operador de asignación para asegurar una única instancia
    ContentManager(const ContentManager&) = delete;
    ContentManager& operator=(const ContentManager&) = delete;

    /// Método estático para obtener la única instancia de la clase
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
        const RawActividadesData& dataActividades
    );

    ContentOperationResult cargarCantidadInscripcionesActividad(
        const std::vector<InscripcionBinaria>& dataInscripciones);

    ContentOperationResult cargarMontoRecaudadoActividad(
        const std::vector<RawComprobanteData>& comprobantes
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
		double precio,
        const std::string& instructor,
        const std::string& descripcion,
        const std::vector<std::string>& titulosClases,
        const std::vector<std::string>& descripcionesClases,
        const std::string& categoria = ""
    );


    ElementoInscripcion cargarDatosInscripcionDash(RawInscripcionElementoDash data);

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


    // ========== BÚSQUEDAS Y CONSULTAS ==========

    /**
     * @brief Obtiene un curso por su ID
     * @param id ID del curso
     * @return Puntero al curso o nullptr si no existe
     */
    Curso* obtenerCurso(int id);

    RawCursoData obtenerCursoDatos(int id);

    ElementoMenu obtenerRawCursoMenu(int id);

    void aumentarMontoActividad(TipoActividad tipo, int id, double monto);


    RawEspecializacionData ContentManager::obtenerEspecializacionDatos(int id);
    /**
     * @brief Obtiene una especialización por su ID
     * @param id ID de la especialización
     * @return Puntero a la especialización o nullptr si no existe
     */
    Especializacion* obtenerEspecializacion(int id);


    /**
     * @brief Obtiene las inscripciones de un estudiante
     * @param idEstudiante ID del estudiante
     * @return Vector con las inscripciones
     */
    std::vector<InscripcionBinaria> obtenerInscripcionesEstudiante(int idEstudiante) const;

    // ========== ESTADÍSTICAS Y REPORTES ==========



    /**

    */
    std::vector<RawLandingData> obtenerActividadesPopulares(LinkedList<RawLandingData>& actividades, int limite = 3);

    /*
    * @brief Se cargan los datos de los cursos más populares
    * @param tipo Se carga los datos de acuerdo al tipo de actividad
    */
    std::vector<ElementoMenu> elegirObtenerActividadesPopulares(TipoActividad tipo, int limite = 3);


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

    /**
 * @brief Busca cursos cuyos títulos comienzan con el texto dado (case-insensitive).
 * @param texto Texto a buscar como prefijo.
 * @param limite Máximo de resultados a retornar (-1 para sin límite).
 * @return Vector de títulos de cursos que coinciden.
 */
    inline std::vector<std::string> sugerirCursosPorPrefijo(const std::string& texto, int limite = -1) const;


    // ========== GETTERS ==========

    const LinkedList<Curso>& getCursos() const { return _cursos; }
    const LinkedList<Especializacion>& getEspecializaciones() const { return _especializaciones; }

    int getTotalCursos() const { return _cursos.getTamano(); }
    int getTotalEspecializaciones() const { return _especializaciones.getTamano(); }
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
    FilesManager& fileManager = FilesManager::getInstance();

    RawActividadesData dataActividades = fileManager.leerDatosActividades();
    std::vector<InscripcionBinaria> dataInscripciones = fileManager.leerDatosInscripciones();
    std::vector<RawComprobanteData> dataComprobantes = fileManager.leerDatosComprobantes();

    // Para debugging: mostrar cantidad de datos cargados
    int cantidad = dataActividades.cursos.size() + dataActividades.especializaciones.size();
    // throw std::runtime_error(std::to_string(cantidad));

    ContentOperationResult result = cargarDesdeDatos(dataActividades);
    if (result != ContentOperationResult::SUCCESS) {
        logError("Inicialización", "Error al cargar datos: " + std::to_string(static_cast<int>(result)));
        return false;
    }
    logOperation("Inicialización", "ContentManager completada con éxito");

    result = cargarCantidadInscripcionesActividad(dataInscripciones);
    if (result != ContentOperationResult::SUCCESS) {
        logError("Inicializacion", "No hay registros para cargar entidades");
        return false;
    }

    result = cargarMontoRecaudadoActividad(dataComprobantes);


    logOperation("Inicializacion", "Carga de cursos y especializaciones exitosa");

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


inline std::vector<RawLandingData> ContentManager::obtenerActividadesPopulares(LinkedList<RawLandingData>& actividades, int limite) {
    auto ordenadoActividades = [](RawLandingData a1, RawLandingData a2) {
        return a1.cantidad > a2.cantidad;
        };

    PriorityQueue<RawLandingData, decltype(ordenadoActividades)> priorityActividades(limite, ordenadoActividades);
    priorityActividades.llenarDesde(actividades);

    std::vector<RawLandingData> respuesta;
    respuesta = priorityActividades.getElementosOrdenados();
	for (auto& actividad : respuesta) {
        logOperation("Verificar Actividad en Priority Queue, de tipo " + std::to_string(static_cast<int>(actividad.tipo)), 
            "Actividad " + std::to_string(actividad.id) + " con " + std::to_string(actividad.cantidad) + " inscripciones.");
	}
   
    return respuesta;
}

inline std::vector<ElementoMenu> ContentManager::elegirObtenerActividadesPopulares(TipoActividad tipo, int limite) {
    LinkedList<RawLandingData> datos;
    if (tipo == TipoActividad::CURSO) {
        
        for (auto it = _cursos.begin(); it != _cursos.end(); ++it) {
            datos.agregarAlFinal((*it).obtenerDatosLanding());
        }

    }
    else {

        for (auto it = _especializaciones.begin(); it != _especializaciones.end(); ++it) {
            datos.agregarAlFinal((*it).obtenerDatosLanding());
        }

    }

    std::vector<RawLandingData> actividadesOrdenadas = obtenerActividadesPopulares(datos, limite);
    std::vector<ElementoMenu> elementosMenu;
    int cantidad = actividadesOrdenadas.size();
    for (int i = cantidad - 1; i >= 0; i--) {
        RawLandingData actividad = actividadesOrdenadas[i];
        if (tipo == TipoActividad::CURSO) {
            Curso* curso = obtenerCurso(actividad.id);
            if (curso) {
                elementosMenu.push_back(curso->obtenerDatosCrudosMenu());
            }
        }
        else if (tipo == TipoActividad::ESPECIALIZACION) {
            Especializacion* especializacion = obtenerEspecializacion(actividad.id);
            if (especializacion) {
                elementosMenu.push_back(especializacion->obtenerDatosCrudosMenu());
            }
        }
    }

    return elementosMenu;
}

inline std::vector<RawExploradorData> ContentManager::obtenerExploradorDatos() const {
    std::vector<RawExploradorData> datosExplorador;

    // Generic lambda que procesa un contenedor de punteros a objetos con obtenerDatosCrudosExplorador()
    auto procesar = [&](const auto& contenedor) {
        for (auto& ptr : contenedor) {
            datosExplorador.push_back(ptr.obtenerDatosCrudosExplorador());
        }
        };


    procesar(_especializaciones); // procesa el vector de especializaciones
    procesar(_cursos);            // procesa el vector de cursos

    return datosExplorador;
}

inline std::vector<std::string> ContentManager::sugerirCursosPorPrefijo(const std::string& texto, int limite) const
{
    std::vector<std::string> sugerencias;
    if (texto.empty()) return sugerencias;

    // Convertir texto de búsqueda a minúsculas  
    std::string textoLower = texto;
    std::transform(textoLower.begin(), textoLower.end(), textoLower.begin(), [](unsigned char c) { return std::tolower(c); });

    FilesManager& fileManager = FilesManager::getInstance();
	fileManager.cargarCursos();   
    auto& hashCursos = fileManager.getIndiceCursos();

    // Solución: Usar iteradores explícitos para recorrer el hash table  
    for (auto it = hashCursos.begin(); it != hashCursos.end(); ++it) {
        std::string tituloLower = it->first;
        std::transform(tituloLower.begin(), tituloLower.end(), tituloLower.begin(), ::tolower);

        if (tituloLower.find(textoLower) == 0) {
            sugerencias.push_back(it->first);
            if (limite > 0 && static_cast<int>(sugerencias.size()) >= limite) break;
        }
    }
    return sugerencias;
}

inline Curso* ContentManager::obtenerCurso(int id) {
    // Buscar curso por ID real, no por índice
    for (int i = 0; i < _cursos.getTamano(); ++i) {
        if (_cursos.getElemento(i).getId() == id) {
            return &_cursos.getElemento(i);
        }
    }
    logError("obtenerCurso", "Curso con ID " + std::to_string(id) + " no encontrado");
    return nullptr;
}

inline RawCursoData ContentManager::obtenerCursoDatos(int id) {
    Curso* curso = obtenerCurso(id);
    if (curso != nullptr) {
        return curso->obtenerDatosCrudosCurso();
    }
    // Retornar datos vacíos si no se encuentra
    RawCursoData datoVacio;
    datoVacio.id = -1;
    return datoVacio;
}

inline ElementoMenu ContentManager::obtenerRawCursoMenu(int id) {
    Curso* curso = obtenerCurso(id);
    if (curso != nullptr) {
        return curso->obtenerDatosCrudosMenu();
    }
    // Retornar elemento vacío si no se encuentra
    return ElementoMenu("Curso no encontrado", "Error", -1);
}

inline void ContentManager::aumentarMontoActividad(TipoActividad tipo, int id, double monto) {
    if (tipo == TipoActividad::CURSO) {
        _cursos.getElemento(id).aumentarMonto(monto);
    }
    else {
        _especializaciones.getElemento(id).aumentarMonto(monto);
    }
}

inline Especializacion* ContentManager::obtenerEspecializacion(int id) {
    // Buscar especialización por ID real, no por índice
    for (int i = 0; i < _especializaciones.getTamano(); ++i) {
        if (_especializaciones.getElemento(i).getId() == id) {
            return &_especializaciones.getElemento(i);
        }
    }
    logError("obtenerEspecializacion", "Especialización con ID " + std::to_string(id) + " no encontrada");
    return nullptr;
}

inline RawEspecializacionData ContentManager::obtenerEspecializacionDatos(int id) {
    return obtenerEspecializacion(id)->obtenerDatosCrudosEspecialidad();
}

// ========== CARGA DE DATOS ==========

inline ContentOperationResult ContentManager::cargarDesdeDatos(
    const RawActividadesData& dataActividades
) {
    try {
        // Limpiar datos existentes
        _cursos.clear();
        _especializaciones.clear();

        // Cargar cursos desde datos crudos
        for (const auto& cursoData : dataActividades.cursos) {
            auto curso = Curso(
                cursoData.id,
                cursoData.idEmpresa,
                cursoData.nombreEmpresa,
                cursoData.categoria,
                cursoData.titulo,
                cursoData.descripcion,
                cursoData.instructor,
                cursoData.cantidadClases,
                cursoData.descripcionClases,
                cursoData.precio
            );

            _cursos.agregarAlFinal(curso);

            // Actualizar contador de IDs
            if (cursoData.id >= _nextCursoId) {
                _nextCursoId = cursoData.id + 1;
            }
        }

        // Cargar especializaciones desde datos crudos
        for (const auto& espData : dataActividades.especializaciones) {
            auto especializacion = Especializacion(
                espData.id,
                espData.idEmpresa,
                espData.nombreEmpresa,
                espData.categoria,
                espData.titulo,
                espData.descripcion,
                espData.idsCursos,
                espData.duracionEstimada,
				espData.precio
            );

            _especializaciones.agregarAlFinal(std::move(especializacion));

            // Actualizar contador de IDs
            if (espData.id >= _nextEspecializacionId) {
                _nextEspecializacionId = espData.id + 1;
            }
        }


        logOperation("CargarDesdeDatos",
            "Cargados " + std::to_string(dataActividades.cursos.size()) + " cursos y " +
            std::to_string(dataActividades.especializaciones.size()) + " especializaciones");

        return ContentOperationResult::SUCCESS;

    }
    catch (const std::exception& e) {
        logError("CargarDesdeDatos", e.what());
        return ContentOperationResult::UNKNOWN_ERROR;
    }
}

inline ContentOperationResult ContentManager::cargarCantidadInscripcionesActividad(
    const std::vector<InscripcionBinaria>& dataInscripciones) {

    if (static_cast<int>(dataInscripciones.size()) == 0) {
        logOperation("Carga de cantidad inscripciones", "No hay inscripciones para anadir a los cursos");
        return ContentOperationResult::SUCCESS;
    }

    for (InscripcionBinaria inscripcion : dataInscripciones) {
        int idActividad = inscripcion.idActividad;
        TipoActividad tipoActividad = static_cast<TipoActividad>(inscripcion.tipoActividad);

        bool completado = inscripcion.completado;
        if (tipoActividad == TipoActividad::CURSO) {
            _cursos.getElemento(idActividad).aumentarAlumno();
            if (completado) _cursos.getElemento(idActividad).aumentarAlumnoCompletado();
        }
        else {
            _especializaciones.getElemento(idActividad).aumentarAlumno();
            if (completado) _especializaciones.getElemento(idActividad).aumentarAlumnoCompletado();
        }

        
    }

    int cantidadCursos = _cursos.getTamano();
    for (int i = 0; i < cantidadCursos; i++) {
        logOperation("Carga de curso", _cursos.getElemento(i).getTitulo() + ": " + std::to_string(_cursos.getElemento(i).getCantidad()));
    }
    int cantidadEspecializaciones = _especializaciones.getTamano();
    for (int i = 0; i < cantidadEspecializaciones; i++) {
        logOperation("Carga de curso", _especializaciones.getElemento(i).getTitulo() + ": " + std::to_string(_especializaciones.getElemento(i).getCantidad()));
    }

    logOperation("Carga de cantidad inscripciones", "Se han cargado todos los datos de las inscripciones");
    return ContentOperationResult::SUCCESS;
}

inline ContentOperationResult ContentManager::cargarMontoRecaudadoActividad(
    const std::vector<RawComprobanteData>& dataComprobantes) {

    if (static_cast<int>(dataComprobantes.size()) == 0) {
        logOperation("Carga de cantidad comprobantes", "No hay comprobantes");
        return ContentOperationResult::SUCCESS;
    }

    for (RawComprobanteData comprobante : dataComprobantes) {
        int idActividad = comprobante.idActividad;
        TipoActividad tipo = static_cast<TipoActividad>(comprobante.tipoActividad);
        double monto = comprobante.montoPagado;
        aumentarMontoActividad(tipo, idActividad, monto);
    }

    logOperation("Carga de cantidad comprobantes", "Todos los comprobantes han sido cargados");
    return ContentOperationResult::SUCCESS;
}


inline ElementoInscripcion ContentManager::cargarDatosInscripcionDash(RawInscripcionElementoDash data) {
    ElementoInscripcion inscripcion;
    int idAhora = data.idActividad;
    inscripcion.idInscripcion = data.idInscripcion;
    inscripcion.tipo = data.tipo;
    inscripcion.idActividad = idAhora;

    if (data.tipo == TipoActividad::CURSO) {
        inscripcion.titulo = _cursos.getElemento(idAhora).getTitulo();
        inscripcion.descripcion = _cursos.getElemento(idAhora).getDescripcion();
    }
    else {
        inscripcion.titulo = _especializaciones.getElemento(idAhora).getTitulo();
        inscripcion.descripcion = _especializaciones.getElemento(idAhora).getDescripcion();
    }

    return inscripcion;
}

// Implementación de obtenerInscripcionesEstudiante
inline std::vector<InscripcionBinaria> ContentManager::obtenerInscripcionesEstudiante(int idEstudiante) const
{
    FilesManager& fileManager = FilesManager::getInstance();
    std::vector<InscripcionBinaria> todasLasInscripciones = fileManager.leerDatosInscripciones();
    std::vector<InscripcionBinaria> inscripcionesEstudiante;
    
    // Filtrar inscripciones por estudiante
    for (const auto& inscripcion : todasLasInscripciones) {
        if (inscripcion.idEstudiante == idEstudiante) {
            inscripcionesEstudiante.push_back(inscripcion);
        }
    }
    
    return inscripcionesEstudiante;
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
    fileManager.logInfo(operation, "Content Manager", details);

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

// ========== MÉTODOS DE CREACIÓN ==========

inline ContentOperationResult ContentManager::crearCurso(
    int idEmpresa,
    const std::string& titulo,
    const std::string& nombreEmpresa,
    double precio,
    const std::string& instructor,
    const std::string& descripcion,
    const std::vector<std::string>& titulosClases,
    const std::vector<std::string>& descripcionesClases,
    const std::string& categoria)
{
    try {
        // Validar datos básicos
        if (titulo.empty() || instructor.empty() || titulosClases.empty()) {
            logError("CrearCurso", "Datos básicos incompletos");
            return ContentOperationResult::INVALID_DATA;
        }

        if (titulosClases.size() != descripcionesClases.size()) {
            logError("CrearCurso", "Mismatch entre títulos y descripciones de clases");
            return ContentOperationResult::INVALID_DATA;
        }

        // Crear vector de pares para las clases
        std::vector<std::pair<std::string, std::string>> descripcionClases;
        for (size_t i = 0; i < titulosClases.size(); ++i) {
            descripcionClases.push_back({titulosClases[i], descripcionesClases[i]});
        }

        // Determinar categoría
        CategoriaActividad cat = CategoriaActividad::DEFAULT;
        if (!categoria.empty()) {
            cat = RawActividadData::stringToCategoria(categoria);
        }

        // Crear objeto Curso
        Curso nuevoCurso(
            _nextCursoId,
            idEmpresa,
            nombreEmpresa,
            cat,
            titulo,
            descripcion,
            instructor,
            static_cast<int>(titulosClases.size()),
            descripcionClases
        );

        // Agregar a la lista
        _cursos.agregarAlFinal(nuevoCurso);

        // Incrementar contador de IDs
        _nextCursoId++;

        // Guardar en archivo
        if (!nuevoCurso.guardar()) {
            logError("CrearCurso", "Error al persistir el curso");
            return ContentOperationResult::FILE_ERROR;
        }

        logOperation("CrearCurso", "Curso '" + titulo + "' creado exitosamente con ID " + std::to_string(nuevoCurso.getId()));
        return ContentOperationResult::SUCCESS;

    } catch (const std::exception& e) {
        logError("CrearCurso", "Excepción: " + std::string(e.what()));
        return ContentOperationResult::UNKNOWN_ERROR;
    }
}

inline ContentOperationResult ContentManager::crearEspecializacion(
    int idEmpresa,
    const std::string& nombreEmpresa,
    const std::string& titulo,
    const std::string& descripcion,
    const std::vector<int>& idsCursos,
    const std::string& categoria)
{
    try {
        // Validar datos básicos
        if (titulo.empty() || idsCursos.empty()) {
            logError("CrearEspecializacion", "Datos básicos incompletos");
            return ContentOperationResult::INVALID_DATA;
        }

        // Validar que todos los cursos existen
        for (int idCurso : idsCursos) {
            bool cursoEncontrado = false;
            for (int i = 0; i < _cursos.getTamano(); ++i) {
                if (_cursos.getElemento(i).getId() == idCurso) {
                    cursoEncontrado = true;
                    break;
                }
            }
            if (!cursoEncontrado) {
                logError("CrearEspecializacion", "Curso con ID " + std::to_string(idCurso) + " no encontrado");
                return ContentOperationResult::COURSE_NOT_FOUND;
            }
        }

        // Determinar categoría
        CategoriaActividad cat = CategoriaActividad::DEFAULT;
        if (!categoria.empty()) {
            cat = RawActividadData::stringToCategoria(categoria);
        }

        // Calcular duración estimada (promedio de 2-3 semanas por curso)
        int duracionEstimada = static_cast<int>(idsCursos.size()) * 2 + (static_cast<int>(idsCursos.size()) / 2);

        // Crear objeto Especializacion
        Especializacion nuevaEspecializacion(
            _nextEspecializacionId,
            idEmpresa,
            nombreEmpresa,
            cat,
            titulo,
            descripcion,
            idsCursos,
            duracionEstimada
        );

        // Agregar a la lista
        _especializaciones.agregarAlFinal(nuevaEspecializacion);

        // Incrementar contador de IDs
        _nextEspecializacionId++;

        // Guardar en archivo usando FilesManager
        RawEspecializacionData rawData;
        rawData.id = nuevaEspecializacion.getId();
        rawData.idEmpresa = idEmpresa;
        rawData.nombreEmpresa = nombreEmpresa;
        rawData.categoria = cat;
        rawData.titulo = titulo;
        rawData.descripcion = descripcion;
        rawData.cantidadCursos = static_cast<int>(idsCursos.size());
        rawData.idsCursos = idsCursos;
        rawData.duracionEstimada = duracionEstimada;

        FileOperationResult resultado = FilesManager::getInstance().guardarEspecializacion(rawData);
        if (resultado != FileOperationResult::SUCCESS) {
            logError("CrearEspecializacion", "Error al persistir la especialización en archivo");
            return ContentOperationResult::FILE_ERROR;
        }

        logOperation("CrearEspecializacion", "Especialización '" + titulo + "' creada exitosamente con ID " + std::to_string(nuevaEspecializacion.getId()));
        return ContentOperationResult::SUCCESS;

    } catch (const std::exception& e) {
        logError("CrearEspecializacion", "Excepción: " + std::string(e.what()));
        return ContentOperationResult::UNKNOWN_ERROR;
    }
}

// ========== UTILIDADES ==========

#endif // COURSERACLONE_CONTROLLERS_COURSEMANAGER_HPP
