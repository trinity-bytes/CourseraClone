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

/// Pantalla para listar y gestionar cursos y especialidades creados por la organización
class ListarContenidoScreen : public PantallaBase
{
private:
    // Estado de navegación
    AccionPantalla _pantallaAnterior;
    bool _primeraRenderizacion;
    
    // Navegación y filtros
    int _contenidoActual;
    int _totalContenidos;
    int _paginaActual;
    int _contenidosPorPagina;
    std::string _filtroTipo; // "TODOS", "CURSOS", "ESPECIALIDADES"
    std::string _filtroEstado; // "TODOS", "ACTIVOS", "INACTIVOS"
    
    // Estructura de datos para contenido
    struct ContenidoCreado {
        int id;
        std::string nombre;
        std::string tipo; // "Curso" o "Especialización"
        std::string categoria;
        std::string fechaCreacion;
        std::string fechaUltimaModificacion;
        double precio;
        int duracionHoras;
        int estudiantesInscritos;
        std::string estado; // "Activo", "Inactivo", "Borrador"
        double calificacionPromedio;
        int totalReseñas;
        bool esEspecializacion;
        std::vector<std::string> cursosIncluidos; // Solo para especializaciones
    };
    
    std::vector<ContenidoCreado> _contenidos;
    std::vector<ContenidoCreado> _contenidosFiltrados;
    
    // Constantes para la interfaz
    static const int CONTENIDOS_POR_PAGINA = 8;
    static const int COL_LISTA = 5;
    static const int FILA_LISTA = 10;
    static const int ANCHO_ITEM = 110;
    static const int ALTO_ITEM = 3;
    
    static const int COL_FILTROS = 90;
    static const int FILA_FILTROS = 6;
    
    static const int COL_NAVEGACION = 40;
    static const int FILA_NAVEGACION = 27;
    
    // ---- MÉTODOS PRIVADOS ----
    
    /// @brief Métodos de inicialización
    inline void _limpiarEstado();
    inline void _cargarContenidoEjemplo();
    
    /// @brief Métodos de renderizado
    inline void dibujarInterfazCompleta();
    inline void _renderizarListaContenido();
    inline void _renderizarItemContenido(const ContenidoCreado& contenido, int fila, bool seleccionado);
    inline void _renderizarFiltros();
    inline void _renderizarEstadisticas();
    inline void _renderizarNavegacion();
    inline void _renderizarInstrucciones();
    
    /// @brief Métodos de navegación
    inline void _navegarArriba();
    inline void _navegarAbajo();
    inline void _cambiarPagina(int direccion);
    inline void _cambiarFiltroTipo();
    inline void _cambiarFiltroEstado();
    
    /// @brief Métodos de filtrado
    inline void _aplicarFiltros();
    inline bool _cumpleFiltros(const ContenidoCreado& contenido);
    
    /// @brief Métodos de acción
    inline void _verDetallesContenido();
    inline void _editarContenido();
    inline void _cambiarEstadoContenido();
    inline void _verEstadisticasContenido();
    
    /// @brief Métodos de utilidad
    inline std::string _formatearPrecio(double precio);
    inline std::string _formatearCalificacion(double calificacion);
    inline std::string _obtenerColorEstado(const std::string& estado);

public:
    inline ListarContenidoScreen(AccionPantalla pantallaAnterior = AccionPantalla::IR_A_DASHBOARD_ORGANIZACION);
    
    inline ~ListarContenidoScreen() = default;

    inline ResultadoPantalla ejecutar() override;
};

// --- IMPLEMENTACIONES INLINE ---

