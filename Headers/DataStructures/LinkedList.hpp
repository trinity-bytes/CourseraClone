// filepath: Headers/DataStructures/LinkedList.hpp
// Lista enlazada genérica para cualquier tipo de dato

#ifndef COURSERACLONE_DATASTRUCTURES_LINKEDLIST_HPP
#define COURSERACLONE_DATASTRUCTURES_LINKEDLIST_HPP

// Includes del sistema
#include <vector>
#include <iterator>
#include <stdexcept>
#include <functional>
#include <memory>

// Includes del proyecto
#include "Nodo.hpp"

template <typename T>
class LinkedList 
{
private:
    Nodo<T>* _head;
    Nodo<T>* _tail;
    int _tamano;

public:
    // Clase iterador para compatibilidad con algoritmos STL
    class Iterator 
    {
    private:
        Nodo<T>* _current;

    public:
        // Typedefs requeridos para iteradores STL
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        // Constructores
        Iterator() : _current(nullptr) {}
        explicit Iterator(Nodo<T>* _ptr) : _current(_ptr) {}

        // Operadores de iterador
        T& operator*()
        {
            if (_current == nullptr)
            {
                throw std::runtime_error("Intentando desreferenciar un iterador nulo");
            }
            return _current->data;
        }

        T* operator->() 
        {
            if (_current == nullptr)
            {
                throw std::runtime_error("Intentando acceder a través de un iterador nulo");
            }            return &(_current->data);
        }

        // Operador de pre-incremento
        Iterator& operator++()
        {
            if (_current)
            {
                _current = _current->next;
            }
            return *this;
        }

        // Operador de post-incremento
        Iterator operator++(int)
        {
            Iterator temporal = *this;
            ++(*this);
            return temporal;
        }

        // Operadores de comparación
        bool operator==(const Iterator& _other) const
        {
            return _current == _other._current;
        }

        bool operator!=(const Iterator& _other) const
        {
            return _current != _other._current;
        }

        // Acceso al nodo para funcionalidades internas
        Nodo<T>* getNode() const
        {
            return _current;        }
    };

    // Constructor y destructor
    LinkedList() : _head(nullptr), _tail(nullptr), _tamano(0) {}

    ~LinkedList()
    {
        clear();
    }

    // Métodos de iteración
    Iterator begin() const
    {
        return Iterator(_head);
    }

    Iterator end() const
    {
        return Iterator(nullptr);
    }

    // Getters
    int getTamano() const
    {
        return _tamano;
    }

    Nodo<T>* getHead() const
    {
        return _head;
    }

    Nodo<T>* getTail() const
    {
        return _tail;
    }

    bool isEmpty() const
    {
        return _head == nullptr;
    }

    // Filtrar elementos usando dos comparadores
    template<typename Key, typename CompIgual, typename CompMenor>
    LinkedList<T> filtrar(std::vector<Key>& _claves, CompIgual _igual, CompMenor _menor) const
    {
        LinkedList<T> resultado;
        Nodo<T>* actual = _head;
        int indice = 0;

        while (actual != nullptr && indice < _claves.size())
        {
            if (_igual(actual->data, _claves[indice]))
            {
                resultado.agregarAlFinal(actual->data);
                actual = actual->next;
                indice++;
            }
            else if (_menor(actual->data, _claves[indice]))
            {
                actual = actual->next;
            }
            else
            {
                indice++;
            }
        }

        return resultado;
    }

    // Extraer datos usando una función de transformación
    template <typename ResultType>
    std::vector<ResultType> extraerDato(std::function<ResultType(const T&)> _transformacion) const
    {
        std::vector<ResultType> datos;
        Nodo<T>* actual = _head;
        while (actual)
        {
            datos.push_back(_transformacion(actual->data));
            actual = actual->next;
        }
        return datos;
    }

    // Métodos para agregar elementos
    void agregarAlInicio(const T& _valor)
    {
        std::unique_ptr<Nodo<T>> nuevoNodo = std::make_unique<Nodo<T>>(_valor);
        if (isEmpty())
        {
            _head = nuevoNodo.release();
            _tail = _head;
        }
        else
        {
            nuevoNodo->next = _head;
            _head = nuevoNodo.release();
        }
        _tamano++;
    }

    void agregarAlFinal(const T& _valor)
    {
        std::unique_ptr<Nodo<T>> nuevoNodo = std::make_unique<Nodo<T>>(_valor);
        if (isEmpty())
        {
            _head = nuevoNodo.release();
            _tail = _head;
        }
        else
        {
            _tail->next = nuevoNodo.release();
            _tail = _tail->next;
        }
        _tamano++;
    }

