// ═══════════════════════════════════════════════════════════════════════════════════
// QRCodeGenerator.cpp
// Implementación simplificada del generador de códigos QR ASCII para CourseraClone
// ═══════════════════════════════════════════════════════════════════════════════════

#include "Utils/QR/QRCodeGenerator.hpp"
#include "Utils/QR/qrcodegen.hpp"
#include "Utils/ColorPalette.hpp"
#include "Utils/ConsoleRenderer.hpp"
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace CourseraClone::QR;
using namespace qrcodegen;

// ═══════════════════════════════════════════════════════════════════════════════════
// CONSTRUCTOR Y CONFIGURACIÓN BÁSICA
// ═══════════════════════════════════════════════════════════════════════════════════

QRCodeGenerator::QRCodeGenerator(const QRConfig& config) : _config(config) {
    // Constructor simplificado
}

void QRCodeGenerator::setStyle(ASCIIStyle style) {
    _config.style = style;
}

std::string QRCodeGenerator::getLastError() const {
    return _lastError;
}

// ═══════════════════════════════════════════════════════════════════════════════════
// MÉTODOS PRINCIPALES DE GENERACIÓN (SIMPLIFICADOS)
// ═══════════════════════════════════════════════════════════════════════════════════

std::string QRCodeGenerator::generateFromText(const std::string& text) {
    try {
        _lastError.clear();
        
        // Usar siempre corrección de errores LOW (simplificado)
        QrCode qr = QrCode::encodeText(text.c_str(), QrCode::Ecc::LOW);
        
        // Renderizar según el estilo configurado
        switch (_config.style) {
            case ASCIIStyle::BASIC:
                return renderBasicASCII(qr);
            case ASCIIStyle::BLOCKS:
                return renderBlocksASCII(qr);
            case ASCIIStyle::COURSERA_STYLE:
                return renderCourseraStyle(qr);
            default:
                return renderBasicASCII(qr);
        }
        
    } catch (const std::exception& e) {
        _lastError = "Error al generar QR: " + std::string(e.what());
        return "";
    }
}

std::string QRCodeGenerator::generateComprobanteQR(int comprobanteId, int estudianteId, double monto) {
    // Crear string con información del comprobante
    std::stringstream ss;
    ss << "COURSERA_COMPROBANTE|"
       << "ID:" << comprobanteId << "|"
       << "ESTUDIANTE:" << estudianteId << "|"
       << "MONTO:" << std::fixed << std::setprecision(2) << monto << "|"
       << "VERIFICAR:coursera.clone/verify/" << comprobanteId;
    
    return generateFromText(ss.str());
}

std::string QRCodeGenerator::generateCursoQR(int cursoId, const std::string& titulo) {
    std::stringstream ss;
    ss << "COURSERA_CURSO|"
       << "ID:" << cursoId << "|"
       << "TITULO:" << titulo << "|"
       << "URL:coursera.clone/curso/" << cursoId;
    
    return generateFromText(ss.str());
}

// ═══════════════════════════════════════════════════════════════════════════════════
// MÉTODOS DE RENDERIZADO ASCII (SIMPLIFICADOS)
// ═══════════════════════════════════════════════════════════════════════════════════

std::string QRCodeGenerator::renderBasicASCII(const QrCode& qr) const {
    std::stringstream result;
    int size = qr.getSize();
    
    // Añadir borde superior
    for (int i = 0; i < _config.borderSize; ++i) {
        for (int x = -_config.borderSize; x < size + _config.borderSize; ++x) {
            result << "  "; // Doble espacio para hacer cuadrados
        }
        result << "\n";
    }
    
    // Renderizar el QR
    for (int y = 0; y < size; ++y) {
        // Borde izquierdo
        for (int i = 0; i < _config.borderSize; ++i) {
            result << "  ";
        }
        
        // Módulos del QR
        for (int x = 0; x < size; ++x) {
            bool isDark = qr.getModule(x, y);
            result << (isDark ? "██" : "  ");
        }
        
        // Borde derecho
        for (int i = 0; i < _config.borderSize; ++i) {
            result << "  ";
        }
        result << "\n";
    }
    
    // Añadir borde inferior
    for (int i = 0; i < _config.borderSize; ++i) {
        for (int x = -_config.borderSize; x < size + _config.borderSize; ++x) {
            result << "  ";
        }
        result << "\n";
    }
    
    return result.str();
}

