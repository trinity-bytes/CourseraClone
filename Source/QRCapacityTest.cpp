// QR Code Capacity Testing Program
// Tests different data types and sizes to determine QR storage limits

#include <iostream>
#include <string>
#include <vector>
#include "Utils/QR/qrcodegen.hpp"

using namespace std;
using namespace qrcodegen;

void testCapacity(const string& dataType, const string& testData, QrCode::Ecc errorLevel) {
    cout << "\n=== Testing " << dataType << " ===\n";
    cout << "Error Correction: ";
    switch (errorLevel) {
        case QrCode::Ecc::LOW: cout << "LOW (~7% tolerance)"; break;
        case QrCode::Ecc::MEDIUM: cout << "MEDIUM (~15% tolerance)"; break;
        case QrCode::Ecc::QUARTILE: cout << "QUARTILE (~25% tolerance)"; break;
        case QrCode::Ecc::HIGH: cout << "HIGH (~30% tolerance)"; break;
    }
    cout << "\n";

    // Test different data lengths
    vector<int> testSizes = {10, 50, 100, 200, 500, 1000, 1500, 2000, 3000, 4000, 5000, 7000};
    
    for (int size : testSizes) {
        if (size > (int)testData.length()) continue;
        
        string data = testData.substr(0, size);
        
        try {
            QrCode qr = QrCode::encodeText(data.c_str(), errorLevel);
            cout << "Size " << size << " chars: SUCCESS (Version " << qr.getVersion() << ", " 
                 << qr.getSize() << "x" << qr.getSize() << " modules)\n";
        } catch (const exception& e) {
            cout << "Size " << size << " chars: FAILED - " << e.what() << "\n";
            break;
        }
    }
}

int qrCapacityMain() {
    cout << "=================================================\n";
    cout << "      QR CODE CAPACITY ANALYSIS TOOL\n";
    cout << "=================================================\n";
    
    // Generate test data
    string numericData = "";
    string alphanumericData = "";
    string binaryData = "";
    
    // Numeric data (0-9)
    for (int i = 0; i < 8000; i++) {
        numericData += to_string(i % 10);
    }
    
    // Alphanumeric data (0-9, A-Z, space, and some symbols)
    string alphaChars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ $%*+-./:";
    for (int i = 0; i < 8000; i++) {
        alphanumericData += alphaChars[i % alphaChars.length()];
    }
    
    // Binary data (any ASCII characters)
    for (int i = 0; i < 8000; i++) {
        binaryData += char(32 + (i % 95)); // Printable ASCII chars
    }
    
    cout << "\nQR Code Version Info:\n";
    cout << "- Version 1: 21x21 modules\n";
    cout << "- Version 40: 177x177 modules\n";
    cout << "- Each version increases size by 4 modules per side\n";
    
    // Test different error correction levels with numeric data
    cout << "\n" << string(50, '=') << "\n";
    cout << "NUMERIC DATA CAPACITY TESTS\n";
    cout << string(50, '=') << "\n";
    
    testCapacity("Numeric - LOW ECC", numericData, QrCode::Ecc::LOW);
    testCapacity("Numeric - MEDIUM ECC", numericData, QrCode::Ecc::MEDIUM);
    testCapacity("Numeric - HIGH ECC", numericData, QrCode::Ecc::HIGH);
    
    cout << "\n" << string(50, '=') << "\n";
    cout << "ALPHANUMERIC DATA CAPACITY TESTS\n";
    cout << string(50, '=') << "\n";
    
    testCapacity("Alphanumeric - LOW ECC", alphanumericData, QrCode::Ecc::LOW);
    testCapacity("Alphanumeric - MEDIUM ECC", alphanumericData, QrCode::Ecc::MEDIUM);
    
    cout << "\n" << string(50, '=') << "\n";
    cout << "BINARY DATA CAPACITY TESTS\n";
    cout << string(50, '=') << "\n";
    
    testCapacity("Binary - LOW ECC", binaryData, QrCode::Ecc::LOW);
    testCapacity("Binary - MEDIUM ECC", binaryData, QrCode::Ecc::MEDIUM);
    
    cout << "\n" << string(50, '=') << "\n";
    cout << "PRACTICAL RECOMMENDATIONS FOR COURSERA CLONE\n";
    cout << string(50, '=') << "\n";
    
    cout << "\nBased on the results above, here are practical recommendations:\n\n";
    
    cout << "1. STUDENT CERTIFICATE QR CODE:\n";
    cout << "   - Student ID (max 20 chars)\n";
    cout << "   - Course ID (max 20 chars)\n";
    cout << "   - Completion Date (10 chars)\n";
    cout << "   - Certificate Hash (32 chars)\n";
    cout << "   - Total: ~82 characters (very safe)\n\n";
    
    cout << "2. COURSE ENROLLMENT QR CODE:\n";
    cout << "   - Course ID (max 20 chars)\n";
    cout << "   - Instructor ID (max 20 chars)\n";
    cout << "   - Course URL (max 100 chars)\n";
    cout << "   - Total: ~140 characters (very safe)\n\n";
    
    cout << "3. PAYMENT RECEIPT QR CODE:\n";
    cout << "   - Transaction ID (max 32 chars)\n";
    cout << "   - Amount (max 10 chars)\n";
    cout << "   - Date (10 chars)\n";
    cout << "   - Student ID (max 20 chars)\n";
    cout << "   - Course ID (max 20 chars)\n";
    cout << "   - Total: ~92 characters (very safe)\n\n";
    
    cout << "4. LARGE DATA (JSON/XML):\n";
    cout << "   - Can store 1000+ characters easily\n";
    cout << "   - Perfect for detailed course info\n";
    cout << "   - Can include full student profiles\n\n";
    
    cout << "RECOMMENDATION: Use LOW error correction for maximum capacity,\n";
    cout << "unless the QR codes will be used in noisy environments.\n";
    
    return 0;
}
