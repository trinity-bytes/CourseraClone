#ifndef COURSERACLONE_SCREENS_DASHBOARDORGANIZACIONSCREEN_HPP
#define COURSERACLONE_SCREENS_DASHBOARDORGANIZACIONSCREEN_HPP

// Headers de librería estándar
#include <string>
#include <vector>
#include <conio.h>

// Headers propios del proyecto
#include "../Utils/SystemUtils.hpp"
#include "../Utils/ScreenSystem.hpp"
#include "../Utils/UI_Ascii.hpp"
#include "../Utils/ConsoleTypes.hpp"
#include "../Controllers/SessionManager.hpp"

/// Pantalla dashboard para organizaciones
class DashboardOrganizacionScreen : public PantallaBase
{
private:
    /// @brief Constantes para las secciones
    static const int SECCION_HEADER = 0;
    static const int SECCION_MENU_SUPERIOR = 1;
    static const int SECCION_CURSOS = 2;
    static const int SECCION_ESPECIALIZACIONES = 3;
    static const int TOTAL_SECCIONES = 4;    
    
    /// @brief Elementos por sección
    static const int MAX_ELEMENTOS_HEADER = 2;            // Ver mi perfil, Cerrar sesión
    static const int MAX_ELEMENTOS_MENU = 3;              // Explorar, Gestionar, Estadísticas
    static const int MAX_ELEMENTOS_CURSOS = 4;            // "Ver todos" + 3 cursos
    static const int MAX_ELEMENTOS_ESPECIALIZACIONES = 4; // "Ver todas" + 3 especializaciones
    
    /// @brief Constantes de formateo
    static const int MAX_ANCHO_CARACTERES_CUADRO = 30;
    static const int MAX_ALTO_CARACTERES_CUADRO = 3;
    
    /// @brief Estadísticas de la organización
    int _cursosPublicados;
    int _especialidadesPublicadas;
    int _estudiantesInscritos;

    /// @brief Datos del usuario
    std::string _nombreOrganizacion;
    int _idOrganizacion;

    /// @brief Coordenadas para dibujar elementos del header
    COORD _coordsElementosHeader[MAX_ELEMENTOS_HEADER] = { 
        {87, 1}, {103, 1} 
    }; // Perfil, Cerrar sesión

    /// @brief Coordenadas para las estadísticas
    COORD _coordsEstadisticas[3] = {
        {30, 5}, {67, 5}, {99, 5}
    }; // Estadísticas números

    /// @brief Coordenadas para elementos del menú superior
    COORD _coordsElementosMenu[MAX_ELEMENTOS_MENU] = { 
        {18, 8}, {56, 8}, {84, 8}
    }; // Explorar, Gestionar, Estadísticas
        
    /// @brief Coordenadas para títulos de cursos
    COORD _coordsTituloCursos[MAX_ELEMENTOS_CURSOS] = {
        {20, 11}, {9, 13}, {45, 13}, {81, 13} // "Ver todos" + 3 cursos
    };
    
    /// @brief Coordenadas para descripciones de cursos
    COORD _coordsDescCursos[MAX_ELEMENTOS_CURSOS] = {
        {23, 12}, {9, 15}, {45, 15}, {81, 15} // "Ver todos" no tiene descripción
    };

    /// @brief Coordenadas para títulos de especializaciones
    COORD _coordsTituloEspecializaciones[MAX_ELEMENTOS_ESPECIALIZACIONES] = {
        {30, 20}, {9, 22}, {45, 22}, {81, 22} // "Ver todas" + 3 especializaciones
    };
    
    /// @brief Coordenadas para descripciones de especializaciones
    COORD _coordsDescEspecializaciones[MAX_ELEMENTOS_ESPECIALIZACIONES] = {
        {28, 22}, {9, 24}, {45, 24}, {81, 24} // "Ver todas" no tiene descripción
    };

    /// @brief Elementos de botones
    std::vector<std::string> _elementosHeader = {
        " VER MI PERFIL ",
        " CERRAR SESION "
    };
    
    std::vector<std::string> _elementosMenuSuperior = {
        " EXPLORAR CURSOS Y ESPECIALIDADES ",
        " GESTIONAR MI CONTENIDO ",
        " VER ESTADISTICAS "
    };

    /// @brief Estado actual de navegación
    int _seccionActual;
    int _elementoActual;
    int _seccionAnterior;
    int _elementoAnterior;
    bool _primeraRenderizacion;    
    
