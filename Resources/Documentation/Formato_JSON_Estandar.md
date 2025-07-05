/*
FORMATO JSON ESTÁNDAR PARA QR - COURSERA CLONE
===============================================

Basado en la especificación técnica definida, el JSON generado tiene esta estructura exacta:

{
  "t": "r",
  "i": 12345,
  "s": "María José García Rodríguez",
  "c": "Desarrollo Full Stack con React y Node.js",
  "d": "2024-12-15",
  "a": 299.99,
  "ct": "c"
}

ESPECIFICACIÓN DE CAMPOS:
========================

Campo | Tipo    | Descripción                    | Valores Posibles           | Obligatorio
------|---------|--------------------------------|----------------------------|------------
t     | string  | Tipo de documento             | "r" = boleta, "c" = cert   | ✓
i     | number  | ID único de la boleta         | Cualquier entero positivo  | ✓
s     | string  | Nombre completo del estudiante | Texto libre (sin límite)   | ✓
c     | string  | Nombre completo del curso     | Texto libre (sin límite)   | ✓
d     | string  | Fecha de emisión              | Formato: "YYYY-MM-DD"      | ✓
a     | number  | Monto pagado                  | Decimal (ej: 299.99)       | ✓
ct    | string  | Tipo de contenido             | "c" = curso, "e" = esp     | ✓

FORMATO DE URL ESTÁNDAR:
=======================
https://trinity-bytes.github.io/WebServices-for-CourseraClone/v?d={base64_payload}

EJEMPLO DE IMPLEMENTACIÓN (JavaScript equivalente):
==================================================// Ejemplo de generación
const receiptData = {
  t: "r",
  i: 12345,
  s: "Juan Pérez López",
  c: "Introducción a Python",
  d: "2024-12-15",
  a: 99.99,
  ct: "c"
};

const payload = btoa(JSON.stringify(receiptData));
const qrURL = `https://trinity-bytes.github.io/WebServices-for-CourseraClone/v?d=${payload}`;
IMPLEMENTACIÓN EN C++ (CourseraClone):
=====================================// El método generarURLEstandar() produce exactamente la misma URL
std::string url = AutocontainedQR::generarURLEstandar(comprobante, nombreEstudiante, nombreCurso);

// Resultado: https://trinity-bytes.github.io/WebServices-for-CourseraClone/v?d=eyJ0IjovuLi...
VENTAJAS DEL FORMATO ESTÁNDAR:
=============================
✓ Nombres completos sin truncamiento para máxima claridad
✓ Formato de fecha estándar ISO (YYYY-MM-DD)
✓ Campos con nombres descriptivos pero compactos
✓ Compatibilidad total con sistemas web de verificación
✓ Fácil de parsear en cualquier lenguaje de programación
✓ Estructura consistente y predecible
✓ URL corta (/v?d=) para QR más pequeños
✓ Base64 encoding estándar (mismo que btoa en JavaScript)

IMPLEMENTACIÓN EN COURSERA CLONE:
===============================
- Método principal: generarQRComprobanteEstandar()
- URL generada: generarURLEstandar()
- Usado en: VerBoletasScreen para mostrar QR
- Base64 encoding para transmisión segura en URL
- Compatible con el sistema web de verificación
*/