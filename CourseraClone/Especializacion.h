#pragma once
#include "Actividad.h"
#include "Curso.h"
#include "LinkedList.h"

class Especializacion : public Actividad {
private:
	LinkedList<Curso> cursos;
};