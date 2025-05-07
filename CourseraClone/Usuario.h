#pragma once

// Headers propios
#include "algoritmosBusqueda.h"

// Headers de la libreria estandar
#include "iostream"
#include "fstream"
#include "string"
#include "vector"     // Podr�a ser �til para manejar indices temporalmente en memoria
#include "cstring"    // Para strncpy, strncmp, memset
#include "limits"     // Para std::numeric_limits
#include "algorithm"  // Para std::sort si manejamos indices en memoria (opcional)

using namespace std;

/// --- Constantes y Enums para mejorar legibilidad y mantenibilidad ---
// Maxima longitud para los campos de caracteres en structs binarios
const int MAX_FIELD_LEN = 50;

// Rutas de archivos
const string DATA_DIR = "Resources/Data/";
const string INDEX_DIR = DATA_DIR + "indices/";
const string EMPRESA_DATA_FILE = DATA_DIR + "usuarios_empresa.dat";
const string ESTUDIANTE_DATA_FILE = DATA_DIR + "usuarios_estudiante.dat";
const string EMPRESA_INDEX_FILE = INDEX_DIR + "usuarios_empresa.dat";
const string ESTUDIANTE_INDEX_FILE = INDEX_DIR + "usuarios_estudiante.dat";

// Tipos de usuario (usamos enum para claridad)
enum class TipoUsuario 
{
    ESTUDIANTE = 1,
    EMPRESA = 2
};

// Estados posibles del login (usamos enum para claridad)
enum class LoginStatus 
{
    SUCCESS = 0,
    USER_NOT_FOUND = 1,
    WRONG_PASSWORD = 2,
    FILE_ERROR = 3 // Agregado para errores de archivo
};

/// --- Structs para la representaci�n en archivos binarios ---
// Struct para datos de usuario en el archivo principal (.dat)
struct UsuarioBinario 
{
    char nombreCompleto[MAX_FIELD_LEN];
    char nombreDeUsuario[MAX_FIELD_LEN];
    char contrasenaHash[MAX_FIELD_LEN]; // Guardamos un HASH de la contrase�a

    // Constructor por defecto: Inicializa todo a cero
    UsuarioBinario() 
    {
        memset(nombreCompleto, 0, sizeof(nombreCompleto));
        memset(nombreDeUsuario, 0, sizeof(nombreDeUsuario));
        memset(contrasenaHash, 0, sizeof(contrasenaHash));
    }

    // Constructor parametrizado (usado para crear el struct antes de guardar)
    // Este constructor se debe llamar con el HASH de la contrase�a y no en texto plano OwO
    UsuarioBinario(
        const string& nombreCompletoStr, 
        const string& nombreUsuarioStr, 
        const string& contrasenaHashStr) 
    {
        // Copia segura de cadenas, asegurando null termination
        strncpy(nombreCompleto, nombreCompletoStr.c_str(), MAX_FIELD_LEN - 1);
        nombreCompleto[MAX_FIELD_LEN - 1] = '\0';

        strncpy(nombreDeUsuario, nombreUsuarioStr.c_str(), MAX_FIELD_LEN - 1);
        nombreDeUsuario[MAX_FIELD_LEN - 1] = '\0';

        strncpy(contrasenaHash, contrasenaHashStr.c_str(), MAX_FIELD_LEN - 1);
        contrasenaHash[MAX_FIELD_LEN - 1] = '\0';
    }
};

// Struct para entradas del archivo �ndice (.dat)
struct UsuarioIndex 
{
    char nombreDeUsuario[MAX_FIELD_LEN];
    int offset; // Offset en bytes en el archivo de datos principal

    // Constructor por defecto
    UsuarioIndex() : offset(0) 
    {
        memset(nombreDeUsuario, 0, sizeof(nombreDeUsuario)); // Inicializa nombre a cero
    }

    // Constructor parametrizado (usado para crear el struct antes de guardar en �ndice)
    UsuarioIndex(const string& nombreUsuarioStr, int _offset) : offset(_offset) 
    {
        // Copia segura de cadena, asegurando null termination
        strncpy(nombreDeUsuario, nombreUsuarioStr.c_str(), MAX_FIELD_LEN - 1);
        nombreDeUsuario[MAX_FIELD_LEN - 1] = '\0';
    }

