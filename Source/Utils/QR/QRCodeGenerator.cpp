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
#include <map>

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
        
        // OPTIMIZACIÓN 1: Selección inteligente del nivel de corrección según tamaño
        QrCode::Ecc correctionLevel;
        if (text.length() <= 100) {
            // URLs cortas: usar HIGH para máxima resistencia a daños (~30% tolerancia)
            correctionLevel = QrCode::Ecc::HIGH;
        } else if (text.length() <= 300) {
            // URLs medianas: usar QUARTILE para balance (~25% tolerancia)
            correctionLevel = QrCode::Ecc::QUARTILE;
        } else {
            // URLs largas: usar MEDIUM para legibilidad (~15% tolerancia)
            correctionLevel = QrCode::Ecc::MEDIUM;
        }
        
        QrCode qr = QrCode::encodeText(text.c_str(), correctionLevel);
        
        // OPTIMIZACIÓN 2: Ajuste automático del borde según tamaño del QR
        int originalBorderSize = _config.borderSize;
        int qrSize = qr.getSize();
        
        // QRs grandes necesitan bordes más pequeños para caber en pantalla
        if (qrSize > 50) {
            _config.borderSize = 1;  // Borde mínimo para QRs grandes
        } else if (qrSize > 35) {
            _config.borderSize = (std::max)(1, _config.borderSize - 1);  // Reducir borde
        }
        // QRs pequeños mantienen el borde original para mejor visibilidad
        
        std::string result;
        
        // Renderizar según el estilo configurado
        switch (_config.style) {
            case ASCIIStyle::BASIC:
                result = renderBasicASCII(qr);
                break;
            case ASCIIStyle::BLOCKS:
                result = renderBlocksASCII(qr);
                break;
            case ASCIIStyle::COURSERA_STYLE:
                result = renderCourseraStyle(qr);
                break;
            default:
                result = renderBasicASCII(qr);
                break;
        }
        
        // Restaurar configuración original del borde
        _config.borderSize = originalBorderSize;
        
        return result;
        
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
    
    // OPTIMIZACIÓN 3: Borde adaptativo según tamaño
    int effectiveBorder = _config.borderSize;
    
    // OPTIMIZACIÓN 4: Caracteres más densos para mejor contraste en ASCII
    const std::string darkBlock = "██";  // Bloque completo
    const std::string lightBlock = "  "; // Espacio doble para mantener proporción
    
    // Añadir borde superior con caracteres de borde específicos
    for (int i = 0; i < effectiveBorder; ++i) {
        for (int x = -effectiveBorder; x < size + effectiveBorder; ++x) {
            result << lightBlock; // Usar bloques consistentes
        }
        result << "\n";
    }
    
    // Renderizar el QR con mejor contraste
    for (int y = 0; y < size; ++y) {
        // Borde izquierdo
        for (int i = 0; i < effectiveBorder; ++i) {
            result << lightBlock;
        }
        
        // OPTIMIZACIÓN 5: Renderizado de módulos con mayor densidad
        for (int x = 0; x < size; ++x) {
            bool isDark = qr.getModule(x, y);
            result << (isDark ? darkBlock : lightBlock);
        }
        
        // Borde derecho
        for (int i = 0; i < effectiveBorder; ++i) {
            result << lightBlock;
        }
        result << "\n";
    }
    
    // Añadir borde inferior
    for (int i = 0; i < effectiveBorder; ++i) {
        for (int x = -effectiveBorder; x < size + effectiveBorder; ++x) {
            result << lightBlock;
        }
        result << "\n";
    }
    
    return result.str();
}

