#ifndef COURSERACLONE_CONTROLLERS_INSCRIPCIONESCONTROLLER_HPP
#define COURSERACLONE_CONTROLLERS_INSCRIPCIONESCONTROLLER_HPP

// Headers estándar

// Headers propios
#include "../DataStructures/ArbolAVL.hpp"
#include "../DataStructures/Stack.hpp"
#include "../Entities/Inscripcion.hpp"

class InscripcionesController
{
private:
	// Estructuras de datos principales
	Stack<Inscripcion> inscripcionesCursos;
	Stack<Inscripcion> inscripcionesEspecialidades;
	std::unique_ptr<ArbolAVL<int>> idCursos, idEspecialidades;

	// Utilidades privadas
	void logOperation(const std::string& operation, const std::string& details);
	void logError(const std::string& operation, const std::string& error);

public:
	// Constructor por defecto
	inline InscripcionesController();
	// Constructor con id del alumno para cargar datos
	inline InscripcionesController(int _idEstudiante);
};

// Constructores
inline InscripcionesController::InscripcionesController()
{
	idCursos = std::make_unique<ArbolAVL<int>>();
	idEspecialidades = std::make_unique<ArbolAVL<int>>();
}

inline InscripcionesController::InscripcionesController(int _idEstudiante) {
	// Inicializar estructuras de datos
	idCursos = std::make_unique<ArbolAVL<int>>();
	idEspecialidades = std::make_unique<ArbolAVL<int>>();

	std::vector<RawInscripcionData> inscripcionesCursosRaw;
	// Cargar inscripciones desde disco
	FileOperationResult resultado = FilesManager::getInstance().cargarInscripcionesPorEstudiante(_idEstudiante, inscripcionesCursosRaw);

	if (resultado == FileOperationResult::SUCCESS) {
		for (RawInscripcionData& rawInscripcion : inscripcionesCursosRaw) {
			Inscripcion inscripcion(rawInscripcion);
			if (inscripcion.getTipo() == TipoActividad::CURSO) {
				inscripcionesCursos.push(inscripcion);
				int idActividad = inscripcion.getIdActividad();
				if (idCursos->Insertar(inscripcion.getIdActividad())) {
					logOperation("Insertar en AVL de curso", "ID: " + std::to_string(idActividad));
				}
				else {
					logError("Insertar en AVL de curso", "Error en el ID: " + std::to_string(idActividad));
				}
			}
			else if (inscripcion.getTipo() == TipoActividad::ESPECIALIZACION) {
				inscripcionesEspecialidades.push(inscripcion);
				int idEspecializacion = inscripcion.getIdActividad();
				if (idCursos->Insertar(inscripcion.getIdActividad())) {
					logOperation("Insertar en AVL de especialidad", "ID: " + std::to_string(idEspecializacion));
				}
				else {
					logError("Insertar en AVL de especialidad", "Error en el ID: " + std::to_string(idEspecializacion));
				}
			}
		}
		logOperation("Cargar inscripciones", "Se han cargado " + std::to_string(inscripcionesCursosRaw.size()) + " inscripciones para el ID: " + std::to_string(_idEstudiante));

	}
	else {
		logError("Cargar inscripciones", "Fallo en el resultado de inscripciones RAW");
	}
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