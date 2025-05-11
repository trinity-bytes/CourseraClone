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

    // Estado de navegaci�n
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

    // M�todo para truncar t�tulos largos
    std::string truncarTitulo(const std::string& titulo, int maxLongitud) {
        if (titulo.length() <= maxLongitud) {
            return titulo;
        }
        return titulo.substr(0, maxLongitud - 3) + "...";
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
        UI_VistaCurso();

        // Mostrar t�tulo del curso
        gotoXY(COL_TITULO_CURSO, FILA_TITULO_CURSO);
        SetConsoleColor(15, 1);
        std::cout << "Curso de: " << curso->getTitulo();

        // Mostrar descripci�n del curso
        gotoXY(COL_DESC_CURSO, FILA_DESC_CURSO);
        SetConsoleColor(15, 1);
        std::cout << "Descripcion del contenido del curso:";
        gotoXY(COL_DESC_CURSO, FILA_DESC_CURSO + 2);

        // Formatear y mostrar descripci�n
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

        // Posici�n para el n�mero del m�dulo
        gotoXY(COL_MODULOS, FILA_MODULOS_BASE + indice * ESPACIO_ENTRE_MODULOS);

        if (seleccionada)
            SetConsoleColor(1, 13); // Color para selecci�n
        else
            SetConsoleColor(15, 1); // Color normal

        // Mostrar n�mero de clase
        std::cout << indice + 1;

        // Posici�n para el t�tulo de la clase
        gotoXY(COL_MODULOS + 5, FILA_MODULOS_BASE + indice * ESPACIO_ENTRE_MODULOS);

        // Truncar y mostrar t�tulo
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
        // Si no se proporcion� un curso, intentar cargarlo por ID
        if (curso == nullptr) {
            // Aqu� deber�amos cargar el curso desde el GestionadorCursos
            // Por ahora, creamos un curso de ejemplo
            curso = new Curso(idCurso, 1, "Empresa",
                "Curso " + std::to_string(idCurso),
                "Esta es la descripci�n detallada del curso. Incluye informaci�n sobre lo que aprender�n los estudiantes, los requisitos previos y los resultados esperados al finalizar el curso.",
                "Instructor", 5);
        }

        // Cargar las clases del curso
        if (curso != nullptr) {
            // Intentar obtener las clases del curso
            LinkedList<Clase> clasesLista = curso->getClases();

            // Si el curso tiene clases, convertir la lista a un vector para facilitar el acceso
            for (int i = 0; i < clasesLista.getTamano(); i++) {
                //clases.push_back(clasesLista[i]);
                Clase nuevaClase("M�dulo " + std::to_string(i + 1), "Contenido del m�dulo");
                clases.push_back(nuevaClase);
            }

            // Si no hay clases, crear algunas de ejemplo
            if (clases.empty()) {
                for (int i = 1; i <= 5; i++) {
                    clases.emplace_back("M�dulo " + std::to_string(i) + ": " + curso->getTitulo(),
                        "Contenido del m�dulo " + std::to_string(i));
                }
            }
        }
    }

    ~MostrarCurso() {
        // Si creamos el curso internamente, liberamos la memoria
        // Comprobar si el curso se cre� aqu� y no fue proporcionado externamente
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
                // Aqu� se implementar�a la l�gica para mostrar el contenido de la clase seleccionada
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
