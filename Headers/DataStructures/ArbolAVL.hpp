#ifndef COURSERACLONE_DATASTRUCTURES_ARBOLAVL_HPP
#define COURSERACLONE_DATASTRUCTURES_ARBOLAVL_HPP
#include "NodoAVL.hpp"

// Árbol AVL autobalanceado genérico
template<typename T>
class ArbolAVL {
private:
    NodoAVL<T>* raiz;
    void (*_procesar)(T); // Función para procesar (por defecto imprimir)

    // Función estática por defecto para imprimir un elemento
    static void _imprimirPorDefecto(T valor) {
        std::cout << " " << valor;
    }

    // Altura de un nodo (nullptr -> 0)
    int _altura(NodoAVL<T>* nodo) {
        return nodo ? nodo->altura : 0;
    }

    // Factor de balance: altura(derecha) - altura(izquierda)
    int _factorBalance(NodoAVL<T>* nodo) {
        return _altura(nodo->der) - _altura(nodo->izq);
    }

    // Rotación simple a la izquierda
    void _rotarIzquierda(NodoAVL<T>*& nodo) {
        NodoAVL<T>* r = nodo->der;
        NodoAVL<T>* rl = r->izq;
        r->izq = nodo;
        nodo->der = rl;
        nodo->altura = 1 + std::max(_altura(nodo->izq), _altura(nodo->der));
        r->altura = 1 + std::max(_altura(r->izq), _altura(r->der));
        nodo = r;
    }

    // Rotación simple a la derecha
    void _rotarDerecha(NodoAVL<T>*& nodo) {
        NodoAVL<T>* l = nodo->izq;
        NodoAVL<T>* lr = l->der;
        l->der = nodo;
        nodo->izq = lr;
        nodo->altura = 1 + std::max(_altura(nodo->izq), _altura(nodo->der));
        l->altura = 1 + std::max(_altura(l->izq), _altura(l->der));
        nodo = l;
    }

    // Aplica las rotaciones necesarias para balancear el subárbol
    void _balancear(NodoAVL<T>*& nodo) {
        if (!nodo) return;
        int fb = _factorBalance(nodo);
        if (fb > 1) {
            if (_factorBalance(nodo->der) < 0)
                _rotarDerecha(nodo->der);
            _rotarIzquierda(nodo);
        }
        else if (fb < -1) {
            if (_factorBalance(nodo->izq) > 0)
                _rotarIzquierda(nodo->izq);
            _rotarDerecha(nodo);
        }
        else {
            // Actualiza altura si sin rotación
            nodo->altura = 1 + std::max(_altura(nodo->izq), _altura(nodo->der));
        }
    }

    // Inserta recursivamente y rebalancea
    bool _insertar(NodoAVL<T>*& nodo, const T& valor) {
        if (!nodo) {
            nodo = new NodoAVL<T>(valor);
            return true;
        }
        if (valor < nodo->elemento) {
            if (!_insertar(nodo->izq, valor)) return false;
        }
        else if (valor > nodo->elemento) {
            if (!_insertar(nodo->der, valor)) return false;
        }
        else {
            return false; // No se permiten duplicados
        }
        _balancear(nodo);
        return true;
    }

	// Busca un valor en el árbol
    bool _buscar(NodoAVL<T>* nodo, const T& valor) const {
        if (!nodo) return false;
        if (valor == nodo->elemento)
            return true;
        else if (valor < nodo->elemento)
            return _buscar(nodo->izq, valor);
        else
            return _buscar(nodo->der, valor);
    }

    // Recorrido in-order de elementos
    void _inOrden(NodoAVL<T>* nodo) {
        if (!nodo) return;
        _inOrden(nodo->izq);
        _procesar(nodo->elemento);
        _inOrden(nodo->der);
    }

    // Recorrido in-order de alturas
    void _inOrdenAlturas(NodoAVL<T>* nodo) {
        if (!nodo) return;
        _inOrdenAlturas(nodo->izq);
        _procesar(nodo->altura);
        _inOrdenAlturas(nodo->der);
    }

public:
    // Constructor: recibe opcionalmente una función para imprimir (o usa la por defecto)
    ArbolAVL(void (*funcImprimir)(T) = _imprimirPorDefecto)
        : raiz(nullptr), _procesar(funcImprimir) {
    }

    // Inserta un nuevo valor en el árbol
    bool Insertar(const T& valor) {
        return _insertar(raiz, valor);
    }

    // Imprime los elementos en orden
    void inOrden() {
        _inOrden(raiz);
    }

	// Busca un valor en el árbol
    bool Buscar(const T& valor) const {
        return _buscar(raiz, valor);
    }

    // Imprime las alturas de los nodos en orden
    void inOrdenH() {
        _inOrdenAlturas(raiz);
    }

    // TODO: implementar destructor para liberar memoria
};

#endif // COURSERACLONE_DATASTRUCTURES_ARBOLAVL_HPP
