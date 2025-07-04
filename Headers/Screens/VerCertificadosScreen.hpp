#ifndef COURSERACLONE_SCREENS_VERCERTIFICADOSSCREEN_HPP
#define COURSERACLONE_SCREENS_VERCERTIFICADOSSCREEN_HPP

// Headers estándar
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <conio.h>
#include <limits>

// Headers propios
#include "../Utils/SystemUtils.hpp"
#include "../Utils/ScreenSystem.hpp"
#include "../Utils/UI_Ascii.hpp"
#include "../Utils/InputUtils.hpp"
#include "../Utils/ValidationUtils.hpp"
#include "../Controllers/ContentManager.hpp"
#include "../Controllers/SessionManager.hpp"
#include "../Types/UsuarioTypes.hpp"

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
    struct Certificado {
        int id;
        std::string nombreCurso;
        std::string tipoCurso; // "Curso" o "Especialización"
        std::string nombreEstudiante;
        std::string instructor;
        std::string fechaFinalizacion;
        std::string fechaEmision;
        double calificacion;
        std::string idCertificado;
        int duracionHoras;
        std::string categoria;
        bool esEspecializacion;
    };
    
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
    
    /// @brief Métodos de utilidad
    inline std::string _formatearFecha(const std::string& fecha);

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
    
    // Obtener datos del usuario actual
    Usuario usuarioActual = sessionManager.getCurrentUser();
    if (usuarioActual.getTipoUsuario() != TipoUsuario::ESTUDIANTE) {
        // Si no es estudiante, no tiene certificados
        _totalCertificados = 0;
        return;
    }
    
    // Obtener ContentManager
    ContentManager& contentManager = ContentManager::getInstance();
    
    // Obtener inscripciones del estudiante
    std::vector<InscripcionBinaria> inscripciones = contentManager.obtenerInscripcionesEstudiante(usuarioActual.getId());
    
    // Procesar solo las inscripciones completadas para generar certificados
    int certificadoId = 1;
    for (const auto& inscripcion : inscripciones) {
        if (inscripcion.completado) {
            Certificado cert;
            cert.id = certificadoId++;
            cert.nombreEstudiante = usuarioActual.getNombreCompleto();
            
            // Obtener datos del curso o especialización según el tipo
            if (static_cast<TipoActividad>(inscripcion.tipoActividad) == TipoActividad::CURSO) {
                RawCursoData cursoData = contentManager.obtenerCursoDatos(inscripcion.idActividad);
                if (cursoData.id != -1) {
                    cert.nombreCurso = cursoData.titulo;
                    cert.tipoCurso = "Curso";
                    cert.instructor = cursoData.instructor;
                    cert.categoria = RawActividadData::categoriaToString(cursoData.categoria);
                    cert.duracionHoras = cursoData.cantidadClases * 2; // Estimación de 2 horas por clase
                    cert.esEspecializacion = false;
                }
            } else {
                RawEspecializacionData espData = contentManager.obtenerEspecializacionDatos(inscripcion.idActividad);
                if (espData.id != -1) {
                    cert.nombreCurso = espData.titulo;
                    cert.tipoCurso = "Especialización";
                    cert.instructor = "Equipo de " + espData.nombreEmpresa;
                    cert.categoria = RawActividadData::categoriaToString(espData.categoria);
                    cert.duracionHoras = espData.duracionEstimada * 8; // Estimación de 8 horas por semana
                    cert.esEspecializacion = true;
                }
            }
            
            // Generar fechas ficticias pero realistas
            cert.fechaFinalizacion = "15/06/2025";
            cert.fechaEmision = "16/06/2025";
            
            // Generar calificación aleatoria alta (como certificado completado)
            cert.calificacion = 85.0 + (rand() % 15); // Entre 85 y 100
            
            // Generar ID único del certificado
            std::ostringstream oss;
            oss << "CERT" << std::setfill('0') << std::setw(3) << cert.id 
                << "-" << (cert.esEspecializacion ? "ESP" : "CUR") << "-2025";
            cert.idCertificado = oss.str();
            
            _certificados.push_back(cert);
        }
    }
    
    _totalCertificados = _certificados.size();
    
    // Si no hay certificados reales, usar algunos de ejemplo para demostración
    if (_totalCertificados == 0) {
        _cargarCertificadosEjemplo();
    }
}

// Cargar certificados de ejemplo
inline void VerCertificadosScreen::_cargarCertificadosEjemplo()
{
    _certificados.clear();
    
    _certificados.push_back({
        1,
        "Fundamentos de Python para Data Science",
        "Curso",
        "Juan Carlos Perez Rodriguez",
        "Dr. Ana Maria Rodriguez",
        "15/06/2025",
        "16/06/2025",
        95.5,
        "CERT001-PY-2025",
        40,
        "Programacion",
        false
    });
    
    _certificados.push_back({
        2,
        "Especialización en Machine Learning",
        "Especialización",
        "Juan Carlos Perez Rodriguez",
        "PhD. Carlos Eduardo Martinez",
        "20/05/2025",
        "21/05/2025",
        88.7,
        "CERT002-ML-2025",
        120,
        "Inteligencia Artificial",
        true
    });
    
    _certificados.push_back({
        3,
        "Desarrollo Web Full Stack con React",
        "Curso",
        "Juan Carlos Perez Rodriguez",
        "Ing. Sofia Elena Gutierrez",
        "10/04/2025",
        "11/04/2025",
        92.3,
        "CERT003-WEB-2025",
        60,
        "Desarrollo Web",
        false
    });
    
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
    std::cout << cert.nombreEstudiante;
    _nombreEstudianteAnterior = cert.nombreEstudiante; // Recordar lo que escribimos
    
    // Nombre del curso
    gotoXY(_coordNombreCurso.X, _coordNombreCurso.Y);
    setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << cert.nombreCurso;
    _nombreCursoAnterior = cert.nombreCurso; // Recordar lo que escribimos
    
    // Instructor con formato completo
    gotoXY(_coordInstructor.X, _coordInstructor.Y);
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::string textoInstructor = "Instructor: " + cert.instructor;
    std::cout << textoInstructor;
    _instructorAnterior = textoInstructor; // Recordar lo que escribimos
    
    // Fecha con formato completo
    gotoXY(_coordFecha.X, _coordFecha.Y);
    std::string textoFecha = "Fecha: " + _formatearFecha(cert.fechaFinalizacion);
    std::cout << textoFecha;
    _fechaAnterior = textoFecha; // Recordar lo que escribimos
    
    // ID Certificado con formato completo
    gotoXY(_coordIdCertificado.X, _coordIdCertificado.Y);
    std::string textoId = "ID Certificado: " + cert.idCertificado;
    std::cout << textoId;
    _idCertificadoAnterior = textoId; // Recordar lo que escribimos
    
    resetColor();
}

// Renderizar navegación usando coordenadas con limpieza dinámica
inline void VerCertificadosScreen::_renderizarNavegacion()
{
    if (_totalCertificados <= 1) {
        // Si no hay navegación necesaria, limpiar la anterior si existía
        if (!_navegacionAnterior.empty()) {
            gotoXY(_coordNavegacion.X, _coordNavegacion.Y);
            std::cout << std::string(_navegacionAnterior.length(), ' ');
            _navegacionAnterior.clear();
        }
        return;
    }
    
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
        case 'D': // D - Descargar PDF
			/// @todo logica para enviar data a la web para que genere los certificados en PDF
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
