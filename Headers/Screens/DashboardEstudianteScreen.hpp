// Pantalla principal del estudiante con navegación por secciones

#ifndef COURSERACLONE_SCREENS_DASHBOARDESTUDIANTESCREEN_HPP
#define COURSERACLONE_SCREENS_DASHBOARDESTUDIANTESCREEN_HPP

// Headers de librería estándar
#include <conio.h>    // Para _getch()
#include <sstream>    // Para std::stringstream
#include <string>
#include <vector>

// Headers propios del proyecto
#include "../Controllers/ContentManager.hpp"
#include "../Controllers/FilesManager.hpp"
#include "../Types/UsuarioTypes.hpp"
#include "../Utils/ConsoleTypes.hpp"
#include "../Utils/DataPaths.hpp"
#include "../Utils/ScreenSystem.hpp"
#include "../Utils/SystemUtils.hpp"
#include "../Utils/UI_Ascii.hpp"

// Pantalla principal del dashboard del estudiante
class DashboardEstudianteScreen : public PantallaBase
{
private:
    /// @brief Constantes de configuración de secciones
    static const int SECCION_HEADER = 0;
    static const int SECCION_MENU_SUPERIOR = 1;
    static const int SECCION_CURSOS = 2;
    static const int SECCION_ESPECIALIZACIONES = 3;
    static const int TOTAL_SECCIONES = 4;  

    /// @brief Constantes de elementos por sección
    static const int MAX_ELEMENTOS_HEADER = 2;
    static const int MAX_ELEMENTOS_MENU_SUPERIOR = 2;
    static const int MAX_ELEMENTOS_CURSOS = 3;
    static const int MAX_ELEMENTOS_ESPECIALIZACIONES = 3;
    static const int TOTAL_ELEMENTOS_NAVEGABLES = MAX_ELEMENTOS_HEADER + MAX_ELEMENTOS_MENU_SUPERIOR + MAX_ELEMENTOS_CURSOS + MAX_ELEMENTOS_ESPECIALIZACIONES;
    
    /// @brief Constantes de formateo de texto (siguiendo patrón del LandingPage)
    static const int MAX_ANCHO_CARACTERES_CUADRO = 32;
    static const int MAX_ALTO_CARACTERES_CUADRO = 3;

    /// @brief Datos del usuario logueado
    std::string _nombreEstudiante;
    int _idEstudiante;

    /// @brief Estado de navegación
    int _seccionActual;
    int _elementoActual;
    int _seccionAnterior;
    int _elementoAnterior;
    bool _primeraRenderizacion;

    /// @brief Índices de visualización
    int _indCursoVisible;
    int _indEspVisible;    
    
    /// @brief Coordenadas de interfaz
    COORD _coordsElementosHeader[MAX_ELEMENTOS_HEADER] = {
        {88, 1}, {103, 1}
    };
    COORD _coordsElementosMenu[MAX_ELEMENTOS_MENU_SUPERIOR] = {
        {7, 8}
    };

    /// @brief Coordenadas para títulos y descripciones de cursos
    COORD _coordsTituloCursos[MAX_ELEMENTOS_CURSOS] = {
        {8, 13}, {44, 13}, {80, 13}
    };
    COORD _coordsDescCursos[MAX_ELEMENTOS_CURSOS] = {
        {8, 15}, {44, 15}, {80, 15}
    };
    
    /// @brief Coordenadas para títulos y descripciones de especializaciones
    COORD _coordsTituloEspecializaciones[MAX_ELEMENTOS_ESPECIALIZACIONES] = {
        {8, 22}, {44, 22}, {80, 22}
    };
    COORD _coordsDescEspecializaciones[MAX_ELEMENTOS_ESPECIALIZACIONES] = {
        {8, 24}, {44, 24}, {80, 24}
    };

	/// @brief Listas de cursos y especializaciones inscritas
    std::vector<ElementoInscripcion> _cursosInscritos;
    std::vector<ElementoInscripcion> _especializacionesInscritas;

	/// @brief Elementos de botones
    std::vector<std::string> _elementosHeader = {
        " VER MI PERFIL ",
        " CERRAR SESION "
	};
    std::vector<std::string> _elementosMenu = {
        " EXPLORAR CURSOS Y ESPECIALIDADES "
    };

	// ---- METODOS PRIVADOS ----

    /// @brief Métodos de inicialización
    inline void _limpiarEstado();
    inline void _cargarDatosDummy();

