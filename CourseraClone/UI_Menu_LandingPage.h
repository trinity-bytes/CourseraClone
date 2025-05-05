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
#include "sstream"    // Para stringstream (usado en formatearDescripcion)

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

// Caracteres maximos que pueden entrar por cuadro de especialidad o curso
const int MAX_ANCHO_CARACTERES_CUADRO = 30; // Maximo de caracteres por linea
const int MAX_ALTO_CARACTERES_CUADRO = 4;   // Maximo de saltos de linea

const vector<string> ELEMENTOS_CABECERA = {
    " Iniciar Sesion ",
    " Registrarse ",
    " Sobre Nosotros "
};

//! se esta jalando ALTO_CONSOLA de ExtendedFunctions.h

/// Estructuras de datos
struct ElementoMenu {
    string titulo;
    string descripcion; // Usado para especialidades y cursos
};

/// Variables globales (para simplicidad en este ejemplo)
// Coordenadas para dibujar contenido dinamico (ajusta segun tu arte ASCII)
COORD coordsElementosCabecera[MAX_ELEMENTOS_CABECERA] = { {67, 3}, {84, 3}, {98, 3} };
COORD coordsTituloEspecialidad[MAX_ELEMENTOS_ESPECIALIDAD] = { {11, 15}, {45, 15}, {79, 15} };
COORD coordsDescEspecialidad[MAX_ELEMENTOS_ESPECIALIDAD] = { {11, 17}, {45, 17}, {79, 17} };
COORD coordsTituloCurso[MAX_ELEMENTOS_CURSO] = { {11, 25}, {45, 25}, {79, 25} };
COORD coordsDescCurso[MAX_ELEMENTOS_CURSO] = { {11, 27}, {45, 27}, {79, 27} };

// Datos cargados
vector<ElementoMenu> especialidades;
vector<ElementoMenu> cursos;

// Estado actual del menu
int seccionActual = SECCION_CABECERA;
int elementoActual = 0;

// Variables para seguimiento del estado anterior de selección
int seccionAnterior = -1;
int elementoAnterior = -1;

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

