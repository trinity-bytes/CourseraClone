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
#include "../Persistence/UsuarioTypes.hpp" // UsuarioBinario, UsuarioIndex, TipoUsuario, LoginStatus
#include "../Persistence/FilesManager.hpp"

const std::string DATA_DIR = "Resources/Data/";
const std::string INDEX_DIR = DATA_DIR + "indices/";
const std::string EMPRESA_DATA_FILE = DATA_DIR + "usuarios_empresa.dat";
const std::string ESTUDIANTE_DATA_FILE = DATA_DIR + "usuarios_estudiante.dat";
const std::string EMPRESA_INDEX_FILE = INDEX_DIR + "usuarios_empresa.dat";       // Debería ser diferente al de datos?Add commentMore actions
const std::string ESTUDIANTE_INDEX_FILE = INDEX_DIR + "usuarios_estudiante.dat"; // Debería ser diferente al de datos?

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
        std::string dataFilePath = getDataFilePath(_tipoUsuario);
        std::ofstream dataFile(dataFilePath, std::ios::binary | std::ios::app);
        long offsetRegistro = 0; // Usar long por si tellp() devuelve un tipo más grande

        if (!dataFile.is_open()) {
            std::cerr << "Error al abrir archivo de datos: " << dataFilePath << std::endl;
            return;
        }

        // Obtener el offset actual antes de escribir
        dataFile.seekp(0, std::ios::end);
        offsetRegistro = dataFile.tellp();

        UsuarioBinario nuevoBinario = toUsuarioBinario();
        dataFile.write(reinterpret_cast<const char*>(&nuevoBinario), sizeof(nuevoBinario));
        
        if (!dataFile.good()) {
            std::cerr << "Error al escribir en el archivo de datos: " << dataFilePath << std::endl;
            dataFile.close();
            return; 
        }
        dataFile.close();


        // 2. Actualizar el archivo de índice (.dat) (mantenido ordenado)
        std::string indexFilePath = getIndexFilePath(_tipoUsuario);
        std::vector<UsuarioIndex> allIndices;
        UsuarioIndex tempIdx;

        // Intentar leer todos los índices existentes
        std::ifstream indexFileRead(indexFilePath, std::ios::binary);
        if (indexFileRead.is_open()) {
            while (indexFileRead.read(reinterpret_cast<char*>(&tempIdx), sizeof(UsuarioIndex))) {
                allIndices.push_back(tempIdx);
            }
            indexFileRead.close();
        }
        // Si el archivo no existía o estaba vacío, allIndices estará vacío, lo cual es correcto.

        // Crear la nueva entrada de índice
        UsuarioIndex nuevoIndex = toUsuarioIndex(static_cast<int>(offsetRegistro));

        // Agregar la nueva entrada al vector
        allIndices.push_back(nuevoIndex);

        // Ordenar el vector de índices por nombreDeUsuario
        std::sort(allIndices.begin(), allIndices.end(), [](const UsuarioIndex& a, const UsuarioIndex& b) {
            return strncmp(a.nombreDeUsuario, b.nombreDeUsuario, MAX_FIELD_LEN) < 0;
        });

        // Reescribir el archivo de índice completo con los índices ordenados
        std::ofstream indexFileWrite(indexFilePath, std::ios::binary | std::ios::trunc);
        if (!indexFileWrite.is_open()) {
            std::cerr << "Error al abrir/crear archivo de indice para escritura: " << indexFilePath << std::endl;
            // Considerar la consistencia de datos: el registro de datos se guardó, pero el índice falló.
            return;
        }

        for (const auto& idxEntry : allIndices) {
            indexFileWrite.write(reinterpret_cast<const char*>(&idxEntry), sizeof(idxEntry));
        }
        
        if (!indexFileWrite.good()) {
            std::cerr << "Error al escribir en el archivo de indice: " << indexFilePath << std::endl;
            indexFileWrite.close();
            // El índice podría estar corrupto o incompleto.
            return;
        }
        indexFileWrite.close();

        // Actualizar el _id del objeto Usuario para que refleje su posición en el índice
        bool idUpdated = false;
        for (size_t i = 0; i < allIndices.size(); ++i) {
            if (allIndices[i].offset == offsetRegistro && 
                strncmp(allIndices[i].nombreDeUsuario, nuevoIndex.nombreDeUsuario, MAX_FIELD_LEN) == 0) {
                this->_id = static_cast<int>(i); // Asigna la posición en el índice como ID
                idUpdated = true;
                break;
            }
        }
        if (!idUpdated) {
            std::cerr << "Advertencia: No se pudo actualizar el ID del objeto Usuario después de guardar y reordenar el índice." << std::endl;
        }
    }    
    
    /// --- Método estático para manejar el login ---
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

	bool actualizarUsuario(
        const std::string& _nuevoNombre,
		const std::string& _nuevoUsername,
        const std::string& _nuevaContrasena
    ) {
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
        if (!_nuevaContrasena.empty()) {
            // User provided a new password, so hash it
            passwordHashParaGuardar = hashContrasena(_nuevaContrasena);
        }
        else {
            // User did not provide a new password, so use the existing hash from the file
            passwordHashParaGuardar = string(existingBinRecord.contrasenaHash, strnlen(existingBinRecord.contrasenaHash, MAX_FIELD_LEN));
        }

        // Update the current Usuario object's instance data
        this->_nombreCompleto = _nuevoNombre;
        this->setUsername(_nuevoUsername); // Uses setter for normalization
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