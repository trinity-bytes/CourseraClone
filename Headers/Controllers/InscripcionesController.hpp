#ifndef COURSERACLONE_CONTROLLERS_INSCRIPCIONESCONTROLLER_HPP
#define COURSERACLONE_CONTROLLERS_INSCRIPCIONESCONTROLLER_HPP

// Headers estándar

// Headers propios
#include "../DataStructures/ArbolAVL.hpp"
#include "../DataStructures/Stack.hpp"
#include "../Entities/Inscripcion.hpp"
#include "../Controllers/ContentManager.hpp"

class InscripcionesController
{
private:
	// Estructuras de datos principales
	Stack<Inscripcion> inscripcionesCursos;
	Stack<Inscripcion> inscripcionesEspecialidades;
	std::unique_ptr<ArbolAVL<int>> idCursos;
	std::unique_ptr<ArbolAVL<int>> idEspecialidades;
	int idEstudiante;


	// Utilidades privadas
	void logOperation(const std::string& operation, const std::string& details);
	void logError(const std::string& operation, const std::string& error);

public:
	// Constructor por defecto
	inline InscripcionesController();
	// Constructor con id del alumno para cargar datos
	inline InscripcionesController(int _idEstudiante);

	// Metodos para inscripciones
	inline void guardarCursoInscripcion(Inscripcion inscripcion);
	inline void guardarEspecializacionInscripcion(Inscripcion inscripcion);
	inline FileOperationResult inscribirCurso(int idCurso);
	inline FileOperationResult inscribirEspecializacion(int idEspecializacion);
	inline bool verificarCurso(int idCurso);
	inline bool verificarEspecializacion(int idEspecializacion);
	inline void mostrarCursos();

	// Métodos para visualizar inscripciones
	inline std::vector<ElementoInscripcion> getElementosInscripcionesDash(Stack<Inscripcion>& inscripciones);
	inline std::vector<ElementoInscripcion> getElementosInscripcionesDashTodos(TipoActividad tipo);
};

// Constructores
inline InscripcionesController::InscripcionesController()
{
	idCursos = std::make_unique<ArbolAVL<int>>();
	idEspecialidades = std::make_unique<ArbolAVL<int>>();
	idEstudiante = -1;
}

inline InscripcionesController::InscripcionesController(int _idEstudiante) {
	// Inicializar estructuras de datos
	idCursos = std::make_unique<ArbolAVL<int>>();
	idEspecialidades = std::make_unique<ArbolAVL<int>>();
	idEstudiante = _idEstudiante;

	std::vector<RawInscripcionData> inscripcionesCursosRaw;
	// Cargar inscripciones desde disco
	FileOperationResult resultado = FilesManager::getInstance().cargarInscripcionesPorEstudiante(_idEstudiante, inscripcionesCursosRaw);
	// throw std::runtime_error(std::to_string(inscripcionesCursosRaw.size()));

	if (resultado == FileOperationResult::SUCCESS) {
	
		for (RawInscripcionData& rawInscripcion : inscripcionesCursosRaw) {
			Inscripcion inscripcion(rawInscripcion);
			if (inscripcion.getTipo() == TipoActividad::CURSO) {
				guardarCursoInscripcion(inscripcion);
			}
			else if (inscripcion.getTipo() == TipoActividad::ESPECIALIZACION) {
				guardarEspecializacionInscripcion(inscripcion);
			}
		}
		logOperation("Cargar inscripciones", "Se han cargado " + std::to_string(inscripcionesCursosRaw.size()) + " inscripciones para el ID: " + std::to_string(_idEstudiante));

	}
	else {
		logError("Cargar inscripciones", "Fallo en el resultado de inscripciones RAW");
	}
}


// ========== MÉTODOS DE INSCRIPCION ==========
inline void InscripcionesController::guardarCursoInscripcion(Inscripcion inscripcion) {
	
	int idActividad = inscripcion.getIdActividad();
	if (idCursos->Insertar(inscripcion.getIdActividad())) {
		inscripcionesCursos.push(inscripcion);
		logOperation("Insertar en AVL de curso", "ID: " + std::to_string(idActividad));
	}
	else {
		logError("Insertar en AVL de curso", "Error en el ID: " + std::to_string(idActividad));
	}
}

