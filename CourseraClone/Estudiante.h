#pragma once
#include "Usuario.h"
#include"LinkedList.h"
#include"Stack.h"
#include"Queue.h"
#include"Inscripcion.h"
#include "GestionadorCursos.h"
#include "Boleta.h"
#include "Curso.h"
#include "algoritmosOrdenamiento.h"



class Estudiante :public Usuario
{
private:
	LinkedList<Boleta*> boletas;
	Stack<Inscripcion*> cursosEs;
	Stack<Inscripcion*> especializacionesEs;
	GestionadorCursos* gestorCursos;
public:

	Estudiante(int _id, string nombreCompleto,
		string _nickname, string _contrasena) : Usuario(_id, TipoUsuario::ESTUDIANTE, nombreCompleto,
			_nickname, _contrasena)
	{
		cursosEs = Stack<Inscripcion*>();
		especializacionesEs = Stack<Inscripcion*>();
		boletas = LinkedList<Boleta*>();
		cargarDatos();
	}

	Estudiante(int _id,
		const string& nombreCompleto,
		const string& _nickname,
		const string& _contrasena,
		GestionadorCursos* _gestor)
		: Usuario(_id, TipoUsuario::ESTUDIANTE, nombreCompleto, _nickname, _contrasena),
		gestorCursos(_gestor),
		boletas(),
		cursosEs(),
		especializacionesEs()
	{
		cargarDatos();
		// no cargues inscripciones aquí, lo harás desde Login::ejecutar
	}

	InscripcionBinaria leerInscripcionEn(int posicion, string rutaBinario) {
		fstream archivo(rutaBinario, ios::binary | ios::in);
		if (!archivo.is_open()) throw runtime_error("No se pudo abrir binario inscripciones");
		archivo.seekg(posicion * sizeof(InscripcionBinaria), ios::beg);

		InscripcionBinaria rec;
		archivo.read(reinterpret_cast<char*>(&rec), sizeof(rec));
		return rec;
	}

	vector<int> obtenerOffsetsInscripciones() {
		ifstream archivoIndice("Resources/Data/indices/inscripciones.dat", ios::binary);
		if (!archivoIndice.is_open())
			throw runtime_error("No se pudo abrir el índice de inscripciones");

		archivoIndice.seekg(0, ios::end);
		int cantidad = archivoIndice.tellg() / sizeof(InscripcionIndex);
		if (cantidad <= 0) return {};
		archivoIndice.seekg(0, ios::beg);

		auto pred = [&](int pos) {
			InscripcionIndex tmp;
			archivoIndice.seekg(pos * sizeof(tmp), ios::beg);
			archivoIndice.read(reinterpret_cast<char*>(&tmp), sizeof(tmp));
			archivoIndice.clear();
			return tmp.idUsuario >= this->getId();
			};
		int inicio = busquedaBinaria(0, cantidad - 1, pred);

		vector<int> offsets;
		for (int i = inicio; i < cantidad; ++i) {
			InscripcionIndex tmp;
			archivoIndice.seekg(i * sizeof(tmp), ios::beg);
			archivoIndice.read(reinterpret_cast<char*>(&tmp), sizeof(tmp));
			if (tmp.idUsuario != this->getId()) break;
			offsets.push_back(tmp.offset);
		}

		return offsets;
	}

	// En Estudiante.h, dentro de la clase Estudiante:
	void cargarInscripciones(
		const LinkedList<Curso*>& cursos,
		const LinkedList<Especializacion*>& listaEspecializaciones
	) {
		// 1) Lee todos los offsets del índice
		vector<int> offsets = obtenerOffsetsInscripciones();
		//throw runtime_error(to_string(offsets.size()));
		if (offsets.empty()) return;
		
		string rutaBin = "Resources/Data/inscripciones.dat";

		//throw runtime_error(to_string(offsets.size()));
		vector<int> offsetCursos, offsetEspecializaciones;
		for (int off : offsets) {
			// leerInscripcionEn usa off-1 internamente si es 1-based
			InscripcionBinaria bin = leerInscripcionEn(off, rutaBin);
			//throw runtime_error(to_string(bin.tipoActividad));
			//system("pause");
			if (bin.tipoActividad == 0)
				offsetCursos.push_back(off);
			else
				offsetEspecializaciones.push_back(off);
		}

		// 3) Ordena cada vector por idActividad
		// mergeSort espera rango [begin, end)
		mergeSort(offsetCursos, 0, int(offsetCursos.size()));
		shellSort(offsetEspecializaciones);

		// 4) Filtra las listas activas para quedarte sólo con las actividades en esos offsets
		LinkedList<Curso*> cursosFiltrados = cursos.filtrar<int>(
			offsetCursos,
			// igualdad: curso.id == bin.idActividad
			[&](Curso* c, const int& off) {
				return c->getId() == leerInscripcionEn(off, rutaBin).idActividad;
			},
			// orden: curso.id < bin.idActividad
			[&](Curso* c, const int& off) {
				return c->getId() < leerInscripcionEn(off, rutaBin).idActividad;
			}
		);

		LinkedList<Especializacion*> espeFiltradas = listaEspecializaciones.filtrar<int>(
			offsetEspecializaciones,
			[&](Especializacion* e, const int& off) {
				return e->getId() == leerInscripcionEn(off, rutaBin).idActividad;
			},
			[&](Especializacion* e, const int& off) {
				return e->getId() < leerInscripcionEn(off, rutaBin).idActividad;
			}
		);

		// 5) Finalmente, recorre otra vez los offsets y crea los Inscripcion*
		for (int off : offsetCursos) {
			InscripcionBinaria bin = leerInscripcionEn(off, rutaBin);
			// busca el Curso* correspondiente en cursosFiltrados
			Curso* act = nullptr;
			for (auto it = cursosFiltrados.begin(); it != cursosFiltrados.end(); ++it) {
				if ((*it)->getId() == bin.idActividad) {
					act = *it;
					break;
				}
			}
			if (!act) continue;
			Inscripcion* ins = new Inscripcion(bin, act);
			cursosEs.push(ins);
		}

		for (int off : offsetEspecializaciones) {
			InscripcionBinaria bin = leerInscripcionEn(off, rutaBin);
			Especializacion* act = nullptr;
			for (auto it = espeFiltradas.begin(); it != espeFiltradas.end(); ++it) {
				if ((*it)->getId() == bin.idActividad) {
					act = *it;
					break;
				}
			}
			if (!act) continue;
			Inscripcion* ins = new Inscripcion(bin, act);
			especializacionesEs.push(ins);
		}
		//throw runtime_error(to_string(cursosEs.getTamano()));
	}

