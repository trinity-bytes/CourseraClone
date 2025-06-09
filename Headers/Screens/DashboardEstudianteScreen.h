// filepath: Headers/Screens/DashboardEstudiante_Screen.h
// Pantalla principal del estudiante con navegación por secciones

#pragma once

// Headers de librería estándar
#include <vector>
#include <string>
#include <fstream>    // Para std::ifstream
#include <sstream>    // Para std::stringstream
#include <windows.h>  // Para COORD y funciones de consola y que std::min funcione bien
#include <algorithm>  // Para std::min

// Headers propios
#include "../Utils/ScreenSystem.h"
#include "../Utils/SystemUtils.h"
#include "../Utils/UI_Ascii.h"
#include "../Entities/Inscripcion.h"
#include "../Entities/Curso.h"
#include "../Entities/Especializacion.h"
#include "../Controllers/GestionadorCursos.h"

// forward declarations
class Controladora; // Declaración adelantada de Controladora

// Pantalla principal del dashboard del estudiante
class DashboardEstudianteScreen : public PantallaBase
{
private:
    // Constantes de configuración de secciones
    static const int SECCION_HEADER = 0;
    static const int SECCION_MENU_SUPERIOR = 1;
    static const int SECCION_CURSOS = 2;
    static const int SECCION_ESPECIALIZACIONES = 3;
    static const int TOTAL_SECCIONES = 4;

    // Constantes de elementos por sección
    static const int MAX_ELEMENTOS_HEADER = 2;
    static const int MAX_ELEMENTOS_MENU = 1;
    static const int MAX_ELEMENTOS_CURSOS = 4;
    static const int MAX_ELEMENTOS_ESPECIALIZACIONES = 4;    // Ruta de archivos de datos
    static const std::string RUTA_INSCRIPCIONES;

    // Datos del usuario logueado
    std::string _nombreEstudiante;
    int _idEstudiante;

    // Estado de navegación
    int _seccionActual;
    int _elementoActual;
    int _seccionAnterior;
    int _elementoAnterior;
    bool _primeraRenderizacion;

    // Índices de visualización
    int _indCursoVisible;
    int _indEspVisible;

    // Coordenadas de interfaz
    COORD _coordsElementosHeader[MAX_ELEMENTOS_HEADER];
    COORD _coordsElementosMenu[MAX_ELEMENTOS_MENU];
    COORD _coordsTituloCursos[MAX_ELEMENTOS_CURSOS];
    COORD _coordsTituloEspecializaciones[MAX_ELEMENTOS_ESPECIALIZACIONES];    // Datos cargados
    std::vector<ElementoMenu> _cursosInscritos;
    std::vector<ElementoMenu> _especializacionesInscritas;

    // Métodos de inicialización
    void inicializarCoordenadas();
    void cargarDatos(GestionadorCursos& _gestion);
    void cargarInscripciones(GestionadorCursos& _gestion);

    // Métodos de renderizado
    void dibujarInterfazCompleta();
    void renderizarHeader();
    void renderizarMenuSuperior();    void renderizarCursos();
    void renderizarEspecializaciones();
    void actualizarSeleccion();
    
    // Métodos de utilidad
    int obtenerMaxElementosEnSeccion(int _seccion);
    ResultadoPantalla procesarSeleccion();

public:
    DashboardEstudianteScreen(Controladora* _controladora, int _idEstudiante, const std::string& _nombreEstudiante);
    ResultadoPantalla ejecutar() override;
};

// Definición de constante estática fuera de la clase
const std::string DashboardEstudianteScreen::RUTA_INSCRIPCIONES = "Resources/Data/inscripciones.dat";

// Implementación de métodos

void DashboardEstudianteScreen::inicializarCoordenadas()
{
    _coordsElementosHeader[0] = {84, 3};
    _coordsElementosHeader[1] = {99, 3};
    
    _coordsElementosMenu[0] = {9, 10};
    
    _coordsTituloCursos[0] = {11, 15};
    _coordsTituloCursos[1] = {42, 15};
    _coordsTituloCursos[2] = {73, 15};
    _coordsTituloCursos[3] = {101, 17};
    
    _coordsTituloEspecializaciones[0] = {11, 25};
    _coordsTituloEspecializaciones[1] = {42, 25};
    _coordsTituloEspecializaciones[2] = {73, 25};
    _coordsTituloEspecializaciones[3] = {101, 27};
}

void DashboardEstudianteScreen::cargarDatos(GestionadorCursos& _gestion)
{
    cargarInscripciones(_gestion);

    // Mostrar mensajes por defecto si no hay inscripciones
    if (_cursosInscritos.empty()) {
        for (int i = 0; i < 3; i++) {
            _cursosInscritos.emplace_back("No inscrito", "Aqui apareceran los cursos en los que te has inscrito");
        }
    }

    if (_especializacionesInscritas.empty()) {
                for (int i = 0; i < 3; i++) {
            _especializacionesInscritas.emplace_back("No inscrito", "Aqui apareceran las especialidades en las que te has inscrito");
        }
    }
}

