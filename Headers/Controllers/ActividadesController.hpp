#ifndef COURSERACLONE_CONTROLLERS_ACTIVIDADESCONTROLLER_HPP
#define COURSERACLONE_CONTROLLERS_ACTIVIDADESCONTROLLER_HPP

#include "../DataStructures/LinkedList.hpp"
#include "../Controllers/ContentManager.hpp"
#include "../DataStructures/algoritmosOrdenamiento.hpp"
#include "../Utils/DateTime.hpp"

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
	inline std::vector<RawComprobanteData> boletasEmpresa();
	inline std::vector<std::pair<std::string, double>> reportarIngresosTrimestrales(std::vector<RawComprobanteData>& comprobantes, double& total, int maximo = 5);
	inline void reportarEstadisticas(std::vector<std::pair<std::string, double>>& trimestres, double& total, int maximo = 5);
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

inline std::vector<RawComprobanteData> ActividadesController::boletasEmpresa() {
	vector<int> idTodosCursos, idTodosEspecialidades;
	idTodosCursos = idCursos.extraerTodo();
	idTodosEspecialidades = idEspecializaciones.extraerTodo();


	ArbolAVL<int> idCursosUnicos(idTodosCursos), idEspecialidadesUnicas(idTodosEspecialidades);
	std::vector<RawComprobanteData> datos = FilesManager::getInstance().leerDatosComprobantes(),
		res;

	auto filtrarRec = [&](auto funcion, int idx, const ArbolAVL<int>& arbol, TipoActividad tipoAct) {
			if (idx >= datos.size())
				return;

			const auto& b = datos[idx];
		
			if (b.tipoActividad == tipoAct && arbol.Buscar(b.idActividad)) {
				res.push_back(b);
			}
			// Avanzamos al siguiente índice
			funcion(funcion, idx + 1, arbol, tipoAct);
		};

	// 5) Aplicamos la misma lambda a cursos y a especializaciones
	filtrarRec(filtrarRec, 0, idCursosUnicos, TipoActividad::CURSO);
	filtrarRec(filtrarRec, 0, idEspecialidadesUnicas, TipoActividad::ESPECIALIZACION);
	
	return res;
}

inline std::vector<std::pair<std::string, double>> ActividadesController::reportarIngresosTrimestrales(std::vector<RawComprobanteData>& comprobantes, double& total, int maximo) {
	std::vector<std::pair<std::string, double>> resultado;

	
	HashTable<std::string, double> dineroTrimestres;
	for (RawComprobanteData comprobante : comprobantes) {
		std::string fechaTrimestre = DateTime::toTrimestreString(comprobante.fechaEmision);
		double costo = 0;
		bool encontrado = dineroTrimestres.find(fechaTrimestre, costo);
		if (encontrado) dineroTrimestres.add(fechaTrimestre, comprobante.montoPagado);
		else dineroTrimestres.insert(fechaTrimestre, comprobante.montoPagado);
		total += comprobante.montoPagado;
	}

	
	std::vector<std::string> ultimosQ = DateTime::obtenerUltimosTrimestres(5);
	for (std::string q : ultimosQ) {
		double costo = 0.0;
		bool encontrado = dineroTrimestres.find(q, costo);
		if (!encontrado) dineroTrimestres.insert(q, 0);
		resultado.push_back({ q,costo });
	}


	auto ordenarQ = [](pair<std::string, double> a, pair<std::string, double> b) {
		return a.second < b.second;
		};

	bubbleSort(resultado, ordenarQ);
	return resultado;
}

inline void ActividadesController::reportarEstadisticas(std::vector<std::pair<std::string, double>>& trimestres, double& total, int maximo) {
	std::vector<RawComprobanteData> boletas = boletasEmpresa();
	trimestres.clear();
	total = 0.0;
	trimestres = reportarIngresosTrimestrales(boletas, total, maximo);
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