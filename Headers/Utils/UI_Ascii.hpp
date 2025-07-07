// filepath: Headers/Utils/UI_Ascii.hpp
// Descripción: Elementos ASCII para interfaces de usuario

#ifndef COURSERACLONE_UTILS_UI_ASCII_HPP
#define COURSERACLONE_UTILS_UI_ASCII_HPP

#include <iostream>
#include <string>
#include "SystemUtils.hpp"

/*
┌──┬─────┐    ╔══╦══╗
│  │     │    ║  ║  ║
├──┼─────┤    ╠══╬══╣
│  │     │    ║  ║  ║
└──┴─────┘    ╚══╩══╝
*/

// UI Landing Page
inline void UI_LandingPage() 
{
//----------------------------------------------------------------------------------------------------------------------
    std::string ui = R"(
   █▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█  |  C L O N E                         INICIAR SESION   REGISTRARSE   SOBRE NOSOTROS   
   █▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█                                        


                    "E L  S I G U I E N T E  N I V E L  D E  T U  C A R R E R A  E S T Á  A Q U Í                      
                      -  Especialízate en las áreas con más demanda laboral y da el gran salto.  -
          
                                 EXPLORAR CURSOS Y ESPECIALIDADES      REVISAR OFERTAS 
 

      -----------------------------------<<    LAS MEJORES ESPECIALIDADES    >>-----------------------------------  
       ╔════════════════════════════════╗  ╔════════════════════════════════╗  ╔════════════════════════════════╗
       ║                                ║  ║                                ║  ║                                ║
       ╠════════════════════════════════╣  ╠════════════════════════════════╣  ╠════════════════════════════════╣
       ║                                ║  ║                                ║  ║                                ║
       ║                                ║  ║                                ║  ║                                ║
       ║                                ║  ║                                ║  ║                                ║
       ╚════════════════════════════════╝  ╚════════════════════════════════╝  ╚════════════════════════════════╝

      ----------------------------------------<<    CURSOS POPULARES    >>----------------------------------------  
       ╔════════════════════════════════╗  ╔════════════════════════════════╗  ╔════════════════════════════════╗
       ║                                ║  ║                                ║  ║                                ║
       ╠════════════════════════════════╣  ╠════════════════════════════════╣  ╠════════════════════════════════╣
       ║                                ║  ║                                ║  ║                                ║
       ║                                ║  ║                                ║  ║                                ║
       ║                                ║  ║                                ║  ║                                ║
       ╚════════════════════════════════╝  ╚════════════════════════════════╝  ╚════════════════════════════════╝

────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de dirección (ARRIBA, ABAJO, IZQUIERDA, DERECHA) para navegar por el menú.
 Pulsa la tecla ENTER para seleccionar y ESC para SALIR DEL PROGRAMA.)";
//----------------------------------------------------------------------------------------------------------------------

    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
	std::cout << ui;

    /// @brief Dibujar fondo de la cabecera
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::BLANCO_PURO);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    /// @brief Dibujar linea inferior de los botones
    gotoXY(72, 2); std::cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯¯   ¯¯¯¯¯¯¯¯¯¯¯   ¯¯¯¯¯¯¯¯¯¯¯¯¯¯";

    /// @brief/ Dibujar logo principal
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::BLANCO_PURO);
    gotoXY(3, 1);  std::cout << "█▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█";
    gotoXY(3, 2);  std::cout << "█▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█";
    gotoXY(35, 1); std::cout << "│  C L O N E";

    /// @brief Dibujar fondo del hero-section
     setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    for (int y = 4; y < 10; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

	/// @brief Mostrar slogan y sugbtitulo en hero section
	gotoXY(22, 5); std::cout << "E L  S I G U I E N T E  N I V E L  D E  T U  C A R R E R A  E S T Á  A Q U Í";
	gotoXY(22, 6); std::cout << "-  Especialízate en las áreas con más demanda laboral y da el gran salto.  -";

	resetColor();
}

/// UI Login
inline void UI_Login()
{
//----------------------------------------------------------------------------------------------------------------------
	std::string ui = R"(

                                         ▒█▀▀█ █▀▀█ █░░█ █▀▀█ █▀▀ █▀▀ █▀▀█ █▀▀█                                      
                                         ▒█░░░ █░░█ █░░█ █▄▄▀ ▀▀█ █▀▀ █▄▄▀ █▄▄█                                      
                                         ▒█▄▄█ ▀▀▀▀ ░▀▀▀ ▀░▀▀ ▀▀▀ ▀▀▀ ▀░▀▀ ▀░░▀                                      
                                                        C L O N E                                                    
                                                                                                                     
                                            - QUE BUENO TENERTE DE VUELTA! -                                         
                                                                                                                     
                                                                                                                     
                                                                                                                     
                                 Email:                                                                              
                                 ┌────────────────────────────────────────────────────┐                              
                                 │                                                    │                              
                                 └────────────────────────────────────────────────────┘                              
                                                                                                                     
                                 Contrasena:                                                                         
                                 ┌────────────────────────────────────────────────────┐                              
                                 │                                                    │                              
                                 └────────────────────────────────────────────────────┘                              
                                                                                                                     
                                 Que tipo de usuario eres?:                                                          
                                                                                                                     
                                             ESTUDIANTE        ORGANIZACION                                          
                                                                                                                     
                                                                                                                     
                                                     INICIAR SESION                                                  
                                                     ¯¯¯¯¯¯¯¯¯¯¯¯¯¯                                                  
                                                                                                                     
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de dirección (ARRIBA Y ABAJO) para navegar por el menú.
 Pulsa la tecla ENTER para seleccionar una opción y ESC para regresar al menú anterior.)";
//----------------------------------------------------------------------------------------------------------------------

    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
	std::cout << ui;

    /// @brief Dibujar fondo de la cabecera
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    for (int y = 0; y < 10; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    gotoXY(45, 7);  std::cout << "- QUE BUENO TENERTE DE VUELTA! -";

    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_AZUL_SUAVE);
    gotoXY(42, 2);  std::cout << "▒█▀▀█ █▀▀█ █░░█ █▀▀█ █▀▀ █▀▀ █▀▀█ █▀▀█";
    gotoXY(42, 3);  std::cout << "▒█░░░ █░░█ █░░█ █▄▄▀ ▀▀█ █▀▀ █▄▄▀ █▄▄█";
    gotoXY(42, 4);  std::cout << "▒█▄▄█ ▀▀▀▀ ░▀▀▀ ▀░▀▀ ▀▀▀ ▀▀▀ ▀░▀▀ ▀░░▀";

    gotoXY(57, 5);  std::cout << "C L O N E";

    resetColor();
}

