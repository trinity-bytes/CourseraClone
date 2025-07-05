// filepath: Headers/DataStructures/Grafo.hpp
// Grafo, permite conexiones de nodos

#ifndef COURSERACLONE_DATASTRUCTURES_GRAFO_HPP
#define COURSERACLONE_DATASTRUCTURES_GRADO_HPP

#include <vector>
#include "Queue.hpp"

template<typename T>
class Grafo {
private:
    std::vector<T> verts;
    std::vector<std::vector<int>> adj;
    std::vector<T> todos;

    // Busca linealmente el índice de un vértice T en verts
    int indexOf(const T& val) const {
        for (int i = 0; i < int(todos.size()); ++i) {
            if (todos[i] == val) return i;
        }
        return -1;
    }

public:
    Grafo(const std::vector<T>& vertices,
        const std::vector<std::vector<int>>& ady, const std::vector<T>& _todos)
        : verts(vertices), adj(ady), todos(_todos) {
    }

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


};

#endif // COURSERACLONE_DATASTRUCTURES_GRAFO_HPP