    /// @brief Métodos de renderizado
    inline void _dibujarInterfazCompleta();
    inline void _renderizarHeader();
    inline void _renderizarMenuSuperior();
    inline void _renderizarCursos();
    inline void _renderizarEspecializaciones();
    inline void _actualizarSeleccion();
    
    /// @brief Métodos de navegación
    inline void _manejarNavegacion(int tecla);
    inline void _calcularPosicionEnSeccion(int indiceGlobal, int& seccion, int& elemento);
    inline int _calcularIndiceGlobal(int seccion, int elemento);

      /// @brief Métodos de utilidad
    inline int _obtenerMaxElementosEnSeccion(int seccion);
    inline ResultadoPantalla _procesarSeleccion();
    
    /// @brief Métodos de formateo (siguiendo patrón del LandingPage)
    inline void _mostrarTituloFormateado(const COORD& coord, const std::string& titulo);
    inline void _mostrarDescripcionFormateada(const COORD& coord, const std::string& descripcion);
    inline std::string _truncarTitulo(const std::string& titulo, int maxLongitud);
    inline std::string _formatearDescripcion(const std::string& texto, int anchoMax, int altoMax);
    inline void _actualizarElementoGenerico(const COORD& coordTitulo, const COORD& coordDesc, 
                                           const std::string& titulo, const std::string& descripcion, bool seleccionado);

public:
    inline DashboardEstudianteScreen();
    inline ResultadoPantalla ejecutar() override;
};

// ---- CONSTRUCTORES INLINE ----
inline DashboardEstudianteScreen::DashboardEstudianteScreen() : PantallaBase(), 
    _nombreEstudiante("Juan Estudiante"), _idEstudiante(1),
    _seccionActual(0), _elementoActual(0), _seccionAnterior(-1), _elementoAnterior(-1),
    _primeraRenderizacion(true), _indCursoVisible(0), _indEspVisible(0) {
}

// ---- METODOS PRIVADOS ----
inline void DashboardEstudianteScreen::_limpiarEstado()
{
    _seccionActual = 0;
    _elementoActual = 0;
    _seccionAnterior = -1;
    _elementoAnterior = -1;
    _primeraRenderizacion = true;
    _indCursoVisible = 0;
    _indEspVisible = 0;
}

inline void DashboardEstudianteScreen::_cargarDatosDummy()
{
    // Cargar datos dummy para los cursos
    _cursosInscritos.clear();
    _especializacionesInscritas.clear();
    if (SessionManager::getInstance().isLoggedIn()) {
		_cursosInscritos = SessionManager::getInstance().getInscripcionesController().getElementosInscripcionesDashTodos(TipoActividad::CURSO);
		_especializacionesInscritas = SessionManager::getInstance().getInscripcionesController().getElementosInscripcionesDashTodos(TipoActividad::ESPECIALIZACION);
    }
    else {
        /*
        _cursosInscritos.push_back(ElementoMenu("Introducción a Python", "Fundamentos de programación en Python", 1));
        _cursosInscritos.push_back(ElementoMenu("Estructuras de Datos", "Arrays, listas, pilas y colas", 2));
        _cursosInscritos.push_back(ElementoMenu("Algoritmos Avanzados", "Ordenamiento y búsqueda eficiente", 3));
        _cursosInscritos.push_back(ElementoMenu("Desarrollo Web", "HTML, CSS y JavaScript moderno", 4));
        */
    }
    

    // Cargar datos dummy para las especializaciones
    /*
    _especializacionesInscritas.push_back(ElementoMenu("Ciencia de Datos", "Machine Learning y análisis estadístico", 1));
    _especializacionesInscritas.push_back(ElementoMenu("Desarrollo Full Stack", "Frontend y backend completo", 2));
    _especializacionesInscritas.push_back(ElementoMenu("Ciberseguridad", "Protección de sistemas y redes", 3));
    _especializacionesInscritas.push_back(ElementoMenu("Inteligencia Artificial", "Deep Learning y redes neuronales", 4));
    */
}

inline void DashboardEstudianteScreen::_dibujarInterfazCompleta()
{
    system("cls");
    UI_StudentDashboard();

    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);

    // Renderizar todas las secciones
    _renderizarHeader();
    _renderizarMenuSuperior();
    _renderizarCursos();
    _renderizarEspecializaciones();

    resetColor();
}