    // Métodos para eliminar elementos
    void eliminarPrimero()
    {
        if (isEmpty()) return;

        Nodo<T>* temporal = _head;
        _head = _head->next;

        if (_head == nullptr)
        {
            _tail = nullptr;
        }

        delete temporal;
        _tamano--;
    }

    void eliminarUltimo()
    {
        if (isEmpty()) return;

        if (_head == _tail)
        {
            delete _head;
            _head = nullptr;
            _tail = nullptr;
            _tamano = 0;
            return;
        }

        Nodo<T>* actual = _head;
        while (actual->next != _tail)
        {
            actual = actual->next;
        }

        delete _tail;
        _tail = actual;
        _tail->next = nullptr;
        _tamano--;
    }

    void eliminarPosicion(int _posicion)
    {
        if (isEmpty() || _posicion <= 0 || _posicion > _tamano) return;

        if (_posicion == 1)
        {
            eliminarPrimero();
            return;
        }

        if (_posicion == _tamano)
        {
            eliminarUltimo();
            return;
        }

        Nodo<T>* anterior = _head;
        for (int i = 1; i < _posicion - 1; i++)
        {
            anterior = anterior->next;
        }

        Nodo<T>* temporal = anterior->next;
        anterior->next = temporal->next;
        delete temporal;
        _tamano--;
    }

    // Eliminar un nodo específico usando iterador
    void eliminar(Iterator _iterador)
    {
        if (isEmpty()) return;

        Nodo<T>* nodoAEliminar = _iterador.getNode();

        if (nodoAEliminar == _head)
        {
            eliminarPrimero();
            return;
        }

        if (nodoAEliminar == _tail)
        {
            eliminarUltimo();
            return;
        }

        // Buscar el nodo anterior
        Nodo<T>* anterior = _head;
        while (anterior && anterior->next != nodoAEliminar)
        {
            anterior = anterior->next;
        }

        if (anterior == nullptr) return; // Nodo no encontrado

        anterior->next = nodoAEliminar->next;
        delete nodoAEliminar;
        _tamano--;
    }

    void clear()
    {
        while (!isEmpty())
        {
            eliminarPrimero();
        }
    }

    // Métodos de búsqueda
    Iterator buscar(const T& _valor) const
    {
        Nodo<T>* actual = _head;
        while (actual)
        {
            if (actual->data == _valor)
            {
                return Iterator(actual);
            }
            actual = actual->next;
        }
        return end();
    }

    T& getElemento(int pos) {
        if (_head == nullptr) return T();
        Nodo<T>* current = _head;
        int contador = 0;
        while (current != nullptr) {
            if (contador == pos) {
                return current->data;
            }
            contador++;
            current = current->next;
        }
        return T(); // Elemento no encontrado
    }

    template <typename KeyType, typename Predicado>
    int buscarPorClave(KeyType _clave, Predicado _predicado) const
    {
        Nodo<T>* actual = _head;
        int indice = 0;

        while (actual)
        {
            if (_predicado(actual->data) == _clave)
            {
                return indice;
            }
            actual = actual->next;
            indice++;
        }

        return -1;
    }

    void modificar(int _posicion, const T& _datos)
    {
        if (_head == nullptr) return;

        Nodo<T>* actual = _head;
        int contador = 1;
        while (actual != nullptr)
        {
            if (contador == _posicion)
            {
                actual->data = _datos;
                return;
            }
            contador++;
            actual = actual->next;
        }
    }

    bool contiene(const T& _valor) const
    {
        return buscar(_valor) != end();
    }

    // Acceso a elementos extremos
    T& primero()
    {
        if (isEmpty())
        {
            throw std::runtime_error("Lista vacía: No hay primer elemento");
        }
        return _head->data;
    }

    const T& primero() const
    {
        if (isEmpty())
        {
            throw std::runtime_error("Lista vacía: No hay primer elemento");
        }
        return _head->data;
    }

    T& ultimo()
    {
        if (isEmpty())
        {
            throw std::runtime_error("Lista vacía: No hay último elemento");
        }
        return _tail->data;
    }

    const T& ultimo() const
    {
        if (isEmpty())
        {
            throw std::runtime_error("Lista vacía: No hay último elemento");
        }
        return _tail->data;
    }
};

#endif // COURSERACLONE_DATASTRUCTURES_LINKEDLIST_HPP