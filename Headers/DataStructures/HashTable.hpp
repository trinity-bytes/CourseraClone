#ifndef COURSERACLONE_DATASTRUCTURES_HASHTABLE_HPP
#define COURSERACLONE_DATASTRUCTURES_HASHTABLE_HPP

#include <iostream>
#include "HashEntity.hpp"

// Implementación de tabla hash con resolución de colisiones por prueba lineal
#include <unordered_map>  

template <typename K,typename T>
class HashTable {
private:
    std::unordered_map<K, T> table;

public:
    // Inserta un elemento en la tabla hash  
    void insert(K key, const T& value) {
        table[key] = value;
    }

    // Busca un elemento por clave  
    bool find(K key, T& value) const {
		auto it = table.find(key);
        if (it != table.end()) {
            value = it->second;
            return true;
        }
        return false;
    }

    // Limpia todos los elementos de la tabla hash  
    void clear() {
        table.clear();
    }

    // Devuelve el tamaño de la tabla hash  
    size_t size() const {
        return table.size();
    }

    bool erase(int _key) {
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

    const T* buscar(int _key) const {
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