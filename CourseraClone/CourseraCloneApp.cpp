// Cabeceras propias
#include "ExtendedFunctions.h"
#include "Controladora.h"

// Librerias
#include "iostream"
#include "conio.h" // Para _kbhit() y _getch()
#include "windows.h" // Para Sleep()

using namespace std;

// maquetacion de funciones
void SecuenciaInicializacion();
// ------------------------

void main() {
	SecuenciaInicializacion();
	
	// Creamos la controladora
	Controladora* controladora = new Controladora();
	bool ejecutando = true;

	while (ejecutando) 
	{
		// Obtenemos el estado actual UwU
		MenuState* estadoActual = controladora->getEstadoActual();
		
		// Renderizamos el estado actual
		estadoActual->render();

		if (_kbhit()) {
			int tecla = _getch();
			
			// Primero dejamos que el estado actual maneje la tecla
			estadoActual->handleInput(tecla);

			// Solo cerramos si es ESC y estamos en el estado inicial
			if (tecla == 27 && dynamic_cast<LandingPageState*>(estadoActual)) {
				ejecutando = false;
				continue;
			}
		}

		Sleep(50); // Retraso para no saturar la CPU
	}

	delete controladora;
}

void SecuenciaInicializacion() 
{
	ConfigurarConsola();
}