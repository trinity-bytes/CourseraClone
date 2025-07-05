#ifndef COURSERACLONE_SCREENS_VERBOLETASSCREEN_HPP
#define COURSERACLONE_SCREENS_VERBOLETASSCREEN_HPP

// Headers estándar
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <conio.h>

// Headers propios
#include "../Utils/SystemUtils.hpp"
#include "../Utils/ScreenSystem.hpp"
#include "../Utils/UI_Ascii.hpp"
#include "../Types/UsuarioTypes.hpp"
#include "../Entities/ComprobanteDePago.hpp"
#include "../Utils/QR/AutocontainedQR.hpp"
#include "../Utils/QR/QRCodeGenerator.hpp"
#include "../Utils/ConsoleConfig.hpp"

/// Pantalla para ver comprobantes de pago del estudiante
class VerBoletasScreen : public PantallaBase
{
private:
    // Estado de navegación
    AccionPantalla _pantallaAnterior;
    bool _primeraRenderizacion;
    
    // Navegación y selección
    int _comprobanteSeleccionado;
    int _indiceInicio;
    int _comprobantesPorPagina;
    
    // Datos simulados de comprobantes
    std::vector<ComprobanteDePago> _comprobantes;
    
    // COORDENADAS PARA EL SISTEMA DE POSICIONAMIENTO
    /// @brief Coordenadas para elementos principales
    static const short LISTA_INICIO_X = 8;
    static const short LISTA_INICIO_Y = 8;
    static const short ALTURA_COMPROBANTE = 2;
    static const short ANCHO_COMPROBANTE = 90;
    
    /// @brief Coordenadas para la información de paginación
    const COORD _coordsPaginacion = {8, 27};
    const COORD _coordsIndicadorPrevio = {60, 27};
    const COORD _coordsIndicadorSiguiente = {60, 27};
    
    /// @brief Coordenadas para los campos de cada comprobante
    struct CoordsComprobante {
        COORD numero;      // Número de comprobante
        COORD fecha;       // Fecha de emisión
        COORD actividad;   // Nombre de la actividad
        COORD monto;       // Monto pagado
        COORD estado;      // Estado del comprobante
    };
    
    // ---- MÉTODOS PRIVADOS ----
    
    /// @brief Métodos de inicialización
    inline void _limpiarEstado();
    inline void _cargarDatosEjemplo();
    
    /// @brief Métodos de renderizado
    inline void dibujarInterfazCompleta();
    inline void _renderizarListaComprobantes();
    inline void _renderizarComprobante(const ComprobanteDePago& comprobante, int indice, bool seleccionado);
    inline void _renderizarIndicadoresPaginacion();
    inline void _mostrarQRComprobante(const ComprobanteDePago& comprobante);
    inline void _actualizarSeleccion();
    
    /// @brief Métodos de configuración de consola para QR
    inline void _configurarConsolaParaQR();
    inline void _restaurarConsolaNormal();
    
    /// @brief Métodos de navegación
    inline void _manejarNavegacion(int tecla);
    inline void _navegarArriba();
    inline void _navegarAbajo();
    
    /// @brief Métodos de procesamiento
    inline ResultadoPantalla _procesarSeleccion();
    
    /// @brief Métodos utilitarios
    inline CoordsComprobante _calcularCoordenadasComprobante(int indice);
    inline std::string _formatearMonto(double monto);

public:
    inline VerBoletasScreen(AccionPantalla pantallaAnterior = AccionPantalla::IR_A_PERFIL_ESTUDIANTE);
    
    inline ~VerBoletasScreen() = default;

    inline ResultadoPantalla ejecutar() override;
};

// --- IMPLEMENTACIONES INLINE ---

// Constructor
inline VerBoletasScreen::VerBoletasScreen(AccionPantalla pantallaAnterior) : PantallaBase(),
    _pantallaAnterior(pantallaAnterior), _primeraRenderizacion(true), 
    _comprobanteSeleccionado(0), _indiceInicio(0), _comprobantesPorPagina(8)
{
    _cargarDatosEjemplo();
}

// Limpiar estado
inline void VerBoletasScreen::_limpiarEstado()
{
    _comprobanteSeleccionado = 0;
    _indiceInicio = 0;
    _primeraRenderizacion = true;
}

