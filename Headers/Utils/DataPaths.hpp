// Gestion de rutas organizadas por dominios de negocio

#ifndef COURSERACLONE_UTILS_DATAPATHS_HPP
#define COURSERACLONE_UTILS_DATAPATHS_HPP

#include <string>

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
};

// Implementacion de constantes
const std::string DataPaths::BASE_PATH = "Resources/Data/";

const std::string DataPaths::Core::BASE = BASE_PATH + "Core/";
const std::string DataPaths::Core::DB_USUARIOS = Core::BASE + "DB_Usuarios.dat";
const std::string DataPaths::Core::DB_INSCRIPCIONES = Core::BASE + "DB_Inscripciones.dat";
const std::string DataPaths::Core::INDICES_ESTUDIANTES = BASE_PATH + "Index/IDX_Usuarios_Estudiantes.dat";
const std::string DataPaths::Core::INDICES_EMPRESAS = BASE_PATH + "Index/IDX_Usuarios_Empresas.dat";

const std::string DataPaths::Content::BASE = BASE_PATH + "Content/";
const std::string DataPaths::Content::DB_CURSOS = Content::BASE + "DB_Cursos.txt";
const std::string DataPaths::Content::DB_ESPECIALIZACIONES = Content::BASE + "DB_Especializaciones.txt";


const std::string DataPaths::Financial::BASE = BASE_PATH + "Financial/";
const std::string DataPaths::Financial::DB_PAGOS = Financial::BASE + "DB_RegistroDePagos.dat";
const std::string DataPaths::Financial::DB_COMPROBANTES = Financial::BASE + "DB_ComprobantesDePago.csv";
const std::string DataPaths::Financial::INDICES_PAGOS = BASE_PATH + "Indices/IDX_RegistroDePagos.dat";
const std::string DataPaths::Financial::INDICES_COMPROBANTES = BASE_PATH + "Indices/IDX_ComprobantesDePago.csv";

const std::string DataPaths::Logs::BASE = BASE_PATH + "Logs/";
const std::string DataPaths::Logs::ERROR_LOGS = Logs::BASE + "Error_Logs.txt";
const std::string DataPaths::Logs::INFO_LOGS = Logs::BASE + "Info_Logs.txt";

#endif // COURSERACLONE_UTILS_DATAPATHS_HPP