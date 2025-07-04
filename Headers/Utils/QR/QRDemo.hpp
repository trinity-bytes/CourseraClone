// ═══════════════════════════════════════════════════════════════════════════════════
// QRDemo.hpp
// Demostración simplificada del generador QR para CourseraClone
// ═══════════════════════════════════════════════════════════════════════════════════

#ifndef COURSERACLONE_QR_QRDEMO_HPP
#define COURSERACLONE_QR_QRDEMO_HPP

#include "QRCodeGenerator.hpp"
#include "../ConsoleRenderer.hpp"
#include <iostream>
#include <string>

namespace CourseraClone {
namespace QR {

    /// @brief Clase para demostrar el uso simplificado del generador QR
    class QRDemo {
    public:
        /// @brief Ejecuta una demostración completa del generador QR
        static void runFullDemo();
        
        /// @brief Demuestra diferentes estilos de renderizado
        static void demoStyles();
        
        /// @brief Demuestra generación de QR para comprobantes
        static void demoComprobantes();
        
        /// @brief Demuestra generación de QR para cursos
        static void demoCursos();
        
        /// @brief Demo rápido para testing
        static void quickDemo();

    private:
        static void printHeader(const std::string& title);
        static void printSeparator();
    };

    // ═══════════════════════════════════════════════════════════════════════════════════
    // IMPLEMENTACIÓN INLINE SIMPLIFICADA
    // ═══════════════════════════════════════════════════════════════════════════════════

    inline void QRDemo::runFullDemo() {
        printHeader("DEMO GENERADOR QR COURSERA");
        
        demoStyles();
        printSeparator();
        demoComprobantes();
        printSeparator();
        demoCursos();
        printSeparator();
    }

    inline void QRDemo::demoStyles() {
        printHeader("ESTILOS DE RENDERIZADO");
        
        std::string texto = "Coursera Demo";
        
        // Estilo básico
        std::cout << "\n1. ESTILO BÁSICO:\n";
        QRConfig basicConfig;
        basicConfig.style = ASCIIStyle::BASIC;
        QRCodeGenerator basicGen(basicConfig);
        std::string basicQR = basicGen.generateFromText(texto);
        std::cout << basicQR << "\n";
        
        // Estilo bloques
        std::cout << "\n2. ESTILO BLOQUES:\n";
        QRConfig blocksConfig;
        blocksConfig.style = ASCIIStyle::BLOCKS;
        QRCodeGenerator blocksGen(blocksConfig);
        std::string blocksQR = blocksGen.generateFromText(texto);
        std::cout << blocksQR << "\n";
        
        // Estilo Coursera
        std::cout << "\n3. ESTILO COURSERA:\n";
        std::string courseraQR = QRCodeGenerator::generateCourseraQR(texto);
        std::cout << courseraQR << "\n";
    }

    inline void QRDemo::demoComprobantes() {
        printHeader("QR PARA COMPROBANTES");
        
        QRCodeGenerator generator;
        std::string comprobanteQR = generator.generateComprobanteQR(12345, 67890, 299.99);
        std::cout << "\nComprobante ID: 12345, Estudiante: 67890, Monto: $299.99\n";
        std::cout << comprobanteQR << "\n";
    }

    inline void QRDemo::demoCursos() {
        printHeader("QR PARA CURSOS");
        
        QRCodeGenerator generator;
        std::string cursoQR = generator.generateCursoQR(101, "Algoritmos y Estructuras de Datos");
        std::cout << "\nCurso: Algoritmos y Estructuras de Datos (ID: 101)\n";
        std::cout << cursoQR << "\n";
    }

    inline void QRDemo::quickDemo() {
        std::cout << "=== DEMO RÁPIDO QR ===\n";
        std::string qr = QRCodeGenerator::quickGenerate("Hello Coursera!");
        std::cout << qr << "\n";
    }

    inline void QRDemo::printHeader(const std::string& title) {
        setTextColor(ColorIndex::AZUL_MARCA, true);
        std::cout << "\n╔";
        for (size_t i = 0; i < title.length() + 2; ++i) std::cout << "═";
        std::cout << "╗\n";
        std::cout << "║ " << title << " ║\n";
        std::cout << "╚";
        for (size_t i = 0; i < title.length() + 2; ++i) std::cout << "═";
        std::cout << "╝\n";
        resetColor();
    }

    inline void QRDemo::printSeparator() {
        setTextColor(ColorIndex::TEXTO_SECUNDARIO);
        std::cout << "\n" << std::string(50, '-') << "\n";
        resetColor();
    }

} // namespace QR
} // namespace CourseraClone

#endif // COURSERACLONE_QR_QRDEMO_HPP
