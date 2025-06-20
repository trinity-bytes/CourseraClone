#ifndef COURSERACLONE_SCREENS_MOSTRARESPECIALIDADSCREEN_HPP
#define COURSERACLONE_SCREENS_MOSTRARESPECIALIDADSCREEN_HPP

// Headers estándar
#include <string>
#include <vector>
#include <sstream>
#include <conio.h>

// Headers propios
#include "../Utils/SystemUtils.hpp"
#include "../Utils/ScreenSystem.hpp"
#include "../Utils/UI_Ascii.hpp"
#include "../Types/UsuarioTypes.hpp"

/// Pantalla para mostrar especialización con detalles y cursos asociados
class MostrarEspecialidadScreen : public PantallaBase
{
private:
    // Datos de la especialidad
    int _idEspecializacion;
    std::string _tituloEspecializacion;
    std::string _descripcionEspecializacion;
    std::string _organizacionEspecializacion;
    std::vector<int> _idCursos;    // Estado de navegación
    TipoUsuario _tipoUsuario;
    AccionPantalla _pantallaAnterior;
    bool _primeraRenderizacion;
    bool _yaInscrito; // Estado de inscripción
      // Navegación
    int _elementoActual;
    int _elementoAnterior;
    int _totalElementos; // Cursos + botón inscribirse (si es estudiante)
    
    // Navegación en matriz 2x2 para cursos
    int _filaActual;    // 0-1 (2 filas)
    int _columnaActual; // 0-1 (2 columnas) 
    bool _enBotonInscribirse; // true si está en el botón, false si está en la matriz de cursos

    static const int MAX_BOTONES_EXTRA = 1; // Botón "Inscribirme"
    static const int MAX_CURSOS = 4; // 4 cursos en total
    static const int FILAS_CURSOS = 2;
    static const int COLUMNAS_CURSOS = 2;
    static const int LONGITUD_ORGANIZACION_ESPECIALIDAD = 38;
    static const int LONGITUD_DESCRIPCION_ESPECIALIDAD = 38;
    static const int LONGITUD_TITULO_CURSO_CELDA = 30;
    static const int LONGITUD_DESCRIPCION_CURSO_CELDA = 30;
    
    /// @brief Elementos de botones
    std::vector<std::string> _elementosBotones = {
        " INSCRIBIRME ",
        "  INSCRITO   "
    };

    /// @brief Contenido de cursos
    std::vector<ElementoMenu> _cursos;
    
    /// @brief Coordenadas para información de la especialidad
    COORD _coordTituloEspecializacion = {20, 5};
    COORD _coordDescripcionEspecializacion = {4, 13};
    COORD _coordOrganizacion = {4, 9};
    
    /// @brief Coordenadas para el botón inscribirme
    COORD _coordsBotonesExtra[MAX_BOTONES_EXTRA] = {
        {15, 25}
    };

    /// @brief Coordenadas para títulos de cursos
    COORD _coordsTituloCursos[MAX_CURSOS] = {
        {47, 9}, {83, 9}, {47, 19}, {83, 19}
    };

    /// @brief Coordenadas para descripciones de cursos
    COORD _coordsDescCursos[MAX_CURSOS] = {
        {47, 11}, {83, 11}, {47, 21}, {83, 21}
    };

    // ---- MÉTODOS PRIVADOS ----
    
    /// @brief Métodos de inicialización
    inline void _limpiarEstado();
    inline void _cargarDatosDummy();

    /// @brief Métodos de renderizado
    inline void dibujarInterfazCompleta();
    inline void _renderizarInformacionEspecializacion();
    inline void _renderizarCursos();
    inline void _renderizarBotonInscribirse(bool seleccionado);
    inline void _renderizarCurso(int indice, bool seleccionado);
    inline void _actualizarSeleccion();    /// @brief Métodos de navegación
    inline void _manejarNavegacion(int tecla);
    inline bool _esBotonInscribirse() const;
    inline int _obtenerIndiceCursoActual() const;
    inline void _irACurso(int fila, int columna);
    inline void _irABotonInscribirse();    /// @brief Métodos de formateo
    inline std::string truncarTitulo(const std::string& titulo, int maxLongitud);
    inline std::vector<std::string> formatearTextoMultilinea(const std::string& texto, int anchoMax);
    inline std::string formatearDescripcion(const std::string& texto, int anchoMax, int altoMax);
    inline int encontrarPuntoCorte(const std::string& texto, int anchoMax);
    inline std::vector<std::string> dividirEnLineas(const std::string& texto);

