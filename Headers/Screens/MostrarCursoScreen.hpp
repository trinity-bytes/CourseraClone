#ifndef COURSERACLONE_SCREENS_MOSTRARCURSOSCREEN_HPP
#define COURSERACLONE_SCREENS_MOSTRARCURSOSCREEN_HPP

// Headers estándar
#include <vector>
#include <string>
#include <sstream>
#include <conio.h>

// Headers propios
#include "../Utils/ScreenSystem.hpp"
#include "../Utils/SystemUtils.hpp"
#include "../Utils/UI_Ascii.hpp"
#include "../Types/UsuarioTypes.hpp"
#include "../Controllers/ContentManager.hpp"
#include "../Controllers/SessionManager.hpp"

/// Pantalla para mostrar curso con detalles y clases asociadas
class MostrarCursoScreen : public PantallaBase
{
private:
    // Datos del curso
    int _idCurso;
    std::string _tituloCurso;
    std::string _descripcionCurso;
    std::string _organizacionCurso;
    
    // Estado de navegación
    TipoUsuario _tipoUsuario;
    AccionPantalla _pantallaAnterior;
    bool _primeraRenderizacion;
    bool _yaInscrito; // Estado de inscripción
    bool _yaPagado;
    bool _yaCompletado;
    
    // Navegación
    int _elementoActual; // 0-4 para clases, 5 para botón inscribirse
    int _totalElementos; // Clases + botón inscribirse (si es estudiante)
    bool _enBotonInscribirse; // true si está en el botón

    static const int MAX_CLASES = 5; // 5 clases en total
    static const int MAX_BOTONES_EXTRA = 1; // Botón "Inscribirme"
    static const int LONGITUD_ORGANIZACION_CURSO = 40;
    static const int LONGITUD_DESCRIPCION_CURSO = 40;
    static const int LONGITUD_TITULO_CURSO = 35;
    static const int LONGITUD_CLASE = 40;
    
    /// @brief Elementos de botones
    std::vector<std::string> _elementosBotones = {
        " INSCRIBIRME ",
        "  COMPLETAR  ",
        "    PAGAR    ",
        " COMPLETADO  ",
    };

    /// @brief Contenido de clases
    std::vector<ElementoMenu> _clases;
    
    /// @brief Coordenadas para información del curso
    COORD _coordTituloCurso = {14, 5};
    COORD _coordDescripcionCurso = {4, 12};
    COORD _coordOrganizacion = {4, 8};
    
    /// @brief Coordenadas para el botón inscribirme
    COORD _coordBotonInscribirse = {20, 26};

    /// @brief Coordenadas para las clases (lista vertical)
    COORD _coordsClases[MAX_CLASES] = {
        {61, 9}, {61, 13}, {61, 17}, {61, 21}, {61, 25}
    };

    // ---- MÉTODOS PRIVADOS ----
    
    /// @brief Métodos de inicialización
    inline void _limpiarEstado();
    inline void _cargarDatosDummy(int _idProvisional);
    inline void _cargarDatosCurso();

    /// @brief Métodos de renderizado
    inline void dibujarInterfazCompleta();
    inline void _renderizarInformacionCurso();
    inline void _renderizarClases();
    inline void _renderizarBotonInscribirse(bool seleccionado);
    inline void _renderizarClase(int indice, bool seleccionada);
    inline void _actualizarSeleccion();

    /// @brief Métodos de navegación
    inline void _manejarNavegacion(int tecla);
    inline bool _esBotonInscribirse() const;
    inline int _obtenerIndiceClaseActual() const;

    /// @brief Métodos de formateo
    inline std::string truncarTitulo(const std::string& titulo, int maxLongitud);
    inline std::vector<std::string> formatearTextoMultilinea(const std::string& texto, int anchoMax);
    inline std::string formatearDescripcion(const std::string& texto, int anchoMax, int altoMax);
    inline int encontrarPuntoCorte(const std::string& texto, int anchoMax);
    inline std::vector<std::string> dividirEnLineas(const std::string& texto);

    /// @brief Métodos de procesamiento
    inline ResultadoPantalla _procesarSeleccion();

public:
    inline MostrarCursoScreen(int idCurso = 1, 
                             TipoUsuario tipoUsuario = TipoUsuario::ESTUDIANTE,
                             AccionPantalla pantallaAnterior = AccionPantalla::IR_A_MOSTRAR_ESPECIALIZACION);
    
    inline ~MostrarCursoScreen() = default;

    inline ResultadoPantalla ejecutar() override;
};

// --- IMPLEMENTACIONES INLINE ---