	void cargarDatos()
	{
		// Cargar boletas del estudiante desde el archivo
		ifstream archivo("Resources/Data/boletas.dat", ios::binary);
		if (!archivo.is_open()) {
			cerr << "No se pudo abrir el archivo de boletas" << endl;
			return;
		}

		BoletaBinaria boletaBin;
		int cantidad = 0;
		while (archivo.read(reinterpret_cast<char*>(&boletaBin), sizeof(BoletaBinaria))) {
			// Solo cargar las boletas del estudiante actual
			if (boletaBin.idEstudiante == this->getId()) {
				Boleta* nuevaBoleta = new Boleta(
					cantidad,
					boletaBin.idEstudiante,
					boletaBin.idActividad,
					boletaBin.fecha,
					boletaBin.precio
				);
				boletas.agregarAlFinal(nuevaBoleta);

			}
			cantidad++;
		}
		archivo.close();
	}

	const LinkedList<Boleta*>& getBoletas() const {
		return boletas;
	}

	// Función auxiliar para obtener el curso asociado a una boleta
	Curso* obtenerCursoPorId(int idCurso) {
		return gestorCursos->obtenerCursoPorId(idCurso);
	}

	// Función auxiliar para obtener la especialización asociada a una boleta
	Especializacion* obtenerEspecializacionPorId(int idEspecializacion) {

		return gestorCursos->obtenerEspecializacionPorId(idEspecializacion);
	}

	void verBoletas() {
		// Mostrar boletas
		for (int i = 0; i < boletas.getTamano(); i++) {
			Boleta* boleta = boletas.get(i);
			if (boleta) {
				boleta->mostrar();
			}
			else {
				cout << "No tienes boletas." << endl;
			}
		}
	}

	void verCursosInscritos() {
		// Mostrar cursos inscritos
		for (int i = 0; i < cursosEs.getTamano(); i++) {
			Inscripcion* inscripcion = cursosEs.get(i);
			if (inscripcion) {
				inscripcion->mostrar();
			}
			else {
				cout << "No tienes cursos inscritos." << endl;
			}
		}
	}

	bool inscribirseACurso(Curso* curso) {
		if (!curso) {
			std::cerr << "Error: Curso inválido" << std::endl;
			return false;
		}

		// Verificar si ya está inscrito al curso
		for (int i = 0; i < cursosEs.getTamano(); i++) {
			Inscripcion* inscripcionExistente = cursosEs.get(i);
			if (inscripcionExistente && inscripcionExistente->getIdActividad() == curso->getId()) {
				std::cerr << "Error: Ya estás inscrito en este curso" << std::endl;
				return false;
			}

		}

		// Crear una nueva inscripción
		Inscripcion* nuevaInscripcion = new Inscripcion(this->getId(), curso);
		//cerr << this->getId();
		//system("pause>0");


		// throw runtime_error(to_string(this->getId()));

		// Guardar en archivo
		nuevaInscripcion->guardar();
		nuevaInscripcion->marcarComoPagada(boletas);

		// Agregar a la pila de cursos inscritos
		cursosEs.push(nuevaInscripcion);

		// Actualizar contador de alumnos del curso
		curso->aumentarAlumno(1);
		return true;
	}

	// Método sobrecargado para inscribirse a una especialización
	bool inscribirseAEspecializacion(Especializacion* especializacion) {
		if (!especializacion) {
			std::cerr << "Error: Especialización inválida" << std::endl;
			return false;
		}

		// Verificar si ya está inscrito a la especialización
		for (int i = 0; i < especializacionesEs.getTamano(); i++) {
			Inscripcion* inscripcionExistente = especializacionesEs.get(i);
			if (inscripcionExistente && inscripcionExistente->getIdActividad() == especializacion->getId()) {
				std::cerr << "Error: Ya estás inscrito en esta especialización" << std::endl;
				return false;
			}
		}

		// Crear una nueva inscripción
		Inscripcion* nuevaInscripcion = new Inscripcion(this->getId(), especializacion);

		// Guardar en archivo
		nuevaInscripcion->guardar();
		nuevaInscripcion->marcarComoPagada(boletas);

		// Agregar a la pila de especializaciones inscritas
		especializacionesEs.push(nuevaInscripcion);

		// Actualizar contador de alumnos de la especialización
		especializacion->aumentarAlumno(1);
		return true;
	}
};