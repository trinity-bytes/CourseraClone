// Descripcion: Pantalla que permite a los usuarios explorar, navegar y seleccionar
//              cursos y especializaciones disponibles en el sistema.

#ifndef COURSERACLONE_SCREENS_EXPLORARCONTENIDOSCREEN_HPP
#define COURSERACLONE_SCREENS_EXPLORARCONTENIDOSCREEN_HPP

// Includes del sistema
#include <iostream>
#include <string>
#include <vector>
#include <conio.h>   // Para _getch()

// Includes propios del proyecto
#include "../Utils/ScreenSystem.hpp"
#include "../Utils/SystemUtils.hpp"
#include "../Utils/UI_Ascii.hpp"
#include "../Types/ActividadTypes.hpp"

// Constantes para teclas
enum KeyCode 
{
    KEY_ENTER = 13,
    KEY_ESCAPE = 27,
    KEY_UP = 72,
    KEY_DOWN = 80,
    KEY_LEFT = 75,
    KEY_RIGHT = 77,
    KEY_BACKSPACE = 8,
    KEY_EXTEND = 224,
    KEY_NULL = 0
};

class ExplorarContenidoScreen : public PantallaBase 
{
private:
    // --- Constantes de configuración ---
    static const int SECCION_BUSCADOR = 0;
    static const int SECCION_FILTRO_TIPOS = 1;
    static const int SECCION_FILTRO_CATEGORIAS = 2;
    static const int SECCION_RESULTADOS = 3;
    static const int SECCION_NAVEGACION_PAGINAS = 4;
    static const int TOTAL_SECCIONES = 5;

    // Límites por sección
    static const int MAX_CATEGORIAS_VISIBLES = 15;
    static const int MAX_RESULTADOS_VISIBLES = 6;

    // --- Coordenadas de la interfaz ---
    COORD _coordBuscador = {44, 6};
    COORD _coordFiltroTipos = {3, 8};
    COORD _coordFiltroCategorias = {2, 13};
    COORD _coordResultados = {34, 9};
    COORD _coordNavegacionPaginas = {70, 28};

    // --- Estado de navegación ---
    int _seccionActual;
    int _elementoActual;
    int _seccionAnterior;
    int _elementoAnterior;
    bool _primeraRenderizacion;

    // --- Datos del buscador ---
    std::string _textoBusqueda;

    // --- Datos de filtros ---
    int _tipoSeleccionado; // 0=TODOS, 1=CURSOS, 2=ESPECIALIDADES
    int _categoriaSeleccionada; // índice en el vector de categorías
    int _paginaCategoriaActual;
    
    // --- Datos de resultados (ejemplo) ---
    int _paginaResultadosActual;
    int _totalPaginas;

    // --- Vectores de datos ---
    std::vector<std::string> _nombresCategorias;
    std::vector<std::string> _textosResultadosEjemplo;
    std::vector<std::string> _textosFiltroTipos;

    // --- Métodos privados de inicialización ---
    inline void _inicializarDatos();
    inline void _cargarCategorias();
    inline void _cargarResultadosEjemplo();

    // --- Métodos privados de estado ---
    inline void _limpiarEstado();

    // --- Métodos privados de renderizado ---
    inline void _dibujarInterfazCompleta();
    inline void _actualizarSeleccion();

    // --- Métodos de renderizado por sección ---
    inline void _renderizarBuscador(bool seleccionado);
    inline void _renderizarFiltroTipos();
    inline void _renderizarFiltroCategorias();
    inline void _renderizarResultados();
    inline void _renderizarNavegacionPaginas();

    // --- Métodos de renderizado de elementos específicos ---
    inline void _renderizarElementoFiltroTipo(int indice, bool seleccionado);
    inline void _renderizarElementoCategoria(int indice, bool seleccionado);
    inline void _renderizarElementoResultado(int indice, bool seleccionado);
    inline void _renderizarElementoNavegacion(int indice, bool seleccionado);

