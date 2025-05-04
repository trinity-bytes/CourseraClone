#pragma once
#include "ExtendedFunctions.h"
#include "UI_Ascii.h"
#include "vector"
#include "string"
#include "conio.h"  // interaccion de menus
#include "fstream"  // interactuar con txt
#include "limits"   // numeric_limits

using namespace std;

/// Constantes globales
// IDs secciones
const int SECCION_CABECERA = 0;
const int SECCION_ESPECIALIDADES = 1;
const int SECCION_CURSOS = 2;
const int TOTAL_SECCIONES = 3;

// Archivos de persistencia
const string ARCHIVO_PERSISTENCIA = "ultima_posi.txt";
const string ARCHIVO_ESPECIALIDADES = "especialidades_muestra.txt";
const string ARCHIVO_CURSOS = "cursos_muestra.txt";

// Items max visibles por seccion
const int MAX_ELEMENTOS_CABECERA = 3;
const int MAX_ELEMENTOS_ESPECIALIDAD = 3; // 3 rectangulos
const int MAX_ELEMENTOS_CURSO = 3;   // 3 rectangulos

/// Estructuras de datos
struct ElementoMenu {
    string titulo;
    string descripcion; // Usado para especialidades y cursos
};

/// Variables globales
// Coordenadas para dibujar contenido dinamico
COORD coordsElementosCabecera[MAX_ELEMENTOS_CABECERA] = { {10, 4}, {40, 4}, {70, 4} }; 
COORD coordsTituloEspecialidad[MAX_ELEMENTOS_ESPECIALIDAD] = { {10, 9}, {50, 9}, {90, 9} };
COORD coordsDescEspecialidad[MAX_ELEMENTOS_ESPECIALIDAD] = { {10, 10}, {50, 10}, {90, 10} }; 
COORD coordsTituloCurso[MAX_ELEMENTOS_CURSO] = { {10, 20}, {50, 20}, {90, 20} }; 
COORD coordsDescCurso[MAX_ELEMENTOS_CURSO] = { {10, 21}, {50, 21}, {90, 21} }; 

vector<ElementoMenu> especialidades;
vector<ElementoMenu> cursos;
int seccionActual = SECCION_CABECERA;
int elementoActual = 0;


// --- Prototipos de Funciones ---
void dibujarInterfaz();
void cargarDatos(const string& nombreArchivo, vector<ElementoMenu>& datos, const vector<ElementoMenu>& datosDefecto);
void cargarPersistencia();
void guardarPersistencia();
int obtenerMaxElementosEnSeccion(int seccion);
void manejarEntrada();
void manejarSeleccion(int seccion, int elemento);
void mostrarMensaje(const string& msg);

short MostrarMenu_LandingPage()
{
	short opc = 0;

    // Datos por defecto si los archivos faltan o están vacíos
    vector<ElementoMenu> especialidadesDefecto = {
        {"Desarrollo Web", "Frontend & Backend"},
        {"Ciencia de Datos", "Análisis y ML"},
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

    bool ejecutando = true;
    while (ejecutando) 
    {
        dibujarInterfaz();
        manejarEntrada();
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) { // Verificar si Esc fue presionado durante manejarEntrada
            ejecutando = false;
        }
        // Pequeño retraso para prevenir alto uso de CPU
        Sleep(50);
    }

    // Guardar última posición seleccionada antes de salir
    guardarPersistencia();

    return opc;
}

