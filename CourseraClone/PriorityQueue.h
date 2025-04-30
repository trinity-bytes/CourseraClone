#pragma once
#include "Nodo.h"

template <typename T, typename O> // O representa el tipo de variable por el cual decidimos el orden
class PriorityQueue {
private:
	Nodo<T>* head;
	Nodo<T>* tail;
	int tamano;
	const int tamanoMaximo;

public:
	PriorityQueue() : head(nullptr), tail(nullptr), tamano(0), tamanoMaximo(10) {}
	PriorityQueue(int _tamanoMaximo) : head(nullptr), tail(nullptr), tamano(0), tamanoMaximo(_tamanoMaximo) {}
	~PriorityQueue() {
		while (head) {
			Nodo<T>* current = head;
			head = head->next;
			delete current;
		}
	}

	int getTamano() {
		return tamano;
	}

	void eliminarExceso() {
		if (tamano > tamanoMaximo) {
			Nodo<T>* current = head;
			if (current->next == nullptr) {
				delete head;
				head = nullptr;
			}
			else {
				while (current->next->next != nullptr) {
					current = current->next;
				}
				delete current->next;
				current->next = nullptr;
				tail = current;
			}
			tamano--;
		}
	}

	void enqueue(T nodoAgregar) {
		Nodo<T>* nuevoNodo = new Nodo<T>;
		nuevoNodo->data = nodoAgregar;
		O val = nodoAgregar.getValorOrden();

		if (head == nullptr || head->data.getValorOrden() < val) {
			nuevoNodo->next = head;
			head = nuevoNodo;
		}
		else {
			Nodo<T>* current = head;
			O valAhora = current->next->data.getValorOrden();
			while (current->next != nullptr && valAhora >= val) {
				current = current->next;
			}
			nuevoNodo->next = current->next;
			current->next = nuevoNodo;
		}
		tamano++;

		eliminarExceso();
	}

	T dequeue() {
		if (head == nullptr) return T();
		T valor = head->data;
		Nodo<T>* temp = head;
		head = head->next;
		delete temp;
		tamano--;
		return valor;
	}

	int getTamano() {
		return tamano;
	}
	bool estaVacio() {
		return tamano == 0;
	}
};