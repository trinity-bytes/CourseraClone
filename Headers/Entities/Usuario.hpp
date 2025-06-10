// filepath: Headers/Entities/Usuario.hpp
// Descripcion: Clase que representa un usuario en el sistema, 
//              incluyendo manejo de archivos binarios e índices para autenticación.

#ifndef COURSERACLONE_ENTITIES_USUARIO_HPP
#define COURSERACLONE_ENTITIES_USUARIO_HPP

// Headers de la libreria estandar
#include <iostream>  // Para std::cerr y std::endl
#include <fstream>   // Para manejo de archivos
#include <string>    // Para manejo de cadenas
#include <vector>    // Para manejo de vectores
#include <cstring>   // Para manejo de cadenas C-style
#include <limits>    // Para std::numeric_limits
#include <algorithm> // Para std::sort y std::min

// Headers propios
#include "../DataStructures/algoritmosBusqueda.hpp" // Para busquedaBinaria

/// ---  CONSTANTES Y ENUMS  ---
// Maxima longitud para los campos de caracteres en structs binarios
const int MAX_FIELD_LEN = 50;

// Rutas de archivos
const std::string DATA_DIR = "Resources/Data/";
const std::string INDEX_DIR = DATA_DIR + "indices/";
const std::string EMPRESA_DATA_FILE = DATA_DIR + "usuarios_empresa.dat";
const std::string ESTUDIANTE_DATA_FILE = DATA_DIR + "usuarios_estudiante.dat";
const std::string EMPRESA_INDEX_FILE = INDEX_DIR + "usuarios_empresa.dat";       // Debería ser diferente al de datos?
const std::string ESTUDIANTE_INDEX_FILE = INDEX_DIR + "usuarios_estudiante.dat"; // Debería ser diferente al de datos?

// Tipos de usuario
enum class TipoUsuario
{
    NINGUNO = 0,
    ESTUDIANTE = 1,
    EMPRESA = 2
};

// Estados posibles del login
enum class LoginStatus 
{
    SUCCESS = 0,
    USER_NOT_FOUND = 1,
    WRONG_PASSWORD = 2,
    FILE_ERROR = 3
};

/// --- Structs para la representación en archivos binarios ---
// Struct para datos de usuario en el archivo principal (.dat)
struct UsuarioBinario 
{
    char nombreCompleto[MAX_FIELD_LEN];
    char nombreDeUsuario[MAX_FIELD_LEN];
    char contrasenaHash[MAX_FIELD_LEN];

    // Constructor por defecto
    UsuarioBinario() 
    {
        memset(nombreCompleto, 0, sizeof(nombreCompleto));
        memset(nombreDeUsuario, 0, sizeof(nombreDeUsuario));
        memset(contrasenaHash, 0, sizeof(contrasenaHash));
    }

    // Constructor parametrizado (usado para crear el struct antes de guardar)
    // Este constructor se debe llamar con el HASH de la contraseña y no en texto plano OwO
    UsuarioBinario(
        const std::string& nombreCompletoStr, 
        const std::string& nombreUsuarioStr, 
        const std::string& contrasenaHashStr) 
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
    UsuarioIndex(const std::string& nombreUsuarioStr, int _offset) : offset(_offset) 
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

    static int compare(const std::string& a, const UsuarioIndex& b) {
        return strncmp(a.c_str(), b.nombreDeUsuario, MAX_FIELD_LEN);
    }
};

/// --- Clase Usuario ---
// @brief Clase que representa un usuario en el sistema, con métodos para autenticación 
//        y manejo de archivos binarios.
// @details Esta clase maneja la creación, almacenamiento y autenticación de usuarios, 
//          incluyendo la conversión entre estructuras binarias y objetos C++.
class Usuario 
{
protected: 
    int _id;
    TipoUsuario _tipoUsuario;
    std::string _nombreCompleto;
    std::string _username;
    std::string _contrasenaHash;

private:
    // Convierte objeto Usuario a struct UsuarioBinario
    UsuarioBinario toUsuarioBinario() const
    {
        return UsuarioBinario(_nombreCompleto, _username, _contrasenaHash);
    }

    // Convierte struct UsuarioBinario a objeto Usuario
    // Necesita el ID y tipo de usuario, que no están en UsuarioBinario
    static Usuario fromUsuarioBinario(const UsuarioBinario& binario, int id, TipoUsuario tipo)
    {
        std::string nomCompleto(binario.nombreCompleto, strnlen(binario.nombreCompleto, MAX_FIELD_LEN));
        std::string user(binario.nombreDeUsuario, strnlen(binario.nombreDeUsuario, MAX_FIELD_LEN)); 
        std::string hash(binario.contrasenaHash, strnlen(binario.contrasenaHash, MAX_FIELD_LEN));

        return Usuario(id, tipo, nomCompleto, user, hash);
    }