    /// @brief Métodos de procesamiento
    inline ResultadoPantalla _procesarSeleccion();

public:
    inline MostrarEspecialidadScreen(int idEspecializacion = 1, 
                                    TipoUsuario tipoUsuario = TipoUsuario::ESTUDIANTE,
                                    AccionPantalla pantallaAnterior = AccionPantalla::IR_A_LANDING_PAGE);
    
    inline ~MostrarEspecialidadScreen() = default;

    inline ResultadoPantalla ejecutar() override;
};

// --- IMPLEMENTACIONES INLINE ---

// Constructor
inline MostrarEspecialidadScreen::MostrarEspecialidadScreen(int idEspecializacion, 
                                                           TipoUsuario tipoUsuario,
                                                           AccionPantalla pantallaAnterior) : PantallaBase(),
    _idEspecializacion(idEspecializacion), _tipoUsuario(tipoUsuario), _pantallaAnterior(pantallaAnterior),
    _primeraRenderizacion(true), _elementoActual(0), _elementoAnterior(-1),
    _filaActual(0), _columnaActual(0), _enBotonInscribirse(false), _yaInscrito(false)
{
    _cargarDatosDummy();
    
    // Calcular total de elementos navegables
    _totalElementos = _cursos.size();
    if (_tipoUsuario == TipoUsuario::ESTUDIANTE) {
        _totalElementos += 1; // Agregar botón inscribirse
    }
}

// Limpiar estado
inline void MostrarEspecialidadScreen::_limpiarEstado()
{
    _elementoActual = 0;
    _elementoAnterior = -1;
    _filaActual = 0;
    _columnaActual = 0;
    _enBotonInscribirse = false;
    _primeraRenderizacion = true;
}

// Cargar datos de ejemplo
inline void MostrarEspecialidadScreen::_cargarDatosDummy()
{
    // Datos de la especialización
    _tituloEspecializacion = "Ingeniería de Software";
    _descripcionEspecializacion = "Domina el desarrollo profesional de software con metodologías ágiles, arquitectura de sistemas y mejores prácticas de la industria.";
    _organizacionEspecializacion = "Universidad Peruana de Ciencias Aplicadas";

    // Cursos de la especialización
    _cursos.clear();
    _cursos.push_back(ElementoMenu("Fundamentos de Programación", "Introducción a la programación con Python", 101));
    _cursos.push_back(ElementoMenu("Estructuras de Datos", "Algoritmos y estructuras de datos avanzadas", 102));
    _cursos.push_back(ElementoMenu("Ingeniería de Software", "Metodologías ágiles y gestión de proyectos", 103));
    _cursos.push_back(ElementoMenu("Arquitectura de Software", "Diseño de sistemas escalables y robustos", 104));

    // IDs de cursos
    _idCursos.clear();
    for (const auto& curso : _cursos) {
        _idCursos.push_back(curso.id);
    }
}

// Dibujar interfaz completa
inline void MostrarEspecialidadScreen::dibujarInterfazCompleta()
{
    system("cls");
    UI_VistaEspecialidad();

    _renderizarInformacionEspecializacion();
    _renderizarCursos();
      // Solo mostrar botón inscribirse para estudiantes
    if (_tipoUsuario == TipoUsuario::ESTUDIANTE) {
        _renderizarBotonInscribirse(_enBotonInscribirse);
    }

    resetColor();
}

// Renderizar información de la especialización
inline void MostrarEspecialidadScreen::_renderizarInformacionEspecializacion()
{
    // Título
    gotoXY(_coordTituloEspecializacion.X, _coordTituloEspecializacion.Y);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << _tituloEspecializacion;

    // Organización (con salto de línea automático)
    std::vector<std::string> lineasOrganizacion = formatearTextoMultilinea(_organizacionEspecializacion, LONGITUD_ORGANIZACION_ESPECIALIDAD);
    for (int i = 0; i < lineasOrganizacion.size() && i < 2; ++i) {
        gotoXY(_coordOrganizacion.X, _coordOrganizacion.Y + i);
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << lineasOrganizacion[i];
    }

    // Descripción (con salto de línea automático)
    std::vector<std::string> lineasDescripcion = formatearTextoMultilinea(_descripcionEspecializacion, LONGITUD_DESCRIPCION_ESPECIALIDAD);
    for (int i = 0; i < lineasDescripcion.size() && i < 3; ++i) {
        gotoXY(_coordDescripcionEspecializacion.X, _coordDescripcionEspecializacion.Y + i);
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << lineasDescripcion[i];
    }

    resetColor();
}

