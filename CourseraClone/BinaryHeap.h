#pragma once
#include <vector> 

template <typename T>
struct comparadorDefecto {
    bool operator()(T& a, T& b) {
        return a < b;
    }
};

template <typename T, typename Comparador = comparadorDefecto<T> > // Max-heap por defecto 
class BinaryHeap {

private:
    vector<T> elementos;
    Comparador comparador;

    int padre(int i) { return (i - 1) / 2; }
    int izquierdo(int i) { return 2 * i + 1; }
    int derecho(int i) { return 2 * i + 2; }

    void heapifyArriba(int i) { // Volvemos al padre y restauramos valores
        while (i != 0 && comparador(elementos[padre(i)], elementos[i])) {
            T temp = elementos[i];
            elementos[i] = elementos[padre(i)];
            elementos[padre(i)] = temp;
            i = padre(i);
        }
    }

    void heapifyAbajo(int i) {
        int izq = izquierdo(i);
        int der = derecho(i);
        int extremo = i;

        if (izq < tamano() && comparador(elementos[extremo], elementos[izq])) {
            extremo = izq;
        }
        if (der < tamano() && comparador(elementos[extremo], elementos[der])) {
            extremo = der;
        }

        if (extremo != i) {
            T temp = elementos[i];
            elementos[i] = elementos[extremo];
            elementos[extremo] = temp;
            heapifyAbajo(extremo);
        }
    }

public:
    BinaryHeap(Comparador comp = Comparador()) : comparador(comp) {}

    void insertar(T valor) {
        elementos.push_back(valor); // insertamos
        heapifyArriba(elementos.size() - 1); // ordenamos
    }

    T extraerRaiz() {
        if (elementos.empty()) {
            return T();
        }
        T raiz_val = elementos[0];
        elementos[0] = elementos.back();
        elementos.pop_back();
        if (!elementos.empty()) {
            heapifyAbajo(0);
        }
        return raiz_val;
    }

    T obtenerRaiz() {
        if (elementos.empty()) {
            return T();
        }
        return elementos[0];
    }

    void eliminarRaiz() {
        if (elementos.empty()) return;
        elementos.pop_back();
        if (!elementos.empty()) heapifyAbajo(0);
    }

    vector<T> getElementos() {
        return elementos;
    }

    bool estaVacio() {
        return elementos.empty();
    }

    int tamano() {
        return elementos.size();
    }

    void ordenar() {
        sort(elementos.begin(), elementos.end(), comparador);
    }
};