// Constructor
inline MostrarCursoScreen::MostrarCursoScreen(int idCurso, 
                                             TipoUsuario tipoUsuario,
                                             AccionPantalla pantallaAnterior) : PantallaBase(),
    _idCurso(idCurso), _tipoUsuario(tipoUsuario), _pantallaAnterior(pantallaAnterior),
    _primeraRenderizacion(true), _elementoActual(0), _enBotonInscribirse(false), _yaInscrito(false)
{
    _idCurso = ContentManager::getInstance().getCursoIdMostrar();
    if (SessionManager::getInstance().isLoggedIn()) {
        SessionManager::getInstance().getInscripcionesController().reportarDatosInscripcion(_yaInscrito, _yaPagado, _yaCompletado, TipoActividad::CURSO, _idCurso);
        _tipoUsuario = SessionManager::getInstance().getCurrentUser().getTipoUsuario();
    }
    else {
        _yaInscrito = false;
        _tipoUsuario = TipoUsuario::DEFAULT;
    }

    if (_idCurso == -1) {
        _cargarDatosDummy(101);
    }
    else {
        _cargarDatosCurso();
    }
    
    
    // Calcular total de elementos navegables
    _totalElementos = _clases.size();
    if (_tipoUsuario == TipoUsuario::ESTUDIANTE) {
        _totalElementos += 1; // Agregar botón inscribirse
    }
}

// Limpiar estado
inline void MostrarCursoScreen::_limpiarEstado()
{
    _elementoActual = 0;
    _enBotonInscribirse = false;
    _primeraRenderizacion = true;
}

// Cargar datos de ejemplo
inline void MostrarCursoScreen::_cargarDatosDummy(int _idProvisional = 101)
{
    // Datos del curso basados en el ID
    switch (_idProvisional) {
    case 101:
        _tituloCurso = "Fundamentos de Programación";
        _descripcionCurso = "Aprende los conceptos básicos de programación usando Python, incluyendo variables, estructuras de control, funciones y programación orientada a objetos.";
        _organizacionCurso = "Universidad Peruana de Ciencias Aplicadas";
        _clases.clear();
        _clases.push_back(ElementoMenu("Introducción a Python", "Variables, tipos de datos y operadores", 1));
        _clases.push_back(ElementoMenu("Estructuras de Control", "If, while, for y control de flujo", 2));
        _clases.push_back(ElementoMenu("Funciones y Módulos", "Definición y uso de funciones", 3));
        _clases.push_back(ElementoMenu("Programación Orientada a Objetos", "Clases, objetos y herencia", 4));
        _clases.push_back(ElementoMenu("Proyecto Final", "Desarrollo de aplicación completa", 5));
        break;
        
    case 102:
        _tituloCurso = "Estructuras de Datos";
        _descripcionCurso = "Domina las estructuras de datos fundamentales como listas, pilas, colas, árboles y grafos, con implementaciones prácticas y análisis de complejidad.";
        _organizacionCurso = "Universidad Peruana de Ciencias Aplicadas";
        _clases.clear();
        _clases.push_back(ElementoMenu("Listas y Arrays", "Implementación y operaciones básicas", 1));
        _clases.push_back(ElementoMenu("Pilas y Colas", "Estructuras LIFO y FIFO", 2));
        _clases.push_back(ElementoMenu("Árboles Binarios", "BST, AVL y operaciones", 3));
        _clases.push_back(ElementoMenu("Grafos y Algoritmos", "BFS, DFS y caminos mínimos", 4));
        _clases.push_back(ElementoMenu("Hash Tables", "Implementación y manejo de colisiones", 5));
        break;
        
    case 103:
        _tituloCurso = "Ingeniería de Software";
        _descripcionCurso = "Aprende metodologías ágiles, gestión de proyectos de software, pruebas, documentación y mejores prácticas del desarrollo profesional.";
        _organizacionCurso = "Universidad Peruana de Ciencias Aplicadas";
        _clases.clear();
        _clases.push_back(ElementoMenu("Metodologías Ágiles", "Scrum, Kanban y DevOps", 1));
        _clases.push_back(ElementoMenu("Gestión de Proyectos", "Planificación y seguimiento", 2));
        _clases.push_back(ElementoMenu("Testing y QA", "Pruebas unitarias e integración", 3));
        _clases.push_back(ElementoMenu("Documentación Técnica", "APIs, specs y manuales", 4));
        _clases.push_back(ElementoMenu("Deployment y CI/CD", "Automatización y despliegue", 5));
        break;
        
    case 104:
        _tituloCurso = "Arquitectura de Software";
        _descripcionCurso = "Diseña sistemas escalables y robustos aprendiendo patrones de arquitectura, microservicios, bases de datos y sistemas distribuidos.";
        _organizacionCurso = "Universidad Peruana de Ciencias Aplicadas";
        _clases.clear();
        _clases.push_back(ElementoMenu("Patrones de Arquitectura", "MVC, MVP, MVVM y Clean Architecture", 1));
        _clases.push_back(ElementoMenu("Microservicios", "Diseño y comunicación entre servicios", 2));
        _clases.push_back(ElementoMenu("Bases de Datos", "SQL, NoSQL y optimización", 3));
        _clases.push_back(ElementoMenu("Sistemas Distribuidos", "Consistencia y disponibilidad", 4));
        _clases.push_back(ElementoMenu("Escalabilidad", "Load balancing y caching", 5));
        break;
        
    default:
        _tituloCurso = "Curso de Ejemplo";
        _descripcionCurso = "Este es un curso de ejemplo para demostrar la funcionalidad de la plataforma de aprendizaje en línea.";
        _organizacionCurso = "Universidad Peruana de Ciencias Aplicadas";
        _clases.clear();
        _clases.push_back(ElementoMenu("Clase 1", "Introducción al tema principal", 1));
        _clases.push_back(ElementoMenu("Clase 2", "Conceptos fundamentales", 2));
        _clases.push_back(ElementoMenu("Clase 3", "Práctica guiada", 3));
        _clases.push_back(ElementoMenu("Clase 4", "Ejercicios avanzados", 4));
        _clases.push_back(ElementoMenu("Clase 5", "Proyecto final", 5));
        break;
    }
}

