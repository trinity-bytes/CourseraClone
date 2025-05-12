#pragma once

#include "Pantalla.h"
#include "ExtendedFunctions.h"
#include "UI_Ascii.h"
#include "Curso.h"
#include "Especializacion.h"
#include "GestionadorCursos.h"
#include <vector>
#include <string>
#include <iostream>
#include <conio.h>
#include <algorithm>

using namespace std;

class ExplorarCursosYEspecialidades : public PantallaBase
{
private:
    // Secciones de la pantalla
    static const int SECCION_CURSOS = 1;      // Lista de cursos
    static const int SECCION_ESPECIALIDADES = 2; // Lista de especialidades
    static const int TOTAL_SECCIONES = 3;

    int ultimoElementoSeleccionadoPorSeccion[TOTAL_SECCIONES];

    // Estado actual
    int seccionActual;
    int elementoActual;
    int indiceInicioCursos;
    int indiceInicioEspecialidades;
    int cursosPorPagina;
    int especialidadesPorPagina;
	int seccionAnterior;
	int elementoAnterior;
    bool primeraRenderizacion;
    bool necesitaRerenderizarCursos;
    bool necesitaRerenderizarEspecialidades;

    TipoUsuario tipoUsuario;

    // Datos
    GestionadorCursos* gestionadorCursos;
    LinkedList<Curso*>& cursos;
    LinkedList<Especializacion*>& especialidades;

    // Coordenadas para la interfaz
    const int COL_TITULO = 50;
    const int FILA_TITULO = 3;

    const int COL_TITULO_CURSOS = 7;
    const int FILA_TITULO_CURSOS = 7;
    const int COL_LISTA_CURSOS = 7;
    const int FILA_LISTA_CURSOS = 9;

    const int COL_TITULO_ESPECIALIDADES = 7;
    const int FILA_TITULO_ESPECIALIDADES = 20;
    const int COL_LISTA_ESPECIALIDADES = 7;
    const int FILA_LISTA_ESPECIALIDADES = 22;

    const int ANCHO_ELEMENTO = 60;

    void dibujarInterfazCompleta() {
        system("cls");
        UI_ExplorarCursosAndEspecialidades();

        // Dibujar título
        gotoXY(COL_TITULO, FILA_TITULO);
        SetConsoleColor(15, 1);
        cout << "EXPLORAR CURSOS Y ESPECIALIDADES";

        // Dibujar secciones
        SetConsoleColor(15, 1);
        renderizarCursos();
        renderizarEspecialidades();

        necesitaRerenderizarCursos = false;
        necesitaRerenderizarEspecialidades = false;
    }

    void renderizarCursos() 
    {
        limpiarAreaCursos();
        limpiarAreaIndicadoresCursos();

        // Título de sección cursos
        gotoXY(COL_TITULO_CURSOS, FILA_TITULO_CURSOS);
        SetConsoleColor(14, 1);  // Amarillo sobre azul
        cout << "CURSOS DISPONIBLES";
        SetConsoleColor(15, 1);  // Blanco sobre azul

        // Dibujar lista de cursos
        int totalCursos = cursos.getTamano();
        int cursosAMostrar = min(cursosPorPagina, totalCursos - indiceInicioCursos);

        // Primero limpiamos toda el área de cursos
        limpiarAreaCursos();

        for (int i = 0; i < cursosAMostrar; i++) {
            int indice = indiceInicioCursos + i;
            Curso* curso = cursos.get(indice);

            gotoXY(COL_LISTA_CURSOS, FILA_LISTA_CURSOS + i * 2);

            if (seccionActual == SECCION_CURSOS && elementoActual == i) {
                SetConsoleColor(1, 13); // Color para selección
            }
            else {
                SetConsoleColor(15, 1); // Color normal
            }

            // Mostrar ID y título del curso
            string titulo = to_string(curso->getId()) + ": " + curso->getTitulo();
            if (titulo.length() > ANCHO_ELEMENTO) {
                titulo = titulo.substr(0, ANCHO_ELEMENTO - 3) + "...";
            }
            cout << titulo;
        }

        // Indicadores de paginación para cursos
        // Limpiar indicadores anteriores
        limpiarAreaIndicadoresCursos();

        if (indiceInicioCursos > 0) {
            gotoXY(COL_LISTA_CURSOS + ANCHO_ELEMENTO + 5, FILA_LISTA_CURSOS);
            SetConsoleColor(15, 1);
            cout << "Mas arriba (Flecha ARRIBA)";
        }

        if (indiceInicioCursos + cursosPorPagina < totalCursos) {
            gotoXY(COL_LISTA_CURSOS + ANCHO_ELEMENTO + 5, FILA_LISTA_CURSOS + (cursosAMostrar * 2) - 2);
            SetConsoleColor(15, 1);
            cout << "Mas abajo (Flecha ABAJO)";
        }

        SetConsoleColor(15, 1); // Restaurar color normal
        necesitaRerenderizarCursos = false;
    }

