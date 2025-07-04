// ═══════════════════════════════════════════════════════════════════════════════════
// QRTest.cpp
// Archivo de prueba para verificar que el generador QR funciona correctamente
// ═══════════════════════════════════════════════════════════════════════════════════

#include "Utils/QR/QRCodeGenerator.hpp"
#include "Utils/QR/QRDemo.hpp"
#include <iostream>

using namespace CourseraClone::QR;

/// @brief Función de prueba simple del generador QR
void testQRGenerator() {
    std::cout << "=== PRUEBA DEL GENERADOR QR ===\n\n";
    
    try {
        // Prueba básica
        std::cout << "1. Generación básica:\n";
        std::string basicQR = QRCodeGenerator::quickGenerate("Hello Coursera!");
        std::cout << basicQR << "\n";
        
        // Prueba con estilo Coursera
        std::cout << "2. Estilo Coursera:\n";
        std::string courseraQR = QRCodeGenerator::generateCourseraQR("Test QR Code");
        std::cout << courseraQR << "\n";
        
        // Prueba de comprobante
        std::cout << "3. QR de comprobante:\n";
        QRCodeGenerator generator;
        std::string comprobanteQR = generator.generateComprobanteQR(123, 456, 299.99);
        std::cout << comprobanteQR << "\n";
        
        std::cout << "✅ ¡Todas las pruebas exitosas!\n";
        
    } catch (const std::exception& e) {
        std::cout << "❌ Error en las pruebas: " << e.what() << "\n";
    }
}

/// @brief Función principal de prueba (renombrada para evitar conflictos)
int qrMain() {
    std::cout << "Iniciando pruebas del generador QR...\n\n";
    
    testQRGenerator();
    
    std::cout << "\n¿Desea ejecutar la demostración completa? (s/n): ";
    char response;
    std::cin >> response;
    
    if (response == 's' || response == 'S') {
        QRDemo::runFullDemo();
    }
    
    std::cout << "\nPresione Enter para continuar...";
    std::cin.ignore();
    std::cin.get();
    
    return 0;
}
