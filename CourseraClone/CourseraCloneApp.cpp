// Cabeceras propias
#include "ExtendedFunctions.h"
#include "Controladora.h"
// #include "ConfigManager.h" // Se incluirá cuando ConfigManager.h esté disponible
// #include "Logger.h"         // Se incluirá cuando Logger.h esté disponible

// Headers de la libreria estandar
#include <iostream> // Para std::cout, std::cerr
#include <string>   // Para std::string, std::stoi
#include <vector>   // No es estrictamente necesario aquí, pero útil para manejo de args más complejo

// maquetacion de funciones
void SecuenciaInicializacion();
// ------------------------

// Modificado para aceptar argumentos de línea de comandos
int main(int argc, char* argv[])
{
	SecuenciaInicializacion();

	// ConfigManager configManager; // Se instanciará y usará cuando esté disponible
	// Logger logger; // Se usará de forma estática o instanciada según su diseño

	// Valores por defecto (eventualmente se cargarían desde ConfigManager)
	int defaultServerPort = 12345; // Ejemplo
	std::string defaultServerIp = "127.0.0.1"; // Ejemplo

	bool isServerMode = false;
	std::string serverIpToConnectTo = defaultServerIp;
	int serverPortToConnectTo = defaultServerPort;
	int serverListenPort = defaultServerPort;

	// Procesar argumentos de línea de comandos
	if (argc >= 2) {
		std::string modeArg = argv[1];
		if (modeArg == "-server") {
			isServerMode = true;
			// Logger::logInfo("Modo Servidor activado."); // Uso futuro de Logger
			std::cout << "Modo Servidor activado." << std::endl;
			if (argc >= 3) { // Puerto del servidor especificado
				try {
					serverListenPort = std::stoi(argv[2]);
					// Logger::logInfo("Usando puerto de escucha especificado: " + std::to_string(serverListenPort));
					std::cout << "Usando puerto de escucha especificado: " << serverListenPort << std::endl;
				}
				catch (const std::invalid_argument& ia) {
					// Logger::logError("Error: Puerto de servidor invalido - " + std::string(argv[2]) + ". " + ia.what());
					std::cerr << "Error: Puerto de servidor invalido - " << argv[2] << ". " << ia.what() << std::endl;
					system("pause");
					return 1;
				}
				catch (const std::out_of_range& oor) {
					// Logger::logError("Error: Puerto de servidor fuera de rango - " + std::string(argv[2]) + ". " + oor.what());
					std::cerr << "Error: Puerto de servidor fuera de rango - " << argv[2] << ". " << oor.what() << std::endl;
					system("pause");
					return 1;
				}
			}
			else {
				// serverListenPort = configManager.getServerPort(); // Uso futuro de ConfigManager
				// Logger::logInfo("Usando puerto de escucha por defecto: " + std::to_string(serverListenPort));
				std::cout << "Usando puerto de escucha por defecto: " << serverListenPort << std::endl;
			}
		}
		else if (modeArg == "-client") {
			isServerMode = false;
			// Logger::logInfo("Modo Cliente activado.");
			std::cout << "Modo Cliente activado." << std::endl;
			if (argc >= 3) { // IP del servidor especificada
				serverIpToConnectTo = argv[2];
				// Logger::logInfo("Intentando conectar a IP: " + serverIpToConnectTo);
				std::cout << "Intentando conectar a IP: " << serverIpToConnectTo << std::endl;

				if (argc >= 4) { // Puerto del servidor especificado
					try {
						serverPortToConnectTo = std::stoi(argv[3]);
						// Logger::logInfo("Usando puerto de servidor especificado: " + std::to_string(serverPortToConnectTo));
						std::cout << "Usando puerto de servidor especificado: " << serverPortToConnectTo << std::endl;
					}
					catch (const std::invalid_argument& ia) {
						// Logger::logError("Error: Puerto de servidor invalido - " + std::string(argv[3]) + ". " + ia.what());
						std::cerr << "Error: Puerto de servidor invalido - " << argv[3] << ". " << ia.what() << std::endl;
						system("pause");
						return 1;
					}
					catch (const std::out_of_range& oor) {
						// Logger::logError("Error: Puerto de servidor fuera de rango - " + std::string(argv[3]) + ". " + oor.what());
						std::cerr << "Error: Puerto de servidor fuera de rango - " << argv[3] << ". " << oor.what() << std::endl;
						system("pause");
						return 1;
					}
				}
				else {
					// serverPortToConnectTo = configManager.getServerPort(); // Uso futuro de ConfigManager
					// Logger::logInfo("Usando puerto de servidor por defecto: " + std::to_string(serverPortToConnectTo));
					std::cout << "Usando puerto de servidor por defecto: " << serverPortToConnectTo << std::endl;
				}
			}
			else {
				// Logger::logError("Error: Modo cliente requiere la direccion IP del servidor.");
				std::cerr << "Error: Modo cliente requiere la direccion IP del servidor." << std::endl;
				std::cerr << "Uso: " << argv[0] << " -client <ip_servidor> [puerto_servidor]" << std::endl;
				system("pause");
				return 1;
			}
		}
		else {
			// Logger::logError("Error: Argumento no reconocido: " + modeArg);
			std::cerr << "Error: Argumento no reconocido: " << modeArg << std::endl;
			std::cerr << "Uso: " << argv[0] << " -server [puerto_servidor] | -client <ip_servidor> [puerto_servidor]" << std::endl;
			system("pause");
			return 1;
		}
	}
	else {
		// Logger::logError("Error: No se especifico el modo de operacion.");
		std::cerr << "Error: No se especifico el modo de operacion." << std::endl;
		std::cerr << "Uso: " << argv[0] << " -server [puerto_servidor] | -client <ip_servidor> [puerto_servidor]" << std::endl;
		system("pause");
		return 1;
	}

	try
	{
		// La instanciación de Controladora se adaptará en una tarea posterior por Santi.
		// Se le pasarán los parámetros de configuración de red y modo.
		// Ejemplo de futura instanciación:
		// Controladora app(isServerMode, serverIpToConnectTo, serverPortToConnectTo, serverListenPort);
		Controladora app; // Por ahora, se mantiene la instanciación original.
		// Cuando Controladora se actualice, esta línea cambiará para pasarle los parámetros.
		app.run();
	}
	catch (const std::exception& e)
	{
		// Logger::logError("Error en la aplicacion: " + std::string(e.what()));
		std::cerr << "Error en la aplicacion: " << e.what() << std::endl;
	}

	system("pause");
	return 0; // Retornar 0 en caso de finalización exitosa
}

void SecuenciaInicializacion()
{
	ConfigurarConsola();
}