    // Funci�n de comparaci�n est�tica para usar con busquedaBinaria
    // Compara por nombre de usuario
    static int compare(const UsuarioIndex& a, const UsuarioIndex& b) {
        return strncmp(a.nombreDeUsuario, b.nombreDeUsuario, MAX_FIELD_LEN);
    }

    static int compare(const string& a, const UsuarioIndex& b) {
        return strncmp(a.c_str(), b.nombreDeUsuario, MAX_FIELD_LEN);
    }
};


/// --- Clase Usuario ---
class Usuario {
private: // Miembros protegidos no tienen mucho sentido si no hay herencia planeada y usada
    int id; 
    TipoUsuario tipoUsuario;
    string nombreCompleto, username;
    string contrasenaHash; 

public:
    // Constructor por default UwU
    Usuario() : id(0), tipoUsuario(TipoUsuario::ESTUDIANTE) {}

    // Constructor principal 
    Usuario(
        int _id, 
        TipoUsuario _tipoUsuario, 
        const string& _nombreCompleto, 
        const string& _username, 
        const string& _contrasenaHash) : id(_id), 
        tipoUsuario(_tipoUsuario), 
        nombreCompleto(_nombreCompleto), 
        username(_username), 
        contrasenaHash(_contrasenaHash)
    { }
private:
    // Funci�n de hashing de contrase�a pero de mentiritas nomas UwU*
    static string hashContrasena(const string& contrasena) 
    {
		string mockHash = "atalapastrukaGohGohGoh"; // Hash inicial con la palabra de seguridad xd
        mockHash += contrasena.substr(0, min((int)contrasena.length(), MAX_FIELD_LEN - (int)mockHash.length() - 1));
        return mockHash;
    }

    // Convierte objeto Usuario a struct UsuarioBinario
    UsuarioBinario toUsuarioBinario() const 
    {
        // Esto funciona si this->contrasenaHash ya contiene el hash
        return UsuarioBinario(nombreCompleto, username, contrasenaHash);
    }

    // Convierte struct UsuarioBinario a objeto Usuario
    // Necesita el ID y tipo de usuario, que no est�n en UsuarioBinario
    static Usuario fromUsuarioBinario(const UsuarioBinario& binario, int id, TipoUsuario tipo) 
    {
        // Funciona la lectura del archivo nos da un struct v�lido.
        string nomCompleto(binario.nombreCompleto, strnlen(binario.nombreCompleto, MAX_FIELD_LEN));
        string user(binario.nombreDeUsuario, strnlen(binario.nombreDeUsuario, MAX_FIELD_LEN));
        string hash(binario.contrasenaHash, strnlen(binario.contrasenaHash, MAX_FIELD_LEN));

        return Usuario(id, tipo, nomCompleto, user, hash);
    }

    // Convierte objeto Usuario a struct UsuarioIndex
    UsuarioIndex toUsuarioIndex(int offset) const 
    {
        return UsuarioIndex(username, offset);
    }

    // Convierte struct UsuarioIndex a string de nombre de usuario
    static string getUsernameFromIndex(const UsuarioIndex& index) 
    {
        // posible basura si el char[] no esta bien terminado.
        return string(index.nombreDeUsuario, strnlen(index.nombreDeUsuario, MAX_FIELD_LEN));
    }

    // Helper para obtener la ruta del archivo de datos seg�n el tipo de usuario
    static string getDataFilePath(TipoUsuario tipo) 
    {
        return (tipo == TipoUsuario::EMPRESA) ? EMPRESA_DATA_FILE : ESTUDIANTE_DATA_FILE;
    }

