#ifndef COURSERACLONE_DATASTRUCTURES_HASHTABLE_HPP
#define COURSERACLONE_DATASTRUCTURES_HASHTABLE_HPP

#include <unordered_map>
#include <iostream>

// Inserta un elemento en el unordered_map
template <typename K, typename T>
void insert(std::unordered_map<K, T>& table, K key, const T& value) {
    table[key] = value;
}

// Busca un elemento por clave
template <typename K, typename T>
bool find(const std::unordered_map<K, T>& table, K key, T& value) {
    auto it = table.find(key);
    if (it != table.end()) {
        value = it->second;
        return true;
    }
    return false;
}

// Limpia la tabla
template <typename K, typename T>
void clear(std::unordered_map<K, T>& table) {
    table.clear();
}

// Devuelve el tamaño
template <typename K, typename T>
size_t size(const std::unordered_map<K, T>& table) {
    return table.size();
}


#endif // COURSERACLONE_DATASTRUCTURES_HASHTABLE_HPP