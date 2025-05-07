#pragma once
#include "../Usuario.h"
#include "../Estudiante.h"
#include "../Empresa.h"
#include "../LinkedList.h"
#include <fstream>
#include <string>

class GestionadorUsuarios {
private:
    LinkedList<Usuario*> usuarios;
    const string RUTA_USUARIOS = "Resources/Data/usuarios.dat";

public:
    GestionadorUsuarios() {
        cargarUsuarios();
    }

    ~GestionadorUsuarios() {
        // Liberar memoria de usuarios
        for (auto usuario : usuarios) {
            delete usuario;
        }
    }

    bool autenticarUsuario(const string& username, const string& password) {
        for (auto usuario : usuarios) {
            if (usuario->getUsername() == username && usuario->getPassword() == password) {
                return true;
            }
        }
        return false;
    }

    Usuario* obtenerUsuario(const string& username) {
        for (auto usuario : usuarios) {
            if (usuario->getUsername() == username) {
                return usuario;
            }
        }
        return nullptr;
    }

    bool registrarUsuario(int tipoUsuario, const string& nombre, const string& apellido,
        const string& username, const string& password) {
        // Verificar si el usuario ya existe
        if (obtenerUsuario(username) != nullptr) {
            return false;
        }

        Usuario* nuevoUsuario;
        if (tipoUsuario == 1) {
            nuevoUsuario = new Estudiante(nombre, apellido);
        }
        else if (tipoUsuario == 2) {
            nuevoUsuario = new Empresa();
        }
        else {
            return false;
        }

        nuevoUsuario->setUsername(username);
        nuevoUsuario->setPassword(password);
        usuarios.agregarAlFinal(nuevoUsuario);

        // Guardar en archivo
        guardarUsuarios();
        return true;
    }

private:
    void cargarUsuarios() {
        ifstream archivo(RUTA_USUARIOS, ios::binary);
        if (!archivo.is_open()) return;

        UsuarioBinario usuarioBin;
        while (archivo.read(reinterpret_cast<char*>(&usuarioBin), sizeof(usuarioBin))) {
            Usuario* usuario;
            if (usuarioBin.tipoUsuario == 1) {
                usuario = new Estudiante(usuarioBin.nombre, usuarioBin.apellido);
            }
            else {
                usuario = new Empresa();
            }
            usuario->setUsername(usuarioBin.username);
            usuario->setPassword(usuarioBin.password);
            usuarios.agregarAlFinal(usuario);
        }
    }

    void guardarUsuarios() {
        ofstream archivo(RUTA_USUARIOS, ios::binary);
        if (!archivo.is_open()) return;

        for (auto usuario : usuarios) {
            UsuarioBinario usuarioBin;
            strcpy_s(usuarioBin.username, usuario->getUsername().c_str());
            strcpy_s(usuarioBin.password, usuario->getPassword().c_str());
            strcpy_s(usuarioBin.nombre, usuario->getNombre().c_str());
            strcpy_s(usuarioBin.apellido, usuario->getApellido().c_str());
            usuarioBin.tipoUsuario = usuario->getTipoUsuario();

            archivo.write(reinterpret_cast<char*>(&usuarioBin), sizeof(usuarioBin));
        }
    }
}; 