std::string QRCodeGenerator::renderBlocksASCII(const QrCode& qr) const {
    std::stringstream result;
    int size = qr.getSize();
    
    // OPTIMIZACIÓN 6: Caracteres Unicode mejorados para mejor visibilidad
    const std::string darkModule = "█";   // Bloque completo sólido
    const std::string lightModule = "░";  // Bloque ligero para fondo
    const std::string borderChar = "▓";   // Bloque medio para borde distintivo
    
    // Añadir borde superior con carácter distintivo
    for (int i = 0; i < _config.borderSize; ++i) {
        for (int x = -_config.borderSize; x < size + _config.borderSize; ++x) {
            result << borderChar;
        }
        result << "\n";
    }
    
    // Renderizar el QR con caracteres diferenciados
    for (int y = 0; y < size; ++y) {
        // Borde izquierdo distintivo
        for (int i = 0; i < _config.borderSize; ++i) {
            result << borderChar;
        }
        
        // Módulos del QR con mejor contraste
        for (int x = 0; x < size; ++x) {
            bool isDark = qr.getModule(x, y);
            result << (isDark ? darkModule : lightModule);
        }
        
        // Borde derecho distintivo
        for (int i = 0; i < _config.borderSize; ++i) {
            result << borderChar;
        }
        result << "\n";
    }
    
    // Añadir borde inferior con carácter distintivo
    for (int i = 0; i < _config.borderSize; ++i) {
        for (int x = -_config.borderSize; x < size + _config.borderSize; ++x) {
            result << borderChar;
        }
        result << "\n";
    }
    
    return result.str();
}

