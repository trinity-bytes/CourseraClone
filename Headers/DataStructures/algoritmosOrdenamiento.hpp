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