    // --- Métodos de navegación ---
    inline void _manejarNavegacion(int tecla);
    inline void _manejarNavegacionVertical(int direccion);
    inline void _manejarNavegacionHorizontal(int direccion);

    // --- Métodos de entrada de texto ---
    inline void _manejarEntradaTexto(int tecla);
    inline void _manejarRetroceso();

    // --- Métodos utilitarios ---
    inline int _obtenerMaxElementosEnSeccion(int seccion);
    inline int _obtenerElementosVisiblesCategoria();
    inline int _obtenerElementosVisiblesResultados();

    // --- Métodos de procesamiento ---
    inline ResultadoPantalla _procesarSeleccion();

public:
    inline ExplorarContenidoScreen();
    inline ~ExplorarContenidoScreen() = default;
    
    inline ResultadoPantalla ejecutar() override;
};

// --- IMPLEMENTACIONES INLINE ---

// Constructor
inline ExplorarContenidoScreen::ExplorarContenidoScreen() : PantallaBase(),
    _seccionActual(0), _elementoActual(0), _seccionAnterior(0), _elementoAnterior(0),
    _primeraRenderizacion(true), _tipoSeleccionado(0), _categoriaSeleccionada(0),
    _paginaCategoriaActual(0), _paginaResultadosActual(0), _totalPaginas(3)
{
    _inicializarDatos();
}

// Inicializar datos de ejemplo
inline void ExplorarContenidoScreen::_inicializarDatos()
{
    _cargarCategorias();
    _cargarResultadosEjemplo();
    
    _textosFiltroTipos = {
        " TODOS ",
        " CURSOS ",
        " ESPECIALIDADES "
    };
}

// Cargar categorías desde el enum
inline void ExplorarContenidoScreen::_cargarCategorias()
{
    _nombresCategorias = {
        "TODAS",
        "PROGRAMACION",
        "DESARROLLO_WEB", 
        "DESARROLLO_MOVIL",
        "INTELIGENCIA_ARTIFICIAL",
        "CIENCIA_DE_DATOS",
        "SEGURIDAD_INFORMATICA",
        "CLOUD_COMPUTING",
        "DEVOPS",
        "UX_UI",
        "DISENO_GRAFICO",
        "MARKETING_DIGITAL",
        "NEGOCIOS",
        "FINANZAS",
        "GESTION_PROYECTOS",
        "FOTOGRAFIA",
        "VIDEO_ANIMACION",
        "EDUCACION",
        "IDIOMAS",
        "OTROS"
    };
}

// Cargar resultados de ejemplo
inline void ExplorarContenidoScreen::_cargarResultadosEjemplo()
{
    _textosResultadosEjemplo = {
        "Introduccion a Python",
        "Desarrollo Web con React",
        "Machine Learning Basico",
        "Especializacion en Data Science",
        "Curso de JavaScript Avanzado",
        "Diseno UX/UI Completo"
    };
}

// Limpiar estado
inline void ExplorarContenidoScreen::_limpiarEstado()
{
    _seccionActual = 0;
    _elementoActual = 0;
    _seccionAnterior = 0;
    _elementoAnterior = 0;
    _primeraRenderizacion = true;
    _textoBusqueda.clear();
}

// Dibujar interfaz completa
inline void ExplorarContenidoScreen::_dibujarInterfazCompleta()
{
    system("cls");
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    UI_ExplorarContenido();

    // Renderizar todas las secciones
    _renderizarBuscador(_seccionActual == SECCION_BUSCADOR);
    _renderizarFiltroTipos();
    _renderizarFiltroCategorias();
    _renderizarResultados();
    _renderizarNavegacionPaginas();

    resetColor();
}

