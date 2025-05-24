#pragma once

#include "Pantalla.h"
#include "ExtendedFunctions.h"
#include "UI_Ascii.h"
#include "Curso.h"
#include "Clase.h"
#include "GestionadorCursos.h"
#include "Estudiante.h"
#include <vector>
#include <string>
#include <algorithm> // Para min
#include <sstream>   // Para istringstream

class MostrarCurso : public PantallaBase
{
private:
    // Datos del curso
    int idCurso;
    Curso* curso;
    GestionadorCursos& gestionadorCursos; // Añadir
    Estudiante& estudiante;
    vector<Clase> clases;

    TipoUsuario tipoUsuario;

    // Estado de navegación
    int claseSeleccionada;
    bool primeraRenderizacion;
    AccionPantalla pantallaAnterior;

    // Constantes para las coordenadas
    const int COL_TITULO_CURSO = 7;
    const int FILA_TITULO_CURSO = 7;

    const int COL_DESC_CURSO = 7;
    const int FILA_DESC_CURSO = 11;

    const int COL_MODULOS = 57;
    const int FILA_MODULOS_BASE = 10;
    const int ESPACIO_ENTRE_MODULOS = 4;

    const int MAX_MODULOS_VISIBLES = 5;
    const int LONGITUD_TEXTO_MODULO = 40;
	const int LONGITUD_TITULO_CURSO = 30;

    // Método para truncar títulos largos
    string truncarTitulo(const string& titulo, int maxLongitud) {
        if (titulo.length() <= maxLongitud) {
            return titulo;
        }
        return titulo.substr(0, maxLongitud - 3) + "...";
    }

    vector<string> dividirTituloEnLineas(const string& titulo, int maxLongitudPorLinea, int maxLineas = 3) {
        vector<string> lineas;
        if (titulo.empty()) {
            return lineas;
        }

        string textoRestante = titulo;

        for (int i = 0; i < maxLineas && !textoRestante.empty(); ++i) {
            if (textoRestante.length() <= maxLongitudPorLinea) {
                // If remaining text fits on one line
                lineas.push_back(textoRestante);
                textoRestante.clear();
            }
            else {
                // Find a good place to break the line
                int posCorte = maxLongitudPorLinea;

                // Try to cut at a space to avoid breaking words
                while (posCorte > 0 && textoRestante[posCorte] != ' ' && textoRestante[posCorte - 1] != ' ') {
                    posCorte--;
                }

                // If no good break point found, just cut at max length
                if (posCorte <= 0) {
                    posCorte = maxLongitudPorLinea;
                }

                // Add the line
                lineas.push_back(textoRestante.substr(0, posCorte));

                // Update remaining text
                textoRestante = textoRestante.substr(posCorte);
                textoRestante.erase(0, textoRestante.find_first_not_of(" "));
            }
        }

        // If text still remains and we've reached max lines, add ellipsis to last line
        if (!textoRestante.empty() && lineas.size() == maxLineas) {
            string& lastLine = lineas.back();
            if (lastLine.length() > 3) {
                lastLine = lastLine.substr(0, lastLine.length() - 3) + "...";
            }
        }

        return lineas;
    }

    // Método para formatear descripción
    string formatearDescripcion(const string& texto, int anchoMax, int altoMax) {
        string resultado;
        string textoRestante = texto;

        for (int linea = 0; linea < altoMax; ++linea) {
            if (textoRestante.empty()) break;

            if (linea == altoMax - 1 && textoRestante.length() > anchoMax) {
                resultado += textoRestante.substr(0, anchoMax - 3) + "...";
                break;
            }

            if (textoRestante.length() <= anchoMax) {
                resultado += textoRestante;
                textoRestante.clear();
            }
            else {
                int posCorte = anchoMax;
                while (posCorte > 0 && textoRestante[posCorte] != ' ' && textoRestante[posCorte - 1] != ' ') {
                    posCorte--;
                }

                if (posCorte <= 0) {
                    posCorte = anchoMax;
                }

                resultado += textoRestante.substr(0, posCorte);
                textoRestante = textoRestante.substr(posCorte);
                textoRestante.erase(0, textoRestante.find_first_not_of(" "));
            }

            if (linea < altoMax - 1 && !textoRestante.empty()) {
                resultado += "\n";
            }
        }

        return resultado;
    }

