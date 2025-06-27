// filepath: Headers/Utils/UI_Ascii.hpp
// Descripcion: Elementos ASCII para interfaces de usuario

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
 Usa las flechas de direccion (ARRIBA, ABAJO, IZQUIERDA, DERECHA) para navegar por el menu.
 Pulsa la tecla ENTER para seleciconar y ESC para SALIR DEL PROGRAMA.)";
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
 Usa las flechas de direccion (ARRIBA Y ABAJO) para navegar por el menu.
 Pulsa la tecla ENTER para seleciconar una opcion y ESC para regresar al menu anterior.)";
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
 Usa las flechas de direccion (ARRIBA Y ABAJO) para moverte por el menu.
 Pulsa la tecla ENTER para seleciconar un boton y ESC para regresar al menu anterior.)";
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
                                                                                                                    
                                 EXPLORAR CURSOS Y ESPECIALIDADES      REVISAR OFERTAS                                 |
       
                                                                                                                     
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
 Usa las flechas de direccion (ARRIBA, ABAJO, IZQUIERDA, DERECHA) para moverte por el menu.
 Pulsa la tecla ENTER para seleciconar y ESC para regresar al menu anterior.)";
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

    gotoXY(22, 5); std::cout << "Te damos la bienvenida";
    gotoXY(22, 6); std::cout << "RECUERDA:";

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
                                                                                                                
                   EXPLORAR CURSOS Y ESPECIALIDADES      GESTIONAR MI CONTENIDO      VER ESTADISTICAS                  

                                                                                                            
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
 Usa las flechas de direccion (ARRIBA, ABAJO, IZQUIERDA, DERECHA) para moverte por el menu.
 Pulsa la tecla ENTER para seleciconar y ESC para regresar al menu anterior.)";
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

    /// @brief Dibujar fondo del menu suoerior
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
 Usa las flechas de direccion (IZQUIERDA, DERECHA) para moverte por el menu.
 Pulsa la tecla ENTER para seleciconar y ESC para regresar al menu anterior.)";
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
 Usa las flechas de direccion (IZQUIERDA, DERECHA) para moverte por el menu.
 Pulsa la tecla ENTER para seleciconar y ESC para regresar al menu anterior)";
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


                                                    GURRDAR CAMBIOS   
                                                    ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯    
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de direccion (ARRIBA Y ABAJO) para moverte por el menu.
 Pulsa ENTER para seleciconar una opcion y ESC para regresar al menu anterior.)";
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
    Descripcion:                           │ ║                                ║  ║                                ║ │
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
 Usa las flechas de direccion (ARRIBA, ABAJO, IZQUIERDA, DERECHA) para navegar por las opciones.
 Pulsa ENTER para seleciconar una opcion o ESC para regresar al menu anterior.)";
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
    Descripcion:                                    │    |                                                          │
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
 Usa las flechas de direccion (ARRIBA, ABAJO, IZQUIERDA, DERECHA) para navegar por las opciones.
 Pulsa ENTER para seleciconar una opcion o ESC para regresar al menu anterior.)";
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
    -                                                                                       │   CURSOS              │
    -                                                                                       │   ESPECIALIDADES      │
    -                                                                                       │                       │
    -                                                                                       │ Categoria:            │
    -                                                                                       │   TODAS               │
    -                                                                                       │                       │
    -                                                                                       │                       │
    -                                                                                       │                       │
    -                                                                                       │                       │
    -                                                                                       │                       │
    -                                                                                       │                       │
    -                                                                                       │                       │
    -                                                                                       │                       │
    -                                                                                       │                       │
    -                                                                                       │                       │
    -                                                                                       │                       │
    -                                                                                       │                       │
    -                                                                                       │                       │
    -                                                                                       │                       │
                                                                                            │                       │
                                  < ANTERIOR   SIGUIENTE >                                  └───────────────────────┘
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de direccion (ARRIBA, ABAJO, IZQUIERDA, DERECHA) para navegar por las opciones.
 Pulsa ENTER para seleciconar una opcion o ESC para regresar al menu anterior.)";   
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
   

                                        TUS COMPROBANTES DE PAGO ELECTRÓNICO                                           |


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








                                           < ANTERIOR     SIGUIENTE >

────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de direccion (ARRIBA, ABAJO) para navegar por las opciones.
 Pulsa ENTER para seleciconar una opcion o ESC para regresar al menu anterior.)";   
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