inline void DashboardEstudianteScreen::_renderizarHeader()
{
    // Renderizar elementos del header (perfil y configuración)
    for (int i = 0; i < MAX_ELEMENTOS_HEADER; ++i)
    {
        bool seleccionado = (_seccionActual == SECCION_HEADER && _elementoActual == i);
        
        gotoXY(_coordsElementosHeader[i].X, _coordsElementosHeader[i].Y);
        
        if (seleccionado)
        {
            setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::HOVER_ESTADO);
        }
        else
        {
            setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::BLANCO_PURO);
        }

		std::cout << _elementosHeader[i];
        
        resetColor();
    }
}

inline void DashboardEstudianteScreen::_renderizarMenuSuperior()
{
    // Renderizar elemento del menú superior (explorar contenido)
    bool seleccionado = (_seccionActual == SECCION_MENU_SUPERIOR && _elementoActual == 0);
    
    gotoXY(_coordsElementosMenu[0].X, _coordsElementosMenu[0].Y);
    
    if (seleccionado)
    {
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::HOVER_ESTADO);
    }
    else
    {
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_AZUL_SUAVE);
    }

    std::cout << _elementosMenu[0];
    resetColor();
}

inline void DashboardEstudianteScreen::_renderizarCursos()
{
    // Renderizar tarjetas de cursos siguiendo el patrón del LandingPage
    for (int i = 0; i < MAX_ELEMENTOS_CURSOS && i < _cursosInscritos.size(); ++i)
    {
        bool seleccionado = (_seccionActual == SECCION_CURSOS && _elementoActual == i);
        
        _actualizarElementoGenerico(
            _coordsTituloCursos[i],
            _coordsDescCursos[i],
            _cursosInscritos[i].titulo,
            _cursosInscritos[i].descripcion,
            seleccionado
        );
    }
}

inline void DashboardEstudianteScreen::_renderizarEspecializaciones()
{
    // Renderizar tarjetas de especializaciones siguiendo el patrón del LandingPage
    for (int i = 0; i < MAX_ELEMENTOS_ESPECIALIZACIONES && i < _especializacionesInscritas.size(); ++i)
    {
        bool seleccionado = (_seccionActual == SECCION_ESPECIALIZACIONES && _elementoActual == i);
        
        _actualizarElementoGenerico(
            _coordsTituloEspecializaciones[i],
            _coordsDescEspecializaciones[i],
            _especializacionesInscritas[i].titulo,
            _especializacionesInscritas[i].descripcion,
            seleccionado
        );
    }
}

inline void DashboardEstudianteScreen::_actualizarSeleccion()
{
    // Solo actualizar si hay cambio de selección
    if (_seccionAnterior != _seccionActual || _elementoAnterior != _elementoActual)
    {
        // Redibujar la sección anterior
        if (_seccionAnterior >= 0)
        {
            switch (_seccionAnterior)
            {
            case SECCION_HEADER:
                _renderizarHeader();
                break;
            case SECCION_MENU_SUPERIOR:
                _renderizarMenuSuperior();
                break;
            case SECCION_CURSOS:
                _renderizarCursos();
                break;
            case SECCION_ESPECIALIZACIONES:
                _renderizarEspecializaciones();
                break;
            }
        }

        // Redibujar la sección actual
        switch (_seccionActual)
        {
        case SECCION_HEADER:
            _renderizarHeader();
            break;
        case SECCION_MENU_SUPERIOR:
            _renderizarMenuSuperior();
            break;
        case SECCION_CURSOS:
            _renderizarCursos();
            break;
        case SECCION_ESPECIALIZACIONES:
            _renderizarEspecializaciones();
            break;
        }

        _seccionAnterior = _seccionActual;
        _elementoAnterior = _elementoActual;
    }
}

inline void DashboardEstudianteScreen::_manejarNavegacion(int tecla)
{
    switch (tecla) {
    case 72: // Flecha arriba
        if (_seccionActual > 0)
        {
            _seccionActual--;
            _elementoActual = (std::min)(_elementoActual, _obtenerMaxElementosEnSeccion(_seccionActual) - 1);
        }
        else
        {
            _seccionActual = TOTAL_SECCIONES - 1;
            _elementoActual = (std::min)(_elementoActual, _obtenerMaxElementosEnSeccion(_seccionActual) - 1);
        }
        break;
        
    case 80: // Flecha abajo
        if (_seccionActual < TOTAL_SECCIONES - 1)
        {
            _seccionActual++;
            _elementoActual = (std::min)(_elementoActual, _obtenerMaxElementosEnSeccion(_seccionActual) - 1);
        }
        else
        {
            _seccionActual = 0;
            _elementoActual = (std::min)(_elementoActual, _obtenerMaxElementosEnSeccion(_seccionActual) - 1);
        }
        break;
        
    case 75: // Flecha izquierda
        if (_elementoActual > 0)
        {
            _elementoActual--;
        }
        else
        {
            _elementoActual = _obtenerMaxElementosEnSeccion(_seccionActual) - 1;
        }
        break;
        
    case 77: // Flecha derecha
        if (_elementoActual < _obtenerMaxElementosEnSeccion(_seccionActual) - 1)
        {
            _elementoActual++;
        }
        else
        {
            _elementoActual = 0;
        }
        break;
    }
}

