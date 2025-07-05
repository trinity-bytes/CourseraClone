#ifndef COURSERACLONE_SCREENS_VERCERTIFICADOSSCREEN_HPP
#define COURSERACLONE_SCREENS_VERCERTIFICADOSSCREEN_HPP

// Headers estándar


#include <string>
#include <vector>
#include <conio.h>
#include <limits>
#include "../Entities/Certificado.hpp"

// Headers propios
#include "../Utils/SystemUtils.hpp"
#include "../Utils/ScreenSystem.hpp"
#include "../Utils/UI_Ascii.hpp"
#include "../Utils/InputUtils.hpp"
#include "../Utils/ValidationUtils.hpp"
#include "../Controllers/ContentManager.hpp"
#include "../Controllers/SessionManager.hpp"
#include "../Types/UsuarioTypes.hpp"
#include "../Utils/QR/AutocontainedQR.hpp"
#include "../Utils/QR/QRCodeGenerator.hpp"
#include "../Utils/ConsoleConfig.hpp"

/// Pantalla para visualizar certificados obtenidos por el estudiante
class VerCertificadosScreen : public PantallaBase
{
private:
    // Estado de navegación
    AccionPantalla _pantallaAnterior;
    bool _primeraRenderizacion;
    
    // Navegación de certificados
    int _certificadoActual;
    int _totalCertificados;
    
    // Estructura de datos para certificados
    
    std::vector<Certificado> _certificados;
    
    // === SISTEMA DE COORDENADAS BASADO EN POSICIONAMIENTO MANUAL ===
    
    /// @brief Coordenadas para elementos del certificado principal
    COORD _coordNombreEstudiante = {38, 18};
    COORD _coordNombreCurso = {36, 22};
    
    /// @brief Coordenadas para información adicional del certificado
    COORD _coordInstructor = {9, 24};
    COORD _coordFecha = {59, 24};
    COORD _coordIdCertificado = {79, 24};
    
    /// @brief Coordenadas para navegación y botones
    COORD _coordNavegacion = {79, 27};
    
    // === SISTEMA DE LIMPIEZA DINÁMICA ===
    /// @brief Variables para recordar textos anteriores y hacer limpieza dinámica
    std::string _nombreEstudianteAnterior;
    std::string _nombreCursoAnterior;
    std::string _instructorAnterior;
    std::string _fechaAnterior;
    std::string _idCertificadoAnterior;
    std::string _navegacionAnterior;
    
    // ---- MÉTODOS PRIVADOS ----
    
    /// @brief Métodos de inicialización
    inline void _limpiarEstado();
    inline void _cargarCertificadosReales();
    inline void _cargarCertificadosEjemplo(); // Mantener como fallback
    
    /// @brief Métodos de renderizado
    inline void dibujarInterfazCompleta();
    inline void _renderizarCertificadoActual();
    inline void _renderizarNavegacion();
    inline void _limpiarTextoAnterior(); // Nuevo método de limpieza dinámica
    
    /// @brief Métodos de navegación
    inline void _navegarAnterior();
    inline void _navegarSiguiente();
    
    /// @brief Métodos de QR para certificados
    inline void _mostrarQRCertificado(const Certificado& certificado);
    inline void _configurarConsolaParaQR();
    inline void _restaurarConsolaNormal();
    inline std::string _formatearCalificacion(double calificacion);
    inline std::string _formatearDuracion(int duracionHoras, bool esEspecializacion);
    
    /// @brief Métodos de utilidad
    inline std::string _formatearFecha(const std::string& fecha);
    inline std::string _convertirFechaAISO(const std::string& fechaDDMMYYYY);

public:
    inline VerCertificadosScreen(AccionPantalla pantallaAnterior = AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE);
    
    inline ~VerCertificadosScreen() = default;

    inline ResultadoPantalla ejecutar() override;
};

// --- IMPLEMENTACIONES INLINE ---

// Constructor
inline VerCertificadosScreen::VerCertificadosScreen(AccionPantalla pantallaAnterior) : PantallaBase(),
    _pantallaAnterior(pantallaAnterior), _primeraRenderizacion(true), 
    _certificadoActual(0), _totalCertificados(0)
{
    _cargarCertificadosReales();
}

