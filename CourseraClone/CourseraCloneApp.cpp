// Cabeceras propias
#include "ExtendedFunctions.h"
#include "UI_Menu_LandingPage.h"
#include "UI_Ascii.h"
#include "Controladora.h"
#include "UI_Menu_State.h"
#include "Usuario.h"

// Librerias
#include "iostream"
#include "memory"

using namespace std;
using namespace System;

// maquetacion de funciones
void SecuenciaInicializacion();
void ManejarLogin(Controladora& controladora);
void ManejarRegistro(Controladora& controladora);
// ------------------------

void main() {
	SecuenciaInicializacion();
	
	// Crear el estado inicial
	unique_ptr<MenuState> currentState = make_unique<LandingPageState>();
	bool ejecutando = true;

	while (ejecutando) {
		// Renderizar el estado actual
		currentState->render();
	Controladora* controladora = new Controladora();

		// Manejar input
		if (_kbhit()) {
			int tecla = _getch();
			
			// Verificar si se presionó ESC
			if (tecla == 27) {
				ejecutando = false;
				continue;
			}

			// Manejar la tecla en el estado actual
			currentState->handleInput(tecla);

			// Verificar si hay un nuevo estado
			auto nextState = currentState->getNextState();
			if (nextState) {
				currentState = move(nextState);
			}
		}

		Sleep(50); // Pequeño retraso para no saturar la CPU
	}
}

void ManejarLogin(Controladora& controladora) {
	UI_Login();
	
	if (controladora.iniciarSesion()) {
		system("cls");
		controladora.mostrarDashboard();
	}
}

void ManejarRegistro(Controladora& controladora) {
	UI_Signup();
	string nombre, apellido, username, password;
	int tipoUsuario;

	// Aqu� ir�a la l�gica para obtener los datos del formulario
	// Por ahora usamos valores de prueba
	cout << "Tipo de usuario (1: Estudiante, 2: Organizaci�n): ";
	cin >> tipoUsuario;
	cout << "Nombre: ";
	cin >> nombre;
	cout << "Apellido: ";
	cin >> apellido;
	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;

	if (controladora.registrarUsuario(tipoUsuario, nombre, apellido, username, password)) {
		cout << "Registro exitoso!" << endl;
	} else {
		cout << "Error en el registro" << endl;
	}
}

void SecuenciaInicializacion() {
	ConfigurarConsola();
}