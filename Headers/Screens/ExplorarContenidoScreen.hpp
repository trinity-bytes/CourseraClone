// Descripcion: Pantalla que permite a los usuarios explorar, navegar y seleccionar
//              cursos y especializaciones disponibles en el sistema.

#ifndef COURSERACLONE_SCREENS_EXPLORARCONTENIDOSCREEN_HPP
#define COURSERACLONE_SCREENS_EXPLORARCONTENIDOSCREEN_HPP

// Includes del sistema
#include <iostream>
#include <string>
#include <vector>
#include "../DataStructures/Grafo.hpp"
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
    static const int SECCION_RESULTADOS = 1;
    static const int SECCION_NAVEGACION_PAGINAS = 2;
    static const int SECCION_FILTRO_TIPOS = 3;
    static const int SECCION_FILTRO_CATEGORIAS = 4;
    static const int TOTAL_SECCIONES = 5;

    // Límites por sección
    static const int MAX_CATEGORIAS_VISIBLES = 15;
    int MAX_RESULTADOS_VISIBLES = 10;

    // --- Coordenadas de la interfaz ---
    COORD _coordBuscador = {16, 6};
    COORD _coordFiltroTipos = {94, 8};
    COORD _coordFiltroCategorias = {94, 13};
    COORD _coordResultados = {4, 9};
    COORD _coordNavegacionPaginas = {44, 28};

    // --- Estado de navegación ---
    int _seccionActual;
    int _elementoActual;
    int _seccionAnterior;
    int _elementoAnterior;
    bool _primeraRenderizacion;

    // --- Datos del buscador ---
    std::string _textoBusqueda;
    int _sugerenciaSeleccionada = -1; // -1 significa ninguna seleccionada

    // --- Datos de filtros ---
    int _tipoSeleccionado; // 0=TODOS, 1=CURSOS, 2=ESPECIALIDADES
    int _categoriaSeleccionada; // índice en el vector de categorías
    int _paginaCategoriaActual;
    
    // --- Datos de resultados (ejemplo) ---
    int _paginaResultadosActual;
    int _totalPaginas;

    // --- Vectores de datos ---
    std::vector<std::string> _nombresCategorias;
    std::vector<RawExploradorData> _resultados;
    std::vector<std::string> _sugerenciasCursos;
    std::vector<std::string> _textosFiltroTipos;
    std::unordered_map<CategoriaActividad, std::vector<RawExploradorData>> _cursosPorCategoria;

    // --- Métodos privados de inicialización ---
    inline void _inicializarDatos();
    inline void _cargarCategorias();
    inline void _cargarCategoriasRecomendacion();
    inline void _cargarDatosSinRecomendacion(); // No hay sesion activa o el usuario no tiene inscripciones
    inline void _cargarResultadosEjemplo();    // --- Métodos privados de estado ---
    inline void _limpiarEstado();
    inline void _mostrarCursor();
    inline void _ocultarCursor();

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

    // --- Métodos de busqueda(sugerencias)
    inline void _actualizarSugerenciasCursos();
	inline void _aplicarFiltroTipos();
    inline CategoriaActividad _indiceACategoriaEnum(int indice);


    // --- Métodos utilitarios ---
    inline int _obtenerMaxElementosEnSeccion(int seccion);
    inline int _obtenerElementosVisiblesCategoria();
    inline int _obtenerElementosVisiblesResultados();

    // --- Métodos de procesamiento ---
    inline ResultadoPantalla _procesarSeleccion();
    inline void procesarSeleccionCursoEspecialidad(ResultadoPantalla& resultado);

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
  
    
	if (SessionManager::getInstance().isLoggedIn()) {
		_cargarCategoriasRecomendacion();
	}
	else {
		_cargarDatosSinRecomendacion(); // No hay sesión activa o el usuario no tiene inscripciones
	}
    //_cargarDatosSinRecomendacion();*/
    
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

