// filepath: Headers/Screens/LandingPageScreen.h
// Pantalla principal del sistema - landing page con navegación por secciones

#pragma once

// Librerías estándar
#include <vector>
#include <string>
#include <sstream>
#include <conio.h>

// Librerias propias
#include "../Utils/ScreenSystem.h"
#include "../DataStructures/PriorityQueue.h"
#include "../Controllers/GestionadorCursos.h"

// forward declarations
class Controladora;
class Curso;
class Especializacion;
template<typename T> class LinkedList;

//=============================================================================
// DEFINICIÓN DE LA CLASE PRINCIPAL
//=============================================================================

/// @brief Pantalla principal del sistema con navegación por secciones
/// @details Implementa la landing page con navegación entre cabecera, especialidades y cursos
class LandingPageScreen : public PantallaBase
{
private:
    //=========================================================================
    // CONSTANTES DE CONFIGURACIÓN
    //=========================================================================
    
    /// @brief Identificadores de secciones navegables
    static const int SECCION_CABECERA = 0;
    static const int SECCION_ESPECIALIDADES = 1;
    static const int SECCION_CURSOS = 2;
    static const int TOTAL_SECCIONES = 3;

    /// @brief Límites máximos de elementos por sección
    static const int MAX_ELEMENTOS_CABECERA = 2;
    static const int MAX_ELEMENTOS_ESPECIALIDAD = 3;
    static const int MAX_ELEMENTOS_CURSO = 3;

    /// @brief Dimensiones de cuadros de contenido
    static const int MAX_ANCHO_CARACTERES_CUADRO = 30;
    static const int MAX_ALTO_CARACTERES_CUADRO = 4;

    //=========================================================================
    // DATOS ESTÁTICOS DE LA INTERFAZ
    //=========================================================================
    
    /// @brief Elementos del menú principal de la cabecera
    const vector<string> ELEMENTOS_CABECERA = {
        " Iniciar Sesion ",
        " Registrarse "
    };

    /// @brief Datos por defecto para demostración
    const vector<ElementoMenu> _especialidadesDefecto = {
        {"Desarrollo Web", "Frontend & Backend"},
        {"Ciencia de Datos", "Analisis y ML"},
        {"Marketing Digital", "SEO, SEM & Ads"}
    };

    const vector<ElementoMenu> _cursosDefecto = {
        {"Curso C++ CLI", "Interaccion consola"},
        {"Curso Python DS", "Data science intro"},
        {"Curso React JS", "Web UI development"}
    };

    //=========================================================================
    // COORDENADAS DE POSICIONAMIENTO
    //=========================================================================
    
