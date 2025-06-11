#ifndef COURSERACLONE_SCREENS_MOSTRARCURSOSCREEN_HPP
#define COURSERACLONE_SCREENS_MOSTRARCURSOSCREEN_HPP

// Headers estándar
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

// Headers propios
#include "../Utils/ScreenSystem.hpp"
#include "../Utils/SystemUtils.hpp"
#include "../Utils/UI_Ascii.hpp"
#include "../Entities/Curso.hpp"
#include "../Entities/Clase.hpp"
#include "../Controllers/GestionadorCursos.hpp"
#include "../Entities/Estudiante.hpp"

// Pantalla que muestra los detalles de un curso específico
class MostrarCursoScreen : public PantallaBase
{
private:
    // Datos del curso
    int _idCurso;
    Curso* _curso;
    GestionadorCursos& _gestionadorCursos;
    Estudiante& _estudiante;
    std::vector<Clase> _clases;
    TipoUsuario _tipoUsuario;

    // Estado de navegación
    int _claseSeleccionada;
    bool _primeraRenderizacion;
    AccionPantalla _pantallaAnterior;

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
	const int LONGITUD_TITULO_CURSO = 30;    // Método para truncar títulos largos
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
        gotoXY(50, 3);
        system("cls");
        UI_VistaCurso();        // Mostrar título del curso
        gotoXY(COL_TITULO_CURSO, FILA_TITULO_CURSO);
        const int INDENTACION_TITULO = COL_TITULO_CURSO + 10;
        std::vector<std::string> tituloCurso = dividirTituloEnLineas(_curso->getTitulo(), LONGITUD_TITULO_CURSO);
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

        std::cout << "Descripcion del contenido del curso:";
        gotoXY(COL_DESC_CURSO, FILA_DESC_CURSO + 2);

        // Formatear y mostrar descripción
        std::string descripcionFormateada = formatearDescripcion(_curso->getDescripcion(), 40, 5);
        std::istringstream descStream(descripcionFormateada);
        std::string linea;
        int fila = FILA_DESC_CURSO + 2;
        while (std::getline(descStream, linea)) {
            gotoXY(COL_DESC_CURSO, fila++);
            std::cout << linea;
        }

        // Mostrar clases del curso
        int numClases = (_clases.size() < MAX_MODULOS_VISIBLES) ? _clases.size() : MAX_MODULOS_VISIBLES;
        for (int i = 0; i < numClases; i++) {
            dibujarClase(i, i == _claseSeleccionada);
        }

        // Muestra la opcion de inscripcion solo a estudiantes
        if (_tipoUsuario == TipoUsuario::ESTUDIANTE) {
            gotoXY(50, 3);
            setConsoleColor(0, 13);
            std::cout << "Presiona 'I' para inscribirte a este curso";
        }
        else if (_tipoUsuario == TipoUsuario::EMPRESA) {
            gotoXY(50, 3);
            setConsoleColor(8, 13); // Color gris para indicar deshabilitado
            std::cout << "Solo estudiantes pueden inscribirse a cursos";
        }
        setConsoleColor(15, 0);
    }    void dibujarClase(int indice, bool seleccionada) {
        if (indice < 0 || indice >= _clases.size()) return;

        // Posición para el número del módulo
        gotoXY(COL_MODULOS, FILA_MODULOS_BASE + indice * ESPACIO_ENTRE_MODULOS);

        if (seleccionada)
            setConsoleColor(1, 13); // Color para selección
        else
            setConsoleColor(15, 0); // Color normal

        // Mostrar número de clase
        std::cout << indice + 1;

        // Posición para el título de la clase
        gotoXY(COL_MODULOS + 5, FILA_MODULOS_BASE + indice * ESPACIO_ENTRE_MODULOS);

        // Truncar y mostrar título
        std::string tituloClase = truncarTitulo(_clases[indice].getTitulo(), LONGITUD_TEXTO_MODULO);
        std::cout << tituloClase;

        setConsoleColor(15, 0);
    }

