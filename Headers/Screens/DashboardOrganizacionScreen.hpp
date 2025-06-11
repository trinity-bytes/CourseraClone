#pragma once

// Headers de librería estándar
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// Headers propios
#include "../Controllers/GestionadorCursos.h"
#include "../Entities/Curso.h"
#include "../Entities/Especializacion.h"
#include "../Entities/Inscripcion.h"
#include "../Utils/SystemUtils.h"
#include "../Utils/ScreenSystem.h"
#include "../Utils/UI_Ascii.h"

class DashboardOrganizacionScreen : public PantallaBase
{
private:
    // Constantes para las secciones
    static const int SECCION_HEADER = 0;
    static const int SECCION_MENU_SUPERIOR = 1;
    static const int SECCION_CURSOS = 2;
    static const int SECCION_ESPECIALIZACIONES = 3;
    static const int TOTAL_SECCIONES = 4;    // Elementos por sección
    static const int MAX_ELEMENTOS_HEADER = 2; // Ver mi perfil, Cerrar sesión
    static const int MAX_ELEMENTOS_MENU = 2; // Explorar cursos, Gestionar cursos
    static const int MAX_ELEMENTOS_CURSOS = 4; // 3 cursos + "Ver todos"
    static const int MAX_ELEMENTOS_ESPECIALIZACIONES = 4; // 3 especializaciones + "Ver todas"// Estadísticas de la organización
    int cursosPublicados = 35;
    int especialidadesPublicadas = 10;
    int estudiantesInscritos = 342;

    // Datos del usuario
    std::string nombreOrganizacion;
    int idOrganizacion;

    // Coordenadas para dibujar
    COORD coordsElementosHeader[MAX_ELEMENTOS_HEADER] = { {84, 3}, {99, 3} }; // Perfil, Cerrar sesión
    COORD coordsElementosMenu[MAX_ELEMENTOS_MENU] = { {9, 10}, {47, 10} }; // Explorar, Gestionar
    COORD coordsEstadisticas[3] = { {11, 7}, {40, 7}, {76, 7} }; // Estadísticas

    // Coordenadas para cursos
    COORD coordsTituloCursos[MAX_ELEMENTOS_CURSOS] = {
        {11, 15}, {42, 15}, {73, 15}, {101, 17} // 3 cursos + "Ver todos"
    };

    // Coordenadas para especializaciones
    COORD coordsTituloEspecializaciones[MAX_ELEMENTOS_ESPECIALIZACIONES] = {
        {11, 25}, {42, 25}, {73, 25}, {101, 27} // 3 especializaciones + "Ver todos"
    };

    // Estado actual
    int seccionActual;
    int elementoActual;
    int seccionAnterior;
    int elementoAnterior;
    bool primeraRenderizacion;    // Datos cargados
    std::vector<ElementoMenu> cursos;
    std::vector<ElementoMenu> especializaciones;    void cargarDatos(GestionadorCursos& gestion) {
        // Cargar cursos y especializaciones de la organización
        for (int i = 1; i <= gestion.getCursos().getTamano(); i++) {
            Curso* c = gestion.getCursos().get(i);
            if (c->getIdEmpresa() == idOrganizacion) {
                cursos.emplace_back(c->getTitulo(), c->getDescripcion());
            }
        }
        cursosPublicados = cursos.size();

        for (int i = 1; i <= gestion.getEspecializaciones().getTamano(); i++) {
            Especializacion* e = gestion.getEspecializaciones().get(i);
            if (e->getIdEmpresa() == idOrganizacion) {
                especializaciones.emplace_back(e->getTitulo(), e->getDescripcion());
            }
        }
        especialidadesPublicadas = especializaciones.size();

        if (cursos.empty()) {
            for (int i = 0; i < 3; i++) {
                cursos.emplace_back("Curso " + std::to_string(i + 1), "Descripción del curso " + std::to_string(i + 1));
            }
        } 

        if (especializaciones.empty()) {
            for (int i = 0; i < 3; i++) {
                especializaciones.emplace_back("Especialización " + std::to_string(i + 1), "Descripción de la especialización " + std::to_string(i + 1));
            }
        }
    }

