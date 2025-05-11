#pragma once
#include "Usuario.h"
#include"LinkedList.h"
#include"Stack.h"
#include"Queue.h"
#include"Inscripcion.h"
#include "Boleta.h"
#include "Curso.h"
#include "algoritmosOrdenamiento.h"

class Estudiante :public Usuario
{
private:
	LinkedList<Boleta*> boletas;
	Stack<Inscripcion*> cursosEs;
	Stack<Inscripcion*> especializacionesEs;
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

	InscripcionBinaria leerInscripcionEn(int posicion, string& rutaBinario) {
		fstream archivo(rutaBinario, ios::binary);
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

	/*
	void cargarInscripciones(LinkedList<Curso*>& cursos, LinkedList<Especializacion*>& listaEspecializaciones) {
		fstream indiceArchivo("Resources/Data/indices/inscripciones.dat", ios::binary | ios::in);
		if (!indiceArchivo.is_open()) return;

		vector<int> filas = obtenerOffsetsInscripciones();
		if (filas.empty()) return;

		// aqui
		string rutaBin = "Resources/Data/inscripciones.dat";
		vector<int> cursosOff, especializacionesOff;

		// 3) Para cada offset, leo el registro binario y lo clasifico
		for (int off : filas) {
			// leerInscripcionEn espera posición 0-based: por eso off - 1
			InscripcionBinaria bin = leerInscripcionEn(off, rutaBin);

			if (bin.tipoActividad == 1) {
				cursosOff.push_back(bin.idActividad);
			}
			else {
				especializacionesOff.push_back(bin.idActividad);
			}
		}

		indiceArchivo.close();

		mergeSort(cursosOff, 0, int(cursosOff.size()));
		shellSort(especializacionesOff);



		LinkedList<Curso*> cursosFiltrados = cursos.filtrar<int>(
			cursosOff, [](Curso* c, const int& id) { return c->getId() == id; }, [](Curso* c, const int& id) { return c->getId() < id; }
		);


		LinkedList<Especializacion*> cursosFiltrados = listaEspecializaciones.filtrar<int>(
			cursosOff, [](Especializacion* c, const int& id) { return c->getId() == id; }, [](Especializacion* c, const int& id) { return c->getId() < id; }
		);

		//cursosEs.cargarDesdeLista(cursosFiltrados);

		
		
	}
	*/

	// En Estudiante.h, dentro de la clase Estudiante:
	void cargarInscripciones(
		const LinkedList<Curso*>& cursos,
		const LinkedList<Especializacion*>& listaEspecializaciones
	) {
		// 1) Lee todos los offsets del índice
		vector<int> offsets = obtenerOffsetsInscripciones();
		if (offsets.empty()) return;

		string rutaBin = "Resources/Data/inscripciones.dat";

		// 2) Separa offsets según tipoActividad
		vector<int> offsetCursos, offsetEspecializaciones;
		for (int off : offsets) {
			// leerInscripcionEn usa off-1 internamente si es 1-based
			InscripcionBinaria bin = leerInscripcionEn(off, rutaBin);
			if (bin.tipoActividad == 1)
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
	}


	void cargarDatos() {
		// cargar boletas
	}

	void verBoletas() {
		//todas las boletas que el estudiante tiene
		/*
		ifstream file("boletas.txt");
		if (!file.is_open()) {
			cout << "No se pudo abrir el archivo." << endl;
			return;
		}
		
		while (file.read(reinterpret_cast<char*>(&boleta), sizeof(Boleta))) {
			boleta->mostrar();
		}
		*/
	}

	void verCursosInscritos() {
		ifstream file("inscripciones.txt");
		/*
		if (!file.is_open()) {
			cout << "No se pudo abrir el archivo." << endl;
			return;
		}
		while (file.read(reinterpret_cast<char*>(&inscripcion), sizeof(Inscripcion))) {
			if (inscripcion->getIdEstudiante() == id) {
				inscripcion->mostrar();
			}
			else {
				cout << "No tienes cursos inscritos." << endl;
			}
		}
		file.close();
		*/
	}

	int incribirseAcurso(Actividad* actividadNueva) {

		Inscripcion* nuevaInscripcion = new Inscripcion(id, actividadNueva);

		// Guarda en archivo binario
		nuevaInscripcion->guardar();

		// 3. Agregar a la lista del estudiante
		if (actividadNueva->getTipo() == 1) {
			cursosEs.push(nuevaInscripcion);
		}
		else {
			especializacionesEs.push(nuevaInscripcion);
		}

		//actividadesInscritas.push(nuevaInscripcion);

		//cout << "Inscripción completada para la actividad: " << actividadNueva.getTitulo() << '\n';
		return 1; 

	}

};
