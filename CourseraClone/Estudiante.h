#pragma once
#include "Usuario.h"
#include"LinkedList.h"
#include"Stack.h"
#include"Queue.h"
#include"Inscripcion.h"
#include "Boleta.h"
#include "Curso.h"

class Estudiante :public Usuario{
private:
	string nombre, apellido, _username;
	Boleta* boleta;
	Curso* curso;
	Actividad* actividad;
	Inscripcion* inscripcion;
	LinkedList<Inscripcion> inscripciones;
	Stack<Inscripcion> actividadesInscritas;
	Queue<Inscripcion> actividadesRecientesCompletadas;
public:
	
	Estudiante(string _nombre, string _apellido): Usuario(id, tipoUsuario,_username, contrasena) {
		nombre = _nombre;
		apellido = _apellido;
	}

	void verBoletas() {
		//todas las boletas que el estudiante tiene
		ifstream file("boletas.txt");
		if (!file.is_open()) {
			cout << "No se pudo abrir el archivo." << endl;
			return;
		}
		while (file.read(reinterpret_cast<char*>(&boleta), sizeof(Boleta))) {
			boleta->mostrar();
		}
	}

	void verCursosInscritos() {
		ifstream file("inscripciones.txt");
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
	}

	int incribirseAcurso(Actividad actividad) {
		Inscripcion nuevaInscripcion(inscripcion->getId(), actividad);

		// Guarda en archivo binario
		nuevaInscripcion.guardar();

		// 3. Agregar a la lista del estudiante
		inscripciones.agregarAlFinal(nuevaInscripcion); 

		//actividadesInscritas.push(nuevaInscripcion);

		cout << "Inscripción completada para la actividad: " << curso->getTitulo() << endl;
		return 1; 

	}

};
