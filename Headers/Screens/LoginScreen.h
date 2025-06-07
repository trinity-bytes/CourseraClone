#pragma once
#include "../Utils/Pantalla.h"
#include "../Entities/Estudiante.h"
#include "../Entities/Empresa.h"
#include "../Utils/ExtendedFunctions.h"
#include "../DataStructures/LinkedList.h"
#include "../Entities/Curso.h"
#include "../Entities/Especializacion.h"
#include "../Utils/UI_Ascii.h"
#include <string>

class Login : public PantallaBase {
private:
    // Constantes del menú
    static const int ELEMENTOS_INPUT = 2;
    static const int CANT_BOTONES = 3;

    string email;
    string password;
    TipoUsuario tipoUsuario;
    int campoActual;
    int campoAnterior;
    bool primeraRenderizacion;
    bool error;
    string mensajeError;
    int tipoUsuarioActual = 0; // 0: Estudiante, 1: Organización
    
    Estudiante& estudiante;
    Empresa& empresa;

    LinkedList<Curso*>& cursos;
    LinkedList<Especializacion*>& especialidades;

    // Coordenadas para dibujar
    COORD coordsElementosUserInput[ELEMENTOS_INPUT] = { {34, 15}, {34, 20} };
    COORD coordsBotones[CANT_BOTONES] = { {44, 25}, {62, 25}, {52, 29} };
	const string elementosUserinput[ELEMENTOS_INPUT] = { " ", " " };
    const string textosBotones[CANT_BOTONES] = { " Estudiante ", " Organizacion ", " Iniciar Sesión "};

    void mostrarCursor(bool mostrar) {
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        cursorInfo.bVisible = mostrar;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    }

    void renderizarCampo(const string& valor, int indice, bool seleccionado) 
    {
        gotoXY(coordsElementosUserInput[indice].X, coordsElementosUserInput[indice].Y);
    
        if (seleccionado) {
            SetConsoleColor(15, 4, true, true); 
            mostrarCursor(true);
        }
        else {
            SetConsoleColor(15, 0); 
            mostrarCursor(false);
        }

        SetConsoleColor(15, 1);
        cout << valor;
    }

    void renderizarBoton(const string& texto, int indice, bool seleccionado) 
    {
        gotoXY(coordsBotones[indice].X, coordsBotones[indice].Y);

        if (indice == 0 || indice == 1) {
            if (seleccionado || (indice == 0 && tipoUsuarioActual == 0) || (indice == 1 && tipoUsuarioActual == 1)) {
                SetConsoleColor(1, 4, true, true);
            } else {
                SetConsoleColor(7, 0);
            }
        } else {
            if (seleccionado) {
                SetConsoleColor(1, 5, true, true);
            } else {
                SetConsoleColor(5, 1, false, true);
            }
        }
        
        mostrarCursor(false);
        cout << texto;
        SetConsoleColor(15, 0);
    }

    void dibujarInterfazCompleta() {
        SetConsoleColor(15, 0);
        
        system("cls");
        
        UI_Login();

        for (int i = 3; i <= 7; i++) {
            gotoXY(3, i);
            SetConsoleColor(1, 13, true);
            cout << string(114, ' ');
        }

        SetConsoleColor(12, 13, true, true);
        gotoXY(42, 4);    cout << "▒█▀▀█ █▀▀█ █░░█ █▀▀█ █▀▀ █▀▀ █▀▀█ █▀▀█";
        gotoXY(42, 5);    cout << "▒█░░░ █░░█ █░░█ █▄▄▀ ▀▀█ █▀▀ █▄▄▀ █▄▄█";
        gotoXY(42, 6);    cout << "▒█▄▄█ ▀▀▀▀ ░▀▀▀ ▀░▀▀ ▀▀▀ ▀▀▀ ▀░▀▀ ▀░░▀";

        SetConsoleColor(12, 13, true, true);
        gotoXY(71, 7);    cout << "C L O N E";

        // Welcome message with soft highlight
        SetConsoleColor(8, 0, true);
        gotoXY(44, 9); cout << "- QUE BUENO TENERTE DE VUELTA! -";

        SetConsoleColor(15, 0);

        // Campos
        for (int i = 0; i < ELEMENTOS_INPUT; ++i) 
        {
            string valor = (i == 0) ? email : string(password.length(), '*');
            renderizarCampo(valor, i, campoActual == i);
        }

        // Botones
        for (int i = 0; i < CANT_BOTONES; ++i) 
        {
            renderizarBoton(textosBotones[i], i, campoActual == i + 2);
        }
                
        if (error) // Mensaje de error
        {
            gotoXY(ANCHO_CONSOLA / 2 - mensajeError.length() / 2, 11);
			SetConsoleColor(1, 3);
            cout << mensajeError;
            SetConsoleColor(15, 1);
        }

        gotoXY(34, 15);
    }

