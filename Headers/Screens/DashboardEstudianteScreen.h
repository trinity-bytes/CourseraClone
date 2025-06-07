// filepath: Headers/Screens/StudentDashboardScreen.h
// Descripción: Define la pantalla del dashboard para estudiantes.
//              Permite al estudiante navegar por su perfil, explorar cursos/especializaciones
//              e interactuar con sus inscripciones.
// Autor: [Nombre del desarrollador]
// Fecha: [Fecha de creación]
// Última modificación: [Fecha y descripción del cambio]

#pragma once

// Headers propios - Refactorizados según la guía de estilo
#include "../Screens/ScreenBase.h"          // Renombrado PantallaBase a ScreenBase
#include "../Entities/ScreenResult.h"       // Incluido ScreenResult.h (anteriormente PantallaResultado.h)
#include "../Utils/ConsoleUtils.h"          // Renombrado ExtendedFunctions.h a ConsoleUtils.h
#include "../Utils/AppConstants.h"          // Renombrado Utils.h a AppConstants.h
#include "../Utils/AsciiUI.h"               // Asumiendo UI_Ascii.h será AsciiUI.h
#include "../Entities/Enrollment.h"         // Renombrado Inscripcion.h a Enrollment.h
#include "../Entities/Course.h"             // Renombrado Curso.h a Course.h
#include "../Entities/Specialization.h"     // Renombrado Especializacion.h a Specialization.h
#include "../Controllers/CourseManager.h"   // Renombrado GestionadorCursos.h a CourseManager.h

// Headers de la librería estándar
#include <vector>     // Para std::vector
#include <string>     // Para std::string
#include <fstream>    // Para std::ifstream
#include <sstream>    // Para std::stringstream
#include <algorithm>  // Para std::min
#include <stdexcept>  // Para std::runtime_error
#include <windows.h>  // Para COORD // COORD no es de AppConstants, viene de windows.h

// No usar 'using namespace std;' en archivos de cabecera.

/**
 * @brief Implementa la pantalla del dashboard para un estudiante.
 * Permite al estudiante ver sus cursos y especializaciones inscritas,
 * así como navegar a otras secciones de la aplicación.
 */
class StudentDashboardScreen : public ScreenBase { // Renombrado DashboardEstudiante a StudentDashboardScreen, PantallaBase a ScreenBase
private:
    // Constantes para las secciones de la interfaz de usuario
    static constexpr int _SECTION_HEADER = 0;             ///< Sección del encabezado (Mi Perfil, Cerrar Sesión). // Renombrado SECCION_HEADER, static constexpr
    static constexpr int _SECTION_TOP_MENU = 1;           ///< Sección del menú superior (Explorar, Gestionar Inscripciones). // Renombrado SECCION_MENU_SUPERIOR
    static constexpr int _SECTION_COURSES = 2;            ///< Sección de cursos inscritos. // Renombrado SECCION_CURSOS
    static constexpr int _SECTION_SPECIALIZATIONS = 3;    ///< Sección de especializaciones inscritas. // Renombrado SECCION_ESPECIALIZACIONES
    static constexpr int _TOTAL_SECTIONS = 4;             ///< Número total de secciones navegables. // Renombrado TOTAL_SECCIONES

    // Límites de elementos por sección
    static constexpr int _MAX_HEADER_ELEMENTS = 2;          ///< Máximo de elementos en la sección de encabezado (Ver perfil, Cerrar sesión). // Renombrado MAX_ELEMENTOS_HEADER
    static constexpr int _MAX_MENU_ELEMENTS = 1;            ///< Máximo de elementos en el menú superior (Explorar cursos y especialidades, Gestionar inscripciones). // Renombrado MAX_ELEMENTOS_MENU
    static constexpr int _MAX_COURSE_ELEMENTS = 4;          ///< Máximo de elementos en la sección de cursos (3 cursos + "Ver todos"). // Renombrado MAX_ELEMENTOS_CURSOS
    static constexpr int _MAX_SPECIALIZATION_ELEMENTS = 4;  ///< Máximo de elementos en la sección de especializaciones (3 especializaciones + "Ver todas"). // Renombrado MAX_ELEMENTOS_ESPECIALIZACIONES

