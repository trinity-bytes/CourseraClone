#pragma once
#include <iostream>
#include <fstream>
using namespace std;

class Usuario{
protected:
	int id, tipoUsuario;
	char nombreDeUsuario[30];
	char contrasena[30];

public:
	Usuario() {};

	Usuario(int _id, int _tipoUsuario, string _userName, string _contrasena) {
		id = _id;
		tipoUsuario = _tipoUsuario;
		strncpy(nombreDeUsuario, _userName.c_str(), sizeof(nombreDeUsuario));
		strncpy(contrasena, _contrasena.c_str(), sizeof(contrasena));
	}

	bool validarUsuario(const string& input) {
		return input == nombreDeUsuario;
	}

	bool validarContrasena(const string& input) {
		return input == contrasena;
	}

	virtual void mostrarPerfil() {
		cout << "ID: " << id << endl;
		cout << "Username: " << nombreDeUsuario << endl;
		cout << "Tipo de Usuario: " << tipoUsuario << endl;
	}

	static bool registrar(const string& filename, const Usuario& usuario) {
		ofstream file(filename, ios::binary | ios::app);
		if (!file.is_open()) {
			cout << "No se pudo abrir el archivo." << endl;
			return false;
		}
		file.write(reinterpret_cast<const char*>(&usuario), sizeof(Usuario));
		file.close();
		cout << "Usuario registrado exitosamente!" << endl;
		return true;
	}

	static bool login(const string& filename, Usuario& usuarioLogueado) {
		string userInput, passInput;

		cout << "Username: ";
		cin >> userInput;
		cout << "Password: ";
		cin >> passInput;

		ifstream file(filename, ios::binary);
		if (!file.is_open()) {
			cout << "No se pudo abrir el archivo." << endl;
			return false;
		}

		Usuario temp;
		while (file.read(reinterpret_cast<char*>(&temp), sizeof(Usuario))) {
			if (temp.validarUsuario(userInput) && temp.validarContrasena(passInput)) {
				usuarioLogueado = temp; 
				file.close();
				cout << "Logeo exitoso!" << endl;
				return true;
			}
		}

		file.close();
		cout << "Usuario o contrasena invalido" << endl;
		return false;
	}



};
