# WebServices-for-Coursera - Especificaciones y Requerimientos

## 📋 Resumen Ejecutivo

**WebServices-for-Coursera** es una aplicación web diseñada con enfoque **mobile-first** para mostrar comprobantes de pago y certificados del sistema CourseraClone a través de enlaces QR. La aplicación está optimizada para dispositivos móviles, considerando que la mayoría del tráfico provendrá del escaneo de códigos QR desde smartphones.

---

## 🎯 Objetivos del Proyecto

### Objetivo Principal

Desarrollar una plataforma web responsiva que reciba datos a través de URLs (generadas por códigos QR) y muestre comprobantes de pago o certificados de forma atractiva, permitiendo guardarlos como PDF.

### Objetivos Específicos

1. **Visualización Elegante**: Mostrar comprobantes/certificados con diseño profesional
2. **Experiencia Mobile-First**: Optimizar para dispositivos móviles como prioridad
3. **Generación PDF**: Permitir descargar/guardar como PDF de alta calidad
4. **Accesibilidad Universal**: Funcionar sin instalación de aplicaciones
5. **Performance**: Carga rápida y navegación fluida

---

## 📱 Requerimientos Mobile-First

### Diseño Responsivo

- **Breakpoints principales**:
  - Mobile: 320px - 768px (prioridad máxima)
  - Tablet: 768px - 1024px
  - Desktop: 1024px+

### Optimización Móvil

- **Touch-friendly**: Botones mínimo 44px x 44px
- **Navegación con pulgar**: Elementos importantes en zona de fácil alcance
- **Carga rápida**: < 3 segundos en 3G
- **URLs amigables**: Recepción de datos a través de parámetros URL
- **PDF generation**: Generación y descarga de PDFs optimizados

---

## 🏗️ Arquitectura Técnica

### Stack Tecnológico Recomendado

#### Frontend

- **Framework**: React 18+ con Next.js 14+ (para SSR y SEO)
- **CSS Framework**: Tailwind CSS (mobile-first por defecto)
- **PDF Generation**: React-PDF o Puppeteer
- **Routing**: Next.js App Router para URLs dinámicas
- **UI Components**: Radix UI + shadcn/ui para componentes accesibles
- **PWA**: Service Workers para funcionalidad offline
- **CSS Framework**: Tailwind CSS (mobile-first por defecto)
- **QR Scanner**: `@zxing/library` o `qr-scanner`
- **Build Tool**: Vite o Next.js

#### Backend (Opcional - para análisis estadístico)

- **API**: Next.js API Routes (integrado)
- **Base de Datos**: No requerida (datos vienen por URL)
- **Hosting**: Vercel, Netlify, o Cloudflare Pages

### Arquitectura de Componentes

```
src/
├── app/
│   ├── receipt/
│   │   └── [data]/
│   │       └── page.tsx      # Página dinámica para recibos
│   ├── certificate/
│   │   └── [data]/
│   │       └── page.tsx      # Página dinámica para certificados
│   └── page.tsx              # Página principal/landing
├── components/
│   ├── ReceiptViewer/
│   ├── CertificateViewer/
│   ├── PDFGenerator/
│   └── Layout/
├── utils/
│   ├── urlParser.ts          # Parsea datos de URL
│   ├── pdfGenerator.ts       # Genera PDFs
│   └── dataFormatter.ts      # Formatea datos para display
└── styles/
    └── globals.css
```

---

## 🔧 Funcionalidades Core

### 1. Recepción de Datos por URL

**Descripción**: La aplicación recibe datos a través de parámetros en la URL generada por el código QR

**Formato de URL Esperado**:

```
https://coursera-receipts.vercel.app/receipt/[base64-encoded-json]
https://coursera-receipts.vercel.app/certificate/[base64-encoded-json]
```

**Ejemplo de datos en URL**:

```javascript
// Datos originales
const receiptData = {
  type: "receipt",
  id: "COMP-001",
  student: "Juan Pérez",
  course: "JavaScript Fundamentals",
  date: "2025-07-04",
  amount: 150.0,
  currency: "PEN",
  paymentMethod: "Tarjeta de Crédito",
  organization: "TechCorp Academy",
};

// Codificado en URL
const encodedData = btoa(JSON.stringify(receiptData));
const finalURL = `https://coursera-receipts.vercel.app/receipt/${encodedData}`;
```

**Requerimientos**:

- Decodificación automática de datos de URL
- Validación básica de estructura de datos
- Manejo de errores para URLs malformadas
- Redirección a página de error si faltan datos
  │ "Apunta la cámara │
  │ al código QR" │
  └─────────────────────┘

````

### 2. Visualización de Comprobantes/Certificados

**Descripción**: Muestra la información recibida por URL de forma elegante y profesional

**Requerimientos**:
- Diseño responsive optimizado para móviles
- Layout diferenciado para comprobantes vs certificados
- Información clara y bien estructurada
- Branding consistente con Coursera

**Estructura de Datos Esperada**:

```typescript
// Para comprobantes de pago
interface ReceiptData {
  type: "receipt";
  id: string;
  student: string;
  course: string;
  date: string;
  amount: number;
  currency: string;
  paymentMethod: string;
  organization: string;
  courseType?: "course" | "specialization";
}

// Para certificados
interface CertificateData {
  type: "certificate";
  id: string;
  student: string;
  course: string;
  completionDate: string;
  issueDate: string;
  organization: string;
  grade?: string;
  duration?: string;
}
````

**Validación Básica**:

```typescript
function validateReceiptData(data: any): data is ReceiptData {
  return (
    data &&
    data.type === "receipt" &&
    typeof data.id === "string" &&
    typeof data.student === "string" &&
    typeof data.course === "string" &&
    typeof data.amount === "number"
  );
}
```

### Validación de Integridad

````typescript
// Ejemplo de validación de checksum
function validateChecksum(data: any, providedChecksum: string): boolean {
  const dataString = JSON.stringify(data, Object.keys(data).sort());
  const calculatedHash = sha256(dataString + SECRET_SALT);
  return `sha256:${calculatedHash}` === providedChecksum;
}

### 3. Generación de PDF

**Descripción**: Permite al usuario descargar/guardar el comprobante o certificado como PDF

**Requerimientos**:
- Generación de PDF de alta calidad
- Diseño profesional para impresión
- Optimización para dispositivos móviles
- Descarga directa sin necesidad de backend

**Librerías Recomendadas**:
```typescript
// Opción 1: react-pdf (más control sobre diseño)
import { PDFDownloadLink, Document, Page, Text, View, StyleSheet } from '@react-pdf/renderer';

// Opción 2: html2canvas + jsPDF (más simple)
import html2canvas from 'html2canvas';
import jsPDF from 'jspdf';

// Opción 3: Puppeteer en servidor (mejor calidad)
// Para casos que requieran calidad de impresión superior
````

**UI Mobile-First para Comprobantes**:

```
┌─────────────────────┐
│ 🧾 COMPROBANTE     │
│                     │
│ Nº COMP-001         │
│ ───────────────     │
│ 📚 JavaScript       │
│    Fundamentals     │
│                     │
│ 👤 Juan Pérez       │
│                     │
│ 📅 04/07/2025       │
│                     │
│ 💰 S/ 150.00        │
│    Tarjeta Crédito  │
│                     │
│ 🏢 TechCorp Academy │
│                     │
│ [� Descargar PDF]  │
│ [� Compartir]      │
└─────────────────────┘
```

**UI Mobile-First para Certificados**:

```
┌─────────────────────┐
│ 🎓 CERTIFICADO     │
│                     │
│ Se certifica que    │
│                     │
│ 👤 JUAN PÉREZ       │
│                     │
│ ha completado       │
│ exitosamente el     │
│                     │
│ 📚 JavaScript       │
│    Fundamentals     │
│                     │
│ 📅 Completado:      │
│    04/07/2025       │
│                     │
│ 🏢 TechCorp Academy │
│                     │
│ [📄 Descargar PDF]  │
│ [📱 Compartir]      │
└─────────────────────┘
```

### 4. Manejo de Errores

**Requerimientos**:

- URLs malformadas o datos faltantes
- JSON inválido en parámetros URL
- Tipos de documentos no soportados
- Errores de generación de PDF

**UI de Error Mobile-First**:

```
┌─────────────────────┐
│ ❌ ERROR            │
│                     │
│ No se pudo cargar   │
│ el documento        │
│                     │
│ El enlace parece    │
│ estar dañado o      │
│ es inválido.        │
│                     │
│ [🔄 Reintentar]     │
│ [🏠 Ir al Inicio]   │
└─────────────────────┘
```

---

## 🎨 Implementación Técnica Simplificada

### Ejemplo de Página Receipt

```typescript
// app/receipt/[data]/page.tsx
import { PDFGenerator } from "@/components/PDFGenerator";
import { ReceiptViewer } from "@/components/ReceiptViewer";

