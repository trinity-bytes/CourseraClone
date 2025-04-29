#include "iostream"
#include "ExtendedFunctions.h"
#include "UI_Ascii.h"

using namespace std;
using namespace System;

void main()
{
	ConfigurarConsola();

	system("cls");
	UI_LandingPage();
	system("pause");

	system("cls");
	UI_Login();
	system("pause");
}