// Limpiar estado
inline void VerCertificadosScreen::_limpiarEstado()
{
    _certificadoActual = 0;
    _primeraRenderizacion = true;
    
    // Limpiar strings de control de limpieza dinámica
    _nombreEstudianteAnterior.clear();
    _nombreCursoAnterior.clear();
    _instructorAnterior.clear();
    _fechaAnterior.clear();
    _idCertificadoAnterior.clear();
    _navegacionAnterior.clear();
}

// Cargar certificados reales desde ContentManager y SessionManager
inline void VerCertificadosScreen::_cargarCertificadosReales()
{
    _certificados.clear();
    
    // Verificar si hay sesión activa
    SessionManager& sessionManager = SessionManager::getInstance();
    if (!sessionManager.isLoggedIn()) {
        // Si no hay sesión, usar datos de ejemplo
        _cargarCertificadosEjemplo();
        return;
    }
    
    // Obtener datos del usuario actual REAL
    Usuario& usuarioActual = sessionManager.getCurrentUser();
    if (usuarioActual.getTipoUsuario() != TipoUsuario::ESTUDIANTE) {
        // Si no es estudiante, no tiene certificados
        _totalCertificados = 0;
        return;
    }
    
    // USAR EL NOMBRE REAL del usuario logueado
    std::string nombreEstudianteReal = usuarioActual.getNombreCompleto();
    
    // Obtener ContentManager
    ContentManager& contentManager = ContentManager::getInstance();
    
    // Obtener inscripciones del estudiante
    std::vector<InscripcionBinaria> inscripciones = contentManager.obtenerInscripcionesEstudiante(usuarioActual.getId());
    
    // Procesar solo las inscripciones completadas para generar certificados
    int certificadoId = 1;
    for (const auto& inscripcion : inscripciones) {
        if (inscripcion.completado && inscripcion.pagado) {
            Certificado cert(certificadoId, nombreEstudianteReal);
            certificadoId++;
            //cert.getNombreEstudiante() = nombreEstudianteReal; // USAR EL NOMBRE REAL
            
            // Obtener datos del curso o especialización según el tipo
            if (static_cast<TipoActividad>(inscripcion.tipoActividad) == TipoActividad::CURSO) {
                RawCursoData cursoData = contentManager.obtenerCursoDatos(inscripcion.idActividad);
                if (cursoData.id != -1) {
                    cert.insertarDatosCurso(cursoData);
                    /*
                    cert.getNombreCurso() = cursoData.titulo;
                    cert.tipoCurso = "Curso";
                    cert.instructor = cursoData.instructor;
                    cert.categoria = RawActividadData::categoriaToString(cursoData.categoria);
                    cert.getDuracionHoras() = cursoData.cantidadClases * 2; // Estimación de 2 horas por clase
                    cert.getEsEspecializacion = false;
                    */
                }
            } else {
                RawEspecializacionData espData = contentManager.obtenerEspecializacionDatos(inscripcion.idActividad);
                if (espData.id != -1) {
                    cert.insertarDatosEspecializacion(espData);
                    /*
                    cert.getNombreCurso() = espData.titulo;
                    cert.tipoCurso = "Especialización";
                    cert.instructor = "Equipo de " + espData.nombreEmpresa;
                    cert.categoria = RawActividadData::categoriaToString(espData.categoria);
                    cert.getDuracionHoras() = espData.duracionEstimada * 8; // Estimación de 8 horas por semana
                    cert.getEsEspecializacion = true;
                    */
                }
            }
            
            // Generar fechas ficticias pero realistas
            cert.insertarDatosInscripcion(inscripcion);
            /*
            cert.getFechaFinalizacion() = "15/06/2025";
            cert.getFechaEmision() = "16/06/2025";
            
            // Generar calificación aleatoria alta (como certificado completado)
            cert.getCalificacion() = 85.0 + (rand() % 15); // Entre 85 y 100
            
            // Generar ID único del certificado
            std::ostringstream oss;
            oss << "CERT" << std::setfill('0') << std::setw(3) << cert.id 
                << "-" << (cert.getEsEspecializacion ? "ESP" : "CUR") << "-2025";
            cert.idCertificado = oss.str();
            */
            _certificados.push_back(cert);
        }
    }
    
    _totalCertificados = _certificados.size();
    
    // Si no hay certificados reales, usar algunos de ejemplo para demostración
    // PERO con el nombre real del usuario
    if (_totalCertificados == 0) {
        _cargarCertificadosEjemplo();
        // Actualizar el nombre en los certificados de ejemplo
        for (auto& cert : _certificados) {
            cert.setNombre(nombreEstudianteReal);
        }
    }
}

