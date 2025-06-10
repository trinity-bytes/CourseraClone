#ifndef COURSERACLONE_PERSISTENCE_USUARIOTYPES_HPP
#define COURSERACLONE_PERSISTENCE_USUARIOTYPES_HPP

#include <string>
#include <cstring>

// Máxima longitud para campos de texto en binarios
static constexpr int MAX_FIELD_LEN = 50;

// Tipos de usuario
enum class TipoUsuario {
    NINGUNO = 0,
    ESTUDIANTE = 1,
    EMPRESA = 2
};

// Estructura para almacenar un usuario en disco (.dat)
struct UsuarioBinario {
    char nombreCompleto[MAX_FIELD_LEN];
    char nombreDeUsuario[MAX_FIELD_LEN];
    char contrasenaHash[MAX_FIELD_LEN];

    // Constructor por defecto (inicializa todo a '\0')
    UsuarioBinario() {
        std::memset(nombreCompleto, 0, MAX_FIELD_LEN);
        std::memset(nombreDeUsuario, 0, MAX_FIELD_LEN);
        std::memset(contrasenaHash, 0, MAX_FIELD_LEN);
    }

    // Constructor parametrizado (pasa datos ya con hash)
    UsuarioBinario(const std::string& nombreFull,
        const std::string& usuario,
        const std::string& hash) {
        std::strncpy(nombreCompleto, nombreFull.c_str(), MAX_FIELD_LEN - 1);
        std::strncpy(nombreDeUsuario, usuario.c_str(), MAX_FIELD_LEN - 1);
        std::strncpy(contrasenaHash, hash.c_str(), MAX_FIELD_LEN - 1);
        nombreCompleto[MAX_FIELD_LEN - 1] = '\0';
        nombreDeUsuario[MAX_FIELD_LEN - 1] = '\0';
        contrasenaHash[MAX_FIELD_LEN - 1] = '\0';
    }
};

// Estructura para índice de usuarios en disco (.idx)
struct UsuarioIndex {
    char nombreDeUsuario[MAX_FIELD_LEN];
    int  offset;  // byte offset en el archivo de datos

    // Constructor por defecto
    UsuarioIndex() : offset(0) {
        std::memset(nombreDeUsuario, 0, MAX_FIELD_LEN);
    }

    // Constructor parametrizado
    UsuarioIndex(const std::string& usuario, int off)
        : offset(off) {
        std::strncpy(nombreDeUsuario, usuario.c_str(), MAX_FIELD_LEN - 1);
        nombreDeUsuario[MAX_FIELD_LEN - 1] = '\0';
    }

    // Comparador para ordenar / búsqueda binaria
    // Retorna <0 si a < b, 0 si iguales, >0 si a > b
    static int compare(const UsuarioIndex& a, const UsuarioIndex& b) {
        return std::strncmp(a.nombreDeUsuario, b.nombreDeUsuario, MAX_FIELD_LEN);
    }

    // Comparador contra clave string
    static int compare(const std::string& a, const UsuarioIndex& b) {
        return std::strncmp(a.c_str(), b.nombreDeUsuario, MAX_FIELD_LEN);
    }
};

// Funciones helper para obtener rutas de archivos
inline std::string getDataFilePath(TipoUsuario tipo) 
{
    switch (tipo) {
    case TipoUsuario::EMPRESA:
        return "Resources/Data/usuarios_empresa.dat";
    case TipoUsuario::ESTUDIANTE:
        return "Resources/Data/usuarios_estudiante.dat";
    default:
        return "";
    }
}

inline std::string getIndexFilePath(TipoUsuario tipo) 
{
    switch (tipo) {
    case TipoUsuario::EMPRESA: 
        return "Resources/Data/indices/usuarios_empresa.idx";
    case TipoUsuario::ESTUDIANTE:
        return "Resources/Data/indices/usuarios_estudiante.idx";
    default:
        return "";
    }
}

#endif // !COURSERACLONE_PERSISTENCE_USUARIOTYPES_HPP