    /// @brief Datos cargados (dummy data)
    std::vector<ElementoMenu> _cursos;
    std::vector<ElementoMenu> _especializaciones; 
    
    // --- MÉTODOS PRIVADOS ---
    
    /// @brief Métodos de inicialización
    inline void _limpiarEstado();
    inline void _cargarDatos();
    inline void _cargarDatosDummy();

    /// @brief Métodos de renderizado
    inline void _dibujarInterfazCompleta();
    inline void _renderizarHeader();
    inline void _renderizarEstadisticas();
    inline void _renderizarMenuSuperior();
    inline void _renderizarCursos();
    inline void _renderizarEspecializaciones();
    inline void _actualizarSeleccion();

    /// @brief Métodos de renderizado específicos
    inline void _renderizarElementoHeader(int indice, bool seleccionado);
    inline void _renderizarElementoMenu(int indice, bool seleccionado);
    inline void _renderizarElementoCurso(int indice, bool seleccionado);
    inline void _renderizarElementoEspecializacion(int indice, bool seleccionado);

    /// @brief Métodos de navegación
    inline void _manejarNavegacion(int tecla);
    inline void _manejarNavegacionVertical(int direccion);
    inline void _manejarNavegacionHorizontal(int direccion);

    /// @brief Métodos utilitarios
    inline int _obtenerMaxElementosEnSeccion(int seccion);
    inline ResultadoPantalla _procesarSeleccion();

    /// @brief Métodos de formateo
    inline void _mostrarTituloFormateado(const COORD& coord, const std::string& titulo);
    inline void _mostrarDescripcionFormateada(const COORD& coord, const std::string& descripcion);
    inline std::string _truncarTitulo(const std::string& titulo, int maxLongitud);
    inline std::string _formatearDescripcion(const std::string& texto, int anchoMax, int altoMax);

public:
    inline DashboardOrganizacionScreen();
    inline ~DashboardOrganizacionScreen() = default;

    inline ResultadoPantalla ejecutar() override;
};

// --- IMPLEMENTACIONES INLINE ---

// Constructor
inline DashboardOrganizacionScreen::DashboardOrganizacionScreen() : PantallaBase(),
    _nombreOrganizacion("UPC - Universidad Peruana de Ciencias Aplicadas"), _idOrganizacion(1),
    _seccionActual(0), _elementoActual(0), _seccionAnterior(-1), _elementoAnterior(-1),
    _primeraRenderizacion(true), _cursosPublicados(12), _especialidadesPublicadas(4), _estudiantesInscritos(350)
{
    _cargarDatos();
}

// Limpiar estado
inline void DashboardOrganizacionScreen::_limpiarEstado()
{
    _seccionActual = 0;
    _elementoActual = 0;
    _seccionAnterior = -1;
    _elementoAnterior = -1;
    _primeraRenderizacion = true;
}

// Cargar datos
inline void DashboardOrganizacionScreen::_cargarDatos()
{
    //_cargarDatosDummy();
    _cursos.clear();
    _especializaciones.clear();
    SessionManager& sm = SessionManager::getInstance();

    _cursos = sm.getActividadesController().getElementosDashboard(TipoActividad::CURSO);
    _especializaciones = sm.getActividadesController().getElementosDashboard(TipoActividad::ESPECIALIZACION);
    _cursosPublicados = sm.getActividadesController().getCantidadCursos();
    _especialidadesPublicadas = sm.getActividadesController().getCantidadEspecializaciones();
    _estudiantesInscritos = sm.getActividadesController().getCantidadInscritos();
}

// Cargar datos de ejemplo
inline void DashboardOrganizacionScreen::_cargarDatosDummy()
{
    // Cargar cursos de ejemplo
    _cursos.clear();
    _cursos.push_back(ElementoMenu("Algoritmos y Estructuras de Datos", "Fundamentos de programación avanzada", 1));
    _cursos.push_back(ElementoMenu("Desarrollo Web Full Stack", "React, Node.js y bases de datos", 2));
    _cursos.push_back(ElementoMenu("Machine Learning Aplicado", "IA y análisis de datos práctico", 3));
    _cursos.push_back(ElementoMenu("Seguridad Informática", "Ciberseguridad empresarial", 4));

    // Cargar especializaciones de ejemplo
    _especializaciones.clear();
    _especializaciones.push_back(ElementoMenu("Ingeniería de Software", "Desarrollo profesional de software", 1));
    _especializaciones.push_back(ElementoMenu("Ciencia de Datos", "Analytics y Business Intelligence", 2));
    _especializaciones.push_back(ElementoMenu("Ciberseguridad Empresarial", "Protección integral de sistemas", 3));
    _especializaciones.push_back(ElementoMenu("Inteligencia Artificial", "ML, Deep Learning y automation", 4));
}

