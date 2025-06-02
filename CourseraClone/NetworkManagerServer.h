#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>   // Para tipos de datos y funciones de Windows
#include <winsock2.h>  // Para funciones de sockets
#include <ws2tcpip.h>  // Para funciones de sockets y direcciones IP
#include <string>      // Para manejar cadenas de texto, especialmente en mensajes de error
#include <vector>      // Incluido para posible manejo futuro de m�ltiples clientes o datos
#include <iostream>    // Para depuraci�n b�sica, se reemplazar�/complementar� con Logger

// Link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_SERVER_BUFLEN 512 // Tama�o del buffer por defecto para recepci�n/env�o

class NetworkManagerServer 
{
private:
    WSADATA wsaData;        // Estructura que contiene informaci�n sobre la implementaci�n de Windows Sockets.
    SOCKET listenSocket;    // Socket para escuchar conexiones entrantes.
    // SOCKET clientSocket; // Para la Semana 1, aceptarCliente devolver� el socket.
                            // La gesti�n de m�ltiples clientSockets se har� externamente o en una capa superior.

    bool isWSAInitialized;  // Flag para rastrear si WSAStartup fue exitoso.
    bool serverRunning;     // Flag para rastrear si el servidor est� activamente escuchando.
public:
    NetworkManagerServer();
    ~NetworkManagerServer();

    /**
     * @brief Inicializa Winsock, crea un socket de escucha, lo enlaza al puerto especificado y comienza a escuchar.
     * @param puerto El n�mero de puerto en el que el servidor escuchar� las conexiones entrantes.
     * @return true si el servidor se inici� correctamente y est� escuchando, false en caso contrario.
     */
    bool iniciarServidor(int puerto);

    /**
     * @brief Acepta una conexi�n de cliente entrante. Esta es una llamada bloqueante.
     *        La gesti�n de m�ltiples clientes (ej. en hilos) se manejar� fuera de esta llamada directa.
     * @return El SOCKET para el cliente aceptado, o INVALID_SOCKET si ocurre un error o el servidor no est� escuchando.
     */
    SOCKET aceptarCliente();

    /**
     * @brief Recibe datos del socket de un cliente espec�fico.
     * @param clientSocket El socket del cliente del cual recibir datos.
     * @param buffer B�fer para almacenar los datos recibidos.
     * @param bufferSize El tama�o del b�fer.
     * @return El n�mero de bytes recibidos. Si es 0, el cliente cerr� la conexi�n de forma elegante.
     *         Si es SOCKET_ERROR, ocurri� un error.
     */
    int recibirDatos(SOCKET clientSocket, char* buffer, int bufferSize);

    /**
     * @brief Env�a datos al socket de un cliente espec�fico.
     * @param clientSocket El socket del cliente al cual enviar datos.
     * @param data Puntero a los datos a enviar.
     * @param dataSize El tama�o de los datos a enviar, en bytes.
     * @return El n�mero de bytes enviados. Si es SOCKET_ERROR, ocurri� un error.
     */
    int enviarDatos(SOCKET clientSocket, const char* data, int dataSize);

    /**
     * @brief Cierra la conexi�n con un cliente espec�fico.
     * @param clientSocket El socket del cliente cuya conexi�n se cerrar�.
     */
    void cerrarConexionCliente(SOCKET clientSocket);

    /**
     * @brief Detiene el socket de escucha del servidor y realiza la limpieza de Winsock.
     */
    void detenerServidor();

    /**
     * @brief Verifica si el servidor est� actualmente en ejecuci�n (es decir, el socket de escucha est� activo).
     * @return true si el servidor est� en ejecuci�n, false en caso contrario.
     */
    bool estaCorriendo() const;
};