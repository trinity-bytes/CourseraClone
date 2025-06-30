#ifndef COURSERACLONE_CONTROLLERS_ACTIVIDADESCONTROLLER_HPP
#define COURSERACLONE_CONTROLLERS_ACTIVIDADESCONTROLLER_HPP

#include "../DataStructures/LinkedList.hpp"

class ActividadesController {
private:
	std::unique_ptr<LinkedList<int>> idCursos;
	std::unique_ptr<LinkedList<int>>  idEspecializaciones;
	int idOrganizacion;


	void logOperation(const std::string& operation, const std::string& details);
	void logError(const std::string& operation, const std::string& error);

public:
	// Constructor por defecto
	inline ActividadesController();
	// Constructor con id del alumno para cargar datos
	inline ActividadesController(int _idOrganizacion);


};

// Constructores
inline ActividadesController::ActividadesController()
{
	idCursos = std::make_unique<LinkedList<int>>();
	idEspecializaciones = std::make_unique<LinkedList<int>>();
	idOrganizacion = -1;
}

inline ActividadesController::ActividadesController(int _idOrganizacion) {
	// Inicializar estructuras de datos
	idCursos = std::make_unique<LinkedList<int>>();
	idEspecializaciones = std::make_unique<LinkedList<int>>();
	idOrganizacion = _idOrganizacion;

	/*

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
	*/
}

#endif // COURSERACLONE_CONTROLLERS_ACTIVIDADESCONTROLLER_HPP