#ifndef COURSERACLONE_SCREENS_CREARCONTENIDOSCREEN_HPP
#define COURSERACLONE_SCREENS_CREARCONTENIDOSCREEN_HPP

// Headers estándar
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <conio.h>
#include <limits>

// Headers propios
#include "../Utils/SystemUtils.hpp"
#include "../Utils/ScreenSystem.hpp"
#include "../Utils/UI_Ascii.hpp"
#include "../Utils/InputUtils.hpp"
#include "../Utils/ValidationUtils.hpp"
#include "../Types/UsuarioTypes.hpp"
#include "../Types/ActividadTypes.hpp"
#include "../Entities/Curso.hpp"
#include "../Entities/Especializacion.hpp"

/// Pantalla para crear nuevo contenido (cursos y especializaciones)
class CrearContenidoScreen : public PantallaBase
{
private:
    // CONSTANTES DE CONFIGURACIÓN
    /// @brief Límites de elementos navegables
    static const int MAX_OPCIONES_MENU = 2;
    static const int ELEMENTOS_INPUT = 4; // Título, Descripción, Precio, Duración
    static const int TOTAL_ELEMENTOS = ELEMENTOS_INPUT + MAX_OPCIONES_MENU; // Total navegables
    
    // COORDENADAS DE POSICIONAMIENTO
    /// @brief Posiciones para las opciones del menú
    const COORD _coordsOpcionesMenu[MAX_OPCIONES_MENU] = {
        {33, 26}, // Crear Curso
        {57, 26}  // Crear Especialización
    };
    
    /// @brief Coordenadas para los campos de entrada
    const COORD _coordsElementosInput[ELEMENTOS_INPUT] = {
        {8, 12},   // Título/Nombre del Contenido
        {8, 16},  // Descripción detallada
        {8, 21},  // Precio (S/)
        {31, 21}  // Duración (horas)
    };
    
    /// @brief Posiciones fijas de interfaz
    static const int COL_TITULO = 40;
    static const int FILA_TITULO = 4;
    static const int COL_FORMULARIO = 20;
    static const int FILA_FORMULARIO = 8;
    
    // DATOS ESTÁTICOS DE LA INTERFAZ
    /// @brief Elementos del menú principal
    const std::vector<std::string> _opcionesMenu = {
        " CREAR NUEVO CURSO ",
        " CREAR NUEVA ESPECIALIZACION "
    };
    
    // ESTADO DE NAVEGACIÓN
    /// @brief Estado actual de la navegación
    AccionPantalla _pantallaAnterior;
    bool _primeraRenderizacion;
    
    /// @brief Estado de navegación unificado
    int _elementoActual; // 0-3: campos, 4-5: botones
    int _elementoAnterior;
    
    /// @brief Datos del formulario (opcionales)
    std::string _titulo;
    std::string _descripcion;
    std::string _precio;
    std::string _duracion;
    
    // Opciones del menú principal
    enum class OpcionMenu {
        CREAR_CURSO = 0,
        CREAR_ESPECIALIZACION = 1
    };
    
    // ---- MÉTODOS PRIVADOS ----
    
    /// @brief Métodos de inicialización
    inline void _limpiarEstado();
    
    /// @brief Métodos de renderizado
    inline void dibujarInterfazCompleta();
    inline void _renderizarCamposYBotones();
    inline void _renderizarCampo(const std::string& valor, int indice, bool seleccionado);
    inline void _renderizarBoton(int indice, bool seleccionado);
    inline void _actualizarElemento(int elemento, bool seleccionado);
    inline void _actualizarSeleccion();
    
    /// @brief Métodos de navegación
    inline void _manejarNavegacion(int tecla);
    inline void _manejarEntradaTexto(int tecla);
    inline void _manejarRetroceso();
    
    /// @brief Métodos de utilidad
    inline bool _esBoton(int elemento);
    inline int _obtenerIndiceBoton(int elemento);
    inline std::string* _obtenerCampoActivo(int elemento);
    inline int _obtenerMaxLength(int indiceCampo);
    
    /// @brief Métodos de procesamiento
    inline ResultadoPantalla _procesarSeleccion();
    inline void _crearCursoConDatos();
    inline void _crearEspecializacionConDatos();
    inline void _limpiarCampos();
    
    /// @brief Métodos de formularios
    inline std::string _solicitarTexto(const std::string& prompt, int maxLength = 100);
    inline int _solicitarNumero(const std::string& prompt, int min = 1, int max = 999);
    inline double _solicitarDecimal(const std::string& prompt, double min = 0.01, double max = 9999.99);
    inline CategoriaActividad _seleccionarCategoria();
    inline std::vector<std::pair<std::string, std::string>> _solicitarClases(int cantidadClases);
    