/// UI Singup
inline void UI_Signup()
{
//----------------------------------------------------------------------------------------------------------------------
	std::string ui = R"(
                                         ▒█▀▀█ █▀▀█ █░░█ █▀▀█ █▀▀ █▀▀ █▀▀█ █▀▀█                                         
                                         ▒█░░░ █░░█ █░░█ █▄▄▀ ▀▀█ █▀▀ █▄▄▀ █▄▄█                                     
                                         ▒█▄▄█ ▀▀▀▀ ░▀▀▀ ▀░▀▀ ▀▀▀ ▀▀▀ ▀░▀▀ ▀░░▀                                     
                                                        C L O N E                                                   
                                                                                        
   
                         Nombres y apellidos (O nombre de la empresa):
                         ┌──────────────────────────────────────────────────────────────────┐  
                         │                                                                  │
                         └──────────────────────────────────────────────────────────────────┘ 
                         Email:
                         ┌──────────────────────────────────────────────────────────────────┐
                         │                                                                  │
                         └──────────────────────────────────────────────────────────────────┘
                         Contraseña:
                         ┌──────────────────────────────────────────────────────────────────┐
                         │                                                                  │
                         └──────────────────────────────────────────────────────────────────┘
                         Vuelva a ingresar su contraseña:
                         ┌──────────────────────────────────────────────────────────────────┐
                         │                                                                  │
                         └──────────────────────────────────────────────────────────────────┘

                         Que tipo de usuario seras?:   UN ESTUDIANTE   UNA ORGANIZACION 


                                                      CREAR CUENTA                                                  
                                                      ¯¯¯¯¯¯¯¯¯¯¯¯                                                  
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de dirección (ARRIBA Y ABAJO) para moverte por el menú.
 Pulsa la tecla ENTER para seleccionar un botón y ESC para regresar al menú anterior.)";
//----------------------------------------------------------------------------------------------------------------------

    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
	std::cout << ui;

    /// @brief Dibujar fondo de la cabecera
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    for (int y = 0; y < 6; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_AZUL_SUAVE);
    gotoXY(42, 1);  std::cout << "▒█▀▀█ █▀▀█ █░░█ █▀▀█ █▀▀ █▀▀ █▀▀█ █▀▀█";
    gotoXY(42, 2);  std::cout << "▒█░░░ █░░█ █░░█ █▄▄▀ ▀▀█ █▀▀ █▄▄▀ █▄▄█";
    gotoXY(42, 3);  std::cout << "▒█▄▄█ ▀▀▀▀ ░▀▀▀ ▀░▀▀ ▀▀▀ ▀▀▀ ▀░▀▀ ▀░░▀";

    gotoXY(57, 4);  std::cout << "C L O N E";
}

/// UI Dashboard for student
inline void UI_StudentDashboard()
{
//----------------------------------------------------------------------------------------------------------------------
    std::string ui = R"(
   █▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█  |  C L O N E                                          VER MI PERFIL  CERRAR SESION   
   █▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█                                                        ¯¯¯¯¯¯¯¯¯¯¯¯¯  ¯¯¯¯¯¯¯¯¯¯¯¯¯
                                                                                                                     

            Te damos la bienvenida   
            RECUERDA: 
                                                                                                                    
                                 EXPLORAR CURSOS Y ESPECIALIDADES      REVISAR OFERTAS                                 
       
                                                                                                                     
       MIS CURSOS: [ VER TODOS ]
       ╔════════════════════════════════╗  ╔════════════════════════════════╗  ╔════════════════════════════════╗
       ║                                ║  ║                                ║  ║                                ║
       ╠════════════════════════════════╣  ╠════════════════════════════════╣  ╠════════════════════════════════╣
       ║                                ║  ║                                ║  ║                                ║
       ║                                ║  ║                                ║  ║                                ║
       ║                                ║  ║                                ║  ║                                ║
       ╚════════════════════════════════╝  ╚════════════════════════════════╝  ╚════════════════════════════════╝

       MIS ESPECIALIZACIONES [ VER TODAS ]
       ╔════════════════════════════════╗  ╔════════════════════════════════╗  ╔════════════════════════════════╗
       ║                                ║  ║                                ║  ║                                ║
       ╠════════════════════════════════╣  ╠════════════════════════════════╣  ╠════════════════════════════════╣
       ║                                ║  ║                                ║  ║                                ║
       ║                                ║  ║                                ║  ║                                ║
       ║                                ║  ║                                ║  ║                                ║
       ╚════════════════════════════════╝  ╚════════════════════════════════╝  ╚════════════════════════════════╝
                                                                                                                     
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de dirección (ARRIBA, ABAJO, IZQUIERDA, DERECHA) para moverte por el menú.
 Pulsa la tecla ENTER para seleccionar y ESC para regresar al menú anterior.)";
//----------------------------------------------------------------------------------------------------------------------

    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << ui;

    /// @brief Dibujar fondo de la cabecera
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::BLANCO_PURO);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    /// @brief Dibujar linea inferior de los botones
    gotoXY(89, 2); std::cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯  ¯¯¯¯¯¯¯¯¯¯¯¯¯";

    /// @brief/ Dibujar logo principal
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::BLANCO_PURO);
    gotoXY(3, 1);  std::cout << "█▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█";
    gotoXY(3, 2);  std::cout << "█▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█";
    gotoXY(35, 1); std::cout << "│  C L O N E";

    /// @brief Dibujar fondo del hero-section
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    for (int y = 4; y < 10; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

	resetColor();
}

/// UI Vista de listar contenido creado por la organización
inline void UI_ListarMisInscripciones()
{
//----------------------------------------------------------------------------------------------------------------------
    std::string ui = R"(
   █▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█  |  C L O N E       
   █▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█                 
   

                                     MIS INSCRIPCIONES - CURSOS Y ESPECIALIDADES                                    


        ID │ NOMBRE                                     │ TIPO              │ COMLETADO        │ PAGADO     
       ────┼────────────────────────────────────────────┼───────────────────┼──────────────────┼──────────────
           │                                            │                   │                  │           
           │                                            │                   │                  │            
           │                                            │                   │                  │            
           │                                            │                   │                  │            
           │                                            │                   │                  │            
           │                                            │                   │                  │            
           │                                            │                   │                  │            
           │                                            │                   │                  │            
           │                                            │                   │                  │           
           │                                            │                   │                  │            
           │                                            │                   │                  │            
           │                                            │                   │                  │            
           │                                            │                   │                  │           
           │                                            │                   │                  │           
           │                                            │                   │                  │            
           │                                            │                   │                  │            


                                        < ANTERIOR     [1/5]     SIGUIENTE >        

────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 ARRIBA/ABAJO: Navegar, IZQUIERDA/DERECHA: Cambiar página, ENTER: Detalles,  ESC: Regresar)";  
  
//----------------------------------------------------------------------------------------------------------------------

    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << ui;

    /// @brief Dibujar fondo de la cabecera
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::BLANCO_PURO);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    /// @brief Dibujar fondo de la sección de título
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    for (int y = 4; y < 7; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    /// @brief Mostrar título de la sección
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    gotoXY(45, 5); std::cout << "MIS INSCRIPCIONES - CURSOS Y ESPECIALIDADES";

    /// @brief Dibujar logo principal
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::BLANCO_PURO);
    gotoXY(3, 1);  std::cout << "█▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█";
    gotoXY(3, 2);  std::cout << "█▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█";
    gotoXY(35, 1); std::cout << "│  C L O N E";

    resetColor();
}

