// filepath: Headers/Screens/LandingPageScreen.hpp
// Pantalla principal del sistema - landing page con navegación por secciones

#ifndef COURSERACLONE_SCREENS_LANDINGPAGESCREEN_HPP
#define COURSERACLONE_SCREENS_LANDINGPAGESCREEN_HPP

// Librerías estándar
#include <vector>  // std::vector
#include <string>  // std::string
#include <sstream> // std::stringstream
#include <conio.h> // _getch()

// Librerias propias
#include "../Utils/UI_Ascii.hpp"
#include "../Utils/SystemUtils.hpp"
#include "../Utils/ScreenSystem.hpp"

/// @brief Pantalla principal del sistema con navegación por secciones
/// @details Implementa la landing page con navegación entre cabecera, especialidades y cursos
class LandingPageScreen : public PantallaBase
{
private:
    // CONSTANTES DE CONFIGURACIÓN
    /// @brief Identificadores de secciones navegables
    static const int SECCION_CABECERA = 0;
	static const int SECCION_SUBMENU = 1;
    static const int SECCION_ESPECIALIDADES = 2;
    static const int SECCION_CURSOS = 3;
    static const int TOTAL_SECCIONES = 4;

    /// @brief Límites máximos de elementos por sección
    static const int MAX_ELEMENTOS_CABECERA = 3;
	static const int MAX_ELEMENTOS_SUBMENU = 2;
    static const int MAX_ELEMENTOS_ESPECIALIDAD = 3;
    static const int MAX_ELEMENTOS_CURSO = 3;

    /// @brief Dimensiones de cuadros de contenido
    static const int MAX_ANCHO_CARACTERES_CUADRO = 32;
    static const int MAX_ALTO_CARACTERES_CUADRO = 4;

    // DATOS ESTÁTICOS DE LA INTERFAZ
    /// @brief Elementos del menú principal de la cabecera
    const std::vector<std::string> ELEMENTOS_CABECERA = {
        " INICIAR SESION ",
        " REGISTRARSE ",
        " SOBRE NOSOTROS "
    };

    // COORDENADAS DE POSICIONAMIENTO
    /// @brief Posiciones fijas para elementos de la cabecera
    const COORD _coordsElementosCabecera[MAX_ELEMENTOS_CABECERA] = { 
        {71, 1}, {88, 1}, {102, 1}
    };

    /// @brief Posiciones para títulos de especialidades
    const COORD _coordsTituloEspecialidad[MAX_ELEMENTOS_ESPECIALIDAD] = { 
        {11, 15}, {45, 15}, {79, 15} 
    };

    /// @brief Posiciones para descripciones de especialidades
    const COORD _coordsDescEspecialidad[MAX_ELEMENTOS_ESPECIALIDAD] = { 
        {11, 17}, {45, 17}, {79, 17} 
    };

    /// @brief Posiciones para títulos de cursos
    const COORD _coordsTituloCurso[MAX_ELEMENTOS_CURSO] = { 
        {11, 25}, {45, 25}, {79, 25} 
    };

    /// @brief Posiciones para descripciones de cursos
    const COORD _coordsDescCurso[MAX_ELEMENTOS_CURSO] = { 
        {11, 27}, {45, 27}, {79, 27} 
    };

    // ESTADO DE NAVEGACIÓN
    /// @brief Estado actual de la navegación
    int _seccionActual;
    int _elementoActual;
    int _seccionAnterior;
    int _elementoAnterior;

    /// @brief Flags de control de renderizado
    bool _primeraRenderizacion;
    bool _presionEnter;    

    /// @brief Datos dinámicos del menú
    std::vector<ElementoMenu> _especialidades;
    std::vector<ElementoMenu> _cursos;

    // MÉTODOS PRIVADOS - CONFIGURACIÓN Y DATOS
    /// @brief Carga todos los datos necesarios para la landing page
    /// @param cursosDatos Lista de cursos disponibles
    /// @param especializacionesDatos Lista de especializaciones disponibles
    /// @param maximo Número máximo de elementos por sección
    inline void cargarDatos(int maxEspecialidad, int maxCursos);

    // MÉTODOS PRIVADOS - INTERFAZ DE USUARIO

    /// @brief Dibuja la interfaz completa de la landing page
    inline void dibujarInterfazCompleta();

    /// @brief Dibuja el fondo de la sección de cabecera
    inline void dibujarFondoCabecera();

    /// @brief Dibuja el logo y elementos de navegación de la cabecera
    inline void dibujarLogoYNavegacion();

