#pragma once

#include "Pantalla.h"
#include "PriorityQueue.h"

class Controladora; // Declaración anticipada de la clase Controladora

class LandingPage : public PantallaBase {
private:
    // Constantes del menú
    static const int SECCION_CABECERA = 0;
    static const int SECCION_ESPECIALIDADES = 1;
    static const int SECCION_CURSOS = 2;
    static const int TOTAL_SECCIONES = 3;

    // Items max visibles por seccion
    static const int MAX_ELEMENTOS_CABECERA = 3;
    static const int MAX_ELEMENTOS_ESPECIALIDAD = 3;
    static const int MAX_ELEMENTOS_CURSO = 3;

    // Caracteres maximos por cuadro
    static const int MAX_ANCHO_CARACTERES_CUADRO = 30;
    static const int MAX_ALTO_CARACTERES_CUADRO = 4;

    // Elementos del menú
    const std::vector<std::string> ELEMENTOS_CABECERA = {
        " Iniciar Sesion ",
        " Registrarse ",
        " Sobre Nosotros "
    };

    // Datos por defecto
    std::vector<ElementoMenu> especialidadesDefecto = {
        {"Desarrollo Web", "Frontend & Backend"},
        {"Ciencia de Datos", "Analisis y ML"},
        {"Marketing Digital", "SEO, SEM & Ads"}
    };

    std::vector<ElementoMenu> cursosDefecto = {
        {"Curso C++ CLI", "Interaccion consola"},
        {"Curso Python DS", "Data science intro"},
        {"Curso React JS", "Web UI development"}
    };

    // Estado actual
    int seccionActual;
    int elementoActual;
    int seccionAnterior;
    int elementoAnterior;

    // Datos del menú
    std::vector<ElementoMenu> especialidades;
    std::vector<ElementoMenu> cursos;

    // Coordenadas para dibujar
    COORD coordsElementosCabecera[MAX_ELEMENTOS_CABECERA] = { {67, 3}, {84, 3}, {98, 3} };
    COORD coordsTituloEspecialidad[MAX_ELEMENTOS_ESPECIALIDAD] = { {11, 15}, {45, 15}, {79, 15} };
    COORD coordsDescEspecialidad[MAX_ELEMENTOS_ESPECIALIDAD] = { {11, 17}, {45, 17}, {79, 17} };
    COORD coordsTituloCurso[MAX_ELEMENTOS_CURSO] = { {11, 25}, {45, 25}, {79, 25} };
    COORD coordsDescCurso[MAX_ELEMENTOS_CURSO] = { {11, 27}, {45, 27}, {79, 27} };

    void actualizarSeleccion() {
        if (seccionActual != seccionAnterior) {
            switch (seccionAnterior) {
                case SECCION_CABECERA:
                    actualizarElementoCabecera(elementoAnterior, false);
                    break;
                case SECCION_ESPECIALIDADES:
                    actualizarElementoEspecialidad(elementoAnterior, false);
                    break;
                case SECCION_CURSOS:
                    actualizarElementoCurso(elementoAnterior, false);
                    break;
            }

            switch (seccionActual) {
                case SECCION_CABECERA:
                    actualizarElementoCabecera(elementoActual, true);
                    break;
                case SECCION_ESPECIALIDADES:
                    actualizarElementoEspecialidad(elementoActual, true);
                    break;
                case SECCION_CURSOS:
                    actualizarElementoCurso(elementoActual, true);
                    break;
            }
        }
        else if (elementoActual != elementoAnterior) {
            switch (seccionActual) {
                case SECCION_CABECERA:
                    actualizarElementoCabecera(elementoAnterior, false);
                    actualizarElementoCabecera(elementoActual, true);
                    break;
                case SECCION_ESPECIALIDADES:
                    actualizarElementoEspecialidad(elementoAnterior, false);
                    actualizarElementoEspecialidad(elementoActual, true);
                    break;
                case SECCION_CURSOS:
                    actualizarElementoCurso(elementoAnterior, false);
                    actualizarElementoCurso(elementoActual, true);
                    break;
            }
        }

        seccionAnterior = seccionActual;
        elementoAnterior = elementoActual;
    }

    void actualizarElementoCabecera(int indice, bool seleccionado) {
        if (indice < 0 || indice >= MAX_ELEMENTOS_CABECERA) return;

        gotoXY(coordsElementosCabecera[indice].X, coordsElementosCabecera[indice].Y);

        if (seleccionado) SetConsoleColor(1, 4);
        else SetConsoleColor(15, 1);

        std::cout << ELEMENTOS_CABECERA[indice];
        SetConsoleColor(15, 1);
    }

    void actualizarElementoEspecialidad(int indice, bool seleccionado) {
        if (indice < 0 || indice >= especialidades.size()) return;

        actualizarElementoGenerico(
            coordsTituloEspecialidad[indice],
            coordsDescEspecialidad[indice],
            especialidades[indice],
            seleccionado
        );
    }

    void actualizarElementoCurso(int indice, bool seleccionado) {
        if (indice < 0 || indice >= cursos.size()) return;

        actualizarElementoGenerico(
            coordsTituloCurso[indice],
            coordsDescCurso[indice],
            cursos[indice],
            seleccionado
        );
    }

