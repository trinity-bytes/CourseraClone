// filepath: Headers/Screens/OrganizationDashboardScreen.h
// Descripción: Define la pantalla del dashboard para organizaciones.
//              Permite a la organización ver sus estadísticas, explorar cursos/especializaciones,
//              y gestionar sus publicaciones.
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
#include "../Entities/Enrollment.h"         // Renombrado Inscripcion.h a Enrollment.h // Aunque no se usa directamente, se mantiene para consistencia si es una dependencia transitoria.
#include "../Entities/Course.h"             // Renombrado Curso.h a Course.h
#include "../Entities/Specialization.h"     // Renombrado Especializacion.h a Specialization.h
#include "../Controllers/CourseManager.h"   // Renombrado GestionadorCursos.h a CourseManager.h

// Headers de la librería estándar
#include <vector>     // Para std::vector
#include <string>     // Para std::string
#include <fstream>    // Para std::ifstream
#include <sstream>    // Para std::stringstream
#include <algorithm>  // Para std::min
#include <windows.h>  // Para COORD

/**
 * @brief Implementa la pantalla del dashboard para una organización.
 * Permite a la organización ver estadísticas, explorar sus cursos y especializaciones,
 * y navegar a otras secciones de gestión.
 */
class OrganizationDashboardScreen : public ScreenBase { // Renombrado DashboardOrganizacion a OrganizationDashboardScreen, PantallaBase a ScreenBase
private:
    // Constantes para las secciones de la interfaz de usuario
    static constexpr int _SECTION_HEADER = 0;             ///< Sección del encabezado (Mi Perfil, Cerrar Sesión). // Renombrado SECCION_HEADER, static constexpr
    static constexpr int _SECTION_TOP_MENU = 1;           ///< Sección del menú superior (Explorar, Gestionar Cursos). // Renombrado SECCION_MENU_SUPERIOR
    static constexpr int _SECTION_COURSES = 2;            ///< Sección de cursos publicados. // Renombrado SECCION_CURSOS
    static constexpr int _SECTION_SPECIALIZATIONS = 3;    ///< Sección de especializaciones publicadas. // Renombrado SECCION_ESPECIALIZACIONES
    static constexpr int _TOTAL_SECTIONS = 4;             ///< Número total de secciones navegables. // Renombrado TOTAL_SECCIONES

    // Límites de elementos por sección
    static constexpr int _MAX_HEADER_ELEMENTS = 2;          ///< Máximo de elementos en la sección de encabezado (Ver perfil, Cerrar sesión). // Renombrado MAX_ELEMENTOS_HEADER
    static constexpr int _MAX_MENU_ELEMENTS = 2;            ///< Máximo de elementos en el menú superior (Explorar, Gestionar). // Renombrado MAX_ELEMENTOS_MENU
    static constexpr int _MAX_COURSE_ELEMENTS = 4;          ///< Máximo de elementos en la sección de cursos (3 cursos + "Ver todos"). // Renombrado MAX_ELEMENTOS_CURSOS
    static constexpr int _MAX_SPECIALIZATION_ELEMENTS = 4;  ///< Máximo de elementos en la sección de especializaciones (3 especializaciones + "Ver todas"). // Renombrado MAX_ELEMENTOS_ESPECIALIZACIONES

    // Estadísticas de la organización
    int _publishedCoursesCount;       ///< Número de cursos publicados por la organización. // Renombrado cursosPublicados a _publishedCoursesCount
    int _publishedSpecializationsCount; ///< Número de especializaciones publicadas por la organización. // Renombrado especialidadesPublicadas a _publishedSpecializationsCount
    int _enrolledStudentsCount;       ///< Número total de estudiantes inscritos en cursos/especializaciones de la organización. // Renombrado estudiantesInscritos a _enrolledStudentsCount

    // Datos de la organización actual
    std::string _organizationName; ///< Nombre de la organización. // Renombrado nombreOrganizacion a _organizationName
    int _organizationId;           ///< ID único de la organización. // Renombrado idOrganizacion a _organizationId

