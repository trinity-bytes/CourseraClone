// ═══════════════════════════════════════════════════════════════════════════════════
// QRCodeGenerator.hpp
// Generador de códigos QR ASCII para CourseraClone
// Wrapper simplificado para la librería de Nayuki adaptado al estilo del proyecto
// ═══════════════════════════════════════════════════════════════════════════════════

#ifndef COURSERACLONE_QR_QRCODEGENERATOR_HPP
#define COURSERACLONE_QR_QRCODEGENERATOR_HPP

// Headers estándar
#include <string>
#include <vector>
#include <stdexcept>
#include <map>

// Headers propios del proyecto
#include "../ColorPalette.hpp"

// Forward declarations para evitar incluir toda la librería de Nayuki en el header
namespace qrcodegen {
    class QrCode;
}

namespace CourseraClone {
namespace QR {

    /// @brief Estilos de renderizado ASCII para los códigos QR (simplificado)
    enum class ASCIIStyle {
        BASIC,          ///< Caracteres básicos: ##/espacios
        BLOCKS,         ///< Bloques Unicode: █░
        COURSERA_STYLE  ///< Estilo personalizado Coursera
    };

    /// @brief Configuración simplificada para la generación de códigos QR
    struct QRConfig {
        ASCIIStyle style = ASCIIStyle::COURSERA_STYLE;
        int borderSize = 2;
        bool useColors = false;  // Simplificado: sin colores por defecto
        
        /// @brief Constructor por defecto optimizado para demo
        QRConfig() = default;
    };

    /// @brief Clase principal para generar códigos QR ASCII (simplificada)
    class QRCodeGenerator {
    private:
        QRConfig _config;
        std::string _lastError;
        
        // Métodos privados de renderizado (simplificados)
        std::string renderBasicASCII(const qrcodegen::QrCode& qr) const;
        std::string renderBlocksASCII(const qrcodegen::QrCode& qr) const;
        std::string renderCourseraStyle(const qrcodegen::QrCode& qr) const;

    public:
        /// @brief Constructor con configuración personalizada
        explicit QRCodeGenerator(const QRConfig& config = QRConfig());
        
        /// @brief Destructor
        ~QRCodeGenerator() = default;
        
        // ========== MÉTODOS PRINCIPALES (SIMPLIFICADOS) ==========
        
        /// @brief Genera un código QR ASCII desde texto (corrección LOW)
        /// @param text Texto a codificar
        /// @return Código QR en formato ASCII, o string vacío si hay error
        std::string generateFromText(const std::string& text);
        
        /// @brief Genera un código QR para un comprobante de pago
        /// @param comprobanteId ID del comprobante
        /// @param estudianteId ID del estudiante
        /// @param monto Monto del pago
        /// @return Código QR en formato ASCII con información del comprobante
        std::string generateComprobanteQR(int comprobanteId, int estudianteId, double monto);
        
        /// @brief Genera un código QR para un curso
        /// @param cursoId ID del curso
        /// @param titulo Título del curso
        /// @return Código QR en formato ASCII con información del curso
        std::string generateCursoQR(int cursoId, const std::string& titulo);
        
        // ========== CONFIGURACIÓN BÁSICA ==========
        
        /// @brief Cambia el estilo de renderizado
        /// @param style Nuevo estilo ASCII
        void setStyle(ASCIIStyle style);
        
        // ========== UTILIDADES BÁSICAS ==========
        
        /// @brief Obtiene el último error ocurrido
        /// @return Descripción del último error
        std::string getLastError() const;
        
        /// @brief Renderiza un QR directamente en la consola
        /// @param qrString Código QR en formato string
        void printQR(const std::string& qrString) const;
        
        // ========== MÉTODOS ESTÁTICOS DE CONVENIENCIA ==========
        
        /// @brief Genera rápidamente un QR básico desde texto
        /// @param text Texto a codificar
        /// @return Código QR en formato ASCII básico
        static std::string quickGenerate(const std::string& text);
        
        /// @brief Genera un QR con estilo Coursera desde texto
        /// @param text Texto a codificar
        /// @return Código QR con estilo Coursera
        static std::string generateCourseraQR(const std::string& text);
        
        /// @brief Configura automáticamente el QR para el mejor balance entre tamaño y legibilidad
        /// @param contentLength Longitud estimada del contenido
        /// @return Configuración optimizada
        static QRConfig configuracionOptima(size_t contentLength);
        
        /// @brief Analiza el contenido y sugiere la mejor configuración
        /// @param text Texto a codificar
        /// @return Información sobre la configuración recomendada
        std::string analizarContenido(const std::string& text) const;
        
        /// @brief Genera múltiples versiones del QR con diferentes estilos para comparación
        /// @param text Texto a codificar
        /// @return Mapa con diferentes versiones del QR
        std::map<std::string, std::string> generarVariaciones(const std::string& text);
    };

} // namespace QR
} // namespace CourseraClone

#endif // COURSERACLONE_QR_QRCODEGENERATOR_HPP