/// UI Dashboard for organization
inline void UI_OrganizationDashboard()
{
//----------------------------------------------------------------------------------------------------------------------
    std::string ui = R"(
   █▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█  |  C L O N E                                         VER MI PERFIL   CERRAR SESION
   █▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█                                                       ¯¯¯¯¯¯¯¯¯¯¯¯¯   ¯¯¯¯¯¯¯¯¯¯¯¯¯
                                                                                                                     
          ┌───────────────────────────┬───────────────────────────────────┬──────────────────────────────────┐
          │ Cursos publicados:        │ Especialidades publicadas:        │ Estudiantes inscritos:           │
          └───────────────────────────┴───────────────────────────────────┴──────────────────────────────────┘
                                                                                                                
          EXPLORAR CURSOS Y ESPECIALIDADES      GESTIONAR MI CONTENIDO      VER ESTADISTICAS      CREAR OFERTA          

                                                                                                            
       MIS CURSOS: [ VER TODOS ]
       ╔════════════════════════════════╗  ╔════════════════════════════════╗  ╔════════════════════════════════╗
       ║                                ║  ║                                ║  ║                                ║
       ╠════════════════════════════════╣  ╠════════════════════════════════╣  ╠════════════════════════════════╣
       ║                                ║  ║                                ║  ║                                ║
       ║                                ║  ║                                ║  ║                                ║
       ║                                ║  ║                                ║  ║                                ║
       ╚════════════════════════════════╝  ╚════════════════════════════════╝  ╚════════════════════════════════╝

       MIS ESPECIALIZACIONES [ VER TODAS ]
       ╔════════════════════════════════╗  ╔════════════════════════════════╗  ╔════════════════════════════════╗ 
       ║                                ║  ║                                ║  ║                                ║
       ╠════════════════════════════════╣  ╠════════════════════════════════╣  ╠════════════════════════════════╣
       ║                                ║  ║                                ║  ║                                ║
       ║                                ║  ║                                ║  ║                                ║
       ║                                ║  ║                                ║  ║                                ║
       ╚════════════════════════════════╝  ╚════════════════════════════════╝  ╚════════════════════════════════╝
                                                                                                                     
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de dirección (ARRIBA, ABAJO, IZQUIERDA, DERECHA) para moverte por el menú.
 Pulsa la tecla ENTER para seleccionar y ESC para regresar al menú anterior.)";
//----------------------------------------------------------------------------------------------------------------------

    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << ui;

    /// @brief Dibujar fondo de la cabecera
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::BLANCO_PURO);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    /// @brief Dibujar linea inferior de los botones
    gotoXY(88, 2); std::cout << "¯¯¯¯¯¯¯¯¯¯¯¯¯   ¯¯¯¯¯¯¯¯¯¯¯¯¯";

    /// @brief/ Dibujar logo principal
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::BLANCO_PURO);
    gotoXY(3, 1);  std::cout << "█▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█";
    gotoXY(3, 2);  std::cout << "█▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█";
    gotoXY(35, 1); std::cout << "│  C L O N E";

    /// @brief Dibujar fondo del menú superior
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    for (int y = 4; y < 10; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

	gotoXY(10, 4);  std::cout << "┌───────────────────────────┬───────────────────────────────────┬──────────────────────────────────┐";
	gotoXY(10, 5);  std::cout << "│ Cursos publicados:        │ Especialidades publicadas:        │ Estudiantes inscritos:           │";
	gotoXY(10, 6);  std::cout << "└───────────────────────────┴───────────────────────────────────┴──────────────────────────────────┘";

	resetColor();
}

/// UI User Profile View
inline void UI_UserProfile()
{
//----------------------------------------------------------------------------------------------------------------------
    std::string ui = R"(     /   __/     /   __/     /   __/     /   __/     /   __/     /   __/     /   __/     /   __/     /   __/     /   __/
__   \__/  \__   \__/  \__   \__/  \__   \__/  \__   \__/  \__   \__/  \__   \__/  \__   \__/  \__   \__/  \__   \__/  \
  \__/  \     \__/  \     \__/  \     \__/  \     \__/  \     \__/  \     \__/  \     \__/  \     \__/  \     \__/  \   
__/     /   __/     / ┌───────────────┐     /   __/     /   __/     /   __/     /   __/     /   __/     /   __/     /   
  \__   \__/  \__   \_│    .+++++.    │__   \__/  \__   \__/  \__   \__/  \__   \__/  \__   \__/  \__   \__/  \__   \__/
     \__/  \     \__/ │   | ~~~~~ |   │  \__/  \     \__/  \     \__/  \     \__/  \     \__/  \     \__/  \     \__/   
   __/     /   __/    │   ) '*_*' (   │__/     /   __/     /   __/     /   __/     /   __/     /   __/     /   __/     /
__/  \__   \__/  \__  │   (  ._.  )   │  \__   \__/  \__   \__/  \__   \__/  \__   \__/  \__   \__/  \__   \__/  \__   \
──────────────────────┤    '.._..'    ├─────────────────────────────────────────────────────────────────────────────────
                      │  _,/\   /\,_  │                                                                           
                      │ /    ':'    \ │           MIS CERTIFICADOS    MIS BOLETAS    EDITAR PERFIL   
                      └───────────────┘           ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯    ¯¯¯¯¯¯¯¯¯¯¯    ¯¯¯¯¯¯¯¯¯¯¯¯¯
                                                                                                                     
                                                                                                                     
                      ID:                                                                                            
                                                                                                                     
                      ────────────────────────────────────────────────────────────────────────────                   
                                                                                                                     
                      ESTUDIANTE:                                                                                    
                                                                                                                    
                      ────────────────────────────────────────────────────────────────────────────                   
                                                                                                                     
                      CORREO:                                                                                        
                                                                                                                     
                      ────────────────────────────────────────────────────────────────────────────                   
                                                                                                                     
                      Estudia en Coursera desde: --/--/----                                                          
                                                                                                                     
                                                                                                                     
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de dirección (IZQUIERDA, DERECHA) para moverte por el menú.
 Pulsa la tecla ENTER para seleccionar y ESC para regresar al menú anterior.)";
//----------------------------------------------------------------------------------------------------------------------

    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << ui;

    resetColor();
}

/// UI Organization Profile View
inline void UI_OrganizationProfile()
{
//----------------------------------------------------------------------------------------------------------------------
    std::string ui = R"( / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/
/ /  \ \____/ /  \ \____/ /  \ \____/ /  \ \____/ /  \ \____/ /  \ \____/ /  \ \____/ /  \ \____/ /  \ \____/ /  \ \____
\ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ 
 \____/ /  \ \____/ /  \ \____/ /  \ \____/ /  \ \____/ /  \ \____/ /  \ \____/ /  \ \____/ /  \ \____/ /  \ \____/ /  \
 / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/
/ /  \ \____/ /  \ \____/ /  \ \____/ /  \ \____/ /  \ \____/ /  \ \____/ /  \ \____/ /  \ \____/ /  \ \____/ /  \ \____
\ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ \ \__/ / __ 
 \____/ /  \ \____/ /  \ \____/ /  \ \____/ /  \ \____/ /  \ \____/ /  \ \____/ /  \ \____/ /  \ \____/ /  \ \____/ /  \
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
                                                                                                                    
                                                                                     EDITAR PERFIL        
                                                                                     ¯¯¯¯¯¯¯¯¯¯¯¯¯          
                                                                                                                    

                      ID:                                                                                           
                                                                                                                    
                      ────────────────────────────────────────────────────────────────────────────                  
                                                                                                                    
                      ORGANIZACION:                                                                                 
                                                                                                                    
                      ────────────────────────────────────────────────────────────────────────────                  
                                                                                                                    
                      CORREO:                                                                                       
                                                                                                                    
                      ────────────────────────────────────────────────────────────────────────────                  
                                                                                                                    
                      Socio de Coursera desde: --/--/----                                                           
                                                                                                                    
                                                                                                                    
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de dirección (IZQUIERDA, DERECHA) para moverte por el menú.
 Pulsa la tecla ENTER para seleccionar y ESC para regresar al menú anterior)";
