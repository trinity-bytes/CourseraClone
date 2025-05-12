#pragma once

#include "Pantalla.h"
#include "ExtendedFunctions.h"
#include "UI_Ascii.h"
#include "Especializacion.h"
#include "GestionadorCursos.h"
#include "Curso.h"
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

class MostrarEspecialidad : public PantallaBase
{
private:
    // Datos de la especialidad
    int idEspecializacion;
    Especializacion* especializacion;
	GestionadorCursos* gestionadorCursos;

    TipoUsuario tipoUsuario;
    Estudiante* estudiante;

    vector<Curso*> cursos;

    bool primeraRenderizacion;
    AccionPantalla pantallaAnterior;

    // Constantes para las coordenadas
    const int COL_TITULO_ESPECIALIZACION = 7;
    const int FILA_TITULO_ESPECIALIZACION = 7;

    const int COL_DESC_ESPECIALIZACION = 7;
    const int FILA_DESC_ESPECIALIZACION = 11;

    // Constantes para la cuadrícula de cursos
    const int COL_INICIO_CUADRICULA = 38;
    const int FILA_INICIO_CUADRICULA = 9;
    const int ANCHO_CELDA = 35;
    const int ALTO_CELDA = 9;
    const int ESPACIO_ENTRE_CELDAS = 0;
    const int FILAS_CUADRICULA = 2;
    const int COLUMNAS_CUADRICULA = 2;
    const int MAX_CURSOS = FILAS_CUADRICULA * COLUMNAS_CUADRICULA; // 4 cursos en total (2x2)

    const int LONGITUD_DESCRIPCION_ESPECIALIDAD = 30;
    const int LONGITUD_TITULO_CURSO_CELDA = 35;
    const int LONGITUD_DESCRIPCION_CURSO_CELDA = 34;
    const int LONGITUD_TITULO_ESPECIALIZACION = 40;

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
        system("cls");
        UI_VistaEspecialidad();

        // Mostrar título de la especialización
        gotoXY(COL_TITULO_ESPECIALIZACION, FILA_TITULO_ESPECIALIZACION);
        
        cout << especializacion->getTitulo();


        // Mostrar descripción de la especialización
        gotoXY(COL_DESC_ESPECIALIZACION, FILA_DESC_ESPECIALIZACION);
        
        cout << "Descripcion:";
        gotoXY(COL_DESC_ESPECIALIZACION, FILA_DESC_ESPECIALIZACION + 2);

        // Formatear y mostrar descripción
        string descripcionFormateada = formatearDescripcion(especializacion->getDescripcion(), LONGITUD_DESCRIPCION_ESPECIALIDAD, 12);
        istringstream descStream(descripcionFormateada);
        string linea;
        int fila = FILA_DESC_ESPECIALIZACION + 2;
        while (getline(descStream, linea)) {
            gotoXY(COL_DESC_ESPECIALIZACION, fila++);
            cout << linea;
        }
        SetConsoleColor(15, 0);

        // Mostrar los cursos en la cuadrícula
        for (int i = 0; i < FILAS_CUADRICULA; i++) {
            for (int j = 0; j < COLUMNAS_CUADRICULA; j++) {
                int indice = i * COLUMNAS_CUADRICULA + j;
                if (indice < cursos.size()) {
                    dibujarCursoCelda(i, j, cursos[indice]);
                }
            }
        }

        // Mostrar opción de inscripción según el tipo de usuario
        if (tipoUsuario == TipoUsuario::ESTUDIANTE) {
            gotoXY(50, 3);
            SetConsoleColor(0, 15);
            cout << "Presiona 'I' para inscribirte a esta especializacion";
        }
        else if (tipoUsuario == TipoUsuario::EMPRESA) {
            gotoXY(50, 3);
            SetConsoleColor(8, 13); // Color gris para indicar deshabilitado
            cout << "Solo estudiantes pueden inscribirse a especializaciones";
        }
        SetConsoleColor(15, 0);
    }

    void dibujarCursoCelda(int fila, int columna, Curso* curso) {
        int x = COL_INICIO_CUADRICULA + columna * (ANCHO_CELDA + ESPACIO_ENTRE_CELDAS);
        int y = FILA_INICIO_CUADRICULA + fila * (ALTO_CELDA + ESPACIO_ENTRE_CELDAS);

        SetConsoleColor(15, 0); // Color normal

        // Dibujar título del curso
        gotoXY(x + 2, y + 1);
        string tituloCurso = truncarTitulo(curso->getTitulo(), LONGITUD_TITULO_CURSO_CELDA);
        cout << tituloCurso;

        // Dibujar descripción del curso
        string descripcionCurso = formatearDescripcion(curso->getDescripcion(), LONGITUD_DESCRIPCION_CURSO_CELDA, 3);
        istringstream descStream(descripcionCurso);
        string linea;
        int lineaY = y + 3;
        while (getline(descStream, linea)) {
            gotoXY(x + 2, lineaY++);
            cout << linea;
        }

        // Dibujar instructor
        gotoXY(x + 2, y + ALTO_CELDA - 2);
        cout << "Instructor: " << curso->getInstructor();

        SetConsoleColor(15, 0); // Restaurar color normal
    }

