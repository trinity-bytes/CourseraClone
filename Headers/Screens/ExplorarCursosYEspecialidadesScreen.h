#pragma once

// Headers estándar
#include <vector>
#include <string>
#include <iostream>
#include <conio.h>
#include <algorithm>

// Headers propios  
#include "../Utils/ScreenSystem.h"
#include "../Utils/ExtendedFunctions.h"
#include "../Utils/UI_Ascii.h"
#include "../Entities/Curso.h"
#include "../Entities/Especializacion.h"
#include "../Controllers/GestionadorCursos.h"

class ExplorarCursosYEspecialidadesScreen : public PantallaBase
{
private:
    // Secciones de la pantalla
    static const int SECCION_CURSOS = 1;      // Lista de cursos
    static const int SECCION_ESPECIALIDADES = 2; // Lista de especialidades
    static const int TOTAL_SECCIONES = 3;

    int ultimoElementoSeleccionadoPorSeccion[TOTAL_SECCIONES];    // Estado actual
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
    bool necesitaRerenderizarEspecialidades;    TipoUsuario tipoUsuario;
    int idUsuario;
    std::string nombreUsuario;

    // Referencias a datos a través de la controladora

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
        SetConsoleColor(15, 0);
        std::cout << "EXPLORAR CURSOS Y ESPECIALIDADES";

        // Dibujar secciones
        SetConsoleColor(15, 0);
        renderizarCursos();
        renderizarEspecialidades();

