#pragma once
// Encabezados propios
#include "Controladora.h"
#include "ExtendedFunctions.h"
#include "UI_Ascii.h"
#include "Menu_State.h"
#include "PriorityQueue.h"
//#include "Login_State.h"

// Encabezados estandar
#include "iostream"
#include "vector"
#include "string"
#include "memory"    // Para std::unique_ptr
#include "conio.h"   // Para _kbhit() y _getch()
#include "fstream"   // Para ifstream, ofstream
#include "sstream"   // Para stringstream (usado en formatearDescripcion)
#include "windows.h" // Para GetAsyncKeyState, VK_ESCAPE

using namespace std;

// Estado de la página principal
class LandingPageState : public MenuState
{
private:
    // Constantes del menú
    static const int SECCION_CABECERA = 0;
    static const int SECCION_ESPECIALIDADES = 1;
    static const int SECCION_CURSOS = 2;
    static const int TOTAL_SECCIONES = 3;

    // Archivos de persistencia
    const string ARCHIVO_PERSISTENCIA = "Resources/Data/ultima_posi.txt";
    const string ARCHIVO_ESPECIALIDADES = "Resources/Data/especialidades_muestra.txt";
    const string ARCHIVO_CURSOS = "Resources/Data/cursos_muestra.txt";

    // Items max visibles por seccion (basado en el diseño ASCII)
    static const int MAX_ELEMENTOS_CABECERA = 3;
    static const int MAX_ELEMENTOS_ESPECIALIDAD = 3; // 3 rectangulos visibles en el layout
    static const int MAX_ELEMENTOS_CURSO = 3;    // 3 rectangulos visibles en el layout

    // Caracteres maximos que pueden entrar por cuadro de especialidad o curso
    static const int MAX_ANCHO_CARACTERES_CUADRO = 30; // Maximo de caracteres por linea
    static const int MAX_ALTO_CARACTERES_CUADRO = 4;   // Maximo de saltos de linea

    const vector<string> ELEMENTOS_CABECERA = {
        " Iniciar Sesion ",
        " Registrarse ",
        " Sobre Nosotros "
    };

    // Datos por defecto si los archivos faltan o están vacíos
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
    int opcionSeleccionada; // Para almacenar la opción seleccionada con Enter

    // Datos del menú
    vector<ElementoMenu> especialidades;
    vector<ElementoMenu> cursos;

    // Coordenadas para dibujar
    COORD coordsElementosCabecera[MAX_ELEMENTOS_CABECERA] = { {67, 3}, {84, 3}, {98, 3} };
    COORD coordsTituloEspecialidad[MAX_ELEMENTOS_ESPECIALIDAD] = { {11, 15}, {45, 15}, {79, 15} };
    COORD coordsDescEspecialidad[MAX_ELEMENTOS_ESPECIALIDAD] = { {11, 17}, {45, 17}, {79, 17} };
    COORD coordsTituloCurso[MAX_ELEMENTOS_CURSO] = { {11, 25}, {45, 25}, {79, 25} };
    COORD coordsDescCurso[MAX_ELEMENTOS_CURSO] = { {11, 27}, {45, 27}, {79, 27} };

