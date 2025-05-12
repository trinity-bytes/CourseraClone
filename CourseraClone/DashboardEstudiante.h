#pragma once

#include "Pantalla.h"
#include "ExtendedFunctions.h"
#include "UI_Ascii.h"
#include "Inscripcion.h"
#include "Curso.h"
#include "Especializacion.h"
#include "GestionadorCursos.h"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm> // Para min

using namespace std;

class DashboardEstudiante : public PantallaBase 
{
private:
    // Constantes para las secciones
    static const int SECCION_HEADER = 0;
    static const int SECCION_MENU_SUPERIOR = 1;
    static const int SECCION_CURSOS = 2;
    static const int SECCION_ESPECIALIZACIONES = 3;
    static const int TOTAL_SECCIONES = 4;

    // Elementos por sección
    static const int MAX_ELEMENTOS_HEADER = 2; // Ver mi perfil, Cerrar sesión
    static const int MAX_ELEMENTOS_MENU = 2; // Explorar cursos, Gestionar inscripciones
    static const int MAX_ELEMENTOS_CURSOS = 4; // 3 cursos + "Ver todos"
    static const int MAX_ELEMENTOS_ESPECIALIZACIONES = 4; // 3 especializaciones + "Ver todas"

    // Datos del usuario
    string nombreEstudiante;
    int idEstudiante;

    // Coordenadas para dibujar
    COORD coordsElementosHeader[MAX_ELEMENTOS_HEADER] = { {84, 3}, {99, 3} }; // Perfil, Cerrar sesión
    COORD coordsElementosMenu[MAX_ELEMENTOS_MENU] = { {9, 10}, {47, 10} }; // Explorar, Gestionar

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
    vector<ElementoMenu> cursosInscritos;
    vector<ElementoMenu> especializacionesInscritas;

    // Ruta del archivo de inscripciones
    const string RUTA_INSCRIPCIONES = ".\\Resources\\Data\\inscripciones.bin";

    void cargarDatos(GestionadorCursos* gestion) {
        cargarInscripciones(gestion);

        // Si no hay datos, agregar algunos de ejemplo
        if (cursosInscritos.empty()) 
        {
            for (int i = 0; i < 3; i++)
            {
                cursosInscritos.emplace_back("No inscrito", "Aqui apareceran los cursos en los que te has inscrito");
            }
        }

        if (especializacionesInscritas.empty()) 
        {
            for (int i = 0; i < 3; i++)
            {
                especializacionesInscritas.emplace_back("No inscrito", "Aqui apareceran las especialidades en las que te has inscrito");
            }
        }
    }

    void cargarInscripciones(GestionadorCursos* gestion) {
        // Abrir el archivo de inscripciones binario
        

        ifstream archivo(RUTA_INSCRIPCIONES, ios::binary);
        if (!archivo.is_open()) {
            return;
        }

        // Leer todas las inscripciones
        InscripcionBinaria inscripcion;
        while (archivo.read(reinterpret_cast<char*>(&inscripcion), sizeof(InscripcionBinaria))) {

            // Filtrar por el ID del estudiante actual
            if (inscripcion.idEstudiante == idEstudiante) {
                throw runtime_error("paso");
                // Determinar si es curso o especialización
                if (inscripcion.tipoActividad == 1) { // Curso
                    // Buscar el curso en el gestionador
                    Curso* curso = gestion->obtenerCursoPorId(inscripcion.idActividad);
                    if (curso) {
                        cursosInscritos.emplace_back(curso->getTitulo(), curso->getDescripcion());
                    }
                }
                else if (inscripcion.tipoActividad == 2) { // Especialización
                    // Buscar la especialización en el gestionador
                    Especializacion* especializacion = gestion->obtenerEspecializacionPorId(inscripcion.idActividad);
                    if (especializacion) {
                        especializacionesInscritas.emplace_back(especializacion->getTitulo(), especializacion->getDescripcion());
                    }
                }
            }
        }
        archivo.close();
    }


    void dibujarInterfazCompleta() 
    {
        system("cls");
        UI_StudentDashboard();
        renderizarHeader();
        renderizarMenuSuperior();
        renderizarCursos();
        renderizarEspecializaciones();
    }

    void renderizarHeader() {
        // Mostrar nombre de estudiante
        gotoXY(52, 3);
        SetConsoleColor(15, 1);
        cout << nombreEstudiante;

        // Botones del header
        for (int i = 0; i < MAX_ELEMENTOS_HEADER; ++i) {
            gotoXY(coordsElementosHeader[i].X, coordsElementosHeader[i].Y);
            if (seccionActual == SECCION_HEADER && elementoActual == i) {
                SetConsoleColor(1, 13); // Color para selección
            }
            else {
                SetConsoleColor(15, 1); // Color normal
            }
            cout << (i == 0 ? " VER MI PERFIL " : " CERRAR SESION ");
        }

        SetConsoleColor(15, 1);
    }