    void dibujarInterfazCompleta() 
    {
        setConsoleColor(15, 0);
        system("cls");
        UI_OrganizationDashboard();
        renderizarHeader();
        renderizarEstadisticas();
        renderizarMenuSuperior();
        renderizarCursos();
        renderizarEspecializaciones();
    }

    
    
    void renderizarHeader() {        // Mostrar nombre de la organización
        gotoXY(53, 3);
        setConsoleColor(15, 0);
        std::cout << nombreOrganizacion;        // Botones del header
        for (int i = 0; i < MAX_ELEMENTOS_HEADER; ++i) {
            gotoXY(coordsElementosHeader[i].X, coordsElementosHeader[i].Y);
            if (seccionActual == SECCION_HEADER && elementoActual == i) {
                setConsoleColor(1, 13); // Color para selección
            }
            else {
                setConsoleColor(15, 0); // Color normal
            }
            std::cout << (i == 0 ? " VER MI PERFIL " : " CERRAR SESION ");
        }

        setConsoleColor(15, 0);
    }    void renderizarEstadisticas() {
        gotoXY(coordsEstadisticas[0].X, coordsEstadisticas[0].Y);
        setConsoleColor(15, 0);
        std::cout << "Cursos publicados: " << cursosPublicados;

        gotoXY(coordsEstadisticas[1].X, coordsEstadisticas[1].Y);
        std::cout << "Especialidades publicadas: " << especialidadesPublicadas;

        gotoXY(coordsEstadisticas[2].X, coordsEstadisticas[2].Y);
        std::cout << "Estudiantes inscritos: " << estudiantesInscritos;
    }    void renderizarMenuSuperior() {
        for (int i = 0; i < MAX_ELEMENTOS_MENU; ++i) {
            gotoXY(coordsElementosMenu[i].X, coordsElementosMenu[i].Y);
            if (seccionActual == SECCION_MENU_SUPERIOR && elementoActual == i) {
                setConsoleColor(1, 13); // Color para selección
            }
            else {
                setConsoleColor(15, 0); // Color normal
            }
            std::cout << (i == 0 ? " EXPLORAR CURSOS Y ESPECIALIDADES " : " GESTIONAR MIS CURSOS ");
        }

        setConsoleColor(15, 0);
    }    void renderizarCursos() {
        // Renderizar 3 cursos
        int numCursos = (int)cursos.size() < 3 ? (int)cursos.size() : 3;
        for (int i = 0; i < numCursos; ++i) {
            gotoXY(coordsTituloCursos[i].X, coordsTituloCursos[i].Y);
            if (seccionActual == SECCION_CURSOS && elementoActual == i) {
                setConsoleColor(1, 13); // Color para selección
            }
            else {
                setConsoleColor(15, 0); // Color normal
            }
            std::cout << cursos[i].titulo;
        }

        // Botón "Ver todos"
        gotoXY(coordsTituloCursos[3].X, coordsTituloCursos[3].Y);
        if (seccionActual == SECCION_CURSOS && elementoActual == 3) {
            setConsoleColor(1, 13); // Color para selección
        }
        else {
            setConsoleColor(15, 0); // Color normal
        }
        std::cout << " Ver todos ";

        setConsoleColor(15, 0);
    }    void renderizarEspecializaciones() {
        // Renderizar 3 especializaciones
        int numEspecializaciones = (int)especializaciones.size() < 3 ? (int)especializaciones.size() : 3;
        for (int i = 0; i < numEspecializaciones; ++i) {
            gotoXY(coordsTituloEspecializaciones[i].X, coordsTituloEspecializaciones[i].Y);
            if (seccionActual == SECCION_ESPECIALIZACIONES && elementoActual == i) {
                setConsoleColor(1, 13); // Color para selección
            }
            else {
                setConsoleColor(15, 0); // Color normal
            }
            std::cout << especializaciones[i].titulo;
        }

        // Botón "Ver todas"
        gotoXY(coordsTituloEspecializaciones[3].X, coordsTituloEspecializaciones[3].Y);
        if (seccionActual == SECCION_ESPECIALIZACIONES && elementoActual == 3) {
            setConsoleColor(1, 13); // Color para selección
        }
        else {
            setConsoleColor(15, 0); // Color normal
        }
        std::cout << " Ver todas ";

        setConsoleColor(15, 0);
    }

