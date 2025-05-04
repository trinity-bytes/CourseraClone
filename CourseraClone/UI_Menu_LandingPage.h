#pragma once

// headers propios
#include "ExtendedFunctions.h" // gotoXY, ANCHO_CONSOLA, ALTO_CONSOLA, etc.
#include "UI_Ascii.h"          // UI_LandingPage()

// Headers estándar 
#include "iostream"
#include "vector"
#include "string"
#include "conio.h"    // _kbhit, _getch
#include "fstream"    // ifstream, ofstream
#include "windows.h"  // COORD, GetAsyncKeyState, VK_ESCAPE, Sleep (Necesario para GetAsyncKeyState y COORD)
#include "cstdlib"    // Para system("pause>0")

using namespace std;

/// Constantes globales
// IDs secciones
const int SECCION_CABECERA = 0;
const int SECCION_ESPECIALIDADES = 1;
const int SECCION_CURSOS = 2;
const int TOTAL_SECCIONES = 3;

// Archivos de persistencia
const string ARCHIVO_PERSISTENCIA = "Resources/Data/ultima_posi.txt";
const string ARCHIVO_ESPECIALIDADES = "Resources/Data/especialidades_muestra.txt";
const string ARCHIVO_CURSOS = "Resources/Data/cursos_muestra.txt";

// Items max visibles por seccion (basado en el diseño ASCII)
const int MAX_ELEMENTOS_CABECERA = 3;
const int MAX_ELEMENTOS_ESPECIALIDAD = 3; // 3 rectangulos visibles en el layout
const int MAX_ELEMENTOS_CURSO = 3;    // 3 rectangulos visibles en el layout

/// Estructuras de datos
struct ElementoMenu {
    string titulo;
    string descripcion; // Usado para especialidades y cursos
};

/// Variables globales (para simplicidad en este ejemplo)
// Coordenadas para dibujar contenido dinamico (ajusta segun tu arte ASCII)
COORD coordsElementosCabecera[MAX_ELEMENTOS_CABECERA] = { {10, 4}, {40, 4}, {70, 4} };
COORD coordsTituloEspecialidad[MAX_ELEMENTOS_ESPECIALIDAD] = { {10, 9}, {50, 9}, {90, 9} };
COORD coordsDescEspecialidad[MAX_ELEMENTOS_ESPECIALIDAD] = { {10, 10}, {50, 10}, {90, 10} };
COORD coordsTituloCurso[MAX_ELEMENTOS_CURSO] = { {10, 20}, {50, 20}, {90, 20} };
COORD coordsDescCurso[MAX_ELEMENTOS_CURSO] = { {10, 21}, {50, 21}, {90, 21} };

// Datos cargados
vector<ElementoMenu> especialidades;
vector<ElementoMenu> cursos;

// Estado actual del menu
int seccionActual = SECCION_CABECERA;
int elementoActual = 0;


// --- Prototipos de Funciones ---
int MostrarMenu_LandingPage();
void dibujarInterfaz();
void cargarDatos(const string& nombreArchivo, vector<ElementoMenu>& datos, const vector<ElementoMenu>& datosDefecto);
void cargarPersistencia();
void guardarPersistencia();
int obtenerMaxElementosEnSeccion(int seccion);