    /// @brief Renderiza todos los elementos de menú
    inline void renderizarElementos();

    // MÉTODOS PRIVADOS - ACTUALIZACIÓN DE SELECCIÓN
    /// @brief Actualiza la selección visual de elementos en la pantalla
    inline void actualizarSeleccion();

    /// @brief Actualiza la visualización cuando cambia de sección
    inline void actualizarCambioSeccion();

    /// @brief Actualiza la visualización cuando cambia de elemento en la misma sección
    inline void actualizarCambioElemento();

    /// @brief Actualiza un elemento específico en una sección dada
    /// @param seccion Sección del elemento
    /// @param elemento Índice del elemento
    /// @param seleccionado Estado de selección
    inline void actualizarElementoEnSeccion(int seccion, int elemento, bool seleccionado);

    // MÉTODOS PRIVADOS - ACTUALIZACIÓN DE ELEMENTOS ESPECÍFICOS

    /// @brief Actualiza la visualización de un elemento de la cabecera
    /// @param indice Índice del elemento a actualizar
    /// @param seleccionado Estado de selección del elemento
    inline void actualizarElementoCabecera(int indice, bool seleccionado);

    /// @brief Actualiza la visualización de un elemento de especialidad
    /// @param indice Índice del elemento a actualizar
    /// @param seleccionado Estado de selección del elemento
    inline void actualizarElementoEspecialidad(int indice, bool seleccionado);

    /// @brief Actualiza la visualización de un elemento de curso
    /// @param indice Índice del elemento a actualizar
    /// @param seleccionado Estado de selección del elemento
    inline void actualizarElementoCurso(int indice, bool seleccionado);

    /// @brief Actualiza la visualización de un elemento genérico (curso/especialidad)
    /// @param coordTitulo Coordenadas del título
    /// @param coordDesc Coordenadas de la descripción
    /// @param elemento Datos del elemento
    /// @param seleccionado Estado de selección
    inline void actualizarElementoGenerico(const COORD& coordTitulo, const COORD& coordDesc, const ElementoMenu& elemento, bool seleccionado);

    /// @brief Muestra un título formateado en las coordenadas especificadas
    /// @param coord Coordenadas donde mostrar el título
    /// @param titulo Título a mostrar
    inline void mostrarTituloFormateado(const COORD& coord, const std::string& titulo);

    /// @brief Muestra una descripción formateada en las coordenadas especificadas
    /// @param coord Coordenadas donde mostrar la descripción
    /// @param descripcion Descripción a mostrar
    inline void mostrarDescripcionFormateada(const COORD& coord, const std::string& descripcion);

    /// @brief Limpia las líneas sobrantes de una descripción
    /// @param coord Coordenadas base
    /// @param lineasUsadas Número de líneas ya utilizadas
    inline void limpiarLineasSobrantes(const COORD& coord, size_t lineasUsadas);

    // MÉTODOS PRIVADOS - UTILIDADES DE FORMATO

    /// @brief Trunca títulos que excedan el máximo de caracteres
    /// @param titulo Título original
    /// @param maxLongitud Longitud máxima permitida
    /// @return Título truncado con puntos suspensivos si es necesario
    inline std::string truncarTitulo(const std::string& titulo, int maxLongitud);

    /// @brief Formatea descripciones respetando límites de ancho y alto
    /// @param texto Texto original
    /// @param anchoMax Ancho máximo por línea
    /// @param altoMax Número máximo de líneas
    /// @return Texto formateado
    inline std::string formatearDescripcion(const std::string& texto, int anchoMax, int altoMax);

    /// @brief Encuentra el punto de corte óptimo para dividir texto
    /// @param texto Texto a dividir
    /// @param anchoMax Ancho máximo de línea
    /// @return Posición de corte óptima
    inline int encontrarPuntoCorte(const std::string& texto, int anchoMax);

    /// @brief Divide un texto formateado en líneas individuales
    /// @param texto Texto a dividir
    /// @return Vector de líneas
    inline std::vector<std::string> dividirEnLineas(const std::string& texto);

    // MÉTODOS PRIVADOS - NAVEGACIÓN Y CONTROL
    /// @brief Obtiene el número máximo de elementos en una sección
    /// @param seccion Sección a consultar
    /// @return Número máximo de elementos
    inline int obtenerMaxElementosEnSeccion(int seccion);

    /// @brief Obtiene el ID del curso seleccionado
    /// @param indice Índice del curso
    /// @return ID del curso
    inline int obtenerIdCurso(int indice);

