// filepath: Source/CourseraCloneApp.cpp
// description: Aplicación monolítica de consola para CourseraCloneApp

// Headers de la libreria estandar
#include <iostream> // Para std::cout, std::cerr

// Cabeceras propias
#include "../Headers/Utils/SystemUtils.hpp"
#include "../Headers/Controllers/MainController.hpp"
#include "../Headers/Controllers/FilesManager.hpp"
#include "../Headers/Controllers/ContentManager.hpp"
#include "../Headers/Controllers/SessionManager.hpp"
#include "./Utils/GeneradorDatos.hpp"

// maquetación de funciones
void SecuenciaInicializacion();
// ------------------------

int main()
{
	SecuenciaInicializacion();

	try
	{
		FilesManager::getInstance();
		ContentManager::getInstance();
		SessionManager::getInstance();
	
		//GeneradorDatos generador;
		//generador.generarTodo();

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
