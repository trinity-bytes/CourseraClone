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


	// Cargar inscripciones desde disco
	FilesManager& filesManager = FilesManager::getInstance();
	auto inscripciones = filesManager.cargarInscripcionesPorEstudiante(_idEstudiante);
	for (const auto& inscripcion : inscripciones) {
		if (inscripcion.tipo == TipoActividad::CURSO) {
			inscripcionesCursos.push(inscripcion);
			idCursos->insertar(inscripcion.idActividad);
		}
		else if (inscripcion.tipo == TipoActividad::ESPECIALIZACION) {
			inscripcionesEspecialidades.push(inscripcion);
			idEspecialidades->insertar(inscripcion.idActividad);
		}
	}


#endif // COURSERACLONE_CONTROLLERS_INSCRIPCIONESCONTROLLER_HPP