// Actualizar selección
inline void ExplorarContenidoScreen::_actualizarSeleccion()
{
    if (_seccionAnterior != _seccionActual || _elementoAnterior != _elementoActual)
    {
        // Actualizar sección anterior
        switch (_seccionAnterior) {
        case SECCION_BUSCADOR:
            _renderizarBuscador(false);
            break;
        case SECCION_FILTRO_TIPOS:
            _renderizarElementoFiltroTipo(_elementoAnterior, false);
            break;
        case SECCION_FILTRO_CATEGORIAS:
            _renderizarElementoCategoria(_elementoAnterior, false);
            break;
        case SECCION_RESULTADOS:
            _renderizarElementoResultado(_elementoAnterior, false);
            break;
        case SECCION_NAVEGACION_PAGINAS:
            _renderizarElementoNavegacion(_elementoAnterior, false);
            break;
        }

        // Actualizar sección actual
        switch (_seccionActual) {
        case SECCION_BUSCADOR:
            _renderizarBuscador(true);
            break;
        case SECCION_FILTRO_TIPOS:
            _renderizarElementoFiltroTipo(_elementoActual, true);
            break;
        case SECCION_FILTRO_CATEGORIAS:
            _renderizarElementoCategoria(_elementoActual, true);
            break;
        case SECCION_RESULTADOS:
            _renderizarElementoResultado(_elementoActual, true);
            break;
        case SECCION_NAVEGACION_PAGINAS:
            _renderizarElementoNavegacion(_elementoActual, true);
            break;
        }

        _seccionAnterior = _seccionActual;
        _elementoAnterior = _elementoActual;
    }
}

// Renderizar buscador
inline void ExplorarContenidoScreen::_renderizarBuscador(bool seleccionado)
{
    gotoXY(_coordBuscador.X, _coordBuscador.Y);
    
    if (seleccionado) {
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::BLANCO_PURO);
    } else {
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::BLANCO_PURO);
    }
    
    std::string texto = _textoBusqueda;
    if (texto.length() > 60) texto = texto.substr(0, 60);
    texto.resize(66, ' '); // Rellenar con espacios
    
    std::cout << texto;
    resetColor();
}

// Renderizar filtro de tipos
inline void ExplorarContenidoScreen::_renderizarFiltroTipos()
{
    for (int i = 0; i < _textosFiltroTipos.size(); ++i) {
        _renderizarElementoFiltroTipo(i, _seccionActual == SECCION_FILTRO_TIPOS && _elementoActual == i);
    }
}

// Renderizar elemento de filtro tipo
inline void ExplorarContenidoScreen::_renderizarElementoFiltroTipo(int indice, bool seleccionado)
{
    if (indice < 0 || indice >= _textosFiltroTipos.size()) return;
    
    gotoXY(_coordFiltroTipos.X, _coordFiltroTipos.Y + indice);
    
    if (seleccionado) {
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::HOVER_ESTADO);
    } else if (indice == _tipoSeleccionado) {
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::EXITO_COLOR);
    } else {
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    }
    
    std::cout << _textosFiltroTipos[indice];
    resetColor();
}

// Renderizar filtro de categorías
inline void ExplorarContenidoScreen::_renderizarFiltroCategorias()
{
    int elementosVisibles = _obtenerElementosVisiblesCategoria();
    int inicioIndice = _paginaCategoriaActual * MAX_CATEGORIAS_VISIBLES;
    
    for (int i = 0; i < elementosVisibles; ++i) {
        int indiceReal = inicioIndice + i;
        _renderizarElementoCategoria(i, _seccionActual == SECCION_FILTRO_CATEGORIAS && _elementoActual == i);
    }
}

// Renderizar elemento de categoría
inline void ExplorarContenidoScreen::_renderizarElementoCategoria(int indice, bool seleccionado)
{
    int inicioIndice = _paginaCategoriaActual * MAX_CATEGORIAS_VISIBLES;
    int indiceReal = inicioIndice + indice;
    
    if (indiceReal >= _nombresCategorias.size()) return;
    
    gotoXY(_coordFiltroCategorias.X, _coordFiltroCategorias.Y + indice);
    
    if (seleccionado) {
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
    } else if (indiceReal == _categoriaSeleccionada) {
        setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    } else {
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    }
    
    std::string texto = "  " + _nombresCategorias[indiceReal];
    if (texto.length() > 19) texto = texto.substr(0, 19);
    std::cout << texto;
    resetColor();
}

