#pragma once
template <typename V>
class HashEntity {
private:
    int key;
    V value;
public:
    HashEntity(int key, V value) : key(key), value(value) {}

    int getKey() const { return key; }
    const V& getValue() const { return value; }
};