//----------------------------------------------------------------------------------------------------------------------

    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << ui;

    resetColor();
}


/// UI Update profile info
inline void UI_UserUpdateData()
{
//----------------------------------------------------------------------------------------------------------------------
    std::string ui = R"(
                                         ▒█▀▀█ █▀▀█ █░░█ █▀▀█ █▀▀ █▀▀ █▀▀█ █▀▀█                                     
                                         ▒█░░░ █░░█ █░░█ █▄▄▀ ▀▀█ █▀▀ █▄▄▀ █▄▄█                                    
                                         ▒█▄▄█ ▀▀▀▀ ░▀▀▀ ▀░▀▀ ▀▀▀ ▀▀▀ ▀░▀▀ ▀░░▀                                     
                                                        C L O N E                                                   

                                         -  ACTUALIZA TU INFORMACION PERSONAL  -

   
                         Nombres y apellidos (O nombre de la empresa):
                         ┌──────────────────────────────────────────────────────────────────┐
                         │                                                                  │
                         └──────────────────────────────────────────────────────────────────┘ 
                         Email:
                         ┌──────────────────────────────────────────────────────────────────┐
                         │                                                                  │
                         └──────────────────────────────────────────────────────────────────┘
                         Contraseña:
                         ┌──────────────────────────────────────────────────────────────────┐
                         │                                                                  │
                         └──────────────────────────────────────────────────────────────────┘
                         Vuelva a ingresar su contraseña:
                         ┌──────────────────────────────────────────────────────────────────┐
                         │                                                                  │
                         └──────────────────────────────────────────────────────────────────┘


                                                    GUARDAR CAMBIOS   
                                                    ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯    
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de dirección ARRIBA/ABAJO para moverte por el menú.
 Pulsa ENTER para seleccionar una opción y ESC para regresar al menú anterior.)";
//----------------------------------------------------------------------------------------------------------------------

    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << ui;

    /// @brief Dibujar fondo de la cabecera
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    gotoXY(42, 6);  std::cout << "- ACTUALIZA TU INFORMACION PERSONAL -";

    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_AZUL_SUAVE);
    gotoXY(42, 1);  std::cout << "▒█▀▀█ █▀▀█ █░░█ █▀▀█ █▀▀ █▀▀ █▀▀█ █▀▀█";
    gotoXY(42, 2);  std::cout << "▒█░░░ █░░█ █░░█ █▄▄▀ ▀▀█ █▀▀ █▄▄▀ █▄▄█";
    gotoXY(42, 3);  std::cout << "▒█▄▄█ ▀▀▀▀ ░▀▀▀ ▀░▀▀ ▀▀▀ ▀▀▀ ▀░▀▀ ▀░░▀";

    gotoXY(57, 4);  std::cout << "C L O N E";

	resetColor();
}

/// UI Vista de las especialidades
inline void UI_VistaEspecialidad()
{
//----------------------------------------------------------------------------------------------------------------------
    std::string ui = R"(
   █▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█  |  C L O N E                                                                    
   █▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█                                                                               

                                                                                                                    
    Especialidad en 
   
                                           ┌────────────────────<< CURSOS DE LA ESPECIALIDAD  >>────────────────────┐
    Por:                                   │ ╔════════════════════════════════╗  ╔════════════════════════════════╗ │
                                           │ ║                                ║  ║                                ║ │
                                           │ ╠════════════════════════════════╣  ╠════════════════════════════════╣ │
                                           │ ║                                ║  ║                                ║ │
    Descripción:                           │ ║                                ║  ║                                ║ │
                                           │ ║                                ║  ║                                ║ │
                                           │ ║                                ║  ║                                ║ │ 
                                           │ ║                                ║  ║                                ║ │
                                           │ ╚════════════════════════════════╝  ╚════════════════════════════════╝ │
                                           │                                                                        │
                                           │ ╔════════════════════════════════╗  ╔════════════════════════════════╗ │
                                           │ ║                                ║  ║                                ║ │
                                           │ ╠════════════════════════════════╣  ╠════════════════════════════════╣ │
                                           │ ║                                ║  ║                                ║ │
                                           │ ║                                ║  ║                                ║ │
                                           │ ║                                ║  ║                                ║ │
                                           │ ║                                ║  ║                                ║ │
                INSCRIBIRME                │ ║                                ║  ║                                ║ │
                ¯¯¯¯¯¯¯¯¯¯¯                │ ╚════════════════════════════════╝  ╚════════════════════════════════╝ │
                                           └────────────────────────────────────────────────────────────────────────┘

────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de dirección (ARRIBA, ABAJO, IZQUIERDA, DERECHA) para navegar por las opciones.
 Pulsa ENTER para seleccionar una opción o ESC para regresar al menú anterior.)";
//----------------------------------------------------------------------------------------------------------------------

    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << ui;

    /// @brief Dibujar fondo de la cabecera
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::BLANCO_PURO);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    /// @brief/ Dibujar logo principal
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::BLANCO_PURO);
    gotoXY(3, 1);  std::cout << "█▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█";
    gotoXY(3, 2);  std::cout << "█▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█";
    gotoXY(35, 1); std::cout << "│  C L O N E";

    resetColor();
}

/// UI Vista de los cursos
inline void UI_VistaCurso()
{
//----------------------------------------------------------------------------------------------------------------------
    std::string ui = R"(
   █▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█  |  C L O N E                                                                 
   █▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█                                                                               
                                                                                                                

    Curso de 

    Por:                                            ┌───────────────────<<  CLASES DEL CURSO  >>────────────────────┐
                                                    │  ┌───┬─────────────────────────────────────────────────────┐  │
                                                    │  │ 1 │                                                     │  │
                                                    │  └───┴─────────────────────────────────────────────────────┘  │
    Descripción:                                    │    |                                                          │
                                                    │  ┌───┬─────────────────────────────────────────────────────┐  │
                                                    │  │ 2 │                                                     │  │
                                                    │  └───┴─────────────────────────────────────────────────────┘  │
                                                    │    |                                                          │
                                                    │  ┌───┬─────────────────────────────────────────────────────┐  │
                                                    │  │ 3 │                                                     │  │
                                                    │  └───┴─────────────────────────────────────────────────────┘  │
                                                    │    |                                                          │
                                                    │  ┌───┬─────────────────────────────────────────────────────┐  │
                                                    │  │ 4 │                                                     │  │
                                                    │  └───┴─────────────────────────────────────────────────────┘  │
                                                    │    |                                                          │
                                                    │  ┌───┬─────────────────────────────────────────────────────┐  │
                                                    │  │ 5 │                                                     │  │
                    INSCRIBIRME                     │  └───┴─────────────────────────────────────────────────────┘  │
                    ¯¯¯¯¯¯¯¯¯¯¯                     └───────────────────────────────────────────────────────────────┘

────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de dirección (ARRIBA, ABAJO, IZQUIERDA, DERECHA) para navegar por las opciones.
 Pulsa ENTER para seleccionar una opción o ESC para regresar al menú anterior.)";
 //----------------------------------------------------------------------------------------------------------------------

    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << ui;

    /// @brief Dibujar fondo de la cabecera
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::BLANCO_PURO);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    /// @brief/ Dibujar logo principal
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::BLANCO_PURO);
    gotoXY(3, 1);  std::cout << "█▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█";
    gotoXY(3, 2);  std::cout << "█▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█";
    gotoXY(35, 1); std::cout << "│  C L O N E";

    resetColor();
}

