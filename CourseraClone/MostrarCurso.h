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
#include <algorithm> // Para std::min
#include <sstream>   // Para std::istringstream

class MostrarCurso : public PantallaBase
{
private:
    // Datos del curso
    int idCurso;
    Curso* curso;
    GestionadorCursos* gestionadorCursos; // Añadir
    Estudiante* estudiante;
    std::vector<Clase> clases;

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

    // Método para formatear descripción
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
        UI_VistaCurso();

        // Mostrar título del curso
        gotoXY(COL_TITULO_CURSO, FILA_TITULO_CURSO);
        SetConsoleColor(15, 1);
        const int INDENTACION_TITULO = COL_TITULO_CURSO + 10;
		std::vector<std::string> tituloCurso = dividirTituloEnLineas(curso->getTitulo(), LONGITUD_TITULO_CURSO);
        std::cout << "Curso de: ";
        if (!tituloCurso.empty()) {
            std::cout << tituloCurso[0];

            // Display the rest of the lines with proper indentation
            for (size_t i = 1; i < tituloCurso.size(); ++i) {
                gotoXY(INDENTACION_TITULO, FILA_TITULO_CURSO + i);
                std::cout << tituloCurso[i];
            }
        }

        // Mostrar descripción del curso
        gotoXY(COL_DESC_CURSO, FILA_DESC_CURSO);
        SetConsoleColor(15, 1);
        std::cout << "Descripcion del contenido del curso:";
        gotoXY(COL_DESC_CURSO, FILA_DESC_CURSO + 2);

        // Formatear y mostrar descripción
        std::string descripcionFormateada = formatearDescripcion(curso->getDescripcion(), 40, 5);
        std::istringstream descStream(descripcionFormateada);
        std::string linea;
        int fila = FILA_DESC_CURSO + 2;
        while (std::getline(descStream, linea)) {
            gotoXY(COL_DESC_CURSO, fila++);
            std::cout << linea;
        }

        // Mostrar clases del curso
        int numClases = (clases.size() < MAX_MODULOS_VISIBLES) ? clases.size() : MAX_MODULOS_VISIBLES;
        for (int i = 0; i < numClases; i++) {
            dibujarClase(i, i == claseSeleccionada);
        }

        gotoXY(5, 30);
        SetConsoleColor(15, 1);
        std::cout << "Presiona 'I' para inscribirte a este curso";
    }

    void dibujarClase(int indice, bool seleccionada) {
        if (indice < 0 || indice >= clases.size()) return;

        // Posición para el número del módulo
        gotoXY(COL_MODULOS, FILA_MODULOS_BASE + indice * ESPACIO_ENTRE_MODULOS);

        if (seleccionada)
            SetConsoleColor(1, 13); // Color para selección
        else
            SetConsoleColor(15, 1); // Color normal

        // Mostrar número de clase
        std::cout << indice + 1;

        // Posición para el título de la clase
        gotoXY(COL_MODULOS + 5, FILA_MODULOS_BASE + indice * ESPACIO_ENTRE_MODULOS);

        // Truncar y mostrar título
        std::string tituloClase = truncarTitulo(clases[indice].getTitulo(), LONGITUD_TEXTO_MODULO);
        std::cout << tituloClase;

        SetConsoleColor(15, 1);
    }

public:
    MostrarCurso(int _idCurso, GestionadorCursos* _gestionadorCursos = nullptr, Estudiante* _estudiante = nullptr, Curso* _curso = nullptr, AccionPantalla _pantallaAnterior = AccionPantalla::IR_A_LANDING_PAGE)
        : idCurso(_idCurso),
        gestionadorCursos(_gestionadorCursos),
        estudiante(_estudiante),
        curso(_curso),
        claseSeleccionada(0),
        primeraRenderizacion(true),
        pantallaAnterior(_pantallaAnterior)
    {
        // Si no se proporcionó un curso, intentar cargarlo por ID
        if (curso == nullptr && gestionadorCursos != nullptr) {
            curso = gestionadorCursos->obtenerCursoPorId(idCurso);
        }
        else if (curso == nullptr) {
            // Si no hay gestionador, crear un curso de ejemplo
            curso = new Curso(idCurso, 1, "Empresa",
                "Curso " + std::to_string(idCurso),
                "Esta es la descripción detallada del curso. Incluye información sobre lo que aprenderán los estudiantes, los requisitos previos y los resultados esperados al finalizar el curso.",
                "Instructor", 5);
        }

        // Cargar las clases del curso
        if (curso != nullptr) {
            // Intentar obtener las clases del curso
            LinkedList<Clase> clasesLista = curso->getClases();

            // Si el curso tiene clases, convertir la lista a un vector para facilitar el acceso
            for (int i = 0; i < clasesLista.getTamano(); i++) {
                Clase clase = clasesLista.get(i); // Usar get() en lugar de []
                clases.push_back(clase);
            }

            // Si no hay clases, crear algunas de ejemplo
            if (clases.empty()) {
                for (int i = 1; i <= 5; i++) {
                    clases.emplace_back("Clase " + std::to_string(i) + ": " + curso->getTitulo(),
                        "Contenido de la clase" + std::to_string(i));
                }
            }
        }
    }

    ~MostrarCurso() {
        // Si creamos el curso internamente, liberamos la memoria
        // Comprobar si el curso se creó aquí y no fue proporcionado externamente
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
                if (estudiante != nullptr) {
                    if (estudiante->inscribirseACurso(curso)) { // Usar el método de estudiante
                        // Mostrar mensaje de éxito
                        gotoXY(5, 25);
                        SetConsoleColor(2, 0); // Verde sobre negro
                        std::cout << "¡Inscripción exitosa!";
                        SetConsoleColor(15, 0); // Restaurar color
                        _getch(); // Esperar una tecla

                        // Refrescar la pantalla
                        dibujarInterfazCompleta();
                    }
                    else {
                        // Mostrar mensaje de error
                        gotoXY(5, 25);
                        SetConsoleColor(4, 0); // Rojo sobre negro
                        std::cout << "Error en la inscripción. Es posible que ya estés inscrito.";
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
                    std::cout << "Necesitas iniciar sesión para inscribirte.";
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
                res.accion = pantallaAnterior;
                return res;

            case 27: // ESC
                res.accion = pantallaAnterior;
                return res;
            }
        }

        return res;
    }
};