// Renderizar resultados
inline void ExplorarContenidoScreen::_renderizarResultados()
{
    int elementosVisibles = _obtenerElementosVisiblesResultados();
    
    for (int i = 0; i < elementosVisibles; ++i) {
        _renderizarElementoResultado(i, _seccionActual == SECCION_RESULTADOS && _elementoActual == i);
    }
}

// Renderizar elemento de resultado
inline void ExplorarContenidoScreen::_renderizarElementoResultado(int indice, bool seleccionado)
{
    if (indice >= _textosResultadosEjemplo.size()) return;
    
    gotoXY(_coordResultados.X, _coordResultados.Y + (indice * 3));
    
    if (seleccionado) {
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
    } else {
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    }
    
    std::string texto = "- " + _textosResultadosEjemplo[indice];
    std::cout << texto;
    resetColor();
}

// Renderizar navegación de páginas
inline void ExplorarContenidoScreen::_renderizarNavegacionPaginas()
{
    std::vector<std::string> elementos = {"< ANTERIOR", "SIGUIENTE >"};
    
    for (int i = 0; i < elementos.size(); ++i) {
        _renderizarElementoNavegacion(i, _seccionActual == SECCION_NAVEGACION_PAGINAS && _elementoActual == i);
    }
}

// Renderizar elemento de navegación
inline void ExplorarContenidoScreen::_renderizarElementoNavegacion(int indice, bool seleccionado)
{
    std::vector<std::string> elementos = {"< ANTERIOR", "SIGUIENTE >"};
    if (indice >= elementos.size()) return;
    
    int offsetX = (indice == 0) ? -10 : 15;
    gotoXY(_coordNavegacionPaginas.X + offsetX, _coordNavegacionPaginas.Y);
    
    if (seleccionado) {
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
    } else {
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    }
    
    std::cout << elementos[indice];
    resetColor();
}

// Obtener máximo de elementos en una sección
inline int ExplorarContenidoScreen::_obtenerMaxElementosEnSeccion(int seccion)
{
    switch (seccion) {
    case SECCION_BUSCADOR:
        return 1;
    case SECCION_FILTRO_TIPOS:
        return _textosFiltroTipos.size();
    case SECCION_FILTRO_CATEGORIAS:
        return _obtenerElementosVisiblesCategoria();
    case SECCION_RESULTADOS:
        return _obtenerElementosVisiblesResultados();
    case SECCION_NAVEGACION_PAGINAS:
        return 2;
    default:
        return 0;
    }
}

// Obtener elementos visibles de categoría
inline int ExplorarContenidoScreen::_obtenerElementosVisiblesCategoria()
{
    int inicioIndice = _paginaCategoriaActual * MAX_CATEGORIAS_VISIBLES;
    int restantes = _nombresCategorias.size() - inicioIndice;
    return (restantes > MAX_CATEGORIAS_VISIBLES) ? MAX_CATEGORIAS_VISIBLES : restantes;
}

// Obtener elementos visibles de resultados
inline int ExplorarContenidoScreen::_obtenerElementosVisiblesResultados()
{
    return (_textosResultadosEjemplo.size() > MAX_RESULTADOS_VISIBLES) ? 
           MAX_RESULTADOS_VISIBLES : _textosResultadosEjemplo.size();
}

// Manejar navegación
inline void ExplorarContenidoScreen::_manejarNavegacion(int tecla)
{
    switch (tecla) {
    case KEY_UP:
        _manejarNavegacionVertical(-1);
        break;
    case KEY_DOWN:
        _manejarNavegacionVertical(1);
        break;
    case KEY_LEFT:
        _manejarNavegacionHorizontal(-1);
        break;
    case KEY_RIGHT:
        _manejarNavegacionHorizontal(1);
        break;
    }
}

