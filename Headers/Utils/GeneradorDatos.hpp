#ifndef COURSErACLONE_HEADERS_UTILS_GENERADORDATOS_HPP
#define COURSErACLONE_HEADERS_UTILS_GENERADORDATOS_HPP

// Headers estándar
#include "../Controllers/SessionManager.hpp"
#include "ContentGenerator.hpp"
#include "../Utils/ValidationUtils.hpp"

class GeneradorDatos {

public:

    inline std::vector<std::string> generarNombres();
    inline std::vector<std::string> generarNombres(int n);
    inline void generarActividad(std::vector<std::string> empresas = {"courclone", "platclone"}, int cantidad = 10);
    inline void generarUsuarios(int n = 2);
	inline void anadirNombresImportantes(std::vector<std::string>& nombres);
    inline void generarTodo();
};

inline void GeneradorDatos::anadirNombresImportantes(std::vector<std::string>& nombres) {
    nombres.push_back("platclone");
	nombres.push_back("jahat");
	nombres.push_back("mauricio");
	nombres.push_back("fabrizio");
    nombres.push_back("courclone");
	
}

inline void GeneradorDatos::generarActividad(std::vector<std::string> empresas, int cantidad) {
    for (std::string& empresa : empresas) {
        std::string nuevo = empresa + "@gmail.com";
        LoginStatus res = SessionManager::getInstance().login(nuevo, "123456", TipoUsuario::EMPRESA);
        if (res == LoginStatus::WRONG_PASSWORD) {
            std::cout << "ayuda";
        }
        else if (res == LoginStatus::USER_NOT_FOUND) {
            std::cout << "Pero encuentralo bien";
        }
        cout << nuevo << endl;
        system("pause");

        if (res == LoginStatus::SUCCESS) {

            std::cout << "POR?????";
            system("pause");

            for (int i = 0; i < cantidad; i++) {
                std::string numero = std::to_string(i + 1);
                RawEspecializacionData datosGenerados = ContentGenerator::generarEspecializacion(
                    "Prueba" + numero,
                    "Texto de prueba " + numero,
                    "50.0",
                    "60"
                );

                ContentManager& contentManager = ContentManager::getInstance();
                std::vector<int> idsReales;

                // Crear cada curso de la especialización
                int prueba = 1;
                for (int i = 0; i < datosGenerados.cantidadCursos; i++) {
                    // Generar datos del curso usando ContentGenerator
                    std::string tituloCurso = datosGenerados.titulo + " - Módulo " + std::to_string(i + 1);
                    RawCursoData cursoDatos = ContentGenerator::generarCurso(tituloCurso, "", "", "");

                    // Asegurar que tenga la misma categoría y empresa
                    cursoDatos.categoria = datosGenerados.categoria;
                    cursoDatos.idEmpresa = datosGenerados.idEmpresa;
                    cursoDatos.nombreEmpresa = datosGenerados.nombreEmpresa;

                    // Separar títulos y descripciones de clases
                    std::vector<std::string> titulosClases;
                    std::vector<std::string> descripcionesClases;

                    for (const auto& clase : cursoDatos.descripcionClases) {
                        titulosClases.push_back(clase.first);
                        descripcionesClases.push_back(clase.second);
                    }

                    // Crear el curso
                    ContentOperationResult resultadoCurso = contentManager.crearCurso(
                        cursoDatos.idEmpresa,
                        cursoDatos.titulo,
                        cursoDatos.nombreEmpresa,
                        cursoDatos.precio,
                        cursoDatos.instructor,
                        cursoDatos.descripcion,
                        titulosClases,
                        descripcionesClases,
                        prueba,
                        RawActividadData::categoriaToString(cursoDatos.categoria)
                    );

                    if (resultadoCurso == ContentOperationResult::SUCCESS) {
                        // Simplificamos: usamos IDs secuenciales predecibles
                        // El ContentManager usa un contador interno que incrementa con cada curso
                        int idEstimado = contentManager.getTotalCursos(); // El ID será aproximadamente el total actual

                        // Verificar que el curso existe con este ID aproximado
                        Curso* cursoCreado = contentManager.obtenerCurso(idEstimado);
                        if (cursoCreado && cursoCreado->getTitulo() == cursoDatos.titulo) {
                            idsReales.push_back(cursoCreado->getId());
                        }
                        else {
                            // Buscar en un rango pequeño alrededor del ID estimado
                            bool encontrado = false;
                            for (int offset = -2; offset <= 2 && !encontrado; ++offset) {
                                int idPrueba = idEstimado + offset;
                                if (idPrueba > 0) {
                                    Curso* cursoPrueba = contentManager.obtenerCurso(idPrueba);
                                    if (cursoPrueba && cursoPrueba->getTitulo() == cursoDatos.titulo) {
                                        idsReales.push_back(cursoPrueba->getId());
                                        encontrado = true;
                                    }
                                }
                            }
                        }
                    }
                }

                // Actualizar los IDs en los datos generados
                datosGenerados.idsCursos = idsReales;
                datosGenerados.cantidadCursos = static_cast<int>(idsReales.size());

				int nuevoId = -1;
                
                // Crear especialización con los IDs reales de los cursos
                ContentOperationResult resultado = contentManager.crearEspecializacion(
                    datosGenerados.idEmpresa,
                    datosGenerados.nombreEmpresa,
                    datosGenerados.titulo,
                    datosGenerados.descripcion,
                    datosGenerados.idsCursos,
                    datosGenerados.precio,
                    nuevoId,
                    RawActividadData::categoriaToString(datosGenerados.categoria)
                );

                if (nuevoId != -1) {
                    SessionManager::getInstance().getActividadesController().anadirActividad(TipoActividad::ESPECIALIZACION, nuevoId);
                    int nuevoIdCurso = ContentManager::getInstance().getNextIdCurso();
                    for (int i = nuevoIdCurso - 4; i < nuevoIdCurso; i++) {
                        SessionManager::getInstance().getActividadesController().anadirActividad(TipoActividad::CURSO, i);
                    }
                }

            }
            

            SessionManager::getInstance().logout();
        }

    }
}