// Dibuja la interfaz completa incluyendo ASCII base y datos/selección dinámicos
void dibujarInterfaz() 
{
	UI_LandingPage(); // Llamar a la función de dibujo ASCII

    // Dibujar Elementos de Cabecera
    vector<string> elementosCabecera = { 
        " Iniciar Sesion ", 
        " Registrarse ", 
        " Sobre Nosotros " 
    };

    for (int i = 0; i < MAX_ELEMENTOS_CABECERA; ++i) 
    {
        if (i < elementosCabecera.size()) 
        {
            gotoXY(coordsElementosCabecera[i].X, coordsElementosCabecera[i].Y);
            if (seccionActual == SECCION_CABECERA && elementoActual == i) 
            {
                cout << "-> ";
            }
            else {
                cout << "   "; // Espacio para marcador
            }
            cout << elementosCabecera[i];
        }
    }

    // Dibujar Especialidades
    for (int i = 0; i < MAX_ELEMENTOS_ESPECIALIDAD; ++i) 
    {
        if (i < especialidades.size()) 
        {
            // Dibujar Título
            gotoXY(coordsTituloEspecialidad[i].X, coordsTituloEspecialidad[i].Y);
            if (seccionActual == SECCION_ESPECIALIDADES && elementoActual == i) 
            {
                // cambiar color texto
            }
            else 
            {
                // reestablecer color
            }
            cout << especialidades[i].titulo;

            // Dibujar Descripción (dividir en líneas si es necesario, o simplemente imprimir)
            gotoXY(coordsDescEspecialidad[i].X, coordsDescEspecialidad[i].Y);
            if (seccionActual == SECCION_ESPECIALIDADES && elementoActual == i) 
            {
                // cambiar color texto
            }
            else 
            {
                // reestablecer color
            }
            cout << especialidades[i].descripcion;

            // Dibujar Marcador de Selección
            if (seccionActual == SECCION_ESPECIALIDADES && elementoActual == i) 
            {
                gotoXY(coordsTituloEspecialidad[i].X - 3, coordsTituloEspecialidad[i].Y); // Marcador a la izquierda del título
                cout << "->";
            }
            else {
                gotoXY(coordsTituloEspecialidad[i].X - 3, coordsTituloEspecialidad[i].Y);
                cout << "  ";
            }

			// Restablecer color
        }
        else {
            // Limpiar área si no existe elemento
            gotoXY(coordsTituloEspecialidad[i].X - 3, coordsTituloEspecialidad[i].Y);
            cout << "                                    "; // Limpiar marcador + área de título/desc
            gotoXY(coordsDescEspecialidad[i].X, coordsDescEspecialidad[i].Y);
            cout << "                                    ";
        }
    }

    // Dibujar Cursos
    for (int i = 0; i < MAX_ELEMENTOS_CURSO; ++i) 
    {
        if (i < cursos.size()) 
        {
            // Dibujar Título
            gotoXY(coordsTituloCurso[i].X, coordsTituloCurso[i].Y);
            if (seccionActual == SECCION_CURSOS && elementoActual == i) 
            {
				// cambiarColorTexto(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            }
            else 
            {
				// restablecerColorTexto();
            }
            cout << cursos[i].titulo;

            // Dibujar Descripción (dividir en líneas si es necesario, o simplemente imprimir)
            gotoXY(coordsDescCurso[i].X, coordsDescCurso[i].Y);
            if (seccionActual == SECCION_CURSOS && elementoActual == i) 
            {
				// cambiarColorTexto(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            }
            else 
            {
                // restablecerColorTexto();
            }
            cout << cursos[i].descripcion;

            // Dibujar Marcador de Selección
            if (seccionActual == SECCION_CURSOS && elementoActual == i) 
            {
                gotoXY(coordsTituloCurso[i].X - 3, coordsTituloCurso[i].Y); // Marcador a la izquierda del título
                //establecerColorTexto(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
                cout << "->";
            }
            else 
            {
                gotoXY(coordsTituloCurso[i].X - 3, coordsTituloCurso[i].Y);
               // restablecerColorTexto();
                cout << "  ";
            }

            //restablecerColorTexto();
        }
        else 
        {
            // Limpiar área si no existe elemento
            gotoXY(coordsTituloCurso[i].X - 3, coordsTituloCurso[i].Y);
            cout << "                                    "; // Limpiar marcador + área de título/desc
            gotoXY(coordsDescCurso[i].X, coordsDescCurso[i].Y);
            cout << "                                    ";
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
                elemento.descripcion = linea.substr(posFlecha + 2);
                datos.push_back(elemento);
                datosCargadosDesdeArchivo = true;
            }
        }
        archivo.close();

        if (!datosCargadosDesdeArchivo && datosDefecto.empty()) 
        {
            // Si el archivo estaba vacío y no hay datos por defecto, añadir un marcador
            datos.push_back({ "No se encontraron datos", "" });
        }
        else if (!datosCargadosDesdeArchivo && !datosDefecto.empty()) 
        {
            // El archivo estaba vacío, usar datos por defecto
            datos = datosDefecto;
        }

    }
    else {
        // Archivo no encontrado, usar datos por defecto
        datos = datosDefecto;
    }

    // Asegurar que el tamaño de datos no exceda el espacio asignado en la UI
    if (datos.size() > (nombreArchivo == ARCHIVO_ESPECIALIDADES ? MAX_ELEMENTOS_ESPECIALIDAD : MAX_ELEMENTOS_CURSO)) 
    {
        datos.resize(nombreArchivo == ARCHIVO_ESPECIALIDADES ? MAX_ELEMENTOS_ESPECIALIDAD : MAX_ELEMENTOS_CURSO);
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
                if (elementoCargado >= 0 && elementoCargado < obtenerMaxElementosEnSeccion(seccionActual)) 
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

// Devuelve el número máximo de elementos visibles para una sección dada
int obtenerMaxElementosEnSeccion(int seccion) 
{
    switch (seccion) 
    {
        case SECCION_CABECERA: return MAX_ELEMENTOS_CABECERA;
        case SECCION_ESPECIALIDADES: return static_cast<int>(especialidades.size()); // Aca el máximo de elementos está limitado por datos cargados Y espacio UI
        case SECCION_CURSOS: return static_cast<int>(cursos.size());
        default: return 0;
    }
}

// Maneja la entrada de teclado para navegación y selección
void manejarEntrada() 
{
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
            manejarSeleccion(seccionActual, elementoActual);
        }
        else if (tecla == 27) // Tecla Esc
        { 
            // El bucle principal verifica GetAsyncKeyState(VK_ESCAPE) para salir
        }
    }
}

// Función de marcador de posición para manejar la acción de selección
void manejarSeleccion(int seccion, int elemento) 
{
    string mensaje = "Seleccionado: ";
    switch (seccion) 
    {
        case SECCION_CABECERA:
            if (elemento == 0) mensaje += "Iniciar Sesion";
            else if (elemento == 1) mensaje += "Registrarse";
            else if (elemento == 2) mensaje += "Sobre Nosotros";
            break;
        case SECCION_ESPECIALIDADES:
            if (elemento >= 0 && elemento < especialidades.size()) {
                mensaje += "Especialidad: " + especialidades[elemento].titulo;
            }
            else {
                mensaje += "Especialidad no valida";
            }
            break;
        case SECCION_CURSOS:
            if (elemento >= 0 && elemento < cursos.size()) {
                mensaje += "Curso: " + cursos[elemento].titulo;
            }
            else {
                mensaje += "Curso no valido";
            }
            break;
    }

    mostrarMensaje(mensaje); // Mostrar el mensaje de selección temporalmente
}

// Muestra un mensaje temporal en la parte inferior de la pantalla
void mostrarMensaje(const string& msg) 
{
    // Guardar posición actual del cursor y atributos de texto
    //CONSOLE_SCREEN_BUFFER_INFO csbi;
    //GetConsoleScreenBufferInfo(manejadorConsola, &csbi);
    //COORD posOriginal = csbi.dwCursorPosition;
    //WORD atributosOriginales = csbi.wAttributes;

    // Limpiar la línea de mensaje
    gotoXY(0, ALTO_CONSOLA - 2);
    for (int i = 0; i < ANCHO_CONSOLA; ++i) cout << " ";

    // Imprimir el mensaje
    gotoXY(2, ALTO_CONSOLA - 2); // Imprimir cerca de la parte inferior
    //establecerColorTexto(FOREGROUND_YELLOW | FOREGROUND_INTENSITY); // Resaltar mensaje
    cout << msg;
    //restablecerColorTexto();

    // Restaurar posición del cursor y atributos
    //gotoXY(posOriginal.X, posOriginal.Y);
    //SetConsoleTextAttribute(manejadorConsola, atributosOriginales);

    // Esperar una pulsación de tecla para continuar (simular entrada a una nueva pantalla)
    gotoXY(2, ALTO_CONSOLA - 1);
    cout << "Presione cualquier tecla para continuar...";
    system("pause>0"); // Esperar pulsación de tecla

    // Limpiar las líneas de mensaje y prompt
    gotoXY(0, ALTO_CONSOLA - 2);
    for (int i = 0; i < ANCHO_CONSOLA; ++i) cout << " ";
    gotoXY(0, ALTO_CONSOLA - 1);
    for (int i = 0; i < ANCHO_CONSOLA; ++i) cout << " ";

    // Restaurar posición original (puede ser complicado, más simple simplemente redibujar la UI después)
    // Para este ejemplo, simplemente limpiamos las áreas de mensaje y prompt.
}