    void actualizarSeleccion()
    {
        // Si cambió de sección, actualizar ambas secciones implicadas (anterior y actual)
        if (seccionActual != seccionAnterior)
        {
            // Desdibujar la selección anterior (sección anterior)
            switch (seccionAnterior)
            {
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

            // Dibujar la nueva selección (sección actual)
            switch (seccionActual)
            {
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
        else if (elementoActual != elementoAnterior)
        {
            switch (seccionActual)
            {
            case SECCION_CABECERA:
                // Actualizar solo los elementos de cabecera que cambiaron
                actualizarElementoCabecera(elementoAnterior, false);
                actualizarElementoCabecera(elementoActual, true);
                break;
            case SECCION_ESPECIALIDADES:
                // Actualizar solo los elementos de especialidad que cambiaron
                actualizarElementoEspecialidad(elementoAnterior, false);
                actualizarElementoEspecialidad(elementoActual, true);
                break;
            case SECCION_CURSOS:
                // Actualizar solo los elementos de curso que cambiaron
                actualizarElementoCurso(elementoAnterior, false);
                actualizarElementoCurso(elementoActual, true);
                break;
            }
        }

        // Actualizar los valores anteriores para la próxima iteración
        seccionAnterior = seccionActual;
        elementoAnterior = elementoActual;
    }

    void actualizarElementoCabecera(int indice, bool seleccionado)
    {
        if (indice < 0 || indice >= MAX_ELEMENTOS_CABECERA) return;

        gotoXY(coordsElementosCabecera[indice].X, coordsElementosCabecera[indice].Y);

        if (seleccionado) SetConsoleColor(1, 4); // Color de texto SELECCION
        else SetConsoleColor(15, 1); // Color por defecto

        cout << ELEMENTOS_CABECERA[indice];
        SetConsoleColor(15, 1); // Restablecer color por defecto
    }

    void actualizarElementoEspecialidad(int indice, bool seleccionado)
    {
        if (indice < 0 || indice >= especialidades.size()) return;

        // Actualizar contenido usando función genérica
        actualizarElementoGenerico(
            coordsTituloEspecialidad[indice],
            coordsDescEspecialidad[indice],
            especialidades[indice],
            seleccionado
        );
    }

    void actualizarElementoCurso(int indice, bool seleccionado)
    {
        if (indice < 0 || indice >= cursos.size()) return;

        // Actualizar contenido usando función genérica
        actualizarElementoGenerico(
            coordsTituloCurso[indice],
            coordsDescCurso[indice],
            cursos[indice],
            seleccionado
        );
    }

    void actualizarElementoGenerico(const COORD& coordTitulo,
        const COORD& coordDesc, const ElementoMenu& elemento,
        bool seleccionado)
    {
        // Actualizar título
        gotoXY(coordTitulo.X, coordTitulo.Y);
        cout << string(20, ' ');
        gotoXY(coordTitulo.X, coordTitulo.Y);

        if (seleccionado) SetConsoleColor(1, 13); // Color de SELECCIONADO
        else SetConsoleColor(15, 1); // Color por defecto

        cout << elemento.titulo;
        SetConsoleColor(15, 1); // Color por defecto

        // Formatear y actualizar descripción
        string descFormateada = formatearDescripcion(
            elemento.descripcion,
            MAX_ANCHO_CARACTERES_CUADRO,
            MAX_ALTO_CARACTERES_CUADRO
        );

        vector<string> lineas;
        stringstream ss(descFormateada);
        string linea;

        while (getline(ss, linea, '\n'))
        {
            lineas.push_back(linea);
        }

        for (size_t i = 0; i < lineas.size(); ++i)
        {
            gotoXY(coordDesc.X, coordDesc.Y + i);
            cout << string(30, ' ');
            gotoXY(coordDesc.X, coordDesc.Y + i);
            cout << lineas[i];
        }

        // Limpiar líneas restantes
        for (size_t i = lineas.size(); i < MAX_ALTO_CARACTERES_CUADRO; ++i)
        {
            gotoXY(coordDesc.X, coordDesc.Y + i);
            cout << string(30, ' ');
        }
    }

    void dibujarInterfazCompleta()
    {
        // Cabecera
        for (int i = 0; i < MAX_ELEMENTOS_CABECERA; ++i)
        {
            actualizarElementoCabecera(i, seccionActual == SECCION_CABECERA && elementoActual == i);
        }

        // Especialidades
        for (size_t i = 0; i < especialidades.size() && i < MAX_ELEMENTOS_ESPECIALIDAD; ++i)
        {
            actualizarElementoEspecialidad(i, seccionActual == SECCION_ESPECIALIDADES && elementoActual == i);
        }

        // Cursos
        for (size_t i = 0; i < cursos.size() && i < MAX_ELEMENTOS_CURSO; ++i)
        {
            actualizarElementoCurso(i, seccionActual == SECCION_CURSOS && elementoActual == i);
        }

        // Asegurar que el cursor esté en una posición no obstructiva
        gotoXY(0, ALTO_CONSOLA - 1);
    }

    // Función auxiliar para formatear texto en múltiples líneas
    string formatearDescripcion(const string& texto, int anchoMax, int altoMax)
    {
        string resultado;
        string textoRestante = texto;

        for (int linea = 0; linea < altoMax; ++linea)
        {
            if (textoRestante.empty()) // Si ya no queda texto, terminar
            {
                break;
            }

            // Si estamos en la última línea y queda más texto del que cabe
            if (linea == altoMax - 1 && textoRestante.length() > anchoMax)
            {
                // Añadir texto truncado con "..."
                resultado += textoRestante.substr(0, anchoMax - 3) + "...";
                break;
            }

            // Para líneas normales, tomar solo hasta anchoMax caracteres
            if (textoRestante.length() <= anchoMax)
            {
                resultado += textoRestante;
                textoRestante.clear();
            }
            else
            {
                // Buscar el último espacio dentro del límite para cortar por palabras
                int posCorte = anchoMax;

                // Intentar cortar por un espacio para no dividir palabras
                while (posCorte > 0 && textoRestante[posCorte] != ' ' && textoRestante[posCorte - 1] != ' ') {
                    posCorte--;
                }

                // Si no se encontró un espacio adecuado, cortar en el límite máximo
                if (posCorte <= 0) {
                    posCorte = anchoMax;
                }

                resultado += textoRestante.substr(0, posCorte);
                textoRestante = textoRestante.substr(posCorte);

                // Eliminar espacios al inicio de la siguiente línea
                textoRestante.erase(0, textoRestante.find_first_not_of(" "));
            }

            // Añadir salto de línea si no es la última línea y hay más texto
            if (linea < altoMax - 1 && !textoRestante.empty())
            {
                resultado += "\n";
            }
        }

        return resultado;
    }

    // Devuelve el número máximo de elementos *visibles* para una sección dada
    int obtenerMaxElementosEnSeccion(int seccion)
    {
        switch (seccion)
        {
        case SECCION_CABECERA: return MAX_ELEMENTOS_CABECERA;
        case SECCION_ESPECIALIDADES: return min(static_cast<int>(especialidades.size()), MAX_ELEMENTOS_ESPECIALIDAD);
        case SECCION_CURSOS: return min(static_cast<int>(cursos.size()), MAX_ELEMENTOS_CURSO);
        default: return 0;
        }
    }

    void cargarDatosLanding(Controladora* ctrl, int maximo) {
        PriorityQueue<Curso*> priorityCursosLandingPage(maximo);
        PriorityQueue<Especializacion*> priorityEspecializacionesLandingPage(maximo);

        vector<string> titulosCursos, descripcionesCursos, titulosEspecializaciones, descripcionesEspecializaciones;
        auto tituloActividad = [](Actividad* a) { // Retorna el dato de titulo
            return a->getTitulo();
            };
        auto descripcionActividad = [](Actividad* a) { // Retorna el dato de inscripción
            return a->getDescripcion();
            };

        // obtener datos
        titulosCursos = priorityCursosLandingPage.extraerDato<string>(tituloActividad);
        titulosEspecializaciones = priorityEspecializacionesLandingPage.extraerDato<string>(tituloActividad);
        descripcionesCursos = priorityCursosLandingPage.extraerDato<string>(descripcionActividad);
        descripcionesEspecializaciones = priorityEspecializacionesLandingPage.extraerDato<string>(descripcionActividad);

        auto cantidad = [](Actividad* a) {
            return a->getCantidadAlumnos();
            };
        int cantidadTotal;

        cantidadTotal = titulosCursos.size();
        if (cantidadTotal < maximo) maximo = cantidadTotal;
        cursos = vector<ElementoMenu>(maximo);
        priorityCursosLandingPage.llenarDesde<int>(ctrl->getCursos(), cantidad);
        for (int i = 0; i < maximo; i++) {
            cursos[i].titulo = titulosCursos[i];
            cursos[i].descripcion = descripcionesCursos[i];
        }

        cantidadTotal = titulosEspecializaciones.size();
        maximo = 3;
        if (cantidadTotal < maximo) maximo = cantidadTotal;
        especialidades = vector<ElementoMenu>(maximo);
        priorityEspecializacionesLandingPage.llenarDesde<int>(ctrl->getEspecializaciones(), cantidad);
        for (int i = 0; i < maximo; i++) {
            especialidades[i].titulo = titulosEspecializaciones[i];
            especialidades[i].descripcion = descripcionesEspecializaciones[i];
        }
    }

    void cargarDatos(Controladora* ctrl, const vector<ElementoMenu>& cursosDefecto, const vector<ElementoMenu>& especialidadesDefecto, int maximo)
    {
        cursos.clear();
        especialidades.clear();
        cargarDatosLanding(ctrl, 3);

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
            cursos.resize(maximo);
            tamanoOriginal = especialidades.size();
            for (int i = tamanoOriginal; i < maximo; i++) {
                especialidades[i].titulo = especialidadesDefecto[i].titulo;
                especialidades[i].descripcion = especialidadesDefecto[i].descripcion;
            }
        }

    }

    // Carga la última sección y elemento guardados del archivo de persistencia
    void cargarPersistencia()
    {
        ifstream archivo(ARCHIVO_PERSISTENCIA);
        if (archivo.is_open())
        {
            int seccionCargada, elementoCargado;
            if (archivo >> seccionCargada >> elementoCargado)
            {
                // Validar valores cargados contra límites de datos reales
                if (seccionCargada >= 0 && seccionCargada < TOTAL_SECCIONES)
                {
                    seccionActual = seccionCargada;
                    // Validar elemento dentro de los límites de la sección cargada
                    int maxElementos = obtenerMaxElementosEnSeccion(seccionActual);
                    if (elementoCargado >= 0 && elementoCargado < maxElementos)
                    {
                        elementoActual = elementoCargado;
                    }
                    else
                    {
                        elementoActual = 0; // Reiniciar elemento si está fuera de límites
                    }
                }
                else
                {
                    seccionActual = SECCION_CABECERA; // Reiniciar sección si está fuera de límites
                    elementoActual = 0;
                }
            }
            archivo.close();
        }
        // Si el archivo no existe o está vacío/inválido, se usa la posición por defecto (0, 0).
    }

    // Guarda la sección y elemento actuales en el archivo de persistencia
    void guardarPersistencia()
    {
        ofstream archivo(ARCHIVO_PERSISTENCIA);
        if (archivo.is_open())
        {
            archivo << seccionActual << endl;
            archivo << elementoActual << endl;
            archivo.close();
        }
    }



public:
    LandingPageState(Controladora* ctrl) : MenuState(ctrl),
        seccionActual(0), elementoActual(0), seccionAnterior(-1),
        elementoAnterior(-1), primeraRenderizacion(true), opcionSeleccionada(0)
    {
        // Cargar datos desde archivos
        cargarDatos(ctrl, cursosDefecto, especialidadesDefecto, 3);

        // Cargar última posición seleccionada
        cargarPersistencia();
    }

    ~LandingPageState()
    {
        // Guardar persistencia al destruir el estado
        guardarPersistencia();
    }

    void handleInput(int tecla) override
    {
        if (tecla == 224) // Tecla extendida
        {
            tecla = _getch();
            switch (tecla)
            {
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
        else if (tecla == 13) // Tecla Enter - Seleccionar opción
        {
            switch (seccionActual)
            {
            case SECCION_CABECERA:
                if (elementoActual >= 0 && elementoActual < MAX_ELEMENTOS_CABECERA)
                {
                    opcionSeleccionada = elementoActual + 1; // 1=Iniciar, 2=Registrarse, 3=Sobre Nosotros
                    //controladora->cambiarEstado(make_unique<LoginState>(controladora)); // Cambiar al siguiente estado
                }
                break;
            case SECCION_ESPECIALIDADES:
                if (elementoActual >= 0 && elementoActual < especialidades.size())
                {
                    opcionSeleccionada = 4; // Código para especialidad seleccionada
                    // Aquí podrías implementar alguna acción específica o cambio de estado
                }
                break;
            case SECCION_CURSOS:
                if (elementoActual >= 0 && elementoActual < cursos.size())
                {
                    opcionSeleccionada = 5; // Código para curso seleccionado
                    // Aquí podrías implementar alguna acción específica o cambio de estado
                }
                break;
            }
        }
        else if (tecla == 27) // ESC - Salir
        {
            opcionSeleccionada = 0; // Opción 0 para salir
            //controladora->terminarAplicacion(); // O implementar la lógica de salida adecuada
        }
    }

    /*
    void update() override
    {
        // Este método podría contener lógica adicional que deba ejecutarse en cada cuadro
        // Por ejemplo, verificar si se pulsó ESC sin usar _kbhit
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
        {
            opcionSeleccionada = 0; // Opción 0 para salir
            controladora->terminarAplicacion(); // O implementar la lógica de salida adecuada
        }
    }
    */

    void render() override
    {
        if (primeraRenderizacion) // Renderizar por primera vez
        {
            renderInicial();
            primeraRenderizacion = false;
        }
        else // Renderizar solo actualizaciones
        {
            renderUpdate();
        }
    }

    void renderInicial() override
    {
        system("cls");
        UI_LandingPage();
        dibujarInterfazCompleta();
    }

    void renderUpdate() override
    {
        actualizarSeleccion();  // Solo actualizar los elementos que cambiaron
    }

    std::unique_ptr<MenuState> getNextState() override // Retornar al siguiente estado
    {
        if (seccionActual == SECCION_CABECERA && elementoActual == 0)
        {
            //return std::make_unique<LoginState>(controladora);
        }
        else if (seccionActual == SECCION_ESPECIALIDADES && opcionSeleccionada == 4)
        {
            //return std::make_unique<EspecialidadDetailState>(controladora, elementoActual);
        }
        else if (seccionActual == SECCION_CURSOS && opcionSeleccionada == 5)
        {
           // return std::make_unique<CursoDetailState>(controladora, elementoActual);
        }
        return nullptr; // No hay cambio de estado
    }

    int getOpcionSeleccionada() const
    {
        return opcionSeleccionada;
    }
};

/*
void cargarDatosLanding(int maximo) {
        cursosPopularesLandingPage = vector<ElementoMenu>(maximo);
        especializacionesPopularesLandingPage = vector<ElementoMenu>(maximo);

        PriorityQueue<Curso*> priorityCursosLandingPage(maximo);
        PriorityQueue<Especializacion*> priorityEspecializacionesLandingPage(maximo);
        auto cantidad = [](Actividad* a) {
            return a->getCantidadAlumnos();
            };
        priorityCursosLandingPage.llenarDesde<int>(cursosTodos, cantidad);
        priorityEspecializacionesLandingPage.llenarDesde<int>(especializacionesTodos, cantidad);

        vector<string> titulosCursos, descripcionesCursos, titulosEspecializaciones, descripcionesEspecializaciones;
        auto tituloActividad = [](Actividad* a) { // Retorna el dato de titulo
            return a->getTitulo();
            };
        auto descripcionActividad = [](Actividad* a) { // Retorna el dato de inscripción
            return a->getDescripcion();
            };

        // obtener datos
        titulosCursos = priorityCursosLandingPage.extraerDato<string>(tituloActividad);
        titulosEspecializaciones = priorityEspecializacionesLandingPage.extraerDato<string>(tituloActividad);
        descripcionesCursos = priorityCursosLandingPage.extraerDato<string>(descripcionActividad);
        descripcionesEspecializaciones = priorityEspecializacionesLandingPage.extraerDato<string>(descripcionActividad);

        for (int i = 0; i < maximo; i++) {
            //cursosPopularesLandingPage[i].titulo = titulosCursos[i];
            //cursosPopularesLandingPage[i].descripcion = descripcionesCursos[i];
            //especializacionesPopularesLandingPage[i].titulo = titulosEspecializaciones[i];
            //especializacionesPopularesLandingPage[i].descripcion = descripcionesEspecializaciones[i];
        }
    }
*/