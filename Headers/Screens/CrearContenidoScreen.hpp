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
    // Estado de navegación
    AccionPantalla _pantallaAnterior;
    bool _primeraRenderizacion;
    
    // Navegación y selección
    int _opcionSeleccionada;
    
    // Constantes para la interfaz
    static const int COL_TITULO = 40;
    static const int FILA_TITULO = 4;
    static const int COL_VOLVER = 100;
    static const int FILA_VOLVER = 4;
    
    static const int COL_MENU = 30;
    static const int FILA_MENU = 10;
    static const int ESPACIO_ENTRE_OPCIONES = 2;
    
    static const int COL_FORMULARIO = 20;
    static const int FILA_FORMULARIO = 8;
    
    // Opciones del menú principal
    enum class OpcionMenu {
        CREAR_CURSO = 0,
        CREAR_ESPECIALIZACION = 1,
        VOLVER = 2
    };
    
    // ---- MÉTODOS PRIVADOS ----
    
    /// @brief Métodos de inicialización
    inline void _limpiarEstado();
    
    /// @brief Métodos de renderizado
    inline void dibujarInterfazCompleta();
    inline void _renderizarTitulo();
    inline void _renderizarBotonVolver();
    inline void _renderizarMenuPrincipal();
    inline void _actualizarSeleccion();
    
    /// @brief Métodos de navegación
    inline void _manejarNavegacion(int tecla);
    inline void _navegarArriba();
    inline void _navegarAbajo();
    
    /// @brief Métodos de procesamiento
    inline ResultadoPantalla _procesarSeleccion();
    inline void _crearCurso();
    inline void _crearEspecializacion();
    
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
    _pantallaAnterior(pantallaAnterior), _primeraRenderizacion(true), _opcionSeleccionada(0)
{
}

// Limpiar estado
inline void CrearContenidoScreen::_limpiarEstado()
{
    _opcionSeleccionada = 0;
    _primeraRenderizacion = true;
}

// Dibujar interfaz completa
inline void CrearContenidoScreen::dibujarInterfazCompleta()
{
    system("cls");
    UI_CrearContenido();
    
    _renderizarTitulo();
    _renderizarBotonVolver();
    _renderizarMenuPrincipal();
    
    resetColor();
}

// Renderizar título
inline void CrearContenidoScreen::_renderizarTitulo()
{
    gotoXY(COL_TITULO, FILA_TITULO);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "CREAR CONTENIDO EDUCATIVO";
    resetColor();
}

// Renderizar botón volver
inline void CrearContenidoScreen::_renderizarBotonVolver()
{
    gotoXY(COL_VOLVER, FILA_VOLVER);
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "[ ESC - VOLVER ]";
    resetColor();
}

// Renderizar menú principal
inline void CrearContenidoScreen::_renderizarMenuPrincipal()
{
    std::vector<std::string> opciones = {
        "Crear Nuevo Curso",
        "Crear Nueva Especializacion", 
        "Volver al Dashboard"
    };
    
    for (size_t i = 0; i < opciones.size(); ++i) {
        int fila = FILA_MENU + i * ESPACIO_ENTRE_OPCIONES;
        
        // Determinar colores según selección
        if (i == _opcionSeleccionada) {
            setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
        } else {
            setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        }
        
        gotoXY(COL_MENU, fila);
        std::cout << "  " << opciones[i] << "  ";
        resetColor();
    }
    
    // Instrucciones de uso
    gotoXY(COL_MENU, FILA_MENU + opciones.size() * ESPACIO_ENTRE_OPCIONES + 2);
    setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "ENTER - Seleccionar | ↑↓ - Navegar | ESC - Volver";
    resetColor();
}

// Actualizar selección
inline void CrearContenidoScreen::_actualizarSeleccion()
{
    _renderizarMenuPrincipal();
}

// Manejar navegación
inline void CrearContenidoScreen::_manejarNavegacion(int tecla)
{
    switch (tecla) {
    case 72: // Flecha arriba
        _navegarArriba();
        break;
    case 80: // Flecha abajo
        _navegarAbajo();
        break;
    }
}

// Navegar hacia arriba
inline void CrearContenidoScreen::_navegarArriba()
{
    if (_opcionSeleccionada > 0) {
        _opcionSeleccionada--;
    } else {
        _opcionSeleccionada = 2; // Última opción
    }
}

// Navegar hacia abajo
inline void CrearContenidoScreen::_navegarAbajo()
{
    if (_opcionSeleccionada < 2) {
        _opcionSeleccionada++;
    } else {
        _opcionSeleccionada = 0; // Primera opción
    }
}