inline void ExplorarContenidoScreen::_cargarCategoriasRecomendacion() {
    std::vector<std::pair<std::string, int>> conteo = SessionManager::getInstance().getInscripcionesController().getConteoCategoria(_nombresCategorias);
	std::vector<std::string> categoriasRecomendadas;
	for (const auto& par : conteo) {
		if (par.second > 0) {
			categoriasRecomendadas.push_back(par.first);
		}
	}
	// Si no hay categorías recomendadas, usar todas
	if (!categoriasRecomendadas.empty()) {
        Grafo grafo(categoriasRecomendadas, adyacenciaCategoriaBusqueda, _nombresCategorias);
        _nombresCategorias = grafo.bfsExpand();
    }
    
  
    int totalCargados = static_cast<int>(_resultados.size());
    MAX_RESULTADOS_VISIBLES = (totalCargados > 15) ? 15 : totalCargados;
    if (MAX_RESULTADOS_VISIBLES == 0) _totalPaginas = 1;
    else _totalPaginas = (totalCargados + MAX_RESULTADOS_VISIBLES - 1) / MAX_RESULTADOS_VISIBLES; // Calcular total de páginas
}


inline void ExplorarContenidoScreen::_cargarDatosSinRecomendacion()
{
    _resultados.clear();
	_resultados = ContentManager::getInstance().obtenerExploradorDatos();
    if (_resultados.empty()) {
        _cargarResultadosEjemplo(); // Cargar datos de ejemplo si no hay resultados
    }
    int totalCargados = static_cast<int>(_resultados.size());
	MAX_RESULTADOS_VISIBLES = (totalCargados > 15) ? 15 : totalCargados;
	_totalPaginas = (totalCargados + MAX_RESULTADOS_VISIBLES - 1) / MAX_RESULTADOS_VISIBLES; // Calcular total de páginas
}

// Cargar resultados de ejemplo
inline void ExplorarContenidoScreen::_cargarResultadosEjemplo()
{
    _resultados = {
        {TipoActividad::CURSO, 1, "Introduccion a Python", CategoriaActividad::PROGRAMACION},
        {TipoActividad::CURSO, 1, "Desarrollo Web con React", CategoriaActividad::DESARROLLO_WEB},
        {TipoActividad::CURSO, 1, "Machine Learning Basico", CategoriaActividad::CIENCIA_DE_DATOS},
        {TipoActividad::CURSO, 1, "Especializacion en Data Science", CategoriaActividad::CIENCIA_DE_DATOS},
        {TipoActividad::CURSO, 1, "Curso de JavaScript Avanzado", CategoriaActividad::DESARROLLO_WEB},
        {TipoActividad::CURSO, 1, "Seguridad Informatica", CategoriaActividad::SEGURIDAD_INFORMATICA},
        {TipoActividad::CURSO, 1, "Cloud Computing", CategoriaActividad::CLOUD_COMPUTING},
		{TipoActividad::CURSO, 1, "DevOps", CategoriaActividad::DEVOPS},
        {TipoActividad::CURSO, 1, "Marketing Digital", CategoriaActividad::MARKETING_DIGITAL},
        {TipoActividad::CURSO, 1, "Fotografia Digital", CategoriaActividad::FOTOGRAFIA},
        {TipoActividad::CURSO, 1, "Video y Edicion", CategoriaActividad::VIDEO_ANIMACION},
		{TipoActividad::CURSO, 1, "Ingles Basico", CategoriaActividad::IDIOMAS},
        {TipoActividad::ESPECIALIZACION, 2, "Diseno UX / UI Completo", CategoriaActividad::DISENO},
        {TipoActividad::ESPECIALIZACION, 2, "Especializacion en Inteligencia Artificial", CategoriaActividad::INTELIGENCIA_ARTIFICIAL},
        {TipoActividad::ESPECIALIZACION, 2, "Especializacion en Negocios Digitales", CategoriaActividad::NEGOCIOS},
        {TipoActividad::ESPECIALIZACION, 2, "Especializacion en Educacion Online", CategoriaActividad::EDUCACION},


    };
}