// Constructor
inline ListarContenidoScreen::ListarContenidoScreen(AccionPantalla pantallaAnterior) : PantallaBase(),
    _pantallaAnterior(pantallaAnterior), _primeraRenderizacion(true), 
    _contenidoActual(0), _totalContenidos(0), _paginaActual(1), _contenidosPorPagina(CONTENIDOS_POR_PAGINA),
    _filtroTipo("TODOS"), _filtroEstado("TODOS")
{
    _cargarContenidoEjemplo();
    _aplicarFiltros();
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
        _renderizarFiltros();
        _renderizarEstadisticas();
        _renderizarNavegacion();
        _renderizarInstrucciones();
        
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
                
            case 13: // Enter - Ver detalles
                _verDetallesContenido();
                break;
                
            case 'e': case 'E': // Editar contenido
                _editarContenido();
                break;
                
            case 's': case 'S': // Cambiar estado
                _cambiarEstadoContenido();
                break;
                
            case 't': case 'T': // Cambiar filtro tipo
                _cambiarFiltroTipo();
                _aplicarFiltros();
                _primeraRenderizacion = true;
                break;
                
            case 'f': case 'F': // Cambiar filtro estado
                _cambiarFiltroEstado();
                _aplicarFiltros();
                _primeraRenderizacion = true;
                break;
                
            case 'v': case 'V': // Ver estadísticas
                _verEstadisticasContenido();
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
        {1, "Introducción a Python", "Curso", "Programación", "15/03/2025", "20/06/2025", 89.90, 40, 1247, "Activo", 4.7, 89, false, {}},
        {2, "Especialización en Data Science", "Especialización", "Ciencia de Datos", "10/02/2025", "25/06/2025", 299.99, 120, 856, "Activo", 4.8, 156, true, {"Python para Data Science", "Machine Learning Básico", "Visualización de Datos"}},
        {3, "JavaScript Moderno", "Curso", "Desarrollo Web", "05/04/2025", "18/06/2025", 79.90, 35, 923, "Activo", 4.6, 67, false, {}},
        {4, "Machine Learning Avanzado", "Curso", "Inteligencia Artificial", "20/01/2025", "15/05/2025", 149.90, 60, 432, "Inactivo", 4.9, 34, false, {}},
        {5, "Especialización Full Stack", "Especialización", "Desarrollo Web", "12/03/2025", "22/06/2025", 399.99, 180, 567, "Activo", 4.5, 89, true, {"HTML/CSS Avanzado", "JavaScript Moderno", "React y Node.js", "Bases de Datos"}},
        {6, "UX/UI Design Fundamentals", "Curso", "Diseño", "08/04/2025", "10/06/2025", 99.90, 45, 678, "Borrador", 0.0, 0, false, {}},
        {7, "Cybersecurity Essentials", "Curso", "Seguridad", "25/02/2025", "20/05/2025", 129.90, 55, 345, "Activo", 4.8, 45, false, {}},
        {8, "Cloud Computing con AWS", "Curso", "Cloud Computing", "14/03/2025", "28/06/2025", 179.90, 70, 289, "Activo", 4.7, 23, false, {}},
        {9, "Especialización DevOps", "Especialización", "DevOps", "01/04/2025", "25/06/2025", 349.99, 150, 234, "Borrador", 0.0, 0, true, {"Docker y Containers", "Kubernetes", "CI/CD", "Monitoring"}},
        {10, "Mobile App Development", "Curso", "Desarrollo Móvil", "18/03/2025", "15/06/2025", 119.90, 50, 456, "Inactivo", 4.4, 28, false, {}}
    };
    
    _totalContenidos = _contenidos.size();
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
    int finItem = (std::min)(inicioItem + _contenidosPorPagina, (int)_contenidosFiltrados.size());
    
    for (int i = inicioItem; i < finItem; i++) {
        int filaItem = FILA_LISTA + (i - inicioItem) * (ALTO_ITEM + 1);
        bool seleccionado = (i == _contenidoActual);
        _renderizarItemContenido(_contenidosFiltrados[i], filaItem, seleccionado);
    }
}

