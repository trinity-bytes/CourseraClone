// filepath: Headers/DataStructures/Stack.hpp
// Pila genérica implementada con lista enlazada

#ifndef COURSERACLONE_DATASTRUCTURES_STACK_HPP
#define COURSERACLONE_DATASTRUCTURES_STACK_HPP

// Includes del sistema
#include <stdexcept>
#include <vector>

// Includes del proyecto
#include "Nodo.hpp"
#include "LinkedList.hpp"

template <typename T>
class Stack
{
private:
    Nodo<T>* _head;
    int _tamano;

private:
    void eliminarDatos()
    {
        while (_head)
        {
            Nodo<T>* actual = _head;
            _head = _head->next;
            delete actual;
        }
    }

public:
    // Constructor y destructor
    Stack() : _head(nullptr), _tamano(0) {}
    
    ~Stack()
    {
        eliminarDatos();
    }

    // Métodos de acceso
    T get(int _indice) const
    {
        if (_indice < 0 || _indice >= _tamano)
        {
            throw std::out_of_range("Índice fuera de rango en Stack::get");
        }
        
        Nodo<T>* actual = _head;
        for (int i = 0; i < _indice; ++i)
        {
            actual = actual->next;
        }
        return actual->data;
    }

    template <typename KeyType, typename Predicado>
    T& buscarPorClave(KeyType _clave, Predicado _predicado) const
    {
        Nodo<T>* actual = _head;

        while (actual)
        {
            if (_predicado(actual->data) == _clave)
            {
                return actual->data;
            }
            actual = actual->next;
        }

    }

    int getTamano() const
    {
        return _tamano;
    }
    // Operaciones básicas de pila
    void push(const T& _valor)
    {
        Nodo<T>* nuevoNodo = new Nodo<T>(_valor);
        nuevoNodo->next = _head;
        _head = nuevoNodo;
        _tamano++;
    }

    void pop()
    {
        if (_head == nullptr) return;
        
        Nodo<T>* actual = _head;
        _head = _head->next;
        delete actual;
        _tamano--;
    }

    T top() const
    {
        if (_head == nullptr) return T();
        return _head->data;
    }

    void clear()
    {
        eliminarDatos();
        _head = nullptr;
        _tamano = 0;
    }

    bool estaVacio() const
    {
        return _tamano == 0;
    }
    // Operaciones avanzadas
    bool eliminarPosicion(int _posicion)
    {
        if (_posicion < 0 || _posicion >= _tamano || _head == nullptr)
        {
            return false;
        }

        // Caso especial: eliminar el primer elemento
        if (_posicion == 0) {
            Nodo<T>* temp = _head;
            _head = _head->next;
            delete temp;
            _tamano--;
            return true;
        }

        // Para posiciones mayores a 0
        Nodo<T>* actual = _head;
        Nodo<T>* anterior = nullptr;
        
        // Avanzar hasta la posición deseada
        for (int i = 0; i < _posicion && actual != nullptr; ++i) {
            anterior = actual;
            actual = actual->next;
        }

        // Si llegamos a la posición correcta, eliminar el nodo
        if (actual != nullptr) {
            anterior->next = actual->next;
            delete actual;
            _tamano--;
            return true;
        }

        return false;
    }

    // Filtrar elementos usando predicado
    template <typename KeyType, typename Predicado>
    Stack<T> filtrarPorClaves(std::vector<KeyType>& _claves, Predicado _predicado) const
    {
        std::vector<T> datos;
        Nodo<T>* actual = _head;
        
        while (actual)
        {
            for (const auto& clave : _claves)
            {
                if (_predicado(actual->data, clave))
                {
                    datos.push_back(actual->data);
                    break;
                }
            }
            actual = actual->next;
        }
        
        // Devolver como Stack en orden inverso
        Stack<T> resultado;
        for (auto it = datos.rbegin(); it != datos.rend(); ++it)
        {
            resultado.push(*it);
        }
        return resultado;
    }

    void cargarDesdeLista(const LinkedList<T>& _lista)
    {
        clear();
        
        // Extraer valores de la lista
        std::vector<T> valores = _lista.extraerDato([](const T& valor) { return valor; });
        
        // Apilar en orden inverso para preservar orden original
        for (auto it = valores.rbegin(); it != valores.rend(); ++it)
        {
            push(*it);
        }
    }
};

#endif // COURSERACLONE_DATASTRUCTURES_STACK_HPP