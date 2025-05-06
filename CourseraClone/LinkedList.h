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

	Nodo<T>* getHead() {
		return head;
	}

	template <typename valor, typename metodoConseguir>
	vector<valor> extraerDato(metodoConseguir requerido) {
		vector<valor> datos;
		Nodo<T>* current = head;
		while (current) {
			datos.push_back(requerido(current->data));
			current = current->next;
		}
		return datos;
	}

	void agregarAlInicio(T value) {
		Nodo<T>* nuevoNodo = new Nodo<T>(value);
		nuevoNodo->next = head;
		head = nuevoNodo;
		tamano++;
	}

	void agregarAlFinal(T value) {
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