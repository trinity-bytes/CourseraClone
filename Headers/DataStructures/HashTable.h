#pragma once
#include "HashEntity.h"

template <typename V>
class HashTable {
private:
    HashEntity<V>** tabla;
    int TABLE_SIZE;
    int numElementos;

public:
    HashTable(int size = 128) {
        TABLE_SIZE = size;
        tabla = new HashEntity<V>*[TABLE_SIZE];
        for (int i = 0; i < TABLE_SIZE; ++i)
            tabla[i] = nullptr;
        numElementos = 0;
    }

    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; ++i)
            if (tabla[i] != nullptr)
                delete tabla[i];
        delete[] tabla;
    }

    int hash(int key) const {
        return key % TABLE_SIZE;
    }

    void insertar(int key, V value) {
        if (numElementos == TABLE_SIZE) return;

        int index = hash(key);
        int step = 0;

        while (tabla[index] != nullptr && tabla[index]->getKey() != key) {
            index = (hash(key) + ++step) % TABLE_SIZE;
        }

        if (tabla[index] != nullptr)
            delete tabla[index]; // reemplaza si existe

        tabla[index] = new HashEntity<V>(key, value);
        numElementos++;
    }

    bool eliminar(int key) {
        int index = hash(key);
        int step = 0;

        while (tabla[index] != nullptr) {
            if (tabla[index]->getKey() == key) {
                delete tabla[index];
                tabla[index] = nullptr;
                numElementos--;
                return true;
            }
            index = (hash(key) + ++step) % TABLE_SIZE;
        }
        return false;
    }

    const V* buscar(int key) {
        int index = hash(key);
        int step = 0;

        while (tabla[index] != nullptr) {
            if (tabla[index]->getKey() == key)
                return &tabla[index]->getValue();
            index = (hash(key) + ++step) % TABLE_SIZE;
        }
        return nullptr;
    }

    void mostrar() const {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (tabla[i] != nullptr) {
                cout << "[" << tabla[i]->getKey() << "] ";
            }
        }
    }
};