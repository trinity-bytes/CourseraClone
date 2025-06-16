#ifndef COURSERACLONE_PERSISTENCE_USUARIOTYPES_HPP
#define COURSERACLONE_PERSISTENCE_USUARIOTYPES_HPP

// Includes del sistema
#include <string>  // Para std::string
#include <cstring> // Para std::memset y std::strncpy

// Maxima longitud para campos de texto en binarios
static constexpr int MAX_FIELD_LEN = 60;

// Tipos de usuario
enum class TipoUsuario 
{
	DEFAULT = 0, // Tipo por defecto, no se usa directamente
    ESTUDIANTE = 1,
    EMPRESA = 2
};

// Estado de resultado de login
enum class LoginStatus 
{
    SUCCESS = 0,          // Login exitoso
    USER_NOT_FOUND = 1,   // Usuario no encontrado
    WRONG_PASSWORD = 2,   // Contraseña incorrecta
    FILE_ERROR = 3        // Error al abrir o leer el archivo
};

// Estructura para almacenar un usuario en disco (.dat)
struct UsuarioBinario 
{
    int id; // ID del usuario
    TipoUsuario tipoUsuario; // Tipo de usuario
    char nombreCompleto[MAX_FIELD_LEN];
    char nombreDeUsuario[MAX_FIELD_LEN];
    char contrasenaHash[MAX_FIELD_LEN];

    // Constructor por defecto (inicializa todo a '\0')
    UsuarioBinario() : id(0), tipoUsuario(TipoUsuario::DEFAULT) {
        std::memset(nombreCompleto, 0, MAX_FIELD_LEN);
        std::memset(nombreDeUsuario, 0, MAX_FIELD_LEN);
        std::memset(contrasenaHash, 0, MAX_FIELD_LEN);
    }

    // Constructor parametrizado
    UsuarioBinario(int id_, TipoUsuario tipo_, const std::string& nombreFull,
                   const std::string& usuario, const std::string& hash)
        : id(id_), tipoUsuario(tipo_) {
        std::strncpy(nombreCompleto, nombreFull.c_str(), MAX_FIELD_LEN - 1);
        std::strncpy(nombreDeUsuario, usuario.c_str(), MAX_FIELD_LEN - 1);
        std::strncpy(contrasenaHash, hash.c_str(), MAX_FIELD_LEN - 1);
        nombreCompleto[MAX_FIELD_LEN - 1] = '\0';
        nombreDeUsuario[MAX_FIELD_LEN - 1] = '\0';
        contrasenaHash[MAX_FIELD_LEN - 1] = '\0';
    }

    // Constructor desde objeto Usuario (requiere declaración previa de Usuario)
    // Se implementa fuera del struct para evitar dependencia circular
};

// Estructura para indice de usuarios en disco (.idx)
struct UsuarioIndex {
    char nombreDeUsuario[MAX_FIELD_LEN];
    int  offset;  // byte offset en el archivo de datos

    // Constructor por defecto
    UsuarioIndex() : offset(0) 
    {
        std::memset(nombreDeUsuario, 0, MAX_FIELD_LEN);
    }

    // Constructor parametrizado
    UsuarioIndex(const std::string& usuario, int off) : offset(off) 
    {
        std::strncpy(nombreDeUsuario, usuario.c_str(), MAX_FIELD_LEN - 1);
        nombreDeUsuario[MAX_FIELD_LEN - 1] = '\0';
    }

    // Comparador para ordenar / búsqueda binaria
    static int compare(const UsuarioIndex& a, const UsuarioIndex& b) {
        return std::strncmp(a.nombreDeUsuario, b.nombreDeUsuario, MAX_FIELD_LEN);
    }
    static int compare(const std::string& a, const UsuarioIndex& b) {
        return std::strncmp(a.c_str(), b.nombreDeUsuario, MAX_FIELD_LEN);
    }
};

struct UsuarioRawData {
    int id;
    TipoUsuario tipoUsuario;
    char nombreCompleto[MAX_FIELD_LEN];
    char nombreDeUsuario[MAX_FIELD_LEN];
    char contrasenaHash[MAX_FIELD_LEN];
    // Constructor por defecto
    UsuarioRawData() : id(0), tipoUsuario(TipoUsuario::DEFAULT) {
        std::memset(nombreCompleto, 0, MAX_FIELD_LEN);
        std::memset(nombreDeUsuario, 0, MAX_FIELD_LEN);
        std::memset(contrasenaHash, 0, MAX_FIELD_LEN);
    }
};

#endif // !COURSERACLONE_PERSISTENCE_USUARIOTYPES_HPP