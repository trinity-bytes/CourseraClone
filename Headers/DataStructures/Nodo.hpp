#ifndef COURSERACLONE_DATASTRUCTURES_NODO_HPP
#define COURSERACLONE_DATASTRUCTURES_NODO_HPP

#include <utility>

template <typename T>
struct Nodo
{
    T data;
    Nodo* next;
    
    // Constructor con parametro (lvalue)
    explicit Nodo(const T& _valor) : data(_valor), next(nullptr) {}

    // Constructor con parametro (rvalue)
    explicit Nodo(T&& _valor) : data(std::move(_valor)), next(nullptr) {}

    // Constructor por defecto
    Nodo() : data(T()), next(nullptr) {}
};

#endif // COURSERACLONE_DATASTRUCTURES_NODO_HPP