    // Coordenadas para dibujar elementos de la interfaz
    COORD _headerElementCoords[_MAX_HEADER_ELEMENTS] = { {84, 3}, {99, 3} }; ///< Coordenadas para "Ver Mi Perfil" y "Cerrar Sesión". // Renombrado coordsElementosHeader
    COORD _menuElementCoords[_MAX_MENU_ELEMENTS] = { {9, 10}, {47, 10} }; ///< Coordenadas para "Explorar Cursos" y "Gestionar Cursos". // Renombrado coordsElementosMenu
    COORD _statisticsCoords[3] = { {11, 7}, {40, 7}, {76, 7} }; ///< Coordenadas para las estadísticas (Cursos, Especialidades, Estudiantes). // Renombrado coordsEstadisticas

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

    // Datos cargados (cursos y especializaciones de la organización)
    std::vector<AppConstants::MenuItem> _courses;          ///< Lista de cursos publicados por esta organización. // Renombrado cursos a _courses, tipo MenuItem
    std::vector<AppConstants::MenuItem> _specializations;  ///< Lista de especializaciones publicadas por esta organización. // Renombrado especializaciones a _specializations, tipo MenuItem

    /**
     * @brief Carga los datos necesarios para la pantalla del dashboard de la organización.
     * Esto incluye los cursos y especializaciones que la organización ha publicado.
     * @param _courseManager Referencia al gestor de cursos para acceder a la base de datos de cursos/especializaciones.
     * @complexity O(C + S), donde C es el número total de cursos y S el número total de especializaciones en el sistema.
     */
    void loadData(CourseManager& _courseManager) { // Renombrado cargarDatos, parámetros
        // Cargar cursos y especializaciones de la organización
        // Asumiendo que getCourses() y getSpecializations() devuelven una estructura iterable como un LinkedList
        // o un vector. Adaptar si la interfaz de CourseManager es diferente.
        for (int i = 1; i <= _courseManager.getCourses().getTamano(); ++i) { // Asumiendo getTamano() para el tamaño de la lista
            Course* c = _courseManager.getCourses().get(i); // Asumiendo get(index) para acceder a elementos
            if (c && c->getOrganizationId() == _organizationId) { // Renombrado getIdEmpresa a getOrganizationId
                _courses.emplace_back(c->getTitle(), c->getDescription(), c->getId()); // Usar getTitle(), getDescription(), getId()
            }
        }
        _publishedCoursesCount = static_cast<int>(_courses.size()); // Actualizar contador

        for (int i = 1; i <= _courseManager.getSpecializations().getTamano(); ++i) { // Asumiendo getTamano() para el tamaño de la lista
            Specialization* e = _courseManager.getSpecializations().get(i); // Asumiendo get(index) para acceder a elementos
            if (e && e->getOrganizationId() == _organizationId) { // Renombrado getIdEmpresa a getOrganizationId
                _specializations.emplace_back(e->getTitle(), e->getDescription(), e->getId()); // Usar getTitle(), getDescription(), getId()
            }
        }
        _publishedSpecializationsCount = static_cast<int>(_specializations.size()); // Actualizar contador

        // Añadir datos de ejemplo si no hay cursos/especializaciones publicados
        if (_courses.empty()) {
            for (int i = 0; i < 3; ++i) {
                _courses.emplace_back("Curso " + std::to_string(i + 1), "Descripción del curso " + std::to_string(i + 1), 0); // Asumiendo ID 0 para ejemplos
            }
        }

        if (_specializations.empty()) {
            for (int i = 0; i < 3; ++i) {
                _specializations.emplace_back("Especialización " + std::to_string(i + 1), "Descripción de la especialización " + std::to_string(i + 1), 0); // Asumiendo ID 0 para ejemplos
            }
        }

        // Asumiendo que el conteo de estudiantes inscritos se obtendrá de alguna manera,
        // por ahora se mantiene el valor inicial o se podría cargar desde un archivo de inscripciones
        // o una función en CourseManager. Para este ejemplo, se mantiene el valor de inicialización si no hay otra fuente.
        // _enrolledStudentsCount = _courseManager.countEnrolledStudentsForOrganization(_organizationId); // Ejemplo de cómo podría cargarse
    }