std::string QRCodeGenerator::renderBlocksASCII(const QrCode& qr) const {
    std::stringstream result;
    int size = qr.getSize();
    
    // Añadir borde superior
    for (int i = 0; i < _config.borderSize; ++i) {
        for (int x = -_config.borderSize; x < size + _config.borderSize; ++x) {
            result << "░";
        }
        result << "\n";
    }
    
    // Renderizar el QR
    for (int y = 0; y < size; ++y) {
        // Borde izquierdo
        for (int i = 0; i < _config.borderSize; ++i) {
            result << "░";
        }
        
        // Módulos del QR
        for (int x = 0; x < size; ++x) {
            bool isDark = qr.getModule(x, y);
            result << (isDark ? "█" : "░");
        }
        
        // Borde derecho
        for (int i = 0; i < _config.borderSize; ++i) {
            result << "░";
        }
        result << "\n";
    }
    
    // Añadir borde inferior
    for (int i = 0; i < _config.borderSize; ++i) {
        for (int x = -_config.borderSize; x < size + _config.borderSize; ++x) {
            result << "░";
        }
        result << "\n";
    }
    
    return result.str();
}

std::string QRCodeGenerator::renderCourseraStyle(const QrCode& qr) const {
    std::stringstream result;
    int size = qr.getSize();
    
    // Header con estilo Coursera
    result << "\n";
    result << "  ╔════════════════════════════╗\n";
    result << "  ║     COURSERA QR CODE       ║\n";
    result << "  ╚════════════════════════════╝\n";
    result << "\n";
    
    // Renderizar QR con estilo de bloques
    for (int y = -_config.borderSize; y < size + _config.borderSize; ++y) {
        result << "    "; // Indentación para centrar
        for (int x = -_config.borderSize; x < size + _config.borderSize; ++x) {
            bool isDark = false;
            if (x >= 0 && x < size && y >= 0 && y < size) {
                isDark = qr.getModule(x, y);
            }
            
            result << (isDark ? "██" : "  ");
        }
        result << "\n";
    }
    
    result << "\n";
    return result.str();
}

// ═══════════════════════════════════════════════════════════════════════════════════
// MÉTODOS DE UTILIDAD
// ═══════════════════════════════════════════════════════════════════════════════════

void QRCodeGenerator::printQR(const std::string& qrString) const {
    if (_config.useColors && _config.style == ASCIIStyle::COURSERA_STYLE) {
        // Imprimir header con color azul Coursera
        setTextColor(ColorIndex::AZUL_MARCA, true);
        std::cout << "\n";
        std::cout << "  ╔════════════════════════════╗\n";
        std::cout << "  ║     COURSERA QR CODE       ║\n";
        std::cout << "  ╚════════════════════════════╝\n";
        resetColor();
        
        // Buscar el contenido del QR (después del header)
        size_t startPos = qrString.find("╝\n\n");
        if (startPos != std::string::npos) {
            startPos += 3; // Saltar "╝\n\n"
            std::string qrContent = qrString.substr(startPos);
            
            // Imprimir QR con colores
            std::istringstream iss(qrContent);
            std::string line;
            while (std::getline(iss, line)) {
                std::cout << "    "; // Indentación
                for (char c : line) {
                    if (c == '█') {
                        setTextColor(ColorIndex::AZUL_MARCA);
                        std::cout << "██";
                        resetColor();
                    } else {
                        std::cout << "  ";
                    }
                }
                std::cout << "\n";
            }
        }
    } else {
        std::cout << qrString;
    }
    std::cout << std::endl;
}

// ═══════════════════════════════════════════════════════════════════════════════════
// MÉTODOS ESTÁTICOS DE CONVENIENCIA
// ═══════════════════════════════════════════════════════════════════════════════════

std::string QRCodeGenerator::quickGenerate(const std::string& text) {
    QRConfig config;
    config.style = ASCIIStyle::BASIC;
    config.useColors = false;
    
    QRCodeGenerator generator(config);
    return generator.generateFromText(text);
}

std::string QRCodeGenerator::generateCourseraQR(const std::string& text) {
    QRConfig config;
    config.style = ASCIIStyle::COURSERA_STYLE;
    config.useColors = true;
    config.borderSize = 2;
    
    QRCodeGenerator generator(config);
    return generator.generateFromText(text);
}