// Renderizar item individual de contenido
inline void ListarContenidoScreen::_renderizarItemContenido(const ContenidoCreado& contenido, int fila, bool seleccionado)
{
    if (seleccionado) {
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::AZUL_MARCA);
    } else {
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    }
    
    // Línea 1: Nombre y tipo
    gotoXY(COL_LISTA, fila);
    std::cout << std::setw(3) << contenido.id << " │ ";
    std::cout << std::left << std::setw(40) << contenido.nombre.substr(0, 38);
    std::cout << " │ " << std::setw(15) << contenido.tipo;
    std::cout << " │ " << std::setw(12) << contenido.categoria;
    std::cout << " │ " << std::setw(10) << _formatearPrecio(contenido.precio);
    std::cout << " │ " << std::setw(8) << contenido.estudiantesInscritos;
    
    // Línea 2: Estado y estadísticas
    gotoXY(COL_LISTA, fila + 1);
    std::cout << "    │ Estado: " << std::setw(8) << contenido.estado;
    std::cout << " │ Duración: " << std::setw(3) << contenido.duracionHoras << "h";
    std::cout << " │ Rating: " << _formatearCalificacion(contenido.calificacionPromedio);
    std::cout << " │ Reseñas: " << contenido.totalReseñas;
    std::cout << " │ Creado: " << contenido.fechaCreacion;
    
    // Línea 3: Separador
    gotoXY(COL_LISTA, fila + 2);
    std::cout << std::string(ANCHO_ITEM, '─');
    
    resetColor();
}

// Renderizar filtros
inline void ListarContenidoScreen::_renderizarFiltros()
{
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    
    gotoXY(COL_FILTROS, FILA_FILTROS);
    std::cout << "┌─ FILTROS ─┐";
    
    gotoXY(COL_FILTROS, FILA_FILTROS + 1);
    std::cout << "│ Tipo: " << std::setw(3) << _filtroTipo.substr(0, 3) << " │";
    
    gotoXY(COL_FILTROS, FILA_FILTROS + 2);
    std::cout << "│ Estado:   │";
    
    gotoXY(COL_FILTROS, FILA_FILTROS + 3);
    std::cout << "│ " << std::setw(9) << _filtroEstado.substr(0, 9) << " │";
    
    gotoXY(COL_FILTROS, FILA_FILTROS + 4);
    std::cout << "└───────────┘";
    
    resetColor();
}

// Renderizar estadísticas
inline void ListarContenidoScreen::_renderizarEstadisticas()
{
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    
    int totalCursos = 0, totalEspecializaciones = 0, totalActivos = 0;
    int totalEstudiantes = 0;
    double ingresoTotal = 0.0;
    
    for (const auto& contenido : _contenidos) {
        if (contenido.esEspecializacion) {
            totalEspecializaciones++;
        } else {
            totalCursos++;
        }
        
        if (contenido.estado == "Activo") {
            totalActivos++;
        }
        
        totalEstudiantes += contenido.estudiantesInscritos;
        ingresoTotal += contenido.precio * contenido.estudiantesInscritos;
    }
    
    gotoXY(10, 6);
    std::cout << "Cursos: " << totalCursos << " │ Especializ.: " << totalEspecializaciones 
              << " │ Activos: " << totalActivos << " │ Estudiantes: " << totalEstudiantes 
              << " │ Ingresos: S/ " << std::fixed << std::setprecision(2) << ingresoTotal;
    
    resetColor();
}

// Renderizar navegación
inline void ListarContenidoScreen::_renderizarNavegacion()
{
    int totalPaginas = (_contenidosFiltrados.size() + _contenidosPorPagina - 1) / _contenidosPorPagina;
    if (totalPaginas == 0) totalPaginas = 1;
    
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    
    gotoXY(COL_NAVEGACION, FILA_NAVEGACION);
    std::cout << "< ANTERIOR     [" << _paginaActual << "/" << totalPaginas << "]     SIGUIENTE >";
    
    gotoXY(COL_NAVEGACION + 60, FILA_NAVEGACION);
    std::cout << "DETALLES  EDITAR  ESTADO";
    
    resetColor();
}

// Renderizar instrucciones
inline void ListarContenidoScreen::_renderizarInstrucciones()
{
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    
    gotoXY(0, 29);
    std::cout << std::string(120, '─');
    gotoXY(5, 30);
    std::cout << "ARRIBA/ABAJO: Navegar │ IZQUIERDA/DERECHA: Cambiar página │ ENTER: Detalles │ E: Editar │ S: Estado";
    gotoXY(5, 31);
    std::cout << "T: Filtro tipo │ F: Filtro estado │ V: Estadísticas │ ESC: Regresar";
    
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
            _paginaActual = paginaItem;
        }
    }
}

