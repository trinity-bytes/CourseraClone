#ifndef COURSERACLONE_DATASTRUCTURES_ALGORITMOSBUSQUEDA_HPP
#define COURSERACLONE_DATASTRUCTURES_ALGORITMOSBUSQUEDA_HPP

// Funciones de algoritmos de búsqueda genéricos
template <typename Predicado>
int busquedaBinaria(int _izquierda, int _derecha, Predicado _predicado)
{
    if (_izquierda > _derecha) {
        return _izquierda;
    }
    int medio = _izquierda + (_derecha - _izquierda) / 2;
    if (_predicado(medio)) {
        return busquedaBinaria(_izquierda, medio - 1, _predicado);
    } else {
        return busquedaBinaria(medio + 1, _derecha, _predicado);
    }
}

#endif // COURSERACLONE_DATASTRUCTURES_ALGORITMOSBUSQUEDA_HPP