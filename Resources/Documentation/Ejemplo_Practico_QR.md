/*
EJEMPLO PRÁCTICO DEL FORMATO JSON ESTÁNDAR
==========================================

Este archivo muestra un ejemplo real de cómo se genera el JSON y la URL final.

DATOS DE ENTRADA (C++):
======================
RawComprobanteData comprobante = {
    .id = 12345,
    .idEstudiante = 1001,
    .idActividad = 201,
    .tipoActividad = TipoActividad::CURSO,
    .fechaEmision = "2024-12-15",
    .montoPagado = 99.99
};

std::string nombreEstudiante = "Juan Pérez López";
std::string nombreCurso = "Introducción a Python";

JSON GENERADO (generarQRComprobanteEstandar):
============================================
{
  "t": "r",
  "i": 12345,
  "s": "Juan Pérez López",
  "c": "Introducción a Python",
  "d": "2024-12-15",
  "a": 99.99,
  "ct": "c"
}

BASE64 ENCODING:
===============
eyJ0IjoiciIsImkiOjEyMzQ1LCJzIjoiSnVhbiBQw6lyZXogTMOzcGV6IiwiYyI6IkludHJvZHVjY2nDs24gYSBQeXRob24iLCJkIjoiMjAyNC0xMi0xNSIsImEiOjk5Ljk5LCJjdCI6ImMifQ==

URL FINAL (generarURLEstandar):
==============================
https://trinity-bytes.github.io/WebServices-for-CourseraClone/v?d=eyJ0IjoiciIsImkiOjEyMzQ1LCJzIjoiSnVhbiBQw6lyZXogTMOzcGV6IiwiYyI6IkludHJvZHVjY2nDs24gYSBQeXRob24iLCJkIjoiMjAyNC0xMi0xNSIsImEiOjk5Ljk5LCJjdCI6ImMifQ==

VERIFICACIÓN JAVASCRIPT:
========================
Para verificar que el formato es correcto, puedes usar este código JavaScript:

```javascript
// La URL generada por C++
const qrURL = "https://trinity-bytes.github.io/WebServices-for-CourseraClone/v?d=eyJ0IjoiciIsImkiOjEyMzQ1LCJzIjoiSnVhbiBQw6lyZXogTMOzcGV6IiwiYyI6IkludHJvZHVjY2nDs24gYSBQeXRob24iLCJkIjoiMjAyNC0xMi0xNSIsImEiOjk5Ljk5LCJjdCI6ImMifQ==";

// Extraer el payload
const urlParams = new URLSearchParams(qrURL.split('?')[1]);
const payload = urlParams.get('d');

// Decodificar el JSON
const receiptData = JSON.parse(atob(payload));
console.log(receiptData);

// Resultado esperado:
// {
//   t: "r",
//   i: 12345,
//   s: "Juan Pérez López", 
//   c: "Introducción a Python",
//   d: "2024-12-15",
//   a: 99.99,
//   ct: "c"
// }
```

FLUJO COMPLETO:
==============
1. C++ genera JSON estándar con generarQRComprobanteEstandar()
2. C++ codifica JSON a Base64 con base64Encode()
3. C++ construye URL: BASE_URL + "/v?d=" + base64_payload
4. Usuario escanea QR con la URL
5. Web app extrae parámetro 'd' de la URL
6. Web app decodifica Base64 con atob()
7. Web app parsea JSON con JSON.parse()
8. Web app muestra boleta con todos los datos

COMPATIBILIDAD GARANTIZADA:
===========================
✓ Formato JSON idéntico al definido en especificación
✓ Base64 encoding compatible con atob() de JavaScript
✓ URL estructura exacta: /v?d={payload}
✓ Todos los campos obligatorios presentes
✓ Tipos de datos correctos (string/number)
*/