// Cargar certificados de ejemplo
inline void VerCertificadosScreen::_cargarCertificadosEjemplo()
{
    _certificados.clear();
    
    // Obtener nombre real del usuario si hay sesión activa
    std::string nombreEstudiante = "Juan Carlos Perez Rodriguez"; // Nombre por defecto
    if (SessionManager::getInstance().isLoggedIn()) {
        nombreEstudiante = SessionManager::getInstance().getCurrentUser().getNombreCompleto();
    }
    
    _certificados.push_back(Certificado(
        1,
        "Fundamentos de Python para Data Science",
        "Curso",
        nombreEstudiante, // USAR NOMBRE REAL
        "Dr. Ana Maria Rodriguez",
        "15/06/2025",
        "16/06/2025",
        95.5,
        "CERT001-PY-2025",
        40,
        "Programacion",
        false
    ));
    
    _certificados.push_back(Certificado(
        2,
        "Especialización en Machine Learning",
        "Especialización",
        nombreEstudiante, // USAR NOMBRE REAL
        "PhD. Carlos Eduardo Martinez",
        "20/05/2025",
        "21/05/2025",
        88.7,
        "CERT002-ML-2025",
        120,
        "Inteligencia Artificial",
        true
    ));
    
    _certificados.push_back(Certificado(
        3,
        "Desarrollo Web Full Stack con React",
        "Curso",
        nombreEstudiante, // USAR NOMBRE REAL
        "Ing. Sofia Elena Gutierrez",
        "10/04/2025",
        "11/04/2025",
        92.3,
        "CERT003-WEB-2025",
        60,
        "Desarrollo Web",
        false
    ));
    
    _totalCertificados = _certificados.size();
}

// Dibujar interfaz completa
inline void VerCertificadosScreen::dibujarInterfazCompleta()
{
    system("cls");
    UI_Certificados();
    
    _renderizarCertificadoActual();
    _renderizarNavegacion();
    
    resetColor();
}

// Método de limpieza dinámica - Solo limpia las zonas donde hubo texto anterior
inline void VerCertificadosScreen::_limpiarTextoAnterior()
{
    // Limpiar nombre del estudiante anterior
    if (!_nombreEstudianteAnterior.empty()) {
        gotoXY(_coordNombreEstudiante.X, _coordNombreEstudiante.Y);
        std::cout << std::string(_nombreEstudianteAnterior.length(), ' ');
    }
    
    // Limpiar nombre del curso anterior
    if (!_nombreCursoAnterior.empty()) {
        gotoXY(_coordNombreCurso.X, _coordNombreCurso.Y);
        std::cout << std::string(_nombreCursoAnterior.length(), ' ');
    }
    
    // Limpiar instructor anterior
    if (!_instructorAnterior.empty()) {
        gotoXY(_coordInstructor.X, _coordInstructor.Y);
        std::cout << std::string(_instructorAnterior.length(), ' ');
    }
    
    // Limpiar fecha anterior
    if (!_fechaAnterior.empty()) {
        gotoXY(_coordFecha.X, _coordFecha.Y);
        std::cout << std::string(_fechaAnterior.length(), ' ');
    }
    
    // Limpiar ID certificado anterior
    if (!_idCertificadoAnterior.empty()) {
        gotoXY(_coordIdCertificado.X, _coordIdCertificado.Y);
        std::cout << std::string(_idCertificadoAnterior.length(), ' ');
    }
    
    // Limpiar navegación anterior
    if (!_navegacionAnterior.empty()) {
        gotoXY(_coordNavegacion.X, _coordNavegacion.Y);
        std::cout << std::string(_navegacionAnterior.length(), ' ');
    }
}