    /// @brief Determina la siguiente pantalla según la selección actual
    /// @return Pantalla a mostrar o NONE si no hay cambio
    inline Pantalla getSiguientePantalla();

    // MÉTODOS PRIVADOS - MANEJO DE ENTRADA
    /// @brief Maneja la navegación vertical (arriba/abajo)
    /// @param direccion Dirección del movimiento (-1 = arriba, 1 = abajo)
    inline void manejarNavegacionVertical(int direccion);

    /// @brief Maneja la navegación horizontal (izquierda/derecha)
    /// @param direccion Dirección del movimiento (-1 = izquierda, 1 = derecha)
    inline void manejarNavegacionHorizontal(int direccion);

    /// @brief Procesa la acción de selección (Enter)
    /// @param resultado Resultado de pantalla a modificar
    inline void procesarSeleccion(ResultadoPantalla& resultado);

    /// @brief Procesa la selección de un curso
    /// @param resultado Resultado de pantalla a modificar
    inline void procesarSeleccionCurso(ResultadoPantalla& resultado);

    /// @brief Procesa la selección de una especialidad
    /// @param resultado Resultado de pantalla a modificar
    inline void procesarSeleccionEspecialidad(ResultadoPantalla& resultado);

    /// @brief Procesa la selección de un elemento de la cabecera
    /// @param resultado Resultado de pantalla a modificar
    inline void procesarSeleccionCabecera(ResultadoPantalla& resultado);

public:
    /// @brief Constructor por defecto
    inline LandingPageScreen();

    // MÉTODOS PÚBLICOS - INTERFAZ PRINCIPAL

    /// @brief Renderiza la pantalla
    inline void renderizar();

    /// @brief Maneja la entrada del usuario
    /// @param tecla Código de la tecla presionada
    inline void manejarInput(int tecla);

    /// @brief Ejecuta el bucle principal de la pantalla
    /// @return Resultado de la ejecución
    inline ResultadoPantalla ejecutar() override;
};

// ---- CONSTRUCTOR ----

inline LandingPageScreen::LandingPageScreen() : PantallaBase(),
    _seccionActual(0), _elementoActual(0),
    _seccionAnterior(-1), _elementoAnterior(-1),
    _primeraRenderizacion(true), _presionEnter(false)
{
    cargarDatos(MAX_ELEMENTOS_ESPECIALIDAD, MAX_ELEMENTOS_CURSO);
}

// ---- MÉTODOS PRIVADOS ----

inline void LandingPageScreen::cargarDatos(int maxEspecialidad, int maxCursos)
{
	/// @todo: Implementar lógica para cargar datos dinámicos
	/// @note Debemos utilizar el ContentManager y el FilesManager para cargar los datos de cursos y especializaciones
    
}

inline void LandingPageScreen::dibujarInterfazCompleta()
{
    /// @brief Dibujar fondo de la cabecera
    dibujarFondoCabecera();

    /// @brief Dibujar logo y elementos de navegación
    dibujarLogoYNavegacion();

    /// @brief Renderizar todos los elementos
    renderizarElementos();

    /// @brief Posicionar cursor al final
    gotoXY(0, ALTO_CONSOLA - 1);
    resetColor();
}

inline void LandingPageScreen::dibujarFondoCabecera()
{
	/// @brief Dibujar fondo de la cabecera
    for (int y = 0; y < 4; y++) 
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++) 
        {
            gotoXY(x, y);
            setConsoleColor(ColorIndex::TEXTO_INTENSO, ColorIndex::NAVEGACION);
            std::cout << " ";
        }
    }
	/// @brief Dibujar linea inferior de los botones
    gotoXY(_coordsElementosCabecera[0].X + 1, _coordsElementosCabecera[0].Y + 1);
    std::cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯   ¯¯¯¯¯¯¯¯¯¯¯   ¯¯¯¯¯¯¯¯¯¯¯¯¯¯";
}

inline void LandingPageScreen::dibujarLogoYNavegacion()
{
    // Dibujar logo principal
    setConsoleColor(ColorIndex::ACENTO, ColorIndex::NAVEGACION, true, true);
    gotoXY(3, 1); std::cout << "█▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█";
    gotoXY(3, 2); std::cout << "█▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█";

    // Dibujar texto "CLONE"
    gotoXY(35, 1);
    std::cout << "│  C L O N E";
}

