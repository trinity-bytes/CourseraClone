#ifndef COURSERACLONE_SCREENS_ESTADISTICASEMPRESASCREEN_HPP
#define COURSERACLONE_SCREENS_ESTADISTICASEMPRESASCREEN_HPP

// Headers estándar
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <conio.h>

// Headers propios
#include "../Utils/SystemUtils.hpp"
#include "../Utils/ScreenSystem.hpp"
#include "../Utils/UI_Ascii.hpp"
#include "../Types/UsuarioTypes.hpp"

/// Pantalla para mostrar estadísticas de empresa/organización
class EstadisticasEmpresaScreen : public PantallaBase
{
private:
    // Datos de la empresa
    std::string _nombreEmpresa;
    
    // Estado de navegación
    AccionPantalla _pantallaAnterior;
    bool _primeraRenderizacion;
    
    // Navegación entre secciones de estadísticas
    int _seccionActual; // 0: Cursos, 1: Estudiantes, 2: Ingresos
    int _totalSecciones;
    
    // Variables para recordar lo que se escribió antes ("limpiar solo lo que ensucias")
    std::string _tituloAnterior;
    std::vector<std::string> _nombresAnteriores;
    std::vector<std::string> _numerosAnteriores;
    
    // Estadísticas generales
    struct EstadisticasGenerales {
        int totalCursos;
        int totalEspecializaciones;
        int totalInscripciones;
        double ingresosTotal;
        double ingresosMes;
        int cursosPopulares;
        int nuevosEstudiantes;
    } _stats;
    
    // Datos para gráficos (simulados)
    std::vector<std::pair<std::string, int>> _datosCursos;
    std::vector<std::pair<std::string, int>> _datosEstudiantes;
    std::vector<std::pair<std::string, double>> _datosIngresos;
    
    static const int MAX_ELEMENTOS_GRAFICO = 5;
    static const int LONGITUD_NOMBRE_ITEM = 20;
    static const int LONGITUD_EMPRESA = 30;
    
    /// @brief Coordenadas para información de la empresa
    COORD _coordNombreEmpresa = {8, 5};
    
    /// @brief Coordenadas para estadísticas generales
    COORD _coordStatsGenerales = {19, 13};
    
    /// @brief Coordenadas para secciones de estadísticas
    COORD _coordSeccionCursos = {47, 18};
    COORD _coordSeccionEstudiantes = {47, 18};
    COORD _coordSeccionIngresos = {47, 18};
    
    /// @brief Coordenadas para navegación de secciones
    COORD _coordNavegacion = {60, 28};

    // ---- MÉTODOS PRIVADOS ----
    
    /// @brief Métodos de inicialización
    inline void _limpiarEstado();
    inline void _cargarDatosDummy();
    inline void _cargarDatos();

    /// @brief Métodos de renderizado
    inline void dibujarInterfazCompleta();
    inline void _renderizarInformacionEmpresa();
    inline void _renderizarEstadisticasGenerales();
    inline void _renderizarSeccionActual();
    inline void _renderizarSeccionCursos();
    inline void _renderizarSeccionEstudiantes();
    inline void _renderizarSeccionIngresos();
    inline void _renderizarNavegacion();
    inline void _limpiarAreaEstadisticas();
    inline void _actualizarSeleccion();

    /// @brief Métodos de navegación
    inline void _manejarNavegacion(int tecla);
    inline void _cambiarSeccion(int nuevaSeccion);

    /// @brief Métodos de formateo
    inline std::string formatearNumero(int numero);
    inline std::string formatearDinero(double cantidad);
    inline std::string truncarTexto(const std::string& texto, int maxLongitud);
    inline std::string crearBarraProgreso(int valor, int maximo, int longitud = 20);

    /// @brief Métodos de procesamiento
    inline ResultadoPantalla _procesarSeleccion();

public:
    inline EstadisticasEmpresaScreen(AccionPantalla pantallaAnterior = AccionPantalla::IR_A_DASHBOARD_ORGANIZACION);
    
    inline ~EstadisticasEmpresaScreen() = default;

    inline ResultadoPantalla ejecutar() override;
};

// --- IMPLEMENTACIONES INLINE ---