interface PageProps {
  params: { data: string };
}

export default function ReceiptPage({ params }: PageProps) {
  try {
    // Decodificar datos de URL
    const jsonData = atob(params.data);
    const receiptData = JSON.parse(jsonData);

    // Validación básica
    if (!receiptData.type || receiptData.type !== "receipt") {
      throw new Error("Invalid receipt data");
    }

    return (
      <div className="min-h-screen bg-gray-50 py-8">
        <div className="container mx-auto px-4">
          <ReceiptViewer data={receiptData} />
          <PDFGenerator data={receiptData} type="receipt" />
        </div>
      </div>
    );
  } catch (error) {
    return <ErrorPage message="No se pudo cargar el comprobante" />;
  }
}
```

### Ejemplo de Componente PDF Generator

```typescript
// components/PDFGenerator.tsx
import { PDFDownloadLink } from "@react-pdf/renderer";
import { ReceiptPDF } from "./ReceiptPDF";

interface PDFGeneratorProps {
  data: any;
  type: "receipt" | "certificate";
}

export function PDFGenerator({ data, type }: PDFGeneratorProps) {
  const fileName = `${type}-${data.id || "document"}.pdf`;

  return (
    <div className="mt-6 space-y-3">
      <PDFDownloadLink
        document={<ReceiptPDF data={data} />}
        fileName={fileName}
        className="w-full bg-blue-600 text-white py-3 px-4 rounded-lg text-center block hover:bg-blue-700 transition-colors"
      >
        {({ loading }) =>
          loading ? "📄 Generando PDF..." : "📄 Descargar PDF"
        }
      </PDFDownloadLink>

      <button
        onClick={() => {
          if (navigator.share) {
            navigator.share({
              title: `${type === "receipt" ? "Comprobante" : "Certificado"} - ${
                data.course
              }`,
              url: window.location.href,
            });
          }
        }}
        className="w-full bg-gray-200 text-gray-800 py-3 px-4 rounded-lg hover:bg-gray-300 transition-colors"
      >
        📱 Compartir
      </button>
    </div>
  );
}
```

### Sistema de URLs Simplificado

```typescript
// utils/urlGenerator.ts (para el sistema C++)
export function generateReceiptURL(receiptData: any): string {
  const baseURL = "https://coursera-receipts.vercel.app";
  const encodedData = btoa(JSON.stringify(receiptData));
  return `${baseURL}/receipt/${encodedData}`;
}

export function generateCertificateURL(certificateData: any): string {
  const baseURL = "https://coursera-receipts.vercel.app";
  const encodedData = btoa(JSON.stringify(certificateData));
  return `${baseURL}/certificate/${encodedData}`;
}

// utils/urlParser.ts (para el sistema web)
export function parseDataFromURL(encodedData: string): any {
  try {
    const jsonString = atob(encodedData);
    return JSON.parse(jsonString);
  } catch (error) {
    throw new Error("Invalid URL data");
  }
}
```

---

## 🔗 Integración con Sistema C++ (CourseraClone)

### Generación de URLs para QR

El sistema C++ debe generar URLs que contengan los datos codificados en base64. Aquí está la implementación sugerida:

#### Ejemplo de implementación C++

```cpp
// Headers/Utils/URLGenerator.hpp
#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include "Base64Encoder.hpp"

class URLGenerator {
public:
    static std::string generateReceiptURL(const ComprobanteDePago& comprobante);
    static std::string generateCertificateURL(const Certificado& certificado);

private:
    static const std::string BASE_URL;
    static std::string encodeToBase64(const nlohmann::json& data);
};