    /// @brief Métodos de utilidad
    inline void _mostrarMensaje(const std::string& mensaje);
    inline std::string _categoriaNombre(CategoriaActividad categoria);

public:
    inline CrearContenidoScreen(AccionPantalla pantallaAnterior = AccionPantalla::IR_A_DASHBOARD_ORGANIZACION);
    
    inline ~CrearContenidoScreen() = default;

    inline ResultadoPantalla ejecutar() override;
};

// --- IMPLEMENTACIONES INLINE ---

// Constructor
inline CrearContenidoScreen::CrearContenidoScreen(AccionPantalla pantallaAnterior) : PantallaBase(),
    _pantallaAnterior(pantallaAnterior), _primeraRenderizacion(true), 
    _elementoActual(0), _elementoAnterior(-1)
{
}

// Limpiar estado
inline void CrearContenidoScreen::_limpiarEstado()
{
    _elementoActual = 0;
    _elementoAnterior = -1; // Importante: -1 para forzar actualización en primera llamada
    _primeraRenderizacion = true;
    _limpiarCampos();
}

// Dibujar interfaz completa
inline void CrearContenidoScreen::dibujarInterfazCompleta()
{
    system("cls");
    UI_CrearContenido();
    
    _renderizarCamposYBotones();
    
    resetColor();
}

// Renderizar campos y botones
inline void CrearContenidoScreen::_renderizarCamposYBotones()
{
    // Renderizar todos los campos
    for (int i = 0; i < ELEMENTOS_INPUT; ++i) {
        std::string* valor = _obtenerCampoActivo(i);
        if (valor != nullptr) {
            _renderizarCampo(*valor, i, i == _elementoActual);
        }
    }
    
    // Renderizar todos los botones
    for (int i = 0; i < MAX_OPCIONES_MENU; ++i) {
        int elementoBoton = ELEMENTOS_INPUT + i;
        _renderizarBoton(i, elementoBoton == _elementoActual);
    }
    
    resetColor();
}

// Renderizar botón individual
inline void CrearContenidoScreen::_renderizarBoton(int indice, bool seleccionado)
{
    if (indice >= MAX_OPCIONES_MENU) return;
    
    const COORD& coord = _coordsOpcionesMenu[indice];
    gotoXY(coord.X, coord.Y);
    
    if (seleccionado) {
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
    } else {
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    }
    
    std::cout << _opcionesMenu[indice];
    resetColor();
}

// Actualizar elemento individual
inline void CrearContenidoScreen::_actualizarElemento(int elemento, bool seleccionado)
{
    if (_esBoton(elemento)) {
        int indiceBoton = _obtenerIndiceBoton(elemento);
        _renderizarBoton(indiceBoton, seleccionado);
    } else if (elemento < ELEMENTOS_INPUT) {
        std::string* valor = _obtenerCampoActivo(elemento);
        if (valor != nullptr) {
            _renderizarCampo(*valor, elemento, seleccionado);
        }
    }
}

// Actualizar selección
inline void CrearContenidoScreen::_actualizarSeleccion()
{
    // Solo actualizar si hay cambio de selección
    if (_elementoAnterior != _elementoActual)
    {
        // Actualizar elemento anterior
        if (_elementoAnterior >= 0 && _elementoAnterior < TOTAL_ELEMENTOS)
        {
            _actualizarElemento(_elementoAnterior, false);
        }

        // Actualizar elemento actual
        if (_elementoActual >= 0 && _elementoActual < TOTAL_ELEMENTOS)
        {
            _actualizarElemento(_elementoActual, true);
        }

        _elementoAnterior = _elementoActual;
    }
}

// Manejar navegación
inline void CrearContenidoScreen::_manejarNavegacion(int tecla)
{
    switch (tecla) {
    case 72: // Flecha arriba
        _elementoActual = (_elementoActual > 0) ? _elementoActual - 1 : TOTAL_ELEMENTOS - 1;
        break;
    case 80: // Flecha abajo
        _elementoActual = (_elementoActual < TOTAL_ELEMENTOS - 1) ? _elementoActual + 1 : 0;
        break;
    case 75: // Flecha izquierda (para navegar entre precio y duración)
        if (_elementoActual == 3) _elementoActual = 2; // De duración a precio
        break;
    case 77: // Flecha derecha (para navegar entre precio y duración)
        if (_elementoActual == 2) _elementoActual = 3; // De precio a duración
        break;
    }
}

// Procesar selección
inline ResultadoPantalla CrearContenidoScreen::_procesarSeleccion()
{
    ResultadoPantalla res;
    
    if (_esBoton(_elementoActual)) {
        int indiceBoton = _obtenerIndiceBoton(_elementoActual);
        
        switch (static_cast<OpcionMenu>(indiceBoton)) {
        case OpcionMenu::CREAR_CURSO:
            _crearCursoConDatos();
            _primeraRenderizacion = true;
            break;
            
        case OpcionMenu::CREAR_ESPECIALIZACION:
            _crearEspecializacionConDatos();
            _primeraRenderizacion = true;
            break;
        }
    }
    
    return res;
}

