#ifndef COURSERACLONE_SCREENS_EDITARPERFILSCREEN_HPP
#define COURSERACLONE_SCREENS_EDITARPERFILSCREEN_HPP

// Headers de librería estándar
#include <iostream>
#include <string>
#include <conio.h>

// Headers propios
#include "../Utils/SystemUtils.hpp"
#include "../Utils/ScreenSystem.hpp"
#include "../Utils/UI_Ascii.hpp"
#include "../Types/UsuarioTypes.hpp"

/// Pantalla para editar perfil de usuario
class EditarPerfilScreen : public PantallaBase
{
private:
    /// @brief Constantes para campos de entrada
    static const int CAMPO_NOMBRE = 0;
    static const int CAMPO_EMAIL = 1;
    static const int CAMPO_PASSWORD = 2;
    static const int CAMPO_CONFIRMAR_PASSWORD = 3;
    static const int CAMPO_GUARDAR = 4;    
    static const int TOTAL_CAMPOS = 5;

    /// @brief Datos del usuario
    int idUsuario;
    TipoUsuario tipoUsuario;
    std::string nombreOriginal;
    std::string emailOriginal;
    std::string passwordOriginal;

    /// @brief Datos modificables
    std::string nombre;
    std::string email;
    std::string password;
    std::string confirmarPassword;

    /// @brief Estado actual
    int campoActual;
    int campoAnterior;
    bool primeraRenderizacion;
    bool error;
    std::string mensajeError;    
    
    /// @brief Coordenadas para dibujar
    const COORD coordsCampos[TOTAL_CAMPOS] = {
        {26, 11}, // Nombre
        {26, 15}, // Email
        {26, 19}, // Password
        {26, 23}, // Confirmar Password
        {51, 27}  // Botón Guardar
    };
    
    // ---- MÉTODOS PRIVADOS ----
    
    /// @brief Métodos de inicialización
    inline void _limpiarEstado();
    inline void _cargarDatosDummy();

    /// @brief Métodos de renderizado
    inline void dibujarInterfazCompleta();
    inline void _renderizarCampo(const std::string& valor, int indice, bool seleccionado);
    inline void renderizarBotonGuardar(bool seleccionado);
    inline void actualizarSeleccion();

    /// @brief Métodos de navegación y entrada
    inline void _manejarNavegacion(int tecla);
    inline void _manejarEntradaTexto(int tecla);
    inline void _manejarRetroceso();

    /// @brief Métodos de validación y guardado
    inline bool validarCampos();
    inline void _mostrarError(const std::string& mensaje);
    inline void guardarCambios();
    inline ResultadoPantalla _procesarGuardado();

public:
    inline EditarPerfilScreen();
    inline EditarPerfilScreen(AccionPantalla pantallaAnterior);
    
    inline ResultadoPantalla ejecutar() override;
};

// --- IMPLEMENTACIONES INLINE ---

// Constructor por defecto
inline EditarPerfilScreen::EditarPerfilScreen() : PantallaBase(),
    idUsuario(1), tipoUsuario(TipoUsuario::ESTUDIANTE),
    nombreOriginal(""), emailOriginal(""), passwordOriginal(""),
    campoActual(0), campoAnterior(-1), primeraRenderizacion(true), error(false)
{
    _cargarDatosDummy();
}

// Constructor con pantalla anterior
inline EditarPerfilScreen::EditarPerfilScreen(AccionPantalla pantallaAnterior) : PantallaBase(),
    idUsuario(1), tipoUsuario(TipoUsuario::ESTUDIANTE),
    nombreOriginal(""), emailOriginal(""), passwordOriginal(""),
    campoActual(0), campoAnterior(-1), primeraRenderizacion(true), error(false)
{
    _cargarDatosDummy();
    // Podemos usar pantallaAnterior para regresar dinámicamente
}

// Limpiar estado
inline void EditarPerfilScreen::_limpiarEstado()
{
    campoActual = 0;
    campoAnterior = -1;
    primeraRenderizacion = true;
    error = false;
    mensajeError.clear();
}

// Cargar datos de ejemplo
inline void EditarPerfilScreen::_cargarDatosDummy()
{
    // Cargar datos actuales para edición
    nombre = nombreOriginal;
    email = emailOriginal;
    password = ""; // Por seguridad, no prellenar password
    confirmarPassword = "";
}