/// --- Prototipos de Funciones ---
int MostrarMenu_LandingPage();
void dibujarInterfazCompleta();
void actualizarSeleccion();
void actualizarElementoCabecera(
    int indice, 
    bool seleccionado
);
void actualizarElementoEspecialidad(
    int indice, 
    bool seleccionado
);
void actualizarElementoCurso(
    int indice, 
    bool seleccionado
);
void dibujarInterfazCompleta();
void cargarDatos(
    const string& nombreArchivo, 
    vector<ElementoMenu>& datos, 
    const vector<ElementoMenu>& datosDefecto
);
void cargarPersistencia();
void guardarPersistencia();
int obtenerMaxElementosEnSeccion(int seccion);
string formatearDescripcion(
    const string& texto, 
    int anchoMax, 
    int altoMax
);
void actualizarElementoGenerico(
    const COORD& coordTitulo,
    const COORD& coordDesc,
    const ElementoMenu& elemento,
    bool seleccionado
);

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
    bool ejecutandoMenu = true; // Controla el bucle de este menu

    // Cargar datos desde archivos (o usar valores por defecto)
    cargarDatos(ARCHIVO_ESPECIALIDADES, especialidades, especialidadesDefecto);
    cargarDatos(ARCHIVO_CURSOS, cursos, cursosDefecto);

    // Cargar última posición seleccionada
    cargarPersistencia();
    
    // Inicializar el estado de selección
    seccionAnterior = seccionActual;
    elementoAnterior = elementoActual;

    // Dibujar interfaz base una sola vez antes de entrar al bucle
    system("cls");
    UI_LandingPage(); // Llama a la función de dibujo ASCII base una única vez
    dibujarInterfazCompleta(); // Dibujamos la interfaz completa por primera vez
    
    while (ejecutandoMenu)
    {
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
                    actualizarSeleccion();
                    break;
                case 80: // Flecha abajo
                    seccionActual++;
                    if (seccionActual >= TOTAL_SECCIONES) seccionActual = TOTAL_SECCIONES - 1;
                    elementoActual = 0; // Reiniciar elemento al cambiar de sección
                    actualizarSeleccion();
                    break;
                case 75: // Flecha izquierda
                    elementoActual--;
                    if (elementoActual < 0) elementoActual = 0;
                    actualizarSeleccion();
                    break;
                case 77: // Flecha derecha
                    elementoActual++;
                    if (elementoActual >= obtenerMaxElementosEnSeccion(seccionActual))
                    {
                        elementoActual = obtenerMaxElementosEnSeccion(seccionActual) > 0 ? obtenerMaxElementosEnSeccion(seccionActual) - 1 : 0;
                    }
                    actualizarSeleccion();
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
                    if (elementoActual >= 0 && elementoActual < MAX_ELEMENTOS_CABECERA) 
                    {
                        opc = elementoActual + 1; // 1=Iniciar, 2=Registrarse, 3=Sobre Nosotros
                        ejecutandoMenu = false; // Salir del bucle principal del menu
                    }
                    break;
                case SECCION_ESPECIALIDADES:
                    if (elementoActual >= 0 && elementoActual < especialidades.size()) 
                    {
                        // Acción placeholder para especialidad
                        gotoXY(2, ALTO_CONSOLA - 2);
                        cout << "Seleccionada Especialidad: " << especialidades[elementoActual].titulo << "       ";
                        gotoXY(2, ALTO_CONSOLA - 1);
                        system("pause>0");
                        // Limpiar mensajes
                        gotoXY(2, ALTO_CONSOLA - 2); cout << string(80, ' ');
                        gotoXY(2, ALTO_CONSOLA - 1); cout << string(80, ' ');
                    }
                    break;
                case SECCION_CURSOS:
                    if (elementoActual >= 0 && elementoActual < cursos.size()) 
                    {
                        // Acción placeholder para curso
                        gotoXY(2, ALTO_CONSOLA - 2);
                        cout << "Seleccionado Curso: " << cursos[elementoActual].titulo << "       ";
                        gotoXY(2, ALTO_CONSOLA - 1);
                        system("pause>0");
                        // Limpiar mensajes
                        gotoXY(2, ALTO_CONSOLA - 2); cout << string(80, ' ');
                        gotoXY(2, ALTO_CONSOLA - 1); cout << string(80, ' ');
                    }
                    break;
                }
            }
        }
                
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) // Verificar si Esc fue presionado (permite salir incluso sin _kbhit)
        {
            opc = 0; // Opcion 0 para salir
            ejecutandoMenu = false;
        }

        // Pequeño retraso para prevenir alto uso de CPU
        Sleep(50);
    }
       
    guardarPersistencia();  // Guardar última posición seleccionada antes de salir del menu

    return opc; // Retorna la opcion seleccionada (0 para salir/otra cosa, 1-3 para cabecera)
}

// Función que actualiza solo los elementos de la selección que cambiaron
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

/// Funciones auxiliares para actualizar cada tipo de elemento
void actualizarElementoCabecera(int indice, bool seleccionado)
{
    if (indice < 0 || indice >= MAX_ELEMENTOS_CABECERA) return;

    gotoXY(coordsElementosCabecera[indice].X, coordsElementosCabecera[indice].Y);

    if (seleccionado) SetConsoleColor(1, 15); // Color de texto SELECCION
    else SetConsoleColor(15, 1); // Color por defecto

    cout << ELEMENTOS_CABECERA[indice];
	SetConsoleColor(15, 1); // Restablecer color por defecto
}

void actualizarElementoEspecialidad(int indice, bool seleccionado)
{
    if (indice < 0 || indice >= especialidades.size())
        return;

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
    if (indice < 0 || indice >= cursos.size())
        return;

    // Actualizar contenido usando función genérica
    actualizarElementoGenerico(
        coordsTituloCurso[indice],
        coordsDescCurso[indice],
        cursos[indice],
        seleccionado
    );
}

void actualizarElementoGenerico(const COORD& coordTitulo, const COORD& coordDesc, const ElementoMenu& elemento, bool seleccionado) 
{
    // Actualizar título
    gotoXY(coordTitulo.X, coordTitulo.Y);
    cout << string(20, ' ');
    gotoXY(coordTitulo.X, coordTitulo.Y);

    if (seleccionado) SetConsoleColor(1, 15); // Color de SELECCIONADO
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

// Dibuja la interfaz completa la primera vez (solo se llama una vez)
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