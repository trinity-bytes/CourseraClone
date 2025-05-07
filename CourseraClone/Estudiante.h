#pragma once
#include "Usuario.h"
#include"LinkedList.h"
#include"Stack.h"
#include"Queue.h"
#include"Inscripcion.h"
#include "Boleta.h"
#include "Curso.h"

class Estudiante :public Usuario
{
private:
	LinkedList<Boleta*> boletas;
	LinkedList<Inscripcion*> inscripciones;
	Stack<Inscripcion*> actividadesInscritas;
	Queue<Inscripcion*> actividadesRecientesCompletadas;
public:
	
	Estudiante(int _id, string nombreCompleto, 
		string _nickname, string _contrasena) : Usuario(_id, 1, nombreCompleto,
												_nickname, _contrasena) 
	{
		inscripciones = LinkedList<Inscripcion*>();
		actividadesInscritas = Stack<Inscripcion*>();
		actividadesRecientesCompletadas = Queue<Inscripcion*>();
		boletas = LinkedList<Boleta*>();
		cargarDatos();
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

	int incribirseAcurso(Actividad actividadNueva) {
		Inscripcion* nuevaInscripcion = new Inscripcion(10, actividadNueva);

		// Guarda en archivo binario
		nuevaInscripcion->guardar();

		// 3. Agregar a la lista del estudiante
		inscripciones.agregarAlFinal(nuevaInscripcion); 

		//actividadesInscritas.push(nuevaInscripcion);

		cout << "Inscripción completada para la actividad: " << actividadNueva.getTitulo() << '\n';
		return 1; 

	}

};