// Dibujar interfaz completa
inline void EditarPerfilScreen::dibujarInterfazCompleta()
{
    system("cls");
    UI_UserUpdateData();

    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);

    // Renderizar campos de entrada
    _renderizarCampo(nombre, CAMPO_NOMBRE, campoActual == CAMPO_NOMBRE);
    _renderizarCampo(email, CAMPO_EMAIL, campoActual == CAMPO_EMAIL);
    _renderizarCampo(password, CAMPO_PASSWORD, campoActual == CAMPO_PASSWORD);
    _renderizarCampo(confirmarPassword, CAMPO_CONFIRMAR_PASSWORD, campoActual == CAMPO_CONFIRMAR_PASSWORD);

    // Renderizar botón guardar
    renderizarBotonGuardar(campoActual == CAMPO_GUARDAR);

    resetColor();
}

// Renderizar campo de entrada
inline void EditarPerfilScreen::_renderizarCampo(const std::string& valor, int indice, bool seleccionado)
{
    gotoXY(coordsCampos[indice].X, coordsCampos[indice].Y);

    if (seleccionado)
    {
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::BORDES_SUTILES);
        _configurarCursor(true);
    }
    else {
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        _configurarCursor(false);
    }

    // Mostrar el valor con padding para limpiar caracteres residuales
    std::string display = valor;
    display.resize(66, ' '); // Asegurar que el campo tenga tamaño fijo
    std::cout << display;

    // Posicionar cursor al final del texto real
    if (seleccionado) 
    {
        gotoXY(coordsCampos[indice].X + valor.length(), coordsCampos[indice].Y);
    }

    resetColor();
}

// Renderizar botón guardar
inline void EditarPerfilScreen::renderizarBotonGuardar(bool seleccionado)
{
    _configurarCursor(false);
    gotoXY(coordsCampos[CAMPO_GUARDAR].X, coordsCampos[CAMPO_GUARDAR].Y);
    
    if (seleccionado) {
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::HOVER_ESTADO);
    } else {
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    }
    
    std::cout << " GUARDAR CAMBIOS ";
    resetColor();
}

// Actualizar selección
inline void EditarPerfilScreen::actualizarSeleccion()
{
    if (campoAnterior != campoActual)
    {
        // Actualizar campo anterior
        if (campoAnterior >= 0)
        {
            if (campoAnterior == CAMPO_GUARDAR) {
                renderizarBotonGuardar(false);
            } else {
                std::string* valor = nullptr;
                switch (campoAnterior)
                {
                case CAMPO_NOMBRE: valor = &nombre; break;
                case CAMPO_EMAIL: valor = &email; break;
                case CAMPO_PASSWORD: valor = &password; break;
                case CAMPO_CONFIRMAR_PASSWORD: valor = &confirmarPassword; break;
                }
                if (valor != nullptr) {
                    _renderizarCampo(*valor, campoAnterior, false);
                }
            }
        }

        // Actualizar campo actual
        if (campoActual == CAMPO_GUARDAR) {
            renderizarBotonGuardar(true);
        } else {
            std::string* valor = nullptr;
            switch (campoActual)
            {
            case CAMPO_NOMBRE: valor = &nombre; break;
            case CAMPO_EMAIL: valor = &email; break;
            case CAMPO_PASSWORD: valor = &password; break;
            case CAMPO_CONFIRMAR_PASSWORD: valor = &confirmarPassword; break;
            }
            if (valor != nullptr) {
                _renderizarCampo(*valor, campoActual, true);
            }
        }

        campoAnterior = campoActual;
    }
}

// Manejar navegación
inline void EditarPerfilScreen::_manejarNavegacion(int tecla)
{
    switch (tecla) {
    case 72: // Flecha arriba
        campoActual = (campoActual > 0) ? campoActual - 1 : TOTAL_CAMPOS - 1;
        break;
    case 80: // Flecha abajo
        campoActual = (campoActual < TOTAL_CAMPOS - 1) ? campoActual + 1 : 0;
        break;
    }
}

// Manejar entrada de texto
inline void EditarPerfilScreen::_manejarEntradaTexto(int tecla)
{
    // Solo procesar entrada de texto si estamos en un campo de entrada (no en el botón)
    if (campoActual < CAMPO_GUARDAR && tecla >= 32 && tecla <= 126)
    {
        std::string* campoActivo = nullptr;
        switch (campoActual)
        {
        case CAMPO_NOMBRE: campoActivo = &nombre; break;
        case CAMPO_EMAIL: campoActivo = &email; break;
        case CAMPO_PASSWORD: campoActivo = &password; break;
        case CAMPO_CONFIRMAR_PASSWORD: campoActivo = &confirmarPassword; break;
        }

        if (campoActivo != nullptr && campoActivo->length() < 48)
        {
            *campoActivo += static_cast<char>(tecla);
            _renderizarCampo(*campoActivo, campoActual, true);
        }
    }
}