// Implementation
const std::string URLGenerator::BASE_URL = "https://coursera-receipts.vercel.app";

std::string URLGenerator::generateReceiptURL(const ComprobanteDePago& comprobante) {
    nlohmann::json data = {
        {"type", "receipt"},
        {"id", comprobante.getId()},
        {"student", comprobante.getNombreEstudiante()},
        {"course", comprobante.getNombreCurso()},
        {"date", comprobante.getFechaEmision()},
        {"amount", comprobante.getMonto()},
        {"currency", "PEN"},
        {"paymentMethod", comprobante.getMetodoPago()},
        {"organization", comprobante.getNombreOrganizacion()},
        {"courseType", comprobante.getTipoCurso()}
    };

    std::string encodedData = encodeToBase64(data);
    return BASE_URL + "/receipt/" + encodedData;
}

std::string URLGenerator::generateCertificateURL(const Certificado& certificado) {
    nlohmann::json data = {
        {"type", "certificate"},
        {"id", certificado.getId()},
        {"student", certificado.getNombreEstudiante()},
        {"course", certificado.getNombreCurso()},
        {"completionDate", certificado.getFechaCompletado()},
        {"issueDate", certificado.getFechaEmision()},
        {"organization", certificado.getNombreOrganizacion()},
        {"grade", certificado.getCalificacion()},
        {"duration", certificado.getDuracionCurso()}
    };

    std::string encodedData = encodeToBase64(data);
    return BASE_URL + "/certificate/" + encodedData;
}

std::string URLGenerator::encodeToBase64(const nlohmann::json& data) {
    std::string jsonString = data.dump();
    return Base64Encoder::encode(jsonString);
}
```

#### Modificación en VerBoletasScreen.hpp

```cpp
// En el método _mostrarQRComprobante, reemplazar la generación QR actual:

void _mostrarQRComprobante(const ComprobanteDePago& comprobante) {
    _configurarConsolaParaQR();

    try {
        // Generar URL en lugar de JSON directo
        std::string url = URLGenerator::generateReceiptURL(comprobante);

        // Generar QR con la URL
        QRCode qr = generateQR(url);

        // Display del QR y datos (mantener lógica existente)
        // ...resto del código...

        // Mostrar también la URL para debug/testing
        gotoxy(2, qr.size + 15);
        setColor(ColorPalette::COURSERA_BLUE);
        std::cout << "URL: " << url.substr(0, 50) << "...";

    } catch (const std::exception& e) {
        // Manejo de errores...
    }

    _restaurarConsolaNormal();
}
```

#### Librerías requeridas

```cpp
// Añadir a las dependencias del proyecto:
// - nlohmann/json para serialización JSON
// - Base64 encoder (implementación custom o librería)

// Headers/Utils/Base64Encoder.hpp
#pragma once
#include <string>

class Base64Encoder {
public:
    static std::string encode(const std::string& input);
    static std::string decode(const std::string& input);

private:
    static const char encoding_table[];
    static const int mod_table[];
};
```

### Testing de URLs

Para testing, el sistema C++ puede generar URLs de prueba:

```cpp
// Para testing durante desarrollo
void testURLGeneration() {
    ComprobanteDePago testReceipt;
    testReceipt.setId("TEST-001");
    testReceipt.setNombreEstudiante("Juan Pérez");
    testReceipt.setNombreCurso("JavaScript Fundamentals");
    testReceipt.setMonto(150.00);

    std::string url = URLGenerator::generateReceiptURL(testReceipt);
    std::cout << "Test URL: " << url << std::endl;

    // También generar QR con esta URL para testing
    QRCode qr = generateQR(url);
    displayQR(qr);
}
```

---

## 🎨 Diseño y UX Mobile-First

### Paleta de Colores (Consistente con CourseraClone)

- **Primary**: #0056D3 (Azul Coursera)
- **Success**: #00C851 (Verde validación)
- **Error**: #FF4444 (Rojo error)
- **Warning**: #FFBB33 (Amarillo advertencia)
- **Background**: #F8F9FA (Gris claro)
- **Text**: #212529 (Gris oscuro)

### Tipografía Mobile-Optimized

- **Headings**: 18px-24px (legible en mobile)
- **Body**: 16px (mínimo recomendado para móviles)
- **Captions**: 14px
- **Font Family**: Sistema nativo (`-apple-system, BlinkMacSystemFont, 'Segoe UI'`)

### Componentes UI Key

#### Loading States

```jsx
<div className="loading-skeleton">
  <div className="animate-pulse">
    <div className="h-4 bg-gray-300 rounded"></div>
    <div className="h-4 bg-gray-300 rounded w-3/4"></div>
  </div>
