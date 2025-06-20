// filepath: Source/CourseraCloneApp.cpp
// description: Aplicación monolítica de consola para CourseraCloneApp

// Headers de la libreria estandar
#include <iostream> // Para std::cout, std::cerr

// Cabeceras propias
#include "../Headers/Utils/SystemUtils.hpp"
#include "../Headers/Controllers/MainController.hpp"
#include "../Headers/Controllers/FilesManager.hpp"
#include "../Headers/Controllers/ContentManager.hpp"

// maquetación de funciones
void SecuenciaInicializacion();
// ------------------------

int main()
{
	SecuenciaInicializacion();

	try
	{
		ContentManager::getInstance().inicializarSistema();
		FilesManager::getInstance().inicializarSistemaArchivos();

		MainController app;
		app.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "ERROR en la aplicacion: " << e.what() << std::endl;
		system("pause");
		return 1;
	}

	return 0;
}

void SecuenciaInicializacion()
{
	inicializarSistema();
}