// Dibujar interfaz completa
inline void DashboardOrganizacionScreen::_dibujarInterfazCompleta()
{
    system("cls");
    UI_OrganizationDashboard();

    // Renderizar todas las secciones
    _renderizarHeader();
    _renderizarEstadisticas();
    _renderizarMenuSuperior();
    _renderizarCursos();
    _renderizarEspecializaciones();

    resetColor();
}

// Renderizar header
inline void DashboardOrganizacionScreen::_renderizarHeader()
{
    for (int i = 0; i < MAX_ELEMENTOS_HEADER; ++i) {
        _renderizarElementoHeader(i, _seccionActual == SECCION_HEADER && _elementoActual == i);
    }
}

// Renderizar estadísticas
inline void DashboardOrganizacionScreen::_renderizarEstadisticas()
{
    setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_AZUL_SUAVE);
    
    gotoXY(_coordsEstadisticas[0].X, _coordsEstadisticas[0].Y);
    std::cout << _cursosPublicados;
    
    gotoXY(_coordsEstadisticas[1].X, _coordsEstadisticas[1].Y);
    std::cout << _especialidadesPublicadas;
    
    gotoXY(_coordsEstadisticas[2].X, _coordsEstadisticas[2].Y);
    std::cout << _estudiantesInscritos;
    
    resetColor();
}

// Renderizar menú superior
inline void DashboardOrganizacionScreen::_renderizarMenuSuperior()
{
    for (int i = 0; i < MAX_ELEMENTOS_MENU; ++i) {
        _renderizarElementoMenu(i, _seccionActual == SECCION_MENU_SUPERIOR && _elementoActual == i);
    }
}

// Renderizar cursos
inline void DashboardOrganizacionScreen::_renderizarCursos()
{
    // Renderizar botón "Ver todos"
    _renderizarElementoCurso(0, _seccionActual == SECCION_CURSOS && _elementoActual == 0);
    
    // Renderizar cursos individuales
    for (int i = 1; i < MAX_ELEMENTOS_CURSOS && i <= _cursos.size(); ++i) {
        _renderizarElementoCurso(i, _seccionActual == SECCION_CURSOS && _elementoActual == i);
    }
}

// Renderizar especializaciones
inline void DashboardOrganizacionScreen::_renderizarEspecializaciones()
{
    // Renderizar botón "Ver todas"
    _renderizarElementoEspecializacion(0, _seccionActual == SECCION_ESPECIALIZACIONES && _elementoActual == 0);
    
    // Renderizar especializaciones individuales
    for (int i = 1; i < MAX_ELEMENTOS_ESPECIALIZACIONES && i <= _especializaciones.size(); ++i) {
        _renderizarElementoEspecializacion(i, _seccionActual == SECCION_ESPECIALIZACIONES && _elementoActual == i);
    }
}

// Actualizar selección
inline void DashboardOrganizacionScreen::_actualizarSeleccion()
{
    if (_seccionAnterior != _seccionActual || _elementoAnterior != _elementoActual)
    {
        // Actualizar elemento anterior
        if (_seccionAnterior >= 0 && _elementoAnterior >= 0) {
            switch (_seccionAnterior) {
            case SECCION_HEADER:
                _renderizarElementoHeader(_elementoAnterior, false);
                break;
            case SECCION_MENU_SUPERIOR:
                _renderizarElementoMenu(_elementoAnterior, false);
                break;
            case SECCION_CURSOS:
                _renderizarElementoCurso(_elementoAnterior, false);
                break;
            case SECCION_ESPECIALIZACIONES:
                _renderizarElementoEspecializacion(_elementoAnterior, false);
                break;
            }
        }

        // Actualizar elemento actual
        switch (_seccionActual) {
        case SECCION_HEADER:
            _renderizarElementoHeader(_elementoActual, true);
            break;
        case SECCION_MENU_SUPERIOR:
            _renderizarElementoMenu(_elementoActual, true);
            break;
        case SECCION_CURSOS:
            _renderizarElementoCurso(_elementoActual, true);
            break;
        case SECCION_ESPECIALIZACIONES:
            _renderizarElementoEspecializacion(_elementoActual, true);
            break;
        }

        _seccionAnterior = _seccionActual;
        _elementoAnterior = _elementoActual;
    }
}

