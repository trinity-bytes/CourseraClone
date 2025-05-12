#pragma once
#include "Pantalla.h"
#include "PriorityQueue.h"
#include "GestionadorCursos.h"

class Controladora; // Declaración anticipada de la clase Controladora

class LandingPage : public PantallaBase {
private:
    // Constantes del menú
    static const int SECCION_CABECERA = 0;
    static const int SECCION_ESPECIALIDADES = 1;
    static const int SECCION_CURSOS = 2;
    static const int TOTAL_SECCIONES = 3;

    // Items max visibles por seccion
    static const int MAX_ELEMENTOS_CABECERA = 2;
    static const int MAX_ELEMENTOS_ESPECIALIDAD = 3;
    static const int MAX_ELEMENTOS_CURSO = 3;

    // Caracteres maximos por cuadro
    static const int MAX_ANCHO_CARACTERES_CUADRO = 30;
    static const int MAX_ALTO_CARACTERES_CUADRO = 4;

    GestionadorCursos* gestionCursos;

    // Elementos del menú
    const vector<string> ELEMENTOS_CABECERA = {
        " Iniciar Sesion ",
        " Registrarse ",
        " Sobre Nosotros "
    };

    // Datos por defecto
    vector<ElementoMenu> especialidadesDefecto = {
        {"Desarrollo Web", "Frontend & Backend"},
        {"Ciencia de Datos", "Analisis y ML"},
        {"Marketing Digital", "SEO, SEM & Ads"}
    };

    vector<ElementoMenu> cursosDefecto = {
        {"Curso C++ CLI", "Interaccion consola"},
        {"Curso Python DS", "Data science intro"},
        {"Curso React JS", "Web UI development"}
    };

    // Estado actual
    int seccionActual;
    int elementoActual;
    int seccionAnterior;
    int elementoAnterior;

    bool primeraRenderizacion;
    bool presionEnter; // Para evitar que se ejecute el evento de enter al iniciar la pantalla

    // Datos del menú
    vector<ElementoMenu> especialidades;
    vector<ElementoMenu> cursos;

    // Coordenadas para dibujar
    COORD coordsElementosCabecera[MAX_ELEMENTOS_CABECERA] = { {67, 3}, {84, 3} /*, {98, 3}*/};
    COORD coordsTituloEspecialidad[MAX_ELEMENTOS_ESPECIALIDAD] = { {11, 15}, {45, 15}, {79, 15} };
    COORD coordsDescEspecialidad[MAX_ELEMENTOS_ESPECIALIDAD] = { {11, 17}, {45, 17}, {79, 17} };
    COORD coordsTituloCurso[MAX_ELEMENTOS_CURSO] = { {11, 25}, {45, 25}, {79, 25} };
    COORD coordsDescCurso[MAX_ELEMENTOS_CURSO] = { {11, 27}, {45, 27}, {79, 27} };

