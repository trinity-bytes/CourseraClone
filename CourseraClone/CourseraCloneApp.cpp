// Define WIN32_LEAN_AND_MEAN to exclude rarely-used stuff from Windows headers
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

// Define NOMINMAX to prevent Windows headers from defining min and max macros
#ifndef NOMINMAX
#define NOMINMAX
#endif

// Windows specific headers
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h> // windows.h should be included after winsock2.h if both are needed directly

// Cabeceras propias
#include "ExtendedFunctions.h"
#include "Controladora.h"
#include "NetworkManagerServer.h"
#include "RequestHandler.h" // Asegurarnos de incluir RequestHandler.h para el manejador de peticiones
// #include "ConfigManager.h" // Se incluirá cuando ConfigManager.h esté disponible
// #include "Logger.h"         // Se incluirá cuando Logger.h esté disponible

// Headers de la libreria estandar
#include <iostream> // Para std::cout, std::cerr
#include <string>   // Para std::string, std::stoi
#include <vector>   // No es estrictamente necesario aquí, pero útil para manejo de args más complejo
#include <thread>   // Para manejo de múltiples clientes

// Link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

// maquetacion de funciones
void SecuenciaInicializacion();
void ejecutarModoServidor(int puerto);
void manejarClienteEnHilo(SOCKET clientSocket, RequestHandler& requestHandler);
// ------------------------

// Modificado para aceptar argumentos de lnea de comandos
int main(int argc, char* argv[])
{
	SecuenciaInicializacion();

	// Initialize Winsock
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		std::cerr << "WSAStartup failed: " << iResult << std::endl;
		system("pause");
		return 1;
	}

	// ConfigManager configManager; // Se instanciará y usar cuando est disponible
	// Logger logger; // Se usar de forma esttica o instanciada segn su diseo

	// Valores por defecto (eventualmente se cargaran desde ConfigManager)
	int defaultServerPort = 12345; // Ejemplo
	std::string defaultServerIp = "127.0.0.1"; // Ejemplo

	bool isServerMode = false;
	std::string serverIpToConnectTo = defaultServerIp;
	int serverPortToConnectTo = defaultServerPort;
	int serverListenPort = defaultServerPort;

	// Procesar argumentos de lnea de comandos
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
		WSACleanup(); // Cleanup Winsock
		return 1;
	}

	try
	{
		// La instancin de Controladora se adaptar en una tarea posterior por Santi.
		// Se le pasarn los parmetros de configuracin de red y modo.
		// Ejemplo de futura instanciacin:
		// Controladora app(isServerMode, serverIpToConnectTo, serverPortToConnectTo, serverListenPort);
		Controladora app; // Por ahora, se mantiene la instanciacin original.
		// Cuando Controladora se actualice, esta lnea cambiar para pasarle los parmetros.
		app.run();
	}
	catch (const std::exception& e)
	{
		// Logger::logError("Error en la aplicacion: " + std::string(e.what()));
		std::cerr << "Error en la aplicacion: " << e.what() << std::endl;
	}

	// Cleanup Winsock
	WSACleanup();

	system("pause");
	return 0; // Retornar 0 en caso de finalizacin exitosa
}

void SecuenciaInicializacion()
{
	ConfigurarConsola();
}

// ======================== FUNCIONES DEL SERVIDOR ========================

/**
 * @brief Función para ejecutar el servidor y manejar múltiples clientes
 * @param puerto Puerto en el que escuchará el servidor
 */
void ejecutarModoServidor(int puerto) {
	NetworkManagerServer servidor;
	RequestHandler requestHandler;

	std::cout << "[SERVER] Iniciando servidor en puerto " << puerto << "..." << std::endl;

	if (!servidor.iniciarServidor(puerto)) {
		std::cerr << "[SERVER] Error al iniciar servidor en puerto " << puerto << std::endl;
		std::cerr << "[SERVER] Verifique que el puerto no esté en uso y que tenga permisos." << std::endl;
		return;
	}

	std::cout << "[SERVER] ========================================" << std::endl;
	std::cout << "[SERVER] Servidor iniciado exitosamente!" << std::endl;
	std::cout << "[SERVER] Puerto: " << puerto << std::endl;
	std::cout << "[SERVER] Comandos soportados: PING" << std::endl;
	std::cout << "[SERVER] Esperando conexiones de clientes..." << std::endl;
	std::cout << "[SERVER] Presione Ctrl+C para detener el servidor" << std::endl;
	std::cout << "[SERVER] ========================================" << std::endl;

	// Bucle principal del servidor
	while (servidor.estaCorriendo()) {
		// Aceptar cliente (esta es una llamada bloqueante)
		SOCKET clientSocket = servidor.aceptarCliente();

		if (clientSocket != INVALID_SOCKET) {
			std::cout << "[SERVER] ¡Cliente conectado! Creando hilo para manejar la conexión..." << std::endl;

			// Crear hilo para manejar cliente (no bloquea para otros clientes)
			std::thread clienteThread(manejarClienteEnHilo, clientSocket, std::ref(requestHandler));
			clienteThread.detach(); // Permitir que el hilo se ejecute independientemente

		}
		else {
			std::cout << "[SERVER] Error al aceptar cliente o servidor detenido" << std::endl;
			break;
		}
	}

	std::cout << "[SERVER] Deteniendo servidor..." << std::endl;
	servidor.detenerServidor();
	std::cout << "[SERVER] Servidor detenido." << std::endl;
}

/**
 * @brief Función para manejar un cliente en un hilo separado
 * @param clientSocket Socket del cliente a manejar
 * @param requestHandler Referencia al manejador de peticiones
 */
void manejarClienteEnHilo(SOCKET clientSocket, RequestHandler& requestHandler) {
	NetworkManagerServer serverInstance; // Instancia local para usar métodos de utilidad

	std::cout << "[SERVER] Iniciando manejo de cliente en hilo separado" << std::endl;

	// Usar el método integrado que ya maneja la comunicación completa
	serverInstance.manejarCliente(clientSocket, requestHandler, true);

	std::cout << "[SERVER] Cliente desconectado, finalizando hilo" << std::endl;
}