// Renderizar elemento del header
inline void DashboardOrganizacionScreen::_renderizarElementoHeader(int indice, bool seleccionado)
{
    if (indice < 0 || indice >= MAX_ELEMENTOS_HEADER) return;
    
    gotoXY(_coordsElementosHeader[indice].X, _coordsElementosHeader[indice].Y);
    
    if (seleccionado) {
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::HOVER_ESTADO);
    } else {
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::BLANCO_PURO);
    }
    
    std::cout << _elementosHeader[indice];
    resetColor();
}

// Renderizar elemento del menú
inline void DashboardOrganizacionScreen::_renderizarElementoMenu(int indice, bool seleccionado)
{
    if (indice < 0 || indice >= MAX_ELEMENTOS_MENU) return;
    
    gotoXY(_coordsElementosMenu[indice].X, _coordsElementosMenu[indice].Y);
    
    if (seleccionado) {
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::HOVER_ESTADO);
    } else {
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_AZUL_SUAVE);
    }
    
    std::cout << _elementosMenuSuperior[indice];
    resetColor();
}

// Renderizar elemento de curso
inline void DashboardOrganizacionScreen::_renderizarElementoCurso(int indice, bool seleccionado)
{
    if (indice < 0 || indice >= MAX_ELEMENTOS_CURSOS) return;
    
    if (indice == 0) {
        // Botón "Ver todos"
        gotoXY(_coordsTituloCursos[0].X, _coordsTituloCursos[0].Y);
        
        if (seleccionado) {
            setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::HOVER_ESTADO);
        } else {
            setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
        }
        
        std::cout << " VER TODOS ";
    } else {
        // Curso individual
        int cursoIndex = indice - 1;
        if (cursoIndex < _cursos.size()) {
            // Renderizar título con colores según selección
            gotoXY(_coordsTituloCursos[indice].X, _coordsTituloCursos[indice].Y);
            if (seleccionado) {
                setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
            } else {
                setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
            }
            std::string tituloTruncado = _truncarTitulo(_cursos[cursoIndex].titulo, MAX_ANCHO_CARACTERES_CUADRO);
            std::cout << tituloTruncado;
            
            // Renderizar descripción
            gotoXY(_coordsDescCursos[indice].X, _coordsDescCursos[indice].Y);
            setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
            std::string descFormateada = _formatearDescripcion(_cursos[cursoIndex].descripcion, MAX_ANCHO_CARACTERES_CUADRO, MAX_ALTO_CARACTERES_CUADRO);
            std::cout << descFormateada;
        }
    }
    
    resetColor();
}

// Renderizar elemento de especialización
inline void DashboardOrganizacionScreen::_renderizarElementoEspecializacion(int indice, bool seleccionado)
{
    if (indice < 0 || indice >= MAX_ELEMENTOS_ESPECIALIZACIONES) return;
    
    if (indice == 0) {
        // Botón "Ver todas"
        gotoXY(_coordsTituloEspecializaciones[0].X, _coordsTituloEspecializaciones[0].Y);
        
        if (seleccionado) {
            setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::HOVER_ESTADO);
        } else {
            setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
        }
        
        std::cout << " VER TODAS ";
    } else {
        // Especialización individual
        int espIndex = indice - 1;
        if (espIndex < _especializaciones.size()) {
            // Renderizar título con colores según selección
            gotoXY(_coordsTituloEspecializaciones[indice].X, _coordsTituloEspecializaciones[indice].Y);
            if (seleccionado) {
                setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
            } else {
                setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
            }
            std::string tituloTruncado = _truncarTitulo(_especializaciones[espIndex].titulo, MAX_ANCHO_CARACTERES_CUADRO);
            std::cout << tituloTruncado;
            
            // Renderizar descripción
            gotoXY(_coordsDescEspecializaciones[indice].X, _coordsDescEspecializaciones[indice].Y);
            setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
            std::string descFormateada = _formatearDescripcion(_especializaciones[espIndex].descripcion, MAX_ANCHO_CARACTERES_CUADRO, MAX_ALTO_CARACTERES_CUADRO);
            std::cout << descFormateada;
        }
    }
    
    resetColor();
}