// --- Función Principal del Menú Landing Page ---
// Retorna:
// 0 = Salir (ESC presionado)
// 1 = Iniciar Sesion
// 2 = Registrarse
// 3 = Sobre Nosotros
// (Otras secciones no retornan, la funcion espera una seleccion de cabecera o ESC)
int MostrarMenu_LandingPage()
{
    int opc = 0; // Valor por defecto: salir o quedarse en la landing page

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

    // Cargar datos desde archivos (o usar valores por defecto)
    cargarDatos(ARCHIVO_ESPECIALIDADES, especialidades, especialidadesDefecto);
    cargarDatos(ARCHIVO_CURSOS, cursos, cursosDefecto);

    // Cargar última posición seleccionada
    cargarPersistencia();

    bool ejecutandoMenu = true; // Controla el bucle de este menu
    while (ejecutandoMenu)
    {
        dibujarInterfaz(); // Dibuja la interfaz en cada iteracion

        // Manejo de entrada dentro del bucle para controlar el retorno
        if (_kbhit()) // Verificar si se ha pulsado una tecla
        {
            int tecla = _getch(); // Obtener el carácter

            if (tecla == 224) // Tecla extendida (teclas de flecha, etc.)
            {
                tecla = _getch(); // Obtener el código de tecla real
                switch (tecla)
                {
                case 72: // Flecha arriba
                    seccionActual--;
                    if (seccionActual < 0) seccionActual = 0;
                    elementoActual = 0; // Reiniciar elemento al cambiar de sección
                    break;
                case 80: // Flecha abajo
                    seccionActual++;
                    if (seccionActual >= TOTAL_SECCIONES) seccionActual = TOTAL_SECCIONES - 1;
                    elementoActual = 0; // Reiniciar elemento al cambiar de sección
                    break;
                case 75: // Flecha izquierda
                    elementoActual--;
                    if (elementoActual < 0) elementoActual = 0;
                    break;
                case 77: // Flecha derecha
                    elementoActual++;
                    if (elementoActual >= obtenerMaxElementosEnSeccion(seccionActual))
                    {
                        elementoActual = obtenerMaxElementosEnSeccion(seccionActual) > 0 ? obtenerMaxElementosEnSeccion(seccionActual) - 1 : 0;
                    }
                    break;
                }
            }
            else if (tecla == 13) // Tecla Enter
            {
                // Manejar selección: Si es de cabecera, retornar opc y salir del bucle.
                // Si es de otra sección, mostrar mensaje temporal y continuar en el menu.
                switch (seccionActual)
                {
                case SECCION_CABECERA:
                    if (elementoActual >= 0 && elementoActual < MAX_ELEMENTOS_CABECERA) {
                        opc = elementoActual + 1; // 1=Iniciar, 2=Registrarse, 3=Sobre Nosotros
                        ejecutandoMenu = false; // Salir del bucle principal del menu
                    }
                    break;
                case SECCION_ESPECIALIDADES:
                    if (elementoActual >= 0 && elementoActual < especialidades.size()) {
                        // Acción placeholder para especialidad
                        gotoXY(2, ALTO_CONSOLA - 2); // Posicionar para mensaje
                        cout << "Seleccionada Especialidad: " << especialidades[elementoActual].titulo << "       "; // Mensaje temporal, limpiar con espacios
                        gotoXY(2, ALTO_CONSOLA - 1);
                        system("pause>0"); // Esperar tecla
                        // Limpiar mensajes
                        gotoXY(2, ALTO_CONSOLA - 2); cout << string(80, ' ');
                        gotoXY(2, ALTO_CONSOLA - 1); cout << string(80, ' ');
                    }
                    else {
                        // Elemento fuera de rango (no deberia pasar con la navegacion clamped)
                        gotoXY(2, ALTO_CONSOLA - 2);
                        cout << "Seleccion de especialidad no valida." << string(80, ' ');
                        gotoXY(2, ALTO_CONSOLA - 1);
                        system("pause>0"); // Esperar tecla
                        // Limpiar mensajes
                        gotoXY(2, ALTO_CONSOLA - 2); cout << string(80, ' ');
                        gotoXY(2, ALTO_CONSOLA - 1); cout << string(80, ' ');
                    }
                    break;
                case SECCION_CURSOS:
                    if (elementoActual >= 0 && elementoActual < cursos.size()) {
                        // Acción placeholder para curso
                        gotoXY(2, ALTO_CONSOLA - 2); // Posicionar para mensaje
                        cout << "Seleccionado Curso: " << cursos[elementoActual].titulo << "       "; // Mensaje temporal, limpiar con espacios
                        gotoXY(2, ALTO_CONSOLA - 1);
                        system("pause>0"); // Esperar tecla
                        // Limpiar mensajes
                        gotoXY(2, ALTO_CONSOLA - 2); cout << string(80, ' ');
                        gotoXY(2, ALTO_CONSOLA - 1); cout << string(80, ' ');
                    }
                    else {
                        // Elemento fuera de rango
                        gotoXY(2, ALTO_CONSOLA - 2);
                        cout << "Seleccion de curso no valida." << string(80, ' ');
                        gotoXY(2, ALTO_CONSOLA - 1);
                        system("pause>0"); // Esperar tecla
                        // Limpiar mensajes
                        gotoXY(2, ALTO_CONSOLA - 2); cout << string(80, ' ');
                        gotoXY(2, ALTO_CONSOLA - 1); cout << string(80, ' ');
                    }
                    break;
                }
            }
            // GetAsyncKeyState(VK_ESCAPE) se usa en el bucle principal para salir
            // directamente en lugar de _getch() == 27
        }

        // Verificar si Esc fue presionado (permite salir incluso sin _kbhit)
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
            opc = 0; // Opcion 0 para salir
            ejecutandoMenu = false;
        }

        // Pequeño retraso para prevenir alto uso de CPU
        Sleep(50);
    }

    // Guardar última posición seleccionada antes de salir del menu
    guardarPersistencia();

    return opc; // Retorna la opcion seleccionada (0 para salir/otra cosa, 1-3 para cabecera)
}

