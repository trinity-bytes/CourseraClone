// filepath: Headers/DataStructures/BinarySearchTree.hpp
// Árbol binario de búsqueda genérico con clave-valor

#ifndef COURSERACLONE_DATASTRUCTURES_BINARYSEARCHTREE_HPP
#define COURSERACLONE_DATASTRUCTURES_BINARYSEARCHTREE_HPP

template <typename KeyType, typename ValueType>
class BinarySearchTree
{
private:
    struct Nodo
    {
        KeyType clave;
        ValueType valor;
        Nodo* _izquierdo;
        Nodo* _derecho;
        
        Nodo(const KeyType& _clave, const ValueType& _valor) 
            : clave(_clave), valor(_valor), _izquierdo(nullptr), _derecho(nullptr) {}
    };
    
    Nodo* _raiz;

    // Insertar nodo de forma recursiva
    Nodo* insertarRecursivo(Nodo* _nodo, const KeyType& _clave, const ValueType& _valor)
    {
        if (!_nodo)
        {
            return new Nodo(_clave, _valor);
        }
        
        if (_clave < _nodo->clave)
        {
            _nodo->_izquierdo = insertarRecursivo(_nodo->_izquierdo, _clave, _valor);
        }
        else if (_clave > _nodo->clave)
        {
            _nodo->_derecho = insertarRecursivo(_nodo->_derecho, _clave, _valor);
        }
        else
        {
            // Claves duplicadas: actualizar valor
            _nodo->valor = _valor;
        }
        return _nodo;
    }

    // Buscar nodo de forma recursiva
    Nodo* buscarRecursivo(Nodo* _nodo, const KeyType& _clave) const
    {
        if (!_nodo || _nodo->clave == _clave)
        {
            return _nodo;
        }
        
        if (_clave < _nodo->clave)
        {
            return buscarRecursivo(_nodo->_izquierdo, _clave);
        }
        
        return buscarRecursivo(_nodo->_derecho, _clave);
    }

    // Destruir nodos de forma recursiva
    void destruirRecursivo(Nodo* _nodo)
    {
        if (_nodo)
        {
            destruirRecursivo(_nodo->_izquierdo);
            destruirRecursivo(_nodo->_derecho);
            delete _nodo;
        }
    }

public:
    // Constructor y destructor
    BinarySearchTree() : _raiz(nullptr) {}
    
    ~BinarySearchTree()
    {
        destruirRecursivo(_raiz);
    }

    // Métodos públicos
    void insertar(const KeyType& _clave, const ValueType& _valor)
    {
        _raiz = insertarRecursivo(_raiz, _clave, _valor);
    }

    ValueType* buscar(const KeyType& _clave) const
    {
        Nodo* encontrado = buscarRecursivo(_raiz, _clave);
        return encontrado ? &(encontrado->valor) : nullptr;
    }

    bool existe(const KeyType& _clave) const
    {
        return buscar(_clave) != nullptr;
    }
};

#endif // COURSERACLONE_DATASTRUCTURES_BINARYSEARCHTREE_HPP