inline void LandingPageScreen::renderizarElementos()
{
    /// @brief Renderizar elementos de cabecera
    for (int i = 0; i < MAX_ELEMENTOS_CABECERA; ++i) 
    {
        actualizarElementoCabecera(i, _seccionActual == SECCION_CABECERA && _elementoActual == i);
    }

    /// @brief Renderizar especialidades
    for (size_t i = 0; i < _especialidades.size() && i < MAX_ELEMENTOS_ESPECIALIDAD; ++i) 
    {
        actualizarElementoEspecialidad(i, _seccionActual == SECCION_ESPECIALIDADES && _elementoActual == i);
    }

    /// @brief Renderizar cursos
    for (size_t i = 0; i < _cursos.size() && i < MAX_ELEMENTOS_CURSO; ++i) 
    {
        actualizarElementoCurso(i, _seccionActual == SECCION_CURSOS && _elementoActual == i);
    }
}

// MÉTODOS PRIVADOS - ACTUALIZACIÓN DE SELECCIÓN

inline void LandingPageScreen::actualizarSeleccion()
{
    /// @brief Manejo de cambio de sección
    if (_seccionAnterior == -1 || _seccionActual != _seccionAnterior) 
    {
        actualizarCambioSeccion();
    }
    /// @brief Manejo de cambio de elemento dentro de la misma sección
    else if (_elementoActual != _elementoAnterior) 
    {
        actualizarCambioElemento();
    }

    /// @brief Actualizar estados anteriores
    _seccionAnterior = _seccionActual;
    _elementoAnterior = _elementoActual;
}

inline void LandingPageScreen::actualizarCambioSeccion()
{
    // Deseleccionar elemento anterior si existe
    if (_seccionAnterior != -1) 
    {
        actualizarElementoEnSeccion(_seccionAnterior, _elementoAnterior, false);
    }

    // Seleccionar el nuevo elemento
    actualizarElementoEnSeccion(_seccionActual, _elementoActual, true);
}

inline void LandingPageScreen::actualizarCambioElemento()
{
    actualizarElementoEnSeccion(_seccionActual, _elementoAnterior, false);
    actualizarElementoEnSeccion(_seccionActual, _elementoActual, true);
}

inline void LandingPageScreen::actualizarElementoEnSeccion(int seccion, int elemento, bool seleccionado)
{
    switch (seccion) {
    case SECCION_CABECERA:
        actualizarElementoCabecera(elemento, seleccionado);
        break;
    case SECCION_ESPECIALIDADES:
        actualizarElementoEspecialidad(elemento, seleccionado);
        break;
    case SECCION_CURSOS:
        actualizarElementoCurso(elemento, seleccionado);
        break;
    }
}

// MÉTODOS PRIVADOS - ACTUALIZACIÓN DE ELEMENTOS ESPECÍFICOS

inline void LandingPageScreen::actualizarElementoCabecera(int indice, bool seleccionado)
{
    if (indice < 0 || indice >= MAX_ELEMENTOS_CABECERA) return;

    gotoXY(_coordsElementosCabecera[indice].X, _coordsElementosCabecera[indice].Y);

    if (seleccionado) {
        setConsoleColor(ColorIndex::TEXTO_INTENSO, ColorIndex::BOTON_PRIMARIO, true, true);
    }
    else {
        setConsoleColor(ColorIndex::TEXTO_INTENSO, ColorIndex::NAVEGACION, false, true);
    }

    std::cout << ELEMENTOS_CABECERA[indice];
    resetColor();
}

inline void LandingPageScreen::actualizarElementoEspecialidad(int indice, bool seleccionado)
{
    if (indice < 0 || indice >= _especialidades.size()) return;

    actualizarElementoGenerico(
        _coordsTituloEspecialidad[indice],
        _coordsDescEspecialidad[indice],
        _especialidades[indice],
        seleccionado
    );
}

inline void LandingPageScreen::actualizarElementoCurso(int indice, bool seleccionado)
{
    if (indice < 0 || indice >= _cursos.size()) return;

    actualizarElementoGenerico(
        _coordsTituloCurso[indice],
        _coordsDescCurso[indice],
        _cursos[indice],
        seleccionado
    );
}