// Procesar selección
inline ResultadoPantalla CrearContenidoScreen::_procesarSeleccion()
{
    ResultadoPantalla res;
    
    switch (static_cast<OpcionMenu>(_opcionSeleccionada)) {
    case OpcionMenu::CREAR_CURSO:
        _crearCurso();
        _primeraRenderizacion = true;
        break;
        
    case OpcionMenu::CREAR_ESPECIALIZACION:
        _crearEspecializacion();
        _primeraRenderizacion = true;
        break;
        
    case OpcionMenu::VOLVER:
        res.accion = _pantallaAnterior;
        break;
    }
    
    return res;
}

// Crear curso
inline void CrearContenidoScreen::_crearCurso()
{
    system("cls");
    
    // Título del formulario
    gotoXY(COL_FORMULARIO, 3);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "=== CREAR NUEVO CURSO ===";
    resetColor();
    
    try {
        // Solicitar datos del curso
        std::string titulo = _solicitarTexto("Título del curso:", 80);
        if (titulo.empty()) return;
        
        std::string descripcion = _solicitarTexto("Descripción del curso:", 200);
        if (descripcion.empty()) return;
        
        std::string instructor = _solicitarTexto("Nombre del instructor:", 50);
        if (instructor.empty()) return;
        
        int cantidadClases = _solicitarNumero("Cantidad de clases:", 1, 50);
        
        CategoriaActividad categoria = _seleccionarCategoria();
        
        // Solicitar información de las clases
        std::vector<std::pair<std::string, std::string>> clases = _solicitarClases(cantidadClases);
        
        // Datos simulados para la empresa (en la implementación real vendrían del usuario logueado)
        int idEmpresa = 1;
        std::string nombreEmpresa = "Tech Education Corp";
        int idCurso = rand() % 10000 + 1000; // ID simulado
        
        // Crear el curso
        Curso nuevoCurso(
            idCurso,
            idEmpresa,
            nombreEmpresa,
            categoria,
            titulo,
            descripcion,
            instructor,
            cantidadClases,
            clases
        );
        
        // Mostrar confirmación
        system("cls");
        gotoXY(COL_FORMULARIO, 8);
        setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "CURSO CREADO EXITOSAMENTE";
        
        gotoXY(COL_FORMULARIO, 10);
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "Título: " << titulo;
        
        gotoXY(COL_FORMULARIO, 11);
        std::cout << "Instructor: " << instructor;
        
        gotoXY(COL_FORMULARIO, 12);
        std::cout << "Clases: " << cantidadClases;
        
        gotoXY(COL_FORMULARIO, 13);
        std::cout << "Categoría: " << _categoriaNombre(categoria);
        
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

// Crear especialización
inline void CrearContenidoScreen::_crearEspecializacion()
{
    system("cls");
    
    // Título del formulario
    gotoXY(COL_FORMULARIO, 3);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "=== CREAR NUEVA ESPECIALIZACIÓN ===";
    resetColor();
    
    try {
        // Solicitar datos de la especialización
        std::string titulo = _solicitarTexto("Título de la especialización:", 80);
        if (titulo.empty()) return;
        
        std::string descripcion = _solicitarTexto("Descripción de la especialización:", 200);
        if (descripcion.empty()) return;
        
        int duracionEstimada = _solicitarNumero("Duración estimada (semanas):", 1, 52);
        
        CategoriaActividad categoria = _seleccionarCategoria();
        
        // IDs de cursos simulados (en la implementación real se seleccionarían cursos existentes)
        std::vector<int> idsCursos = {1001, 1002, 1003}; // Ejemplo
        
        // Datos simulados para la empresa
        int idEmpresa = 1;
        std::string nombreEmpresa = "Tech Education Corp";
        int idEspecializacion = rand() % 10000 + 2000; // ID simulado
        
        // Crear la especialización
        Especializacion nuevaEspecializacion(
            idEspecializacion,
            idEmpresa,
            nombreEmpresa,
            categoria,
            titulo,
            descripcion,
            idsCursos,
            duracionEstimada
        );
        
        // Mostrar confirmación
        system("cls");
        gotoXY(COL_FORMULARIO, 8);
        setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "ESPECIALIZACION CREADA EXITOSAMENTE";
        
        gotoXY(COL_FORMULARIO, 10);
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "Título: " << titulo;
        
        gotoXY(COL_FORMULARIO, 11);
        std::cout << "Duración: " << duracionEstimada << " semanas";
        
        gotoXY(COL_FORMULARIO, 12);
        std::cout << "Cursos incluidos: " << idsCursos.size();
        
        gotoXY(COL_FORMULARIO, 13);
        std::cout << "Categoría: " << _categoriaNombre(categoria);
        
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

// Solicitar texto
inline std::string CrearContenidoScreen::_solicitarTexto(const std::string& prompt, int maxLength)
{
    static int fila = 6;
    fila += 2;
    
    gotoXY(COL_FORMULARIO, fila);
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << prompt;
    
    gotoXY(COL_FORMULARIO, fila + 1);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "> ";
    resetColor();
    
    std::string input;
    std::getline(std::cin, input);
    
    if (input.length() > maxLength) {
        input = input.substr(0, maxLength);
    }
    
    return input;
}

// Solicitar número
inline int CrearContenidoScreen::_solicitarNumero(const std::string& prompt, int min, int max)
{
    static int fila = 6;
    fila += 2;
    
    while (true) {
        gotoXY(COL_FORMULARIO, fila);
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << prompt << " (" << min << "-" << max << ")";
        
        gotoXY(COL_FORMULARIO, fila + 1);
        setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "> ";
        resetColor();
        
        int numero;
        if (std::cin >> numero && numero >= min && numero <= max) {
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            return numero;
        }
        
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        
        gotoXY(COL_FORMULARIO, fila + 2);
        setConsoleColor(ColorIndex::ERROR_COLOR, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "Número inválido. Presiona Enter para reintentar.";
        resetColor();
        _getch();
        
        // Limpiar las líneas
        gotoXY(COL_FORMULARIO, fila + 2);
        std::cout << "                                                ";
    }
}

// Seleccionar categoría
inline CategoriaActividad CrearContenidoScreen::_seleccionarCategoria()
{
    static int fila = 6;
    fila += 3;
    
    std::vector<std::pair<CategoriaActividad, std::string>> categorias = {
        {CategoriaActividad::PROGRAMACION, "Programación"},
        {CategoriaActividad::DESARROLLO_WEB, "Desarrollo Web"},
        {CategoriaActividad::CIENCIA_DE_DATOS, "Ciencia de Datos"},
        {CategoriaActividad::INTELIGENCIA_ARTIFICIAL, "Inteligencia Artificial"},
        {CategoriaActividad::DISENO, "Diseño"},
        {CategoriaActividad::MARKETING_DIGITAL, "Marketing Digital"},
        {CategoriaActividad::NEGOCIOS, "Negocios"}
    };
    
    int seleccion = 0;
    
    while (true) {
        gotoXY(COL_FORMULARIO, fila);
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "Selecciona una categoría:";
        
        for (size_t i = 0; i < categorias.size(); ++i) {
            gotoXY(COL_FORMULARIO + 2, fila + 2 + i);
            
            if (i == seleccion) {
                setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
                std::cout << "► " << categorias[i].second;
            } else {
                setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
                std::cout << "  " << categorias[i].second;
            }
            resetColor();
        }
        
        gotoXY(COL_FORMULARIO, fila + categorias.size() + 4);
        setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "↑↓ - Navegar | ENTER - Seleccionar";
        resetColor();
        
        int tecla = _getch();
        
        if (tecla == 0 || tecla == 224) {
            tecla = _getch();
            
            if (tecla == 72 && seleccion > 0) { // Flecha arriba
                seleccion--;
            } else if (tecla == 80 && seleccion < categorias.size() - 1) { // Flecha abajo
                seleccion++;
            }
        } else if (tecla == 13) { // Enter
            return categorias[seleccion].first;
        }
    }
}

// Solicitar clases
inline std::vector<std::pair<std::string, std::string>> CrearContenidoScreen::_solicitarClases(int cantidadClases)
{
    std::vector<std::pair<std::string, std::string>> clases;
    
    system("cls");
    gotoXY(COL_FORMULARIO, 3);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "=== INFORMACIÓN DE LAS CLASES ===";
    resetColor();
    
    for (int i = 0; i < cantidadClases; ++i) {
        gotoXY(COL_FORMULARIO, 6 + i * 4);
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "Clase " << (i + 1) << ":";
        
        gotoXY(COL_FORMULARIO, 7 + i * 4);
        std::cout << "Título: ";
        setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "> ";
        resetColor();
        
        std::string titulo;
        std::getline(std::cin, titulo);
        
        gotoXY(COL_FORMULARIO, 8 + i * 4);
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "Descripción: ";
        setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "> ";
        resetColor();
        
        std::string descripcion;
        std::getline(std::cin, descripcion);
        
        clases.push_back({titulo, descripcion});
    }
    
    return clases;
}

// Mostrar mensaje
inline void CrearContenidoScreen::_mostrarMensaje(const std::string& mensaje)
{
    gotoXY(COL_FORMULARIO, 20);
    setConsoleColor(ColorIndex::ERROR_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << mensaje;
    resetColor();
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
    
    while (true) {
        if (_primeraRenderizacion) {
            dibujarInterfazCompleta();
            _primeraRenderizacion = false;
        } else {
            _actualizarSeleccion();
        }
        
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
        
        case 27: // ESC - Volver a pantalla anterior
        {
            ResultadoPantalla res;
            res.accion = _pantallaAnterior;
            return res;
        }
        
        default:
            // Ignorar otras teclas
            break;
        }
    }
}

#endif // COURSERACLONE_SCREENS_CREARCONTENIDOSCREEN_HPP
