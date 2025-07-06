#ifndef COURSERACLONE_CONTROLLERS_INSCRIPCIONESCONTROLLER_HPP
#define COURSERACLONE_CONTROLLERS_INSCRIPCIONESCONTROLLER_HPP

// Headers estándar

// Headers propios
#include "../DataStructures/ArbolAVL.hpp"
#include "../DataStructures/Stack.hpp"
#include "../Entities/Inscripcion.hpp"
#include "../Controllers/ContentManager.hpp"
#include "../DataStructures/algoritmosOrdenamiento.hpp"

class InscripcionesController{
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
	inline FileOperationResult completarActividad(TipoActividad tipo, int id);
	inline FileOperationResult completarEspecializacion(int idInscripciones, int idEspecializacion = -1);
	inline FileOperationResult pagarActividad(TipoActividad tipo, int id);
	inline FileOperationResult inscribirEspecializacion(int idEspecializacion);
	inline std::vector<std::pair<std::string, int>> getConteoCategoria(std::vector<std::string> categoriasInicio);
	inline bool verificarCurso(int idCurso);
	inline bool verificarEspecializacion(int idEspecializacion);
	inline void mostrarCursos();
	inline void reportarDatosInscripcion(bool& _yaInscrito, bool& _yaPagado, bool& _yaCompletado, TipoActividad tipo, int id);

