#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>   // Para tipos de datos y funciones de Windows
#include <winsock2.h>  // Para funciones de sockets
#include <ws2tcpip.h>  // Para funciones de sockets y direcciones IP
#include <string>      // Para manejar cadenas de texto, especialmente en mensajes de error
#include <vector>      // Incluido para posible manejo futuro de múltiples clientes o datos
#include <iostream>    // Para depuración básica, se reemplazará/complementará con Logger

// Link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_SERVER_BUFLEN 512 // Tamaño del buffer por defecto para recepción/envío

class NetworkManagerServer 
{
private:
    WSADATA wsaData;        // Estructura que contiene información sobre la implementación de Windows Sockets.
    SOCKET listenSocket;    // Socket para escuchar conexiones entrantes.
    // SOCKET clientSocket; // Para la Semana 1, aceptarCliente devolverá el socket.
                            // La gestión de múltiples clientSockets se hará externamente o en una capa superior.

    bool isWSAInitialized;  // Flag para rastrear si WSAStartup fue exitoso.
    bool serverRunning;     // Flag para rastrear si el servidor está activamente escuchando.
public:
    NetworkManagerServer();
    ~NetworkManagerServer();

    /**
     * @brief Inicializa Winsock, crea un socket de escucha, lo enlaza al puerto especificado y comienza a escuchar.
     * @param puerto El número de puerto en el que el servidor escuchará las conexiones entrantes.
     * @return true si el servidor se inició correctamente y está escuchando, false en caso contrario.
     */
    bool iniciarServidor(int puerto);

    /**
     * @brief Acepta una conexión de cliente entrante. Esta es una llamada bloqueante.
     *        La gestión de múltiples clientes (ej. en hilos) se manejará fuera de esta llamada directa.
     * @return El SOCKET para el cliente aceptado, o INVALID_SOCKET si ocurre un error o el servidor no está escuchando.
     */
    SOCKET aceptarCliente();

    /**
     * @brief Recibe datos del socket de un cliente específico.
     * @param clientSocket El socket del cliente del cual recibir datos.
     * @param buffer Búfer para almacenar los datos recibidos.
     * @param bufferSize El tamaño del búfer.
     * @return El número de bytes recibidos. Si es 0, el cliente cerró la conexión de forma elegante.
     *         Si es SOCKET_ERROR, ocurrió un error.
     */
    int recibirDatos(SOCKET clientSocket, char* buffer, int bufferSize);

    /**
     * @brief Envía datos al socket de un cliente específico.
     * @param clientSocket El socket del cliente al cual enviar datos.
     * @param data Puntero a los datos a enviar.
     * @param dataSize El tamaño de los datos a enviar, en bytes.
     * @return El número de bytes enviados. Si es SOCKET_ERROR, ocurrió un error.
     */
    int enviarDatos(SOCKET clientSocket, const char* data, int dataSize);

    /**
     * @brief Cierra la conexión con un cliente específico.
     * @param clientSocket El socket del cliente cuya conexión se cerrará.
     */
    void cerrarConexionCliente(SOCKET clientSocket);

    /**
     * @brief Detiene el socket de escucha del servidor y realiza la limpieza de Winsock.
     */
    void detenerServidor();

    /**
     * @brief Verifica si el servidor está actualmente en ejecución (es decir, el socket de escucha está activo).
     * @return true si el servidor está en ejecución, false en caso contrario.
     */
    bool estaCorriendo() const;
};