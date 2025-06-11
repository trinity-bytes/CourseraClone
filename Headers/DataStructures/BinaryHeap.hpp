#ifndef COURSERACLONE_DATASTRUCTURES_BINARYHEAP_HPP
#define COURSERACLONE_DATASTRUCTURES_BINARYHEAP_HPP

#include <vector>
#include <algorithm>

template <typename T>
struct DefaultComparator {
    bool operator()(const T& _a, const T& _b) const {
        return _a < _b;
    }
};

// Implementación de montículo binario genérico
template <typename T, typename Comparator = DefaultComparator<T>>
class BinaryHeap {
private:
    std::vector<T> _elementos;
    Comparator _comparator;

    int _padre(int _i) const { return (_i - 1) / 2; }
    int _izquierdo(int _i) const { return 2 * _i + 1; }
    int _derecho(int _i) const { return 2 * _i + 2; }

    void _heapifyArriba(int _i) {
        while (_i != 0 && _comparator(_elementos[_padre(_i)], _elementos[_i])) {
            std::swap(_elementos[_i], _elementos[_padre(_i)]);
            _i = _padre(_i);
        }
    }

    void _heapifyAbajo(int _i) {
        int izq = _izquierdo(_i);
        int der = _derecho(_i);
        int extremo = _i;

        if (izq < size() && _comparator(_elementos[extremo], _elementos[izq])) {
            extremo = izq;
        }
        if (der < size() && _comparator(_elementos[extremo], _elementos[der])) {
            extremo = der;
        }

        if (extremo != _i) {
            std::swap(_elementos[_i], _elementos[extremo]);
            _heapifyAbajo(extremo);
        }
    }

public:
    BinaryHeap(Comparator _comp = Comparator()) : _comparator(_comp) {}

    void insertar(const T& _valor) {
        _elementos.push_back(_valor);
        _heapifyArriba(_elementos.size() - 1);
    }

    T extraerRaiz() {
        if (_elementos.empty()) {
            return T();
        }
        T raizVal = _elementos[0];
        _elementos[0] = _elementos.back();
        _elementos.pop_back();
        if (!_elementos.empty()) {
            _heapifyAbajo(0);
        }
        return raizVal;
    }

    const T& obtenerRaiz() const {
        if (_elementos.empty()) {
            static T defaultValue = T();
            return defaultValue;
        }
        return _elementos[0];
    }

    void eliminarRaiz() {
        if (_elementos.empty()) return;
        _elementos[0] = _elementos.back();
        _elementos.pop_back();
        if (!_elementos.empty()) {
            _heapifyAbajo(0);
        }
    }

    const std::vector<T>& getElementos() const {
        return _elementos;
    }

    bool estaVacio() const {
        return _elementos.empty();
    }

    std::size_t size() const {
        return _elementos.size();
    }

    void ordenar() {
        std::sort(_elementos.begin(), _elementos.end(), _comparator);
    }
};

#endif // COURSERACLONE_DATASTRUCTURES_BINARYHEAP_HPP