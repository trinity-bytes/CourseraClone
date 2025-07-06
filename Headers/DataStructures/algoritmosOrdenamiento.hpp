#pragma once
#include <vector>
#include <iostream>
using namespace std;

template <typename T>
auto menorDefecto = [](T a, T b) {
	return a < b;
	};

template <typename T, typename Comp>
void merge(vector<T>& arr, int l, int r, int mid, Comp comp) {
	int n1 = mid - l + 1;
	int n2 = r - mid;

	vector<T> L(n1);
	vector<T> R(n2);

	for (int i = 0; i < n1; i++)
		L[i] = arr[l + i];

	for (int j = 0; j < n2; j++)
		R[j] = arr[mid + 1 + j];

	int i = 0, j = 0, k = l;

	while (i < n1 && j < n2) {
		if (comp(L[i], R[j])) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}

}

template < typename T, typename Comp = decltype(menorDefecto<T>) >
void mergeSort(vector<T>& arr, int l, int r, Comp comp = menorDefecto<T>) {
	if (l >= r) return;

	int mid = l + (r - l) / 2;
	mergeSort(arr, l, mid, comp);
	mergeSort(arr, mid + 1, r, comp);
	merge(arr, l, r, mid, comp);
}


template <typename T, typename Comp = decltype(menorDefecto<T>)>
void bubbleSort(vector<T>& arr, Comp comp = menorDefecto<T>) {
	int n = arr.size();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n - 1 - i; ++j) {
			if (comp(arr[j], arr[j + 1])) {
				T tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}

// Shell sort
// Usa gaps decrecientes para comparar e intercambiar elementos
template <typename T, typename Comp = decltype(menorDefecto<T>)>
void shellSort(vector<T>& arr, Comp comp = menorDefecto<T>) {
	int n = int(arr.size());
	for (int gap = n / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; ++i) {
			T temp = arr[i];
			int j = i;
			// Reemplazamos "arr[j-gap] > temp" por "comp(temp, arr[j-gap])"
			while (j >= gap && comp(temp, arr[j - gap])) {
				arr[j] = arr[j - gap];
				j -= gap;
			}
			arr[j] = temp;
		}
	}
}

template <typename T, typename Comp = decltype(menorDefecto<T>)>
void insertionSort(vector<T>& arr, Comp comp = menorDefecto<T>) {
	int n = int(arr.size());
	for (int i = 1; i < n; ++i) {
		T key = arr[i];
		int j = i - 1;
		// desplaza hacia la derecha mientras key sea "menor" que arr[j]
		while (j >= 0 && comp(key, arr[j])) {
			arr[j + 1] = arr[j];
			--j;
		}
		arr[j + 1] = key;
	}
}

template <typename T, typename Comp = decltype(menorDefecto<T>)>
void selectionSort(vector<T>& arr, Comp comp = menorDefecto<T>) {
	int n = int(arr.size());
	for (int i = 0; i < n - 1; ++i) {
		int idxMin = i;
		for (int j = i + 1; j < n; ++j) {
			if (comp(arr[j], arr[idxMin])) {
				idxMin = j;
			}
		}
		if (idxMin != i) {
			T tmp = arr[i];
			arr[i] = arr[idxMin];
			arr[idxMin] = tmp;
		}
	}
}

template <typename T, typename Comp = decltype(menorDefecto<T>)>
int partitionQS(vector<T>& arr, int low, int high, Comp comp) {
	T pivot = arr[high];
	int i = low - 1;
	for (int j = low; j < high; ++j) {
		if (comp(arr[j], pivot)) {
			++i;
			T tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
	}
	T tmp = arr[i + 1];
	arr[i + 1] = arr[high];
	arr[high] = tmp;
	return i + 1;
}

template <typename T, typename Comp = decltype(menorDefecto<T>)>
void quickSort(vector<T>& arr, int low, int high, Comp comp = menorDefecto<T>) {
	if (low < high) {
		int pi = partitionQS(arr, low, high, comp);
		quickSort(arr, low, pi - 1, comp);
		quickSort(arr, pi + 1, high, comp);
	}
}

// Sobrecarga para no tener que pasar índices
template <typename T, typename Comp = decltype(menorDefecto<T>)>
void quickSort(vector<T>& arr, Comp comp = menorDefecto<T>) {
	if (!arr.empty())
		quickSort(arr, 0, int(arr.size()) - 1, comp);
}