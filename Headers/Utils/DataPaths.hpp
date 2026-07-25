// Gestion de rutas organizadas por dominios de negocio

#ifndef COURSERACLONE_UTILS_DATAPATHS_HPP
#define COURSERACLONE_UTILS_DATAPATHS_HPP

#include <windows.h>
#include <filesystem>
#include <string>
#include <system_error>

namespace DataPathsDetalle
{
    /// @brief Devuelve la carpeta donde vive el ejecutable
    inline std::filesystem::path directorioDelEjecutable()
    {
        wchar_t ruta[MAX_PATH] = { 0 };
        DWORD largo = GetModuleFileNameW(nullptr, ruta, MAX_PATH);
        if (largo == 0 || largo >= MAX_PATH) return std::filesystem::current_path();

        return std::filesystem::path(ruta).parent_path();
    }

    /// @brief Resuelve dónde vive Resources/Data.
    ///
    /// Las rutas eran relativas al directorio de trabajo, así que la app solo
    /// encontraba sus datos cuando se lanzaba con el CWD en la raíz del repo
    /// (lo que hace Visual Studio con F5). Desde una terminal, el CWD es
    /// cualquier cosa y la app terminaba creando carpetas vacías donde estuviera
    /// parada. Ahora el ancla es el ejecutable, no el CWD.
    inline std::string resolverBasePath()
    {
        namespace fs = std::filesystem;
        const fs::path relativa = "Resources/Data";
        std::error_code ec;

        // 1) El CWD manda si ya tiene los datos (compatibilidad con F5 en VS)
        if (fs::exists(relativa, ec)) return "Resources/Data/";

        // 2) Desde el ejecutable hacia arriba: x64/Release -> x64 -> raíz del repo
        fs::path directorio = directorioDelEjecutable();
        for (int nivel = 0; nivel < 6; ++nivel)
        {
            fs::path candidata = directorio / relativa;
            if (fs::exists(candidata, ec)) return candidata.generic_string() + "/";

            fs::path padre = directorio.parent_path();
            if (padre.empty() || padre == directorio) break;
            directorio = padre;
        }

        // 3) Sin datos a la vista: se crean al lado del ejecutable, no en el CWD
        return (directorioDelEjecutable() / relativa).generic_string() + "/";
    }
}

class DataPaths
{
private:
    static const std::string BASE_PATH;

public:
	// Dominio Nucleo
    struct Core 
    {
        static const std::string BASE;
		static const std::string DB_USUARIOS;
        static const std::string DB_INSCRIPCIONES;
        static const std::string INDICES_INSCRIPCIONES;
        static const std::string INDICES_ESTUDIANTES;
        static const std::string INDICES_EMPRESAS;
    };

	// Dominio de Contenido 
    struct Content 
    {
        static const std::string BASE;
        static const std::string DB_CURSOS;
        static const std::string DB_ESPECIALIZACIONES;
    };

    // Dominio Financiero
    struct Financial 
    {
        static const std::string BASE;
        static const std::string DB_PAGOS;
        static const std::string DB_COMPROBANTES;
        static const std::string INDICES_PAGOS;
        static const std::string INDICES_COMPROBANTES;
    };

    // Dominio Logs
    struct Logs
    {
        static const std::string BASE;
        static const std::string ERROR_LOGS;
        static const std::string INFO_LOGS;
    };

    // Índices (transversal a los demás dominios)
    struct Index
    {
        static const std::string BASE;
    };
};

// Implementacion de constantes
const std::string DataPaths::BASE_PATH = DataPathsDetalle::resolverBasePath();

const std::string DataPaths::Core::BASE = BASE_PATH + "Core/";
const std::string DataPaths::Core::DB_USUARIOS = Core::BASE + "DB_Usuarios.dat";
const std::string DataPaths::Core::DB_INSCRIPCIONES = Core::BASE + "DB_Inscripciones.dat";
const std::string DataPaths::Core::INDICES_ESTUDIANTES = BASE_PATH + "Index/IDX_Usuarios_Estudiantes.dat";
const std::string DataPaths::Core::INDICES_EMPRESAS = BASE_PATH + "Index/IDX_Usuarios_Empresas.dat";
const std::string DataPaths::Core::INDICES_INSCRIPCIONES = BASE_PATH + "Index/IDX_Inscripciones.dat";

const std::string DataPaths::Content::BASE = BASE_PATH + "Content/";
const std::string DataPaths::Content::DB_CURSOS = Content::BASE + "DB_Cursos.txt";
const std::string DataPaths::Content::DB_ESPECIALIZACIONES = Content::BASE + "DB_Especializaciones.txt";


const std::string DataPaths::Financial::BASE = BASE_PATH + "Financial/";
const std::string DataPaths::Financial::DB_PAGOS = Financial::BASE + "DB_RegistroDePagos.dat";
const std::string DataPaths::Financial::DB_COMPROBANTES = Financial::BASE + "DB_ComprobantesDePago.csv";
const std::string DataPaths::Financial::INDICES_PAGOS = BASE_PATH + "Index/IDX_RegistroDePagos.dat";
const std::string DataPaths::Financial::INDICES_COMPROBANTES = BASE_PATH + "Index/IDX_ComprobantesDePago.csv";

const std::string DataPaths::Logs::BASE = BASE_PATH + "Logs/";
const std::string DataPaths::Logs::ERROR_LOGS = Logs::BASE + "Error_Logs.txt";
const std::string DataPaths::Logs::INFO_LOGS = Logs::BASE + "Info_Logs.txt";

const std::string DataPaths::Index::BASE = BASE_PATH + "Index/";

#endif // COURSERACLONE_UTILS_DATAPATHS_HPP