// Constructor
inline EstadisticasEmpresaScreen::EstadisticasEmpresaScreen(AccionPantalla pantallaAnterior) : PantallaBase(),
    _pantallaAnterior(pantallaAnterior), _primeraRenderizacion(true), _seccionActual(0), _totalSecciones(3)
{
    _cargarDatosDummy();
    _cargarDatos();
    
    // Inicializar vectores para recordar lo escrito anteriormente
    _nombresAnteriores.resize(MAX_ELEMENTOS_GRAFICO);
    _numerosAnteriores.resize(MAX_ELEMENTOS_GRAFICO);
}

// Limpiar estado
inline void EstadisticasEmpresaScreen::_limpiarEstado()
{
    _seccionActual = 0;
    _primeraRenderizacion = true;
    
    // Limpiar memoria de lo escrito anteriormente
    _tituloAnterior.clear();
    for (auto& nombre : _nombresAnteriores) {
        nombre.clear();
    }
    for (auto& numero : _numerosAnteriores) {
        numero.clear();
    }
}

// Cargar datos de ejemplo
inline void EstadisticasEmpresaScreen::_cargarDatosDummy()
{
    // Información de la empresa
    _nombreEmpresa = "Universidad Peruana de Ciencias Aplicadas";
    
    // Estadísticas generales (simuladas)
    _stats.totalCursos = 45;
    _stats.totalEspecializaciones = 12;
    _stats.totalInscripciones = 5692;
    _stats.ingresosTotal = 125640.50;
    _stats.ingresosMes = 18320.25;
    _stats.cursosPopulares = 8;
    _stats.nuevosEstudiantes = 156;
    
    // Datos para gráfico de cursos más populares
    _datosCursos.clear();
    _datosCursos.push_back({"Fundamentos de Prog.", 420});
    _datosCursos.push_back({"Estructuras de Datos", 385});
    _datosCursos.push_back({"Ingeniería de Software", 342});
    _datosCursos.push_back({"Arquitectura SW", 298});
    _datosCursos.push_back({"Base de Datos", 276});
    
    // Datos para estudiantes por mes
    _datosEstudiantes.clear();
    _datosEstudiantes.push_back({"Enero", 234});
    _datosEstudiantes.push_back({"Febrero", 287});
    _datosEstudiantes.push_back({"Marzo", 312});
    _datosEstudiantes.push_back({"Abril", 298});
    _datosEstudiantes.push_back({"Mayo", 356});
    
    // Datos para ingresos por trimestre
    _datosIngresos.clear();
    _datosIngresos.push_back({"Q1 2024", 28450.75});
    _datosIngresos.push_back({"Q2 2024", 32100.25});
    _datosIngresos.push_back({"Q3 2024", 29875.50});
    _datosIngresos.push_back({"Q4 2024", 35214.00});
    _datosIngresos.push_back({"Q1 2025", 38920.30});
}

inline void EstadisticasEmpresaScreen::_cargarDatos() {
    SessionManager& sm = SessionManager::getInstance();

    /*
    _stats.totalCursos = 45;
    _stats.totalEspecializaciones = 12;
    _stats.totalEstudiantes = 2847;
    _stats.totalInscripciones = 5692;
    _stats.ingresosTotal = 125640.50;
    _stats.ingresosMes = 18320.25;
    _stats.cursosPopulares = 8;
    _stats.nuevosEstudiantes = 156;
    */
 
    _stats.totalCursos = sm.getActividadesController().getCantidadCursos();
    _stats.totalEspecializaciones = sm.getActividadesController().getCantidadEspecializaciones();
    _stats.totalInscripciones = sm.getActividadesController().getCantidadInscritos();
    _nombreEmpresa = sm.getCurrentUser().getNombreCompleto();
    

    _datosCursos.clear();
    _datosCursos = sm.getActividadesController().getOrdenadoInscripciones(5);
    sm.getActividadesController().reportarEstadisticas(_datosIngresos, _datosEstudiantes, _stats.ingresosTotal, 5);
    
}

