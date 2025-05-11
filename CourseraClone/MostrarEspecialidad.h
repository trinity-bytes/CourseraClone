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
    std::vector<Curso*> cursos;

    // Estado de navegaci�n
    int cursoSeleccionadoFila;
    int cursoSeleccionadoColumna;
    bool primeraRenderizacion;
    AccionPantalla pantallaAnterior;

    // Constantes para las coordenadas
    const int COL_TITULO_ESPECIALIZACION = 7;
    const int FILA_TITULO_ESPECIALIZACION = 7;

    const int COL_DESC_ESPECIALIZACION = 7;
    const int FILA_DESC_ESPECIALIZACION = 11;

    // Constantes para la cuadr�cula de cursos
    const int COL_INICIO_CUADRICULA = 30;
    const int FILA_INICIO_CUADRICULA = 20;
    const int ANCHO_CELDA = 40;
    const int ALTO_CELDA = 10;
    const int ESPACIO_ENTRE_CELDAS = 5;
    const int FILAS_CUADRICULA = 2;
    const int COLUMNAS_CUADRICULA = 2;
    const int MAX_CURSOS = FILAS_CUADRICULA * COLUMNAS_CUADRICULA; // 4 cursos en total (2x2)

    const int LONGITUD_TITULO_CURSO_CELDA = 30;
    const int LONGITUD_DESCRIPCION_CURSO_CELDA = 35;
    const int LONGITUD_TITULO_ESPECIALIZACION = 40;

    // M�todo para truncar t�tulos largos
    std::string truncarTitulo(const std::string& titulo, int maxLongitud) {
        if (titulo.length() <= maxLongitud) {
            return titulo;
        }
        return titulo.substr(0, maxLongitud - 3) + "...";
    }

    std::vector<std::string> dividirTituloEnLineas(const std::string& titulo, int maxLongitudPorLinea, int maxLineas = 3) {
        std::vector<std::string> lineas;
        if (titulo.empty()) {
            return lineas;
        }

        std::string textoRestante = titulo;

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
            std::string& lastLine = lineas.back();
            if (lastLine.length() > 3) {
                lastLine = lastLine.substr(0, lastLine.length() - 3) + "...";
            }
        }

        return lineas;
    }

    // M�todo para formatear descripci�n
    std::string formatearDescripcion(const std::string& texto, int anchoMax, int altoMax) {
        std::string resultado;
        std::string textoRestante = texto;

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
        UI_VistaEspecialidad(); // Asumimos que existe esta funci�n en UI_Ascii.h

        // Mostrar t�tulo de la especializaci�n
        gotoXY(COL_TITULO_ESPECIALIZACION, FILA_TITULO_ESPECIALIZACION);
        SetConsoleColor(15, 1);
        const int INDENTACION_TITULO = COL_TITULO_ESPECIALIZACION + 16; // "Especialidad en: " tiene 16 caracteres
        std::vector<std::string> tituloEspecializacion = dividirTituloEnLineas(especializacion->getTitulo(), LONGITUD_TITULO_ESPECIALIZACION);
        std::cout << "Especialidad en: ";
        if (!tituloEspecializacion.empty()) {
            std::cout << tituloEspecializacion[0];

            // Display the rest of the lines with proper indentation
            for (size_t i = 1; i < tituloEspecializacion.size(); ++i) {
                gotoXY(INDENTACION_TITULO, FILA_TITULO_ESPECIALIZACION + i);
                std::cout << tituloEspecializacion[i];
            }
        }

        // Mostrar descripci�n de la especializaci�n
        gotoXY(COL_DESC_ESPECIALIZACION, FILA_DESC_ESPECIALIZACION);
        SetConsoleColor(15, 1);
        std::cout << "Descripcion de la especializacion:";
        gotoXY(COL_DESC_ESPECIALIZACION, FILA_DESC_ESPECIALIZACION + 2);

        // Formatear y mostrar descripci�n
        std::string descripcionFormateada = formatearDescripcion(especializacion->getDescripcion(), 40, 5);
        std::istringstream descStream(descripcionFormateada);
        std::string linea;
        int fila = FILA_DESC_ESPECIALIZACION + 2;
        while (std::getline(descStream, linea)) {
            gotoXY(COL_DESC_ESPECIALIZACION, fila++);
            std::cout << linea;
        }

        // Mostrar los cursos en la cuadr�cula
        for (int i = 0; i < FILAS_CUADRICULA; i++) {
            for (int j = 0; j < COLUMNAS_CUADRICULA; j++) {
                int indice = i * COLUMNAS_CUADRICULA + j;
                if (indice < cursos.size()) {
                    dibujarCursoCelda(i, j, cursos[indice], i == cursoSeleccionadoFila && j == cursoSeleccionadoColumna);
                }
            }
        }
    }

    void dibujarCursoCelda(int fila, int columna, Curso* curso, bool seleccionado) {
        int x = COL_INICIO_CUADRICULA + columna * (ANCHO_CELDA + ESPACIO_ENTRE_CELDAS);
        int y = FILA_INICIO_CUADRICULA + fila * (ALTO_CELDA + ESPACIO_ENTRE_CELDAS);

        // Dibujar el borde de la celda
        if (seleccionado) {
            SetConsoleColor(1, 13); // Color para selecci�n
        }
        else {
            SetConsoleColor(15, 1); // Color normal
        }

        // Dibujar t�tulo del curso
        gotoXY(x + 2, y + 1);
        std::string tituloCurso = truncarTitulo(curso->getTitulo(), LONGITUD_TITULO_CURSO_CELDA);
        std::cout << tituloCurso;

        // Dibujar descripci�n del curso
        std::string descripcionCurso = formatearDescripcion(curso->getDescripcion(), LONGITUD_DESCRIPCION_CURSO_CELDA, 3);
        std::istringstream descStream(descripcionCurso);
        std::string linea;
        int lineaY = y + 3;
        while (std::getline(descStream, linea)) {
            gotoXY(x + 2, lineaY++);
            std::cout << linea;
        }

        // Dibujar instructor
        gotoXY(x + 2, y + ALTO_CELDA - 2);
        std::cout << "Instructor: " << curso->getInstructor();

        SetConsoleColor(15, 1); // Restaurar color normal
    }

