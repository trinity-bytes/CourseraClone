// filepath: Headers/Screens/ExplorarCursosScreen.h
// Descripcion: Pantalla que permite a los usuarios explorar, navegar y seleccionar
//              cursos y especializaciones disponibles en el sistema.

#ifndef SCREENS_EXPLORARCURSOSSCREEN_H
#define SCREENS_EXPLORARCURSOSSCREEN_H

// 1. Includes del sistema
#include <iostream>
#include <string>
#include <vector>
#include <algorithm> // Para std::min y std::max
#include <conio.h>   // Para _getch()

// 2. Includes del proyecto
#include "../Entities/Curso.h"
#include "../Entities/Especializacion.h"
#include "../Controllers/GestionadorCursos.h"
#include "../Utils/ScreenSystem.h"
#include "../Utils/SystemUtils.h"
#include "../Utils/UI_Ascii.h"

// 3. Forward declarations
class Controladora;

// 4. Constantes y tipos (reemplazan "magic numbers")
enum KeyCode {
    KEY_ENTER = 13,
    KEY_ESCAPE = 27,
    KEY_UP = 72,
    KEY_DOWN = 80,
    KEY_PAGE_UP = 33, // El código original usaba 33 y 34 para PageUp/Down
    KEY_PAGE_DOWN = 34,
    KEY_EXTEND = 224,
    KEY_NULL = 0
};

// Clase para explorar el contenido del sistema.
// Simplificada de ExplorarCursosYEspecialidadesScreen a ExplorarCursosScreen.
class ExplorarCursosScreen : public PantallaBase {
private:
    // --- Atributos de Configuración y Constantes ---

    // Secciones de la pantalla
    static const int SECCION_CURSOS = 0;
    static const int SECCION_ESPECIALIDADES = 1;
    static const int TOTAL_SECCIONES = 2;

    // Coordenadas para la UI
    struct Coords {
        const int tituloCol = 50, tituloFila = 3;
        const int cursosTituloCol = 7, cursosTituloFila = 7;
        const int cursosListaCol = 7, cursosListaFila = 9;
        const int espTituloCol = 7, espTituloFila = 20;
        const int espListaCol = 7, espListaFila = 22;
        const int anchoElemento = 60;
    } _uiCoords;

    // --- Atributos de Estado ---

    int _seccionActual;
    int _elementoActual;
    int _seccionAnterior;
    int _elementoAnterior;
    int _indicesInicio[TOTAL_SECCIONES]; // 0 para cursos, 1 para especialidades
    bool _necesitaRedibujarTodo;

    // Paginación
    const int _itemsPorPaginaCursos = 5;
    const int _itemsPorPaginaEspecialidades = 5;

    // Datos del usuario actual
    TipoUsuario _tipoUsuario;
    int _idUsuario;
    std::string _nombreUsuario;

    // --- Referencias ---
    Controladora* _controladora; // Sigue la convención de prefijo _

    // --- Métodos Privados de Renderizado ---

    // Dibuja el marco estático de la pantalla una sola vez
    void dibujarInterfazEstatica() {
        system("cls");
        UI_ExplorarCursosAndEspecialidades(); // Asumiendo que esta es una función de UI_Ascii.h

        gotoXY(_uiCoords.tituloCol, _uiCoords.tituloFila);
        setConsoleColor(15, 0);
        std::cout << "EXPLORAR CURSOS Y ESPECIALIDADES";
    }

    // Función genérica para renderizar una lista de items (cursos o especialidades)
    template <typename T>
    void renderizarSeccion(const LinkedList<T*>& items, int seccionId, const std::string& tituloSeccion, int xTitulo, int yTitulo, int xLista, int yLista, int itemsPorPagina) {
        // Limpiar área de la lista y los indicadores de paginación
        for (int i = 0; i < itemsPorPagina; i++) {
            gotoXY(xLista, yLista + i * 2);
            std::cout << std::string(_uiCoords.anchoElemento + 30, ' ');
        }

        // Título de la sección
        gotoXY(xTitulo, yTitulo);
        setConsoleColor(14, 0); // Amarillo
        std::cout << tituloSeccion;

        // Dibujar lista de items
        int totalItems = items.getTamano();
        int& indiceInicio = _indicesInicio[seccionId];
        int itemsAMostrar = std::min(itemsPorPagina, totalItems - indiceInicio);

        for (int i = 0; i < itemsAMostrar; i++) {
            int indiceAbsoluto = indiceInicio + i;
            T* item = items.get(indiceAbsoluto + 1);

            gotoXY(xLista, yLista + i * 2);

            bool estaSeleccionado = (_seccionActual == seccionId && _elementoActual == i);
            setConsoleColor(estaSeleccionado ? 1 : 15, estaSeleccionado ? 13 : 1); // Color de selección o normal

            std::string texto = std::to_string(item->getId()) + ": " + item->getTitulo();
            if (texto.length() > _uiCoords.anchoElemento) {
                texto = texto.substr(0, _uiCoords.anchoElemento - 3) + "...";
            }
            std::cout << texto;
        }

        // Indicadores de paginación
        setConsoleColor(15, 0);
        if (indiceInicio > 0) {
            gotoXY(xLista + _uiCoords.anchoElemento + 5, yLista);
            std::cout << "Mas arriba (ARRIBA)";
        }
        if (indiceInicio + itemsPorPagina < totalItems) {
            gotoXY(xLista + _uiCoords.anchoElemento + 5, yLista + (itemsAMostrar - 1) * 2);
            std::cout << "Mas abajo (ABAJO)";
        }
    }

