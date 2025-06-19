// filepath: Headers/Entities/Usuario.hpp
// Clase que representa un usuario en el sistema, 
// incluyendo manejo de archivos binarios e índices para autenticación.

#ifndef COURSERACLONE_ENTITIES_USUARIO_HPP
#define COURSERACLONE_ENTITIES_USUARIO_HPP

// Headers de la libreria estandar
#include <iostream>  // Para std::cerr y std::endl
#include "../Controllers/FilesManager.hpp"

// Headers propios
#include "../Types/UsuarioTypes.hpp"

/// @brief Clase que representa un usuario en el sistema, con métodos para autenticación 
///        y manejo de archivos binarios.
/// @details Esta clase maneja la creación, almacenamiento y autenticación de usuarios, 
///          incluyendo la conversión entre estructuras binarias y objetos C++.
class Usuario
{
protected:
    int _id;
    TipoUsuario _tipoUsuario;
    std::string _nombreCompleto;
    std::string _username;
    std::string _contrasenaHash;
	std::string _fechaRegistro; // Fecha de registro del usuario

private:
    // Convierte un objeto Usuario a struct UsuarioBinario
    inline UsuarioBinario toUsuarioBinario();

    // Convierte un UsuarioBinario a Usuario
    inline Usuario fromUsuarioBinario(const UsuarioBinario& bin);

    // Convierte un objeto Usuario a UsuarioIndex
    inline UsuarioIndex toUsuarioIndex();

    // Convierte struct UsuarioIndex a string de nombre de usuario
    inline std::string getUsernameFromIndex(const UsuarioIndex& index);

    // Convierte correo a minuscula
    inline std::string Usuario::correoCorrecto(std::string _correo);

	// Hashea la contraseña usando un método seguro
    inline std::string hashContrasena(const std::string& contrasena);
public:
    inline Usuario();
    inline Usuario(
        int id,
        TipoUsuario tipoUsuario,
        const std::string& nombreCompleto,
        const std::string& username,
        const std::string& contrasenaHash
    );

    // Getters
    inline int getId();
    inline TipoUsuario getTipoUsuario();
    inline std::string getNombreCompleto();
    inline std::string getUsername();
    inline std::string getContrasenaHash();

    // Setters
    inline void setId(int id);
    inline void setTipoUsuario(TipoUsuario tipo);
    inline void setNombreCompleto(const std::string& nombre);
    inline void setUsername(const std::string& username);
    inline void setContrasena(std::string _contrasena);

    inline void reset();
    inline void guardar();

    inline void establecerDatosBase(Usuario otroUsuario);

    // Retorna un codigo de estado y, si es exitoso, carga los datos del usuario en usuarioLogueado
    inline LoginStatus login(Usuario& usuarioLogueado, TipoUsuario tipoUsuario, std::string passInput, int pos);

    inline int buscarIndexUsuario();

    inline bool actualizarUsuario(const std::string& _nuevoNombre, const std::string& _nuevoUsername, const std::string& _nuevaContrasena);
};

// IMPLEMENTACION DE CONSTCTORES Y DESTRUCTORES
// Constructor por default UwU
inline Usuario::Usuario() : _id(0),
                     _tipoUsuario(TipoUsuario::DEFAULT), 
                     _nombreCompleto(""), 
                     _username(""), 
                     _contrasenaHash("") 
{}

// Constructor principal 
inline Usuario::Usuario(
    int id,
    TipoUsuario tipoUsuario,
    const std::string& nombreCompleto,
    const std::string& username,
    const std::string& contrasenaHash
) : _id(id),
    _tipoUsuario(tipoUsuario),
    _nombreCompleto(nombreCompleto),
    _username(correoCorrecto(username)),
    _contrasenaHash(contrasenaHash) 
{}

// IMPLEMENTACION DE FUNCIONES PRIVADAS

// Convierte objeto Usuario a struct UsuarioBinario
inline UsuarioBinario Usuario::toUsuarioBinario() 
{
    return UsuarioBinario(
        _id,
        _tipoUsuario,
        _nombreCompleto,
        _username,
        _contrasenaHash
    );
}