    void renderizarEspecialidades() 
    {
        // Convertir LinkedList a vector
        vector<Especializacion*> especialidadesVector;
        for (int i = 0; i < especialidades.getTamano(); ++i) {
            especialidadesVector.push_back(especialidades.get(i));
        }

        // Aplicar Bubble Sort al vector
        bubbleSort(especialidadesVector);
        for (Especializacion* especializacion :especialidadesVector){
            especialidades.agregarAlFinal(especializacion); 
        }

        limpiarAreaEspecialidades();
        limpiarAreaIndicadoresEspecialidades();

        // Título de sección especialidades
        gotoXY(COL_TITULO_ESPECIALIDADES, FILA_TITULO_ESPECIALIDADES);
        SetConsoleColor(14, 1);  // Amarillo sobre azul
        cout << "ESPECIALIZACIONES DISPONIBLES";
        SetConsoleColor(15, 1);  // Blanco sobre azul

        // Dibujar lista de especialidades
        int totalEspecialidades = especialidades.getTamano();
        int especialidadesAMostrar = min(especialidadesPorPagina, totalEspecialidades - indiceInicioEspecialidades);

        // Primero limpiamos toda el área de especialidades
        limpiarAreaEspecialidades();

        for (int i = 0; i < especialidadesAMostrar; i++) {
            int indice = indiceInicioEspecialidades + i;
            Especializacion* especializacion = especialidades.get(indice);

            gotoXY(COL_LISTA_ESPECIALIDADES, FILA_LISTA_ESPECIALIDADES + i * 2);

            if (seccionActual == SECCION_ESPECIALIDADES && elementoActual == i) {
                SetConsoleColor(1, 13); // Color para selección
            }
            else {
                SetConsoleColor(15, 1); // Color normal
            }

            // Mostrar ID y título de la especialización
            string titulo = to_string(especializacion->getId()) + ": " + especializacion->getTitulo();
            if (titulo.length() > ANCHO_ELEMENTO) {
                titulo = titulo.substr(0, ANCHO_ELEMENTO - 3) + "...";
            }
            cout << titulo;
        }

        // Indicadores de paginación para especialidades
        // Limpiar indicadores anteriores
        limpiarAreaIndicadoresEspecialidades();

        if (indiceInicioEspecialidades > 0) {
            gotoXY(COL_LISTA_ESPECIALIDADES + ANCHO_ELEMENTO + 5, FILA_LISTA_ESPECIALIDADES);
            SetConsoleColor(15, 1);
            cout << "Mas arriba (Flecha ARRIBA)";
        }

        if (indiceInicioEspecialidades + especialidadesPorPagina < totalEspecialidades) {
            gotoXY(COL_LISTA_ESPECIALIDADES + ANCHO_ELEMENTO + 5, FILA_LISTA_ESPECIALIDADES + (especialidadesAMostrar * 2) - 2);
            SetConsoleColor(15, 1);
            cout << "Ms abajo Flecha ABAJO)";
        }

        SetConsoleColor(15, 1); // Restaurar color normal
        necesitaRerenderizarEspecialidades = false;
    }

    // Métodos para limpieza de áreas
    void limpiarAreaCursos() {
        // Limpiar toda el área donde se muestran los cursos
        for (int i = 0; i < cursosPorPagina; i++) {
            gotoXY(COL_LISTA_CURSOS, FILA_LISTA_CURSOS + i * 2);
            cout << string(ANCHO_ELEMENTO + 20, ' '); // El +20 es para asegurar limpieza completa
        }
    }