    static string getIndexFilePath(TipoUsuario tipo) 
    {
        return (tipo == TipoUsuario::EMPRESA) ? EMPRESA_INDEX_FILE : ESTUDIANTE_INDEX_FILE;
    }
public:
    // --- M�todo para guardar un usuario ---
    void guardar() 
    {
        // NOTA: Este m�todo guarda la *instancia actual* del usuario.
        // Se asume que el ID y tipo ya est�n establecidos y que la contrase�a
        // ya fue hasheada y guardada en contrasenaHash.

        // 1. Guardar en el archivo de datos principal (.dat)
        string dataFilePath = getDataFilePath(tipoUsuario);
        ofstream dataFile(dataFilePath, ios::binary | ios::app); // Abre para agregar al final
        int offsetRegistro = 0; // Offset donde se escribir� este registro

        if (!dataFile.is_open()) {
            cerr << "Error al abrir archivo de datos: " << dataFilePath << endl;
            // Deber�amos manejar este error, quiz�s lanzando una excepci�n o retornando false
            return;
        }

        // Obtener el offset actual antes de escribir
        dataFile.seekp(0, ios::end);
        offsetRegistro = dataFile.tellp();

        // Crear la struct binaria para guardar (asumiendo que this->contrasenaHash ya tiene el hash)
        UsuarioBinario nuevoBinario = toUsuarioBinario();
        dataFile.write(reinterpret_cast<const char*>(&nuevoBinario), sizeof(nuevoBinario));
        dataFile.close(); // El destructor del stream tambi�n cerrar�a el archivo


        // 2. Guardar e insertar en el archivo de �ndice (.dat) (mantenido ordenado)
        string indexFilePath = getIndexFilePath(tipoUsuario);
        fstream indexFile(indexFilePath, ios::binary | ios::in | ios::out); // Abrir para leer y escribir

        // Si el archivo no existe o falla la apertura inicial en in|out, intentamos crearlo
        if (!indexFile.is_open()) {
            // Intentar abrir en modo out para crearlo
            ofstream createIndexFile(indexFilePath, ios::binary | ios::out);
            if (!createIndexFile.is_open()) {
                cerr << "Error al crear archivo de indice: " << indexFilePath << endl;
                // Manejo de error
                return;
            }
            createIndexFile.close(); // Cerrar despu�s de crear

            // Ahora intentar abrir de nuevo en modo in|out
            indexFile.open(indexFilePath, ios::binary | ios::in | ios::out);
            if (!indexFile.is_open()) {
                cerr << "Error al reabrir archivo de indice despues de crear: " << indexFilePath << endl;
                // Manejo de error
                return;
            }
        }

        // Calcular la cantidad actual de registros en el �ndice
        indexFile.seekg(0, ios::end);
        int cantidad = indexFile.tellg() / sizeof(UsuarioIndex);
        indexFile.seekg(0, ios::beg); // Volver al principio

        // Crear la entrada del �ndice para el nuevo usuario
        UsuarioIndex nuevoIndex = toUsuarioIndex(offsetRegistro);

        // Lambda para la b�squeda binaria de la posici�n de inserci�n
        // Queremos encontrar la primera posici�n `p` tal que el nombre de usuario del
        // nuevo �ndice sea menor o igual al nombre de usuario en la posici�n `p`.
        // Esto nos da el punto de inserci�n correcto para mantener el orden ascendente.
        // Esta lambda se pasa a la funci�n busquedaBinaria (asumimos que esta funci�n
        // encuentra el primer �ndice donde la lambda devuelve true en el rango [inicio, fin]).
        // La lambda recibe la posici�n `p` a verificar.
        auto predicadoInsercion = [&](int pos) {
            if (pos < 0 || pos >= cantidad) { // Fuera de rango si la lista est� vac�a
                return true; // Inserta al principio si la lista est� vac�a
            }
            UsuarioIndex temp;
            indexFile.seekg(pos * sizeof(UsuarioIndex), ios::beg);
            indexFile.read(reinterpret_cast<char*>(&temp), sizeof(UsuarioIndex));
            indexFile.clear(); // Limpiar flags de error/eof despu�s de leer

            // Comparar el nombre del nuevo usuario con el de la posici�n actual
            // strncmp(a, b, n) regresa <0 si a < b, 0 si a == b, >0 si a > b
            // Queremos el primer pos donde nuevoIndex.username <= temp.username
            // Es decir, donde strncmp(nuevoIndex.username, temp.username, ...) <= 0 es true.
            return strncmp(nuevoIndex.nombreDeUsuario, temp.nombreDeUsuario, MAX_FIELD_LEN) <= 0;
            };

        // Usar busquedaBinaria para encontrar la posici�n de inserci�n
        // Asumimos que busquedaBinaria(inicio, fin, predicado) encuentra el
        // primer �ndice `i` en el rango [inicio, fin] donde predicado(i) es true.
        // Si la lista est� vac�a, cantidad es 0, cantidad-1 es -1.
        // La b�squeda debe manejar el rango vac�o [0, -1].
        int posInsercion = 0; // Posici�n por defecto si el archivo est� vac�o
        if (cantidad > 0) {
            // Rango [0, cantidad - 1]. busquedaBinaria debe manejar este rango.
            // Si nuestro busquedaBinaria no maneja inicio > fin, necesitamos ajustarlo.
            // Un busqueda binaria para lower_bound (punto de insercion) tipico seria:
            // low = inicio, high = fin + 1. while(low < high) mid = low + (high-low)/2.
            // if (predicado(mid)) high = mid; else low = mid + 1. return low.
            // Asumiendo busquedaBinaria(inicio, fin, predicado) implementa lower_bound-like:
            posInsercion = busquedaBinaria(0, cantidad - 1, predicadoInsercion);
            // Si busquedaBinaria retorna cantidad, significa que el nuevo elemento es mayor
            // que todos los existentes y debe ir al final. El loop de shift lo manejar�.
        }
        else {
            posInsercion = 0; // Primer elemento en archivo vac�o
        }


        // Mover elementos para hacer espacio en el archivo de �ndice
        // Desde el final hacia la posici�n de inserci�n
        for (int i = cantidad - 1; i >= posInsercion; --i) {
            UsuarioIndex temp;
            // Leer el elemento actual
            indexFile.seekg(i * sizeof(UsuarioIndex), ios::beg);
            indexFile.read(reinterpret_cast<char*>(&temp), sizeof(UsuarioIndex));
            indexFile.clear(); // Limpiar flags despu�s de leer

            // Escribir el elemento en la siguiente posici�n (corriendo uno a la derecha)
            indexFile.seekp((i + 1) * sizeof(UsuarioIndex), ios::beg);
            indexFile.write(reinterpret_cast<const char*>(&temp), sizeof(UsuarioIndex));
            indexFile.clear(); // Limpiar flags despu�s de escribir
        }

        // Escribir el nuevo �ndice en la posici�n de inserci�n encontrada
        indexFile.seekp(posInsercion * sizeof(UsuarioIndex), ios::beg);
        indexFile.write(reinterpret_cast<const char*>(&nuevoIndex), sizeof(nuevoIndex));
        indexFile.clear(); // Limpiar flags despu�s de escribir

        // El destructor de fstream cerrar� el archivo
    }

