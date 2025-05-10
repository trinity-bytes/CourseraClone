#pragma once

// headers propios
#include "Nodo.h"

// headers de la libreria estandar
#include <vector>
#include "iterator"
#include "stdexcept"
#include "functional"

using namespace std;

template <typename T>
class LinkedList 
{
private:
    Nodo<T>* head;
    Nodo<T>* tail;
    int tamano;

public:
    // Clase iterador para compatibilidad con algoritmos STL
    class Iterator 
    {
    private:
        Nodo<T>* current;

    public:
        // Typedefs requeridos para iteradores STL
        using iterator_category = forward_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        // Constructores
        Iterator() : current(nullptr) {}
        explicit Iterator(Nodo<T>* ptr) : current(ptr) {}

        // Operadores de iterador
        T& operator*() const {
            if (current == nullptr)
                throw std::runtime_error("Intentando desreferenciar un iterador nulo");
            return current->data;
        }

        T* operator->() const {
            if (current == nullptr)
                throw std::runtime_error("Intentando acceder a través de un iterador nulo");
            return &(current->data);
        }

        // Operador de pre-incremento
        Iterator& operator++() {
            if (current)
                current = current->next;
            return *this;
        }

        // Operador de post-incremento
        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        // Operadores de comparación
        bool operator==(const Iterator& other) const {
            return current == other.current;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }

        // Acceso al nodo (para funcionalidades internas)
        Nodo<T>* getNode() const {
            return current;
        }
    };

    // Constructor y destructor
    LinkedList() : head(nullptr), tail(nullptr), tamano(0) {}

    ~LinkedList() {
        clear();
    }

    // Métodos de iteración
    Iterator begin() const {
        return Iterator(head);
    }

    Iterator end() const {
        return Iterator(nullptr);
    }

    // Métodos para obtener información
    int getTamano() const {
        return tamano;
    }

    Nodo<T>* getHead() const {
        return head;
    }

    Nodo<T>* getTail() const {
        return tail;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    // Método para extraer datos usando una función
    template <typename ResultType>
    vector<ResultType> extraerDato(function<ResultType(const T&)> requerido) const {
        vector<ResultType> datos;
        Nodo<T>* current = head;
        while (current) {
            datos.push_back(requerido(current->data));
            current = current->next;
        }
        return datos;
    }

    // Métodos para agregar elementos
    void agregarAlInicio(const T& value) {
        Nodo<T>* nuevoNodo = new Nodo<T>(value);
        if (isEmpty()) {
            head = nuevoNodo;
            tail = nuevoNodo;
        }
        else {
            nuevoNodo->next = head;
            head = nuevoNodo;
        }
        tamano++;
    }


    void agregarAlFinal(const T& value) {
        Nodo<T>* nuevoNodo = new Nodo<T>(value);
        if (isEmpty()) {
            head = nuevoNodo;
            tail = nuevoNodo;
        }
        else {
            tail->next = nuevoNodo;
            tail = nuevoNodo;
        }
        tamano++;
    }

    // Métodos para eliminar elementos
    void eliminarPrimero() {
        if (isEmpty()) return;

        Nodo<T>* temp = head;
        head = head->next;

        if (head == nullptr) {
            tail = nullptr;
        }

        delete temp;
        tamano--;
    }

    void eliminarUltimo() {
        if (isEmpty()) return;

        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
            tamano = 0;
            return;
        }

        Nodo<T>* current = head;
        while (current->next != tail) {
            current = current->next;
        }

        delete tail;
        tail = current;
        tail->next = nullptr;
        tamano--;
    }

    void eliminarPosicion(int pos) {
        if (isEmpty() || pos <= 0 || pos > tamano) return;

        if (pos == 1) {
            eliminarPrimero();
            return;
        }

        if (pos == tamano) {
            eliminarUltimo();
            return;
        }

        Nodo<T>* anterior = head;
        for (int i = 1; i < pos - 1; i++) {
            anterior = anterior->next;
        }

        Nodo<T>* temp = anterior->next;
        anterior->next = temp->next;
        delete temp;
        tamano--;
    }

    // Eliminar un nodo específico usando iterador
    void eliminar(Iterator it) {
        if (isEmpty()) return;

        Nodo<T>* nodeToDelete = it.getNode();

        // Caso especial: eliminar el primer nodo
        if (nodeToDelete == head) {
            eliminarPrimero();
            return;
        }

        // Caso especial: eliminar el último nodo
        if (nodeToDelete == tail) {
            eliminarUltimo();
            return;
        }

        // Buscar el nodo anterior
        Nodo<T>* anterior = head;
        while (anterior && anterior->next != nodeToDelete) {
            anterior = anterior->next;
        }

        if (anterior == nullptr) return; // Nodo no encontrado

        anterior->next = nodeToDelete->next;
        delete nodeToDelete;
        tamano--;
    }

    // Limpiar toda la lista
    void clear() {
        while (!isEmpty()) {
            eliminarPrimero();
        }
    }

    // Buscar por valor
    Iterator buscar(const T& value) const {
        Nodo<T>* current = head;
        while (current) {
            if (current->data == value) {
                return Iterator(current);
            }
            current = current->next;
        }
        return end();
    }

    // Verificar si existe un valor
    bool contiene(const T& value) const {
        return buscar(value) != end();
    }

    // Acceder al primer elemento
    T& primero() {
        if (isEmpty())
            throw runtime_error("Lista vacía: No hay primer elemento");
        return head->data;
    }

    const T& primero() const {
        if (isEmpty())
            throw runtime_error("Lista vacía: No hay primer elemento");
        return head->data;
    }

    // Acceder al último elemento
    T& ultimo() {
        if (isEmpty())
            throw runtime_error("Lista vacía: No hay último elemento");
        return tail->data;
    }

    const T& ultimo() const {
        if (isEmpty())
            throw runtime_error("Lista vacía: No hay último elemento");
        return tail->data;
    }
};