inline std::vector<std::string> GeneradorDatos::generarNombres(int n) {
    // Backtracking
    std::vector<std::string> nombres;
	anadirNombresImportantes(nombres);

    std::string current = "";
    for (int i = 0; i < n; i++) {
        current += 'a';
    }

    auto backtrack = [&](auto&& self, int pos) -> void {
        if (pos == n) {
            std::cout << current;
            nombres.push_back(current);
            return;
        }
        for (char c = 'a'; c <= 'z'; c++) {
            current[pos] = c;
            self(self, pos + 1);
        }
        };

    backtrack(backtrack, 0);
    return nombres;
}

inline std::vector<std::string> GeneradorDatos::generarNombres() {
	return generarNombres(2);
}

inline void GeneradorDatos::generarUsuarios(int n) {
    std::vector<std::string> nombres = generarNombres(n);
    

    for (std::string& nombre : nombres) {
		std::string email = nombre + "@gmail.com";
		std::string password = "123456";

        int longitud = n;

        for (int i = 1; i <= 2; i++) {
            bool emailNuevo = emailRepetido(email, i);
            if (emailNuevo) {
                if (email == "courclone@gmail.com") std::cout << "Pero si esta";
            }
            if (!emailNuevo) {
                
                TipoUsuario tipoUsuarioActual = static_cast<TipoUsuario>(i);
                int cantidadAhora = FilesManager::getInstance().cantidadUsuarios(tipoUsuarioActual);
                Usuario nuevoUsuario(cantidadAhora, tipoUsuarioActual, nombre, email, password);
                nuevoUsuario.guardar();
            }

        }
    }

}

inline void GeneradorDatos::generarTodo() {
    generarUsuarios(2);
    generarActividad({ "courclone", "platclone" });
}

#endif // COURSERACLONE_HEADERS_UTILS_GENERADORDATOS_HPP
