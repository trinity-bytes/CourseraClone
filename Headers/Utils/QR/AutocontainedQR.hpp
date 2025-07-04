#ifndef COURSERACLONE_UTILS_QR_AUTOCONTAINED_HPP
#define COURSERACLONE_UTILS_QR_AUTOCONTAINED_HPP

#include <string>
#include <sstream>
#include <iomanip>
#include "../../Types/ComprobanteDePagoTypes.hpp"
#include "../../Types/ActividadTypes.hpp"

namespace CourseraClone {
namespace QR {

/// @brief Utilidad para generar códigos QR autocontenidos para la web de verificación
/// Diseñado para proyectos académicos - prioriza legibilidad sobre seguridad
class AutocontainedQR {
public:
    
    /// @brief Genera un QR JSON para comprobante de pago
    /// @param comprobante Datos del comprobante
    /// @param nombreEstudiante Nombre completo del estudiante
    /// @param nombreActividad Nombre del curso/especialización
    /// @return JSON compacto para el QR
    static std::string generarQRComprobante(
        const RawComprobanteData& comprobante,
        const std::string& nombreEstudiante,
        const std::string& nombreActividad
    ) {
        std::stringstream json;
        json << "{";
        json << "\"type\":\"receipt\",";
        json << "\"id\":" << comprobante.id << ",";
        json << "\"student\":\"" << truncarTexto(nombreEstudiante, 20) << "\",";
        json << "\"course\":\"" << truncarTexto(nombreActividad, 30) << "\",";
        json << "\"date\":\"" << extraerFecha(comprobante.fechaEmision) << "\",";
        json << "\"amount\":" << std::fixed << std::setprecision(2) << comprobante.montoPagado << ",";
        json << "\"courseType\":\"" << tipoActividadToString(comprobante.tipoActividad) << "\"";
        json << "}";
        return json.str();
    }

    /// @brief Genera un QR JSON para certificado
    /// @param idCertificado ID único del certificado
    /// @param nombreEstudiante Nombre completo del estudiante
    /// @param nombreActividad Nombre del curso/especialización
    /// @param fechaFinalizacion Fecha de finalización
    /// @param calificacion Calificación obtenida
    /// @param tipoActividad Tipo de actividad
    /// @return JSON compacto para el QR
    static std::string generarQRCertificado(
        int idCertificado,
        const std::string& nombreEstudiante,
        const std::string& nombreActividad,
        const std::string& fechaFinalizacion,
        const std::string& calificacion,
        TipoActividad tipoActividad
    ) {
        std::stringstream json;
        json << "{";
        json << "\"type\":\"certificate\",";
        json << "\"id\":" << idCertificado << ",";
        json << "\"student\":\"" << truncarTexto(nombreEstudiante, 20) << "\",";
        json << "\"course\":\"" << truncarTexto(nombreActividad, 30) << "\",";
        json << "\"completed\":\"" << extraerFecha(fechaFinalizacion) << "\",";
        json << "\"grade\":\"" << truncarTexto(calificacion, 15) << "\",";
        json << "\"courseType\":\"" << tipoActividadToString(tipoActividad) << "\"";
        json << "}";
        return json.str();
    }

    /// @brief Calcula el tamaño estimado de un QR para planificación
    /// @param contenido Contenido del QR
    /// @return Tamaño en caracteres y evaluación de seguridad
    static std::string evaluarTamaño(const std::string& contenido) {
        int tamaño = static_cast<int>(contenido.length());
        std::stringstream resultado;
        resultado << "Tamaño: " << tamaño << " caracteres - ";
        
        if (tamaño <= 100) {
            resultado << "✅ MUY SEGURO";
        } else if (tamaño <= 200) {
            resultado << "✅ SEGURO";
        } else if (tamaño <= 500) {
            resultado << "⚠️ ACEPTABLE";
        } else {
            resultado << "❌ DEMASIADO GRANDE";
        }
        
        return resultado.str();
    }

private:
    /// @brief Trunca texto a una longitud máxima
    static std::string truncarTexto(const std::string& texto, size_t maxLongitud) {
        if (texto.length() <= maxLongitud) {
            return texto;
        }
        return texto.substr(0, maxLongitud - 3) + "...";
    }

    /// @brief Extrae solo la fecha de una cadena de fecha/hora
    static std::string extraerFecha(const std::string& fechaCompleta) {
        // Si ya está en formato YYYY-MM-DD, devolverla tal como está
        if (fechaCompleta.length() >= 10 && fechaCompleta[4] == '-' && fechaCompleta[7] == '-') {
            return fechaCompleta.substr(0, 10);
        }
        
        // Si tiene formato diferente, intentar extraer o devolver tal como está
        return fechaCompleta.length() > 10 ? fechaCompleta.substr(0, 10) : fechaCompleta;
    }

    /// @brief Convierte TipoActividad a string
    static std::string tipoActividadToString(TipoActividad tipo) {
        switch (tipo) {
            case TipoActividad::CURSO:
                return "course";
            case TipoActividad::ESPECIALIZACION:
                return "specialization";
            default:
                return "unknown";
        }
    }
};

} // namespace QR
} // namespace CourseraClone

#endif // COURSERACLONE_UTILS_QR_AUTOCONTAINED_HPP