inline void LandingPageScreen::actualizarElementoGenerico(const COORD& coordTitulo, const COORD& coordDesc,
    const ElementoMenu& elemento, bool seleccionado)
{
    // Configurar colores según selección
    if (seleccionado) {
        setConsoleColor(ColorIndex::TEXTO_PRINCIPAL, ColorIndex::NAVEGACION);
    }
    else {
        setConsoleColor(ColorIndex::NAVEGACION, ColorIndex::FONDO_SECCION);
    }

    // Mostrar título
    mostrarTituloFormateado(coordTitulo, elemento.titulo);

    // Mostrar descripción
    mostrarDescripcionFormateada(coordDesc, elemento.descripcion);

    resetColor();
}    

inline void LandingPageScreen::mostrarTituloFormateado(const COORD& coord, const std::string& titulo)
{        // Limpiar área del título
    gotoXY(coord.X, coord.Y);
    std::cout << std::string(MAX_ANCHO_CARACTERES_CUADRO, ' ');

    // Mostrar título truncado si es necesario
    gotoXY(coord.X, coord.Y);
    std::string tituloTruncado = truncarTitulo(titulo, MAX_ANCHO_CARACTERES_CUADRO);
    std::cout << tituloTruncado;
}   

inline void LandingPageScreen::mostrarDescripcionFormateada(const COORD& coord, const std::string& descripcion)
{
    std::string descFormateada = formatearDescripcion(
        descripcion,
        MAX_ANCHO_CARACTERES_CUADRO,
        MAX_ALTO_CARACTERES_CUADRO
    );

    // Dividir en líneas
    std::vector<std::string> lineas = dividirEnLineas(descFormateada);

    // Mostrar cada línea        
    for (size_t i = 0; i < lineas.size(); ++i) {
        gotoXY(coord.X, coord.Y + i);
        std::cout << std::string(MAX_ANCHO_CARACTERES_CUADRO, ' ');  // Limpiar línea
        gotoXY(coord.X, coord.Y + i);
        std::cout << lineas[i];
    }

    // Limpiar líneas sobrantes
    limpiarLineasSobrantes(coord, lineas.size());
}

inline void LandingPageScreen::limpiarLineasSobrantes(const COORD& coord, size_t lineasUsadas)
{
    for (size_t i = lineasUsadas; i < MAX_ALTO_CARACTERES_CUADRO; ++i) {
        gotoXY(coord.X, coord.Y + i);
        std::cout << std::string(MAX_ANCHO_CARACTERES_CUADRO, ' ');
    }
}

inline std::string LandingPageScreen::truncarTitulo(const std::string& titulo, int maxLongitud)
{
    if (titulo.length() <= maxLongitud) {
        return titulo;
    }
    return titulo.substr(0, maxLongitud - 3) + "...";
}   