	inline Inscripcion& getInscripcion(TipoActividad tipo, int id);

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

inline FileOperationResult InscripcionesController::completarEspecializacion(int idInscripcion, int idEspecializacion) {
	Inscripcion& inscripcionEspecializacion = inscripcionesEspecialidades.get(idInscripcion);

	 if (idEspecializacion != -1) {
		inscripcionEspecializacion = getInscripcion(TipoActividad::ESPECIALIZACION, idEspecializacion);
	 }
	

	if (inscripcionEspecializacion.getCompletado()) {
		logOperation("Completar especializacion", "Especializacion ya completada: " + std::to_string(idInscripcion));
		return FileOperationResult::SUCCESS;
	}
	
	RawEspecializacionData especializacionDatos = ContentManager::getInstance().obtenerEspecializacionDatos(inscripcionEspecializacion.getIdActividad());
	std::vector<int> idDeCursosEspecializacion = especializacionDatos.idsCursos;
	int tamano = idDeCursosEspecializacion.size();
	bool todosCompletados = true;
	for (int i = 0; i < tamano; i++) {
		Inscripcion& inscripcionCurso = getInscripcion(TipoActividad::CURSO, idDeCursosEspecializacion[i]);
		if (!inscripcionCurso.getCompletado()) {
			todosCompletados = false;
			break;
		}
	}

	if (todosCompletados) {
		inscripcionEspecializacion.completar();
		inscripcionEspecializacion.actualizar();
		ContentManager::getInstance().obtenerEspecializacion(idEspecializacion)->aumentarAlumnoCompletado();
	}
	else {
		logOperation("Completar especializacion",
			"Error: No se puede completar la especializacion " + std::to_string(idEspecializacion) +
			" porque no todos los cursos están completados para estudiante " + std::to_string(idEstudiante));
		return FileOperationResult::SUCCESS;
	}

	return FileOperationResult::SUCCESS;

}

inline FileOperationResult InscripcionesController::completarActividad(TipoActividad tipo, int id) {
	Inscripcion& actual = getInscripcion(tipo, id);
	if (!actual.getCompletado()) {
		
		if (tipo == TipoActividad::CURSO) {
			actual.completar();
			actual.actualizar();
			ContentManager::getInstance().obtenerCurso(id)->aumentarAlumnoCompletado();

			int tamano = inscripcionesEspecialidades.getTamano();
			for (int i = 0; i < tamano; i++) {
				completarEspecializacion(i);

			}

		} 
		else if (tipo == TipoActividad::ESPECIALIZACION) {
			completarEspecializacion(0, id);
		}
		



		logOperation("Completar actividad",
			"Éxito: Actividad " + std::to_string(id) +
			" para estudiante " + std::to_string(idEstudiante));
	}
	else {
		logOperation("Completar actiivdad",
			"Error: Actividad completada antes " + std::to_string(id) +
			" para estudiante " + std::to_string(idEstudiante));
	}

	
	return FileOperationResult::SUCCESS;
}

inline FileOperationResult InscripcionesController::pagarActividad(TipoActividad tipo, int id) {
	Inscripcion& actual = getInscripcion(tipo, id);
	if (!actual.getEstadoPago()) {
		actual.marcarComoPagada();
		actual.actualizar();


		if (tipo == TipoActividad::ESPECIALIZACION) {
			std::vector<int> idDeCursosEspecializacion = ContentManager::getInstance().obtenerEspecializacionDatos(id).idsCursos;
			int tamano = idDeCursosEspecializacion.size();
			for (int i = 0; i < tamano; i++) {
				Inscripcion& nueva = getInscripcion(TipoActividad::CURSO, idDeCursosEspecializacion[i]);
				nueva.marcarComoPagada();
				nueva.actualizar();
			}

		}

		logOperation("Pagar actividad actividad",
			"Éxito: Actividad " + std::to_string(id) +
			" para estudiante " + std::to_string(idEstudiante));
	}
	else {
		logOperation("Pagar actividadd",
			"Error: Actividad completada antes " + std::to_string(id) +
			" para estudiante " + std::to_string(idEstudiante));
	}


	return FileOperationResult::SUCCESS;
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
	ContentManager::getInstance().obtenerCurso(idCurso)->aumentarAlumno();

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

	std::vector<int> idDeCursosEspecializacion = ContentManager::getInstance().obtenerEspecializacionDatos(idEspecializacion).idsCursos;
	int tamano = idDeCursosEspecializacion.size();
	for (int i = 0; i < tamano; i++) {
		inscribirCurso(idDeCursosEspecializacion[i]);
	}

	// 2) Crea la nueva Inscripcion y la persiste en disco
	int idActual = FilesManager::getInstance().cantidadInscripciones();
	Inscripcion nueva(idEstudiante, idEspecializacion, idActual, TipoActividad::ESPECIALIZACION);
	nueva.guardar();
	inscripcionesEspecialidades.push(nueva);
	ContentManager::getInstance().obtenerEspecializacion(idEspecializacion)->aumentarAlumno();

	logOperation("Inscribir especializacion",
		"Éxito: especializacon " + std::to_string(idEspecializacion) +
		" para estudiante " + std::to_string(idEstudiante));
	return FileOperationResult::SUCCESS;
}

inline std::vector<std::pair<std::string, int>> InscripcionesController::getConteoCategoria(std::vector<std::string> categoriasInicio) {
	std::vector<std::pair<std::string, int>> conteo;
	HashTable<std::string, int> conteoCategorias;
	for (std::string c : categoriasInicio) {
		conteoCategorias.insert(c, 0);
	}

	int cantidadCursos = inscripcionesCursos.getTamano();
	for (int i = 0; i < cantidadCursos; i++) {
		Inscripcion& inscripcion = inscripcionesCursos.get(i);
		int idCurso = inscripcion.getIdActividad();
		CategoriaActividad categoria = ContentManager::getInstance().obtenerCursoDatos(idCurso).categoria;
		std::string textoCategoria = RawActividadData::categoriaToString(categoria);
		int total = 0;
		bool encontrado = conteoCategorias.find(textoCategoria, total);
		int todo = 1 + inscripcion.getEstadoPago() * 3 + inscripcion.getCompletado() * 5;
		if (encontrado) conteoCategorias.insert(textoCategoria, todo);
		else conteoCategorias.insert("OTROS", 1);
	}

	int cantidadEspecializaciones = inscripcionesEspecialidades.getTamano();
	for (int i = 0; i < cantidadEspecializaciones; i++) {
		Inscripcion& inscripcion = inscripcionesEspecialidades.get(i);
		int idEspecializacion = inscripcion.getIdActividad();
		CategoriaActividad categoria = ContentManager::getInstance().obtenerEspecializacionDatos(idEspecializacion).categoria;
		std::string textoCategoria = RawActividadData::categoriaToString(categoria);
		int total = 0;
		bool encontrado = conteoCategorias.find(textoCategoria, total);
		int todo = 1 + inscripcion.getEstadoPago() * 3 + inscripcion.getCompletado() * 5;
		if (encontrado) conteoCategorias.insert(textoCategoria, todo);
		else conteoCategorias.insert("OTROS", 1);
	}

	for (std::string c : categoriasInicio) {
		if (c == "OTROS" || c == "TODAS") continue;
		int total = 0;
		bool encontrado = conteoCategorias.find(c, total);
		if (encontrado) {
			conteo.push_back({ c, total });
		}
	}

	auto ordenar = [](std::pair<std::string, int> a, std::pair<std::string, int> b) {
		return a.second > b.second;
		};
	insertionSort(conteo, ordenar);

	return conteo;
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

inline void InscripcionesController::reportarDatosInscripcion(bool& _yaInscrito, bool& _yaPagado, bool& _yaCompletado, TipoActividad tipo, int id) {
	if (tipo == TipoActividad::CURSO) {
		_yaInscrito = verificarCurso(id);
	}
	else {
		_yaInscrito = verificarEspecializacion(id);
	}
	
	if (_yaInscrito) {
		Inscripcion& ins = getInscripcion(tipo, id);
		_yaPagado = ins.getEstadoPago();
		_yaCompletado = ins.getCompletado();
	}
	else {
		_yaPagado = false;
		_yaCompletado = false;
	}

	
}

inline Inscripcion& InscripcionesController::getInscripcion(TipoActividad tipo, int id) {
	auto igualarId = [](const Inscripcion& i) {
		return i.getId();
		};

	if (tipo == TipoActividad::CURSO) {
		Inscripcion& ins = inscripcionesCursos.buscarPorClave(id, igualarId);
		return ins;
	}
	else {
		Inscripcion& ins = inscripcionesEspecialidades.buscarPorClave(id, igualarId);
		return ins;
	}
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
    fileManager.logError(operation, "InscripcionesController", error);
}


inline void InscripcionesController::logOperation(const std::string& operation, const std::string& details) {
    // Implementación simple para logging de operaciones
    // En un proyecto más complejo esto iría a un archivo de log
	FilesManager& fileManager = FilesManager::getInstance();
	fileManager.logInfo(operation, "InscripcionesController");

}

#endif // COURSERACLONE_CONTROLLERS_INSCRIPCIONESCONTROLLER_HPP