// Renderizar cursos
inline void MostrarEspecialidadScreen::_renderizarCursos()
{
    for (int i = 0; i < _cursos.size() && i < MAX_CURSOS; ++i) {
        // Verificar si este curso está seleccionado
        int fila = i / COLUMNAS_CURSOS;
        int columna = i % COLUMNAS_CURSOS;
        bool seleccionado = (!_enBotonInscribirse && _filaActual == fila && _columnaActual == columna);
        
        _renderizarCurso(i, seleccionado);
    }
}

// Renderizar curso individual
inline void MostrarEspecialidadScreen::_renderizarCurso(int indice, bool seleccionado)
{
    if (indice >= _cursos.size() || indice >= MAX_CURSOS) return;

    // Título del curso
    gotoXY(_coordsTituloCursos[indice].X, _coordsTituloCursos[indice].Y);
    
    // Limpiar área del título primero
    std::cout << std::string(LONGITUD_TITULO_CURSO_CELDA, ' ');
    gotoXY(_coordsTituloCursos[indice].X, _coordsTituloCursos[indice].Y);
    
    if (seleccionado) {
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
    } else {
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    }
    
    std::string tituloTruncado = truncarTitulo(_cursos[indice].titulo, LONGITUD_TITULO_CURSO_CELDA);
    std::cout << tituloTruncado;

    resetColor();

    // Descripción del curso (SIEMPRE con colores normales, sin selección)
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    
    // Formatear descripción con saltos de línea
    std::string descripcionFormateada = formatearDescripcion(
        _cursos[indice].descripcion, 
        LONGITUD_DESCRIPCION_CURSO_CELDA, 
        2  // Máximo 2 líneas
    );
    
    // Dividir en líneas y mostrar
    std::vector<std::string> lineas = dividirEnLineas(descripcionFormateada);
    
    for (size_t i = 0; i < lineas.size() && i < 2; ++i) {
        gotoXY(_coordsDescCursos[indice].X, _coordsDescCursos[indice].Y + i);
        // Limpiar línea primero
        std::cout << std::string(LONGITUD_DESCRIPCION_CURSO_CELDA, ' ');
        gotoXY(_coordsDescCursos[indice].X, _coordsDescCursos[indice].Y + i);
        std::cout << lineas[i];
    }

    resetColor();
}

// Renderizar botón inscribirse
inline void MostrarEspecialidadScreen::_renderizarBotonInscribirse(bool seleccionado)
{
    if (_tipoUsuario != TipoUsuario::ESTUDIANTE) return;

    gotoXY(_coordsBotonesExtra[0].X, _coordsBotonesExtra[0].Y);
    
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
    
    std::string botonTexto = _yaInscrito ? _elementosBotones[1] : _elementosBotones[0];
    std::cout << botonTexto;
    resetColor();
}

// Actualizar selección
inline void MostrarEspecialidadScreen::_actualizarSeleccion()
{
    // Siempre actualizar todo para asegurar que se refleje correctamente la selección
    _renderizarCursos();
    
    if (_tipoUsuario == TipoUsuario::ESTUDIANTE) {
        _renderizarBotonInscribirse(_enBotonInscribirse);
    }
}

