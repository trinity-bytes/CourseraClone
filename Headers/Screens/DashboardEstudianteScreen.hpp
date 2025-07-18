#ifndef COURSERACLONE_SCREENS_DASHBOARDESTUDIANTESCREEN_HPP
#define COURSERACLONE_SCREENS_DASHBOARDESTUDIANTESCREEN_HPP

// Headers de librería estándar
#include <conio.h>    // Para _getch()
#include <sstream>    // Para std::stringstream
#include <string>
#include <vector>
#include <random>     // Para generación de números aleatorios
#include <chrono>     // Para semilla temporal

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
    static const int MAX_ELEMENTOS_HEADER = 2;            // Ver mi perfil, Cerrar sesión
    static const int MAX_ELEMENTOS_MENU_SUPERIOR = 1;     // Explorar contenido
    static const int MAX_ELEMENTOS_CURSOS = 4;            // "Ver todos" + 3 cursos
    static const int MAX_ELEMENTOS_ESPECIALIZACIONES = 4; // "Ver todas" + 3 especializaciones
    static const int TOTAL_ELEMENTOS_NAVEGABLES = MAX_ELEMENTOS_HEADER + MAX_ELEMENTOS_MENU_SUPERIOR + MAX_ELEMENTOS_CURSOS + MAX_ELEMENTOS_ESPECIALIZACIONES;
    
    /// @brief Constantes de formateo de texto (siguiendo patrón del LandingPage)
    static const int MAX_ANCHO_CARACTERES_CUADRO = 32;
    static const int MAX_ALTO_CARACTERES_CUADRO = 3;

    /// @brief Datos del usuario logueado
    std::string _nombreEstudiante;
    int _idEstudiante;

    /// @brief Sistema de frases motivacionales
    std::string _fraseMotivacional;
    std::string _autorFrase;

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

    /// @brief Coordenadas para el nombre del estudiante y frase motivacional
    COORD _coordNombreEstudiante = {15, 5};        // Posición del saludo personalizado
    COORD _coordFraseMotivacional = {50, 5};       // Posición de la frase motivacional
    COORD _coordAutorFrase = {80, 7};              // Posición del autor (más a la derecha)

    /// @brief Coordenadas para títulos y descripciones de cursos
    COORD _coordsTituloCursos[MAX_ELEMENTOS_CURSOS] = {
        {20, 11}, {8, 13}, {44, 13}, {80, 13}  // "Ver todos" + 3 cursos
    };
    COORD _coordsDescCursos[MAX_ELEMENTOS_CURSOS] = {
        {23, 12}, {8, 15}, {44, 15}, {80, 15}  // "Ver todos" no tiene descripción
    };
    
    /// @brief Coordenadas para títulos y descripciones de especializaciones
    COORD _coordsTituloEspecializaciones[MAX_ELEMENTOS_ESPECIALIZACIONES] = {
        {30, 20}, {8, 22}, {44, 22}, {80, 22}  // "Ver todas" + 3 especializaciones
    };
    COORD _coordsDescEspecializaciones[MAX_ELEMENTOS_ESPECIALIZACIONES] = {
        {28, 22}, {8, 24}, {44, 24}, {80, 24}  // "Ver todas" no tiene descripción
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

    /// @brief Frases motivacionales con sus autores
    std::vector<std::pair<std::string, std::string>> _frasesMotivacionales = {
        {"\"El éxito es la suma de pequeños esfuerzos repetidos día tras día.\"", "Robert Collier"},
        {"\"La educación es el arma más poderosa que puedes usar para cambiar el mundo.\"", "Nelson Mandela"},
        {"\"El aprendizaje nunca agota la mente.\"", "Leonardo da Vinci"},
        {"\"Invierte en tu educación, es la mejor inversión que puedes hacer.\"", "Benjamin Franklin"},
        {"\"El conocimiento es poder.\"", "Francis Bacon"},
        {"\"No dejes que lo que no puedes hacer interfiera con lo que puedes hacer.\"", "John Wooden"},
        {"\"El único modo de hacer un gran trabajo es amar lo que haces.\"", "Steve Jobs"},
        {"\"La perseverancia es la base de todas las acciones.\"", "Lao Tzu"},
        {"\"Cada día es una nueva oportunidad para aprender algo nuevo.\"", "Anónimo"},
        {"\"El futuro pertenece a quienes creen en la belleza de sus sueños.\"", "Eleanor Roosevelt"}
    };

	// ---- METODOS PRIVADOS ----

    /// @brief Métodos de inicialización
    inline void _limpiarEstado();
    inline void _cargarDatosDummy();
    inline void _cargarDatosUsuario();
    inline void _seleccionarFraseAleatoria();

    /// @brief Métodos de renderizado
    inline void _dibujarInterfazCompleta();
    inline void _renderizarHeader();
    inline void _renderizarMenuSuperior();
    inline void _renderizarCursos();
    inline void _renderizarEspecializaciones();
    inline void _renderizarInformacionPersonal();
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
    _nombreEstudiante("Estudiante"), _idEstudiante(1),
    _seccionActual(0), _elementoActual(0), _seccionAnterior(-1), _elementoAnterior(-1),
    _primeraRenderizacion(true), _indCursoVisible(0), _indEspVisible(0) {
    _cargarDatosUsuario();
    _seleccionarFraseAleatoria();
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

inline void DashboardEstudianteScreen::_cargarDatosUsuario()
{
    // Cargar datos del usuario desde SessionManager si está logueado
    if (SessionManager::getInstance().isLoggedIn()) {
        Usuario& currentUser = SessionManager::getInstance().getCurrentUser();
        _nombreEstudiante = currentUser.getNombreCompleto();
        _idEstudiante = currentUser.getId();
    } else {
        // Datos por defecto si no hay sesión
        _nombreEstudiante = "Estudiante Invitado";
        _idEstudiante = 0;
    }
}

inline void DashboardEstudianteScreen::_seleccionarFraseAleatoria()
{
    // Usar generador de números aleatorios para seleccionar una frase
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, _frasesMotivacionales.size() - 1);
    
    int indiceAleatorio = dis(gen);
    _fraseMotivacional = _frasesMotivacionales[indiceAleatorio].first;
    _autorFrase = "- " + _frasesMotivacionales[indiceAleatorio].second;
}

inline void DashboardEstudianteScreen::_dibujarInterfazCompleta()
{
    system("cls");
    UI_StudentDashboard();

    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);

    // Renderizar información personal del estudiante
    _renderizarInformacionPersonal();

    // Renderizar todas las secciones
    _renderizarHeader();
    _renderizarMenuSuperior();
    _renderizarCursos();
    _renderizarEspecializaciones();

    resetColor();
}

