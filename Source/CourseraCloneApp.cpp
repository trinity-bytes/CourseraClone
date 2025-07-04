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
#include "../Headers/Utils/QR/QRDemo.hpp"

// Declaración de función externa para test de capacidad
extern int qrCapacityMain();

// maquetación de funciones
void SecuenciaInicializacion();
// ------------------------

int main()
{
	SecuenciaInicializacion();

	// Demo rápido del generador QR
	std::cout << "¿Desea ejecutar el demo del generador QR? (s/n): ";
	char response;
	std::cin >> response;
	
	if (response == 's' || response == 'S') {
		std::cout << "\n=== DEMO QR COURSERA ===\n";
		CourseraClone::QR::QRDemo::quickDemo();
		std::cout << "\nPresione Enter para continuar al sistema principal...";
		std::cin.ignore();
		std::cin.get();
	}

	// Test de capacidad de datos QR
	std::cout << "\n¿Desea ejecutar el análisis de capacidad de datos QR? (s/n): ";
	std::cin >> response;
	
	if (response == 's' || response == 'S') {
		qrCapacityMain();
		std::cout << "\nPresione Enter para continuar al sistema principal...";
		std::cin.ignore();
		std::cin.get();
	}

	try
	{
		FilesManager::getInstance();
		ContentManager::getInstance();
		SessionManager::getInstance();

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