    void actualizarSeleccion() {
        // Si es la primera renderización o cambió de sección
        if (seccionAnterior == -1 || seccionActual != seccionAnterior) {
            // Si no es la primera renderización, deseleccionar el elemento anterior
            if (seccionAnterior != -1) {
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
            }

            // Seleccionar el nuevo elemento
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
        // Si solo cambió el elemento dentro de la misma sección
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

        if (seleccionado) SetConsoleColor(15, 4, true, true);
        else SetConsoleColor(15, 13, false, true);

        cout << ELEMENTOS_CABECERA[indice];
        SetConsoleColor(15, 0);
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
        cout << string(20, ' ');
        gotoXY(coordTitulo.X, coordTitulo.Y);

        if (seleccionado) SetConsoleColor(1, 13);
        else SetConsoleColor(13, 6);

		string tituloFormateado = truncarTitulo(elemento.titulo, MAX_ANCHO_CARACTERES_CUADRO);

        cout << tituloFormateado;
        SetConsoleColor(15, 0);

        string descFormateada = formatearDescripcion(
            elemento.descripcion,
            MAX_ANCHO_CARACTERES_CUADRO,
            MAX_ALTO_CARACTERES_CUADRO
        );

        vector<string> lineas;
        stringstream ss(descFormateada);
        string linea;

        while (getline(ss, linea, '\n')) {
            lineas.push_back(linea);
        }

        for (size_t i = 0; i < lineas.size(); ++i) {
            gotoXY(coordDesc.X, coordDesc.Y + i);
            cout << string(30, ' ');
            gotoXY(coordDesc.X, coordDesc.Y + i);
            cout << lineas[i];
        }

        for (size_t i = lineas.size(); i < MAX_ALTO_CARACTERES_CUADRO; ++i) {
            gotoXY(coordDesc.X, coordDesc.Y + i);
            cout << string(30, ' ');
        }
    }

    void dibujarInterfazCompleta() {

        // Draw header background
        for (int y = 2; y < 6; y++) {
            for (int x = 4; x < ANCHO_CONSOLA - 4; x++) {
                gotoXY(x, y);
                SetConsoleColor(15, 13);
                cout << " ";
            }
        }

        // Draw app name/logo
        SetConsoleColor(12, 13, true, true); // Yellow on dark blue
        gotoXY(7, 3);    cout << "█▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█";
        gotoXY(7, 4);    cout << "█▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█";
        // Draw "CLONE" text
        gotoXY(39, 3);   cout << "│  C L O N E";

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

        // Inicializar estados anteriores
        seccionAnterior = seccionActual;
        elementoAnterior = elementoActual;

        gotoXY(0, ALTO_CONSOLA - 1);
    }

    // Método para truncar títulos que excedan el máximo de caracteres
    string truncarTitulo(const string& titulo, int maxLongitud) {
        if (titulo.length() <= maxLongitud) {
            return titulo;
        }
        return titulo.substr(0, maxLongitud - 3) + "...";
    }

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

    void cargarDatosLanding(LinkedList<Curso*>& cursosDatos, LinkedList<Especializacion*>& especializacionesDatos, int maximo) {
        PriorityQueue<Curso*> priorityCursosLandingPage(maximo);
        PriorityQueue<Especializacion*> priorityEspecializacionesLandingPage(maximo);

        auto cantidad = [](Actividad* a) {
            return a->getCantidadAlumnos();
            };
        int cantidadTotal;
        priorityCursosLandingPage.llenarDesde<int>(cursosDatos, cantidad);
        priorityEspecializacionesLandingPage.llenarDesde<int>(especializacionesDatos, cantidad);

		vector<int> idsCursos, idsEspecializaciones;
        vector<string> titulosCursos, descripcionesCursos, titulosEspecializaciones, descripcionesEspecializaciones;
        auto tituloActividad = [](Actividad* a) { // Retorna el dato de titulo
            return a->getTitulo();
            };
        auto descripcionActividad = [](Actividad* a) { // Retorna el dato de inscripción
            return a->getDescripcion();
            };

		auto idActividad = [](Actividad* a) { return a->getId(); };
        idsCursos = priorityCursosLandingPage.extraerDato<int>(idActividad);
        idsEspecializaciones = priorityEspecializacionesLandingPage.extraerDato<int>(idActividad);
        titulosCursos = priorityCursosLandingPage.extraerDato<string>(tituloActividad);
        titulosEspecializaciones = priorityEspecializacionesLandingPage.extraerDato<string>(tituloActividad);
        descripcionesCursos = priorityCursosLandingPage.extraerDato<string>(descripcionActividad);
        descripcionesEspecializaciones = priorityEspecializacionesLandingPage.extraerDato<string>(descripcionActividad);
        //throw runtime_error(titulosCursos[0]);
        cantidadTotal = titulosCursos.size();
        if (cantidadTotal < maximo) maximo = cantidadTotal;
        cursos = vector<ElementoMenu>(maximo);


        for (int i = 0; i < maximo; i++) {
			cursos[i].id = idsCursos[i];
            cursos[i].titulo = titulosCursos[i];
            cursos[i].descripcion = descripcionesCursos[i];
        }

        cantidadTotal = titulosEspecializaciones.size();
        maximo = 3;
        if (cantidadTotal < maximo) maximo = cantidadTotal;
        especialidades = vector<ElementoMenu>(maximo);


        for (int i = 0; i < maximo; i++) {
			especialidades[i].id = idsEspecializaciones[i];
            especialidades[i].titulo = titulosEspecializaciones[i];
            especialidades[i].descripcion = descripcionesEspecializaciones[i];
        }
    }

    void cargarDatos(LinkedList<Curso*>& cursosDatos, LinkedList<Especializacion*>& especializacionesDatos, int maximo) {
        cursos.clear();
        especialidades.clear();
        //string tamanoA = to_string(cursosDatos.getTamano());
        //throw runtime_error(tamanoA);
        cargarDatosLanding(cursosDatos, especializacionesDatos, maximo);
        
        int tamanoOriginal;
        if (cursos.size() < maximo) {
            cursos.resize(maximo);
            tamanoOriginal = cursos.size();
            for (int i = tamanoOriginal; i < maximo; i++) {
                cursos[i].titulo = cursosDefecto[i].titulo;
                cursos[i].descripcion = cursosDefecto[i].descripcion;
            }
        }
        if (especialidades.size() < maximo) {
            especialidades.resize(maximo);
            tamanoOriginal = especialidades.size();
            for (int i = tamanoOriginal; i < maximo; i++) {
                especialidades[i].titulo = especialidadesDefecto[i].titulo;
                especialidades[i].descripcion = especialidadesDefecto[i].descripcion;
            }
        }
    }

public:
    LandingPage() : PantallaBase(),
        seccionActual(0), elementoActual(0),
        seccionAnterior(-1), elementoAnterior(-1),
        primeraRenderizacion(true), presionEnter(false) {
    }

    LandingPage(LinkedList<Curso*>& cursosDatos, LinkedList<Especializacion*>& especializacionesDatos)
        : PantallaBase(),
        seccionActual(0), elementoActual(0),
        seccionAnterior(-1), elementoAnterior(-1),
        primeraRenderizacion(true), presionEnter(false)
    {
        //cargarDatos(cursosDatos, especializacionesDatos, 3);
        cargarDatos(cursosDatos, especializacionesDatos, 3);
    }

    void renderizar()
    {
        if (primeraRenderizacion)
        {
            system("cls");
            UI_LandingPage();
            dibujarInterfazCompleta();
            primeraRenderizacion = false;
        }
        else {
            actualizarSeleccion();
        }
    }

    void manejarInput(int tecla)
    {
        presionEnter = false;

        if (tecla == 224) // Tecla extendida
        {
            tecla = _getch();
            switch (tecla)
            {
            case 72: // Flecha arriba
                seccionActual--;
                if (seccionActual < 0) seccionActual = 0;
                elementoActual = 0;
                actualizarSeleccion();
                break;
            case 80: // Flecha abajo
                seccionActual++;
                if (seccionActual >= TOTAL_SECCIONES)
                    seccionActual = TOTAL_SECCIONES - 1;
                elementoActual = 0;
                actualizarSeleccion();
                break;
            case 75: // Flecha izquierda
                elementoActual--;
                if (elementoActual < 0) elementoActual = 0;
                actualizarSeleccion();
                break;
            case 77: // Flecha derecha
                elementoActual++;
                int maxElementos = obtenerMaxElementosEnSeccion(seccionActual);
                if (elementoActual >= maxElementos)
                    elementoActual = maxElementos > 0 ? maxElementos - 1 : 0;
                actualizarSeleccion();
                break;
            }
        }
        else if (tecla == 13) // Enter
        {
            presionEnter = true;
        }
    }

    Pantalla getSiguientePantalla() {
        if (seccionActual == SECCION_CABECERA)
        {
            switch (elementoActual)
            {
            case 0: // Iniciar Sesion
                return Pantalla::LOGIN;
            case 1: // Registrarse
                return Pantalla::REGISTRO;
                /*
            case 2: // Sobre Nosotros
                return Pantalla::SOBRE_NOSOTROS;
                */
            default:
                return Pantalla::NONE;
            }
        }
    }

    ResultadoPantalla ejecutar() override
    {
        ResultadoPantalla res;
        renderizar();

        int tecla;
        while (res.accion == AccionPantalla::NINGUNA) {
            // Handle input
            tecla = _getch(); // Assuming _getch() is available for input
            manejarInput(tecla);

            // Re-render based on updated selection
            renderizar();

            if (presionEnter)
            {
                if (seccionActual == SECCION_CURSOS) {
                    // Si se seleccionó un curso específico (no "Ver todos")
                    if (elementoActual < cursos.size()) {
                        // Obtener el ID del curso seleccionado (asumiendo que tienes acceso a él)
                        int idCursoSeleccionado = obtenerIdCurso(elementoActual); // Implementar este método
                        res.idCursoSeleccionado = idCursoSeleccionado;
                        res.accion = AccionPantalla::IR_A_MOSTRAR_CURSO;
                        res.accionAnterior = AccionPantalla::IR_A_LANDING_PAGE;
                        return res;
                    }
                }

                if (seccionActual == SECCION_ESPECIALIDADES) {
                    if (elementoActual < especialidades.size()) {
                        int idEspecializacionSeleccionada = especialidades[elementoActual].id; // Obtener el ID de la especialización
                        res.idCursoSeleccionado = idEspecializacionSeleccionada; // Reutilizamos este campo
                        res.accion = AccionPantalla::IR_A_MOSTRAR_ESPECIALIZACION;
                        res.accionAnterior = AccionPantalla::IR_A_LANDING_PAGE;
                        return res;
                    }
                }

                // Check if a selection triggers a screen change
                Pantalla siguiente = getSiguientePantalla();
                if (siguiente != Pantalla::NONE) {
                    switch (siguiente) {
                    case Pantalla::LOGIN:
                        res.accion = AccionPantalla::IR_A_LOGIN;
                        break;
                        // Add cases for other possible screens (REGISTRO, etc.)
                        // based on getSiguientePantalla() logic and ELEMENTOS_CABECERA
                    case Pantalla::REGISTRO: // Assuming you have a Pantalla::REGISTRO enum value
                        if (seccionActual == SECCION_CABECERA && elementoActual == 1) { // Assuming Registrarse is at index 1
                            res.accion = AccionPantalla::IR_A_REGISTRO; // Assuming you have AccionPantalla::IR_A_REGISTRO
                        }
                        break;
                    /*
                    case Pantalla::SOBRE_NOSOTROS: // Assuming you have a Pantalla::SOBRE_NOSOTROS enum value
                        if (seccionActual == SECCION_CABECERA && elementoActual == 2) { // Assuming Sobre Nosotros is at index 2
                            res.accion = AccionPantalla::IR_A_SOBRE_NOSOTROS; // Assuming you have AccionPantalla::IR_A_SOBRE_NOSOTROS
                        }
                        break;
                    */
                    default:
                        // Handle other possible next screens if needed
                        break;
                    }
                }
            }

            if (tecla == 27) // tecla ESC
            {
                res.accion = AccionPantalla::SALIR;
            }
        }

        return res;
    }

private:
	int obtenerIdCurso(int indice) {
		// Aquí deberías implementar la lógica para obtener el ID del curso
		// basado en el índice seleccionado. Por ahora, retornamos un valor de ejemplo.
		return indice + 1; // Ejemplo: ID del curso es el índice + 1
	}

    int obtenerMaxElementosEnSeccion(int seccion)
    {
        switch (seccion)
        {
        case SECCION_CABECERA: return MAX_ELEMENTOS_CABECERA;
        case SECCION_ESPECIALIDADES: return MAX_ELEMENTOS_ESPECIALIDAD;
        case SECCION_CURSOS: return MAX_ELEMENTOS_CURSO;
        default: return 0;
        }
    }
};