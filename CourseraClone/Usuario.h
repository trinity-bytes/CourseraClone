#pragma once
#include <iostream>
using namespace std;

class Usuario{
protected:
	int id, tipoUsuario;
	string nickName, contrasena;
public:
	Usuario(int _id, int _tipoUsuario, string _nickName, string _contrasena) {
		id = _id;
		tipoUsuario = _tipoUsuario;
		nickName = _nickName;
		contrasena = _contrasena;
	}

	bool validarUsuario() {

	}
	bool validarContrasena() {

	}
	virtual void mostrarPerfil() {

	}

};