inline void MostrarCursoScreen::_cargarDatosCurso() {
    RawCursoData datosCurso = ContentManager::getInstance().obtenerCursoDatos(_idCurso);
    _tituloCurso = datosCurso.titulo;
    _descripcionCurso = datosCurso.descripcion;
    _organizacionCurso = datosCurso.nombreEmpresa;
    _clases.clear();
   
    for (int i = 0; i < datosCurso.cantidadClases; i++) {
        _clases.push_back(ElementoMenu(datosCurso.descripcionClases[i].first, datosCurso.descripcionClases[i].second));
    }
}

// Dibujar interfaz completa
inline void MostrarCursoScreen::dibujarInterfazCompleta()
{
    system("cls");
    UI_VistaCurso();

    _renderizarInformacionCurso();
    _renderizarClases();
    
    // Solo mostrar botón inscribirse para estudiantes
    if (_tipoUsuario == TipoUsuario::ESTUDIANTE) {
        _renderizarBotonInscribirse(_enBotonInscribirse);
    }

    resetColor();
}

// Renderizar información del curso
inline void MostrarCursoScreen::_renderizarInformacionCurso()
{
    // Título
    gotoXY(_coordTituloCurso.X, _coordTituloCurso.Y);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::string tituloTruncado = truncarTitulo(_tituloCurso, LONGITUD_TITULO_CURSO);
    std::cout << tituloTruncado;

    // Organización (con salto de línea automático)
    std::vector<std::string> lineasOrganizacion = formatearTextoMultilinea(_organizacionCurso, LONGITUD_ORGANIZACION_CURSO);
    for (int i = 0; i < lineasOrganizacion.size() && i < 2; ++i) {
        gotoXY(_coordOrganizacion.X, _coordOrganizacion.Y + i);
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << lineasOrganizacion[i];
    }

    // Descripción (con salto de línea automático)
    std::vector<std::string> lineasDescripcion = formatearTextoMultilinea(_descripcionCurso, LONGITUD_DESCRIPCION_CURSO);
    for (int i = 0; i < lineasDescripcion.size() && i < 4; ++i) {
        gotoXY(_coordDescripcionCurso.X, _coordDescripcionCurso.Y + i);
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << lineasDescripcion[i];
    }

    resetColor();
}

// Renderizar clases
inline void MostrarCursoScreen::_renderizarClases()
{
    for (int i = 0; i < _clases.size() && i < MAX_CLASES; ++i) {
        bool seleccionada = (!_enBotonInscribirse && _elementoActual == i);
        _renderizarClase(i, seleccionada);
    }
}

// Renderizar clase individual
inline void MostrarCursoScreen::_renderizarClase(int indice, bool seleccionada)
{
    if (indice >= _clases.size() || indice >= MAX_CLASES) return;

    gotoXY(_coordsClases[indice].X, _coordsClases[indice].Y);
    
    // Limpiar área de la clase primero
    std::cout << std::string(LONGITUD_CLASE, ' ');
    gotoXY(_coordsClases[indice].X, _coordsClases[indice].Y);
    
    if (seleccionada) {
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
    } else {
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    }
    
    // Mostrar número de clase y título
    std::string textoClase =  _clases[indice].descripcion;
    std::string textoTruncado = truncarTitulo(textoClase, LONGITUD_CLASE);
    std::cout << textoTruncado;

    resetColor();
}