// Mostrar mensaje
inline void CrearContenidoScreen::_mostrarMensaje(const std::string& mensaje)
{
    gotoXY(COL_FORMULARIO, 20);
    setConsoleColor(ColorIndex::ERROR_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << mensaje;
    resetColor();
}

// Renderizar campo de entrada
inline void CrearContenidoScreen::_renderizarCampo(const std::string& valor, int indice, bool seleccionado)
{
    if (indice >= ELEMENTOS_INPUT) return;
    
    gotoXY(_coordsElementosInput[indice].X, _coordsElementosInput[indice].Y);

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
    int maxLength = _obtenerMaxLength(indice);
    
    display.resize(maxLength, ' ');
    std::cout << display;

    // Posicionar cursor al final del texto real si está seleccionado
    if (seleccionado) 
    {
        gotoXY(_coordsElementosInput[indice].X + valor.length(), _coordsElementosInput[indice].Y);
    }

    resetColor();
}

// Manejar entrada de texto
inline void CrearContenidoScreen::_manejarEntradaTexto(int tecla)
{
    // Solo procesar entrada de texto si estamos en un campo de entrada
    if (_elementoActual < ELEMENTOS_INPUT && tecla >= 32 && tecla <= 126)
    {
        std::string* campoActivo = _obtenerCampoActivo(_elementoActual);
        int maxLength = _obtenerMaxLength(_elementoActual);

        if (campoActivo != nullptr && campoActivo->length() < maxLength)
        {
            *campoActivo += static_cast<char>(tecla);
            _renderizarCampo(*campoActivo, _elementoActual, true);
        }
    }
}

// Manejar retroceso
inline void CrearContenidoScreen::_manejarRetroceso()
{
    if (_elementoActual < ELEMENTOS_INPUT)
    {
        std::string* campoActivo = _obtenerCampoActivo(_elementoActual);

        if (campoActivo != nullptr && !campoActivo->empty())
        {
            campoActivo->pop_back();
            _renderizarCampo(*campoActivo, _elementoActual, true);
        }
    }
}

// Verificar si un elemento es un botón
inline bool CrearContenidoScreen::_esBoton(int elemento)
{
    return elemento >= ELEMENTOS_INPUT && elemento < TOTAL_ELEMENTOS;
}

// Obtener índice de botón
inline int CrearContenidoScreen::_obtenerIndiceBoton(int elemento)
{
    return elemento - ELEMENTOS_INPUT;
}

// Obtener campo activo
inline std::string* CrearContenidoScreen::_obtenerCampoActivo(int elemento)
{
    switch (elemento)
    {
    case 0: return &_titulo;
    case 1: return &_descripcion;
    case 2: return &_precio;
    case 3: return &_duracion;
    default: return nullptr;
    }
}

// Obtener longitud máxima del campo
inline int CrearContenidoScreen::_obtenerMaxLength(int indiceCampo)
{
    switch (indiceCampo)
    {
    case 0: return 104; // Título
    case 1: return 104; // Descripción
    case 2: return 17; // Precio
    case 3: return 22; // Duración
    default: return 50;
    }
}

// Crear curso con datos opcionales
inline void CrearContenidoScreen::_crearCursoConDatos()
{
    system("cls");
    
    // Título del formulario
    gotoXY(COL_FORMULARIO, 3);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "=== CREANDO NUEVO CURSO ===";
    resetColor();
    
    try {
        // Usar datos del formulario si están disponibles, sino usar valores por defecto
        std::string titulo = _titulo.empty() ? "Curso de Programación" : _titulo;
        std::string descripcion = _descripcion.empty() ? "Curso completo de programación" : _descripcion;
        
        // Datos simulados para la empresa
        int idEmpresa = 1;
        std::string nombreEmpresa = "Tech Education Corp";
        int idCurso = rand() % 10000 + 1000; // ID simulado
        
        // Mostrar confirmación
        gotoXY(COL_FORMULARIO, 8);
        setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "CURSO CREADO EXITOSAMENTE";
        
        gotoXY(COL_FORMULARIO, 10);
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "Título: " << titulo;
        
        gotoXY(COL_FORMULARIO, 11);
        std::cout << "Descripción: " << descripcion;
        
        if (!_precio.empty()) {
            gotoXY(COL_FORMULARIO, 12);
            std::cout << "Precio: S/ " << _precio;
        }
        
        if (!_duracion.empty()) {
            gotoXY(COL_FORMULARIO, 13);
            std::cout << "Duración: " << _duracion << " horas";
        }
        
        gotoXY(COL_FORMULARIO, 15);
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "ID del curso: " << idCurso;
        
        gotoXY(COL_FORMULARIO, 18);
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
        std::cout << " Presiona cualquier tecla para continuar ";
        resetColor();
        
        _getch();
        
    } catch (...) {
        _mostrarMensaje("Error al crear el curso");
        _getch();
    }
}

// Crear especialización con datos opcionales
inline void CrearContenidoScreen::_crearEspecializacionConDatos()
{
    system("cls");
    
    // Título del formulario
    gotoXY(COL_FORMULARIO, 3);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "=== CREANDO NUEVA ESPECIALIZACIÓN ===";
    resetColor();
    
    try {
        // Usar datos del formulario si están disponibles, sino usar valores por defecto
        std::string titulo = _titulo.empty() ? "Especialización en Tecnología" : _titulo;
        std::string descripcion = _descripcion.empty() ? "Especialización completa en tecnología" : _descripcion;
        
        // Datos simulados para la empresa
        int idEmpresa = 1;
        std::string nombreEmpresa = "Tech Education Corp";
        int idEspecializacion = rand() % 10000 + 2000; // ID simulado
        
        // Mostrar confirmación
        gotoXY(COL_FORMULARIO, 8);
        setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "ESPECIALIZACION CREADA EXITOSAMENTE";
        
        gotoXY(COL_FORMULARIO, 10);
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "Título: " << titulo;
        
        gotoXY(COL_FORMULARIO, 11);
        std::cout << "Descripción: " << descripcion;
        
        if (!_precio.empty()) {
            gotoXY(COL_FORMULARIO, 12);
            std::cout << "Precio: S/ " << _precio;
        }
        
        if (!_duracion.empty()) {
            gotoXY(COL_FORMULARIO, 13);
            std::cout << "Duración estimada: " << _duracion << " semanas";
        }
        
        gotoXY(COL_FORMULARIO, 15);
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "ID de la especialización: " << idEspecializacion;
        
        gotoXY(COL_FORMULARIO, 18);
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
        std::cout << " Presiona cualquier tecla para continuar ";
        resetColor();
        
        _getch();
        
    } catch (...) {
        _mostrarMensaje("Error al crear la especialización");
        _getch();
    }
}

// Limpiar campos
inline void CrearContenidoScreen::_limpiarCampos()
{
    _titulo.clear();
    _descripcion.clear();
    _precio.clear();
    _duracion.clear();
}

// Obtener nombre de categoría
inline std::string CrearContenidoScreen::_categoriaNombre(CategoriaActividad categoria)
{
    switch (categoria) {
    case CategoriaActividad::PROGRAMACION: return "Programación";
    case CategoriaActividad::DESARROLLO_WEB: return "Desarrollo Web";
    case CategoriaActividad::CIENCIA_DE_DATOS: return "Ciencia de Datos";
    case CategoriaActividad::INTELIGENCIA_ARTIFICIAL: return "Inteligencia Artificial";
    case CategoriaActividad::DISENO: return "Diseño";
    case CategoriaActividad::MARKETING_DIGITAL: return "Marketing Digital";
    case CategoriaActividad::NEGOCIOS: return "Negocios";
    default: return "Desconocida";
    }
}

// Método principal de ejecución
inline ResultadoPantalla CrearContenidoScreen::ejecutar()
{
    _limpiarEstado();
    
    if (_primeraRenderizacion) {
        dibujarInterfazCompleta();
        _primeraRenderizacion = false;
    }
    
    while (true) {
        _actualizarSeleccion();
        
        int tecla = _getch();
        
        switch (tecla) {
        case 0:
        case 224: // Teclas especiales
        {
            int segundaTecla = _getch();
            _manejarNavegacion(segundaTecla);
        }
        break;
        
        case 72: // Flecha arriba (por si acaso)
        case 75: // Flecha izquierda
        case 77: // Flecha derecha  
        case 80: // Flecha abajo (por si acaso)
            _manejarNavegacion(tecla);
            break;
            
        case 13: // Enter - Procesar selección
        {
            ResultadoPantalla res = _procesarSeleccion();
            if (res.accion != AccionPantalla::NINGUNA) {
                return res;
            }
        }
        break;
        
        case 8: // Backspace
            _manejarRetroceso();
            break;
        
        case 27: // ESC - Volver a pantalla anterior
        {
            ResultadoPantalla res;
            res.accion = _pantallaAnterior;
            return res;
        }
        break;
        
        default:
            // Manejar entrada de texto
            _manejarEntradaTexto(tecla);
            break;
        }
    }
}

#endif // COURSERACLONE_SCREENS_CREARCONTENIDOSCREEN_HPP
