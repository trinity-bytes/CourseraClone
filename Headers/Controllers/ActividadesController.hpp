#ifndef COURSERACLONE_CONTROLLERS_ACTIVIDADESCONTROLLER_HPP
#define COURSERACLONE_CONTROLLERS_ACTIVIDADESCONTROLLER_HPP

#include "../DataStructures/LinkedList.hpp"
#include "../Controllers/ContentManager.hpp"
#include "../DataStructures/algoritmosOrdenamiento.hpp"

class ActividadesController {
private:
	LinkedList<int> idCursos;
	LinkedList<int> idEspecializaciones;
	int idOrganizacion;
	int totalInscritos;


	void logOperation(const std::string& operation, const std::string& details);
	void logError(const std::string& operation, const std::string& error);

public:
	// Constructor por defecto
	inline ActividadesController();
	// Constructor con id del alumno para cargar datos
	inline ActividadesController(int _idOrganizacion);

	inline std::vector<ElementoMenu> getElementosDashboard(TipoActividad _tipo);

	inline int calcularCantidad();
	inline void reportarDatosMostrarActividad(std::string& _cantidadRecaudada, std::string& _cantidadAlumnos, std::string& _porcentajeCompletado, TipoActividad _tipo, int id);

	inline int getCantidadCursos();
	inline int getCantidadEspecializaciones();
	inline int getCantidadInscritos();
	
	inline std::vector<std::pair<std::string, int>> getOrdenadoInscripciones(int maximoDatos);

};

// Constructores
inline ActividadesController::ActividadesController()
{
	idCursos = LinkedList<int>();
	idEspecializaciones = LinkedList<int>();
	idOrganizacion = -1;
}


inline ActividadesController::ActividadesController(int _idOrganizacion) {
	// Inicializar estructuras de datos
	idOrganizacion = _idOrganizacion;
	ContentManager& cm = ContentManager::getInstance();

	auto comparador = [](Actividad& c, int llave) {
		return c.getIdEmpresa() == llave;
		};
	auto convertidor = [](Actividad& c) {
		return c.getId();
		};

	cm.getCursos().filtrarTransformar<int, decltype(comparador), decltype(convertidor), int>(idOrganizacion, comparador, convertidor, idCursos);
	cm.getEspecializaciones().filtrarTransformar<int, decltype(comparador), decltype(convertidor), int>(idOrganizacion, comparador, convertidor, idEspecializaciones);
	totalInscritos = calcularCantidad();
}

inline int ActividadesController::calcularCantidad() {
	int total = 0;

	for (auto it = idCursos.begin(); it != idCursos.end(); it++) {
		Curso* curso = ContentManager::getInstance().obtenerCurso(*it);
		if (curso != nullptr) {
			int adicionar = curso->getCantidad();
			total += adicionar;
		}
	}

	for (auto it = idEspecializaciones.begin(); it != idEspecializaciones.end(); it++) {
		Especializacion* esp = ContentManager::getInstance().obtenerEspecializacion(*it);
		if (esp != nullptr) {
			int adicionar = esp->getCantidad();
			total += adicionar;
		}
	}

	return total;
}

inline void ActividadesController::reportarDatosMostrarActividad(std::string& _cantidadRecaudada, std::string& _cantidadAlumnos, std::string& _porcentajeCompletado, TipoActividad _tipo, int id) {
	int cantidad = 0;
	double ingreso = 0.0, porcentaje = 0.0;

	auto textoDouble = [](double valor) {
		auto decimalEnteroMuestra = [](double numero) {
			int nuevo = numero * 100;
			int resultado = nuevo % 100;
			return resultado;
			};

		int parteEntera = static_cast<int> (valor);
		int parteDecimal = decimalEnteroMuestra(valor);
		return std::to_string(parteEntera) + "." + std::to_string(parteDecimal);

		};

	if (_tipo == TipoActividad::CURSO) {
		Curso* curso = ContentManager::getInstance().obtenerCurso(id);
		if (curso != nullptr) {
			cantidad = curso->getCantidad();
			ingreso = curso->getMontoRecaudado();
			porcentaje = curso->getProgresoTotal();
		}
	}
	else {
		Especializacion* especializacion = ContentManager::getInstance().obtenerEspecializacion(id);
		if (especializacion != nullptr) {
			cantidad = especializacion->getCantidad();
			ingreso = especializacion->getMontoRecaudado();
			porcentaje = especializacion->getProgresoTotal();
		}
	}

	_cantidadRecaudada = "S/" + textoDouble(ingreso);
	_cantidadAlumnos = std::to_string(cantidad);
	_porcentajeCompletado = textoDouble(porcentaje) + "%";
}