inline void DashboardEstudianteScreen::_calcularPosicionEnSeccion(int indiceGlobal, int& seccion, int& elemento)
{
    int acumulado = 0;
    
    for (int s = 0; s < TOTAL_SECCIONES; ++s)
    {
        int maxElementos = _obtenerMaxElementosEnSeccion(s);
        if (indiceGlobal < acumulado + maxElementos)
        {
            seccion = s;
            elemento = indiceGlobal - acumulado;
            return;
        }
        acumulado += maxElementos;
    }
    
    // Si llegamos aquí, usar los últimos elementos válidos
    seccion = TOTAL_SECCIONES - 1;
    elemento = _obtenerMaxElementosEnSeccion(seccion) - 1;
}

inline int DashboardEstudianteScreen::_calcularIndiceGlobal(int seccion, int elemento)
{
    int indice = 0;
    
    for (int s = 0; s < seccion; ++s)
    {
        indice += _obtenerMaxElementosEnSeccion(s);
    }
    
    return indice + elemento;
}

inline int DashboardEstudianteScreen::_obtenerMaxElementosEnSeccion(int seccion)
{
    switch (seccion)
    {
    case SECCION_HEADER:
        return MAX_ELEMENTOS_HEADER;
    case SECCION_MENU_SUPERIOR:
        return MAX_ELEMENTOS_MENU_SUPERIOR;
    case SECCION_CURSOS:
        return (std::min)(MAX_ELEMENTOS_CURSOS, static_cast<int>(_cursosInscritos.size()));
    case SECCION_ESPECIALIZACIONES:
        return (std::min)(MAX_ELEMENTOS_ESPECIALIZACIONES, static_cast<int>(_especializacionesInscritas.size()));
    default:
        return 1;
    }
}

inline ResultadoPantalla DashboardEstudianteScreen::_procesarSeleccion()
{
    switch (_seccionActual)
    {
    case SECCION_HEADER:
        if (_elementoActual == 0) // MI PERFIL
        {
            return ResultadoPantalla(AccionPantalla::IR_A_PERFIL_ESTUDIANTE);
        }
        else if (_elementoActual == 1) // SALIR
        {
            return ResultadoPantalla(AccionPantalla::IR_A_LOGIN);
        }
        break;
        
    case SECCION_MENU_SUPERIOR:
        if (_elementoActual == 0) // EXPLORAR CURSOS Y ESPECIALIDADES
        {
            return ResultadoPantalla(AccionPantalla::IR_A_EXPLORAR_CURSOS_Y_ESPECIALIDADES);
        }
        break;
        
    case SECCION_CURSOS:
        if (_elementoActual < _cursosInscritos.size())
        {
            // TODO: Aquí se podría pasar el ID del curso seleccionado
            int idCurso = _cursosInscritos[_elementoActual].idActividad;
            ContentManager::getInstance().setCursoIdMostrar(idCurso);
            return ResultadoPantalla(AccionPantalla::IR_A_MOSTRAR_CURSO);
        }
        break;
        
    case SECCION_ESPECIALIZACIONES:
        if (_elementoActual < _especializacionesInscritas.size())
        {
            // TODO: Aquí se podría pasar el ID de la especialización seleccionada
			int idEspecializacion = _especializacionesInscritas[_elementoActual].idActividad;
            ContentManager::getInstance().setEspecializacionIdMostar(idEspecializacion);
            return ResultadoPantalla(AccionPantalla::IR_A_MOSTRAR_ESPECIALIZACION);
        }
        break;
    }
    
    return ResultadoPantalla(AccionPantalla::NINGUNA);
}

inline ResultadoPantalla DashboardEstudianteScreen::ejecutar()
{
    _limpiarEstado();
    _cargarDatosDummy();
    
    if (_primeraRenderizacion)
    {
        _dibujarInterfazCompleta();
        _primeraRenderizacion = false;
    }

    while (true)
    {
        _actualizarSeleccion();

        int tecla = _getch();

        // Verificar si es una tecla especial (códigos extendidos)
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
                return _procesarSeleccion();

            case 27: // ESC - Salir al login
                return ResultadoPantalla(AccionPantalla::IR_A_LOGIN);

            default:
                // Ignorar otras teclas
                break;
            }
        }    }
}

