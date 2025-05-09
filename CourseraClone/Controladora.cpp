#include "Controladora.h"

// Incluir los headers necesarios para la implementación
#include "LandingPage_State.h"
#include "Login_State.h"
#include "States/DashboardEstudiante_State.h"
#include "States/DashboardOrganizacion_State.h"
#include "Managers/GestionadorUsuarios.h"
#include "Managers/GestionadorCursos.h"
#include "Usuario.h"
#include "Actividad.h"
#include <fstream>
#include <iostream>
#include <conio.h>
#include <stdexcept>

Controladora::Controladora() : usuarioActual(nullptr), ejecutando(true) {
    try {
        gestionadorUsuarios = std::make_unique<GestionadorUsuarios>();
        gestionadorCursos = std::make_unique<GestionadorCursos>();
        estadoActual = std::make_unique<LandingPageState>(this);
        cargarDatosArchivo();
        cargarDatosInscripciones();
    } catch (const std::exception& e) {
        std::cerr << "Error al inicializar la controladora: " << e.what() << std::endl;
        throw;
    }
}

Controladora::~Controladora() = default;

void Controladora::cargarDatosArchivo() {
    std::ifstream archivo("actividades.txt");
    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo de actividades");
    }

    std::string linea;
    while (getline(archivo, linea)) {
        actividades.push_back(Actividad(
            0,                  // id
            0,                  // idEmpresa
            "",                 // nombreEmpresa
            linea,             // titulo
            0,                  // cantidadAlumnos
            0,                  // tipo
            ""                 // descripcion
        ));
    }
    archivo.close();
}

void Controladora::cargarDatosInscripciones() {
    std::ifstream archivo("inscripciones.bin", std::ios::binary);
    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo de inscripciones");
    }

    try {
        InscripcionBinaria inscripcion;
        while (archivo.read(reinterpret_cast<char*>(&inscripcion), sizeof(InscripcionBinaria))) {
            int idx = inscripcion.idActividad - 1;
            if (idx >= 0 && idx < static_cast<int>(actividades.size())) {
                actividades[idx].aumentarAlumno(1);
            }
        }
        
        // Verificar si el error fue por EOF o por otro motivo
        if (!archivo.eof()) {
            throw std::runtime_error("Error al leer el archivo de inscripciones");
        }
    } catch (const std::exception& e) {
        archivo.close();
        throw std::runtime_error(std::string("Error al procesar inscripciones: ") + e.what());
    }
    
    archivo.close();
}

void Controladora::cambiarEstado(std::unique_ptr<MenuState> nuevoEstado) {
    if (!nuevoEstado) {
        throw std::invalid_argument("No se puede cambiar a un estado nulo");
    }
    estadoActual = std::move(nuevoEstado);
}

bool Controladora::iniciarSesion(const std::string& email, const std::string& password) {
    try {
        if (gestionadorUsuarios->autenticarUsuario(email, password)) {
            // Obtener el usuario actual del gestionador de usuarios después de la autenticación
            usuarioActual = gestionadorUsuarios->getUsuarioActual();
            
            // Login exitoso, cambiar al estado correspondiente según el tipo de usuario
            if (usuarioActual && usuarioActual->getTipoUsuario() == TipoUsuario::ESTUDIANTE) {
                cambiarEstado(std::make_unique<DashboardEstudianteState>(this));
            } else if (usuarioActual) {
                cambiarEstado(std::make_unique<DashboardOrganizacionState>(this));
            } else {
                // Error, no se pudo obtener el usuario
                std::cerr << "Error: Usuario autenticado pero no se pudo obtener la instancia" << std::endl;
                return false;
            }
            return true;
        }
        return false;
    } catch (const std::exception& e) {
        std::cerr << "Error durante el inicio de sesión: " << e.what() << std::endl;
        return false;
    }
}

bool Controladora::registrarUsuario(const std::string& nombre, const std::string& email, 
                                  const std::string& password, const std::string& tipo) {
    try {
        return gestionadorUsuarios->registrarUsuario(nombre, email, password, tipo);
    } catch (const std::exception& e) {
        std::cerr << "Error durante el registro: " << e.what() << std::endl;
        return false;
    }
}

void Controladora::cerrarSesion() {
    // Cerrar sesión en el gestionador de usuarios primero
    if (gestionadorUsuarios) {
        gestionadorUsuarios->cerrarSesion();
    }
    usuarioActual = nullptr;
    cambiarEstado(std::make_unique<LandingPageState>(this));
}

void Controladora::run() {
    while (ejecutando) {
        try {
            estadoActual->render();
            int tecla = _getch();
            if (tecla == 27) { // ESC
                ejecutando = false;
            } else {
                estadoActual->handleInput(tecla);
                auto siguienteEstado = estadoActual->getNextState();
                if (siguienteEstado) {
                    estadoActual = std::move(siguienteEstado);
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error durante la ejecución: " << e.what() << std::endl;
            // Opcional: cambiar a un estado de error o reiniciar
            ejecutando = false;
        }
    }
} 

LinkedList<Curso*> Controladora::getCursos()  { return gestionadorCursos->getCursos(); }
LinkedList<Especializacion*> Controladora::getEspecializaciones()  { return gestionadorCursos->getEspecializaciones(); }