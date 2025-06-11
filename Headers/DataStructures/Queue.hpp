// filepath: Headers/DataStructures/Queue.hpp
// Cola genérica implementada con lista enlazada

#ifndef COURSERACLONE_DATASTRUCTURES_QUEUE_HPP
#define COURSERACLONE_DATASTRUCTURES_QUEUE_HPP

// Includes del sistema
#include <stdexcept>

// Includes del proyecto
#include "Nodo.hpp"

template <typename T>
class Queue
{
private:
    Nodo<T>* _head;
    Nodo<T>* _tail;
    int _tamano;

public:
    // Constructor y destructor
    Queue() : _head(nullptr), _tail(nullptr), _tamano(0) {}
    
    ~Queue()
    {
        while (_head)
        {
            Nodo<T>* actual = _head;
            _head = _head->next;
            delete actual;
        }
    }

    // Getters
    int getTamano() const
    {
        return _tamano;
    }

    bool estaVacio() const
    {
        return _tamano == 0;
    }

    // Operaciones básicas de cola
    void enqueue(const T& _valor)
    {
        Nodo<T>* nuevoNodo = new Nodo<T>(_valor);
        if (_tail)
        {
            _tail->next = nuevoNodo;
        }
        else
        {
            _head = nuevoNodo;
        }
        _tail = nuevoNodo;
        _tamano++;
    }

    void dequeue()
    {
        if (_head == nullptr) return;
        
        Nodo<T>* actual = _head;
        _head = _head->next;
        
        if (_head == nullptr)
        {
            _tail = nullptr;
        }
        
        delete actual;
        _tamano--;
    }

    T front() const
    {
        if (_head == nullptr)
        {
            throw std::runtime_error("Cola vacía: No hay primer elemento");
        }
        return _head->data;
    }

    void clear()
    {
        while (!estaVacio())
        {
            dequeue();
        }
    }
};

#endif // COURSERACLONE_DATASTRUCTURES_QUEUE_HPP