// Manejar navegación
inline void MostrarEspecialidadScreen::_manejarNavegacion(int tecla)
{
    switch (tecla) {
    case 72: // Flecha arriba
        if (_enBotonInscribirse) {
            // Del botón ir a la fila inferior de cursos
            _enBotonInscribirse = false;
            _filaActual = FILAS_CURSOS - 1; // Fila 1
        } else {
            // Navegación en matriz de cursos
            if (_filaActual > 0) {
                _filaActual--;
            } else {
                // Si está en la fila superior y hay botón, ir al botón
                if (_tipoUsuario == TipoUsuario::ESTUDIANTE) {
                    _enBotonInscribirse = true;
                } else {
                    // Si no hay botón, hacer wrap a la fila inferior
                    _filaActual = FILAS_CURSOS - 1;
                }
            }
        }
        break;
        
    case 80: // Flecha abajo
        if (_enBotonInscribirse) {
            // Del botón ir a la fila superior de cursos
            _enBotonInscribirse = false;
            _filaActual = 0;
        } else {
            // Navegación en matriz de cursos
            if (_filaActual < FILAS_CURSOS - 1) {
                _filaActual++;
            } else {
                // Si está en la fila inferior y hay botón, ir al botón
                if (_tipoUsuario == TipoUsuario::ESTUDIANTE) {
                    _enBotonInscribirse = true;
                } else {
                    // Si no hay botón, hacer wrap a la fila superior
                    _filaActual = 0;
                }
            }
        }
        break;
        
    case 75: // Flecha izquierda
        if (!_enBotonInscribirse) {
            // Solo navegar horizontalmente en la matriz de cursos
            if (_columnaActual > 0) {
                _columnaActual--;
            } else {
                _columnaActual = COLUMNAS_CURSOS - 1; // Wrap a la última columna
            }
        }
        break;
        
    case 77: // Flecha derecha
        if (!_enBotonInscribirse) {
            // Solo navegar horizontalmente en la matriz de cursos
            if (_columnaActual < COLUMNAS_CURSOS - 1) {
                _columnaActual++;
            } else {
                _columnaActual = 0; // Wrap a la primera columna
            }
        }
        break;
    }
}

// Verificar si está en el botón inscribirse
inline bool MostrarEspecialidadScreen::_esBotonInscribirse() const
{
    return _enBotonInscribirse;
}

// Obtener índice del curso actual
inline int MostrarEspecialidadScreen::_obtenerIndiceCursoActual() const
{
    if (_enBotonInscribirse) {
        return -1;
    }
    return _filaActual * COLUMNAS_CURSOS + _columnaActual;
}

// Ir a curso específico
inline void MostrarEspecialidadScreen::_irACurso(int fila, int columna)
{
    _enBotonInscribirse = false;
    _filaActual = fila;
    _columnaActual = columna;
}

// Ir al botón inscribirse
inline void MostrarEspecialidadScreen::_irABotonInscribirse()
{
    if (_tipoUsuario == TipoUsuario::ESTUDIANTE) {
        _enBotonInscribirse = true;
    }
}

// Truncar título
inline std::string MostrarEspecialidadScreen::truncarTitulo(const std::string& titulo, int maxLongitud)
{
    if (titulo.length() <= maxLongitud) {
        return titulo;
    }
    return titulo.substr(0, maxLongitud - 3) + "...";
}

// Formatear texto en múltiples líneas
inline std::vector<std::string> MostrarEspecialidadScreen::formatearTextoMultilinea(const std::string& texto, int anchoMax)
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
inline std::string MostrarEspecialidadScreen::formatearDescripcion(const std::string& texto, int anchoMax, int altoMax)
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
inline int MostrarEspecialidadScreen::encontrarPuntoCorte(const std::string& texto, int anchoMax)
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
inline std::vector<std::string> MostrarEspecialidadScreen::dividirEnLineas(const std::string& texto)
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
inline ResultadoPantalla MostrarEspecialidadScreen::_procesarSeleccion()
{
    ResultadoPantalla res;
    
    if (_esBotonInscribirse()) {
        if (!_yaInscrito) {
            // Procesar inscripción (simulado)
            _yaInscrito = true;
            
            // Actualizar el botón inmediatamente
            _renderizarBotonInscribirse(true);
            
            gotoXY(8, 28);
            setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::EXITO_COLOR);
            std::cout << "[ÉXITO]: Te has inscrito a la especialización";
            resetColor();
            _getch(); // Pausa para mostrar mensaje
            
            // Limpiar mensaje
            gotoXY(8, 28);
            std::cout << "                                                ";
        }
        // Si ya está inscrito, no hacer nada
    } else {
        // Ir al curso seleccionado
        int indiceCurso = _obtenerIndiceCursoActual();
        if (indiceCurso >= 0 && indiceCurso < _cursos.size()) {
            res.accion = AccionPantalla::IR_A_MOSTRAR_CURSO;
            res.idCursoSeleccionado = _cursos[indiceCurso].id;
        }
    }
    
    return res;
}

// Método principal de ejecución
inline ResultadoPantalla MostrarEspecialidadScreen::ejecutar()
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

#endif // COURSERACLONE_SCREENS_MOSTRARESPECIALIDADSCREEN_HPP