void DashboardEstudianteScreen::cargarInscripciones(GestionadorCursos& _gestion)
{
    std::ifstream archivo(RUTA_INSCRIPCIONES, std::ios::binary);
    if (!archivo.is_open()) {
        throw std::runtime_error("Error: No se pudo abrir el archivo de inscripciones");
    }
    
    // Leer todas las inscripciones del archivo
    InscripcionBinaria inscripcion;
    while (archivo.read(reinterpret_cast<char*>(&inscripcion), sizeof(InscripcionBinaria))) {
        // Filtrar solo las inscripciones del estudiante actual
        if (inscripcion.idEstudiante == _idEstudiante) {
            if (inscripcion.tipoActividad == 1) { // Es un curso
                Curso* curso = _gestion.obtenerCurso(inscripcion.idActividad);
                if (curso) {
                    _cursosInscritos.emplace_back(curso->getTitulo(), curso->getDescripcion());
                }
            }
            else if (inscripcion.tipoActividad == 2) { // Es una especialización
                Especializacion* especializacion = _gestion.obtenerEspecializacion(inscripcion.idActividad);
                if (especializacion) {
                    _especializacionesInscritas.emplace_back(especializacion->getTitulo(), especializacion->getDescripcion());
                }
            }
        }
    }
    archivo.close();
}

void DashboardEstudianteScreen::dibujarInterfazCompleta()
{
    setConsoleColor(15, 0);
    system("cls");
    UI_StudentDashboard();
    renderizarHeader();
    renderizarMenuSuperior();
    renderizarCursos();
    renderizarEspecializaciones();
}

void DashboardEstudianteScreen::renderizarHeader()
{    // Mostrar nombre del estudiante
    gotoXY(52, 3);
    setConsoleColor(15, 1);
    std::cout << _nombreEstudiante;
    setConsoleColor(15, 0);

    // Renderizar botones del header
    for (int i = 0; i < MAX_ELEMENTOS_HEADER; ++i) {
        gotoXY(_coordsElementosHeader[i].X, _coordsElementosHeader[i].Y);
        if (_seccionActual == SECCION_HEADER && _elementoActual == i) {
            setConsoleColor(1, 13);
        }
        else {
            setConsoleColor(15, 0);        }
        std::cout << (i == 0 ? " VER MI PERFIL " : " CERRAR SESION ");
    }
    setConsoleColor(15, 0);
}

void DashboardEstudianteScreen::renderizarMenuSuperior()
{
    for (int i = 0; i < MAX_ELEMENTOS_MENU; ++i) {
        gotoXY(_coordsElementosMenu[i].X, _coordsElementosMenu[i].Y);
        if (_seccionActual == SECCION_MENU_SUPERIOR && _elementoActual == i) {
            setConsoleColor(1, 13);
        }
        else {
            setConsoleColor(15, 0);        }
        std::cout << (i == 0 ? " EXPLORAR CURSOS Y ESPECIALIDADES " : " GESTIONAR MIS INSCRIPCIONES ");
    }
    setConsoleColor(15, 0);
}

void DashboardEstudianteScreen::renderizarCursos()
{
    // Renderizar hasta 3 cursos inscritos
    int numCursos = (std::min)(3, static_cast<int>(_cursosInscritos.size()));

    for (int i = 0; i < numCursos; ++i) {
        gotoXY(_coordsTituloCursos[i].X, _coordsTituloCursos[i].Y);
        if (_seccionActual == SECCION_CURSOS && _elementoActual == i) {
            setConsoleColor(1, 13);
        }
        else {
            setConsoleColor(15, 0);
        }
        std::cout << _cursosInscritos[i].titulo;
    }

    // Botón "Ver todos"
    gotoXY(_coordsTituloCursos[3].X, _coordsTituloCursos[3].Y);
    if (_seccionActual == SECCION_CURSOS && _elementoActual == 3) {
        setConsoleColor(1, 13);
    }    else {
        setConsoleColor(15, 0);
    }
    std::cout << " Ver todos ";
    setConsoleColor(15, 0);
}

void DashboardEstudianteScreen::renderizarEspecializaciones()
{
    // Renderizar hasta 3 especializaciones inscritas
    int numEspecializaciones = (std::min)(3, static_cast<int>(_especializacionesInscritas.size()));

    for (int i = 0; i < numEspecializaciones; ++i) 
    {
        gotoXY(_coordsTituloEspecializaciones[i].X, _coordsTituloEspecializaciones[i].Y);
        if (_seccionActual == SECCION_ESPECIALIZACIONES && _elementoActual == i) {
            setConsoleColor(1, 13);
        }
        else {
            setConsoleColor(15, 13);
        }
        std::cout << _especializacionesInscritas[i].titulo;
    }

    // Botón "Ver todas"
    gotoXY(_coordsTituloEspecializaciones[3].X, _coordsTituloEspecializaciones[3].Y);
    if (_seccionActual == SECCION_ESPECIALIZACIONES && _elementoActual == 3) {
        setConsoleColor(1, 13);
    }    else {
        setConsoleColor(15, 13);
    }
    std::cout << " Ver todas ";
    setConsoleColor(15, 0);
}

