#pragma once
#include "ExtendedFunctions.h"
#include "UI_Ascii.h"
#include "vector"
#include "string"
#include "conio.h"  // interaccion de menus
#include "fstream"  // interactuar con txt
#include "limits"   // numeric_limits

using namespace std;

/// Constantes globales
// IDs secciones
const int SECCION_CABECERA = 0;
const int SECCION_ESPECIALIDADES = 1;
const int SECCION_CURSOS = 2;
const int TOTAL_SECCIONES = 3;

// Archivos de persistencia
const string ARCHIVO_PERSISTENCIA = "ultima_posi.txt";
const string ARCHIVO_ESPECIALIDADES = "especialidades_muestra.txt";
const string ARCHIVO_CURSOS = "cursos_muestra.txt";

// Items max visibles por seccion
const int MAX_ELEMENTOS_CABECERA = 3;
const int MAX_ELEMENTOS_ESPECIALIDAD = 3; // 3 rectangulos
const int MAX_ELEMENTOS_CURSO = 3;   // 3 rectangulos

/// Estructuras de datos
struct ElementoMenu {
    string titulo;
    string descripcion; // Usado para especialidades y cursos
};

/// Variables globales
// Coordenadas para dibujar contenido dinamico
COORD coordsElementosCabecera[MAX_ELEMENTOS_CABECERA] = { {10, 4}, {40, 4}, {70, 4} }; 
COORD coordsTituloEspecialidad[MAX_ELEMENTOS_ESPECIALIDAD] = { {10, 9}, {50, 9}, {90, 9} };
COORD coordsDescEspecialidad[MAX_ELEMENTOS_ESPECIALIDAD] = { {10, 10}, {50, 10}, {90, 10} }; 
COORD coordsTituloCurso[MAX_ELEMENTOS_CURSO] = { {10, 20}, {50, 20}, {90, 20} }; 
COORD coordsDescCurso[MAX_ELEMENTOS_CURSO] = { {10, 21}, {50, 21}, {90, 21} }; 

vector<ElementoMenu> especialidades;
vector<ElementoMenu> cursos;
int seccionActual = SECCION_CABECERA;
int elementoActual = 0;


// --- Prototipos de Funciones ---
void dibujarInterfaz();
void cargarDatos(const string& nombreArchivo, vector<ElementoMenu>& datos, const vector<ElementoMenu>& datosDefecto);
void cargarPersistencia();
void guardarPersistencia();
int obtenerMaxElementosEnSeccion(int seccion);
void manejarEntrada();
void manejarSeleccion(int seccion, int elemento);
void mostrarMensaje(const string& msg);

short MostrarMenu_LandingPage()
{
	short opc = 0;

    // Datos por defecto si los archivos faltan o están vacíos
    vector<ElementoMenu> especialidadesDefecto = {
        {"Desarrollo Web", "Frontend & Backend"},
        {"Ciencia de Datos", "Análisis y ML"},
        {"Marketing Digital", "SEO, SEM & Ads"}
    };
    vector<ElementoMenu> cursosDefecto = {
        {"Curso C++ CLI", "Interaccion consola"},
        {"Curso Python DS", "Data science intro"},
        {"Curso React JS", "Web UI development"}
    };

    // Cargar datos desde archivos (o usar valores por defecto)
    cargarDatos(ARCHIVO_ESPECIALIDADES, especialidades, especialidadesDefecto);
    cargarDatos(ARCHIVO_CURSOS, cursos, cursosDefecto);

    // Cargar última posición seleccionada
    cargarPersistencia();

    bool ejecutando = true;
    while (ejecutando) {
        dibujarInterfaz();
        manejarEntrada();
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { // Verificar si Esc fue presionado durante manejarEntrada
            ejecutando = false;
        }
        // Pequeño retraso para prevenir alto uso de CPU
        Sleep(50);
    }

    // Guardar última posición seleccionada antes de salir
    guardarPersistencia();

    return opc;
}