    void renderizarMenuSuperior() {
        for (int i = 0; i < MAX_ELEMENTOS_MENU; ++i) {
            gotoXY(coordsElementosMenu[i].X, coordsElementosMenu[i].Y);
            if (seccionActual == SECCION_MENU_SUPERIOR && elementoActual == i) {
                SetConsoleColor(1, 13); // Color para selección
            }
            else {
                SetConsoleColor(15, 1); // Color normal
            }
            cout << (i == 0 ? " EXPLORAR CURSOS Y ESPECIALIDADES " : " GESTIONAR MIS INSCRIPCIONES ");
        }

        SetConsoleColor(15, 1);
    }

    void renderizarCursos() 
    {
        // Renderizar 3 cursos
        int numCursos = (int)cursosInscritos.size() < 3 ? (int)cursosInscritos.size() : 3;
        for (int i = 0; i < numCursos; ++i) {
            gotoXY(coordsTituloCursos[i].X, coordsTituloCursos[i].Y);
            if (seccionActual == SECCION_CURSOS && elementoActual == i) {
                SetConsoleColor(1, 13); // Color para selección
            }
            else {
                SetConsoleColor(15, 1); // Color normal
            }
            cout << cursosInscritos[i].titulo;
        }

        // Botón "Ver todos"
        gotoXY(coordsTituloCursos[3].X, coordsTituloCursos[3].Y);
        if (seccionActual == SECCION_CURSOS && elementoActual == 3) {
            SetConsoleColor(1, 13); // Color para selección
        }
        else {
            SetConsoleColor(15, 1); // Color normal
        }
        cout << " Ver todos ";

        SetConsoleColor(15, 1);
    }

    void renderizarEspecializaciones() 
    {
        // Renderizar 3 especializaciones
        int numEspecializaciones = (int)especializacionesInscritas.size() < 3 ? (int)especializacionesInscritas.size() : 3;
        for (int i = 0; i < numEspecializaciones; ++i) {
            gotoXY(coordsTituloEspecializaciones[i].X, coordsTituloEspecializaciones[i].Y);
            if (seccionActual == SECCION_ESPECIALIZACIONES && elementoActual == i) {
                SetConsoleColor(1, 13); // Color para selección
            }
            else {
                SetConsoleColor(15, 1); // Color normal
            }
            cout << especializacionesInscritas[i].titulo;
        }

        // Botón "Ver todas"
        gotoXY(coordsTituloEspecializaciones[3].X, coordsTituloEspecializaciones[3].Y);
        if (seccionActual == SECCION_ESPECIALIZACIONES && elementoActual == 3) {
            SetConsoleColor(1, 13); // Color para selección
        }
        else {
            SetConsoleColor(15, 1); // Color normal
        }
        cout << " Ver todas ";

        SetConsoleColor(15, 1);
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
    DashboardEstudiante(int _idEstudiante, string _nombreEstudiante, GestionadorCursos* gestion)
        : seccionActual(SECCION_HEADER), elementoActual(0),
        seccionAnterior(-1), elementoAnterior(-1),
        primeraRenderizacion(true), idEstudiante(_idEstudiante),
        nombreEstudiante(_nombreEstudiante) {

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
                // Procesar la acción según la sección y elemento actual
                if (seccionActual == SECCION_HEADER) {
                    if (elementoActual == 0) {
                        // Ver perfil
                        ResultadoPantalla res;
                        res.accion = AccionPantalla::IR_A_PERFIL_ESTUDIANTE;
                        return res;
                    }
                    else if (elementoActual == 1) {
                        // Cerrar sesión
                        ResultadoPantalla res;
                        res.accion = AccionPantalla::IR_A_LANDING_PAGE;
                        return res;
                    }
                }
                else if (seccionActual == SECCION_MENU_SUPERIOR) {
                    if (elementoActual == 0) {
                        // Explorar cursos y especialidades
                        ResultadoPantalla res;
                        res.accion = AccionPantalla::IR_A_EXPLORAR_CURSOS_Y_ESPECIALIDADES; // Nueva acción que debemos añadir
                        return res;
                    }
                    else if (elementoActual == 1) {
                        // Gestionar mis inscripciones
                        ResultadoPantalla res;
                        res.accion = AccionPantalla::IR_A_GESTIONAR_INSCRIPCIONES; // Nueva acción que debemos añadir
                        return res;
                    }
                }
                break;
            case 27: // ESC
                ResultadoPantalla res;
                res.accion = AccionPantalla::IR_A_LANDING_PAGE;
                return res;
            }
        }
    }
}; 