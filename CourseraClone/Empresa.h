#pragma once
#include "Usuario.h"
#include "Curso.h"
class Empresa: public Usuario
{
private:
	LinkedList<Actividad*> actividadesPropias;
	LinkedList<Especializacion*> especializaciones;
	LinkedList<Curso*> cursos;
public:
	void cargarDatos() { }

	Empresa(int _id, string nombreCompleto, string _nickname, string _contrasena): Usuario(_id, TipoUsuario::EMPRESA, nombreCompleto, _nickname, _contrasena) {
		cargarDatos();
		this->actividadesPropias = LinkedList<Actividad*>();
		cursos = LinkedList<Curso*>();
	}
	
	int crearCurso(Curso *nuevoCurso){
		cursos.agregarAlFinal(nuevoCurso);
	}

	int crearEspecializacion(Especializacion *_nuevaEspecializacion) {
		especializaciones.agregarAlFinal(_nuevaEspecializacion);
	}
	void verProfesores() {

	}
	void eliminarCursoEspecializacion() {

	}
    void anadirCursoEspecilizacion(Curso* curso) {
		Especializacion* especializacion = new Especializacion(); // Crear una nueva especialización
        if (curso == nullptr) {
            cout << "Error: El curso no existe." << endl;
            return;
        }

        // Solicitar datos para la nueva especialización
        int idEspecializacion = especializacion->getId(); // Generar un ID único
        string titulo = especializacion->getTitulo(); // Título por defecto o solicitado al usuario
        string descripcion = especializacion->getDescripcion(); // Descripción por defecto o solicitada
        string categoria = curso->getCategoria(); // Usar la categoría del curso como base
        int duracionEstimada = curso->getCantidadClases(); // Ejemplo: usar la cantidad de clases como duración estimada

        // Crear la nueva especialización
        Especializacion* nuevaEspecializacion = new Especializacion(
            idEspecializacion,
            this->getId(), // ID de la empresa
            this->getNombreCompleto(), // Nombre de la empresa
            titulo,
            0, // Cantidad inicial de alumnos
            descripcion,
            categoria,
            duracionEstimada
        );

        // Añadir el curso a la especialización
        nuevaEspecializacion->anadirCurso(curso);

        // Agregar la especialización a la lista de especializaciones de la empresa
        especializaciones.agregarAlFinal(nuevaEspecializacion);

        cout << "Especialización creada y curso añadido exitosamente." << endl;
    }
};
