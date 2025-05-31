#pragma once
#include "BinaryHeap.h"
#include "LinkedList.h"
#include <algorithm>

using namespace std;

template <typename T, typename Comparador = comparadorDefecto<T> >
class PriorityQueue {
private:
	BinaryHeap<T, Comparador> monticulo;
	int tamano, tamanoMaximo;

public:
	PriorityQueue(int _tamanoMaximo = 3, Comparador comp = Comparador()) : tamano(0), tamanoMaximo(_tamanoMaximo), monticulo(comp) {}

	void enqueue(T valor) {
		monticulo.insertar(valor);
		tamano++;
	}

	T dequeue() {
		if (estaVacio()) return T();
		return monticulo.extraerRaiz();
	}

	T front() {
		if (estaVacio()) return T();
		return monticulo.obtenerRaiz();
	}

	~PriorityQueue() {
		while (!monticulo.estaVacio()) {
			T nuevo = monticulo.extraerRaiz();
		}
	}

	void eliminarExceso() {
		while (tamano > tamanoMaximo) {
			monticulo.eliminarRaiz();
			tamano--;
		}
	}

	void llenarDesde(LinkedList<T>& lista) {
		Nodo<T>* current = lista.getHead();
		while (current != nullptr) {
			enqueue(current->data);
			current = current->next;
		}
		tamano = lista.getTamano();
		eliminarExceso();
	}
	
	template <typename valor, typename metodoConseguir>
	vector<valor> extraerDato(metodoConseguir requerido) {
		vector<T> clasesBase = monticulo.getElementos();
		vector<valor> resultado;
		for (int i = 0; i < monticulo.tamano(); i++) {
			resultado.push_back(requerido(clasesBase[i]));
		}

		return resultado;
	}

	vector<T> getElementos() {
		return monticulo.getElementos();
	}

	void ordenar() {
		monticulo.ordenar();
	}

	vector<T> getElementosOrdenados() {
		vector<T> elementos = monticulo.getElementos();
		sort(elementos.begin(), elementos.end(), Comparador()); // agregar metodo de sort
		return elementos;
	}

	int getTamano() {
		return tamano;
	}
	bool estaVacio() {
		return tamano == 0;
	}
};