// Renderizar certificado actual usando coordenadas con limpieza dinámica
inline void VerCertificadosScreen::_renderizarCertificadoActual()
{
    if (_certificados.empty()) {
        gotoXY(40, 15);
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "No tienes certificados disponibles";
        resetColor();
        return;
    }
    
    const auto& cert = _certificados[_certificadoActual];
    
    // PASO 1: Limpiar exactamente las zonas donde hubo texto anterior
    _limpiarTextoAnterior();
    
    // PASO 2: Renderizar nuevo contenido y recordar lo que escribimos
    
    // Nombre del estudiante
    gotoXY(_coordNombreEstudiante.X, _coordNombreEstudiante.Y);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << cert.getNombreEstudiante();
    _nombreEstudianteAnterior = cert.getNombreEstudiante(); // Recordar lo que escribimos
    
    // Nombre del curso
    gotoXY(_coordNombreCurso.X, _coordNombreCurso.Y);
    setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << cert.getNombreCurso();
    _nombreCursoAnterior = cert.getNombreCurso(); // Recordar lo que escribimos
    
    // Instructor con formato completo
    gotoXY(_coordInstructor.X, _coordInstructor.Y);
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::string textoInstructor = "Instructor: " + cert.getInstructor();
    std::cout << textoInstructor;
    _instructorAnterior = textoInstructor; // Recordar lo que escribimos
    
    // Fecha con formato completo
    gotoXY(_coordFecha.X, _coordFecha.Y);
    std::string textoFecha = "Fecha: " + _formatearFecha(cert.getFechaFinalizacion());
    std::cout << textoFecha;
    _fechaAnterior = textoFecha; // Recordar lo que escribimos
    
    // ID Certificado con formato completo
    gotoXY(_coordIdCertificado.X, _coordIdCertificado.Y);
    std::string textoId = "ID Certificado: " + cert.getIdCertificado();
    std::cout << textoId;
    _idCertificadoAnterior = textoId; // Recordar lo que escribimos
    
    resetColor();
}

// Renderizar navegación usando coordenadas con limpieza dinámica
inline void VerCertificadosScreen::_renderizarNavegacion()
{
    // Mostrar navegación solo si hay más de un certificado
    if (_totalCertificados > 1) {
        // Limpiar navegación anterior antes de escribir la nueva
        if (!_navegacionAnterior.empty()) {
            gotoXY(_coordNavegacion.X, _coordNavegacion.Y);
            std::cout << std::string(_navegacionAnterior.length(), ' ');
        }
        
        // Renderizar nueva navegación
        gotoXY(_coordNavegacion.X, _coordNavegacion.Y);
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        std::string textoNavegacion = "< ANTERIOR     [" + std::to_string(_certificadoActual + 1) + "/" + std::to_string(_totalCertificados) + "]     SIGUIENTE >";
        std::cout << textoNavegacion;
        _navegacionAnterior = textoNavegacion; // Recordar lo que escribimos
    } else {
        // Si no hay navegación necesaria, limpiar la anterior si existía
        if (!_navegacionAnterior.empty()) {
            gotoXY(_coordNavegacion.X, _coordNavegacion.Y);
            std::cout << std::string(_navegacionAnterior.length(), ' ');
            _navegacionAnterior.clear();
        }
    }
    
    resetColor();
}

// Navegar al certificado anterior
inline void VerCertificadosScreen::_navegarAnterior()
{
    if (_certificadoActual > 0) {
        _certificadoActual--;
        // Solo renderizar las partes que cambiaron (limpieza dinámica automática)
        _renderizarCertificadoActual();
        _renderizarNavegacion();
    }
}

// Navegar al certificado siguiente
inline void VerCertificadosScreen::_navegarSiguiente()
{
    if (_certificadoActual < _totalCertificados - 1) {
        _certificadoActual++;
        // Solo renderizar las partes que cambiaron (limpieza dinámica automática)
        _renderizarCertificadoActual();
        _renderizarNavegacion();
    }
}

// Formatear fecha
inline std::string VerCertificadosScreen::_formatearFecha(const std::string& fecha)
{
	return fecha; /// @todo podemos personalizar esto más adelante si es necesario
}