    void limpiarAreaIndicadoresCursos() {
        // Limpiar área de indicadores de paginación para cursos
        gotoXY(COL_LISTA_CURSOS + ANCHO_ELEMENTO + 5, FILA_LISTA_CURSOS);
        cout << string(26, ' '); // Espacio para "▲ Más arriba"

        gotoXY(COL_LISTA_CURSOS + ANCHO_ELEMENTO + 5, FILA_LISTA_CURSOS + (cursosPorPagina * 2) - 2);
        cout << string(26, ' '); // Espacio para "▼ Más abajo"
    }

    void limpiarAreaEspecialidades() {
        // Limpiar toda el área donde se muestran las especialidades
        for (int i = 0; i < especialidadesPorPagina; i++) {
            gotoXY(COL_LISTA_ESPECIALIDADES, FILA_LISTA_ESPECIALIDADES + i * 2);
            cout << string(ANCHO_ELEMENTO + 20, ' '); // El +20 es para asegurar limpieza completa
        }
    }

    void limpiarAreaIndicadoresEspecialidades() {
        // Limpiar área de indicadores de paginación para especialidades
        gotoXY(COL_LISTA_ESPECIALIDADES + ANCHO_ELEMENTO + 5, FILA_LISTA_ESPECIALIDADES);
        cout << string(26, ' '); // Espacio para "▲ Más arriba"

        gotoXY(COL_LISTA_ESPECIALIDADES + ANCHO_ELEMENTO + 5, FILA_LISTA_ESPECIALIDADES + (especialidadesPorPagina * 2) - 2);
        cout << string(26, ' '); // Espacio para "▼ Más abajo"
    }

    void actualizarInterfaz() {
        // Si necesitamos rerenderizar alguna sección completa, lo hacemos primero
        if (necesitaRerenderizarCursos) {
            renderizarCursos();
        }
        if (necesitaRerenderizarEspecialidades) {
            renderizarEspecialidades();
        }

        // Limpiamos la selección anterior
        if (seccionAnterior >= 0 && seccionAnterior < TOTAL_SECCIONES) {
            switch (seccionAnterior) 
            {
            case SECCION_CURSOS:
                // Solo si estamos en la misma página, limpiamos el elemento anterior
                if (seccionActual != SECCION_CURSOS || elementoActual != elementoAnterior) {
                    limpiarYRedibujarElementoCurso(elementoAnterior);
                }
                break;

            case SECCION_ESPECIALIDADES:
                // Solo si estamos en la misma página, limpiamos el elemento anterior
                if (seccionActual != SECCION_ESPECIALIDADES || elementoActual != elementoAnterior) {
                    limpiarYRedibujarElementoEspecializacion(elementoAnterior);
                }
                break;
            }
        }

        // Dibujamos la nueva selección
        switch (seccionActual) 
        {
        case SECCION_CURSOS:
            dibujarElementoCursoSeleccionado(elementoActual);
            break;

        case SECCION_ESPECIALIDADES:
            dibujarElementoEspecializacionSeleccionado(elementoActual);
            break;
        }

        // Actualizar registros de selección
        elementoAnterior = elementoActual;
        seccionAnterior = seccionActual;
    }

    void limpiarYRedibujarElementoCurso(int indice) {
        if (indice >= 0 && indice < cursosPorPagina &&
            indiceInicioCursos + indice < cursos.getTamano()) {

            int x = COL_LISTA_CURSOS;
            int y = FILA_LISTA_CURSOS + indice * 2;

            // Limpiar la línea completa
            gotoXY(x, y);
            cout << string(ANCHO_ELEMENTO, ' ');

            // Redibujar con color normal
            Curso* curso = cursos.get(indiceInicioCursos + indice);
            gotoXY(x, y);
            SetConsoleColor(15, 1); // Color normal
            string titulo = to_string(curso->getId()) + ": " + curso->getTitulo();
            if (titulo.length() > ANCHO_ELEMENTO) {
                titulo = titulo.substr(0, ANCHO_ELEMENTO - 3) + "...";
            }
            cout << titulo;
        }
    }

