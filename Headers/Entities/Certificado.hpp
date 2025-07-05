// filepath: Headers/Entities/Certificado.hpp
// Descripcion: Clase que representa el certificado de una actividad

#ifndef COURSERACLONE_ENTITIES_CERTIFICADO_HPP
#define COURSERACLONE_ENTITIES_CERTIFICADO_HPP

#include <iostream>
#include <sstream>
#include <iomanip>
#include "../Types/ActividadTypes.hpp"
#include "../Types/InscripcionTypes.hpp"
#include "../Utils/DateTime.hpp"

// Clase que representa un certificado
class Certificado {
private:
    int id;
    std::string nombreCurso;
    std::string tipoCurso; // "Curso" o "Especialización"
    std::string nombreEstudiante;
    std::string instructor;
    std::string fechaFinalizacion;
    std::string fechaEmision;
    double calificacion;
    std::string idCertificado;
    int duracionHoras;
    std::string categoria;
    bool esEspecializacion;

public:
    
    Certificado(int _id, std::string _nombreEstudiante) :
        id(_id), nombreEstudiante(_nombreEstudiante),
        tipoCurso(""), instructor(""), fechaFinalizacion(""),
        fechaEmision(""), calificacion(0.0), idCertificado(""),
        duracionHoras(0), categoria(""), esEspecializacion(false) {}

    Certificado(int _id, std::string _nombreCurso, std::string _tipoCurso, std::string _nombreEstudiante,
        std::string _instructor, std::string _fechaEmision, std::string _fechaFinalizacion,
        double _calificacion, std::string _idCertificado, int _duracionHoras,
        std::string _categoria, bool _esEspecializacion
	) : id(_id), nombreCurso(_nombreCurso), tipoCurso(_tipoCurso),
		nombreEstudiante(_nombreEstudiante), instructor(_instructor),
		fechaEmision(_fechaEmision), fechaFinalizacion(_fechaFinalizacion),
		calificacion(_calificacion), idCertificado(_idCertificado),
		duracionHoras(_duracionHoras), categoria(_categoria),
		esEspecializacion(_esEspecializacion) {
	}

    void insertarDatosCurso(RawCursoData cursoData) {
        nombreCurso = cursoData.titulo;
        tipoCurso = "Curso";
        instructor = cursoData.instructor;
        categoria = RawActividadData::categoriaToString(cursoData.categoria);
        duracionHoras = cursoData.cantidadClases * 2;
        esEspecializacion = false;
    }

    void insertarDatosEspecializacion(RawEspecializacionData especializacionData) {
        nombreCurso = especializacionData.titulo;
        tipoCurso = "Especializacion";
        instructor = "Equipo de " + especializacionData.nombreEmpresa;
        categoria = RawActividadData::categoriaToString(especializacionData.categoria);
        duracionHoras = especializacionData.duracionEstimada * 8;
        esEspecializacion = true;
    }

    void insertarDatosInscripcion(InscripcionBinaria ins) {
        calificacion = ins.progreso;
        fechaEmision = std::string(ins.fechaInicio, strnlen(ins.fechaInicio, MAX_DATE_LEN_INS));
        fechaFinalizacion = std::string(ins.fechaFinal, strnlen(ins.fechaFinal, MAX_DATE_LEN_INS));
    }

    void generarIdCertificado() {
        std::ostringstream oss;
        oss << "CERT" << std::setfill('0') << std::setw(3) << id
            << "-" << (esEspecializacion ? "ESP" : "CUR") << "-" << DateTime::now().getYear();
        idCertificado = oss.str();
    }

    void setNombre(std::string nombre) {
        nombreEstudiante = nombre;
    }

    // Getters
	inline int getId() const {
		return id;
	}
	inline std::string getNombreCurso() const {
		return nombreCurso;
	}
	inline std::string getTipoCurso() const {
		return tipoCurso;
	}
	inline std::string getNombreEstudiante() const {
		return nombreEstudiante;
	}
	inline std::string getInstructor() const {
		return instructor;
	}
	inline std::string getFechaFinalizacion() const {
		return fechaFinalizacion;
	}
	inline std::string getFechaEmision() const {
		return fechaEmision;
	}
	inline double getCalificacion() const {
		return calificacion;
	}
	inline std::string getIdCertificado() const {
		return idCertificado;
	}
	inline int getDuracionHoras() const {
		return duracionHoras;
	}
	inline std::string getCategoria() const {
		return categoria;
	}
	inline bool getEsEspecializacion() const {
		return esEspecializacion;
	}


};

#endif // COURSERACLONE_ENTITIES_CERTIFICADO_HPP