inline std::vector<ElementoMenu> ActividadesController::getElementosDashboard(TipoActividad _tipo) {
	std::vector<ElementoMenu> resultado;

	
	if (_tipo == TipoActividad::CURSO) {
		for (int i = 0; i < 3 && i < idCursos.getTamano(); i++) {
			int id = idCursos.getElemento(i);
			std::cout << id << " ";
			
			ElementoMenu nuevo = ContentManager::getInstance().obtenerCurso(id)->obtenerDatosCrudosMenu();
			resultado.push_back(nuevo);
		}
	}
	else {
		for (int i = 0; i < 3 && i < idEspecializaciones.getTamano(); i++) {
			int id = idEspecializaciones.getElemento(i);
			ElementoMenu nuevo = ContentManager::getInstance().obtenerEspecializacion(id)->obtenerDatosCrudosMenu();
			resultado.push_back(nuevo);
		}
	}
	

	return resultado;
}

inline int ActividadesController::getCantidadCursos() {
	return idCursos.getTamano();
}

inline int ActividadesController::getCantidadEspecializaciones() {
	return idEspecializaciones.getTamano();
}

inline int ActividadesController::getCantidadInscritos() {
	return totalInscritos;
}

inline std::vector<std::pair<std::string, int>> ActividadesController::getOrdenadoInscripciones(int maximoDatos) {
	std::vector < std::pair < std::string, int > > informacion;

	for (auto it = idCursos.begin(); it != idCursos.end(); it++) {
		Curso* curso = ContentManager::getInstance().obtenerCurso(*it);
		if (curso != nullptr) {
			std::string tituloActividad = curso->getTitulo();
			int cantidad = curso->getCantidad();
			informacion.push_back({ tituloActividad, cantidad });
		}
	}
	for (auto it = idEspecializaciones.begin(); it != idEspecializaciones.end(); it++) {
		Especializacion* esp = ContentManager::getInstance().obtenerEspecializacion(*it);
		if (esp != nullptr) {
			std::string tituloActividad = esp->getTitulo();
			int cantidad = esp->getCantidad();
			informacion.push_back({ tituloActividad, cantidad });
		}
	}

	auto comparador = [](std::pair < std::string, int > a, std::pair < std::string, int > b) {
		return a.second > b.second;
		};
	int tamano = informacion.size();
	mergeSort(informacion, 0, tamano - 1, comparador);

	
	int minimo = (tamano > 5) ? 5 : tamano;
	std::vector < std::pair < std::string, int > > resultado;
	for (int i = 0; i < minimo; i++) {
		resultado.push_back(informacion[i]);
	}

	return resultado;
}

// ========== M�TODOS PRIVADOS - LOGGING ==========
inline void ActividadesController::logError(const std::string& operation, const std::string& error) {
	// Implementaci�n simple para logging de errores
	FilesManager& fileManager = FilesManager::getInstance();
	fileManager.logError(operation, "ActividadesController", error);
}


inline void ActividadesController::logOperation(const std::string& operation, const std::string& details) {
	// Implementaci�n simple para logging de operaciones
	// En un proyecto m�s complejo esto ir�a a un archivo de log
	FilesManager& fileManager = FilesManager::getInstance();
	fileManager.logInfo(operation, "ActividadesController");

}

#endif // COURSERACLONE_CONTROLLERS_ACTIVIDADESCONTROLLER_HPP