    // Función genérica para actualizar solo el item que cambió de estado (seleccionado/deseleccionado)
    template<typename T>
    void actualizarElemento(int indiceLocal, int seccionId, const LinkedList<T*>& items, int x, int y, bool seleccionado) {
        int indiceAbsoluto = _indicesInicio[seccionId] + indiceLocal;
        if (indiceLocal < 0 || indiceAbsoluto >= items.getTamano()) return;

        T* item = items.get(indiceAbsoluto + 1);
        gotoXY(x, y + indiceLocal * 2);

        setConsoleColor(seleccionado ? 1 : 15, seleccionado ? 13 : 1);

        std::string texto = std::to_string(item->getId()) + ": " + item->getTitulo();
        if (texto.length() > _uiCoords.anchoElemento) {
            texto = texto.substr(0, _uiCoords.anchoElemento - 3) + "...";
        }
        std::cout << texto;
    }

    void actualizarInterfaz() {
        if (_necesitaRedibujarTodo) {
            dibujarInterfazEstatica();
            renderizarSeccion(_controladora->getGestionadorCursos().getCursos(), SECCION_CURSOS, "CURSOS DISPONIBLES", _uiCoords.cursosTituloCol, _uiCoords.cursosTituloFila, _uiCoords.cursosListaCol, _uiCoords.cursosListaFila, _itemsPorPaginaCursos);
            renderizarSeccion(_controladora->getGestionadorCursos().getEspecializaciones(), SECCION_ESPECIALIDADES, "ESPECIALIZACIONES DISPONIBLES", _uiCoords.espTituloCol, _uiCoords.espTituloFila, _uiCoords.espListaCol, _uiCoords.espListaFila, _itemsPorPaginaEspecialidades);
            _necesitaRedibujarTodo = false;
            return;
        }

        // Optimización: Solo redibuja los elementos que cambiaron
        if (_seccionAnterior != -1 && (_seccionActual != _seccionAnterior || _elementoActual != _elementoAnterior)) {
            if (_seccionAnterior == SECCION_CURSOS) {
                actualizarElemento<Curso>(_elementoAnterior, SECCION_CURSOS, _controladora->getGestionadorCursos().getCursos(), _uiCoords.cursosListaCol, _uiCoords.cursosListaFila, false);
            }
            else {
                actualizarElemento<Especializacion>(_elementoAnterior, SECCION_ESPECIALIDADES, _controladora->getGestionadorCursos().getEspecializaciones(), _uiCoords.espListaCol, _uiCoords.espListaFila, false);
            }
        }

        if (_seccionActual == SECCION_CURSOS) {
            actualizarElemento<Curso>(_elementoActual, SECCION_CURSOS, _controladora->getGestionadorCursos().getCursos(), _uiCoords.cursosListaCol, _uiCoords.cursosListaFila, true);
        }
        else {
            actualizarElemento<Especializacion>(_elementoActual, SECCION_ESPECIALIDADES, _controladora->getGestionadorCursos().getEspecializaciones(), _uiCoords.espListaCol, _uiCoords.espListaFila, true);
        }
    }


    // --- Métodos Privados de Lógica ---