        necesitaRerenderizarCursos = false;
        necesitaRerenderizarEspecialidades = false;
    }

    void renderizarCursos() 
    {
        limpiarAreaCursos();
        limpiarAreaIndicadoresCursos();        // Título de sección cursos
        gotoXY(COL_TITULO_CURSOS, FILA_TITULO_CURSOS);
        SetConsoleColor(14, 0);  // Amarillo sobre negro
        std::cout << "CURSOS DISPONIBLES";
        SetConsoleColor(15, 0);  // Blanco sobre negro        // Dibujar lista de cursos
        int totalCursos = _controladora->getGestionadorCursos().getCursos().getTamano();
       
        int cursosAMostrar = std::min(cursosPorPagina, totalCursos - indiceInicioCursos);

        // Primero limpiamos toda el área de cursos
        limpiarAreaCursos();        for (int i = 0; i < cursosAMostrar; i++) {
            int indice = indiceInicioCursos + i;
            Curso* curso = _controladora->getGestionadorCursos().getCursos().get(indice + 1);

            gotoXY(COL_LISTA_CURSOS, FILA_LISTA_CURSOS + i * 2);

            if (seccionActual == SECCION_CURSOS && elementoActual == i) {
                SetConsoleColor(1, 13); // Color para selección
            }
            else {
                SetConsoleColor(15, 1); // Color normal
            }            // Mostrar ID y título del curso
            std::string titulo = std::to_string(curso->getId()) + ": " + curso->getTitulo();
            if (titulo.length() > ANCHO_ELEMENTO) {
                titulo = titulo.substr(0, ANCHO_ELEMENTO - 3) + "...";
            }
            std::cout << titulo;
        }
        

        // Indicadores de paginación para cursos
        // Limpiar indicadores anteriores
        limpiarAreaIndicadoresCursos();        if (indiceInicioCursos > 0) {
            gotoXY(COL_LISTA_CURSOS + ANCHO_ELEMENTO + 5, FILA_LISTA_CURSOS);
            SetConsoleColor(15, 1);
            std::cout << "Mas arriba (Flecha ARRIBA)";
        }

        if (indiceInicioCursos + cursosPorPagina < totalCursos) {
            gotoXY(COL_LISTA_CURSOS + ANCHO_ELEMENTO + 5, FILA_LISTA_CURSOS + (cursosAMostrar * 2) - 2);
            SetConsoleColor(15, 0);
            std::cout << "Mas abajo (Flecha ABAJO)";
        }

        SetConsoleColor(15, 0); // Restaurar color normal
        necesitaRerenderizarCursos = false;
    }    void renderizarEspecialidades() 
    {
        // Convertir LinkedList a vector
        std::vector<Especializacion*> especialidadesVector;
        auto& especialidades = _controladora->getGestionadorCursos().getEspecializaciones();
        for (int i = 1; i <= especialidades.getTamano(); ++i) {
            especialidadesVector.push_back(especialidades.get(i));
        }

        // Aplicar Bubble Sort al vector
        //bubbleSort(especialidadesVector);
        /*
        for (Especializacion* especializacion : especialidadesVector){
            especialidades.agregarAlFinal(especializacion); 
        }
        */

        limpiarAreaEspecialidades();
        limpiarAreaIndicadoresEspecialidades();        // Título de sección especialidades
        gotoXY(COL_TITULO_ESPECIALIDADES, FILA_TITULO_ESPECIALIDADES);
        SetConsoleColor(14, 0);  // Amarillo sobre negro
        std::cout << "ESPECIALIZACIONES DISPONIBLES";
        SetConsoleColor(15, 0);  // Blanco sobre negro        // Dibujar lista de especialidades
        int totalEspecialidades = especialidades.getTamano();
        int especialidadesAMostrar = std::min(especialidadesPorPagina, totalEspecialidades - indiceInicioEspecialidades);

        // Primero limpiamos toda el área de especialidades
        limpiarAreaEspecialidades();

        for (int i = 0; i < especialidadesAMostrar; i++) {
            int indice = indiceInicioEspecialidades + i;
            Especializacion* especializacion = especialidades.get(indice + 1);

            gotoXY(COL_LISTA_ESPECIALIDADES, FILA_LISTA_ESPECIALIDADES + i * 2);

            if (seccionActual == SECCION_ESPECIALIDADES && elementoActual == i) {
                SetConsoleColor(1, 13); // Color para selección
            }
            else {
                SetConsoleColor(15, 1); // Color normal
            }            // Mostrar ID y título de la especialización
            std::string titulo = std::to_string(especializacion->getId()) + ": " + especializacion->getTitulo();
            if (titulo.length() > ANCHO_ELEMENTO) {
                titulo = titulo.substr(0, ANCHO_ELEMENTO - 3) + "...";
            }
            std::cout << titulo;
        }

        // Indicadores de paginación para especialidades
        // Limpiar indicadores anteriores
        limpiarAreaIndicadoresEspecialidades();        if (indiceInicioEspecialidades > 0) {
            gotoXY(COL_LISTA_ESPECIALIDADES + ANCHO_ELEMENTO + 5, FILA_LISTA_ESPECIALIDADES);
            SetConsoleColor(15, 0);
            std::cout << "Mas arriba (Flecha ARRIBA)";
        }

        if (indiceInicioEspecialidades + especialidadesPorPagina < totalEspecialidades) {
            gotoXY(COL_LISTA_ESPECIALIDADES + ANCHO_ELEMENTO + 5, FILA_LISTA_ESPECIALIDADES + (especialidadesAMostrar * 2) - 2);
            SetConsoleColor(15, 0);
            std::cout << "Mas abajo (Flecha ABAJO)";
        }

        SetConsoleColor(15, 0); // Restaurar color normal
        necesitaRerenderizarEspecialidades = false;
    }

    // Métodos para limpieza de áreas    void limpiarAreaCursos() {
        // Limpiar toda el área donde se muestran los cursos
        for (int i = 0; i < cursosPorPagina; i++) {
            gotoXY(COL_LISTA_CURSOS, FILA_LISTA_CURSOS + i * 2);
            std::cout << std::string(ANCHO_ELEMENTO + 20, ' '); // El +20 es para asegurar limpieza completa
        }
    }    void limpiarAreaIndicadoresCursos() {
        // Limpiar área de indicadores de paginación para cursos
        gotoXY(COL_LISTA_CURSOS + ANCHO_ELEMENTO + 5, FILA_LISTA_CURSOS);
        std::cout << std::string(26, ' '); // Espacio para "▲ Más arriba"

        gotoXY(COL_LISTA_CURSOS + ANCHO_ELEMENTO + 5, FILA_LISTA_CURSOS + (cursosPorPagina * 2) - 2);
        std::cout << std::string(26, ' '); // Espacio para "▼ Más abajo"
    }    void limpiarAreaEspecialidades() {
        // Limpiar toda el área donde se muestran las especialidades
        for (int i = 0; i < especialidadesPorPagina; i++) {
            gotoXY(COL_LISTA_ESPECIALIDADES, FILA_LISTA_ESPECIALIDADES + i * 2);
            std::cout << std::string(ANCHO_ELEMENTO + 20, ' '); // El +20 es para asegurar limpieza completa
        }
    }    void limpiarAreaIndicadoresEspecialidades() {
        // Limpiar área de indicadores de paginación para especialidades
        gotoXY(COL_LISTA_ESPECIALIDADES + ANCHO_ELEMENTO + 5, FILA_LISTA_ESPECIALIDADES);
        std::cout << std::string(26, ' '); // Espacio para "▲ Más arriba"

        gotoXY(COL_LISTA_ESPECIALIDADES + ANCHO_ELEMENTO + 5, FILA_LISTA_ESPECIALIDADES + (especialidadesPorPagina * 2) - 2);
        std::cout << std::string(26, ' '); // Espacio para "▼ Más abajo"
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
    }    void limpiarYRedibujarElementoCurso(int indice) {
        if (indice >= 0 && indice < cursosPorPagina &&
            indiceInicioCursos + indice < _controladora->getGestionadorCursos().getCursos().getTamano()) {

            int x = COL_LISTA_CURSOS;
            int y = FILA_LISTA_CURSOS + indice * 2;            // Limpiar la línea completa
            gotoXY(x, y);
            std::cout << std::string(ANCHO_ELEMENTO, ' ');

            // Redibujar con color normal
            Curso* curso = _controladora->getGestionadorCursos().getCursos().get(indiceInicioCursos + indice + 1);
            gotoXY(x, y);
            SetConsoleColor(15, 0); // Color normal
            std::string titulo = std::to_string(curso->getId()) + ": " + curso->getTitulo();
            if (titulo.length() > ANCHO_ELEMENTO) {
                titulo = titulo.substr(0, ANCHO_ELEMENTO - 3) + "...";
            }
            std::cout << titulo;
        }
    }    void limpiarYRedibujarElementoEspecializacion(int indice) {
        if (indice >= 0 && indice < especialidadesPorPagina &&
            indiceInicioEspecialidades + indice < _controladora->getGestionadorCursos().getEspecializaciones().getTamano()) {

            int x = COL_LISTA_ESPECIALIDADES;
            int y = FILA_LISTA_ESPECIALIDADES + indice * 2;            // Limpiar la línea completa
            gotoXY(x, y);
            std::cout << std::string(ANCHO_ELEMENTO, ' ');            // Redibujar con color normal
            Especializacion* especializacion = _controladora->getGestionadorCursos().getEspecializaciones().get(indiceInicioEspecialidades + indice + 1);
            gotoXY(x, y);
            SetConsoleColor(15, 0); // Color normal
            std::string titulo = std::to_string(especializacion->getId()) + ": " + especializacion->getTitulo();
            if (titulo.length() > ANCHO_ELEMENTO) {
                titulo = titulo.substr(0, ANCHO_ELEMENTO - 3) + "...";
            }
            std::cout << titulo;
        }
    }    void dibujarElementoCursoSeleccionado(int indice) {
        if (indice >= 0 && indice < cursosPorPagina &&
            indiceInicioCursos + indice < _controladora->getGestionadorCursos().getCursos().getTamano()) {

            int x = COL_LISTA_CURSOS;
            int y = FILA_LISTA_CURSOS + indice * 2;            // Limpiar la línea completa primero
            gotoXY(x, y);
            std::cout << std::string(ANCHO_ELEMENTO, ' ');

            // Redibujar con color seleccionado
            Curso* curso = _controladora->getGestionadorCursos().getCursos().get(indiceInicioCursos + indice + 1);
            gotoXY(x, y);
            SetConsoleColor(1, 13); // Color seleccionado
            std::string titulo = std::to_string(curso->getId()) + ": " + curso->getTitulo();
            if (titulo.length() > ANCHO_ELEMENTO) {
                titulo = titulo.substr(0, ANCHO_ELEMENTO - 3) + "...";
            }
            std::cout << titulo;
        }
    }    void dibujarElementoEspecializacionSeleccionado(int indice) {
        if (indice >= 0 && indice < especialidadesPorPagina &&
            indiceInicioEspecialidades + indice < _controladora->getGestionadorCursos().getEspecializaciones().getTamano()) {

            int x = COL_LISTA_ESPECIALIDADES;
            int y = FILA_LISTA_ESPECIALIDADES + indice * 2;            // Limpiar la línea completa primero
            gotoXY(x, y);
            std::cout << std::string(ANCHO_ELEMENTO, ' ');            // Redibujar con color seleccionado
            Especializacion* especializacion = _controladora->getGestionadorCursos().getEspecializaciones().get(indiceInicioEspecialidades + indice + 1);
            gotoXY(x, y);
            SetConsoleColor(1, 13); // Color seleccionado
            std::string titulo = std::to_string(especializacion->getId()) + ": " + especializacion->getTitulo();
            if (titulo.length() > ANCHO_ELEMENTO) {
                titulo = titulo.substr(0, ANCHO_ELEMENTO - 3) + "...";
            }
            std::cout << titulo;
        }
    }    void renderizarCursoSeleccionado() {
        if (elementoActual < cursosPorPagina && indiceInicioCursos + elementoActual < _controladora->getGestionadorCursos().getCursos().getTamano()) {
            int indice = indiceInicioCursos + elementoActual;
            Curso* curso = _controladora->getGestionadorCursos().getCursos().get(indice);gotoXY(COL_LISTA_CURSOS, FILA_LISTA_CURSOS + elementoActual * 2);
            SetConsoleColor(1, 13); // Color para selección
            std::string titulo = std::to_string(curso->getId()) + ": " + curso->getTitulo();
            if (titulo.length() > ANCHO_ELEMENTO) {
                titulo = titulo.substr(0, ANCHO_ELEMENTO - 3) + "...";
            }
            std::cout << titulo;
        }
    }    void renderizarEspecializacionSeleccionada() {
        if (elementoActual < especialidadesPorPagina && indiceInicioEspecialidades + elementoActual < _controladora->getGestionadorCursos().getEspecializaciones().getTamano()) {
            int indice = indiceInicioEspecialidades + elementoActual;
            Especializacion* especializacion = _controladora->getGestionadorCursos().getEspecializaciones().get(indice + 1);gotoXY(COL_LISTA_ESPECIALIDADES, FILA_LISTA_ESPECIALIDADES + elementoActual * 2);
            SetConsoleColor(1, 13); // Color para selección
            std::string titulo = std::to_string(especializacion->getId()) + ": " + especializacion->getTitulo();
            if (titulo.length() > ANCHO_ELEMENTO) {
                titulo = titulo.substr(0, ANCHO_ELEMENTO - 3) + "...";
            }
            std::cout << titulo;
        }
    }

    void manejarMovimientoTeclas(int tecla) {
        int maxElementos = 0;
        int seccionPrevia = seccionActual;
        int elementoPrevio = elementoActual;
        int indiceInicioCursosPrevio = indiceInicioCursos;
        int indiceInicioEspecialidadesPrevio = indiceInicioEspecialidades;        switch (seccionActual) {

        case SECCION_CURSOS:
            maxElementos = std::min(cursosPorPagina, _controladora->getGestionadorCursos().getCursos().getTamano() - indiceInicioCursos);
            break;

        case SECCION_ESPECIALIDADES:
            maxElementos = std::min(especialidadesPorPagina, _controladora->getGestionadorCursos().getEspecializaciones().getTamano() - indiceInicioEspecialidades);
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
            }            else if (seccionActual == SECCION_ESPECIALIDADES) {
                // Cambiar de sección especialidades a cursos
                seccionActual = SECCION_CURSOS;
                // Seleccionar el último elemento de la lista de cursos
                elementoActual = std::min(cursosPorPagina, _controladora->getGestionadorCursos().getCursos().getTamano() - indiceInicioCursos) - 1;
            }
            break;

        case 80: // Flecha abajo
            if (elementoActual < maxElementos - 1) {
                elementoActual++;
            }            else if (seccionActual == SECCION_CURSOS && indiceInicioCursos + cursosPorPagina < _controladora->getGestionadorCursos().getCursos().getTamano()) {
                // Mover página hacia abajo en cursos
                indiceInicioCursos++;
                renderizarCursos(); // Ahora limpia correctamente
            }
            else if (seccionActual == SECCION_ESPECIALIDADES && indiceInicioEspecialidades + especialidadesPorPagina < _controladora->getGestionadorCursos().getEspecializaciones().getTamano()) {
                // Mover página hacia abajo en especialidades
                indiceInicioEspecialidades++;
                renderizarEspecialidades(); // Ahora limpia correctamente
            }
            else if (seccionActual < TOTAL_SECCIONES - 1) {
                seccionActual++;
                elementoActual = 0;
            }
            break;        case 33: // Page Up
            if (seccionActual == SECCION_CURSOS) {
                indiceInicioCursos = std::max(0, indiceInicioCursos - cursosPorPagina);
                elementoActual = 0;
                renderizarCursos(); // Ahora limpia correctamente
            }
            else if (seccionActual == SECCION_ESPECIALIDADES) {
                indiceInicioEspecialidades = std::max(0, indiceInicioEspecialidades - especialidadesPorPagina);
                elementoActual = 0;
                renderizarEspecialidades(); // Ahora limpia correctamente
            }
            break;        case 34: // Page Down
            if (seccionActual == SECCION_CURSOS) {
                indiceInicioCursos = std::min(_controladora->getGestionadorCursos().getCursos().getTamano() - 1, indiceInicioCursos + cursosPorPagina);
                elementoActual = 0;
                renderizarCursos(); // Ahora limpia correctamente
            }
            else if (seccionActual == SECCION_ESPECIALIDADES) {
                indiceInicioEspecialidades = std::min(_controladora->getGestionadorCursos().getEspecializaciones().getTamano() - 1, indiceInicioEspecialidades + especialidadesPorPagina);
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
    ExplorarCursosYEspecialidadesScreen(Controladora* _controladora,
        TipoUsuario _tipoUsuario,
        int _idUsuario = 0,
        const std::string& _nombreUsuario = "")
        : PantallaBase(_controladora),
        tipoUsuario(_tipoUsuario),
        idUsuario(_idUsuario),
        nombreUsuario(_nombreUsuario),
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
        necesitaRerenderizarEspecialidades(false)
    {

      
        // Inicializar el array de últimas selecciones
        for (int i = 0; i < TOTAL_SECCIONES; i++) {
            ultimoElementoSeleccionadoPorSeccion[i] = 0;
        }    }

    ~ExplorarCursosYEspecialidadesScreen() {
        // No necesitamos liberar memoria aquí ya que no somos dueños de los objetos
    }    ResultadoPantalla ejecutar() override {
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
                    auto& cursos = _controladora->getGestionadorCursos().getCursos();
                    if (indiceCurso < cursos.getTamano()) {
                        auto resultado = crearResultado(AccionPantalla::IR_A_MOSTRAR_CURSO, tipoUsuario);
                        resultado.idCursoSeleccionado = cursos.get(indiceCurso + 1)->getId();
                        resultado.accionAnterior = tipoUsuario == TipoUsuario::ESTUDIANTE ?
                            AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE :
                            AccionPantalla::IR_A_DASHBOARD_ORGANIZACION;
                        return resultado;
                    }
                }
                else if (seccionActual == SECCION_ESPECIALIDADES) {
                    // Seleccionar una especialización y mostrar sus detalles
                    int indiceEspecialidad = indiceInicioEspecialidades + elementoActual;
                    auto& especialidades = _controladora->getGestionadorCursos().getEspecializaciones();
                    if (indiceEspecialidad < especialidades.getTamano()) {
                        auto resultado = crearResultado(AccionPantalla::IR_A_MOSTRAR_ESPECIALIZACION, tipoUsuario);
                        resultado.idCursoSeleccionado = especialidades.get(indiceEspecialidad + 1)->getId();
                        resultado.accionAnterior = tipoUsuario == TipoUsuario::ESTUDIANTE ?
                            AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE :
                            AccionPantalla::IR_A_DASHBOARD_ORGANIZACION;
                        return resultado;
                    }
                }
            }
            // Si es tecla Escape
            else if (tecla == 27) {
                AccionPantalla accionDestino = tipoUsuario == TipoUsuario::ESTUDIANTE ?
                    AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE :
                    AccionPantalla::IR_A_DASHBOARD_ORGANIZACION;
                return crearResultado(accionDestino, tipoUsuario);
            }
        }

        return crearResultado(AccionPantalla::SALIR, tipoUsuario);
    }
};
