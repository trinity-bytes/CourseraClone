#pragma once

#include "Pantalla.h"
#include "ExtendedFunctions.h"
#include "UI_Ascii.h"
#include "Curso.h"
#include "Clase.h"
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
    std::vector<Clase> clases;

    // Estado de navegación
    int claseSeleccionada;
    bool primeraRenderizacion;
    AccionPantalla pantallaAnterior;

    // Constantes para las coordenadas
    const int COL_TITULO_CURSO = 15;
    const int FILA_TITULO_CURSO = 17;

    const int COL_DESC_CURSO = 15;
    const int FILA_DESC_CURSO = 25;

    const int COL_MODULOS = 55;
    const int FILA_MODULOS_BASE = 25;
    const int ESPACIO_ENTRE_MODULOS = 7;

    const int MAX_MODULOS_VISIBLES = 5;
    const int LONGITUD_TEXTO_MODULO = 40;

    // Método para truncar títulos largos
    std::string truncarTitulo(const std::string& titulo, int maxLongitud) {
        if (titulo.length() <= maxLongitud) {
            return titulo;
        }
        return titulo.substr(0, maxLongitud - 3) + "...";
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
        std::cout << "Curso de: " << curso->getTitulo();

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
    MostrarCurso(int _idCurso, Curso* _curso = nullptr, AccionPantalla _pantallaAnterior = AccionPantalla::IR_A_LANDING_PAGE)
        : idCurso(_idCurso),
        curso(_curso),
        claseSeleccionada(0),
        primeraRenderizacion(true),
        pantallaAnterior(_pantallaAnterior)
    {
        // Si no se proporcionó un curso, intentar cargarlo por ID
        if (curso == nullptr) {
            // Aquí deberíamos cargar el curso desde el GestionadorCursos
            // Por ahora, creamos un curso de ejemplo
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
                //clases.push_back(clasesLista[i]);
                Clase nuevaClase("Módulo " + std::to_string(i + 1), "Contenido del módulo");
                clases.push_back(nuevaClase);
            }

            // Si no hay clases, crear algunas de ejemplo
            if (clases.empty()) {
                for (int i = 1; i <= 5; i++) {
                    clases.emplace_back("Módulo " + std::to_string(i) + ": " + curso->getTitulo(),
                        "Contenido del módulo " + std::to_string(i));
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