// Renderizar botón inscribirse
inline void MostrarCursoScreen::_renderizarBotonInscribirse(bool seleccionado)
{
    if (_tipoUsuario != TipoUsuario::ESTUDIANTE) return;

    gotoXY(_coordBotonInscribirse.X, _coordBotonInscribirse.Y);
    
    if (seleccionado) {
        if (_yaInscrito) {
            setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::TEXTO_SECUNDARIO);
        } else {
            setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::EXITO_COLOR);
        }
    } else {
        if (_yaInscrito) {
            setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        } else {
            setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
        }
    }

    std::string botonTexto = _elementosBotones[0];
    if (_yaInscrito) {
        if (_yaCompletado) {
            if (_yaPagado) botonTexto = _elementosBotones[3];
            else botonTexto = _elementosBotones[2];
        }
        else {
            botonTexto = _elementosBotones[1];
        }
    }

    std::cout << botonTexto;
    resetColor();
}

// Actualizar selección
inline void MostrarCursoScreen::_actualizarSeleccion()
{
    // Siempre actualizar todo para asegurar que se refleje correctamente la selección
    _renderizarClases();
    
    if (_tipoUsuario == TipoUsuario::ESTUDIANTE) {
        _renderizarBotonInscribirse(_enBotonInscribirse);
    }
}

// Manejar navegación
inline void MostrarCursoScreen::_manejarNavegacion(int tecla)
{
    switch (tecla) {
    case 72: // Flecha arriba
        if (_enBotonInscribirse) {
            // Del botón ir a la última clase
            _enBotonInscribirse = false;
            _elementoActual = _clases.size() - 1;
        } else {
            // Navegación en lista de clases
            if (_elementoActual > 0) {
                _elementoActual--;
            } else {
                // Si está en la primera clase y hay botón, ir al botón
                if (_tipoUsuario == TipoUsuario::ESTUDIANTE) {
                    _enBotonInscribirse = true;
                } else {
                    // Si no hay botón, hacer wrap a la última clase
                    _elementoActual = _clases.size() - 1;
                }
            }
        }
        break;
        
    case 80: // Flecha abajo
        if (_enBotonInscribirse) {
            // Del botón ir a la primera clase
            _enBotonInscribirse = false;
            _elementoActual = 0;
        } else {
            // Navegación en lista de clases
            if (_elementoActual < _clases.size() - 1) {
                _elementoActual++;
            } else {
                // Si está en la última clase y hay botón, ir al botón
                if (_tipoUsuario == TipoUsuario::ESTUDIANTE) {
                    _enBotonInscribirse = true;
                } else {
                    // Si no hay botón, hacer wrap a la primera clase
                    _elementoActual = 0;
                }
            }
        }
        break;
        
    // Las flechas izquierda y derecha no hacen nada en una lista vertical
    case 75: // Flecha izquierda
    case 77: // Flecha derecha
        // No hacer nada en lista vertical
        break;
    }
}

// Verificar si está en el botón inscribirse
inline bool MostrarCursoScreen::_esBotonInscribirse() const
{
    return _enBotonInscribirse;
}

// Obtener índice de la clase actual
inline int MostrarCursoScreen::_obtenerIndiceClaseActual() const
{
    if (_enBotonInscribirse) {
        return -1;
    }
    return _elementoActual;
}

// Truncar título
inline std::string MostrarCursoScreen::truncarTitulo(const std::string& titulo, int maxLongitud)
{
    if (titulo.length() <= maxLongitud) {
        return titulo;
    }
    return titulo.substr(0, maxLongitud - 3) + "...";
}

// Formatear texto en múltiples líneas
inline std::vector<std::string> MostrarCursoScreen::formatearTextoMultilinea(const std::string& texto, int anchoMax)
{
    std::vector<std::string> lineas;
    
    if (texto.length() <= anchoMax) {
        lineas.push_back(texto);
        return lineas;
    }
    
    std::string restante = texto;
    while (!restante.empty()) {
        if (restante.length() <= anchoMax) {
            lineas.push_back(restante);
            break;
        }
        
        // Buscar un espacio cerca del límite para cortar
        int posCorte = anchoMax;
        for (int i = anchoMax - 1; i >= anchoMax - 10 && i >= 0; --i) {
            if (restante[i] == ' ') {
                posCorte = i;
                break;
            }
        }
        
        lineas.push_back(restante.substr(0, posCorte));
        restante = restante.substr(posCorte + (restante[posCorte] == ' ' ? 1 : 0));
    }
    
    return lineas;
}

