#pragma once
template <typename T>

struct Nodo {
	T data;
	Nodo* next;
	Nodo(T value) : data(value), next(nullptr) {};
};