    void actualizarElementoGenerico(const COORD& coordTitulo,
        const COORD& coordDesc, const ElementoMenu& elemento,
        bool seleccionado) {
        
        gotoXY(coordTitulo.X, coordTitulo.Y);
        std::cout << std::string(20, ' ');
        gotoXY(coordTitulo.X, coordTitulo.Y);

        if (seleccionado) SetConsoleColor(1, 13);
        else SetConsoleColor(15, 1);

        std::cout << elemento.titulo;
        SetConsoleColor(15, 1);

        std::string descFormateada = formatearDescripcion(
            elemento.descripcion,
            MAX_ANCHO_CARACTERES_CUADRO,
            MAX_ALTO_CARACTERES_CUADRO
        );

        std::vector<std::string> lineas;
        std::stringstream ss(descFormateada);
        std::string linea;

        while (std::getline(ss, linea, '\n')) {
            lineas.push_back(linea);
        }

        for (size_t i = 0; i < lineas.size(); ++i) {
            gotoXY(coordDesc.X, coordDesc.Y + i);
            std::cout << std::string(30, ' ');
            gotoXY(coordDesc.X, coordDesc.Y + i);
            std::cout << lineas[i];
        }

        for (size_t i = lineas.size(); i < MAX_ALTO_CARACTERES_CUADRO; ++i) {
            gotoXY(coordDesc.X, coordDesc.Y + i);
            std::cout << std::string(30, ' ');
        }
    }

    void dibujarInterfazCompleta() {
        // Cabecera
        for (int i = 0; i < MAX_ELEMENTOS_CABECERA; ++i) {
            actualizarElementoCabecera(i, seccionActual == SECCION_CABECERA && elementoActual == i);
        }

        // Especialidades
        for (size_t i = 0; i < especialidades.size() && i < MAX_ELEMENTOS_ESPECIALIDAD; ++i) {
            actualizarElementoEspecialidad(i, seccionActual == SECCION_ESPECIALIDADES && elementoActual == i);
        }

        // Cursos
        for (size_t i = 0; i < cursos.size() && i < MAX_ELEMENTOS_CURSO; ++i) {
            actualizarElementoCurso(i, seccionActual == SECCION_CURSOS && elementoActual == i);
        }

        gotoXY(0, ALTO_CONSOLA - 1);
    }

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

    void cargarDatos() {
        // TODO: Implementar carga de datos desde la controladora
        especialidades = especialidadesDefecto;
        cursos = cursosDefecto;
    }

public:
    LandingPage(Controladora* ctrl) 
        : PantallaBase(ctrl),
          seccionActual(0), elementoActual(0),
          seccionAnterior(-1), elementoAnterior(-1) {
        cargarDatos();
    }

    void renderizar() override {
        if (primeraRenderizacion) {
            limpiarPantalla();
            UI_LandingPage();
            dibujarInterfazCompleta();
            primeraRenderizacion = false;
        }
        else {
            actualizarSeleccion();
        }
    }

    void manejarInput(int tecla) override {
        if (tecla == 224) { // Tecla extendida
            tecla = _getch();
            switch (tecla) {
                case 72: // Flecha arriba
                    seccionActual--;
                    if (seccionActual < 0) seccionActual = 0;
                    elementoActual = 0;
                    break;
                case 80: // Flecha abajo
                    seccionActual++;
                    if (seccionActual >= TOTAL_SECCIONES)
                        seccionActual = TOTAL_SECCIONES - 1;
                    elementoActual = 0;
                    break;
                case 75: // Flecha izquierda
                    elementoActual--;
                    if (elementoActual < 0) elementoActual = 0;
                    break;
                case 77: // Flecha derecha
                    elementoActual++;
                    int maxElementos = obtenerMaxElementosEnSeccion(seccionActual);
                    if (elementoActual >= maxElementos)
                        elementoActual = maxElementos > 0 ? maxElementos - 1 : 0;
                    break;
            }
            actualizarSeleccion();
        }
        else if (tecla == 13) { // Enter
            switch (seccionActual) {
                case SECCION_CABECERA:
                    if (elementoActual == 0) { // Iniciar Sesión
                        // TODO: Cambiar a pantalla de login
                    }
                    break;
                case SECCION_ESPECIALIDADES:
                    // TODO: Navegar a detalle de especialidad
                    break;
                case SECCION_CURSOS:
                    // TODO: Navegar a detalle de curso
                    break;
            }
        }
    }

    Pantalla getSiguientePantalla() override {
        if (seccionActual == SECCION_CABECERA && elementoActual == 0) {
            return Pantalla::LOGIN;
        }
        return pantallaActual;
    }

private:
    int obtenerMaxElementosEnSeccion(int seccion) {
        switch (seccion) {
            case SECCION_CABECERA: return MAX_ELEMENTOS_CABECERA;
            //case SECCION_ESPECIALIDADES: return std::min(static_cast<int>(especialidades.size()), MAX_ELEMENTOS_ESPECIALIDAD);
            //case SECCION_CURSOS: return std::min(static_cast<int>(cursos.size()), MAX_ELEMENTOS_CURSO);
            default: return 0;
        }
    }
}; 