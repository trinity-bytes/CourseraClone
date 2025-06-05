#pragma once
template <typename C, typename V>
class ArbolBinarioBusqueda {
private:
	struct Nodo {
		C clave;
		V valor;
		Nodo* izquierdo;
		Nodo* derecho;
		Nodo(const C& c, const V& v) : clave(c), valor(v), izquierdo(nullptr),
			derecho(nullptr) {
		}
	};
	Nodo* raiz;
	Nodo* insertarRecursivo(Nodo* nodo, const C& clave, const V& valor) {
		if (!nodo) {
			return new Nodo(clave, valor);
		}
		if (clave < nodo->clave) {
			nodo->izquierdo = insertarRecursivo(nodo->izquierdo, clave, valor);
		}
		else if (clave > nodo->clave) {
			nodo->derecho = insertarRecursivo(nodo->derecho, clave, valor);
		}
		else {
			// Claves duplicadas: opcionalmente actualizar valor o lanzar error
			nodo->valor = valor;
		}
		return nodo;
	}
	Nodo* buscarRecursivo(Nodo* nodo, const C& clave) const {
		if (!nodo || nodo->clave == clave) {
			return nodo;
		}
		if (clave < nodo->clave) {
			return buscarRecursivo(nodo->izquierdo, clave);
		}
		return buscarRecursivo(nodo->derecho, clave);
	}
	void destruirRecursivo(Nodo* nodo) {
		if (nodo) {
			destruirRecursivo(nodo->izquierdo);
			destruirRecursivo(nodo->derecho);
			delete nodo;
		}
	}
public:
	ArbolBinarioBusqueda() : raiz(nullptr) {}
	~ArbolBinarioBusqueda() {
		destruirRecursivo(raiz);
	}
	void insertar(const C& clave, const V& valor) {
		raiz = insertarRecursivo(raiz, clave, valor);
	}
	V* buscar(const C& clave) const {
		Nodo* encontrado = buscarRecursivo(raiz, clave);
		return encontrado ? &(encontrado->valor) : nullptr;
	}

};