// Convertir fecha de DD/MM/YYYY a formato ISO YYYY-MM-DD
inline std::string VerCertificadosScreen::_convertirFechaAISO(const std::string& fechaDDMMYYYY)
{
    if (fechaDDMMYYYY.length() != 10 || fechaDDMMYYYY[2] != '/' || fechaDDMMYYYY[5] != '/') {
        return fechaDDMMYYYY; // Si no está en formato esperado, devolver tal como está
    }
    
    std::string dia = fechaDDMMYYYY.substr(0, 2);
    std::string mes = fechaDDMMYYYY.substr(3, 2);
    std::string año = fechaDDMMYYYY.substr(6, 4);
    
    return año + "-" + mes + "-" + dia;
}

// Formatear calificación para mostrar en QR
inline std::string VerCertificadosScreen::_formatearCalificacion(double calificacion)
{
    std::ostringstream oss;
    
    // Determinar el nivel de calificación
    std::string nivel;
    if (calificacion >= 95.0) {
        nivel = "Excelente";
    } else if (calificacion >= 85.0) {
        nivel = "Muy Bueno";
    } else if (calificacion >= 75.0) {
        nivel = "Bueno";
    } else if (calificacion >= 65.0) {
        nivel = "Satisfactorio";
    } else {
        nivel = "Aprobado";
    }
    
    oss << nivel << " (" << std::fixed << std::setprecision(1) << calificacion << "%)";
    return oss.str();
}

// Formatear duración para mostrar en QR
inline std::string VerCertificadosScreen::_formatearDuracion(int duracionHoras, bool esEspecializacion)
{
    std::ostringstream oss;
    
    if (esEspecializacion) {
        // Para especializaciones, mostrar en semanas si es mucho tiempo
        if (duracionHoras >= 40) {
            int semanas = duracionHoras / 8; // Asumiendo 8 horas por semana
            oss << duracionHoras << " horas (" << semanas << " semanas)";
        } else {
            oss << duracionHoras << " horas académicas";
        }
    } else {
        // Para cursos, mostrar solo las horas
        oss << duracionHoras << " horas académicas";
    }
    
    return oss.str();
}

