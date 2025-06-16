#ifndef COURSERACLONE_DATASTRUCTURES_NODOAVL_HPP
#define COURSERACLONE_DATASTRUCTURES_NODOAVL_HPP

template<typename T>
class NodoAVL {
public:
    T elemento;
    NodoAVL<T>* izq;
    NodoAVL<T>* der;
    int altura;

    // Constructor por defecto y con valor inicial
    NodoAVL() : izq(nullptr), der(nullptr), altura(0) {}
    NodoAVL(const T& valor) : elemento(valor), izq(nullptr), der(nullptr), altura(1) {}
};

#endif // COURSERACLONE_DATASTRUCTURES_NODOAVL_HPP