    void actualizarSeleccion() {
        if (seccionActual != seccionAnterior || elementoActual != elementoAnterior) {
            switch (seccionAnterior) {
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

            switch (seccionActual) {
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

            seccionAnterior = seccionActual;
            elementoAnterior = elementoActual;
        }
    }

    int obtenerMaxElementosEnSeccion(int seccion) {
        switch (seccion) {
        case SECCION_HEADER: return MAX_ELEMENTOS_HEADER;
        case SECCION_MENU_SUPERIOR: return MAX_ELEMENTOS_MENU;
        case SECCION_CURSOS: return MAX_ELEMENTOS_CURSOS;
        case SECCION_ESPECIALIZACIONES: return MAX_ELEMENTOS_ESPECIALIZACIONES;
        default: return 0;
        }
    }

public:
    DashboardOrganizacionScreen(Controladora* _controladora, int _idOrganizacion, const std::string& _nombreOrganizacion)
        : PantallaBase(_controladora), seccionActual(SECCION_HEADER), elementoActual(0),
        seccionAnterior(-1), elementoAnterior(-1),
        primeraRenderizacion(true), idOrganizacion(_idOrganizacion),
        nombreOrganizacion(_nombreOrganizacion) {

        cargarDatos(*_controladora->getGestionadorCursos());
    }

    ResultadoPantalla ejecutar() override {
        while (true) {
            if (primeraRenderizacion) {
                system("cls");
                dibujarInterfazCompleta();
                primeraRenderizacion = false;
            }
            else {
                actualizarSeleccion();
            }

            int tecla = _getch();
            switch (tecla) {
            case 224: // Tecla extendida
                tecla = _getch();
                switch (tecla) {
                case 72: // Flecha arriba
                    if (seccionActual > SECCION_HEADER) {
                        seccionActual--;
                        elementoActual = 0;
                    }
                    break;
                case 80: // Flecha abajo
                    if (seccionActual < TOTAL_SECCIONES - 1) {
                        seccionActual++;
                        elementoActual = 0;
                    }
                    break;
                case 75: // Flecha izquierda
                    if (elementoActual > 0) {
                        elementoActual--;
                    }
                    break;
                case 77: // Flecha derecha
                    if (elementoActual < obtenerMaxElementosEnSeccion(seccionActual) - 1) {
                        elementoActual++;
                    }
                    break;
                }
                break;            case 13: // Enter
                // Procesar la acción según la sección y elemento actual
                if (seccionActual == SECCION_HEADER) {
                    if (elementoActual == 0) {
                        // Ver perfil
                        return crearResultado(AccionPantalla::IR_A_PERFIL_ORGANIZACION);
                    }
                    else if (elementoActual == 1) {
                        // Cerrar sesión
                        return crearResultado(AccionPantalla::IR_A_LANDING_PAGE);
                    }
                }
                else if (seccionActual == SECCION_MENU_SUPERIOR) {
                    if (elementoActual == 0) {
                        // Explorar cursos y especialidades
                        return crearResultado(AccionPantalla::IR_A_EXPLORAR_CURSOS_Y_ESPECIALIDADES);
                    }
                    // Aca se pueden agregar mas acciones
                }
                break;
            case 27: // ESC
                return crearResultado(AccionPantalla::IR_A_LANDING_PAGE);
            }
        }
    }
};