// Cargar datos de ejemplo para pruebas
inline void VerBoletasScreen::_cargarDatosEjemplo()
{
    _comprobantes.clear();
    
    // Generar comprobantes de ejemplo con datos más realistas para QR
    ComprobanteDePago comp1(1, 1001, 101, TipoActividad::CURSO, 99.99);
    comp1.establecerFechaEmision("2024-12-15");
    _comprobantes.push_back(comp1);
    
    ComprobanteDePago comp2(2, 1001, 102, TipoActividad::ESPECIALIZACION, 299.50);
    comp2.establecerFechaEmision("2024-12-10");
    _comprobantes.push_back(comp2);
    
    ComprobanteDePago comp3(3, 1001, 103, TipoActividad::CURSO, 149.99);
    comp3.establecerFechaEmision("2024-12-05");
    _comprobantes.push_back(comp3);
    
    ComprobanteDePago comp4(4, 1001, 104, TipoActividad::ESPECIALIZACION, 399.99);
    comp4.establecerFechaEmision("2024-11-28");
    _comprobantes.push_back(comp4);
    
    ComprobanteDePago comp5(5, 1001, 105, TipoActividad::CURSO, 79.99);
    comp5.establecerFechaEmision("2024-11-20");
    _comprobantes.push_back(comp5);
    
    ComprobanteDePago comp6(6, 1001, 106, TipoActividad::CURSO, 119.99);
    comp6.establecerFechaEmision("2024-11-15");
    _comprobantes.push_back(comp6);
    
    ComprobanteDePago comp7(7, 1001, 107, TipoActividad::ESPECIALIZACION, 249.99);
    comp7.establecerFechaEmision("2024-11-10");
    _comprobantes.push_back(comp7);
    
    ComprobanteDePago comp8(8, 1001, 108, TipoActividad::CURSO, 89.99);
    comp8.establecerFechaEmision("2024-11-05");
    _comprobantes.push_back(comp8);
}

// Dibujar interfaz completa
inline void VerBoletasScreen::dibujarInterfazCompleta()
{
    system("cls");
    UI_ComprobanteDePago();
    
    _renderizarListaComprobantes();
    _renderizarIndicadoresPaginacion();
    
    resetColor();
}

// Calcular coordenadas para un comprobante específico
inline VerBoletasScreen::CoordsComprobante VerBoletasScreen::_calcularCoordenadasComprobante(int indice)
{
    short fila = static_cast<short>(LISTA_INICIO_Y + (indice * ALTURA_COMPROBANTE));
    
    CoordsComprobante coords;
    coords.numero = {LISTA_INICIO_X, fila};
    coords.fecha = {static_cast<short>(LISTA_INICIO_X + 8), fila};
    coords.actividad = {static_cast<short>(LISTA_INICIO_X + 20), fila};
    coords.monto = {static_cast<short>(LISTA_INICIO_X + 65), fila};
    coords.estado = {static_cast<short>(LISTA_INICIO_X + 78), fila};
    
    return coords;
}

// Formatear monto con símbolo de moneda
inline std::string VerBoletasScreen::_formatearMonto(double monto)
{
    std::ostringstream oss;
    oss << "S/ " << std::fixed << std::setprecision(2) << monto;
    return oss.str();
}

// Renderizar lista de comprobantes usando coordenadas
inline void VerBoletasScreen::_renderizarListaComprobantes()
{
    if (_comprobantes.empty()) {
        gotoXY(LISTA_INICIO_X, LISTA_INICIO_Y + 2);
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "No tienes comprobantes de pago registrados.";
        resetColor();
        return;
    }
    
    int comprobantesAMostrar = (std::min)(_comprobantesPorPagina,
                                      static_cast<int>(_comprobantes.size()) - _indiceInicio);
    
    for (int i = 0; i < comprobantesAMostrar; ++i) {
        int indiceGlobal = _indiceInicio + i;
        const ComprobanteDePago& comprobante = _comprobantes[indiceGlobal];
        bool seleccionado = (_comprobanteSeleccionado == i);
        
        _renderizarComprobante(comprobante, i, seleccionado);
    }
}

