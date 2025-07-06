// filepath: Headers/Entities/Estadistica.hpp
// Header que representa los datos de las estadisticas de una empresa

#ifndef COURSERACLONE_ENTITIES_ESTADISTICA_HPP
#define COURSERACLONE_ENTITIES_ESTADISTICA_HPP

class Estadistica
{
private:
    int totalCursos;
    int totalEspecializaciones;
    int totalInscripciones;
    double ingresosTotal;

public:
    
    // Getters
	inline int getTotalCursos() const { return totalCursos; }
	inline int getTotalEspecializaciones() const { return totalEspecializaciones; }
	inline int getTotalInscripciones() const { return totalInscripciones; }
	inline double getIngresosTotal() const { return ingresosTotal; }
	// Setters
	inline void setTotalCursos(int value) { totalCursos = value; }
	inline void setTotalEspecializaciones(int value) { totalEspecializaciones = value; }
	inline void setTotalInscripciones(int value) { totalInscripciones = value; }
	inline void setIngresosTotal(double value) { ingresosTotal = value; }

};

#endif COURSERACLONE_ENTITIES_ESTADISTICA_HPP