/// UI Vista de explorar contenido
inline void UI_ExplorarContenido()
{
//----------------------------------------------------------------------------------------------------------------------
    std::string ui = R"(
   █▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█  |  C L O N E       
   █▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█                 
   

               ┌──────────────────────────────────────────────────────────────────┐         ┌──<<  FILTRAR POR  >>──┐  
      Buscar:  │                                                                  │         │                       │   
               └──────────────────────────────────────────────────────────────────┘         │ Tipo de contenido:    │   
                                                                                            │   TODOS               │
                                                                                            │   CURSOS              │
                                                                                            │   ESPECIALIDADES      │
                                                                                            │                       │
                                                                                            │ Categoria:            │
                                                                                            │   TODAS               │
                                                                                            │                       │
                                                                                            │                       │
                                                                                            │                       │
                                                                                            │                       │
                                                                                            │                       │
                                                                                            │                       │
                                                                                            │                       │
                                                                                            │                       │
                                                                                            │                       │
                                                                                            │                       │
                                                                                            │                       │
                                                                                            │                       │
                                                                                            │                       │
                                                                                            │                       │
                                                                                            │                       │
                                  < ANTERIOR   SIGUIENTE >                                  └───────────────────────┘
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de dirección (ARRIBA, ABAJO, IZQUIERDA, DERECHA) para navegar por las opciones.
 Pulsa ENTER para seleccionar una opción o ESC para regresar al menú anterior.)";   
//----------------------------------------------------------------------------------------------------------------------

    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << ui;

    /// @brief Dibujar fondo de la cabecera
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::BLANCO_PURO);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::BLANCO_PURO);
    gotoXY(3, 1);  std::cout << "█▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█";
    gotoXY(3, 2);  std::cout << "█▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█";
    gotoXY(35, 1); std::cout << "│  C L O N E";

    resetColor();
}

/// UI Vista de las boletas de venta
inline void UI_ComprobanteDePago()
{
//----------------------------------------------------------------------------------------------------------------------
    std::string ui = R"(
   █▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█  |  C L O N E       
   █▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█                 
   

                                        TUS COMPROBANTES DE PAGO ELECTRÓNICO                                           


        -
        -
        -
        -
        -
        -
        -
        -
        -
        -
        -








                                           

────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de dirección (ARRIBA, ABAJO) para navegar por las opciones.
 Pulsa ENTER para seleccionar una opción o ESC para regresar al menú anterior.)";   
//----------------------------------------------------------------------------------------------------------------------

    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << ui;

    /// @brief Dibujar fondo de la cabecera
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::BLANCO_PURO);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::BLANCO_PURO);
    gotoXY(3, 1);  std::cout << "█▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█";
    gotoXY(3, 2);  std::cout << "█▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█";
    gotoXY(35, 1); std::cout << "│  C L O N E";

    /// @brief Dibujar fondo de la sección de título
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    for (int y = 4; y < 7; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    /// @brief Mostrar título de la sección
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    gotoXY(38, 5); std::cout << "TUS COMPROBANTES DE PAGO ELECTRÓNICO";

    resetColor();
}

/// UI Vista de la pantalla de creacion de cursos y especialidades
inline void UI_CrearContenido()
{
//----------------------------------------------------------------------------------------------------------------------
    std::string ui = R"(
   █▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█  |  C L O N E       
   █▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█                 
   

                                      GESTIÓN AUTOMATIZADA DE CONTENIDO EDUCATIVO                                      


    ╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
    ║                                    FORMULARIO DE CREACIÓN DE CONTENIDO                                       ║
    ║                                                                                                              ║
    ║  ┌ Título/Nombre del Contenido: ──────────────────────────────────────────────────────────────────────────┐  ║
    ║  │                                                                                                        │  ║
    ║  └────────────────────────────────────────────────────────────────────────────────────────────────────────┘  ║
    ║                                                                                                              ║
    ║  ┌ Descripción detallada: ────────────────────────────────────────────────────────────────────────────────┐  ║
    ║  │                                                                                                        │  ║
    ║  │                                                                                                        │  ║
    ║  └────────────────────────────────────────────────────────────────────────────────────────────────────────┘  ║
    ║                                                                                                              ║
    ║  ┌ Precio (S/): ───┐    ┌ Duración (horas): ───┐                                                             ║
    ║  │                 │    │                      │                                                             ║
    ║  └─────────────────┘    └──────────────────────┘                                                             ║
    ║                                                                                                              ║
    ╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════╝

                                  CREAR NUEVO CURSO       CREAR NUEVA ESPECIALIZACION
                                  ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯       ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯

────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de dirección ARRIBA/ABAJO para navegar por las opciones.
 Pulsa ENTER para seleccionar una opción o ESC para regresar al menú anterior.)";   
//----------------------------------------------------------------------------------------------------------------------

    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << ui;

    /// @brief Dibujar fondo de la cabecera
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::BLANCO_PURO);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    /// @brief Dibujar logo principal
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::BLANCO_PURO);
    gotoXY(3, 1);  std::cout << "█▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█";
    gotoXY(3, 2);  std::cout << "█▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█";
    gotoXY(35, 1); std::cout << "│  C L O N E";

    /// @brief Dibujar fondo de la sección de título
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    for (int y = 4; y < 7; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    /// @brief Mostrar título de la sección
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    gotoXY(38, 5); std::cout << "GESTIÓN AUTOMATIZADA DE CONTENIDO EDUCATIVO";

    resetColor();
}

/// UI Vista de la pantalla de creacion de ofertas para cursos y especialidades
inline void UI_CrearOferta()
{
//----------------------------------------------------------------------------------------------------------------------
    std::string ui = R"(
   █▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█  |  C L O N E       
   █▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█                 
   

                                           CREAR NUEVA OFERTA PROMOCIONAL                            


    ╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
    ║                                                                                                              ║
    ║  Seleccionar contenido a promocionar:                                                                        ║
    ║                                                                                                              ║
    ║  ┌─ ID: ────────────┐  ┌─ Nombre del contenido: ──────────────────────────────────────────────────────────┐  ║
    ║  │                  │  │                                                                                  │  ║
    ║  └──────────────────┘  └──────────────────────────────────────────────────────────────────────────────────┘  ║
    ║                                                                                                              ║
    ║  Detalles de la oferta:                                                                                      ║
    ║                                                                                                              ║
    ║  ┌─ Código promocional: ──────────┐  ┌─ Descuento (%): ────┐  ┌─ Fecha vencimiento: ──────────────┐          ║
    ║  │                                │  │                     │  │ DD/MM/AAAA                        │          ║
    ║  └────────────────────────────────┘  └─────────────────────┘  └───────────────────────────────────┘          ║
    ║                                                                                                              ║
    ║  Precio original (S/):  [          ]     Precio con descuento (S/):  [          ]                            ║
    ║                                                                                                              ║
    ╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════╝

                                                    CREAR OFERTA
                                                    ¯¯¯¯¯¯¯¯¯¯¯¯

────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de dirección (ARRIBA, ABAJO, IZQUIERDA, DERECHA) para navegar por las opciones.
 Pulsa ENTER para seleccionar una opción o ESC para regresar al menú anterior.)";   
