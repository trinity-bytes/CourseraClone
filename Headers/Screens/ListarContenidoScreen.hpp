#ifndef COURSERACLONE_SCREENS_LISTARCONTENIDOSCREEN_HPP
#define COURSERACLONE_SCREENS_LISTARCONTENIDOSCREEN_HPP

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
#include "../Controllers/ContentManager.hpp"
#include "../Controllers/SessionManager.hpp"

/// Pantalla para listar y gestionar cursos y especialidades creados por la organización
class ListarContenidoScreen : public PantallaBase
{
private:
    // Estado de navegación
    AccionPantalla _pantallaAnterior;
    bool _primeraRenderizacion;
    
    // Navegación
    int _contenidoActual;
    int _totalContenidos;
    int _paginaActual;
    int _contenidosPorPagina;
   
    
    std::vector<ContenidoCreado> _contenidos;
    
    // Constantes para la interfaz
    static const int CONTENIDOS_POR_PAGINA = 8;
    static const int ANCHO_ITEM = 110;
    static const int ALTO_ITEM = 1;
    
    // COORDENADAS DE POSICIONAMIENTO
    /// @brief Coordenadas base para el listado
    static const int COL_LISTA_BASE = 5;
    static const int FILA_LISTA_BASE = 10;
    
    /// @brief Coordenadas para cada campo del contenido
    COORD _coordsID = {COL_LISTA_BASE, 0}; // Y será calculado dinámicamente
    COORD _coordsNombre = {COL_LISTA_BASE + 4, 0};
    COORD _coordsTipo = {COL_LISTA_BASE + 44, 0};
    COORD _coordsCategoria = {COL_LISTA_BASE + 62, 0};
    COORD _coordsPrecio = {COL_LISTA_BASE + 81, 0};
    COORD _coordsInscritos = {COL_LISTA_BASE + 94, 0};
    
    /// @brief Coordenadas para elementos de navegación
    COORD _coordsNavegacion = {40, 28};

    // ---- MÉTODOS PRIVADOS ----
    
    /// @brief Métodos de inicialización
    inline void _limpiarEstado();
    inline void _cargarContenidoOrganizacion();
    inline void _cargarContenidoEjemplo(); // Mantener como fallback
    
    /// @brief Métodos de renderizado
    inline void dibujarInterfazCompleta();
    inline void _renderizarListaContenido();
    inline void _renderizarItemContenido(const ContenidoCreado& contenido, int fila, bool seleccionado);
    inline void _renderizarCampo(const COORD& coordBase, int fila, const std::string& texto, int ancho, bool alinearDerecha = false);
    inline void _limpiarAreaItems();
    inline void _renderizarNavegacion();
    
    /// @brief Métodos de navegación
    inline void _navegarArriba();
    inline void _navegarAbajo();
    inline void _cambiarPagina(int direccion);
    
    /// @brief Métodos de utilidad
    inline std::string _formatearPrecio(double precio);
    
public:
    inline ListarContenidoScreen(AccionPantalla pantallaAnterior = AccionPantalla::IR_A_DASHBOARD_ORGANIZACION);
    
    inline ~ListarContenidoScreen() = default;

    inline ResultadoPantalla ejecutar() override;
};

// --- IMPLEMENTACIONES INLINE ---

// Constructor
inline ListarContenidoScreen::ListarContenidoScreen(AccionPantalla pantallaAnterior) : PantallaBase(),
    _pantallaAnterior(pantallaAnterior), _primeraRenderizacion(true), 
    _contenidoActual(0), _totalContenidos(0), _paginaActual(1), _contenidosPorPagina(CONTENIDOS_POR_PAGINA)
{
    _cargarContenidoOrganizacion();
}