/// UI Vista de la pantalla de creacion de cursos y especialidades
inline void UI_CrearContenido()
{
//----------------------------------------------------------------------------------------------------------------------
    std::string ui = R"(
   █▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█  |  C L O N E       
   █▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█                 
   

                                    GESTIÓN AUTOMATIZADA DE CONTENIDO EDUCATIVO                               

    ╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
    ║                                   FORMULARIO DE CREACIÓN DE CONTENIDO                                        ║
    ║                                                                                                              ║
    ║  Título/Nombre del Contenido:                                                                                ║
    ║  ┌────────────────────────────────────────────────────────────────────────────────────────────────────────┐  ║
    ║  │                                                                                                        │  ║
    ║  └────────────────────────────────────────────────────────────────────────────────────────────────────────┘  ║
    ║                                                                                                              ║
    ║  Descripción detallada:                                                                                      ║
    ║  ┌────────────────────────────────────────────────────────────────────────────────────────────────────────┐  ║
    ║  │                                                                                                        │  ║
    ║  │                                                                                                        │  ║
    ║  └────────────────────────────────────────────────────────────────────────────────────────────────────────┘  ║
    ║                                                                                                              ║
    ║  Precio (S/):       Duración (horas):                                                                        ║
    ║  ┌─────────────┐    ┌─────────────────┐                                                                      ║
    ║  │             │    │                 │                                                                      ║
    ║  └─────────────┘    └─────────────────┘                                                                      ║
    ╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════╝

                                      CREAR CURSO       CREAR ESPECIALIDAD
                                      ¯¯¯¯¯¯¯¯¯¯¯       ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de direccion (ARRIBA, ABAJO, IZQUIERDA, DERECHA) para navegar por las opciones.
 Pulsa ENTER para seleciconar una opcion o ESC para regresar al menu anterior.)";   
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
    gotoXY(30, 5); std::cout << "📚 GESTIÓN AUTOMATIZADA DE CONTENIDO EDUCATIVO 📚";

    /// @brief Dibujar logo principal
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::BLANCO_PURO);
    gotoXY(3, 1);  std::cout << "█▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█";
    gotoXY(3, 2);  std::cout << "█▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█";
    gotoXY(35, 1); std::cout << "│  C L O N E";

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
 Usa las flechas de direccion (ARRIBA, ABAJO, IZQUIERDA, DERECHA) para navegar por las opciones.
 Pulsa ENTER para seleciconar una opcion o ESC para regresar al menu anterior.)";   
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
    ║ │                         ││                         ││                         ││                         │ ║
    ║ │       1,247             ││    S/ 89,450.00         ││         23              ││          5              │ ║
    ║ └─────────────────────────┘└─────────────────────────┘└─────────────────────────┘└─────────────────────────┘ ║
    ╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
    ╔═════════════════════════════════════╗ ╔══════════════════════════════════════════════════════════════════════╗
    ║         INSCRIPCIONES POR MES       ║ ║                    TOP CURSOS MÁS POPULARES                          ║
    ║                                     ║ ╠══════════════════════════════════════════════════════════════════════╣
    ║  200┤                               ║ ║  Pos │ Curso                                  │ Inscritos │ Ingresos ║
    ║     │    ██                         ║ ╟──────┼────────────────────────────────────────┼───────────┼──────────╢
    ║  150┤    ██                         ║ ║  1º  │ Python para Data Science               │    245    │  S/15K   ║
    ║     │ ██ ██    ██                   ║ ║  2º  │ Machine Learning Avanzado              │    198    │  S/12K   ║
    ║  100┤ ██ ██ ██ ██                   ║ ║  3º  │ Desarrollo Web Full Stack              │    167    │  S/10K   ║
    ║     │ ██ ██ ██ ██ ██                ║ ║  4º  │ Análisis de Datos con R                │    134    │  S/8K    ║
    ║  50 ┤ ██ ██ ██ ██ ██ ██             ║ ║  5º  │ Fundamentos de IA                      │    112    │  S/7K    ║
    ║     └─┬──┬──┬──┬──┬──┬─             ║ ║  5º  │ Fundamentos de IA                      │    112    │  S/7K    ║
    ║      Ene Feb Mar Abr May Jun        ║ ║  5º  │ Fundamentos de IA                      │    112    │  S/7K    ║
    ╚═════════════════════════════════════╝ ╚══════════════════════════════════════════════════════════════════════╝
                                             
                                                   EXPORTAR REPORTE  
                                                   ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯  
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de direccion (ARRIBA, ABAJO, IZQUIERDA, DERECHA) para navegar por las opciones.
 Pulsa ENTER para seleciconar una opcion o ESC para regresar al menu anterior.)";   
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

    /// @brief Mostrar título de la sección
    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
    gotoXY(42, 5); std::cout << "***  DASHBOARD DE ESTADÍSTICAS  ***";

    /// @brief Dibujar logo principal
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::BLANCO_PURO);
    gotoXY(3, 1);  std::cout << "█▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█";
    gotoXY(3, 2);  std::cout << "█▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█";
    gotoXY(35, 1); std::cout << "│  C L O N E";

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

    ╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════╗    
    ║ Sistema de gestión de cursos desarrollado en C++ que replica las funcionalidades core de una plataforma      ║
    ║ moderna. Implementa estructuras de datos avanzadas (AVL, HashMap, etc) y algoritmos optimizados para ofrecer ║
    ║ una experiencia completa de inscripciones, gestion de contenido y usuarios desde una interfaz intuitiva.     ║
    ╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════╝
               ┌───────────────────────────┬────────────────────────────────┬──────────────────────────┐
               │      DESARROLLADORES      │       STACK TECNOLÓGICO        │     INFORMACIÓN UPC      │
               ├───────────────────────────┼────────────────────────────────┼──────────────────────────┤
               │- Fabrizio Santi           │ Lenguaje: C++17                │ Universidad Peruana de   │
               │   u202411774@upc.edu.pe   │ IDE: Visual Studio 2022        │ Ciencias Aplicadas (UPC) │
               │   [ Ver perfil GitHub ]   │ Plataforma: Windows            │                          │
               │                           │                                │ Facultad de Ingeniería   │
               │- Mauricio Teran           │ Estructuras implementadas:     │ Ciclo: 2025-1            │
               │   u202417423@upc.edu.pe   │ • AVL Trees & Hash Tables      │                          │
               │   [ Ver perfil GitHub ]   │ • Priority Queues & BST        │ Curso: Algoritmos y      │
               │                           │ • Linked Lists & Stacks        │ Estructura de Datos      │
               │- Jahat Trinidad           │                                │                          │
               │   u202412248@upc.edu.pe   │ Algoritmos de búsqueda:        │ Trabajo Parcial          │
               │   [ Ver perfil GitHub ]   │ • Búsqueda binaria & lineal    │ Versión: 2.0.0           │
               │                           │ • Ordenamiento: Quick, Merge   │ Fecha: Julio 2025        │
               └───────────────────────────┴────────────────────────────────┴──────────────────────────┘

                                          VER REPOSITORIO         DOCUMENTACIÓN      
                                          ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯         ¯¯¯¯¯¯¯¯¯¯¯¯¯      
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de direccion (ARRIBA, ABAJO) para navegar. ENTER para seleccionar, ESC para regresar.)";
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

    /// @brief Dibujar logo principal
    setConsoleColor(ColorIndex::AZUL_MARCA, ColorIndex::FONDO_AZUL_SUAVE);
    gotoXY(42, 1);  std::cout << "▒█▀▀█ █▀▀█ █░░█ █▀▀█ █▀▀ █▀▀ █▀▀█ █▀▀█";
    gotoXY(42, 2);  std::cout << "▒█░░░ █░░█ █░░█ █▄▄▀ ▀▀█ █▀▀ █▄▄▀ █▄▄█";
    gotoXY(42, 3);  std::cout << "▒█▄▄█ ▀▀▀▀ ░▀▀▀ ▀░▀▀ ▀▀▀ ▀▀▀ ▀░▀▀ ▀░░▀";

    gotoXY(57, 4);  std::cout << "C L O N E";

    resetColor();
}