public:
    MostrarCursoScreen(int idCurso, GestionadorCursos& gestionadorCursos, Estudiante& estudiante,
        Curso* curso, AccionPantalla pantallaAnterior = AccionPantalla::IR_A_LANDING_PAGE,
        TipoUsuario tipoUsuario = TipoUsuario::ESTUDIANTE)
        : PantallaBase(),
        _idCurso(idCurso),
        _gestionadorCursos(gestionadorCursos),
        _estudiante(estudiante),
        _curso(curso),
        _claseSeleccionada(0),
        _primeraRenderizacion(true),
        _pantallaAnterior(pantallaAnterior),
        _tipoUsuario(tipoUsuario)
    {
        // Si no se proporcionó un curso, intentar cargarlo por ID
        /*
        if (_curso.getTitulo() == "" && _gestionadorCursos != nullptr) {
            _curso = _gestionadorCursos->obtenerCurso(_idCurso);
        }
        else if (_curso == nullptr) {
            // Si no hay gestionador, crear un curso de ejemplo
            _curso = new Curso(_idCurso, 1, "Empresa",
                "Curso " + std::to_string(_idCurso),
                "Esta es la descripción detallada del curso. Incluye información sobre lo que aprenderán los estudiantes, los requisitos previos y los resultados esperados al finalizar el curso.",
                "Instructor", 5);
        }
        */

        // Cargar las clases del curso
        if (_curso) {
            // Intentar obtener las clases del curso
            const LinkedList<Clase>& clasesLista = _curso->getClases();
            int tamano = _curso->getCantidadClases();

            // Si el curso tiene clases, convertir la lista a un vector para facilitar el acceso
            for (int i = 1; i <= tamano; i++) {
                Clase clase = _curso->getClases().get(i); // Usar get() en lugar de []
                _clases.push_back(clase);
            }

            // Si no hay clases, crear algunas de ejemplo
            if (_clases.empty()) {
                for (int i = 1; i <= 5; i++) {
                    _clases.emplace_back("Clase " + std::to_string(i) + ": " + _curso->getTitulo(),
                        "Contenido de la clase" + std::to_string(i));
                }
            }
        }
    }

    ~MostrarCursoScreen() = default;    ResultadoPantalla ejecutar() override {
        ResultadoPantalla res;

        if (_primeraRenderizacion) {
            dibujarInterfazCompleta();
            _primeraRenderizacion = false;
        }

        while (true) {
            int tecla = _getch();

            switch (tecla) {
            case 224: // Tecla extendida
                tecla = _getch();

                switch (tecla) {
                case 72: // Flecha arriba
                    if (_claseSeleccionada > 0) {
                        dibujarClase(_claseSeleccionada, false);
                        _claseSeleccionada--;
                        dibujarClase(_claseSeleccionada, true);
                    }
                    break;

                case 80: // Flecha abajo
                    if (_claseSeleccionada < _clases.size() - 1 && _claseSeleccionada < MAX_MODULOS_VISIBLES - 1) {
                        dibujarClase(_claseSeleccionada, false);
                        _claseSeleccionada++;
                        dibujarClase(_claseSeleccionada, true);
                    }
                    break;
                }
                break;
            case 'i': // Inscribirse al curso
            case 'I':

                if (_tipoUsuario == TipoUsuario::EMPRESA) {
                    gotoXY(5, 25);
                    setConsoleColor(4, 0); // Rojo sobre negro
                    std::cout << "Las organizaciones no pueden inscribirse a cursos.";
                    setConsoleColor(15, 0); // Restaurar color
                    _getch(); // Esperar una tecla
                    dibujarInterfazCompleta();
                    break;
                }

                if (_estudiante.getNombreCompleto() != "") {
                    if (_estudiante.inscribirseACurso(_curso)) { // Usar el método de estudiante
                        // Mostrar mensaje de éxito
                        gotoXY(5, 25);
                        setConsoleColor(2, 0); // Verde sobre negro
                        std::cout << "Inscripción exitosa!";
                        setConsoleColor(15, 0); // Restaurar color
                        _getch(); // Esperar una tecla

                        // Refrescar la pantalla
                        dibujarInterfazCompleta();
                    }
                    else {
                        // Mostrar mensaje de error
                        gotoXY(5, 25);
                        setConsoleColor(4, 0); // Rojo sobre negro
                        std::cout << "Error en la inscripción. Es posible que ya estés inscrito.";
                        setConsoleColor(15, 0); // Restaurar color
                        _getch(); // Esperar una tecla

                        // Refrescar la pantalla
                        dibujarInterfazCompleta();
                    }
                }
                else {
                    // El usuario no ha iniciado sesión, mostrar mensaje
                    gotoXY(5, 25);
                    setConsoleColor(4, 0); // Rojo sobre negro
                    std::cout << "Necesitas iniciar sesión para inscribirte.";
                    setConsoleColor(15, 0); // Restaurar color
                    _getch(); // Esperar una tecla

                    // Redirigir a la pantalla de login
                    res.accion = AccionPantalla::IR_A_LOGIN;
                    return res;
                }
                break;
            case 13: // Enter
                // Aquí se implementaría la lógica para mostrar el contenido de la clase seleccionada
                // Por ahora, simplemente volvemos a la pantalla anterior
                //res.accion = _pantallaAnterior;
                //return res;

            case 27: // ESC
                res.accion = _pantallaAnterior;
                res.tipoUsuario = _tipoUsuario; // Ensure we keep the user type
                return res;
            }
        }        return res;
    }
};

#endif // COURSERACLONE_SCREENS_MOSTRARCURSOSCREEN_HPP