inline void ExplorarContenidoScreen::_actualizarSugerenciasCursos() {
    _sugerenciasCursos = ContentManager::getInstance().sugerirCursosPorPrefijo(_textoBusqueda, 5);
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
    _sugerenciaSeleccionada = -1;

}

// Mostrar cursor
inline void ExplorarContenidoScreen::_mostrarCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// Ocultar cursor
inline void ExplorarContenidoScreen::_ocultarCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
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

    // Configurar cursor inicial
    if (_seccionActual == SECCION_BUSCADOR) {
        _mostrarCursor();
    } else {
        _ocultarCursor();
    }

    resetColor();
}

// Actualizar selección
inline void ExplorarContenidoScreen::_actualizarSeleccion()
{
    if (_seccionAnterior != _seccionActual || _elementoAnterior != _elementoActual)
    {
        // Manejar cursor
        if (_seccionActual == SECCION_BUSCADOR) {
            _mostrarCursor();
        } else {
            _ocultarCursor();
        }

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
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::BORDES_SUTILES);
    } else {
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    }
    
    std::string texto = _textoBusqueda;
    if (texto.length() > 60) texto = texto.substr(0, 60);
    
    // Rellenar con espacios hasta el ancho total
    std::string textoCompleto = texto;
    textoCompleto.resize(66, ' ');
    
    std::cout << textoCompleto;
    
    // Si está seleccionado, posicionar el cursor al final del texto
    if (seleccionado) {
        gotoXY(_coordBuscador.X + texto.length(), _coordBuscador.Y);
        _mostrarCursor();
    }
    
    resetColor();

    // Mostrar sugerencias debajo del buscador (titulos de los cursos)
    int y = _coordBuscador.Y + 2;
    const size_t maxLen = 40;
    for (size_t i = 0; i < _sugerenciasCursos.size(); ++i) {
        gotoXY(_coordBuscador.X, y++);
        if (static_cast<int>(i) == _sugerenciaSeleccionada) {
            setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::HOVER_ESTADO);
        }
        else {
            setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        }
        std::string texto = "  > " + _sugerenciasCursos[i];
        if (texto.length() > maxLen) {
            texto = texto.substr(0, maxLen - 3) + "...";
        }
        // Rellenar hasta maxLen para que el fondo no sea más largo
        texto.resize(maxLen, ' ');
        std::cout << texto;
    }
    // Limpiar líneas sobrantes
    for (int i = _sugerenciasCursos.size(); i < 5; ++i) {
        gotoXY(_coordBuscador.X, y++);
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << std::string(maxLen, ' ');
    }
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
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::HOVER_ESTADO);
    } else if (indiceReal == _categoriaSeleccionada) {
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::EXITO_COLOR);
    } else {
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    }
    
    std::string texto = " " + _nombresCategorias[indiceReal] + " ";
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
    if (indice >= _resultados.size()) return;
    
    gotoXY(_coordResultados.X, _coordResultados.Y + indice);
    
    const int anchoLinea = 50;
    std::cout << std::string(anchoLinea, ' ');

    gotoXY(_coordResultados.X, _coordResultados.Y + indice);

    if (seleccionado) {
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::HOVER_ESTADO);
    }
    else {
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    }

    std::string titulo = _resultados[indice].titulo;
    if (titulo.length() > anchoLinea - 2) {
        titulo = titulo.substr(0, anchoLinea - 5) + "...";
    }
    std::string texto = "- " + titulo;
    texto.resize(anchoLinea, ' '); // Rellenar para evitar residuos

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
    std::vector<std::string> elementos = {" < ANTERIOR ", " SIGUIENTE > "};
    if (indice >= elementos.size()) return;
    
    int offsetX = (indice == 0) ? -10 : 3;
    gotoXY(_coordNavegacionPaginas.X + offsetX, _coordNavegacionPaginas.Y);
    
    if (seleccionado) {
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::HOVER_ESTADO);
    } else {
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
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
// Filtrado de tipos de contenido
inline void ExplorarContenidoScreen::_aplicarFiltroTipos() {
    static bool _cursosPorCategoriaInicializado = false;
    if (!_cursosPorCategoriaInicializado) {
        _cursosPorCategoria.clear();
        std::vector<RawExploradorData> todos = ContentManager::getInstance().obtenerExploradorDatos();
        for (const auto& curso : todos) {
            _cursosPorCategoria[curso.categoria].push_back(curso);
        }
        _cursosPorCategoriaInicializado = true;
    }
	_resultados.clear();
    // Obtén todos los datos (puedes optimizar esto si tienes muchos datos)
    std::vector<RawExploradorData> todos = ContentManager::getInstance().obtenerExploradorDatos();

    for (const auto& item : todos) {
        // Filtro por tipo
        bool tipoOk = (_tipoSeleccionado == 0) ||
            (_tipoSeleccionado == 1 && item.tipo == TipoActividad::CURSO) ||
            (_tipoSeleccionado == 2 && item.tipo == TipoActividad::ESPECIALIZACION);
       
        // Filtro por categoría
        bool categoriaOk = (_categoriaSeleccionada == 0) || (item.categoria == _indiceACategoriaEnum(_categoriaSeleccionada));

        if (tipoOk && categoriaOk) {
            _resultados.push_back(item);
        }
    }

    // Actualiza paginación
    int totalCargados = static_cast<int>(_resultados.size());
    MAX_RESULTADOS_VISIBLES = (totalCargados > 15) ? 15 : totalCargados;
    _totalPaginas = (MAX_RESULTADOS_VISIBLES == 0) ? 1 : (totalCargados + MAX_RESULTADOS_VISIBLES - 1) / MAX_RESULTADOS_VISIBLES;
    _paginaResultadosActual = 0;
}

inline CategoriaActividad ExplorarContenidoScreen::_indiceACategoriaEnum(int indice) {
    // El índice 0 es "TODAS", así que los enums empiezan en 0 para la posición 1
    return static_cast<CategoriaActividad>(indice - 1);
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
    return (_resultados.size() > MAX_RESULTADOS_VISIBLES) ? 
           MAX_RESULTADOS_VISIBLES : _resultados.size();
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
    if (_seccionActual == SECCION_BUSCADOR && !_sugerenciasCursos.empty()) {
        if (!_sugerenciasCursos.empty()) {
            if (direccion > 0) { // Abajo
                if (_sugerenciaSeleccionada < static_cast<int>(_sugerenciasCursos.size()) - 1)
                    _sugerenciaSeleccionada++;
                else
                    _sugerenciaSeleccionada = 0;
            }
            else { // Arriba
                if (_sugerenciaSeleccionada > 0)
                    _sugerenciaSeleccionada--;
                else
                    _sugerenciaSeleccionada = static_cast<int>(_sugerenciasCursos.size()) - 1;
            }
            _renderizarBuscador(true);
        }
        return;
    }
    if (direccion > 0) { // ABAJO
        switch (_seccionActual) {
        case SECCION_BUSCADOR:
            // Desde buscador -> Resultados
            _seccionActual = SECCION_RESULTADOS;
            _elementoActual = 0;
            break;
            
        case SECCION_RESULTADOS:
        {   // Navegar dentro de resultados
            int maxResultados = _obtenerMaxElementosEnSeccion(SECCION_RESULTADOS);
            if (_elementoActual < maxResultados - 1) {
                _elementoActual++;
            }
            else {
                // Al final de resultados -> Navegación de páginas
                _seccionActual = SECCION_NAVEGACION_PAGINAS;
                _elementoActual = 0;
            }
            break;
        }
        case SECCION_NAVEGACION_PAGINAS:
            // Ciclar dentro de navegación de páginas
            _elementoActual = (_elementoActual == 0) ? 1 : 0;
            break;
            
        case SECCION_FILTRO_TIPOS:
        {   // Navegar dentro de filtro tipos
            int maxTipos = _obtenerMaxElementosEnSeccion(SECCION_FILTRO_TIPOS);
            if (_elementoActual < maxTipos - 1) {
                _elementoActual++;
            }
            else {
                // Al final de tipos -> Categorías
                _seccionActual = SECCION_FILTRO_CATEGORIAS;
                _elementoActual = 0;
            }
            break;
        }
        case SECCION_FILTRO_CATEGORIAS:
        {    // Navegar dentro de categorías
            int maxCategorias = _obtenerMaxElementosEnSeccion(SECCION_FILTRO_CATEGORIAS);
            if (_elementoActual < maxCategorias - 1) {
                _elementoActual++;
            }
            break;
        }
        }
    } else { // ARRIBA
        switch (_seccionActual) {
        case SECCION_BUSCADOR:
            // No hay nada arriba del buscador
            break;
            
        case SECCION_RESULTADOS:
            if (_elementoActual > 0) {
                _elementoActual--;
            } else {
                // Al inicio de resultados -> Buscador
                _seccionActual = SECCION_BUSCADOR;
                _elementoActual = 0;
            }
            break;
            
        case SECCION_NAVEGACION_PAGINAS:
            // Desde navegación -> Último resultado
            _seccionActual = SECCION_RESULTADOS;
            _elementoActual = _obtenerMaxElementosEnSeccion(SECCION_RESULTADOS) - 1;
            break;
            
        case SECCION_FILTRO_TIPOS:
            // No hay nada arriba de tipos
            break;
            
        case SECCION_FILTRO_CATEGORIAS:
            if (_elementoActual > 0) {
                _elementoActual--;
            } else {
                // Al inicio de categorías -> Tipos
                _seccionActual = SECCION_FILTRO_TIPOS;
                _elementoActual = _obtenerMaxElementosEnSeccion(SECCION_FILTRO_TIPOS) - 1;
            }
            break;
        }
    }
}

// Manejar navegación horizontal
inline void ExplorarContenidoScreen::_manejarNavegacionHorizontal(int direccion)
{
    if (direccion > 0) { // DERECHA
        switch (_seccionActual) {
        case SECCION_BUSCADOR:
        case SECCION_RESULTADOS:
            // Desde buscador o resultados -> Filtros (tipos)
            _seccionActual = SECCION_FILTRO_TIPOS;
            _elementoActual = 0;
            break;
            
        case SECCION_NAVEGACION_PAGINAS:
            if (_elementoActual == 0) {
                // Primer botón -> Segundo botón
                _elementoActual = 1;
            } else {
                // Segundo botón -> Filtros (DERECHA x2)
                _seccionActual = SECCION_FILTRO_TIPOS;
                _elementoActual = 0;
            }
            break;
            
        case SECCION_FILTRO_TIPOS:
        case SECCION_FILTRO_CATEGORIAS:
            // Dentro de filtros, no hacer nada o ciclar
            break;
        }
    } else { // IZQUIERDA
        switch (_seccionActual) {
        case SECCION_BUSCADOR:
        case SECCION_RESULTADOS:
            // No hay nada a la izquierda
            break;
            
        case SECCION_NAVEGACION_PAGINAS:
            if (_elementoActual == 1) {
                // Segundo botón -> Primer botón
                _elementoActual = 0;
            }
            // Si ya está en el primer botón, no hacer nada
            break;
            
        case SECCION_FILTRO_TIPOS:
        case SECCION_FILTRO_CATEGORIAS:
            // Desde filtros -> Regresar a resultados
            _seccionActual = SECCION_RESULTADOS;
            _elementoActual = 0;
            break;
        }
    }
}

// Manejar entrada de texto
inline void ExplorarContenidoScreen::_manejarEntradaTexto(int tecla)
{
    if (_seccionActual == SECCION_BUSCADOR && tecla >= 32 && tecla <= 126) {
        if (_textoBusqueda.length() < 60) {
            _textoBusqueda.push_back(static_cast<char>(tecla));
            _actualizarSugerenciasCursos();
			_sugerenciaSeleccionada = -1;
            _renderizarBuscador(true);
        }
    }
}

// Manejar retroceso
inline void ExplorarContenidoScreen::_manejarRetroceso()
{
    if (_seccionActual == SECCION_BUSCADOR && !_textoBusqueda.empty()) {
        _textoBusqueda.pop_back();
        _actualizarSugerenciasCursos();
		_sugerenciaSeleccionada = -1;
        _renderizarBuscador(true);
    }
}

inline void ExplorarContenidoScreen::procesarSeleccionCursoEspecialidad(ResultadoPantalla& resultado)
{
	int idSeleccionado = _resultados[_elementoActual].id;
	if (_resultados[_elementoActual].tipo == TipoActividad::CURSO) {
        ContentManager::getInstance().setCursoIdMostrar(idSeleccionado);
        resultado.accion = AccionPantalla::IR_A_MOSTRAR_CURSO;
	}
	else if (_resultados[_elementoActual].tipo == TipoActividad::ESPECIALIZACION) {
		ContentManager::getInstance().setEspecializacionIdMostar(idSeleccionado);
		resultado.accion = AccionPantalla::IR_A_MOSTRAR_ESPECIALIZACION;
	}
    resultado.accionAnterior = AccionPantalla::IR_A_EXPLORAR_CURSOS_Y_ESPECIALIDADES;
}

// Procesar selección
inline ResultadoPantalla ExplorarContenidoScreen::_procesarSeleccion()
{
    ResultadoPantalla res;

    switch (_seccionActual) {
    case SECCION_FILTRO_TIPOS:
        _tipoSeleccionado = _elementoActual;
		_aplicarFiltroTipos();
        _renderizarFiltroTipos(); // Actualizar visual
		_renderizarResultados(); // Actualizar resultados
        break;
    case SECCION_FILTRO_CATEGORIAS:
        {
            int inicioIndice = _paginaCategoriaActual * MAX_CATEGORIAS_VISIBLES;
            _categoriaSeleccionada = inicioIndice + _elementoActual;
			_aplicarFiltroTipos();
            _renderizarFiltroCategorias(); // Actualizar visual
			_renderizarResultados(); // Actualizar resultados
        }
        break;
    case SECCION_RESULTADOS:
        // Aquí podrías abrir el detalle del curso/especialización seleccionado
        gotoXY(30, 25);
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "Abriendo: " << _resultados[_elementoActual].titulo;
        resetColor();
        Sleep(1000);
        gotoXY(30, 25);
        std::cout << "                                            ";
        procesarSeleccionCursoEspecialidad(res);
        return res;
        break;
    case SECCION_NAVEGACION_PAGINAS:
        // Cambiar página
        if (_elementoActual == 0 && _paginaResultadosActual > 0) {
            _paginaResultadosActual--;
        } else if (_elementoActual == 1 && _paginaResultadosActual < _totalPaginas - 1) {
            _paginaResultadosActual++;
        }
        break;
	case SECCION_BUSCADOR:
        if (_sugerenciaSeleccionada >= 0 && _sugerenciaSeleccionada < static_cast<int>(_sugerenciasCursos.size())) {
            std::string tituloSeleccionado = _sugerenciasCursos[_sugerenciaSeleccionada];
            RawCursoData curso;
            if (FilesManager::getInstance().buscarCursoPorNombreHash(tituloSeleccionado, curso)) {
                ContentManager::getInstance().setCursoIdMostrar(curso.id);
                res.accion = AccionPantalla::IR_A_MOSTRAR_CURSO;
                res.accionAnterior = AccionPantalla::IR_A_EXPLORAR_CURSOS_Y_ESPECIALIDADES;
                return res;
            }
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
            _ocultarCursor(); // Ocultar cursor antes de salir
            res.accion = AccionPantalla::IR_A_LANDING_PAGE;
            return res;        
        case KEY_ENTER: // Enter - Procesar selección
            res = _procesarSeleccion();
            if (res.accion != AccionPantalla::NINGUNA) {
                _ocultarCursor(); // Ocultar cursor antes de salir
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