/// UI Vista de ofertas y promociones
inline void UI_Ofertas()
{
//----------------------------------------------------------------------------------------------------------------------
    std::string ui = R"(
   █▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█  |  C L O N E       
   █▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█                 
   
╔═══════════════════════════════════════════════════════════════════════════════════════════════╗  ┌───────────────────┐
║                                         OFERTAS DESTACADAS                                    ║  │  FILTRAR OFERTAS  │
║                                                                                               ║  ├───────────────────┤
║ ┌─────────────────────────────┐┌─────────────────────────────┐┌─────────────────────────────┐ ║  │ Categoría:        │
║ │   MEGA OFERTA ESTUDIANTES   ││  PACK DESARROLLADOR WEB     ││   ESPECIALIZACIÓN DATA      │ ║  │  TODAS            │
║ │                             ││                             ││                             │ ║  │  TECNOLOGÍA       │
║ │ 50% OFF en todos los cursos ││ 3 cursos + certificación    ││ Machine Learning + Python   │ ║  │  NEGOCIOS         │
║ │ ¡Solo por tiempo limitado!  ││ HTML, CSS, JavaScript       ││ 2 especialidades por S/99   │ ║  │  DISEÑO           │
║ │                             ││                             ││                             │ ║  │  CIENCIAS         │
║ │ Antes: S/150  Ahora: S/75   ││ Antes: S/300  Ahora: S/199  ││ Antes: S/250  Ahora: S/99   │ ║  │                   │
║ │                             ││                             ││                             │ ║  │ Descuento:        │
║ │     Código: STUDENT50       ││     Código: WEBDEV2025      ││     Código: DATAAI99        │ ║  │  TODOS            │
║ └─────────────────────────────┘└─────────────────────────────┘└─────────────────────────────┘ ║  │  >30%             │
╚═══════════════════════════════════════════════════════════════════════════════════════════════╝  │  >50%             │
╔═══════════════════════════════════════════════════════════════════════════════════════════════╗  │  >70%             │
║                                      LISTA DE PROMOCIONES ACTIVAS                             ║  │                   │
║                                                                                               ║  │ Precio:           │
║  Curso "Python Básico"                          S/80 -> S/49        Válido hasta: 30/06/2025  ║  │  TODOS            │
║  Especialización "Marketing Digital"            S/200 -> S/149      Válido hasta: 15/07/2025  ║  │  <S/50            │
║  Pack "Diseño UX/UI Completo"                   S/180 -> S/120      Válido hasta: 25/06/2025  ║  │  <S/100           │
║  Curso "Análisis de Datos con R"                S/120 -> S/89       Válido hasta: 28/06/2025  ║  │  <S/200           │
║  Especialización "Ciberseguridad"               S/250 -> S/175      Válido hasta: 10/07/2025  ║  │                   │
║  Curso "Fundamentos de IA"                      S/90 -> S/59        Válido hasta: 05/07/2025  ║  │                   │
║                                                                                               ║  │                   │
╚═══════════════════════════════════════════════════════════════════════════════════════════════╝  └───────────────────┘
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de direccion (ARRIBA, ABAJO, IZQUIERDA, DERECHA) para navegar por las opciones.
 Pulsa ENTER para seleciconar una opcion o ESC para regresar al menu anterior.)";   
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
    ║  ┌─────┬─────┬─────┬─────┐       ┌─────┐      ┌────┬────┐                                                    ║
    ║  │     │     │     │     │       │     │      │ MM │ AA │                                                    ║
    ║  └─────┴─────┴─────┴─────┘       └─────┘      └────┴────┘                                                    ║
    ║                                                                                                              ║
    ║  ┌ Nombre del titular (como aparece en la tarjeta): ──────────────────────────────────────────────────────┐  ║
    ║  │                                                                                                        │  ║
    ║  └────────────────────────────────────────────────────────────────────────────────────────────────────────┘  ║
    ║                                                                                                              ║
    ║  ┌ Banco emisor: ──────────────┐   ┌ Dirección del titular: ─────────────────────────────────────────────┐   ║
    ║  │ BCP, BBVA, Interbank, etc.  │   │                                                                     │   ║
    ║  └─────────────────────────────┘   └─────────────────────────────────────────────────────────────────────┘   ║
    ║                                                                                                              ║
    ║  Tipo de cuenta:  TARJETA DE CREDITO   TARGETA DE DEBITO                                                     ║
    ╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════╝

                Guardar como método de pago predeterminado   Habilitar pagos automáticos para suscripciones                  

                                                 GUARDAR MÉTODO                                      
                                                 ¯¯¯¯¯¯¯¯¯¯¯¯¯¯
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de direccion (ARRIBA, ABAJO, IZQUIERDA, DERECHA) para navegar. 
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
   
 
    ╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════╗
    ║                                          RESUMEN DE COMPRA                                                   ║
    ╠══════════════════════════════════════════════════════════════════════════════════════════════════════════════╣
    ║                                                                                                              ║
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
    ║  Método de pago seleccionado:  Visa **** **** **** 4567 (Juan Pérez)                                         ║
    ║                                [ Cambiar método de pago ]                                                    ║
    ║                                                                                                              ║
    ╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════╝

    Acepto los términos y condiciones de CourseraClone 

                                CONFIRMAR PAGO                CANCELAR COMPRA                          
                                ¯¯¯¯¯¯¯¯¯¯¯¯¯¯                ¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯

────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de direccion (ARRIBA, ABAJO, IZQUIERDA, DERECHA) para navegar. 
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

    resetColor();
}

/*
┌──┬───────┐
│  │       │
├──┼───────┤
│  │       │
└──┴───────┘
*/

#endif // COURSERACLONE_UTILS_UI_ASCII_HPP