// filepath: Headers/Screens/EditProfileScreen.h
// Descripción: Define la pantalla para que los usuarios (estudiantes u organizaciones)
//              puedan editar su información de perfil, incluyendo nombre, email y contraseña.
// Autor: [Nombre del desarrollador]
// Fecha: [Fecha de creación]
// Última modificación: [Fecha y descripción del cambio]

#pragma once

// Headers propios - Refactorizados según la guía de estilo
#include "../Screens/ScreenBase.h"          // Renombrado PantallaBase a ScreenBase
#include "../Entities/ScreenResult.h"       // Incluido ScreenResult.h (anteriormente PantallaResultado.h)
#include "../Utils/ConsoleUtils.h"          // Renombrado ExtendedFunctions.h a ConsoleUtils.h
#include "../Utils/AsciiUI.h"               // Asumiendo UI_Ascii.h será AsciiUI.h
#include "../Entities/User.h"               // Renombrado Usuario.h a User.h
#include "../Entities/Student.h"            // Renombrado Estudiante.h a Student.h
#include "../Entities/Organization.h"       // Renombrado Empresa.h a Organization.h
#include "../Utils/AppConstants.h"          // Para UserType

// Headers de la librería estándar
#include <string>     // Para std::string
#include <iostream>   // Para std::cout
#include <conio.h>    // Para _getch()
#include <windows.h>  // Para COORD y funciones de cursor de consola

/**
 * @brief Clase que representa la pantalla de edición de perfil para usuarios.
 * Permite a estudiantes y organizaciones modificar su nombre, email y contraseña.
 */
class EditProfileScreen : public ScreenBase { // Renombrado EditarPerfil a EditProfileScreen, PantallaBase a ScreenBase
private:
    // Constantes para identificar los campos de entrada y botones
    static constexpr int _FIELD_NAME = 0;              ///< Índice del campo para el nombre. // Renombrado CAMPO_NOMBRE, static constexpr
    static constexpr int _FIELD_EMAIL = 1;             ///< Índice del campo para el email. // Renombrado CAMPO_EMAIL
    static constexpr int _FIELD_PASSWORD = 2;          ///< Índice del campo para la contraseña. // Renombrado CAMPO_PASSWORD
    static constexpr int _FIELD_CONFIRM_PASSWORD = 3;  ///< Índice del campo para confirmar la contraseña. // Renombrado CAMPO_CONFIRMAR_PASSWORD
    static constexpr int _FIELD_SAVE = 4;              ///< Índice del botón para guardar cambios. // Renombrado CAMPO_GUARDAR
    static constexpr int _TOTAL_FIELDS = 5;            ///< Número total de campos navegables (incluyendo el botón de guardar). // Renombrado TOTAL_CAMPOS

    // Datos del usuario
    int _userId;            ///< ID único del usuario actual. // Renombrado idUsuario a _userId
    AppConstants::UserType _userType; ///< Tipo de usuario (ESTUDIANTE o EMPRESA). // Renombrado tipoUsuario a _userType, AppConstants::UserType
    std::string _originalName;      ///< Nombre original del usuario al cargar la pantalla. // Renombrado nombreOriginal a _originalName
    std::string _originalEmail;     ///< Email original del usuario al cargar la pantalla. // Renombrado emailOriginal a _originalEmail
    // std::string _originalPassword; ///< Contraseña original del usuario (no utilizada para validación aquí). // Renombrado passwordOriginal a _originalPassword

    // Datos modificables por el usuario
    std::string _name;          ///< Nombre actual en el campo de entrada. // Renombrado nombre a _name
    std::string _email;         ///< Email actual en el campo de entrada. // Renombrado email a _email
    std::string _password;      ///< Contraseña actual en el campo de entrada. // Renombrado password a _password
    std::string _confirmPassword; ///< Confirmación de contraseña actual en el campo de entrada. // Renombrado confirmarPassword a _confirmPassword

    // Estado de la interfaz
    int _currentField;       ///< Índice del campo actualmente seleccionado. // Renombrado campoActual a _currentField
    int _previousField;      ///< Índice del campo previamente seleccionado, para refresco parcial. // Renombrado campoAnterior a _previousField
    bool _firstRender;       ///< Bandera para controlar la primera renderización completa de la interfaz. // Renombrado primeraRenderizacion a _firstRender
    bool _hasError;          ///< Bandera que indica si hay un error de validación. // Renombrado error a _hasError
    std::string _errorMessage; ///< Mensaje de error a mostrar al usuario. // Renombrado mensajeError a _errorMessage

