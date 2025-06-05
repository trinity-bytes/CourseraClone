#pragma once

#include "../Utils/Pantalla.h"
#include "../Utils/ExtendedFunctions.h"
#include "../Utils/UI_Ascii.h"
#include "../Entities/Inscripcion.h"
#include "../Entities/Curso.h"
#include "../Entities/Especializacion.h"
#include "../Controllers/GestionadorCursos.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

class DashboardOrganizacion : public PantallaBase
{
private:
    // Constantes para las secciones
    static const int SECCION_HEADER = 0;
    static const int SECCION_MENU_SUPERIOR = 1;
    static const int SECCION_CURSOS = 2;
    static const int SECCION_ESPECIALIZACIONES = 3;
    static const int TOTAL_SECCIONES = 4;

    // Elementos por secci�n
    static const int MAX_ELEMENTOS_HEADER = 2; // Ver mi perfil, Cerrar sesi�n
    static const int MAX_ELEMENTOS_MENU = 2; // Explorar cursos, Gestionar cursos
    static const int MAX_ELEMENTOS_CURSOS = 4; // 3 cursos + "Ver todos"
    static const int MAX_ELEMENTOS_ESPECIALIZACIONES = 4; // 3 especializaciones + "Ver todas"

    // Estad�sticas de la organizaci�n
    int cursosPublicados = 35;
    int especialidadesPublicadas = 10;
    int estudiantesInscritos = 342;

    // Datos del usuario
    string nombreOrganizacion;
    int idOrganizacion;

    // Coordenadas para dibujar
    COORD coordsElementosHeader[MAX_ELEMENTOS_HEADER] = { {84, 3}, {99, 3} }; // Perfil, Cerrar sesi�n
    COORD coordsElementosMenu[MAX_ELEMENTOS_MENU] = { {9, 10}, {47, 10} }; // Explorar, Gestionar
    COORD coordsEstadisticas[3] = { {11, 7}, {40, 7}, {76, 7} }; // Estad�sticas

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
    bool primeraRenderizacion;

    // Datos cargados
    vector<ElementoMenu> cursos;
    vector<ElementoMenu> especializaciones;