    void dibujarInterfazCompleta() {
        gotoXY(50, 3);
        system("cls");
        UI_VistaCurso();

        // Mostrar título del curso
        gotoXY(COL_TITULO_CURSO, FILA_TITULO_CURSO);
        const int INDENTACION_TITULO = COL_TITULO_CURSO + 10;
        vector<string> tituloCurso = dividirTituloEnLineas(curso->getTitulo(), LONGITUD_TITULO_CURSO);
        cout << "Curso de: ";
        if (!tituloCurso.empty()) {
            cout << tituloCurso[0];

            // Display the rest of the lines with proper indentation
            for (size_t i = 1; i < tituloCurso.size(); ++i) {
                gotoXY(INDENTACION_TITULO, FILA_TITULO_CURSO + i);
                cout << tituloCurso[i];
            }
        }

        // Mostrar descripción del curso
        gotoXY(COL_DESC_CURSO, FILA_DESC_CURSO);

        cout << "Descripcion del contenido del curso:";
        gotoXY(COL_DESC_CURSO, FILA_DESC_CURSO + 2);

        // Formatear y mostrar descripción
        string descripcionFormateada = formatearDescripcion(curso->getDescripcion(), 40, 5);
        istringstream descStream(descripcionFormateada);
        string linea;
        int fila = FILA_DESC_CURSO + 2;
        while (getline(descStream, linea)) {
            gotoXY(COL_DESC_CURSO, fila++);
            cout << linea;
        }

        // Mostrar clases del curso
        int numClases = (clases.size() < MAX_MODULOS_VISIBLES) ? clases.size() : MAX_MODULOS_VISIBLES;
        for (int i = 0; i < numClases; i++) {
            dibujarClase(i, i == claseSeleccionada);
        }

        // Muestra la opcion de inscripcion solo a estudiantes
        if (tipoUsuario == TipoUsuario::ESTUDIANTE) {
            gotoXY(50, 3);
            SetConsoleColor(0, 13);
            cout << "Presiona 'I' para inscribirte a este curso";
        }
        else if (tipoUsuario == TipoUsuario::EMPRESA) {
            gotoXY(50, 3);
            SetConsoleColor(8, 13); // Color gris para indicar deshabilitado
            cout << "Solo estudiantes pueden inscribirse a cursos";
        }
        SetConsoleColor(15, 0);
    }

    void dibujarClase(int indice, bool seleccionada) {
        if (indice < 0 || indice >= clases.size()) return;

        // Posición para el número del módulo
        gotoXY(COL_MODULOS, FILA_MODULOS_BASE + indice * ESPACIO_ENTRE_MODULOS);

        if (seleccionada)
            SetConsoleColor(1, 13); // Color para selección
        else
            SetConsoleColor(15, 0); // Color normal

        // Mostrar número de clase
        cout << indice + 1;

        // Posición para el título de la clase
        gotoXY(COL_MODULOS + 5, FILA_MODULOS_BASE + indice * ESPACIO_ENTRE_MODULOS);

        // Truncar y mostrar título
        string tituloClase = truncarTitulo(clases[indice].getTitulo(), LONGITUD_TEXTO_MODULO);
        cout << tituloClase;

        SetConsoleColor(15, 0);
    }

public:
    MostrarCurso(int _idCurso, GestionadorCursos& _gestionadorCursos, Estudiante& _estudiante,
        Curso* _curso, AccionPantalla _pantallaAnterior = AccionPantalla::IR_A_LANDING_PAGE,
        TipoUsuario _tipoUsuario = TipoUsuario::ESTUDIANTE)
        : idCurso(_idCurso),
        gestionadorCursos(_gestionadorCursos),
        estudiante(_estudiante),
        curso(_curso),
        claseSeleccionada(0),
        primeraRenderizacion(true),
        pantallaAnterior(_pantallaAnterior),
        tipoUsuario(_tipoUsuario)
    {
        // Si no se proporcionó un curso, intentar cargarlo por ID
        /*
        if (curso.getTitulo() == "" && gestionadorCursos != nullptr) {
            curso = gestionadorCursos->obtenerCurso(idCurso);
        }
        else if (curso == nullptr) {
            // Si no hay gestionador, crear un curso de ejemplo
            curso = new Curso(idCurso, 1, "Empresa",
                "Curso " + to_string(idCurso),
                "Esta es la descripción detallada del curso. Incluye información sobre lo que aprenderán los estudiantes, los requisitos previos y los resultados esperados al finalizar el curso.",
                "Instructor", 5);
        }
        */

        // Cargar las clases del curso
        if (curso) {
            // Intentar obtener las clases del curso
            const LinkedList<Clase>& clasesLista = curso->getClases();
            int tamano = curso->getCantidadClases();

            // Si el curso tiene clases, convertir la lista a un vector para facilitar el acceso
            for (int i = 0; i < tamano; i++) {
                Clase clase = curso->getClases().get(i); // Usar get() en lugar de []
                clases.push_back(clase);
            }

            // Si no hay clases, crear algunas de ejemplo
            if (clases.empty()) {
                for (int i = 1; i <= 5; i++) {
                    clases.emplace_back("Clase " + to_string(i) + ": " + curso->getTitulo(),
                        "Contenido de la clase" + to_string(i));
                }
            }
        }
    }