// Dibuja la interfaz completa incluyendo ASCII base y datos/selección dinámicos
void dibujarInterfaz() 
{
	UI_LandingPage(); // Llamar a la función de dibujo ASCII

    // Dibujar Elementos de Cabecera
    vector<string> elementosCabecera = { " Iniciar Sesion ", " Registrarse ", " Sobre Nosotros " };
    for (int i = 0; i < MAX_ELEMENTOS_CABECERA; ++i) 
    {
        if (i < elementosCabecera.size()) 
        {
            gotoXY(coordsElementosCabecera[i].X, coordsElementosCabecera[i].Y);
            if (seccionActual == SECCION_CABECERA && elementoActual == i) 
            {
                cout << "-> ";
            }
            else {
                cout << "   "; // Espacio para marcador
            }
            cout << elementosCabecera[i];
            restablecerColorTexto(); // Restablecer después de potencialmente resaltar
        }
    }

    // Dibujar Especialidades
    for (int i = 0; i < MAX_ELEMENTOS_ESPECIALIDAD; ++i) {
        if (i < especialidades.size()) {
            // Dibujar Título
            gotoXY(coordsTituloEspecialidad[i].X, coordsTituloEspecialidad[i].Y);
            if (seccionActual == SECCION_ESPECIALIDADES && elementoActual == i) {
                establecerColorTexto(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            }
            else {
                restablecerColorTexto();
            }
            cout << especialidades[i].titulo;

            // Dibujar Descripción (dividir en líneas si es necesario, o simplemente imprimir)
            gotoXY(coordsDescEspecialidad[i].X, coordsDescEspecialidad[i].Y);
            if (seccionActual == SECCION_ESPECIALIDADES && elementoActual == i) {
                establecerColorTexto(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            }
            else {
                restablecerColorTexto();
            }
            cout << especialidades[i].descripcion;

            // Dibujar Marcador de Selección
            if (seccionActual == SECCION_ESPECIALIDADES && elementoActual == i) {
                gotoXY(coordsTituloEspecialidad[i].X - 3, coordsTituloEspecialidad[i].Y); // Marcador a la izquierda del título
                establecerColorTexto(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "->";
            }
            else {
                gotoXY(coordsTituloEspecialidad[i].X - 3, coordsTituloEspecialidad[i].Y);
                restablecerColorTexto();
                cout << "  ";
            }

            restablecerColorTexto();
        }
        else {
            // Limpiar área si no existe elemento
            gotoXY(coordsTituloEspecialidad[i].X - 3, coordsTituloEspecialidad[i].Y);
            cout << "                                    "; // Limpiar marcador + área de título/desc
            gotoXY(coordsDescEspecialidad[i].X, coordsDescEspecialidad[i].Y);
            cout << "                                    ";
        }
    }

    // Dibujar Cursos
    for (int i = 0; i < MAX_ELEMENTOS_CURSO; ++i) {
        if (i < cursos.size()) {
            // Dibujar Título
            gotoXY(coordsTituloCurso[i].X, coordsTituloCurso[i].Y);
            if (seccionActual == SECCION_CURSOS && elementoActual == i) {
                establecerColorTexto(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            }
            else {
                restablecerColorTexto();
            }
            cout << cursos[i].titulo;

            // Dibujar Descripción (dividir en líneas si es necesario, o simplemente imprimir)
            gotoXY(coordsDescCurso[i].X, coordsDescCurso[i].Y);
            if (seccionActual == SECCION_CURSOS && elementoActual == i) {
                establecerColorTexto(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            }
            else {
                restablecerColorTexto();
            }
            cout << cursos[i].descripcion;

            // Dibujar Marcador de Selección
            if (seccionActual == SECCION_CURSOS && elementoActual == i) {
                gotoXY(coordsTituloCurso[i].X - 3, coordsTituloCurso[i].Y); // Marcador a la izquierda del título
                establecerColorTexto(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "->";
            }
            else {
                gotoXY(coordsTituloCurso[i].X - 3, coordsTituloCurso[i].Y);
                restablecerColorTexto();
                cout << "  ";
            }

            restablecerColorTexto();
        }
        else {
            // Limpiar área si no existe elemento
            gotoXY(coordsTituloCurso[i].X - 3, coordsTituloCurso[i].Y);
            cout << "                                    "; // Limpiar marcador + área de título/desc
            gotoXY(coordsDescCurso[i].X, coordsDescCurso[i].Y);
            cout << "                                    ";
        }
    }


    // Asegurar que el cursor esté en una posición no obstructiva después de dibujar
    gotoXY(0, ALTO_CONSOLA - 1);
}