    void cargarDatos(GestionadorCursos& gestion) {
        // Cargar cursos y especializaciones de la organizaci�n
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
                cursos.emplace_back("Curso " + to_string(i + 1), "Descripci�n del curso " + to_string(i + 1));
            }
        } 

        if (especializaciones.empty()) {
            for (int i = 0; i < 3; i++) {
                especializaciones.emplace_back("Especializaci�n " + to_string(i + 1), "Descripci�n de la especializaci�n " + to_string(i + 1));
            }
        }
    }

    void dibujarInterfazCompleta() 
    {
        SetConsoleColor(15, 0);
        system("cls");
        UI_OrganizationDashboard();
        renderizarHeader();
        renderizarEstadisticas();
        renderizarMenuSuperior();
        renderizarCursos();
        renderizarEspecializaciones();
    }

    void renderizarHeader() {
        // Mostrar nombre de la organizaci�n
        gotoXY(53, 3);
        SetConsoleColor(15, 0);
        cout << nombreOrganizacion;

        // Botones del header
        for (int i = 0; i < MAX_ELEMENTOS_HEADER; ++i) {
            gotoXY(coordsElementosHeader[i].X, coordsElementosHeader[i].Y);
            if (seccionActual == SECCION_HEADER && elementoActual == i) {
                SetConsoleColor(1, 13); // Color para selecci�n
            }
            else {
                SetConsoleColor(15, 0); // Color normal
            }
            cout << (i == 0 ? " VER MI PERFIL " : " CERRAR SESION ");
        }

        SetConsoleColor(15, 0);
    }

    void renderizarEstadisticas() {
        gotoXY(coordsEstadisticas[0].X, coordsEstadisticas[0].Y);
        SetConsoleColor(15, 0);
        cout << "Cursos publicados: " << cursosPublicados;

        gotoXY(coordsEstadisticas[1].X, coordsEstadisticas[1].Y);
        cout << "Especialidades publicadas: " << especialidadesPublicadas;

        gotoXY(coordsEstadisticas[2].X, coordsEstadisticas[2].Y);
        cout << "Estudiantes inscritos: " << estudiantesInscritos;
    }

    void renderizarMenuSuperior() {
        for (int i = 0; i < MAX_ELEMENTOS_MENU; ++i) {
            gotoXY(coordsElementosMenu[i].X, coordsElementosMenu[i].Y);
            if (seccionActual == SECCION_MENU_SUPERIOR && elementoActual == i) {
                SetConsoleColor(1, 13); // Color para selecci�n
            }
            else {
                SetConsoleColor(15, 0); // Color normal
            }
            cout << (i == 0 ? " EXPLORAR CURSOS Y ESPECIALIDADES " : " GESTIONAR MIS CURSOS ");
        }

        SetConsoleColor(15, 0);
    }

    void renderizarCursos() {
        // Renderizar 3 cursos
        int numCursos = (int)cursos.size() < 3 ? (int)cursos.size() : 3;
        for (int i = 0; i < numCursos; ++i) {
            gotoXY(coordsTituloCursos[i].X, coordsTituloCursos[i].Y);
            if (seccionActual == SECCION_CURSOS && elementoActual == i) {
                SetConsoleColor(1, 13); // Color para selecci�n
            }
            else {
                SetConsoleColor(15, 0); // Color normal
            }
            cout << cursos[i].titulo;
        }

        // Bot�n "Ver todos"
        gotoXY(coordsTituloCursos[3].X, coordsTituloCursos[3].Y);
        if (seccionActual == SECCION_CURSOS && elementoActual == 3) {
            SetConsoleColor(1, 13); // Color para selecci�n
        }
        else {
            SetConsoleColor(15, 0); // Color normal
        }
        cout << " Ver todos ";

        SetConsoleColor(15, 0);
    }

    void renderizarEspecializaciones() {
        // Renderizar 3 especializaciones
        int numEspecializaciones = (int)especializaciones.size() < 3 ? (int)especializaciones.size() : 3;
        for (int i = 0; i < numEspecializaciones; ++i) {
            gotoXY(coordsTituloEspecializaciones[i].X, coordsTituloEspecializaciones[i].Y);
            if (seccionActual == SECCION_ESPECIALIZACIONES && elementoActual == i) {
                SetConsoleColor(1, 13); // Color para selecci�n
            }
            else {
                SetConsoleColor(15, 0); // Color normal
            }
            cout << especializaciones[i].titulo;
        }

        // Bot�n "Ver todas"
        gotoXY(coordsTituloEspecializaciones[3].X, coordsTituloEspecializaciones[3].Y);
        if (seccionActual == SECCION_ESPECIALIZACIONES && elementoActual == 3) {
            SetConsoleColor(1, 13); // Color para selecci�n
        }
        else {
            SetConsoleColor(15, 0); // Color normal
        }
        cout << " Ver todas ";

        SetConsoleColor(15, 0);
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
    DashboardOrganizacion(int _idOrganizacion = 1, string _nombreOrganizacion = "Organizaci�n de Prueba", GestionadorCursos& gestion = GestionadorCursos())
        : seccionActual(SECCION_HEADER), elementoActual(0),
        seccionAnterior(-1), elementoAnterior(-1),
        primeraRenderizacion(true), idOrganizacion(_idOrganizacion),
        nombreOrganizacion(_nombreOrganizacion) {

        cargarDatos(gestion);
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
                break;
            case 13: // Enter
                // Procesar la acci�n seg�n la secci�n y elemento actual
                if (seccionActual == SECCION_HEADER) {
                    if (elementoActual == 0) {
                        // Ver perfil
                        ResultadoPantalla res;
                        res.accion = AccionPantalla::IR_A_PERFIL_ORGANIZACION;
                        return res;
                    }
                    else if (elementoActual == 1) {
                        // Cerrar sesi�n
                        ResultadoPantalla res;
                        res.accion = AccionPantalla::IR_A_LANDING_PAGE;
                        return res;
                    }
                }
                else if (seccionActual == SECCION_MENU_SUPERIOR) {
                    if (elementoActual == 0) {
                        // Explorar cursos y especialidades
                        ResultadoPantalla res;
                        res.accion = AccionPantalla::IR_A_EXPLORAR_CURSOS_Y_ESPECIALIDADES;
                        res.tipoUsuario = TipoUsuario::EMPRESA; // Indicar que es una organizaci�n
                        return res;
                    }
                    // Aca se pueden agregar mas acciones
                }
                break;
            case 27: // ESC
            {
                ResultadoPantalla res;
                res.accion = AccionPantalla::IR_A_LANDING_PAGE;
                return res;
            }
            }
        }
    }
};
