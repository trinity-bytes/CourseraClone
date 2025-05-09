#pragma once

// Headers propios
#include "algoritmosBusqueda.h"

// Headers de la libreria estandar
#include "iostream"
#include "fstream"
#include "string"
#include "vector"     // Podría ser útil para manejar indices temporalmente en memoria
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

/// --- Structs para la representación en archivos binarios ---
// Struct para datos de usuario en el archivo principal (.dat)
struct UsuarioBinario 
{
    char nombreCompleto[MAX_FIELD_LEN];
    char nombreDeUsuario[MAX_FIELD_LEN];
    char contrasenaHash[MAX_FIELD_LEN]; // Guardamos un HASH de la contraseña

    // Constructor por defecto: Inicializa todo a cero
    UsuarioBinario() 
    {
        memset(nombreCompleto, 0, sizeof(nombreCompleto));
        memset(nombreDeUsuario, 0, sizeof(nombreDeUsuario));
        memset(contrasenaHash, 0, sizeof(contrasenaHash));
    }

    // Constructor parametrizado (usado para crear el struct antes de guardar)
    // Este constructor se debe llamar con el HASH de la contraseña y no en texto plano OwO
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

// Struct para entradas del archivo índice (.dat)
struct UsuarioIndex 
{
    char nombreDeUsuario[MAX_FIELD_LEN];
    int offset; // Offset en bytes en el archivo de datos principal

    // Constructor por defecto
    UsuarioIndex() : offset(0) 
    {
        memset(nombreDeUsuario, 0, sizeof(nombreDeUsuario)); // Inicializa nombre a cero
    }

    // Constructor parametrizado (usado para crear el struct antes de guardar en índice)
    UsuarioIndex(const string& nombreUsuarioStr, int _offset) : offset(_offset) 
    {
        // Copia segura de cadena, asegurando null termination
        strncpy(nombreDeUsuario, nombreUsuarioStr.c_str(), MAX_FIELD_LEN - 1);
        nombreDeUsuario[MAX_FIELD_LEN - 1] = '\0';
    }

    // Función de comparación estática para usar con busquedaBinaria
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

    static string hashContrasena(const string& contrasena) 
    {
        string mockHash = "atalapastrukaGohGohGoh"; // Hash inicial con la palabra de seguridad xd
        mockHash += contrasena.substr(0, min((int)contrasena.length(), MAX_FIELD_LEN - (int)mockHash.length() - 1));
        return mockHash;
    }

private:
    // Convierte objeto Usuario a struct UsuarioBinario
    UsuarioBinario toUsuarioBinario() const 
    {
        // Esto funciona si this->contrasenaHash ya contiene el hash
        return UsuarioBinario(nombreCompleto, username, contrasenaHash);
    }