//----------------------------------------------------------------------------------------------------------------------

    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << ui;

    /// @brief Dibujar fondo de la cabecera
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::BLANCO_PURO);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    /// @brief Dibujar fondo de la sección de título
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    for (int y = 4; y < 7; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    /// @brief Mostrar título de la sección
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    gotoXY(35, 5); std::cout << "CREAR NUEVA OFERTA PROMOCIONAL";

    /// @brief Dibujar logo principal
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::BLANCO_PURO);
    gotoXY(3, 1);  std::cout << "█▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█";
    gotoXY(3, 2);  std::cout << "█▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█";
    gotoXY(35, 1); std::cout << "│  C L O N E";

    resetColor();
}

/// UI Vista de las estadisticas de la empresa
inline void UI_EstadisticasEmpresa()
{
//----------------------------------------------------------------------------------------------------------------------
    std::string ui = R"(
   █▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█  |  C L O N E       
   █▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█                 


    



    ╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
    ║                                         R E S U M E N  G E N E R A L                                         ║
    ║ ┌─────────────────────────┐┌─────────────────────────┐┌─────────────────────────┐┌─────────────────────────┐ ║
    ║ │ ESTUDIANTES             ││ INGRESOS                ││ CURSOS                  ││ ESPECIALIZACIONES       │ ║
    ║ │ INSCRITOS:              ││ TOTALES:                ││ PUBLICADOS:             ││ PUBLICADAS:             │ ║
    ║ └─────────────────────────┘└─────────────────────────┘└─────────────────────────┘└─────────────────────────┘ ║
    ╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════╝

                                            ╔══════════════════════════════════════════════════════════════════════╗
                                            ║                                                                      ║
                                            ╠══════════════════════════════════════════════════════════════════════╣
                                            ║  Pos                                            Inscritos - Ingresos ║
                                            ║                                                                      ║
                                            ║  1º                                                                  ║
                                            ║  2º                                                                  ║
                                            ║  3º                                                                  ║
                                            ║  4º                                                                  ║
                                            ║  5º                                                                  ║
                                            ╚══════════════════════════════════════════════════════════════════════╝


────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Use IZQUIERDA/DERECHA para cambiar sección. Pulsa ESC para regresar.)";   
//----------------------------------------------------------------------------------------------------------------------

    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << ui;

    /// @brief Dibujar fondo de la cabecera
    setConsoleColor(ColorIndex::AZUL_MARCA , ColorIndex::BLANCO_PURO);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    /// @brief Dibujar logo principal
    gotoXY(3, 1);  std::cout << "█▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█";
    gotoXY(3, 2);  std::cout << "█▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█";
    gotoXY(35, 1); std::cout << "│  C L O N E";

    /// @brief Dibujar fondo de la sección de título
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    for (int y = 4; y < 8; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    gotoXY(8, 6); std::cout << "Institucion Educativa";

    resetColor();
}

/// UI Update profile info
inline void UI_AboutUs()
{
//----------------------------------------------------------------------------------------------------------------------
    std::string ui = R"(
                                         ▒█▀▀█ █▀▀█ █░░█ █▀▀█ █▀▀ █▀▀ █▀▀█ █▀▀█                                     
                                         ▒█░░░ █░░█ █░░█ █▄▄▀ ▀▀█ █▀▀ █▄▄▀ █▄▄█                                    
                                         ▒█▄▄█ ▀▀▀▀ ░▀▀▀ ▀░▀▀ ▀▀▀ ▀▀▀ ▀░▀▀ ▀░░▀                                     
                                                        C L O N E       

 
      Sistema de gestión de cursos desarrollado en C++ que replica las funcionalidades core de una plataforma      
      moderna. Implementa estructuras de datos avanzadas (AVL, HashMap, etc) y algoritmos optimizados para ofrecer 
      una experiencia completa de inscripciones, gestion de contenido y usuarios desde una interfaz intuitiva.     

             ┌──────────────────────────────┬────────────────────────────────┬──────────────────────────┐
             │      DESARROLLADORES         │       STACK TECNOLÓGICO        │     INFORMACIÓN UPC      │
             ├──────────────────────────────┼────────────────────────────────┼──────────────────────────┤
             │- Fabrizio Santi              │ Lenguaje: C++17                │ Universidad Peruana de   │
             │   u202411774@upc.edu.pe      │ IDE: Visual Studio 2022        │ Ciencias Aplicadas (UPC) │
             │   [ Ver perfil de GitHub ]   │ Plataforma: Windows            │                          │
             │                              │                                │ Facultad de Ingeniería   │
             │- Mauricio Teran              │ Estructuras implementadas:     │ Ciclo: 2025-1            │
             │   u202417423@upc.edu.pe      │ • AVL Trees & Hash Tables      │                          │
             │   [ Ver perfil de GitHub ]   │ • Priority Queues & BST        │ Curso: Algoritmos y      │
             │                              │ • Linked Lists & Stacks        │ Estructura de Datos      │
             │- Jahat Trinidad              │                                │                          │
             │   u202412248@upc.edu.pe      │ Algoritmos de búsqueda:        │ Trabajo Parcial          │
             │   [ Ver perfil de GitHub ]   │ • Búsqueda binaria & lineal    │ Versión: 2.0.0           │
             │                              │ • Ordenamiento: Quick, Merge   │ Fecha: Julio 2025        │
             └──────────────────────────────┴────────────────────────────────┴──────────────────────────┘

                                IR AL REPOSITORIO DE GITHUB                                
                                ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯         ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯        
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de dirección (ARRIBA, ABAJO) para navegar. ENTER para seleccionar, ESC para regresar.)";
//----------------------------------------------------------------------------------------------------------------------

    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << ui;

    /// @brief Dibujar fondo de la cabecera
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::BLANCO_PURO);
    for (int y = 0; y < 6; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    /// @brief Dibujar logo principal
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::BLANCO_PURO);
    gotoXY(42, 1);  std::cout << "▒█▀▀█ █▀▀█ █░░█ █▀▀█ █▀▀ █▀▀ █▀▀█ █▀▀█";
    gotoXY(42, 2);  std::cout << "▒█░░░ █░░█ █░░█ █▄▄▀ ▀▀█ █▀▀ █▄▄▀ █▄▄█";
    gotoXY(42, 3);  std::cout << "▒█▄▄█ ▀▀▀▀ ░▀▀▀ ▀░▀▀ ▀▀▀ ▀▀▀ ▀░▀▀ ▀░░▀";

    gotoXY(57, 4);  std::cout << "C L O N E";

    /// @brief Dibujar fondo de la sección de título
    setConsoleColor(ColorIndex::TEXTO_IMPORTANTE, ColorIndex::FONDO_AZUL_SUAVE);
    for (int y = 6; y < 11; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    gotoXY(6, 7); std::cout << "Sistema de gestión de cursos desarrollado en C++ que replica las funcionalidades core de una plataforma";
    gotoXY(6, 8); std::cout << "moderna. Implementa estructuras de datos avanzadas (AVL, HashMap, etc) y algoritmos optimizados para ofrecer";
    gotoXY(6, 9); std::cout << "una experiencia completa de inscripciones, gestion de contenido y usuarios desde una interfaz intuitiva.";

    resetColor();
}

