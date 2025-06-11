#ifndef COURSERACLONE_DATASTRUCTURES_HASHTABLE_HPP
#define COURSERACLONE_DATASTRUCTURES_HASHTABLE_HPP

#include <iostream>
#include "HashEntity.hpp"

// Implementación de tabla hash con resolución de colisiones por prueba lineal
template <typename V>
class HashTable {
private:
    HashEntity<V>** _tabla;
    int _tableSize;
    int _numElementos;

public:
    HashTable(int _size = 128) {
        _tableSize = _size;
        _tabla = new HashEntity<V>*[_tableSize];
        for (int i = 0; i < _tableSize; ++i)
            _tabla[i] = nullptr;
        _numElementos = 0;
    }

    ~HashTable() {
        for (int i = 0; i < _tableSize; ++i)
            if (_tabla[i] != nullptr)
                delete _tabla[i];
        delete[] _tabla;
    }

    int hash(int _key) const {
        return _key % _tableSize;
    }

    void insertar(int _key, V _value) {
        if (_numElementos == _tableSize) return;

        int index = hash(_key);
        int step = 0;

        while (_tabla[index] != nullptr && _tabla[index]->getKey() != _key) {
            index = (hash(_key) + ++step) % _tableSize;
        }

        if (_tabla[index] != nullptr)
            delete _tabla[index];

        _tabla[index] = new HashEntity<V>(_key, _value);
        _numElementos++;
    }

    bool eliminar(int _key) {
        int index = hash(_key);
        int step = 0;

        while (_tabla[index] != nullptr) {
            if (_tabla[index]->getKey() == _key) {
                delete _tabla[index];
                _tabla[index] = nullptr;
                _numElementos--;
                return true;
            }
            index = (hash(_key) + ++step) % _tableSize;
        }
        return false;
    }

    const V* buscar(int _key) const {
        int index = hash(_key);
        int step = 0;

        while (_tabla[index] != nullptr) {
            if (_tabla[index]->getKey() == _key)
                return &_tabla[index]->getValue();
            index = (hash(_key) + ++step) % _tableSize;
        }
        return nullptr;
    }

    void mostrar() const {
        for (int i = 0; i < _tableSize; ++i) {
            if (_tabla[i] != nullptr) {
                std::cout << "[" << _tabla[i]->getKey() << "] ";
            }
        }
    }
};

#endif // COURSERACLONE_DATASTRUCTURES_HASHTABLE_HPP