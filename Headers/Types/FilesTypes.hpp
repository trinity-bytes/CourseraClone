#ifndef COURSERACLONE_TYPES_FILESTYPES_HPP
#define COURSERACLONE_TYPES_FILESTYPES_HPP

/// @brief Resultados de operaciones de archivo
enum class FileOperationResult
{
    SUCCESS,
    FILE_NOT_FOUND,
    PERMISSION_DENIED,
    CORRUPTION_DETECTED,
    UNKNOWN_ERROR,
    DUPLICATED_VALUE
};
inline std::string obtenerMensaje(FileOperationResult resultado) {
    switch (resultado) {
    case FileOperationResult::SUCCESS:
        return "Operación completada exitosamente.";
    case FileOperationResult::FILE_NOT_FOUND:
        return "Archivo no encontrado.";
    case FileOperationResult::UNKNOWN_ERROR:
        return "Error desconocido.";
    default:
        return "Estado no reconocido.";
    }
}
#endif // !COURSERACLONE_TYPES_FILESTYPES_HPP