    void limpiarYRedibujarElementoEspecializacion(int indice) {
        if (indice >= 0 && indice < especialidadesPorPagina &&
            indiceInicioEspecialidades + indice < especialidades.getTamano()) {

            int x = COL_LISTA_ESPECIALIDADES;
            int y = FILA_LISTA_ESPECIALIDADES + indice * 2;

            // Limpiar la línea completa
            gotoXY(x, y);
            cout << string(ANCHO_ELEMENTO, ' ');

            // Redibujar con color normal
            Especializacion* especializacion = especialidades.get(indiceInicioEspecialidades + indice);
            gotoXY(x, y);
            SetConsoleColor(15, 1); // Color normal
            string titulo = to_string(especializacion->getId()) + ": " + especializacion->getTitulo();
            if (titulo.length() > ANCHO_ELEMENTO) {
                titulo = titulo.substr(0, ANCHO_ELEMENTO - 3) + "...";
            }
            cout << titulo;
        }
    }

    void dibujarElementoCursoSeleccionado(int indice) {
        if (indice >= 0 && indice < cursosPorPagina &&
            indiceInicioCursos + indice < cursos.getTamano()) {

            int x = COL_LISTA_CURSOS;
            int y = FILA_LISTA_CURSOS + indice * 2;

            // Limpiar la línea completa primero
            gotoXY(x, y);
            cout << string(ANCHO_ELEMENTO, ' ');

            // Redibujar con color seleccionado
            Curso* curso = cursos.get(indiceInicioCursos + indice);
            gotoXY(x, y);
            SetConsoleColor(1, 13); // Color seleccionado
            string titulo = to_string(curso->getId()) + ": " + curso->getTitulo();
            if (titulo.length() > ANCHO_ELEMENTO) {
                titulo = titulo.substr(0, ANCHO_ELEMENTO - 3) + "...";
            }
            cout << titulo;
        }
    }

    void dibujarElementoEspecializacionSeleccionado(int indice) {
        if (indice >= 0 && indice < especialidadesPorPagina &&
            indiceInicioEspecialidades + indice < especialidades.getTamano()) {

            int x = COL_LISTA_ESPECIALIDADES;
            int y = FILA_LISTA_ESPECIALIDADES + indice * 2;

            // Limpiar la línea completa primero
            gotoXY(x, y);
            cout << string(ANCHO_ELEMENTO, ' ');

            // Redibujar con color seleccionado
            Especializacion* especializacion = especialidades.get(indiceInicioEspecialidades + indice);
            gotoXY(x, y);
            SetConsoleColor(1, 13); // Color seleccionado
            string titulo = to_string(especializacion->getId()) + ": " + especializacion->getTitulo();
            if (titulo.length() > ANCHO_ELEMENTO) {
                titulo = titulo.substr(0, ANCHO_ELEMENTO - 3) + "...";
            }
            cout << titulo;
        }
    }

    void renderizarCursoSeleccionado() {
        if (elementoActual < cursosPorPagina && indiceInicioCursos + elementoActual < cursos.getTamano()) {
            int indice = indiceInicioCursos + elementoActual;
            Curso* curso = cursos.get(indice);
            gotoXY(COL_LISTA_CURSOS, FILA_LISTA_CURSOS + elementoActual * 2);
            SetConsoleColor(1, 13); // Color para selección
            string titulo = to_string(curso->getId()) + ": " + curso->getTitulo();
            if (titulo.length() > ANCHO_ELEMENTO) {
                titulo = titulo.substr(0, ANCHO_ELEMENTO - 3) + "...";
            }
            cout << titulo;
        }
    }

    void renderizarEspecializacionSeleccionada() {
        if (elementoActual < especialidadesPorPagina && indiceInicioEspecialidades + elementoActual < especialidades.getTamano()) {
            int indice = indiceInicioEspecialidades + elementoActual;
            Especializacion* especializacion = especialidades.get(indice);
            gotoXY(COL_LISTA_ESPECIALIDADES, FILA_LISTA_ESPECIALIDADES + elementoActual * 2);
            SetConsoleColor(1, 13); // Color para selección
            string titulo = to_string(especializacion->getId()) + ": " + especializacion->getTitulo();
            if (titulo.length() > ANCHO_ELEMENTO) {
                titulo = titulo.substr(0, ANCHO_ELEMENTO - 3) + "...";
            }
            cout << titulo;
        }
    }

