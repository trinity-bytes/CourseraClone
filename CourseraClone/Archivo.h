#pragma once
#include <iostream>
#include "fstream"
using namespace std;
template<typename T>
class Archivo{
private:
	T objeto;
	ifstream archivoLectura;
	ofstream archivoEscritura;
public:
	Archivo(){
		objeto = new T();
	}	

	void crearArchivoBinario(string ruta) {
		ofstream archivo(ruta, ios::binary);
		if (!archivo) {
			cout << "Error al crear el archivo" << endl;
			return;
		}
		for (int i = 0; i < 10; i++) {
			T reg;
			// leer nombres y contrasena 
			archivo.write(reinterpret_cast<char*>(&reg), sizeof(T));
		}
		archivo.close();
		cout << "Archivo creado con exito." << endl;
	}

	void crearArchivoTxt() {

	}


};