// Formatear descripción (método mejorado como LandingPageScreen)
inline std::string MostrarCursoScreen::formatearDescripcion(const std::string& texto, int anchoMax, int altoMax)
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
            int posCorte = encontrarPuntoCorte(textoRestante, anchoMax);
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

// Encontrar punto de corte óptimo
inline int MostrarCursoScreen::encontrarPuntoCorte(const std::string& texto, int anchoMax)
{
    int posCorte = anchoMax;

    // Buscar espacio para corte natural
    while (posCorte > 0 && texto[posCorte] != ' ' && texto[posCorte - 1] != ' ') {
        posCorte--;
    }

    // Si no hay espacios, hacer corte forzado
    if (posCorte <= 0) {
        posCorte = anchoMax;
    }

    return posCorte;
}

// Dividir texto en líneas
inline std::vector<std::string> MostrarCursoScreen::dividirEnLineas(const std::string& texto)
{
    std::vector<std::string> lineas;
    std::stringstream ss(texto);
    std::string linea;

    while (std::getline(ss, linea, '\n')) {
        lineas.push_back(linea);
    }

    return lineas;
}



// Procesar selección
inline ResultadoPantalla MostrarCursoScreen::_procesarSeleccion()
{
    ResultadoPantalla res;
    bool registrado = SessionManager::getInstance().isLoggedIn();
    auto restablecer = []() {
        resetColor();
        _getch(); // Pausa para mostrar mensaje

        // Limpiar mensaje
        gotoXY(30, 29);
        std::cout << "                                  ";
        };

    if (_esBotonInscribirse()) {

        if (registrado) {
            if (!_yaInscrito) {
                _yaInscrito = true;
                SessionManager::getInstance().getInscripcionesController().inscribirCurso(_idCurso);

                // Actualizar el botón inmediatamente
                _renderizarBotonInscribirse(true);

                gotoXY(30, 29);
                setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::EXITO_COLOR);
                std::cout << "[ÉXITO]: Te has inscrito al curso";
                restablecer();
            }
            else if (!_yaCompletado) {
                _yaCompletado = true;
                SessionManager::getInstance().getInscripcionesController().completarActividad(TipoActividad::CURSO, _idCurso);
                _renderizarBotonInscribirse(true);

                gotoXY(30, 29);
                setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::EXITO_COLOR);
                std::cout << "[EXITO]: Curso Completado";
                restablecer();
            }
            else if (!_yaPagado) {
                _yaPagado = true;
                _renderizarBotonInscribirse(true);

                gotoXY(30, 29);
                setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::EXITO_COLOR);
                std::cout << "[EXITO]: Curso Pagado";
                restablecer();
            }
            else {
                gotoXY(30, 29);
                setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::EXITO_COLOR);
                std::cout << "[EXITO]: Curso Finalizado";
                restablecer();
            }
        }
		else {
			gotoXY(30, 29);
			setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::ERROR_COLOR);
			std::cout << "[ERROR]: Curso Finalizado";
            restablecer();
		}
        // Si ya está inscrito, no hacer nada
    } else {
        // Ir a la clase seleccionada (simulado)
        int indiceClase = _obtenerIndiceClaseActual();
        if (indiceClase >= 0 && indiceClase < _clases.size()) {
            gotoXY(30, 29);
            setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
            std::cout << "[INFO]: Abriendo " << _clases[indiceClase].titulo;
            resetColor();
            _getch(); // Pausa para mostrar mensaje
            
            // Limpiar mensaje
            gotoXY(30, 29);
            std::cout << "                                           ";
        }
    }
    
    return res;
}

// Método principal de ejecución
inline ResultadoPantalla MostrarCursoScreen::ejecutar()
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
        case 75: // Flecha izquierda (por si acaso)
        case 77: // Flecha derecha (por si acaso)
            _manejarNavegacion(tecla);
            break;

        case 27: // ESC - Regresar a pantalla anterior
        {
            ResultadoPantalla res;
            res.accion = _pantallaAnterior;
            return res;
        }

        case 13: // Enter - Procesar selección
        {
            ResultadoPantalla res = _procesarSeleccion();
            if (res.accion != AccionPantalla::NINGUNA) {
                return res;
            }
        }
        break;

        default:
            // Ignorar otras teclas
            break;
        }
    }
}

#endif // COURSERACLONE_SCREENS_MOSTRARCURSOSCREEN_HPP
