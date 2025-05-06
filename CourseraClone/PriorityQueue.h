#pragma once
#include "Nodo.h"
#include "vector"

using namespace std;

template <typename T>
class PriorityQueue {
private:
	Nodo<T>* head;
	Nodo<T>* tail;
	int tamano;
	const int tamanoMaximo;

public:
	PriorityQueue(int _tamanoMaximo) : head(nullptr), tail(nullptr), tamano(0), tamanoMaximo(_tamanoMaximo) {}
	PriorityQueue() : head(nullptr), tail(nullptr), tamano(0), tamanoMaximo(10) {}
	~PriorityQueue() {
		while (head) {
			Nodo<T>* current = head;
			head = head->next;
			delete current;
		}
	}

	void eliminarExceso() {
		if (tamano > tamanoMaximo) {
			Nodo<T>* current = head;
			if (current->next == nullptr) {
				delete current;
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

	template <typename valor, typename metodoOrden>
	void enqueue(T nodoAgregar, metodoOrden requerido) {
		Nodo<T>* nuevoNodo = new Nodo<T>(nodoAgregar);
		valor val = requerido(nuevoNodo->data);

		if (head == nullptr || requerido(head->data) < val) {
			nuevoNodo->next = head;
			head = nuevoNodo;
		}
		else {
			Nodo<T>* current = head;
			while (current->next != nullptr && requerido(current->next->data) >= val) {
				current = current->next;
			}
			nuevoNodo->next = current->next;
			current->next = nuevoNodo;
		}
		tamano++;

		eliminarExceso();
	}

	template <typename valor, typename metodoOrden>
	void llenarDesde(LinkedList<T>& lista, metodoOrden requerido) {
		Nodo<T>* current = lista.getHead();
		while (current != nullptr) {
			enqueue<valor>(current->data, requerido);
			current = current->next;
		}
	}


	template <typename valor, typename metodoConseguir>
	vector<valor> extraerDato(metodoConseguir requerido) {
		vector<valor> datos;
		Nodo<T>* current = head;
		while (current != nullptr) {
			datos.push_back(requerido(current->data)); 
			current = current->next;
		}
		return datos;
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