#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <string>
#include <map>
#include <functional>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <vector>

/**
 * @brief Clase para manejar y procesar peticiones del cliente al servidor
 * 
 * Esta clase parsea peticiones de texto, las procesa usando handlers registrados
 * y devuelve respuestas apropiadas. Inicialmente maneja PING/PONG pero es
 * extensible para futuros comandos.
 */
class RequestHandler {
private:
    // Mapa de comandos a funciones handler
    std::map<std::string, std::function<std::string(const std::string&)>> commandHandlers;
    
    /**
     * @brief Parsea una petición en comando y parámetros
     * @param request La petición completa como string
     * @return Par con el comando y los parámetros
     */
    std::pair<std::string, std::string> parseRequest(const std::string& request) {
        std::istringstream iss(request);
        std::string command;
        
        // Extraer el primer token como comando
        if (!(iss >> command)) {
            throw std::runtime_error("Invalid request format");
        }
        
        // Convertir comando a mayúsculas
        std::transform(command.begin(), command.end(), command.begin(), ::toupper);
        
        // El resto es parámetros
        std::string parameters;
        std::getline(iss, parameters);
        
        // Trim leading whitespace from parameters
        if (!parameters.empty() && parameters[0] == ' ') {
            parameters = parameters.substr(1);
        }
        
        return {command, parameters};
    }
    
    /**
     * @brief Handler específico para el comando PING
     * @param parameters Parámetros del comando PING
     * @return Respuesta PONG
     */
    std::string handlePing(const std::string& parameters) {
        // Implementación básica de PING/PONG
        if (parameters.empty()) {
            return "PONG";
        } else {
            return "PONG " + parameters;
        }
    }
    
    /**
     * @brief Handler para comandos no reconocidos
     * @param command El comando no reconocido
     * @return Mensaje de error
     */
    std::string handleUnknownCommand(const std::string& command) {
        return "ERROR: Unknown command '" + command + "'";
    }

public:
    /**
     * @brief Constructor por defecto
     * Registra los handlers iniciales (PING)
     */
    RequestHandler() {
        // Registrar handlers iniciales
        commandHandlers["PING"] = [this](const std::string& params) { 
            return handlePing(params); 
        };
    }
    
    /**
     * @brief Destructor por defecto
     */
    ~RequestHandler() {
        // Cleanup automático de std::map
    }
    
    /**
     * @brief Método principal para procesar peticiones
     * @param request La petición completa como string
     * @return La respuesta procesada
     */
    std::string processRequest(const std::string& request) {
        if (request.empty()) {
            return "ERROR: Empty request";
        }
        
        try {
            // Parsear la petición
            auto [command, parameters] = parseRequest(request);
            
            // Buscar el handler correspondiente
            auto it = commandHandlers.find(command);
            if (it != commandHandlers.end()) {
                return it->second(parameters);
            } else {
                return handleUnknownCommand(command);
            }
        } catch (const std::exception& e) {
            return "ERROR: " + std::string(e.what());
        }
    }
    
    /**
     * @brief Registra un nuevo handler para un comando
     * @param command El comando a registrar (se convertirá a mayúsculas)
     * @param handler La función que manejará el comando
     */
    void registerHandler(const std::string& command, 
                        std::function<std::string(const std::string&)> handler) {
        std::string upperCommand = command;
        std::transform(upperCommand.begin(), upperCommand.end(), 
                      upperCommand.begin(), ::toupper);
        commandHandlers[upperCommand] = handler;
    }
    
    /**
     * @brief Obtiene la lista de comandos registrados
     * @return Vector con los nombres de comandos disponibles
     */
    std::vector<std::string> getAvailableCommands() const {
        std::vector<std::string> commands;
        for (const auto& pair : commandHandlers) {
            commands.push_back(pair.first);
        }
        return commands;
    }
    
    /**
     * @brief Verifica si un comando está registrado
     * @param command El comando a verificar
     * @return true si el comando existe, false en caso contrario
     */
    bool hasCommand(const std::string& command) const {
        std::string upperCommand = command;
        std::transform(upperCommand.begin(), upperCommand.end(), 
                      upperCommand.begin(), ::toupper);
        return commandHandlers.find(upperCommand) != commandHandlers.end();
    }
};

#endif // REQUESTHANDLER_H
