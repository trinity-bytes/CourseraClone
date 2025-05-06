#include "iostream"
#include "Usuario.h"
#include "ExtendedFunctions.h"
#include "UI_Menu_LandingPage.h"
#include "Controladora.h"

using namespace std;
using namespace System;

// maquetacion de funciones
void SecuenciaInicializacion();

void main(){
	int opc;
	bool ejecutando = true;

	
	SecuenciaInicializacion();
	Controladora* controladora = new Controladora();

	do
	{
		controladora->cargarTodosDatos();
		opc = MostrarMenu_LandingPage();

		switch (opc)
		{
		case 1: // Iniciar Sesion
			system("cls");
			UI_Login();
			break;
		case 2: // Registrarse
			system("cls");
			UI_Signup();
			break;
		case 3: // Sobre Nosotros
			// ui about us
			break;
		case 0: // Salir
			ejecutando = false;
			break;
		default:
			break;
		}
		system("pause");
	} while (ejecutando);
}

void SecuenciaInicializacion(){
	ConfigurarConsola();
}