    // Datos del usuario actual
    std::string _studentName; ///< Nombre del estudiante. // Renombrado nombreEstudiante a _studentName
    int _studentId;           ///< ID único del estudiante. // Renombrado idEstudiante a _studentId

    // Coordenadas para dibujar elementos de la interfaz
    COORD _headerElementCoords[_MAX_HEADER_ELEMENTS] = { {84, 3}, {99, 3} }; ///< Coordenadas para "Ver Mi Perfil" y "Cerrar Sesión". // Renombrado coordsElementosHeader
    COORD _menuElementCoords[_MAX_MENU_ELEMENTS] = { {9,10} /*, {47, 10}*/ }; ///< Coordenadas para "Explorar Cursos" y "Gestionar Inscripciones". // Renombrado coordsElementosMenu

    COORD _courseTitleCoords[_MAX_COURSE_ELEMENTS] = {
        {11, 15}, {42, 15}, {73, 15}, {101, 17} ///< Coordenadas para los títulos de cursos y el botón "Ver todos". // Renombrado coordsTituloCursos
    };

    COORD _specializationTitleCoords[_MAX_SPECIALIZATION_ELEMENTS] = {
        {11, 25}, {42, 25}, {73, 25}, {101, 27} ///< Coordenadas para los títulos de especializaciones y el botón "Ver todas". // Renombrado coordsTituloEspecializaciones
    };

    // Estado de la selección actual en la interfaz
    int _currentSection;    ///< Sección actualmente seleccionada. // Renombrado seccionActual a _currentSection
    int _currentElement;    ///< Elemento actualmente seleccionado dentro de la sección. // Renombrado elementoActual a _currentElement
    int _previousSection;   ///< Sección previamente seleccionada, para refresco parcial. // Renombrado seccionAnterior a _previousSection
    int _previousElement;   ///< Elemento previamente seleccionado, para refresco parcial. // Renombrado elementoAnterior a _previousElement
    bool _firstRender;      ///< Bandera para controlar la primera renderización completa de la interfaz. // Renombrado primeraRenderizacion a _firstRender

    // Datos cargados desde el sistema
    std::vector<AppConstants::MenuItem> _enrolledCourses;         ///< Lista de cursos en los que el estudiante está inscrito. // Renombrado cursosInscritos a _enrolledCourses, tipo MenuItem
    std::vector<AppConstants::MenuItem> _enrolledSpecializations; ///< Lista de especializaciones en las que el estudiante está inscrito. // Renombrado especializacionesInscritas a _enrolledSpecializations, tipo MenuItem

    int _visibleCourseIndex = 0;       ///< Índice del primer curso visible en la lista (para scroll futuro). // Renombrado indCursoVisible
    int _visibleSpecializationIndex = 0; ///< Índice de la primera especialización visible (para scroll futuro). // Renombrado indEspVisible

    // Ruta del archivo de datos
    static const std::string _ENROLLMENTS_FILE_PATH; ///< Ruta al archivo binario de inscripciones. // Renombrado RUTA_INSCRIPCIONES a _ENROLLMENTS_FILE_PATH, static const std::string

    /**
     * @brief Carga los datos necesarios para la pantalla del dashboard, incluyendo inscripciones.
     * @param _courseManager Referencia al gestor de cursos para obtener detalles de cursos/especializaciones.
     * @throws std::runtime_error si no se puede abrir el archivo de inscripciones.
     * @complexity O(M + N), donde M es el número de inscripciones y N el número de cursos/especializaciones a buscar.
     */
    void loadData(CourseManager& _courseManager) { // Renombrado cargarDatos, parámetros
        loadEnrollments(_courseManager); // Renombrado cargarInscripciones

        // Si no hay datos, agregar algunos de ejemplo para mostrar la UI
        if (_enrolledCourses.empty()) {
            for (int i = 0; i < 3; ++i) {
                _enrolledCourses.emplace_back("No inscrito", "Aqui apareceran los cursos en los que te has inscrito");
            }
        }

        if (_enrolledSpecializations.empty()) {
            for (int i = 0; i < 3; ++i) {
                _enrolledSpecializations.emplace_back("No inscrito", "Aqui apareceran las especialidades en las que te has inscrito");
            }
        }
    }