// Dibuja la interfaz completa incluyendo ASCII base y datos/selección dinámicos
void dibujarInterfaz()
{
    //system("cls"); // Asumiendo que UI_LandingPage() ya limpia la pantalla
    UI_LandingPage(); // Llama a la función de dibujo ASCII base

    // Dibujar Elementos de Cabecera
    // Estos se dibujan directamente ya que no vienen de archivos de datos cargables
    vector<string> elementosCabecera = {
        " Iniciar Sesion ",
        " Registrarse ",
        " Sobre Nosotros "
    };

    for (int i = 0; i < MAX_ELEMENTOS_CABECERA; ++i)
    {
        if (i < elementosCabecera.size()) // Asegurar que no excedemos los elementos definidos
        {
            gotoXY(coordsElementosCabecera[i].X, coordsElementosCabecera[i].Y);
            if (seccionActual == SECCION_CABECERA && elementoActual == i)
            {
                // Si ExtendedFunctions.h tiene cambiarColorTexto
                // cambiarColorTexto(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "->"; // Indicador de seleccion
            }
            else {
                // Si ExtendedFunctions.h tiene restablecerColorTexto
                // restablecerColorTexto();
                cout << "  "; // Espacio para marcador
            }
            cout << elementosCabecera[i];
            // Si ExtendedFunctions.h tiene restablecerColorTexto
            // restablecerColorTexto();
        }
    }

    // Dibujar Especialidades
    for (int i = 0; i < MAX_ELEMENTOS_ESPECIALIDAD; ++i)
    {
        // Solo dibujar si tenemos suficientes datos Y espacio en la UI
        if (i < especialidades.size())
        {
            // Dibujar Título
            gotoXY(coordsTituloEspecialidad[i].X, coordsTituloEspecialidad[i].Y);
            if (seccionActual == SECCION_ESPECIALIDADES && elementoActual == i)
            {
                // cambiarColorTexto(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            }
            else {
                // restablecerColorTexto();
            }
            // Limpiar espacio antes de escribir (manejar titulos de diferente longitud)
            cout << string(20, ' '); gotoXY(coordsTituloEspecialidad[i].X, coordsTituloEspecialidad[i].Y);
            cout << especialidades[i].titulo;

            // Dibujar Descripción
            gotoXY(coordsDescEspecialidad[i].X, coordsDescEspecialidad[i].Y);
            if (seccionActual == SECCION_ESPECIALIDADES && elementoActual == i)
            {
                // cambiarColorTexto(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            }
            else {
                // restablecerColorTexto();
            }
            // Limpiar espacio antes de escribir
            cout << string(20, ' '); gotoXY(coordsDescEspecialidad[i].X, coordsDescEspecialidad[i].Y);
            cout << especialidades[i].descripcion;

            // Dibujar Marcador de Selección
            if (seccionActual == SECCION_ESPECIALIDADES && elementoActual == i)
            {
                gotoXY(coordsTituloEspecialidad[i].X - 3, coordsTituloEspecialidad[i].Y); // Marcador a la izquierda del título
                //establecerColorTexto(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "->";
            }
            else {
                gotoXY(coordsTituloEspecialidad[i].X - 3, coordsTituloEspecialidad[i].Y);
                // restablecerColorTexto();
                cout << "  ";
            }

            // restablecerColorTexto(); // Restablecer color después de dibujar elemento
        }
        else {
            // Limpiar área si no existe elemento de datos para ese slot de UI
            gotoXY(coordsTituloEspecialidad[i].X - 3, coordsTituloEspecialidad[i].Y);
            cout << string(30, ' '); // Limpiar marcador + área de título/desc
            gotoXY(coordsDescEspecialidad[i].X, coordsDescEspecialidad[i].Y);
            cout << string(30, ' ');
        }
    }

    // Dibujar Cursos
    for (int i = 0; i < MAX_ELEMENTOS_CURSO; ++i)
    {
        // Solo dibujar si tenemos suficientes datos Y espacio en la UI
        if (i < cursos.size())
        {
            // Dibujar Título
            gotoXY(coordsTituloCurso[i].X, coordsTituloCurso[i].Y);
            if (seccionActual == SECCION_CURSOS && elementoActual == i)
            {
                // cambiarColorTexto(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            }
            else {
                // restablecerColorTexto();
            }
            // Limpiar espacio antes de escribir
            cout << string(20, ' '); gotoXY(coordsTituloCurso[i].X, coordsTituloCurso[i].Y);
            cout << cursos[i].titulo;

            // Dibujar Descripción
            gotoXY(coordsDescCurso[i].X, coordsDescCurso[i].Y);
            if (seccionActual == SECCION_CURSOS && elementoActual == i)
            {
                // cambiarColorTexto(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            }
            else {
                // restablecerColorTexto();
            }
            // Limpiar espacio antes de escribir
            cout << string(20, ' '); gotoXY(coordsDescCurso[i].X, coordsDescCurso[i].Y);
            cout << cursos[i].descripcion;

            // Dibujar Marcador de Selección
            if (seccionActual == SECCION_CURSOS && elementoActual == i)
            {
                gotoXY(coordsTituloCurso[i].X - 3, coordsTituloCurso[i].Y); // Marcador a la izquierda del título
                //establecerColorTexto(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "->";
            }
            else {
                gotoXY(coordsTituloCurso[i].X - 3, coordsTituloCurso[i].Y);
                // restablecerColorTexto();
                cout << "  ";
            }

            // restablecerColorTexto(); // Restablecer color después de dibujar elemento
        }
        else {
            // Limpiar área si no existe elemento de datos para ese slot de UI
            gotoXY(coordsTituloCurso[i].X - 3, coordsTituloCurso[i].Y);
            cout << string(30, ' '); // Limpiar marcador + área de título/desc
            gotoXY(coordsDescCurso[i].X, coordsDescCurso[i].Y);
            cout << string(30, ' ');
        }
    }

    // Asegurar que el cursor esté en una posición no obstructiva después de dibujar
    gotoXY(0, ALTO_CONSOLA - 1);
}

// Carga datos desde un archivo, usa datos por defecto si el archivo no se encuentra o está vacío
void cargarDatos(const string& nombreArchivo, vector<ElementoMenu>& datos, const vector<ElementoMenu>& datosDefecto)
{
    ifstream archivo(nombreArchivo);
    datos.clear(); // Limpiar datos existentes

    if (archivo.is_open())
    {
        string linea;
        bool datosCargadosDesdeArchivo = false;
        while (getline(archivo, linea))
        {
            size_t posFlecha = linea.find("->");
            if (posFlecha != string::npos)
            {
                ElementoMenu elemento;
                elemento.titulo = linea.substr(0, posFlecha);
                // Eliminar posibles espacios en blanco al inicio/fin del título
                size_t first = elemento.titulo.find_first_not_of(' ');
                if (string::npos != first) {
                    size_t last = elemento.titulo.find_last_not_of(' ');
                    elemento.titulo = elemento.titulo.substr(first, (last - first + 1));
                }
                else {
                    elemento.titulo = ""; // Título vacío si solo son espacios
                }

                elemento.descripcion = linea.substr(posFlecha + 2);
                // Eliminar posibles espacios en blanco al inicio/fin de la descripcion
                first = elemento.descripcion.find_first_not_of(' ');
                if (string::npos != first) {
                    size_t last = elemento.descripcion.find_last_not_of(' ');
                    elemento.descripcion = elemento.descripcion.substr(first, (last - first + 1));
                }
                else {
                    elemento.descripcion = ""; // Descripcion vacia si solo son espacios
                }


                if (!elemento.titulo.empty()) { // Solo agregar si tiene titulo (evitar lineas vacias o invalidas)
                    datos.push_back(elemento);
                    datosCargadosDesdeArchivo = true;
                }

            }
        }
        archivo.close();

        if (!datosCargadosDesdeArchivo) // Si despues de leer el archivo, no se cargo ningun dato valido
        {
            if (datosDefecto.empty()) {
                // Si el archivo estaba vacío y no hay datos por defecto, añadir un marcador
                datos.push_back({ "No se encontraron datos", "" });
            }
            else {
                // El archivo estaba vacío, usar datos por defecto
                datos = datosDefecto;
            }
        }

    }
    else {
        // Archivo no encontrado, usar datos por defecto
        datos = datosDefecto;
    }

    // Asegurar que el tamaño de datos no exceda el espacio asignado en la UI
    // Esto es importante para que obtenerMaxElementosEnSeccion no devuelva un valor mayor al que la UI puede mostrar
    if (nombreArchivo == ARCHIVO_ESPECIALIDADES && datos.size() > MAX_ELEMENTOS_ESPECIALIDAD) {
        datos.resize(MAX_ELEMENTOS_ESPECIALIDAD);
    }
    else if (nombreArchivo == ARCHIVO_CURSOS && datos.size() > MAX_ELEMENTOS_CURSO) {
        datos.resize(MAX_ELEMENTOS_CURSO);
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

// Devuelve el número máximo de elementos *visibles* para una sección dada
// Para especialidades/cursos, es el mínimo entre los datos cargados y el espacio UI
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

// Función para manejar solo la navegación (flechas)
// El manejo de Enter y Esc se hace en MostrarMenu_LandingPage
void manejarNavegacion()
{
    int tecla = _getch(); // Obtener el carácter

    if (tecla == 224) // Tecla extendida (teclas de flecha, etc.)
    {
        tecla = _getch(); // Obtener el código de tecla real
        switch (tecla)
        {
        case 72: // Flecha arriba
            seccionActual--;
            if (seccionActual < 0) seccionActual = 0;
            elementoActual = 0; // Reiniciar elemento al cambiar de sección
            break;
        case 80: // Flecha abajo
            seccionActual++;
            if (seccionActual >= TOTAL_SECCIONES) seccionActual = TOTAL_SECCIONES - 1;
            elementoActual = 0; // Reiniciar elemento al cambiar de sección
            break;
        case 75: // Flecha izquierda
            elementoActual--;
            if (elementoActual < 0) elementoActual = 0;
            break;
        case 77: // Flecha derecha
            elementoActual++;
            if (elementoActual >= obtenerMaxElementosEnSeccion(seccionActual))
            {
                elementoActual = obtenerMaxElementosEnSeccion(seccionActual) > 0 ? obtenerMaxElementosEnSeccion(seccionActual) - 1 : 0;
            }
            break;
        }
    }
}