    // Coordenadas para dibujar los campos de entrada
    const COORD _fieldCoords[_TOTAL_FIELDS] = { // Renombrado coordsCampos a _fieldCoords
        {11, 15}, // Nombre
        {11, 20}, // Email
        {11, 25}, // Password
        {63, 25}, // Confirmar Password
        {52, 29}  // Botón Guardar
    };

    // Referencias a los objetos de usuario para actualizar sus datos
    Student& _student;     ///< Referencia al objeto Student si el usuario es un estudiante. // Renombrado estudiante a _student
    Organization& _organization; ///< Referencia al objeto Organization si el usuario es una organización. // Renombrado empresa a _organization

    /**
     * @brief Dibuja la interfaz completa de la pantalla de edición de perfil.
     * Limpia la consola y renderiza todos los campos y el botón de guardar.
     * También muestra el mensaje de error si existe.
     * @complexity O(1) + O(Número de campos)
     */
    void drawFullInterface() { // Renombrado dibujarInterfazCompleta
        ConsoleUtils::clearConsole(); // Reemplazado system("cls")
        AsciiUI::drawUserUpdateDataScreen(); // Asumiendo una función de dibujo general en AsciiUI.h

        // Mostrar valores actuales en los campos
        renderField(_FIELD_NAME, _name, _currentField == _FIELD_NAME); // Usar _FIELD_NAME, _name
        renderField(_FIELD_EMAIL, _email, _currentField == _FIELD_EMAIL); // Usar _FIELD_EMAIL, _email
        renderField(_FIELD_PASSWORD, std::string(_password.length(), '*'), _currentField == _FIELD_PASSWORD); // Usar _FIELD_PASSWORD, _password
        renderField(_FIELD_CONFIRM_PASSWORD, std::string(_confirmPassword.length(), '*'), _currentField == _FIELD_CONFIRM_PASSWORD); // Usar _FIELD_CONFIRM_PASSWORD, _confirmPassword
        renderSaveButton(_currentField == _FIELD_SAVE); // Usar _FIELD_SAVE

        // Mostrar mensaje de error si lo hay
        if (_hasError) { // Usar _hasError
            ConsoleUtils::setCursorPosition(_fieldCoords[_FIELD_SAVE].X - 10, _fieldCoords[_FIELD_SAVE].Y + 2); // Ajuste de coordenadas
            ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::RED_TEXT, AppConstants::ConsoleColors::BACKGROUND); // Color para error
            std::cout << _errorMessage; // Usar _errorMessage
            ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::BACKGROUND); // Resetear color
        }
    }

    /**
     * @brief Renderiza un campo de entrada específico, aplicando el color de selección si es necesario.
     * @param _fieldIndex El índice del campo a renderizar.
     * @param _value El valor de tipo std::string a mostrar en el campo.
     * @param _isSelected Verdadero si el campo está seleccionado, falso en caso contrario.
     * @complexity O(1)
     */
    void renderField(int _fieldIndex, const std::string& _value, bool _isSelected) { // Renombrado renderizarCampo, parámetros
        ConsoleUtils::setCursorPosition(_fieldCoords[_fieldIndex].X, _fieldCoords[_fieldIndex].Y); // Usar ConsoleUtils::setCursorPosition

        // Limpiar el área del campo (importante para nombres largos o backspace)
        if (_fieldIndex == _FIELD_NAME) { // Solo para el campo de nombre, ya que los demás son de longitud fija o enmascarados
            std::cout << std::string(60, ' '); // Limpiar un área grande para el nombre
            ConsoleUtils::setCursorPosition(_fieldCoords[_fieldIndex].X, _fieldCoords[_fieldIndex].Y);
        } else if (_fieldIndex == _FIELD_EMAIL) {
            std::cout << std::string(40, ' '); // Limpiar un área para el email
            ConsoleUtils::setCursorPosition(_fieldCoords[_fieldIndex].X, _fieldCoords[_fieldIndex].Y);
        } else if (_fieldIndex == _FIELD_PASSWORD || _fieldIndex == _FIELD_CONFIRM_PASSWORD) {
            std::cout << std::string(20, ' '); // Limpiar un área para las contraseñas
            ConsoleUtils::setCursorPosition(_fieldCoords[_fieldIndex].X, _fieldCoords[_fieldIndex].Y);
        }

        if (_isSelected) {
            ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::PURE_WHITE, AppConstants::ConsoleColors::DARK_BLUE); // Color para selección
            ConsoleUtils::showConsoleCursor(true); // Mostrar cursor si está seleccionado
        } else {
            ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::BACKGROUND); // Color normal
            ConsoleUtils::showConsoleCursor(false); // Ocultar cursor si no está seleccionado
        }

        std::cout << _value;
        ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::BACKGROUND); // Resetear color
    }

    /**
     * @brief Renderiza el botón "GUARDAR CAMBIOS", aplicando el color de selección si es necesario.
     * @param _isSelected Verdadero si el botón está seleccionado, falso en caso contrario.
     * @complexity O(1)
     */
    void renderSaveButton(bool _isSelected) { // Renombrado renderizarBotonGuardar, parámetro
        ConsoleUtils::setCursorPosition(_fieldCoords[_FIELD_SAVE].X, _fieldCoords[_FIELD_SAVE].Y); // Usar ConsoleUtils::setCursorPosition

        if (_isSelected) {
            ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::PURE_WHITE, AppConstants::ConsoleColors::DARK_BLUE); // Color para selección
        } else {
            ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::BACKGROUND); // Color normal
        }

        std::cout << "GUARDAR CAMBIOS";
        ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::BACKGROUND); // Resetear color
    }

    /**
     * @brief Actualiza la visualización de la selección de campos en la interfaz.
     * Solo vuelve a renderizar los campos afectados por el cambio de selección.
     * @complexity O(1)
     */
    void updateSelection() { // Renombrado actualizarSeleccion
        if (_previousField >= 0 && _previousField < _TOTAL_FIELDS) {
            if (_previousField == _FIELD_SAVE) {
                renderSaveButton(false); // Des-seleccionar botón anterior
            } else {
                std::string value;
                switch (_previousField) {
                case _FIELD_NAME: value = _name; break;
                case _FIELD_EMAIL: value = _email; break;
                case _FIELD_PASSWORD: value = std::string(_password.length(), '*'); break;
                case _FIELD_CONFIRM_PASSWORD: value = std::string(_confirmPassword.length(), '*'); break;
                }
                renderField(_previousField, value, false); // Des-seleccionar campo anterior
            }
        }

        if (_currentField >= 0 && _currentField < _TOTAL_FIELDS) {
            if (_currentField == _FIELD_SAVE) {
                renderSaveButton(true); // Seleccionar botón actual
            } else {
                std::string value;
                switch (_currentField) {
                case _FIELD_NAME: value = _name; break;
                case _FIELD_EMAIL: value = _email; break;
                case _FIELD_PASSWORD: value = std::string(_password.length(), '*'); break;
                case _FIELD_CONFIRM_PASSWORD: value = std::string(_confirmPassword.length(), '*'); break;
                }
                renderField(_currentField, value, true); // Seleccionar campo actual
            }
        }
        _previousField = _currentField; // Actualizar campo anterior
    }

    /**
     * @brief Valida los campos de entrada del formulario.
     * Verifica que los campos obligatorios no estén vacíos, que las contraseñas coincidan,
     * la longitud mínima de la contraseña y si el email ya está en uso.
     * @return Verdadero si todos los campos son válidos, falso en caso contrario.
     * @complexity O(1) (asumiendo que User::searchUserByEmail es eficiente)
     */
    bool validateFields() { // Renombrado validarCampos
        _hasError = false; // Resetear estado de error
        _errorMessage = "";

        // Validar que los campos de nombre y email no están vacíos
        if (_name.empty() || _email.empty()) {
            _hasError = true;
            _errorMessage = "El nombre y el email son obligatorios.";
            return false;
        }

        // Validar que las contraseñas coincidan si se están modificando
        // Solo si la contraseña no está vacía (indicando que el usuario quiere cambiarla)
        if (!_password.empty() && _password != _confirmPassword) {
            _hasError = true;
            _errorMessage = "Las contraseñas no coinciden.";
            return false;
        }

        // Validar longitud mínima de contraseña si se está modificando
        if (!_password.empty() && _password.length() < AppConstants::MIN_PASSWORD_LENGTH) { // Usar MIN_PASSWORD_LENGTH de AppConstants
            _hasError = true;
            _errorMessage = "La contraseña debe tener al menos " + std::to_string(AppConstants::MIN_PASSWORD_LENGTH) + " caracteres.";
            return false;
        }

        // Validar formato de email (simple, solo presencia de '@')
        if (_email.find('@') == std::string::npos) {
            _hasError = true;
            _errorMessage = "Formato de email inválido (debe contener '@').";
            return false;
        }

        // Validar que el email no está ya en uso por otro usuario
        if (_email != _originalEmail) { // Solo si el email ha cambiado
            User tempUser; // Este objeto User podría representar un "User Repository" o "UserManager"
            // Asumiendo que User::searchUserByEmail(email, userType) es un método estático o una función global
            // o un método de un UserManager pasado como dependencia.
            // La implementación actual de Usuario::buscarIndexUsuario implica que carga y busca.
            // Idealmente, se debería usar un UserManager.
            int index = tempUser.searchUserIndexByEmail(_email, _userType); // Renombrado buscarIndexUsuario a searchUserIndexByEmail
            if (index != -1 && index != _userId) { // Si el email está en uso por otro ID de usuario
                _hasError = true;
                _errorMessage = "Este email ya está en uso por otro usuario.";
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Guarda los cambios realizados en el perfil del usuario.
     * Actualiza el objeto Student o Organization con la nueva información.
     * @complexity O(1)
     */
    void saveChanges() { // Renombrado guardarCambios
        // Las referencias _student y _organization apuntan al objeto real en memoria
        // (presumiblemente cargado en un controlador superior).
        // Llamar a updateInformation() en esos objetos persistirá los cambios.
        if (_userType == AppConstants::UserType::STUDENT) { // Usar AppConstants::UserType::STUDENT
            _student.updateInformation(_name, _email, _password); // Renombrado updateInfo a updateInformation
        } else if (_userType == AppConstants::UserType::ORGANIZATION) { // Usar AppConstants::UserType::ORGANIZATION
            _organization.updateInformation(_name, _email, _password); // Renombrado updateInfo a updateInformation
        }
    }

public:
    /**
     * @brief Constructor de la clase EditProfileScreen.
     * Inicializa la pantalla con los datos del usuario actual.
     * @param _userId El ID del usuario cuyo perfil se va a editar.
     * @param _userType El tipo de usuario (Estudiante o Empresa).
     * @param _name El nombre actual del usuario.
     * @param _email El email actual del usuario.
     * @param _student_ref Referencia al objeto Student (se usa si _userType es ESTUDIANTE).
     * @param _organization_ref Referencia al objeto Organization (se usa si _userType es EMPRESA).
     */
    EditProfileScreen(int _userId, AppConstants::UserType _userType, std::string _name, std::string _email,
                      Student& _student_ref, Organization& _organization_ref)
        : _userId(_userId),
        _userType(_userType),
        _originalName(_name),
        _originalEmail(_email),
        _name(_name),
        _email(_email),
        _password(""), // La contraseña no se carga, se edita o se deja vacía para no cambiar
        _confirmPassword(""),
        _currentField(0),
        _previousField(-1),
        _firstRender(true),
        _hasError(false),
        _student(_student_ref),
        _organization(_organization_ref) {
    }

    /**
     * @brief Implementación del método virtual para ejecutar la pantalla de edición de perfil.
     * Gestiona la entrada del usuario, la navegación entre campos, la validación y el guardado.
     * @return ScreenResult El resultado de la interacción, indicando la siguiente acción/pantalla.
     * @complexity Bucle que se ejecuta hasta que el usuario decida salir o guardar cambios.
     */
    ScreenResult run() override { // Renombrado ejecutar a run, tipo de retorno ScreenResult
        ScreenResult result; // Renombrado res a result

        while (true) {
            if (_firstRender) {
                drawFullInterface(); // Dibujar la interfaz completa por primera vez
                _firstRender = false;
                ConsoleUtils::showConsoleCursor(true); // Mostrar cursor para la edición
            } else {
                updateSelection(); // Actualizar solo la selección y el cursor
            }

            int key = _getch(); // Renombrado tecla a key
            switch (key) {
            case 224: // Tecla extendida (flechas, etc.)
                key = _getch(); // Obtener el código de la tecla extendida
                switch (key) {
                case 72: // Flecha arriba
                    if (_currentField > 0) {
                        // Lógica de navegación especial para saltar entre campos no adyacentes visualmente
                        if (_currentField == _FIELD_SAVE) {
                            _currentField = _FIELD_CONFIRM_PASSWORD;
                        } else if (_currentField == _FIELD_PASSWORD || _currentField == _FIELD_CONFIRM_PASSWORD) {
                            _currentField = _FIELD_EMAIL;
                        } else {
                            _currentField--;
                        }
                    }
                    break;

                case 80: // Flecha abajo
                    if (_currentField < _TOTAL_FIELDS - 1) {
                        // Lógica de navegación especial
                        if (_currentField == _FIELD_EMAIL) {
                            _currentField = _FIELD_PASSWORD;
                        } else if (_currentField == _FIELD_PASSWORD || _currentField == _FIELD_CONFIRM_PASSWORD) {
                            _currentField = _FIELD_SAVE;
                        } else {
                            _currentField++;
                        }
                    }
                    break;

                case 75: // Flecha izquierda
                    if (_currentField == _FIELD_CONFIRM_PASSWORD) {
                        _currentField = _FIELD_PASSWORD;
                    }
                    break;

                case 77: // Flecha derecha
                    if (_currentField == _FIELD_PASSWORD) {
                        _currentField = _FIELD_CONFIRM_PASSWORD;
                    }
                    break;
                }
                break;

            case 13: // Enter
                if (_currentField == _FIELD_SAVE) {
                    if (validateFields()) { // Renombrado validarCampos
                        saveChanges(); // Renombrado guardarCambios
                        ConsoleUtils::showConsoleCursor(false); // Ocultar cursor al salir
                        // Redirigir al perfil correspondiente según el tipo de usuario
                        result.action = (_userType == AppConstants::UserType::STUDENT) ?
                                        ScreenAction::GO_TO_STUDENT_PROFILE : // Usar ScreenAction y GO_TO_STUDENT_PROFILE
                                        ScreenAction::GO_TO_ORGANIZATION_PROFILE; // Usar ScreenAction y GO_TO_ORGANIZATION_PROFILE
                        return result;
                    } else {
                        // Si hay error, volver a dibujar la interfaz para mostrar el mensaje
                        drawFullInterface();
                    }
                }
                break;

            case 27: { // ESC
                ConsoleUtils::showConsoleCursor(false); // Ocultar cursor al salir
                // Volver al perfil correspondiente sin guardar cambios
                result.action = (_userType == AppConstants::UserType::STUDENT) ?
                                ScreenAction::GO_TO_STUDENT_PROFILE :
                                ScreenAction::GO_TO_ORGANIZATION_PROFILE;
                return result;
            }

            case 9: // Tab
                _currentField = (_currentField + 1) % _TOTAL_FIELDS;
                break;

            case 8: // Backspace
                if (_currentField >= 0 && _currentField < _FIELD_SAVE) {
                    std::string* currentInputString = nullptr;
                    switch (_currentField) {
                    case _FIELD_NAME: currentInputString = &_name; break;
                    case _FIELD_EMAIL: currentInputString = &_email; break;
                    case _FIELD_PASSWORD: currentInputString = &_password; break;
                    case _FIELD_CONFIRM_PASSWORD: currentInputString = &_confirmPassword; break;
                    }
                    if (currentInputString && !currentInputString->empty()) {
                        currentInputString->pop_back();
                        drawFullInterface(); // Redibujar para mostrar el cambio
                    }
                }
                break;

            default:
                if (key >= 32 && key <= 126) { // Caracteres imprimibles (ASCII)
                    std::string* currentInputString = nullptr;
                    switch (_currentField) {
                    case _FIELD_NAME: currentInputString = &_name; break;
                    case _FIELD_EMAIL: currentInputString = &_email; break;
                    case _FIELD_PASSWORD: currentInputString = &_password; break;
                    case _FIELD_CONFIRM_PASSWORD: currentInputString = &_confirmPassword; break;
                    }
                    if (currentInputString) {
                        currentInputString->push_back(static_cast<char>(key));
                        drawFullInterface(); // Redibujar para mostrar el nuevo carácter
                    }
                }
                break;
            }
            _hasError = false; // Limpiar el estado de error después de procesar la entrada
        }
    }
};