    // Convierte objeto Usuario a struct UsuarioIndex
    UsuarioIndex toUsuarioIndex(int offset) const
    {
        return UsuarioIndex(_username, offset);
    }

    // Convierte struct UsuarioIndex a string de nombre de usuario
    static std::string getUsernameFromIndex(const UsuarioIndex& index)
    {
        // posible basura si el char[] no esta bien terminado.
        return std::string(index.nombreDeUsuario, strnlen(index.nombreDeUsuario, MAX_FIELD_LEN)); // MODIFICADO: string a std::string
    }

    // Helper para obtener la ruta del archivo de datos según el tipo de usuario
    static std::string getDataFilePath(TipoUsuario tipo)
    {
        return (tipo == TipoUsuario::EMPRESA) ? EMPRESA_DATA_FILE : ESTUDIANTE_DATA_FILE;
    }

	// Helper para obtener la ruta del archivo de índice según el tipo de usuario
    static std::string getIndexFilePath(TipoUsuario tipo)
    {
        return (tipo == TipoUsuario::EMPRESA) ? EMPRESA_INDEX_FILE : ESTUDIANTE_INDEX_FILE;
    }

    static std::string hashContrasena(const std::string& contrasena)
    {
        std::string mockHash = "atalapastrukaGohGohGoh"; // Hash inicial con la palabra de seguridad xd // MODIFICADO: string a std::string
        mockHash += contrasena.substr(0, (std::min)((int)contrasena.length(), MAX_FIELD_LEN - (int)mockHash.length() - 1)); // MODIFICADO: min a std::min
        return mockHash;
    }
public:
    // Constructor por default UwU
    Usuario() : _id(0), _tipoUsuario(TipoUsuario::NINGUNO) {}

    // Constructor principal 
    Usuario(
        int id,
        TipoUsuario tipoUsuario,
        const std::string& nombreCompleto,
        const std::string& username,
        const std::string& contrasenaHash
    ) : _id(id), 
        _tipoUsuario(tipoUsuario), 
        _nombreCompleto(nombreCompleto), 
        _username(username), 
        _contrasenaHash(contrasenaHash) {}

    // Getters
    int getId() const { return _id; }
    TipoUsuario getTipoUsuario() const { return _tipoUsuario; }
    std::string getNombreCompleto() const { return _nombreCompleto; }
    std::string getUsername() const { return _username; }
    std::string getContrasenaHash() const { return _contrasenaHash; }

    // Setters
    void setId(int id) { _id = id; }
    void setTipoUsuario(TipoUsuario tipo) { _tipoUsuario = tipo; }
    void setNombreCompleto(const std::string& nombre) { _nombreCompleto = nombre; }
    void setUsername(const std::string& username) { _username = username; }
    void setContrasena(string _contrasena) { _contrasenaHash = hashContrasena(_contrasena); }

    void reset() 
    {
        _id = -1;
        _tipoUsuario = TipoUsuario::NINGUNO; 
        _nombreCompleto = ""; 
        _username = ""; 
        _contrasenaHash = "";
    }

    void establecerDatosBase(Usuario otroUsuario) 
    {
        _tipoUsuario = otroUsuario.getTipoUsuario(); 
        _nombreCompleto = otroUsuario.getNombreCompleto();
        _username = otroUsuario.getUsername();
        _contrasenaHash = otroUsuario.getContrasenaHash();
    }

