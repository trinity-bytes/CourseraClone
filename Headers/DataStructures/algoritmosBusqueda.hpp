// filepath: Headers/DataStructures/AlgoritmosBusqueda.hpp
// Descripcion: Funciones de algoritmos de búsqueda genéricos.

#ifndef COURSERACLONE_HEADERS_DATASTRUCTURES_ALGORITMOSBUSQUEDA_HPP
#define COURSERACLONE_HEADERS_DATASTRUCTURES_ALGORITMOSBUSQUEDA_HPP

template <typename Pred>
int busquedaBinaria(int l, int r, Pred pred)
{
    if (l > r)
    {
        return l;  // este es el punto de inserción
    }
    int m = l + (r - l) / 2;
    if (pred(m))
    {
        return busquedaBinaria(l, m - 1, pred);
    }
    else
    {
        return busquedaBinaria(m + 1, r, pred);
    }
}

#endif // COURSERACLONE_HEADERS_DATASTRUCTURES_ALGORITMOSBUSQUEDA_HPP