    /**
     * @brief Carga las inscripciones del estudiante actual desde un archivo binario.
     * Filtra las inscripciones por ID de estudiante y las categoriza como cursos o especializaciones.
     * @param _courseManager Referencia al gestor de cursos para obtener detalles de las actividades inscritas.
     * @throws std::runtime_error si el archivo de inscripciones no se puede abrir.
     * @complexity O(E * (C + S)), donde E es el número de inscripciones en el archivo,
     * C es el tiempo de búsqueda de un curso, S es el tiempo de búsqueda de una especialización.
     */
    void loadEnrollments(CourseManager& _courseManager) { // Renombrado cargarInscripciones, parámetros
        std::ifstream file(_ENROLLMENTS_FILE_PATH, std::ios::binary); // Usar std::ifstream, std::ios::binary
        if (!file.is_open()) {
            throw std::runtime_error("Error al abrir archivo de inscripciones: " + _ENROLLMENTS_FILE_PATH); // Mensaje de error más descriptivo
        }

        BinaryEnrollment enrollment; // Asumiendo 'InscripcionBinaria' fue refactorizado a 'BinaryEnrollment' en Enrollment.h
        while (file.read(reinterpret_cast<char*>(&enrollment), sizeof(BinaryEnrollment))) {
            // Filtrar por el ID del estudiante actual
            if (enrollment.studentId == _studentId) { // Renombrado idEstudiante a studentId
                // Determinar si es curso o especialización
                if (enrollment.activityType == 1) { // Curso
                    // Buscar el curso en el gestor
                    Course* course = _courseManager.getCourse(enrollment.activityId); // Renombrado obtenerCurso a getCourse, idActividad a activityId
                    if (course) {
                        _enrolledCourses.emplace_back(course->getTitle(), course->getDescription(), course->getId()); // Usar getTitle(), getDescription(), getId()
                    }
                } else if (enrollment.activityType == 2) { // Especialización
                    // Buscar la especialización en el gestor
                    Specialization* specialization = _courseManager.getSpecialization(enrollment.activityId); // Renombrado obtenerEspecializacion a getSpecialization
                    if (specialization) {
                        _enrolledSpecializations.emplace_back(specialization->getTitle(), specialization->getDescription(), specialization->getId()); // Usar getTitle(), getDescription(), getId()
                    }
                }
            }
        }
        file.close();
    }