// Manejar navegación
inline void DashboardOrganizacionScreen::_manejarNavegacion(int tecla)
{
    switch (tecla) {
    case 72: // Flecha arriba
        _manejarNavegacionVertical(-1);
        break;
    case 80: // Flecha abajo
        _manejarNavegacionVertical(1);
        break;
    case 75: // Flecha izquierda
        _manejarNavegacionHorizontal(-1);
        break;
    case 77: // Flecha derecha
        _manejarNavegacionHorizontal(1);
        break;
    }
}

// Manejar navegación vertical
inline void DashboardOrganizacionScreen::_manejarNavegacionVertical(int direccion)
{
    if (_seccionActual == SECCION_CURSOS || _seccionActual == SECCION_ESPECIALIZACIONES) {
        // En secciones de cursos/especialidades, ARRIBA/ABAJO navega entre "Ver todos" y elementos individuales
        if (direccion > 0) { // ABAJO
            if (_elementoActual == 0) {
                _elementoActual = 1; // De "Ver todos" al primer elemento
            } else {
                // Ir a la siguiente sección
                if (_seccionActual < TOTAL_SECCIONES - 1) {
                    _seccionActual++;
                    _elementoActual = 0;
                } else {
                    _seccionActual = 0;
                    _elementoActual = 0;
                }
            }
        } else { // ARRIBA
            if (_elementoActual == 0) {
                // Ir a la sección anterior
                if (_seccionActual > 0) {
                    _seccionActual--;
                    _elementoActual = 0;
                } else {
                    _seccionActual = TOTAL_SECCIONES - 1;
                    _elementoActual = 0;
                }
            } else {
                _elementoActual = 0; // De elementos individuales a "Ver todos"
            }
        }
    } else {
        // Navegación normal entre secciones para header y menú
        if (direccion > 0) { // ABAJO
            if (_seccionActual < TOTAL_SECCIONES - 1) {
                _seccionActual++;
                _elementoActual = 0;
            } else {
                _seccionActual = 0;
                _elementoActual = 0;
            }
        } else { // ARRIBA
            if (_seccionActual > 0) {
                _seccionActual--;
                _elementoActual = 0;
            } else {
                _seccionActual = TOTAL_SECCIONES - 1;
                _elementoActual = 0;
            }
        }
    }
}

// Manejar navegación horizontal
inline void DashboardOrganizacionScreen::_manejarNavegacionHorizontal(int direccion)
{
    if (_seccionActual == SECCION_CURSOS || _seccionActual == SECCION_ESPECIALIZACIONES) {
        // Solo navegar horizontalmente entre elementos individuales (no "Ver todos")
        if (_elementoActual > 0) {
            int maxElementos = _obtenerMaxElementosEnSeccion(_seccionActual);
            
            if (direccion > 0) { // DERECHA
                if (_elementoActual < maxElementos - 1) {
                    _elementoActual++;
                } else {
                    _elementoActual = 1; // Ciclar al primer elemento individual
                }
            } else { // IZQUIERDA
                if (_elementoActual > 1) {
                    _elementoActual--;
                } else {
                    _elementoActual = maxElementos - 1; // Ciclar al último elemento
                }
            }
        }
    } else {
        // Navegación horizontal normal para header y menú
        int maxElementos = _obtenerMaxElementosEnSeccion(_seccionActual);
        
        if (direccion > 0) { // DERECHA
            if (_elementoActual < maxElementos - 1) {
                _elementoActual++;
            } else {
                _elementoActual = 0; // Ciclar al inicio
            }
        } else { // IZQUIERDA
            if (_elementoActual > 0) {
                _elementoActual--;
            } else {
                _elementoActual = maxElementos - 1; // Ciclar al final
            }
        }
    }
}

// Obtener máximo de elementos en una sección
inline int DashboardOrganizacionScreen::_obtenerMaxElementosEnSeccion(int seccion)
{
    switch (seccion) {
    case SECCION_HEADER:
        return MAX_ELEMENTOS_HEADER;
    case SECCION_MENU_SUPERIOR:
        return MAX_ELEMENTOS_MENU;
    case SECCION_CURSOS:
        return MAX_ELEMENTOS_CURSOS;
    case SECCION_ESPECIALIZACIONES:
        return MAX_ELEMENTOS_ESPECIALIZACIONES;
    default:
        return 1;
    }
}

