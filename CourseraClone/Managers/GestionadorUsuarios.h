#pragma once
#include "../Usuario.h"
#include "../Estudiante.h"
#include "../Empresa.h"
#include "../LinkedList.h"
#include <fstream>
#include <string>
#include <stdexcept>

class GestionadorUsuarios 
{
private:
    LinkedList<Usuario*> usuarios;

public:
    GestionadorUsuarios() {}

    ~GestionadorUsuarios() 
    {
        for (auto usuario : usuarios) {
            delete usuario;
        }
    }

    bool autenticarUsuario(const std::string& username, const std::string& password) {
        try {
            // Primero intentar como estudiante
            Usuario usuarioTemp;
            LoginStatus status = Usuario::login(usuarioTemp, TipoUsuario::ESTUDIANTE, username, password);
            
            if (status == LoginStatus::SUCCESS) {
                // Crear una copia del usuario autenticado
                Usuario* usuarioAutenticado = new Usuario(usuarioTemp);
                usuarios.agregarAlFinal(usuarioAutenticado);
                return true;
            }
            
            // Si no es estudiante, intentar como empresa
            status = Usuario::login(usuarioTemp, TipoUsuario::EMPRESA, username, password);
            if (status == LoginStatus::SUCCESS) {
                // Crear una copia del usuario autenticado
                Usuario* usuarioAutenticado = new Usuario(usuarioTemp);
                usuarios.agregarAlFinal(usuarioAutenticado);
                return true;
            }

            return false;
        } catch (const std::exception& e) {
            throw std::runtime_error(std::string("Error en autenticación: ") + e.what());
        }
    }

    bool registrarUsuario(const std::string& nombre, const std::string& email, 
                         const std::string& password, const std::string& tipo) {
        // Aquí deberías implementar la lógica de registro, por ejemplo, guardar en archivo o base de datos
        // Por ahora, solo retorna false para evitar el error de método inexistente
        return false;
    }
}; 