public:
    MostrarEspecialidad(int _idEspecializacion, GestionadorCursos* _gestionadorCursos,
        Especializacion* _especializacion, AccionPantalla _pantallaAnterior,
        TipoUsuario _tipoUsuario = TipoUsuario::ESTUDIANTE,
        Estudiante* _estudiante = nullptr)
        : idEspecializacion(_idEspecializacion),
        gestionadorCursos(_gestionadorCursos),
        especializacion(_especializacion),
        primeraRenderizacion(true),
        pantallaAnterior(_pantallaAnterior),
        tipoUsuario(_tipoUsuario),
        estudiante(_estudiante)
    {
        // Si no se proporcionó una especialización, intentar cargarla por ID
        if (especializacion == nullptr) {
            especializacion = gestionadorCursos->obtenerEspecializacionPorId(idEspecializacion);
        }

        // Si todavía no tenemos una especialización, crear una de ejemplo para que la UI no esté vacía
        if (especializacion == nullptr) {
            especializacion = new Especializacion(
                idEspecializacion, 1, "Empresa",
                "Especialización " + to_string(idEspecializacion),
                0, "Esta especialización no pudo ser cargada correctamente.");
        }

        // Intentar cargar los cursos de la especialización
        vector<int> idsCursosEsp = especializacion->getIdsCursosVector();

        // Verificar si tenemos IDs de cursos asociados
        bool tieneCursosAsociados = !idsCursosEsp.empty();

        // Primero, intentar cargar cursos desde el gestionador si hay IDs asociados
        if (tieneCursosAsociados && gestionadorCursos) {
            for (int idCurso : idsCursosEsp) {
                Curso* curso = gestionadorCursos->obtenerCursoPorId(idCurso);
                if (curso) {
                    cursos.push_back(curso);
                }
            }
        }

        // Si no se encontraron cursos, crear cursos de ejemplo basados en la especialización
        if (cursos.empty()) {
            string tituloBase = especializacion->getTitulo();
            if (tituloBase.length() > 15) {
                tituloBase = tituloBase.substr(0, 12) + "...";
            }

            // Crear 4 cursos de ejemplo relacionados con la especialización
            for (int i = 1; i <= MAX_CURSOS; i++) {
                string titulo = "Curso Ejemplo ";
                string descripcion = "Este curso es de ejemplo.";

                // Diferentes instructores para diversidad
                string instructor = "Profesor: UwU*";

                Curso* cursoDemo = new Curso(1000 + i,
                    especializacion->getIdEmpresa(),
                    especializacion->getNombreEmpresa(),
                    titulo,
                    descripcion,
                    instructor,
                    5);
                cursos.push_back(cursoDemo);
            }
        }
    }

    ~MostrarEspecialidad() {}

    ResultadoPantalla ejecutar() override {
        ResultadoPantalla res;

        if (primeraRenderizacion) {
            dibujarInterfazCompleta();
            primeraRenderizacion = false;
        }

        while (true) {
            int tecla = _getch();

            switch (tecla) {
            
            case 'i': // Inscribirse a la especialización
            case 'I':
                if (tipoUsuario == TipoUsuario::EMPRESA) {
                    gotoXY(5, 25);
                    SetConsoleColor(4, 0);
                    cout << "Las organizaciones no pueden inscribirse a especializaciones.";
                    SetConsoleColor(15, 0);
                    _getch();
                    dibujarInterfazCompleta();
                    break;
                }

                if (estudiante == nullptr) {
                    // El usuario no ha iniciado sesión, mostrar mensaje
                    gotoXY(5, 25);
                    SetConsoleColor(4, 0);
                    cout << "Necesitas iniciar sesion para inscribirte.";
                    SetConsoleColor(15, 0);
                    _getch();

                    // Redirigir a la pantalla de login
                    res.accion = AccionPantalla::IR_A_LOGIN;
                    res.accionAnterior = AccionPantalla::IR_A_MOSTRAR_ESPECIALIZACION;
                    res.idCursoSeleccionado = idEspecializacion;
                    res.tipoUsuario = TipoUsuario::ESTUDIANTE; // Important to set the user type
                    return res;
                }

                if (estudiante->inscribirseAEspecializacion(especializacion)) {
                    // Mostrar mensaje de éxito
                    gotoXY(5, 25);
                    SetConsoleColor(2, 0);
                    cout << "¡Inscripcion exitosa a la especializacion!";
                    SetConsoleColor(15, 0);
                    _getch();
                    dibujarInterfazCompleta();
                }
                else {
                    // Mostrar mensaje de error
                    gotoXY(5, 25);
                    SetConsoleColor(4, 0);
                    cout << "Error en la inscripcion. Es posible que ya estes inscrito.";
                    SetConsoleColor(15, 0);
                    _getch();
                    dibujarInterfazCompleta();
                }
                break;

            case 27: // ESC - volver a la pantalla anterior
                res.accion = pantallaAnterior;
                res.tipoUsuario = tipoUsuario; // Ensure user type persists
                return res;
            }
        }

        return res;
    }
};