// Método principal de ejecución
inline ResultadoPantalla ListarContenidoScreen::ejecutar()
{
    char tecla;
    
    do {
        if (_primeraRenderizacion) {
            dibujarInterfazCompleta();
            _primeraRenderizacion = false;
        }

        _renderizarListaContenido();
        _renderizarNavegacion();
        
        tecla = _getch();
        
        switch (tecla) {
            case 72: // Flecha arriba
                _navegarArriba();
                break;
                
            case 80: // Flecha abajo
                _navegarAbajo();
                break;
                
            case 75: // Flecha izquierda
                _cambiarPagina(-1);
                break;
                
            case 77: // Flecha derecha
                _cambiarPagina(1);
                break;
                
            case 13: // Enter - Navigate to course/specialization
                {
                    if (_contenidoActual >= 0 && _contenidoActual < _contenidos.size()) {
                        const auto& contenidoSeleccionado = _contenidos[_contenidoActual];
                        
                        if (contenidoSeleccionado.esEspecializacion) {
                            // Navegar a MostrarEspecializacion
                            ContentManager::getInstance().setEspecializacionIdMostar(contenidoSeleccionado.id);
                            ResultadoPantalla resultado(AccionPantalla::IR_A_MOSTRAR_ESPECIALIZACION);
                            resultado.idEspecializacionSeleccionada = contenidoSeleccionado.id;
                            resultado.accionAnterior = AccionPantalla::IR_A_LISTAR_CONTENIDO;
                            return resultado;
                        } else {
                            // Navegar a MostrarCurso
                            ContentManager::getInstance().setCursoIdMostrar(contenidoSeleccionado.id);
                            ResultadoPantalla resultado(AccionPantalla::IR_A_MOSTRAR_CURSO);
                            resultado.idCursoSeleccionado = contenidoSeleccionado.id;
                            resultado.accionAnterior = AccionPantalla::IR_A_LISTAR_CONTENIDO;
                            return resultado;
                        }
                    }
                }
                break;
                
            case 27: // ESC
                return ResultadoPantalla(_pantallaAnterior);
        }
        
    } while (true);
    
    return ResultadoPantalla(AccionPantalla::SALIR);
}

// Limpiar estado
inline void ListarContenidoScreen::_limpiarEstado()
{
    _contenidoActual = 0;
    _paginaActual = 1;
}

// Cargar contenido de ejemplo
inline void ListarContenidoScreen::_cargarContenidoEjemplo()
{
    _contenidos = {
        {1, "Introducción a Python", "Curso", "Programación", 89.90, 1247, false},
        {2, "Data Science", "Especialización", "Ciencia de Datos", 299.99, 856, true},
        {3, "JavaScript Moderno", "Curso", "Desarrollo Web", 79.90, 923, false},
        {4, "Machine Learning Avanzado", "Curso", "Inteligencia Artificial", 149.90, 432, false},
        {5, "Full Stack Developer", "Especialización", "Desarrollo Web", 399.99, 567, true},
        {6, "UX/UI Design", "Curso", "Diseño", 99.90, 678, false},
        {7, "Cybersecurity Essentials", "Curso", "Seguridad", 129.90, 345, false},
        {8, "Cloud Computing AWS", "Curso", "Cloud Computing", 179.90, 289, false},
        {9, "DevOps Professional", "Especialización", "DevOps", 349.99, 234, true},
        {10, "Mobile App Development", "Curso", "Desarrollo Móvil", 119.90, 456, false},
        {11, "AI & Deep Learning", "Especialización", "Inteligencia Artificial", 449.99, 189, true},
        {12, "React Native", "Curso", "Desarrollo Móvil", 159.90, 312, false}
    };
    
    _totalContenidos = _contenidos.size();
}

// Cargar contenido específico de la organización actual
inline void ListarContenidoScreen::_cargarContenidoOrganizacion()
{
    _contenidos.clear();
    
    // Verificar si hay sesión activa
    if (!SessionManager::getInstance().isLoggedIn()) {
        _cargarContenidoEjemplo();
        return;
    }
    
    try {
        // Obtener el usuario actual (debe ser una organización)
        Usuario& usuarioActual = SessionManager::getInstance().getCurrentUser();
        
        if (usuarioActual.getTipoUsuario() != TipoUsuario::EMPRESA) {
            _cargarContenidoEjemplo();
            return;
        }
        
        // Obtener el controlador de actividades de la organización
        auto& actividadesController = SessionManager::getInstance().getActividadesController();
        
        // Cargar cursos de la organización
        _contenidos.clear();
        _contenidos = actividadesController.getContenidoCreado();
        
        
        if (_contenidos.empty()) {
            //_cargarContenidoEjemplo();
        } else {
            _totalContenidos = _contenidos.size();
        }
        
    } catch (...) {
        // En caso de cualquier error, usar datos de ejemplo
        _cargarContenidoEjemplo();
    }
}

// Dibujar interfaz completa
inline void ListarContenidoScreen::dibujarInterfazCompleta()
{
    system("cls");
    UI_ListarContenido();
}

// Renderizar lista de contenido
inline void ListarContenidoScreen::_renderizarListaContenido()
{
    int inicioItem = (_paginaActual - 1) * _contenidosPorPagina;
    int finItem = (std::min)(inicioItem + _contenidosPorPagina, (int)_contenidos.size());
    
    for (int i = inicioItem; i < finItem; i++) {
        int fila = FILA_LISTA_BASE + (i - inicioItem) * 2;
        bool seleccionado = (i == _contenidoActual);
        _renderizarItemContenido(_contenidos[i], fila, seleccionado);
    }
}

