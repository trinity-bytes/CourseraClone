// Archivo de prueba para QR autocontenidos
// Valida que la generación de datos completos para web funcione correctamente

#include <iostream>
#include <string>
#include "Utils/QR/AutocontainedQR.hpp"
#include "Utils/QR/QRCodeGenerator.hpp"

using namespace std;
using namespace CourseraClone::QR;

void testQRComprobante() {
    cout << "\n=== TEST QR COMPROBANTE AUTOCONTENIDO ===\n";
    
    // Crear datos de prueba
    RawComprobanteData comprobante;
    comprobante.id = 12345;
    comprobante.idEstudiante = 67890;
    comprobante.idActividad = 101;
    comprobante.tipoActividad = TipoActividad::CURSO;
    comprobante.fechaEmision = "2025-01-15";
    comprobante.montoPagado = 299.99;
    
    string nombreEstudiante = "Juan Carlos Perez Rodriguez";
    string nombreCurso = "Introducción a Python para Principiantes";
    
    // Generar JSON para QR
    string jsonQR = AutocontainedQR::generarQRComprobante(
        comprobante, 
        nombreEstudiante, 
        nombreCurso
    );
    
    cout << "JSON generado para QR:" << endl;
    cout << jsonQR << endl;
    cout << "\n" << AutocontainedQR::evaluarTamaño(jsonQR) << endl;
    
    // Generar QR visual
    QRConfig config;
    config.style = ASCIIStyle::BASIC;
    config.useColors = false;
    config.borderSize = 1;
    
    cout << "\nCódigo QR para Comprobante:" << endl;
    QRCodeGenerator generator(config);
    cout << generator.generateFromText(jsonQR) << endl;
}

void testQRCertificado() {
    cout << "\n=== TEST QR CERTIFICADO AUTOCONTENIDO ===\n";
    
    // Datos de prueba para certificado
    int idCertificado = 54321;
    string nombreEstudiante = "Maria Isabel Garcia Lopez";
    string nombreCurso = "Especialización en Data Science con R";
    string fechaFinalizacion = "2025-01-30";
    string calificacion = "Excelente";
    TipoActividad tipo = TipoActividad::ESPECIALIZACION;
    
    // Generar JSON para QR
    string jsonQR = AutocontainedQR::generarQRCertificado(
        idCertificado,
        nombreEstudiante,
        nombreCurso,
        fechaFinalizacion,
        calificacion,
        tipo
    );
    
    cout << "JSON generado para QR:" << endl;
    cout << jsonQR << endl;
    cout << "\n" << AutocontainedQR::evaluarTamaño(jsonQR) << endl;
    
    // Generar QR visual
    QRConfig config;
    config.style = ASCIIStyle::BASIC;
    config.useColors = false;
    config.borderSize = 1;
    
    cout << "\nCódigo QR para Certificado:" << endl;
    QRCodeGenerator generator(config);
    cout << generator.generateFromText(jsonQR) << endl;
}

void testCapacidadDatos() {
    cout << "\n=== TEST CAPACIDAD DE DATOS ===\n";
    
    // Probar con nombres muy largos
    string nombreLargo = "Estudiante con Nombre Extremadamente Largo Para Probar Limites";
    string cursoLargo = "Curso de Programación Avanzada en Múltiples Lenguajes y Tecnologías Modernas";
    
    RawComprobanteData comprobante;
    comprobante.id = 99999;
    comprobante.tipoActividad = TipoActividad::ESPECIALIZACION;
    comprobante.fechaEmision = "2025-12-31";
    comprobante.montoPagado = 9999.99;
    
    string jsonQR = AutocontainedQR::generarQRComprobante(
        comprobante,
        nombreLargo,
        cursoLargo
    );
    
    cout << "Prueba con nombres largos:" << endl;
    cout << jsonQR << endl;
    cout << AutocontainedQR::evaluarTamaño(jsonQR) << endl;
    
    // Probar certificado con datos largos
    string jsonCert = AutocontainedQR::generarQRCertificado(
        88888,
        nombreLargo,
        cursoLargo,
        "2025-12-31",
        "Sobresaliente",
        TipoActividad::ESPECIALIZACION
    );
    
    cout << "\nPrueba certificado con nombres largos:" << endl;
    cout << jsonCert << endl;
    cout << AutocontainedQR::evaluarTamaño(jsonCert) << endl;
}

int testAutocontainedQRMain() {
    cout << "==================================================\n";
    cout << "      PRUEBAS DE QR AUTOCONTENIDOS\n";
    cout << "==================================================\n";
    
    testQRComprobante();
    testQRCertificado();
    testCapacidadDatos();
    
    cout << "\n==================================================\n";
    cout << "RESUMEN:\n";
    cout << "✅ QR autocontenidos para mostrar en web\n";
    cout << "✅ Formato JSON legible y compacto\n";
    cout << "✅ Truncamiento automático para nombres largos\n";
    cout << "✅ Soporte para comprobantes y certificados\n";
    cout << "✅ Optimizado para proyectos académicos\n";
    cout << "==================================================\n";
    
    return 0;
}