    void actualizarSeleccion() 
    {
        // Actualiza el campo/botón anterior como NO seleccionado
        if (campoAnterior >= 0 && campoAnterior < ELEMENTOS_INPUT) {
            string valorAnterior = (campoAnterior == 0) ? email : string(password.length(), '*');
            renderizarCampo(valorAnterior, campoAnterior, false);
        }
        // Actualiza el campo/botón actual como seleccionado
        if (campoActual >= 0 && campoActual < ELEMENTOS_INPUT) {
            string valorActual = (campoActual == 0) ? email : string(password.length(), '*');
            renderizarCampo(valorActual, campoActual, true);
        }
        
        // Actualiza selección de botones
        if (campoAnterior >= 2 || campoActual >= 2) {
            for (int i = 0; i < CANT_BOTONES; ++i) {
                renderizarBoton(textosBotones[i], i, campoActual == i + 2);
            }
        }
        campoAnterior = campoActual;
    }

public:
    Login() : campoActual(0), 
        campoAnterior(-1), 
        primeraRenderizacion(true), 
        error(false), 
        tipoUsuarioActual(0),
        estudiante(Estudiante()),
        empresa(Empresa()),
        cursos(LinkedList<Curso*>()),
        especialidades(LinkedList<Especializacion*>())
        {}

    Login(Estudiante& _estudiante, Empresa& _empresa,  LinkedList<Curso*>& _cursos, LinkedList<Especializacion*>& _especialidades) : campoActual(0),
        campoAnterior(-1),
        primeraRenderizacion(true),
        error(false),
        tipoUsuarioActual(0),
        estudiante(_estudiante),
        empresa(_empresa), 
        cursos(_cursos),
        especialidades(_especialidades)
        {
    }

    void clearState() {
        email.clear();
        password.clear();
        tipoUsuarioActual = 0;
        campoActual = 0;
        campoAnterior = -1;
        error = false;
        mensajeError.clear();
    }