    /**
     * @brief Dibuja la interfaz completa del dashboard del estudiante en la consola.
     * Realiza un borrado de pantalla y renderiza todas las secciones.
     * @complexity O(1) + O(Número de elementos a renderizar).
     */
    void drawFullInterface() { // Renombrado dibujarInterfazCompleta
        ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::BACKGROUND); // Usar ConsoleUtils y AppConstants::ConsoleColors
        system("cls"); // Considerar reemplazar system("cls") con una función de ConsoleUtils.h si es posible.
        AsciiUI::drawStudentDashboardScreen(); // Asumiendo una función de dibujo general en AsciiUI.h
        renderHeader();            // Renombrado renderizarHeader
        renderTopMenu();           // Renombrado renderizarMenuSuperior
        renderCourses();           // Renombrado renderizarCursos
        renderSpecializations();   // Renombrado renderizarEspecializaciones
    }

    /**
     * @brief Renderiza la sección del encabezado del dashboard, incluyendo el nombre del estudiante y los botones.
     * @complexity O(1)
     */
    void renderHeader() { // Renombrado renderizarHeader
        // Mostrar nombre de estudiante
        ConsoleUtils::setCursorPosition(52, 3); // Usar ConsoleUtils::setCursorPosition
        ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::BACKGROUND); // Usar ConsoleUtils y AppConstants::ConsoleColors
        std::cout << _studentName;
        ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::BACKGROUND); // Resetear color

        // Botones del header
        for (int i = 0; i < _MAX_HEADER_ELEMENTS; ++i) {
            ConsoleUtils::setCursorPosition(_headerElementCoords[i].X, _headerElementCoords[i].Y); // Usar ConsoleUtils::setCursorPosition
            if (_currentSection == _SECTION_HEADER && _currentElement == i) {
                ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::PURE_WHITE, AppConstants::ConsoleColors::DARK_BLUE); // Color para selección (texto blanco sobre azul oscuro de ColorPalette)
            } else {
                ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::BACKGROUND); // Color normal
            }
            std::cout << (i == 0 ? " VER MI PERFIL " : " CERRAR SESION ");
        }
        ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::BACKGROUND); // Resetear color
    }

    /**
     * @brief Renderiza la sección del menú superior del dashboard.
     * @complexity O(1)
     */
    void renderTopMenu() { // Renombrado renderizarMenuSuperior
        for (int i = 0; i < _MAX_MENU_ELEMENTS; ++i) {
            ConsoleUtils::setCursorPosition(_menuElementCoords[i].X, _menuElementCoords[i].Y); // Usar ConsoleUtils::setCursorPosition
            if (_currentSection == _SECTION_TOP_MENU && _currentElement == i) {
                ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::PURE_WHITE, AppConstants::ConsoleColors::DARK_BLUE); // Color para selección
            } else {
                ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::BACKGROUND); // Color normal
            }
            std::cout << (i == 0 ? " EXPLORAR CURSOS Y ESPECIALIDADES " : " GESTIONAR MIS INSCRIPCIONES ");
        }
        ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::BACKGROUND); // Resetear color
    }

    /**
     * @brief Renderiza la sección de cursos inscritos, mostrando hasta 3 cursos y la opción "Ver todos".
     * @complexity O(1)
     */
    void renderCourses() { // Renombrado renderizarCursos
        int numCoursesToShow = static_cast<int>(std::min(static_cast<size_t>(3), _enrolledCourses.size())); // Usar std::min
        for (int i = 0; i < numCoursesToShow; ++i) {
            ConsoleUtils::setCursorPosition(_courseTitleCoords[i].X, _courseTitleCoords[i].Y); // Usar ConsoleUtils::setCursorPosition
            if (_currentSection == _SECTION_COURSES && _currentElement == i) {
                ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::PURE_WHITE, AppConstants::ConsoleColors::DARK_BLUE); // Color para selección
            } else {
                ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::BACKGROUND); // Color normal
            }
            std::cout << _enrolledCourses[i].title; // Usar .title
        }

        // Botón "Ver todos"
        ConsoleUtils::setCursorPosition(_courseTitleCoords[3].X, _courseTitleCoords[3].Y); // Usar ConsoleUtils::setCursorPosition
        if (_currentSection == _SECTION_COURSES && _currentElement == 3) {
            ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::PURE_WHITE, AppConstants::ConsoleColors::DARK_BLUE); // Color para selección
        } else {
            ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::BACKGROUND); // Color normal
        }
        std::cout << " Ver todos ";
        ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::BACKGROUND); // Resetear color
    }

    /**
     * @brief Renderiza la sección de especializaciones inscritas, mostrando hasta 3 especializaciones y la opción "Ver todas".
     * @complexity O(1)
     */
    void renderSpecializations() { // Renombrado renderizarEspecializaciones
        int numSpecializationsToShow = static_cast<int>(std::min(static_cast<size_t>(3), _enrolledSpecializations.size())); // Usar std::min
        for (int i = 0; i < numSpecializationsToShow; ++i) {
            ConsoleUtils::setCursorPosition(_specializationTitleCoords[i].X, _specializationTitleCoords[i].Y); // Usar ConsoleUtils::setCursorPosition
            if (_currentSection == _SECTION_SPECIALIZATIONS && _currentElement == i) {
                ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::PURE_WHITE, AppConstants::ConsoleColors::DARK_BLUE); // Color para selección
            } else {
                ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::DARK_BLUE); // Color normal (fondo azul para esta sección)
            }
            std::cout << _enrolledSpecializations[i].title; // Usar .title
        }

        // Botón "Ver todas"
        ConsoleUtils::setCursorPosition(_specializationTitleCoords[3].X, _specializationTitleCoords[3].Y); // Usar ConsoleUtils::setCursorPosition
        if (_currentSection == _SECTION_SPECIALIZATIONS && _currentElement == 3) {
            ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::PURE_WHITE, AppConstants::ConsoleColors::DARK_BLUE); // Color para selección
        } else {
            ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::DARK_BLUE); // Color normal
        }
        std::cout << " Ver todas ";
        ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::BACKGROUND); // Resetear color
    }

    /**
     * @brief Actualiza la visualización de la selección de elementos en la interfaz.
     * Solo vuelve a renderizar las secciones afectadas por el cambio de selección.
     * @complexity O(1)
     */
    void updateSelection() { // Renombrado actualizarSeleccion
        if (_currentSection != _previousSection || _currentElement != _previousElement) {
            // Des-renderizar la selección anterior (restaurar color normal)
            switch (_previousSection) { // Usar _previousSection
            case _SECTION_HEADER: renderHeader(); break; // Usar constantes refactorizadas
            case _SECTION_TOP_MENU: renderTopMenu(); break;
            case _SECTION_COURSES: renderCourses(); break;
            case _SECTION_SPECIALIZATIONS: renderSpecializations(); break;
            }

            // Renderizar la nueva selección (aplicar color de selección)
            switch (_currentSection) { // Usar _currentSection
            case _SECTION_HEADER: renderHeader(); break;
            case _SECTION_TOP_MENU: renderTopMenu(); break;
            case _SECTION_COURSES: renderCourses(); break;
            case _SECTION_SPECIALIZATIONS: renderSpecializations(); break;
            }

            _previousSection = _currentSection; // Actualizar estado anterior
            _previousElement = _currentElement; // Actualizar estado anterior
        }
    }

    /**
     * @brief Obtiene el número máximo de elementos navegables en una sección dada.
     * @param _section El índice de la sección.
     * @return El número máximo de elementos para la sección especificada.
     * @complexity O(1)
     */
    int getMaxElementsInSection(int _section) { // Renombrado obtenerMaxElementosEnSeccion, parámetro
        switch (_section) {
        case _SECTION_HEADER: return _MAX_HEADER_ELEMENTS; // Usar constantes refactorizadas
        case _SECTION_TOP_MENU: return _MAX_MENU_ELEMENTS;
        case _SECTION_COURSES: return _MAX_COURSE_ELEMENTS;
        case _SECTION_SPECIALIZATIONS: return _MAX_SPECIALIZATION_ELEMENTS;
        default: return 0;
        }
    }