// Limpiar área de items mostrados
inline void ListarContenidoScreen::_limpiarAreaItems()
{
    // Limpiar solo las filas donde se muestran los items (sin tocar encabezados)
    for (int i = 0; i < CONTENIDOS_POR_PAGINA; i++) {
        int fila = FILA_LISTA_BASE + i * 2;
        gotoXY(COL_LISTA_BASE, fila);
        
        // Limpiar solo el área donde se escriben los datos (ancho específico)
        std::cout << std::string(ANCHO_ITEM, ' ');
    }
}

// Renderizar item individual de contenido
inline void ListarContenidoScreen::_renderizarItemContenido(const ContenidoCreado& contenido, int fila, bool seleccionado)
{
    // Configurar colores según selección
    if (seleccionado) {
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
    } else {
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    }
    
    // Renderizar cada campo en sus coordenadas específicas
    _renderizarCampo(_coordsID, fila, std::to_string(contenido.id), 3, true); // Right-aligned
    _renderizarCampo(_coordsNombre, fila, contenido.nombre, 35, false);
    _renderizarCampo(_coordsTipo, fila, contenido.tipo, 15, false);
    _renderizarCampo(_coordsCategoria, fila, contenido.categoria, 18, false);
    _renderizarCampo(_coordsPrecio, fila, _formatearPrecio(contenido.precio), 12, true); // Right-aligned
    _renderizarCampo(_coordsInscritos, fila, std::to_string(contenido.estudiantesInscritos), 8, true); // Right-aligned
    
    resetColor();
}

// Renderizar un campo individual en coordenadas específicas
inline void ListarContenidoScreen::_renderizarCampo(const COORD& coordBase, int fila, const std::string& texto, int ancho, bool alinearDerecha)
{
    gotoXY(coordBase.X, fila);
    
    // Limpiar el área específica del campo antes de escribir
    std::cout << std::string(ancho, ' ');
    gotoXY(coordBase.X, fila);
    
    std::string textoFormateado = texto.length() > ancho ? texto.substr(0, ancho - 3) + "..." : texto;
    
    if (alinearDerecha) {
        std::cout << std::setw(ancho) << std::right << textoFormateado;
    } else {
        std::cout << std::setw(ancho) << std::left << textoFormateado;
    }
}

// Renderizar navegación
inline void ListarContenidoScreen::_renderizarNavegacion()
{
    int totalPaginas = (_contenidos.size() + _contenidosPorPagina - 1) / _contenidosPorPagina;
    if (totalPaginas == 0) totalPaginas = 1;
    
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    
    gotoXY(_coordsNavegacion.X, _coordsNavegacion.Y);
    std::cout << "< ANTERIOR     [" << _paginaActual << "/" << totalPaginas << "]     SIGUIENTE >";
    
    resetColor();
}

// Navegación arriba
inline void ListarContenidoScreen::_navegarArriba()
{
    if (_contenidoActual > 0) {
        _contenidoActual--;
        
        // Cambiar página si es necesario
        int paginaItem = _contenidoActual / _contenidosPorPagina + 1;
        if (paginaItem != _paginaActual) {
            // Limpiar área de items antes de cambiar de página
            _limpiarAreaItems();
            _paginaActual = paginaItem;
        }
    }
}

// Navegación abajo
inline void ListarContenidoScreen::_navegarAbajo()
{
    if (_contenidoActual < (int)_contenidos.size() - 1) {
        _contenidoActual++;
        
        // Cambiar página si es necesario
        int paginaItem = _contenidoActual / _contenidosPorPagina + 1;
        if (paginaItem != _paginaActual) {
            // Limpiar área de items antes de cambiar de página
            _limpiarAreaItems();
            _paginaActual = paginaItem;
        }
    }
}

// Cambiar página
inline void ListarContenidoScreen::_cambiarPagina(int direccion)
{
    int totalPaginas = (_contenidos.size() + _contenidosPorPagina - 1) / _contenidosPorPagina;
    if (totalPaginas == 0) totalPaginas = 1;
    
    int nuevaPagina = _paginaActual + direccion;
    if (nuevaPagina >= 1 && nuevaPagina <= totalPaginas) {
        // Limpiar área de items antes de cambiar de página
        _limpiarAreaItems();
        
        _paginaActual = nuevaPagina;
        _contenidoActual = (_paginaActual - 1) * _contenidosPorPagina;
        
        // Asegurar que el índice está dentro del rango
        if (_contenidoActual >= (int)_contenidos.size()) {
            _contenidoActual = (std::max)(0, (int)_contenidos.size() - 1);
        }
    }
}

// Formatear precio
inline std::string ListarContenidoScreen::_formatearPrecio(double precio)
{
    std::ostringstream oss;
    oss << "S/ " << std::fixed << std::setprecision(2) << precio;
    return oss.str();
}

#endif // COURSERACLONE_SCREENS_LISTARCONTENIDOSCREEN_HPP