    // --- Método para guardar un usuario ---
    void guardar() 
    {
        // NOTA: Este método guarda la *instancia actual* del usuario.
        // Se asume que el ID y tipo ya están establecidos y que la contraseña
        // ya fue hasheada y guardada en _contrasenaHash.

        // 1. Guardar en el archivo de datos principal (.dat)
        std::string dataFilePath = getDataFilePath(_tipoUsuario); // MODIFICADO
        std::ofstream dataFile(dataFilePath, std::ios::binary | std::ios::app); // Abre para agregar al final // MODIFICADO
        int offsetRegistro = 0; // Offset donde se escribirá este registro

        if (!dataFile.is_open()) {
            std::cerr << "Error al abrir archivo de datos: " << dataFilePath << std::endl; // MODIFICADO
            // Deberíamos manejar este error, quizás lanzando una excepción o retornando false
            return;
        }

        // Obtener el offset actual antes de escribir
        dataFile.seekp(0, std::ios::end); // MODIFICADO
        offsetRegistro = dataFile.tellp();

        // Crear la struct binaria para guardar (asumiendo que this->_contrasenaHash ya tiene el hash)
        UsuarioBinario nuevoBinario = toUsuarioBinario();
        dataFile.write(reinterpret_cast<const char*>(&nuevoBinario), sizeof(nuevoBinario));
        dataFile.close(); // El destructor del stream también cerrará el archivo


        // 2. Guardar e insertar en el archivo de índice (.dat) (mantenido ordenado)
        std::string indexFilePath = getIndexFilePath(_tipoUsuario); // MODIFICADO
        std::fstream indexFile(indexFilePath, std::ios::binary | std::ios::in | std::ios::out); // Abrir para leer y escribir // MODIFICADO

        // Si el archivo no existe o falla la apertura inicial en in|out, intentamos crearlo
        if (!indexFile.is_open()) {
            // Intentar abrir en modo out para crearlo
            std::ofstream createIndexFile(indexFilePath, std::ios::binary | std::ios::out); // MODIFICADO
            if (!createIndexFile.is_open()) {
                std::cerr << "Error al crear archivo de indice: " << indexFilePath << std::endl; // MODIFICADO
                return;
            }
            createIndexFile.close(); // Cerrar después de crear

            // Ahora intentar abrir de nuevo en modo in|out
            indexFile.open(indexFilePath, std::ios::binary | std::ios::in | std::ios::out); // MODIFICADO
            if (!indexFile.is_open()) {
                std::cerr << "Error al reabrir archivo de indice despues de crear: " << indexFilePath << std::endl; // MODIFICADO
                return;
            }
        }

        // Calcular la cantidad actual de registros en el índice
        indexFile.seekg(0, std::ios::end); // MODIFICADO
        int cantidad = indexFile.tellg() / sizeof(UsuarioIndex);
        indexFile.seekg(0, std::ios::beg); // Volver al principio // MODIFICADO

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
            indexFile.seekg(pos * sizeof(UsuarioIndex), std::ios::beg); // MODIFICADO
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
            indexFile.seekg(i * sizeof(UsuarioIndex), std::ios::beg); // MODIFICADO
            indexFile.read(reinterpret_cast<char*>(&temp), sizeof(UsuarioIndex));
            indexFile.clear(); // Limpiar flags después de leer

            // Escribir el elemento en la siguiente posición (corriendo uno a la derecha)
            indexFile.seekp((i + 1) * sizeof(UsuarioIndex), std::ios::beg); // MODIFICADO
            indexFile.write(reinterpret_cast<const char*>(&temp), sizeof(UsuarioIndex));
            indexFile.clear(); // Limpiar flags después de escribir
        }

        // Escribir el nuevo índice en la posición de inserción encontrada
        indexFile.seekp(posInsercion * sizeof(UsuarioIndex), std::ios::beg); // MODIFICADO
        indexFile.write(reinterpret_cast<const char*>(&nuevoIndex), sizeof(nuevoIndex));
        indexFile.clear(); // Limpiar flags después de escribir