// Configurar consola específicamente para mostrar QR de certificados
inline void VerCertificadosScreen::_configurarConsolaParaQR()
{
    // Configurar fuente más pequeña para que el QR quepa mejor
    configurarFuente(L"Consolas", 6);  // Fuente pequeña para QR
    
    // Configurar tamaño de ventana grande para QR completo
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = { 300, 120 };  // Ventana grande
    SetConsoleScreenBufferSize(hConsole, bufferSize);
    
    SMALL_RECT windowSize = { 0, 0, 299, 119 };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

// Restaurar configuración normal de consola
inline void VerCertificadosScreen::_restaurarConsolaNormal()
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

// Mostrar QR para el certificado seleccionado
inline void VerCertificadosScreen::_mostrarQRCertificado(const Certificado& certificado)
{
    // Configurar consola para mostrar QR óptimamente
    _configurarConsolaParaQR();
    
    system("cls");
    
    // Coordenadas para layout del QR de certificado
    const COORD coordsTituloQR = {120, 1};             // Centrado en ventana más ancha
    const COORD coordsInfoCertificado = {5, 3};        // Información izquierda
    const COORD coordsQR = {5, 15};                    // QR en la izquierda
    const COORD coordsURL = {150, 3};                  // URL en la derecha
    const COORD coordsJSON = {150, 10};                // JSON en la derecha, más abajo
    const COORD coordsInstrucciones = {120, 110};      // Instrucciones al final
    
    // Título de la pantalla del QR - CENTRADO
    gotoXY(coordsTituloQR.X, coordsTituloQR.Y);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "QR CERTIFICADO AUTOCONTENIDO - VERIFICAR EN WEB";
    
    // ===== SECCIÓN IZQUIERDA: INFORMACIÓN DEL CERTIFICADO =====
    gotoXY(coordsInfoCertificado.X, coordsInfoCertificado.Y);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "=== DATOS DEL CERTIFICADO ===";
    
    gotoXY(coordsInfoCertificado.X, coordsInfoCertificado.Y + 2);
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Certificado ID: " << certificado.getIdCertificado();
    
    gotoXY(coordsInfoCertificado.X, coordsInfoCertificado.Y + 3);
    std::cout << "Estudiante: " << certificado.getNombreEstudiante();
    
    gotoXY(coordsInfoCertificado.X, coordsInfoCertificado.Y + 4);
    std::cout << "Curso: " << certificado.getNombreCurso();
    
    gotoXY(coordsInfoCertificado.X, coordsInfoCertificado.Y + 5);
    std::cout << "Tipo: " << certificado.getTipoCurso();
    
    gotoXY(coordsInfoCertificado.X, coordsInfoCertificado.Y + 6);
    std::cout << "Instructor: " << certificado.getInstructor();
    
    gotoXY(coordsInfoCertificado.X, coordsInfoCertificado.Y + 7);
    std::cout << "Fecha Finalización: " << certificado.getFechaFinalizacion();
    
    gotoXY(coordsInfoCertificado.X, coordsInfoCertificado.Y + 8);
    std::cout << "Fecha Emisión: " << certificado.getFechaEmision();
    
    gotoXY(coordsInfoCertificado.X, coordsInfoCertificado.Y + 9);
    std::cout << "Calificación: " << _formatearCalificacion(certificado.getCalificacion());
    
    gotoXY(coordsInfoCertificado.X, coordsInfoCertificado.Y + 10);
    std::cout << "Duración: " << _formatearDuracion(certificado.getDuracionHoras(), certificado.getEsEspecializacion());
    
    // Convertir tipo de actividad
    TipoActividad tipoActividad = certificado.getEsEspecializacion() ? TipoActividad::ESPECIALIZACION : TipoActividad::CURSO;
    
    // Generar URL con formato ESTÁNDAR para certificados
    std::string urlAutocontenida = CourseraClone::QR::AutocontainedQR::generarURLCertificadoEstandar(
        certificado.getId(),
        certificado.getNombreEstudiante(),
        certificado.getNombreCurso(),
        _convertirFechaAISO(certificado.getFechaFinalizacion()),
        _convertirFechaAISO(certificado.getFechaEmision()),
        _formatearCalificacion(certificado.getCalificacion()),
        _formatearDuracion(certificado.getDuracionHoras(), certificado.getEsEspecializacion()),
        tipoActividad
    );
    
    // Mostrar evaluación del tamaño
    gotoXY(coordsInfoCertificado.X, coordsInfoCertificado.Y + 12);
    setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << CourseraClone::QR::AutocontainedQR::evaluarTamaño(urlAutocontenida);
    
    // ===== SECCIÓN IZQUIERDA ABAJO: CÓDIGO QR =====
    gotoXY(coordsQR.X, coordsQR.Y);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "=== CÓDIGO QR CERTIFICADO ===";
    
    gotoXY(coordsQR.X, coordsQR.Y + 1);
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Escanea para verificar certificado en web:";
    
    try {
        // Usar configuración optimizada automática para el QR
        CourseraClone::QR::QRConfig config = CourseraClone::QR::QRCodeGenerator::configuracionOptima(urlAutocontenida.length());
        
        // Forzar estilo básico para mejor legibilidad en consola
        config.style = CourseraClone::QR::ASCIIStyle::BASIC;
        config.useColors = false;
        config.borderSize = 1;
        
        CourseraClone::QR::QRCodeGenerator generator(config);
        
        // Mostrar análisis del contenido
        gotoXY(coordsQR.X, coordsQR.Y + 2);
        setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "Análisis: URL de " << urlAutocontenida.length() << " caracteres - Optimización automática activa";
        
        std::string qrVisual = generator.generateFromText(urlAutocontenida);
        
        // Mostrar el QR línea por línea
        gotoXY(coordsQR.X, coordsQR.Y + 4);
        size_t pos = 0;
        int lineaActual = 0;
        while (pos < qrVisual.length() && lineaActual < 85) {  // Espacio disponible para QR
            size_t finLinea = qrVisual.find('\n', pos);
            if (finLinea == std::string::npos) {
                finLinea = qrVisual.length();
            }
            
            gotoXY(coordsQR.X, coordsQR.Y + 4 + lineaActual);
            std::cout << qrVisual.substr(pos, finLinea - pos);
            
            pos = finLinea + 1;
            lineaActual++;
        }
    }
    catch (const std::exception& e) {
        gotoXY(coordsQR.X, coordsQR.Y + 4);
        setConsoleColor(ColorIndex::ERROR_COLOR, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "Error generando QR: " << e.what();
    }
    
    // ===== SECCIÓN DERECHA ARRIBA: URL COMPLETA =====
    gotoXY(coordsURL.X, coordsURL.Y);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "=== URL CERTIFICADO AUTOCONTENIDA ===";
    
    gotoXY(coordsURL.X, coordsURL.Y + 1);
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Esta URL contiene TODOS los datos del certificado:";
    
    // Mostrar URL línea por línea
    std::string urlFormateada = urlAutocontenida;
    size_t maxLineLength = 140;
    size_t pos = 0;
    int lineNumber = 0;
    
    while (pos < urlFormateada.length() && lineNumber < 25) {
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
    std::cout << "=== DATOS JSON DEL CERTIFICADO ===";
    
    gotoXY(coordsJSON.X, coordsJSON.Y + 1);
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Datos que recibe la página web:";
    
    // Generar el JSON ESTÁNDAR para mostrar
    std::string jsonDatos = CourseraClone::QR::AutocontainedQR::generarQRCertificadoEstandar(
        certificado.getId(),
        certificado.getNombreEstudiante(),
        certificado.getNombreCurso(),
        _convertirFechaAISO(certificado.getFechaFinalizacion()),
        _convertirFechaAISO(certificado.getFechaEmision()),
        _formatearCalificacion(certificado.getCalificacion()),
        _formatearDuracion(certificado.getDuracionHoras(), certificado.getEsEspecializacion()),
        tipoActividad
    );
    
    // Mostrar JSON formateado
    size_t jsonPos = 0;
    int jsonLineNumber = 0;
    
    while (jsonPos < jsonDatos.length() && jsonLineNumber < 20) {
        size_t jsonEndPos = jsonPos + 120;
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
    std::cout << "▶ Formato JSON estándar para certificados (t=c)";
    
    gotoXY(coordsInstrucciones.X, coordsInstrucciones.Y + 1);
    std::cout << "▶ Campos: t, i, s, c, cd, id, g, dur, ct (verificables en web)";
    
    gotoXY(coordsInstrucciones.X, coordsInstrucciones.Y + 2);
    std::cout << "▶ Certificado completamente verificable con datos reales";
    
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

// Método principal de ejecución
inline ResultadoPantalla VerCertificadosScreen::ejecutar()
{
    _limpiarEstado();
    
    while (true) {
        if (_primeraRenderizacion) {
            dibujarInterfazCompleta();
            _primeraRenderizacion = false;
        }
        
        int tecla = _getch();
        
        switch (tecla) {
        case 0:
        case 224: // Teclas especiales
        {
            int segundaTecla = _getch();
            switch (segundaTecla) {
            case 75: // Flecha izquierda - Anterior
                _navegarAnterior();
                break;
            case 77: // Flecha derecha - Siguiente
                _navegarSiguiente();
                break;
            }
        }
        break;
        
        case 75: // Flecha izquierda (por si acaso)
            _navegarAnterior();
            break;
            
        case 77: // Flecha derecha (por si acaso)
            _navegarSiguiente();
            break;

        case 'd':
        case 'D': // D - Generar QR del certificado
            if (!_certificados.empty()) {
                const auto& certificadoActual = _certificados[_certificadoActual];
                _mostrarQRCertificado(certificadoActual);
                
                // Después de mostrar el QR, redibujar la interfaz completa
                _primeraRenderizacion = true;
            } else {
                // Mostrar mensaje si no hay certificados
                gotoXY(40, 28);
                setConsoleColor(ColorIndex::ERROR_COLOR, ColorIndex::FONDO_PRINCIPAL);
                std::cout << "No hay certificados para generar QR";
                resetColor();
                _getch(); // Pausa para mostrar mensaje
                
                // Limpiar mensaje
                gotoXY(40, 28);
                std::cout << "                                   ";
            }
            break;
            
        case 27: // ESC - Volver a pantalla anterior
            return ResultadoPantalla{_pantallaAnterior};
            
        default:
            // Ignorar otras teclas
            break;
        }
    }
}

#endif // COURSERACLONE_SCREENS_VERCERTIFICADOSSCREEN_HPP
