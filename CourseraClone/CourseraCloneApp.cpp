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
	} catch (const 
		exception& e) 
	{
		cerr << "Error: " << e.what() << endl;
	}

	system("pause");
}

void SecuenciaInicializacion() 
{
	ConfigurarConsola();
}