// Manejar navegación vertical
inline void ExplorarContenidoScreen::_manejarNavegacionVertical(int direccion)
{
    if (_seccionActual == SECCION_BUSCADOR) {
        // Desde buscador, moverse a otras secciones
        if (direccion > 0) {
            _seccionActual = SECCION_FILTRO_TIPOS;
            _elementoActual = 0;
        }
    } else {
        int maxElementos = _obtenerMaxElementosEnSeccion(_seccionActual);
        if (maxElementos > 0) {
            if (direccion > 0) {
                _elementoActual = (_elementoActual < maxElementos - 1) ? _elementoActual + 1 : 0;
            } else {
                _elementoActual = (_elementoActual > 0) ? _elementoActual - 1 : maxElementos - 1;
            }
        }
    }
}

// Manejar navegación horizontal
inline void ExplorarContenidoScreen::_manejarNavegacionHorizontal(int direccion)
{
    if (direccion > 0) {
        // Moverse a la derecha entre secciones
        if (_seccionActual < TOTAL_SECCIONES - 1) {
            _seccionActual++;
            _elementoActual = 0;
        }
    } else {
        // Moverse a la izquierda entre secciones
        if (_seccionActual > 0) {
            _seccionActual--;
            _elementoActual = 0;
        }
    }
}

// Manejar entrada de texto
inline void ExplorarContenidoScreen::_manejarEntradaTexto(int tecla)
{
    if (_seccionActual == SECCION_BUSCADOR && tecla >= 32 && tecla <= 126) {
        if (_textoBusqueda.length() < 60) {
            _textoBusqueda.push_back(static_cast<char>(tecla));
            _renderizarBuscador(true);
        }
    }
}

// Manejar retroceso
inline void ExplorarContenidoScreen::_manejarRetroceso()
{
    if (_seccionActual == SECCION_BUSCADOR && !_textoBusqueda.empty()) {
        _textoBusqueda.pop_back();
        _renderizarBuscador(true);
    }
}

// Procesar selección
inline ResultadoPantalla ExplorarContenidoScreen::_procesarSeleccion()
{
    ResultadoPantalla res;

    switch (_seccionActual) {
    case SECCION_FILTRO_TIPOS:
        _tipoSeleccionado = _elementoActual;
        _renderizarFiltroTipos(); // Actualizar visual
        break;
    case SECCION_FILTRO_CATEGORIAS:
        {
            int inicioIndice = _paginaCategoriaActual * MAX_CATEGORIAS_VISIBLES;
            _categoriaSeleccionada = inicioIndice + _elementoActual;
            _renderizarFiltroCategorias(); // Actualizar visual
        }
        break;
    case SECCION_RESULTADOS:
        // Aquí podrías abrir el detalle del curso/especialización seleccionado
        gotoXY(30, 25);
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "Abriendo: " << _textosResultadosEjemplo[_elementoActual];
        resetColor();
        Sleep(1000);
        gotoXY(30, 25);
        std::cout << "                                            ";
        break;
    case SECCION_NAVEGACION_PAGINAS:
        // Cambiar página
        if (_elementoActual == 0 && _paginaResultadosActual > 0) {
            _paginaResultadosActual--;
        } else if (_elementoActual == 1 && _paginaResultadosActual < _totalPaginas - 1) {
            _paginaResultadosActual++;
        }
        break;
    }
    
    res.accion = AccionPantalla::NINGUNA;
    return res;
}

// Método principal de ejecución
inline ResultadoPantalla ExplorarContenidoScreen::ejecutar()
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

        case KEY_UP:
        case KEY_DOWN:
        case KEY_LEFT:
        case KEY_RIGHT:
            _manejarNavegacion(tecla);
            break;

        case KEY_ESCAPE: // ESC - Regresar
            res.accion = AccionPantalla::IR_A_LANDING_PAGE;
            return res;

        case KEY_ENTER: // Enter - Procesar selección
            res = _procesarSeleccion();
            if (res.accion != AccionPantalla::NINGUNA) {
                return res;
            }
            break;

        case KEY_BACKSPACE: // Backspace
            _manejarRetroceso();
            break;

        default:
            _manejarEntradaTexto(tecla);
            break;
        }
    }
}

#endif // COURSERACLONE_SCREENS_EXPLORARCONTENIDOSCREEN_HPP