    /// --- M�todo est�tico para manejar el login ---
    // Retorna un c�digo de estado y, si es exitoso, carga los datos del usuario en usuarioLogueado
    static LoginStatus login(Usuario& usuarioLogueado, TipoUsuario tipoUsuario) {
        string userInput, passInput;

        cout << "Username: ";
        cin >> userInput;
        // Limpiar el buffer de entrada para evitar problemas con getline o futuras lecturas
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Password: ";
        // En un sistema real, no mostrar la contrase�a en pantalla (usar t�cnicas de entrada segura)
        cin >> passInput;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');


        string indexFilePath = getIndexFilePath(tipoUsuario);
        ifstream indexFile(indexFilePath, ios::binary); // Abrir solo para leer

        if (!indexFile.is_open()) {
            cerr << "Error al abrir archivo de indice para login: " << indexFilePath << endl;
            return LoginStatus::FILE_ERROR; // Indicar error de archivo
        }

        indexFile.seekg(0, ios::end);
        int cantidad = indexFile.tellg() / sizeof(UsuarioIndex);
        indexFile.seekg(0, ios::beg); // Volver al principio

        if (cantidad == 0) {
            // Archivo de �ndice vac�o, ning�n usuario registrado
            indexFile.close();
            return LoginStatus::USER_NOT_FOUND;
        }


        // Lambda para la b�squeda binaria de un match exacto (o el posible lugar donde deber�a estar)
        // Queremos encontrar la primera posici�n `p` tal que el username buscado sea
        // menor o igual al nombre de usuario en la posici�n `p`.
        // Esto nos da la posici�n donde el usuario *podr�a* estar si existe.
        auto predicadoBusqueda = [&](int pos) {
            UsuarioIndex temp;
            indexFile.seekg(pos * sizeof(UsuarioIndex), ios::beg);
            indexFile.read(reinterpret_cast<char*>(&temp), sizeof(UsuarioIndex));
            indexFile.clear(); // Limpiar flags

            // Queremos el primer pos donde userInput <= temp.nombreDeUsuario
            return strncmp(userInput.c_str(), temp.nombreDeUsuario, MAX_FIELD_LEN) <= 0;
            };

        // Usar busquedaBinaria para encontrar el posible �ndice del usuario
        // La b�squeda binaria nos dar� la posici�n donde el usuario *deber�a* estar
        // si existe, o la posici�n de inserci�n si no existe.
        // Rango de b�squeda: [0, cantidad - 1].
        int posPosibleUsuario = busquedaBinaria(0, cantidad - 1, predicadoBusqueda);

        // Verificar si la posici�n encontrada es v�lida y si el usuario en esa posici�n
        // realmente coincide con el username buscado.
        bool usuarioEncontrado = false;
        UsuarioIndex encontrado;

        // posPosibleUsuario podr�a ser 'cantidad' si el usuario buscado es mayor que todos.
        if (posPosibleUsuario >= 0 && posPosibleUsuario < cantidad) {
            indexFile.seekg(posPosibleUsuario * sizeof(UsuarioIndex), ios::beg);
            indexFile.read(reinterpret_cast<char*>(&encontrado), sizeof(UsuarioIndex));
            indexFile.clear(); // Limpiar flags

            // Comparar el nombre de usuario encontrado con el nombre de usuario de entrada
            if (strncmp(encontrado.nombreDeUsuario, userInput.c_str(), MAX_FIELD_LEN) == 0) {
                // �Match exacto del nombre de usuario en el �ndice!
                usuarioEncontrado = true;
            }
        }
        indexFile.close(); // Ya no necesitamos el archivo de �ndice


        if (!usuarioEncontrado) {
            // El nombre de usuario no se encontr� en el �ndice en la posici�n esperada
            return LoginStatus::USER_NOT_FOUND;
        }

        // Si el usuario fue encontrado en el �ndice, leer sus datos del archivo principal
        string dataFilePath = getDataFilePath(tipoUsuario);
        ifstream dataFile(dataFilePath, ios::binary);

        if (!dataFile.is_open()) {
            cerr << "Error al abrir archivo de datos para login: " << dataFilePath << endl;
            return LoginStatus::FILE_ERROR; // Indicar error de archivo
        }

        UsuarioBinario datos;
        // Mover al offset indicado en el �ndice y leer el struct binario
        dataFile.seekg(encontrado.offset, ios::beg);
        dataFile.read(reinterpret_cast<char*>(&datos), sizeof(UsuarioBinario));
        dataFile.close();

        // 3. Verificar la contrase�a (comparando hashes)
        // Hashear la contrase�a ingresada por el usuario
        string inputPassHash = hashContrasena(passInput);

        // Comparar el hash de la contrase�a ingresada con el hash almacenado
        // Usamos strncmp ya que contrasenaHash en 'datos' es char[] y inputPassHash es string
        // Debemos comparar las cadenas hasta la longitud del campo, considerando el null terminator
        if (strncmp(datos.contrasenaHash, inputPassHash.c_str(), MAX_FIELD_LEN) == 0) {
            // �Login exitoso! Crear el objeto UsuarioLogueado
            // NOTA: Aqu� necesitas decidir c�mo generar el ID al cargar.
            // Usar 'cantidad + 1' como antes no es un ID persistente y �nico.
            // Un enfoque mejor ser�a guardar el ID en UsuarioBinario o tener
            // un archivo de metadatos que lleve un contador de IDs.
            // Por ahora, usamos un ID placeholder (por ejemplo, 0 o el offset).
            // Usaremos el offset como un ID temporal para la demostraci�n,
            // aunque no es un ID "sem�ntico" real.

            usuarioLogueado = fromUsuarioBinario(datos, encontrado.offset, tipoUsuario); // Usamos offset como ID temporal
            return LoginStatus::SUCCESS; // Login logrado wiiiiiii!! ^.^
        }
        else {
            return LoginStatus::WRONG_PASSWORD; // Contrase�a incorrecta
        }
    }

    // --- Getters ---
    int getId() const { return id; } // Agregado const
    string getNombreCompleto() const { return nombreCompleto; } // Agregado const
    TipoUsuario getTipoUsuario() const { return tipoUsuario; } // Agregado const
    string getNickname() const { return username; } // Agregado const
	// string getContrasenaHash() const { return contrasenaHash; } // No deberiamos exponer el hash OwO, no es necesario

    // Setter para el ID si es necesario establecerlo despu�s de la creaci�n
    void setId(int newId) { id = newId; }
};