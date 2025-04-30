#pragma once
#include "Nodo.h"

template <typename T>
class Queue {
private:
	Nodo<T>* head;
	Nodo<T>* tail;
	int tamano;

public:
	Queue() : head(nullptr), tail(nullptr), tamano(0) {}
	~Queue() {
		while (head) {
			Nodo<T>* current = head;
			head = head->next;
			delete current;
		}
	}

	int getTamano() {
		return tamano;
	}
	void enqueue(T value) {
		Nodo<T>* nuevoNodo = new Nodo<T>(value);
		if (tail) {
			tail->next = nuevoNodo;
		}
		else {
			head = nuevoNodo;
		}
		tail = nuevoNodo;
		tamano++;
	}
	void dequeue() {
		if (head == nullptr) return;
		Nodo<T>* current = head;
		head = head->next;
		delete current;
		tamano--;
	}
	T front() {
		if (head == nullptr) return T();
		return head->data;
	}
	
	bool estaVacio() {
		return tamano == 0;
	}
};