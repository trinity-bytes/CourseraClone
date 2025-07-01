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
    
    // Constantes para la interfaz
    static const int COL_CERTIFICADO = 10;
    static const int FILA_CERTIFICADO = 9;
    static const int ANCHO_CERTIFICADO = 95;
    static const int ALTO_CERTIFICADO = 15;
    
    static const int COL_NAVEGACION = 30;
    static const int FILA_NAVEGACION = 27;
    
    static const int COL_BOTONES = 45;
    static const int FILA_BOTONES = 27;
    
    // ---- MÉTODOS PRIVADOS ----
    
    /// @brief Métodos de inicialización
    inline void _limpiarEstado();
    inline void _cargarCertificadosEjemplo();
    
    /// @brief Métodos de renderizado
    inline void dibujarInterfazCompleta();
    inline void _renderizarCertificadoActual();
    inline void _renderizarNavegacion();
    inline void _renderizarBotones();
    inline void _renderizarInstrucciones();
    inline void _mostrarDetallesCertificado();
    
    /// @brief Métodos de navegación
    inline void _navegarAnterior();
    inline void _navegarSiguiente();
    inline void _simularDescargarPDF();
    
    /// @brief Métodos de utilidad
    inline std::string _formatearFecha(const std::string& fecha);
    inline std::string _formatearCalificacion(double calificacion);

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
    _cargarCertificadosEjemplo();
}

// Limpiar estado
inline void VerCertificadosScreen::_limpiarEstado()
{
    _certificadoActual = 0;
    _primeraRenderizacion = true;
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
    
    _certificados.push_back({
        4,
        "Bases de Datos Avanzadas con PostgreSQL",
        "Curso",
        "Juan Carlos Perez Rodriguez",
        "MSc. Roberto Luis Fernandez",
        "25/03/2025",
        "26/03/2025",
        89.1,
        "CERT004-DB-2025",
        35,
        "Bases de Datos",
        false
    });
    
    _certificados.push_back({
        5,
        "Especialización en Ciberseguridad",
        "Especialización",
        "Juan Carlos Perez Rodriguez",
        "Dr. Patricia Isabel Morales",
        "15/02/2025",
        "16/02/2025",
        94.8,
        "CERT005-SEC-2025",
        150,
        "Seguridad Informatica",
        true
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
    _renderizarBotones();
    _renderizarInstrucciones();
    
    resetColor();
}

// Renderizar certificado actual
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
    
    // Limpiar área del certificado primero
    setConsoleColor(ColorIndex::FONDO_PRINCIPAL, ColorIndex::FONDO_PRINCIPAL);
    for (int y = 11; y < 23; y++) {
        for (int x = 15; x < 100; x++) {
            gotoXY(x, y);
            std::cout << " ";
        }
    }
    
    // Título del certificado
    gotoXY(45, 11);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "CERTIFICADO DE FINALIZACION";
    
    // Logo/Marca
    gotoXY(20, 13);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "COURSERA CLONE";
    
    // Texto principal
    gotoXY(20, 15);
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Por la presente certifica que:";
    
    // Nombre del estudiante
    gotoXY(40, 17);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << cert.nombreEstudiante;
    
    // Texto de completación
    gotoXY(20, 19);
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Ha completado satisfactoriamente el " << cert.tipoCurso << ":";
    
    // Nombre del curso
    gotoXY(35, 21);
    setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << cert.nombreCurso;
    
    // Información adicional
    gotoXY(20, 23);
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Instructor: " << cert.instructor;
    
    gotoXY(55, 23);
    std::cout << "Fecha: " << _formatearFecha(cert.fechaFinalizacion);
    
    gotoXY(20, 24);
    std::cout << "Calificacion: " << _formatearCalificacion(cert.calificacion);
    
    gotoXY(55, 24);
    std::cout << "ID Certificado: " << cert.idCertificado;
    
    resetColor();
}

// Renderizar navegación
inline void VerCertificadosScreen::_renderizarNavegacion()
{
    if (_totalCertificados <= 1) return;
    
    gotoXY(COL_NAVEGACION, FILA_NAVEGACION);
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "< ANTERIOR     [" << (_certificadoActual + 1) << "/" << _totalCertificados << "]     SIGUIENTE >";
    resetColor();
}

// Renderizar botones
inline void VerCertificadosScreen::_renderizarBotones()
{
    gotoXY(COL_BOTONES, FILA_BOTONES);
    setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
    std::cout << " VER DETALLES ";
    
    gotoXY(COL_BOTONES + 18, FILA_BOTONES);
    setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::EXITO_COLOR);
    std::cout << " DESCARGAR PDF ";
    
    resetColor();
}

