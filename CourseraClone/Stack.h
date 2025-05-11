#pragma once
#include "Nodo.h"

template <typename T>
class Stack {
private:
	Nodo<T>* head;
	int tamano;
	
private:
	void eliminarDatos() {
		while (head) {
			Nodo<T>* current = head;
			head = head->next;
			delete current;
		}
	}

public:
	Stack() : head(nullptr), tamano(0) {}
	~Stack() {
		eliminarDatos();
	}

	T get(int index) {
		if (index < 0 || index >= tamano) {
			throw out_of_range("Índice fuera de rango en Stack::get");
		}
		Nodo<T>* actual = head;
		for (int i = 0; i < index; ++i) {
			actual = actual->next;
		}
		return actual->data; // Aquí está el problema
	}

	int getTamano() {
		return tamano;
	}

	void push(T value) {
		Nodo<T>* nuevoNodo = new Nodo<T>(value);
		nuevoNodo->next = head;
		head = nuevoNodo;
		tamano++;
	}

	void pop() {
		if (head == nullptr) return;
		Nodo<T>* current = head;
		head = head->next;
		delete current;
		tamano--;
	}

	T top() {
		if (head == nullptr) return T();
		return head->data;
	}

	void clear() {
		eliminarDatos();
		tamano = 0;
	}

	bool eliminarPosicion(int pos) {
		if (pos < 1 || pos > tamano || head == nullptr) return false;

		Stack<T> temporal;

		for (int i = 1; i < pos; ++i) {
			temporal.push(top());
			pop();
		}

		pop();

		while (!temporal.estaVacio()) {
			push(temporal.top());
			temporal.pop();
		}

		return true;
	}

	bool estaVacio() {
		return tamano == 0;
	}
	
	
};