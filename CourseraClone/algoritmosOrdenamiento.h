#pragma once
#include <vector>
#include <iostream>
using namespace std;

template <typename T>
void merge(vector<T>& arr, int l, int r, int mid) {
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
		if (L[i] <= R[j]) {
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

template <typename T>
void mergeSort(vector<T>& arr, int l, int r) {
	if (r - l == 1) return;

	int mid = l + (r - l) / 2;
	mergeSort(arr, l, mid);
	mergeSort(arr, mid + 1, r);
	merge(arr, l, r, mid);
}

template <typename T>
void bubbleSort(vector<T>& arr) {
	int n = arr.size();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n - 1 - i; ++j) {
			if (arr[j] > arr[j + 1]) {
				T tmp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = tmp;
			}
		}
	}
}

// Shell sort
// Usa gaps decrecientes para comparar e intercambiar elementos
template <typename T>
void shellSort(vector<T>& arr) {
	int n = arr.size();
	for (int gap = n / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < n; ++i) {
			T temp = arr[i];
			int j = i;
			while (j >= gap && arr[j - gap] > temp) {
				arr[j] = arr[j - gap];
				j -= gap;
			}
			arr[j] = temp;
		}
	}
}


