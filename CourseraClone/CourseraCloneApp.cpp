// Cabeceras propias
#include "ExtendedFunctions.h"
//#include "UI_Menu_LandingPage.h"
#include "UI_Ascii.h"
#include "Controladora.h"
#include "UI_MenuLanding_State.h"

// Librerias
#include "iostream"
#include "memory"

using namespace std;
using namespace System;

// maquetacion de funciones
void SecuenciaInicializacion();
// ------------------------

void main() {
	SecuenciaInicializacion();
	
	// Crear la controladora y el estado inicial
	Controladora* controladora = new Controladora();
	unique_ptr<MenuState> currentState = make_unique<LandingPageState>(controladora);
	bool ejecutando = true;

	while (ejecutando) 
	{
		currentState->render(); // Renderizar el estado actual

		if (_kbhit()) // Manejar input
		{
			int tecla = _getch();
			
			if (tecla == 27) // Verificar si se presionó ESC
			{
				ejecutando = false;
				continue;
			}
						
			currentState->handleInput(tecla); // Manejar la tecla en el estado actual
						
			auto nextState = currentState->getNextState(); // Verificar si hay un nuevo estado
			if (nextState) 
			{
				currentState = move(nextState);
			}
		}

		Sleep(50); // Retraso para no saturar la CPU
	}
}

void SecuenciaInicializacion() 
{
	ConfigurarConsola();
}