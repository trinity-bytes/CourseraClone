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

    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
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

    setConsoleColor(ColorIndex::TEXTO_SECUNDARIO, ColorIndex::FONDO_AZUL_SUAVE);
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
   
   Descripcion:                            ┌────────────────────<< CURSOS DE LA ESPECIALIDAD  >>────────────────────┐
                                           │ ╔════════════════════════════════╗  ╔════════════════════════════════╗ |
                                           │ ║                                ║  ║                                ║ │
                                           │ ╠════════════════════════════════╣  ╠════════════════════════════════╣ │
                                           │ ║                                ║  ║                                ║ │
                                           │ ║                                ║  ║                                ║ │
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

    std::cout << ui;
}

/// UI Vista de los cursos
inline void UI_VistaCurso()
{
    std::string ui = R"(
   █▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█  |  C L O N E                                                                 
   █▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█                                                                               
                                                                                                                

   Curso de 

   Descripcion:                                     ┌───────────────────<<  CLASES DEL CURSO  >>────────────────────┐
                                                    │  ┌───┬─────────────────────────────────────────────────────┐  │
                                                    │  │ 1 │                                                     │  │
                                                    │  └───┴─────────────────────────────────────────────────────┘  │
                                                    │    |                                                          │
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

    std::cout << ui;
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

/// UI Update profile info
inline void UI_AboutUs()
{
//----------------------------------------------------------------------------------------------------------------------
    std::string ui = R"(
                                         ▒█▀▀█ █▀▀█ █░░█ █▀▀█ █▀▀ █▀▀ █▀▀█ █▀▀█                                     
                                         ▒█░░░ █░░█ █░░█ █▄▄▀ ▀▀█ █▀▀ █▄▄▀ █▄▄█                                    
                                         ▒█▄▄█ ▀▀▀▀ ░▀▀▀ ▀░▀▀ ▀▀▀ ▀▀▀ ▀░▀▀ ▀░░▀                                     
                                                        C L O N E       


        CourseraClone es un sistema de gestión de cursos desarrollado en C++ que replica las funcionalidades    
        core de una plataforma educativa moderna inspirada en Coursera. Implementa estructuras de datos         
        avanzadas (AVL, HashMap, PriorityQueue) y algoritmos optimizados para ofrecer una experiencia completa  
        de inscripciones, exploración de contenido y gestión de usuarios, todo desde una interfaz de consola.   
 
                                        IR AL REPOSITORIO DE GITHUB DEL PROYECTO                                        

        ----------------------------------------<<  DESARROLLADORES  >>----------------------------------------
                         Fabrizio Santi  -  (u202411774@upc.edu.pe)  [ Ver perfil de GitHub ]
                         Mauricio Teran  -  (u202417423@upc.edu.pe)  [ Ver perfil de GitHub ]
                         Jahat Trinidad  -  (u202412248@upc.edu.pe)  [ Ver perfil de GitHub ]

        ───────────────────────────────────────<<  STACK TECNOLÓGICO  >>───────────────────────────────────────
                          Lenguaje: C++17  -  IDE: Visual Studio 2022  -  Plataforma: Windows  

        ───────────────────────────────────<<  INFORMACION INSTITUCIONAL  >>───────────────────────────────────
                       Universidad Peruana de Ciencias Aplicadas (UPC) - Facultad de Ingeniería                
                                                Ciclo académico: 2025-1


                                     "CourseraClone - Sistema de Gestión de Cursos"
                                   Versión actual: 2.0.0 (Arquitectura Refactorizada)                                   
────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de direccion (ARRIBA Y ABAJO) para navegar por las opciones.
 Pulsa la tecla ENTER para seleciconar una opcion y ESC para regresar al menu anterior.)";
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

/// UI Vista de pantalla generica
inline void UI_Generico()
{
//----------------------------------------------------------------------------------------------------------------------
    std::string ui = R"(
   █▀▀ █▀█ █░█ █▀█ █▀ █▀▀ █▀█ ▄▀█  |  C L O N E       
   █▄▄ █▄█ █▄█ █▀▄ ▄█ ██▄ █▀▄ █▀█                 
   

























────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────
 Usa las flechas de direccion (ARRIBA, ABAJO, IZQUIERDA, DERECHA) para navegar por las opciones.
 Pulsa ENTER para seleciconar una opcion o ESC para regresar al menu anterior.)";   
//----------------------------------------------------------------------------------------------------------------------

    std::cout << ui;
}

/*
┌──┬───────┐
│  │       │
├──┼───────┤
│  │       │
└──┴───────┘
*/

#endif // COURSERACLONE_UTILS_UI_ASCII_HPP