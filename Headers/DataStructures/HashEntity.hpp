#ifndef COURSERACLONE_DATASTRUCTURES_HASHENTITY_HPP
#define COURSERACLONE_DATASTRUCTURES_HASHENTITY_HPP

// Entidad que representa un par clave-valor para la tabla hash
template <typename V>
class HashEntity {
private:
    int _key;
    V _value;

public:
    HashEntity(int _key, V _value) : _key(_key), _value(_value) {}

    int getKey() const { return _key; }
    const V& getValue() const { return _value; }
};

#endif // COURSERACLONE_DATASTRUCTURES_HASHENTITY_HPP