// Navegación abajo
inline void ListarContenidoScreen::_navegarAbajo()
{
    if (_contenidoActual < (int)_contenidosFiltrados.size() - 1) {
        _contenidoActual++;
        
        // Cambiar página si es necesario
        int paginaItem = _contenidoActual / _contenidosPorPagina + 1;
        if (paginaItem != _paginaActual) {
            _paginaActual = paginaItem;
        }
    }
}

// Cambiar página
inline void ListarContenidoScreen::_cambiarPagina(int direccion)
{
    int totalPaginas = (_contenidosFiltrados.size() + _contenidosPorPagina - 1) / _contenidosPorPagina;
    if (totalPaginas == 0) totalPaginas = 1;
    
    int nuevaPagina = _paginaActual + direccion;
    if (nuevaPagina >= 1 && nuevaPagina <= totalPaginas) {
        _paginaActual = nuevaPagina;
        _contenidoActual = (_paginaActual - 1) * _contenidosPorPagina;
        
        // Asegurar que el índice está dentro del rango
        if (_contenidoActual >= (int)_contenidosFiltrados.size()) {
            _contenidoActual = (std::max)(0, (int)_contenidosFiltrados.size() - 1);
        }
    }
}

// Cambiar filtro tipo
inline void ListarContenidoScreen::_cambiarFiltroTipo()
{
    if (_filtroTipo == "TODOS") {
        _filtroTipo = "CURSOS";
    } else if (_filtroTipo == "CURSOS") {
        _filtroTipo = "ESPECIALIDADES";
    } else {
        _filtroTipo = "TODOS";
    }
    
    _contenidoActual = 0;
    _paginaActual = 1;
}

// Cambiar filtro estado
inline void ListarContenidoScreen::_cambiarFiltroEstado()
{
    if (_filtroEstado == "TODOS") {
        _filtroEstado = "ACTIVOS";
    } else if (_filtroEstado == "ACTIVOS") {
        _filtroEstado = "INACTIVOS";
    } else if (_filtroEstado == "INACTIVOS") {
        _filtroEstado = "BORRADORES";
    } else {
        _filtroEstado = "TODOS";
    }
    
    _contenidoActual = 0;
    _paginaActual = 1;
}

// Aplicar filtros
inline void ListarContenidoScreen::_aplicarFiltros()
{
    _contenidosFiltrados.clear();
    
    for (const auto& contenido : _contenidos) {
        if (_cumpleFiltros(contenido)) {
            _contenidosFiltrados.push_back(contenido);
        }
    }
    
    // Ajustar índices si es necesario
    if (_contenidoActual >= (int)_contenidosFiltrados.size()) {
        _contenidoActual = (std::max)(0, (int)_contenidosFiltrados.size() - 1);
    }
}

// Verificar si cumple filtros
inline bool ListarContenidoScreen::_cumpleFiltros(const ContenidoCreado& contenido)
{
    // Filtro por tipo
    if (_filtroTipo != "TODOS") {
        if (_filtroTipo == "CURSOS" && contenido.esEspecializacion) return false;
        if (_filtroTipo == "ESPECIALIDADES" && !contenido.esEspecializacion) return false;
    }
    
    // Filtro por estado
    if (_filtroEstado != "TODOS") {
        if (_filtroEstado == "ACTIVOS" && contenido.estado != "Activo") return false;
        if (_filtroEstado == "INACTIVOS" && contenido.estado != "Inactivo") return false;
        if (_filtroEstado == "BORRADORES" && contenido.estado != "Borrador") return false;
    }
    
    return true;
}