// Renderizar instrucciones
inline void VerCertificadosScreen::_renderizarInstrucciones()
{
    gotoXY(15, 35);
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Navegacion: ";
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "[FLECHAS IZQUIERDA/DERECHA] ";
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "| Ver detalles: ";
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "[ENTER] ";
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "| Descargar: ";
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "[D] ";
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "| Volver: ";
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "[ESC]";
    resetColor();
}

// Mostrar detalles del certificado
inline void VerCertificadosScreen::_mostrarDetallesCertificado()
{
    if (_certificados.empty()) return;
    
    const auto& cert = _certificados[_certificadoActual];
    
    system("cls");
    
    gotoXY(35, 8);
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "DETALLES DEL CERTIFICADO";
    
    gotoXY(20, 11);
    setConsoleColor(ColorIndex::TEXTO_PRIMARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "ID del Certificado: " << cert.idCertificado;
    
    gotoXY(20, 12);
    std::cout << "Tipo de Contenido: " << cert.tipoCurso;
    
    gotoXY(20, 13);
    std::cout << "Nombre: " << cert.nombreCurso;
    
    gotoXY(20, 14);
    std::cout << "Categoria: " << cert.categoria;
    
    gotoXY(20, 15);
    std::cout << "Estudiante: " << cert.nombreEstudiante;
    
    gotoXY(20, 16);
    std::cout << "Instructor: " << cert.instructor;
    
    gotoXY(20, 17);
    std::cout << "Duracion: " << cert.duracionHoras << " horas academicas";
    
    gotoXY(20, 18);
    std::cout << "Fecha de Finalizacion: " << _formatearFecha(cert.fechaFinalizacion);
    
    gotoXY(20, 19);
    std::cout << "Fecha de Emision: " << _formatearFecha(cert.fechaEmision);
    
    gotoXY(20, 20);
    setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Calificacion Final: " << _formatearCalificacion(cert.calificacion);
    
    if (cert.esEspecializacion) {
        gotoXY(20, 22);
        setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "ESPECIALIZACION COMPLETADA - Credito Academico Valido";
    }
    
    gotoXY(30, 25);
    setConsoleColor(ColorIndex::BLANCO_PURO, ColorIndex::AZUL_MARCA);
    std::cout << " Presiona cualquier tecla para volver ";
    resetColor();
    
    _getch();
    _primeraRenderizacion = true;
}

// Navegar al certificado anterior
inline void VerCertificadosScreen::_navegarAnterior()
{
    if (_certificadoActual > 0) {
        _certificadoActual--;
        _renderizarCertificadoActual();
        _renderizarNavegacion();
    }
}

// Navegar al certificado siguiente
inline void VerCertificadosScreen::_navegarSiguiente()
{
    if (_certificadoActual < _totalCertificados - 1) {
        _certificadoActual++;
        _renderizarCertificadoActual();
        _renderizarNavegacion();
    }
}

// Simular descarga de PDF
inline void VerCertificadosScreen::_simularDescargarPDF()
{
    if (_certificados.empty()) return;
    
    const auto& cert = _certificados[_certificadoActual];
    
    gotoXY(20, 30);
    setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Descargando certificado " << cert.idCertificado << ".pdf...";
    resetColor();
    
    // Simular progreso de descarga
    for (int i = 0; i <= 10; i++) {
        gotoXY(20, 31);
        setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_PRINCIPAL);
        std::cout << "Progreso: [";
        for (int j = 0; j < i; j++) {
            std::cout << "=";
        }
        for (int j = i; j < 10; j++) {
            std::cout << " ";
        }
        std::cout << "] " << (i * 10) << "%";
        resetColor();
        Sleep(200);
    }
    
    gotoXY(20, 32);
    setConsoleColor(ColorIndex::EXITO_COLOR, ColorIndex::FONDO_PRINCIPAL);
    std::cout << "Descarga completada! Archivo guardado en Descargas/";
    resetColor();
    
    Sleep(2000);
    _primeraRenderizacion = true;
}

// Formatear fecha
inline std::string VerCertificadosScreen::_formatearFecha(const std::string& fecha)
{
    return fecha; // En una implementación real, se podría formatear la fecha
}

// Formatear calificación
inline std::string VerCertificadosScreen::_formatearCalificacion(double calificacion)
{
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << calificacion << "/100";
    return oss.str();
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
            
        case 13: // Enter - Ver detalles
            _mostrarDetallesCertificado();
            break;
            
        case 'd':
        case 'D': // D - Descargar PDF
            _simularDescargarPDF();
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
