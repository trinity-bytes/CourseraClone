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
#include "RequestHandler.h" // Para procesamiento de peticiones de clientes

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

    /**
     * @brief Maneja la comunicación con un cliente específico usando RequestHandler
     * @param clientSocket El socket del cliente a manejar
     * @param requestHandler Referencia al manejador de peticiones
     * @param mantenerConexion Si true, mantiene la conexión abierta para múltiples peticiones
     */
    void manejarCliente(SOCKET clientSocket, RequestHandler& requestHandler, bool mantenerConexion = true) {
        char buffer[DEFAULT_SERVER_BUFLEN];
        
        do {
            // Limpiar buffer
            memset(buffer, 0, DEFAULT_SERVER_BUFLEN);
            
            // Recibir petición del cliente
            int bytesRecibidos = recibirDatos(clientSocket, buffer, DEFAULT_SERVER_BUFLEN - 1);
            
            if (bytesRecibidos > 0) {
                // Procesar la petición usando RequestHandler
                std::string peticion(buffer);
                std::string respuesta = requestHandler.processRequest(peticion);
                
                // Enviar respuesta al cliente
                enviarDatos(clientSocket, respuesta.c_str(), static_cast<int>(respuesta.length()));
                
                // Log básico (reemplazar con Logger en el futuro)
                std::cout << "[SERVER] Petición: " << peticion << " -> Respuesta: " << respuesta << std::endl;
                
            } else if (bytesRecibidos == 0) {
                // Cliente cerró la conexión elegantemente
                std::cout << "[SERVER] Cliente desconectado" << std::endl;
                break;
            } else {
                // Error en la recepción
                std::cout << "[SERVER] Error al recibir datos del cliente" << std::endl;
                break;
            }
            
        } while (mantenerConexion);
        
        // Cerrar conexión con el cliente
        cerrarConexionCliente(clientSocket);
    }

    /**
     * @brief Método de utilidad para enviar un string como respuesta
     * @param clientSocket El socket del cliente
     * @param mensaje El mensaje a enviar
     * @return true si se envió correctamente, false en caso contrario
     */
    bool enviarMensaje(SOCKET clientSocket, const std::string& mensaje) {
        int resultado = enviarDatos(clientSocket, mensaje.c_str(), static_cast<int>(mensaje.length()));
        return resultado != SOCKET_ERROR && resultado == static_cast<int>(mensaje.length());
    }

    /**
     * @brief Método de utilidad para recibir un string del cliente
     * @param clientSocket El socket del cliente
     * @return El mensaje recibido, o string vacío si hay error
     */
    std::string recibirMensaje(SOCKET clientSocket) {
        char buffer[DEFAULT_SERVER_BUFLEN];
        memset(buffer, 0, DEFAULT_SERVER_BUFLEN);
        
        int bytesRecibidos = recibirDatos(clientSocket, buffer, DEFAULT_SERVER_BUFLEN - 1);
        
        if (bytesRecibidos > 0) {
            return std::string(buffer);
        }
        
        return "";
    }
};