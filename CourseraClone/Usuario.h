#pragma once
#include <iostream>
#include <fstream>
#include "algoritmosBusqueda.h"
using namespace std;

struct UsuarioBinario {
	char nombreDeUsuario[30];
	char contrasena[30];

	UsuarioBinario() {}
	UsuarioBinario(string _user, string _pass) {
		strncpy(nombreDeUsuario, _user.c_str(), sizeof(nombreDeUsuario));
		strncpy(contrasena, _pass.c_str(), sizeof(contrasena));
	}
};

struct UsuarioIndex {
	char nombreDeUsuario[30];
	int offset;

	UsuarioIndex() {}
	UsuarioIndex(string _user, int _offset) {
		strncpy(nombreDeUsuario, _user.c_str(), sizeof(nombreDeUsuario));
		offset = _offset;
	}
};

class Usuario{
protected:
	int id, tipoUsuario;
	string nombreCompleto, username, password;
	//char nombreDeUsuario[30];
	//char contrasena[30];

public:
	Usuario() {};
	Usuario(int _id, int _tipoUsuario, string nombreCompleto, string _nickname, string _contrasena) {
		this->id = _id;
		this->tipoUsuario = _tipoUsuario;
		this->nombreCompleto = nombreCompleto;
		this->username = _nickname;
		this->password = _contrasena;
	}

	void guardar() {
		string rutaArchivo = (tipoUsuario == 1)
			? "Resources/Data/usuarios_empresa.dat"
			: "Resources/Data/usuarios_estudiante.dat";
		ofstream archivo(rutaArchivo, ios::binary | ios::app);
		int offsetRegistro = 0;

		if (archivo.is_open()) {
			archivo.seekp(0, ios::end);
			offsetRegistro = archivo.tellp();

			UsuarioBinario nuevo(username, password);
			archivo.write(reinterpret_cast<char*>(&nuevo), sizeof(nuevo));
			archivo.close();
		}

		string archivoIndice = (tipoUsuario == 1)
			? "Resources/Data/indices/usuarios_empresa.dat"
			: "Resources/Data/indices/usuarios_estudiante.dat";

		fstream archivoOrden(archivoIndice, ios::binary | ios::in | ios::out);
		if (!archivoOrden.is_open()) {
			archivoOrden.open(archivoIndice, ios::binary | ios::out); 
			archivoOrden.close();
			archivoOrden.open(archivoIndice, ios::binary | ios::in | ios::out);
		}

		archivoOrden.seekg(0, ios::end);
		int cantidad = archivoOrden.tellg() / sizeof(UsuarioIndex);

		auto busqueda = [&](int pos) {
			UsuarioIndex temp;
			archivoOrden.seekg(pos * sizeof(UsuarioIndex), ios::beg);
			archivoOrden.read(reinterpret_cast<char*>(&temp), sizeof(UsuarioIndex));
			return strncmp(username.c_str(), temp.nombreDeUsuario, 30) >= 0; // compara los nombres
			};

		int pos = busquedaBinaria(0, cantidad - 1, busqueda);

		// Mover elementos para hacer espacio
		for (int i = cantidad - 1; i >= pos; --i) {
			UsuarioIndex temp;
			archivoOrden.seekg(i * sizeof(UsuarioIndex), ios::beg);
			archivoOrden.read(reinterpret_cast<char*>(&temp), sizeof(UsuarioIndex));
			archivoOrden.seekp((i + 1) * sizeof(UsuarioIndex), ios::beg);
			archivoOrden.write(reinterpret_cast<char*>(&temp), sizeof(UsuarioIndex));
		}

		UsuarioIndex nuevo(username, offsetRegistro);
		archivoOrden.seekp(pos * sizeof(UsuarioIndex), ios::beg);
		archivoOrden.write(reinterpret_cast<char*>(&nuevo), sizeof(UsuarioIndex));
		archivoOrden.close();
	}
	static bool login(Usuario& usuarioLogueado, int tipoUsuario) {
		string userInput, passInput;

		cout << "Username: ";
		cin >> userInput;
		cout << "Password: ";
		cin >> passInput;

		string archivoIndice = (tipoUsuario == 1)
			? "Resources/Data/indices/usuarios_empresa.dat"
			: "Resources/Data/indices/usuarios_estudiante.dat";

		ifstream archivoOrden(archivoIndice, ios::binary);
		if (archivoOrden.is_open()) {

			archivoOrden.seekg(0, ios::end);
			int cantidad = archivoOrden.tellg() / sizeof(UsuarioIndex);
			archivoOrden.seekg(0);

			auto busqueda = [&](int pos) {
				UsuarioIndex temp;
				archivoOrden.seekg(pos * sizeof(UsuarioIndex), ios::beg);
				archivoOrden.read(reinterpret_cast<char*>(&temp), sizeof(UsuarioIndex));
				return strncmp(userInput.c_str(), temp.nombreDeUsuario, 30) >= 0;
				};

			int pos = busquedaBinaria(0, cantidad - 1, busqueda);
			archivoOrden.seekg(pos * sizeof(UsuarioIndex), ios::beg);
			UsuarioIndex encontrado;
			archivoOrden.read(reinterpret_cast<char*>(&encontrado), sizeof(UsuarioIndex));
			archivoOrden.close();

			if (strncmp(encontrado.nombreDeUsuario, userInput.c_str(), 30) != 0) {
				return 1; // Usuario no encontrado
			}

			string rutaCompleta = (tipoUsuario == 1)
				? "Resources/Data/usuarios_empresa.dat"
				: "Resources/Data/usuarios_estudiante.dat";
			ifstream archivo(rutaCompleta, ios::binary);

			UsuarioBinario datos;
			archivo.seekg(encontrado.offset, ios::beg);
			archivo.read(reinterpret_cast<char*>(&datos), sizeof(UsuarioBinario));
			archivo.close();

			if (passInput == datos.contrasena) {
				usuarioLogueado = Usuario(cantidad + 1, tipoUsuario, datos.nombreDeUsuario, datos.contrasena);
				return 0; // Login logrado
			}
			else {
				return 2; // Contraseña incorrecta
			}
		}

	}

	bool validarUsuario(const string& input) {
		return input == username;
	}

	bool validarContrasena(const string& input) {
		return input == username;
	}

	
	virtual void mostrarPerfil() {
		cout << "ID: " << id << endl;
		cout << "Username: " << username << endl;
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

	// Getters
	int getId() { return id; }
	string getNombreCompleto() { return nombreCompleto; }
	int getTipoUsuario() { return tipoUsuario; }
	string getNickname() { return username; }
	string getContrasena() { return password; }
};
