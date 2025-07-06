// filepath: ./Headers/DataStructures/Nodo.hpp
// description: Cabecera para la estructura Nodo

#ifndef COURSERACLONE_DATASTRUCTURES_NODO_HPP
#define COURSERACLONE_DATASTRUCTURES_NODO_HPP

template <typename T>
struct Nodo
{
    T data;
    Nodo* next;

    // Constructor con parametro (solo acepta rvalue/movimiento)
    explicit Nodo(T valor) : data(std::move(valor)), next(nullptr) {}

    // Constructor por defecto
    Nodo() : data(T()), next(nullptr) {}
};

#endif // COURSERACLONE_DATASTRUCTURES_NODO_HPP