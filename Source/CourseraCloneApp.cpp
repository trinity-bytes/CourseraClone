// Cabeceras propias
#include "../Headers/Utils/SystemUtils.h"
#include "../Headers/Controllers/Controladora.h"

// Headers de la libreria estandar
#include <iostream> // Para std::cout, std::cerr

// maquetacion de funciones
void SecuenciaInicializacion();
// ------------------------

// Aplicación monolítica - modo consola simple
int main()
{
	SecuenciaInicializacion();

	try
	{
		std::cout << "==================================" << std::endl;
		std::cout << "   Bienvenido a CourseraClone" << std::endl;
		std::cout << "==================================" << std::endl;
		
		Controladora app;
		app.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error en la aplicacion: " << e.what() << std::endl;
	}

	system("pause");
	return 0;
}

void SecuenciaInicializacion()
{
	ConfigurarConsola();
}