    ~MostrarCurso() = default;

    ResultadoPantalla ejecutar() override {
        ResultadoPantalla res;

        if (primeraRenderizacion) {
            dibujarInterfazCompleta();
            primeraRenderizacion = false;
        }

        while (true) {
            int tecla = _getch();

            switch (tecla) {
            case 224: // Tecla extendida
                tecla = _getch();

                switch (tecla) {
                case 72: // Flecha arriba
                    if (claseSeleccionada > 0) {
                        dibujarClase(claseSeleccionada, false);
                        claseSeleccionada--;
                        dibujarClase(claseSeleccionada, true);
                    }
                    break;

                case 80: // Flecha abajo
                    if (claseSeleccionada < clases.size() - 1 && claseSeleccionada < MAX_MODULOS_VISIBLES - 1) {
                        dibujarClase(claseSeleccionada, false);
                        claseSeleccionada++;
                        dibujarClase(claseSeleccionada, true);
                    }
                    break;
                }
                break;
            case 'i': // Inscribirse al curso
            case 'I':

                if (tipoUsuario == TipoUsuario::EMPRESA) {
                    gotoXY(5, 25);
                    SetConsoleColor(4, 0); // Rojo sobre negro
                    cout << "Las organizaciones no pueden inscribirse a cursos.";
                    SetConsoleColor(15, 0); // Restaurar color
                    _getch(); // Esperar una tecla
                    dibujarInterfazCompleta();
                    break;
                }

                if (estudiante.getNombreCompleto() == "") {
                    if (estudiante.inscribirseACurso(curso)) { // Usar el método de estudiante
                        // Mostrar mensaje de éxito
                        gotoXY(5, 25);
                        SetConsoleColor(2, 0); // Verde sobre negro
                        cout << "Inscripción exitosa!";
                        SetConsoleColor(15, 0); // Restaurar color
                        _getch(); // Esperar una tecla

                        // Refrescar la pantalla
                        dibujarInterfazCompleta();
                    }
                    else {
                        // Mostrar mensaje de error
                        gotoXY(5, 25);
                        SetConsoleColor(4, 0); // Rojo sobre negro
                        cout << "Error en la inscripción. Es posible que ya estés inscrito.";
                        SetConsoleColor(15, 0); // Restaurar color
                        _getch(); // Esperar una tecla

                        // Refrescar la pantalla
                        dibujarInterfazCompleta();
                    }
                }
                else {
                    // El usuario no ha iniciado sesión, mostrar mensaje
                    gotoXY(5, 25);
                    SetConsoleColor(4, 0); // Rojo sobre negro
                    cout << "Necesitas iniciar sesión para inscribirte.";
                    SetConsoleColor(15, 0); // Restaurar color
                    _getch(); // Esperar una tecla

                    // Redirigir a la pantalla de login
                    res.accion = AccionPantalla::IR_A_LOGIN;
                    return res;
                }
                break;
            case 13: // Enter
                // Aquí se implementaría la lógica para mostrar el contenido de la clase seleccionada
                // Por ahora, simplemente volvemos a la pantalla anterior
                //res.accion = pantallaAnterior;
                //return res;

            case 27: // ESC
                res.accion = pantallaAnterior;
                res.tipoUsuario = tipoUsuario; // Ensure we keep the user type
                return res;
            }
        }

        return res;
    }
};
