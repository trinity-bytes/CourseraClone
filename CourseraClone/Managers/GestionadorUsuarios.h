#pragma once
#include "../Usuario.h"
#include "../Estudiante.h"
#include "../Empresa.h"
#include "../LinkedList.h"
#include <fstream>
#include <string>

class GestionadorUsuarios 
{
private:
    LinkedList<Usuario*> usuarios;
public:
    GestionadorUsuarios() {}

    ~GestionadorUsuarios() 
    {
        for (auto usuario : usuarios) // Liberar memoria de usuarios
        {
            delete usuario;
        }
    }

    bool autenticarUsuario(const string& username, const string& password) {
        // Usar el método login de Usuario
        Usuario usuarioTemp;
        LoginStatus status = Usuario::login(usuarioTemp, TipoUsuario::ESTUDIANTE, username, password);
        
        if (status == LoginStatus::SUCCESS) {
            return true;
        }
        
        // Intentar como empresa si no es estudiante
        status = Usuario::login(usuarioTemp, TipoUsuario::EMPRESA, username, password);
        return status == LoginStatus::SUCCESS;
    }

    Usuario* obtenerUsuario(const string& username) 
    {
        for (auto usuario : usuarios) 
        {
            if (usuario->getUsername() == username) 
            {
                return usuario;
            }
        }
        return nullptr;
    }

    bool registrarUsuario(int tipoUsuario, const int& id, 
        const string& nombreCompleto, const string& username, 
        const string& password) {
        
        // Verificar si el usuario ya existe intentando hacer login
        Usuario usuarioTemp;
        if (Usuario::login(usuarioTemp, TipoUsuario::ESTUDIANTE, username, password) == LoginStatus::SUCCESS ||
            Usuario::login(usuarioTemp, TipoUsuario::EMPRESA, username, password) == LoginStatus::SUCCESS) {
            return false;
        }

        // Crear nuevo usuario
        Usuario* nuevoUsuario = new Usuario(
            id,
            static_cast<TipoUsuario>(tipoUsuario),
            nombreCompleto,
            username,
            Usuario::hashContrasena(password) // Usar el método de hash de Usuario
        );

        // Guardar el usuario usando su método guardar
        nuevoUsuario->guardar();
        
        usuarios.agregarAlFinal(nuevoUsuario);
        return true;
    }
}; 