</div>
```

#### Error Boundaries

```jsx
<ErrorBoundary fallback={<ErrorPage />}>
  <QRScanner />
</ErrorBoundary>
```

---

## 🔒 Seguridad y Validación

### Validación de Datos QR

1. **Estructura JSON**: Verificar campos obligatorios
2. **Tipos de datos**: Validar tipos y formatos
3. **Rangos válidos**: Fechas, montos, IDs
4. **Hash verificación**: Opcional para anti-falsificación

### Seguridad Frontend

- **CSP Headers**: Content Security Policy estricta
- **HTTPS Only**: Forzar conexiones seguras
- **Input Sanitization**: Limpiar datos de entrada
- **Rate Limiting**: Prevenir abuso del scanner

---

## 📱 Especificaciones de PWA (Progressive Web App)

### Manifest.json

```json
{
  "name": "Coursera QR Validator",
  "short_name": "CourseraQR",
  "description": "Validador de comprobantes Coursera mediante QR",
  "start_url": "/",
  "display": "standalone",
  "orientation": "portrait",
  "theme_color": "#0056D3",
  "background_color": "#FFFFFF",
  "icons": [
    {
      "src": "/icons/icon-72x72.png",
      "sizes": "72x72",
      "type": "image/png",
      "purpose": "maskable any"
    },
    {
      "src": "/icons/icon-96x96.png",
      "sizes": "96x96",
      "type": "image/png",
      "purpose": "maskable any"
    },
    {
      "src": "/icons/icon-128x128.png",
      "sizes": "128x128",
      "type": "image/png",
      "purpose": "maskable any"
    },
    {
      "src": "/icons/icon-144x144.png",
      "sizes": "144x144",
      "type": "image/png",
      "purpose": "maskable any"
    },
    {
      "src": "/icons/icon-152x152.png",
      "sizes": "152x152",
      "type": "image/png",
      "purpose": "maskable any"
    },
    {
      "src": "/icons/icon-192x192.png",
      "sizes": "192x192",
      "type": "image/png",
      "purpose": "maskable any"
    },
    {
      "src": "/icons/icon-384x384.png",
      "sizes": "384x384",
      "type": "image/png",
      "purpose": "maskable any"
    },
    {
      "src": "/icons/icon-512x512.png",
      "sizes": "512x512",
      "type": "image/png",
      "purpose": "maskable any"
    }
  ],
  "categories": ["education", "productivity", "utilities"],
  "screenshots": [
    {
      "src": "/screenshots/mobile-home.png",
      "sizes": "320x640",
      "type": "image/png",
      "form_factor": "narrow"
    },
    {
      "src": "/screenshots/tablet-home.png",
      "sizes": "768x1024",
      "type": "image/png",
      "form_factor": "wide"
    }
  ]
}
```

### Service Worker Strategy

```javascript
// sw.js - Cache Strategy
const CACHE_NAME = "coursera-qr-v1";
const STATIC_ASSETS = [
  "/",
  "/static/css/main.css",
  "/static/js/main.js",
  "/icons/icon-192x192.png",
  "/offline.html",
];

// Install Event
self.addEventListener("install", (event) => {
  event.waitUntil(
    caches.open(CACHE_NAME).then((cache) => cache.addAll(STATIC_ASSETS))
  );
});

// Fetch Event - Network First with Fallback
self.addEventListener("fetch", (event) => {
  if (event.request.destination === "document") {
    event.respondWith(
      fetch(event.request).catch(() => caches.match("/offline.html"))
    );
  } else {
    event.respondWith(
      caches
        .match(event.request)
        .then((response) => response || fetch(event.request))
    );
  }
});
```

### Performance Optimization

```javascript
// Lazy loading de QR scanner
const QRScanner = lazy(() => import("./components/QRScanner"));

