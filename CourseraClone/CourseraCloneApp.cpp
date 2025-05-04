#include "iostream"
#include "ExtendedFunctions.h"
#include "UI_Menu_LandingPage.h"

using namespace std;
using namespace System;

// maquetacion de funciones
void SecuenciaInicializacion();

void main()
{
	short opc;

	SecuenciaInicializacion();
	system("cls");

	opc = MostrarMenu_LandingPage();

	switch (opc)
	{
	case 1:
		cout << "Iniciar Sesion" << endl;
		break;
	default:
		break;
	}
	system("pause");
}

void SecuenciaInicializacion()
{
	ConfigurarConsola();
}