// Procesar selección
inline ResultadoPantalla DashboardOrganizacionScreen::_procesarSeleccion()
{
    ResultadoPantalla res;
    
    switch (_seccionActual) {
    case SECCION_HEADER:
        if (_elementoActual == 0) {
            // Ver mi perfil
            res.accion = AccionPantalla::IR_A_PERFIL_ORGANIZACION;
        } else if (_elementoActual == 1) {
            // Cerrar sesión
            res.accion = AccionPantalla::IR_A_LANDING_PAGE;
        }
        break;
        
    case SECCION_MENU_SUPERIOR:
        if (_elementoActual == 0) {
            // Explorar cursos y especialidades
            res.accion = AccionPantalla::IR_A_EXPLORAR_CURSOS_Y_ESPECIALIDADES;
        } else if (_elementoActual == 1) {
            // Gestionar mi contenido
            res.accion = AccionPantalla::NINGUNA; // Por implementar
        } else if (_elementoActual == 2) {
            // Ver estadísticas
            res.accion = AccionPantalla::NINGUNA; // Por implementar
        }
        break;
        
    case SECCION_CURSOS:
        if (_elementoActual == 0) {
            // Ver todos los cursos
            res.accion = AccionPantalla::NINGUNA; // Por implementar
        } else {
            // Ver curso específico
            int cursoIndex = _elementoActual - 1;
            if (cursoIndex < _cursos.size()) {
                res.accion = AccionPantalla::IR_A_MOSTRAR_CURSO;
                res.idCursoSeleccionado = _cursos[cursoIndex].id;
            }
        }
        break;
        
    case SECCION_ESPECIALIZACIONES:
        if (_elementoActual == 0) {
            // Ver todas las especializaciones
            res.accion = AccionPantalla::NINGUNA; // Por implementar
        } else {
            // Ver especialización específica
            int espIndex = _elementoActual - 1;
            if (espIndex < _especializaciones.size()) {
                res.accion = AccionPantalla::IR_A_MOSTRAR_ESPECIALIZACION;
                res.idEspecializacionSeleccionada = _especializaciones[espIndex].id;
            }
        }
        break;
    }
    
    return res;
}

// Mostrar título formateado
inline void DashboardOrganizacionScreen::_mostrarTituloFormateado(const COORD& coord, const std::string& titulo)
{
    gotoXY(coord.X, coord.Y);
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    std::string tituloTruncado = _truncarTitulo(titulo, MAX_ANCHO_CARACTERES_CUADRO);
    std::cout << tituloTruncado;
    resetColor();
}

// Mostrar descripción formateada
inline void DashboardOrganizacionScreen::_mostrarDescripcionFormateada(const COORD& coord, const std::string& descripcion)
{
    std::string descFormateada = _formatearDescripcion(descripcion, MAX_ANCHO_CARACTERES_CUADRO, MAX_ALTO_CARACTERES_CUADRO);
    
    gotoXY(coord.X, coord.Y);
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << descFormateada;
    resetColor();
}

// Truncar título
inline std::string DashboardOrganizacionScreen::_truncarTitulo(const std::string& titulo, int maxLongitud)
{
    if (titulo.length() <= maxLongitud) {
        return titulo;
    }
    return titulo.substr(0, maxLongitud - 3) + "...";
}

// Formatear descripción
inline std::string DashboardOrganizacionScreen::_formatearDescripcion(const std::string& texto, int anchoMax, int altoMax)
{
    if (texto.length() <= anchoMax) {
        return texto;
    }
    
    std::string resultado = texto.substr(0, anchoMax - 3) + "...";
    return resultado;
}

// Método principal de ejecución
inline ResultadoPantalla DashboardOrganizacionScreen::ejecutar()
{
    ResultadoPantalla res;
    _limpiarEstado();

    while (true) {
        if (_primeraRenderizacion) {
            _dibujarInterfazCompleta();
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
        case 75: // Flecha izquierda (por si acaso)
        case 77: // Flecha derecha (por si acaso)
            _manejarNavegacion(tecla);
            break;

        case 27: // ESC - Cerrar sesión
            res.accion = AccionPantalla::IR_A_LANDING_PAGE;
            return res;

        case 13: // Enter - Procesar selección
            res = _procesarSeleccion();
            if (res.accion != AccionPantalla::NINGUNA) {
                return res;
            }
            break;

        default:
            // Ignorar otras teclas
            break;
        }
    }
}

#endif // COURSERACLONE_SCREENS_DASHBOARDORGANIZACIONSCREEN_HPP