    void manejarEntrada(int tecla) {
        _seccionAnterior = _seccionActual;
        _elementoAnterior = _elementoActual;
        int* indiceInicio = &_indicesInicio[_seccionActual];
        int totalItems, itemsPorPagina;

        if (_seccionActual == SECCION_CURSOS) {
            totalItems = _controladora->getGestionadorCursos().getCursos().getTamano();
            itemsPorPagina = _itemsPorPaginaCursos;
        }
        else {
            totalItems = _controladora->getGestionadorCursos().getEspecializaciones().getTamano();
            itemsPorPagina = _itemsPorPaginaEspecialidades;
        }
        int itemsEnPantalla = std::min(itemsPorPagina, totalItems - *indiceInicio);

        switch (tecla) {
        case KEY_UP:
            if (_elementoActual > 0) _elementoActual--;
            else if (*indiceInicio > 0) { // Scroll hacia arriba
                (*indiceInicio)--;
                _necesitaRedibujarTodo = true;
            }
            else if (_seccionActual == SECCION_ESPECIALIDADES) { // Cambiar a sección de cursos
                _seccionActual = SECCION_CURSOS;
                int totalCursos = _controladora->getGestionadorCursos().getCursos().getTamano();
                _elementoActual = std::min(_itemsPorPaginaCursos, totalCursos - _indicesInicio[SECCION_CURSOS]) - 1;
                _necesitaRedibujarTodo = true;
            }
            break;

        case KEY_DOWN:
            if (_elementoActual < itemsEnPantalla - 1) _elementoActual++;
            else if (*indiceInicio + itemsPorPagina < totalItems) { // Scroll hacia abajo
                (*indiceInicio)++;
                _necesitaRedibujarTodo = true;
            }
            else if (_seccionActual == SECCION_CURSOS) { // Cambiar a sección de especialidades
                _seccionActual = SECCION_ESPECIALIDADES;
                _elementoActual = 0;
                _necesitaRedibujarTodo = true;
            }
            break;

            // NOTE: PageUp/PageDown no estaban en el código original, pero se incluyen por completitud
            // case KEY_PAGE_UP: ...
            // case KEY_PAGE_DOWN: ...
        }
    }

    ResultadoPantalla procesarSeleccion() {
        if (_seccionActual == SECCION_CURSOS) {
            int indiceAbsoluto = _indicesInicio[SECCION_CURSOS] + _elementoActual;
            auto& cursos = _controladora->getGestionadorCursos().getCursos();
            if (indiceAbsoluto < cursos.getTamano()) {
                auto resultado = crearResultado(AccionPantalla::IR_A_MOSTRAR_CURSO, _tipoUsuario);
                resultado.idCursoSeleccionado = cursos.get(indiceAbsoluto + 1)->getId();
                return resultado;
            }
        }
        else { // SECCION_ESPECIALIDADES
            int indiceAbsoluto = _indicesInicio[SECCION_ESPECIALIDADES] + _elementoActual;
            auto& especializaciones = _controladora->getGestionadorCursos().getEspecializaciones();
            if (indiceAbsoluto < especializaciones.getTamano()) {
                auto resultado = crearResultado(AccionPantalla::IR_A_MOSTRAR_ESPECIALIZACION, _tipoUsuario);
                resultado.idCursoSeleccionado = especializaciones.get(indiceAbsoluto + 1)->getId();
                return resultado;
            }
        }
        return crearResultado(AccionPantalla::NINGUNA, _tipoUsuario); // No se seleccionó nada válido
    }


public:
    // Constructor corregido para evitar shadowing de parámetros
    ExplorarCursosScreen(Controladora* controladora, TipoUsuario tipoUsuario, int idUsuario, const std::string& nombreUsuario)
        : PantallaBase(controladora),
        _controladora(controladora),
        _tipoUsuario(tipoUsuario),
        _idUsuario(idUsuario),
        _nombreUsuario(nombreUsuario),
        _seccionActual(SECCION_CURSOS),
        _elementoActual(0),
        _seccionAnterior(-1),
        _elementoAnterior(-1),
        _necesitaRedibujarTodo(true)
    {
        for (int i = 0; i < TOTAL_SECCIONES; i++) {
            _indicesInicio[i] = 0;
        }
    }

    ResultadoPantalla ejecutar() override {
        while (true) {
            actualizarInterfaz();
            _seccionAnterior = -1; // Reset para evitar redibujo innecesario

            int tecla = _getch();

            if (tecla == KEY_EXTEND || tecla == KEY_NULL) {
                tecla = _getch();
                manejarEntrada(tecla);
            }
            else if (tecla == KEY_ENTER) {
                return procesarSeleccion();
            }
            else if (tecla == KEY_ESCAPE) {
                AccionPantalla accionDestino = (_tipoUsuario == TipoUsuario::ESTUDIANTE)
                    ? AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE
                    : AccionPantalla::IR_A_DASHBOARD_ORGANIZACION;
                return crearResultado(accionDestino, _tipoUsuario);
            }
        }
    }
};

#endif // SCREENS_EXPLORARCURSOSSCREEN_H