std::string QRCodeGenerator::renderCourseraStyle(const QrCode& qr) const {
    std::stringstream result;
    int size = qr.getSize();
    
    // OPTIMIZACIÓN 7: Header adaptativo según tamaño del QR
    result << "\n";
    if (size <= 25) {
        // QR pequeño - header compacto
        result << "  ╔══════════════════╗\n";
        result << "  ║   COURSERA QR    ║\n";
        result << "  ╚══════════════════╝\n";
    } else if (size <= 40) {
        // QR mediano - header estándar
        result << "  ╔════════════════════════════╗\n";
        result << "  ║     COURSERA QR CODE       ║\n";
        result << "  ╚════════════════════════════╝\n";
    } else {
        // QR grande - header extendido
        result << "  ╔════════════════════════════════════╗\n";
        result << "  ║        COURSERA QR CODE            ║\n";
        result << "  ║     Escanea para verificar         ║\n";
        result << "  ╚════════════════════════════════════╝\n";
    }
    result << "\n";
    
    // OPTIMIZACIÓN 8: Indentación dinámica para centrado visual
    int indentation = (std::max)(2, (50 - size) / 4);  // Centrado adaptativo
    std::string indent(indentation, ' ');
    
    // Renderizar QR con estilo mejorado y centrado
    for (int y = -_config.borderSize; y < size + _config.borderSize; ++y) {
        result << indent; // Indentación para centrar
        for (int x = -_config.borderSize; x < size + _config.borderSize; ++x) {
            bool isDark = false;
            if (x >= 0 && x < size && y >= 0 && y < size) {
                isDark = qr.getModule(x, y);
            }
            
            // OPTIMIZACIÓN 9: Caracteres más visibles para estilo Coursera
            result << (isDark ? "██" : "░░");
        }
        result << "\n";
    }
    
    result << "\n";
    
    // OPTIMIZACIÓN 10: Footer informativo adaptativo
    if (size > 35) {
        result << indent << "┌─── QR de alta densidad ───┐\n";
        result << indent << "│ Escanea desde cerca para  │\n";
        result << indent << "│    mejor legibilidad      │\n";
        result << indent << "└───────────────────────────┘\n";
    }
    
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
// NUEVOS MÉTODOS DE OPTIMIZACIÓN Y ANÁLISIS
// ═══════════════════════════════════════════════════════════════════════════════════

QRConfig QRCodeGenerator::configuracionOptima(size_t contentLength) {
    QRConfig config;
    
    if (contentLength <= 50) {
        // Contenido muy corto - máxima calidad visual
        config.style = ASCIIStyle::COURSERA_STYLE;
        config.borderSize = 3;
        config.useColors = true;
    } else if (contentLength <= 200) {
        // Contenido moderado - balance entre calidad y tamaño
        config.style = ASCIIStyle::BLOCKS;
        config.borderSize = 2;
        config.useColors = false;
    } else {
        // Contenido largo - priorizar compacidad
        config.style = ASCIIStyle::BASIC;
        config.borderSize = 1;
        config.useColors = false;
    }
    
    return config;
}

std::string QRCodeGenerator::analizarContenido(const std::string& text) const {
    std::stringstream analysis;
    size_t length = text.length();
    
    analysis << "=== ANÁLISIS DEL CONTENIDO QR ===\n";
    analysis << "Longitud: " << length << " caracteres\n";
    
    // Estimar tamaño del QR resultante
    if (length <= 25) {
        analysis << "Tamaño estimado: Muy pequeño (≤21x21)\n";
        analysis << "Recomendación: Estilo COURSERA_STYLE con borde grande\n";
        analysis << "Nivel de corrección: HIGH para máxima resistencia\n";
    } else if (length <= 100) {
        analysis << "Tamaño estimado: Pequeño (25x25 - 29x29)\n";
        analysis << "Recomendación: Estilo BLOCKS con borde medio\n";
        analysis << "Nivel de corrección: QUARTILE para balance\n";
    } else if (length <= 300) {
        analysis << "Tamaño estimado: Mediano (33x33 - 41x41)\n";
        analysis << "Recomendación: Estilo BASIC con borde pequeño\n";
        analysis << "Nivel de corrección: MEDIUM para legibilidad\n";
    } else {
        analysis << "Tamaño estimado: Grande (≥45x45)\n";
        analysis << "Recomendación: Estilo BASIC con borde mínimo\n";
        analysis << "Nivel de corrección: MEDIUM para mantener tamaño\n";
        analysis << "⚠️ Considerar acortar el contenido para mejor escaneo\n";
    }
    
    // Análisis de caracteres especiales
    bool hasUTF8 = false;
    for (unsigned char c : text) {
        if (c > 127) {
            hasUTF8 = true;
            break;
        }
    }
    
    if (hasUTF8) {
        analysis << "Codificación: UTF-8 detectada ✓\n";
        analysis << "Nota: Caracteres especiales aumentan el tamaño del QR\n";
    } else {
        analysis << "Codificación: ASCII puro ✓\n";
    }
    
    return analysis.str();
}

std::map<std::string, std::string> QRCodeGenerator::generarVariaciones(const std::string& text) {
    std::map<std::string, std::string> variaciones;
    
    // Configuraciones predefinidas para comparación
    std::vector<std::pair<std::string, QRConfig>> configs = {
        {"Básico Compacto", {ASCIIStyle::BASIC, 1, false}},
        {"Bloques Estándar", {ASCIIStyle::BLOCKS, 2, false}},
        {"Coursera Premium", {ASCIIStyle::COURSERA_STYLE, 3, true}},
        {"Óptimo Auto", configuracionOptima(text.length())}
    };
    
    for (const auto& configPair : configs) {
        QRCodeGenerator tempGenerator(configPair.second);
        std::string qrResult = tempGenerator.generateFromText(text);
        
        if (!qrResult.empty()) {
            std::stringstream header;
            header << "\n=== " << configPair.first << " ===\n";
            header << "Estilo: " << static_cast<int>(configPair.second.style) << "\n";
            header << "Borde: " << configPair.second.borderSize << "\n";
            header << "Colores: " << (configPair.second.useColors ? "Sí" : "No") << "\n\n";
            
            variaciones[configPair.first] = header.str() + qrResult;
        } else {
            variaciones[configPair.first] = "Error al generar esta variación";
        }
    }
    
    return variaciones;
}

// ═══════════════════════════════════════════════════════════════════════════════════
// MÉTODOS ESTÁTICOS DE CONVENIENCIA MEJORADOS
// ═══════════════════════════════════════════════════════════════════════════════════

std::string QRCodeGenerator::quickGenerate(const std::string& text) {
    // OPTIMIZACIÓN 11: Usar configuración automática óptima
    QRConfig config = configuracionOptima(text.length());
    
    QRCodeGenerator generator(config);
    return generator.generateFromText(text);
}

std::string QRCodeGenerator::generateCourseraQR(const std::string& text) {
    QRConfig config;
    config.style = ASCIIStyle::COURSERA_STYLE;
    config.useColors = true;
    config.borderSize = (text.length() > 200) ? 1 : 2;  // Borde adaptativo
    
    QRCodeGenerator generator(config);
    return generator.generateFromText(text);
}
