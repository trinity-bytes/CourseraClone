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

	template <typename KeyType, typename Pred>
	Stack<T> filtrarPorClaves(vector<KeyType>& claves, Pred pred) {
		// Primero acumulamos en buffer los elementos que coincidan
		vector<T> datos;
		Nodo<T>* current = head;
		while (current) {
			for (const auto& clave : claves) {
				if (pred(current->data, clave)) {
					datos.push_back(current->data);
					break;
				}
			}
			current = current->next;
		}
		// Para devolverlos como Stack, empujamos en orden inverso al buffer
		Stack<T> resultado;
		for (auto it = buffer.rbegin(); it != buffer.rend(); ++it) {
			datos.push(*it);
		}
		return resultado;
	}

	T get(int index) {
		if (index < 0 || index >= tamano) {
			throw std::out_of_range("Índice fuera de rango en Stack::get");
		}
		Nodo<T>* actual = head;
		for (int i = 0; i < index; ++i) {
			actual = actual->next;
		}
		return actual->data;
	}

	bool estaVacio() {
		return tamano == 0;
	}

	void cargarDesdeLista(LinkedList<T> lista) {
		clear();
		// Extraer todos los valores de la lista en un vector
		vector<T> valores = lista.extraerDato([](const T& v) { return v; });
		// Apilar en orden inverso para preservar el orden original de la lista
		for (auto it = valores.rbegin(); it != valores.rend(); ++it) {
			push(*it);
		}
	}
};