    ResultadoPantalla ejecutar() override 
    {
        ResultadoPantalla res;

        while (true) 
        {
            if (primeraRenderizacion) 
            {
                dibujarInterfazCompleta();
				mostrarCursor(true);
                primeraRenderizacion = false;
            } else {
                actualizarSeleccion();
            }
            
            int tecla = _getch();
            switch (tecla) 
            {
                case 72: // Flecha arriba
                    if (campoActual > 0) campoActual--;
                    break;
                case 80: // Flecha abajo
                    if (campoActual < 4) campoActual++;
                    break;
                case 27: // ESC
                    res.accion = AccionPantalla::IR_A_LANDING_PAGE;
                    return res;
                case 13: // Enter
                    if (campoActual == 2) // Botón Estudiante
                    { 
                        tipoUsuarioActual = 0;
                        dibujarInterfazCompleta();
                    } 
                    else if (campoActual == 3) // Botón Organización
                    { 
                        tipoUsuarioActual = 1;
                        dibujarInterfazCompleta();
                    } 
                    else if (campoActual == 4) // Iniciar Sesión
                    { 
                        // Primero verificamos que los campos no estén vacíos
                        if (email.empty() || password.empty()) 
                        {
                            error = true;
                            //gotoXY();
                            mensajeError = "Todos los campos son obligatorios";
                            dibujarInterfazCompleta();
                            continue;
                        }

                        // Verificar credenciales localmente
                        Usuario usuarioTemp;
                        tipoUsuario = (tipoUsuarioActual == 0) ? TipoUsuario::ESTUDIANTE : TipoUsuario::EMPRESA;
                        int index = usuarioTemp.buscarIndexUsuario(email, tipoUsuario);

                        if (index == -1) {
                            // Usuario no encontrado
                            error = true;
                            mensajeError = "Usuario no encontrado";
                            dibujarInterfazCompleta();
                            continue;
                        }

                        LoginStatus status = usuarioTemp.login(usuarioTemp, tipoUsuario, password, index);

                        if (status == LoginStatus::SUCCESS) {
                            //cout << "HI";
                            //system("pause>0");

                            res.email = email;
                            res.password = password;
                            res.tipoUsuario = tipoUsuario;

                            if (tipoUsuario == TipoUsuario::ESTUDIANTE) {
                                estudiante.reset();
                                estudiante.setId(index);
                                estudiante.setNombre(usuarioTemp.getNombreCompleto());
                                estudiante.setUsername(email);
                                estudiante.setContrasena("");
                                estudiante.cargarInscripciones(cursos, especialidades);
                                estudiante.cargarDatos();
                                // throw runtime_error(to_string(estudiante.getInscripcionCursos().getTamano()));

                                empresa.reset();
                                res.accion = AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE;

                                /*
                                if (res.accionAnterior != AccionPantalla::NINGUNA) {
                                    res.accion = res.accionAnterior;
                                    res.idCursoSeleccionado = res.idCursoSeleccionado;
                                }
                                else {
                                    res.accion = AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE;
                                }
                                */
                            }
                            else {
                                empresa.reset();
                                empresa.setId(index);
                                empresa.setNombre(usuarioTemp.getNombreCompleto());
                                empresa.setUsername(email);
                                empresa.setContrasena("");
                                estudiante.reset();
                                // throw runtime_error("ldfkjlajf");
                                // Cuando se implemente el dashboard de organización:
                                res.accion = AccionPantalla::IR_A_DASHBOARD_ORGANIZACION;
                            }
                            clearState();
                            return res;
                        }
                        else {
                            // Contraseña incorrecta
                            error = true;
                            mensajeError = "Contraseña incorrecta";
                            dibujarInterfazCompleta();
                            continue;
                        }

                        /*
                         //ResultadoPantalla res;
                        res.email = email;
                        res.password = password;
                        res.tipoUsuario = (tipoUsuarioActual == 0) ? TipoUsuario::ESTUDIANTE : TipoUsuario::EMPRESA;

                        // Intentar autenticar al usuario
                        Usuario usuarioTemp;
                        int index = usuarioTemp.buscarIndexUsuario(email, res.tipoUsuario);
                        LoginStatus status = usuarioTemp.login(usuarioTemp, res.tipoUsuario, password, index);
                        //LoginStatus status = Usuario::login(usuarioTemp, res.tipoUsuario, email, password);

                        if (status == LoginStatus::SUCCESS) {
                            if (tipoUsuarioActual == 0) {
                                res.accion = AccionPantalla::IR_A_DASHBOARD_ESTUDIANTE;
                            }
                            else {
                                // res.accion = AccionPantalla::IR_A_DASHBOARD_ORGANIZACION; // Descomentar cuando esté implementado
                                res.accion = AccionPantalla::NINGUNA;
                            }
                            return res;
                        }
                        else {
                            error = true;
                            mensajeError = "Credenciales inválidas. Intente nuevamente.";
                            dibujarInterfazCompleta();
                            // Resetear campos y posicionar en el primero para volver a ingresar
                            email = "";
                            password = "";
                            tipoUsuarioActual = 0;
                            campoActual = 0;
                            campoAnterior = -1;
                            dibujarInterfazCompleta();
                            continue;
                        */
                    }
                    break;
                case 8: // Backspace
                    if (campoActual >= 0 && campoActual <= 1) {
                        string* campo = nullptr;
                        switch (campoActual) {
                            case 0: campo = &email; break;
                            case 1: campo = &password; break;
                        }
                        if (campo && !campo->empty()) {
                            campo->pop_back();
                            dibujarInterfazCompleta();
                        }
                    }
                    break;
                default:
                    if (tecla >= 32 && tecla <= 126) { // Caracteres imprimibles
                        string* campo = nullptr;
                        switch (campoActual) {
                            case 0: campo = &email; break;
                            case 1: campo = &password; break;
                        }
                        if (campo) {
                            campo->push_back(static_cast<char>(tecla));
                            dibujarInterfazCompleta();
                        }
                    }
                    break;
            }
            error = false;
        }
    }

/*
private:
    bool validarCampos() {
        Usuario temp;
        if (email.empty() || password.empty()) {
            error = true;
            mensajeError = "Todos los campos son obligatorios";
            return false;
        }
        int index = temp.buscarIndexUsuario(email, tipoUsuario);
        if (index == -1) {
            error = true;
            mensajeError = "Usuario no encontrado";
            return false;
        }
        else {
            LoginStatus res = temp.login(temp, tipoUsuario, password, index);
            if (res == LoginStatus::SUCCESS) return true;
        }

        return false;
    }
*/
};