void DashboardEstudianteScreen::actualizarSeleccion()
{
    if (_seccionActual != _seccionAnterior || _elementoActual != _elementoAnterior) {
        // Re-renderizar sección anterior para quitar selección
        switch (_seccionAnterior) {
        case SECCION_HEADER:
            renderizarHeader();
            break;
        case SECCION_MENU_SUPERIOR:
            renderizarMenuSuperior();
            break;
        case SECCION_CURSOS:
            renderizarCursos();
            break;
        case SECCION_ESPECIALIZACIONES:
            renderizarEspecializaciones();
            break;
        }

        // Re-renderizar sección actual para mostrar nueva selección
        switch (_seccionActual) {
        case SECCION_HEADER:
            renderizarHeader();
            break;
        case SECCION_MENU_SUPERIOR:
            renderizarMenuSuperior();
            break;
        case SECCION_CURSOS:
            renderizarCursos();
            break;
        case SECCION_ESPECIALIZACIONES:
            renderizarEspecializaciones();
            break;
        }

        _seccionAnterior = _seccionActual;
        _elementoAnterior = _elementoActual;
    }
}

int DashboardEstudianteScreen::obtenerMaxElementosEnSeccion(int _seccion)
{
    switch (_seccion) {
    case SECCION_HEADER: 
        return MAX_ELEMENTOS_HEADER;
    case SECCION_MENU_SUPERIOR: 
        return MAX_ELEMENTOS_MENU;
    case SECCION_CURSOS: 
        return MAX_ELEMENTOS_CURSOS;
    case SECCION_ESPECIALIZACIONES: 
        return MAX_ELEMENTOS_ESPECIALIZACIONES;
    default: 
        return 0;
    }
}

DashboardEstudianteScreen::DashboardEstudianteScreen(Controladora* _controladora, int _idEstudiante, const std::string& _nombreEstudiante)
    : PantallaBase(_controladora), _seccionActual(SECCION_HEADER), _elementoActual(0),
      _seccionAnterior(-1), _elementoAnterior(-1),
      _primeraRenderizacion(true), _idEstudiante(_idEstudiante),
      _nombreEstudiante(_nombreEstudiante), _indCursoVisible(0), _indEspVisible(0)
{    inicializarCoordenadas();
    // Cargar datos usando el GestionadorCursos de la controladora
    if (_controladora) {
        cargarDatos(_controladora->getGestionadorCursos());
    }
}

ResultadoPantalla DashboardEstudianteScreen::ejecutar()
{
    while (true) {
        if (_primeraRenderizacion) {
            dibujarInterfazCompleta();
            _primeraRenderizacion = false;
        }
        else {
            actualizarSeleccion();
        }

        int tecla = _getch();
        switch (tecla) {
        case 224: // Teclas de dirección
            tecla = _getch();
            switch (tecla) {
            case 72: // Flecha arriba
                if (_seccionActual > SECCION_HEADER) {
                    _seccionActual--;
                    _elementoActual = 0;
                }
                break;
            case 80: // Flecha abajo
                if (_seccionActual < TOTAL_SECCIONES - 1) {
                    _seccionActual++;
                    _elementoActual = 0;
                }
                break;
            case 75: // Flecha izquierda
                if (_elementoActual > 0) {
                    _elementoActual--;
                }
                break;
            case 77: // Flecha derecha
                if (_elementoActual < obtenerMaxElementosEnSeccion(_seccionActual) - 1) {
                    _elementoActual++;
                }
                break;
            }
            break;
        
        case 13: // Enter - Procesar selección
            return procesarSeleccion();
              case 27: // ESC - Volver al landing page
            return crearResultado(AccionPantalla::IR_A_LANDING_PAGE);
        }
    }
}

ResultadoPantalla DashboardEstudianteScreen::procesarSeleccion()
{
    if (_seccionActual == SECCION_HEADER) {
        if (_elementoActual == 0) {
            return crearResultado(AccionPantalla::IR_A_PERFIL_ESTUDIANTE);
        }
        else if (_elementoActual == 1) {
            return crearResultado(AccionPantalla::IR_A_LANDING_PAGE);
        }
    }
    else if (_seccionActual == SECCION_MENU_SUPERIOR) {
        if (_elementoActual == 0) {
            ResultadoPantalla res = crearResultado(AccionPantalla::IR_A_EXPLORAR_CURSOS_Y_ESPECIALIDADES);
            res.tipoUsuario = TipoUsuario::ESTUDIANTE;
            res.idUsuarioActual = _idEstudiante;
            res.sesionActiva = true;
            return res;
        }
    }
    
    // Si no hay acción específica, no hacer nada
    return crearResultado(AccionPantalla::NINGUNA);
}