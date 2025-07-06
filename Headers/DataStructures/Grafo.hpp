// filepath: Headers/DataStructures/Grafo.hpp
// Grafo, permite conexiones de nodos

#ifndef COURSERACLONE_DATASTRUCTURES_GRAFO_HPP
#define COURSERACLONE_DATASTRUCTURES_GRADO_HPP

#include <vector>
#include "Queue.hpp"


template<typename U>
struct DefaultEqual {
    bool operator()(const U& a, const U& b) const {
        return a == b;
    }
};

template<
    typename T,
    typename Eq = DefaultEqual<T>
>

class Grafo {
private:
    std::vector<T> verts;
    std::vector<std::vector<int>> adj;
    std::vector<T> todos;
	Eq equal;

    // Busca linealmente el índice de un vértice T en verts
    int indexOf(const T& val) const {
        for (int i = 0; i < int(todos.size()); ++i) {
            if (equal(todos[i], val)) return i;
        }
        return -1;
    }

public:
    Grafo(const std::vector<T>& vertices,
        const std::vector<std::vector<int>>& ady, const std::vector<T>& _todos, Eq eq = Eq())
        : verts(vertices), adj(ady), todos(_todos), equal(eq) {
    }

    const std::vector<T>& getTodos() const {
        return todos;
    }

	const std::vector<T>& getVertices() const {
		return verts;
	}

	const std::vector<std::vector<int>>& getListaAdyacencia() const {
		return adj;
	}

    /** Comprueba existencia de un vértice. */
    bool tieneVertice(const T& v) const {
        return indexOf(v) >= 0;
    }

    void addVertice(const T& v) {
        if (!hasVertice(v)) {
            todos.push_back(v);
            adj.emplace_back();
        }
    }

    /** Añade arista dirigida u->w (agrega vértices si faltan). */
    void addEdge(const T& u, const T& w) {
        int iu = indexOf(u);
        if (iu < 0) { addVerttice(u); iu = int(todos.size()) - 1; }
        int iw = indexOf(w);
        if (iw < 0) { addVertice(w); iw = int(todos.size()) - 1; }
        adj[iu].push_back(iw);
    }

	// Expande los vértices usando BFS, comenzando desde los vértices en verts
    std::vector<T> bfsExpand() const {
        std::vector<T> res = verts;
        int n = todos.size();
        std::vector<bool> visto(n, false);
        Queue<int> q;

        // Marca e inserta los iniciales
        for (auto const& v : res) {
            int idx = indexOf(v);
            if (idx >= 0 && !visto[idx]) {
                visto[idx] = true;
                q.enqueue(idx);
            }
        }

        // BFS
        while (!q.estaVacio()) {
            int u = q.front(); q.dequeue();
            if (u < 0 || u >= int(adj.size())) continue;
            for (int w : adj[u]) {
                if (w >= 0 && w < int(n) && !visto[w]) {
                    visto[w] = true;
                    res.push_back(todos[w]);
                    q.enqueue(w);
                }
            }
        }

        // Falta
        for (int i = 0; i < n; i++) {
            if (!visto[i]) {
                res.push_back(todos[i]);
            }
        }

        return res;
    }

    /** BFS para saber si hay camino from->to. */
    bool pathExists(const T& from, const T& to) const {
        int iFrom = indexOf(from);
        int iTo = indexOf(to);
        if (iFrom < 0 || iTo < 0) return false;
        int n = int(todos.size());
        std::vector<bool> visto(n, false);
        Queue<int> q;
        visto[iFrom] = true;
        q.enqueue(iFrom);
        while (!q.estaVacio()) {
            int u = q.dequeue();
            if (u == iTo) return true;
            for (int w : adj[u]) {
                if (!visto[w]) {
                    visto[w] = true;
                    q.enqueue(w);
                }
            }
        }
        return false;
    }


};

#endif // COURSERACLONE_DATASTRUCTURES_GRAFO_HPP