inline void DashboardEstudianteScreen::_renderizarHeader()
{
    // Renderizar elementos del header usando el método específico
    for (int i = 0; i < MAX_ELEMENTOS_HEADER; ++i)
    {
        bool seleccionado = (_seccionActual == SECCION_HEADER && _elementoActual == i);
        _renderizarElementoHeader(i, seleccionado);
    }
}

inline void DashboardEstudianteScreen::_renderizarMenuSuperior()
{
    // Renderizar elemento del menú superior usando el método específico
    for (int i = 0; i < MAX_ELEMENTOS_MENU_SUPERIOR; ++i)
    {
        bool seleccionado = (_seccionActual == SECCION_MENU_SUPERIOR && _elementoActual == i);
        _renderizarElementoMenu(i, seleccionado);
    }
}

inline void DashboardEstudianteScreen::_renderizarCursos()
{
    // Renderizar botón "Ver todos"
    _renderizarElementoCurso(0, _seccionActual == SECCION_CURSOS && _elementoActual == 0);
    
    // Renderizar cursos individuales
    for (int i = 1; i < MAX_ELEMENTOS_CURSOS && i <= _cursosInscritos.size(); ++i) {
        _renderizarElementoCurso(i, _seccionActual == SECCION_CURSOS && _elementoActual == i);
    }
}

inline void DashboardEstudianteScreen::_renderizarEspecializaciones()
{
    // Renderizar botón "Ver todas"
    _renderizarElementoEspecializacion(0, _seccionActual == SECCION_ESPECIALIZACIONES && _elementoActual == 0);
    
    // Renderizar especializaciones individuales
    for (int i = 1; i < MAX_ELEMENTOS_ESPECIALIZACIONES && i <= _especializacionesInscritas.size(); ++i) {
        _renderizarElementoEspecializacion(i, _seccionActual == SECCION_ESPECIALIZACIONES && _elementoActual == i);
    }
}

inline void DashboardEstudianteScreen::_renderizarInformacionPersonal()
{
    // Renderizar saludo personalizado
    gotoXY(_coordNombreEstudiante.X, _coordNombreEstudiante.Y);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_AZUL_SUAVE);
    std::cout << "¡Bienvenid@, " << _nombreEstudiante << "!";
    
    // Renderizar frase motivacional
    gotoXY(_coordFraseMotivacional.X, _coordFraseMotivacional.Y);
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_AZUL_SUAVE);
    
    // Formatear la frase para que no exceda el ancho de pantalla
    std::string fraseFormateada = _fraseMotivacional;
    const int MAX_ANCHO_FRASE = 50; // Ancho máximo para la frase
    
    if (fraseFormateada.length() > MAX_ANCHO_FRASE) {
        // Buscar el último espacio antes del límite
        size_t puntoCorte = fraseFormateada.find_last_of(' ', MAX_ANCHO_FRASE);
        if (puntoCorte != std::string::npos) {
            std::string primeraLinea = fraseFormateada.substr(0, puntoCorte);
            std::string segundaLinea = fraseFormateada.substr(puntoCorte + 1);
            
            std::cout << primeraLinea;
            gotoXY(_coordFraseMotivacional.X, _coordFraseMotivacional.Y + 1);
            std::cout << segundaLinea;
        } else {
            std::cout << fraseFormateada;
        }
    } else {
        std::cout << fraseFormateada;
    }
    
    // Renderizar autor
    gotoXY(_coordAutorFrase.X, _coordAutorFrase.Y);
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    std::cout << _autorFrase;
    
    resetColor();
}