// Renderizar un comprobante individual con coordenadas precisas
inline void VerBoletasScreen::_renderizarComprobante(const ComprobanteDePago& comprobante, int indice, bool seleccionado)
{
    CoordsComprobante coords = _calcularCoordenadasComprobante(indice);
    
    // Obtener datos del comprobante usando el método público
    RawComprobanteData datos = const_cast<ComprobanteDePago&>(comprobante).obtenerDatosCrudosComprobante();
    
    // Configurar colores según selección
    if (seleccionado) {
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
    } else {
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    }
    
    // Limpiar línea completa
    gotoXY(LISTA_INICIO_X, coords.numero.Y);
    std::cout << std::string(ANCHO_COMPROBANTE, ' ');
    
    // Renderizar campos del comprobante con datos QR-ready
    // Número de comprobante
    gotoXY(coords.numero.X, coords.numero.Y);
    std::cout << "#" << std::setfill('0') << std::setw(4) << datos.id;
    
    // Fecha de emisión (formato QR)
    gotoXY(coords.fecha.X, coords.fecha.Y);
    std::cout << datos.fechaEmision;
    
    // Información de actividad con datos para QR
    gotoXY(coords.actividad.X, coords.actividad.Y);
    std::string tipoActividad = (datos.tipoActividad == TipoActividad::CURSO) ? "Curso" : "Especialización";
    std::string nombreSimulado = (datos.tipoActividad == TipoActividad::CURSO) 
        ? "Programación C++" 
        : "Data Science";
    std::cout << tipoActividad << ": " << nombreSimulado;
    
    // Monto pagado (exacto para QR)
    gotoXY(coords.monto.X, coords.monto.Y);
    std::cout << _formatearMonto(datos.montoPagado);
    
    // Estado con indicador de QR disponible
    gotoXY(coords.estado.X, coords.estado.Y);
    setConsoleColor(ColorIndex::EXITO_COLOR, seleccionado ? ColorIndex::AZUL_MARCA : ColorIndex::FONDO_PRINCIPAL);
    std::cout << "QR ✓";
    
    // Indicador visual de que tiene QR autocontenido
    if (seleccionado) {
        gotoXY(coords.estado.X + 6, coords.estado.Y);
        setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
        std::cout << "ENTER=Ver QR";
    }
    
    resetColor();
}

// Renderizar indicadores de paginación usando coordenadas
inline void VerBoletasScreen::_renderizarIndicadoresPaginacion()
{
    if (_comprobantes.empty()) return;
    
    // Información de página actual
    gotoXY(_coordsPaginacion.X, _coordsPaginacion.Y);
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    
    int paginaActual = (_indiceInicio / _comprobantesPorPagina) + 1;
    int totalPaginas = ((_comprobantes.size() - 1) / _comprobantesPorPagina) + 1;
    
    std::cout << "Página " << paginaActual << " de " << totalPaginas 
              << " | Total: " << _comprobantes.size() << " comprobantes con formato JSON estándar";
    
    // Instrucciones QR
    gotoXY(_coordsPaginacion.X, _coordsPaginacion.Y + 1);
    setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "ENTER = Ver QR estándar (formato definitivo) | ESC = Volver | ↑↓ = Navegar";
    
    // Indicadores de navegación
    if (_indiceInicio > 0) {
        gotoXY(_coordsIndicadorPrevio.X, _coordsIndicadorPrevio.Y);
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "↑ Flecha ARRIBA para ver anteriores ";
    }
    
    if (_indiceInicio + _comprobantesPorPagina < _comprobantes.size()) {
        gotoXY(_coordsIndicadorSiguiente.X, _coordsIndicadorSiguiente.Y);
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "↓ Flecha ABAJO para ver siguientes  ";
    }
    
    resetColor();
}