    void manejarMovimientoTeclas(int tecla) {
        int maxElementos = 0;
        int seccionPrevia = seccionActual;
        int elementoPrevio = elementoActual;
        int indiceInicioCursosPrevio = indiceInicioCursos;
        int indiceInicioEspecialidadesPrevio = indiceInicioEspecialidades;


        switch (seccionActual) {

        case SECCION_CURSOS:
            maxElementos = min(cursosPorPagina, cursos.getTamano() - indiceInicioCursos);
            break;

        case SECCION_ESPECIALIDADES:
            maxElementos = min(especialidadesPorPagina, especialidades.getTamano() - indiceInicioEspecialidades);
            break;
        }

        switch (tecla) {
        case 72: // Flecha arriba
            if (elementoActual > 0) {
                elementoActual--;
            }
            else if (seccionActual == SECCION_CURSOS && indiceInicioCursos > 0) {
                // Mover página hacia arriba en cursos
                indiceInicioCursos--;
                renderizarCursos(); // Ahora limpia correctamente
            }
            else if (seccionActual == SECCION_ESPECIALIDADES && indiceInicioEspecialidades > 0) {
                // Mover página hacia arriba en especialidades
                indiceInicioEspecialidades--;
                renderizarEspecialidades(); // Ahora limpia correctamente
            }
            else if (seccionActual > 0) {
                seccionActual--;
                if (seccionActual == SECCION_CURSOS) {
                    elementoActual = min(cursosPorPagina, cursos.getTamano() - indiceInicioCursos) - 1;
                }
                else {
                    elementoActual = 0; // Para header
                }
            }
            break;

        case 80: // Flecha abajo
            if (elementoActual < maxElementos - 1) {
                elementoActual++;
            }
            else if (seccionActual == SECCION_CURSOS && indiceInicioCursos + cursosPorPagina < cursos.getTamano()) {
                // Mover página hacia abajo en cursos
                indiceInicioCursos++;
                renderizarCursos(); // Ahora limpia correctamente
            }
            else if (seccionActual == SECCION_ESPECIALIDADES && indiceInicioEspecialidades + especialidadesPorPagina < especialidades.getTamano()) {
                // Mover página hacia abajo en especialidades
                indiceInicioEspecialidades++;
                renderizarEspecialidades(); // Ahora limpia correctamente
            }
            else if (seccionActual < TOTAL_SECCIONES - 1) {
                seccionActual++;
                elementoActual = 0;
            }
            break;

        case 33: // Page Up
            if (seccionActual == SECCION_CURSOS) {
                indiceInicioCursos = max(0, indiceInicioCursos - cursosPorPagina);
                elementoActual = 0;
                renderizarCursos(); // Ahora limpia correctamente
            }
            else if (seccionActual == SECCION_ESPECIALIDADES) {
                indiceInicioEspecialidades = max(0, indiceInicioEspecialidades - especialidadesPorPagina);
                elementoActual = 0;
                renderizarEspecialidades(); // Ahora limpia correctamente
            }
            break;

        case 34: // Page Down
            if (seccionActual == SECCION_CURSOS) {
                indiceInicioCursos = min(cursos.getTamano() - 1, indiceInicioCursos + cursosPorPagina);
                elementoActual = 0;
                renderizarCursos(); // Ahora limpia correctamente
            }
            else if (seccionActual == SECCION_ESPECIALIDADES) {
                indiceInicioEspecialidades = min(especialidades.getTamano() - 1, indiceInicioEspecialidades + especialidadesPorPagina);
                elementoActual = 0;
                renderizarEspecialidades(); // Ahora limpia correctamente
            }
            break;
        }
        // Después de manejar las teclas, verificar si necesitamos rerenderizar
        if (seccionActual == SECCION_CURSOS && indiceInicioCursosPrevio != indiceInicioCursos) {
            necesitaRerenderizarCursos = true;
        }

        if (seccionActual == SECCION_ESPECIALIDADES && indiceInicioEspecialidadesPrevio != indiceInicioEspecialidades) {
            necesitaRerenderizarEspecialidades = true;
        }

        // Si cambiamos de sección, puede que necesitemos rerenderizar ambas
        if (seccionPrevia != seccionActual) {
            // Si volvemos a una sección que ya estábamos viendo, asegurar que se renderice correctamente
            if (seccionActual == SECCION_CURSOS) {
                necesitaRerenderizarCursos = true;
            }
            else if (seccionActual == SECCION_ESPECIALIDADES) {
                necesitaRerenderizarEspecialidades = true;
            }
        }
    }

public:
    ExplorarCursosYEspecialidades(GestionadorCursos* _gestionadorCursos, TipoUsuario _tipoUsuario = TipoUsuario::ESTUDIANTE)
        : gestionadorCursos(_gestionadorCursos),
        tipoUsuario(_tipoUsuario),
        seccionActual(SECCION_CURSOS),
        elementoActual(0),
        indiceInicioCursos(0),
        indiceInicioEspecialidades(0),
        cursosPorPagina(5),
        especialidadesPorPagina(5),
        primeraRenderizacion(true),
        seccionAnterior(-1),
        elementoAnterior(-1),
        necesitaRerenderizarCursos(false),
        necesitaRerenderizarEspecialidades(false),
        cursos(_gestionadorCursos->getCursos()),
        especialidades(_gestionadorCursos->getEspecializaciones())
    {

        // Inicializar el array de últimas selecciones
        for (int i = 0; i < TOTAL_SECCIONES; i++) {
            ultimoElementoSeleccionadoPorSeccion[i] = 0;
        }

    }