// Ver detalles del contenido
inline void ListarContenidoScreen::_verDetallesContenido()
{
    if (_contenidosFiltrados.empty()) return;
    
    const auto& contenido = _contenidosFiltrados[_contenidoActual];
    
	system("cls");
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    
    gotoXY(40, 5);
    std::cout << "DETALLES DEL " << contenido.tipo.substr(0, contenido.tipo.length()).c_str();
    
    gotoXY(10, 8);
    std::cout << "ID: " << contenido.id << " │ Nombre: " << contenido.nombre;
    
    gotoXY(10, 10);
    std::cout << "Categoría: " << contenido.categoria << " │ Estado: " << contenido.estado;
    
    gotoXY(10, 12);
    std::cout << "Precio: " << _formatearPrecio(contenido.precio) << " │ Duración: " << contenido.duracionHoras << " horas";
    
    gotoXY(10, 14);
    std::cout << "Estudiantes inscritos: " << contenido.estudiantesInscritos;
    
    gotoXY(10, 16);
    std::cout << "Calificación promedio: " << _formatearCalificacion(contenido.calificacionPromedio) 
              << " (" << contenido.totalReseñas << " reseñas)";
    
    gotoXY(10, 18);
    std::cout << "Fecha de creación: " << contenido.fechaCreacion;
    
    gotoXY(10, 20);
    std::cout << "Última modificación: " << contenido.fechaUltimaModificacion;
    
    if (contenido.esEspecializacion && !contenido.cursosIncluidos.empty()) {
        gotoXY(10, 22);
        std::cout << "Cursos incluidos:";
        
        for (size_t i = 0; i < contenido.cursosIncluidos.size(); i++) {
            gotoXY(15, 23 + i);
            std::cout << "- " << contenido.cursosIncluidos[i];
        }
    }
    
    gotoXY(40, 28);
    std::cout << "Presiona cualquier tecla para continuar...";
    
    resetColor();
    _getch();
    _primeraRenderizacion = true;
}

// Editar contenido
inline void ListarContenidoScreen::_editarContenido()
{
    if (_contenidosFiltrados.empty()) return;
    
	system("cls");
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    
    gotoXY(45, 10);
    std::cout << "FUNCIÓN DE EDICIÓN";
    
    gotoXY(30, 15);
    std::cout << "Esta funcionalidad será implementada próximamente.";
    
    gotoXY(40, 20);
    std::cout << "Presiona cualquier tecla para continuar...";
    
    resetColor();
    _getch();
    _primeraRenderizacion = true;
}

// Cambiar estado del contenido
inline void ListarContenidoScreen::_cambiarEstadoContenido()
{
    if (_contenidosFiltrados.empty()) return;
    
    auto& contenido = _contenidosFiltrados[_contenidoActual];
    
    // Encontrar el contenido original en la lista principal
    for (auto& original : _contenidos) {
        if (original.id == contenido.id) {
            if (original.estado == "Activo") {
                original.estado = "Inactivo";
            } else if (original.estado == "Inactivo") {
                original.estado = "Activo";
            } else if (original.estado == "Borrador") {
                original.estado = "Activo";
            }
            
            // Actualizar también en la lista filtrada
            contenido.estado = original.estado;
            break;
        }
    }
    
    _aplicarFiltros();
}

// Ver estadísticas del contenido
inline void ListarContenidoScreen::_verEstadisticasContenido()
{
    if (_contenidosFiltrados.empty()) return;
    
	system("cls");
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    
    gotoXY(45, 10);
    std::cout << "ESTADÍSTICAS DETALLADAS";
    
    gotoXY(30, 15);
    std::cout << "Esta funcionalidad será implementada próximamente.";
    
    gotoXY(40, 20);
    std::cout << "Presiona cualquier tecla para continuar...";
    
    resetColor();
    _getch();
    _primeraRenderizacion = true;
}

// Formatear precio
inline std::string ListarContenidoScreen::_formatearPrecio(double precio)
{
    std::ostringstream oss;
    oss << "S/ " << std::fixed << std::setprecision(2) << precio;
    return oss.str();
}

// Formatear calificación
inline std::string ListarContenidoScreen::_formatearCalificacion(double calificacion)
{
    if (calificacion == 0.0) return "N/A";
    
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << calificacion << "/5.0";
    return oss.str();
}

// Obtener color del estado
inline std::string ListarContenidoScreen::_obtenerColorEstado(const std::string& estado)
{
    if (estado == "Activo") return "VERDE";
    if (estado == "Inactivo") return "ROJO";
    if (estado == "Borrador") return "AMARILLO";
    return "GRIS";
}

#endif // COURSERACLONE_SCREENS_LISTARCONTENIDOSCREEN_HPP