    /**
     * @brief Dibuja la interfaz completa del dashboard de la organización en la consola.
     * Realiza un borrado de pantalla y renderiza todas las secciones.
     * @complexity O(1) + O(Número de elementos a renderizar).
     */
    void drawFullInterface() { // Renombrado dibujarInterfazCompleta
        ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::BACKGROUND); // Usar ConsoleUtils y AppConstants::ConsoleColors
        system("cls"); // Considerar reemplazar system("cls") con una función de ConsoleUtils.h si es posible.
        AsciiUI::drawOrganizationDashboardScreen(); // Asumiendo una función de dibujo general en AsciiUI.h
        renderHeader();            // Renombrado renderizarHeader
        renderStatistics();        // Renombrado renderizarEstadisticas
        renderTopMenu();           // Renombrado renderizarMenuSuperior
        renderCourses();           // Renombrado renderizarCursos
        renderSpecializations();   // Renombrado renderizarEspecializaciones
    }

    /**
     * @brief Renderiza la sección del encabezado del dashboard, incluyendo el nombre de la organización y los botones.
     * @complexity O(1)
     */
    void renderHeader() { // Renombrado renderizarHeader
        // Mostrar nombre de la organización
        ConsoleUtils::setCursorPosition(53, 3); // Usar ConsoleUtils::setCursorPosition
        ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::BACKGROUND); // Usar ConsoleUtils y AppConstants::ConsoleColors
        std::cout << _organizationName;

        // Botones del header
        for (int i = 0; i < _MAX_HEADER_ELEMENTS; ++i) {
            ConsoleUtils::setCursorPosition(_headerElementCoords[i].X, _headerElementCoords[i].Y); // Usar ConsoleUtils::setCursorPosition
            if (_currentSection == _SECTION_HEADER && _currentElement == i) {
                ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::PURE_WHITE, AppConstants::ConsoleColors::DARK_BLUE); // Color para selección
            } else {
                ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::BACKGROUND); // Color normal
            }
            std::cout << (i == 0 ? " VER MI PERFIL " : " CERRAR SESION ");
        }
        ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::BACKGROUND); // Resetear color
    }

    /**
     * @brief Renderiza la sección de estadísticas de la organización.
     * @complexity O(1)
     */
    void renderStatistics() { // Renombrado renderizarEstadisticas
        ConsoleUtils::setCursorPosition(_statisticsCoords[0].X, _statisticsCoords[0].Y); // Usar ConsoleUtils::setCursorPosition
        ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::BACKGROUND); // Usar ConsoleUtils y AppConstants::ConsoleColors
        std::cout << "Cursos publicados: " << _publishedCoursesCount; // Usar _publishedCoursesCount

        ConsoleUtils::setCursorPosition(_statisticsCoords[1].X, _statisticsCoords[1].Y);
        std::cout << "Especialidades publicadas: " << _publishedSpecializationsCount; // Usar _publishedSpecializationsCount

        ConsoleUtils::setCursorPosition(_statisticsCoords[2].X, _statisticsCoords[2].Y);
        std::cout << "Estudiantes inscritos: " << _enrolledStudentsCount; // Usar _enrolledStudentsCount
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
            std::cout << (i == 0 ? " EXPLORAR CURSOS Y ESPECIALIDADES " : " GESTIONAR MIS CURSOS ");
        }
        ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::BACKGROUND); // Resetear color
    }

    /**
     * @brief Renderiza la sección de cursos publicados, mostrando hasta 3 cursos y la opción "Ver todos".
     * @complexity O(1)
     */
    void renderCourses() { // Renombrado renderizarCursos
        int numCoursesToShow = static_cast<int>(std::min(static_cast<size_t>(3), _courses.size())); // Usar std::min
        for (int i = 0; i < numCoursesToShow; ++i) {
            ConsoleUtils::setCursorPosition(_courseTitleCoords[i].X, _courseTitleCoords[i].Y); // Usar ConsoleUtils::setCursorPosition
            if (_currentSection == _SECTION_COURSES && _currentElement == i) {
                ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::PURE_WHITE, AppConstants::ConsoleColors::DARK_BLUE); // Color para selección
            } else {
                ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::BACKGROUND); // Color normal
            }
            std::cout << _courses[i].title; // Usar .title
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
     * @brief Renderiza la sección de especializaciones publicadas, mostrando hasta 3 especializaciones y la opción "Ver todas".
     * @complexity O(1)
     */
    void renderSpecializations() { // Renombrado renderizarEspecializaciones
        int numSpecializationsToShow = static_cast<int>(std::min(static_cast<size_t>(3), _specializations.size())); // Usar std::min
        for (int i = 0; i < numSpecializationsToShow; ++i) {
            ConsoleUtils::setCursorPosition(_specializationTitleCoords[i].X, _specializationTitleCoords[i].Y); // Usar ConsoleUtils::setCursorPosition
            if (_currentSection == _SECTION_SPECIALIZATIONS && _currentElement == i) {
                ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::PURE_WHITE, AppConstants::ConsoleColors::DARK_BLUE); // Color para selección
            } else {
                ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::BACKGROUND); // Color normal
            }
            std::cout << _specializations[i].title; // Usar .title
        }

        // Botón "Ver todas"
        ConsoleUtils::setCursorPosition(_specializationTitleCoords[3].X, _specializationTitleCoords[3].Y); // Usar ConsoleUtils::setCursorPosition
        if (_currentSection == _SECTION_SPECIALIZATIONS && _currentElement == 3) {
            ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::PURE_WHITE, AppConstants::ConsoleColors::DARK_BLUE); // Color para selección
        } else {
            ConsoleUtils::setConsoleTextAttributes(AppConstants::ConsoleColors::NORMAL_TEXT, AppConstants::ConsoleColors::BACKGROUND); // Color normal
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
     * @brief Constructor de la clase OrganizationDashboardScreen.
     * Inicializa el dashboard con los datos de la organización y carga sus publicaciones.
     * @param _organizationId El ID de la organización.
     * @param _organizationName El nombre de la organización.
     * @param _courseManager Referencia al gestor de cursos para la carga de datos.
     */
    OrganizationDashboardScreen(int _organizationId, std::string _organizationName, CourseManager& _courseManager) // Renombrado constructor, parámetros
        : _currentSection(_SECTION_HEADER), _currentElement(0), // Inicializar miembros
        _previousSection(-1), _previousElement(-1),
        _firstRender(true), _organizationId(_organizationId),
        _organizationName(_organizationName),
        _publishedCoursesCount(0), _publishedSpecializationsCount(0), _enrolledStudentsCount(0) // Inicializar contadores
    {
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
                system("cls"); // Considerar reemplazar system("cls") con una función de ConsoleUtils.h si es posible.
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
                        // Ver perfil de la organización
                        result.action = ScreenAction::GO_TO_ORGANIZATION_PROFILE; // Usar ScreenAction y GO_TO_ORGANIZATION_PROFILE
                        result.userType = UserType::ORGANIZATION; // Explicitly set user type
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
                        result.userType = UserType::ORGANIZATION; // Indicar que es una organización
                        return result;
                    } else if (_currentElement == 1) {
                        // Gestionar mis cursos (ej. añadir, editar, eliminar)
                        result.action = ScreenAction::GO_TO_MANAGE_ORGANIZATION_COURSES; // Nueva acción si es necesario
                        result.userType = UserType::ORGANIZATION;
                        return result;
                    }
                }
                // Lógica para _SECTION_COURSES y _SECTION_SPECIALIZATIONS
                else if (_currentSection == _SECTION_COURSES) {
                    if (_currentElement == _MAX_COURSE_ELEMENTS - 1) { // Último elemento es "Ver todos"
                        result.action = ScreenAction::ORGANIZATION_COURSES_SCREEN; // O una pantalla que liste todos los cursos de la organización
                        return result;
                    } else if (_currentElement < _courses.size()) {
                         // Asumiendo que los elementos tienen un ID asociado para la navegación a detalles
                        result.action = ScreenAction::COURSE_DETAIL_SCREEN;
                        result.selectedCourseId = _courses[_currentElement].id; // Pasar el ID del curso seleccionado
                        return result;
                    }
                }
                else if (_currentSection == _SECTION_SPECIALIZATIONS) {
                    if (_currentElement == _MAX_SPECIALIZATION_ELEMENTS - 1) { // Último elemento es "Ver todas"
                        result.action = ScreenAction::ORGANIZATION_SPECIALIZATIONS_SCREEN; // O una pantalla que liste todas las especializaciones de la organización
                        return result;
                    } else if (_currentElement < _specializations.size()) {
                        result.action = ScreenAction::SPECIALIZATION_DETAIL_SCREEN;
                        result.selectedCourseId = _specializations[_currentElement].id; // Usar selectedCourseId para el ID de especialización temporalmente
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

// No se requiere inicialización de constantes estáticas con valores por defecto en el constructor,
// ya que la inicialización de _publishedCoursesCount, _publishedSpecializationsCount, _enrolledStudentsCount
// se realiza en el constructor, y las coordenadas son arrays con valores fijos.