// Dibujar interfaz completa
inline void EstadisticasEmpresaScreen::dibujarInterfazCompleta()
{
    system("cls");
    UI_EstadisticasEmpresa();

    _renderizarInformacionEmpresa();
    _renderizarEstadisticasGenerales();
    _renderizarSeccionActual();
    _renderizarNavegacion();

    resetColor();
}

// Renderizar información de la empresa
inline void EstadisticasEmpresaScreen::_renderizarInformacionEmpresa()
{
    // Nombre de la empresa
    gotoXY(_coordNombreEmpresa.X, _coordNombreEmpresa.Y);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::string nombreTruncado = truncarTexto(_nombreEmpresa, LONGITUD_EMPRESA);
    std::cout << nombreTruncado;

    resetColor();
}

// Renderizar estadísticas generales
inline void EstadisticasEmpresaScreen::_renderizarEstadisticasGenerales()
{
    // Cursos y Especializaciones
    gotoXY(_coordStatsGenerales.X + 55, _coordStatsGenerales.Y);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << formatearNumero(_stats.totalCursos);
    
    gotoXY(_coordStatsGenerales.X + 82, _coordStatsGenerales.Y);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << formatearNumero(_stats.totalEspecializaciones);
    
    // Estudiantes e Inscripciones
    gotoXY(_coordStatsGenerales.X, _coordStatsGenerales.Y);
    setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << formatearNumero(_stats.totalInscripciones);
    
    //gotoXY(_coordStatsGenerales.X, _coordStatsGenerales.Y);
    //setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
    //std::cout << formatearNumero(_stats.totalInscripciones);
    
    // Ingresos
    gotoXY(_coordStatsGenerales.X + 25, _coordStatsGenerales.Y);
    setConsoleColor(ColorIndex::ERROR_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << formatearDinero(_stats.ingresosTotal);
    
    //gotoXY(_coordStatsGenerales.X + 25, _coordStatsGenerales.Y);
    //setConsoleColor(ColorIndex::ERROR_COLOR, ColorIndex::FONDO_PRINCIPAL);
    //std::cout << formatearDinero(_stats.ingresosMes);

    resetColor();
}

// Renderizar sección actual
inline void EstadisticasEmpresaScreen::_renderizarSeccionActual()
{
    switch (_seccionActual) {
    case 0:
        _renderizarSeccionCursos();
        break;
    case 1:
        _renderizarSeccionEstudiantes();
        break;
    case 2:
        _renderizarSeccionIngresos();
        break;
    }
}

// Limpiar área de estadísticas - MÉTODO NO USADO
inline void EstadisticasEmpresaScreen::_limpiarAreaEstadisticas()
{
    // Este método ya no se usa - ahora cada función borra exactamente lo que va a escribir
    // Se mantiene por compatibilidad pero no se llama desde ningún lado
}

// Renderizar sección de cursos
inline void EstadisticasEmpresaScreen::_renderizarSeccionCursos()
{
    int fila = _coordSeccionCursos.Y;
    
    // Limpiar título anterior (solo lo que ensuciamos antes) y escribir nuevo
    gotoXY(_coordSeccionCursos.X, fila);
    if (!_tituloAnterior.empty()) {
        std::cout << std::string(_tituloAnterior.length(), ' '); // Borrar exactamente lo anterior
    }
    gotoXY(_coordSeccionCursos.X, fila);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "CURSOS MAS POPULARES";
    _tituloAnterior = "CURSOS MAS POPULARES"; // Recordar lo que escribimos
    
    fila += 4;
    
    // Redimensionar vectores si es necesario
    _nombresAnteriores.resize(MAX_ELEMENTOS_GRAFICO);
    _numerosAnteriores.resize(MAX_ELEMENTOS_GRAFICO);
    
    // Mostrar top 5 cursos
    for (int i = 0; i < _datosCursos.size() && i < MAX_ELEMENTOS_GRAFICO; ++i) 
    {
        // Limpiar nombre anterior y escribir nuevo
        gotoXY(_coordSeccionCursos.X + 3, fila + i);
        if (!_nombresAnteriores[i].empty()) {
            std::cout << std::string(_nombresAnteriores[i].length(), ' '); // Borrar exactamente lo anterior
        }
        gotoXY(_coordSeccionCursos.X + 3, fila + i);
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        std::string nombreTruncado = truncarTexto(_datosCursos[i].first, LONGITUD_NOMBRE_ITEM);
        std::cout << nombreTruncado;
        _nombresAnteriores[i] = nombreTruncado; // Recordar lo que escribimos
        
        // Limpiar número anterior y escribir nuevo
        gotoXY(_coordSeccionCursos.X + 50, fila + i);
        if (!_numerosAnteriores[i].empty()) {
            std::cout << std::string(_numerosAnteriores[i].length(), ' '); // Borrar exactamente lo anterior
        }
        gotoXY(_coordSeccionCursos.X + 50, fila + i);
        setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
        std::string numeroFormateado = formatearNumero(_datosCursos[i].second);
        std::cout << numeroFormateado;
        _numerosAnteriores[i] = numeroFormateado; // Recordar lo que escribimos
    }
    
    // Limpiar líneas que ya no se usan (elementos que había antes pero ya no)
    for (int i = _datosCursos.size(); i < MAX_ELEMENTOS_GRAFICO; ++i) {
        if (!_nombresAnteriores[i].empty()) {
            gotoXY(_coordSeccionCursos.X + 3, fila + i);
            std::cout << std::string(_nombresAnteriores[i].length(), ' ');
            _nombresAnteriores[i].clear();
        }
        if (!_numerosAnteriores[i].empty()) {
            gotoXY(_coordSeccionCursos.X + 50, fila + i);
            std::cout << std::string(_numerosAnteriores[i].length(), ' ');
            _numerosAnteriores[i].clear();
        }
    }
    
    resetColor();
}

// Renderizar sección de estudiantes
inline void EstadisticasEmpresaScreen::_renderizarSeccionEstudiantes()
{
    int fila = _coordSeccionEstudiantes.Y;
    
    // Limpiar título anterior (solo lo que ensuciamos antes) y escribir nuevo
    gotoXY(_coordSeccionEstudiantes.X, fila);
    if (!_tituloAnterior.empty()) {
        std::cout << std::string(_tituloAnterior.length(), ' '); // Borrar exactamente lo anterior
    }
    gotoXY(_coordSeccionEstudiantes.X, fila);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "NUEVOS ESTUDIANTES POR MES";
    _tituloAnterior = "NUEVOS ESTUDIANTES POR MES"; // Recordar lo que escribimos
    
    fila += 4;
    
    // Redimensionar vectores si es necesario
    _nombresAnteriores.resize(MAX_ELEMENTOS_GRAFICO);
    _numerosAnteriores.resize(MAX_ELEMENTOS_GRAFICO);
    
    // Mostrar datos de estudiantes por mes
    for (int i = 0; i < _datosEstudiantes.size() && i < MAX_ELEMENTOS_GRAFICO; ++i) 
    {
        // Limpiar mes anterior y escribir nuevo
        gotoXY(_coordSeccionEstudiantes.X + 3, fila + i);
        if (!_nombresAnteriores[i].empty()) {
            std::cout << std::string(_nombresAnteriores[i].length(), ' '); // Borrar exactamente lo anterior
        }
        gotoXY(_coordSeccionEstudiantes.X + 3, fila + i);
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << _datosEstudiantes[i].first;
        _nombresAnteriores[i] = _datosEstudiantes[i].first; // Recordar lo que escribimos
        
        // Limpiar número anterior y escribir nuevo
        gotoXY(_coordSeccionEstudiantes.X + 50, fila + i);
        if (!_numerosAnteriores[i].empty()) {
            std::cout << std::string(_numerosAnteriores[i].length(), ' '); // Borrar exactamente lo anterior
        }
        gotoXY(_coordSeccionEstudiantes.X + 50, fila + i);
        setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
        std::string numeroFormateado = formatearNumero(_datosEstudiantes[i].second);
        std::cout << numeroFormateado;
        _numerosAnteriores[i] = numeroFormateado; // Recordar lo que escribimos
    }
    
    // Limpiar líneas que ya no se usan (elementos que había antes pero ya no)
    for (int i = _datosEstudiantes.size(); i < MAX_ELEMENTOS_GRAFICO; ++i) {
        if (!_nombresAnteriores[i].empty()) {
            gotoXY(_coordSeccionEstudiantes.X + 3, fila + i);
            std::cout << std::string(_nombresAnteriores[i].length(), ' ');
            _nombresAnteriores[i].clear();
        }
        if (!_numerosAnteriores[i].empty()) {
            gotoXY(_coordSeccionEstudiantes.X + 50, fila + i);
            std::cout << std::string(_numerosAnteriores[i].length(), ' ');
            _numerosAnteriores[i].clear();
        }
    }
    
    resetColor();
}

// Renderizar sección de ingresos
inline void EstadisticasEmpresaScreen::_renderizarSeccionIngresos()
{
    int fila = _coordSeccionIngresos.Y;
    
    // Limpiar título anterior (solo lo que ensuciamos antes) y escribir nuevo
    gotoXY(_coordSeccionIngresos.X, fila);
    if (!_tituloAnterior.empty()) {
        std::cout << std::string(_tituloAnterior.length(), ' '); // Borrar exactamente lo anterior
    }
    gotoXY(_coordSeccionIngresos.X, fila);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "INGRESOS POR TRIMESTRE";
    _tituloAnterior = "INGRESOS POR TRIMESTRE"; // Recordar lo que escribimos
    
    fila += 4;
    
    // Redimensionar vectores si es necesario
    _nombresAnteriores.resize(MAX_ELEMENTOS_GRAFICO);
    _numerosAnteriores.resize(MAX_ELEMENTOS_GRAFICO);
    
    // Mostrar datos de ingresos por trimestre
    for (int i = 0; i < _datosIngresos.size() && i < MAX_ELEMENTOS_GRAFICO; ++i) 
    {
        // Limpiar trimestre anterior y escribir nuevo
        gotoXY(_coordSeccionIngresos.X + 3, fila + i);
        if (!_nombresAnteriores[i].empty()) {
            std::cout << std::string(_nombresAnteriores[i].length(), ' '); // Borrar exactamente lo anterior
        }
        gotoXY(_coordSeccionIngresos.X + 3, fila + i);
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << _datosIngresos[i].first;
        _nombresAnteriores[i] = _datosIngresos[i].first; // Recordar lo que escribimos
        
        // Limpiar dinero anterior y escribir nuevo
        gotoXY(_coordSeccionIngresos.X + 50, fila + i);
        if (!_numerosAnteriores[i].empty()) {
            std::cout << std::string(_numerosAnteriores[i].length(), ' '); // Borrar exactamente lo anterior
        }
        gotoXY(_coordSeccionIngresos.X + 50, fila + i);
        setConsoleColor(ColorIndex::ERROR_COLOR, ColorIndex::FONDO_PRINCIPAL);
        std::string dineroFormateado = formatearDinero(_datosIngresos[i].second);
        std::cout << dineroFormateado;
        _numerosAnteriores[i] = dineroFormateado; // Recordar lo que escribimos
    }
    
    // Limpiar líneas que ya no se usan (elementos que había antes pero ya no)
    for (int i = _datosIngresos.size(); i < MAX_ELEMENTOS_GRAFICO; ++i) {
        if (!_nombresAnteriores[i].empty()) {
            gotoXY(_coordSeccionIngresos.X + 3, fila + i);
            std::cout << std::string(_nombresAnteriores[i].length(), ' ');
            _nombresAnteriores[i].clear();
        }
        if (!_numerosAnteriores[i].empty()) {
            gotoXY(_coordSeccionIngresos.X + 50, fila + i);
            std::cout << std::string(_numerosAnteriores[i].length(), ' ');
            _numerosAnteriores[i].clear();
        }
    }
    
    resetColor();
}

// Renderizar navegación
inline void EstadisticasEmpresaScreen::_renderizarNavegacion()
{
    gotoXY(_coordNavegacion.X, _coordNavegacion.Y);
    
    // Mostrar indicadores de sección
    std::vector<std::string> secciones = {"CURSOS", "ESTUDIANTES", "INGRESOS"};
    
    for (int i = 0; i < secciones.size(); ++i) {
        if (i == _seccionActual) {
            setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
        } else {
            setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        }
        
        std::cout << " " << secciones[i] << " ";
        
        if (i < secciones.size() - 1) {
            setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
            std::cout << " | ";
        }
    }
    
    resetColor();
}

// Actualizar selección - borrado preciso por string
inline void EstadisticasEmpresaScreen::_actualizarSeleccion()
{
    // Solo renderizar las nuevas estadísticas (cada función borra lo suyo)
    _renderizarSeccionActual();
    
    // Actualizar la navegación
    _renderizarNavegacion();
}

// Manejar navegación
inline void EstadisticasEmpresaScreen::_manejarNavegacion(int tecla)
{
    switch (tecla) {
    case 75: // Flecha izquierda
        if (_seccionActual > 0) {
            _seccionActual--;
        } else {
            _seccionActual = _totalSecciones - 1; // Wrap al final
        }
        break;
        
    case 77: // Flecha derecha
        if (_seccionActual < _totalSecciones - 1) {
            _seccionActual++;
        } else {
            _seccionActual = 0; // Wrap al inicio
        }
        break;
    }
}

// Cambiar sección
inline void EstadisticasEmpresaScreen::_cambiarSeccion(int nuevaSeccion)
{
    if (nuevaSeccion >= 0 && nuevaSeccion < _totalSecciones) {
        _seccionActual = nuevaSeccion;
    }
}

// Formatear número
inline std::string EstadisticasEmpresaScreen::formatearNumero(int numero)
{
    std::string resultado = std::to_string(numero);
    
    // Agregar comas cada 3 dígitos (simplificado)
    if (resultado.length() > 3) {
        for (int i = resultado.length() - 3; i > 0; i -= 3) {
            resultado.insert(i, ",");
        }
    }
    
    return resultado;
}

// Formatear dinero
inline std::string EstadisticasEmpresaScreen::formatearDinero(double cantidad)
{
    std::ostringstream oss;
    oss << "S/" << std::fixed << std::setprecision(2) << cantidad;
    std::string resultado = oss.str();
    
    // Agregar comas (simplificado)
    size_t pos = resultado.find('.');
    if (pos != std::string::npos && pos > 4) {
        for (int i = pos - 3; i > 1; i -= 3) {
            resultado.insert(i, ",");
        }
    }
    
    return resultado;
}

// Truncar texto
inline std::string EstadisticasEmpresaScreen::truncarTexto(const std::string& texto, int maxLongitud)
{
    if (texto.length() <= maxLongitud) {
        return texto;
    }
    return texto.substr(0, maxLongitud - 3) + "...";
}

// Crear barra de progreso
inline std::string EstadisticasEmpresaScreen::crearBarraProgreso(int valor, int maximo, int longitud)
{
    if (maximo <= 0) return std::string(longitud, ' ');
    
    int relleno = (valor * longitud) / maximo;
    if (relleno > longitud) relleno = longitud;
    
    std::string barra = "[";
    barra += std::string(relleno, '=');
    barra += std::string(longitud - relleno, '-');
    barra += "]";
    
    return barra;
}

// Procesar selección
inline ResultadoPantalla EstadisticasEmpresaScreen::_procesarSeleccion()
{
    ResultadoPantalla res;
    
    // Por ahora no hay acciones específicas en la selección
    // Se podría agregar funcionalidad para ver detalles de cada sección
    
    return res;
}

// Método principal de ejecución
inline ResultadoPantalla EstadisticasEmpresaScreen::ejecutar()
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

        case 13: // Enter - Procesar selección (opcional)
        {
            ResultadoPantalla res = _procesarSeleccion();
            if (res.accion != AccionPantalla::NINGUNA) {
                return res;
            }
        }
        break;
        
        case 'r':
        case 'R': // Tecla R para refrescar datos (funcionalidad futura)
        {
            gotoXY(10, 28);
            setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
            std::cout << "[INFO]: Datos actualizados";
            resetColor();
            _getch();
            
            // Limpiar mensaje
            gotoXY(10, 28);
            std::cout << "                        ";
        }
        break;

        default:
            // Ignorar otras teclas
            break;
        }
    }
}

#endif // COURSERACLONE_SCREENS_ESTADISTICASEMPRESASCREEN_HPP