/// UI Vista de ofertas y promociones
inline void UI_Ofertas()
{
//----------------------------------------------------------------------------------------------------------------------
    std::string ui = R"(
   █▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█  |  C L O N E       
   █▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█                 
   

                                           LISTA DE PROMOCIONES ACTIVAS 


   ╔══════════════════╦══════════════════════════════════════╦══════════════════════╦══════════════╗  ┌─────────────┐
   ║ TIPO             ║ NOMBRE                               ║ PRECIO CON DESCUENTO ║ VALIDO HASTA ║  │   FILTRAR   │
   ╠══════════════════╩══════════════════════════════════════╩══════════════════════╩══════════════╣  ├─────────────┤
   ║                                                                                               ║  │ Descuento:  │
   ║                                                                                               ║  │  TODOS      │
   ║                                                                                               ║  │  >30%       │
   ║                                                                                               ║  │  >50%       │
   ║                                                                                               ║  │  >70%       │
   ║                                                                                               ║  │             │
   ║                                                                                               ║  │ Tipo:       │
   ║                                                                                               ║  │  TODOS      │
   ║                                                                                               ║  │  Cursos     │
   ║                                                                                               ║  │  Especi...  │
   ║                                                                                               ║  └─────────────┘
   ║                                                                                               ║
   ╚═══════════════════════════════════════════════════════════════════════════════════════════════╝

────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de dirección (ARRIBA, ABAJO, IZQUIERDA, DERECHA) para navegar por las opciones.
 Pulsa ENTER para seleccionar una opción o ESC para regresar al menú anterior.)";   
//----------------------------------------------------------------------------------------------------------------------

    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << ui;

    /// @brief Dibujar fondo de la cabecera
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::BLANCO_PURO);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    /// @brief Dibujar logo principal
    gotoXY(3, 1);  std::cout << "█▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█";
    gotoXY(3, 2);  std::cout << "█▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█";
    gotoXY(35, 1); std::cout << "│  C L O N E";



    resetColor();
}

/// UI Pantalla para agregar métodos de pago
inline void UI_AgregarMetodoPago()
{
//----------------------------------------------------------------------------------------------------------------------
    std::string ui = R"(
   █▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█  |  C L O N E       
   █▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█                 
   

                                               AGREGAR MÉTODO DE PAGO                                        

    ╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
    ║   Número de tarjeta:              CVV:        Vencimiento:                                                   ║
    ║  ┌──────┬──────┬──────┬──────┐       ┌─────┐      ┌────┬────┐                                                ║
    ║  │      │      │      │      │       │     │      │ MM │ AA │                                                ║
    ║  └──────┴──────┴──────┴──────┘       └─────┘      └────┴────┘                                                ║
    ║                                                                                                              ║
    ║  ┌ Nombre del titular (como aparece en la tarjeta): ──────────────────────────────────────────────────────┐  ║
    ║  │                                                                                                        │  ║
    ║  └────────────────────────────────────────────────────────────────────────────────────────────────────────┘  ║
    ║                                                                                                              ║
    ║  ┌ Banco emisor: ──────────────┐   ┌ Dirección del titular: ─────────────────────────────────────────────┐   ║
    ║  │                             │   │                                                                     │   ║
    ║  └─────────────────────────────┘   └─────────────────────────────────────────────────────────────────────┘   ║
    ║                                                                                                              ║
    ║  Tipo de cuenta:  TARJETA DE CREDITO   TARGETA DE DEBITO                                                     ║
    ╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════╝

                        METODO DE PAGO PREDETERMINADO       HABILITAR PAGO AUTOATICO                 

                                                 GUARDAR MÉTODO                                      
                                                 ¯¯¯¯¯¯¯¯¯¯¯¯¯¯
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de dirección (ARRIBA, ABAJO, IZQUIERDA, DERECHA) para navegar. 
 Pulsa ENTER para seleccionar, ESC para cancelar.)";   
//----------------------------------------------------------------------------------------------------------------------

    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << ui;

    /// @brief Dibujar fondo de la cabecera
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::BLANCO_PURO);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    /// @brief Dibujar fondo de la sección de título
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    for (int y = 4; y < 7; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    /// @brief Mostrar título de la sección
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    gotoXY(40, 5); std::cout << " AGREGAR MÉTODO DE PAGO ";

    /// @brief Dibujar logo principal
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::BLANCO_PURO);
    gotoXY(3, 1);  std::cout << "█▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█";
    gotoXY(3, 2);  std::cout << "█▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█";
    gotoXY(35, 1); std::cout << "│  C L O N E";

    resetColor();
}

/// UI Pantalla para procesar pagos
inline void UI_ProcesarPago()
{
//----------------------------------------------------------------------------------------------------------------------
    std::string ui = R"(
   █▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█  |  C L O N E       
   █▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█                 
  

                                                 RESUMEN DE COMPRA


    ╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
    ║  Producto:                                                                                                   ║
    ║                                                                                                              ║
    ║  ┌────────────────────────────────────────────────────────────────────────────────────────────────────────┐  ║
    ║  │ Sub Total:                                                                     S/                      │  ║
    ║  │ Descuento aplicado:                                                            S/                      │  ║
    ║  │ IGV (18%):                                                                     S/                      │  ║
    ║  │                                                                                                        │  ║
    ║  │ TOTAL A PAGAR:                                                                 S/                      │  ║
    ║  └────────────────────────────────────────────────────────────────────────────────────────────────────────┘  ║
    ║                                                                                                              ║
    ║  Método de pago seleccionado:                                                                                ║
    ║                                [ Cambiar método de pago ]                                                    ║
    ║                                                                                                              ║
    ╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════╝

    Acepto los términos y condiciones de CourseraClone 

                                     CONFIRMAR PAGO                CANCELAR COMPRA                          
                                     ¯¯¯¯¯¯¯¯¯¯¯¯¯¯                ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯

────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de dirección (ARRIBA, ABAJO, IZQUIERDA, DERECHA) para navegar. 
 Pulsa ENTER para confirmar, ESC para cancelar.)";   
//----------------------------------------------------------------------------------------------------------------------

    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << ui;

    /// @brief Dibujar fondo de la cabecera
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::BLANCO_PURO);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    /// @brief Dibujar logo principal
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::BLANCO_PURO);
    gotoXY(3, 1);  std::cout << "█▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█";
    gotoXY(3, 2);  std::cout << "█▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█";
    gotoXY(35, 1); std::cout << "│  C L O N E";

    /// @brief Dibujar fondo de la sección de título
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    for (int y = 4; y < 7; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    /// @brief Mostrar título de la sección
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    gotoXY(40, 5); std::cout << " RESUMEN DE COMPRA ";

    resetColor();
}

