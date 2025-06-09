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
	configurarConsola();
}
