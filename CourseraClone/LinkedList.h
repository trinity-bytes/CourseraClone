#pragma once
#include "Nodo.h"

template <typename T>
class LinkedList {
private:
	Nodo<T>* head;
	Nodo<T>* tail;
	int tamano;

public:
	LinkedList() : head(nullptr), tamano(0) {}
	~LinkedList() {
		while (head) {
			Nodo<T>* current = head;
			head = head->next;
			delete current;
		}
	}

	int getTamano() {
		return tamano;
	}

	vector<int> getID() {
		Nodo<T>* current = head;
		vector<int> ids;

		if (current != nullptr) {
			ids.push_back(current->data.getId());
			current = current->next;
		}
		return ids;
	}

	void agregarAlInicio(T value) {
		Nodo<T>* nuevoNodo = new Nodo<T>(value);
		nuevoNodo->next = head;
		head = nuevoNodo;
		tamano++;
	}

	void agregarAlFinal() {
		Nodo<T>* nuevoNodo = new Nodo<T>(value);
		if (head == nullptr) {
			head = nuevoNodo;
		}
		else {
			tail->next = nuevoNodo;
		}

		tail = nuevoNodo;
		tamano++;
	}

	void eliminarPosicion(int pos) {
		int contador = 2;

		if (head == nullptr) return;

		Nodo<T>* current = head;

		if (pos == 1) {
			head = head->next;
			delete current;
			return;
		}

		while (current->next != nullptr) {
			if (contador == pos) {
				Nodo<T>* temp = current->next;
				current->next = current->next->next;
				delete temp;
				return;
			}
			contador++;
			current = current->next;
		}
	}
	
};