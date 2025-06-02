// Cabeceras propias
#include "ExtendedFunctions.h"
#include "Controladora.h"

// Headers de la libreria estandar
#include <iostream> // Para std::cout, std::cerr
#include <string>   // Para std::string, std::stoi
#include <vector>   // No es estrictamente necesario aqu�, pero �til para manejo de args m�s complejo

// maquetacion de funciones
void SecuenciaInicializacion();
// ------------------------

// Modificado para aceptar argumentos de l�nea de comandos
int main(int argc, char* argv[]) 
{
	SecuenciaInicializacion();

	bool isServerMode = false;
	std::string clientIpAddress = "";
	int clientPort = 0; // Puerto por defecto o se leer� de argumentos

	// Procesar argumentos de l�nea de comandos
	if (argc >= 2) {
		std::string modeArg = argv[1];
		if (modeArg == "-server") {
			isServerMode = true;
			std::cout << "Modo Servidor activado." << std::endl;
			// Opcionalmente, aqu� se podr�a parsear un puerto para el servidor si se a�ade al plan:
			// if (argc > 2) { /* parse server port from argv[2] */ }
		}
		else if (modeArg == "-client") {
			isServerMode = false;
			if (argc >= 3) {
				clientIpAddress = argv[2];
				std::cout << "Modo Cliente activado." << std::endl;
				std::cout << "Intentando conectar a IP: " << clientIpAddress << std::endl;
				if (argc >= 4) {
					try {
						clientPort = std::stoi(argv[3]);
						std::cout << "Usando puerto especificado: " << clientPort << std::endl;
					}
					catch (const std::invalid_argument& ia) {
						std::cerr << "Error: Puerto invalido - " << argv[3] << ". " << ia.what() << std::endl;
						system("pause");
						return 1;
					}
					catch (const std::out_of_range& oor) {
						std::cerr << "Error: Puerto fuera de rango - " << argv[3] << ". " << oor.what() << std::endl;
						system("pause");
						return 1;
					}
				}
				else {
					// Usar un puerto por defecto si no se especifica para el cliente
					clientPort = 12345; // Puerto por defecto (ejemplo)
					std::cout << "Usando puerto por defecto: " << clientPort << std::endl;
				}
			}
			else {
				std::cerr << "Error: Modo cliente requiere la direccion IP del servidor." << std::endl;
				std::cerr << "Uso: " << argv[0] << " -client <ip_servidor> [puerto]" << std::endl;
				system("pause");
				return 1;
			}
		}
		else {
			std::cerr << "Error: Argumento no reconocido: " << modeArg << std::endl;
			std::cerr << "Uso: " << argv[0] << " -server | -client <ip_servidor> [puerto]" << std::endl;
			system("pause");
			return 1;
		}
	}
	else {
		// Comportamiento por defecto si no hay argumentos (o error)
		// Podr�a ser iniciar como cliente a localhost, o mostrar mensaje de uso.
		// Por ahora, mostraremos un mensaje de error y uso.
		std::cerr << "Error: No se especifico el modo de operacion." << std::endl;
		std::cerr << "Uso: " << argv[0] << " -server | -client <ip_servidor> [puerto]" << std::endl;
		system("pause");
		return 1;
	}

	// En este punto, isServerMode, clientIpAddress, y clientPort est�n configurados.
	// Estos valores se usar�n para inicializar la Controladora o los NetworkManagers
	// seg�n las tareas de Santi y Mauricio/Jahat respectivamente.

	try
	{
		// La instanciaci�n de Controladora se adaptar� en una tarea posterior
		// para ser consciente del modo (isServerMode) y los par�metros de red.
		// Controladora app(isServerMode, clientIpAddress, clientPort); // Ejemplo de futura instanciaci�n
		Controladora app; // Por ahora, se mantiene la instanciaci�n original.
		app.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error en la aplicacion: " << e.what() << std::endl;
	}

	system("pause");
	return 0; // Retornar 0 en caso de finalizaci�n exitosa
}

void SecuenciaInicializacion()
{
	ConfigurarConsola();
}