// Convierte struct UsuarioBinario a objeto Usuario
// Necesita el ID y tipo de usuario, que no están en UsuarioBinario
inline Usuario Usuario::fromUsuarioBinario(const UsuarioBinario& binario) 
{
    return Usuario(
        binario.id,
        binario.tipoUsuario,
        std::string(binario.nombreCompleto),
        std::string(binario.nombreDeUsuario),
        std::string(binario.contrasenaHash)
    );
}

// Convierte objeto Usuario a struct UsuarioIndex
inline UsuarioIndex Usuario::toUsuarioIndex()
{
    return UsuarioIndex(_username, _id);
}

// Convierte struct UsuarioIndex a string de nombre de usuario
inline std::string Usuario::getUsernameFromIndex(const UsuarioIndex& index)
{
    // posible basura si el char[] no esta bien terminado.
    return std::string(index.nombreDeUsuario, strnlen(index.nombreDeUsuario, MAX_FIELD_LEN));
}

inline std::string Usuario::correoCorrecto(std::string _correo) {
    std::string res = "";
    for (char c : _correo) res += tolower(c);
    return res;
}

inline std::string Usuario::hashContrasena(const std::string& contrasena)
{
    std::string mockHash = "atalapastrukaGohGohGoh"; // Hash inicial con la palabra de seguridad xd
    mockHash += contrasena.substr(0, min((int)contrasena.length(), MAX_FIELD_LEN - (int)mockHash.length() - 1));
    return mockHash;
}

// IMPLEMENTACION DE FUNCIONES ESTATICAS PUBLICAS

// Getters
inline int Usuario::getId() { return _id; }
inline TipoUsuario Usuario::getTipoUsuario() { return _tipoUsuario; }
inline std::string Usuario::getNombreCompleto() { return _nombreCompleto; }
inline std::string Usuario::getUsername() { return _username; }
inline std::string Usuario::getContrasenaHash() { return _contrasenaHash; }

// Setters
inline void Usuario::setId(int id) { _id = id; }
inline void Usuario::setTipoUsuario(TipoUsuario tipo) { _tipoUsuario = tipo; }
inline void Usuario::setNombreCompleto(const std::string& nombre) { _nombreCompleto = nombre; }
inline void Usuario::setUsername(const std::string& username) { _username = username; }
inline void Usuario::setContrasena(std::string _contrasena) { _contrasenaHash = hashContrasena(_contrasena); }

inline void Usuario::reset()
{
    _id = -1;
    _tipoUsuario = TipoUsuario::DEFAULT;
    _nombreCompleto = "";
    _username = "";
    _contrasenaHash = "";
}

inline void Usuario::establecerDatosBase(Usuario otroUsuario)
{
    _tipoUsuario = otroUsuario.getTipoUsuario();
    _nombreCompleto = otroUsuario.getNombreCompleto();
    _username = otroUsuario.getUsername();
    _contrasenaHash = otroUsuario.getContrasenaHash();
}

inline void Usuario::guardar()
{
    // Todo: Implementar la lógica para guardar el usuario en el archivo correspondiente.
    // Usaremos las funciones de la clase FilesManager para manejar los archivos.
	FilesManager::getInstance().guardarUsuarioBinario(toUsuarioBinario(), _tipoUsuario);
    FilesManager::getInstance().guardarIndiceUsuario(toUsuarioIndex(), _tipoUsuario);
}

/// --- Método estático para manejar el login ---
inline LoginStatus Usuario::login(
    Usuario& usuarioLogueado,
    TipoUsuario tipoUsuario,
    std::string passInput,
    int pos
) {
	// ToDo: Implementar la lógica de autenticación.
	// Usaremos las funciones de la clase FilesManager para manejar los archivos.
	return LoginStatus::SUCCESS; // Retorna un código de estado de error por defecto
}

inline int Usuario::buscarIndexUsuario() {
	return FilesManager::getInstance().buscarIndexUsuario(_nombreCompleto, static_cast<int>(_tipoUsuario));
}

inline bool Usuario::actualizarUsuario(
    const std::string& _nuevoNombre,
    const std::string& _nuevoUsername,
    const std::string& _nuevaContrasena
) {
	// ToDo: Implementar la lógica para actualizar el usuario en el archivo correspondiente.
	// Usaremos las funciones de la clase FilesManager para manejar los archivos.
}

#endif // COURSERACLONE_ENTITIES_USUARIO_HPP