public:
    /**
     * @brief Constructor de la clase StudentDashboardScreen.
     * Inicializa el dashboard con los datos del estudiante y carga sus inscripciones.
     * @param _studentId El ID del estudiante.
     * @param _studentName El nombre del estudiante.
     * @param _courseManager Referencia al gestor de cursos para la carga de datos.
     */
    StudentDashboardScreen(int _studentId, std::string _studentName, CourseManager& _courseManager) // Renombrado constructor, parámetros
        : _currentSection(_SECTION_HEADER), _currentElement(0), // Inicializar miembros
        _previousSection(-1), _previousElement(-1),
        _firstRender(true), _studentId(_studentId),
        _studentName(_studentName) {
        loadData(_courseManager); // Cargar datos al construir la pantalla
    }

    /**
     * @brief Implementación del método virtual para ejecutar la pantalla del dashboard.
     * Gestiona la interacción del usuario y la navegación entre secciones.
     * @return ScreenResult El resultado de la interacción, indicando la siguiente acción/pantalla.
     * @complexity Bucle que se ejecuta hasta que el usuario decida salir o navegar a otra pantalla.
     */
    ScreenResult run() override { // Renombrado ejecutar a run, tipo de retorno ScreenResult
        while (true) {
            if (_firstRender) {
                drawFullInterface(); // Dibujar la interfaz completa si es la primera vez
                _firstRender = false; // Desactivar bandera de primera renderización
            } else {
                updateSelection(); // Actualizar solo la selección si ya se renderizó
            }

            int key = _getch(); // Renombrado tecla a key
            switch (key) {
            case 224: // Tecla extendida (flechas, etc.)
                key = _getch(); // Obtener el código de la tecla extendida
                switch (key) {
                case 72: // Flecha arriba
                    if (_currentSection > _SECTION_HEADER) {
                        _currentSection--;
                        _currentElement = 0; // Resetear elemento al cambiar de sección
                    }
                    break;
                case 80: // Flecha abajo
                    if (_currentSection < _TOTAL_SECTIONS - 1) {
                        _currentSection++;
                        _currentElement = 0; // Resetear elemento al cambiar de sección
                    }
                    break;
                case 75: // Flecha izquierda
                    if (_currentElement > 0) {
                        _currentElement--;
                    }
                    break;
                case 77: // Flecha derecha
                    if (_currentElement < getMaxElementsInSection(_currentSection) - 1) {
                        _currentElement++;
                    }
                    break;
                }
                break;
            case 13: { // Enter
                ScreenResult result; // Crear un ScreenResult local
                // Procesar la acción según la sección y elemento actual
                if (_currentSection == _SECTION_HEADER) {
                    if (_currentElement == 0) {
                        // Ver perfil del estudiante
                        result.action = ScreenAction::GO_TO_STUDENT_PROFILE; // Usar ScreenAction y GO_TO_STUDENT_PROFILE
                        result.userType = UserType::STUDENT; // Explicitly set user type
                        return result;
                    } else if (_currentElement == 1) {
                        // Cerrar sesión
                        result.action = ScreenAction::GO_TO_LANDING_PAGE; // Usar ScreenAction y GO_TO_LANDING_PAGE
                        return result;
                    }
                } else if (_currentSection == _SECTION_TOP_MENU) {
                    if (_currentElement == 0) {
                        // Explorar cursos y especialidades
                        result.action = ScreenAction::GO_TO_EXPLORE_COURSES_AND_SPECIALIZATIONS; // Usar ScreenAction
                        result.userType = UserType::STUDENT; // Explicitly set student type
                        return result;
                    }
                    // else if (_currentElement == 1) {
                    //     // Gestionar mis inscripciones (futura implementación)
                    //     // result.action = ScreenAction::GO_TO_MANAGE_ENROLLMENTS;
                    //     // return result;
                    // }
                }
                // Lógica para SECCION_CURSOS y SECCION_ESPECIALIZACIONES
                else if (_currentSection == _SECTION_COURSES) {
                    if (_currentElement == _MAX_COURSE_ELEMENTS - 1) { // Último elemento es "Ver todos"
                        result.action = ScreenAction::ENROLLED_COURSES_SCREEN; // O una pantalla que liste todos los cursos inscritos
                        return result;
                    } else if (_currentElement < _enrolledCourses.size()) {
                         // Asumiendo que los elementos tienen un ID asociado para la navegación a detalles
                        result.action = ScreenAction::COURSE_DETAIL_SCREEN;
                        result.selectedCourseId = _enrolledCourses[_currentElement].id; // Pasar el ID del curso seleccionado
                        return result;
                    }
                }
                else if (_currentSection == _SECTION_SPECIALIZATIONS) {
                    if (_currentElement == _MAX_SPECIALIZATION_ELEMENTS - 1) { // Último elemento es "Ver todas"
                        result.action = ScreenAction::ENROLLED_SPECIALIZATIONS_SCREEN; // O una pantalla que liste todas las especializaciones inscritas
                        return result;
                    } else if (_currentElement < _enrolledSpecializations.size()) {
                        result.action = ScreenAction::SPECIALIZATION_DETAIL_SCREEN;
                        result.selectedCourseId = _enrolledSpecializations[_currentElement].id; // Usar selectedCourseId para el ID de especialización temporalmente
                        return result;
                    }
                }
                break;
            }
            case 27: { // ESC
                ScreenResult result;
                result.action = ScreenAction::GO_TO_LANDING_PAGE; // Volver a Landing Page
                return result;
            }
            }
        }
    }
};

// Inicialización de la constante estática
const std::string StudentDashboardScreen::_ENROLLMENTS_FILE_PATH = "Resources/Data/inscripciones.dat"; // Inicialización fuera de la clase