// ---- MÉTODOS DE FORMATEO ----

inline void DashboardEstudianteScreen::_actualizarElementoGenerico(const COORD& coordTitulo, const COORD& coordDesc, 
                                                                  const std::string& titulo, const std::string& descripcion, bool seleccionado)
{
    // Configurar colores según selección
    if (seleccionado) {
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::HOVER_ESTADO);
    }
    else {
        setConsoleColor(ColorIndex::TEXTO_IMPORTANTE, ColorIndex::FONDO_PRINCIPAL);
    }

    // Mostrar título
    _mostrarTituloFormateado(coordTitulo, titulo);

    // Cambiar color para descripción
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    
    // Mostrar descripción
    _mostrarDescripcionFormateada(coordDesc, descripcion);

    resetColor();
}

inline void DashboardEstudianteScreen::_mostrarTituloFormateado(const COORD& coord, const std::string& titulo)
{
    // Limpiar área del título
    gotoXY(coord.X, coord.Y);
    std::cout << std::string(MAX_ANCHO_CARACTERES_CUADRO, ' ');

    // Mostrar título truncado si es necesario
    gotoXY(coord.X, coord.Y);
    std::string tituloTruncado = _truncarTitulo(titulo, MAX_ANCHO_CARACTERES_CUADRO);
    std::cout << tituloTruncado;
}

inline void DashboardEstudianteScreen::_mostrarDescripcionFormateada(const COORD& coord, const std::string& descripcion)
{
    std::string descFormateada = _formatearDescripcion(
        descripcion,
        MAX_ANCHO_CARACTERES_CUADRO,
        MAX_ALTO_CARACTERES_CUADRO
    );

    // Dividir en líneas (método simplificado)
    std::vector<std::string> lineas;
    std::stringstream ss(descFormateada);
    std::string linea;
    
    while (std::getline(ss, linea, '\n')) {
        lineas.push_back(linea);
    }

    // Mostrar cada línea
    for (size_t i = 0; i < lineas.size() && i < MAX_ALTO_CARACTERES_CUADRO; ++i) {
        gotoXY(coord.X, coord.Y + i);
        std::cout << std::string(MAX_ANCHO_CARACTERES_CUADRO, ' ');  // Limpiar línea
        gotoXY(coord.X, coord.Y + i);
        std::cout << lineas[i];
    }

    // Limpiar líneas sobrantes
    for (size_t i = lineas.size(); i < MAX_ALTO_CARACTERES_CUADRO; ++i) {
        gotoXY(coord.X, coord.Y + i);
        std::cout << std::string(MAX_ANCHO_CARACTERES_CUADRO, ' ');
    }
}

inline std::string DashboardEstudianteScreen::_truncarTitulo(const std::string& titulo, int maxLongitud)
{
    if (titulo.length() <= maxLongitud) {
        return titulo;
    }
    return titulo.substr(0, maxLongitud - 3) + "...";
}

inline std::string DashboardEstudianteScreen::_formatearDescripcion(const std::string& texto, int anchoMax, int altoMax)
{
    std::string resultado;
    std::string textoRestante = texto;

    for (int linea = 0; linea < altoMax; ++linea) {
        if (textoRestante.empty()) break;

        // Manejo de la última línea
        if (linea == altoMax - 1 && textoRestante.length() > anchoMax) {
            resultado += textoRestante.substr(0, anchoMax - 3) + "...";
            break;
        }

        // Procesamiento de línea normal
        if (textoRestante.length() <= anchoMax) {
            resultado += textoRestante;
            textoRestante.clear();
        }
        else {
            // Buscar punto de corte óptimo
            int posCorte = anchoMax;
            while (posCorte > 0 && textoRestante[posCorte] != ' ' && textoRestante[posCorte - 1] != ' ') {
                posCorte--;
            }
            
            if (posCorte <= 0) {
                posCorte = anchoMax;
            }
            
            resultado += textoRestante.substr(0, posCorte);
            textoRestante = textoRestante.substr(posCorte);
            textoRestante.erase(0, textoRestante.find_first_not_of(" "));
        }

        // Agregar salto de línea si no es la última
        if (linea < altoMax - 1 && !textoRestante.empty()) {
            resultado += "\n";
        }
    }

    return resultado;
}


#endif // COURSERACLONE_SCREENS_DASHBOARDESTUDIANTESCREEN_HPP