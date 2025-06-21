// description: Clase para gestionar la sesion del usuario

#ifndef COURSERACLONE_CONTROLLERS_SESSIONMANAGER_HPP
#define COURSERACLONE_CONTROLLERS_SESSIONMANAGER_HPP

#include <memory>
#include <string>

#include "../Entities/Usuario.hpp"
#include "InscripcionesController.hpp"
#include "FilesManager.hpp"


/// @brief Singleton que gestiona la sesión del usuario activo y expone el controlador de inscripciones.
class SessionManager {
private:
    /// @brief Constructor privado para singleton.
    SessionManager();

    static std::unique_ptr<SessionManager> _instance;
    static std::once_flag _onceFlag;  ///< Flag para asegurar la inicialización única.
    std::unique_ptr<Usuario> _currentUser;                    /// Usuario en sesión.
    std::unique_ptr<InscripcionesController> _inscripcionesCtrl;  /// Controlador de inscripciones.

    // Utilidades privadas
    void logOperation(const std::string& operation, const std::string& details);
    void logError(const std::string& operation, const std::string& error);


public:
    /**
     * @brief Obtiene la instancia global de SessionManager.
     * @return Referencia única al SessionManager.
     */
    static SessionManager& getInstance();

    SessionManager(const SessionManager&) = delete;
    SessionManager& operator=(const SessionManager&) = delete;

    ~SessionManager() = default;

    /**
     * @brief Intenta iniciar sesión con las credenciales proporcionadas.
     * @param username Nombre de usuario o correo.
     * @param password Contraseña en texto plano.
     * @param tipoUsuario Tipo de usuario (e.g., Estudiante, Profesor).
     * @return true si las credenciales son válidas y se inicia sesión; false en caso contrario.
     */
    LoginStatus login(const std::string& username, const std::string& password, TipoUsuario tipoUsuario);

    LoginStatus update(const std::string& nombre, const std::string email, const std::string password);

	/**
	 * @brief Inicializa el sistema de archivos y carga los datos necesarios.
	 * @return true si la inicialización fue exitosa; false en caso contrario.
	 */
    bool inicializarSistema();

    /**
     * @brief Cierra la sesión del usuario actual y resetea el estado interno.
     */
    void logout();

    /**
     * @brief Comprueba si existe un usuario logueado.
     * @return true si hay un usuario en sesión; false en caso contrario.
     */
    bool isLoggedIn();

    /**
     * @brief Obtiene el usuario actualmente logueado.
     * @return Referencia al objeto Usuario.
     * @note Precondición: isLoggedIn() debe ser true.
     */
    Usuario& getCurrentUser();

    /**
     * @brief Obtiene el controlador de inscripciones del usuario activo.
     * @return Referencia al InscripcionesController.
     * @note Precondición: isLoggedIn() debe ser true.
     */
    InscripcionesController& getInscripcionesController();

    
};

// ========== IMPLEMENTACIONES INLINE ==========
inline std::unique_ptr<SessionManager> SessionManager::_instance = nullptr;
inline std::once_flag SessionManager::_onceFlag;

inline SessionManager& SessionManager::getInstance() {
	std::call_once(_onceFlag, []() {
		_instance.reset(new SessionManager());
		});

    return *_instance;
}

inline SessionManager::SessionManager() {
    logOperation("Constructor", "SessionManager inicializado (Singleton)");
    inicializarSistema();
}

inline LoginStatus SessionManager::login(const std::string& username, const std::string& password, TipoUsuario tipoUsuario) {
    // Buscar posición en índice de usuario
    int offset = FilesManager::getInstance().buscarIndexUsuario(username, static_cast<int>(tipoUsuario));
    if (offset == -1) {
        return LoginStatus::USER_NOT_FOUND;
    }

    // Crear y cargar datos del usuario
    auto userPtr = std::make_unique<Usuario>(offset, tipoUsuario);
	Usuario provisionalUser;
	provisionalUser.setContrasena(password);
    // Verificar contraseña (hash)
    if (userPtr->getContrasenaHash() != provisionalUser.getContrasenaHash()) {
        return LoginStatus::WRONG_PASSWORD;
    }

    // Mantener sesión activa
    _currentUser = std::move(userPtr);
    _inscripcionesCtrl = std::make_unique<InscripcionesController>(_currentUser->getId());
    return LoginStatus::SUCCESS;
}

inline LoginStatus SessionManager::update(const std::string& nombre, const std::string email, const std::string password) {
    if (!isLoggedIn()) {
        logError("Update User", "No hay usuario activo para actualizar");
        return LoginStatus::USER_NOT_FOUND;
    }
    // Actualizar los datos del usuario actual
    _currentUser->setUsername(email);
    _currentUser->setNombreCompleto(nombre);
    _currentUser->setContrasena(password);

    // Se actualiza el usuario en el sistema de archivos
    FilesManager::getInstance().updateUsuarioBinario(_currentUser->toUsuarioBinario());
    // Se elimina el anterior indice
    FilesManager::getInstance().eliminarIndiceUsuario(_currentUser->getUsername(), _currentUser->getTipoUsuario());
    // Se crea un nuevo indice con los datos actualizados
    FilesManager::getInstance().guardarIndiceUsuario(_currentUser->toUsuarioIndex(), _currentUser->getTipoUsuario());

    logOperation("Update User", "Usuario actualizado exitosamente");
    return LoginStatus::SUCCESS;
}

inline bool SessionManager::inicializarSistema() {
	FilesManager& fileManager = FilesManager::getInstance();
	if (!fileManager.inicializarSistemaArchivos()) {
		logError("Inicialización del sistema", "Error al inicializar el sistema de archivos");
		return false;
	}

    return true;
}

inline void SessionManager::logout() {
	if (!isLoggedIn()) {
		logError("Cierre de Sesion", "No hay ningun usuario activo para cerrar sesion");
		return;
	}
    _inscripcionesCtrl.reset();
    _currentUser.reset();
    logOperation("Cierre de Sesion", "Exitoso");
}

inline bool SessionManager::isLoggedIn() {
	// Verifica si hay un usuario activo en sesión
	if (_currentUser == nullptr) {
        logOperation("Verificacion de usuario Activo", "No hay ningun usuario activo");
		return false;
	}

	// Si el usuario es válido, retorna true
	logOperation("Verificacion de usuario Activo", "Usuario activo");
    return true;
}

inline Usuario& SessionManager::getCurrentUser() {
    return *_currentUser;
}

inline InscripcionesController& SessionManager::getInscripcionesController() {
    return *_inscripcionesCtrl;
}

// ========== MÉTODOS PRIVADOS - LOGGING ==========
inline void SessionManager::logError(const std::string& operation, const std::string& error) {
    // Implementación simple para logging de errores
    FilesManager& fileManager = FilesManager::getInstance();
    fileManager.logError(operation, "SessionManager", error);
}


inline void SessionManager::logOperation(const std::string& operation, const std::string& details) {
    // Implementación simple para logging de operaciones
    // En un proyecto más complejo esto iría a un archivo de log
    FilesManager& fileManager = FilesManager::getInstance();
    fileManager.logInfo(operation, "SessionManager");
}

#endif