// Manejar retroceso
inline void EditarPerfilScreen::_manejarRetroceso()
{
    if (campoActual < CAMPO_GUARDAR)
    {
        std::string* campoActivo = nullptr;
        switch (campoActual)
        {
        case CAMPO_NOMBRE: campoActivo = &nombre; break;
        case CAMPO_EMAIL: campoActivo = &email; break;
        case CAMPO_PASSWORD: campoActivo = &password; break;
        case CAMPO_CONFIRMAR_PASSWORD: campoActivo = &confirmarPassword; break;
        }

        if (campoActivo != nullptr && !campoActivo->empty())
        {
            campoActivo->pop_back();
            _renderizarCampo(*campoActivo, campoActual, true);
        }
    }
}

// Mostrar error
inline void EditarPerfilScreen::_mostrarError(const std::string& mensaje)
{
    gotoXY(25, 30);
    setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::ERROR_COLOR);
    std::cout << "[ERROR]: " << mensaje;
    resetColor();

    // Pausa para mostrar el error
    _getch();

    // Limpia el mensaje de error
    gotoXY(25, 30);
    for (int i = 0; i < mensaje.length() + 9; ++i)
    {
        std::cout << " ";
    }
}

// Validar campos
inline bool EditarPerfilScreen::validarCampos()
{
    if (nombre.empty())
    {
        _mostrarError("El nombre es obligatorio");
        return false;
    }
    
    if (email.empty())
    {
        _mostrarError("El email es obligatorio");
        return false;
    }

    // Solo validar password si se está cambiando
    if (!password.empty())
    {
        if (password.length() < 6)
        {
            _mostrarError("La contraseña debe tener al menos 6 caracteres");
            return false;
        }
        
        if (password != confirmarPassword)
        {
            _mostrarError("Las contraseñas no coinciden");
            return false;
        }
    }

    return true;
}

// Guardar cambios (dummy)
inline void EditarPerfilScreen::guardarCambios()
{
    SessionManager::getInstance().update(nombre, email, password);
    
    gotoXY(25, 30);
    setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::EXITO_COLOR);
    std::cout << "[ÉXITO]: Perfil actualizado correctamente";
    resetColor();
    _configurarCursor(false);
    
    // Pausa para mostrar el mensaje
    _getch();
}

// Procesar guardado
inline ResultadoPantalla EditarPerfilScreen::_procesarGuardado()
{
    if (!validarCampos())
    {
        return ResultadoPantalla(AccionPantalla::NINGUNA);
    }

    guardarCambios();
    
    // Determinar a dónde regresar según el tipo de usuario
    if (tipoUsuario == TipoUsuario::ESTUDIANTE)
    {
        return ResultadoPantalla(AccionPantalla::IR_A_PERFIL_ESTUDIANTE);
    }
    else
    {
        return ResultadoPantalla(AccionPantalla::IR_A_PERFIL_ORGANIZACION);
    }
}

// Método principal de ejecución
inline ResultadoPantalla EditarPerfilScreen::ejecutar()
{
    _limpiarEstado();
    
    if (primeraRenderizacion)
    {
        dibujarInterfazCompleta();
        primeraRenderizacion = false;
    }

    while (true)
    {
        actualizarSeleccion();

        int tecla = _getch();

        // Verificar si es una tecla especial
        if (tecla == 224 || tecla == 0)
        {
            int codigoExtendido = _getch();
            _manejarNavegacion(codigoExtendido);
        }
        else
        {
            switch (tecla)
            {
            case 13: // Enter
                if (campoActual == CAMPO_GUARDAR)
                {
                    ResultadoPantalla resultado = _procesarGuardado();
                    if (resultado.accion != AccionPantalla::NINGUNA)
                    {
                        return resultado;
                    }
                }
                break;

            case 8: // Backspace
                _manejarRetroceso();
                break;

            case 27: // ESC - Regresar sin guardar
                _configurarCursor(false);
                // Regresar según el tipo de usuario
                if (tipoUsuario == TipoUsuario::ESTUDIANTE)
                {
                    return ResultadoPantalla(AccionPantalla::IR_A_PERFIL_ESTUDIANTE);
                }
                else
                {
                    return ResultadoPantalla(AccionPantalla::IR_A_PERFIL_ORGANIZACION);
                }

            default:
                _manejarEntradaTexto(tecla);
                break;
            }
        }
    }
}

#endif // COURSERACLONE_SCREENS_EDITARPERFILSCREEN_HPP