    // Convierte struct UsuarioBinario a objeto Usuario
    // Necesita el ID y tipo de usuario, que no están en UsuarioBinario
    static Usuario fromUsuarioBinario(const UsuarioBinario& binario, int id, TipoUsuario tipo) 
    {
        // Funciona la lectura del archivo nos da un struct válido.
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

    // Helper para obtener la ruta del archivo de datos según el tipo de usuario
    static string getDataFilePath(TipoUsuario tipo) 
    {
        return (tipo == TipoUsuario::EMPRESA) ? EMPRESA_DATA_FILE : ESTUDIANTE_DATA_FILE;
    }

    static string getIndexFilePath(TipoUsuario tipo) 
    {
        return (tipo == TipoUsuario::EMPRESA) ? EMPRESA_INDEX_FILE : ESTUDIANTE_INDEX_FILE;
    }
public:
    // --- Método para guardar un usuario ---
    void guardar() 
    {
        // NOTA: Este método guarda la *instancia actual* del usuario.
        // Se asume que el ID y tipo ya están establecidos y que la contraseña
        // ya fue hasheada y guardada en contrasenaHash.

        // 1. Guardar en el archivo de datos principal (.dat)
        string dataFilePath = getDataFilePath(tipoUsuario);
        ofstream dataFile(dataFilePath, ios::binary | ios::app); // Abre para agregar al final
        int offsetRegistro = 0; // Offset donde se escribirá este registro

        if (!dataFile.is_open()) {
            cerr << "Error al abrir archivo de datos: " << dataFilePath << endl;
            // Deberíamos manejar este error, quizás lanzando una excepción o retornando false
            return;
        }

        // Obtener el offset actual antes de escribir
        dataFile.seekp(0, ios::end);
        offsetRegistro = dataFile.tellp();

        // Crear la struct binaria para guardar (asumiendo que this->contrasenaHash ya tiene el hash)
        UsuarioBinario nuevoBinario = toUsuarioBinario();
        dataFile.write(reinterpret_cast<const char*>(&nuevoBinario), sizeof(nuevoBinario));
        dataFile.close(); // El destructor del stream también cerrará el archivo


        // 2. Guardar e insertar en el archivo de índice (.dat) (mantenido ordenado)
        string indexFilePath = getIndexFilePath(tipoUsuario);
        fstream indexFile(indexFilePath, ios::binary | ios::in | ios::out); // Abrir para leer y escribir

        // Si el archivo no existe o falla la apertura inicial en in|out, intentamos crearlo
        if (!indexFile.is_open()) {
            // Intentar abrir en modo out para crearlo
            ofstream createIndexFile(indexFilePath, ios::binary | ios::out);
            if (!createIndexFile.is_open()) {
                cerr << "Error al crear archivo de indice: " << indexFilePath << endl;
                return;
            }
            createIndexFile.close(); // Cerrar después de crear

            // Ahora intentar abrir de nuevo en modo in|out
            indexFile.open(indexFilePath, ios::binary | ios::in | ios::out);
            if (!indexFile.is_open()) {
                cerr << "Error al reabrir archivo de indice despues de crear: " << indexFilePath << endl;
                return;
            }
        }

        // Calcular la cantidad actual de registros en el índice
        indexFile.seekg(0, ios::end);
        int cantidad = indexFile.tellg() / sizeof(UsuarioIndex);
        indexFile.seekg(0, ios::beg); // Volver al principio

        // Crear la entrada del índice para el nuevo usuario
        UsuarioIndex nuevoIndex = toUsuarioIndex(offsetRegistro);

        // Lambda para la búsqueda binaria de la posición de inserción
        // Queremos encontrar la primera posición `p` tal que el nombre de usuario del
        // nuevo índice sea menor o igual al nombre de usuario en la posición `p`.
        // Esto nos da el punto de inserción correcto para mantener el orden ascendente.
        // Esta lambda se pasa a la función busquedaBinaria (asumimos que esta función
        // encuentra el primer índice donde la lambda devuelve true en el rango [inicio, fin]).
        // La lambda recibe la posición `p` a verificar.
        auto predicadoInsercion = [&](int pos) {
            if (pos < 0 || pos >= cantidad) { // Fuera de rango si la lista está vacía
                return true; // Inserta al principio si la lista está vacía
            }
            UsuarioIndex temp;
            indexFile.seekg(pos * sizeof(UsuarioIndex), ios::beg);
            indexFile.read(reinterpret_cast<char*>(&temp), sizeof(UsuarioIndex));
            indexFile.clear(); // Limpiar flags de error/eof después de leer

            // Comparar el nombre del nuevo usuario con el de la posición actual
            // strncmp(a, b, n) regresa <0 si a < b, 0 si a == b, >0 si a > b
            // Queremos el primer pos donde nuevoIndex.username <= temp.username
            // Es decir, donde strncmp(nuevoIndex.username, temp.username, ...) <= 0 es true.
            return strncmp(nuevoIndex.nombreDeUsuario, temp.nombreDeUsuario, MAX_FIELD_LEN) <= 0;
            };

        // Usar busquedaBinaria para encontrar la posición de inserción
        // Asumimos que busquedaBinaria(inicio, fin, predicado) encuentra el
        // primer índice `i` en el rango [inicio, fin] donde predicado(i) es true.
        // Si la lista está vacía, cantidad es 0, cantidad-1 es -1.
        // La búsqueda debe manejar el rango vacío [0, -1].
        int posInsercion = 0; // Posición por defecto si el archivo está vacío
        if (cantidad > 0) {
            // Rango [0, cantidad - 1]. busquedaBinaria debe manejar este rango.
            // Si nuestro busquedaBinaria no maneja inicio > fin, necesitamos ajustarlo.
            // Un busqueda binaria para lower_bound (punto de insercion) tipico seria:
            // low = inicio, high = fin + 1. while(low < high) mid = low + (high-low)/2.
            // if (predicado(mid)) high = mid; else low = mid + 1. return low.
            // Asumiendo busquedaBinaria(inicio, fin, predicado) implementa lower_bound-like:
            posInsercion = busquedaBinaria(0, cantidad - 1, predicadoInsercion);
            // Si busquedaBinaria retorna cantidad, significa que el nuevo elemento es mayor
            // que todos los existentes y debe ir al final. El loop de shift lo manejará.
        }
        else {
            posInsercion = 0; // Primer elemento en archivo vacío
        }


        // Mover elementos para hacer espacio en el archivo de índice
        // Desde el final hacia la posición de inserción
        for (int i = cantidad - 1; i >= posInsercion; --i) {
            UsuarioIndex temp;
            // Leer el elemento actual
            indexFile.seekg(i * sizeof(UsuarioIndex), ios::beg);
            indexFile.read(reinterpret_cast<char*>(&temp), sizeof(UsuarioIndex));
            indexFile.clear(); // Limpiar flags después de leer

            // Escribir el elemento en la siguiente posición (corriendo uno a la derecha)
            indexFile.seekp((i + 1) * sizeof(UsuarioIndex), ios::beg);
            indexFile.write(reinterpret_cast<const char*>(&temp), sizeof(UsuarioIndex));
            indexFile.clear(); // Limpiar flags después de escribir
        }

        // Escribir el nuevo índice en la posición de inserción encontrada
        indexFile.seekp(posInsercion * sizeof(UsuarioIndex), ios::beg);
        indexFile.write(reinterpret_cast<const char*>(&nuevoIndex), sizeof(nuevoIndex));
        indexFile.clear(); // Limpiar flags después de escribir

        // El destructor de fstream cerrará el archivo
    }

    /// --- Método estático para manejar el login ---
    // Retorna un codigo de estado y, si es exitoso, carga los datos del usuario en usuarioLogueado
    // Dentro de class Usuario:
public:
    bool usuarioRepetido(string _username, TipoUsuario tipoUsuario) {
        for (char& c : _username) {
            if (c >= 'A' && c <= 'Z') c = c + 32;
        }

        const string indexFilePath = getIndexFilePath(tipoUsuario);
        ifstream indexFile(indexFilePath, ios::in | ios::binary);
        if (!indexFile.is_open()) {
            return false;
        }

        indexFile.seekg(0, ios::end);
        int cantidad = indexFile.tellg() / sizeof(UsuarioIndex);
        indexFile.seekg(0, ios::beg);

        if (cantidad == 0) {
            return false;
        }

        auto pred = [&](int pos) {
            UsuarioIndex tmp;
            indexFile.seekg(pos * sizeof(UsuarioIndex), ios::beg);
            indexFile.read(reinterpret_cast<char*>(&tmp), sizeof(tmp));
            return strncmp(_username.c_str(), tmp.nombreDeUsuario, MAX_FIELD_LEN) <= 0;
            };

        int pos = busquedaBinaria(0, cantidad - 1, pred);
        if (pos < cantidad) {
            UsuarioIndex encontrado;
            indexFile.seekg(pos * sizeof(UsuarioIndex), ios::beg);
            indexFile.read(reinterpret_cast<char*>(&encontrado), sizeof(encontrado));

            // Si coincide exactamente, está repetido
            if (strncmp(encontrado.nombreDeUsuario, _username.c_str(), MAX_FIELD_LEN) == 0) {
                return true;
            }
        }
        return false;
    }



    static LoginStatus login(Usuario& usuarioLogueado, TipoUsuario tipoUsuario, string userInput, string passInput) 
    {
        string indexFilePath = getIndexFilePath(tipoUsuario);
        ifstream indexFile(indexFilePath, ios::binary); // Abrir solo para leer

        if (!indexFile.is_open()) 
        {
            cerr << "Error al abrir archivo de indice para login: " << indexFilePath << endl;
            return LoginStatus::FILE_ERROR; // Indicar error de archivo
        }

        indexFile.seekg(0, ios::end);
        int cantidad = indexFile.tellg() / sizeof(UsuarioIndex);
        indexFile.seekg(0, ios::beg); // Volver al principio

        if (cantidad == 0) 
        {
            // Archivo de índice vacío, ningún usuario registrado
            indexFile.close();
            return LoginStatus::USER_NOT_FOUND;
        }

        // Lambda para la búsqueda binaria de un match exacto (o el posible lugar donde debería estar)
        // Queremos encontrar la primera posición `p` tal que el username buscado sea
        // menor o igual al nombre de usuario en la posición `p`.
        // Esto nos da la posición donde el usuario *podría* estar si existe.
        auto predicadoBusqueda = [&](int pos) {
            UsuarioIndex temp;
            indexFile.seekg(pos * sizeof(UsuarioIndex), ios::beg);
            indexFile.read(reinterpret_cast<char*>(&temp), sizeof(UsuarioIndex));
            indexFile.clear(); // Limpiar flags

            // Queremos el primer pos donde userInput <= temp.nombreDeUsuario
            return strncmp(userInput.c_str(), temp.nombreDeUsuario, MAX_FIELD_LEN) <= 0;
            };

        // Usar busquedaBinaria para encontrar el posible índice del usuario
        // La búsqueda binaria nos dará la posición donde el usuario *debería* estar
        // si existe, o la posición de inserción si no existe.
        // Rango de búsqueda: [0, cantidad - 1].
        int posPosibleUsuario = busquedaBinaria(0, cantidad - 1, predicadoBusqueda);

        // Verificar si la posición encontrada es válida y si el usuario en esa posición realmente coincide con el username buscado.
        bool usuarioEncontrado = false;
        UsuarioIndex encontrado;

        // posPosibleUsuario podría ser 'cantidad' si el usuario buscado es mayor que todos.
        if (posPosibleUsuario >= 0 && posPosibleUsuario < cantidad) {
            indexFile.seekg(posPosibleUsuario * sizeof(UsuarioIndex), ios::beg);
            indexFile.read(reinterpret_cast<char*>(&encontrado), sizeof(UsuarioIndex));
            indexFile.clear(); // Limpiar flags

            // Comparar el nombre de usuario encontrado con el nombre de usuario de entrada
            if (strncmp(encontrado.nombreDeUsuario, userInput.c_str(), MAX_FIELD_LEN) == 0) {
                // Match exacto del nombre de usuario en el índice!
                usuarioEncontrado = true;
            }
        }
        indexFile.close(); // Ya no necesitamos el archivo de índice


        if (!usuarioEncontrado) {
            // El nombre de usuario no se encontró en el índice en la posición esperada
            return LoginStatus::USER_NOT_FOUND;
        }

        // Si el usuario fue encontrado en el índice, leer sus datos del archivo principal
        string dataFilePath = getDataFilePath(tipoUsuario);
        ifstream dataFile(dataFilePath, ios::binary);

        if (!dataFile.is_open()) {
            cerr << "Error al abrir archivo de datos para login: " << dataFilePath << endl;
            return LoginStatus::FILE_ERROR; // Indicar error de archivo
        }

        UsuarioBinario datos;
        // Mover al offset indicado en el índice y leer el struct binario
        dataFile.seekg(encontrado.offset, ios::beg);
        dataFile.read(reinterpret_cast<char*>(&datos), sizeof(UsuarioBinario));
        dataFile.close();

        // 3. Verificar la contraseña (comparando hashes)
        // Hashear la contraseña ingresada por el usuario
        string inputPassHash = hashContrasena(passInput);

        // Comparar el hash de la contraseña ingresada con el hash almacenado
        // Usamos strncmp ya que contrasenaHash en 'datos' es char[] y inputPassHash es string
        // Debemos comparar las cadenas hasta la longitud del campo, considerando el null terminator
        if (strncmp(datos.contrasenaHash, inputPassHash.c_str(), MAX_FIELD_LEN) == 0) {
            // Login exitoso! Crear el objeto UsuarioLogueado
            // NOTA: Aquí necesitas decidir cómo generar el ID al cargar.
            // Usar 'cantidad + 1' como antes no es un ID persistente y único.
            // Un enfoque mejor sería guardar el ID en UsuarioBinario o tener
            // un archivo de metadatos que lleve un contador de IDs.
            // Por ahora, usamos un ID placeholder (por ejemplo, 0 o el offset).
            // Usaremos el offset como un ID temporal para la demostración,
            // aunque no es un ID "semántico" real.

            usuarioLogueado = fromUsuarioBinario(datos, encontrado.offset, tipoUsuario); // Usamos offset como ID temporal
            return LoginStatus::SUCCESS; // Login logrado wiiiiiii!! ^.^
        }
        else {
            return LoginStatus::WRONG_PASSWORD; // Contraseña incorrecta
        }
    }

    // --- Getters ---
    int getId() const { return id; } // Agregado const
    string getNombreCompleto() const { return nombreCompleto; } // Agregado const
    TipoUsuario getTipoUsuario() const { return tipoUsuario; } // Agregado const
    string getUsername() const { return username; } // Agregado const
	// string getContrasenaHash() const { return contrasenaHash; } // No deberiamos exponer el hash OwO, no es necesario

    // Setter para el ID si es necesario establecerlo después de la creación
    void setId(int newId) { id = newId; }
    void setNombre(string _nombreCompleto) { nombreCompleto = _nombreCompleto; }
    void setUsername(string _username) {
        for (char& c : _username) {
            if (c >= 'A' && c <= 'Z') c = c + 32;
        }
        username = _username;
    }
    void setContrasena(string _contrasena) { contrasenaHash = hashContrasena(_contrasena); }
    void setTipoUsuario(TipoUsuario _tipoUsuario) { tipoUsuario = _tipoUsuario; }

};