inline void InscripcionesController::guardarEspecializacionInscripcion(Inscripcion inscripcion) {
	int idEspecializacion = inscripcion.getIdActividad();
	if (idEspecialidades->Insertar(inscripcion.getIdActividad())) {
		inscripcionesEspecialidades.push(inscripcion);
		logOperation("Insertar en AVL de especialidad", "ID: " + std::to_string(idEspecializacion));
	}
	else {
		logError("Insertar en AVL de especialidad", "Error en el ID: " + std::to_string(idEspecializacion));
	}
}

inline FileOperationResult InscripcionesController::inscribirCurso(int idCurso) {
	if (!idCursos->Insertar(idCurso)) {
		logError("Inscribir curso",
			"ID duplicado, no se agrega: curso " + std::to_string(idCurso) +
			" para estudiante " + std::to_string(idEstudiante));
		return FileOperationResult::DUPLICATED_VALUE;
	}

	// 2) Crea la nueva Inscripcion y la persiste en disco
	int idActual = FilesManager::getInstance().cantidadInscripciones();
	Inscripcion nueva(idEstudiante, idCurso, idActual, TipoActividad::CURSO);
	nueva.guardar();
	inscripcionesCursos.push(nueva);

	logOperation("Inscribir curso",
		"Éxito: curso " + std::to_string(idCurso) +
		" para estudiante " + std::to_string(idEstudiante));
	return FileOperationResult::SUCCESS;
}

inline FileOperationResult InscripcionesController::inscribirEspecializacion(int idEspecializacion) {
	if (!idEspecialidades->Insertar(idEspecializacion)) {
		logError("Inscribir especializacion", 
			"ID duplicado, no se agrega: especializacion " + std::to_string(idEspecializacion) + 
			" para estudiante " + std::to_string(idEstudiante));
		return FileOperationResult::DUPLICATED_VALUE;
	}
	// 2) Crea la nueva Inscripcion y la persiste en disco
	int idActual = FilesManager::getInstance().cantidadInscripciones();
	Inscripcion nueva(idEstudiante, idEspecializacion, idActual, TipoActividad::ESPECIALIZACION);
	nueva.guardar();
	inscripcionesEspecialidades.push(nueva);
	logOperation("Inscribir especializacion",
		"Éxito: especializacon " + std::to_string(idEspecializacion) +
		" para estudiante " + std::to_string(idEstudiante));
	return FileOperationResult::SUCCESS;
}

inline bool InscripcionesController::verificarCurso(int idCurso) {
	return idCursos->Buscar(idCurso);
}

inline bool InscripcionesController::verificarEspecializacion(int idEspecializacion) {
	return idEspecialidades->Buscar(idEspecializacion);
}

inline void InscripcionesController::mostrarCursos() {
	idCursos.get()->inOrden();
}

inline std::vector<ElementoInscripcion> InscripcionesController::getElementosInscripcionesDash(Stack<Inscripcion>& inscripciones) {
	std::vector<ElementoInscripcion> elementos;
	int cantidad = inscripciones.getTamano();
	int minimo = (cantidad > 3) ? 3 : cantidad;
	for (int i = 0; i < minimo; i++) {
		RawInscripcionElementoDash inscripcion = inscripciones.get(i).obtenerElementoDash();
		ElementoInscripcion nuevoElemento = ContentManager::getInstance().cargarDatosInscripcionDash(inscripcion);
		elementos.push_back(nuevoElemento);
	}
	return elementos;
}

inline std::vector<ElementoInscripcion> InscripcionesController::getElementosInscripcionesDashTodos(TipoActividad tipo) {
	if (tipo == TipoActividad::CURSO) return getElementosInscripcionesDash(inscripcionesCursos);
	return getElementosInscripcionesDash(inscripcionesEspecialidades);
}

// ========== MÉTODOS PRIVADOS - LOGGING ==========
inline void InscripcionesController::logError(const std::string& operation, const std::string& error) {
    // Implementación simple para logging de errores
    FilesManager& fileManager = FilesManager::getInstance();
    fileManager.logError(operation, "ContentManager", error);
}


inline void InscripcionesController::logOperation(const std::string& operation, const std::string& details) {
    // Implementación simple para logging de operaciones
    // En un proyecto más complejo esto iría a un archivo de log
	FilesManager& fileManager = FilesManager::getInstance();
	fileManager.logInfo(operation, "InscripcionesController");

}

#endif // COURSERACLONE_CONTROLLERS_INSCRIPCIONESCONTROLLER_HPP