inline void DashboardEstudianteScreen::_actualizarSeleccion()
{
    // Solo actualizar si hay cambio de selección
    if (_seccionAnterior != _seccionActual || _elementoAnterior != _elementoActual)
    {
        // Actualizar elemento anterior
        if (_seccionAnterior >= 0 && _elementoAnterior >= 0) {
            switch (_seccionAnterior) {
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

        // Actualizar elemento actual
        switch (_seccionActual) {
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
inline void DashboardEstudianteScreen::_manejarNavegacionVertical(int direccion)
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
inline void DashboardEstudianteScreen::_manejarNavegacionHorizontal(int direccion)
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
        return MAX_ELEMENTOS_CURSOS;
    case SECCION_ESPECIALIZACIONES:
        return MAX_ELEMENTOS_ESPECIALIZACIONES;
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
        if (_elementoActual == 0) {
            // Ver todos los cursos - Navegar a ListarMisInscripciones
            return ResultadoPantalla(AccionPantalla::IR_A_LISTAR_MIS_INSCRIPCIONES);
        } else {
            // Ver curso específico
            int cursoIndex = _elementoActual - 1;
            if (cursoIndex < _cursosInscritos.size()) {
                int idCurso = _cursosInscritos[cursoIndex].idActividad;
                ContentManager::getInstance().setCursoIdMostrar(idCurso);
                return ResultadoPantalla(AccionPantalla::IR_A_MOSTRAR_CURSO);
            }
        }
        break;
        
    case SECCION_ESPECIALIZACIONES:
        if (_elementoActual == 0) {
            // Ver todas las especializaciones - Navegar a ListarMisInscripciones
            return ResultadoPantalla(AccionPantalla::IR_A_LISTAR_MIS_INSCRIPCIONES);
        } else {
            // Ver especialización específica
            int espIndex = _elementoActual - 1;
            if (espIndex < _especializacionesInscritas.size()) {
                int idEspecializacion = _especializacionesInscritas[espIndex].idActividad;
                ContentManager::getInstance().setEspecializacionIdMostar(idEspecializacion);
                return ResultadoPantalla(AccionPantalla::IR_A_MOSTRAR_ESPECIALIZACION);
            }
        }
        break;
    }
    
    return ResultadoPantalla(AccionPantalla::NINGUNA);
}

inline ResultadoPantalla DashboardEstudianteScreen::ejecutar()
{
    _limpiarEstado();
    _cargarDatosUsuario();  // Actualizar datos del usuario
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
        }
    }
}

// ---- MÉTODOS DE RENDERIZADO ESPECÍFICOS ----

// Renderizar elemento del header
inline void DashboardEstudianteScreen::_renderizarElementoHeader(int indice, bool seleccionado)
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
inline void DashboardEstudianteScreen::_renderizarElementoMenu(int indice, bool seleccionado)
{
    if (indice < 0 || indice >= MAX_ELEMENTOS_MENU_SUPERIOR) return;
    
    gotoXY(_coordsElementosMenu[indice].X, _coordsElementosMenu[indice].Y);
    
    if (seleccionado) {
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::HOVER_ESTADO);
    } else {
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_AZUL_SUAVE);
    }
    
    std::cout << _elementosMenu[indice];
    resetColor();
}

// Renderizar elemento de curso
inline void DashboardEstudianteScreen::_renderizarElementoCurso(int indice, bool seleccionado)
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
        if (cursoIndex < _cursosInscritos.size()) {
            // Renderizar título con colores según selección
            gotoXY(_coordsTituloCursos[indice].X, _coordsTituloCursos[indice].Y);
            if (seleccionado) {
                setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
            } else {
                setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
            }
            std::string tituloTruncado = _truncarTitulo(_cursosInscritos[cursoIndex].titulo, MAX_ANCHO_CARACTERES_CUADRO);
            std::cout << tituloTruncado;
            
            // Renderizar descripción usando el método que maneja correctamente las líneas múltiples
            setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
            _mostrarDescripcionFormateada(_coordsDescCursos[indice], _cursosInscritos[cursoIndex].descripcion);
        }
    }
    
    resetColor();
}

// Renderizar elemento de especialización
inline void DashboardEstudianteScreen::_renderizarElementoEspecializacion(int indice, bool seleccionado)
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
        if (espIndex < _especializacionesInscritas.size()) {
            // Renderizar título con colores según selección
            gotoXY(_coordsTituloEspecializaciones[indice].X, _coordsTituloEspecializaciones[indice].Y);
            if (seleccionado) {
                setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
            } else {
                setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
            }
            std::string tituloTruncado = _truncarTitulo(_especializacionesInscritas[espIndex].titulo, MAX_ANCHO_CARACTERES_CUADRO);
            std::cout << tituloTruncado;
            
            // Renderizar descripción usando el método que maneja correctamente las líneas múltiples
            setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
            _mostrarDescripcionFormateada(_coordsDescEspecializaciones[indice], _especializacionesInscritas[espIndex].descripcion);
        }
    }
    
    resetColor();
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