// Cliente básico para probar el servidor PING/PONG
// Compilar con: g++ -o cliente_test cliente_test.cpp -lws2_32
// Usar: cliente_test.exe <ip_servidor> <puerto>

#include <iostream>
#include <string>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment (lib, "Ws2_32.lib")

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Uso: " << argv[0] << " <ip_servidor> <puerto>" << std::endl;
        std::cout << "Ejemplo: " << argv[0] << " 127.0.0.1 12345" << std::endl;
        return 1;
    }

    std::string serverIP = argv[1];
    int serverPort = std::stoi(argv[2]);

    WSADATA wsaData;
    SOCKET clientSocket = INVALID_SOCKET;
    
    // Inicializar Winsock
    int result = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return 1;
    }

    // Crear socket
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error al crear socket: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Configurar dirección del servidor
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    inet_pton(AF_INET, serverIP.c_str(), &serverAddr.sin_addr);

    // Conectar al servidor
    std::cout << "Conectando a " << serverIP << ":" << serverPort << "..." << std::endl;
    
    result = connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    if (result == SOCKET_ERROR) {
        std::cerr << "Error al conectar: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "¡Conectado al servidor!" << std::endl;
    std::cout << "Comandos disponibles:" << std::endl;
    std::cout << "  PING - Respuesta básica" << std::endl;
    std::cout << "  PING <mensaje> - Eco del mensaje" << std::endl;
    std::cout << "  quit - Salir" << std::endl;
    std::cout << "===========================================" << std::endl;

    // Bucle principal del cliente
    std::string input;
    char buffer[512];
    
    while (true) {
        std::cout << "Cliente> ";
        std::getline(std::cin, input);
        
        if (input == "quit" || input == "exit") {
            break;
        }
        
        if (input.empty()) {
            continue;
        }

        // Enviar comando al servidor
        int bytesSent = send(clientSocket, input.c_str(), input.length(), 0);
        if (bytesSent == SOCKET_ERROR) {
            std::cerr << "Error al enviar datos: " << WSAGetLastError() << std::endl;
            break;
        }

        // Recibir respuesta del servidor
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        
        if (bytesReceived > 0) {
            std::cout << "Servidor> " << buffer << std::endl;
        } else if (bytesReceived == 0) {
            std::cout << "Servidor cerró la conexión." << std::endl;
            break;
        } else {
            std::cerr << "Error al recibir datos: " << WSAGetLastError() << std::endl;
            break;
        }
    }

    // Limpieza
    std::cout << "Cerrando conexión..." << std::endl;
    closesocket(clientSocket);
    WSACleanup();
    
    return 0;
}
