#ifndef COURSERACLONE_DATAESTRUCTURES_PRIORITYQUEUE_HPP
#define COURSERACLONE_DATAESTRUCTURES_PRIORITYQUEUE_HPP

#include "BinaryHeap.hpp"
#include "LinkedList.hpp"
#include <algorithm>
#include <vector>

template <typename T, typename Comparator = DefaultComparator<T>>
class PriorityQueue {
private:
    BinaryHeap<T, Comparator> _monticulo;
    int _tamano;
    int _tamanoMaximo;

public:
    PriorityQueue(int _tamanoMaximo = 3, Comparator _comp = Comparator()) 
        : _tamano(0), _tamanoMaximo(_tamanoMaximo), _monticulo(_comp) {}

    void enqueue(const T& _valor) {
        _monticulo.insertar(_valor);
        _tamano++;
    }

    T dequeue() {
        if (estaVacio()) return T();
        _tamano--;
        return _monticulo.extraerRaiz();
    }

    const T& front() const {
        if (estaVacio()) {
            static T defaultValue = T();
            return defaultValue;
        }
        return _monticulo.obtenerRaiz();
    }

    ~PriorityQueue() {
        while (!_monticulo.estaVacio()) {
            _monticulo.extraerRaiz();
        }
    }

    void eliminarExceso() {
        while (_tamano > _tamanoMaximo) {
            _monticulo.eliminarRaiz();
            _tamano--;
        }
    }

    void llenarDesde(LinkedList<T>& _lista) {
        Nodo<T>* current = _lista.getHead();
        while (current != nullptr) {
            enqueue(current->_data);
            current = current->_next;
        }
        _tamano = _lista.getTamano();
        eliminarExceso();
    }

    template <typename ValorTipo, typename MetodoConseguir>
    std::vector<ValorTipo> extraerDato(MetodoConseguir _requerido) const {
        const std::vector<T>& clasesBase = _monticulo.getElementos();
        std::vector<ValorTipo> resultado;
        for (std::size_t i = 0; i < _monticulo.size(); i++) {
            resultado.push_back(_requerido(clasesBase[i]));
        }
        return resultado;
    }

    const std::vector<T>& getElementos() const {
        return _monticulo.getElementos();
    }

    void ordenar() {
        _monticulo.ordenar();
    }

    std::vector<T> getElementosOrdenados() const {
        std::vector<T> elementos = _monticulo.getElementos();
        std::sort(elementos.begin(), elementos.end(), Comparator());
        return elementos;
    }

    int getTamano() const {
        return _tamano;
    }

    bool estaVacio() const {
        return _tamano == 0;
    }
};

#endif // COURSERACLONE_DATAESTRUCTURES_PRIORITYQUEUE_HPP