inline std::string LandingPageScreen::formatearDescripcion(const std::string& texto, int anchoMax, int altoMax) {
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

inline int LandingPageScreen::encontrarPuntoCorte(const std::string& texto, int anchoMax)
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

inline std::vector<std::string> LandingPageScreen::dividirEnLineas(const std::string& texto)
{
    std::vector<std::string> lineas;
    std::stringstream ss(texto);
    std::string linea;

    while (std::getline(ss, linea, '\n')) {
        lineas.push_back(linea);
    }

    return lineas;
}

// MÉTODOS PRIVADOS - NAVEGACIÓN Y CONTROL

inline int LandingPageScreen::obtenerMaxElementosEnSeccion(int seccion)
{
    switch (seccion) {
    case SECCION_CABECERA:
        return MAX_ELEMENTOS_CABECERA;
    case SECCION_ESPECIALIDADES:
        return static_cast<int>(_especialidades.size());
    case SECCION_CURSOS:
        return static_cast<int>(_cursos.size());
    default:
        return 0;
    }
}

inline int LandingPageScreen::obtenerIdCurso(int indice)
{
    if (indice >= 0 && indice < _cursos.size()) {
        return _cursos[indice].id;
    }
    return -1;
}

inline Pantalla LandingPageScreen::getSiguientePantalla()
{
    if (_seccionActual == SECCION_CABECERA) {
        switch (_elementoActual) {
        case 0: return Pantalla::LOGIN;
        case 1: return Pantalla::REGISTRO;
        default: return Pantalla::NONE;
        }
    }
    return Pantalla::NONE;
}

inline void LandingPageScreen::manejarNavegacionVertical(int direccion)
{
    int nuevaSeccion = _seccionActual + direccion;

    // Validar límites
    if (nuevaSeccion < 0) {
        nuevaSeccion = 0;
    }
    else if (nuevaSeccion >= TOTAL_SECCIONES) {
        nuevaSeccion = TOTAL_SECCIONES - 1;
    }

    // Actualizar solo si hay cambio
    if (nuevaSeccion != _seccionActual) {
        _seccionActual = nuevaSeccion;
        _elementoActual = 0;  // Resetear elemento al cambiar de sección
        actualizarSeleccion();
    }
}

inline void LandingPageScreen::manejarNavegacionHorizontal(int direccion)
{
    int nuevoElemento = _elementoActual + direccion;
    int maxElementos = obtenerMaxElementosEnSeccion(_seccionActual);

    // Validar límites
    if (nuevoElemento < 0) {
        nuevoElemento = 0;
    }
    else if (nuevoElemento >= maxElementos) {
        nuevoElemento = maxElementos > 0 ? maxElementos - 1 : 0;
    }

    // Actualizar solo si hay cambio
    if (nuevoElemento != _elementoActual) {
        _elementoActual = nuevoElemento;
        actualizarSeleccion();
    }
}

inline void LandingPageScreen::procesarSeleccion(ResultadoPantalla& resultado)
{
    if (_seccionActual == SECCION_CURSOS) {
        procesarSeleccionCurso(resultado);
    }
    else if (_seccionActual == SECCION_ESPECIALIDADES) {
        procesarSeleccionEspecialidad(resultado);
    }
    else if (_seccionActual == SECCION_CABECERA) {
        procesarSeleccionCabecera(resultado);
    }
}

inline void LandingPageScreen::procesarSeleccionCurso(ResultadoPantalla& resultado)
{
    if (_elementoActual < _cursos.size()) {
        int idCursoSeleccionado = obtenerIdCurso(_elementoActual);
        resultado.idCursoSeleccionado = idCursoSeleccionado;
        resultado.accion = AccionPantalla::IR_A_MOSTRAR_CURSO;
        resultado.accionAnterior = AccionPantalla::IR_A_LANDING_PAGE;
    }
}

inline void LandingPageScreen::procesarSeleccionEspecialidad(ResultadoPantalla& resultado)
{
    if (_elementoActual < _especialidades.size()) {
        int idEspecializacionSeleccionada = _especialidades[_elementoActual].id;
        resultado.idCursoSeleccionado = idEspecializacionSeleccionada;
        resultado.accion = AccionPantalla::IR_A_MOSTRAR_ESPECIALIZACION;
        resultado.accionAnterior = AccionPantalla::IR_A_LANDING_PAGE;
    }
}

inline void LandingPageScreen::procesarSeleccionCabecera(ResultadoPantalla& resultado)
{
    Pantalla siguiente = getSiguientePantalla();

    switch (siguiente) {
    case Pantalla::LOGIN:
        resultado.accion = AccionPantalla::IR_A_LOGIN;
        break;
    case Pantalla::REGISTRO:
        resultado.accion = AccionPantalla::IR_A_REGISTRO;
        break;
    default:
        // No hay acción definida
        break;
    }
}

// MÉTODOS PÚBLICOS - INTERFAZ PRINCIPAL

inline void LandingPageScreen::renderizar()
{
    if (_primeraRenderizacion)
    {
        system("cls");
        UI_LandingPage();
        dibujarInterfazCompleta();
        _primeraRenderizacion = false;
    } else {
        actualizarSeleccion();
    }
}

inline void LandingPageScreen::manejarInput(int tecla)
{
    _presionEnter = false;

    if (tecla == 224) // Tecla extendida
    {
        tecla = _getch();
        switch (tecla)
        {
        case 72:  // Flecha arriba
            manejarNavegacionVertical(-1);
            break;
        case 80:  // Flecha abajo
            manejarNavegacionVertical(1);
            break;
        case 75:  // Flecha izquierda
            manejarNavegacionHorizontal(-1);
            break;
        case 77:  // Flecha derecha
            manejarNavegacionHorizontal(1);
            break;
        }
    }
    else if (tecla == 13) // Enter
    {
        _presionEnter = true;
    }
}

inline ResultadoPantalla LandingPageScreen::ejecutar()
{
    ResultadoPantalla resultado;
    renderizar();

    int tecla;
    while (resultado.accion == AccionPantalla::NINGUNA)
    {
        tecla = _getch();
        manejarInput(tecla);
        renderizar();

        if (_presionEnter) // Procesar acciones
        {
            procesarSeleccion(resultado);
        }

        if (tecla == 27) {  // ESC
            resultado.accion = AccionPantalla::SALIR;
        }
    }

    return resultado;
}

#endif // COURSERACLONE_SCREENS_LANDINGPAGESCREEN_HPP