    /// @brief Posiciones fijas para elementos de la cabecera
    const COORD _coordsElementosCabecera[MAX_ELEMENTOS_CABECERA] = { 
        {67, 3}, {84, 3} 
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

    //=========================================================================
    // ESTADO DE NAVEGACIÓN
    //=========================================================================
    
    /// @brief Estado actual de la navegación
    int _seccionActual;
    int _elementoActual;
    int _seccionAnterior;
    int _elementoAnterior;

    /// @brief Flags de control de renderizado
    bool _primeraRenderizacion;
    bool _presionEnter;

    /// @brief Datos dinámicos del menú
    vector<ElementoMenu> _especialidades;
    vector<ElementoMenu> _cursos;

    //=========================================================================
    // MÉTODOS PRIVADOS - CONFIGURACIÓN Y DATOS
    //=========================================================================

    /// @brief Carga los datos de cursos y especialidades más populares
    /// @param cursosDatos Lista de cursos disponibles
    /// @param especializacionesDatos Lista de especializaciones disponibles
    /// @param maximo Número máximo de elementos a cargar
    void cargarDatosLanding(LinkedList<Curso*>& cursosDatos, 
                           LinkedList<Especializacion*>& especializacionesDatos, 
                           int maximo)
    {
        // Comparadores para ordenar por popularidad
        auto ordenadoCursos = [](Curso* c1, Curso* c2) {
            return c1->getCantidadAlumnos() < c2->getCantidadAlumnos();
        };
        
        auto ordenadoEspecializaciones = [](Especializacion* e1, Especializacion* e2) {
            return e1->getCantidadAlumnos() < e2->getCantidadAlumnos();
        };

        // Colas de prioridad para obtener los más populares
        PriorityQueue<Curso*, decltype(ordenadoCursos)> priorityCursosLanding(maximo, ordenadoCursos);
        PriorityQueue<Especializacion*, decltype(ordenadoEspecializaciones)> priorityEspecializacionesLanding(maximo, ordenadoEspecializaciones);

        // Llenar las colas de prioridad
        priorityCursosLanding.llenarDesde(cursosDatos);
        priorityEspecializacionesLanding.llenarDesde(especializacionesDatos);

        // Extraer datos relevantes
        vector<int> idsCursos, idsEspecializaciones;
        vector<string> titulosCursos, descripcionesCursos;
        vector<string> titulosEspecializaciones, descripcionesEspecializaciones;

        // Lambdas para extracción de datos
        auto idActividad = [](Actividad* a) { return a->getId(); };
        auto tituloActividad = [](Actividad* a) { return a->getTitulo(); };
        auto descripcionActividad = [](Actividad* a) { return a->getDescripcion(); };

        // Ordenar y extraer datos
        priorityCursosLanding.ordenar();
        priorityEspecializacionesLanding.ordenar();

        idsCursos = priorityCursosLanding.extraerDato<int>(idActividad);
        idsEspecializaciones = priorityEspecializacionesLanding.extraerDato<int>(idActividad);
        titulosCursos = priorityCursosLanding.extraerDato<string>(tituloActividad);
        titulosEspecializaciones = priorityEspecializacionesLanding.extraerDato<string>(tituloActividad);
        descripcionesCursos = priorityCursosLanding.extraerDato<string>(descripcionActividad);
        descripcionesEspecializaciones = priorityEspecializacionesLanding.extraerDato<string>(descripcionActividad);

        // Crear elementos de menú para cursos
        int cantidadCursos = min(static_cast<int>(titulosCursos.size()), maximo);
        _cursos.resize(cantidadCursos);
        for (int i = 0; i < cantidadCursos; i++) {
            _cursos[i].id = idsCursos[i];
            _cursos[i].titulo = titulosCursos[i];
            _cursos[i].descripcion = descripcionesCursos[i];
        }

        // Crear elementos de menú para especialidades
        int cantidadEspecializaciones = min(static_cast<int>(titulosEspecializaciones.size()), maximo);
        _especialidades.resize(cantidadEspecializaciones);
        for (int i = 0; i < cantidadEspecializaciones; i++) {
            _especialidades[i].id = idsEspecializaciones[i];
            _especialidades[i].titulo = titulosEspecializaciones[i];
            _especialidades[i].descripcion = descripcionesEspecializaciones[i];
        }
    }

    /// @brief Carga todos los datos necesarios para la landing page
    /// @param cursosDatos Lista de cursos disponibles
    /// @param especializacionesDatos Lista de especializaciones disponibles
    /// @param maximo Número máximo de elementos por sección
    void cargarDatos(LinkedList<Curso*>& cursosDatos, 
                     LinkedList<Especializacion*>& especializacionesDatos, 
                     int maximo)
    {
        _cursos.clear();
        _especialidades.clear();
        
        // Cargar datos reales
        cargarDatosLanding(cursosDatos, especializacionesDatos, maximo);
        
        // Completar con datos por defecto si es necesario
        completarConDatosDefecto(maximo);
    }

    /// @brief Completa los datos faltantes con valores por defecto
    /// @param maximo Número máximo de elementos requeridos
    void completarConDatosDefecto(int maximo)
    {
        // Completar cursos si es necesario
        if (_cursos.size() < maximo) {
            int tamanoOriginal = _cursos.size();
            _cursos.resize(maximo);
            for (int i = tamanoOriginal; i < maximo; i++) {
                _cursos[i] = _cursosDefecto[i % _cursosDefecto.size()];
            }
        }

        // Completar especialidades si es necesario
        if (_especialidades.size() < maximo) {
            int tamanoOriginal = _especialidades.size();
            _especialidades.resize(maximo);
            for (int i = tamanoOriginal; i < maximo; i++) {
                _especialidades[i] = _especialidadesDefecto[i % _especialidadesDefecto.size()];
            }
        }
    }

    //=========================================================================
    // MÉTODOS PRIVADOS - INTERFAZ DE USUARIO
    //=========================================================================

    /// @brief Dibuja la interfaz completa de la landing page
    void dibujarInterfazCompleta()
    {
        // Dibujar fondo de la cabecera
        dibujarFondoCabecera();
        
        // Dibujar logo y elementos de navegación
        dibujarLogoYNavegacion();
        
        // Renderizar todos los elementos
        renderizarElementos();
        
        // Configurar estados iniciales
        _seccionAnterior = _seccionActual;
        _elementoAnterior = _elementoActual;
        
        // Posicionar cursor al final
        gotoXY(0, ALTO_CONSOLA - 1);
        resetColor();
    }

    /// @brief Dibuja el fondo de la sección de cabecera
    void dibujarFondoCabecera()
    {
        for (int y = 2; y < 6; y++) {            for (int x = 4; x < ANCHO_CONSOLA - 4; x++) {
                gotoXY(x, y);
                setConsoleColor(ColorIndex::TEXTO_INTENSO, ColorIndex::NAVEGACION);
                std::cout << " ";
            }
        }
    }

    /// @brief Dibuja el logo y elementos de navegación de la cabecera
    void dibujarLogoYNavegacion()
    {
        // Dibujar logo principal
        setConsoleColor(ColorIndex::ACENTO, ColorIndex::NAVEGACION, true, true);
        gotoXY(7, 3);
        std::cout << "█▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█";
        gotoXY(7, 4);
        std::cout << "█▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█";
        
        // Dibujar texto "CLONE"
        gotoXY(39, 3);
        std::cout << "│  C L O N E";
    }

    /// @brief Renderiza todos los elementos de menú
    void renderizarElementos()
    {
        // Renderizar elementos de cabecera
        for (int i = 0; i < MAX_ELEMENTOS_CABECERA; ++i) {
            actualizarElementoCabecera(i, _seccionActual == SECCION_CABECERA && _elementoActual == i);
        }

        // Renderizar especialidades
        for (size_t i = 0; i < _especialidades.size() && i < MAX_ELEMENTOS_ESPECIALIDAD; ++i) {
            actualizarElementoEspecialidad(i, _seccionActual == SECCION_ESPECIALIDADES && _elementoActual == i);
        }

        // Renderizar cursos
        for (size_t i = 0; i < _cursos.size() && i < MAX_ELEMENTOS_CURSO; ++i) {
            actualizarElementoCurso(i, _seccionActual == SECCION_CURSOS && _elementoActual == i);
        }
    }

    //=========================================================================
    // MÉTODOS PRIVADOS - ACTUALIZACIÓN DE SELECCIÓN
    //=========================================================================

    /// @brief Actualiza la selección visual de elementos en la pantalla
    void actualizarSeleccion()
    {
        // Manejo de cambio de sección
        if (_seccionAnterior == -1 || _seccionActual != _seccionAnterior) {
            actualizarCambioSeccion();
        }
        // Manejo de cambio de elemento dentro de la misma sección
        else if (_elementoActual != _elementoAnterior) {
            actualizarCambioElemento();
        }

        // Actualizar estados anteriores
        _seccionAnterior = _seccionActual;
        _elementoAnterior = _elementoActual;
    }

    /// @brief Actualiza la visualización cuando cambia de sección
    void actualizarCambioSeccion()
    {
        // Deseleccionar elemento anterior si existe
        if (_seccionAnterior != -1) {
            actualizarElementoEnSeccion(_seccionAnterior, _elementoAnterior, false);
        }

        // Seleccionar el nuevo elemento
        actualizarElementoEnSeccion(_seccionActual, _elementoActual, true);
    }

    /// @brief Actualiza la visualización cuando cambia de elemento en la misma sección
    void actualizarCambioElemento()
    {
        actualizarElementoEnSeccion(_seccionActual, _elementoAnterior, false);
        actualizarElementoEnSeccion(_seccionActual, _elementoActual, true);
    }

    /// @brief Actualiza un elemento específico en una sección dada
    /// @param seccion Sección del elemento
    /// @param elemento Índice del elemento
    /// @param seleccionado Estado de selección
    void actualizarElementoEnSeccion(int seccion, int elemento, bool seleccionado)
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

    //=========================================================================
    // MÉTODOS PRIVADOS - ACTUALIZACIÓN DE ELEMENTOS ESPECÍFICOS
    //=========================================================================

    /// @brief Actualiza la visualización de un elemento de la cabecera
    /// @param indice Índice del elemento a actualizar
    /// @param seleccionado Estado de selección del elemento
    void actualizarElementoCabecera(int indice, bool seleccionado)
    {
        if (indice < 0 || indice >= MAX_ELEMENTOS_CABECERA) return;

        gotoXY(_coordsElementosCabecera[indice].X, _coordsElementosCabecera[indice].Y);

        if (seleccionado) {
            setConsoleColor(ColorIndex::TEXTO_INTENSO, ColorIndex::BOTON_PRIMARIO, true, true);        } else {
            setConsoleColor(ColorIndex::TEXTO_INTENSO, ColorIndex::NAVEGACION, false, true);
        }

        std::cout << ELEMENTOS_CABECERA[indice];
        resetColor();
    }

    /// @brief Actualiza la visualización de un elemento de especialidad
    /// @param indice Índice del elemento a actualizar
    /// @param seleccionado Estado de selección del elemento
    void actualizarElementoEspecialidad(int indice, bool seleccionado)
    {
        if (indice < 0 || indice >= _especialidades.size()) return;

        actualizarElementoGenerico(
            _coordsTituloEspecialidad[indice],
            _coordsDescEspecialidad[indice],
            _especialidades[indice],
            seleccionado
        );
    }

    /// @brief Actualiza la visualización de un elemento de curso
    /// @param indice Índice del elemento a actualizar
    /// @param seleccionado Estado de selección del elemento
    void actualizarElementoCurso(int indice, bool seleccionado)
    {
        if (indice < 0 || indice >= _cursos.size()) return;

        actualizarElementoGenerico(
            _coordsTituloCurso[indice],
            _coordsDescCurso[indice],
            _cursos[indice],
            seleccionado
        );
    }

    /// @brief Actualiza la visualización de un elemento genérico (curso/especialidad)
    /// @param coordTitulo Coordenadas del título
    /// @param coordDesc Coordenadas de la descripción
    /// @param elemento Datos del elemento
    /// @param seleccionado Estado de selección
    void actualizarElementoGenerico(const COORD& coordTitulo, const COORD& coordDesc, 
                                   const ElementoMenu& elemento, bool seleccionado)
    {
        // Configurar colores según selección
        if (seleccionado) {
            setConsoleColor(ColorIndex::TEXTO_PRINCIPAL, ColorIndex::NAVEGACION);
        } else {
            setConsoleColor(ColorIndex::NAVEGACION, ColorIndex::FONDO_SECCION);
        }

        // Mostrar título
        mostrarTituloFormateado(coordTitulo, elemento.titulo);
        
        // Mostrar descripción
        mostrarDescripcionFormateada(coordDesc, elemento.descripcion);
        
        resetColor();
    }

    /// @brief Muestra un título formateado en las coordenadas especificadas
    /// @param coord Coordenadas donde mostrar el título
    /// @param titulo Título a mostrar
    void mostrarTituloFormateado(const COORD& coord, const string& titulo)
    {        // Limpiar área del título
        gotoXY(coord.X, coord.Y);
        std::cout << std::string(MAX_ANCHO_CARACTERES_CUADRO, ' ');
        
        // Mostrar título truncado si es necesario
        gotoXY(coord.X, coord.Y);
        std::string tituloTruncado = truncarTitulo(titulo, MAX_ANCHO_CARACTERES_CUADRO);
        std::cout << tituloTruncado;
    }

    /// @brief Muestra una descripción formateada en las coordenadas especificadas
    /// @param coord Coordenadas donde mostrar la descripción
    /// @param descripcion Descripción a mostrar
    void mostrarDescripcionFormateada(const COORD& coord, const string& descripcion)
    {
        string descFormateada = formatearDescripcion(
            descripcion, 
            MAX_ANCHO_CARACTERES_CUADRO, 
            MAX_ALTO_CARACTERES_CUADRO
        );

        // Dividir en líneas
        vector<string> lineas = dividirEnLineas(descFormateada);

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

    /// @brief Limpia las líneas sobrantes de una descripción
    /// @param coord Coordenadas base
    /// @param lineasUsadas Número de líneas ya utilizadas
    void limpiarLineasSobrantes(const COORD& coord, size_t lineasUsadas)
    {        for (size_t i = lineasUsadas; i < MAX_ALTO_CARACTERES_CUADRO; ++i) {
            gotoXY(coord.X, coord.Y + i);
            std::cout << std::string(MAX_ANCHO_CARACTERES_CUADRO, ' ');
        }
    }

    //=========================================================================
    // MÉTODOS PRIVADOS - UTILIDADES DE FORMATO
    //=========================================================================

    /// @brief Trunca títulos que excedan el máximo de caracteres
    /// @param titulo Título original
    /// @param maxLongitud Longitud máxima permitida
    /// @return Título truncado con puntos suspensivos si es necesario
    std::string truncarTitulo(const std::string& titulo, int maxLongitud)
    {
        if (titulo.length() <= maxLongitud) {
            return titulo;
        }
        return titulo.substr(0, maxLongitud - 3) + "...";
    }

    /// @brief Formatea descripciones respetando límites de ancho y alto
    /// @param texto Texto original
    /// @param anchoMax Ancho máximo por línea
    /// @param altoMax Número máximo de líneas
    /// @return Texto formateado
    string formatearDescripcion(const string& texto, int anchoMax, int altoMax)
    {
        string resultado;
        string textoRestante = texto;

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
            } else {
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

    /// @brief Encuentra el punto de corte óptimo para dividir texto
    /// @param texto Texto a dividir
    /// @param anchoMax Ancho máximo de línea
    /// @return Posición de corte óptima
    int encontrarPuntoCorte(const string& texto, int anchoMax)
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

    /// @brief Divide un texto formateado en líneas individuales
    /// @param texto Texto a dividir
    /// @return Vector de líneas
    vector<string> dividirEnLineas(const string& texto)
    {
        vector<string> lineas;
        stringstream ss(texto);
        string linea;

        while (getline(ss, linea, '\n')) {
            lineas.push_back(linea);
        }

        return lineas;
    }

    //=========================================================================
    // MÉTODOS PRIVADOS - NAVEGACIÓN Y CONTROL
    //=========================================================================

    /// @brief Obtiene el número máximo de elementos en una sección
    /// @param seccion Sección a consultar
    /// @return Número máximo de elementos
    int obtenerMaxElementosEnSeccion(int seccion)
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

    /// @brief Obtiene el ID del curso seleccionado
    /// @param indice Índice del curso
    /// @return ID del curso
    int obtenerIdCurso(int indice)
    {
        if (indice >= 0 && indice < _cursos.size()) {
            return _cursos[indice].id;
        }
        return -1;
    }

    /// @brief Determina la siguiente pantalla según la selección actual
    /// @return Pantalla a mostrar o NONE si no hay cambio
    Pantalla getSiguientePantalla()
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

    //=========================================================================
    // MÉTODOS PRIVADOS - MANEJO DE ENTRADA
    //=========================================================================

    /// @brief Maneja la navegación vertical (arriba/abajo)
    /// @param direccion Dirección del movimiento (-1 = arriba, 1 = abajo)
    void manejarNavegacionVertical(int direccion)
    {
        int nuevaSeccion = _seccionActual + direccion;
        
        // Validar límites
        if (nuevaSeccion < 0) {
            nuevaSeccion = 0;
        } else if (nuevaSeccion >= TOTAL_SECCIONES) {
            nuevaSeccion = TOTAL_SECCIONES - 1;
        }

        // Actualizar solo si hay cambio
        if (nuevaSeccion != _seccionActual) {
            _seccionActual = nuevaSeccion;
            _elementoActual = 0;  // Resetear elemento al cambiar de sección
            actualizarSeleccion();
        }
    }

    /// @brief Maneja la navegación horizontal (izquierda/derecha)
    /// @param direccion Dirección del movimiento (-1 = izquierda, 1 = derecha)
    void manejarNavegacionHorizontal(int direccion)
    {
        int nuevoElemento = _elementoActual + direccion;
        int maxElementos = obtenerMaxElementosEnSeccion(_seccionActual);

        // Validar límites
        if (nuevoElemento < 0) {
            nuevoElemento = 0;
        } else if (nuevoElemento >= maxElementos) {
            nuevoElemento = maxElementos > 0 ? maxElementos - 1 : 0;
        }

        // Actualizar solo si hay cambio
        if (nuevoElemento != _elementoActual) {
            _elementoActual = nuevoElemento;
            actualizarSeleccion();
        }
    }

    /// @brief Procesa la acción de selección (Enter)
    /// @param resultado Resultado de pantalla a modificar
    void procesarSeleccion(ResultadoPantalla& resultado)
    {
        if (_seccionActual == SECCION_CURSOS) {
            procesarSeleccionCurso(resultado);
        } else if (_seccionActual == SECCION_ESPECIALIDADES) {
            procesarSeleccionEspecialidad(resultado);
        } else if (_seccionActual == SECCION_CABECERA) {
            procesarSeleccionCabecera(resultado);
        }
    }

    /// @brief Procesa la selección de un curso
    /// @param resultado Resultado de pantalla a modificar
    void procesarSeleccionCurso(ResultadoPantalla& resultado)
    {
        if (_elementoActual < _cursos.size()) {
            int idCursoSeleccionado = obtenerIdCurso(_elementoActual);
            resultado.idCursoSeleccionado = idCursoSeleccionado;
            resultado.accion = AccionPantalla::IR_A_MOSTRAR_CURSO;
            resultado.accionAnterior = AccionPantalla::IR_A_LANDING_PAGE;
        }
    }

    /// @brief Procesa la selección de una especialidad
    /// @param resultado Resultado de pantalla a modificar
    void procesarSeleccionEspecialidad(ResultadoPantalla& resultado)
    {
        if (_elementoActual < _especialidades.size()) {
            int idEspecializacionSeleccionada = _especialidades[_elementoActual].id;
            resultado.idCursoSeleccionado = idEspecializacionSeleccionada;
            resultado.accion = AccionPantalla::IR_A_MOSTRAR_ESPECIALIZACION;
            resultado.accionAnterior = AccionPantalla::IR_A_LANDING_PAGE;
        }
    }

    /// @brief Procesa la selección de un elemento de la cabecera
    /// @param resultado Resultado de pantalla a modificar
    void procesarSeleccionCabecera(ResultadoPantalla& resultado)
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

public:
    //=========================================================================
    // CONSTRUCTORES
    //=========================================================================

    /// @brief Constructor por defecto
    LandingPageScreen() : PantallaBase(),
        _seccionActual(0), _elementoActual(0),
        _seccionAnterior(-1), _elementoAnterior(-1),
        _primeraRenderizacion(true), _presionEnter(false)
    {
        // Inicializar con datos por defecto
        _especialidades = _especialidadesDefecto;
        _cursos = _cursosDefecto;
    }

    /// @brief Constructor con datos dinámicos
    /// @param cursosDatos Lista de cursos disponibles
    /// @param especializacionesDatos Lista de especializaciones disponibles
    LandingPageScreen(LinkedList<Curso*>& cursosDatos, 
                     LinkedList<Especializacion*>& especializacionesDatos)
        : PantallaBase(),
        _seccionActual(0), _elementoActual(0),
        _seccionAnterior(-1), _elementoAnterior(-1),
        _primeraRenderizacion(true), _presionEnter(false)
    {
        cargarDatos(cursosDatos, especializacionesDatos, 3);
    }

    //=========================================================================
    // MÉTODOS PÚBLICOS - INTERFAZ PRINCIPAL
    //=========================================================================

    /// @brief Renderiza la pantalla
    void renderizar()
    {
        if (_primeraRenderizacion) {
            system("cls");
            UI_LandingPage();
            dibujarInterfazCompleta();
            _primeraRenderizacion = false;
        } else {
            actualizarSeleccion();
        }
    }

    /// @brief Maneja la entrada del usuario
    /// @param tecla Código de la tecla presionada
    void manejarInput(int tecla)
    {
        _presionEnter = false;

        if (tecla == 224) {  // Tecla extendida
            tecla = _getch();
            switch (tecla) {
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
        } else if (tecla == 13) {  // Enter
            _presionEnter = true;
        }
    }

    /// @brief Ejecuta el bucle principal de la pantalla
    /// @return Resultado de la ejecución
    ResultadoPantalla ejecutar() override
    {
        ResultadoPantalla resultado;
        renderizar();

        int tecla;
        while (resultado.accion == AccionPantalla::NINGUNA) {
            tecla = _getch();
            manejarInput(tecla);
            renderizar();

            // Procesar acciones
            if (_presionEnter) {
                procesarSeleccion(resultado);
            }

            if (tecla == 27) {  // ESC
                resultado.accion = AccionPantalla::SALIR;
            }
        }

        return resultado;
    }
};

//=============================================================================
// ALIAS DE COMPATIBILIDAD
//=============================================================================

/// @brief Alias para mantener compatibilidad con código existente
using LandingPage = LandingPageScreen;