public:
    MostrarEspecialidad(int _idEspecializacion, GestionadorCursos* _gestionadorCursos, Especializacion* _especializacion = nullptr, AccionPantalla _pantallaAnterior = AccionPantalla::IR_A_LANDING_PAGE)
        : idEspecializacion(_idEspecializacion),
        gestionadorCursos(_gestionadorCursos),
        especializacion(_especializacion),
        cursoSeleccionadoFila(0),
        cursoSeleccionadoColumna(0),
        primeraRenderizacion(true),
        pantallaAnterior(_pantallaAnterior)
    {
        // Si no se proporcion� una especializaci�n, intentar cargarla por ID
        if (especializacion == nullptr) {
            especializacion = gestionadorCursos->obtenerEspecializacionPorId(idEspecializacion);
        }

        // Cargar los cursos de la especializaci�n
        if (especializacion != nullptr) {
            LinkedList<Curso*> cursosLista = especializacion->getIdsCursos(gestionadorCursos->getCursos());

            // Convertir la lista a un vector para facilitar el acceso
            for (int i = 0; i < cursosLista.getTamano(); i++) {
                if (i < MAX_CURSOS) {
                    Curso* curso = cursosLista.get(i);  
                    if (curso != nullptr) {
                        cursos.push_back(curso);
                    }
                    else {
                        std::cerr << "Error: Curso nulo en la posici�n " << i << " de la lista." << std::endl;
                    }
                }
            }
        }
    }

    ~MostrarEspecialidad() {
        // Liberar memoria si es necesario
        // Cuidado con los punteros que podr�an ser utilizados en otras partes
    }

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
                    if (cursoSeleccionadoFila > 0) {
                        dibujarCursoCelda(cursoSeleccionadoFila, cursoSeleccionadoColumna,
                            cursos[cursoSeleccionadoFila * COLUMNAS_CUADRICULA + cursoSeleccionadoColumna], false);
                        cursoSeleccionadoFila--;
                        dibujarCursoCelda(cursoSeleccionadoFila, cursoSeleccionadoColumna,
                            cursos[cursoSeleccionadoFila * COLUMNAS_CUADRICULA + cursoSeleccionadoColumna], true);
                    }
                    break;

                case 80: // Flecha abajo
                    if (cursoSeleccionadoFila < FILAS_CUADRICULA - 1 &&
                        (cursoSeleccionadoFila + 1) * COLUMNAS_CUADRICULA + cursoSeleccionadoColumna < cursos.size()) {
                        dibujarCursoCelda(cursoSeleccionadoFila, cursoSeleccionadoColumna,
                            cursos[cursoSeleccionadoFila * COLUMNAS_CUADRICULA + cursoSeleccionadoColumna], false);
                        cursoSeleccionadoFila++;
                        dibujarCursoCelda(cursoSeleccionadoFila, cursoSeleccionadoColumna,
                            cursos[cursoSeleccionadoFila * COLUMNAS_CUADRICULA + cursoSeleccionadoColumna], true);
                    }
                    break;

                case 75: // Flecha izquierda
                    if (cursoSeleccionadoColumna > 0) {
                        dibujarCursoCelda(cursoSeleccionadoFila, cursoSeleccionadoColumna,
                            cursos[cursoSeleccionadoFila * COLUMNAS_CUADRICULA + cursoSeleccionadoColumna], false);
                        cursoSeleccionadoColumna--;
                        dibujarCursoCelda(cursoSeleccionadoFila, cursoSeleccionadoColumna,
                            cursos[cursoSeleccionadoFila * COLUMNAS_CUADRICULA + cursoSeleccionadoColumna], true);
                    }
                    break;

                case 77: // Flecha derecha
                    if (cursoSeleccionadoColumna < COLUMNAS_CUADRICULA - 1 &&
                        cursoSeleccionadoFila * COLUMNAS_CUADRICULA + cursoSeleccionadoColumna + 1 < cursos.size()) {
                        dibujarCursoCelda(cursoSeleccionadoFila, cursoSeleccionadoColumna,
                            cursos[cursoSeleccionadoFila * COLUMNAS_CUADRICULA + cursoSeleccionadoColumna], false);
                        cursoSeleccionadoColumna++;
                        dibujarCursoCelda(cursoSeleccionadoFila, cursoSeleccionadoColumna,
                            cursos[cursoSeleccionadoFila * COLUMNAS_CUADRICULA + cursoSeleccionadoColumna], true);
                    }
                    break;
                }
                break;

            case 13: // Enter - seleccionar curso
            {
                int indice = cursoSeleccionadoFila * COLUMNAS_CUADRICULA + cursoSeleccionadoColumna;
                if (indice < cursos.size()) {
                    // Configurar resultado para ir a la pantalla MostrarCurso con el curso seleccionado
                    res.idCursoSeleccionado = cursos[indice]->getId();
                    res.accion = AccionPantalla::IR_A_MOSTRAR_CURSO;
                    res.accionAnterior = AccionPantalla::IR_A_MOSTRAR_ESPECIALIZACION;
                    return res;
                }
            }
            break;

            case 27: // ESC - volver a la pantalla anterior
                res.accion = pantallaAnterior;
                return res;
            }
        }

        return res;
    }
};
