#include "Controladora.h"

// Incluir los headers necesarios para la implementación
#include "LandingPage_State.h"
#include "Login_State.h"
#include "Managers/GestionadorUsuarios.h"
#include "Managers/GestionadorCursos.h"
#include "Usuario.h"
#include "Actividad.h"
#include <fstream>
#include <iostream>
#include <conio.h>

Controladora::Controladora() : usuarioActual(nullptr), ejecutando(true) {
    gestionadorUsuarios = std::make_unique<GestionadorUsuarios>();
    gestionadorCursos = std::make_unique<GestionadorCursos>();
    estadoActual = std::make_unique<LandingPageState>(this);
    cargarDatosArchivo();
    cargarDatosInscripciones();
}

Controladora::~Controladora() = default;

void Controladora::cargarDatosArchivo() {
    std::ifstream archivo("actividades.txt");
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir el archivo de actividades" << std::endl;
        return;
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
        std::cerr << "Error al abrir el archivo de inscripciones" << std::endl;
        return;
    }

    InscripcionBinaria inscripcion;
    auto procesarInscripcion = [&](const InscripcionBinaria& ins) {
        int idx = ins.idActividad - 1;
        if (idx >= 0 && idx < actividades.size())
            actividades[idx].aumentarAlumno(1);
    };

    std::function<void()> leerRecursivo = [&]() {
        InscripcionBinaria ins;
        if (archivo.read(reinterpret_cast<char*>(&ins), sizeof(ins))) {
            procesarInscripcion(ins);
            leerRecursivo();
        }
    };

    leerRecursivo();
    archivo.close();
}

void Controladora::cambiarEstado(std::unique_ptr<MenuState> nuevoEstado) {
    estadoActual = std::move(nuevoEstado);
}

bool Controladora::iniciarSesion(const std::string& email, const std::string& password) {
    //usuarioActual = gestionadorUsuarios->iniciarSesion(email, password);
    return usuarioActual != nullptr;
}

bool Controladora::registrarUsuario(const std::string& nombre, const std::string& email, 
                                  const std::string& password, const std::string& tipo) {
    //return gestionadorUsuarios->registrarUsuario(nombre, email, password, tipo);
    return false;
}

void Controladora::cerrarSesion() {
    usuarioActual = nullptr;
}

void Controladora::run() {
    while (ejecutando) {
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
    }
} 