        // El destructor de fstream cerrará el archivo
    }    /// --- Método estático para manejar el login ---
    
    // Retorna un codigo de estado y, si es exitoso, carga los datos del usuario en usuarioLogueado
    static LoginStatus login(
        Usuario& usuarioLogueado, 
        TipoUsuario tipoUsuario, 
        string passInput, 
        int pos
    ) {
        if (pos == -1) return LoginStatus::USER_NOT_FOUND;

		// Abrir el archivo de índice y leer el registro en la posición `pos`
        const string indexPath = getIndexFilePath(tipoUsuario);
        ifstream indexFile(indexPath, ios::in | ios::binary);
        if (!indexFile.is_open()) {
            return LoginStatus::FILE_ERROR;
        }
        indexFile.seekg(pos * sizeof(UsuarioIndex), ios::beg);
        UsuarioIndex encontrado;
        indexFile.read(reinterpret_cast<char*>(&encontrado), sizeof(encontrado));
        indexFile.close();

        // Abrir el archivo de datos y saltar al offset
        const string dataPath = getDataFilePath(tipoUsuario);
        ifstream dataFile(dataPath, ios::in | ios::binary);
        if (!dataFile.is_open()) {
            return LoginStatus::FILE_ERROR;
        }

        dataFile.seekg(encontrado.offset, ios::beg);
        UsuarioBinario binRec;
        dataFile.read(reinterpret_cast<char*>(&binRec), sizeof(binRec));
        dataFile.close();

        // Comparar hashes
        string inputHash = hashContrasena(passInput);
        if (strncmp(binRec.contrasenaHash,
            inputHash.c_str(),
            MAX_FIELD_LEN) != 0)
        {
            return LoginStatus::WRONG_PASSWORD;
        }

        usuarioLogueado = fromUsuarioBinario(binRec, /*id=*/encontrado.offset, tipoUsuario); // Usamos offset como ID temporal
        return LoginStatus::SUCCESS; // Login logrado wiiiiiii!! ^.^
    }

    static int buscarIndexUsuario(string _username, TipoUsuario tipoUsuario) {
        // 1) Normalizar a minúsculas
        for (char& c : _username) {
            if (c >= 'A' && c <= 'Z')
                c += ('a' - 'A');
        }

        // 2) Abrir el archivo de índices
        const string indexFilePath = Usuario::getIndexFilePath(tipoUsuario);
        ifstream indexFile(indexFilePath, ios::in | ios::binary);
        if (!indexFile.is_open())
            return -1;

        // 3) Calcular cuántos registros hay
        indexFile.seekg(0, ios::end);
        int cantidad = indexFile.tellg() / sizeof(UsuarioIndex);
        indexFile.seekg(0, ios::beg);
        if (cantidad == 0)
            return -1;

        // 4) Predicado para lower_bound
        auto pred = [&](int pos) {
            UsuarioIndex tmp;
            indexFile.seekg(pos * sizeof(UsuarioIndex), ios::beg);
            indexFile.read(reinterpret_cast<char*>(&tmp), sizeof(tmp));
            return strncmp(_username.c_str(), tmp.nombreDeUsuario, MAX_FIELD_LEN) <= 0;
            };

        // 5) Búsqueda binaria para encontrar la posición
        int pos = busquedaBinaria(0, cantidad - 1, pred);
        if (pos < cantidad) {
            UsuarioIndex encontrado;
            indexFile.seekg(pos * sizeof(UsuarioIndex), ios::beg);
            indexFile.read(reinterpret_cast<char*>(&encontrado), sizeof(encontrado));
            if (strncmp(encontrado.nombreDeUsuario, _username.c_str(), MAX_FIELD_LEN) == 0)
                return pos;
        }
        return -1;
    }

	bool actualizarUsuario() 
    {
		if (this->_id == -1) // Verificamos si el ID es válido
        {
            cerr << "Error: Usuario ID no válido para actualización." << endl;
            return false;
        }

        string dataFilePath = getDataFilePath(this->_tipoUsuario);
        string indexFilePath = getIndexFilePath(this->_tipoUsuario);

        fstream indexFileAccess(indexFilePath, ios::binary | ios::in); 
        if (!indexFileAccess.is_open()) {
            cerr << "Error: No se pudo abrir el archivo de índice para leer: " << indexFilePath << endl;
            return false;
        }

        indexFileAccess.seekg(this->_id * sizeof(UsuarioIndex), ios::beg);
        UsuarioIndex currentIdxRecord;
        indexFileAccess.read(reinterpret_cast<char*>(&currentIdxRecord), sizeof(currentIdxRecord));

        if (indexFileAccess.fail()) {
            cerr << "Error: No se pudo leer el registro de índice en la posición: " << this->_id << endl;
            indexFileAccess.close();
            return false;
        }
        int dataRecordOffset = currentIdxRecord.offset;
        string oldUsernameInIndex = string(currentIdxRecord.nombreDeUsuario, strnlen(currentIdxRecord.nombreDeUsuario, MAX_FIELD_LEN));
        indexFileAccess.close(); // Close for now, will reopen if username changes significantly

        // --- 2. Read the current User's Binary Data from .dat file ---
        // This is to get the existing password hash if nuevaContrasena is empty.
        UsuarioBinario existingBinRecord;
        ifstream dataFileRead(dataFilePath, ios::binary);
        if (!dataFileRead.is_open()) {
            cerr << "Error: No se pudo abrir el archivo de datos para leer datos existentes: " << dataFilePath << endl;
            return false;
        }
        dataFileRead.seekg(dataRecordOffset, ios::beg);
        dataFileRead.read(reinterpret_cast<char*>(&existingBinRecord), sizeof(existingBinRecord));
        if (dataFileRead.fail()) {
            cerr << "Error: No se pudo leer el registro de datos existente para el offset: " << dataRecordOffset << endl;
            dataFileRead.close();
            return false;
        }
        dataFileRead.close();

        // --- 3. Determine the Password Hash to Save and Update Object's State ---
        string passwordHashParaGuardar;
        if (!nuevaContrasena.empty()) {
            // User provided a new password, so hash it
            passwordHashParaGuardar = hashContrasena(nuevaContrasena);
        }
        else {
            // User did not provide a new password, so use the existing hash from the file
            passwordHashParaGuardar = string(existingBinRecord.contrasenaHash, strnlen(existingBinRecord.contrasenaHash, MAX_FIELD_LEN));
        }

        // Update the current Usuario object's instance data
        this->_nombreCompleto = nuevoNombreCompleto;
        this->setUsername(nuevoUsername); // Uses setter for normalization
        this->_contrasenaHash = passwordHashParaGuardar; // Update object's hash for consistency

        // --- 4. Prepare the UsuarioBinario struct with all data to be saved ---
        UsuarioBinario binDataToSave(this->_nombreCompleto, this->_username, this->_contrasenaHash);

        // --- 5. Overwrite the record in the main data file (.dat) ---
        fstream dataFileWrite(dataFilePath, ios::binary | ios::in | ios::out); // Open for read/write
        if (!dataFileWrite.is_open()) {
            cerr << "Error: No se pudo abrir el archivo de datos para actualizar: " << dataFilePath << endl;
            return false;
        }
        dataFileWrite.seekp(dataRecordOffset, ios::beg); // Go to the specific record's offset
        dataFileWrite.write(reinterpret_cast<const char*>(&binDataToSave), sizeof(binDataToSave));
        dataFileWrite.close(); // Close data file after writing

        // --- 6. Handle Index File Update if Username (key) Changed ---
        if (this->_username != oldUsernameInIndex) {
            // Username has changed. The index file needs to be restructured.
            // Strategy: Read all, remove old, add new, sort, rewrite.
            ifstream indexFileRead(indexFilePath, ios::binary);
            if (!indexFileRead.is_open()) {
                cerr << "Error: No se pudo reabrir el archivo de índice para procesar cambio de username: " << indexFilePath << endl;
                return false; // Critical error if index can't be read
            }

            vector<UsuarioIndex> allIndices;
            UsuarioIndex tempIdx;
            while (indexFileRead.read(reinterpret_cast<char*>(&tempIdx), sizeof(UsuarioIndex))) {
                allIndices.push_back(tempIdx);
            }
            indexFileRead.close();

            bool removed = false;
            for (auto it = allIndices.begin(); it != allIndices.end(); ++it) {
                if (it->offset == dataRecordOffset) { // Match by the unique data offset
                    allIndices.erase(it);
                    removed = true;
                    break;
                }
            }

            if (!removed) {
                // This case implies an inconsistency, as the record we just updated in the .dat file
                // should have had a corresponding index entry.
                cerr << "Error crítico: No se encontró el registro de índice antiguo (offset: " << dataRecordOffset
                    << ") durante la actualización del nombre de usuario. El índice NO se actualizó." << endl;
                return false; // Prevent leaving index in a more broken state
            }

            allIndices.push_back(UsuarioIndex(this->_username, dataRecordOffset)); // Add new index entry

            sort(allIndices.begin(), allIndices.end(), [](const UsuarioIndex& a, const UsuarioIndex& b) {
                return strncmp(a.nombreDeUsuario, b.nombreDeUsuario, MAX_FIELD_LEN) < 0;
                });

            ofstream indexFileRewrite(indexFilePath, ios::binary | ios::trunc); // Truncate and write
            if (!indexFileRewrite.is_open()) {
                cerr << "Error: No se pudo abrir el archivo de índice para reescribir: " << indexFilePath << endl;
                return false;
            }
            for (const auto& idxEntry : allIndices) {
                indexFileRewrite.write(reinterpret_cast<const char*>(&idxEntry), sizeof(idxEntry));
            }
            indexFileRewrite.close();

            bool idUpdated = false;
            for (size_t i = 0; i < allIndices.size(); ++i) {
                if (allIndices[i].offset == dataRecordOffset) {
                    this->_id = static_cast<int>(i);
                    idUpdated = true;
                    break;
                }
            }
            if (!idUpdated) {
                cerr << "Advertencia: No se pudo actualizar el ID del objeto Usuario después de la reordenación del índice." << endl;
            }
        }
        // If username didn't change, no index file modification is needed.        
        return true; // Update successful
    }
};

#endif // COURSERACLONE_ENTITIES_USUARIO_HPP