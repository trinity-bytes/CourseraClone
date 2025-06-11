// filepath: Headers/DataStructures/Nodo.hpp
// Nodo generico para estructuras de datos enlazadas

#ifndef COURSERACLONE_DATASTRUCTURES_NODO_HPP
#define COURSERACLONE_DATASTRUCTURES_NODO_HPP

template <typename T>
struct Nodo
{
    T data;
    Nodo* next;
    
    // Constructor con parametro
    explicit Nodo(const T& _valor) : data(_valor), next(nullptr) {}
    
    // Constructor por defecto
    Nodo() : data(T()), next(nullptr) {}
};

#endif // COURSERACLONE_DATASTRUCTURES_NODO_HPP