// Preload crítico
const criticalResources = ["/api/validate", "/static/css/critical.css"];

// Intersection Observer para lazy images
const imageObserver = new IntersectionObserver((entries) => {
  entries.forEach((entry) => {
    if (entry.isIntersecting) {
      const img = entry.target;
      img.src = img.dataset.src;
      imageObserver.unobserve(img);
    }
  });
});
```

---

## 📞 Contacto y Mantenimiento

### Responsables

- **Frontend Lead**: [Nombre]
- **Mobile UX**: [Nombre]
- **DevOps**: [Nombre]

### Documentación Adicional

- API Documentation (cuando aplique)
- Component Storybook
- Testing Guidelines
- Performance Monitoring Setup

---

**Fecha de Creación**: 4 de Julio, 2025  
**Versión**: 1.0  
**Estado**: Especificaciones Iniciales  
**Próxima Revisión**: Al completar MVP

---

## 📋 Checklist de Implementación

### Pre-Development

- [ ] **Environment Setup**
  - [ ] Node.js 18+ instalado
  - [ ] Configurar repositorio Git
  - [ ] Setup de herramientas de desarrollo (ESLint, Prettier, TypeScript)
  - [ ] Configurar testing framework (Jest, React Testing Library, Playwright)

### Phase 1: Core Functionality (Semana 1-2)

- [ ] **Project Setup**

  - [ ] Inicializar proyecto React/Next.js con TypeScript
  - [ ] Configurar Tailwind CSS con breakpoints mobile-first
  - [ ] Setup de PWA básico con Vite/Next.js
  - [ ] Configurar estructura de carpetas

- [ ] **QR Scanner Implementation**

  - [ ] Integrar librería QR scanner (@zxing/library)
  - [ ] Implementar UI del scanner mobile-first
  - [ ] Manejar permisos de cámara
  - [ ] Implementar fallback de upload de imagen
  - [ ] Testing en diferentes dispositivos

- [ ] **QR Validation**
  - [ ] Implementar parser JSON del QR
  - [ ] Crear schema de validación con Zod
  - [ ] Implementar validación de checksum
  - [ ] Manejar errores de validación
  - [ ] Unit tests para validación

### Phase 2: User Experience (Semana 2-3)

- [ ] **Receipt Display**

  - [ ] Diseñar componente de visualización responsive
  - [ ] Implementar states de loading/error/success
  - [ ] Añadir animaciones suaves
  - [ ] Optimizar para lectura en móviles
  - [ ] Testing de usabilidad

- [ ] **Error Handling**

  - [ ] Implementar Error Boundaries
  - [ ] Crear mensajes de error user-friendly
  - [ ] Manejar casos edge (QR corrupto, permisos denegados)
  - [ ] Implementar retry mechanisms
  - [ ] Logging de errores

- [ ] **Performance Optimization**
  - [ ] Code splitting por rutas
  - [ ] Lazy loading de componentes pesados
  - [ ] Optimización de imágenes
  - [ ] Bundle size optimization
  - [ ] Lighthouse score > 90

### Phase 3: PWA Features (Semana 3-4)

- [ ] **Service Worker**

  - [ ] Implementar caching strategy
  - [ ] Offline functionality básica

### Phase 3: Deployment & Polish (Semana 2-3)

- [ ] **Production Setup**

  - [ ] Configurar hosting (Vercel recomendado)
  - [ ] Setup de dominio personalizado
  - [ ] Configurar variables de entorno
  - [ ] SSL y seguridad básica

- [ ] **Testing & QA**

  - [ ] Testing en dispositivos móviles reales
  - [ ] Verificar generación PDF en diferentes navegadores
  - [ ] Testing de URLs con diferentes tipos de datos
  - [ ] Performance testing (Lighthouse score > 90)
  - [ ] Accessibility testing básico

- [ ] **Optional Enhancements**
  - [ ] PWA básica (manifest.json)
  - [ ] Dark mode support
  - [ ] Analytics básicas
  - [ ] Error monitoring (Sentry)

### Post-Launch

- [ ] **Monitoring & Optimization**
  - [ ] Review de métricas de uso
  - [ ] Optimización basada en feedback
  - [ ] Maintenance y updates

---

## 🎯 Timeline Simplificado

**Total: 2-3 semanas**

- **Semana 1**: Setup + URL handling + Display básico
- **Semana 2**: PDF generation + UX polish + Testing
- **Semana 3**: Deployment + Testing final + Optimizaciones

  - [ ] Integrar error monitoring (Sentry)
  - [ ] Setup de analytics (Vercel Analytics/Google Analytics)
  - [ ] Performance monitoring
  - [ ] User behavior tracking

- [ ] **Documentation & Handoff**
  - [ ] Documentación de usuario final
  - [ ] Guía de mantenimiento
  - [ ] API documentation si aplica
  - [ ] Handoff a equipo de soporte

### Post-Launch

- [ ] **Monitoring & Optimization**

  - [ ] Review de métricas semanales
  - [ ] A/B testing para mejoras UX
  - [ ] Performance optimization continua
  - [ ] User feedback collection

- [ ] **Feature Enhancements**
  - [ ] Dashboard administrativo
  - [ ] Bulk validation features
  - [ ] Integration APIs
  - [ ] Multi-language support

---

## 🔧 Technical Configuration Examples

### Tailwind Config Mobile-First

```javascript
// tailwind.config.js
module.exports = {
  content: ["./src/**/*.{js,ts,jsx,tsx}"],
  theme: {
    screens: {
      sm: "640px",
      md: "768px",
      lg: "1024px",
      xl: "1280px",
      "2xl": "1536px",
    },
    extend: {
      colors: {
        coursera: {
          blue: "#0056D3",
          lightBlue: "#4285F4",
          success: "#00C851",
          error: "#FF4444",
          warning: "#FFBB33",
        },
      },
      fontFamily: {
        sans: ["-apple-system", "BlinkMacSystemFont", "Segoe UI", "Roboto"],
      },
      spacing: {
        "safe-top": "env(safe-area-inset-top)",
        "safe-bottom": "env(safe-area-inset-bottom)",
        "safe-left": "env(safe-area-inset-left)",
        "safe-right": "env(safe-area-inset-right)",
      },
    },
  },
  plugins: [
    require("@tailwindcss/forms"),
    require("@tailwindcss/aspect-ratio"),
  ],
};
```

### TypeScript Configurations

```json
// tsconfig.json
{
  "compilerOptions": {
    "target": "ES2020",
    "lib": ["DOM", "DOM.Iterable", "ES2020"],
    "allowJs": true,
    "skipLibCheck": true,
    "esModuleInterop": true,
    "allowSyntheticDefaultImports": true,
    "strict": true,
    "forceConsistentCasingInFileNames": true,
    "noFallthroughCasesInSwitch": true,
    "module": "ESNext",
    "moduleResolution": "node",
    "resolveJsonModule": true,
    "isolatedModules": true,
    "noEmit": true,
    "jsx": "react-jsx",
    "baseUrl": ".",
    "paths": {
      "@/*": ["./src/*"],
      "@/components/*": ["./src/components/*"],
      "@/utils/*": ["./src/utils/*"],
      "@/types/*": ["./src/types/*"]
    }
  },
  "include": ["src", "src/**/*"],
  "exclude": ["node_modules"]
}
```

### Package.json Scripts

```json
{
  "scripts": {
    "dev": "vite",
    "build": "tsc && vite build",
    "preview": "vite preview",
    "test": "vitest",
    "test:e2e": "playwright test",
    "test:coverage": "vitest --coverage",
    "lint": "eslint src --ext ts,tsx --report-unused-disable-directives --max-warnings 0",
    "lint:fix": "eslint src --ext ts,tsx --fix",
    "type-check": "tsc --noEmit",
    "build:analyze": "npm run build && npx vite-bundle-analyzer dist",
    "lighthouse": "lhci autorun"
  }
}
```

---

**Final Update**: 4 de Julio, 2025  
**Versión**: 2.0 - Comprehensive Mobile-First Specifications  
**Estado**: Ready for Development  
**Estimated Timeline**: 4-5 semanas para MVP completo