// Mostrar QR para el comprobante usando coordenadas
inline void VerBoletasScreen::_mostrarQRComprobante(const ComprobanteDePago& comprobante)
{
    // Configurar consola para mostrar QR óptimamente
    _configurarConsolaParaQR();
    
    system("cls");
    
    // Obtener datos del comprobante usando el método público
    RawComprobanteData datos = const_cast<ComprobanteDePago&>(comprobante).obtenerDatosCrudosComprobante();
    
    // Coordenadas REORGANIZADAS para QR completo
    const COORD coordsTituloQR = {120, 1};             // Centrado en ventana más ancha
    const COORD coordsInfoComprobante = {5, 3};        // Información izquierda
    const COORD coordsQR = {5, 12};                    // QR en la izquierda, suficiente espacio
    const COORD coordsURL = {150, 3};                  // URL en la derecha
    const COORD coordsJSON = {150, 35};                // JSON en la derecha, más abajo
    const COORD coordsInstrucciones = {120, 110};      // Instrucciones al final
    
    // Título de la pantalla del QR - CENTRADO
    gotoXY(coordsTituloQR.X, coordsTituloQR.Y);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "QR AUTOCONTENIDO - GENERAR BOLETA EN WEB";
    
    // ===== SECCIÓN IZQUIERDA: INFORMACIÓN DEL COMPROBANTE =====
    gotoXY(coordsInfoComprobante.X, coordsInfoComprobante.Y);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "=== DATOS DEL COMPROBANTE ===";
    
    gotoXY(coordsInfoComprobante.X, coordsInfoComprobante.Y + 2);
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Comprobante #" << std::setfill('0') << std::setw(4) << datos.id;
    
    gotoXY(coordsInfoComprobante.X, coordsInfoComprobante.Y + 3);
    std::cout << "Fecha: " << datos.fechaEmision;
    
    gotoXY(coordsInfoComprobante.X, coordsInfoComprobante.Y + 4);
    std::cout << "Estudiante ID: " << datos.idEstudiante;
    
    gotoXY(coordsInfoComprobante.X, coordsInfoComprobante.Y + 5);
    std::cout << "Actividad ID: " << datos.idActividad;
    
    gotoXY(coordsInfoComprobante.X, coordsInfoComprobante.Y + 6);
    std::cout << "Tipo: " << (datos.tipoActividad == TipoActividad::CURSO ? "Curso" : "Especialización");
    
    gotoXY(coordsInfoComprobante.X, coordsInfoComprobante.Y + 7);
    std::cout << "Monto: " << _formatearMonto(datos.montoPagado);
    
    // Nombres simulados para el QR
    std::string nombreEstudiante = "Estudiante de Prueba";
    std::string nombreCurso = (datos.tipoActividad == TipoActividad::CURSO) 
        ? "Curso de Programación" 
        : "Especialización en Data Science";
    
    // Generar URL con formato ESTÁNDAR según especificación
    std::string urlAutocontenida = CourseraClone::QR::AutocontainedQR::generarURLEstandar(
        datos, 
        nombreEstudiante, 
        nombreCurso
    );
    
    // Mostrar evaluación del tamaño
    gotoXY(coordsInfoComprobante.X, coordsInfoComprobante.Y + 9);
    setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << CourseraClone::QR::AutocontainedQR::evaluarTamaño(urlAutocontenida);
    
    // ===== SECCIÓN IZQUIERDA ABAJO: CÓDIGO QR =====
    gotoXY(coordsQR.X, coordsQR.Y);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "=== CÓDIGO QR AUTOCONTENIDO ===";
    
    gotoXY(coordsQR.X, coordsQR.Y + 1);
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Escanea para generar boleta en web:";
    
    try {
        // USANDO LAS NUEVAS OPTIMIZACIONES: Configuración automática óptima
        CourseraClone::QR::QRConfig config = CourseraClone::QR::QRCodeGenerator::configuracionOptima(urlAutocontenida.length());
        
        // Forzar estilo básico para mejor legibilidad en consola
        config.style = CourseraClone::QR::ASCIIStyle::BASIC;
        config.useColors = false;
        config.borderSize = 1;  // Las optimizaciones ajustarán automáticamente si es necesario
        
        CourseraClone::QR::QRCodeGenerator generator(config);
        
        // Mostrar análisis del contenido antes de generar
        gotoXY(coordsQR.X, coordsQR.Y + 2);
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "Análisis: URL de " << urlAutocontenida.length() << " caracteres - Optimización automática activa";
        
        std::string qrVisual = generator.generateFromText(urlAutocontenida);
        
        // Mostrar el QR línea por línea con MÁS espacio disponible
        gotoXY(coordsQR.X, coordsQR.Y + 3);
        size_t pos = 0;
        int lineaActual = 0;
        while (pos < qrVisual.length() && lineaActual < 90) {  // Muchas más líneas disponibles
            size_t finLinea = qrVisual.find('\n', pos);
            if (finLinea == std::string::npos) {
                finLinea = qrVisual.length();
            }
            
            gotoXY(coordsQR.X, coordsQR.Y + 3 + lineaActual);
            std::cout << qrVisual.substr(pos, finLinea - pos);
            
            pos = finLinea + 1;
            lineaActual++;
        }
    }
    catch (const std::exception& e) {
        gotoXY(coordsQR.X, coordsQR.Y + 3);
        setConsoleColor(ColorIndex::ERROR_COLOR, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "Error generando QR: " << e.what();
    }
    
    // ===== SECCIÓN DERECHA ARRIBA: URL COMPLETA =====
    gotoXY(coordsURL.X, coordsURL.Y);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "=== URL AUTOCONTENIDA COMPLETA ===";
    
    gotoXY(coordsURL.X, coordsURL.Y + 1);
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Esta URL contiene TODOS los datos:";
    
    // Mostrar URL línea por línea sin sobreescritura
    std::string urlFormateada = urlAutocontenida;
    size_t maxLineLength = 140;  // Más ancho para la ventana más grande
    size_t pos = 0;
    int lineNumber = 0;
    
    while (pos < urlFormateada.length() && lineNumber < 30) {  // Más líneas para URL
        size_t endPos = pos + maxLineLength;
        if (endPos >= urlFormateada.length()) {
            endPos = urlFormateada.length();
        } else {
            // Buscar punto de corte apropiado
            while (endPos > pos && urlFormateada[endPos] != '/' && 
                   urlFormateada[endPos] != '&' && urlFormateada[endPos] != '=') {
                endPos--;
            }
            if (endPos == pos) endPos = pos + maxLineLength;
        }
        
        gotoXY(coordsURL.X, coordsURL.Y + 3 + lineNumber);
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << urlFormateada.substr(pos, endPos - pos);
        
        pos = endPos;
        lineNumber++;
    }
    
    // ===== SECCIÓN DERECHA ABAJO: JSON DECODIFICADO =====
    gotoXY(coordsJSON.X, coordsJSON.Y);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "=== DATOS JSON INCLUIDOS ===";
    
    gotoXY(coordsJSON.X, coordsJSON.Y + 1);
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Datos que recibe la página web:";
    
    // Generar el JSON ESTÁNDAR que va en la URL
    std::string jsonDatos = CourseraClone::QR::AutocontainedQR::generarQRComprobanteEstandar(
        datos, 
        nombreEstudiante, 
        nombreCurso
    );
    
    // Mostrar JSON formateado sin sobreescritura
    size_t jsonPos = 0;
    int jsonLineNumber = 0;
    
    while (jsonPos < jsonDatos.length() && jsonLineNumber < 25) {  // Más líneas para JSON
        size_t jsonEndPos = jsonPos + 120;  // Líneas más largas para JSON
        if (jsonEndPos >= jsonDatos.length()) {
            jsonEndPos = jsonDatos.length();
        } else {
            // Buscar punto de corte apropiado para JSON
            while (jsonEndPos > jsonPos && jsonDatos[jsonEndPos] != ',' && 
                   jsonDatos[jsonEndPos] != '"' && jsonDatos[jsonEndPos] != ':') {
                jsonEndPos--;
            }
            if (jsonEndPos == jsonPos) jsonEndPos = jsonPos + 120;
        }
        
        gotoXY(coordsJSON.X, coordsJSON.Y + 3 + jsonLineNumber);
        setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << jsonDatos.substr(jsonPos, jsonEndPos - jsonPos);
        
        jsonPos = jsonEndPos;
        jsonLineNumber++;
    }
    
    // ===== INSTRUCCIONES AL FINAL =====
    gotoXY(coordsInstrucciones.X, coordsInstrucciones.Y);
    setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "▶ Formato JSON estándar según especificación técnica definida";
    
    gotoXY(coordsInstrucciones.X, coordsInstrucciones.Y + 1);
    std::cout << "▶ Campos: t, i, s, c, d, a, ct (sin abreviaciones en datos)";
    
    gotoXY(coordsInstrucciones.X, coordsInstrucciones.Y + 2);
    std::cout << "▶ Compatibilidad total con sistema web de verificación";
    
    gotoXY(coordsInstrucciones.X, coordsInstrucciones.Y + 3);
    std::cout << "▶ URL: trinity-bytes.github.io/WebServices-for-CourseraClone";
    
    gotoXY(coordsInstrucciones.X, coordsInstrucciones.Y + 5);
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Presiona cualquier tecla para volver...";
    
    resetColor();
    
    // Esperar a que el usuario presione una tecla
    _getch();
    
    // Restaurar configuración normal de consola
    _restaurarConsolaNormal();
}

// Actualizar selección
inline void VerBoletasScreen::_actualizarSeleccion()
{
    _renderizarListaComprobantes();
    _renderizarIndicadoresPaginacion();
}

// Manejar navegación
inline void VerBoletasScreen::_manejarNavegacion(int tecla)
{
    switch (tecla) {
    case 72: // Flecha arriba
        _navegarArriba();
        break;
    case 80: // Flecha abajo
        _navegarAbajo();
        break;
    }
}

// Navegar hacia arriba
inline void VerBoletasScreen::_navegarArriba()
{
    if (_comprobanteSeleccionado > 0) {
        _comprobanteSeleccionado--;
    } else if (_indiceInicio > 0) {
        _indiceInicio--;
        _comprobanteSeleccionado = 0;
    }
}

// Navegar hacia abajo
inline void VerBoletasScreen::_navegarAbajo()
{
    int comprobantesEnPagina = (std::min)(_comprobantesPorPagina,
                                       static_cast<int>(_comprobantes.size()) - _indiceInicio);
    
    if (_comprobanteSeleccionado < comprobantesEnPagina - 1) {
        _comprobanteSeleccionado++;
    } else if (_indiceInicio + _comprobantesPorPagina < _comprobantes.size()) {
        _indiceInicio++;
        _comprobanteSeleccionado = 0;
    }
}

// Procesar selección
inline ResultadoPantalla VerBoletasScreen::_procesarSeleccion()
{
    ResultadoPantalla res;
    
    if (!_comprobantes.empty() && _indiceInicio + _comprobanteSeleccionado < _comprobantes.size()) {
        // Obtener el comprobante seleccionado
        const ComprobanteDePago& comprobanteSeleccionado = _comprobantes[_indiceInicio + _comprobanteSeleccionado];
        
        // Mostrar el QR del comprobante
        _mostrarQRComprobante(comprobanteSeleccionado);
        
        // Después de mostrar el QR, redibujar la interfaz completa
        _primeraRenderizacion = true;
    }
    
    return res;
}

// Configurar consola específicamente para mostrar QR
inline void VerBoletasScreen::_configurarConsolaParaQR()
{
    // Configurar fuente más pequeña para que el QR quepa mejor
    configurarFuente(L"Consolas", 6);  // Fuente aún más pequeña
    
    // Configurar tamaño de ventana MUY grande para QR completo
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = { 300, 120 };  // Ventana mucho más grande
    SetConsoleScreenBufferSize(hConsole, bufferSize);
    
    SMALL_RECT windowSize = { 0, 0, 299, 119 };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

// Restaurar configuración normal de consola
inline void VerBoletasScreen::_restaurarConsolaNormal()
{
    // Restaurar fuente normal
    configurarFuente(L"Cascadia Code Semibold", 22);
    
    // Restaurar tamaño de ventana normal
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = { ANCHO_CONSOLA, ALTO_CONSOLA };
    SetConsoleScreenBufferSize(hConsole, bufferSize);
    
    SMALL_RECT windowSize = { 0, 0, ANCHO_CONSOLA - 1, ALTO_CONSOLA - 1 };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

inline ResultadoPantalla VerBoletasScreen::ejecutar()
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
            _manejarNavegacion(tecla);
            break;
            
        case 13: // Enter - Ver detalles del comprobante
        {
            ResultadoPantalla res = _procesarSeleccion();
            if (res.accion != AccionPantalla::NINGUNA) {
                return res;
            }
        }
        break;
        
        case 27: // ESC - Volver a pantalla anterior
        {
            ResultadoPantalla res;
            res.accion = _pantallaAnterior;
            return res;
        }
        
        default:
            // Ignorar otras teclas
            break;
        }
    }
}

#endif // COURSERACLONE_SCREENS_VERBOLETASSCREEN_HPP
