# Propuesta: Integración Web Services y Notificaciones para CourseraClone

## Resumen Ejecutivo

Esta propuesta presenta la integración de servicios web y un sistema de notificaciones nativas para mejorar significativamente la experiencia de usuario del proyecto CourseraClone, agregando funcionalidades modernas y profesionales sin comprometer el timeline de desarrollo.

## Componentes Propuestos

### 1. Web Services (GitHub Pages)

**Repositorio:** `WebServices-for-CourseraClone`  
**URL Base:** `https://[usuario].github.io/WebServices-for-CourseraClone`

#### 1.1 Términos y Condiciones (`/terms`)

- **Propósito:** Mostrar términos y condiciones simulados de la plataforma
- **Integración:** Durante el proceso de pago, el usuario puede acceder vía botón
- **Implementación:** Página HTML estática con diseño profesional

#### 1.2 Visualizador de Boletas (`/receipt`)

- **Propósito:** Mostrar boletas de pago generadas dinámicamente
- **Integración:**
  - Usuario selecciona boleta de la lista en la aplicación
  - Se genera código QR ASCII en consola con datos de la transacción
  - QR contiene URL con parámetros de la boleta
  - Usuario escanea QR → accede a boleta web → opción de descargar PDF
- **Datos transmitidos:** ID transacción, monto, fecha, curso, método de pago

#### 1.3 Generador de Certificados (`/certificate`)

- **Propósito:** Generar certificados digitales de finalización de cursos
- **Integración:**
  - Al completar un curso, se genera enlace único
  - Usuario presiona botón → abre navegador → certificado se genera automáticamente
  - Opción de descargar como PDF
- **Datos transmitidos:** Nombre estudiante, curso, fecha, ID único

### 2. Sistema de Notificaciones Nativas (Windows)

#### 2.1 Toast Notifications (Preferida)

- **Tecnología:** WinRT APIs / Windows Notification System
- **Ubicación:** Esquina inferior derecha (estilo Windows 10/11)
- **Características:** Soporte para iconos, botones de acción, sonidos

#### 2.2 Fallback: Ventanas Emergentes

- **Tecnología:** MessageBox personalizado
- **Uso:** Si Toast Notifications no están disponibles
- **Características:** Ventanas modales con diseño custom

#### 2.3 Casos de Uso

- Confirmación de inscripciones
- Notificación de nuevo contenido disponible
- Finalización de cursos
- Certificados listos para descargar
- Recordatorios de actividades pendientes

## Arquitectura Técnica

### Web Services

```
WebServices-for-CourseraClone/
├── index.html                 # Landing page
├── terms/index.html          # Términos y condiciones
├── receipt/index.html        # Visualizador de boletas
├── certificate/index.html    # Generador de certificados
├── assets/
│   ├── css/styles.css       # Estilos compartidos
│   ├── js/utils.js          # Funciones JavaScript
│   └── images/              # Logos e iconos
└── README.md                # Documentación
```

### Integración C++

```cpp
// Pseudo-estructura
namespace WebServices {
    class NotificationManager {
        static void showToast(string title, string message, NotificationType type);
        static void showFallbackDialog(string title, string message);
    };

    class URLGenerator {
        static string generateReceiptURL(ReceiptData data);
        static string generateCertificateURL(CertificateData data);
        static string getTermsURL();
    };

    class QRGenerator {
        static string generateASCIIQR(string data);
    };
}
```

## Ventajas de la Propuesta

### Técnicas

- **Escalabilidad:** Fácil agregar nuevos servicios web
- **Mantenibilidad:** Código centralizado y organizado
- **Compatibilidad:** Funciona en cualquier dispositivo con navegador
- **Rendimiento:** Servicios web estáticos (rápidos y eficientes)

### Experiencia de Usuario

- **Profesionalismo:** Experiencia similar a plataformas reales
- **Interactividad:** QR codes y notificaciones modernas
- **Accesibilidad:** URLs compartibles y archivables
- **Conveniencia:** Descarga de PDFs, notificaciones automáticas

### Desarrollo

- **Timeline Realista:** Implementación factible en tiempo disponible
- **Tecnologías Conocidas:** HTML/CSS/JS + C++ estándar
- **Sin Dependencias Externas:** No requiere servicios de terceros
- **Riesgo Bajo:** Fallbacks disponibles para cada funcionalidad

## Estimación de Desarrollo

| Componente                | Tiempo Estimado | Complejidad |
| ------------------------- | --------------- | ----------- |
| Términos y Condiciones    | 2-3 horas       | Baja        |
| Visualizador de Boletas   | 4-6 horas       | Media       |
| Generador de Certificados | 4-6 horas       | Media       |
| QR Generator (ASCII)      | 3-4 horas       | Media       |
| Sistema de Notificaciones | 5-7 horas       | Media-Alta  |
| Integración y Testing     | 3-4 horas       | Media       |
| **TOTAL**                 | **21-30 horas** | **Media**   |

## Consideraciones de Implementación

### Prioridades

1. **Alta:** Términos y Condiciones + Notificaciones básicas
2. **Media:** Visualizador de Boletas
3. **Baja:** Generador de Certificados (nice-to-have)

### Riesgos y Mitigaciones

- **Riesgo:** Complejidad de QR en ASCII
  - **Mitigación:** Usar librerías existentes de GitHub
- **Riesgo:** APIs de Windows para Toast
  - **Mitigación:** Fallback a MessageBox personalizado
- **Riesgo:** Timeline ajustado
  - **Mitigación:** Implementación por fases

## Conclusión

Esta propuesta eleva significativamente el nivel de profesionalismo del proyecto CourseraClone, agregando funcionalidades modernas y realistas que demuestran competencias técnicas avanzadas. La arquitectura propuesta es escalable, mantenible y factible dentro del timeline disponible.

La implementación por fases permite entregar valor incremental, con la opción de escalar funcionalidades según el tiempo disponible.

---

**Preparado por:** [Nombre]  
**Fecha:** 2 de Julio, 2025  
**Estado:** Propuesta para Revisión del Equipo
