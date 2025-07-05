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
    
    /// @brief Genera un token de verificación simple para proyecto académico
    /// @param id1 Primer ID (comprobante/certificado)
    /// @param id2 Segundo ID (estudiante)
    /// @return Token de verificación
    static std::string generarTokenVerificacion(int id1, int id2) {
        // Token simple para proyecto académico (no usar en producción)
        std::stringstream ss;
        ss << std::hex << (id1 * 7 + id2 * 11 + 2024);
        std::string token = ss.str();
        
        // Agregar sufijo para hacer más legible
        token += "cc";  // CourseraClone
        
        return token;
    }
    
    /// @brief Codifica URL básica (reemplaza espacios y caracteres especiales)
    /// @param texto Texto a codificar
    /// @return Texto codificado para URL
    static std::string urlEncode(const std::string& texto) {
        std::string resultado;
        for (char c : texto) {
            if (c == ' ') {
                resultado += "%20";
            } else if (c == '&') {
                resultado += "%26";
            } else if (c == '=') {
                resultado += "%3D";
            } else if (c == '?') {
                resultado += "%3F";
            } else if (c == '#') {
                resultado += "%23";
            } else if (c == '/') {
                resultado += "%2F";
            } else {
                resultado += c;
            }
        }
        return resultado;
    }
    
    /// @brief Codificación base64 simple para proyecto académico
    /// @param input Datos a codificar
    /// @return Datos codificados en base64
    static std::string base64Encode(const std::string& input) {
        // Implementación básica de base64 para proyecto académico
        // En producción usar una librería especializada
        const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        std::string result;
        int val = 0, valb = -6;
        for (unsigned char c : input) {
            val = (val << 8) + c;
            valb += 8;
            while (valb >= 0) {
                result.push_back(chars[(val >> valb) & 0x3F]);
                valb -= 6;
            }
        }
        if (valb > -6) result.push_back(chars[((val << 8) >> (valb + 8)) & 0x3F]);
        while (result.size() % 4) result.push_back('=');
        return result;
    }

    /// @brief Abrevia nombres de manera inteligente
    /// @param nombreCompleto Nombre completo del estudiante
    /// @return Nombre super abreviado pero reconocible
    static std::string abreviarNombre(const std::string& nombreCompleto) {
        if (nombreCompleto.empty()) return "N/A";
        
        std::stringstream resultado;
        std::istringstream iss(nombreCompleto);
        std::string palabra;
        bool esPrimera = true;
        
        while (iss >> palabra && resultado.str().length() < 8) {  // Límite de 8 caracteres
            if (esPrimera) {
                // Primera palabra: tomar hasta 4 caracteres
                resultado << palabra.substr(0, 4);
                esPrimera = false;
            } else {
                // Otras palabras: solo inicial
                resultado << palabra[0];
            }
        }
        
        return resultado.str();
    }
    
    /// @brief Función auxiliar para reemplazar texto
    /// @param str String donde buscar y reemplazar
    /// @param desde Texto a buscar
    /// @param hacia Texto de reemplazo
    static void reemplazarTexto(std::string& str, const std::string& desde, const std::string& hacia) {
        size_t pos = 0;
        while ((pos = str.find(desde, pos)) != std::string::npos) {
            str.replace(pos, desde.length(), hacia);
            pos += hacia.length();
        }
    }
    
    /// @brief Abrevia nombres de cursos de manera contextual
    /// @param nombreActividad Nombre completo del curso/especialización
    /// @param tipo Tipo de actividad para contexto
    /// @return Curso abreviado pero descriptivo
    static std::string abreviarCurso(const std::string& nombreActividad, TipoActividad tipo) {
        if (nombreActividad.empty()) return "N/A";
        
        std::string nombre = nombreActividad;
        
        // Reemplazos específicos para términos comunes
        reemplazarTexto(nombre, "Programación", "Prog");
        reemplazarTexto(nombre, "Desarrollo", "Dev");
        reemplazarTexto(nombre, "Introducción", "Intro");
        reemplazarTexto(nombre, "Fundamentos", "Fund");
        reemplazarTexto(nombre, "Avanzado", "Adv");
        reemplazarTexto(nombre, "Especialización", "Esp");
        reemplazarTexto(nombre, "Certificación", "Cert");
        reemplazarTexto(nombre, "Algoritmos", "Algo");
        reemplazarTexto(nombre, "Estructura", "Struct");
        reemplazarTexto(nombre, "Datos", "Data");
        reemplazarTexto(nombre, "Ciencia", "Sci");
        reemplazarTexto(nombre, "Aplicaciones", "Apps");
        reemplazarTexto(nombre, "Sistemas", "Sys");
        reemplazarTexto(nombre, "Información", "Info");
        reemplazarTexto(nombre, "Tecnología", "Tech");
        reemplazarTexto(nombre, "Computación", "Comp");
        reemplazarTexto(nombre, "Inteligencia", "IA");
        reemplazarTexto(nombre, "Artificial", "Art");
        reemplazarTexto(nombre, "Machine Learning", "ML");
        reemplazarTexto(nombre, "Deep Learning", "DL");
        reemplazarTexto(nombre, "JavaScript", "JS");
        reemplazarTexto(nombre, "TypeScript", "TS");
        reemplazarTexto(nombre, "Python", "Py");
        reemplazarTexto(nombre, "Database", "DB");
        reemplazarTexto(nombre, "Frontend", "FE");
        reemplazarTexto(nombre, "Backend", "BE");
        reemplazarTexto(nombre, "Full Stack", "FS");
        
        // Eliminar palabras muy comunes que no aportan valor
        reemplazarTexto(nombre, " de ", " ");
        reemplazarTexto(nombre, " para ", " ");
        reemplazarTexto(nombre, " con ", " ");
        reemplazarTexto(nombre, " en ", " ");
        reemplazarTexto(nombre, " y ", " ");
        reemplazarTexto(nombre, " del ", " ");
        reemplazarTexto(nombre, " las ", " ");
        reemplazarTexto(nombre, " los ", " ");
        reemplazarTexto(nombre, " una ", " ");
        reemplazarTexto(nombre, " un ", " ");
        
        // Truncar si sigue siendo muy largo
        return truncarTexto(nombre, 15);
    }
    
    /// @brief Compacta fechas para usar menos caracteres
    /// @param fechaCompleta Fecha en formato completo
    /// @return Fecha en formato compacto
    static std::string compactarFecha(const std::string& fechaCompleta) {
        std::string fecha = extraerFecha(fechaCompleta);
        
        // Convertir de YYYY-MM-DD a YYMMDD (6 caracteres vs 10)
        if (fecha.length() >= 10 && fecha[4] == '-' && fecha[7] == '-') {
            std::string año = fecha.substr(2, 2);  // Solo últimos 2 dígitos del año
            std::string mes = fecha.substr(5, 2);
            std::string dia = fecha.substr(8, 2);
            return año + mes + dia;
        }
        
        return fecha;
    }
    
    /// @brief Codificación URL más compacta (solo caracteres problemáticos)
    /// @param texto Texto a codificar
    /// @return Texto con codificación mínima
    static std::string urlEncodeCompacto(const std::string& texto) {
        std::string resultado;
        for (char c : texto) {
            if (c == ' ') {
                resultado += "+";  // + es más corto que %20
            } else if (c == '&') {
                resultado += "%26";
            } else if (c == '=') {
                resultado += "%3D";
            } else {
                resultado += c;  // Mantener otros caracteres tal como están
            }
        }
        return resultado;
    }

