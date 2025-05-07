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
		Especializacion* especializacion = new Especializacion(); // Crear una nueva especializaci�n
        if (curso == nullptr) {
            cout << "Error: El curso no existe." << endl;
            return;
        }

        // Solicitar datos para la nueva especializaci�n
        int idEspecializacion = especializacion->getId(); // Generar un ID �nico
        string titulo = especializacion->getTitulo(); // T�tulo por defecto o solicitado al usuario
        string descripcion = especializacion->getDescripcion(); // Descripci�n por defecto o solicitada
        string categoria = curso->getCategoria(); // Usar la categor�a del curso como base
        int duracionEstimada = curso->getCantidadClases(); // Ejemplo: usar la cantidad de clases como duraci�n estimada

        // Crear la nueva especializaci�n
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

        // A�adir el curso a la especializaci�n
        nuevaEspecializacion->anadirCurso(curso);

        // Agregar la especializaci�n a la lista de especializaciones de la empresa
        especializaciones.agregarAlFinal(nuevaEspecializacion);

        cout << "Especializaci�n creada y curso a�adido exitosamente." << endl;
    }
};
