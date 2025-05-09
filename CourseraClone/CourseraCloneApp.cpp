// Cabeceras propias
#include "ExtendedFunctions.h"
#include "Controladora.h"

// maquetacion de funciones
void SecuenciaInicializacion();
// ------------------------

void main() {
	SecuenciaInicializacion();

	try 
	{
		Controladora app;
		app.run();
	} catch (const std::exception& e) 
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	cout << "Presione una tecla para salir...";
	_getch();
}

void SecuenciaInicializacion() 
{
	ConfigurarConsola();
}