public:
    
    /// @brief Base URL de la aplicación web (GitHub Pages)
    static inline std::string BASE_URL = "https://trinity-bytes.github.io/WebServices-for-CourseraClone";
    
    /// @brief Genera una URL para verificación de comprobante de pago
    /// @param comprobante Datos del comprobante
    /// @param nombreEstudiante Nombre completo del estudiante
    /// @param nombreActividad Nombre del curso/especialización
    /// @return URL optimizada para QR
    static std::string generarURLComprobante(
        const RawComprobanteData& comprobante,
        const std::string& nombreEstudiante,
        const std::string& nombreActividad
    ) {
        // Generar token de verificación simple (para proyecto académico)
        std::string token = generarTokenVerificacion(comprobante.id, comprobante.idEstudiante);
        
        std::stringstream url;
        url << BASE_URL << "/verify/receipt/" << comprobante.id
            << "?token=" << token
            << "&student=" << urlEncode(truncarTexto(nombreEstudiante, 20))
            << "&course=" << urlEncode(truncarTexto(nombreActividad, 30))
            << "&type=" << tipoActividadToString(comprobante.tipoActividad)
            << "&amount=" << std::fixed << std::setprecision(2) << comprobante.montoPagado
            << "&date=" << extraerFecha(comprobante.fechaEmision);
        
        return url.str();
    }
    
    /// @brief Genera una URL para verificación de certificado
    /// @param idCertificado ID único del certificado
    /// @param nombreEstudiante Nombre completo del estudiante
    /// @param nombreActividad Nombre del curso/especialización
    /// @param tipoActividad Tipo de actividad
    /// @return URL optimizada para QR
    static std::string generarURLCertificado(
        int idCertificado,
        const std::string& nombreEstudiante,
        const std::string& nombreActividad,
        TipoActividad tipoActividad
    ) {
        std::string token = generarTokenVerificacion(idCertificado, 0);
        
        std::stringstream url;
        url << BASE_URL << "/verify/certificate/" << idCertificado
            << "?token=" << token
            << "&student=" << urlEncode(truncarTexto(nombreEstudiante, 20))
            << "&course=" << urlEncode(truncarTexto(nombreActividad, 30))
            << "&type=" << tipoActividadToString(tipoActividad);
        
        return url.str();
    }
    
    /// @brief Genera una URL con datos autocontenidos (JSON codificado) para GitHub Pages
    /// @param comprobante Datos del comprobante
    /// @param nombreEstudiante Nombre completo del estudiante
    /// @param nombreActividad Nombre del curso/especialización
    /// @return URL con datos completos codificados
    static std::string generarURLAutocontenida(
        const RawComprobanteData& comprobante,
        const std::string& nombreEstudiante,
        const std::string& nombreActividad
    ) {
        // Generar JSON compacto
        std::string jsonData = generarQRComprobante(comprobante, nombreEstudiante, nombreActividad);
        
        // Codificar en base64 simple (para proyecto académico)
        std::string dataEncoded = base64Encode(jsonData);
        
        std::stringstream url;
        url << BASE_URL << "/verify/data?payload=" << dataEncoded;
        
        return url.str();
    }
    
    /// @brief Genera una URL simple para página principal con parámetros básicos
    /// @param comprobante Datos del comprobante
    /// @param nombreEstudiante Nombre completo del estudiante
    /// @param nombreActividad Nombre del curso/especialización
    /// @return URL simple para GitHub Pages
    static std::string generarURLPaginaPrincipal(
        const RawComprobanteData& comprobante,
        const std::string& nombreEstudiante,
        const std::string& nombreActividad
    ) {
        std::string token = generarTokenVerificacion(comprobante.id, comprobante.idEstudiante);
        
        std::stringstream url;
        url << BASE_URL << "/?receipt=" << comprobante.id
            << "&token=" << token
            << "&verify=true";
        
        return url.str();
    }
    
    /// @brief Configura la URL base de la aplicación (para desarrollo/producción)
    /// @param nuevaUrl Nueva URL base
    static void configurarURLBase(const std::string& nuevaUrl) {
        BASE_URL = nuevaUrl;
    }
    
    /// @brief Configura para GitHub Pages con repositorio específico
    /// @param usuario Usuario de GitHub
    /// @param repositorio Nombre del repositorio
    static void configurarGitHubPages(const std::string& usuario, const std::string& repositorio) {
        BASE_URL = "https://" + usuario + ".github.io/" + repositorio;
    }
    
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
        json << "\"courseType\":\"" << tipoActividadToString(comprobante.tipoActividad) << "\",";
        json << "\"studentId\":" << comprobante.idEstudiante << ",";
        json << "\"activityId\":" << comprobante.idActividad;
        json << "}";
        return json.str();
    }

    /// @brief Genera un QR JSON COMPACTO para comprobante de pago
    /// @param comprobante Datos del comprobante
    /// @param nombreEstudiante Nombre completo del estudiante
    /// @param nombreActividad Nombre del curso/especialización
    /// @return JSON ultra-compacto para el QR
    static std::string generarQRComprobanteCompacto(
        const RawComprobanteData& comprobante,
        const std::string& nombreEstudiante,
        const std::string& nombreActividad
    ) {
        std::stringstream json;
        json << "{";
        json << "\"t\":\"r\",";  // type = receipt (abreviado)
        json << "\"i\":" << comprobante.id << ",";  // id
        json << "\"nm\":\"" << abreviarNombre(nombreEstudiante) << "\",";  // nombre abreviado inteligentemente
        json << "\"crs\":\"" << abreviarCurso(nombreActividad, comprobante.tipoActividad) << "\",";   // curso abreviado
        json << "\"dt\":\"" << compactarFecha(comprobante.fechaEmision) << "\",";  // fecha compacta
        json << "\"amt\":" << std::fixed << std::setprecision(2) << comprobante.montoPagado << ",";  // amount
        json << "\"tp\":\"" << (comprobante.tipoActividad == TipoActividad::CURSO ? "c" : "e") << "\",";  // tipo más claro
        json << "\"si\":" << comprobante.idEstudiante << ",";  // studentId
        json << "\"ai\":" << comprobante.idActividad;  // activityId
        json << "}";
        return json.str();
    }
    
    /// @brief Genera un QR JSON ULTRA-COMPACTO para comprobante de pago
    /// @param comprobante Datos del comprobante
    /// @param nombreEstudiante Nombre completo del estudiante
    /// @param nombreActividad Nombre del curso/especialización
    /// @return JSON ultra-compacto para el QR más pequeño posible
    static std::string generarQRComprobanteUltraCompacto(
        const RawComprobanteData& comprobante,
        const std::string& nombreEstudiante,
        const std::string& nombreActividad
    ) {
        std::stringstream json;
        json << "{";
        json << "\"t\":\"r\",";  // type = receipt
        json << "\"i\":" << comprobante.id << ",";  // id del comprobante
        json << "\"n\":\"" << abreviarNombre(nombreEstudiante) << "\",";  // nombre (super abreviado)
        json << "\"crs\":\"" << abreviarCurso(nombreActividad, comprobante.tipoActividad) << "\",";   // curso abreviado
        json << "\"d\":\"" << compactarFecha(comprobante.fechaEmision) << "\",";  // fecha compacta
        json << "\"$\":" << std::fixed << std::setprecision(2) << comprobante.montoPagado << ",";  // monto con símbolo
        json << "\"tp\":\"" << (comprobante.tipoActividad == TipoActividad::CURSO ? "c" : "e") << "\",";  // tipo: c=curso, e=especialización
        json << "\"si\":" << comprobante.idEstudiante << ",";  // student id
        json << "\"ci\":" << comprobante.idActividad;  // course/activity id
        json << "}";
        return json.str();
    }
    
    /// @brief Genera una URL autocontenida COMPACTA (para QR más legibles)
    /// @param comprobante Datos del comprobante
    /// @param nombreEstudiante Nombre completo del estudiante
    /// @param nombreActividad Nombre del curso/especialización
    /// @return URL más corta para QR más legible
    static std::string generarURLAutocontenidaCompacta(
        const RawComprobanteData& comprobante,
        const std::string& nombreEstudiante,
        const std::string& nombreActividad
    ) {
        // Generar JSON compacto mejorado
        std::string jsonData = generarQRComprobanteCompacto(comprobante, nombreEstudiante, nombreActividad);
        
        // Codificar en base64 simple
        std::string dataEncoded = base64Encode(jsonData);
        
        std::stringstream url;
        url << BASE_URL << "/v?d=" << dataEncoded;  // 'd' es más corto que 'p' (payload)
        
        return url.str();
    }
    
    /// @brief Genera una URL autocontenida ULTRA-COMPACTA (máxima optimización)
    /// @param comprobante Datos del comprobante
    /// @param nombreEstudiante Nombre completo del estudiante
    /// @param nombreActividad Nombre del curso/especialización
    /// @return URL súper corta para QR más pequeño
    static std::string generarURLUltraCompacta(
        const RawComprobanteData& comprobante,
        const std::string& nombreEstudiante,
        const std::string& nombreActividad
    ) {
        // Generar JSON ultra-compacto
        std::string jsonData = generarQRComprobanteUltraCompacto(comprobante, nombreEstudiante, nombreActividad);
        
        // Codificar en base64 simple
        std::string dataEncoded = base64Encode(jsonData);
        
        std::stringstream url;
        // Usar dominio más corto si es posible + ruta mínima
        url << "https://trin.by/v?d=" << dataEncoded;  // Dominio ultra-corto + ruta mínima
        
        return url.str();
    }

    /// @brief Genera una URL usando parámetros directos (sin JSON) para máxima compactación
    /// @param comprobante Datos del comprobante
    /// @param nombreEstudiante Nombre completo del estudiante
    /// @param nombreActividad Nombre del curso/especialización
    /// @return URL con parámetros directos, ultra-compacta
    static std::string generarURLParametrosDirectos(
        const RawComprobanteData& comprobante,
        const std::string& nombreEstudiante,
        const std::string& nombreActividad
    ) {
        std::stringstream url;
        url << "https://trin.by/r/"  // r = receipt
            << comprobante.id << "/"
            << comprobante.idEstudiante << "/"
            << comprobante.idActividad
            << "?n=" << urlEncodeCompacto(abreviarNombre(nombreEstudiante))
            << "&c=" << urlEncodeCompacto(abreviarCurso(nombreActividad, comprobante.tipoActividad))
            << "&d=" << compactarFecha(comprobante.fechaEmision)
            << "&$=" << std::fixed << std::setprecision(2) << comprobante.montoPagado
            << "&t=" << (comprobante.tipoActividad == TipoActividad::CURSO ? "c" : "e");
        
        return url.str();
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

    /// @brief Genera un QR JSON con formato estándar según especificación definida
    /// @param comprobante Datos del comprobante
    /// @param nombreEstudiante Nombre completo del estudiante
    /// @param nombreActividad Nombre del curso/especialización
    /// @return JSON en formato estándar según especificación
    static std::string generarQRComprobanteEstandar(
        const RawComprobanteData& comprobante,
        const std::string& nombreEstudiante,
        const std::string& nombreActividad
    ) {
        std::stringstream json;
        json << "{";
        json << "\"t\":\"r\",";  // Tipo de documento: "r" = boleta, "c" = certificado
        json << "\"i\":" << comprobante.id << ",";  // ID único de la boleta
        json << "\"s\":\"" << nombreEstudiante << "\",";  // Nombre completo del estudiante (sin límite)
        json << "\"c\":\"" << nombreActividad << "\",";  // Nombre completo del curso (sin límite)
        json << "\"d\":\"" << extraerFecha(comprobante.fechaEmision) << "\",";  // Fecha de emisión formato YYYY-MM-DD
        json << "\"a\":" << std::fixed << std::setprecision(2) << comprobante.montoPagado << ",";  // Monto pagado (decimal)
        json << "\"ct\":\"" << (comprobante.tipoActividad == TipoActividad::CURSO ? "c" : "e") << "\"";  // Tipo de contenido: "c" = curso, "e" = especialización
        json << "}";
        return json.str();
    }
    
    /// @brief Genera una URL con el formato estándar para máxima compatibilidad
    /// @param comprobante Datos del comprobante
    /// @param nombreEstudiante Nombre completo del estudiante
    /// @param nombreActividad Nombre del curso/especialización
    /// @return URL con JSON estándar para máxima compatibilidad web
    static std::string generarURLEstandar(
        const RawComprobanteData& comprobante,
        const std::string& nombreEstudiante,
        const std::string& nombreActividad
    ) {
        // Generar JSON en formato estándar exacto
        std::string jsonData = generarQRComprobanteEstandar(comprobante, nombreEstudiante, nombreActividad);
        
        // Codificar en base64 (equivalente a btoa en JavaScript)
        std::string dataEncoded = base64Encode(jsonData);
        
        std::stringstream url;
        // Formato exacto: https://trinity-bytes.github.io/WebServices-for-CourseraClone/v?d={base64_payload}
        url << BASE_URL << "/v?d=" << dataEncoded;
        
        return url.str();
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
};

} // namespace QR
} // namespace CourseraClone

#endif // COURSERACLONE_UTILS_QR_AUTOCONTAINED_HPP
