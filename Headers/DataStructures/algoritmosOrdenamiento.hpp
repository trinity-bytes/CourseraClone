// filepath: Headers/DataStructures/algoritmosOrdenamiento.hpp
// Algoritmos de ordenamiento genéricos para diferentes tipos de datos

#ifndef COURSERACLONE_DATASTRUCTURES_ALGORITMOSORDENAMIENTO_HPP
#define COURSERACLONE_DATASTRUCTURES_ALGORITMOSORDENAMIENTO_HPP

// Includes del sistema
#include <vector>
#include <iostream>

// Fusionar dos subarreglos ordenados
template <typename T>
void merge(std::vector<T>& _arreglo, int _izquierda, int _derecha, int _medio)
{
    int n1 = _medio - _izquierda + 1;
    int n2 = _derecha - _medio;

    std::vector<T> izq(n1);
    std::vector<T> der(n2);

    // Copiar datos a arreglos temporales
    for (int i = 0; i < n1; i++)
    {
        izq[i] = _arreglo[_izquierda + i];
    }

    for (int j = 0; j < n2; j++)
    {
        der[j] = _arreglo[_medio + 1 + j];
    }

    // Fusionar los arreglos temporales de vuelta al arreglo original
    int i = 0, j = 0, k = _izquierda;

    while (i < n1 && j < n2)
    {
        if (izq[i] <= der[j])
        {
            _arreglo[k] = izq[i];
            i++;
        }
        else
        {
            _arreglo[k] = der[j];
            j++;
        }
        k++;
    }

    // Copiar elementos restantes de izq[], si los hay
    while (i < n1)
    {
        _arreglo[k] = izq[i];
        i++;
        k++;
    }

    // Copiar elementos restantes de der[], si los hay
    while (j < n2)
    {
        _arreglo[k] = der[j];
        j++;
        k++;
    }
}

// Algoritmo Merge Sort recursivo
template <typename T>
void mergeSort(std::vector<T>& _arreglo, int _izquierda, int _derecha)
{
    if (_izquierda >= _derecha) return;

    int medio = _izquierda + (_derecha - _izquierda) / 2;
    mergeSort(_arreglo, _izquierda, medio);
    mergeSort(_arreglo, medio + 1, _derecha);
    merge(_arreglo, _izquierda, _derecha, medio);
}

// Algoritmo Bubble Sort
template <typename T>
void bubbleSort(std::vector<T>& _arreglo)
{
    int n = _arreglo.size();
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n - 1 - i; ++j)
        {
            if (_arreglo[j] > _arreglo[j + 1])
            {
                T temporal = _arreglo[j];
                _arreglo[j] = _arreglo[j + 1];
                _arreglo[j + 1] = temporal;
            }
        }
    }
}

// Algoritmo Shell Sort usando gaps decrecientes
template <typename T>
void shellSort(std::vector<T>& _arreglo)
{
    int n = _arreglo.size();
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; ++i)
        {
            T temporal = _arreglo[i];
            int j = i;
            while (j >= gap && _arreglo[j - gap] > temporal)
            {
                _arreglo[j] = _arreglo[j - gap];
                j -= gap;
            }
            _arreglo[j] = temporal;
        }
    }
}

#endif // COURSERACLONE_DATASTRUCTURES_ALGORITMOSORDENAMIENTO_HPP