    ~ExplorarCursosYEspecialidades() {
        // No necesitamos liberar memoria aquí ya que no somos dueños de los objetos
    }

    ResultadoPantalla ejecutar() override {
        ResultadoPantalla resultado;
        int tecla;

        if (primeraRenderizacion) {
            dibujarInterfazCompleta();
            primeraRenderizacion = false;
        }

        while (true) {
            // Actualizar interfaz según la selección actual
            actualizarInterfaz();

            // Esperar entrada del usuario
            tecla = _getch();

            // Si es una tecla extendida
            if (tecla == 224 || tecla == 0) {
                tecla = _getch();
                manejarMovimientoTeclas(tecla);
            }
            // Si es tecla Enter
            else if (tecla == 13) {
                if (seccionActual == SECCION_CURSOS) {
                    // Seleccionar un curso y mostrar sus detalles
                    int indiceCurso = indiceInicioCursos + elementoActual;
                    if (indiceCurso < cursos.getTamano()) {
                        resultado.idCursoSeleccionado = cursos.get(indiceCurso)->getId();
                        resultado.accion = AccionPantalla::IR_A_MOSTRAR_CURSO;
                        resultado.accionAnterior = tipoUsuario == TipoUsuario::ESTUDIANTE ?
                            AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE :
                            AccionPantalla::IR_A_DASHBOARD_ORGANIZACION;
                        resultado.tipoUsuario = tipoUsuario; // Pasar el tipo de usuario
                        return resultado;
                    }
                }
                else if (seccionActual == SECCION_ESPECIALIDADES) {
                    // Seleccionar una especialización y mostrar sus detalles
                    int indiceEspecialidad = indiceInicioEspecialidades + elementoActual;
                    if (indiceEspecialidad < especialidades.getTamano()) {
                        resultado.idCursoSeleccionado = especialidades.get(indiceEspecialidad)->getId();
                        resultado.accion = AccionPantalla::IR_A_MOSTRAR_ESPECIALIZACION;
                        resultado.accionAnterior = tipoUsuario == TipoUsuario::ESTUDIANTE ?
                            AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE :
                            AccionPantalla::IR_A_DASHBOARD_ORGANIZACION;
                        resultado.tipoUsuario = tipoUsuario; // Pasar el tipo de usuario
                        return resultado;
                    }
                }
            }
            // Si es tecla Escape
            else if (tecla == 27) {
                resultado.accion = tipoUsuario == TipoUsuario::ESTUDIANTE ?
                    AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE :
                    AccionPantalla::IR_A_DASHBOARD_ORGANIZACION;
                return resultado;
            }
        }

        return resultado;
    }
};