/// UI Vista de certificados obtenidos
inline void UI_Certificados()
{
//----------------------------------------------------------------------------------------------------------------------
    std::string ui = R"(
   █▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█  |  C L O N E
   █▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█                 


                                           MIS CERTIFICADOS OBTENIDOS

    ╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
    ║  ┌───────────────────────────────────────────────────────────────────────────────────────────────────────┐  ║
    ║  │                                    CERTIFICADO DE FINALIZACIÓN                                        │  ║
    ║  │                                                                                                       │  ║
    ║  │                              ▒█▀▀█ █▀▀█ █░░█ █▀▀█ █▀▀ █▀▀ █▀▀█ █▀▀█                                   │  ║
    ║  │                              ▒█░░░ █░░█ █░░█ █▄▄▀ ▀▀█ █▀▀ █▄▄▀ █▄▄█                                   │  ║
    ║  │                              ▒█▄▄█ ▀▀▀▀ ░▀▀▀ ▀░▀▀ ▀▀▀ ▀▀▀ ▀░▀▀ ▀░░▀                                   │  ║
    ║  │                                             C L O N E                                                 │  ║
    ║  │                                                                                                       │  ║
    ║  │   Por la presente certifica que:                                                                      │  ║
    ║  │                                                                                                       │  ║
    ║  │                                                                                                       │  ║
    ║  │                                                                                                       │  ║
    ║  │   Ha completado satisfactoriamente el curso:                                                          │  ║
    ║  │                                                                                                       │  ║
    ║  │                                                                                                       │  ║
    ║  │                                                                                                       │  ║
    ║  │ Instructor:                                       Fecha: DD/MM/AAAA    ID Certificado: [ID]           │  ║
    ║  └───────────────────────────────────────────────────────────────────────────────────────────────────────┘  ║
    ╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
    (Pulsa D para descargar el certificado en PDF)                             < ANTERIOR     [1/5]     SIGUIENTE >

────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de dirección (IZQUIERDA/DERECHA) para navegar por certificados.
 Pulsa ENTER para ver detalles o ESC para regresar al menú anterior.)";   
//----------------------------------------------------------------------------------------------------------------------

    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << ui;

    /// @brief Dibujar fondo de la cabecera
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::BLANCO_PURO);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    /// @brief Dibujar fondo de la sección de título
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    for (int y = 4; y < 7; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    /// @brief Mostrar título de la sección
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    gotoXY(43, 5); std::cout << "MIS CERTIFICADOS OBTENIDOS";

    /// @brief Dibujar logo principal
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::BLANCO_PURO);
    gotoXY(3, 1);  std::cout << "█▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█";
    gotoXY(3, 2);  std::cout << "█▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█";
    gotoXY(35, 1); std::cout << "│  C L O N E";

    resetColor();
}

/// UI Vista de listar contenido creado por la organización
inline void UI_ListarContenido()
{
//----------------------------------------------------------------------------------------------------------------------
    std::string ui = R"(
   █▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█  |  C L O N E       
   █▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█                 
   

                                               LISTADO DE CONTENIDO PUBLICADO                                      


     ID │ Nombre del contenido                  │ Tipo            │ Categoría        │ Precio     │ Inscritos
    ────┼───────────────────────────────────────┼─────────────────┼──────────────────┼────────────┼──────────
        │                                       │                 │                  │            │
        │                                       │                 │                  │            │
        │                                       │                 │                  │            │
        │                                       │                 │                  │            │
        │                                       │                 │                  │            │
        │                                       │                 │                  │            │
        │                                       │                 │                  │            │
        │                                       │                 │                  │            │
        │                                       │                 │                  │            │
        │                                       │                 │                  │            │
        │                                       │                 │                  │            │
        │                                       │                 │                  │            │
        │                                       │                 │                  │            │
        │                                       │                 │                  │            │
        │                                       │                 │                  │            │
        │                                       │                 │                  │            │


                                        < ANTERIOR     [1/5]     SIGUIENTE >        

────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 ARRIBA/ABAJO: Navegar, IZQUIERDA/DERECHA: Cambiar página, ENTER: Detalles,  ESC: Regresar)";  
  
//----------------------------------------------------------------------------------------------------------------------

    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << ui;

    /// @brief Dibujar fondo de la cabecera
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::BLANCO_PURO);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    /// @brief Dibujar fondo de la sección de título
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    for (int y = 4; y < 7; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    /// @brief Mostrar título de la sección
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    gotoXY(45, 5); std::cout << "LISTADO DE CONTENIDO PUBLICADO";

    /// @brief Dibujar logo principal
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::BLANCO_PURO);
    gotoXY(3, 1);  std::cout << "█▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█";
    gotoXY(3, 2);  std::cout << "█▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█";
    gotoXY(35, 1); std::cout << "│  C L O N E";

    resetColor();
}



/*
┌──┬───────┐
│  │       │
├──┼───────┤
│  │       │
└──┴───────┘
*/

/// UI Vista de gestión de ofertas para la organización
inline void UI_GestionarOfertas()
{
//----------------------------------------------------------------------------------------------------------------------
    std::string ui = R"(
   █▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█  |  C L O N E       
   █▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█                 
   

                                        GESTIÓN DE OFERTAS PROMOCIONALES                                  


     ID │ Nombre del contenido                      │ Codigo          │ Descuento    │ Precio     │ Estado
    ────┼───────────────────────────────────────────┼─────────────────┼──────────────┼────────────┼──────────
        │                                           │                 │              │            │
        │                                           │                 │              │            │
        │                                           │                 │              │            │
        │                                           │                 │              │            │
        │                                           │                 │              │            │
        │                                           │                 │              │            │
        │                                           │                 │              │            │
        │                                           │                 │              │            │
        │                                           │                 │              │            │
        │                                           │                 │              │            │
        │                                           │                 │              │            │
        │                                           │                 │              │            │
        │                                           │                 │              │            │
        │                                           │                 │              │            │
        │                                           │                 │              │            │
        │                                           │                 │              │            │


                                      < ANTERIOR     [1/3]     SIGUIENTE >    

────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 ARRIBA/ABAJO: Navegar, IZQUIERDA/DERECHA: Página, X: Eliminar.  ESC: Regresar)"; 
  
//----------------------------------------------------------------------------------------------------------------------

    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_PRINCIPAL);
    std::cout << ui;

    /// @brief Dibujar fondo de la cabecera
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::BLANCO_PURO);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    /// @brief Dibujar fondo de la sección de título
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    for (int y = 4; y < 7; y++)
    {
        for (int x = 0; x < ANCHO_CONSOLA; x++)
        {
            gotoXY(x, y);
            std::cout << " ";
        }
    }

    /// @brief Mostrar título de la sección
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    gotoXY(35, 5); std::cout << "GESTIÓN DE OFERTAS PROMOCIONALES";

    /// @brief Dibujar logo principal
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::BLANCO_PURO);
    gotoXY(3, 1);  std::cout << "█▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█";
    gotoXY(3, 2);  std::cout << "█▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█";
    gotoXY(35, 1); std::cout << "│  C L O N E";

    resetColor();
}

#endif // COURSERACLONE_UTILS_UI_ASCII_HPP